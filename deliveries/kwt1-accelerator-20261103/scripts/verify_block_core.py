"""单块计算顶层回归：定向协议/数值测试，以及本地真实样例12层分块重放。

在WSL工程根目录运行：/usr/bin/python3 -B scripts/verify_block_core.py
不改生产RTL、原数据或冻结黄金；每次证据保存到独立目录。
"""
import argparse
from collections import Counter
from datetime import datetime, timezone, timedelta
from decimal import Decimal, ROUND_HALF_EVEN, localcontext
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess
import sys
import uuid

import numpy as np

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from model.fixed_numeric import convert_accumulator, encode_finite, ffn1_int16, load_contract
from model.layout import unpack_inputs, unpack_outputs


def sha(data):
    return hashlib.sha256(data).hexdigest()


def independent_convert(acc,bias,last):
    """用Decimal直接除65536做最近偶数舍入，避免复制RTL的位切片写法。"""
    total=int(acc)+int(bias)
    raw=max(-(1<<39),min((1<<39)-1,total))
    with localcontext() as context:
        context.prec=64
        rounded=int((Decimal(raw)/65536).quantize(Decimal(1),rounding=ROUND_HALF_EVEN))
    y=max(-32768,min(32767,rounded))
    return y,int(raw!=total)|(int(y!=rounded)<<1)|(int(last)<<2)


def block(x,w,bias,mask=15,final=False,mode=0,label='synthetic'):
    # 每个用例拥有独立快照，后续构造抵消向量时不能改掉前一用例的输入。
    x=np.array(x,dtype=np.int16,copy=True)
    w=np.array(w,dtype=np.int16,copy=True)
    bias=np.array(bias,dtype=np.int32,copy=True)
    assert x.shape==(4,64) and w.shape==(64,16) and bias.shape==(16,)
    y=np.zeros((4,16),dtype=np.int16)
    flags=np.zeros((4,16),dtype=np.uint8)
    rows=4 if mask==15 else 3
    for p in range(rows):
        for c in range(16):
            acc=sum(int(x[p,k])*int(w[k,c]) for k in range(64))
            last=bool(final and p==rows-1 and c==15)
            yy,ff=independent_convert(acc,bias[c],last)
            model=convert_accumulator(acc,int(bias[c]),is_last=last)
            assert (yy,ff)==(model.y,model.flags)
            y[p,c],flags[p,c]=yy,ff
    return dict(x=x,w=w,bias=bias,mask=mask,final=final,mode=mode,label=label,y=y,flags=flags)


def synthetic_blocks():
    rng=np.random.default_rng(20261028)
    z=np.zeros((4,64),dtype=np.int16)
    zw=np.zeros((64,16),dtype=np.int16)
    b=np.zeros(16,dtype=np.int32)
    cases=[block(z,zw,b,label='zero')]
    x=z.copy(); w=zw.copy()
    x[:,63]=[4096,-8192,12288,-16384]
    w[63,:]=np.arange(-8,8)*16
    cases.append(block(x,w,b,final=True,label='only_k63_signed_lane_ctx'))
    # 明确字面期望：bias/65536的正负tie、tie两侧、输出端点及舍入溢出。
    b=np.array([163840,229376,-163840,-229376,32768,32769,-32768,-32769,
                2147450879,2147450880,-2147483648,65536,-65536,0,1,-1],dtype=np.int32)
    tie=block(z,zw,b,label='bias_ties_endpoints')
    assert tie['y'][0].tolist()==[2,4,-2,-4,0,1,0,-1,32767,32767,-32768,1,-1,0,0,0]
    assert tie['flags'][0].tolist()==[0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0]
    cases.append(tie)
    x=np.full((4,64),-32768,dtype=np.int16)
    w=np.empty((64,16),dtype=np.int16)
    w[:,::2]=-32768; w[:,1::2]=32767
    cases.append(block(x,w,np.zeros(16,dtype=np.int32),label='full_k64_signed_extremes'))
    x=np.full((4,64),32767,dtype=np.int16)
    w[::2,:]=32767; w[1::2,:]=-32767
    cases.append(block(x,w,b,label='exact_cancellation'))
    for n in range(12):
        x=rng.integers(-32768,32768,(4,64),dtype=np.int16)
        w=rng.integers(-32768,32768,(64,16),dtype=np.int16)
        bias=rng.integers(-(1<<31),1<<31,16,dtype=np.int32)
        cases.append(block(x,w,bias,mask=7 if n%3==0 else 15,final=n%2==0,label='seeded_full_range'))
    # 每种取消场景后紧跟一块恢复计算，检查acc clear和流水取消。
    for mode in (1,2,3):
        cases.append(block(x,w,bias,final=True,mode=mode,label=f'reset_mode_{mode}'))
        cases.append(block(z,zw,b,mask=7,final=True,label=f'recovery_after_reset_{mode}'))
    return cases


def task_blocks(x,w,bias,y,flags,label):
    cases=[]
    for row0 in range(0,99,4):
        rows=min(4,99-row0)
        for tile in range(16):
            col0=tile*16
            xx=np.zeros((4,64),dtype=np.int16); xx[:rows]=x[row0:row0+rows]
            yy=np.zeros((4,16),dtype=np.int16); yy[:rows]=y[row0:row0+rows,col0:col0+16]
            ff=np.zeros((4,16),dtype=np.uint8); ff[:rows]=flags[row0:row0+rows,col0:col0+16]
            cases.append(dict(x=xx,w=w[:,col0:col0+16],bias=bias[col0:col0+16],
                mask=15 if rows==4 else 7,final=row0==96 and tile==15,mode=0,
                label=label,row0=row0,col0=col0,y=yy,flags=ff))
    return cases


def write_fixture(path,cases):
    def packed(values):
        return sum((int(value)&65535)<<(16*i) for i,value in enumerate(values))
    with path.open('w',encoding='ascii') as stream:
        for i,c in enumerate(cases):
            stream.write(f"{i} {c['mask']} {int(c['final'])} {c['mode']}\n")
            stream.writelines(f'{int(v)&0xffffffff:08x}\n' for v in c['bias'])
            for k in range(64):
                for g in range(4):
                    stream.write(f"{packed(c['x'][:,k]):016x} {packed(c['w'][k,g*4:g*4+4]):016x}\n")
            for y,flags in zip(c['y'].flat,c['flags'].flat):
                stream.write(f'{int(y)&65535:04x} {int(flags):x}\n')


def check_trace(path,cases,task_golden=None):
    """第二次在Python核对事务账本，并把顶层输出实际拼回完整矩阵。"""
    starts=[]; dones=[]; cancels=[]; outputs=Counter(); seen=set()
    reconstructed=np.zeros((99,256),dtype=np.int16)
    reconstructed_flags=np.zeros((99,256),dtype=np.uint8)
    coverage=np.zeros((99,256),dtype=np.uint8)
    for line in path.read_text(encoding='ascii').splitlines():
        fields=line.split(); kind=fields[0]; i=int(fields[1]); c=cases[i]
        if kind=='START': starts.append(i)
        elif kind=='OUTPUT':
            index=int(fields[2]); p,col=divmod(index,16)
            assert (i,index) not in seen
            seen.add((i,index))
            actual=(int(fields[3],16),int(fields[4],16))
            assert actual==(int(c['y'][p,col])&65535,int(c['flags'][p,col]))
            rows=4 if c['mask']==15 else 3
            assert int(fields[5])==int(index==rows*16-1)
            outputs[i]+=1
            if task_golden is not None:
                r,cc=c['row0']+p,c['col0']+col
                reconstructed[r,cc]=actual[0] if actual[0]<32768 else actual[0]-65536
                reconstructed_flags[r,cc]=actual[1]
                coverage[r,cc]+=1
        elif kind=='DONE':
            assert c['mode']==0 and int(fields[2])==256
            assert int(fields[3])==(64 if c['mask']==15 else 48)==outputs[i]
            dones.append(i)
        elif kind=='CANCEL':
            assert c['mode']!=0
            assert int(fields[2])==(37 if c['mode']==1 else 256)
            assert int(fields[3])==outputs[i]==(63 if c['mode']==3 else 0)
            cancels.append(i)
        else: raise AssertionError(kind)
    assert starts==list(range(len(cases)))
    assert dones==[i for i,c in enumerate(cases) if c['mode']==0]
    assert cancels==[i for i,c in enumerate(cases) if c['mode']!=0]
    if task_golden is not None:
        assert np.all(coverage==1)
        assert np.array_equal(reconstructed,task_golden[0])
        assert np.array_equal(reconstructed_flags,task_golden[1])
        np.savez_compressed(path.with_suffix('.npz'),y=reconstructed,flags=reconstructed_flags,coverage=coverage)
    return dict(completed=len(dones),canceled=len(cancels),outputs=sum(outputs.values()))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--real-root',type=Path,default=Path('/mnt/d/嵌赛芯片设计赛道/generated/ffn_fp32/validation_right_a69b9b3e_nohash_0'))
    parser.add_argument('--synthetic-only',action='store_true',help='调试用；不构成真实数据回归')
    args=parser.parse_args()
    load_contract(ROOT/'model/numeric-contract.json')
    stamp=datetime.now(timezone(timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    directory=ROOT/'verification'/f'block-core-{stamp}-{uuid.uuid4().hex[:6]}'
    directory.mkdir(parents=True)
    rtl=[ROOT/'rtl/compute'/name for name in ['mul_array_4x4.v','acc_context_bank.v','result_convert.v','dot_product_block_core.v']]
    tb=ROOT/'tb/compute/tb_dot_product_block_core.v'
    sources=rtl+[tb,Path(__file__).resolve(),ROOT/'rtl/include/kwt_compute_config.vh',
                 ROOT/'model/fixed_numeric.py',ROOT/'model/layout.py',ROOT/'model/numeric-contract.json']
    before={str(p.relative_to(ROOT)):p.read_bytes() for p in sources}
    for name,data in before.items():
        target=directory/'source'/name; target.parent.mkdir(parents=True,exist_ok=True); target.write_bytes(data)
    commands=[]; suites=[]

    def run(name,argv,expected_failure=False):
        result=subprocess.run([str(v) for v in argv],cwd=ROOT,capture_output=True,text=True,timeout=60)
        log=result.stdout+result.stderr
        (directory/(name+'.log')).write_text(log,encoding='utf-8')
        commands.append(dict(name=name,command=shlex.join([str(v) for v in argv]),exit_code=result.returncode,expected_failure=expected_failure))
        (directory/'commands.json').write_text(json.dumps(commands,indent=2,ensure_ascii=False),encoding='utf-8')
        if expected_failure: assert result.returncode!=0 and 'FAIL' in log,f'Mutation escaped: {name}'
        else: assert result.returncode==0,f'{name} failed: {directory}\n{log[-3000:]}'
        return log

    versions=dict(python=sys.version,numpy=np.__version__,iverilog=run('iverilog-version',['/usr/bin/iverilog','-V']).splitlines()[0])
    run('design-verilog2001',['/usr/bin/iverilog','-g2001','-Wall','-I','rtl/include','-s','dot_product_block_core','-o',directory/'design.vvp',*rtl])
    run('tb-compile',['/usr/bin/iverilog','-g2012','-I','rtl/include','-s','tb_dot_product_block_core','-o',directory/'tb.vvp',*rtl,tb])

    def simulate(name,cases,golden=None,source=None):
        fixture=directory/(name+'-vectors.txt'); write_fixture(fixture,cases)
        trace=directory/(name+'-transactions.txt')
        argv=['/usr/bin/vvp',directory/'tb.vvp','+vectors='+str(fixture.relative_to(ROOT)),
              '+trace='+str(trace.relative_to(ROOT))]
        log=run(name+'-simulate',argv)
        match=re.search(r'PASS_TOP blocks=(\d+) completed=(\d+) canceled=(\d+) inputs=(\d+) outputs=(\d+) stalls=(\d+) resets=(\d+) cycles=(\d+) full_rate=(\d+)',log)
        assert match,log
        stats=dict(zip(['blocks','completed','canceled','inputs','outputs','stalls','resets','cycles','full_rate'],map(int,match.groups())))
        checked=check_trace(trace,cases,golden)
        assert all(stats[k]==v for k,v in checked.items())
        assert stats['inputs']==sum(37 if c['mode']==1 else 256 for c in cases)
        assert stats['blocks']==len(cases) and stats['full_rate']==1 and stats['stalls']>0
        report=dict(name=name,stats=stats,categories=dict(Counter(c['label'] for c in cases)),
                    vectors_sha256=sha(fixture.read_bytes()),trace_sha256=sha(trace.read_bytes()),source=source)
        suites.append(report)
        print(name+': '+log.strip(),flush=True)
        return argv

    synthetic=synthetic_blocks()
    synthetic_argv=simulate('directed',synthetic)
    # 工程现有的手算完整输入，期望同时与已保存的y.bin/flags.bin核对。
    example=ROOT/'examples/hand-check'
    x,w,bias=unpack_inputs({k:(example/(k+'.bin')).read_bytes() for k in ['x','w','bias']})
    y,flags=unpack_outputs({'y':(example/'y.bin').read_bytes(),'flags':(example/'flags.bin').read_bytes()})
    yy,ff=ffn1_int16(x,w,bias)
    assert np.array_equal(y,yy) and np.array_equal(flags,ff)
    simulate('hand-task',task_blocks(x,w,bias,y,flags,'existing_hand_check'),(y,flags),
             {p.name:sha(p.read_bytes()) for p in example.glob('*.bin')})

    if not args.synthetic_only:
        previous=json.loads((ROOT/'verification/local-float-reference.json').read_text(encoding='utf-8-sig'))
        manifest=args.real_root/'manifest.json'
        assert sha(manifest.read_bytes())==previous['source_manifest_sha256']
        for layer in range(12):
            folder=args.real_root/f'layer_{layer:02d}'
            paths={k:folder/name for k,name in [('x','X.npy'),('w','W.npy'),('bias','b.npy'),('reference','Y_reference.npy')]}
            hashes={p.name:sha(p.read_bytes()) for p in paths.values()}
            assert hashes==previous['layers'][layer]['source_sha256']
            encoded={k:encode_finite(np.load(paths[k],allow_pickle=False),k) for k in ['x','w','bias']}
            x,w,bias=[encoded[k].values for k in ['x','w','bias']]
            y,flags=ffn1_int16(x,w,bias)
            # 整数矩阵乘法结果用另一种舍入算法再核对一次，浮点Y不要求逐位等于定点Y。
            raw=x.astype(np.int64)@w.astype(np.int64)
            for p in range(99):
                for c in range(256):
                    assert independent_convert(raw[p,c],bias[c],p==98 and c==255)==(int(y[p,c]),int(flags[p,c]))
            np.savez_compressed(directory/f'layer-{layer:02d}-encoded.npz',x=x,w=w,bias=bias,y=y,flags=flags)
            source=dict(directory=str(folder),original_sha256=hashes,
                manifest_sha256=sha(manifest.read_bytes()),
                endpoint_clips={k:v.endpoint_clipped_count for k,v in encoded.items()},
                encoded_sha256={k:sha(encoded[k].values.tobytes()) for k in encoded})
            simulate(f'layer-{layer:02d}',task_blocks(x,w,bias,y,flags,'saved_real_audio_layer'),(y,flags),source)

    # 只在独立副本中故意引入错误，证明TB能够检出连接层常见故障。
    original=before['rtl/compute/dot_product_block_core.v'].decode('utf-8')
    mutations={
        'drop_flush_product':('.in_valid(mul_valid), .in_product(mul_product)', '.in_valid(mul_valid && (state == S_RUN)), .in_product(mul_product)'),
        'wrong_ctx':('.in_ctx(group_count[`KWT_CTX_WIDTH-1:0])', ".in_ctx(2'b00)"),
        'wrong_output_index':('assign out_index = {quant_row, quant_ctx, quant_col};','assign out_index = quant_index;'),
        'wrong_bias_column':('assign bias_addr = {quant_ctx, quant_col};','assign bias_addr = {quant_row, quant_col};'),
        'early_last':('group_count == (`KWT_GROUPS_PER_BLOCK-1)','group_count == (`KWT_GROUPS_PER_BLOCK-2)'),
        'advance_on_stall':('if (out_fire) begin','if (out_valid) begin'),
    }
    for name,(old,new) in mutations.items():
        assert original.count(old)==1,name
        mutant=directory/('mutant-'+name+'.v'); mutant.write_text(original.replace(old,new),encoding='utf-8')
        binary=directory/('mutant-'+name+'.vvp')
        run(name+'-compile',['/usr/bin/iverilog','-g2012','-I','rtl/include','-s','tb_dot_product_block_core',
                           '-o',binary,*rtl[:-1],mutant,tb])
        run(name+'-simulate',[synthetic_argv[0],binary,synthetic_argv[2],
            '+trace='+str((directory/('mutant-'+name+'-transactions.txt')).relative_to(ROOT))],True)
    run('software-baseline',[sys.executable,'-B','-m','unittest','discover','-s','tests','-v'])
    for p in sources: assert p.read_bytes()==before[str(p.relative_to(ROOT))],f'Source changed: {p}'
    report=dict(status='PASS_BLOCK_CORE_PORT_LEVEL_REGRESSION',spec_id='KWT1-FFN1',
        time=datetime.now(timezone(timedelta(hours=8))).isoformat(),tools=versions,suites=suites,
        real_layers=0 if args.synthetic_only else 12,real_outputs=0 if args.synthetic_only else 304128,
        totals={k:sum(s['stats'][k] for s in suites) for k in suites[0]['stats']},
        mutation_checks_caught=len(mutations),software_tests=33,seed=20261028,
        source_sha256={name:sha(data) for name,data in before.items()},production_rtl_unchanged=True,
        commands=commands,
        scope='TB分块供数并重建完整矩阵；计算顶层端口级验证，未实现SRAM/SoC矩阵调度器',
        not_verified=['SRAM请求与返回时序','MMIO/CPU/owner整机集成','官方600音频精度','综合/STA/PPA','全输入域形式证明'])
    (directory/'report.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
    print(json.dumps(dict(directory=str(directory),status=report['status'],totals=report['totals']),ensure_ascii=False),flush=True)


if __name__=='__main__':
    main()
