"""Explicit official artifact integration gate, enabled by the shell runner."""
import importlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

import numpy as np

WORKSPACE = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(WORKSPACE))


@unittest.skipUnless(os.environ.get("KWT_BASELINE_REPORT"), "run scripts/run_model_baseline.sh for real integration")
class OfficialIntegrationTests(unittest.TestCase):
    def setUp(self):
        self.root = Path(os.environ["KWT_BASELINE_REPORT"])

    def test_real_checkpoint_and_validation_exports(self):
        try:
            api = importlib.import_module("model.verify_baseline")
        except ModuleNotFoundError:
            self.fail("model.verify_baseline has not been implemented")
        report = api.verify_run(Path(os.environ["KWT_BASELINE_REPORT"]))
        self.assertGreaterEqual(report["real_validation_samples"], 2)
        self.assertGreaterEqual(report["case_count"], 24)
        self.assertGreater(report["restored_variable_count"], 0)

    def copy_metadata(self, directory):
        directory = Path(directory)
        shutil.copy(self.root / "manifest.json", directory / "manifest.json")
        shutil.copy(self.root / "environment.json", directory / "environment.json")
        return json.loads((directory / "manifest.json").read_text())

    def write_manifest(self, directory, manifest):
        (Path(directory) / "manifest.json").write_text(json.dumps(manifest), encoding="utf-8")

    def test_changed_label_order_is_rejected(self):
        from model.verify_baseline import verify_run
        with tempfile.TemporaryDirectory() as directory:
            manifest = self.copy_metadata(directory)
            manifest["labels"][2], manifest["labels"][3] = manifest["labels"][3], manifest["labels"][2]
            self.write_manifest(directory, manifest)
            with self.assertRaisesRegex(ValueError, "label"):
                verify_run(Path(directory))

    def test_wrong_tensorflow_runtime_is_rejected(self):
        from model.verify_baseline import verify_run
        with tempfile.TemporaryDirectory() as directory:
            manifest = self.copy_metadata(directory)
            manifest["runtime"]["installed_tensorflow"] = "2.15.0"
            self.write_manifest(directory, manifest)
            with self.assertRaisesRegex(ValueError, "runtime"):
                verify_run(Path(directory))

    def test_real_wav_cannot_be_claimed_for_zero_audio(self):
        from model.contracts import sha256_file
        from model.verify_baseline import verify_run
        with tempfile.TemporaryDirectory() as directory:
            copied = Path(directory) / "baseline"
            shutil.copytree(self.root, copied)
            manifest = json.loads((copied / "manifest.json").read_text())
            sample = next(item for item in manifest["samples"] if item["partition"] == "validation")
            path = copied / sample["audio_array"]["path"]
            np.save(str(path), np.zeros(16000, dtype=np.float32), allow_pickle=False)
            sample["audio_array"]["sha256"] = sha256_file(path)
            self.write_manifest(copied, manifest)
            with self.assertRaisesRegex(ValueError, "real WAV PCM"):
                verify_run(copied)

    def test_self_consistent_zero_weight_case_is_not_official_checkpoint(self):
        from model.contracts import ffn1_numpy, sha256_file
        from model.verify_baseline import verify_run
        with tempfile.TemporaryDirectory() as directory:
            copied = Path(directory) / "baseline"
            shutil.copytree(self.root, copied)
            manifest = json.loads((copied / "manifest.json").read_text())
            case = manifest["cases"][0]
            arrays = {key: np.load(str(copied / descriptor["path"]), allow_pickle=False)
                      for key, descriptor in case["arrays"].items()}
            arrays["W"].fill(0)
            arrays["Y"] = ffn1_numpy(arrays["X"], arrays["W"], arrays["b"])
            for key in ("W", "Y"):
                path = copied / case["arrays"][key]["path"]
                np.save(str(path), arrays[key], allow_pickle=False)
                case["arrays"][key]["sha256"] = sha256_file(path)
            self.write_manifest(copied, manifest)
            with self.assertRaisesRegex(ValueError, "exact official checkpoint"):
                verify_run(copied)


if __name__ == "__main__":
    unittest.main()
