"""Root acceptance after actual outer exit and read-only verification.

Only writes new root evidence/snapshots. Producer status remains untouched.
"""
from __future__ import annotations

import hashlib
import json
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "reports/system/report-cycle"
EXPECTED_RUN = "20261015-165042-884"


def load(path):
    return json.loads(path.read_text(encoding="utf-8"))


def sha(path):
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(chunk)
    return value.hexdigest()


def require(ok, message):
    if not ok:
        raise ValueError(message)


def epoch(value):
    return datetime.fromisoformat(value.replace("Z", "+00:00")).timestamp()


def boundary(state, readiness, manifest, commands):
    require(state["status"] == "AWAITING_REVIEW", "outer report CLI has not completed")
    require(state.get("exit_code") == 0, "outer report CLI failed")
    require(state["run_id"] == EXPECTED_RUN and state["task_file"].endswith("report_cycle_task.md"), "wrong report execution identity")
    begin, finish = epoch(state["round_started_at"]), epoch(state["round_finished_at"])
    require(readiness["status"] == "READY_FOR_REVIEW" and readiness["root_acceptance"] is False, "not an unaccepted producer-ready record")
    require(begin <= epoch(commands["started_utc"]) <= epoch(commands["completed_utc"]) <= epoch(manifest["created_utc"]) <= epoch(readiness["completed_checks_utc"]) <= finish + 1, "stale or cross-round final evidence")
    require(manifest["root_acceptance"] is False and manifest["formal_acceptance"] == "EXTERNAL_PENDING", "producer granted unauthorized acceptance")
    return begin, finish


def boundary_tests():
    s = {"status": "AWAITING_REVIEW", "exit_code": 0, "run_id": EXPECTED_RUN, "task_file": "work/report_cycle_task.md", "round_started_at": "2026-10-15T16:50:00Z", "round_finished_at": "2026-10-15T18:00:00Z"}
    r = {"status": "READY_FOR_REVIEW", "root_acceptance": False, "completed_checks_utc": "2026-10-15T17:22:00Z"}
    m = {"created_utc": "2026-10-15T17:21:50Z", "root_acceptance": False, "formal_acceptance": "EXTERNAL_PENDING"}
    c = {"started_utc": "2026-10-15T17:21:00Z", "completed_utc": "2026-10-15T17:21:40Z"}
    boundary(s, r, m, c)
    trials = [(dict(s, status="RUNNING"), r, m, c), (dict(s, exit_code=1), r, m, c),
              (dict(s, run_id="wrong-run"), r, m, c), (s, dict(r, root_acceptance=True), m, c),
              (s, r, dict(m, created_utc="2026-10-15T15:00:00Z"), c),
              (s, r, dict(m, formal_acceptance="PASS"), c)]
    for values in trials:
        try:
            boundary(*values)
        except ValueError:
            continue
        raise AssertionError("invalid acceptance fixture was accepted")
    return len(trials)


def main():
    rejected = boundary_tests()
    state = load(ROOT / ".omx/prototype-run.json")
    readiness = load(ROOT / "work/report_cycle_status.json")
    manifest = load(OUT / "manifest.json")
    commands = load(OUT / "final-commands.json")
    begin, finish = boundary(state, readiness, manifest, commands)
    require((ROOT / "work/report_cycle_status.json").stat().st_mtime >= begin, "stale readiness filesystem timestamp")
    require(readiness["manifest_sha256"] == sha(OUT / "manifest.json"), "final manifest changed")
    require(manifest["report_count"] == readiness["report_count"] == 7 and manifest["document_count"] == 11, "incorrect report count")
    require(manifest["review_rounds"] == readiness["independent_review_rounds"] == 2, "missing independent rounds")
    require(readiness["formal_acceptance"] == "EXTERNAL_PENDING" and readiness["open_findings"] == {"P1": 0, "P2": 0, "P3": 0}, "open findings or formal scope error")
    fields = ["baseline_accepted", "requirements", *[f"report{i}" for i in range(1, 8)], "reproduce", "spec_review", "quality_review", "document_check"]
    require(all(readiness.get(key) is True for key in fields), "incomplete readiness fields")
    expected = [("report_cycle_evidence_check.py", ["--self-test"]), ("report_cycle_evidence_check.py", []),
                ("report_cycle_document_check.py", ["--self-test"]), ("report_cycle_document_check.py", [])]
    require(commands["status"] == "PASS" and len(commands["commands"]) == 4, "final command coverage incomplete")
    for entry, (name, extra) in zip(commands["commands"], expected):
        argv = entry["command"]
        require(Path(argv[1]).name == name and argv[2:] == extra and entry["exit_code"] == 0, "incorrect or failed final check")
        require(begin <= epoch(entry["started_utc"]) <= epoch(entry["completed_utc"]) <= finish + 1, "command is outside current round")
        require(sha(ROOT / entry["log"]) == entry["log_sha256"], "command log changed")
    require(manifest["generator_sha256"] == sha(ROOT / "work/report_cycle_finalize.py"), "finalizer source drift")
    require(manifest["bound_files"] == len(manifest["files_sha256"]) and len(manifest["files_sha256"]) >= 9365, "evidence inventory incomplete")
    for name, expected_hash in manifest["files_sha256"].items():
        require(sha(ROOT / name) == expected_hash, "manifest member changed " + name)
    # Run the reviewed verifier as an actual read-only subprocess after outer exit.
    argv = [sys.executable, "-X", "utf8", "-B", str(ROOT / "work/report_cycle_finalize.py"), "--verify-ready"]
    result = subprocess.run(argv, cwd=ROOT, text=True, encoding="utf-8", capture_output=True, timeout=300)
    log = OUT / "root-ready-verification.log"
    log.write_text(result.stdout + result.stderr, encoding="utf-8")
    require(result.returncode == 0 and "READY_VERIFIED" in result.stdout, "read-only ready verification failed")
    require(sha(OUT / "manifest.json") == readiness["manifest_sha256"], "manifest changed during root verification")
    # Freeze both mutable producer pointers before root annotates completion.
    snapshot_state = OUT / "root-accepted-runner.json"
    snapshot_ready = OUT / "root-accepted-producer-readiness.json"
    snapshot_state.write_bytes((ROOT / ".omx/prototype-run.json").read_bytes())
    snapshot_ready.write_bytes((ROOT / "work/report_cycle_status.json").read_bytes())
    root_evidence = [snapshot_state, snapshot_ready, OUT / "manifest.json", OUT / "final-commands.json", log,
                    OUT / "review-spec-all.json", OUT / "review-spec-delta.json", OUT / "review-quality-all.json",
                    OUT / "review-checkers.json", ROOT / "reports/system/root-formal-acceptance.json"]
    acceptance = {
        "status": "ACCEPTED_LOCAL_REPORT_BATCH", "root_acceptance": True,
        "checked_utc": datetime.now(timezone.utc).isoformat(), "run_id": EXPECTED_RUN,
        "round": state["round"], "round_started_utc": state["round_started_at"], "round_finished_utc": state["round_finished_at"],
        "outer_cli_exit_code": state["exit_code"], "negative_boundary_fixtures_rejected": rejected,
        "documents": 11, "technical_reports": 7, "independent_review_rounds": 2,
        "bound_files_rechecked": len(manifest["files_sha256"]), "actual_final_checks": 4,
        "post_exit_readonly_verification_command": argv, "post_exit_readonly_verification_exit_code": result.returncode,
        "manifest_sha256": sha(OUT / "manifest.json"), "acceptor_sha256": sha(Path(__file__)),
        "evidence_sha256": {p.relative_to(ROOT).as_posix(): sha(p) for p in root_evidence},
        "open_findings": {"P1": 0, "P2": 0, "P3": 0}, "formal_acceptance": "EXTERNAL_PENDING",
        "scope": "Approved A local technical reports and accepted local hardware evidence only; no formal contest/PPA/600/official12 acceptance",
        "no_hardware_simulation_synthesis_search_started": True,
    }
    (OUT / "root-acceptance.json").write_text(json.dumps(acceptance, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("ROOT_REPORT_BATCH_ACCEPTED reports=7 documents=11 files=" + str(len(manifest["files_sha256"])))


if __name__ == "__main__":
    main()
