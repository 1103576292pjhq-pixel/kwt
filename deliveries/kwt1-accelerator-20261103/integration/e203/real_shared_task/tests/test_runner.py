import importlib.util
from pathlib import Path
import sys
import unittest

HERE=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(HERE))


class RunnerTest(unittest.TestCase):
    def runner(self):
        path=HERE/'run_server.py'
        self.assertTrue(path.is_file(), 'Real CPU runner not implemented')
        spec=importlib.util.spec_from_file_location('real_run',path)
        mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
        return mod

    def text(self):
        return ('REAL_LOADER_DONE writes=48320 cpu_held_in_reset=1\n'
                'REAL_SHARED_READBACK_DONE writes=25344 reads=25344\n'
                'Total cycle_count value: 9999999\nThe valid Instruction Count: 6000000\n'
                'The test ending reached at cycle: 9999982\nThe final x3 Reg value: 1\nTEST_PASS\n')

    def test_valid_and_vcs_zero_exit_failure_text(self):
        m=self.runner()
        self.assertEqual(m.audit_cpu(self.text())['final_x3'],1)
        for marker in ['TEST_FAIL','Time Out !!!','Fatal: dropped store','FATAL: timeout']:
            with self.assertRaises(ValueError):m.audit_cpu(self.text()+marker)
        with self.assertRaises(ValueError):m.audit_cpu(self.text().replace('REAL_SHARED_READBACK_DONE','ABSENT'))
        with self.assertRaises(ValueError):m.audit_cpu(self.text()+self.text())


if __name__=='__main__':unittest.main()
