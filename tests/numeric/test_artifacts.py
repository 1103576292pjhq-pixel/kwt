"""Reject corrupt, incomplete or unsafe numerical artifact inputs."""
import hashlib
from pathlib import Path

import numpy as np
import pytest

from numeric.artifacts import load_array, validate_case_coverage


def test_array_loader_checks_hash_shape_dtype_and_path(tmp_path):
    path = tmp_path / "value.npy"
    np.save(path, np.array([[1, 2]], dtype=np.float32))
    descriptor = {"path": "value.npy", "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
                  "shape": [1, 2], "dtype": "float32"}
    assert load_array(tmp_path, descriptor, (1, 2), "float32").tolist() == [[1, 2]]
    for field, bad in [("sha256", "0" * 64), ("shape", [2, 1]), ("dtype", "float64"),
                       ("path", "../value.npy")]:
        changed = dict(descriptor, **{field: bad})
        with pytest.raises(ValueError):
            load_array(tmp_path, changed, (1, 2), "float32")


def test_array_loader_rejects_nan(tmp_path):
    path = tmp_path / "value.npy"
    np.save(path, np.array([[np.nan]], dtype=np.float32))
    descriptor = {"path": "value.npy", "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
                  "shape": [1, 1], "dtype": "float32"}
    with pytest.raises(ValueError):
        load_array(tmp_path, descriptor, (1, 1), "float32")


def test_coverage_requires_all_36_distinct_cases():
    samples = ["eight_750e3e75_nohash_0", "eight_d3831f6a_nohash_3", "synthetic_zero_silence"]
    cases = [{"sample_id": sample, "layer": layer} for sample in samples for layer in range(1, 13)]
    validate_case_coverage(cases)
    for invalid in [cases[:-1], cases + [cases[0]], cases[:-1] + [cases[0]],
                    [dict(item, layer=13) if index == 0 else item for index, item in enumerate(cases)]]:
        with pytest.raises(ValueError):
            validate_case_coverage(invalid)


@pytest.mark.parametrize("keys", [[], ["numeric/fixedpoint.py"],
                                  ["numeric/fixedpoint.py", "numeric/artifacts.py"],
                                  ["numeric/fixedpoint.py", "numeric/artifacts.py", "scripts/generate_prototype_vectors.py", "unexpected.py"]])
def test_code_inventory_cannot_omit_or_add_keys(keys, tmp_path):
    from numeric.artifacts import verify_code_hashes
    hashes = {}
    for relative in keys:
        path = tmp_path / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("source", encoding="utf-8")
        hashes[relative] = hashlib.sha256(path.read_bytes()).hexdigest()
    with pytest.raises(ValueError, match="inventory"):
        verify_code_hashes(tmp_path, hashes)


def test_exact_code_inventory_still_checks_each_digest(tmp_path):
    from numeric.artifacts import verify_code_hashes
    hashes = {}
    for relative in ["numeric/fixedpoint.py", "numeric/artifacts.py", "scripts/generate_prototype_vectors.py"]:
        path = tmp_path / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(relative, encoding="utf-8")
        hashes[relative] = hashlib.sha256(path.read_bytes()).hexdigest()
    verify_code_hashes(tmp_path, hashes)
    hashes["numeric/fixedpoint.py"] = "0" * 64
    with pytest.raises(ValueError, match="hash mismatch"):
        verify_code_hashes(tmp_path, hashes)
