"""生成V07局部计算测试向量；仅使用Python标准库，期望值不依赖RTL。"""
import hashlib
import json
import random
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'out/v07-vectors'
SEED = 20261023


def sat(value, bits):
    return max(-(1 << (bits - 1)), min((1 << (bits - 1)) - 1, value))


def convert(total, bias=0, last=False):
    raw = total + bias
    clipped = sat(raw, 48)
    # 有符号floor商余数法，与RTL的取幅值法独立。
    q, r = divmod(clipped, 65536)
    q += int(r > 32768 or (r == 32768 and q % 2 != 0))
    result = sat(q, 16)
    flags = int(raw != clipped) | (int(q != result) << 1) | (int(last) << 2)
    return result, flags


def write_hex(name, values, bits):
    text = ''.join(f'{v & ((1 << bits)-1):0{(bits+3)//4}x}\n' for v in values)
    (OUT / name).write_text(text, encoding='utf-8')
    return dict(entries=len(values), bits=bits, sha256=hashlib.sha256(text.encode()).hexdigest())


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    fixture = ROOT / 'tests/fixtures/dot64-v0.1'
    manifest = json.loads((fixture / 'manifest.json').read_text())
    cases = []
    for item in manifest['files']:
        p = fixture / item['path']
        if hashlib.sha256(p.read_bytes()).hexdigest() != item['sha256']:
            raise ValueError('固定向量校验失败：' + str(p))
        data = json.loads(p.read_text())
        cases.extend(data.get('cases', [data]))
    cases.extend([
        dict(case_id='positive_bias', x=[256]*64, w=[256]*64, bias=655360,
             accumulator_after_bias=4849664, y_integer=74),
        dict(case_id='negative_bias', x=[-256]*64, w=[256]*64, bias=655360,
             accumulator_after_bias=-3538944, y_integer=-54),
        dict(case_id='last_only', x=[0]*63+[256], w=[0]*63+[256], bias=0,
             accumulator_after_bias=65536, y_integer=1),
    ])
    rng = random.Random(SEED)
    blocks = []
    # 每个已有点积放入对应块的[0,0]，其余行列增加不同数据检查串扰。
    for i, case in enumerate(cases):
        x = [[rng.randrange(-2048, 2048) for _ in range(64)] for _ in range(4)]
        w = [[rng.randrange(-2048, 2048) for _ in range(16)] for _ in range(64)]
        b = [rng.randrange(-(1 << 25), 1 << 25) for _ in range(16)]
        x[0] = case['x'][:]
        for k in range(64):
            w[k][0] = case['w'][k]
        b[0] = case['bias']
        assert sum(x[0][k]*w[k][0] for k in range(64))+b[0] == case['accumulator_after_bias']
        assert convert(case['accumulator_after_bias'])[0] == case['y_integer']
        blocks.append((x, w, b, [15, 7, 3, 1][i % 4]))
    for mask in [15, 7, 3, 1]:
        x = [[rng.randrange(-32768, 32768) for _ in range(64)] for _ in range(4)]
        w = [[rng.randrange(-32768, 32768) for _ in range(16)] for _ in range(64)]
        b = [rng.randrange(-(1 << 31), 1 << 31) for _ in range(16)]
        blocks.append((x, w, b, mask))
    for xv, wv in [(-32768, -32768), (-32768, 32767)]:
        blocks.append(([[xv]*64 for _ in range(4)], [[wv]*16 for _ in range(64)],
                       [-(1 << 31), (1 << 31)-1]*8, 15))
    streams = {k: [] for k in ['x', 'w', 'mask', 'sum', 'bias', 'y', 'flags']}
    for index, (x, w, b, mask) in enumerate(blocks):
        streams['mask'].append(mask)
        for k in range(64):
            for g in range(4):
                streams['x'].append(sum((x[r][k] & 65535) << (r*16) for r in range(4)))
                streams['w'].append(sum((w[k][g*4+c] & 65535) << (c*16) for c in range(4)))
        streams['bias'].extend(b)
        for r in range(4):
            for c in range(16):
                acc = sum(x[r][k]*w[k][c] for k in range(64)) if mask & (1 << r) else 0
                assert -(1 << 39) <= acc+b[c] < (1 << 39)
                last = index == len(blocks)-1 and r == 3 and c == 15
                y, flags = convert(acc, b[c], last)
                streams['sum'].append(acc)
                streams['y'].append(y)
                streams['flags'].append(flags)
    files = {}
    for key, width in [('x', 64), ('w', 64), ('mask', 4), ('sum', 48),
                       ('bias', 48), ('y', 32), ('flags', 3)]:
        files[key+'.hex'] = write_hex(key+'.hex', streams[key], width)
    # 沿用180个旧转换输入，并增加物理48位边界/偏置相加场景。
    conv_root = ROOT / 'tests/fixtures/result-convert-v0.1'
    raw_inputs = [int(line, 16) for line in (conv_root/'input.hex').read_text().split()]
    cvt = [(v-(1 << 40) if v & (1 << 39) else v, 0) for v in raw_inputs]
    old_expected = [int(line, 16) for line in (conv_root/'expected.hex').read_text().split()]
    assert len(cvt) == len(old_expected) == 180
    for (a, b), encoded in zip(cvt, old_expected):
        expected = encoded-65536 if encoded & 32768 else encoded
        assert convert(a, b)[0] == expected
    cvt += [((1 << 47)-1, 1), (-(1 << 47), -1), (-(1 << 47), 0),
            (98303, 1), (-98303, -1), (0, (1 << 31)-1), (0, -(1 << 31))]
    for i in range(64):
        cvt.append((rng.randrange(-(1 << 47), 1 << 47), rng.randrange(-(1 << 31), 1 << 31)))
    for name, values, width in [
        ('cvt_sum.hex', [a for a, b in cvt], 48),
        ('cvt_bias.hex', [b for a, b in cvt], 48),
        ('cvt_y.hex', [convert(a, b, bool(i % 2))[0] for i, (a, b) in enumerate(cvt)], 32),
        ('cvt_flags.hex', [convert(a, b, bool(i % 2))[1] for i, (a, b) in enumerate(cvt)], 3),
    ]:
        files[name] = write_hex(name, values, width)
    info = dict(seed=SEED, blocks=len(blocks), converter_cases=len(cvt), files=files,
                source='30 original dot64 fixtures + 3 directed + 4 full-range random + 2 extrema blocks',
                expected='Python arbitrary-precision integers; floor divmod ties-to-even; no RTL golden')
    (OUT/'manifest.json').write_text(json.dumps(info, indent=2)+'\n')
    print(f'Generated {len(blocks)} blocks and {len(cvt)} converter cases; seed={SEED}')


if __name__ == '__main__':
    main()
