"""生成可手算4×16块，完整任务的其余输入补零。"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import numpy as np

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from model.fixed_numeric import ffn1_int16, load_contract
from model.layout import pack_inputs, pack_outputs


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'out/example')
    args = parser.parse_args()
    contract = load_contract(ROOT / 'model/numeric-contract.json')
    x = np.zeros((99, 64), dtype=np.int16)
    w = np.zeros((64, 256), dtype=np.int16)
    bias = np.zeros(256, dtype=np.int32)
    x[:4, 0] = np.array([4096, 8192, 12288, 16384], dtype=np.int16)
    w[0, :16] = np.arange(1, 17, dtype=np.int16) * 16
    y, flags = ffn1_int16(x, w, bias)
    payloads = {**pack_inputs(x, w, bias), **pack_outputs(y, flags)}
    args.output.mkdir(parents=True, exist_ok=True)
    for name, data in payloads.items():
        (args.output / f'{name}.bin').write_bytes(data)
    report = {
        'spec_id': contract['spec_id'], 'source': 'hand_computable_example_not_model_sample',
        'first_block': y[:4, :16].tolist(), 'outputs': int(y.size),
        'saturated': int(np.count_nonzero(flags & 2)),
        'last_records': int(np.count_nonzero(flags & 4)),
        'sha256': {name + '.bin': hashlib.sha256(data).hexdigest() for name, data in payloads.items()},
        'rtl_simulation_run': False,
    }
    (args.output / 'example.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
