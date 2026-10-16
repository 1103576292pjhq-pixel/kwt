"""Independent narrow gate review. Writes only this owned evidence subtree."""
import contextlib
import copy
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
from datetime import datetime, timezone

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[4]
OWN = Path(__file__).resolve().parent
WORK = ROOT / "work"
sys.path.insert(0, str(WORK))
import report_cycle_document_check as doc
import report_cycle_evidence_check as ev
import report_cycle_finalize as fin
SUBPROCESS_ENV = dict(os.environ, PYTHONIOENCODING="utf-8")

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

tests = []
def case(name, action, expect_reject=False):
    try:
        value = action()
    except (ValueError, KeyError, OSError, UnicodeError) as exc:
        tests.append(dict(name=name, passed=expect_reject, rejected=True, message=str(exc)))
    else:
        tests.append(dict(name=name, passed=not expect_reject, rejected=False, result=value))

start = {"work/" + p.name: digest(p) for p in (WORK / "report_cycle_document_check.py", WORK / "report_cycle_evidence_check.py", WORK / "report_cycle_finalize.py")}
selfroot = OWN / "fixtures" / "cli-selftests"
(selfroot / "work").mkdir(parents=True, exist_ok=True)
for filename in ("report_cycle_document_check.py", "report_cycle_evidence_check.py", "report_cycle_finalize.py"):
    dst = selfroot / "work" / filename
    shutil.copyfile(WORK / filename, dst)
    cp = subprocess.run([sys.executable, "-B", str(dst), "--self-test"], capture_output=True, text=True, encoding="utf-8", env=SUBPROCESS_ENV)
    (OWN / (filename + ".selftest.log")).write_text(cp.stdout + cp.stderr, encoding="utf-8")
    tests.append(dict(name=filename + " --self-test", passed=cp.returncode == 0, exit_code=cp.returncode))

current = {name: digest(ROOT / name) for name in fin.DOCS}
case("actual-current-eleven-review-overlay", lambda: len(fin.effective_reviews(current)))
first, delta, quality = fin.effective_reviews(current)
assert set(delta["supersedes_document_sha256"]) == {n for n in fin.DOCS if Path(n).name.startswith(("00_", "03_"))}
checker_fixture = dict(reviewer="cycle_checker_review_fixture", closed_findings=[dict(id="CHECKER-FIXTURE", state="CLOSED")])
closure = fin.findings_closure(first, delta, quality, checker_fixture)
assert set(f["id"] for f in closure["closed_findings"]) == set(f["id"] for r in (first, quality, checker_fixture) for f in r["closed_findings"])
assert closure["spec_delta_checks"] == delta["delta_checks"]
tests.append(dict(name="actual-closure-preserves-all-ten-closed-findings-and-six-delta-checks", passed=True, closed=len(closure["closed_findings"]), delta=len(closure["spec_delta_checks"])))

fixture = OWN / "fixtures" / ("reviews-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%f"))
fixture_out = fixture / "reports/system/report-cycle"
fixture_out.mkdir(parents=True, exist_ok=True)
for prefix in ("review-spec-all", "review-spec-delta", "review-quality-all"):
    for ext in (".md", ".json"):
        shutil.copyfile(ROOT / "reports/system/report-cycle" / (prefix + ext), fixture_out / (prefix + ext))
for name in fin.DOCS:
    dst = fixture / name
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(ROOT / name, dst)
for filename in ("report_cycle_document_check.py", "report_cycle_evidence_check.py", "report_cycle_finalize.py"):
    dst = fixture / "work" / filename
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(WORK / filename, dst)
fin.ROOT, fin.OUT = fixture, fixture_out
case("isolated-valid-review-overlay", lambda: len(fin.effective_reviews(current)))

def changed_review(filename, mutate, call=None):
    path = fixture_out / filename
    raw = path.read_bytes()
    payload = json.loads(raw)
    mutate(payload)
    write(path, payload)
    try:
        return (call or (lambda: fin.effective_reviews(current)))()
    finally:
        path.write_bytes(raw)

case("reject-quality-hash-drift", lambda: changed_review("review-quality-all.json", lambda r: r["documents"].__setitem__(fin.DOCS[1], "0"*64)), True)
case("reject-missing-first-snapshot", lambda: changed_review("review-spec-all.json", lambda r: r["snapshots"].pop()), True)
case("reject-wrong-delta-predecessor", lambda: changed_review("review-spec-delta.json", lambda r: r["supersedes_document_sha256"].__setitem__(next(iter(r["supersedes_document_sha256"])), "0"*64)), True)
case("reject-delta-silent-third-document-change", lambda: changed_review("review-spec-delta.json", lambda r: r["documents"].__setitem__(fin.DOCS[1], "0"*64)), True)
case("reject-missing-delta-unchanged-entry", lambda: changed_review("review-spec-delta.json", lambda r: r["unchanged_documents"].pop(next(iter(r["unchanged_documents"])))), True)
case("reject-review-prose-hash-drift", lambda: changed_review("review-quality-all.json", lambda r: r.__setitem__("review_sha256", "0"*64)), True)
case("reject-same-reviewer-both-rounds", lambda: changed_review("review-quality-all.json", lambda r: r.__setitem__("reviewer", first["reviewer"])), True)
for priority in ("P1", "P2", "P3"):
    case("reject-open-"+priority, lambda p=priority: changed_review("review-quality-all.json", lambda r: r["open_findings"].__setitem__(p, 1)), True)
case("reject-OPEN-finding-labelled-closed", lambda: fin.findings_closure(dict(first, closed_findings=[dict(id="OPEN", state="OPEN")]), delta, quality, checker_fixture), True)
case("reject-OPEN-delta-check", lambda: fin.findings_closure(first, dict(delta, delta_checks=[dict(id="OPEN", state="OPEN")]), quality, checker_fixture), True)
case("reject-OPEN-checker-finding", lambda: fin.findings_closure(first, delta, quality, dict(checker_fixture, closed_findings=[dict(id="OPEN", state="OPEN")])), True)
case("reject-unauthorized-root-acceptance", lambda: fin.validate_ready_state(dict(status="READY_FOR_REVIEW", root_acceptance=True, formal_acceptance="EXTERNAL_PENDING", report_count=7, **dict.fromkeys(fin.REQUIRED, True))), True)
case("reject-formal-PASS", lambda: fin.validate_ready_state(dict(status="READY_FOR_REVIEW", root_acceptance=False, formal_acceptance="PASS", report_count=7, **dict.fromkeys(fin.REQUIRED, True))), True)

# A minimal internally consistent READY fixture exercises the read-only verifier.
for name in ("document-check.json", "evidence-check.json"):
    write(fixture_out / name, dict(status="PASS"))
mapping = {p.relative_to(fixture).as_posix(): digest(p) for p in fixture.rglob("*") if p.is_file()}
write(fixture_out / "manifest.json", dict(status="PASS", root_acceptance=False, files_sha256=mapping))
state = dict(status="READY_FOR_REVIEW", root_acceptance=False, formal_acceptance="EXTERNAL_PENDING", report_count=7, **dict.fromkeys(fin.REQUIRED, True))
state.update(manifest_sha256=digest(fixture_out / "manifest.json"), document_check_sha256=digest(fixture_out / "document-check.json"), evidence_check_sha256=digest(fixture_out / "evidence-check.json"))
write(fixture / "work/report_cycle_status.json", state)
def verify():
    with contextlib.redirect_stdout(io.StringIO()) as output:
        fin.verify_ready()
    return output.getvalue().strip()
before = {p.relative_to(fixture).as_posix(): digest(p) for p in fixture.rglob("*") if p.is_file()}
case("verify-ready-positive-fixture", verify)
after = {p.relative_to(fixture).as_posix(): digest(p) for p in fixture.rglob("*") if p.is_file()}
tests.append(dict(name="verify-ready-does-not-alter-existing-fixture", passed=before == after))
cp = subprocess.run([sys.executable, "-B", str(fixture / "work/report_cycle_finalize.py"), "--verify-ready"], capture_output=True, text=True, encoding="utf-8", env=SUBPROCESS_ENV)
(OWN / "verify-ready-positive-cli.log").write_text(cp.stdout + cp.stderr, encoding="utf-8")
after_cli = {p.relative_to(fixture).as_posix(): digest(p) for p in fixture.rglob("*") if p.is_file()}
tests.append(dict(name="verify-ready-positive-CLI-exit0-and-no-writes", passed=cp.returncode == 0 and before == after_cli, exit_code=cp.returncode, stdout=cp.stdout.strip()))
docpath = fixture / fin.DOCS[1]
original_doc = docpath.read_bytes()
docpath.write_bytes(original_doc + b"\nChanged\n")
case("verify-ready-reject-changed-manifest-member", verify, True)
docpath.write_bytes(original_doc)
docpath.unlink()
case("verify-ready-reject-missing-manifest-member", verify, True)
docpath.write_bytes(original_doc)
(fixture / "broken-link-target.md").write_text("# Test\n[missing](absent-file.md)\n", encoding="utf-8")
tests.append(dict(name="independent-broken-local-link-rejected", passed=bool(doc.scan(fixture / "broken-link-target.md")["errors"])))
(fixture / "broken-link-target.md").unlink()
(fixture / "docs/encoder/reports/unreviewed.md").write_text("# Unreviewed extra\n", encoding="utf-8")
case("verify-ready-reject-extra-unreviewed-document", verify, True)

# The document checker alone must classify a directory as missing a required file.
fake = OWN / "fixtures" / "missing-file-directory"
(fake / "work").mkdir(parents=True, exist_ok=True)
shutil.copyfile(WORK / "report_cycle_document_check.py", fake / "work/report_cycle_document_check.py")
for name in doc.NAMES:
    dst = fake / "docs/encoder/reports" / name
    dst.parent.mkdir(parents=True, exist_ok=True)
    if name == "README.md":
        dst.mkdir(exist_ok=True)
    else:
        dst.write_text("# Title\n" + "body text " * 500, encoding="utf-8")
cp = subprocess.run([sys.executable, "-B", str(fake / "work/report_cycle_document_check.py")], capture_output=True, text=True, encoding="utf-8", env=SUBPROCESS_ENV)
(OWN / "missing-file-directory.log").write_text(cp.stdout + cp.stderr, encoding="utf-8")
tests.append(dict(name="document-checker-rejects-required-document-directory", passed=cp.returncode != 0, exit_code=cp.returncode, stdout=cp.stdout.strip()))

empty = OWN / "fixtures" / ("verify-empty-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%f"))
(empty / "work").mkdir(parents=True, exist_ok=True)
for filename in ("report_cycle_document_check.py", "report_cycle_evidence_check.py", "report_cycle_finalize.py"):
    shutil.copyfile(WORK / filename, empty / "work" / filename)
cp = subprocess.run([sys.executable, "-B", str(empty / "work/report_cycle_finalize.py"), "--verify-ready"], capture_output=True, text=True, encoding="utf-8", env=SUBPROCESS_ENV)
(OWN / "verify-empty.log").write_text(cp.stdout + cp.stderr, encoding="utf-8")
tests.append(dict(name="verify-ready-failure-does-not-create-output-directories", passed=cp.returncode != 0 and not (empty / "reports").exists(), exit_code=cp.returncode, created_output_directory=(empty / "reports").exists()))

fin.ROOT, fin.OUT = ROOT, ROOT / "reports/system/report-cycle"
def actual_scan(name):
    found = doc.scan(ROOT / "docs/encoder/reports" / name)["errors"]
    if found:
        raise ValueError(str(found))
    return "PASS"
for name in doc.NAMES:
    case("actual-mechanical-scan:" + name, lambda n=name: actual_scan(n))
result = dict(status="PASS" if all(t["passed"] for t in tests) else "FINDINGS", reviewer="cycle_checker_review", completed_utc=datetime.now(timezone.utc).isoformat(), files=start, tests=tests)
write(OWN / "independent-checker-tests.json", result)
print(json.dumps(dict(status=result["status"], cases=len(tests), failures=[t for t in tests if not t["passed"]]), ensure_ascii=False))
