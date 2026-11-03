#!/usr/bin/env python3
"""Local WSL cross build. Output directories must be new; server is untouched."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parents[2]
BOOT = HERE.parent / "mmio_smoke"
INSTALL = Path("/mnt/d/嵌赛芯片设计赛道/toolchains/nuclei-2024.06/installation.json")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", default="task-build-01")
    args = parser.parse_args()
    gcc = Path(json.loads(INSTALL.read_text())["gcc"])
    prefix = str(gcc).removesuffix("gcc")
    header = (HERE/"task_test.h").read_text() + (BOOT/"kwt_mmio.h").read_text()
    rtl = (PROJECT/"rtl/include/kwt_icb_config.vh").read_text()
    offsets = {}
    for name, value in re.findall(r"`define\s+KWT_ICB_(\w+)\s+8'h([0-9a-f]+)", rtl, re.I):
        match = re.search(rf"#define\s+KWT_{name}\s+0x([0-9a-f]+)u", header, re.I)
        # ABORT is deliberately unused in the successful task path.
        if name == "ABORT": continue
        assert match and int(match[1],16) == int(value,16), name
        offsets[name] = int(value,16)
    base = re.search(r"`define\s+KWT_ICB_DEFAULT_BASE\s+32'h([0-9a-f_]+)", rtl, re.I)
    assert base and int(base[1].replace("_", ""),16) == 0x11000000
    control = (PROJECT/"rtl/include/kwt_control_config.vh").read_text()
    for name in ("BEGIN", "X", "OPEN", "W", "BIAS", "COMMIT", "START"):
        cv = re.search(rf"#define\s+KWT_CMD_{name}\s+(\d+)u", header)
        rv = re.search(rf"`define\s+KWT_CMD_{name}\s+3'd(\d+)", control)
        assert cv and rv and cv[1] == rv[1], name

    out = HERE/args.output
    out.mkdir()
    commands = []

    def run(argv):
        result = subprocess.run(list(map(str,argv)), cwd=HERE, capture_output=True, text=True)
        commands.append({"argv":list(map(str,argv)),"code":result.returncode,
                         "stdout":result.stdout,"stderr":result.stderr})
        (out/"commands.json").write_text(json.dumps(commands,indent=2))
        result.check_returncode()
        return result.stdout

    numeric = run(["python3", HERE/"tests/check_numeric.py"])
    print(numeric.strip(), flush=True)
    elf, binary, image = [out/f"task_smoke.{suffix}" for suffix in ("elf", "bin", "verilog")]
    run([gcc,"-std=c11","-Os","-Wall","-Wextra","-Werror",
         "-march=rv32imac_zicsr_zifencei","-mabi=ilp32","-mcmodel=medany",
         "-msmall-data-limit=0","-mno-relax","-ffreestanding","-fno-builtin",
         "-fno-pic","-fno-stack-protector","-fstack-usage","-nostdlib","-nostartfiles",
         "-Wl,--build-id=none","-Wl,--no-relax","-Wl,-Map="+str(out/"task_smoke.map"),
         "-T",BOOT/"link.ld", BOOT/"start.S",HERE/"task_test.c",HERE/"fixture.c",
         HERE/"real_io.c","-o",elf])
    symbols = run([prefix+"nm","-n",elf])
    table = {p[2]:int(p[0],16) for line in symbols.splitlines() if len(p:=line.split()) == 3}
    assert table["_start"] == 0x80000000 and table["test_end"] == 0x80000086
    assert table["__bss_end"] <= 0x80000c00 and table["__stack_top"] == 0x80001000
    assert not run([prefix+"nm","-u",elf]).strip()
    eh = elf.read_bytes()[:52]
    assert eh[:7] == b"\x7fELF\x01\x01\x01" and struct.unpack_from("<H",eh,18)[0] == 243
    assert struct.unpack_from("<I",eh,24)[0] == 0x80000000
    dump = run([prefix+"objdump","-d",elf])
    assert not re.search(r"\(\s*gp\s*\)", dump), "Unexpected gp-relative data reference"
    (out/"task_smoke.dump").write_text(dump)
    (out/"symbols.txt").write_text(symbols)
    (out/"elf-attributes.txt").write_text(run([prefix+"readelf","-h","-A",elf]))
    run([prefix+"objcopy","-O","binary","--gap-fill=0",elf,binary])
    data = binary.read_bytes()
    assert data[0x86:0x88] == b"\x01\xa0" and 0x100 < len(data) <= 0xc00
    image.write_text("@00000000\n"+"\n".join(" ".join(f"{b:02X}" for b in data[i:i+16])
                                              for i in range(0,len(data),16))+"\n")
    assert bytes.fromhex(" ".join(image.read_text().splitlines()[1:])) == data
    sources = [HERE/n for n in ("task_test.c","task_test.h","fixture.c","fixture.h","real_io.c","build.py")]
    sources += [BOOT/n for n in ("start.S","link.ld","kwt_mmio.h")]
    report = {
        "status":"CROSS_COMPILED_SERVER_CPU_TASK_VALIDATION_PENDING",
        "compiler":str(gcc),"version":run([gcc,"--version"]).splitlines()[0],
        "entry":hex(table["_start"]),"test_end":hex(table["test_end"]),
        "bss_end":hex(table["__bss_end"]),"diagnostics_address":hex(table["kwt_diag"]),
        "stack_top":hex(table["__stack_top"]),"binary_bytes":len(data),
        "arch":"rv32imac_zicsr_zifencei","abi":"ilp32","offsets":offsets,
        "expected_blocks":400,"expected_outputs":25344,"numeric_check":numeric.strip(),
        "sources":{str(p.relative_to(PROJECT)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sources},
        "outputs":{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (elf,binary,image)},
        "limitations":"No server CPU task run yet. Local RTL uses SRAM contract models. No shared RAM or STA result.",
    }
    (out/"build-report.json").write_text(json.dumps(report,indent=2))
    print(f"FW_READY bytes={len(data)} bss_end={table['__bss_end']:#x} diag={table['kwt_diag']:#x}")
    print("UPLOAD_ONLY",image)


if __name__ == "__main__":
    main()
