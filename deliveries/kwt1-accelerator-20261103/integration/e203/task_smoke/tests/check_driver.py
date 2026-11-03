"""Run the actual C task driver against RTL, plus response corruption checks."""
import argparse
import os
from pathlib import Path
import re
import subprocess
import tempfile
import json

HERE = Path(__file__).resolve().parents[1]
PROJECT = HERE.parents[2]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    assert (HERE / "task_test.c").exists(), "Missing CPU task driver implementation"
    out = args.output.resolve()
    out.mkdir()
    native = out / "native-driver"
    subprocess.run(["gcc", "-std=c11", "-Os", "-Wall", "-Wextra", "-Werror",
                    str(HERE/"tests/native_io.c"), str(HERE/"task_test.c"),
                    str(HERE/"fixture.c"), "-o", str(native)], check=True)
    rtl = out / "driver.vvp"
    built = subprocess.run(["iverilog", "-g2012", "-DKWT_STORAGE_TEST_CONTRACT",
                            "-s", "tb_c_driver", "-o", str(rtl),
                            "-f", "rtl/kwt.f", "tb/memory/support/sram_contract_models.v",
                            str(HERE/"tests/tb_c_driver.v")], cwd=PROJECT, capture_output=True, text=True)
    (out/"compile.log").write_text(built.stdout+built.stderr)
    built.check_returncode()
    reports = []
    # A bit error, incorrect sequence, reported fault, incorrect cursor, no ready.
    for mutation, want in ((0, 1), (1, 0x54), (2, 0x51), (3, 0x41), (4, 0x55), (5, 0x42)):
        with tempfile.TemporaryDirectory(prefix="kwt-c-rtl-") as tmp:
            req, rsp = Path(tmp)/"request", Path(tmp)/"response"
            os.mkfifo(req); os.mkfifo(rsp)
            # Keep both ends open until processes exit; no open-order deadlock.
            fds = [os.open(p, os.O_RDWR) for p in (req, rsp)]
            log_path = out/f"rtl-{mutation}.log"
            try:
                with log_path.open("w") as log:
                    sim = subprocess.Popen(["vvp", str(rtl), f"+request={req}",
                                            f"+response={rsp}", f"+mutation={mutation}"], stdout=log, stderr=log)
                    try:
                        run = subprocess.run([str(native), str(req), str(rsp)], capture_output=True,
                                             text=True, timeout=180)
                        sim.wait(timeout=10)
                    finally:
                        if sim.poll() is None:
                            sim.kill(); sim.wait()
            finally:
                for fd in fds: os.close(fd)
            (out/f"native-{mutation}.log").write_text(run.stdout+run.stderr)
            print(run.stdout.strip(), flush=True)
            match = re.search(r"C_TASK code=([0-9a-f]+)", run.stdout)
            assert match and int(match[1], 16) == want, (mutation, run.stdout, run.stderr)
            assert run.returncode == (0 if mutation == 0 else 1)
            assert sim.returncode == 0, log_path.read_text()
            if mutation == 0:
                assert "blocks=400 outputs=25344" in run.stdout
                assert "result_reads=25344" in log_path.read_text()
            else:
                assert "altered=1" in log_path.read_text()
            reports.append({"mutation":mutation,"code":hex(want),"driver":run.stdout.strip(),
                            "rtl":log_path.read_text().strip()})
    (out/"report.json").write_text(json.dumps(reports, indent=2))
    print("PASS C_DRIVER_RTL scenarios=6 full_tasks=1 blocks=400 outputs=25344")


if __name__ == "__main__":
    main()
