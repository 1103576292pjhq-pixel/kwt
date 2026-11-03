#!/usr/bin/env python3
"""Preview/apply wiring ONLY inside the user's kwt-soc integration copy.

No third-party Python packages. No compilation, shell execution, or RTL arithmetic
changes. The installed server sources are checked, never replaced by GitHub RTL.
"""
import argparse
import difflib
import hashlib
import json
from pathlib import Path
import re
import sys

SOC = "rtl/e203/soc/e203_soc_top.v"
MAIN = "rtl/e203/subsys/e203_subsys_main.v"
SUBSYS = "rtl/e203/subsys/e203_subsys_top.v"
TB = "tb/tb_top.v"
ACC = "accelerator/rtl/kwt_accelerator.v"
NEW = "rtl/e203/soc/kwt_soc_top.v"
INPUTS = (SOC, MAIN, SUBSYS, TB, ACC)
OUTPUTS = (MAIN, SUBSYS, NEW, TB)
STAGE = "wiring_01"


def digest(data):
    return hashlib.sha256(data).hexdigest()


def inside(root, relative):
    path = root / relative
    if not path.resolve().is_relative_to(root):
        raise ValueError("Path escapes integration copy: " + relative)
    return path


def once(text, pattern, replacement, description):
    matches = list(re.finditer(pattern, text, re.MULTILINE))
    if len(matches) != 1:
        raise ValueError(f"Expected exactly one {description}; found {len(matches)}")
    match = matches[0]
    value = replacement(match) if callable(replacement) else replacement
    return text[:match.start()] + value + text[match.end():]


def add_ports(text, module, declarations):
    return once(text, rf"^module\s+{module}\s*\(",
                lambda m: m[0] + "\n" + declarations,
                module + " ANSI module header")


def add_connections(text, module, instance, connections):
    return once(text, rf"^[ \t]*{module}\s+{instance}\s*\(",
                lambda m: m[0] + "\n" + connections,
                instance + " instance")


def append_logic(text, logic):
    return once(text, r"^[ \t]*endmodule\b", logic + "\nendmodule", "endmodule")


def connect_sysper(text):
    old = {
        "cmd_valid": "sysper_icb_cmd_valid", "cmd_ready": "sysper_icb_cmd_ready",
        "cmd_read": "", "cmd_addr": "", "cmd_wdata": "", "cmd_wmask": "",
        "rsp_valid": "sysper_icb_cmd_valid", "rsp_ready": "sysper_icb_cmd_ready",
        "rsp_err": "1'b0", "rsp_rdata": "32'b0",
    }
    for suffix, expected in old.items():
        port = "sysper_icb_" + suffix

        def replace(match):
            if re.sub(r"\s+", "", match[1]) != expected:
                raise ValueError("Unrecognized/already modified placeholder: " + port)
            return f".{port}({port})"

        text = once(text, rf"\.{port}\s*\(([^()]*)\)", replace, port + " connection")
    return text


def generate(raw):
    texts = {key: value.decode("utf-8").replace("\r\n", "\n") for key, value in raw.items()}
    main = texts[MAIN]
    if not re.search(r"\bwire\s+bus_rst_n\s*=\s*main_rst_n\s*;", main):
        raise ValueError("Server bus_rst_n = main_rst_n relationship was not found")
    if not re.search(r"\boutput\s+hfclk\b", main):
        raise ValueError("Expected main-generated output hfclk")
    if not re.search(r"\.clk\s*\(\s*hfclk\s*\)", main):
        raise ValueError("Expected hfclk bus/peripheral connections")
    for text in (texts[MAIN], texts[SUBSYS], texts[SOC]):
        if "kwt_bus_clk" in text or "kwt_bus_rst_n" in text:
            raise ValueError("KWT clock/reset exports already exist")
    if not re.search(r"\bmodule\s+kwt_accelerator\b", texts[ACC]):
        raise ValueError("Expected current kwt_accelerator source")

    main = add_ports(main, "e203_subsys_main", "  output wire kwt_bus_rst_n,\n")
    main = append_logic(main, "  // Export the existing synchronized bus reset; no new reset logic.\n"
                              "  assign kwt_bus_rst_n = bus_rst_n;\n")

    subsys = add_ports(texts[SUBSYS], "e203_subsys_top",
                       "  output wire kwt_bus_clk,\n  output wire kwt_bus_rst_n,\n")
    subsys = add_connections(subsys, "e203_subsys_main", "u_e203_subsys_main",
                             "    .kwt_bus_rst_n(kwt_bus_rst_n),\n")
    subsys = append_logic(subsys, "  // This is the main-generated clock already used by SysPer.\n"
                                  "  assign kwt_bus_clk = hfclk;\n")

    soc = once(texts[SOC], r"^module\s+e203_soc_top\s*\(",
               "module kwt_soc_top(", "original SoC module header")
    wires = """
 // KWT integration wires; SysPer is connected to one accelerator slave.
 wire kwt_bus_clk;
 wire kwt_bus_rst_n;
 wire [`E203_ADDR_SIZE-1:0] sysper_icb_cmd_addr;
 wire sysper_icb_cmd_read;
 wire [`E203_XLEN-1:0] sysper_icb_cmd_wdata;
 wire [`E203_XLEN/8-1:0] sysper_icb_cmd_wmask;
 wire sysper_icb_rsp_valid;
 wire sysper_icb_rsp_ready;
 wire sysper_icb_rsp_err;
 wire [`E203_XLEN-1:0] sysper_icb_rsp_rdata;
"""
    soc = once(soc, r"^[ \t]*wire\s+sysper_icb_cmd_ready\s*;",
               lambda m: m[0] + "\n" + wires, "existing SysPer ready wire")
    soc = connect_sysper(soc)
    soc = add_connections(soc, "e203_subsys_top", "u_e203_subsys_top",
                          "    .kwt_bus_clk(kwt_bus_clk),\n"
                          "    .kwt_bus_rst_n(kwt_bus_rst_n),\n")
    acc = """
 // Project development address; software polls the current custom ICB ABI.
 // Functional SRAM configuration: ARM_UD_MODEL at compilation, EMA=2/EMAW=0.
 kwt_accelerator #(
   .BASE_ADDR(32'h11000000),
   .SRAM_EMA(3'd2),
   .SRAM_EMAW(2'd0)
 ) u_kwt_accelerator (
   .clk(kwt_bus_clk),
   .rst_n(kwt_bus_rst_n),
   .icb_cmd_valid(sysper_icb_cmd_valid),
   .icb_cmd_ready(sysper_icb_cmd_ready),
   .icb_cmd_addr(sysper_icb_cmd_addr),
   .icb_cmd_read(sysper_icb_cmd_read),
   .icb_cmd_wdata(sysper_icb_cmd_wdata),
   .icb_cmd_wmask(sysper_icb_cmd_wmask),
   .icb_rsp_valid(sysper_icb_rsp_valid),
   .icb_rsp_ready(sysper_icb_rsp_ready),
   .icb_rsp_rdata(sysper_icb_rsp_rdata),
   .icb_rsp_err(sysper_icb_rsp_err),
   .external_abort_req(1'b0),
   .busy(), .compute_done(), .task_done(), .fault(),
   .error_code(), .abort_pending(), .abort_done()
 );
"""
    soc = append_logic(soc, acc)
    tb = once(texts[TB], r"^[ \t]*e203_soc_top\s+u_e203_soc_top\s*\(",
              "kwt_soc_top u_e203_soc_top(", "testbench SoC instance")
    # Select the VCS branch explicitly without accumulating `define lines.
    tb = "`ifndef vcs\n`define vcs\n`endif\n" + tb

    changed = {MAIN: main, SUBSYS: subsys, NEW: soc, TB: tb}
    result = {}
    for relative, text in changed.items():
        original = raw[SOC] if relative == NEW else raw[relative]
        if b"\r\n" in original:
            text = text.replace("\n", "\r\n")
        result[relative] = text.encode("utf-8")
    return result


def preview(root):
    stage = inside(root, STAGE)
    if stage.exists():
        raise ValueError("Existing preview is preserved: " + str(stage))
    if inside(root, NEW).exists():
        raise ValueError("Existing kwt_soc_top.v is preserved; refusing to overwrite")
    raw = {relative: inside(root, relative).read_bytes() for relative in INPUTS}
    changed = generate(raw)  # Validate all anchors before creating any preview files.
    report = {"root": str(root), "inputs": {p: digest(b) for p, b in raw.items()},
              "outputs": {p: digest(b) for p, b in changed.items()},
              "scope": "WIRING_PREVIEW_ONLY_NOT_COMPILED_NOT_SIMULATED"}
    stage.mkdir()
    for kind, contents in (("before", raw), ("after", changed)):
        for relative, data in contents.items():
            path = inside(root, f"{STAGE}/{kind}/{relative}")
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
    diffs = []
    for relative, data in changed.items():
        before = raw.get(relative, b"").decode("utf-8").splitlines(keepends=True)
        after = data.decode("utf-8").splitlines(keepends=True)
        diffs.extend(difflib.unified_diff(before, after, fromfile="before/" + relative,
                                          tofile="after/" + relative))
    (stage / "wiring.diff").write_text("".join(diffs), encoding="utf-8")
    (stage / "report.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
    print("PREVIEW_READY")
    print("Input RTL was not modified. Changes proposed:")
    for relative in OUTPUTS:
        print("  " + relative)
    print("Clock: main.hfclk -> subsys.hfclk -> kwt_bus_clk -> accelerator.clk")
    print("Reset: main.bus_rst_n -> kwt_bus_rst_n -> accelerator.rst_n")
    print("Base=0x11000000 EMA=2 EMAW=0 external_abort_req=0")
    print("Review: wiring_01/wiring.diff; backups: wiring_01/before/")
    print("No compilation, simulation, driver or STA validation has run.")


def apply(root):
    stage = inside(root, STAGE)
    if (stage / "applied.json").exists():
        raise ValueError("This preview was already applied")
    report = json.loads((stage / "report.json").read_text(encoding="utf-8"))
    if (report["root"] != str(root) or set(report["inputs"]) != set(INPUTS)
            or set(report["outputs"]) != set(OUTPUTS)):
        raise ValueError("Preview does not match this integration root/file set")
    for relative, sha in report["inputs"].items():
        if digest(inside(root, relative).read_bytes()) != sha:
            raise ValueError("Input changed since preview; nothing applied: " + relative)
    if inside(root, NEW).exists():
        raise ValueError("Existing kwt_soc_top.v is preserved")
    candidates = {}
    for relative, sha in report["outputs"].items():
        data = inside(root, f"{STAGE}/after/{relative}").read_bytes()
        if digest(data) != sha:
            raise ValueError("Preview candidate changed; nothing applied: " + relative)
        candidates[relative] = data
    # Inputs and all candidates have been checked. Backups stay in wiring_01/before.
    # This is not a multi-file atomic transaction; any OS write failure is reported.
    for relative, data in candidates.items():
        target = inside(root, relative)
        if relative == NEW:
            with target.open("xb") as stream:
                stream.write(data)
        else:
            target.write_bytes(data)
    (stage / "applied.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
    print("APPLY_DONE")
    print("Original e203_soc_top.v and accelerator RTL were preserved.")
    print("Next: compile with top=tb_top and official SRAM functional models.")
    print("This is wiring only; CPU-to-accelerator accesses are not yet verified.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("preview", "apply"))
    parser.add_argument("--root", type=Path, default=Path.cwd())
    args = parser.parse_args()
    root = args.root.resolve()
    if not root.is_dir() or root.name != "kwt-soc":
        parser.error("Run inside the separate kwt-soc integration copy")
    try:
        (preview if args.action == "preview" else apply)(root)
    except (OSError, ValueError, KeyError) as error:
        print("STOP: " + str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
