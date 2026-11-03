from pathlib import Path
import hashlib
import importlib.util
import json
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1]
PROJECT=HERE.parents[2]


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod


class WiringTests(unittest.TestCase):
    def evidence(self,bundle,library):
        bundle.mkdir(exist_ok=True);library.mkdir(parents=True,exist_ok=True)
        (bundle/'package-sha256.json').write_text('{}\n')
        models=[]
        for name in ['RAMSP4096X16_rtl.v','RAMSP4096X16.v']:
            p=library/name;p.write_text('// Local metadata fixture only\n')
            models.append(dict(path=str(p),sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
        ev=bundle/'official-run-01';ev.mkdir()
        (ev/'report.json').write_text(json.dumps(dict(status='PASS_SHARED_SRAM_OFFICIAL_COMPONENTS',ema=2,emaw=0,
            official_models=models,package_manifest_sha256=hashlib.sha256((bundle/'package-sha256.json').read_bytes()).hexdigest())))

    def fixture(self,root):
        old=load(PROJECT/'integration/e203/prepare_kwt_soc.py','old_kwt_wiring')
        vendor=PROJECT/'integration/e203/tests/upstream'
        raw={key:(vendor/Path(key).name).read_bytes() for key in old.INPUTS if key!=old.ACC}
        raw[old.ACC]=(PROJECT/'rtl/kwt_accelerator.v').read_bytes()
        result=old.generate(raw)
        for rel,data in result.items():
            p=root/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)

    def tool(self):
        path=HERE/'prepare_shared_soc.py'
        self.assertTrue(path.is_file(),'Shared SoC wiring tool not implemented')
        return load(path,'shared_soc_wiring')

    def test_preview_keeps_existing_soc_and_tb(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            soc=(root/tool.SOC).read_bytes();tb=(root/tool.TB).read_bytes()
            tool.preview(root,HERE,tool.STAGE)
            self.assertEqual((root/tool.SOC).read_bytes(),soc)
            self.assertEqual((root/tool.TB).read_bytes(),tb)
            text=(root/tool.STAGE/'after'/tool.NEW).read_text()
            self.assertIn('module kwt_shared_soc_top',text)
            self.assertIn('.icb_cmd_addr(sysmem_icb_cmd_addr)',text)
            self.assertIn('u_kwt_accelerator',text)
            self.assertIn('.icb_cmd_addr(sysper_icb_cmd_addr)',text)
            self.assertIn('.clk(kwt_bus_clk)',text)

    def test_stale_source_is_rejected_before_any_apply(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            tool.preview(root,HERE,tool.STAGE)
            with (root/tool.TB).open('a') as f:f.write('// edit\n')
            with self.assertRaises(ValueError):tool.apply(root,HERE,tool.STAGE)
            self.assertFalse((root/tool.NEW).exists())

    def test_existing_target_is_preserved(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            p=root/tool.NEW;p.write_text('KEEP')
            with self.assertRaises(ValueError):tool.preview(root,HERE,tool.STAGE)
            self.assertEqual(p.read_text(),'KEEP')

    def test_apply_requires_official_component_pass(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            tool.preview(root,HERE,tool.STAGE)
            with self.assertRaises((ValueError,FileNotFoundError)):tool.apply(root,HERE,tool.STAGE)
            self.assertFalse((root/tool.NEW).exists())

    def test_apply_with_bound_component_evidence_preserves_old_top(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            bundle=Path(folder)/'bundle';self.evidence(bundle,Path(folder)/'local-library')
            before=(root/tool.SOC).read_bytes()
            tool.preview(root,bundle,tool.STAGE);tool.apply(root,bundle,tool.STAGE)
            self.assertEqual((root/tool.SOC).read_bytes(),before)
            self.assertTrue((root/tool.NEW).is_file())
            self.assertIn('kwt_shared_soc_top u_e203_soc_top',(root/tool.TB).read_text())

    def test_custom_models_used_by_preview_and_additions_are_sealed(self):
        tool=self.tool()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)/'kwt-soc';self.fixture(root)
            bundle=Path(folder)/'bundle';library=Path(folder)/'custom-library'
            self.evidence(bundle,library)
            tool.preview(root,bundle,tool.STAGE)
            additions=root/tool.STAGE/'shared_sram_additions.f'
            self.assertIn(str(library/'RAMSP4096X16.v'),additions.read_text())
            with additions.open('a') as f:f.write('/unreviewed/source.v\n')
            with self.assertRaises(ValueError):tool.apply(root,bundle,tool.STAGE)
            self.assertFalse((root/tool.NEW).exists())


if __name__=='__main__':unittest.main()
