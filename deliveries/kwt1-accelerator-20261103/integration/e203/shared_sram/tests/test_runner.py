from pathlib import Path
import importlib.util
import json
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1]


class RunnerTests(unittest.TestCase):
    def test_negative_vcs_zero_requires_exact_injected_failure(self):
        m=self.tool();check=getattr(m,'audit_negative',None)
        self.assertTrue(callable(check),'VCS zero-exit negative-result audit is not implemented')
        text='FAIL SHARED_SRAM_READ addr=a0000000 actual=5ac36917 expected=5ac36916 err=0\nFatal: deliberate golden mismatch\n'
        for code in [0,1]:check(text,code)
        for bad,code in [('Fatal: unrelated failure\n',0),(text+'PASS SHARED_SRAM\n',0),
                         (text.replace('5ac36916','5ac36917'),0),(text.replace('5ac36917','xxxxxxxx'),1),(text,-11)]:
            with self.assertRaises(ValueError):check(bad,code)

    def tool(self):
        p=HERE/'run_all.py';self.assertTrue(p.is_file(),'Bundle runner not implemented')
        spec=importlib.util.spec_from_file_location('shared_bundle_runner',p)
        m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

    def test_audit_requires_complete_counts_and_no_duplicate_pass(self):
        m=self.tool()
        good='PASS SHARED_SRAM words=131072 macros=64 full_sweeps=2 initialized_words=131072 requests=656397 responses=656394 read_checks=393735 holds=1264 errors=3 canceled=3 wait_resets=2 queued_reads=2 mask_cases=512 ema=2 emaw=0 period_ns=20\n'
        self.assertEqual(m.audit_shared(good,2,0)['read_checks'],393735)
        for text in [good+good,good.replace('full_sweeps=2','full_sweeps=0'),
                     good.replace('responses=656394','responses=656397'),good.replace('ema=2','ema=0')]:
            with self.assertRaises(ValueError):m.audit_shared(text,2,0)

    def test_existing_output_not_overwritten(self):
        self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);shutil.copy2(HERE/'run_all.py',root/'run_all.py')
            (root/'package-sha256.json').write_text('{}\n')
            out=root/'official-run-01';out.mkdir();(out/'report.json').write_text('KEEP')
            run=subprocess.run([sys.executable,'-B',str(root/'run_all.py')],capture_output=True,text=True)
            self.assertNotEqual(run.returncode,0)
            self.assertEqual((out/'report.json').read_text(),'KEEP')


if __name__=='__main__':unittest.main()
