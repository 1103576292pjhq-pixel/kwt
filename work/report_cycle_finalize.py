"""Generate report readiness from checked artifacts; never grant root acceptance."""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

from report_cycle_document_check import NAMES, document_set_errors
from report_cycle_evidence_check import check_map, load, require, sha

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "reports/system/report-cycle"
REQUIRED = ["baseline_accepted", "requirements", *[f"report{i}" for i in range(1, 8)],
            "reproduce", "spec_review", "quality_review", "document_check"]
DOCS = ["docs/encoder/reports/" + name for name in NAMES]


def now():
    return datetime.now(timezone.utc).isoformat()


def write_json(path, value):
    # Atomic publication keeps a consumer from observing a half-written JSON file.
    temp = path.with_name(path.name + ".tmp")
    temp.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    temp.replace(path)


def review_header(review, round_number):
    require(review.get("status") == "PASS" and review.get("round") == round_number, "review not complete/PASS")
    require(isinstance(review.get("reviewer"), str) and bool(review["reviewer"]), "review identity missing")
    counts = review.get("open_findings", {})
    require(all(key in counts and counts[key] == 0 for key in ["P1", "P2", "P3"]), "open or unreported review findings")


def validate_document_maps(current, spec, quality):
    require(set(current) == set(DOCS), "incomplete document set")
    require(current == spec, "first-round review stale/incomplete")
    require(current == quality, "second-round review stale/incomplete")


def check_review_file(review):
    path = ROOT / review["review_file"]
    require(path.is_file() and sha(path) == review["review_sha256"], "review prose hash mismatch")


def effective_reviews(current):
    first = load(OUT / "review-spec-all.json")
    delta = load(OUT / "review-spec-delta.json")
    quality = load(OUT / "review-quality-all.json")
    for review, round_number in [(first, 1), (delta, 1), (quality, 2)]:
        review_header(review, round_number)
        check_review_file(review)
    require(first["reviewer"] != quality["reviewer"] and delta["reviewer"] != quality["reviewer"], "reviews are not independent")
    require(first["document_count"] == quality["document_count"] == 11, "review coverage incomplete")
    require(delta["prior_review_json_sha256"] == sha(OUT / "review-spec-all.json"), "delta bound to wrong first round")
    require(delta["prior_review_sha256"] == first["review_sha256"], "delta prior prose drift")
    spec = {r["path"]: r["sha256_after"] for r in first["snapshots"] if r["accepted"] and r["reviewed"]}
    require(set(spec) == set(DOCS), "first-round snapshot coverage incomplete")
    changed = delta["supersedes_document_sha256"]
    for name, previous in changed.items():
        require(name in spec and spec[name] == previous, "invalid delta predecessor")
        spec[name] = delta["documents"][name]
    require(spec == delta["documents"], "delta silently changed unreviewed documents")
    require(set(delta["unchanged_documents"]) == set(DOCS) - set(changed), "delta unchanged scope incomplete")
    validate_document_maps(current, spec, quality["documents"])
    return first, delta, quality


def requirements_audit():
    import fitz

    source = load(ROOT / "work/report_cycle_sources/manifest.json")
    original = Path(source["pdf_path"])
    require(sha(original) == source["pdf_sha256"], "original PDF changed")
    require(sha(ROOT / source["workspace_pdf_copy"]) == source["pdf_sha256"], "PDF copy changed")
    require(sha(ROOT / source["text_path"]) == source["text_sha256"], "PDF text changed")
    guide = (ROOT / source["text_path"]).read_text(encoding="utf-8")
    compact = re.sub(r"\s+", "", guide)
    pages = []
    with fitz.open(original) as pdf:
        require(len(pdf) == 15, "wrong PDF page count")
        for physical in range(1, 16):
            text = pdf[physical - 1].get_text()
            # The existing source extraction intentionally omits the title cover.
            if physical > 1:
                require(re.sub(r"\s+", "", text) in compact, "source extraction omits page " + str(physical))
            pages.append({"physical_page": physical, "printed_page": physical - 1,
                          "text_sha256": hashlib.sha256(text.encode("utf-8")).hexdigest(),
                          "characters": len(text), "extracted_body_matched": physical > 1})
    matrix_path = ROOT / "docs/encoder/reports/00_赛题要求与验收对应表.md"
    matrix = matrix_path.read_text(encoding="utf-8")
    clauses = []
    for task in range(1, 8):
        for part in [1, 2]:
            marker = f"| {task}({part})，页"
            matches = [(n, line) for n, line in enumerate(matrix.splitlines(), 1) if line.startswith(marker)]
            require(len(matches) == 1 and "](" in matches[0][1], "missing task clause or evidence " + marker)
            clauses.append({"task": task, "part": part, "matrix_line": matches[0][0], "row": matches[0][1]})
    topics = {
        "platform_and_sram": ["512", "16bit", "150MHz", "2.25", "E203"],
        "model_and_input": ["237e4097", "batch=1", "PostNorm", "99×64", "best_weights"],
        "data_and_configuration": ["600", "训练集标定", "测试集不调", "数值配置"],
        "accuracy_and_bittruth": ["NRMSE", "3%", "2个百分点", "逐位一致", "有限"],
        "official_timing_and_power": ["正式12任务", "缓存", "SAIF", "VCD", "静态", "任务数"],
        "scoring_qualification": ["全部必做", "全部必测", "准入", "合格设计", "T/T_{", "E_{", "A_{"],
        "submission_and_provenance": ["初赛/决赛", "SDC", "来源", "自主设计", "预存", "冻结版本"],
    }
    for topic, tokens in topics.items():
        require(all(token in matrix for token in tokens), "missing requirements topic: " + topic)
    return {"status": "PASS", "checked_utc": now(), "matrix_sha256": sha(matrix_path),
            "pdf_sha256": source["pdf_sha256"], "source_manifest_sha256": sha(ROOT / "work/report_cycle_sources/manifest.json"),
            "source_text_sha256": source["text_sha256"], "pages": pages, "task_clauses": clauses,
            "task_clause_count": len(clauses), "common_topics": topics,
            "scope": "PDF extraction and explicit coverage index; semantic correctness separately accepted by both independent reviews",
            "visual_spotcheck": {"physical_pages": [4, 8, 11, 12],
                                  "method": "Rendered from original PDF and viewed by executor using view_image before this finalizer"},
            "formal_acceptance": "EXTERNAL_PENDING"}


def run_check(script, extra, log_name):
    command = [sys.executable, str(ROOT / "work" / script), *extra]
    started = now()
    process = subprocess.run(command, cwd=ROOT, capture_output=True, encoding="utf-8", errors="strict")
    (OUT / log_name).write_text(process.stdout + process.stderr, encoding="utf-8")
    record = {"command": command, "started_utc": started, "completed_utc": now(), "exit_code": process.returncode,
              "log": "reports/system/report-cycle/" + log_name, "log_sha256": sha(OUT / log_name)}
    require(process.returncode == 0, "check failed: " + script + " (see " + log_name + ")")
    return record


def findings_closure(first, delta, quality, checker_review):
    closed = {}
    for review in [first, quality, checker_review]:
        for finding in review.get("closed_findings", []):
            require(finding.get("state", finding.get("status")) == "CLOSED", "finding not independently closed")
            closed[finding["id"]] = {**finding, "confirmed_by": review["reviewer"]}
    require(all(r["state"] in ["CLOSED", "PASS"] for r in delta["delta_checks"]), "delta not closed")
    return {"status": "PASS", "checked_utc": now(), "open_findings": {"P1": 0, "P2": 0, "P3": 0},
            "closed_findings": list(closed.values()), "spec_delta_checks": delta["delta_checks"],
            "history_preserved": ["review-spec-01-05", "review-spec-all", "review-spec-delta"],
            "note": "Original reports retained; closure consumes actual independent review records"}


def validate_ready_state(state):
    require(state.get("status") == "READY_FOR_REVIEW", "report not ready")
    require(all(state.get(k) is True for k in REQUIRED), "missing readiness proof")
    require(state.get("report_count") == 7 and state.get("root_acceptance") is False, "incorrect count/unauthorized acceptance")
    require(state.get("formal_acceptance") == "EXTERNAL_PENDING", "formal acceptance misrepresented")


def verify_ready():
    require(not document_set_errors(ROOT / "docs/encoder/reports", NAMES), "report directory missing/extra/non-file entry")
    state = load(ROOT / "work/report_cycle_status.json")
    validate_ready_state(state)
    require(sha(OUT / "manifest.json") == state["manifest_sha256"], "manifest changed")
    manifest = load(OUT / "manifest.json")
    require(manifest["status"] == "PASS" and manifest["root_acceptance"] is False, "invalid report manifest")
    check_map(ROOT, manifest["files_sha256"])
    current = {name: sha(ROOT / name) for name in DOCS}
    effective_reviews(current)
    require(state["document_check_sha256"] == sha(OUT / "document-check.json"), "document check changed")
    require(state["evidence_check_sha256"] == sha(OUT / "evidence-check.json"), "evidence check changed")
    print("READY_VERIFIED files=" + str(len(manifest["files_sha256"])) + " documents=11 reports=7 root_acceptance=false")


def finalize():
    started = now()
    state_path = ROOT / "work/report_cycle_status.json"
    previous = load(state_path)
    require(datetime.now(timezone.utc) < datetime.fromisoformat(previous["checkpoint_utc"].replace("Z", "+00:00")), "approved budget checkpoint reached")
    current = {name: sha(ROOT / name) for name in DOCS}
    first, delta, quality = effective_reviews(current)
    checker_review = load(OUT / "review-checkers.json")
    require(checker_review["status"] == "PASS" and all(checker_review["open_findings"].get(p) == 0 for p in ["P1", "P2", "P3"]), "checker review incomplete")
    expected_checkers = {"work/" + name: sha(ROOT / "work" / name) for name in
                         ["report_cycle_document_check.py", "report_cycle_evidence_check.py", "report_cycle_finalize.py"]}
    require(checker_review["files"] == expected_checkers, "checker review stale/incomplete")
    check_review_file(checker_review)
    quality_inventory = "reports/system/report-cycle/quality-readback/evidence-inputs.json"
    require(quality_inventory in quality["artifacts_sha256"] and
            sha(ROOT / quality_inventory) == quality["artifacts_sha256"][quality_inventory], "quality input inventory missing/stale")
    quality_inputs = load(ROOT / quality_inventory)
    check_map(ROOT, quality_inputs)
    commands = [run_check("report_cycle_evidence_check.py", ["--self-test"], "final-evidence-self-test.log"),
                run_check("report_cycle_evidence_check.py", [], "final-evidence-check.log"),
                run_check("report_cycle_document_check.py", ["--self-test"], "final-document-self-test.log")]
    evidence = load(OUT / "evidence-check.json")
    require(evidence["status"] == "PASS" and evidence["baseline_accepted"] is True, "evidence not accepted")
    evidence_self = load(OUT / "evidence-self-test.json")
    document_self = load(OUT / "document-self-test.json")
    require(evidence_self["status"] == document_self["status"] == "PASS", "negative tests incomplete")
    require(evidence_self["checker_sha256"] == sha(ROOT / "work/report_cycle_evidence_check.py"), "evidence tests stale")
    require(document_self["checker_sha256"] == sha(ROOT / "work/report_cycle_document_check.py"), "document tests stale")
    require(evidence["checker_sha256"] == evidence_self["checker_sha256"], "evidence check stale")
    coverage = requirements_audit()
    closure = findings_closure(first, delta, quality, checker_review)
    write_json(OUT / "requirements-coverage.json", coverage)
    write_json(OUT / "issue-closure.json", closure)
    # This is the last check command. No document edit follows it.
    commands.append(run_check("report_cycle_document_check.py", [], "final-document-check.log"))
    document = load(OUT / "document-check.json")
    require(document["status"] == "PASS" and document["documents_checked"] == 11 and not document["errors"], "document check incomplete")
    require(document["checker_sha256"] == document_self["checker_sha256"], "document result stale")
    require({"docs/encoder/reports/" + k: v["sha256"] for k, v in document["documents"].items()} == current, "document drift after review")
    write_json(OUT / "final-commands.json", {"status": "PASS", "started_utc": started, "completed_utc": now(), "commands": commands})
    paths = list(current) + [
        "work/report_cycle_plan.md", "work/report_cycle_task.md", "work/report_cycle_authors.json", "work/report_cycle_launch.json",
        "work/report_cycle_document_check.py", "work/report_cycle_evidence_check.py", "work/report_cycle_finalize.py",
        "work/report_cycle_sources/manifest.json", "work/report_cycle_sources/guide-text.txt", "work/report_cycle_sources/2026赛题指南.pdf",
    ]
    for filename in ["review-spec-01-05.md", "review-spec-01-05.json", "review-spec-all.md", "review-spec-all.json",
                     "review-spec-delta.md", "review-spec-delta.json", "review-quality-all.md", "review-quality-all.json",
                     "evidence-check.json", "evidence-self-test.json", "document-check.json", "document-self-test.json",
                     "finalizer-self-test.json", "review-checkers.md", "review-checkers.json",
                     "requirements-coverage.json", "issue-closure.json", "final-commands.json"]:
        paths.append("reports/system/report-cycle/" + filename)
    paths.extend(command["log"] for command in commands)
    # Include every static file used by the quality reviewer, including its actual
    # readback script, stdout, inputs and output bindings when supplied in its JSON.
    for review in [quality, checker_review]:
        for key in ["artifacts_sha256", "review_evidence_sha256"]:
            if key in review:
                check_map(ROOT, review[key])
                paths.extend(review[key])
    files = dict(quality_inputs)
    files.update(evidence["artifacts_sha256"])
    files.update({name: sha(ROOT / name) for name in paths})
    check_map(ROOT, files)
    manifest = {"status": "PASS", "created_utc": now(), "generator_sha256": sha(Path(__file__)),
                "document_count": 11, "report_count": 7, "review_rounds": 2,
                "baseline_acceptance": "reports/system/root-formal-acceptance.json", "baseline_accepted": True,
                "unified_run_id": evidence["unified_run_id"], "files_sha256": files, "bound_files": len(files),
                "root_acceptance": False, "formal_acceptance": "EXTERNAL_PENDING",
                "boundary": "Immutable inputs/checks only. Mutable readiness and outer runner are outputs, excluded to avoid circular hashes; root must independently check actual outer CLI exit0."}
    write_json(OUT / "manifest.json", manifest)
    derived = {
        "baseline_accepted": evidence["baseline_accepted"], "requirements": coverage["status"] == "PASS",
        "reproduce": current["docs/encoder/reports/09_复现与学习指南.md"] == quality["documents"]["docs/encoder/reports/09_复现与学习指南.md"],
        "spec_review": first["status"] == delta["status"] == "PASS", "quality_review": quality["status"] == "PASS",
        "document_check": document["status"] == "PASS",
    }
    for i in range(1, 8):
        name = next(name for name in DOCS if Path(name).name.startswith(f"0{i}_"))
        derived[f"report{i}"] = Path(name).name in document["documents"] and current[name] == quality["documents"][name]
    result = dict(previous, **derived)
    result.update(status="READY_FOR_REVIEW", report_count=sum(derived[f"report{i}"] for i in range(1, 8)),
                  stage="REPORT_BATCH_CHECKED_AWAITING_OUTER_EXIT_AND_ROOT_ACCEPTANCE", root_acceptance=False,
                  formal_acceptance="EXTERNAL_PENDING", persistent_execution="CODEX_CLI_VISIBLE_CMD_SERIAL",
                  active_reviewers=[], updated_utc=now(), completed_checks_utc=now(),
                  manifest="reports/system/report-cycle/manifest.json", manifest_sha256=sha(OUT / "manifest.json"),
                  document_check_sha256=sha(OUT / "document-check.json"), evidence_check_sha256=sha(OUT / "evidence-check.json"),
                  baseline_acceptance_sha256=sha(ROOT / "reports/system/root-formal-acceptance.json"),
                  independent_review_rounds=2, open_findings={"P1": 0, "P2": 0, "P3": 0},
                  report_execution_exit="PENDING_OUTER_RUNNER_OBSERVATION")
    validate_ready_state(result)
    write_json(state_path, result)
    print("READY_FOR_REVIEW reports=7 documents=11 independent_rounds=2 bound_files=" + str(len(files)) + " root_acceptance=false")


def self_test():
    rejected = []

    def reject(name, action):
        try:
            action()
        except ValueError:
            rejected.append(name)
        else:
            raise AssertionError("negative fixture accepted: " + name)

    review = {"status": "PASS", "round": 2, "reviewer": "independent", "open_findings": {"P1": 0, "P2": 0, "P3": 0}}
    review_header(review, 2)
    reject("review-in-progress", lambda: review_header(dict(review, status="RUNNING"), 2))
    reject("wrong-round", lambda: review_header(review, 1))
    for priority in ["P1", "P2", "P3"]:
        reject("open-" + priority, lambda p=priority: review_header(dict(review, open_findings={**review["open_findings"], p: 1}), 2))
    reject("missing-findings-counts", lambda: review_header(dict(review, open_findings={}), 2))
    docs = {name: "a" * 64 for name in DOCS}
    validate_document_maps(docs, docs, docs)
    reject("missing-report", lambda: validate_document_maps({k: v for k, v in docs.items() if k != DOCS[0]}, docs, docs))
    reject("stale-first-review", lambda: validate_document_maps(docs, {**docs, DOCS[0]: "b" * 64}, docs))
    reject("stale-quality-review", lambda: validate_document_maps(docs, docs, {**docs, DOCS[1]: "b" * 64}))
    ready = dict(status="READY_FOR_REVIEW", root_acceptance=False, formal_acceptance="EXTERNAL_PENDING", report_count=7, **dict.fromkeys(REQUIRED, True))
    validate_ready_state(ready)
    reject("false-proof", lambda: validate_ready_state(dict(ready, quality_review=False)))
    reject("self-root-acceptance", lambda: validate_ready_state(dict(ready, root_acceptance=True)))
    reject("formal-pass", lambda: validate_ready_state(dict(ready, formal_acceptance="PASS")))
    reject("wrong-report-count", lambda: validate_ready_state(dict(ready, report_count=6)))
    result = {"status": "PASS", "checked_utc": now(), "checker_sha256": sha(Path(__file__)),
              "negative_fixtures_rejected": len(rejected), "negative_cases": rejected}
    write_json(OUT / "finalizer-self-test.json", result)
    print("FINALIZER_SELF_TEST_PASS rejected=" + str(len(rejected)))


def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--self-test", action="store_true")
    group.add_argument("--verify-ready", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        OUT.mkdir(parents=True, exist_ok=True)
        self_test()
    elif args.verify_ready:
        verify_ready()
    else:
        OUT.mkdir(parents=True, exist_ok=True)
        own_tests = load(OUT / "finalizer-self-test.json")
        require(own_tests["status"] == "PASS" and own_tests["checker_sha256"] == sha(Path(__file__)), "finalizer negative tests stale/missing")
        finalize()


if __name__ == "__main__":
    main()
