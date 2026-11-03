import importlib.util
import json
from pathlib import Path
import re
import tempfile
import unittest

HERE = Path(__file__).resolve().parents[1]
ROOT = HERE.parents[2]
FIXTURES = ROOT/'verification/real12-20261102-02/fixtures'


def tool():
    path = HERE/'real_tools.py'
    assert path.is_file(), 'Real shared-task data and wiring tools not implemented'
    spec = importlib.util.spec_from_file_location('real_tools', path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


class RealToolsTest(unittest.TestCase):
    def test_real_identity_and_column_major_conversion(self):
        m = tool()
        identity = json.loads((HERE/'fixture-identity.json').read_text())
        with tempfile.TemporaryDirectory() as temp:
            data = m.prepare_data(FIXTURES, Path(temp)/'data', identity)
            self.assertEqual(data['sample']['source_word'], 'yes')
            self.assertEqual(data['hardware_layer'], 2)
            self.assertEqual(len(data['x']), 6336)
            self.assertEqual(len(data['gold']), 25344)
            original = m.hex_words(FIXTURES/'case3-w.hex', 16384, 16)
            self.assertEqual(data['w'][0], m.sign_extend(original[0]))
            self.assertEqual(data['w'][1], m.sign_extend(original[64]))
            self.assertEqual(data['w'][256], m.sign_extend(original[1]))

    def test_changed_manifest_rejected_before_output(self):
        m = tool()
        identity = json.loads((HERE/'fixture-identity.json').read_text())
        identity['manifest_sha256'] = '0'*64
        with tempfile.TemporaryDirectory() as temp:
            out = Path(temp)/'data'
            with self.assertRaisesRegex(ValueError, 'manifest'):
                m.prepare_data(FIXTURES, out, identity)
            self.assertFalse(out.exists())

    def test_unknown_or_truncated_hex_rejected(self):
        m = tool()
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)/'x.hex'
            for value in ['xxxx\n', 'fffff\n', '0001\n']:
                path.write_text(value)
                with self.assertRaises(ValueError):
                    m.hex_words(path, 2, 16)

    def test_output_audit_rejects_duplicate_or_wrong_word(self):
        m = tool()
        gold = m.hex_words(FIXTURES/'case3-y.hex', 25344, 32)
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)/'trace.txt'
            text = ''.join('Y %d %08x\n'%(i,v) for i,v in enumerate(gold))
            path.write_text(text)
            report = m.audit_trace(path, gold, FIXTURES/'case3-ref.f32')
            self.assertEqual(report['bit_mismatches'], 0)
            self.assertLess(report['nrmse_percent'], 3)
            path.write_text(text+'Y 0 %08x\n'%gold[0])
            with self.assertRaises(ValueError): m.audit_trace(path, gold, FIXTURES/'case3-ref.f32')
            path.write_text(text.replace('Y 0 %08x'%gold[0], 'Y 0 %08x'%(gold[0]^1), 1))
            with self.assertRaises(ValueError): m.audit_trace(path, gold, FIXTURES/'case3-ref.f32')

    def test_generated_wiring_preserves_original_and_handoff(self):
        m = tool()
        import sys
        sys.path.insert(0, str(ROOT/'integration/e203/shared_sram/tests'))
        from test_wiring import WiringTests
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            helper = WiringTests()
            helper.fixture(root)
            old = importlib.util.spec_from_file_location('shared_soc', ROOT/'integration/e203/shared_sram/prepare_shared_soc.py')
            shared = importlib.util.module_from_spec(old); old.loader.exec_module(shared)
            soc = (root/'rtl/e203/soc/kwt_soc_top.v').read_bytes()
            tb = (root/'tb/tb_top.v').read_bytes()
            current = shared.candidates(soc, tb)
            oldtop = current['rtl/e203/soc/kwt_shared_soc_top.v'].decode()
            oldtb = current['tb/tb_top.v'].decode()
            top, result = m.prepare_wiring(oldtop, oldtb)
            self.assertIn('module kwt_real_soc_top(', top)
            self.assertIn('kwt_load_mode ? kwt_load_clk : kwt_bus_clk', top)
            self.assertIn('kwt_load_mode ? kwt_load_rst_n : kwt_bus_rst_n', top)
            self.assertIn('wait(kwt_load_done); #120 rst_n <=1;', result)
            self.assertIn('kwt_real_loader u_real_loader', result)
            # VCS Q-2020 rejects a clk reference before the original reg declaration.
            clock_declaration = re.search(r'\breg\s+clk\s*;', result)
            reset_declaration = re.search(r'\breg\s+rst_n\s*;', result)
            self.assertLess(clock_declaration.end(), result.index('wire kwt_load_clk = clk;'))
            self.assertLess(reset_declaration.end(), result.index('wire kwt_load_clk = clk;'))
            self.assertNotIn('kwt_load_mode', oldtop)
            with self.assertRaises(ValueError): m.prepare_wiring(oldtop, oldtb.replace('#40000000', '#123'))


if __name__ == '__main__': unittest.main()
