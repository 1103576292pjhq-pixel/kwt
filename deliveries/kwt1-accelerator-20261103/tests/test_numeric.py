"""用手算字面值和独立Decimal舍入检查正式数值合同。"""
from decimal import Decimal, ROUND_HALF_EVEN
import importlib
import importlib.util
import unittest

import numpy as np


class NumericTests(unittest.TestCase):
    def setUp(self):
        # 缺少实现时清楚失败；实现存在后，下面全部检查真实数值行为。
        self.assertIsNotNone(importlib.util.find_spec('model.fixed_numeric'),
                             '数值参考模型尚未实现')
        self.fm = importlib.import_module('model.fixed_numeric')

    def test_positive_and_negative_half_ties_round_to_even(self):
        for bias, expected in [(163840, 2), (229376, 4), (-163840, -2), (-229376, -4)]:
            with self.subTest(bias=bias):
                result = self.fm.convert_accumulator(0, bias)
                self.assertEqual((result.raw, result.rounded, result.y, result.flags),
                                 (bias, expected, expected, 0))

    def test_values_either_side_of_half_do_not_use_ties_away(self):
        for bias, expected in [(32767, 0), (32768, 0), (32769, 1),
                               (-32767, 0), (-32768, 0), (-32769, -1)]:
            with self.subTest(bias=bias):
                self.assertEqual(self.fm.convert_accumulator(0, bias).y, expected)

    def test_output_saturation_occurs_after_rounding(self):
        cases = [(0, 2147450879, 32767, 32767, 0),
                 (0, 2147450880, 32768, 32767, 2),
                 (0, 2147483647, 32768, 32767, 2),
                 (0, -2147483648, -32768, -32768, 0),
                 (-65536, -2147483648, -32769, -32768, 2)]
        for accumulator, bias, rounded, y, flags in cases:
            with self.subTest(accumulator=accumulator, bias=bias):
                result = self.fm.convert_accumulator(accumulator, bias)
                self.assertEqual((result.rounded, result.y, result.flags), (rounded, y, flags))

    def test_component_raw_overflow_is_distinct_from_output_saturation(self):
        for accumulator, bias, raw in [(549755813887, 1, 549755813887),
                                        (-549755813888, -1, -549755813888)]:
            result = self.fm.convert_accumulator(accumulator, bias)
            self.assertEqual(result.raw, raw)
            self.assertEqual(result.flags, 3)

    def test_last_flag_does_not_imply_numeric_saturation(self):
        result = self.fm.convert_accumulator(65536, 0, is_last=True)
        self.assertEqual((result.y, result.flags), (1, 4))

    def test_converter_rejects_values_before_narrowing(self):
        cases = [(549755813888, 0), (-549755813889, 0),
                 (0, 2147483648), (0, -2147483649), (0, 1 << 48)]
        for accumulator, bias in cases:
            with self.subTest(accumulator=accumulator, bias=bias):
                with self.assertRaises(ValueError):
                    self.fm.convert_accumulator(accumulator, bias)

    def test_converter_rejects_float_bool_and_nonbool_last(self):
        for accumulator, bias in [(True, 0), (0, False), (1.0, 0), (0, 1.0)]:
            with self.assertRaises(TypeError):
                self.fm.convert_accumulator(accumulator, bias)
        with self.assertRaises(TypeError):
            self.fm.convert_accumulator(0, 0, is_last=1)

    def test_maximum_legal_dot_is_exact_before_output_clip(self):
        result = self.fm.dot64_scalar([-32768] * 64, [-32768] * 64, 2147483647)
        self.assertEqual((result.raw, result.rounded, result.y, result.flags),
                         (70866960383, 1081344, 32767, 2))

    def test_minimum_legal_dot_is_exact_before_output_clip(self):
        result = self.fm.dot64_scalar([-32768] * 64, [32767] * 64, -2147483648)
        self.assertEqual((result.raw, result.rounded, result.y, result.flags),
                         (-70864863232, -1081312, -32768, 2))

    def test_k63_is_included_and_multiplication_is_signed(self):
        x, w = [0] * 64, [0] * 64
        x[63], w[63] = -4096, 96
        result = self.fm.dot64_scalar(x, w, 0, is_last=True)
        self.assertEqual((result.raw, result.y, result.flags), (-393216, -6, 4))

    def test_large_opposite_prefixes_cancel_without_early_output_clipping(self):
        result = self.fm.dot64_scalar([32767] * 32 + [-32767] * 32, [-32768] * 64, 0)
        self.assertEqual((result.raw, result.y, result.flags), (0, 0, 0))

    def test_dot_rejects_wrong_length_or_out_of_range_operands(self):
        with self.assertRaises(ValueError):
            self.fm.dot64_scalar([0] * 63, [0] * 64, 0)
        for bad in (32768, -32769):
            with self.assertRaises(ValueError):
                self.fm.dot64_scalar([bad] + [0] * 63, [0] * 64, 0)
        for bad in (True, 0.0):
            with self.assertRaises(TypeError):
                self.fm.dot64_scalar([0] * 64, [bad] + [0] * 63, 0)

    def test_matrix_axes_bias_broadcast_and_global_last(self):
        x = np.zeros((99, 64), dtype=np.int16)
        w = np.zeros((64, 256), dtype=np.int16)
        bias = np.zeros(256, dtype=np.int32)
        x[0, 0], w[0, 0], bias[1] = 4096, 6554, 163840
        x[98, 63], w[63, 255] = -4096, 96
        y, flags = self.fm.ffn1_int16(x, w, bias)
        expected = np.zeros((99, 256), dtype=np.int16)
        expected[:, 1], expected[0, 0], expected[98, 255] = 2, 410, -6
        expected_flags = np.zeros((99, 256), dtype=np.uint8)
        expected_flags[98, 255] = 4
        np.testing.assert_array_equal(y, expected)
        np.testing.assert_array_equal(flags, expected_flags)
        self.assertEqual(y.dtype, np.dtype(np.int16))
        self.assertEqual(flags.dtype, np.dtype(np.uint8))

    def test_matrix_saturation_flags_are_per_element(self):
        x = np.zeros((99, 64), dtype=np.int16)
        w = np.zeros((64, 256), dtype=np.int16)
        bias = np.zeros(256, dtype=np.int32)
        bias[0], bias[255] = 2147483647, 2147483647
        y, flags = self.fm.ffn1_int16(x, w, bias)
        self.assertEqual((int(y[0, 0]), int(flags[0, 0])), (32767, 2))
        self.assertEqual((int(y[98, 255]), int(flags[98, 255])), (32767, 6))
        self.assertEqual(int(np.count_nonzero(flags & 4)), 1)
        self.assertFalse(np.any(flags & 0xf9))

    def test_matrix_rejects_implicit_narrowing_and_nonproduction_shapes(self):
        x = np.zeros((99, 64), dtype=np.int16)
        w = np.zeros((64, 256), dtype=np.int16)
        bias = np.zeros(256, dtype=np.int32)
        for bad_x, bad_w, bad_b in [(x.astype(np.int64), w, bias),
                                    (x, w.astype(np.uint16), bias),
                                    (x, w, bias.astype(np.int64))]:
            with self.assertRaises(TypeError):
                self.fm.ffn1_int16(bad_x, bad_w, bad_b)
        for bad_x, bad_w, bad_b in [(x[:98], w, bias), (x[:, :63], w, bias),
                                    (x, w[:, :255], bias[:255]), (x, w, bias[:255])]:
            with self.assertRaises(ValueError):
                self.fm.ffn1_int16(bad_x, bad_w, bad_b)

    def test_dense_vector_path_matches_independent_decimal_dots(self):
        rng = np.random.default_rng(20261027)
        x = rng.integers(-32768, 32768, (99, 64), dtype=np.int16)
        w = rng.integers(-32768, 32768, (64, 256), dtype=np.int16)
        bias = rng.integers(-2147483648, 2147483648, 256, dtype=np.int32)
        y, flags = self.fm.ffn1_int16(x, w, bias)
        probes = [(0, 0), (98, 255)] + [(int(rng.integers(99)), int(rng.integers(256)))
                                       for _ in range(30)]
        for row, col in probes:
            raw = sum(int(x[row, k]) * int(w[k, col]) for k in range(64)) + int(bias[col])
            rounded = int((Decimal(raw) / Decimal(65536)).quantize(Decimal(1),
                                                                  rounding=ROUND_HALF_EVEN))
            expected = max(-32768, min(32767, rounded))
            expected_flags = (2 if expected != rounded else 0) | (4 if (row, col) == (98, 255) else 0)
            self.assertEqual((int(y[row, col]), int(flags[row, col])), (expected, expected_flags))


if __name__ == '__main__':
    unittest.main()
