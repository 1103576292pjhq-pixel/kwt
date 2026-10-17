"""Generate and re-read complete, hash-bound FFN1 integer vectors."""
import hashlib
import json
import math
from pathlib import Path

import numpy as np

from .fixedpoint import derive_layer_config, ffn1_reference, quantize_signed

SOURCE_COMMIT = "237e4097afd4f6851e0b82f0a8d65c2dfe8eae30"
BASELINE_SHA256 = "2a5abbf45c768dfe2333735781991cb78b396378b0a70821d7ac8c40010d287a"
SAMPLES = ("eight_750e3e75_nohash_0", "eight_d3831f6a_nohash_3", "synthetic_zero_silence")
SCOPE = "Two real validation WAVs (both unknown) plus synthetic zero silence; no calibration, test tuning, or official 600-sample acceptance claim."
REQUIRED_CODE_PATHS = frozenset({
    "numeric/fixedpoint.py", "numeric/artifacts.py", "scripts/generate_prototype_vectors.py",
})
PROTECTED_WORKSPACE_PATHS = (
    "config", "data", "docs", "dv", "model", "numeric", "rtl", "scripts", "tests",
    "tools", "vendor", "work", ".venv-dv", ".venv-model", ".venv-model.ntfs-partial",
    ".git", ".agents", ".codex", ".vscode", "reports/model", "reports/environment",
    "reports/FIRST_BATCH.md", "reports/first-batch-independent.json", "README.md", ".gitignore",
)


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def validate_output_path(workspace, output):
    """Reject input overlap in either direction, resolving directory symlinks.

    This function performs no filesystem mutation. Call it before creating the
    output directory or writing even a RUNNING/FAIL marker.
    """
    workspace, output = Path(workspace).resolve(), Path(output).resolve()
    for relative in PROTECTED_WORKSPACE_PATHS:
        protected = (workspace / relative).resolve()
        if output == protected or protected in output.parents or output in protected.parents:
            raise ValueError(f"output overlaps protected input: {relative}")
    if output.is_file():
        raise ValueError("output must be a directory")
    return output


def verify_code_hashes(workspace, hashes):
    """Require the complete fixed source inventory before checking digests."""
    if not isinstance(hashes, dict) or set(hashes) != REQUIRED_CODE_PATHS:
        raise ValueError("numeric code SHA-256 inventory must contain exactly the three required paths")
    for relative in sorted(REQUIRED_CODE_PATHS):
        if sha256_file(Path(workspace) / relative) != hashes[relative]:
            raise ValueError("numeric implementation hash mismatch: " + relative)


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(value, indent=2, sort_keys=True, allow_nan=False) + "\n", encoding="utf-8")
    temporary.replace(path)


def load_array(root, descriptor, shape, dtype):
    root = Path(root).resolve()
    path = (root / descriptor["path"]).resolve()
    if root not in path.parents:
        raise ValueError("array path escapes root")
    if sha256_file(path) != descriptor["sha256"]:
        raise ValueError("array SHA-256 mismatch: " + descriptor["path"])
    array = np.load(path, allow_pickle=False)
    if tuple(array.shape) != tuple(shape) or array.dtype != np.dtype(dtype):
        raise ValueError("array shape or dtype mismatch")
    if descriptor["shape"] != list(shape) or descriptor["dtype"] != str(np.dtype(dtype)):
        raise ValueError("array descriptor shape or dtype mismatch")
    if array.dtype.kind == "f" and not np.isfinite(array).all():
        raise ValueError("nonfinite array")
    return array


def validate_case_coverage(cases):
    expected = {(sample, layer) for sample in SAMPLES for layer in range(1, 13)}
    actual = [(case["sample_id"], case["layer"]) for case in cases]
    if len(actual) != 36 or set(actual) != expected:
        raise ValueError("must cover exactly three frozen inputs times twelve independent layers")


def _baseline(workspace, baseline):
    manifest_path = baseline / "manifest.json"
    if sha256_file(manifest_path) != BASELINE_SHA256:
        raise ValueError("frozen baseline manifest differs from accepted batch1")
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    if manifest["status"] != "verified" or manifest["source"]["commit"] != SOURCE_COMMIT:
        raise ValueError("unverified or wrong official baseline")
    validate_case_coverage(manifest["cases"])
    inventory_path = workspace / "config/source-manifest.json"
    if sha256_file(inventory_path) != manifest["source"]["manifest_sha256"]:
        raise ValueError("source inventory SHA-256 mismatch")
    inventory = json.loads(inventory_path.read_text(encoding="utf-8"))
    if inventory["commit"] != SOURCE_COMMIT or len(inventory["files"]) != 124:
        raise ValueError("official source inventory mismatch")
    for file in inventory["files"]:
        if sha256_file(workspace / "vendor/keyword-transformer" / file["path"]) != file["sha256"]:
            raise ValueError("official source changed: " + file["path"])
    return manifest


def _float_case(baseline, case):
    shapes = {"X": (99, 64), "W": (64, 256), "b": (256,), "Y": (99, 256)}
    return {name: load_array(baseline, case["arrays"][name], shape, "float32") for name, shape in shapes.items()}


def _metrics(decoded, reference):
    error = decoded - reference.astype(np.float64)
    error_energy = float(np.sum(error * error, dtype=np.float64))
    reference64 = reference.astype(np.float64)
    reference_energy = float(np.sum(reference64 * reference64, dtype=np.float64))
    count = int(reference.size)
    rmse = math.sqrt(error_energy / count)
    nrmse = rmse / max(math.sqrt(reference_energy / count), 1e-8)
    return {"nrmse": nrmse, "rmse": rmse, "max_abs_error": float(np.max(np.abs(error))),
            "sum_squared_error": error_energy, "sum_squared_reference": reference_energy,
            "output_count": count, "within_3_percent": nrmse <= 0.03}


def _aggregate(cases):
    per_layer = []
    for layer in range(1, 13):
        selected = [case for case in cases if case["layer"] == layer]
        count = sum(case["metrics"]["output_count"] for case in selected)
        error = sum(case["metrics"]["sum_squared_error"] for case in selected)
        reference = sum(case["metrics"]["sum_squared_reference"] for case in selected)
        nrmse = math.sqrt(error / count) / max(math.sqrt(reference / count), 1e-8)
        per_layer.append({"layer": layer, "case_count": len(selected), "output_count": count,
                          "nrmse": nrmse, "rmse": math.sqrt(error / count),
                          "max_abs_error": max(case["metrics"]["max_abs_error"] for case in selected),
                          "within_3_percent": nrmse <= 0.03,
                          "saturation": {key: sum(case["saturation"][key] for case in selected)
                                         for key in ("input", "weight", "bias", "raw48", "output32")}})
    summary = {"max_case_nrmse": max(case["metrics"]["nrmse"] for case in cases),
               "max_layer_nrmse": max(layer["nrmse"] for layer in per_layer),
               "all_cases_within_3_percent": all(case["metrics"]["within_3_percent"] for case in cases),
               "all_layers_within_3_percent": all(layer["within_3_percent"] for layer in per_layer),
               "saturation": {key: sum(case["saturation"][key] for case in cases)
                              for key in ("input", "weight", "bias", "raw48", "output32")}}
    return per_layer, summary


def _array_descriptor(output, path, array):
    path.parent.mkdir(parents=True, exist_ok=True)
    np.save(path, array, allow_pickle=False)
    return {"path": path.relative_to(output).as_posix(), "sha256": sha256_file(path),
            "shape": list(array.shape), "dtype": str(array.dtype)}


def generate_vectors(workspace, baseline, output):
    workspace, baseline, output = map(lambda p: Path(p).resolve(), (workspace, baseline, output))
    validate_output_path(workspace, output)
    original = _baseline(workspace, baseline)
    numeric_config_path = workspace / "config/prototype-numeric.json"
    numeric_config = json.loads(numeric_config_path.read_text(encoding="utf-8"))
    if (numeric_config["input_scale"], numeric_config["input_bits"], numeric_config["weight_bits"],
            numeric_config["bias_bits"], numeric_config["raw_bits"], numeric_config["output_bits"]) != (
            2 ** -8, 16, 16, 48, 48, 32):
        raise ValueError("numeric configuration does not match frozen implementation")
    cases, layers = [], {}
    for case in original["cases"]:
        data = _float_case(baseline, case)
        layer = case["layer"]
        cfg = derive_layer_config(data["W"], data["b"])
        frozen = {key: case["arrays"][key]["sha256"] for key in ("W", "b")}
        if layer in layers and layers[layer] != frozen:
            raise ValueError("frozen parameters differ across samples for one layer")
        layers[layer] = frozen
        xq, xstats = quantize_signed(data["X"], cfg.input_scale, 16)
        xq = xq.astype(np.int16)
        result = ffn1_reference(xq, cfg.weight_q, cfg.bias_q, cfg.output_shift)
        case_id = f"{case['sample_id']}/layer_{layer:02d}"
        arrays = {"Xq": xq, "Wq": cfg.weight_q, "Wq_packed": cfg.weight_q.T.copy(),
                  "bq": cfg.bias_q, "Yq": result.output, "raw48": result.raw,
                  "overflow": result.overflow, "output_saturated": result.output_saturated}
        descriptors = {name: _array_descriptor(output, output / "cases" / case_id / (name + ".npy"), value)
                       for name, value in arrays.items()}
        entry = {"case_id": case_id, "sample_id": case["sample_id"], "layer": layer,
                 "partition": case["partition"], "config": cfg.metadata(), "arrays": descriptors,
                 "source_arrays": case["arrays"], "input_stats": xstats,
                 "metrics": _metrics(result.output.astype(np.float64) * cfg.output_scale, data["Y"]),
                 "saturation": {"input": xstats["saturated"], "weight": cfg.weight_stats["saturated"],
                                "bias": cfg.bias_stats["saturated"], "raw48": int(result.overflow.sum()),
                                "output32": int(result.output_saturated.sum())},
                 "scalar_checks": result.scalar_checks, "int64_bound": result.int64_bound}
        cases.append(entry)
        print(f"numeric {len(cases):02d}/36 {case_id}: NRMSE={entry['metrics']['nrmse']:.8g}", flush=True)
    per_layer, summary = _aggregate(cases)
    manifest = {"schema_version": 1, "status": "PASS", "scope": SCOPE,
                "source": {"commit": SOURCE_COMMIT, "baseline_manifest_sha256": BASELINE_SHA256,
                           "source_manifest_sha256": original["source"]["manifest_sha256"],
                           "official_files_verified": 124},
                "numeric_config": {"path": "config/prototype-numeric.json", "sha256": sha256_file(numeric_config_path)},
                "code_sha256": {path: sha256_file(workspace / path) for path in sorted(REQUIRED_CODE_PATHS)},
                "case_count": len(cases), "output_count": sum(case["metrics"]["output_count"] for case in cases),
                "cases": cases, "per_layer": per_layer, "summary": summary}
    # Verify every saved array against the source before publishing a PASS file.
    verify_vectors(workspace, baseline, output, manifest)
    write_json(output / "manifest.json", manifest)
    return manifest


def verify_vectors(workspace, baseline, output, manifest=None):
    workspace, baseline, output = map(lambda p: Path(p).resolve(), (workspace, baseline, output))
    original = _baseline(workspace, baseline)
    manifest = manifest or json.loads((output / "manifest.json").read_text(encoding="utf-8"))
    if manifest["status"] != "PASS" or manifest["schema_version"] != 1:
        raise ValueError("vectors are not a completed supported artifact")
    if manifest["source"] != {"commit": SOURCE_COMMIT, "baseline_manifest_sha256": BASELINE_SHA256,
                               "source_manifest_sha256": original["source"]["manifest_sha256"],
                               "official_files_verified": 124}:
        raise ValueError("vector source provenance mismatch")
    if manifest["numeric_config"]["sha256"] != sha256_file(workspace / "config/prototype-numeric.json"):
        raise ValueError("numeric configuration hash mismatch")
    verify_code_hashes(workspace, manifest["code_sha256"])
    validate_case_coverage(manifest["cases"])
    originals = {(case["sample_id"], case["layer"]): case for case in original["cases"]}
    for case in manifest["cases"]:
        source_case = originals[(case["sample_id"], case["layer"])]
        if case["case_id"] != f"{case['sample_id']}/layer_{case['layer']:02d}" or case["source_arrays"] != source_case["arrays"]:
            raise ValueError("case identity/source mapping mismatch")
        data = _float_case(baseline, source_case)
        cfg = derive_layer_config(data["W"], data["b"])
        if cfg.metadata() != case["config"]:
            raise ValueError("case scales not derived from frozen parameters")
        xq, xstats = quantize_signed(data["X"], cfg.input_scale, 16)
        result = ffn1_reference(xq, cfg.weight_q, cfg.bias_q, cfg.output_shift)
        expected = {"Xq": xq.astype(np.int16), "Wq": cfg.weight_q, "Wq_packed": cfg.weight_q.T.copy(),
                    "bq": cfg.bias_q, "Yq": result.output, "raw48": result.raw,
                    "overflow": result.overflow, "output_saturated": result.output_saturated}
        if set(case["arrays"]) != set(expected):
            raise ValueError("missing or unexpected integer array")
        for name, value in expected.items():
            actual = load_array(output, case["arrays"][name], value.shape, value.dtype)
            if not np.array_equal(actual, value):
                raise ValueError("stored integer vector differs from exact rule: " + name)
        metrics = _metrics(result.output.astype(np.float64) * cfg.output_scale, data["Y"])
        saturation = {"input": xstats["saturated"], "weight": cfg.weight_stats["saturated"],
                      "bias": cfg.bias_stats["saturated"], "raw48": int(result.overflow.sum()),
                      "output32": int(result.output_saturated.sum())}
        if metrics != case["metrics"] or saturation != case["saturation"] or case["input_stats"] != xstats:
            raise ValueError("case numerical metrics do not match saved/source arrays")
    per_layer, summary = _aggregate(manifest["cases"])
    if manifest["per_layer"] != per_layer or manifest["summary"] != summary:
        raise ValueError("aggregate numerical metrics mismatch")
    if manifest["case_count"] != 36 or manifest["output_count"] != 912384:
        raise ValueError("incomplete full-sized vector inventory")
    return {"status": "PASS", "case_count": 36, "array_count": 288, "output_count": 912384,
            "official_files_verified": 124, "max_case_nrmse": summary["max_case_nrmse"],
            "max_layer_nrmse": summary["max_layer_nrmse"]}
