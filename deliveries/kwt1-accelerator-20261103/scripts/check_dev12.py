"""只读重算冻结DEV12输入；对照原Y/flags，不修改原始fixture。"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys

import numpy as np

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from model.fixed_numeric import ffn1_int16, load_contract
from model.layout import unpack_inputs, unpack_outputs

BASE = 0xa0000000  # 仅解析旧fixture的已知地址，不声明为官方共享基址。
RANGES = [(0x100, 0x10c), (0x120, 0x140), (0x1000, 0x4180),
          (0x5000, 0xd000), (0xd000, 0xd800)]
OFFSETS = {offset for start, stop in RANGES for offset in range(start, stop, 4)}
FILES = ('loader.hex', 'expected.hex', 'flags.hex')


def _input_images(content):
    memory = bytearray(524288)
    words = {}
    for line in content.decode('ascii').splitlines():
        fields = line.split()
        if len(fields) != 2 or any(re.fullmatch(r'[0-9a-fA-F]{8}', token) is None for token in fields):
            raise ValueError('loader records must be address32/value32 hexadecimal pairs')
        address, value = (int(token, 16) for token in fields)
        offset = address - BASE
        if offset not in OFFSETS or offset in words:
            raise ValueError('loader has a duplicate, unaligned or unexpected address')
        words[offset] = value
        memory[offset:offset + 4] = value.to_bytes(4, 'little')
    if set(words) != OFFSETS:
        raise ValueError('loader input/parameter coverage is incomplete')
    required = {0x100: 99, 0x104: 256, 0x128: 16, 0x12c: 0x1000,
                0x130: 0x5000, 0x134: 0xd000, 0x138: 0x10000, 0x13c: 0x30000}
    if any(words[key] != value for key, value in required.items()) or not 1 <= words[0x124] <= 12:
        raise ValueError('fixture descriptor geometry/scale/layout/layer mismatch')
    inputs = unpack_inputs({'x': memory[0x1000:0x4180], 'w': memory[0x5000:0xd000],
                            'bias': memory[0xd000:0xd800]})
    return inputs, words[0x124], words[0x120]


def _hex_blob(content, digits):
    lines = content.decode('ascii').splitlines()
    if len(lines) != 25344 or any(re.fullmatch('[0-9a-fA-F]{' + str(digits) + '}', line) is None
                                for line in lines):
        raise ValueError('golden item count or hexadecimal width mismatch')
    return b''.join(int(line, 16).to_bytes(digits // 2, 'little') for line in lines)


def check_dev12(fixtures):
    contract = load_contract(ROOT / 'model/numeric-contract.json')
    if not fixtures.is_dir():
        raise ValueError('fixture root is not a directory')
    directories = sorted(path for path in fixtures.iterdir() if path.is_dir())
    if len(directories) != 12:
        raise ValueError('DEV12 must contain exactly twelve case directories')
    cases = []
    for directory in directories:
        # 同一份只读字节既用于计算也用于哈希，避免来源身份与输入不一致。
        content = {name: (directory / name).read_bytes() for name in FILES}
        inputs, layer, task = _input_images(content['loader.hex'])
        expected, expected_flags = unpack_outputs({'y': _hex_blob(content['expected.hex'], 8),
                                                   'flags': _hex_blob(content['flags.hex'], 2)})
        actual, flags = ffn1_int16(*inputs)
        for label, result, golden in [('Y', actual, expected), ('flags', flags, expected_flags)]:
            different = np.argwhere(result != golden)
            if different.size:
                row, col = (int(v) for v in different[0])
                raise ValueError(f'{directory.name}: {label} mismatch at [{row},{col}]')
        cases.append({'case_id': directory.name, 'layer': layer, 'task': task,
                      'outputs_checked': 25344, 'flags_checked': 25344,
                      'sha256': {name: hashlib.sha256(data).hexdigest() for name, data in content.items()}})
    if {case['layer'] for case in cases} != set(range(1, 13)):
        raise ValueError('DEV12 does not cover each layer exactly once')
    return {
        'status': 'PASS_SOFTWARE_MODEL_ONLY', 'spec_id': contract['spec_id'],
        'fixture_root': str(fixtures), 'outputs_checked': 304128, 'flags_checked': 304128,
        'cases': cases,
        'model_sha256': {name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
                         for name in ('model/fixed_numeric.py', 'model/layout.py', 'model/numeric-contract.json')},
        'rtl_simulation_run': False, 'official_qualification': False,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fixtures', type=Path, required=True)
    parser.add_argument('--report', type=Path, default=ROOT / 'verification/dev12-compatibility.json')
    args = parser.parse_args()
    fixtures, report_path = args.fixtures.resolve(), args.report.resolve()
    if report_path.is_relative_to(fixtures):
        parser.error('report must be outside the read-only fixture root')
    try:
        report = check_dev12(fixtures)
        exit_code = 0
    except (OSError, ValueError, TypeError, ArithmeticError) as error:
        report = {'status': 'FAIL', 'error': str(error), 'rtl_simulation_run': False,
                  'official_qualification': False}
        exit_code = 1
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'status': report['status'], 'report': str(report_path)}))
    return exit_code


if __name__ == '__main__':
    raise SystemExit(main())
