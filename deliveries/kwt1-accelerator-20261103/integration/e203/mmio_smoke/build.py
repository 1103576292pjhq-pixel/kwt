#!/usr/bin/env python3
"""Build locally in WSL; preserve earlier builds and never touch server/RTL."""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parents[2]
INSTALL = Path("/mnt/d/嵌赛芯片设计赛道/toolchains/nuclei-2024.06/installation.json")


def main():
    gcc = Path(json.loads(INSTALL.read_text())["gcc"])
    prefix = str(gcc).removesuffix("gcc")
    c_header = (HERE / "kwt_mmio.h").read_text()
    rtl_header = (PROJECT / "rtl/include/kwt_icb_config.vh").read_text()
    names = ("STATUS", "TASK", "LAYER", "TILE", "INDEX", "DATA", "ERROR",
             "ACK_TASK", "ACK_SEQ", "ACK_COUNT")
    for name in names:
        c = re.search(rf"#define\s+KWT_{name}\s+0x([0-9a-f]+)u", c_header, re.I)
        v = re.search(rf"`define\s+KWT_ICB_{name}\s+8'h([0-9a-f]+)", rtl_header, re.I)
        assert c and v and int(c[1], 16) == int(v[1], 16), name

    out = HERE / "build-01"
    out.mkdir()  # Fail rather than overwrite an earlier run.
    commands = []

    def run(args):
        result = subprocess.run(list(map(str, args)), cwd=HERE, check=True,
                                capture_output=True, text=True)
        commands.append({"argv": list(map(str, args)), "returncode": result.returncode,
                         "stdout": result.stdout, "stderr": result.stderr})
        return result.stdout

    run(["gcc", "-std=c11", "-O2", "-Wall", "-Wextra", "-Werror",
         HERE / "tests/native.c", HERE / "register_test.c", "-o", out / "native-check"])
    native = run([out / "native-check"])
    print(native.strip(), flush=True)
    elf = out / "mmio_smoke.elf"
    binary = out / "mmio_smoke.bin"
    image = out / "mmio_smoke.verilog"
    run([gcc, "-std=c11", "-O2", "-Wall", "-Wextra", "-Werror",
         "-march=rv32imac_zicsr_zifencei", "-mabi=ilp32", "-mcmodel=medany",
         "-msmall-data-limit=0", "-mno-relax", "-ffreestanding", "-fno-builtin",
         "-fno-pic", "-fno-stack-protector", "-nostdlib", "-nostartfiles",
         "-Wl,--build-id=none", "-Wl,--no-relax", "-Wl,-Map=" + str(out / "mmio_smoke.map"),
         "-T", HERE / "link.ld", HERE / "start.S", HERE / "register_test.c",
         HERE / "real_io.c", "-o", elf])
    symbols = run([prefix + "nm", "-n", elf])
    table = {parts[2]: int(parts[0], 16) for line in symbols.splitlines()
             if len(parts := line.split()) == 3}
    assert table["_start"] == 0x80000000
    assert table["test_end"] == 0x80000086
    assert table["__bss_end"] <= 0x80000c00
    assert table["__stack_top"] == 0x80001000
    assert not run([prefix + "nm", "-u", elf]).strip(), "Unresolved firmware symbol"
    header = elf.read_bytes()[:52]
    assert header[:7] == b"\x7fELF\x01\x01\x01"
    assert struct.unpack_from("<H", header, 18)[0] == 243
    assert struct.unpack_from("<I", header, 24)[0] == 0x80000000
    disassembly = run([prefix + "objdump", "-d", elf])
    assert not re.search(r"\(\s*gp\s*\)", disassembly), "Unexpected gp-relative data access"
    (out / "mmio_smoke.dump").write_text(disassembly)
    (out / "symbols.txt").write_text(symbols)
    (out / "elf-attributes.txt").write_text(run([prefix + "readelf", "-h", "-A", elf]))
    run([prefix + "objcopy", "-O", "binary", "--gap-fill=0", elf, binary])
    data = binary.read_bytes()
    assert 0x100 < len(data) <= 0xc00
    assert data[0x86:0x88] == b"\x01\xa0", "Termination must be c.j at offset 0x86"
    image.write_text("@00000000\n" + "\n".join(
        " ".join(f"{b:02X}" for b in data[i:i+16]) for i in range(0, len(data), 16)) + "\n")
    assert bytes.fromhex(" ".join(image.read_text().splitlines()[1:])) == data
    sources = ("start.S", "link.ld", "kwt_mmio.h", "register_test.c", "real_io.c", "build.py", "tests/native.c")
    report = {
        "status": "COMPILED_AND_HOST_LOGIC_CHECKED_NOT_SOC_VALIDATED",
        "gcc": str(gcc), "version": run([gcc, "--version"]).splitlines()[0],
        "arch": "rv32imac_zicsr_zifencei", "abi": "ilp32", "base": "0x11000000",
        "entry": "0x80000000", "test_end": "0x80000086", "stack_top": "0x80001000",
        "binary_bytes": len(data), "bss_end": hex(table["__bss_end"]),
        "native_test": native.strip(), "expected_mmio_reads": 28, "expected_mmio_writes": 24,
        "sources": {p: hashlib.sha256((HERE/p).read_bytes()).hexdigest() for p in sources},
        "outputs": {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in (elf, binary, image)},
        "commands": commands,
        "limitations": "No E203 CPU execution yet. Tests only register shadows, not accelerator tasks or shared SRAM."
    }
    (out / "build-report.json").write_text(json.dumps(report, indent=2))
    print(f"FW_READY bytes={len(data)} entry=0x80000000 test_end=0x80000086 bss_end={table['__bss_end']:#x}")
    print("UPLOAD_ONLY", image)
    print("Server E203 MMIO execution is still pending.")


if __name__ == "__main__":
    main()
