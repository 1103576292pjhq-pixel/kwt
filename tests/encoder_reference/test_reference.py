"""Independent checks for frozen arithmetic and complete stage topology."""
import ctypes as C
import math
import os
from pathlib import Path
import struct
import subprocess
import unittest
import numpy as np

ROOT = Path(__file__).resolve().parents[2]
F = C.POINTER(C.c_float)
CB = C.CFUNCTYPE(None, C.c_void_p, C.c_uint, F, C.c_size_t, C.c_size_t)


def build(path):
    source=Path(os.environ.get('KWT_ENCODER_REFERENCE_SOURCE',str(ROOT/'numeric/encoder/encoder_ref.c')))
    subprocess.run(["gcc", "-std=c11", "-O2", "-ffp-contract=off", "-fno-fast-math",
                    "-Wall", "-Wextra", "-Werror", "-fPIC", "-shared",
                    '-I',str(ROOT/'numeric/encoder'),str(source), "-lm", "-o", str(path)], check=True)


def pointer(a):
    return a.ctypes.data_as(F)


class ReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        report = ROOT / "reports/encoder/reference/tests"
        report.mkdir(parents=True, exist_ok=True)
        cls.so = report / "libreference_test.so"
        build(cls.so)
        cls.lib = C.CDLL(str(cls.so))
        for name in ("kwt_exp_neg", "kwt_gelu"):
            fn = getattr(cls.lib, name)
            fn.argtypes = [C.c_float]
            fn.restype = C.c_float
        cls.lib.kwt_weight_words.argtypes = [C.c_size_t, C.c_size_t]
        cls.lib.kwt_weight_words.restype = C.c_size_t
        cls.lib.kwt_encoder_layer.argtypes = [C.c_size_t]*3+[F,F,F,CB,C.c_void_p]
        cls.lib.kwt_encoder_layer.restype = C.c_int
        cls.lib.kwt_classifier.argtypes = [C.c_size_t,C.c_size_t,F,F,F,F]

    def test_exp_known_values_and_boundaries(self):
        for x in (0., -0., -1., -0.125, -12., -79.):
            self.assertLessEqual(abs(self.lib.kwt_exp_neg(x)-math.exp(x)), 3e-7*math.exp(x))
        self.assertEqual(self.lib.kwt_exp_neg(-80.), 0.)
        self.assertEqual(self.lib.kwt_exp_neg(-1000.), 0.)

    def test_gelu_independent_erf(self):
        for x in np.linspace(-10,10,1001):
            exact = 0.5*float(x)*(1+math.erf(float(x)/math.sqrt(2)))
            self.assertLess(abs(self.lib.kwt_gelu(x)-exact), 0.00048)
        self.assertEqual(self.lib.kwt_gelu(11.), 11.)
        self.assertEqual(struct.pack('<f', self.lib.kwt_gelu(-11.)), b'\0\0\0\x80')

    def test_packed_words(self):
        self.assertEqual(self.lib.kwt_weight_words(64,256),49792)
        self.assertEqual(self.lib.kwt_weight_words(4,8),160)

    def test_zero_layer_complete_topology(self):
        m,d,h=3,4,8
        x=np.zeros((m,d),np.float32)
        w=np.zeros(160,np.float32)
        y=np.full_like(x,np.nan)
        stages={}
        @CB
        def callback(ctx,stage,values,rows,cols):
            stages[stage]=np.ctypeslib.as_array(values,shape=(rows*cols,)).copy().reshape(rows,cols)
        rc=self.lib.kwt_encoder_layer(m,d,h,pointer(x),pointer(w),pointer(y),callback,None)
        self.assertEqual(rc,0)
        self.assertEqual(set(stages),set(range(14)))
        np.testing.assert_array_equal(y,0)
        np.testing.assert_allclose(stages[4],np.float32(1/3),rtol=0,atol=0)

    def test_classifier_hand_computed(self):
        x=np.array([1.,2.,-3.,4.],np.float32)
        w=np.array([[1.,0.],[0.,2.],[1.,1.],[-1.,0.]],np.float32)
        b=np.array([0.5,-1.],np.float32)
        y=np.zeros(2,np.float32)
        self.lib.kwt_classifier(4,2,pointer(x),pointer(w),pointer(b),pointer(y))
        np.testing.assert_array_equal(y,[-5.5,0.])

    def call_layer(self,x,w,h=8):
        m,d=x.shape;y=np.empty_like(x);stages={}
        @CB
        def callback(ctx,stage,values,rows,cols):
            stages[stage]=np.ctypeslib.as_array(values,shape=(rows*cols,)).copy().reshape(rows,cols)
        self.assertEqual(self.lib.kwt_encoder_layer(m,d,h,pointer(x),pointer(w),pointer(y),callback,None),0)
        return y,stages

    def test_attention_identity_and_axes(self):
        x=np.array([[1,0,-1,2],[0,1,1,0],[-1,1,0,-1]],np.float32)
        w=np.zeros(160,np.float32)
        for offset in (0,16,32,48):w[offset:offset+16]=np.eye(4,dtype=np.float32).reshape(-1)
        _,stages=self.call_layer(x,w)
        for stage in (0,1,2):np.testing.assert_array_equal(stages[stage],x)
        scores=x.astype(np.float64)@x.astype(np.float64).T/8
        prob=np.exp(scores-scores.max(axis=1,keepdims=True));prob/=prob.sum(axis=1,keepdims=True)
        np.testing.assert_array_equal(stages[3],scores)
        np.testing.assert_allclose(stages[4],prob,rtol=3e-7,atol=3e-8)
        np.testing.assert_allclose(stages[5],prob@x.astype(np.float64),rtol=5e-7,atol=1e-7)
        np.testing.assert_array_equal(stages[6],stages[5])

    def test_norm_centered_variance_and_second_residual(self):
        x=np.full((3,4),3,np.float32)
        w=np.zeros(160,np.float32)
        # Layout d4/h8: bo64,gamma1=68,beta1=72,W1=76,b1=108,
        # W2=116,b2=148,gamma2=152,beta2=156.
        beta=np.array([-1,0,1,2],np.float32)
        gamma2=np.array([1,2,3,4],np.float32)
        beta2=np.array([-.1,.2,.3,.4],np.float32)
        w[68:72]=1;w[72:76]=beta;w[152:156]=gamma2;w[156:160]=beta2
        y,stages=self.call_layer(x,w)
        np.testing.assert_array_equal(stages[8],np.tile(beta,(3,1)))
        np.testing.assert_array_equal(stages[12],stages[8])
        centered=beta.astype(np.float64)-.5
        expected=centered/math.sqrt(1.25+1e-6)*gamma2+beta2
        np.testing.assert_allclose(y,np.tile(expected,(3,1)),rtol=3e-7,atol=1e-7)

    def test_exp_domain_rejected(self):
        for x in (1.,float('inf'),float('-inf'),float('nan')):
            self.assertTrue(math.isnan(self.lib.kwt_exp_neg(x)))

    def test_classifier_explicit_fma_cancellation(self):
        x=np.array([-1.,1+2**-23],np.float32)
        w=np.array([1.,1-2**-23],np.float32)
        b=np.zeros(1,np.float32);y=np.zeros(1,np.float32)
        self.lib.kwt_classifier(2,1,pointer(x),pointer(w),pointer(b),pointer(y))
        self.assertEqual(float(y[0]),-2**-46)

    def test_dimensions_rejected_before_access(self):
        x=np.zeros(1,np.float32);w=x.copy();y=x.copy()
        callback=CB(lambda *args:None)
        for m,d,h in ((0,4,8),(100,4,8),(3,0,8),(3,65,8),(3,4,0),(3,4,257)):
            self.assertEqual(self.lib.kwt_encoder_layer(m,d,h,pointer(x),pointer(w),pointer(y),callback,None),-1)

if __name__ == '__main__':
    unittest.main()
