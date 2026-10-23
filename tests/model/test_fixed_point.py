import importlib.util
from pathlib import Path
import unittest

import numpy as np

SOURCE = Path(__file__).resolve().parents[2] / 'scripts/model/fixed_point.py'


class FixedPointTests(unittest.TestCase):
    def setUp(self):
        self.assertTrue(SOURCE.is_file(), 'Fixed-point model is missing')
        spec = importlib.util.spec_from_file_location('fixed_point_under_test', str(SOURCE))
        self.fp = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.fp)

    def test_signed_half_ties_are_even(self):
        result = self.fp.round_shift(np.array([-7,-5,-3,-1,1,3,5,7]), 1, 'rne')
        np.testing.assert_array_equal(result, [-4,-2,-2,0,0,2,2,4])
        truncated = self.fp.round_shift(np.array([-7,-5,-3,-1,1,3,5,7]), 1, 'tz')
        np.testing.assert_array_equal(truncated, [-3,-2,-1,0,0,1,2,3])

    def test_float_quantization_saturates_both_signed_limits(self):
        quantized, clips = self.fp.quantize(np.array([-99.,-8.,-7.5,7.,7.5,99.]), 4, 0, 'rne')
        np.testing.assert_array_equal(quantized, [-8,-8,-8,7,7,7])
        self.assertEqual(clips, 3)
        ties, _ = self.fp.quantize(np.array([-2.5,-1.5,-.5,.5,1.5,2.5]), 4, 0, 'rne')
        np.testing.assert_array_equal(ties, [-2,-2,0,0,2,2])

    def test_prefix_saturation_survives_later_cancellation(self):
        result, stats = self.fp.integer_linear(np.array([[3,3,-3]]), np.array([[2],[2],[2]]),
                                                np.array([0]), 4, 0, 4, 'rne', 3)
        np.testing.assert_array_equal(result, [[1]])
        self.assertFalse(stats['prefix_fast_path'])
        self.assertEqual(stats['accumulator_saturations'], 1)

    def test_bias_is_added_before_signed_output_rounding(self):
        result, stats = self.fp.integer_linear(np.array([[1],[-1]]), np.array([[3]]),
                                                np.array([2]), 16, 1, 4, 'rne', 4)
        np.testing.assert_array_equal(result, [[2],[0]])
        self.assertEqual(stats['bias_saturations'], 0)

    def test_proven_fast_path_matches_python_integer_dots(self):
        rng = np.random.RandomState(123)
        x = rng.randint(-8, 8, size=(9, 5))
        w = rng.randint(-4, 4, size=(5, 3))
        b = np.array([-1,0,2])
        result, stats = self.fp.integer_linear(x, w, b, 32, 0, 16, 'rne', 4)
        expected = [[sum(int(x[i,k])*int(w[k,j]) for k in range(5))+int(b[j])
                     for j in range(3)] for i in range(9)]
        np.testing.assert_array_equal(result, expected)
        self.assertTrue(stats['prefix_fast_path'])
        reordered,_ = self.fp.integer_linear(x,np.asfortranarray(w),b,32,0,16,'rne',4)
        np.testing.assert_array_equal(reordered,expected)

    def test_scale_uses_peak_and_output_metrics_sum_energies(self):
        self.assertEqual(self.fp.fraction_bits(7., 8, 1.125), 4)
        metrics = self.fp.error_metrics(np.array([1.,100.]), np.array([2.,100.]))
        self.assertAlmostEqual(metrics['nrmse'], np.sqrt(1./10001.))

    def test_output_conversion_saturates_after_rounding(self):
        result, stats = self.fp.integer_linear(np.array([[7],[-8]]), np.array([[3]]),
                                                np.array([0]), 16, 1, 4, 'rne', 4)
        np.testing.assert_array_equal(result, [[7],[-8]])
        self.assertEqual(stats['output_saturations'], 2)


if __name__ == '__main__':
    unittest.main()
