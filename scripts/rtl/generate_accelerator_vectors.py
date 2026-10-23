"""独立整数参考：只生成输入和期望，不调用RTL，也不依赖第三方包。"""
import argparse
import hashlib
import json
import random
from pathlib import Path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--m', type=int, default=99)
    parser.add_argument('--n', type=int, default=256)
    parser.add_argument('--layers', type=int, default=12)
    parser.add_argument('--out', type=Path, default=Path('out/accelerator-vectors'))
    args = parser.parse_args()
    assert 1 <= args.m <= 99 and args.n % 16 == 0 and 16 <= args.n <= 256
    assert 1 <= args.layers <= 12
    rng = random.Random(20261023)
    streams = dict(x=[], w=[], bias=[], y=[], flags=[])
    for layer in range(args.layers):
        # 交替使用小数值和全范围编码，兼顾非饱和、正负饱和与偏置边界。
        scale = 32768 if layer % 2 else 2048
        x = [[rng.randrange(-scale, scale) for _ in range(64)] for _ in range(args.m)]
        w = [[rng.randrange(-scale, scale) for _ in range(args.n)] for _ in range(64)]
        bias = [rng.randrange(-(1 << 31), 1 << 31) for _ in range(args.n)]
        bias[:4] = [32768, -98304, (1 << 31)-1, -(1 << 31)]
        # 第一行固定零，直接覆盖bias的RNE tie和符号扩展。
        x[0] = [0] * 64
        streams['x'].extend(value for row in x for value in row)
        streams['w'].extend(value for row in w for value in row)
        streams['bias'].extend(bias)
        for row in range(args.m):
            for col in range(args.n):
                raw = bias[col] + sum(x[row][k] * w[k][col] for k in range(64))
                assert -(1 << 39) <= raw < (1 << 39)
                # signed floor商余数法，与RTL取幅值法不同，负数tie也正确。
                q, r = divmod(raw, 65536)
                rounded = q + (r > 32768 or (r == 32768 and q % 2 != 0))
                result = min(32767, max(-32768, rounded))
                last = row == args.m-1 and col == args.n-1
                streams['y'].append(result)
                streams['flags'].append((2 if result != rounded else 0) | (4 if last else 0))
    args.out.mkdir(parents=True, exist_ok=True)
    widths = dict(x=16, w=16, bias=32, y=32, flags=4)
    hashes = {}
    for name, values in streams.items():
        width = widths[name]
        data = ''.join(f'{value & ((1 << width)-1):0{(width+3)//4}x}\n' for value in values)
        (args.out / (name+'.hex')).write_text(data, encoding='ascii')
        hashes[name] = hashlib.sha256(data.encode('ascii')).hexdigest()
    manifest = dict(seed=20261023, m=args.m, n=args.n, layers=args.layers,
                    reference='Python exact sum + signed floor divmod RNE', sha256=hashes)
    (args.out / 'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n', encoding='utf-8')
    print(f'Generated accelerator vectors M={args.m} N={args.n} layers={args.layers}')


if __name__ == '__main__':
    main()
