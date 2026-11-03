#!/usr/bin/env python3
"""Run under WSL: verify the downloaded compiler, ELF target and byte-image tool.

This is an installation check, not a CPU/accelerator test.
"""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parents[1]
INSTALL = Path("/mnt/d/嵌赛芯片设计赛道/toolchains/nuclei-2024.06/installation.json")


def main():
    install = json.loads(INSTALL.read_text())
    gcc = Path(install["gcc"])
    bindir = gcc.parent
    prefix = gcc.name.removesuffix("gcc")
    out = PROJECT / "verification/toolchain-20261102-01"
    out.mkdir(parents=True)  # Preserve previous runs; do not overwrite.
    commands = []

    def run(args):
        result = subprocess.run(list(map(str, args)), check=True, text=True, capture_output=True)
        commands.append({"argv": list(map(str, args)), "stdout": result.stdout,
                         "stderr": result.stderr, "returncode": result.returncode})
        return result.stdout

    version = run([gcc, "--version"])
    target = run([gcc, "-dumpmachine"]).strip()
    assert target == "riscv64-unknown-elf", target
    multilib = run([gcc, "-print-multi-lib"])
    elf = out / "toolchain-probe.elf"
    image = out / "toolchain-probe.verilog"
    run([gcc, "-march=rv32imac_zicsr_zifencei", "-mabi=ilp32", "-O2",
         "-ffreestanding", "-nostdlib", "-nostartfiles",
         "-Wl,--build-id=none", "-Wl,-Ttext=0x80000000",
         "-Wl,-e,kwt_toolchain_probe", HERE / "toolchain_probe.c", "-o", elf])
    header = elf.read_bytes()[:52]
    assert header[:7] == b"\x7fELF\x01\x01\x01", "Expected ELF32 little-endian"
    assert struct.unpack_from("<H", header, 18)[0] == 243, "Expected RISC-V machine"
    assert struct.unpack_from("<I", header, 24)[0] == 0x80000000, "Wrong entry"
    attributes = run([bindir / (prefix + "readelf"), "-h", "-A", elf])
    disassembly = run([bindir / (prefix + "objdump"), "-d", elf])
    run([bindir / (prefix + "objcopy"), "-O", "verilog", "-j", ".text",
         "--change-addresses=-0x80000000", elf, image])
    assert image.read_text().splitlines()[0] == "@00000000", "Expected ITCM-relative byte image"
    (out / "probe.dump").write_text(disassembly)
    (out / "elf-attributes.txt").write_text(attributes)
    report = {"status": "TOOLCHAIN_CHECK_PASS_NOT_CPU_TEST", "gcc": str(gcc),
              "version": version, "target": target, "arch": "rv32imac_zicsr_zifencei",
              "abi": "ilp32", "installation": install, "commands": commands,
              "files": {p.name: hashlib.sha256(p.read_bytes()).hexdigest()
                        for p in (elf, image)},
              "limitations": "Probe has no startup/termination; not a runnable accelerator test."}
    (out / "report.json").write_text(json.dumps(report, indent=2))
    print(version.splitlines()[0])
    print("TARGET", target)
    print("RV32_MULTILIB", [line for line in multilib.splitlines() if "rv32imac" in line])
    print("PASS TOOLCHAIN ELF32 little-endian RISC-V entry=0x80000000 image=@00000000")
    print("REPORT", out / "report.json")
    print("This check did not run an E203 CPU or accelerator.")


if __name__ == "__main__":
    main()
