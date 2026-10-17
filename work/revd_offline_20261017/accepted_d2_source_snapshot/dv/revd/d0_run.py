"""D0 read-only source freeze, exact-reference execution and input validation."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import platform
from pathlib import Path
import random
import subprocess
import sys
import uuid

sys.dont_write_bytecode = True

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))

from dv.revd.d0_inputs import validated_case, verify_frozen_inputs
from numeric.fixedpoint import dot64_reference, ffn1_reference

BASE = "3d9d0fc77457b8869cbf525d826dafb114f2a8e1"
BLOB = "116dfb84c51a6847cb10678c9e5a7230fb796598"


def sha(path):
    h = hashlib.sha256()
    with Path(path).open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def write(path, data):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2, sort_keys=True, ensure_ascii=False,
                               allow_nan=False) + "\n", encoding="utf-8")


def read(path):
    return json.loads(Path(path).read_text(encoding="utf-8"))


def git(*args):
    run = subprocess.run(["git", "-C", str(ROOT), *args], capture_output=True,
                         text=True, encoding="utf-8", check=True, timeout=60)
    return run.stdout.strip()


def identity():
    release = read(ROOT / "work/revd/MASTER_RELEASE.json")
    launch = read(ROOT / "work/revd/launch_baseline.json")
    if git("branch", "--show-current") != "v2":
        raise ValueError("must remain on branch v2")
    head = git("rev-parse", "HEAD")
    git("merge-base", "--is-ancestor", BASE, head)
    numeric = (ROOT / "numeric/fixedpoint.py").read_bytes()
    blob = hashlib.sha1(b"blob " + str(len(numeric)).encode() + b"\0" + numeric).hexdigest()
    if blob != BLOB:
        raise ValueError("pinned numeric git blob changed")
    freeze_path = ROOT / launch["protected_freeze_path"]
    if sha(freeze_path) != release["protected_source_freeze_sha256"]:
        raise ValueError("protected source freeze manifest changed")
    frozen = read(freeze_path)["source_sha256"]
    if len(frozen) != 192:
        raise ValueError("expected 192 protected sources")
    for name, expected in frozen.items():
        if sha(ROOT / name) != expected:
            raise ValueError("protected source changed: " + name)
    for name, expected in launch["tracked_file_sha256"].items():
        if sha(ROOT / name) != expected:
            raise ValueError("preexisting tracked file changed: " + name)
    snapshot_receipt = read(ROOT / launch["source_snapshot_receipt"])
    for item in snapshot_receipt["files"]:
        if sha(ROOT / "docs/revd" / item["path"]) != item["sha256"]:
            raise ValueError("RevD read-only package changed: " + item["path"])
    return {"schema_version": 1, "status": "PASS", "checked_utc": datetime.now(timezone.utc).isoformat(),
            "branch": "v2", "head": head, "baseline_commit": BASE, "baseline_is_ancestor": True,
            "golden_path": "numeric/fixedpoint.py", "golden_git_blob": blob,
            "golden_sha256": sha(ROOT / "numeric/fixedpoint.py"),
            "protected_manifest": launch["protected_freeze_path"], "protected_count": len(frozen),
            "protected_manifest_sha256": sha(freeze_path), "protected_source_sha256": frozen,
            "tracked_inventory_count": len(launch["tracked_file_sha256"]),
            "launch_baseline_sha256": sha(ROOT / "work/revd/launch_baseline.json"),
            "snapshot_file_count": len(snapshot_receipt["files"]),
            "snapshot_receipt_sha256": sha(ROOT / launch["source_snapshot_receipt"]),
            "git_status": git("status", "--porcelain=v1", "--untracked-files=normal"),
            "git_diff": git("diff", "--stat"), "git_staged_diff": git("diff", "--cached", "--stat"),
            "git_remotes": git("remote", "-v")}


def source_manifest():
    files = {}
    for prefix in ("rtl/revd", "dv/revd", "config/revd"):
        for path in sorted((ROOT / prefix).rglob("*")):
            if path.is_file() and "__pycache__" not in path.parts:
                files[path.relative_to(ROOT).as_posix()] = sha(path)
    for name in ("scripts/run_revd_trial.sh", "scripts/revd_trial_gate.py",
                 "work/revd/MASTER_RELEASE.json", "work/revd/requirements.json",
                 "work/revd/contracts.json", "work/revd/baseline.json"):
        path = ROOT / name
        if path.is_file():
            files[name] = sha(path)
    return {"schema_version": 1, "created_utc": datetime.now(timezone.utc).isoformat(),
            "head": git("rev-parse", "HEAD"), "includes_untracked_sources": True,
            "excludes": ["dynamic STATUS/results/logs", "source_manifest itself", "__pycache__"],
            "files": files}


def execute(out, key, command, timeout=600):
    started = datetime.now(timezone.utc).isoformat()
    run = subprocess.run(command, cwd=ROOT, capture_output=True, timeout=timeout)
    (out / (key + ".stdout.log")).write_bytes(run.stdout)
    (out / (key + ".stderr.log")).write_bytes(run.stderr)
    record = {"command": [str(x) for x in command], "cwd": str(ROOT), "exit_code": run.returncode,
              "started_utc": started, "finished_utc": datetime.now(timezone.utc).isoformat(),
              "stdout": (out / (key + ".stdout.log")).relative_to(ROOT).as_posix(),
              "stderr": (out / (key + ".stderr.log")).relative_to(ROOT).as_posix()}
    write(out / (key + ".command.json"), record)
    if run.returncode:
        raise ValueError(key + " actual process failed: " + str(run.returncode))
    return record


def preserve_v0_vectors(out):
    sys.path.insert(0, str(ROOT / "docs/revd/tools"))
    from core_model import Geometry, make_case, finalize
    folder = out / "v0_vectors"
    folder.mkdir(exist_ok=False)
    rng = random.Random(20261017)
    with (folder / "scalar_vectors.jsonl").open("w", encoding="utf-8") as sink:
        for shift in range(48):
            for ordinal in range(16):
                x = [rng.randint(-32768, 32767) for _ in range(64)]
                w = [rng.randint(-32768, 32767) for _ in range(64)]
                bias = rng.choice([-(2**47), 2**47 - 1, rng.randint(-(2**46), 2**46)])
                old = dot64_reference(x, w, bias, shift)
                independent = finalize(sum(a * b for a, b in zip(x, w)), bias, shift)
                expected = {"raw48": old.raw, "Y": old.output, "overflow": old.overflow,
                            "saturated": old.output_saturated}
                if (old.raw, old.output, old.overflow, old.output_saturated) != (
                        independent.raw, independent.data, independent.overflow, independent.saturated):
                    raise ValueError("scalar replay differs")
                sink.write(json.dumps({"vector": shift * 16 + ordinal, "shift": shift,
                                       "x": x, "w": w, "bias": bias, "expected": expected}) + "\n")
    case = make_case(Geometry(), 20261017, 8)
    full = ffn1_reference(case["x"], case["w"], case["bias"], 8)
    arrays = {"X": np.array(case["x"], dtype=np.int16), "W": np.array(case["w"], dtype=np.int16),
              "b": np.array(case["bias"], dtype=np.int64), "raw48": full.raw, "Y": full.output,
              "overflow": full.overflow, "saturated": full.output_saturated}
    descriptors = {}
    for name, array in arrays.items():
        path = folder / (name + ".npy")
        np.save(path, array, allow_pickle=False)
        descriptors[name] = {"path": path.relative_to(ROOT).as_posix(), "sha256": sha(path),
                             "shape": list(array.shape), "dtype": str(array.dtype)}
    report = {"scalar_count": 768, "scalar_vectors": (folder / "scalar_vectors.jsonl").relative_to(ROOT).as_posix(),
              "scalar_sha256": sha(folder / "scalar_vectors.jsonl"), "full_matrix_outputs": 25344,
              "seed": 20261017, "shift": 8, "full_matrix": descriptors,
              "origin": "Exact replay of compare_v0 RNG/inputs; pinned numeric result arrays retained"}
    write(folder / "manifest.json", report)
    return report


def repack_all(out):
    manifest, verification = verify_frozen_inputs(ROOT)
    results = []
    layers = {}
    for case in manifest["cases"]:
        data = validated_case(ROOT, case)
        tiles, biases = data["W_tiles"], data["b_tiles"]
        # Independent dense mathematical loops, no DUT bank/scheduler address helper.
        for n in range(256):
            for k in range(64):
                if int(tiles[n // 16, k * 16 + n % 16]) != int(data["Wq"][k, n]):
                    raise ValueError("repacking mismatch " + case["case_id"])
            if int(biases[n // 16, n % 16]) != int(data["bq"][n]):
                raise ValueError("bias repacking mismatch")
        results.append({"case_id": case["case_id"], "layer": case["layer"],
                        "weights_checked": 16384, "biases_checked": 256,
                        "sentinel_columns": [0, 15, 16, 255],
                        "tile_words_sha256": hashlib.sha256(tiles.tobytes()).hexdigest(),
                        "bias_words_sha256": hashlib.sha256(biases.tobytes()).hexdigest(),
                        "input_arrays": case["arrays"]})
        parameter_identity = {"Wq_sha256": case["arrays"]["Wq"]["sha256"],
                              "bq_sha256": case["arrays"]["bq"]["sha256"],
                              "output_shift": case["config"]["output_shift"]}
        layer = str(case["layer"])
        if layer in layers and layers[layer]["parameters"] != parameter_identity:
            raise ValueError("same-layer parameter identity differs across samples")
        if layer not in layers:
            layers[layer] = {"parameters": parameter_identity, "cases": []}
        layers[layer]["cases"].append(case["case_id"])
    if len(layers) != 12 or any(len(layer["cases"]) != 3 for layer in layers.values()):
        raise ValueError("must cover three independent inputs for each of twelve layers")
    report = {"status": "PASS", "verification_api": "numeric.artifacts.verify_vectors",
              "verification_result": verification,
              "vector_manifest": "reports/prototype/vectors/manifest.json",
              "vector_manifest_sha256": sha(ROOT / "reports/prototype/vectors/manifest.json"),
              "numeric_handoff_sha256": sha(ROOT / "work/numeric_handoff.json"),
              "baseline_manifest_sha256": sha(ROOT / "reports/model/baseline/manifest.json"),
              "case_count": len(results), "layers": sorted({x["layer"] for x in results}),
              "layer_identities": layers,
              "weights_checked": len(results) * 16384, "biases_checked": len(results) * 256,
              "cases": results}
    write(out / "validated_inputs.json", report)
    return report


def contracts(out):
    import fitz
    path = ROOT / "work/report_cycle_sources/2026赛题指南.pdf"
    document = fitz.open(path)
    if len(document) != 15:
        raise ValueError("guide physical page count must be15")
    pages = [{"physical_page": i + 1, "text": page.get_text()} for i, page in enumerate(document)]
    write(out / "guide_pages.json", {"source": path.relative_to(ROOT).as_posix(),
                                     "sha256": sha(path), "physical_page_count": len(document), "pages": pages})
    mapping = [
        {"id": "TASK1_DOT64", "physical_pages": [8], "stage": "D1", "checks": ["64 signed16 products", "bias", "RNE0..47", "raw48/Y/both flags"]},
        {"id": "TASK1_BOUNDARY_PROTOCOL", "physical_pages": [8], "stage": "D1-D2", "checks": ["normal", "boundaries", "reset", "continuous tasks", "ready-valid stability"]},
        {"id": "TASK2_FFN1", "physical_pages": [8], "stage": "D2", "checks": ["99x64x256", "25344 unique outputs", "1622016 valid MAC", "parameter load", "independent output stream"]},
        {"id": "TASK2_LAYER_SWITCH", "physical_pages": [8], "stage": "D2", "checks": ["36 engineering inputs=3x12", "cold reload all W/b", "layer identity"], "official_600_acceptance": False},
        {"id": "RTL_BIT_TRUE", "physical_pages": [11], "stage": "D1-D2", "checks": ["exact integer reference", "NRMSE not an RTL error tolerance"]},
        {"id": "TASK3_SOC", "physical_pages": [4, 8, 12, 14], "status": "NOT_RUN", "deferred": "E203 integration/driver/formal library pre-post synth"},
        {"id": "OFFICIAL_NUMERICAL", "physical_pages": [8, 11], "status": "NOT_RUN", "criterion": "600 official samples, worst12-layer aggregate NRMSE<=3%, finite decoded outputs"},
        {"id": "OFFICIAL_PERFORMANCE", "physical_pages": [12], "status": "NOT_RUN", "criterion": "12 cold tasks incl parameter/input load, E203/bus waits, final writeback"},
        {"id": "STA150", "physical_pages": [4, 12], "status": "NOT_RUN", "criterion": "150MHz official library and valid constraints; behavioral period insufficient"},
        {"id": "AREA", "physical_pages": [13], "status": "NOT_RUN", "criterion": "new accelerator+interface+internal SRAM<=2.25mm2; fixed E203/sharedSRAM excluded"},
        {"id": "POWER_ENERGY", "physical_pages": [12, 13], "status": "NOT_RUN", "criterion": "same frozen configuration/window, E203+accelerator+interconnect+SRAM activity and library models"},
        {"id": "NO_PRECOMPUTED_HARDWARE_ANSWERS", "physical_pages": [5, 15], "stage": "D1-D2", "checks": ["DUT executes all MAC and quantization", "TB only reference and observation", "no private RAM writes or answer injection"]},
    ]
    result = {"schema_version": 1, "source": path.relative_to(ROOT).as_posix(), "source_sha256": sha(path),
              "physical_page_count": 15, "physical_pages_read": list(range(1, 16)),
              "priority_physical_pages": [4, 8, 11, 12, 13, 14], "source_test_mapping": mapping,
              "numeric": {"K": 64, "input": "signed16", "bias": "signed48", "sum_plus_bias": "signed49",
                          "sequence": ["exact sum of64 signed16 products k ascending", "add bias in signed49", "sat48", "RNE shift0..47", "sat32"],
                          "overflow": "bias addition exceeded signed48", "saturated": "only final signed32 truncation"},
              "geometry": {"M": 99, "K": 64, "N": 256, "PM": 4, "PN": 4, "N_TILE": 16},
              "input_events": ["BEGIN", "LOAD_X", "TILE_OPEN", "LOAD_W", "LOAD_B", "TILE_COMMIT", "START"],
              "load_order": "V1_full: load every X and W/b tile then START; accept != write retire; COMMIT waits writes",
              "public_output": ["task_id", "y_index", "data", "overflow", "saturated", "last"],
              "public_order": "tile -> row_group -> valid row -> tile column; y_index=m*N+n",
              "raw48_observation": "D1 quant_epilogue standalone public output only, not D2 production stream",
              "reset": "synchronous active low; invalidate ownership/tags/counters; no full RAM clear",
              "deferred_P1": "Single E203 CPU must alternate nonblocking enqueue/status and Y drain; W/Y full fairness; accept vs retire; system_done after last write response",
              "source_contradictions": [], "official_contest_acceptance": False}
    write(ROOT / "work/revd/contracts.json", result)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--refresh-sources", action="store_true")
    arguments = parser.parse_args()
    if arguments.refresh_sources:
        write(ROOT / "work/revd/source_manifest.json", source_manifest())
        print("source manifest refreshed")
        return 0
    run_id = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "_" + uuid.uuid4().hex[:8]
    out = ROOT / "reports/revd/d0/frozen" / run_id
    out.mkdir(parents=True, exist_ok=False)
    record = {"schema_version": 1, "run_id": run_id, "run_dir": out.relative_to(ROOT).as_posix(),
              "started_utc": datetime.now(timezone.utc).isoformat(), "status": "RUNNING", "commands": [],
              "tools": {"python": sys.version, "numpy": np.__version__, "platform": platform.platform()}}
    try:
        dependency_names = [path.relative_to(ROOT).as_posix() for path in sorted((ROOT / "dv/revd").glob("d0*.py"))]
        dependency_names += ["numeric/fixedpoint.py", "numeric/artifacts.py", "docs/revd/tools/compare_v0.py",
                             "docs/revd/tools/core_model.py", "scripts/prepare_repository.py",
                             "work/revd/MASTER_RELEASE.json", "work/revd/requirements.json"]
        record["execution_sources"] = {name: sha(ROOT / name) for name in dependency_names}
        baseline = identity()
        write(ROOT / "work/revd/baseline.json", baseline)
        write(out / "baseline_start.json", baseline)
        print("D0 protected192/tracked/snapshot/golden verified", flush=True)
        if sys.platform == "win32":
            command = ["wsl", "-d", "Ubuntu-24.04", "--", "bash", "-lc",
                       "cd /mnt/d/github/kwt && python3 scripts/prepare_repository.py --check"]
        else:
            command = [sys.executable, "scripts/prepare_repository.py", "--check"]
        record["commands"].append(execute(out, "prepare_check", command))
        record["commands"].append(execute(out, "input_unit_tests", [sys.executable, "-B", "-X", "utf8", "-m", "unittest", "dv.revd.d0_test_inputs", "-v"]))
        record["commands"].append(execute(out, "artifact_negatives", [sys.executable, "-B", "-X", "utf8", "dv/revd/d0_artifact_negatives.py",
                                                                     "--out", str(out / "artifact_negatives")]))
        record["commands"].append(execute(out, "compare_v0", [sys.executable, "-B", "-X", "utf8", "docs/revd/tools/compare_v0.py",
                                                "--source", "numeric/fixedpoint.py", "--out", str(out / "compare_v0"), "--full"]))
        compare = read(out / "compare_v0/compare_v0.json")
        if compare["vectors"] != 768 or compare["full_matrix_outputs"] != 25344:
            raise ValueError("incomplete V0 comparison")
        record["v0_compare"] = compare
        record["retained_vectors"] = preserve_v0_vectors(out)
        print("D0 real compare_v0 --full:768 scalar +25344 matrix outputs; vectors retained", flush=True)
        validated = repack_all(out)
        record["inputs"] = {k: v for k, v in validated.items() if k != "cases"}
        record["validated_inputs"] = (out / "validated_inputs.json").relative_to(ROOT).as_posix()
        print("D0 verify_vectors +repack:36 cases/12layers verified", flush=True)
        record["contracts"] = contracts(out)
        final_identity = identity()
        if final_identity["head"] != baseline["head"] or final_identity["git_remotes"] != baseline["git_remotes"]:
            raise ValueError("Git head/remote changed during D0")
        write(out / "baseline_end.json", final_identity)
        for name, expected in record["execution_sources"].items():
            if sha(ROOT / name) != expected:
                raise ValueError("D0 execution dependency changed during run: " + name)
        record["status"] = "PASS"
        record["exit_code"] = 0
    except Exception as error:
        record["status"] = "FAIL"
        record["exit_code"] = 1
        record["error"] = repr(error)
        import traceback
        (out / "failure.log").write_text(traceback.format_exc(), encoding="utf-8")
    record["finished_utc"] = datetime.now(timezone.utc).isoformat()
    record["artifacts_sha256"] = {path.relative_to(ROOT).as_posix(): sha(path)
                                  for path in sorted(out.rglob("*")) if path.is_file()}
    write(out / "run_manifest.json", record)
    write(ROOT / "work/revd/d0_result.json", record)
    write(ROOT / "work/revd/source_manifest.json", source_manifest())
    print(json.dumps({"status": record["status"], "run_dir": record["run_dir"], "error": record.get("error")}))
    return record["exit_code"]


if __name__ == "__main__":
    raise SystemExit(main())
