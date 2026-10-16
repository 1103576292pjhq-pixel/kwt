"""Root-only final acceptance of completed, independently read local evidence.

Does not run simulation or rewrite producer statuses. A running/failed/stale round
is rejected before reading the rest of the evidence.
"""
from __future__ import annotations

import hashlib
import json
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def read(name):
    return json.loads((ROOT / name).read_text(encoding="utf-8"))


def resolve(name):
    if name.startswith("/mnt/c/"):
        return Path("C:/" + name[7:])
    p = Path(name)
    return p if p.is_absolute() else ROOT / p


def sha(path):
    h = hashlib.sha256()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def require(ok, why):
    if not ok:
        raise ValueError(why)


def round_boundary(state, unified, gate):
    require(state["status"] in {"AWAITING_REVIEW", "ACCEPTED_LOCAL_DRAFT"}, "CLI round is not completed and ready")
    require(state.get("exit_code") == 0, "CLI did not exit zero")
    require(unified["status"] == "PASS", "unified invocation did not pass")
    require(gate["status"] == "PASS" and unified["run_id"] == gate["run_id"], "gate is not from successful unified invocation")
    start = datetime.fromisoformat(state["round_started_at"].replace("Z", "+00:00")).timestamp()
    finish = datetime.fromisoformat(state["round_finished_at"].replace("Z", "+00:00")).timestamp()
    require(start <= unified["started_unix"] <= gate["created_unix"] <= unified["completed_unix"] <= finish + 1, "stale/cross-round readiness")
    require(len(unified["run_id"]) == 32, "invalid invocation identity")
    return start, finish


def boundary_negative_checks():
    """Acceptance guard must reject running, failed, stale and cross-run fixtures."""
    s = {"status": "AWAITING_REVIEW", "exit_code": 0, "round_started_at": "2026-10-15T16:00:00Z", "round_finished_at": "2026-10-15T17:00:00Z"}
    t = datetime(2026, 10, 15, 16, tzinfo=timezone.utc).timestamp()
    u = {"status": "PASS", "run_id": "a" * 32, "started_unix": t + 10, "completed_unix": t + 100}
    g = {"status": "PASS", "run_id": "a" * 32, "created_unix": t + 90}
    round_boundary(s, u, g)
    trials = [(dict(s, status="RUNNING"), u, g), (dict(s, exit_code=1), u, g), (s, dict(u, started_unix=t - 10), g), (s, u, dict(g, run_id="b" * 32))]
    for values in trials:
        try:
            round_boundary(*values)
        except ValueError:
            continue
        raise AssertionError("boundary negative fixture was accepted")
    return len(trials)


def main():
    negatives = boundary_negative_checks()
    state = read(".omx/prototype-run.json")
    unified = read("reports/encoder/verification/unified/status.json")
    gate = read("reports/encoder/verification/gate.json")
    start, finish = round_boundary(state, unified, gate)
    status = read("work/encoder_status.json")
    require(status["status"] == "READY_FOR_REVIEW", "producer readiness is not ready")
    for key in [f"task{i}" for i in range(1, 8)]:
        require(status.get(key) is True and gate["tasks"].get(key) is True, "incomplete task " + key)
    require(status["full_encoder_cases"] == 15, "full case count changed")
    require("EXTERNAL_PENDING" in status["formal_acceptance"], "formal contest boundary lost")
    require((ROOT / "work/encoder_status.json").stat().st_mtime >= start, "stale readiness mtime")
    require(unified["source_sha256"] == sha(ROOT / "scripts/run_formal_seven.py"), "unified source changed")
    commands = unified["commands"]
    require(commands == read("reports/encoder/verification/unified/commands.json"), "command journal differs from successful status")
    actual = {entry["name"]: entry for entry in commands if entry["identity"] == "ACTUAL_EXECUTION"}
    for name in ["gate-tests", "gate-schema-mutation", "source-freeze", "final-evidence-gate", "render-report"]:
        require(name in actual, "missing actual stage " + name)
    for entry in commands:
        if entry["identity"] == "ACTUAL_EXECUTION":
            require(entry["exit_code"] == 0 and entry["run_id"] == unified["run_id"], "failed/cross-run actual command")
            require("--help" not in entry["command"], "help is not a verification run")
            require(unified["started_unix"] <= entry["started_unix"] <= entry["completed_unix"] <= unified["completed_unix"], "invalid command interval")
            require(sha(ROOT / "reports/encoder/verification/unified" / (entry["name"] + ".log")) == entry["log_sha256"], "actual command log changed")
        else:
            require(entry["identity"] == "EXPLICIT_VERIFIED_HISTORY" and entry.get("evidence"), "unverified history")
    for name in ["cpu-pingpong", "cpu-reload", "independent-repeat"] + [f"original-{i}" for i in range(3)] + [f"test12-{i}" for i in range(12)]:
        require(any(entry["name"] == name for entry in commands), "coverage missing " + name)
    review = read("reports/encoder/verification/review.json")
    require(review["status"] == "PASS" and review["rounds"] >= 2 and review["independent"] is True, "review incomplete")
    require(review["open_p1"] == review["open_p2"] == 0 and review["final_evidence_review_pending"] is False, "review has open problems")
    checked = {}
    for field in ["review_sha256", "source_sha256", "input_sha256"]:
        for name, expected in review[field].items():
            require(sha(resolve(name)) == expected, "review binding changed " + name)
            checked[name] = expected
    freeze = read("work/encoder_source_freeze.json")
    require(len(freeze["source_sha256"]) == 192, "freeze count changed")
    for name, expected in freeze["source_sha256"].items():
        require(sha(resolve(name)) == expected, "production source changed " + name)
    freeze_sha = sha(ROOT / "work/encoder_source_freeze.json")
    rtl = read("reports/system/root-encoder-completed-readback.json")
    require(rtl["status"] == "COMPLETED_RECORDS_READBACK_PASS" and rtl["freeze_sha256"] == freeze_sha, "RTL independent readback not current")
    require((rtl["unique_full12_cases"], rtl["completed_processes"], rtl["full12_output_words"], rtl["independently_compared_trace_words"]) == (15, 16, 1216512, 1603800), "RTL coverage differs")
    for record in rtl["records"]:
        require(sha(ROOT / record["record"]) == record["record_sha256"], "RTL record changed after independent readback")
    common = read("reports/system/root-readback.json")
    require(common["status"] == "PASS" and common["icb_complete_cases"] == 36, "common base incomplete")
    require(common["cpu_full_output_and_flags_rechecked"] == common["cpu_repeat_output_and_flags_rechecked"] == 25344, "FFN1 CPU coverage incomplete")
    cpu_dir = ROOT / "reports/system/review/encoder-final-cpu-readback"
    cpu = read("reports/system/review/encoder-final-cpu-readback/result.json")
    require(cpu["status"] == "PASS" and cpu["freeze_sha256"] == freeze_sha, "CPU independent evidence not current")
    require((cpu["neural_words_independently_compared"], cpu["cpu_words_independently_compared"], cpu["bit_mismatches"], cpu["nonfinite_words"]) == (152064, 82368, 0, 0), "CPU result coverage differs")
    for name, expected in read("reports/system/review/encoder-final-cpu-readback/manifest.json")["artifacts_sha256"].items():
        require(sha(cpu_dir / name) == expected, "independent CPU artifact changed " + name)
    reference = read("reports/system/root-reference-readback.json")
    require(reference["status"] == "PASS" and reference["totals"]["samples"] == 15 and reference["totals"]["layers"] == 180, "reference readback incomplete")
    require(reference["handoff_sha256"] == sha(ROOT / "work/encoder_reference_handoff.json"), "reference release changed")
    synth = read("reports/system/root-encoder-synth-readback.json")
    require(synth["status"] == "PASS" and synth["top_reachable_modules"] == 278, "SoC structure readback missing")
    require(synth["status_sha256"] == sha(ROOT / "reports/encoder/synthesis/soc/status.json"), "SoC synthesis identity changed")
    cold_files = sorted((ROOT / "reports/system/root-fp32-cold").glob("*/status.json"))
    require(bool(cold_files), "root cold FP32 evidence missing")
    cold = json.loads(cold_files[-1].read_text(encoding="utf-8"))
    require(cold["status"] == "PASS", "root cold FP32 failed")
    artifact = read("reports/encoder/verification/report-artifact.json")
    require(artifact["report_sha256"] == sha(ROOT / "reports/encoder/verification/report.md"), "rendered report changed")
    require(artifact["gate_sha256"] == sha(ROOT / "reports/encoder/verification/gate.json"), "report is not rendered from final gate")
    require(artifact["generator_sha256"] == sha(ROOT / "scripts/encoder_report.py"), "reporter changed")
    require(artifact["utf8_readback"] is True and artifact["all_local_links_exist"] is True, "render checks failed")
    for name, expected in artifact["derived_sha256"].items():
        require(sha(ROOT / "reports/encoder/verification" / name) == expected, "derived report artifact changed " + name)
    # The next authorized serial task replaces .omx/prototype-run.json. Bind an
    # immutable accepted-round snapshot rather than that mutable pointer.
    snapshot = ROOT / "reports/system/formal-baseline/runner-state.json"
    snapshot.parent.mkdir(parents=True, exist_ok=True)
    snapshot.write_bytes((ROOT / ".omx/prototype-run.json").read_bytes())
    evidence_paths = [snapshot.relative_to(ROOT).as_posix(), "work/encoder_status.json", "work/encoder_source_freeze.json", "reports/encoder/verification/unified/status.json", "reports/encoder/verification/unified/commands.json", "reports/encoder/verification/gate.json", "reports/encoder/verification/review.json", "reports/encoder/verification/report-artifact.json", "reports/encoder/verification/report.md", "reports/system/root-readback.json", "reports/system/root-encoder-completed-readback.json", "reports/system/root-encoder-repeat-readback.json", "reports/system/root-reference-readback.json", "reports/system/root-encoder-synth-readback.json", "reports/system/review/encoder-final-cpu-readback.md", "reports/system/review/encoder-final-cpu-readback/manifest.json", cold_files[-1].relative_to(ROOT).as_posix()]
    acceptance = {
        "status": "ACCEPTED_LOCAL_DRAFT", "root_acceptance": True,
        "acceptor_sha256": sha(Path(__file__)),
        "checked_utc": datetime.now(timezone.utc).isoformat(), "outer_run_id": state["run_id"],
        "outer_round": state["round"], "outer_round_started_unix": start, "outer_round_finished_unix": finish,
        "unified_run_id": unified["run_id"], "source_freeze_sha256": freeze_sha,
        "negative_boundary_fixtures_rejected": negatives, "actual_commands": len(actual),
        "explicit_verified_history_commands": len(commands) - len(actual), "production_sources_checked": 192,
        "review_bound_files_checked": len(checked), "rtl_unique_inputs": 15, "rtl_output_words_with_repeat": 1216512,
        "cpu_neural_words": 152064, "cpu_writeback_words": 82368,
        "scope": "Official tasks 1..7 local prototype only; no target-platform contest acceptance",
        "formal_acceptance": "EXTERNAL_PENDING_PLATFORM_LIBRARIES_150MHZ_AREA_POWER_MAPPED_FUNCTION_600_AND_OFFICIAL_12_TASKS",
        "evidence_sha256": {name: sha(ROOT / name) for name in evidence_paths},
        "review_inputs_sha256": checked,
        "no_simulations_started": True,
    }
    out = ROOT / "reports/system/root-formal-acceptance.json"
    out.write_text(json.dumps(acceptance, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("ROOT_FORMAL_LOCAL_DRAFT_ACCEPTED", unified["run_id"], "sources=192 cases=15+repeat cpu=2")


if __name__ == "__main__":
    main()
