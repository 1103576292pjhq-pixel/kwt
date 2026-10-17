"""Actual software rejection checks against the frozen artifact loading API."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import sys
import uuid

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from numeric.artifacts import load_array


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()
    out = args.out or ROOT / "reports/revd/d0/negative_inputs" / (
        datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "_" + uuid.uuid4().hex[:8])
    out = out.resolve()
    allowed = (ROOT / "reports/revd/d0").resolve()
    if allowed not in out.parents:
        raise ValueError("negative artifacts must remain in reports/revd/d0")
    out.mkdir(parents=True, exist_ok=False)
    records = []
    scenarios = [
        ("wrong_sha", np.array([1, -2], dtype=np.int16), [2], "int16", "SHA-256", "sha"),
        ("wrong_dtype", np.array([1, -2], dtype=np.int32), [2], "int16", "shape or dtype", None),
        ("wrong_shape", np.array([[1, -2]], dtype=np.int16), [2], "int16", "shape or dtype", None),
        ("wrong_descriptor_dtype", np.array([1, -2], dtype=np.int16), [2], "int16", "descriptor", "dtype"),
        ("wrong_descriptor_shape", np.array([1, -2], dtype=np.int16), [2], "int16", "descriptor", "shape"),
        ("nonfinite", np.array([1, np.nan], dtype=np.float32), [2], "float32", "nonfinite", None),
    ]
    for name, array, shape, dtype, expected_error, mutation in scenarios:
        path = out / (name + ".npy")
        np.save(path, array, allow_pickle=False)
        descriptor = {"path": path.name, "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
                      "shape": shape, "dtype": dtype}
        if mutation == "sha":
            descriptor["sha256"] = "0" * 64
        elif mutation == "dtype":
            descriptor["dtype"] = "float32"
        elif mutation == "shape":
            descriptor["shape"] = [1, 2]
        error = None
        try:
            load_array(out, descriptor, shape, dtype)
        except ValueError as caught:
            error = str(caught)
        detected = error is not None and expected_error in error
        records.append({"name": name, "descriptor": descriptor, "expected_error": expected_error,
                        "actual_error": error, "detected": detected,
                        "actual_file_sha256": hashlib.sha256(path.read_bytes()).hexdigest()})
    report = {"schema_version": 1, "kind": "SOFTWARE_ARTIFACT_LOADER_NEGATIVES_NOT_RTL_MUTATIONS",
              "api": "numeric.artifacts.load_array", "cases": records,
              "status": "PASS" if all(r["detected"] for r in records) else "FAIL"}
    (out / "result.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": report["status"], "cases_detected": sum(r["detected"] for r in records),
                      "report": (out / "result.json").relative_to(ROOT).as_posix()}))
    return 0 if report["status"] == "PASS" else 1


if __name__ == "__main__":
    raise SystemExit(main())
