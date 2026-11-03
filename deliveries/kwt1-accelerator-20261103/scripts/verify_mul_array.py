"""在Ubuntu WSL运行乘法组件自检，保留向量、命令、退出码与来源身份。"""
import collections
from datetime import datetime, timezone, timedelta
import hashlib
import json
from pathlib import Path
import random
import shlex
import subprocess
import sys
import uuid

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from model.fixed_numeric import load_contract, dot64_scalar

SEED = 20261027
DUT = ROOT / 'rtl/compute/mul_array_4x4.v'
TB = ROOT / 'tb/compute/tb_mul_array_4x4.v'


def pack(values, width):
    """第0项放最低位；负数显式转成width位补码位图。"""
    return sum((value & ((1 << width) - 1)) << (i * width)
               for i, value in enumerate(values))


def generate_vectors(directory):
    rng = random.Random(SEED)
    rows, labels = [], []

    def add(label, x, w, *, valid=1, reset=1, ctx=0, mask=15, last=0):
        rows.append((reset, valid, x, w, ctx, mask, last))
        labels.append(label)

    # 手算锚点：全矩阵字面期望，及signed16的两个乘积端点。
    hand_x, hand_w = [1, 2, 3, 4], [5, -6, 7, -8]
    hand_expected = [5, -6, 7, -8, 10, -12, 14, -16,
                     15, -18, 21, -24, 20, -24, 28, -32]
    assert [a * b for a in hand_x for b in hand_w] == hand_expected
    assert (-32768) * (-32768) == 1073741824
    assert (-32768) * 32767 == -1073709056
    # 与既有标量黄金核对交接文档中的k63例子；不从Y反推全部乘积。
    anchor = dot64_scalar([0] * 63 + [-4096], [0] * 63 + [96], 0)
    assert (anchor.raw, anchor.y, anchor.flags) == (-393216, -6, 0)

    add('initial_reset', None, None, reset=0, valid=1, ctx=3, mask=7, last=1)
    add('initial_bubble', None, None, valid=0, ctx=2, mask=0, last=1)
    add('zero', [0] * 4, [-32768, -1, 1, 32767])
    add('hand_mapping', hand_x, hand_w, ctx=1)
    add('signed_extremes', [-32768, 32767, -1, 0], [-32768, 32767, -1, 1], ctx=2)
    add('q28_anchor', [-4096, 1, -1, 4096], [96, -1, 1, -96], ctx=3, last=1)
    add('bubble_with_unknown_inputs', None, None, valid=0, ctx=0, mask=0)
    add('reset_after_valid', None, None, reset=0, valid=1, ctx=3, mask=15, last=1)
    add('reset_held', None, None, reset=0, valid=0)
    add('restart_after_reset', hand_x, hand_w, ctx=0, mask=7)

    # 所有ctx、所有16种mask与两种last组合；这里只检查标签透传。
    # 任意last取值是组件压力刺激，不声称外围调度会生成这些组合。
    for ctx in range(4):
        for mask in range(16):
            for last in range(2):
                add('all_tag_combinations', hand_x, hand_w, ctx=ctx, mask=mask, last=last)

    boundary = [-32768, -32767, -4096, -1, 0, 1, 96, 4096, 32766, 32767]
    # 对每个lane都覆盖10×10对边界值，防止只有lane0检查到极值。
    for i in range(10):
        for j in range(10):
            add('boundary_pairs', [boundary[(i+p) % 10] for p in range(4)],
                [boundary[(j+q) % 10] for q in range(4)], ctx=(i+j) % 4)

    # 两个紧邻的合法256组时序：k0/g0..k63/g3，不插入空拍。
    # 第一块仅k63非零；第二块随机数据且只有三行有效。
    for block in range(2):
        for k in range(64):
            x = ([-4096, 32767, -32768, -1] if k == 63 else [0]*4) if block == 0 else [rng.randrange(-32768, 32768) for _ in range(4)]
            weights = [96, -1, 32767, -32768] * 4 if block == 0 else [rng.randrange(-32768, 32768) for _ in range(16)]
            for g in range(4):
                add('two_consecutive_blocks', x, weights[4*g:4*g+4], ctx=g,
                    mask=15 if block == 0 else 7, last=int(k == 63 and g == 3))

    for i in range(4096):
        reset = int(rng.random() >= 0.025)
        valid = int(rng.random() < 0.78)
        x = [rng.randrange(-32768, 32768) for _ in range(4)] if reset and valid else None
        w = [rng.randrange(-32768, 32768) for _ in range(4)] if reset and valid else None
        add('seeded_random', x, w, reset=reset, valid=valid,
            ctx=rng.randrange(4), mask=rng.randrange(16), last=rng.randrange(2))
    # 最后一组后立刻停止有效输入，检查最后一次输出及其后的valid清除。
    add('final_valid', [-4096, 32767, -32768, -1], [96, -1, 32767, -32768], ctx=3, mask=7, last=1)
    add('final_drain', None, None, valid=0)
    add('final_drain', None, None, valid=0)

    product, known, tag = 0, False, (0, 0, 0)
    stats = collections.Counter()
    text_rows = []
    for reset, valid, x, w, ctx, mask, last in rows:
        if not reset:
            tag = (0, 0, 0)
            stats['reset_cycles'] += 1
        elif valid:
            # Python任意精度有符号整数运算，独立于RTL的位切片及乘法结果。
            product = pack([a*b for a in x for b in w], 32)
            known, tag = True, (ctx, mask, last)
            stats['accepted_groups'] += 1
            stats['accepted_last_groups'] += last
        else:
            stats['bubble_cycles'] += 1
        stats['payload_hold_checks'] += int(known and not (reset and valid))
        x_hex = f'{pack(x, 16):016x}' if x is not None else 'x'*16
        w_hex = f'{pack(w, 16):016x}' if w is not None else 'x'*16
        text_rows.append(f'{reset} {valid} {x_hex} {w_hex} {ctx:x} {mask:x} {last} '
                         f'{int(bool(reset and valid))} {int(known)} {product:0128x} '
                         f'{tag[0]:x} {tag[1]:x} {tag[2]}')
    (directory / 'vectors.txt').write_text('\n'.join(text_rows)+'\n', encoding='ascii')
    (directory / 'vector-labels.json').write_text(json.dumps(labels), encoding='utf-8')
    stats.update(cycles=len(rows), product_checks=stats['accepted_groups']*16)
    return dict(stats), dict(collections.Counter(labels))


def main():
    contract = load_contract(ROOT / 'model/numeric-contract.json')
    stamp = datetime.now(timezone(timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    directory = ROOT / 'verification' / f'mul-array-{stamp}-{uuid.uuid4().hex[:6]}'
    directory.mkdir(parents=True, exist_ok=False)
    records = []

    def run(name, args, expected_failure=False):
        result = subprocess.run([str(x) for x in args], cwd=ROOT,
                                capture_output=True, text=True, timeout=60)
        log = result.stdout + result.stderr
        (directory / f'{name}.log').write_text(log, encoding='utf-8')
        records.append({'name': name, 'command': shlex.join([str(x) for x in args]),
                        'exit_code': result.returncode, 'expected_failure': expected_failure})
        (directory/'commands.json').write_text(json.dumps(records, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')
        if expected_failure:
            assert result.returncode != 0 and 'FAIL:' in log, f'{name}: mutation escaped or wrong failure'
        else:
            assert result.returncode == 0, f'{name} failed; see {directory}'
        return log

    source = DUT.read_bytes()
    stats, categories = generate_vectors(directory)
    versions = {
        'python': sys.version,
        'iverilog': run('iverilog-version', ['/usr/bin/iverilog', '-V']).splitlines()[0],
        'vvp': run('vvp-version', ['/usr/bin/vvp', '-V']).splitlines()[0],
    }
    run('compile-verilog2001', ['/usr/bin/iverilog', '-g2001', '-I', 'rtl/include',
        '-s', 'mul_array_4x4', '-o', directory/'design-2001.vvp', DUT])

    def simulate(name, source_path, expect_fail=False):
        binary = directory/f'{name}.vvp'
        run(f'{name}-compile', ['/usr/bin/iverilog', '-g2012', '-I', 'rtl/include',
            '-s', 'tb_mul_array_4x4', '-o', binary, source_path, TB])
        return run(f'{name}-simulate', ['/usr/bin/vvp', binary,
                   # Icarus对packed字符串中的中文路径处理异常；从工程根目录
                   # 传入纯ASCII相对路径，避免损坏文件名，向量内容保持不变。
                   f'+vectors={(directory / "vectors.txt").relative_to(ROOT)}'], expect_fail)

    sim_log = simulate('rtl', DUT)
    assert f'cycles={stats["cycles"]} accepted_groups={stats["accepted_groups"]} product_checks={stats["product_checks"]}' in sim_log
    # 只修改报告目录中的副本，证明比较器会拒绝真实的数值/控制错误。
    mutations = {
        'unsigned': ('x_lane * w_lane', '$unsigned(x_lane) * $unsigned(w_lane)'),
        'wrong_w_lane': ('in_w[`KWT_W_WIDTH*q +: `KWT_W_WIDTH]', 'in_w[`KWT_W_WIDTH*(3-q) +: `KWT_W_WIDTH]'),
        'lost_last': ('out_block_last <= in_block_last;', "out_block_last <= 1'b0;"),
        'bubble_valid': ('out_valid <= in_valid;', "out_valid <= 1'b1;"),
        'reset_valid': ("out_valid      <= 1'b0;", "out_valid      <= 1'b1;"),
    }
    for name, (old, new) in mutations.items():
        original = source.decode('utf-8')
        assert original.count(old) == 1, f'mutation anchor ambiguous: {name}'
        mutant = directory/f'mutant-{name}.v'
        mutant.write_text(original.replace(old, new), encoding='utf-8')
        simulate(f'mutant-{name}', mutant, True)
    run('software-baseline', [sys.executable, '-B', '-m', 'unittest', 'discover', '-s', 'tests', '-v'])
    assert DUT.read_bytes() == source, 'DUT changed during verification; rerun required'
    files = [DUT, TB, Path(__file__).resolve(), ROOT/'rtl/include/kwt_compute_config.vh',
             ROOT/'model/numeric-contract.json', ROOT/'model/fixed_numeric.py']
    report = {
        'status': 'PASS_MULTIPLIER_COMPONENT_ONLY', 'spec_id': contract['spec_id'],
        'time': datetime.now(timezone(timedelta(hours=8))).isoformat(),
        'seed': SEED, 'tools': versions, 'counts': stats, 'categories': categories,
        'golden_source': 'hand literals and independent Python arbitrary-precision signed multiplication',
        'model_anchor': {'x63': -4096, 'w63': 96, 'raw': -393216, 'y': -6},
        'mutation_checks_caught': len(mutations), 'software_tests': 33,
        'source_sha256': {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in files},
        'vectors_sha256': hashlib.sha256((directory/'vectors.txt').read_bytes()).hexdigest(),
        'commands': records,
        'not_verified': ['accumulator', 'bias/quantization RTL', 'SRAM', 'full-matrix RTL', 'STA/PPA'],
    }
    (directory/'report.json').write_text(json.dumps(report, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')
    print(json.dumps({'report_directory': str(directory), 'status': report['status'],
                      'counts': stats, 'mutations_caught': len(mutations)}, ensure_ascii=False))


if __name__ == '__main__':
    main()
