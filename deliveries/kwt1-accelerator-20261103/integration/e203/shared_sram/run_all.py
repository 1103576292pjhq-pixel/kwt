#!/usr/bin/env python3
"""Run sealed single-macro then64-macro ICB tests; do not edit E203 automatically."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys


def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def save(path,data):path.write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def check_bundle(root):
    mapping=json.loads((root/'package-sha256.json').read_text(encoding='utf-8'))
    for rel,want in mapping.items():
        p=(root/rel).resolve()
        if root not in p.parents or not p.is_file() or digest(p)!=want:raise ValueError('Bundle missing/changed: '+rel)
    return mapping


def audit_shared(text,ema,emaw):
    found=re.findall(r'^PASS SHARED_SRAM (.*)$',text,re.M)
    if len(found)!=1:raise ValueError('Expected one complete shared SRAM summary')
    values={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',found[0])}
    expected=dict(words=131072,macros=64,full_sweeps=2,initialized_words=131072,
                  requests=656397,responses=656394,read_checks=393735,holds=1264,errors=3,
                  canceled=3,wait_resets=2,queued_reads=2,mask_cases=512,ema=ema,emaw=emaw,period_ns=20)
    if values!=expected:raise ValueError('Wrong full-coverage/configuration/accounting: '+str(values))
    return values


def audit_negative(text,returncode):
    # 同时兼容VCS返回0与Icarus返回1，但必须核实指定地址/数据的故意改错。
    found=re.findall(r'^FAIL SHARED_SRAM_READ addr=a0000000 actual=([0-9a-fA-F]{8}) expected=([0-9a-fA-F]{8}) err=0$',text,re.M)
    if (returncode not in (0,1) or len(found)!=1 or 'PASS SHARED_SRAM' in text or
        tuple(int(v,16) for v in found[0])!=(0x5ac36917,0x5ac36916)):
        raise ValueError('Negative control did not produce the exact injected first-read failure')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=Path('official-run-01'))
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    parser.add_argument('--ema',type=int,choices=range(8),default=2)
    parser.add_argument('--emaw',type=int,choices=range(4),default=0)
    args=parser.parse_args();root=Path(__file__).resolve().parent
    out=(root/args.output).resolve()
    if root not in out.parents or out.exists():parser.error('Use a NEW output directory inside this bundle')
    sealed=check_bundle(root);out.mkdir(parents=True,exist_ok=False)
    report=dict(status='RUNNING',package_manifest_sha256=digest(root/'package-sha256.json'),source_sha256=sealed,
                mode='ARM_UD_MODEL functional20ns',ema=args.ema,emaw=args.emaw,commands=[],
                official_macro_functional_verified=False,soc_cpu_executed=False,
                limitations=['Not150MHz STA or setup/hold closure','No CPU execution or formal real-data loading/writeback',
                             'No area/power/energy result','Shared0xa0000000 is a development address'])
    save(out/'report.json',report)
    def run(name,argv,negative=False):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            r=subprocess.run(list(map(str,argv)),cwd=out,stdout=log,stderr=subprocess.STDOUT,timeout=1800)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=r.returncode));save(out/'report.json',report)
        text=(out/(name+'.log')).read_text(encoding='utf-8',errors='replace')
        if (not negative and r.returncode!=0) or (negative and r.returncode not in (0,1)):raise RuntimeError('Unexpected exit: '+name+'; see '+str(out/(name+'.log')))
        return text
    try:
        # 单文件脚本保持原样复制到当前新输出中，保留其目录保护策略。
        single=out/'single';single.mkdir()
        entry=single/'run_sram4096_smoke.py';shutil.copy2(root/'single/run_sram4096_smoke.py',entry)
        print('STEP1_SINGLE_MACRO; EMA=%d EMAW=%d; official functional only'%(args.ema,args.emaw),flush=True)
        run('single',[sys.executable,entry,'--output','run','--sram-root',args.sram_root,
                      '--ema',args.ema,'--emaw',args.emaw])
        first=json.loads((single/'run/report.json').read_text(encoding='utf-8'))
        if first.get('status')!='PASS_SINGLE_SRAM4096_OFFICIAL_FUNCTIONAL':raise ValueError('Single macro did not qualify')
        report['single_macro_report']=str(single/'run/report.json')
        report['official_models']=first['official_models']
        models=[Path(v['path']) for v in first['official_models']]
        print('STEP1_PASS; STEP2_64_MACRO_FULL_CAPACITY_ICB',flush=True)
        sources=[root/v.strip() for v in (root/'rtl/shared_sram.f').read_text().splitlines() if v.strip()]
        run('compile-shared',['vcs','-full64','-sverilog','-timescale=1ns/1ps','+define+ARM_UD_MODEL',
            '+define+KWT_TEST_EMA='+str(args.ema),'+define+KWT_TEST_EMAW='+str(args.emaw),
            '+incdir+'+str(models[0].parent),'-top','tb_shared_sram','-Mdir='+str(out/'csrc'),'-o',out/'simv',
            *sources,root/'tb/tb_shared_sram.v',*models])
        text=run('run-shared',[out/'simv'])
        report['counts']=audit_shared(text,args.ema,args.emaw)
        negative=run('negative-shared',[out/'simv','+quick','+corrupt_first'],negative=True)
        audit_negative(negative,report['commands'][-1]['returncode'])
        check_bundle(root)
        for info in report['official_models']:
            if digest(Path(info['path']))!=info['sha256']:raise ValueError('Official model changed during run')
        report.update(status='PASS_SHARED_SRAM_OFFICIAL_COMPONENTS',official_macro_functional_verified=True,
                      negative_golden_caught=True,
                      log_sha256={name:digest(out/(name+'.log')) for name in ['single','compile-shared','run-shared','negative-shared']})
        save(out/'report.json',report)
        print(text[text.index('PASS SHARED_SRAM'):].splitlines()[0],flush=True)
        print('PASS SHARED_SRAM_OFFICIAL; single+64macros+ICB verified, CPU/STA still pending',flush=True)
        print('REPORT',out/'report.json',flush=True)
        soc_root=next((p for p in root.parents if p.name=='kwt-soc'),None)
        if soc_root is not None:
            print('NEXT wiring preview: python3 prepare_shared_soc.py preview --root '+str(soc_root),flush=True)
        else:print('NEXT see README for prepare_shared_soc.py and the existing kwt-soc root',flush=True)
        return 0
    except Exception as e:
        report.update(status='FAIL_SHARED_SRAM_COMPONENTS',error=str(e));save(out/'report.json',report)
        print('STOP:',e,flush=True);print('REPORT',out/'report.json',flush=True);return 1


if __name__=='__main__':raise SystemExit(main())
