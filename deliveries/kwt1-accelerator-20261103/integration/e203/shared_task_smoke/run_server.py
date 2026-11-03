#!/usr/bin/env python3
"""Compile isolated full shared-data task simulation; preserve all production RTL."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess


def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(p,x):p.write_text(json.dumps(x,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')


def check_firmware_sources(bundle,build):
    for rel,want in build['sources'].items():
        p=(bundle/rel).resolve()
        if bundle not in p.parents or not p.is_file() or sha(p)!=want:
            raise ValueError('Firmware source differs from compiled image: '+rel)


def prepare_text(tb_bytes,listing,new_tb):
    text=tb_bytes.decode('utf-8')
    if not re.search(r'\bkwt_shared_soc_top\s+u_e203_soc_top\s*\(',text):raise ValueError('Expected the already-connected shared-SRAM SoC')
    if len(re.findall(r'#\s*40000000\b',text))!=1:raise ValueError('Unrecognized watchdog; inspect actual server TB before changing it')
    changed=re.sub(r'#\s*40000000\b','#160000000',text).encode('utf-8')
    count=0;lines=[]
    for line in listing.splitlines():
        value=line.strip().strip('"')
        if value=='tb/tb_top.v' or value.endswith('/tb/tb_top.v'):
            lines.append(str(new_tb));count+=1
        else:lines.append(line)
    if count!=1:raise ValueError('Need exactly one original tb_top source in soc.f')
    return changed,'\n'.join(lines)+'\n'


def audit_cpu(text):
    if len(re.findall(r'\bTEST_PASS\b',text))!=1 or re.search(r'TEST_FAIL|Time\s+Out|\bFatal\b|\bFATAL\b',text):
        raise ValueError('Missing unique TEST_PASS or a failure/timeout occurred')
    patterns=dict(total_cycles=r'Total cycle_count value:\s*(\d+)',instructions=r'The valid Instruction Count:\s*(\d+)',
                  ending_cycle=r'The test ending reached at cycle:\s*(\d+)',final_x3=r'The final x3 Reg value:\s*(\d+)')
    result={}
    for key,pattern in patterns.items():
        found=re.findall(pattern,text)
        if len(found)!=1:raise ValueError('Missing/duplicate CPU result '+key)
        result[key]=int(found[0])
    if result['final_x3']!=1 or not 0<result['ending_cycle']<=result['total_cycles']<40000000:
        raise ValueError('CPU result code or cycle range invalid')
    return result


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root',type=Path,required=True)
    p.add_argument('--output',default='verification/shared_task_compile_01')
    p.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    args=p.parse_args();root=args.root.resolve();bundle=Path(__file__).resolve().parent
    out=(root/args.output).resolve()
    if root.name!='kwt-soc' or root not in out.parents or out.exists():p.error('Use existing kwt-soc and a NEW output directory inside it')
    manifest=json.loads((bundle/'package-sha256.json').read_text(encoding='utf-8'))
    for rel,want in manifest.items():
        source=(bundle/rel).resolve()
        if bundle not in source.parents or sha(source)!=want:raise ValueError('Bundle changed: '+rel)
    tb=root/'tb/tb_top.v';base_list=root/'verification/soc_compile_01/soc.f'
    extra=root/'verification/shared_sram_wiring_01/shared_sram_additions.f'
    top=root/'rtl/e203/soc/kwt_shared_soc_top.v'
    original_inputs={str(v):sha(v) for v in [tb,base_list,extra,top]}
    changed,listing=prepare_text(tb.read_bytes(),base_list.read_text(encoding='utf-8'),out/'tb_shared_task.v')
    models=[args.sram_root/part/'verilog'/name for part in ['RAMSP1024X16','RAMSP128X16']
            for name in [part+'_rtl.v',part+'.v']]
    for model in models:
        if not model.is_file():raise FileNotFoundError(model)
    # 绑定当前实际E203/加速器/共享源码与头文件，不仅记录filelist本身。
    input_paths={tb,base_list,extra,top,*models}
    for folder in [root/'rtl',root/'accelerator/rtl']:
        if not folder.is_dir():raise FileNotFoundError(folder)
        input_paths.update(p for p in folder.rglob('*') if p.is_file() and p.suffix in {'.v','.vh'})
    for line in extra.read_text(encoding='utf-8').splitlines():
        value=line.strip()
        if value and not value.startswith(('+','-','//')):
            source=Path(value)
            if not source.is_absolute():source=root/source
            if not source.is_file():raise FileNotFoundError(source)
            input_paths.add(source)
    inputs={str(v):sha(v) for v in sorted(input_paths)}
    image=bundle/'build-01/shared_task_smoke.verilog'
    build=json.loads((bundle/'build-01/build-report.json').read_text(encoding='utf-8'))
    if sha(image)!=build['image_sha256']:raise ValueError('CPU image changed')
    check_firmware_sources(bundle,build)
    out.mkdir(parents=True,exist_ok=False)
    (out/'original_tb.v').write_bytes(tb.read_bytes());(out/'tb_shared_task.v').write_bytes(changed)
    (out/'soc_shared_task.f').write_text(listing,encoding='utf-8')
    report=dict(status='RUNNING',commands=[],input_sha256=inputs,firmware_sha256=sha(image),
        package_manifest_sha256=sha(bundle/'package-sha256.json'),tb_watchdog_ns=160000000,
        original_input_sha256=original_inputs,clock_changed=False,production_rtl_changed=False,sources='Existing production accelerator +64macro shared SRAM +original E203',
        scope='Synthetic generated input with actual CPU shared load and full result writeback/checking; not official performance')
    save(out/'report.json',report)
    def run(name,argv,cwd=root):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            proc=subprocess.run(list(map(str,argv)),cwd=cwd,stdout=log,stderr=subprocess.STDOUT,timeout=7200)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=proc.returncode));save(out/'report.json',report)
        if proc.returncode:raise RuntimeError(name+' failed; see '+str(out/(name+'.log')))
        return (out/(name+'.log')).read_text(encoding='utf-8',errors='replace')
    try:
        print('COMPILING_NEW_SHARED_TASK_SOC; original TB/RTL/simv preserved',flush=True)
        run('compile',['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all','+define+FPGA+ARM_UD_MODEL',
             '+incdir+rtl/e203/core+rtl/e203/perips+rtl/e203/perips/apb_i2c+accelerator/rtl/include','-top','tb_top',
             '-f',out/'soc_shared_task.f','-f',extra,*models,'-Mdir='+str(out/'csrc'),'-o',out/'simv'])
        run_dir=out/'run-01';run_dir.mkdir()
        print('COMPILE_PASS; FULL_SHARED_TASK_RUNNING; may take10-20minutes or longer with server load',flush=True)
        text=run('run',[out/'simv','+DUMPWAVE=0','+SIM_TOOL=vcs','+TESTCASE='+str(image.with_suffix(''))],cwd=run_dir)
        report['cpu']=audit_cpu(text)
        for path,want in inputs.items():
            if sha(Path(path))!=want:raise ValueError('Original SoC input changed during run: '+path)
        for rel,want in manifest.items():
            if sha(bundle/rel)!=want:raise ValueError('Bundle changed during run')
        report.update(status='PASS_E203_SHARED_TASK_SYNTHETIC',cpu_executed=True,shared_output_words_verified=25344,
            result_blocks=400,limitations=['CPU-generated synthetic data, not official real12tasks','No host parameter-loading qualification',
                                          'Includes source generation and software reference; not official performance','No STA/PPA claim'])
        save(out/'report.json',report)
        print('PASS E203_SHARED_TASK blocks=400 stored_outputs=25344 verified_outputs=25344 x3=1',flush=True)
        print('CPU_COUNTS',json.dumps(report['cpu']),flush=True)
        print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        report.update(status='FAIL_E203_SHARED_TASK',error=str(error));save(out/'report.json',report)
        print('STOP:',error,flush=True);print('REPORT',out/'report.json',flush=True);return 1
    return 0


if __name__=='__main__':raise SystemExit(main())
