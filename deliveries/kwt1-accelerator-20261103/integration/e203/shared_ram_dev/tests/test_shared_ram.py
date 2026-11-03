from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[1]

class SharedRamTests(unittest.TestCase):
    def test_bus_transactions(self):
        with tempfile.TemporaryDirectory() as tmp:
            exe=Path(tmp)/"simv"
            built=subprocess.run(["iverilog","-g2012","-s","tb_shared_ram_icb","-o",str(exe),
                                  str(ROOT/"rtl/kwt_shared_ram_icb.v"),
                                  str(ROOT/"sim/kwt_shared_ram_sim.v"),
                                  str(ROOT/"tb/tb_shared_ram_icb.v")],capture_output=True,text=True)
            self.assertEqual(built.returncode,0,built.stderr)
            run=subprocess.run(["vvp",str(exe)],capture_output=True,text=True,timeout=20)
            self.assertEqual(run.returncode,0,run.stdout+run.stderr)
            self.assertIn("PASS SHARED_RAM_ICB",run.stdout)
            print(run.stdout.strip())

    def test_synthesis_guard_rejects_behavioral_memory(self):
        with tempfile.TemporaryDirectory() as tmp:
            run=subprocess.run(["iverilog","-g2012","-DSYNTHESIS","-s","kwt_shared_ram_sim",
                                "-o",str(Path(tmp)/"bad"),str(ROOT/"rtl/kwt_shared_ram_icb.v"),
                                str(ROOT/"sim/kwt_shared_ram_sim.v")],capture_output=True,text=True)
            self.assertNotEqual(run.returncode,0)
            self.assertIn("ERROR_SHARED_RAM_MODEL_IS_SIMULATION_ONLY",run.stderr)

    def test_production_accelerator_manifest_excludes_shared_ram(self):
        project=ROOT.parents[2]
        text=(project/"rtl/kwt.f").read_text()
        self.assertNotIn("shared_ram",text)
        self.assertEqual(sum(line.strip().endswith(".v") for line in text.splitlines()),15)

if __name__=="__main__":
    unittest.main()
