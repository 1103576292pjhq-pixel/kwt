#!/usr/bin/env python3
"""本工程独立ICB协议验证；--contract-models增加实际加速器双任务总线回归。"""
from pathlib import Path
import argparse, datetime, hashlib, json, re, subprocess, sys, uuid
from verify_controls import fixtures,CONTROL,CORE,MEMORY,MODEL
ROOT=Path(__file__).resolve().parents[1]
ICB=[Path('rtl/interface')/(n+'.v') for n in ['kwt_command_fifo','kwt_icb_regs','kwt_result_access','kwt_icb']]
TOP=Path('rtl/kwt_accelerator.v')
UNITS=[('tb_command_fifo','COMMAND_FIFO',ICB[:1]),('tb_icb_regs','ICB_REGS',ICB[1:2]),
       ('tb_result_access','RESULT_ACCESS',[ICB[2],CONTROL[2]]),('tb_icb_completion','ICB_COMPLETION',ICB[1:2])]
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--contract-models',action='store_true')
    args=parser.parse_args()
    stamp=datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=8))).strftime('%Y%m%dT%H%M%S')
    folder=ROOT/'verification'/f'icb-{stamp}-{uuid.uuid4().hex[:6]}';folder.mkdir()
    sources=[ROOT/p for p in ICB+CONTROL+CORE+MEMORY+[TOP,MODEL]]+list((ROOT/'rtl/include').glob('*.vh'))+list((ROOT/'tb/interface').glob('*.v'))+[Path(__file__),ROOT/'scripts/verify_controls.py']
    rtl_before={str(p.relative_to(ROOT)):p.read_bytes() for p in sources if p.suffix in ('.v','.vh') and 'rtl' in p.relative_to(ROOT).parts}
    report=dict(status='RUNNING',official_macro_verified=False,soc_cpu_executed=False,suites={},mutations_caught=[],source_sha256={str(p.relative_to(ROOT)):sha(p.read_bytes()) for p in sources},rtl_before_sha256={n:sha(b) for n,b in rtl_before.items()})
    for p in sources:
        dest=folder/'source'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(p.read_bytes())
    commands=[]
    def save():
        (folder/'report.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
        (folder/'commands.json').write_text(json.dumps(commands,ensure_ascii=False,indent=2),encoding='utf-8')
    def run(name,argv,fail=False):
        argv=list(map(str,argv))
        p=subprocess.run(argv,cwd=ROOT,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=1200)
        (folder/(name+'.log')).write_text(p.stdout,encoding='utf-8')
        commands.append(dict(name=name,argv=argv,returncode=p.returncode));save()
        if (p.returncode!=0)!=fail:raise RuntimeError(name+': '+p.stdout[-3000:])
        return p.stdout
    flags=['-I','rtl/include']
    try:
        report['python']=sys.version
        report['iverilog']=run('iverilog-version',['/usr/bin/iverilog','-V']).splitlines()[0]
        for top,prefix,rtl in UNITS:
            binary=folder/(top+'.vvp')
            run(top+'-design2001',['/usr/bin/iverilog','-g2001',*flags,'-s',rtl[0].stem,'-o',folder/(rtl[0].stem+'.vvp'),*rtl])
            run(top+'-compile',['/usr/bin/iverilog','-g2012',*flags,'-s',top,'-o',binary,*rtl,Path('tb/interface')/(top+'.v')])
            text=run(top+'-run',['/usr/bin/vvp',binary]);m=re.search(r'^PASS '+prefix+r' (.*)$',text,re.M)
            if not m:raise RuntimeError('Missing summary '+top)
            report['suites'][top]={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',m[1])};print(m[0],flush=True);save()
        if args.contract_models:
            golden,info=fixtures(folder/'fixtures');report['fixture_cases']=info
            rtl=ICB+CONTROL+CORE+MEMORY+[TOP,MODEL];binary=folder/'icb-system.vvp';trace=folder/'icb-trace.txt'
            run('accelerator-design2001',['/usr/bin/iverilog','-g2001',*flags,'-DKWT_STORAGE_TEST_CONTRACT','-s','kwt_accelerator','-o',folder/'design.vvp',*rtl])
            run('icb-system-compile',['/usr/bin/iverilog','-g2012',*flags,'-DKWT_STORAGE_TEST_CONTRACT','-s','tb_icb_system','-o',binary,*rtl,'tb/interface/tb_icb_system.v'])
            text=run('icb-system-run',['/usr/bin/vvp',binary,'+fixtures='+str((folder/'fixtures').relative_to(ROOT)),'+trace='+str(trace.relative_to(ROOT))])
            m=re.search(r'^PASS ICB_SYSTEM_CONTRACT (.*)$',text,re.M)
            if not m:raise RuntimeError('Missing system summary')
            report['suites']['tb_icb_system']={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',m[1])}
            seen=[set(),set()]
            for line in trace.read_text().splitlines():
                kind,case,index,value=line.split();case=int(case);index=int(index)
                if kind!='R' or index in seen[case] or int(value,16)!=golden[case+1][index]:raise RuntimeError('wrong/duplicate actual ICB result')
                seen[case].add(index)
            if [len(s) for s in seen]!=[25344,25344]:raise RuntimeError('incomplete ICB ledger')
            report['trace']=dict(outputs=[len(s) for s in seen],sha256=sha(trace.read_bytes()))
            report['fixture_sha256']={p.name:sha(p.read_bytes()) for p in (folder/'fixtures').iterdir()}
            print(m[0],flush=True);save()
        mutants=[
            ('fifo_overwrite',ICB[0],'(!valid || out_ready)','1\'b1','tb_command_fifo',ICB[:1]),
            ('regs_ignore_mask',ICB[1],"(icb_cmd_wmask != {`KWT_ICB_MASK_WIDTH{1'b1}})","1'b0",'tb_icb_regs',ICB[1:2]),
            ('result_early_retire',ICB[2],'&& rsp_ready;',';', 'tb_result_access',[ICB[2],CONTROL[2]]),
            ('completion_not_latched',ICB[1],'(completion_seen || task_done)','task_done','tb_icb_completion',ICB[1:2]),
        ]
        for name,source,old,new,top,rtl in mutants:
            original=(ROOT/source).read_text(encoding='utf-8')
            if original.count(old)<1:raise RuntimeError('Mutation anchor missing '+name)
            mutant=folder/(name+'.v');mutant.write_text(original.replace(old,new),encoding='utf-8')
            binary=folder/(name+'.vvp')
            run(name+'-compile',['/usr/bin/iverilog','-g2012',*flags,'-s',top,'-o',binary,*[mutant if p==source else p for p in rtl],Path('tb/interface')/(top+'.v')])
            text=run(name+'-run',['/usr/bin/vvp',binary],True)
            if 'FATAL:' not in text:raise RuntimeError('Mutation failed outside assertion '+name)
            report['mutations_caught'].append(name);save()
        text=run('controls-regression',['/usr/bin/python3','-B','scripts/verify_controls.py'])
        report['controls_report']=json.loads(text.splitlines()[-1]);print(text,flush=True)
        changed=[n for n,b in rtl_before.items() if (ROOT/n).read_bytes()!=b]
        if changed:raise RuntimeError('Source changed while running '+','.join(changed))
        report.update(status='PASS_ICB_AND_ACCELERATOR_CONTRACT' if args.contract_models else 'PASS_ICB_UNITS_ONLY',tested_rtl_unchanged_during_run=True)
        lines=['# 独立ICB接口与加速器验证记录','','状态：`'+report['status']+'`。','',
            '**总线发起方为自检TB，不是运行固件的E203 CPU；存储为测试合同模型，非官方宏。**','',
            '实际生产顶层kwt_accelerator连接ICB、四控制模块、既有核和存储wrapper/实体。自定义寄存器表见docs/implementation/icb-independent-design-20261031.md；不沿用交接包ABI。','',
            '| 测试 | 实测统计 |','|---|---|']
        for name,stats in report['suites'].items():lines.append('| '+name+' | '+', '.join(f'{k}={v}' for k,v in stats.items())+' |')
        lines+=['','双任务使用固定种子的稠密小数值与全signed16范围输入；Python任意精度点积+bias、独立RNE及sat16生成黄金。实际ICB响应账本二次检查每任务25344个位置无重复且值一致。另验证一次装载中止。','',
            '错误副本均先编译成功，再由TB断言检出：'+', '.join(report['mutations_caught'])+'。控制模块4独立TB、4种故障副本及33项软件基线也已重跑，通过路径见report.json。','',
            '默认20ns只是功能条件；未验证E203 CPU/完整SoC、共享RAM固件、官方SRAM模型、官方样本/性能或STA/PPA。命令、日志、数据及源码快照在本目录。']
        (folder/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8');save()
        print(json.dumps(dict(directory=str(folder),status=report['status'],official_macro_verified=False,soc_cpu_executed=False),ensure_ascii=False),flush=True)
    except Exception as e:report.update(status='FAIL_ICB_REGRESSION',error=str(e));save();raise
if __name__=='__main__':main()
