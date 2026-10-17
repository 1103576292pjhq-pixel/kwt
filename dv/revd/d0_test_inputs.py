"""Independent element-level tests for old n*64+k -> public k*16+j."""
import unittest

import numpy as np

from dv.revd.d0_inputs import repack_weights


class RepackTests(unittest.TestCase):
    def setUp(self):
        self.w = np.arange(64 * 256, dtype=np.int16).reshape(64, 256)
        self.b = np.arange(256, dtype=np.int64) - 128
        self.old = self.w.T.copy()

    def test_all_elements_math_index(self):
        tiles, biases = repack_weights(self.w, self.b, self.old)
        self.assertEqual(tiles.shape, (16, 1024))
        self.assertEqual(biases.shape, (16, 16))
        for nt in range(0, 256, 16):
            for k in range(64):
                for j in range(16):
                    self.assertEqual(int(tiles[nt // 16, k * 16 + j]), int(self.w[k, nt + j]))
            for j in range(16):
                self.assertEqual(int(biases[nt // 16, j]), int(self.b[nt + j]))

    def test_wrong_packed_transpose_rejected(self):
        wrong = self.w.reshape(256, 64).copy()
        with self.assertRaisesRegex(ValueError, "packed"):
            repack_weights(self.w, self.b, wrong)

    def test_missing_weight_rejected(self):
        with self.assertRaisesRegex(ValueError, "shape"):
            repack_weights(self.w[:, :-1], self.b, self.old)

    def test_wrong_dtype_rejected(self):
        for w, b, old in ((self.w.astype(np.int32), self.b, self.old),
                          (self.w, self.b.astype(np.float64), self.old),
                          (self.w, self.b, self.old.astype(np.int32))):
            with self.subTest(dtype=(w.dtype, b.dtype, old.dtype)):
                with self.assertRaisesRegex(ValueError, "dtype"):
                    repack_weights(w, b, old)

    def test_wrong_shape_rejected(self):
        for w, b, old in ((self.w.T.copy(), self.b, self.old),
                          (self.w, self.b.reshape(16, 16), self.old),
                          (self.w, self.b, self.old.reshape(-1))):
            with self.subTest(shape=(w.shape, b.shape, old.shape)):
                with self.assertRaisesRegex(ValueError, "shape"):
                    repack_weights(w, b, old)

    def test_bias_signed48_range_rejected(self):
        for value in (-(1 << 47) - 1, 1 << 47):
            b = self.b.copy()
            b[15] = value
            with self.assertRaisesRegex(ValueError, "signed48"):
                repack_weights(self.w, b, self.old)

    def test_small_public_tiles_and_sources_unchanged(self):
        for n in (16, 32):
            w = self.w[:, :n].copy()
            b = self.b[:n].copy()
            old = w.T.copy()
            frozen_w, frozen_b, frozen_old = w.copy(), b.copy(), old.copy()
            tiles, biases = repack_weights(w, b, old)
            for k in range(64):
                for column in range(n):
                    self.assertEqual(int(tiles[column // 16, k * 16 + column % 16]),
                                     int(w[k, column]))
            self.assertTrue(np.array_equal(biases.reshape(n), b))
            tiles[0, 0] = -32768
            biases[0, 0] = -(1 << 47)
            for actual, expected in ((w, frozen_w), (b, frozen_b), (old, frozen_old)):
                self.assertTrue(np.array_equal(actual, expected))


if __name__ == "__main__":
    unittest.main(verbosity=2)
