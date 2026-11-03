"""检查编码、实际字节布局和冻结合同；期望字节为手工推导。"""
import importlib
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

import numpy as np


ROOT = Path(__file__).resolve().parents[1]


class EncodingTests(unittest.TestCase):
    def setUp(self):
        self.fm = importlib.import_module('model.fixed_numeric')
        self.assertTrue(callable(getattr(self.fm, 'encode_finite', None)), '浮点编码尚未实现')

    def test_float_encoding_uses_each_roles_scale_and_even_ties(self):
        real = np.array([-3.5, -2.5, -0.5, 0.5, 2.5, 3.5]) / 4096
        result = self.fm.encode_finite(real, 'x')
        np.testing.assert_array_equal(result.values, [-4, -2, 0, 0, 2, 4])
        self.assertEqual(result.endpoint_clipped_count, 0)
        self.assertEqual(result.values.dtype, np.dtype(np.int16))
        self.assertEqual(int(self.fm.encode_finite(np.array([0.25]), 'w').values[0]), 16384)
        encoded_bias = self.fm.encode_finite(np.array([0.25]), 'bias')
        self.assertEqual((int(encoded_bias.values[0]), encoded_bias.values.dtype),
                         (67108864, np.dtype(np.int32)))

    def test_encoding_preclips_huge_finite_values_without_float_overflow(self):
        values = np.array([-np.finfo(np.float64).max, np.finfo(np.float64).max])
        with np.errstate(over='raise', invalid='raise'):
            result = self.fm.encode_finite(values, 'x')
        np.testing.assert_array_equal(result.values, [-32768, 32767])
        self.assertEqual(result.endpoint_clipped_count, 2)

    def test_encoding_reports_endpoint_clip_even_if_rounding_would_return_endpoint(self):
        result = self.fm.encode_finite(np.array([(32767 + 0.125) / 4096]), 'x')
        self.assertEqual((int(result.values[0]), result.endpoint_clipped_count), (32767, 1))

    def test_encoding_refuses_nonfinite_nonreal_and_integer_inputs(self):
        for values in (np.array([np.nan]), np.array([np.inf]), np.array([-np.inf])):
            with self.assertRaises(ValueError):
                self.fm.encode_finite(values, 'x')
        for values in (np.array([1]), np.array([True]), np.array([1 + 0j])):
            with self.assertRaises(TypeError):
                self.fm.encode_finite(values, 'x')
        with self.assertRaises(ValueError):
            self.fm.encode_finite(np.array([0.0]), 'output')

    def test_decode_uses_effective_width_and_scale(self):
        result = self.fm.decode_fixed(np.array([-32768, 0, 32767], dtype=np.int32), 'y')
        np.testing.assert_array_equal(result, [-8.0, 0.0, 32767 / 4096])
        self.assertEqual(float(self.fm.decode_fixed(np.array([16384], dtype=np.int16), 'w')[0]), 0.25)
        with self.assertRaises(ValueError):
            self.fm.decode_fixed(np.array([65535], dtype=np.int32), 'y')
        with self.assertRaises(TypeError):
            self.fm.decode_fixed(np.array([1.0]), 'x')


class LayoutTests(unittest.TestCase):
    def setUp(self):
        self.assertIsNotNone(importlib.util.find_spec('model.layout'), '内存布局模型尚未实现')
        self.layout = importlib.import_module('model.layout')
        self.x = np.zeros((99, 64), dtype=np.int16)
        self.w = np.zeros((64, 256), dtype=np.int16)
        self.bias = np.zeros(256, dtype=np.int32)

    def test_input_bytes_use_little_endian_row_major_x_column_major_w(self):
        self.x[0, 0], self.x[0, 1], self.x[1, 0] = -2, 3, 4
        self.w[0, 0], self.w[1, 0], self.w[0, 1] = -2, 3, 4
        self.bias[0] = -2
        packed = self.layout.pack_inputs(self.x, self.w, self.bias)
        self.assertEqual({key: len(value) for key, value in packed.items()},
                         {'x': 12672, 'w': 32768, 'bias': 2048})
        self.assertEqual(packed['x'][:4], b'\xfe\xff\x03\x00')
        self.assertEqual(packed['w'][:4], b'\xfe\xff\x03\x00')
        self.assertEqual(packed['x'][128:130], b'\x04\x00')
        self.assertEqual(packed['w'][128:130], b'\x04\x00')
        self.assertEqual(packed['bias'][:8], b'\xfe\xff\xff\xff\xff\xff\xff\xff')
        unpacked = self.layout.unpack_inputs(packed)
        for result, expected in zip(unpacked, (self.x, self.w, self.bias)):
            np.testing.assert_array_equal(result, expected)
            self.assertEqual(result.dtype, expected.dtype)

    def test_input_unpack_refuses_64bit_bias_before_casting_to_32(self):
        for bad in (2147483648, -2147483649, 1 << 48):
            packed = self.layout.pack_inputs(self.x, self.w, self.bias)
            packed['bias'] = bad.to_bytes(8, 'little', signed=True) + packed['bias'][8:]
            with self.assertRaises(ValueError):
                self.layout.unpack_inputs(packed)

    def test_input_unpack_refuses_missing_keys_and_wrong_byte_lengths(self):
        packed = self.layout.pack_inputs(self.x, self.w, self.bias)
        with self.assertRaises(ValueError):
            self.layout.unpack_inputs({'x': packed['x'], 'w': packed['w']})
        for key in ('x', 'w', 'bias'):
            bad = dict(packed)
            bad[key] = bad[key][:-1]
            with self.assertRaises(ValueError):
                self.layout.unpack_inputs(bad)

    def test_output_bytes_sign_extend_y16_into_y32_and_keep_flags8(self):
        y = np.zeros((99, 256), dtype=np.int16)
        flags = np.zeros((99, 256), dtype=np.uint8)
        y[0, 0], y[-1, -1], flags[-1, -1] = -1, 32767, 4
        packed = self.layout.pack_outputs(y, flags)
        self.assertEqual((len(packed['y']), len(packed['flags'])), (101376, 25344))
        self.assertEqual(packed['y'][:4], b'\xff\xff\xff\xff')
        self.assertEqual(packed['y'][-4:], b'\xff\x7f\x00\x00')
        self.assertEqual(packed['flags'][-1], 4)
        decoded_y, decoded_flags = self.layout.unpack_outputs(packed)
        np.testing.assert_array_equal(decoded_y, y)
        np.testing.assert_array_equal(decoded_flags, flags)

    def test_output_unpack_refuses_invalid_sign_extension_and_flags(self):
        y = np.zeros((99, 256), dtype=np.int16)
        flags = np.zeros((99, 256), dtype=np.uint8)
        flags[-1, -1] = 4
        packed = self.layout.pack_outputs(y, flags)
        packed['y'] = b'\xff\xff\x00\x00' + packed['y'][4:]
        with self.assertRaises(ValueError):
            self.layout.unpack_outputs(packed)
        for bad_flags in (0, 1, 4, 8):
            damaged = flags.copy()
            if bad_flags == 0:
                damaged[-1, -1] = 0
            else:
                damaged[0, 0] = bad_flags
            with self.assertRaises(ValueError):
                self.layout.pack_outputs(y, damaged)


class ContractTests(unittest.TestCase):
    def setUp(self):
        self.fm = importlib.import_module('model.fixed_numeric')
        self.assertTrue(callable(getattr(self.fm, 'load_contract', None)), '冻结合同检查尚未实现')

    def test_contract_loads_but_rejects_numeric_drift_and_duplicate_keys(self):
        contract = self.fm.load_contract(ROOT / 'model/numeric-contract.json')
        self.assertEqual(contract['spec_id'], 'KWT1-FFN1')
        with tempfile.TemporaryDirectory() as directory:
            target = Path(directory) / 'contract.json'
            for field, value in [('accumulator', 48), ('bias', 48), ('output', 32)]:
                changed = json.loads(json.dumps(contract))
                changed['widths'][field] = value
                target.write_text(json.dumps(changed), encoding='utf-8')
                with self.assertRaises(ValueError):
                    self.fm.load_contract(target)
            target.write_text('{"spec_id":"first","spec_id":"second"}', encoding='utf-8')
            with self.assertRaises(ValueError):
                self.fm.load_contract(target)


if __name__ == '__main__':
    unittest.main()
