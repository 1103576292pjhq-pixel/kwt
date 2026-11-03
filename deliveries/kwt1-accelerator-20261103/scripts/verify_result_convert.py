"""量化组件回归：独立数值期望、真实握手统计、复位取消及错误注入。"""
from collections import Counter
from datetime import datetime, timezone, timedelta
from decimal import Decimal, ROUND_HALF_EVEN, localcontext
import hashlib
import json
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import uuid

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from model.fixed_numeric import convert_accumulator, load_contract


def independent_conversion(acc,bias,last):
    """用Decimal最近偶数舍入，与RTL的绝对值/商/余数写法独立。"""
    total=acc+bias
    raw=max(-(1<<39),min((1<<39)-1,total))
    with localcontext() as context:
        context.prec=64
        rounded=int((Decimal(raw)/Decimal(65536)).quantize(Decimal(1),rounding=ROUND_HALF_EVEN))
    y=max(-32768,min(32767,rounded))
    flags=int(raw!=total) | (int(y!=rounded)<<1) | (int(last)<<2)
    return raw,rounded,y,flags


def build_vectors(hand_vectors,directory):
    rng=random.Random(20261028)
    inputs=[]
    def add(source,acc,bias,last):
        assert -(1<<39)<=acc<(1<<39) and -(1<<31)<=bias<(1<<31)
        inputs.append((source,acc,bias,bool(last)))
    for acc,bias,last,y,flags in hand_vectors:
        assert independent_conversion(acc,bias,last)[2:]==(y,flags)
        add('hand_literals',acc,bias,last)
    # 正负tie及输出端点附近的前一位/后一位；用不同bias拆分同一个raw。
    quotients=[-32769,-32768,-32767,-4,-3,-2,-1,0,1,2,3,4,32766,32767,32768,32769]
    for q in quotients:
        for remainder in [0,1,32767,32768,32769,65534,65535]:
            for bias in [-(1<<31),0,(1<<31)-1]:
                add('rounding_and_y_boundaries',q*65536+remainder-bias,bias,rng.getrandbits(1))
    for offset in [0,1,32767,32768,65535,(1<<31)-1]:
        for acc in [-(1<<39)+offset,(1<<39)-1-offset]:
            for bias in [-(1<<31),-1,0,1,(1<<31)-1]:
                add('raw40_boundaries',acc,bias,rng.getrandbits(1))
    for _ in range(4096):
        add('full_acc40_random',rng.randrange(-(1<<39),1<<39),
            rng.randrange(-(1<<31),1<<31),rng.getrandbits(1))
    for _ in range(1024):
        raw=rng.randrange(-32772,32773)*65536+rng.randrange(65536)
        bias=rng.randrange(-(1<<31),1<<31)
        add('focused_output_random',raw-bias,bias,rng.getrandbits(1))
    for _ in range(256):
        acc=sum(rng.randrange(-32768,32768)*rng.randrange(-32768,32768) for _ in range(64))
        add('legal_k64_random',acc,rng.randrange(-(1<<31),1<<31),rng.getrandbits(1))
    records=[]
    stats=Counter()
    lines=[]
    for i,(source,acc,bias,last) in enumerate(inputs):
        raw,rounded,y,flags=independent_conversion(acc,bias,last)
        model=convert_accumulator(acc,bias,is_last=last)
        assert (model.raw,model.rounded,model.y,model.flags)==(raw,rounded,y,flags)
        records.append(dict(id=i,source=source,acc=acc,bias=bias,last=last,
                            raw=raw,rounded=rounded,y=y,flags=flags))
        lines.append(f'{acc&((1<<40)-1):010x} {bias&0xffffffff:08x} {int(last)} {y&65535:04x} {flags:x}')
        stats['raw_overflow_cases']+=bool(flags&1)
        stats['y_saturation_cases']+=bool(flags&2)
        stats['ties_cases']+=(abs(raw)%65536==32768)
    (directory/'vectors.txt').write_text('\n'.join(lines)+'\n',encoding='ascii')
    (directory/'golden-vectors.jsonl').write_text(
        ''.join(json.dumps(r,ensure_ascii=False)+'\n' for r in records),encoding='utf-8')
    return records,dict(Counter(row[0] for row in inputs)),dict(stats)


def main():
    load_contract(ROOT/'model/numeric-contract.json')
    stamp=datetime.now(timezone(timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    directory=ROOT/'verification'/f'result-convert-{stamp}-{uuid.uuid4().hex[:6]}'
    directory.mkdir(parents=True,exist_ok=False)
    dut=ROOT/'rtl/compute/result_convert.v'
    tb=ROOT/'tb/compute/tb_result_convert.v'
    sources=[dut,tb,Path(__file__).resolve(),ROOT/'rtl/include/kwt_compute_config.vh',
             ROOT/'model/fixed_numeric.py',ROOT/'model/numeric-contract.json']
    before={str(p.relative_to(ROOT)):p.read_bytes() for p in sources}
    # 保留本次确切接收的用户版本及测试源码快照，不覆盖以前的结果。
    for name,data in before.items():
        target=directory/'source'/name
        target.parent.mkdir(parents=True,exist_ok=True)
        target.write_bytes(data)
    commands=[]

    def run(name,args,expected_failure=False):
        result=subprocess.run([str(x) for x in args],cwd=ROOT,capture_output=True,text=True,timeout=60)
        log=result.stdout+result.stderr
        (directory/(name+'.log')).write_text(log,encoding='utf-8')
        commands.append({'command':shlex.join([str(x) for x in args]),'exit_code':result.returncode,
                         'name':name,'expected_failure':expected_failure})
        (directory/'commands.json').write_text(json.dumps(commands,indent=2,ensure_ascii=False),encoding='utf-8')
        if expected_failure:
            assert result.returncode!=0 and 'FAIL' in log,f'Mutation escaped or failed incorrectly: {name}'
        else:
            assert result.returncode==0,f'{name} failed: {directory}'
        return log

    # 与TB手算字面期望分别核对软件黄金，避免修改黄金迎合RTL。
    vectors=[(0,0,True,0,4),(0,163840,False,2,0),(0,229376,False,4,0),
             (0,-163840,False,-2,0),(0,-229376,False,-4,0),
             (0,32768,False,0,0),(0,32769,False,1,0),
             (0,-32768,False,0,0),(0,-32769,False,-1,0),
             (0,2147450879,False,32767,0),(0,2147450880,False,32767,2),
             (0,-2147483648,False,-32768,0),(-65536,-2147483648,False,-32768,2),
             (549755813887,1,False,32767,3),(-549755813888,-1,True,-32768,7),
             (-549755813888,0,False,-32768,2)]
    for acc,bias,last,y,flags in vectors:
        actual=convert_accumulator(acc,bias,is_last=last)
        assert (actual.y,actual.flags)==(y,flags)
    (directory/'hand-vectors.json').write_text(json.dumps(vectors,indent=2),encoding='utf-8')
    records,categories,numeric_coverage=build_vectors(vectors,directory)
    versions={'python':sys.version,
              'iverilog':run('iverilog-version',['/usr/bin/iverilog','-V']).splitlines()[0],
              'vvp':run('vvp-version',['/usr/bin/vvp','-V']).splitlines()[0]}
    run('design-verilog2001',['/usr/bin/iverilog','-g2001','-I','rtl/include','-s','result_convert',
        '-o',directory/'design.vvp',dut])
    run('tb-compile',['/usr/bin/iverilog','-g2012','-I','rtl/include','-s','tb_result_convert',
        '-o',directory/'tb.vvp',dut,tb])
    def simulate_args(binary,name):
        # 用ASCII相对路径避开Icarus packed字符串处理中文路径的限制。
        return ['/usr/bin/vvp',binary,'+vectors='+str((directory/'vectors.txt').relative_to(ROOT)),
                '+trace='+str((directory/(name+'-transactions.txt')).relative_to(ROOT))]
    simulation=run('tb-simulate',simulate_args(directory/'tb.vvp','tb'))
    assert 'PASS directed_cases=16 stall_cycles=48 replacement=PASS reset=PASS' in simulation
    match=re.search(r'PASS_STREAM cycles=(\d+) accepted=(\d+) consumed=(\d+) canceled=(\d+) stalls=(\d+) replacements=(\d+)',simulation)
    assert match,'Missing stream counters'
    stream=dict(zip(['cycles','accepted','consumed','canceled','stalls','replacements'],map(int,match.groups())))
    assert stream['accepted']==len(records)==stream['consumed']+stream['canceled']
    # 独立核对事务账本：每项输入只接受一次，且只能输出一次或被复位取消一次。
    accepted_ids=[]
    output_ids=[]
    canceled_ids=[]
    for line in (directory/'tb-transactions.txt').read_text(encoding='ascii').splitlines():
        fields=line.split()
        i=int(fields[1])
        expected=records[i]
        if fields[0]=='ACCEPT':
            assert [int(v,16) for v in fields[2:4]]==[expected['acc']&((1<<40)-1),expected['bias']&0xffffffff]
            assert (int(fields[4]),int(fields[5],16),int(fields[6],16))==(int(expected['last']),expected['y']&65535,expected['flags'])
            accepted_ids.append(i)
        elif fields[0]=='OUTPUT':
            assert (int(fields[2],16),int(fields[3],16))==(expected['y']&65535,expected['flags'])
            output_ids.append(i)
        elif fields[0]=='CANCEL': canceled_ids.append(i)
        else: raise AssertionError('Unknown transaction record')
    assert accepted_ids==list(range(len(records)))
    assert output_ids==sorted(set(output_ids)) and len(output_ids)==stream['consumed']
    assert len(canceled_ids)==len(set(canceled_ids))==stream['canceled']
    assert set(output_ids).isdisjoint(canceled_ids)
    assert set(output_ids)|set(canceled_ids)==set(accepted_ids)

    original=before[str(dut.relative_to(ROOT))].decode('utf-8')
    mutations={
        'ties_away':('((remainder == HALF) && quotient[0])','(remainder == HALF)'),
        'lost_negative_sign':('-$signed(rounded_magnitude)','$signed(rounded_magnitude)'),
        'lost_raw_overflow':('assign raw_overflow = sum_ext[`KWT_ADD_WIDTH-1] ^ sum_ext[`KWT_ACC_WIDTH-1];',"assign raw_overflow = 1'b0;"),
        'no_rounding':("{1'b0, quotient} + {{QUOT_WIDTH{1'b0}}, round_up}","{1'b0, quotient}"),
        'overwrite_stalled':('end else if (in_ready) begin','end else begin'),
        'lost_global_last':('assign flags_next[`KWT_FLAG_GLOBAL_LAST_BIT] = in_global_last;',"assign flags_next[`KWT_FLAG_GLOBAL_LAST_BIT] = 1'b0;"),
        'unsigned_rounded':('wire signed [QUOT_WIDTH:0] rounded;','wire [QUOT_WIDTH:0] rounded;'),
    }
    for name,(old,new) in mutations.items():
        assert original.count(old)==1,f'Mutation anchor ambiguous: {name}'
        mutant=directory/('mutant-'+name+'.v')
        mutant.write_text(original.replace(old,new),encoding='utf-8')
        binary=directory/('mutant-'+name+'.vvp')
        run('mutant-'+name+'-compile',['/usr/bin/iverilog','-g2012','-I','rtl/include',
            '-s','tb_result_convert','-o',binary,mutant,tb])
        run('mutant-'+name+'-simulate',simulate_args(binary,'mutant-'+name),True)
    run('software-baseline',[sys.executable,'-B','-m','unittest','discover','-s','tests','-v'])
    for p in sources:
        assert p.read_bytes()==before[str(p.relative_to(ROOT))],f'Source changed: {p}'
    report={'status':'PASS_QUANTIZER_COMPONENT_REGRESSION','spec_id':'KWT1-FFN1',
            'time':datetime.now(timezone(timedelta(hours=8))).isoformat(),'tools':versions,
            'directed_cases':16,'stalled_cycles_checked':48,'same_edge_replacement':'PASS',
            'reset_cancellation':'PASS','software_tests':33,'commands':commands,
            'golden_vectors':len(records),'categories':categories,'numeric_coverage':numeric_coverage,
            'stream':stream,'mutation_checks_caught':len(mutations),'vector_seed':20261028,'handshake_seed':20261028,
            'vectors_sha256':hashlib.sha256((directory/'vectors.txt').read_bytes()).hexdigest(),
            'source_sha256':{name:hashlib.sha256(data).hexdigest() for name,data in before.items()},
            'data_source':'hand literals; boundary sweeps; seeded Python integers; Decimal ROUND_HALF_EVEN independently cross-checked with convert_accumulator',
            'not_verified':['exhaustive input-domain proof','full-compute pipeline','SRAM','STA/PPA']}
    (directory/'report.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
    print(json.dumps({'directory':str(directory),'status':report['status'],'golden_vectors':len(records),
                      'stream':stream,'mutations_caught':len(mutations)},ensure_ascii=False))


if __name__=='__main__':
    main()
