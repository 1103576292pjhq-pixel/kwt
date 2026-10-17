"""Run SOFTWARE checks only. Does not invoke a simulator or modify a repo."""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import hashlib
import io
import json
from pathlib import Path
import platform
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tests"))
import test_design
import test_revd


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--out", type=Path, help="New result directory, never overwritten")
    args = p.parse_args()
    if args.out:
        try:
            args.out.mkdir(parents=True, exist_ok=False)
        except OSError as exc:
            p.error(str(exc))
    start = datetime.now(timezone.utc).isoformat()
    suite = unittest.TestSuite([unittest.defaultTestLoader.loadTestsFromModule(test_design), unittest.defaultTestLoader.loadTestsFromModule(test_revd)])
    log = io.StringIO()
    result = unittest.TextTestRunner(stream=log, verbosity=2).run(suite)
    print(log.getvalue())
    sources = {str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest()
               for folder in ("tools", "tests") for path in sorted((ROOT / folder).glob("*.py"))}
    report = dict(status="SOFTWARE_CHECK_PASS" if result.wasSuccessful() and not result.skipped else "SOFTWARE_CHECK_FAIL",
                  scope="Synthetic arithmetic/address/ownership specification checks; NO new RTL/CPU/PPA",
                  python=platform.python_version(), started_utc=start,
                  finished_utc=datetime.now(timezone.utc).isoformat(),
                  test_methods=result.testsRun, failures=len(result.failures),
                  errors=len(result.errors), skipped=len(result.skipped),
                  counters={"inherited_design":test_design.COUNTS,"revd_review":test_revd.COUNTS}, source_sha256=sources,
                  not_run=["V0_FILE_EXECUTION", "OFFICIAL_MODEL_VECTORS", "NEW_RTL", "NEW_E203_SOC", "SYNTHESIS", "PPA"])
    print(json.dumps(report, ensure_ascii=False, indent=2))
    if args.out:
        (args.out / "self_check.log").write_text(log.getvalue(), encoding="utf-8")
        (args.out / "self_check.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return 0 if result.wasSuccessful() and not result.skipped else 1

if __name__ == "__main__":
    raise SystemExit(main())
