"""Publish only the independent narrow review after its own evidence passes."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
OWN = Path(__file__).resolve().parent
OUT = OWN.parent

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

tests = json.loads((OWN / "independent-checker-tests.json").read_text(encoding="utf-8"))
readback = json.loads((OWN / "actual-readonly-readback.json").read_text(encoding="utf-8"))
assert tests["status"] == readback["status"] == "PASS"
assert len(tests["tests"]) == 41 and all(item["passed"] for item in tests["tests"])
assert tests["files"] == readback["files"]
assert {name: sha(ROOT / name) for name in tests["files"]} == tests["files"]
prose = OUT / "review-checkers.md"
prose_text = prose.read_bytes().decode("utf-8", errors="strict")
assert "\ufffd" not in prose_text and "结论：PASS" in prose_text

names = [
    "independent_checker_tests.py", "independent-checker-tests.json", "initial-defects.json",
    "actual_readonly_readback.py", "actual-evidence-readback.json", "actual-readonly-readback.json",
    "report_cycle_document_check.py.selftest.log", "report_cycle_evidence_check.py.selftest.log",
    "report_cycle_finalize.py.selftest.log", "missing-file-directory.log", "verify-empty.log",
    "verify-ready-positive-cli.log", "write_review.py",
    "fixtures/cli-selftests/reports/system/report-cycle/document-self-test.json",
    "fixtures/cli-selftests/reports/system/report-cycle/evidence-self-test.json",
    "fixtures/cli-selftests/reports/system/report-cycle/finalizer-self-test.json",
]
artifacts = {(OWN / name).relative_to(ROOT).as_posix(): sha(OWN / name) for name in names}
closed = [
    dict(id="CK2-01", severity="P2", state="CLOSED", issue="READY verifier accepted an extra twelfth unreviewed document", closure="Exact directory check added; isolated extra-document fixture now rejected", evidence="reports/system/report-cycle/checker-review/independent-checker-tests.json", test="verify-ready-reject-extra-unreviewed-document"),
    dict(id="CK3-01", severity="P3", state="CLOSED", issue="Required document represented by a directory yielded mechanical PASS with ten documents", closure="Expected regular-file inventory added; original directory fixture now exits nonzero", evidence="reports/system/report-cycle/checker-review/independent-checker-tests.json", test="document-checker-rejects-required-document-directory"),
    dict(id="CK3-02", severity="P3", state="CLOSED", issue="Read-only CLI failure path created the absent output directory", closure="Directory creation moved into write branches; empty fixture rejects without creating output and valid CLI is unchanged", evidence="reports/system/report-cycle/checker-review/independent-checker-tests.json", test="verify-ready-failure-does-not-create-output-directories"),
]
result = dict(status="PASS", reviewer="cycle_checker_review", scope="Independent narrow checker/finalizer review only; does not replace either document-content review round", files=tests["files"], open_findings=dict(P1=0, P2=0, P3=0), closed_findings=closed, review_file=prose.relative_to(ROOT).as_posix(), review_sha256=sha(prose), artifacts_sha256=artifacts, test_summary=dict(independent_checks=41, all_passed=True, checker_selftest_negative_counts=dict(document=14, evidence=10, finalizer=13), actual_evidence_bound_files=788, quality_actual_input_files=9365, frozen_files_verified_unchanged=192, formal_finalize_executed=False, production_or_simulation_commands_executed=0, root_acceptance_granted=False, verify_ready_fixture_real_cli_exit_code=0), boundary="The root must run read-only --verify-ready after actual finalization and observe the true outer CLI exit0; root_acceptance remains false and formal_acceptance remains EXTERNAL_PENDING", completed_utc=datetime.now(timezone.utc).isoformat())
target = OUT / "review-checkers.json"
target.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
reloaded = json.loads(target.read_bytes().decode("utf-8", errors="strict"))
assert reloaded == result and sha(prose) == result["review_sha256"]
assert all(sha(ROOT / name) == expected for name, expected in reloaded["artifacts_sha256"].items())
print(json.dumps(dict(status=result["status"], files=result["files"], artifacts=len(artifacts), closed_findings=len(closed), open_findings=result["open_findings"], review_sha256=result["review_sha256"], completed_utc=result["completed_utc"])))
