from pathlib import Path
import hashlib
import importlib.util
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1]


class ServerTests(unittest.TestCase):
    def test_changed_cannot_reuse_old_firmware_image(self):
        m=self.module();check=getattr(m,'check_firmware_sources',None)
        self.assertTrue(callable(check),'Firmware-source binding missing')
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);source=root/'task.c';source.write_text('original source')
            build=dict(sources={'task.c':hashlib.sha256(source.read_bytes()).hexdigest()})
            check(root,build);source.write_text('changed but not recompiled')
            with self.assertRaises(ValueError):check(root,build)

    def module(self):
        p=HERE/'run_server.py';self.assertTrue(p.is_file(),'Shared task server runner missing')
        spec=importlib.util.spec_from_file_location('shared_task_server',p)
        m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

    def test_timeout_copy_and_filelist_leave_original_unchanged(self):
        m=self.module()
        tb=b'module tb_top;\nkwt_shared_soc_top u_e203_soc_top();\ninitial begin #40000000; $finish;end\nendmodule\n'
        listing='rtl/e203/soc/kwt_soc_top.v\ntb/tb_top.v\n'
        changed,new_f=m.prepare_text(tb,listing,Path('/tmp/new/tb_shared_task.v'))
        self.assertIn(b'#160000000',changed);self.assertIn(b'#40000000',tb)
        self.assertIn(str(Path('/tmp/new/tb_shared_task.v')),new_f);self.assertNotIn('\ntb/tb_top.v\n',new_f)
        for bad in [tb.replace(b'kwt_shared_soc_top',b'kwt_soc_top'),tb.replace(b'#40000000',b'#12345')]:
            with self.assertRaises(ValueError):m.prepare_text(bad,listing,Path('/tmp/new.v'))
        with self.assertRaises(ValueError):m.prepare_text(tb,listing+'tb/tb_top.v\n',Path('/tmp/new.v'))

    def test_vcs_zero_exit_still_requires_positive_cpu_result(self):
        m=self.module()
        good='Total cycle_count value: 12000000\nThe valid Instruction Count: 7000000\nThe test ending reached at cycle: 11999983\nThe final x3 Reg value: 1\nTEST_PASS\n'
        self.assertEqual(m.audit_cpu(good)['total_cycles'],12000000)
        for bad in [good.replace('value: 1\n','value: 112\n'),good+'Time Out !!!\n',good+'Fatal: bad\n',good+'TEST_FAIL\n','']:
            with self.assertRaises(ValueError):m.audit_cpu(bad)


if __name__=='__main__':unittest.main()
