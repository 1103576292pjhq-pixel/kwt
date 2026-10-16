"""Validate a real space/Unicode workspace and a missing-venv failure in /tmp."""
import json
import os
import shutil
import subprocess
import tempfile
from pathlib import Path


WORKSPACE = Path(__file__).resolve().parents[2]
REPORT_DIR = WORKSPACE / "reports" / "environment"
with tempfile.TemporaryDirectory(prefix="kwt dv—路径-") as temporary:
    fixture = Path(temporary)
    (fixture / "scripts").mkdir()
    (fixture / "dv" / "smoke").mkdir(parents=True)
    for script in ("run_smoke.sh", "setup_dv.sh"):
        shutil.copy2(WORKSPACE / "scripts" / script, fixture / "scripts" / script)
    for source in (WORKSPACE / "dv" / "smoke").glob("*.py"):
        shutil.copy2(source, fixture / "dv" / "smoke" / source.name)
    shutil.copy2(WORKSPACE / "dv" / "smoke" / "counter.sv", fixture / "dv" / "smoke" / "counter.sv")
    (fixture / ".venv-dv").symlink_to(WORKSPACE / ".venv-dv", target_is_directory=True)
    environment = os.environ.copy()
    environment.update(WAVES="0", GUI="1", COCOTB_ANSI_OUTPUT="0")
    passed = subprocess.run(["/usr/bin/bash", str(fixture / "scripts" / "run_smoke.sh")], cwd="/tmp", env=environment,
                            capture_output=True, text=True, timeout=60)
    (REPORT_DIR / "path-portability.log").write_text(passed.stdout + passed.stderr, encoding="utf-8")
    if passed.returncode != 0:
        raise RuntimeError(f"Space/Unicode smoke failed: {passed.returncode}")
    status_path = fixture / "reports" / "environment" / "smoke-result.json"
    passed_status = json.loads(status_path.read_text(encoding="utf-8"))
    assert passed_status["status"] == "passed" and passed_status["waveform_vcd_bytes"] > 0

    # Remove only this test's symlink, leaving the real shared virtual environment intact.
    (fixture / ".venv-dv").unlink()
    environment["SMOKE_LOG_NAME"] = "missing-venv.log"
    failed = subprocess.run(["/usr/bin/bash", str(fixture / "scripts" / "run_smoke.sh")], cwd="/tmp", env=environment,
                            capture_output=True, text=True, timeout=60)
    (REPORT_DIR / "missing-venv.log").write_text(failed.stdout + failed.stderr, encoding="utf-8")
    failed_status = json.loads(status_path.read_text(encoding="utf-8"))
    failed_environment = json.loads((fixture / "reports" / "environment" / "environment.json").read_text(encoding="utf-8"))
    assert failed.returncode == 2 and failed_status["status"] == "failed"
    assert failed_environment["smoke"]["status"] == "failed", "A previous passed report must not survive startup failure"
    report = {
        "status": "passed", "tested_workspace": str(fixture), "caller_cwd": "/tmp",
        "space_unicode_smoke_exit_code": passed.returncode, "tests": passed_status["tests"],
        "external_WAVES_0_and_GUI_1_overridden": True,
        "missing_venv_exit_code": failed.returncode, "missing_venv_report": failed_status["status"],
        "temporary_fixture_removed_after_check": True,
    }
    (REPORT_DIR / "path-portability.json").write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps(report, ensure_ascii=False))
