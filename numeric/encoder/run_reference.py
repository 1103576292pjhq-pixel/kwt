"""Compile, execute, export and independently repeat the frozen C reference."""
import argparse
import ctypes as C
import json
import math
import os
from pathlib import Path
import platform
import subprocess
import sys
import time
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.encoder.contracts import STAGES,layout,sha,write_array,json_write,metrics

FP=C.POINTER(C.c_float)
CALLBACK=C.CFUNCTYPE(None,C.c_void_p,C.c_uint,FP,C.c_size_t,C.c_size_t)


class Reference:
    def __init__(self,output):
        output.mkdir(parents=True,exist_ok=True)
        library=output/'libencoder_ref.so'
        self.command=['gcc','-std=c11','-O2','-ffp-contract=off','-fno-fast-math',
                      '-Wall','-Wextra','-Werror','-fPIC','-shared',
                      str(ROOT/'numeric/encoder/encoder_ref.c'),'-lm','-o',str(library)]
        built=subprocess.run(self.command,capture_output=True,text=True)
        (output/'build.log').write_text(built.stdout+built.stderr,encoding='utf-8')
        built.check_returncode()
        self.lib=C.CDLL(str(library))
        self.lib.kwt_encoder_layer.argtypes=[C.c_size_t]*3+[FP,FP,FP,CALLBACK,C.c_void_p]
        self.lib.kwt_encoder_layer.restype=C.c_int
        self.lib.kwt_classifier.argtypes=[C.c_size_t,C.c_size_t,FP,FP,FP,FP]
        for fn in ('kwt_exp_neg','kwt_gelu'):
            getattr(self.lib,fn).argtypes=[C.c_float];getattr(self.lib,fn).restype=C.c_float
        self.library_hash=sha(library)
        # Conversion to integer in range reduction requires round-to-nearest.
        libc=C.CDLL(None)
        if libc.fegetround()!=0:
            raise ValueError('host float rounding mode must be FE_TONEAREST')

    @staticmethod
    def ptr(a):return a.ctypes.data_as(FP)

    def layer(self,x,w,h):
        x=np.ascontiguousarray(x,dtype=np.float32)
        w=np.ascontiguousarray(w,dtype=np.float32)
        m,d=x.shape
        if w.size!=4*d*d+2*d*h+h+6*d:
            raise ValueError('wrong packed length')
        y=np.empty_like(x);stages={}
        @CALLBACK
        def callback(context,index,values,rows,cols):
            stages[STAGES[index]]=np.ctypeslib.as_array(values,shape=(rows*cols,)).copy().reshape(rows,cols)
        result=self.lib.kwt_encoder_layer(m,d,h,self.ptr(x),self.ptr(w),self.ptr(y),callback,None)
        if result!=0 or set(stages)!=set(STAGES):
            raise ValueError('C reference rejected input/stages rc='+str(result))
        return y,stages

    def classify(self,cls,kernel,bias):
        y=np.empty(bias.size,dtype=np.float32)
        self.lib.kwt_classifier(cls.size,bias.size,self.ptr(cls),self.ptr(kernel),self.ptr(bias),self.ptr(y))
        return y


def constants():
    values={'positive_zero':0.,'negative_zero':-0.,'one':1.,'negative_two':-2.,'attention_scale':0.125,
            'inverse_d64':1/64,'epsilon':1e-6,'log2e':1.4426950408889634,
            'ln2_hi':0.693145751953125,'ln2_lo':1.428606765330187e-6,
            'gelu_cubic':0.044715,'sqrt_2_over_pi':0.7978845608028654,
            'exp_cutoff':-80.,'gelu_cutoff':10.}
    values.update({'exp_c'+str(k):1/math.factorial(k) for k in range(9)})
    return {k:{'float32':float(np.float32(v)),'bits':'{:08x}'.format(int(np.float32(v).view(np.uint32)))}
            for k,v in values.items()}


def nonlinear_validation(ref):
    # Fixed-formula verification sweep, not coefficient/architecture search.
    exp_x=np.linspace(-79.999,0,100001,dtype=np.float32)
    exp_y=np.array([ref.lib.kwt_exp_neg(float(x)) for x in exp_x],dtype=np.float64)
    exp_e=np.exp(exp_x.astype(np.float64))
    rel=np.abs(exp_y-exp_e)/exp_e
    gx=np.linspace(-10,10,40001,dtype=np.float32)
    gy=np.array([ref.lib.kwt_gelu(float(x)) for x in gx],dtype=np.float64)
    ge=np.array([0.5*float(x)*(1+math.erf(float(x)/math.sqrt(2))) for x in gx])
    absdiff=np.abs(gy-ge)
    if not np.isfinite(exp_y).all() or not np.isfinite(gy).all():raise ValueError('nonfinite nonlinear')
    return {'purpose':'Fixed formula verification, no parameter search or training',
            'exp':{'count':int(exp_x.size),'range':[-79.999,0],
                   'max_relative':float(rel.max()),'max_abs':float(np.max(np.abs(exp_y-exp_e))),
                   'worst_x':float(exp_x[int(rel.argmax())]),
                   'clamp_abs_bound_at_minus80':math.exp(-80)},
            'gelu_vs_exact_erf':{'count':int(gx.size),'range':[-10,10],
                                'max_abs':float(absdiff.max()),'worst_x':float(gx[int(absdiff.argmax())]),
                                'rmse':float(np.sqrt(np.mean(absdiff**2)))}}


def emit_layer(output,directory,x,w,h,ref,expected=None):
    y,stages=ref.layer(x,w,h)
    item={'input':write_array(output,directory+'/input',x),'stages':{},'comparisons':{}}
    for name in STAGES:
        item['stages'][name]=write_array(output,directory+'/'+name,stages[name])
        if expected is not None:item['comparisons'][name]=metrics(stages[name],expected[name])
    return y,item


def make_fixtures(output,ref):
    rng=np.random.default_rng(20261015)
    m,d,h=3,4,8
    x=rng.uniform(-1,1,(m,d)).astype(np.float32)
    w=rng.uniform(-0.2,0.2,160).astype(np.float32)
    for e in layout(d,h):
        if e['name'].endswith('gamma'):
            w[e['offset_words']:e['offset_words']+e['words']]=rng.uniform(.8,1.2,d).astype(np.float32)
    result=[]
    for name,xx,ww in [('small_3_4_8',x,w),('small_zero_3_4_8',np.zeros_like(x),np.zeros_like(w))]:
        directory='fixtures/'+name
        yy,item=emit_layer(output,directory,xx,ww,h,ref)
        item.update(name=name,m=m,d=d,h=h,weight_layout=layout(d,h),
                    weights=write_array(output,directory+'/weights',ww),
                    final=write_array(output,directory+'/final',yy))
        result.append(item)
    return result


def inventory(manifest):
    result={}
    def walk(obj):
        if isinstance(obj,dict):
            if 'bits_sha256' in obj:result[obj['bin']]=obj['bits_sha256']
            for value in obj.values():walk(value)
        elif isinstance(obj,list):
            for value in obj:walk(value)
    walk(manifest)
    return result


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--export',type=Path,default=ROOT/'reports/encoder/export')
    parser.add_argument('--output',type=Path,default=ROOT/'reports/encoder/reference')
    parser.add_argument('--compare',type=Path)
    args=parser.parse_args()
    output=args.output.resolve();export=args.export.resolve()
    if (ROOT/'reports/encoder').resolve() not in output.parents:raise ValueError('unsafe output')
    if (output/'manifest.json').exists():(output/'manifest.json').unlink()
    json_write(output/'status.json',{'status':'RUNNING','started_unix':time.time()})
    official=json.loads((export/'manifest.json').read_text(encoding='utf-8'))
    if official['status']!='PASS' or official['parameter_count']!=607308:raise ValueError('invalid export')
    for path,expected in official['source_hashes'].items():
        if sha(ROOT/path)!=expected:raise ValueError('stale export source: '+path)
    def load(meta):
        if sha(export/meta['npy'])!=meta['npy_sha256']:raise ValueError('stale export array')
        return np.load(str(export/meta['npy']),allow_pickle=False)
    ref=Reference(output)
    gcc=subprocess.run(['gcc','--version'],capture_output=True,text=True,check=True).stdout.splitlines()[0]
    manifest={'schema_version':1,'status':'PASS','numeric_contract':'formal_seven_design.md deterministic scalar binary32',
              'design_sha256':sha(ROOT/'work/formal_seven_design.md'),
              'export_manifest_sha256':sha(export/'manifest.json'),'source_hashes':{},
              'shape':official['shape'],'stages':list(STAGES),'weight_layout':layout(),
              'labels':official['labels'],'label_to_index':official['label_to_index'],
              'label_mapping_verified_against_official_flags':official['label_mapping_verified_against_official_flags'],
              'weight_words':49792,'constants':constants(),'samples':[],'weights':[],
              'compiler':{'version':gcc,'command':ref.command,'library_sha256':ref.library_hash,
                          'float_rounding':'nearest ties even','implicit_fma_contraction':False,
                          'explicit_dot_fma':True,'fast_math':False},
              'scope':'Independent host verification reference; no RTL/CPU/PPA/600-sample acceptance claim'}
    json_write(output/'constants.json',manifest['constants'])
    manifest['nonlinear_validation']=nonlinear_validation(ref)
    manifest['fixtures']=make_fixtures(output,ref)
    weights=[load(w) for w in official['weights']]
    for i,w in enumerate(weights):
        item=write_array(output,'weights/layer_{:02d}'.format(i),w);item['layer_index']=i
        manifest['weights'].append(item)
    classifier_kernel=load(official['classifier']['classifier_kernel'])
    classifier_bias=load(official['classifier']['classifier_bias'])
    manifest['classifier']={'kernel':write_array(output,'classifier/kernel',classifier_kernel),
                            'bias':write_array(output,'classifier/bias',classifier_bias)}
    for sample in official['samples']:
        sid=sample['sample_id'];x=load(sample['input'])
        item={'sample_id':sid,'ground_truth_label':sample['ground_truth_label'],'layers':[],
              'input':write_array(output,'cases/'+sid+'/input',x)}
        for i,(w,olayer) in enumerate(zip(weights,sample['layers'])):
            expected={name:load(olayer['stages'][name]) for name in STAGES}
            x,layer=emit_layer(output,'cases/{}/layer_{:02d}'.format(sid,i),x,w,256,ref,expected)
            layer['layer_index']=i
            item['layers'].append(layer)
            print('C reference {} layer {:02d}: y NRMSE={:.7g}'.format(sid,i,layer['comparisons']['y']['nrmse']),flush=True)
        logits=ref.classify(np.ascontiguousarray(x[0]),classifier_kernel,classifier_bias)
        item.update(final=write_array(output,'cases/'+sid+'/final',x),
                    logits=write_array(output,'cases/'+sid+'/logits',logits),
                    final_comparison=metrics(x,load(sample['final'])),
                    logits_comparison=metrics(logits,load(sample['logits'])))
        pred=int(np.argmax(logits));item['predicted_index']=pred;item['predicted_label']=official['labels'][pred]
        item['official_predicted_index']=sample['predicted_index']
        item['same_prediction_as_official']=pred==sample['predicted_index']
        manifest['samples'].append(item)
    for p in ('numeric/encoder/encoder_ref.c','numeric/encoder/encoder_ref.h',
              'numeric/encoder/contracts.py','numeric/encoder/run_reference.py'):
        manifest['source_hashes'][p]=sha(ROOT/p)
    manifest['summary']={'full_cases':len(manifest['samples']),'full_layers':len(manifest['samples'])*12,
                         'full_output_words':len(manifest['samples'])*12*99*64,
                         'all_stages_finite':True,
                         'max_final_nrmse':max(x['final_comparison']['nrmse'] for x in manifest['samples']),
                         'same_prediction_count':sum(x['same_prediction_as_official'] for x in manifest['samples'])}
    manifest['array_inventory']=inventory(manifest)
    if args.compare:
        prior=json.loads((args.compare/'manifest.json').read_text(encoding='utf-8'))
        for field in ('source_hashes','export_manifest_sha256','design_sha256','array_inventory'):
            if prior[field]!=manifest[field]:raise ValueError('independent repeat differs: '+field)
        manifest['repeat']={'status':'PASS','compared_arrays':len(manifest['array_inventory']),
                            'prior_manifest_sha256':sha(args.compare/'manifest.json')}
    json_write(output/'manifest.json',manifest)
    json_write(output/'status.json',{'status':'PASS','manifest_sha256':sha(output/'manifest.json'),
                                   'summary':manifest['summary'],'finished_unix':time.time()})

if __name__=='__main__':main()
