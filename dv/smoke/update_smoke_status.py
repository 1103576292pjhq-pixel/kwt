"""Stdlib-only shell status gate, including missing-venv/import failures."""
import json
import sys
from datetime import datetime, timezone
from pathlib import Path


WORKSPACE = Path(__file__).resolve().parents[2]
REPORT_DIR = WORKSPACE / "reports" / "environment"
STATUS_FILE = REPORT_DIR / "smoke-result.json"
ENV_FILE = REPORT_DIR / "environment.json"
REPORT_DIR.mkdir(parents=True, exist_ok=True)
mode = sys.argv[1]
if mode == "begin":
    status = {"status": "running", "started_at_utc": datetime.now(timezone.utc).isoformat()}
elif mode == "finalize":
    exit_code = int(sys.argv[2])
    status = json.loads(STATUS_FILE.read_text(encoding="utf-8")) if STATUS_FILE.exists() else {}
    if exit_code != 0:
        status.update(status="failed", exit_code=exit_code)
    elif status.get("status") != "passed":
        raise RuntimeError("Exit 0 without a verified passed smoke result")
    status["shell_exit_code"] = exit_code
    status["shell_completed_at_utc"] = datetime.now(timezone.utc).isoformat()
else:
    raise ValueError(f"Unknown mode: {mode}")
STATUS_FILE.write_text(json.dumps(status, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
if ENV_FILE.exists():
    environment = json.loads(ENV_FILE.read_text(encoding="utf-8"))
    environment["smoke"] = status
    ENV_FILE.write_text(json.dumps(environment, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
