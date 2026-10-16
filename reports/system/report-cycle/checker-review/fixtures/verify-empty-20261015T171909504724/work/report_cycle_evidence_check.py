"""Read accepted evidence without launching simulation or changing frozen results."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import tempfile
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "reports/system/report-cycle"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha(path):
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def load(path):
    return json.loads(path.read_text(encoding="utf-8-sig"))


def check_map(base, mapping):
    require(isinstance(mapping, dict) and mapping, "empty hash inventory")
    for name, expected in mapping.items():
        path = base / name
        require(path.is_file() and sha(path) == expected, "changed/missing hash member: " + name)


def read_words(path):
    words = path.read_text(encoding="ascii").splitlines()
    require(bool(words) and all(re.fullmatch(r"[0-9a-fA-F]{8}", w) for w in words), "malformed hex " + str(path))
    return [int(w, 16) for w in words]


def compare_words(got, expected):
    require(len(got) == len(expected), "incomplete word sequence")
    require(all((w & 0x7F800000) != 0x7F800000 for w in got), "nonfinite FP32 word")
    require(got == expected, "word mismatch")


def summary_fields(text):
    require(text.startswith("E203_ENCODER_PASS "), "missing actual CPU success summary")
    return {k: int(v) for k, v in re.findall(r"(\w+)=(\d+)", text)}


def validate_timing(fields, reported):
    require(fields["final_write_cycle"] - fields["begin_cycle"] + 1 == fields["end_to_end_cycles"], "inclusive timing mismatch")
    parts = ["initial_mmio_to_first_host_request_cycles", "host_load_cycles",
             "parameter_ready_to_start_cycles", "start_to_next_request_or_final_write_cycles"]
    require(sum(reported[k] for k in parts) == fields["end_to_end_cycles"] == reported["end_to_end_cycles"], "timing segments mismatch")
    require(len(reported["layers"]) == 12 and [r["layer"] for r in reported["layers"]] == list(range(12)), "partial layer timings")
    for name in parts[1:]:
        require(sum(r[name] for r in reported["layers"]) == reported[name], "layer timing sum mismatch: " + name)


def self_test():
    rejected = []

    def reject(name, action):
        try:
            action()
        except (ValueError, OSError):
            rejected.append(name)
        else:
            raise AssertionError("accepted negative fixture: " + name)

    with tempfile.TemporaryDirectory() as td:
        base = Path(td)
        (base / "x").write_bytes(b"actual")
        check_map(base, {"x": sha(base / "x")})
        nested = base / "review"
        nested.mkdir()
        (nested / "result.json").write_text("{}", encoding="utf-8")
        check_map(nested, {"result.json": sha(nested / "result.json")})
        reject("wrong-manifest-base", lambda: check_map(base, {"result.json": sha(nested / "result.json")}))
        reject("missing-file", lambda: check_map(base, {"missing": "0" * 64}))
        reject("wrong-hash", lambda: check_map(base, {"x": "0" * 64}))
        reject("empty-inventory", lambda: check_map(base, {}))
        compare_words([0x3F800000], [0x3F800000])
        reject("wrong-output", lambda: compare_words([0], [1]))
        reject("partial-output", lambda: compare_words([0], [0, 0]))
        reject("nonfinite-output", lambda: compare_words([0x7F800000], [0x7F800000]))
        reject("fake-cpu-summary", lambda: summary_fields("COMPILED_ONLY layers=12"))
        fields = {"begin_cycle": 3, "final_write_cycle": 14, "end_to_end_cycles": 12}
        report = dict(initial_mmio_to_first_host_request_cycles=0, host_load_cycles=12,
                      parameter_ready_to_start_cycles=0, start_to_next_request_or_final_write_cycles=0,
                      end_to_end_cycles=12, layers=[dict(layer=i, host_load_cycles=1,
                      parameter_ready_to_start_cycles=0, start_to_next_request_or_final_write_cycles=0) for i in range(12)])
        validate_timing(fields, report)
        reject("exclusive-timing", lambda: validate_timing(dict(fields, end_to_end_cycles=11), report))
        reject("segment-mismatch", lambda: validate_timing(fields, dict(report, host_load_cycles=13)))
    return {"status": "PASS", "negative_fixtures_rejected": len(rejected), "negative_cases": rejected,
            "checker_sha256": sha(Path(__file__)), "checked_utc": datetime.now(timezone.utc).isoformat()}


def readback():
    bound = {}
    comparisons = []

    def bind(name, expected=None):
        path = Path(name)
        if str(name).startswith("/mnt/c/"):
            path = Path("C:/" + str(name)[7:])
        if not path.is_absolute():
            path = ROOT / path
        # All execution evidence is inside this workspace. The original PDF is
        # separately checked below and is the only explicitly authorized external input.
        key = path.relative_to(ROOT).as_posix()
        actual = bound.get(key)
        if actual is None:
            require(path.is_file(), "missing evidence: " + key)
            actual = sha(path)
            bound[key] = actual
        require(expected is None or actual == expected, "stale evidence: " + key)
        return path

    def mapping(values):
        require(isinstance(values, dict) and values, "empty binding map")
        for name, expected in values.items():
            bind(name, expected)

    acceptance = load(bind("reports/system/root-formal-acceptance.json"))
    require(acceptance["status"] == "ACCEPTED_LOCAL_DRAFT" and acceptance["root_acceptance"] is True, "hardware not independently accepted")
    mapping(acceptance["evidence_sha256"])
    mapping(acceptance["review_inputs_sha256"])
    freeze = load(bind("work/encoder_source_freeze.json", acceptance["source_freeze_sha256"]))
    require(len(freeze["source_sha256"]) == 192, "wrong freeze size")
    mapping(freeze["source_sha256"])
    old_runner = load(bind("reports/system/formal-baseline/runner-state.json"))
    require(old_runner["exit_code"] == 0 and old_runner["run_id"] == acceptance["outer_run_id"], "wrong accepted runner")
    require(old_runner["round"] == acceptance["outer_round"] and old_runner["round_finished_at"], "incomplete accepted round")
    unified = load(bind("reports/encoder/verification/unified/status.json"))
    commands = load(bind("reports/encoder/verification/unified/commands.json"))
    require(unified["status"] == "PASS" and unified["run_id"] == acceptance["unified_run_id"], "unified identity mismatch")
    require(len(commands) == 34, "partial unified commands")
    actual = [r for r in commands if r["identity"] == "ACTUAL_EXECUTION"]
    require(len(actual) == 5 and len(commands) - len(actual) == 29, "wrong command classes")
    require(all(r["exit_code"] == 0 and r["run_id"] == unified["run_id"] for r in actual), "failed/mixed unified execution")

    source = load(bind("work/report_cycle_sources/manifest.json"))
    original = Path(source["pdf_path"])
    require(original.is_file() and sha(original) == source["pdf_sha256"], "original PDF changed")
    bind(source["workspace_pdf_copy"], source["pdf_sha256"])
    bind(source["text_path"], source["text_sha256"])

    completed = load(bind("reports/system/root-encoder-completed-readback.json"))
    unique_cases, rtl_words, trace_words = set(), 0, 0
    for item in completed["records"]:
        record_path = bind(item["record"], item["record_sha256"])
        record, folder = load(record_path), record_path.parent
        require(record["status"] == "PASS" and record["exit_code"] == 0 and record["layers"] == 12, "incomplete RTL record")
        for key in ["source_sha256", "compiled_source_sha256", "input_sha256"]:
            mapping(record[key])
        for filename, key in [("output.hex", "output_sha256"), ("simulation.log", "log_sha256"),
                              ("compile.log", "compile_log_sha256"), ("build.json", "build_key_sha256")]:
            bind(folder / filename, record[key])
        bind(record["command"][0], record["binary_sha256"])
        expected = []
        for layer in range(12):
            ref = bind(f"reports/encoder/{record['reference']}/cases/{record['case']}/layer_{layer:02d}/y.hex")
            expected.extend(read_words(ref))
        words = read_words(folder / "output.hex")
        compare_words(words, expected)
        require(len(words) == record["output_words"] == 76032, "wrong RTL words")
        if folder.name != "repeat":
            unique_cases.add((record["reference"], record["case"]))
            rtl_words += len(words)
        if "trace_words" in record:
            trace = bind(folder / "trace.txt", record["trace_sha256"])
            with trace.open(encoding="ascii") as stream:
                count = sum(1 for _ in stream)
            require(count == record["trace_words"] == 1603800, "partial trace")
            trace_words += count
        comparisons.append({"record": item["record"], "kind": "RTL", "words": len(words), "bit_mismatches": 0})
    require(len(completed["records"]) == 16 and len(unique_cases) == 15 and rtl_words == 1140480, "wrong RTL coverage")
    first = load(ROOT / "reports/encoder/rtl/full/original-0/status.json")
    repeat = load(ROOT / "reports/encoder/rtl/repeat/status.json")
    require(first["pid"] != repeat["pid"] and first["started_unix"] != repeat["started_unix"], "repeat is same execution")
    require(first["output_sha256"] == repeat["output_sha256"] and first["case"] == repeat["case"], "repeat identity mismatch")

    perf = load(bind("reports/encoder/verification/performance.json"))
    bind("scripts/encoder_report.py", perf["source_sha256"])
    cpu_fields = {}
    for policy, output_words in [("pingpong", 6336), ("reload", 76032)]:
        prefix = f"reports/encoder/system/{policy}"
        record_path = bind(prefix + "/status.json", perf["policies"][policy]["status_sha256"])
        record = load(record_path)
        require(record["status"] == "PASS" and record["exit_code"] == 0 and record["layers"] == 12, "incomplete CPU record")
        for key in ["source_sha256", "compiled_source_sha256", "input_sha256"]:
            mapping(record[key])
        for filename, key in [("firmware.elf", "firmware_sha256"), ("cpu-output.hex", "output_sha256"),
                              ("neural-output.hex", "neural_sha256"), ("simulation.log", "log_sha256"),
                              ("compile.log", "compile_log_sha256"), ("build.json", "build_key_sha256")]:
            bind(prefix + "/" + filename, record[key])
        bind(record["command"][0], record["binary_sha256"])
        # These ELF-derived files are also independently bound in the accepted CPU review.
        for filename in ["firmware.bin", "firmware.hex", "firmware.map", "firmware-disassembly.log"]:
            bind(prefix + "/" + filename)
        expected = []
        for layer in range(12):
            expected.extend(read_words(bind(f"reports/encoder/reference/cases/{record['case']}/layer_{layer:02d}/y.hex")))
        neural = read_words(ROOT / prefix / "neural-output.hex")
        cpu = read_words(ROOT / prefix / "cpu-output.hex")
        compare_words(neural, expected)
        compare_words(cpu, expected[-6336:] if policy == "pingpong" else expected)
        require(len(neural) == record["neural_words"] == 76032 and len(cpu) == record["output_words"] == output_words, "wrong CPU coverage")
        log_text = (ROOT / prefix / "simulation.log").read_text(encoding="utf-8")
        require(record["summary"] in log_text, "CPU summary not from actual log")
        fields = summary_fields(record["summary"])
        validate_timing(fields, perf["policies"][policy])
        require(fields["host_words"] == fields["cpu_weight_words"] == 597504, "wrong host load")
        cpu_fields[policy] = fields
        comparisons.append({"record": prefix + "/status.json", "kind": "CPU", "neural_words": len(neural), "cpu_words": len(cpu), "bit_mismatches": 0})
    metrics = {}
    for metric, per_policy in {
        "end_to_end_cycles": {p: f["end_to_end_cycles"] for p, f in cpu_fields.items()},
        "cpu_shared_transactions": {p: f["shared_reads"] + f["shared_writes"] for p, f in cpu_fields.items()},
        "model_shared_transactions": {p: f["shared_reads"] + f["shared_writes"] + f["host_words"] + 12 + 12 for p, f in cpu_fields.items()},
    }.items():
        result = dict(per_policy, saved=per_policy["reload"] - per_policy["pingpong"])
        result["saved_fraction_of_reload"] = result["saved"] / result["reload"]
        for k, value in result.items():
            require(abs(perf["comparison"][metric][k] - value) < 1e-12, "performance mismatch " + metric + "." + k)
        metrics[metric] = result
    cpu_manifest = load(bind("reports/system/review/encoder-final-cpu-readback/manifest.json"))
    for name, expected in cpu_manifest["artifacts_sha256"].items():
        bind("reports/system/review/encoder-final-cpu-readback/" + name, expected)
    with bind("reports/encoder/verification/rtl-case-results.csv").open(encoding="utf-8", newline="") as stream:
        case_count = len(list(csv.DictReader(stream)))
    with bind("reports/encoder/verification/rtl-layer-results.csv").open(encoding="utf-8", newline="") as stream:
        layer_count = len(list(csv.DictReader(stream)))
    require(case_count == 15 and layer_count == 180, "CSV coverage mismatch")
    # The inputs were read serially. Re-hash the final inventory to reject drift.
    check_map(ROOT, bound)
    return {"status": "PASS", "checked_utc": datetime.now(timezone.utc).isoformat(),
            "checker_sha256": sha(Path(__file__)), "scope": "Accepted local evidence readback; no simulation, synthesis or search",
            "baseline_acceptance": "reports/system/root-formal-acceptance.json", "baseline_accepted": True,
            "unified_run_id": unified["run_id"], "frozen_sources_checked": 192,
            "root_evidence_checked": len(acceptance["evidence_sha256"]), "root_review_inputs_checked": len(acceptance["review_inputs_sha256"]),
            "original_pdf_sha256": source["pdf_sha256"], "rtl_unique_inputs": 15, "rtl_layers": 180,
            "rtl_unique_output_words": rtl_words, "rtl_repeat_output_words": 76032,
            "trace_words_hash_and_length_checked": trace_words,
            "trace_note": "All trace bytes bound to accepted independent per-word readback; trace arithmetic not re-executed here",
            "cpu_neural_words": 152064, "cpu_writeback_words": 82368, "comparisons": comparisons,
            "performance_recomputed": metrics, "artifacts_sha256": bound, "unique_bound_files": len(bound),
            "formal_acceptance": "EXTERNAL_PENDING", "root_report_acceptance": False}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    OUT.mkdir(parents=True, exist_ok=True)
    target = OUT / ("evidence-self-test.json" if args.self_test else "evidence-check.json")
    try:
        result = self_test() if args.self_test else readback()
    except Exception as exc:
        result = {"status": "FAIL", "checked_utc": datetime.now(timezone.utc).isoformat(), "error": str(exc), "checker_sha256": sha(Path(__file__))}
        target.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        raise
    target.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in result.items() if k in ["status", "negative_fixtures_rejected", "unique_bound_files", "frozen_sources_checked", "rtl_unique_output_words", "cpu_neural_words"]}))


if __name__ == "__main__":
    main()
