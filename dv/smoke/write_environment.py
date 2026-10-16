"""Record observed tools and smoke evidence, without inferring unrun checks."""
from __future__ import annotations

import importlib.metadata
import json
import platform
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path


WORKSPACE = Path(__file__).resolve().parents[2]
REPORT_DIR = WORKSPACE / "reports" / "environment"


def inspect_tool(binary: str, args: list[str]) -> dict:
    path = Path(binary)
    if not path.is_file():
        return {"installed": False, "path": binary, "version": None}
    result = subprocess.run([binary, *args], capture_output=True, text=True, timeout=20)
    output = (result.stdout + result.stderr).strip()
    first_line = output.splitlines()[0] if output else None
    return {"installed": True, "path": binary, "version": first_line, "version_exit_code": result.returncode}


def main() -> None:
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    smoke_path = REPORT_DIR / "smoke-result.json"
    smoke = json.loads(smoke_path.read_text(encoding="utf-8")) if smoke_path.exists() else {"status": "not_run"}
    report = {
        "schema_version": 1,
        "recorded_at_utc": datetime.now(timezone.utc).isoformat(),
        "workspace_linux": str(WORKSPACE),
        "execution_platform": "WSL2/Linux",
        "kernel": platform.release(),
        "os_release": platform.freedesktop_os_release(),
        "python": {"version": platform.python_version(), "executable": sys.executable, "isolated_venv": sys.prefix != sys.base_prefix},
        "python_packages": {name: importlib.metadata.version(name) for name in ("cocotb", "pytest", "numpy")},
        "system_packages": {
            name: subprocess.run(["/usr/bin/dpkg-query", "-W", "-f=${Version}", name], capture_output=True, text=True, check=True).stdout
            for name in ("iverilog", "gtkwave", "verilator", "python3-venv", "python3.12")
        },
        "tools": {
            "iverilog": inspect_tool("/usr/bin/iverilog", ["-V"]),
            "vvp": inspect_tool("/usr/bin/vvp", ["-V"]),
            "gtkwave": inspect_tool("/usr/bin/gtkwave", ["--version"]),
            "verilator": inspect_tool("/usr/bin/verilator", ["--version"]),
        },
        "primary_simulator": "icarus",
        "smoke": smoke,
        "observed_diagnostics": (
            ["cocotb GPI startup printed 'Log message construction failed: (error code) -1'; simulation continued successfully"]
            if (REPORT_DIR / "smoke.log").exists() and "Log message construction failed" in (REPORT_DIR / "smoke.log").read_text(encoding="utf-8")
            else []
        ),
        "not_run": ["GTKWave GUI interactive viewing", "Verilator cocotb simulation", "accelerator RTL", "synthesis", "PPA"],
        "dependency_lock": "config/requirements-dv.txt",
        "pip_freeze": "reports/environment/pip-freeze.txt",
        "portability_check": "reports/environment/path-portability.json",
    }
    destination = REPORT_DIR / "environment.json"
    destination.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(f"Environment report: {destination}")


if __name__ == "__main__":
    main()
