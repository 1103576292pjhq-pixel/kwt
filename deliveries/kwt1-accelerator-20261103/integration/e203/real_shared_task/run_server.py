#!/usr/bin/env python3
"""Run one existing real-audio FFN1 fixture through actual E203/shared SRAM."""
import argparse
import json
from pathlib import Path
import re
import subprocess
from real_tools import prepare_data,prepare_wiring,audit_trace,sha,save


def audit_cpu(text):
    if len(re.findall(r'\bTEST_PASS\b',text))!=1 or re.search(r'TEST_FAIL|Time\s+Out|\bFatal\b|\bFATAL\b',text):
        raise ValueError('Missing unique TEST_PASS or failure/timeout')
    for marker in ['REAL_LOADER_DONE writes=48320 cpu_held_in_reset=1',
                   'REAL_SHARED_READBACK_DONE writes=25344 reads=25344']:
        if text.count(marker)!=1:raise ValueError('Missing/duplicate real shared-task marker: '+marker)
    patterns=dict(total_cycles=r'Total cycle_count value:\s*(\d+)',instructions=r'The valid Instruction Count:\s*(\d+)',
                  ending_cycle=r'The test ending reached at cycle:\s*(\d+)',final_x3=r'The final x3 Reg value:\s*(\d+)')
    result={}
    for key,pattern in patterns.items():
        found=re.findall(pattern,text)
        if len(found)!=1:raise ValueError('Missing/duplicate CPU result '+key)
        result[key]=int(found[0])
    if result['final_x3']!=1 or not 0<result['ending_cycle']<=result['total_cycles']<40000000:
        raise ValueError('Invalid CPU result or cycles')
    return result


def check_sources(bundle,entries):
    for rel,want in entries.items():
        path=(bundle/rel).resolve()
        if bundle not in path.parents or not path.is_file() or sha(path)!=want:
            raise ValueError('Source/image/package identity mismatch: '+rel)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,required=True)
    parser.add_argument('--fixtures',type=Path,default=Path('real12_verify_01/kwt-real12-validation/fixtures'))
    parser.add_argument('--output',default='verification/real_shared_case3_01')
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    args=parser.parse_args();root=args.root.resolve();bundle=Path(__file__).resolve().parent
    out=(root/args.output).resolve()
    if root.name!='kwt-soc' or root not in out.parents or out.exists():
        parser.error('Use existing kwt-soc and a NEW output directory inside it')
    fixtures=(root/args.fixtures).resolve()
    manifest=json.loads((bundle/'package-sha256.json').read_text(encoding='utf-8'))
    check_sources(bundle,manifest)
    build=json.loads((bundle/'build-01/build-report.json').read_text(encoding='utf-8'))
    check_sources(bundle,build['sources'])
    image=bundle/'build-01/real_shared_task.verilog'
    if sha(image)!=build['image_sha256']:raise ValueError('Firmware image mismatch')
    tb=root/'tb/tb_top.v';top=root/'rtl/e203/soc/kwt_shared_soc_top.v'
    base=root/'verification/soc_compile_01/soc.f'
    extra=root/'verification/shared_sram_wiring_01/shared_sram_additions.f'
    soc_text,tb_text=prepare_wiring(top.read_text(encoding='utf-8'),tb.read_text(encoding='utf-8'))
    models=[args.sram_root/part/'verilog'/name for part in ['RAMSP1024X16','RAMSP128X16']
            for name in [part+'_rtl.v',part+'.v']]
    inputs={tb,top,base,extra,*models,fixtures/'manifest.json'}
    inputs.update(fixtures/name for name in json.loads((bundle/'fixture-identity.json').read_text())['files'])
    for folder in [root/'rtl',root/'accelerator/rtl']:
        if not folder.is_dir():raise FileNotFoundError(folder)
        inputs.update(p for p in folder.rglob('*') if p.is_file() and p.suffix in {'.v','.vh'})
    for line in extra.read_text(encoding='utf-8').splitlines():
        line=line.strip()
        if line and not line.startswith(('+','-','//')):
            inputs.add((root/line).resolve())
    before={str(path):sha(path) for path in sorted(inputs)}
    listing=[];count=0
    for line in base.read_text(encoding='utf-8').splitlines():
        value=line.strip().strip('"')
        if value=='tb/tb_top.v' or value.endswith('/tb/tb_top.v'):
            listing.append(str(out/'tb_real.v'));count+=1
        else:listing.append(line)
    if count!=1:raise ValueError('Expected one original TB in soc.f')
    out.mkdir(parents=True,exist_ok=False)
    report=dict(status='RUNNING',commands=[],case=3,input_sha256=before,firmware_sha256=sha(image),
        package_manifest_sha256=sha(bundle/'package-sha256.json'),production_rtl_changed=False,
        cpu_clock_after_loading_changed=False,simulation_top='kwt_real_soc_top',
        scope='TB ICB preload while CPU reset; actual CPU shared input, full accelerator task and actual shared result readback')
    save(out/'report.json',report)
    def run(name,argv,cwd=root):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            proc=subprocess.run(list(map(str,argv)),cwd=cwd,stdout=log,stderr=subprocess.STDOUT,timeout=7200)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=proc.returncode));save(out/'report.json',report)
        if proc.returncode:raise RuntimeError(name+' failed; inspect '+str(out/(name+'.log')))
        return (out/(name+'.log')).read_text(encoding='utf-8',errors='replace')
    try:
        identity=json.loads((bundle/'fixture-identity.json').read_text(encoding='utf-8'))
        data=prepare_data(fixtures,out/'data',identity)
        report['sample']=data['sample'];report['prepared_data_sha256']=data['files_sha256']
        (out/'original_tb.v').write_bytes(tb.read_bytes());(out/'original_soc.v').write_bytes(top.read_bytes())
        (out/'tb_real.v').write_text(tb_text,encoding='utf-8')
        (out/'kwt_real_soc_top.v').write_text(soc_text,encoding='utf-8')
        (out/'soc_real.f').write_text('\n'.join(listing)+'\n',encoding='utf-8')
        print('DATA_IDENTITY_PASS case3 yes layer3; COMPILING_NEW_REAL_SHARED_SOC',flush=True)
        run('compile',['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all','+define+FPGA+ARM_UD_MODEL',
            '+incdir+rtl/e203/core+rtl/e203/perips+rtl/e203/perips/apb_i2c+accelerator/rtl/include',
            '-top','tb_top','-f',out/'soc_real.f','-f',extra,*models,out/'kwt_real_soc_top.v',bundle/'real_loader.v',
            '-Mdir='+str(out/'csrc'),'-o',out/'simv'])
        run_dir=out/'run-01';run_dir.mkdir()
        print('COMPILE_PASS; REAL_SHARED_CASE3_RUNNING; may take10-20minutes or longer',flush=True)
        text=run('run',[out/'simv','+DUMPWAVE=0','+SIM_TOOL=vcs','+TESTCASE='+str(image.with_suffix('')),
                        '+real_data=../data','+real_trace=shared-y.txt'],cwd=run_dir)
        report['cpu']=audit_cpu(text)
        report['audit']=audit_trace(run_dir/'shared-y.txt',data['gold'],fixtures/'case3-ref.f32')
        for path,want in before.items():
            if sha(path)!=want:raise ValueError('Original server input changed: '+path)
        for name,want in data['files_sha256'].items():
            if sha(out/'data'/name)!=want:raise ValueError('Prepared data changed')
        check_sources(bundle,manifest)
        report.update(status='PASS_E203_REAL_SHARED_CASE3',cpu_executed=True,official_sram_functional=True,
            shared_result_stores=25344,shared_result_reads=25344,result_blocks=400,
            limitations=['Single representative validation recording, not official600 or official12',
                         'Simulation-only loader mux; no production host interface or arbiter qualification',
                         'Initialization and software comparisons included; not formal performance',
                         'No 150MHz/hold/STA/area/power acceptance','TF2.4.0 vs2.4.0rc1 equivalence unproven'])
        save(out/'report.json',report)
        print('PASS E203_REAL_SHARED case=3 blocks=400 outputs=25344 bit_mismatches=0 NRMSE=%.8f%%'%report['audit']['nrmse_percent'],flush=True)
        print('CPU_COUNTS',json.dumps(report['cpu']),flush=True);print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        report.update(status='FAIL_E203_REAL_SHARED_CASE3',error=str(error));save(out/'report.json',report)
        print('STOP:',error,flush=True);print('REPORT',out/'report.json',flush=True);return 1
    return 0


if __name__=='__main__':raise SystemExit(main())
