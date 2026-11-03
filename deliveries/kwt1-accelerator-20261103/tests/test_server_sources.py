import hashlib
import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[1]


def tool():
    path=ROOT/'tools/check_server_sources.py'
    assert path.is_file(),'Server source identity checker missing'
    spec=importlib.util.spec_from_file_location('server_identity_tool',path)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


class ServerIdentityTest(unittest.TestCase):
    def fixture(self,folder):
        root=Path(folder);repo=root/'repo';server=root/'soc';standalone=root/'standalone'
        for base,rel in [(repo,'rtl/core.v'),(server,'accelerator/rtl/core.v'),(standalone,'rtl/core.v')]:
            p=base/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_text('module core;endmodule\n')
        data=dict(files=[dict(kind='accelerator',repository_path='rtl/core.v',server_soc_path='accelerator/rtl/core.v',
                             sha256=hashlib.sha256((repo/'rtl/core.v').read_bytes()).hexdigest())],platform_files=[])
        return repo,server,standalone,data

    def test_matching_copies_pass_without_mutation(self):
        m=tool()
        with tempfile.TemporaryDirectory() as temp:
            repo,server,standalone,data=self.fixture(temp)
            result=m.verify(repo,server,data,standalone)
            self.assertEqual(result['matched_soc_files'],1)
            self.assertEqual(result['matched_standalone_files'],1)
            self.assertEqual((server/'accelerator/rtl/core.v').read_text(),'module core;endmodule\n')

    def test_mismatch_and_missing_server_sources_fail(self):
        m=tool()
        with tempfile.TemporaryDirectory() as temp:
            repo,server,standalone,data=self.fixture(temp)
            p=server/'accelerator/rtl/core.v';p.write_text('changed\n')
            with self.assertRaisesRegex(ValueError,'hash mismatch'):m.verify(repo,server,data)
            p.unlink()
            with self.assertRaisesRegex(ValueError,'missing'):m.verify(repo,server,data)

    def test_paths_outside_the_declared_root_are_rejected(self):
        m=tool()
        with tempfile.TemporaryDirectory() as temp:
            repo,server,standalone,data=self.fixture(temp)
            data['files'][0]['server_soc_path']='../outside.v'
            with self.assertRaisesRegex(ValueError,'escapes'):m.verify(repo,server,data)


if __name__=='__main__':unittest.main()
