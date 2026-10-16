"""Fail-closed Icarus regression and lint entry for DOT64."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import xml.etree.ElementTree as ET
from datetime import datetime, timezone

from cocotb_tools.runner import get_runner

from inspect_wave import inspect_first_result

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
REPORT = ROOT / "reports/prototype/dot64"
STATUS = REPORT / "status.json"
BUILD = REPORT / "build"
RESULTS = REPORT / "results.xml"
EXPECTED_TESTS = 8


def write_status(value):
    STATUS.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def main():
    REPORT.mkdir(parents=True, exist_ok=True)
    write_status({"status": "RUNNING", "started_utc": datetime.now(timezone.utc).isoformat()})
    try:
        if sys.prefix == sys.base_prefix:
            raise RuntimeError("Use project Linux .venv-dv")
        os.environ["PATH"] = "/usr/bin:/bin"
        os.environ.pop("GUI", None)
        os.environ["COCOTB_ANSI_OUTPUT"] = "0"
        sources = [ROOT / "rtl/dot64.sv"]
        for file in [RESULTS, BUILD / "dot64.fst", REPORT / "dot64.vcd"]:
            file.unlink(missing_ok=True)
        subprocess.run(["/usr/bin/verilator", "--lint-only", "--Wall", "--top-module", "dot64", *map(str, sources)], check=True)
        runner = get_runner("icarus")
        runner.build(sources=sources, hdl_toplevel="dot64", build_dir=BUILD,
                     timescale=("1ns", "1ps"), always=True, waves=True)
        runner.test(hdl_toplevel="dot64", test_module="test_dot64", test_dir=BUILD,
                    build_dir=BUILD, results_xml=RESULTS, seed=20261015, waves=True,
                    plusargs=["+dumpfile_path=dot64.fst"], extra_env={"PYTHONPATH": str(HERE)})
        tree = ET.parse(RESULTS)
        tests = tree.findall(".//testcase")
        failures = tree.findall(".//failure") + tree.findall(".//error")
        skips = tree.findall(".//skipped")
        if len(tests) != EXPECTED_TESTS or failures or skips:
            raise RuntimeError(f"DOT64 results invalid: tests={len(tests)}, failures={len(failures)}, skips={len(skips)}")
        fst, vcd = BUILD / "dot64.fst", REPORT / "dot64.vcd"
        if not fst.is_file() or not fst.stat().st_size:
            raise RuntimeError("DOT64 FST absent or empty")
        subprocess.run(["/usr/bin/fst2vcd", "-f", str(fst), "-o", str(vcd)], check=True)
        wave = vcd.read_text(encoding="ascii")
        if "$enddefinitions" not in wave or "out_raw" not in wave or "#" not in wave:
            raise RuntimeError("DOT64 VCD invalid")
        waveform_check = inspect_first_result(vcd)
        hashes = {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest()
                  for p in [*sources, HERE / "test_dot64.py", HERE / "run_dot64.py", HERE / "inspect_wave.py", RESULTS, fst, vcd]}
        write_status({"status": "PASS", "exit_code": 0, "tests": len(tests), "failures": 0,
                      "skips": 0, "seed": 20261015, "lint": "PASS", "hashes": hashes,
                      "waveform_check": waveform_check,
                      "completed_utc": datetime.now(timezone.utc).isoformat()})
        print(f"DOT64 PASS: {len(tests)} tests, no skips; lint PASS", flush=True)
    except BaseException as error:
        write_status({"status": "FAIL", "exit_code": 1, "error": str(error),
                      "completed_utc": datetime.now(timezone.utc).isoformat()})
        raise


if __name__ == "__main__":
    main()
