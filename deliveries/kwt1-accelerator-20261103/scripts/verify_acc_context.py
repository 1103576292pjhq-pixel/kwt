"""运行累加组件自检，保存真实日志、命令、退出码和源码身份。"""
from datetime import datetime, timezone, timedelta
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess
import sys
import uuid

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from model.fixed_numeric import dot64_scalar, load_contract


def main():
    load_contract(ROOT/'model/numeric-contract.json')
    stamp = datetime.now(timezone(timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    directory = ROOT/'verification'/f'acc-context-{stamp}-{uuid.uuid4().hex[:6]}'
    directory.mkdir(parents=True, exist_ok=False)
    dut = ROOT/'rtl/compute/acc_context_bank.v'
    tb = ROOT/'tb/compute/tb_acc_context_bank.v'
    sources = [dut, tb, Path(__file__).resolve(), ROOT/'rtl/include/kwt_compute_config.vh',
               ROOT/'model/fixed_numeric.py', ROOT/'model/numeric-contract.json']
    before = {str(p.relative_to(ROOT)): p.read_bytes() for p in sources}
    commands = []

    def run(name, args, expected_failure=False):
        result = subprocess.run([str(x) for x in args], cwd=ROOT,
                                capture_output=True, text=True, timeout=60)
        log = result.stdout + result.stderr
        (directory/f'{name}.log').write_text(log, encoding='utf-8')
        commands.append({'name': name, 'command': shlex.join([str(x) for x in args]),
                         'exit_code': result.returncode, 'expected_failure': expected_failure})
        (directory/'commands.json').write_text(json.dumps(commands, indent=2, ensure_ascii=False), encoding='utf-8')
        if expected_failure:
            assert result.returncode != 0 and 'FAIL' in log, f'Mutation escaped: {name}'
        else:
            assert result.returncode == 0, f'{name} failed: see {directory}'
        return log

    versions = {'python': sys.version,
                'iverilog': run('iverilog-version', ['/usr/bin/iverilog','-V']).splitlines()[0],
                'vvp': run('vvp-version', ['/usr/bin/vvp','-V']).splitlines()[0]}
    run('design-verilog2001', ['/usr/bin/iverilog','-g2001','-I','rtl/include',
        '-s','acc_context_bank','-o',directory/'design.vvp',dut])

    def simulate(name, source, expected_failure=False):
        binary = directory/f'{name}.vvp'
        run(name+'-compile', ['/usr/bin/iverilog','-g2012','-I','rtl/include',
            '-s','tb_acc_context_bank','-o',binary,source,tb])
        return run(name+'-simulate', ['/usr/bin/vvp',binary,
            '+trace='+str((directory/(name+'-trace.txt')).relative_to(ROOT))], expected_failure)

    output = simulate('acc', dut)
    match = re.search(r'PASS cycles=(\d+) accepted_groups=(\d+) acc_read_checks=(\d+) done_pulses=(\d+)', output)
    assert match, 'Missing TB PASS counters'
    counts = dict(zip(['cycles','accepted_groups','acc_read_checks','done_pulses'], map(int,match.groups())))

    # 从保存的真实X/W激励重建4×64和64×16矩阵，独立核对全部640个最终acc。
    # 不使用TB参考数组生成Python期望，也不从RTL输出反推输入。
    def signed(bits,width):
        return bits-(1<<width) if bits & (1<<(width-1)) else bits
    matrices = {}
    results = {}
    input_rows = 0
    for line in (directory/'acc-trace.txt').read_text(encoding='ascii').splitlines():
        fields=line.split()
        if fields[0]=='INPUT':
            block,k,g=map(int,fields[1:4])
            xv,wv=int(fields[4],16),int(fields[5],16)
            x,w=matrices.setdefault(block,([[None]*64 for _ in range(4)],[[None]*16 for _ in range(64)]))
            for p in range(4):
                val=signed((xv>>(16*p))&65535,16)
                assert x[p][k] is None or x[p][k]==val
                x[p][k]=val
            for col in range(16):
                val=signed((wv>>(16*col))&65535,16)
                assert w[k][col] is None or w[k][col]==val
                w[k][col]=val
            input_rows+=1
        elif fields[0]=='RESULT':
            key=tuple(map(int,fields[1:3]))
            assert key not in results
            results[key]=signed(int(fields[3],16),40)
    assert input_rows==2560 and len(matrices)==10 and len(results)==640
    for (block,address),actual in results.items():
        x,w=matrices[block]
        ctx,p,q=address//16,(address%16)//4,address%4
        expected=dot64_scalar(x[p],[w[k][ctx*4+q] for k in range(64)],0).raw
        if block==9 and p==3: expected=0
        assert actual==expected, f'Golden mismatch block={block} address={address}: {actual} != {expected}'

    # 在副本中注入真实错误，检查TB能检出；生产RTL不做修改。
    original = before[str(dut.relative_to(ROOT))].decode('utf-8')
    mutations = {
        'zero_extend': ('{product_lane[`KWT_PRODUCT_WIDTH-1]}', "{1'b0}"),
        'wrong_context_read': ('assign write_addr = in_ctx * `KWT_MAC_LANES + LANE;', 'assign write_addr = LANE;'),
        'ignore_mask': ('if (in_row_mask[row]) begin', "if (1'b1) begin"),
        'drop_last_group': ('if (active && in_valid) begin', 'if (active && in_valid && !in_block_last) begin'),
        'ignore_active': ('if (active && in_valid) begin', 'if (in_valid) begin'),
        'incomplete_clear': ('index < `KWT_ACC_COUNT;', 'index < (`KWT_ACC_COUNT-1);'),
    }
    for name,(old,new) in mutations.items():
        assert original.count(old)==1, f'Ambiguous mutation: {name}'
        mutant=directory/f'mutant-{name}.v'
        mutant.write_text(original.replace(old,new),encoding='utf-8')
        simulate('mutant-'+name,mutant,True)

    # 独立手算常量同时核对冻结软件黄金，bias=0，所以raw等于点积和。
    anchors = [([-32768]*64,[-32768]*64,68719476736),
               ([-32768]*64,[32767]*64,-68717379584),
               ([32767]*32+[-32767]*32,[-32768]*64,0),
               ([0]*63+[-4096],[0]*63+[96],-393216)]
    for x,w,expected in anchors:
        assert dot64_scalar(x,w,0).raw==expected
    run('software-baseline',[sys.executable,'-B','-m','unittest','discover','-s','tests','-v'])
    for p in sources:
        assert p.read_bytes()==before[str(p.relative_to(ROOT))], f'Source changed: {p}; rerun required'
    report={'status':'PASS_ACCUMULATOR_COMPONENT_ONLY',
            'spec_id':'KWT1-FFN1',
            'time':datetime.now(timezone(timedelta(hours=8))).isoformat(),
            'tools':versions,'counts':counts,'seed':20261028,
            'full_k64_blocks':10,'all_ctx_mask_cases':64,
            'mutations_caught':len(mutations),'software_tests':33,
            'golden_model_anchors_checked':len(anchors),
            'golden_final_accumulators_checked':len(results),
            'input_trace_rows':input_rows,
            'trace_sha256':hashlib.sha256((directory/'acc-trace.txt').read_bytes()).hexdigest(),
            'data_source':'hand literals; signed16 products; Icarus $random(seed=20261028)',
            'source_sha256':{name:hashlib.sha256(data).hexdigest() for name,data in before.items()},
            'commands':commands,
            'not_verified':['multiplier-to-accumulator connection','bias/quantization RTL','SRAM','full matrix','STA/PPA']}
    (directory/'report.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
    print(json.dumps({'directory':str(directory),'status':report['status'],'counts':counts,
                      'mutations_caught':len(mutations)},ensure_ascii=False))


if __name__=='__main__':
    main()
