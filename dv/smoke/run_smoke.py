"""Icarus-only cocotb entry point with explicit tools and checked evidence."""
from __future__ import annotations

import hashlib
import json
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
from datetime import datetime, timezone
from pathlib import Path

from cocotb_tools.runner import get_runner


WORKSPACE = Path(__file__).resolve().parents[2]
SMOKE_DIR = Path(__file__).resolve().parent
REPORT_DIR = WORKSPACE / "reports" / "environment"
BUILD_DIR = REPORT_DIR / "smoke-build"
RESULT_FILE = REPORT_DIR / "smoke-results.xml"
STATUS_FILE = REPORT_DIR / "smoke-result.json"


def main() -> None:
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    STATUS_FILE.write_text(json.dumps({"status": "running", "started_at_utc": datetime.now(timezone.utc).isoformat()}, indent=2) + "\n", encoding="utf-8")

    source = SMOKE_DIR / "counter.sv"
    try:
        if sys.prefix == sys.base_prefix:
            raise RuntimeError("Run with .venv-dv/bin/python; global Python is not supported.")
        # The runner searches PATH; provide the exact approved Linux tool directory.
        os.environ["PATH"] = "/usr/bin:/bin"
        os.environ["WAVES"] = "1"
        # cocotb 2.0's GUI=0 logging branch forces ANSI colors; removing GUI
        # also prevents an inherited GUI=1 from opening a viewer.
        os.environ.pop("GUI", None)
        os.environ["COCOTB_ANSI_OUTPUT"] = "0"
        for tool in ("iverilog", "vvp", "verilator", "fst2vcd"):
            if not Path("/usr/bin", tool).is_file():
                raise RuntimeError(f"Missing /usr/bin/{tool}; run bash scripts/setup_dv.sh first.")
        # Current evidence must come from this run, even when reusing a build directory.
        for artifact in (RESULT_FILE, BUILD_DIR / "counter.fst", REPORT_DIR / "smoke-counter.vcd"):
            artifact.unlink(missing_ok=True)
        print("Lint: /usr/bin/verilator --lint-only --Wall --top-module counter", flush=True)
        subprocess.run(["/usr/bin/verilator", "--lint-only", "--Wall", "--top-module", "counter", str(source)], check=True)
        runner = get_runner("icarus")
        runner.build(sources=[source], hdl_toplevel="counter", build_dir=BUILD_DIR,
                     timescale=("1ns", "1ps"), always=True, waves=True)
        # Icarus rejects non-ASCII bytes in $dumpfile names; use a relative ASCII
        # plusarg inside the build directory, while keeping Unicode workspace paths.
        runner.test(hdl_toplevel="counter", test_module="test_counter", test_dir=BUILD_DIR, build_dir=BUILD_DIR,
                    results_xml=RESULT_FILE, seed=20261014, waves=True, plusargs=["+dumpfile_path=counter.fst"],
                    extra_env={"PYTHONPATH": str(SMOKE_DIR)})
        tree = ET.parse(RESULT_FILE)
        cases = tree.findall(".//testcase")
        failures = tree.findall(".//failure") + tree.findall(".//error")
        if not cases or failures:
            raise RuntimeError(f"Smoke XML validation failed: testcases={len(cases)}, failures={len(failures)}")

        # cocotb 2.x Icarus runner emits FST; generate a plain VCD for inspection.
        fst_path = BUILD_DIR / "counter.fst"
        vcd_path = REPORT_DIR / "smoke-counter.vcd"
        if not fst_path.is_file() or fst_path.stat().st_size == 0:
            raise RuntimeError(f"No waveform generated: {fst_path}")
        subprocess.run(["/usr/bin/fst2vcd", "-f", str(fst_path), "-o", str(vcd_path)], check=True)
        vcd = vcd_path.read_text(encoding="ascii")
        if "$enddefinitions" not in vcd or "count" not in vcd or "#" not in vcd:
            raise RuntimeError("Generated VCD lacks definitions, count or time markers.")
        report = {
            "status": "passed", "exit_code": 0, "completed_at_utc": datetime.now(timezone.utc).isoformat(),
            "simulator": "Icarus Verilog", "seed": 20261014, "tests": len(cases), "failures": 0,
            "verilator_lint": "passed", "results_xml": str(RESULT_FILE.relative_to(WORKSPACE)),
            "waveform_fst": str(fst_path.relative_to(WORKSPACE)), "waveform_vcd": str(vcd_path.relative_to(WORKSPACE)),
            "waveform_vcd_bytes": vcd_path.stat().st_size,
            "rtl_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
            "test_sha256": hashlib.sha256((SMOKE_DIR / "test_counter.py").read_bytes()).hexdigest(),
            "coverage": ["asynchronous reset", "35 continuous increments", "two 4-bit wraps", "5 disabled hold cycles", "reset held for 3 cycles", "5 restart increments"],
        }
        STATUS_FILE.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(f"Smoke PASS: tests={len(cases)}, failures=0; FST={fst_path}; VCD={vcd_path}", flush=True)
    except BaseException as error:
        STATUS_FILE.write_text(json.dumps({"status": "failed", "exit_code": 1, "error": str(error), "recorded_at_utc": datetime.now(timezone.utc).isoformat()}, indent=2) + "\n", encoding="utf-8")
        raise


if __name__ == "__main__":
    main()
