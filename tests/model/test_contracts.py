"""Numeric and artifact rejection tests; no TensorFlow dependency."""
import importlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

import numpy as np

WORKSPACE = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(WORKSPACE))


class ContractTests(unittest.TestCase):
    def setUp(self):
        try:
            self.api = importlib.import_module("model.contracts")
        except ModuleNotFoundError:
            self.fail("model.contracts has not been implemented")

    def arrays(self):
        # These zeros are unit fixtures, never an official model baseline.
        return {
            "X": np.zeros((99, 64), dtype=np.float32),
            "W": np.zeros((64, 256), dtype=np.float32),
            "b": np.zeros((256,), dtype=np.float32),
            "Y": np.zeros((99, 256), dtype=np.float32),
        }

    def provenance(self):
        return {
            "sample_id": "yes_example",
            "partition": "validation",
            "sample_sha256": "a" * 64,
            "source_commit": "237e4097afd4f6851e0b82f0a8d65c2dfe8eae30",
            "checkpoint_sha256": {"best_weights.index": "b" * 64},
        }

    def test_hand_calculated_matrix_and_bias(self):
        x = np.array([[1, 2], [-1, 3]], dtype=np.float32)
        w = np.array([[2, -1, 4], [3, 5, -2]], dtype=np.float32)
        b = np.array([0.5, 1, -3], dtype=np.float32)
        expected = np.array([[8.5, 10, -3], [7.5, 17, -13]], dtype=np.float32)
        np.testing.assert_array_equal(self.api.ffn1_numpy(x, w, b), expected)

    def test_incompatible_matrix_and_bias_are_rejected(self):
        with self.assertRaisesRegex(ValueError, "shape"):
            self.api.ffn1_numpy(np.zeros((2, 3)), np.zeros((2, 4)), np.zeros(4))
        with self.assertRaisesRegex(ValueError, "shape"):
            self.api.ffn1_numpy(np.zeros((2, 3)), np.zeros((3, 4)), np.zeros((1, 4)))

    def test_wrong_baseline_shape_is_rejected(self):
        arrays = self.arrays()
        arrays["X"] = arrays["X"][:-1]
        with self.assertRaisesRegex(ValueError, "X.*shape"):
            self.api.validate_ffn1_arrays(arrays)

    def test_nonfinite_and_wrong_dtype_are_rejected(self):
        arrays = self.arrays()
        arrays["Y"][0, 0] = np.nan
        with self.assertRaisesRegex(ValueError, "finite"):
            self.api.validate_ffn1_arrays(arrays)
        arrays = self.arrays()
        arrays["W"] = arrays["W"].astype(np.float64)
        with self.assertRaisesRegex(ValueError, "float32"):
            self.api.validate_ffn1_arrays(arrays)

    def test_round_trip_and_corrupt_array_rejection(self):
        with tempfile.TemporaryDirectory() as directory:
            metadata = self.api.write_ffn1_case(Path(directory), 1, self.arrays(), self.provenance())
            self.api.verify_ffn1_case(Path(directory), metadata)
            self.assertEqual(metadata["stage"], "ffn1_dense_pre_gelu")
            self.assertEqual(metadata["layer"], 1)
            self.assertEqual(metadata["arrays"]["X"]["shape"], [99, 64])
            filename = Path(directory) / metadata["arrays"]["X"]["path"]
            with filename.open("ab") as stream:
                stream.write(b"corruption")
            with self.assertRaisesRegex(ValueError, "SHA-256"):
                self.api.verify_ffn1_case(Path(directory), metadata)

    def test_metadata_refuses_wrong_stage_and_incomplete_origin(self):
        with tempfile.TemporaryDirectory() as directory:
            metadata = self.api.write_ffn1_case(Path(directory), 12, self.arrays(), self.provenance())
            metadata["stage"] = "gelu_output"
            with self.assertRaisesRegex(ValueError, "stage"):
                self.api.verify_ffn1_case(Path(directory), metadata)
            with self.assertRaisesRegex(ValueError, "partition"):
                self.api.write_ffn1_case(Path(directory), 1, self.arrays(), {"sample_id": "bad"})

    def test_tensor_mismatch_is_rejected_and_zero_reference_is_well_defined(self):
        equal = self.api.compare_arrays(np.zeros((2, 2)), np.zeros((2, 2)), atol=1e-6, rtol=1e-5)
        self.assertEqual(equal["max_abs_error"], 0.0)
        self.assertEqual(equal["nrmse"], 0.0)
        near_zero = self.api.compare_arrays(np.array([1e-9]), np.zeros(1), atol=1e-6, rtol=1e-5)
        self.assertAlmostEqual(near_zero["nrmse"], 0.1)
        with self.assertRaisesRegex(ValueError, "tolerance"):
            self.api.compare_arrays(np.ones((2, 2)), np.zeros((2, 2)), atol=1e-6, rtol=1e-5)

    def test_official_flags_refuse_readme_mlp_size_and_prenorm(self):
        flags = json.loads((WORKSPACE / "vendor/keyword-transformer/models_data_v2_12_labels/kwt1/flags.json").read_text())
        flags.update(prenorm=False, approximate_gelu=False, distill_teacher_json="")
        try:
            self.api.validate_official_flags(flags)
        except AttributeError:
            self.fail("official flag validation has not been implemented")
        flags["mlp_dim"] = 128
        with self.assertRaisesRegex(ValueError, "mlp_dim"):
            self.api.validate_official_flags(flags)
        flags["mlp_dim"] = 256
        flags["prenorm"] = True
        with self.assertRaisesRegex(ValueError, "prenorm"):
            self.api.validate_official_flags(flags)
        flags["prenorm"] = False
        flags["approximate_gelu"] = True
        with self.assertRaisesRegex(ValueError, "approximate_gelu"):
            self.api.validate_official_flags(flags)

    def test_escape_path_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            metadata = self.api.write_ffn1_case(Path(directory), 1, self.arrays(), self.provenance())
            metadata["arrays"]["X"]["path"] = "../outside.npy"
            with self.assertRaisesRegex(ValueError, "inside"):
                self.api.verify_ffn1_case(Path(directory), metadata)

    def test_layer_cannot_reuse_another_layer_artifact_paths(self):
        with tempfile.TemporaryDirectory() as directory:
            metadata = self.api.write_ffn1_case(Path(directory), 1, self.arrays(), self.provenance())
            metadata["layer"] = 2
            with self.assertRaisesRegex(ValueError, "layer path"):
                self.api.verify_ffn1_case(Path(directory), metadata)


if __name__ == "__main__":
    unittest.main()
