from pathlib import Path
import json
import shutil
import tempfile
import unittest
import sys

HERE=Path(__file__).resolve().parents[1]
ROOT=HERE.parents[2]
sys.path.insert(0,str(HERE))
from rtl_overlay import prepare_overlay
from server_wiring import prepare_wiring
from real_tools import sha
from throughput_tools import validate_baseline,BASELINE_IMAGE,BASELINE_CYCLES
from source_fixture import fixture

class ServerSetupTests(unittest.TestCase):
    def test_declarations_are_outside_license_comment(self):
        from prepare_soc import convert
        license_text='/* Copyright. Licensed under Apache (the "License");\n*/\n'
        result=convert(license_text+fixture())
        self.assertTrue(result.startswith(license_text))
        start=result.index('module kwt_dma_soc_top(')
        header_end=result.index(');',start)+2
        self.assertGreater(result.index('wire [31:0] kwt_dma_shared_cmd_addr;'),header_end)
        self.assertLess(result.index('wire [31:0] kwt_dma_shared_cmd_addr;'),result.index('u_kwt_accelerator('))

    def setup_tree(self,temp):
        root=temp/'kwt-soc';root.mkdir()
        original=json.loads((HERE/'baseline-rtl-sha256.json').read_text())
        for name in original:
            target=root/'accelerator'/name;target.parent.mkdir(parents=True,exist_ok=True)
            shutil.copyfile(ROOT/name,target)
        (root/'tb').mkdir();(root/'tb/tb_top.v').write_text('module tb_top; endmodule\n')
        (root/'rtl/e203/soc').mkdir(parents=True)
        top=root/'rtl/e203/soc/kwt_shared_soc_top.v';top.write_text(fixture())
        base=root/'soc.f'
        base.write_text('tb/tb_top.v\n-f acc.f\n+incdir+accelerator/rtl/include\n')
        (root/'acc.f').write_text('\n'.join('accelerator/'+n for n in original if n.endswith('.v'))+'\n')
        extra=root/'extra.f';extra.write_text(str(top)+'\n+define+ARM_UD_MODEL\n')
        return root,base,extra

    def test_overlay_selects_dma_top_and_discards_legacy_interface_modules(self):
        with tempfile.TemporaryDirectory() as temp:
            root,base,extra=self.setup_tree(Path(temp))
            before={str(p):sha(p) for p in root.rglob('*') if p.is_file()}
            report=prepare_overlay(root,HERE,base,extra,root/'output')
            selected=report['base_lines']+report['extra_lines']
            files=[Path(line) for line in selected if not line.startswith('+')]
            self.assertEqual(len(report['mapping']),15)
            self.assertEqual(sum(p.name=='kwt_dma_accelerator.v' for p in files),1)
            self.assertEqual(sum(p.name=='kwt_dma_engine.v' for p in files),1)
            self.assertFalse(any(p.name in ['kwt_accelerator.v','kwt_icb.v','kwt_shared_soc_top.v'] for p in files))
            self.assertEqual(sum(p.suffix=='.v' and 'dma' in p.parts for p in files),6)
            self.assertEqual(before,{str(p):sha(p) for p in root.rglob('*') if p.is_file()})

    def test_wrong_baseline_and_duplicate_source_are_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            root,base,extra=self.setup_tree(Path(temp))
            report=dict(status='PASS_E203_THROUGHPUT_ICB',firmware_sha256=BASELINE_IMAGE,
                timing=dict(cycles=BASELINE_CYCLES),audit=dict(outputs=25344,bit_mismatches=0),
                input_sha256={str(base):sha(base)})
            self.assertTrue(validate_baseline(report,root))
            report['timing']['cycles']=2799866
            with self.assertRaises(ValueError):validate_baseline(report,root)
            with base.open('a') as file:file.write('accelerator/rtl/kwt_accelerator.v\n')
            with self.assertRaises(ValueError):prepare_overlay(root,HERE,base,extra,root/'output')

    def test_loader_adaptation_preserves_cpu_side_of_arbiter(self):
        tb='module tb_top;\nreg clk;\nreg rst_n;\ninitial begin #120 rst_n <=1;end\ninitial begin #40000000;$finish;end\nkwt_shared_soc_top u_e203_soc_top();\nendmodule\n'
        soc,tb=prepare_wiring(fixture(),tb)
        import re
        for name in re.findall(r'wire (?:\[\d+:\d+\] )?(kwt_dma_(?:mem|shared)_\w+);',soc):
            declaration=re.search(r'wire (?:\[\d+:\d+\] )?'+name+r';',soc)
            self.assertEqual(re.search(r'\b'+name+r'\b',soc).start(),declaration.end()-len(name)-1)
        self.assertIn('.a_rsp_valid(sysmem_icb_rsp_valid)',soc)
        self.assertIn('assign kwt_dma_shared_rsp_valid = !kwt_load_mode',soc)
        self.assertNotIn('assign sysmem_icb_rsp_valid =',soc)
        self.assertIn('u_e203_soc_top.kwt_dma_shared_cmd_valid',tb)
        with self.assertRaises(ValueError):prepare_wiring(soc,tb)

if __name__=='__main__':unittest.main()
