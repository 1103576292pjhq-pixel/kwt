"""将外围TB的独立golden与已有软件整数参考逐项交叉核对。需要NumPy。"""
import argparse
import importlib.util
import json
from pathlib import Path
import sys

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/model'))
from fixed_point import integer_linear


def load_hex(path, width):
    values = [int(line, 16) for line in path.read_text().split()]
    return np.array([value-(1 << width) if value & (1 << (width-1)) else value
                     for value in values], dtype=np.int64)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--vectors', type=Path, default=Path('out/accelerator-vectors'))
    parser.add_argument('--teammate-oracle', type=Path)
    args = parser.parse_args()
    config = json.loads((args.vectors / 'manifest.json').read_text())
    m, n, layers = config['m'], config['n'], config['layers']
    x = load_hex(args.vectors / 'x.hex', 16).reshape(layers, m, 64)
    w = load_hex(args.vectors / 'w.hex', 16).reshape(layers, 64, n)
    b = load_hex(args.vectors / 'bias.hex', 32).reshape(layers, n)
    y = load_hex(args.vectors / 'y.hex', 32).reshape(layers, m, n)
    flags = np.array([int(line, 16) for line in (args.vectors/'flags.hex').read_text().split()]).reshape(layers,m,n)
    teammate = None
    if args.teammate_oracle:
        spec = importlib.util.spec_from_file_location('teammate_fixed_numeric', args.teammate_oracle)
        teammate = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(teammate)
    for layer in range(layers):
        expected, _ = integer_linear(x[layer], w[layer], b[layer], 40, 16, 16, 'rne', 16)
        np.testing.assert_array_equal(y[layer], expected)
        if teammate:
            other, other_flags = teammate.ffn1_int16(x[layer].astype(np.int16),w[layer].astype(np.int16),b[layer].astype(np.int32))
            np.testing.assert_array_equal(y[layer], other)
            np.testing.assert_array_equal(flags[layer], other_flags)
    print(f'PASS: {layers*m*n} golden Y values vs fixed_point.py'
          + ('; Y/flags also match teammate fixed_numeric.py' if teammate else ''))


if __name__ == '__main__':
    main()
