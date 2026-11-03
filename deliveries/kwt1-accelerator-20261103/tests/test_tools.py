"""以实际命令行和独立零输入fixture检查可复现工具。"""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
RANGES = [(0x100, 0x10c), (0x120, 0x140), (0x1000, 0x4180),
          (0x5000, 0xd000), (0xd000, 0xd800)]


def zero_fixtures(root):
    """零点积输出全0、flags仅最后4；不调用待测模型来生成期望。"""
    for layer in range(1, 13):
        directory = root / f'L{layer:02d}'
        directory.mkdir(parents=True)
        header = {0x100: 99, 0x104: 256, 0x108: 1,
                  0x120: 0x100 + layer - 1, 0x124: layer, 0x128: 16,
                  0x12c: 0x1000, 0x130: 0x5000, 0x134: 0xd000,
                  0x138: 0x10000, 0x13c: 0x30000}
        lines = [f'{0xa0000000 + offset:08x} {header.get(offset, 0):08x}\n'
                 for start, stop in RANGES for offset in range(start, stop, 4)]
        (directory / 'loader.hex').write_text(''.join(lines), encoding='ascii')
        (directory / 'expected.hex').write_text('00000000\n' * 25344, encoding='ascii')
        (directory / 'flags.hex').write_text('00\n' * 25343 + '04\n', encoding='ascii')


class ToolTests(unittest.TestCase):
    def setUp(self):
        self.assertTrue((ROOT / 'scripts/run_example.py').is_file(), '例子工具尚未实现')
        self.assertTrue((ROOT / 'scripts/check_dev12.py').is_file(), 'DEV12工具尚未实现')
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.work = Path(self.temp.name)

    def invoke(self, name, *args):
        # 从项目外启动，抓住仅能在某个固定cwd运行的问题。
        return subprocess.run([sys.executable, '-B', str(ROOT / 'scripts' / name), *map(str, args)],
                              cwd=self.work, capture_output=True, text=True, encoding='utf-8')

    def fixtures(self):
        fixtures = self.work / 'fixtures'
        zero_fixtures(fixtures)
        return fixtures

    def check(self, fixtures):
        report = self.work / 'result.json'
        process = self.invoke('check_dev12.py', '--fixtures', fixtures, '--report', report)
        return process, json.loads(report.read_text(encoding='utf-8'))

    def test_example_runs_from_other_directory_and_writes_hand_checkable_block(self):
        output = self.work / 'example'
        process = self.invoke('run_example.py', '--output', output)
        self.assertEqual(process.returncode, 0, process.stderr)
        report = json.loads((output / 'example.json').read_text(encoding='utf-8'))
        self.assertEqual(report['first_block'][0], list(range(1, 17)))
        self.assertEqual(report['first_block'][3], list(range(4, 65, 4)))
        self.assertEqual((report['outputs'], report['saturated'], report['last_records']), (25344, 0, 1))
        self.assertEqual((output / 'y.bin').stat().st_size, 101376)
        self.assertEqual((output / 'flags.bin').read_bytes()[-1], 4)

    def test_dev12_recomputes_all_outputs_and_records_source_hashes(self):
        process, report = self.check(self.fixtures())
        self.assertEqual(process.returncode, 0, process.stderr)
        self.assertEqual((report['status'], report['outputs_checked'], report['flags_checked']),
                         ('PASS_SOFTWARE_MODEL_ONLY', 304128, 304128))
        self.assertEqual(sorted(case['layer'] for case in report['cases']), list(range(1, 13)))
        self.assertEqual(len(report['cases'][0]['sha256']['loader.hex']), 64)
        self.assertFalse(report['rtl_simulation_run'])
        self.assertFalse(report['official_qualification'])

    def test_dev12_refuses_changed_golden_instead_of_regenerating_it(self):
        fixtures = self.fixtures()
        golden = fixtures / 'L01/expected.hex'
        text = golden.read_text(encoding='ascii')
        golden.write_text('ffffffff\n' + text[9:], encoding='ascii')
        before = golden.read_bytes()
        process, report = self.check(fixtures)
        self.assertNotEqual(process.returncode, 0)
        self.assertEqual(report['status'], 'FAIL')
        self.assertEqual(golden.read_bytes(), before)

    def test_dev12_refuses_duplicate_loader_addresses(self):
        fixtures = self.fixtures()
        loader = fixtures / 'L01/loader.hex'
        text = loader.read_text(encoding='ascii')
        loader.write_text(text + text.splitlines()[0] + '\n', encoding='ascii')
        process, report = self.check(fixtures)
        self.assertNotEqual(process.returncode, 0)
        self.assertEqual(report['status'], 'FAIL')

    def test_dev12_refuses_out_of_range_bias_container(self):
        fixtures = self.fixtures()
        loader = fixtures / 'L01/loader.hex'
        text = loader.read_text(encoding='ascii')
        loader.write_text(text.replace('a000d004 00000000', 'a000d004 00000001'), encoding='ascii')
        process, report = self.check(fixtures)
        self.assertNotEqual(process.returncode, 0)
        self.assertEqual(report['status'], 'FAIL')

    def test_report_cannot_overwrite_frozen_fixture_files(self):
        fixtures = self.fixtures()
        golden = fixtures / 'L01/expected.hex'
        before = hashlib.sha256(golden.read_bytes()).hexdigest()
        process = self.invoke('check_dev12.py', '--fixtures', fixtures, '--report', golden)
        self.assertNotEqual(process.returncode, 0)
        self.assertEqual(hashlib.sha256(golden.read_bytes()).hexdigest(), before)


if __name__ == '__main__':
    unittest.main()
