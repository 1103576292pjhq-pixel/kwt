#!/usr/bin/env python3
"""控制模块自检；显式--contract-models才运行测试专用存储模型联合测试。"""
from pathlib import Path
import argparse, datetime, hashlib, json, random, re, subprocess, sys, uuid

ROOT=Path(__file__).resolve().parents[1]
CONTROL=[Path('rtl/control')/(n+'.v') for n in
         ['kwt_operand_feeder','kwt_load_ctrl','kwt_result_blocks','kwt_task_ctrl']]
CORE=[Path('rtl/compute')/(n+'.v') for n in
      ['mul_array_4x4','acc_context_bank','result_convert','dot_product_block_core']]
MEMORY=[Path('rtl/memory/kwt_storage_array.v'),Path('rtl/memory/kwt_storage_wrapper.v')]
HEADERS=[Path('rtl/include')/name for name in
         ['kwt_control_config.vh','kwt_storage_config.vh','kwt_compute_config.vh']]
MODEL=Path('tb/memory/support/sram_contract_models.v')
SUITES=[('tb_operand_feeder','OPERAND_FEEDER',CONTROL[:1]),
        ('tb_load_ctrl','LOAD_CTRL',CONTROL[1:2]),
        ('tb_result_blocks','CONTROL_RESULT',CONTROL[2:3]),
        ('tb_task_ctrl','CONTROL_TASK',CONTROL[3:4])]
def sha(b):return hashlib.sha256(b).hexdigest()

def fixtures(folder):
    folder.mkdir()
    all_gold=[];info=[]
    for case in range(3):
        rng=random.Random(0x20261031+case)
        if case==0:
            x=[256*(r+1) if k==63 else 0 for r in range(99) for k in range(64)]
            w=[256*(c%64+1) if k==63 else 0 for c in range(256) for k in range(64)]
            b=[(c//16-8)*32768 for c in range(256)]
        elif case==1:
            x=[rng.randint(-4096,4095) for _ in range(6336)]
            w=[rng.randint(-2048,2047) for _ in range(16384)]
            b=[rng.randint(-(1<<25),(1<<25)-1) for _ in range(256)]
        else:
            x=[rng.randint(-32768,32767) for _ in range(6336)]
            w=[rng.randint(-32768,32767) for _ in range(16384)]
            x[:64]=[32767]*64;x[64:128]=[-32768]*64
            w[:64]=[32767]*64;w[64:128]=[-32768]*64
            b=[rng.randint(-(1<<31),(1<<31)-1) for _ in range(256)]
        y=[];ties=0;sats=0;negative=0
        for r in range(99):
            for c in range(256):
                raw=sum(x[r*64+k]*w[c*64+k] for k in range(64))+b[c]
                if not -(1<<39)<=raw<(1<<39):raise AssertionError('legal domain raw40')
                mag,rem=divmod(abs(raw),65536)
                ties+=rem==32768
                mag+=rem>32768 or (rem==32768 and mag%2==1)
                rounded=-mag if raw<0 else mag
                sat=rounded < -32768 or rounded >32767;sats+=sat
                out=max(-32768,min(32767,rounded));negative+=out<0
                flags=(int(sat)<<1) | ((r==98 and c==255)<<2)
                y.append((out&65535)|(flags<<16))
        for name,words,bits in [('x',x,16),('w',w,16),('b',b,32),('y',y,32)]:
            (folder/f'case{case}-{name}.hex').write_text(''.join(f'{v&((1<<bits)-1):0{bits//4}x}\n' for v in words),encoding='ascii')
        all_gold.append(y)
        info.append(dict(case=case,seed=0x20261031+case,outputs=len(y),ties=ties,saturated=sats,negative=negative,
                         pattern=['k63_only_row_column_tags_and_half_ties','dense_small_random_unsaturated','dense_full_signed16_and_bias32_extremes'][case]))
    (folder/'source.json').write_text(json.dumps(dict(source='本脚本确定性生成，非官方数据集/音频',layout='X row-major; W column-major; bias column; Y row-major packed flags/Y',oracle='Python arbitrary precision dot+bias, independent divmod ties-to-even and sat16',cases=info),ensure_ascii=False,indent=2),encoding='utf-8')
    return all_gold,info

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--contract-models',action='store_true')
    ap.add_argument('--skip-mutations',action='store_true')
    args=ap.parse_args()
    stamp=datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    out=ROOT/'verification'/f'controls-{stamp}-{uuid.uuid4().hex[:6]}'
    out.mkdir();commands=[]
    report=dict(status='RUNNING',official_macro_verified=False,contract_internal=args.contract_models,suites={},mutations_caught=[],not_verified=['官方SRAM模型','生产顶层/ICB/FIFO/guard/SoC','官方精度性能验收','150MHz/STA/PVT/PPA'],rtl_identity_scope='四控制模块、实际计算核、存储实体/wrapper及三份依赖头文件；未编译的ICB源码不纳入')
    # 只绑定真实被测依赖；并行开发尚未编译的ICB不能使本次控制测试假失败。
    rtl_before={str(p): (ROOT/p).read_bytes() for p in CONTROL+CORE+MEMORY+HEADERS}
    sources=[ROOT/p for p in CONTROL+CORE+MEMORY+HEADERS+[MODEL]]+list((ROOT/'tb/control').glob('*.v'))+[Path(__file__)]
    report['source_sha256']={str(p.relative_to(ROOT)):sha(p.read_bytes()) for p in sources}
    report['rtl_before_sha256']={n:sha(b) for n,b in rtl_before.items()}
    for p in sources:
        dest=out/'source'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(p.read_bytes())
    def save():
        (out/'report.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
        (out/'commands.json').write_text(json.dumps(commands,ensure_ascii=False,indent=2),encoding='utf-8')
    def run(name,argv,expected_fail=False):
        argv=list(map(str,argv))
        p=subprocess.run(argv,cwd=ROOT,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=600)
        (out/(name+'.log')).write_text(p.stdout,encoding='utf-8')
        commands.append(dict(name=name,argv=argv,returncode=p.returncode));save()
        if (p.returncode!=0)!=expected_fail:raise RuntimeError(f'{name}: unexpected exit {p.returncode}: {p.stdout[-2500:]}')
        return p.stdout
    flags=['-I','rtl/include']
    try:
        report['iverilog']=run('iverilog-version',['/usr/bin/iverilog','-V']).splitlines()[0]
        for source in CONTROL:
            run(source.stem+'-design2001',['/usr/bin/iverilog','-g2001',*flags,'-s',source.stem,'-o',out/(source.stem+'.vvp'),source])
        for top,prefix,rtl in SUITES:
            binary=out/(top+'.vvp')
            run(top+'-compile',['/usr/bin/iverilog','-g2012',*flags,'-s',top,'-o',binary,*rtl,Path('tb/control')/(top+'.v')])
            text=run(top+'-run',['/usr/bin/vvp',binary])
            m=re.search(r'^PASS '+prefix+r' (.*)$',text,re.M)
            if not m:raise RuntimeError('Missing PASS summary '+top)
            report['suites'][top]={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',m[1])};print(m[0],flush=True);save()
        if args.contract_models:
            golden,info=fixtures(out/'fixtures');report['fixture_cases']=info
            rtl=CONTROL+CORE+MEMORY+[MODEL];binary=out/'internal.vvp';trace=out/'internal-trace.txt'
            run('internal-compile',['/usr/bin/iverilog','-g2012',*flags,'-DKWT_STORAGE_TEST_CONTRACT','-s','tb_control_internal','-o',binary,*rtl,'tb/control/tb_control_internal.v'])
            text=run('internal-run',['/usr/bin/vvp',binary,'+fixtures='+str((out/'fixtures').relative_to(ROOT)),'+trace='+str(trace.relative_to(ROOT))])
            m=re.search(r'^PASS CONTROL_INTERNAL_CONTRACT (.*)$',text,re.M)
            if not m:raise RuntimeError('Missing internal PASS')
            report['suites']['tb_control_internal']={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',m[1])}
            seen=[set() for _ in range(3)];pubs=[0]*3
            for line in trace.read_text().splitlines():
                fields=line.split()
                if fields[0]=='R':
                    case,index,value=int(fields[1]),int(fields[2]),int(fields[3],16)
                    if index in seen[case] or value!=golden[case][index]:raise AssertionError('trace duplicate or wrong Y')
                    seen[case].add(index)
                elif fields[0]=='P':pubs[int(fields[1])]+=1
                else:raise AssertionError('unknown trace event')
            if any(len(s)!=25344 for s in seen) or pubs!=[400]*3:raise AssertionError('incomplete transaction trace')
            report['trace']=dict(sha256=sha(trace.read_bytes()),unique_outputs=[len(s) for s in seen],publishes=pubs)
            print(m[0],flush=True);save()
        if not args.skip_mutations:
            mutants=[
                ('feeder_wrong_w_slot',CONTROL[0],'w_rd_data[w_slot*`KWT_W_GROUP_WIDTH','w_rd_data[0*`KWT_W_GROUP_WIDTH','tb_operand_feeder',CONTROL[:1],'FAIL'),
                ('loader_wrong_x_bank',CONTROL[1],'== xb);','== ((xb+1)%4));','tb_load_ctrl',CONTROL[1:2],'FAIL'),
                ('result_cursor_on_accept',CONTROL[2],'if (rsp_retire && rsp_is_read && !rsp_error)','if (cmd_fire && !cmd_ack && read_ok)','tb_result_blocks',CONTROL[2:3],'FAIL'),
                ('task_release_every_block',CONTROL[3],'if (last_row_group) next_state = S_RELEASE;','if (1\'b1) next_state = S_RELEASE;','tb_task_ctrl',CONTROL[3:4],'FAIL'),
            ]
            for name,source,old,new,top,rtl,failprefix in mutants:
                original=(ROOT/source).read_text(encoding='utf-8')
                if original.count(old)!=1:raise RuntimeError('mutation anchor changed '+name)
                mutant=out/(name+'.v');mutant.write_text(original.replace(old,new),encoding='utf-8')
                binary=out/(name+'.vvp')
                run(name+'-compile',['/usr/bin/iverilog','-g2012',*flags,'-s',top,'-o',binary,*[mutant if p==source else p for p in rtl],Path('tb/control')/(top+'.v')])
                text=run(name+'-run',['/usr/bin/vvp',binary],True)
                if 'FATAL:' not in text:raise RuntimeError('mutant not caught by scoreboard '+name)
                report['mutations_caught'].append(name);save()
        run('software-baseline',['/usr/bin/python3','-B','-m','unittest','discover','-s','tests','-v'])
        changed=[n for n,b in rtl_before.items() if (ROOT/n).read_bytes()!=b]
        if changed:raise RuntimeError('Concurrent RTL changes: '+', '.join(changed))
        report.update(status='PASS_CONTROLS_AND_INTERNAL_CONTRACT' if args.contract_models else 'PASS_CONTROL_UNITS_ONLY',production_rtl_unchanged=True,software_tests=33)
        lines=['# 控制模块验证记录','','**内部联合使用测试专用存储模型，未验证官方SRAM、ICB或平台。**','',f"状态：`{report['status']}`。默认时钟周期20ns仅是功能条件。",'','| 测试 | 统计 |','|---|---|']
        for name,stats in report['suites'].items():lines.append('| '+name+' | '+', '.join(f'{k}={v}' for k,v in stats.items())+' |')
        lines+=['','数据来源：fixtures/source.json及本脚本固定种子，Python任意精度整数独立计算点积、RNE和sat16。非官方数据集。','联合验证实际连接四控制模块、既有点积核和当前存储wrapper/实体；测试专用模型为显式启用的sram_contract_models.v，其待机Q保持及0.2ns读延时为假设。','',
                '错误副本检出：'+', '.join(report['mutations_caught'])+'；只修改证据目录副本。上述身份范围内的被测生产RTL运行前后字节一致。','',
                '命令、日志、源码快照与SHA256见commands.json、report.json、source/。联合结果账本见internal-trace.txt；脚本再次独立检查三任务每任务25344个位置无重复、值匹配及400次发布。','',
                '未验证：'+'；'.join(report['not_verified'])+'。']
        (out/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8');save()
        print(json.dumps(dict(directory=str(out),status=report['status'],official_macro_verified=False),ensure_ascii=False),flush=True)
        return 0
    except Exception as e:
        report.update(status='FAIL_CONTROL_REGRESSION',error=str(e));save();raise
if __name__=='__main__':sys.exit(main())
