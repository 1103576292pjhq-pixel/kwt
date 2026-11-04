from pathlib import Path
import subprocess
import tempfile
import unittest
HERE=Path(__file__).resolve().parents[1]

class ArbiterTests(unittest.TestCase):
    def test_two_requesters_with_random_stalls_and_response_backpressure(self):
        with tempfile.TemporaryDirectory() as folder:
            binary=Path(folder)/'arbiter.vvp'
            compile_result=subprocess.run(['iverilog','-g2012','-s','tb_arbiter','-o',str(binary),
                str(HERE/'rtl/dma/kwt_icb_arbiter2.v'),str(HERE/'tests/tb_arbiter.v')],capture_output=True,text=True)
            self.assertEqual(compile_result.returncode,0,compile_result.stderr)
            result=subprocess.run(['vvp',str(binary)],capture_output=True,text=True,timeout=30)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            self.assertIn('PASS ARBITER randomized_backpressure=1 a=100 b=100',result.stdout)

if __name__=='__main__':unittest.main()
