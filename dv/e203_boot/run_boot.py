"""Reproduce official E203 ISA smoke and the reusable freestanding boot shell."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "reports/system/upstream-smoke"
UP = ROOT / "vendor/e203_hbirdv2-upstream"
CODE_INPUTS=["soc/e203_common/e203_cpu_shell.sv", "soc/e203_common/icb_shared_ram.sv", "sw/e203/start.S", "sw/e203/link.ld", "sw/e203/boot_smoke.c", "dv/e203_boot/run_boot.py", "dv/e203_boot/tb_e203_boot.sv", "dv/e203_boot/tb_icb_shared_ram.sv", "dv/e203_boot/timescale.v", "scripts/run_e203_upstream_smoke.sh"]

def input_hashes():
    return {p:hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in CODE_INPUTS}

def run(name: str, command: list[str], timeout: int = 180, cwd: Path = ROOT) -> str:
    with (OUT / "commands.jsonl").open("a") as stream:
        stream.write(json.dumps({"name": name, "cwd": str(cwd), "command": command}) + "\n")
    shown=' '.join(command) if len(command)<30 else f"{command[0]} ({len(command)-1} arguments; exact command in commands.jsonl)"
    print(f"[{name}] {shown}", flush=True)
    try:
        p = subprocess.run(command, cwd=cwd, text=True, stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT, timeout=timeout)
    except subprocess.TimeoutExpired as exc:
        (OUT / f"{name}.log").write_bytes(exc.stdout or b"")
        raise
    (OUT / f"{name}.log").write_text(p.stdout)
    print(p.stdout[-3500:], flush=True)
    if p.returncode:
        raise RuntimeError(f"{name}: exit {p.returncode}")
    return p.stdout

def verify_sources():
    manifest = json.loads((ROOT / "config/e203-source-manifest.json").read_text(encoding="utf-8-sig"))
    count = 0
    for repo in manifest["repositories"]:
        for item in repo["files"]:
            path = ROOT / repo["root"] / item["path"]
            if item["type"] == "symlink":
                if not path.is_symlink() or str(path.readlink()) != item["target"]:
                    raise RuntimeError(f"upstream symlink mismatch: {path}")
            elif hashlib.sha256(path.read_bytes()).hexdigest() != item["sha256"]:
                raise RuntimeError(f"upstream hash mismatch: {path}")
            count += 1
    return count

def rtl_compile(top: str, extra: list[Path]) -> Path:
    rtl = UP / "rtl/e203"
    out = OUT / f"{top}.vvp"
    includes = [rtl/"core", rtl/"perips", rtl/"perips/apb_i2c"]
    run(f"compile-{top}", ["iverilog", "-g2012", "-Diverilog", "-DDISABLE_SV_ASSERTION=1",
        "-s", top, "-o", str(out), *[x for d in includes for x in ("-I", str(d))],
        str(ROOT/"dv/e203_boot/timescale.v"), *map(str, sorted(rtl.rglob("*.v"))), *map(str, extra)])
    return out

def artifacts(name: str):
    elf = OUT / f"{name}.elf"
    disassembly=run(f"disassemble-{name}", ["riscv64-unknown-elf-objdump", "-d", "-S", str(elf)])
    attributes=run(f"attributes-{name}", ["riscv64-unknown-elf-readelf", "-h", "-A", str(elf)])
    if not all(token in attributes for token in ["ELF32", "RISC-V", "0x80000000", "soft-float ABI", "rv32i", "_m2", "_a2", "_c2", "_zicsr", "_zifencei"]):
        raise RuntimeError(f"{name}: unexpected ELF32 / ILP32 / ISA attributes")
    if name=="boot-smoke" and not all(token in disassembly for token in ["amoadd.w", "divu", "remu", "mul", "mtvec", "mcycle"]):
        raise RuntimeError("boot-smoke: actual ISA/startup coverage missing")
    run(f"hex-{name}", ["riscv64-unknown-elf-objcopy", "-O", "verilog", str(elf), str(OUT/f"{name}.verilog")])

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument("--upstream-only", action="store_true")
    args=parser.parse_args()
    OUT.mkdir(parents=True, exist_ok=True)
    report={"status":"RUNNING"}
    (OUT/"result.json").write_text(json.dumps(report))
    if not args.upstream_only:
        (ROOT/"work/e203_boot_handoff.json").write_text(json.dumps({"status":"RUNNING", "report":"reports/system/upstream-smoke/result.json"},indent=2)+"\n")
    (OUT/"commands.jsonl").write_text("")
    verified=verify_sources()
    frozen_inputs=input_hashes() if not args.upstream_only else {}
    run("gcc-version", ["riscv64-unknown-elf-gcc", "--version"])
    isa=UP/"riscv-tools/riscv-tests/isa"
    env=UP/"riscv-tools/riscv-tests/env"
    gcc=["riscv64-unknown-elf-gcc", "-march=rv32imac_zicsr_zifencei", "-mabi=ilp32", "-mcmodel=medany",
         "-nostdlib", "-nostartfiles", "-ffreestanding", "-fno-builtin", "-Wl,--no-relax"]
    run("build-upstream-add", [*gcc, "-I", str(env/"p"), "-I", str(isa/"macros/scalar"),
        "-T", str(env/"p/link.ld"), f"-Wl,-Map,{OUT/'upstream-add.map'}",
        str(isa/"rv32ui/add.S"), "-o", str(OUT/"upstream-add.elf")])
    artifacts("upstream-add")
    # The official makefile applies the same 0x80000000 -> 0 byte-image relocation.
    run("relocate-upstream-image", ["riscv64-unknown-elf-objcopy", "-O", "verilog", "--adjust-vma=-0x80000000", str(OUT/"upstream-add.elf"), str(OUT/"upstream-add.verilog")])
    image=rtl_compile("tb_top", [UP/"tb/tb_top.v"])
    # Icarus packed-string readmemh mishandles UTF-8 in absolute filenames.
    # Keep cwd Unicode-safe at OS level and use ASCII relative image filenames.
    log=run("simulate-upstream-add", ["vvp", str(image), "+DUMPWAVE=0", "+TESTCASE=upstream-add"], cwd=OUT)
    if "TEST_PASS" not in log or "TEST_FAIL" in log or "Time Out" in log:
        raise RuntimeError("upstream smoke did not explicitly pass")
    report.update(upstream_isa="PASS", source_entries_verified=verified)
    if not args.upstream_only:
        run("compile-shared-ram", ["iverilog", "-g2012", "-s", "tb_icb_shared_ram", "-o", str(OUT/"shared-ram.vvp"), str(ROOT/"soc/e203_common/icb_shared_ram.sv"), str(ROOT/"dv/e203_boot/tb_icb_shared_ram.sv")])
        log=run("simulate-shared-ram", ["vvp", str(OUT/"shared-ram.vvp")])
        if "ICB_SHARED_RAM_PASS checks=12" not in log:
            raise RuntimeError("shared RAM evidence incomplete")
        report["shared_ram"]="PASS"
        run("lint-shared-ram", ["verilator", "--lint-only", "-Wall", "--top-module", "icb_shared_ram", str(ROOT/"soc/e203_common/icb_shared_ram.sv")])
        report["shared_ram_lint"]="PASS"
        run("build-boot-smoke", [*gcc, "-Os", "-g", "-msmall-data-limit=8", "-Wall", "-Wextra", "-Werror",
            "-T", str(ROOT/"sw/e203/link.ld"), f"-Wl,-Map,{OUT/'boot-smoke.map'}",
            str(ROOT/"sw/e203/start.S"), str(ROOT/"sw/e203/boot_smoke.c"), "-o", str(OUT/"boot-smoke.elf")])
        artifacts("boot-smoke")
        run("binary-boot-smoke", ["riscv64-unknown-elf-objcopy", "-O", "binary", str(OUT/"boot-smoke.elf"), str(OUT/"boot-smoke.bin")])
        payload=(OUT/"boot-smoke.bin").read_bytes()
        if len(payload)>65536:
            raise RuntimeError("firmware exceeds ITCM")
        (OUT/"boot-smoke.hex").write_text("\n".join(f"{b:02x}" for b in payload)+"\n")
        image=rtl_compile("tb_e203_boot", [ROOT/"soc/e203_common/e203_cpu_shell.sv", ROOT/"soc/e203_common/icb_shared_ram.sv", ROOT/"dv/e203_boot/tb_e203_boot.sv"])
        for mode in ["normal", "trap"]:
            log=run(f"simulate-boot-{mode}", ["vvp", str(image), "+FIRMWARE=boot-smoke.hex", f"+FIRMWARE_BYTES={len(payload)}", f"+MODE={mode}"], timeout=240, cwd=OUT)
            if f"BOOT_{mode.upper()}_PASS" not in log:
                raise RuntimeError(f"boot {mode} lacks explicit pass")
        report.update(freestanding_boot="PASS", illegal_instruction_trap="PASS", firmware_bytes=len(payload))
    verified_after=verify_sources()
    if not args.upstream_only and input_hashes()!=frozen_inputs:
        raise RuntimeError("implementation inputs changed during verification; repeat required")
    report.update(status="PASS", source_entries_verified_after=verified_after)
    report["input_sha256"]=frozen_inputs
    report["artifacts"]={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in OUT.iterdir() if p.is_file() and p.suffix in (".elf", ".map", ".hex", ".verilog", ".bin")}
    (OUT/"result.json").write_text(json.dumps(report, indent=2)+"\n")
    if not args.upstream_only:
        handoff={"status":"PASS", "scope":"Reusable public E203 boot only; no FFN1 CPU integration or competition completion claim", "report":"reports/system/upstream-smoke/result.json", "command":"bash scripts/run_e203_upstream_smoke.sh", "exit_code":0,
                 "cpu_module":"e203_cpu_shell", "cpu_ports":"clk,lfclk,rst_n; bus_clk,bus_rst_n; sysper_icb_*,sysmem_icb_*", "ram_module":"icb_shared_ram", "ram_ports":"clk,rst_n,icb_cmd_valid,icb_cmd_ready,icb_cmd_addr[31:0],icb_cmd_read,icb_cmd_wdata[31:0],icb_cmd_wmask[3:0],icb_rsp_valid,icb_rsp_ready,icb_rsp_rdata[31:0],icb_rsp_err",
                 "shared_base":"0xa0000000", "shared_bytes":524288, "itcm_base":"0x80000000", "dtcm_base":"0x90000000", "main_signature":"int main(void)", "mailbox":{"0x00":"commit magic BOOT=0x424f4f54 or TRAP=0x54524150", "0x04":"main return value; trap 0xffffffff", "0x08":"mcause", "0x0c":"mepc", "0x10":"mcycle low32"},
                 "build_isa":"rv32imac_zicsr_zifencei", "abi":"ilp32", "limitations":["Keep default PLL bypass and PMU clock/reset configuration", "Compile dv/e203_boot/timescale.v before upstream RTL", "Use ASCII relative readmemh image filenames", "No competition-specific platform confirmation, PPA, timing, SDK compatibility or accelerator integration claim"], "input_sha256":frozen_inputs, "result_sha256":hashlib.sha256((OUT/"result.json").read_bytes()).hexdigest()}
        (ROOT/"work/e203_boot_handoff.json").write_text(json.dumps(handoff,indent=2)+"\n")
    print(json.dumps(report, indent=2), flush=True)

if __name__=="__main__":
    try:
        main()
    except Exception as exc:
        OUT.mkdir(parents=True, exist_ok=True)
        (OUT/"result.json").write_text(json.dumps({"status":"FAIL", "error": str(exc)}, indent=2)+"\n")
        print(str(exc), file=sys.stderr)
        sys.exit(1)
