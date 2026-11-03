"""Exercise source preservation and stale-preview rejection on pinned upstream RTL."""
import hashlib
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
TOOL = HERE.parent / "prepare_kwt_soc.py"
SOURCES = {
    "e203_soc_top.v": "rtl/e203/soc/e203_soc_top.v",
    "e203_subsys_top.v": "rtl/e203/subsys/e203_subsys_top.v",
    "e203_subsys_main.v": "rtl/e203/subsys/e203_subsys_main.v",
    "tb_top.v": "tb/tb_top.v",
}


class WiringTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / "kwt-soc"
        for leaf, relative in SOURCES.items():
            target = self.root / relative
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(HERE / "upstream" / leaf, target)
        target = self.root / "accelerator/rtl/kwt_accelerator.v"
        target.parent.mkdir(parents=True)
        shutil.copyfile(HERE.parents[2] / "rtl/kwt_accelerator.v", target)

    def run_tool(self, action):
        return subprocess.run(
            [sys.executable, "-X", "utf8", str(TOOL), action, "--root", str(self.root)],
            text=True, encoding="utf-8", capture_output=True,
        )

    def hashes(self):
        return {
            p.relative_to(self.root).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
            for folder in ("rtl", "tb", "accelerator")
            for p in (self.root / folder).rglob("*") if p.is_file()
        }

    def test_preview_preserves_every_input_and_explains_clock_reset_path(self):
        before = self.hashes()
        result = self.run_tool("preview")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("PREVIEW_READY", result.stdout)
        self.assertEqual(before, self.hashes())
        after = self.root / "wiring_01/after"
        main = (after / SOURCES["e203_subsys_main.v"]).read_text()
        subsys = (after / SOURCES["e203_subsys_top.v"]).read_text()
        soc = (after / "rtl/e203/soc/kwt_soc_top.v").read_text()
        self.assertIn("assign kwt_bus_rst_n = bus_rst_n;", main)
        self.assertIn("assign kwt_bus_clk = hfclk;", subsys)
        self.assertIn(".kwt_bus_rst_n(kwt_bus_rst_n)", subsys)
        self.assertIn(".clk(kwt_bus_clk)", soc)
        self.assertIn(".rst_n(kwt_bus_rst_n)", soc)
        self.assertIn(".SRAM_EMA(3'd2)", soc)
        self.assertIn(".SRAM_EMAW(2'd0)", soc)
        self.assertIn(".external_abort_req(1'b0)", soc)

    def test_rejects_already_wired_or_unrecognized_sysper_without_changes(self):
        path = self.root / SOURCES["e203_soc_top.v"]
        path.write_text(path.read_text().replace(".sysper_icb_rsp_rdata (32'b0)",
                                                ".sysper_icb_rsp_rdata (custom_data)"))
        before = self.hashes()
        result = self.run_tool("preview")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("sysper_icb_rsp_rdata", result.stderr)
        self.assertEqual(before, self.hashes())
        self.assertFalse((self.root / "wiring_01").exists())

    def test_apply_rejects_stale_source_before_writing_any_target(self):
        self.assertEqual(self.run_tool("preview").returncode, 0)
        path = self.root / SOURCES["tb_top.v"]
        path.write_bytes(path.read_bytes() + b"\n// new user work\n")
        before = self.hashes()
        result = self.run_tool("apply")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("changed", result.stderr)
        self.assertEqual(before, self.hashes())

    def test_apply_preserves_original_soc_accelerator_and_test_hierarchy(self):
        before = self.hashes()
        self.assertEqual(self.run_tool("preview").returncode, 0)
        result = self.run_tool("apply")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("APPLY_DONE", result.stdout)
        after = self.hashes()
        self.assertEqual(before[SOURCES["e203_soc_top.v"]], after[SOURCES["e203_soc_top.v"]])
        name = "accelerator/rtl/kwt_accelerator.v"
        self.assertEqual(before[name], after[name])
        tb = (self.root / "tb/tb_top.v").read_text()
        self.assertIn("kwt_soc_top u_e203_soc_top(", tb)
        self.assertIn("`define CPU_TOP u_e203_soc_top.u_e203_subsys_top", tb)
        applied = self.hashes()
        self.assertNotEqual(self.run_tool("apply").returncode, 0)
        self.assertEqual(applied, self.hashes())

    def test_existing_output_is_never_overwritten(self):
        target = self.root / "rtl/e203/soc/kwt_soc_top.v"
        target.write_text("// user work\n")
        before = self.hashes()
        result = self.run_tool("preview")
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(before, self.hashes())

    def test_candidate_changed_after_preview_is_rejected(self):
        self.assertEqual(self.run_tool("preview").returncode, 0)
        candidate = self.root / "wiring_01/after/tb/tb_top.v"
        candidate.write_bytes(candidate.read_bytes() + b"\n// changed\n")
        before = self.hashes()
        result = self.run_tool("apply")
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(before, self.hashes())

    def test_existing_preview_is_preserved(self):
        self.assertEqual(self.run_tool("preview").returncode, 0)
        report = self.root / "wiring_01/report.json"
        before = report.read_bytes()
        result = self.run_tool("preview")
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(before, report.read_bytes())


if __name__ == "__main__":
    unittest.main()
