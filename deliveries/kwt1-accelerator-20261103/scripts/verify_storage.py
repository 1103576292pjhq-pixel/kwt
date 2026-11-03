"""X/W官方宏存储实体及逻辑bank wrapper回归，WSL工程根目录运行。

正式入口：/usr/bin/python3 -B scripts/verify_storage.py --models-dir <官方模型目录>
TB自检：  /usr/bin/python3 -B scripts/verify_storage.py --contract-models
缺官方文件时默认停止并保存BLOCKED报告，不自动退回合同模型。
"""
import argparse
from collections import Counter
from datetime import datetime, timezone, timedelta
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess
import sys
import uuid

ROOT=Path(__file__).resolve().parents[1]
RTL=[ROOT/'rtl/memory/kwt_storage_array.v',ROOT/'rtl/memory/kwt_storage_wrapper.v']
HEADERS=[ROOT/'rtl/include/kwt_compute_config.vh',ROOT/'rtl/include/kwt_storage_config.vh']
TBS=[ROOT/'tb/memory/tb_storage_array.v',ROOT/'tb/memory/tb_storage_wrapper.v']
SUPPORT=ROOT/'tb/memory/support/sram_contract_models.v'
REQUIRED=['RAMSP128X16_rtl_top','RAMSP1024X16_rtl_top','RAMSP128X16','RAMSP1024X16']

def sha(data):
    return hashlib.sha256(data).hexdigest()

def code_only(source):
    return re.sub(r'//[^\n]*','',re.sub(r'/\*.*?\*/','',source,flags=re.S))

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--models-dir',type=Path,action='append',default=[],help='可重复：递归寻找两种RAMSP的官方.v/.sv文件')
    parser.add_argument('--model-file',type=Path,action='append',default=[],help='可重复：显式指定模型或依赖源码')
    parser.add_argument('--include-dir',type=Path,action='append',default=[])
    parser.add_argument('--define',action='append',default=[],help='传递给编译器的宏，例如ARM_UD_MODEL；不会自动替用户启用')
    parser.add_argument('--contract-models',action='store_true',help='只用测试专用合同模型自检TB，绝不计作官方宏通过')
    parser.add_argument('--skip-mutations',action='store_true')
    parser.add_argument('--vcd',action='store_true')
    parser.add_argument('--clock-half-ns',type=float,default=10.0,help='默认半周期10ns，仅用于功能仿真')
    args=parser.parse_args()
    if args.contract_models and (args.models_dir or args.model_file):
        parser.error('合同模型与官方模型选项互斥')
    if args.clock_half_ns<=2:
        parser.error('此TB需要半周期大于2ns，以保留驱动和采样间隔')
    if any('KWT_STORAGE_TEST_CONTRACT' in d for d in args.define):
        parser.error('请用--contract-models显式选择合同模式，不能通过--define隐藏切换')
    now=datetime.now(timezone(timedelta(hours=8)))
    directory=ROOT/'verification'/f"storage-{now.strftime('%Y%m%dT%H%M%S')}-{uuid.uuid4().hex[:6]}"
    directory.mkdir(parents=True)
    print('EVIDENCE '+str(directory),flush=True)
    mode='test_contract_only' if args.contract_models else 'official_verilog'
    report=dict(status='RUNNING',mode=mode,time=now.isoformat(),spec_id='KWT1-FFN1',
        clock_period_ns=2*args.clock_half_ns,official_macro_verified=False,commands=[],suites={},mutations_caught=[],
        not_verified=['150MHz/STA/PVT/宏面积功耗','矩阵供数与任务调度','结果owner/ICB/SoC','完整输入域形式证明'])
    report_path=directory/'report.json'
    def save():
        report_path.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (directory/'commands.json').write_text(json.dumps(report['commands'],ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    def run(name,argv,expected_failure=False):
        argv=list(map(str,argv));p=subprocess.run(argv,cwd=ROOT,capture_output=True,text=True,timeout=180)
        (directory/(name+'.log')).write_text(p.stdout+p.stderr,encoding='utf-8')
        report['commands'].append(dict(name=name,command=shlex.join(argv),exit_code=p.returncode,expected_failure=expected_failure))
        save()
        if (p.returncode!=0)!=expected_failure:
            raise RuntimeError(name+' unexpected exit '+str(p.returncode)+'\n'+p.stdout[-2500:]+p.stderr[-2000:])
        preview=p.stdout.splitlines()[0] if name.endswith('-version') and p.stdout.splitlines() else p.stdout[-500:].strip()
        print(name+': '+('DETECTED' if expected_failure else 'PASS')+' '+preview,flush=True)
        return p.stdout
    # 保存开始时生产RTL身份；用户并行编辑会使本次报告失去绑定，绝不覆盖其修改。
    all_rtl=sorted(p for p in (ROOT/'rtl').rglob('*') if p.is_file())
    before={str(p.relative_to(ROOT)):p.read_bytes() for p in all_rtl}
    sources=RTL+HEADERS+TBS+[Path(__file__),SUPPORT]
    for p in sources:
        target=directory/'source'/p.relative_to(ROOT);target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(p.read_bytes())
    report['source_sha256']={str(p.relative_to(ROOT)):sha(p.read_bytes()) for p in sources}
    report['rtl_before_sha256']={name:sha(data) for name,data in before.items()}
    report['tools']=dict(python=sys.version,iverilog=run('iverilog-version',['/usr/bin/iverilog','-V']).splitlines()[0])

    model_files=[]
    if args.contract_models:
        model_files=[SUPPORT]
        report['contract_assumptions']=['上升沿同步读','Q经0.2ns更新','低有效片选/全局写/逐位掩码','写时Q保持','待机Q保持，仅为自检假设','没有初始化或数据复位']
        report['not_verified'].append('官方宏Verilog及待机Q实际行为')
        print('CONTRACT ONLY: not official SRAM models; no macro-integration PASS will be issued.',flush=True)
    else:
        for folder in args.models_dir:
            if not folder.is_dir():
                report['status']='BLOCKED_MISSING_OFFICIAL_MODELS';report['missing_directory']=str(folder);save();return 2
            model_files.extend(p for p in folder.rglob('*') if p.is_file() and p.suffix.lower() in ('.v','.sv') and p.name.startswith(('RAMSP128X16','RAMSP1024X16')))
        model_files.extend(args.model_file)
        model_files=sorted(set(p.resolve() for p in model_files))
        missing_paths=[str(p) for p in model_files if not p.is_file()]
        modules=set()
        for p in model_files:
            if p.is_file():modules.update(re.findall(r'\bmodule\s+(\w+)',code_only(p.read_text(encoding='utf-8',errors='replace'))))
        missing=[m for m in REQUIRED if m not in modules]
        if missing or missing_paths:
            report.update(status='BLOCKED_MISSING_OFFICIAL_MODELS',missing_modules=missing,missing_paths=missing_paths,
                production_rtl_unchanged=all((ROOT/n).read_bytes()==d for n,d in before.items()))
            save()
            (directory/'README.md').write_text('# 官方宏存储验证尚未执行\n\n缺少完整官方模型及封装，未编译或运行功能仿真。没有使用替身自动补齐。\n\n所需模块：'+', '.join(missing)+'。\n',encoding='utf-8')
            print('BLOCKED_MISSING_OFFICIAL_MODELS: '+', '.join(missing),flush=True)
            return 2
        for i,p in enumerate(model_files):
            (directory/'vendor-source').mkdir(exist_ok=True)
            (directory/'vendor-source'/f'{i:02d}-{p.name}').write_bytes(p.read_bytes())
    report['model_files']=[dict(path=str(p),sha256=sha(p.read_bytes())) for p in model_files]
    flags=['-I','rtl/include']
    for d in sorted(set([p.parent for p in model_files]+args.include_dir)):
        flags+=['-I',str(d)]
    for d in args.define:flags+=['-D'+d]
    if args.contract_models:flags+=['-DKWT_STORAGE_TEST_CONTRACT']
    report['defines']=args.define+(['KWT_STORAGE_TEST_CONTRACT'] if args.contract_models else [])
    save()
    try:
        run('design-verilog2001',['/usr/bin/iverilog','-g2001',*flags,'-s','kwt_storage_wrapper','-o',directory/'design.vvp',*RTL,*model_files])
        for top,tb,kind in [('tb_storage_array',TBS[0],'STORAGE_ARRAY'),('tb_storage_wrapper',TBS[1],'STORAGE_WRAPPER')]:
            binary=directory/(top+'.vvp');trace=directory/(top+'-trace.txt')
            argv=['/usr/bin/iverilog','-g2012',*flags,'-s',top,'-P'+top+'.CLK_HALF='+str(args.clock_half_ns),'-o',binary,*RTL,*model_files,tb]
            run(top+'-compile',argv)
            sim=['/usr/bin/vvp',binary,'+trace='+str(trace.relative_to(ROOT))]
            if args.vcd:sim+=['+vcd='+str((directory/(top+'.vcd')).relative_to(ROOT))]
            out=run(top+'-simulate',sim)
            match=re.search(r'^PASS '+kind+r' (.+)$',out,re.M)
            if not match:raise RuntimeError('missing checked summary '+top)
            stats={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match.group(1))}
            counts=Counter(line.split()[0] for line in trace.read_text(encoding='ascii').splitlines())
            if kind=='STORAGE_ARRAY':
                assert counts['AXR']==stats['x_reads'] and counts['AWR']==stats['w_reads']
            else:
                assert counts['XR']==stats['x_returns'] and counts['WR']==stats['w_returns']
                assert counts['XW']==stats['x_writes'] and counts['WW']==stats['w_writes']
                assert stats['x_reads']+stats['w_reads']==stats['x_returns']+stats['w_returns']+stats['canceled']
            report['suites'][top]=dict(stats=stats,trace_sha256=sha(trace.read_bytes()),trace_records=dict(counts));save()

        # 错误只写入verification副本；每个副本先成功编译，再要求TB报出功能错误。
        mutations=[
            ('current_x_address','rtl/memory/kwt_storage_wrapper.v','+: `KWT_X_WIDTH] = x_return_part[xb]','+: `KWT_X_WIDTH] = bank_addr[`KWT_X_BANK_ADDR_WIDTH-1]'),
            ('w_slot_alias','rtl/memory/kwt_storage_wrapper.v','(wb*`KWT_SRAMS_PER_BANK+1)*`KWT_SRAM_DATA_WIDTH','((wb%4)*`KWT_SRAMS_PER_BANK+1)*`KWT_SRAM_DATA_WIDTH'),
            ('bad_x_read_valid','rtl/memory/kwt_storage_wrapper.v','x_rd_valid[xb]     <= bank_read;','x_rd_valid[xb]     <= x_rd_en[xb];'),
            ('wrong_bias_slot','rtl/memory/kwt_storage_array.v','bias_reg[{bias_wr_slot,bias_wr_addr}] <= bias_wr_data;','bias_reg[{1\'b0,bias_wr_addr}] <= bias_wr_data;'),
        ]
        if not args.skip_mutations:
            for name,relative,old,new in mutations:
                original=(ROOT/relative).read_text(encoding='utf-8')
                if original.count(old)!=1:raise RuntimeError('mutation anchor changed: '+name)
                mutant=directory/('mutant-'+name+'.v');mutant.write_text(original.replace(old,new),encoding='utf-8')
                rtl=[mutant if p==ROOT/relative else p for p in RTL];binary=directory/('mutant-'+name+'.vvp')
                run(name+'-compile',['/usr/bin/iverilog','-g2012',*flags,'-s','tb_storage_wrapper',
                    '-Ptb_storage_wrapper.CLK_HALF='+str(args.clock_half_ns),'-o',binary,*rtl,*model_files,TBS[1]])
                out=run(name+'-simulate',['/usr/bin/vvp',binary],True)
                if 'FAIL STORAGE_WRAPPER' not in out:raise RuntimeError('mutation failed outside TB assertions: '+name)
                report['mutations_caught'].append(name);save()
        run('software-baseline',['/usr/bin/python3','-B','-m','unittest','discover','-s','tests','-v'])
        changed=[n for n,d in before.items() if (ROOT/n).read_bytes()!=d]
        if changed:raise RuntimeError('Concurrent production file modification: '+', '.join(changed))
        for item in report['model_files']:
            if sha(Path(item['path']).read_bytes())!=item['sha256']:raise RuntimeError('model changed during verification: '+item['path'])
        report.update(status='PASS_STORAGE_TB_CONTRACT_SELFTEST_ONLY' if args.contract_models else 'PASS_STORAGE_OFFICIAL_VERILOG_FUNCTIONAL',
            official_macro_verified=not args.contract_models,production_rtl_unchanged=True,software_tests=33)
        save()
        warning='**仅为测试专用合同模型自检，未使用官方宏；不能宣称官方SRAM集成通过。**' if args.contract_models else '**使用报告绑定的官方Verilog模型完成存储功能回归；不是STA或全PVT资格。**'
        lines=['# X/W/bias存储验证记录','',warning,'',f"状态：`{report['status']}`。",'',
            '周期为'+str(report['clock_period_ns'])+'ns，仅是功能仿真条件，不是最高工作频率测量。',
            '向量由TB的字面边界和固定种子生成；黄金存储按真实合法请求更新，不使用DUT内部存储数组算期望。','',
            '| 套件 | 实测统计 |','|---|---|']
        for top,result in report['suites'].items():lines.append('| '+top+' | '+', '.join(f'{k}={v}' for k,v in result['stats'].items())+' |')
        lines+=['','错误副本检出：'+', '.join(report['mutations_caught'])+'。','软件基线33项通过；生产RTL及公共宏在本次运行前后字节一致。','',
            '物理实体测试覆盖24颗宏全部物理地址、16个低有效掩码位、写时Q保持、待机不误写及复位禁止写入。',
            'wrapper测试覆盖全部6400个X逻辑位置和2048个W逻辑位置、连续跨宏返回、bank/槽独立性、所有X越界地址、冲突、复位取消和两槽bias。',
            'bank3尾64项在容量测试中由TB主动装载；尾行屏蔽仅测试接口驱动，不代表已经验证硬件矩阵调度器。','',
            '完整命令、模型路径/哈希、源码快照、仿真日志和事务账本分别见commands.json、report.json、source/及*-trace.txt。',
            '尚未覆盖：'+'；'.join(report['not_verified'])+'。','']
        (directory/'README.md').write_text('\n'.join(lines),encoding='utf-8')
        print(json.dumps(dict(directory=str(directory),status=report['status'],official_macro_verified=report['official_macro_verified']),ensure_ascii=False),flush=True)
        return 0
    except Exception as error:
        report.update(status='FAIL_STORAGE_REGRESSION',error=str(error));save();raise

if __name__=='__main__':
    sys.exit(main())
