import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1];sys.path.insert(0,str(HERE))


class RunnerTest(unittest.TestCase):
    def runner(self):
        path=HERE/'run_server.py';self.assertTrue(path.is_file(),'Suite server runner missing')
        spec=importlib.util.spec_from_file_location('suite_runner',path)
        m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

    def text(self):
        lines=[]
        for i in range(1,13):
            lines+=['SUITE_LOADER_DONE sequence=%d case=%d words=48323 runtime_reset=0'%(i,i),
                    'SUITE_TASK_DONE sequence=%d case=%d layer=%d writes=25344 reads=25344'%(i,i,i-1)]
        return '\n'.join(lines)+'\nTotal cycle_count value: 90000000\nThe valid Instruction Count: 44000000\nThe test ending reached at cycle: 89999983\nThe final x3 Reg value: 1\nTEST_PASS\n'

    def test_unique_ordered_twelve_windows_and_fatal_audit(self):
        m=self.runner();text=self.text();self.assertEqual(m.audit_cpu(text)['final_x3'],1)
        for extra in ['TEST_FAIL','Fatal: injected','Time Out !!!','TEST_PASS']:
            with self.assertRaises(ValueError):m.audit_cpu(text+extra)
        with self.assertRaises(ValueError):m.audit_cpu(text.replace('sequence=12 case=12 layer=11','sequence=11 case=12 layer=11'))
        with self.assertRaises(ValueError):m.audit_cpu(text.replace('words=48323','words=48322',1))

    def test_stream_preserves_log_and_failure_exit(self):
        m=self.runner()
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp);log=root/'run.log'
            code=m.stream_simulation([sys.executable,'-c','print("SUITE_TASK_DONE test-progress");print("Fatal: injected");raise SystemExit(1)'],root,log,timeout=10)
            self.assertEqual(code,1)
            self.assertIn('Fatal: injected',log.read_text())


if __name__=='__main__':unittest.main()
