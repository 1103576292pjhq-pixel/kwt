import importlib.util
import json
from pathlib import Path
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2]
sys.path.insert(0,str(HERE))


def load():
    path=HERE/'suite_tools.py'
    assert path.is_file(),'Continuous real suite tools missing'
    spec=importlib.util.spec_from_file_location('suite_tools',path)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod


class SuiteTest(unittest.TestCase):
    def test_all_twelve_data_identity_layout_and_audit(self):
        m=load();fixtures=ROOT/'verification/real12-20261102-02/fixtures'
        with tempfile.TemporaryDirectory() as temp:
            out=Path(temp)
            data=m.prepare_suite(fixtures,out/'data',json.loads((HERE/'fixture-identity.json').read_text()))
            self.assertEqual(len(data),12)
            self.assertEqual([d['hardware_layer'] for d in data],list(range(12)))
            self.assertIsNone(data[0]['sample']['path'])
            self.assertEqual(data[2]['sample']['source_word'],'yes')
            trace=out/'trace.txt'
            trace.write_text(''.join('Y %d %d %08x\n'%(case,i,value) for case,d in enumerate(data,1) for i,value in enumerate(d['gold'])))
            audit=m.audit_suite(trace,data,fixtures)
            self.assertEqual(audit['outputs'],304128)
            self.assertEqual(audit['bit_mismatches'],0)
            self.assertAlmostEqual(audit['max_nrmse_percent'],0.02214978,places=8)
            with trace.open('a') as f:f.write('Y 1 0 00000000\n')
            with self.assertRaises(ValueError):m.audit_suite(trace,data,fixtures)

    def test_runtime_mux_uses_bus_clock_and_keeps_declaration_order(self):
        m=load()
        sys.path.insert(0,str(ROOT/'integration/e203/real_shared_suite/tests'))
        sys.path.insert(0,str(ROOT/'integration/e203/shared_sram/tests'))
        from test_wiring import WiringTests
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp);WiringTests().fixture(root)
            path=ROOT/'integration/e203/shared_sram/prepare_shared_soc.py'
            spec=importlib.util.spec_from_file_location('shared_prepare',path)
            old=importlib.util.module_from_spec(spec);spec.loader.exec_module(old)
            current=old.candidates((root/'rtl/e203/soc/kwt_soc_top.v').read_bytes(),(root/'tb/tb_top.v').read_bytes())
            soc,tb=m.prepare_wiring(current['rtl/e203/soc/kwt_shared_soc_top.v'].decode(),current['tb/tb_top.v'].decode())
            self.assertIn('kwt_load_first ? clk : u_e203_soc_top.kwt_bus_clk',tb)
            self.assertLess(tb.index('reg  clk;'),tb.index('kwt_load_first ? clk'))
            self.assertIn('kwt_suite_loader',tb)
            self.assertIn('.reload_seq(kwt_reload_seq)',tb)
            self.assertIn('#1600000000',tb)


if __name__=='__main__':unittest.main()
