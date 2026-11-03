#!/usr/bin/env python3
"""One E203 boot, twelve shared-data FFN1 tasks, no inter-task reset."""
import argparse
import json
from pathlib import Path
import queue
import re
import subprocess
import threading
import time
from suite_tools import prepare_suite,prepare_wiring,audit_suite,sha,save


def check_sources(bundle,entries):
    for rel,want in entries.items():
        path=(bundle/rel).resolve()
        if bundle not in path.parents or not path.is_file() or sha(path)!=want:raise ValueError('Source/image/package identity changed: '+rel)


def audit_cpu(text):
    if len(re.findall(r'\bTEST_PASS\b',text))!=1 or re.search(r'TEST_FAIL|Time\s+Out|\bFatal\b|\bFATAL\b',text):
        raise ValueError('Missing unique TEST_PASS or fatal/failure/timeout')
    loaded=[tuple(map(int,m)) for m in re.findall(r'^SUITE_LOADER_DONE sequence=(\d+) case=(\d+) words=(\d+) runtime_reset=(\d+)\s*$',text,re.M)]
    completed=[tuple(map(int,m)) for m in re.findall(r'^SUITE_TASK_DONE sequence=(\d+) case=(\d+) layer=(\d+) writes=(\d+) reads=(\d+)\s*$',text,re.M)]
    if loaded!=[(i,i,48323,0) for i in range(1,13)]:raise ValueError('Missing/duplicate/out-of-order loader windows')
    if completed!=[(i,i,i-1,25344,25344) for i in range(1,13)]:raise ValueError('Missing/duplicate/out-of-order result windows')
    patterns=dict(total_cycles=r'Total cycle_count value:\s*(\d+)',instructions=r'The valid Instruction Count:\s*(\d+)',
                  ending_cycle=r'The test ending reached at cycle:\s*(\d+)',final_x3=r'The final x3 Reg value:\s*(\d+)')
    result={}
    for key,pattern in patterns.items():
        found=re.findall(pattern,text)
        if len(found)!=1:raise ValueError('Missing/duplicate CPU result '+key)
        result[key]=int(found[0])
    if result['final_x3']!=1 or not 0<result['ending_cycle']<=result['total_cycles']<400000000:raise ValueError('CPU result/cycles invalid')
    return result


def stream_simulation(argv,cwd,log_path,timeout=14400):
    """Keep a full log while publishing one line when each real task completes."""
    proc=subprocess.Popen(list(map(str,argv)),cwd=cwd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,bufsize=1)
    events=queue.Queue()
    def reader():
        try:
            for line in proc.stdout:events.put(line)
        finally:events.put(None)
    thread=threading.Thread(target=reader,daemon=True);thread.start();deadline=time.monotonic()+timeout
    try:
        with log_path.open('w',encoding='utf-8') as log:
            while True:
                if time.monotonic()>deadline:raise TimeoutError('Simulation wall timeout; log retained')
                try:line=events.get(timeout=1)
                except queue.Empty:continue
                if line is None:break
                log.write(line);log.flush()
                if line.startswith(('SUITE_LOADER_DONE','SUITE_TASK_DONE')):print(line.rstrip(),flush=True)
        return proc.wait(timeout=10)
    finally:
        if proc.poll() is None:proc.kill();proc.wait()
        thread.join(timeout=2);proc.stdout.close()


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,required=True)
    parser.add_argument('--fixtures',type=Path,default=Path('real12_verify_01/kwt-real12-validation/fixtures'))
    parser.add_argument('--output',default='verification/real_shared_suite_01')
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    args=parser.parse_args();root=args.root.resolve();bundle=Path(__file__).resolve().parent
    out=(root/args.output).resolve();fixtures=(root/args.fixtures).resolve()
    if root.name!='kwt-soc' or root not in out.parents or out.exists():parser.error('Use existing kwt-soc and a NEW output directory')
    manifest=json.loads((bundle/'package-sha256.json').read_text());check_sources(bundle,manifest)
    build=json.loads((bundle/'build-01/build-report.json').read_text());check_sources(bundle,build['sources'])
    image=bundle/'build-01/real_shared_suite.verilog'
    if sha(image)!=build['image_sha256']:raise ValueError('Firmware image differs')
    tb=root/'tb/tb_top.v';top=root/'rtl/e203/soc/kwt_shared_soc_top.v'
    base=root/'verification/soc_compile_01/soc.f';extra=root/'verification/shared_sram_wiring_01/shared_sram_additions.f'
    soc_text,tb_text=prepare_wiring(top.read_text(),tb.read_text())
    identity=json.loads((bundle/'fixture-identity.json').read_text())
    models=[args.sram_root/part/'verilog'/name for part in ['RAMSP1024X16','RAMSP128X16'] for name in [part+'_rtl.v',part+'.v']]
    inputs={tb,top,base,extra,*models,fixtures/'manifest.json',*(fixtures/name for name in identity['files'])}
    for folder in [root/'rtl',root/'accelerator/rtl']:
        if not folder.is_dir():raise FileNotFoundError(folder)
        inputs.update(p for p in folder.rglob('*') if p.is_file() and p.suffix in {'.v','.vh'})
    for line in extra.read_text().splitlines():
        line=line.strip()
        if line and not line.startswith(('+','-','//')):inputs.add((root/line).resolve())
    before={str(path):sha(path) for path in sorted(inputs)}
    listing=[];count=0
    for line in base.read_text().splitlines():
        value=line.strip().strip('"')
        if value=='tb/tb_top.v' or value.endswith('/tb/tb_top.v'):listing.append(str(out/'tb_suite.v'));count+=1
        else:listing.append(line)
    if count!=1:raise ValueError('Expected unique original TB file')
    out.mkdir(parents=True,exist_ok=False)
    report=dict(status='RUNNING',commands=[],input_sha256=before,firmware_sha256=sha(image),
        package_manifest_sha256=sha(bundle/'package-sha256.json'),production_rtl_changed=False,
        simulation_top='kwt_suite_soc_top',scope='12 representative tasks in one E203 boot; simulation-only ICB loading mux',inter_task_resets=0)
    save(out/'report.json',report)
    try:
        data=prepare_suite(fixtures,out/'data',identity)
        prepared={p.relative_to(out/'data').as_posix():sha(p) for p in (out/'data').rglob('*') if p.is_file()}
        report['prepared_sha256']=prepared
        (out/'original_tb.v').write_bytes(tb.read_bytes());(out/'original_soc.v').write_bytes(top.read_bytes())
        (out/'tb_suite.v').write_text(tb_text);(out/'kwt_suite_soc_top.v').write_text(soc_text)
        (out/'soc_suite.f').write_text('\n'.join(listing)+'\n')
        print('DATA_IDENTITY_PASS cases1..12; COMPILING_NEW_CONTINUOUS_SHARED_SUITE',flush=True)
        argv=['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all','+define+FPGA+ARM_UD_MODEL',
            '+incdir+rtl/e203/core+rtl/e203/perips+rtl/e203/perips/apb_i2c+accelerator/rtl/include','-top','tb_top',
            '-f',out/'soc_suite.f','-f',extra,*models,out/'kwt_suite_soc_top.v',bundle/'suite_loader.v',
            '-Mdir='+str(out/'csrc'),'-o',out/'simv']
        with (out/'compile.log').open('w') as log:compiled=subprocess.run(list(map(str,argv)),cwd=root,stdout=log,stderr=subprocess.STDOUT,timeout=1800)
        report['commands'].append(dict(name='compile',argv=list(map(str,argv)),returncode=compiled.returncode));save(out/'report.json',report)
        if compiled.returncode:raise RuntimeError('Compile failed; inspect '+str(out/'compile.log'))
        run_dir=out/'run-01';run_dir.mkdir()
        print('COMPILE_PASS; CONTINUOUS_SHARED_SUITE_RUNNING tasks=12; progress is printed after each task',flush=True)
        argv=[out/'simv','+DUMPWAVE=0','+SIM_TOOL=vcs','+TESTCASE='+str(image.with_suffix('')),'+real_data=../data','+real_trace=shared-y.txt']
        code=stream_simulation(argv,run_dir,out/'run.log')
        report['commands'].append(dict(name='run',argv=list(map(str,argv)),returncode=code));save(out/'report.json',report)
        if code:raise RuntimeError('Simulation failed; inspect '+str(out/'run.log'))
        report['cpu']=audit_cpu((out/'run.log').read_text(errors='replace'))
        report['audit']=audit_suite(run_dir/'shared-y.txt',data,fixtures)
        for path,want in before.items():
            if sha(Path(path))!=want:raise ValueError('Original input changed: '+path)
        for name,want in prepared.items():
            if sha(out/'data'/name)!=want:raise ValueError('Prepared input changed')
        check_sources(bundle,manifest)
        report.update(status='PASS_E203_REAL_SHARED_SUITE',cpu_executed=True,official_sram_functional=True,
            result_blocks=4800,shared_result_stores=304128,shared_result_reads=304128,
            limitations=['Representative validation cases, not official600/12','Simulation-only loading mux, not production host/arbiter',
                         'Test initialization/software checking/loading waits included; not formal performance','No STA/hold/area/power acceptance',
                         'TF2.4.0 vs2.4.0rc1 equivalence unproven'])
        save(out/'report.json',report)
        print('PASS E203_REAL_SHARED_SUITE tasks=12 blocks=4800 outputs=304128 bit_mismatches=0 max_NRMSE=%.8f%%'%report['audit']['max_nrmse_percent'],flush=True)
        for row in report['audit']['tasks_audit']:print('CASE %02d LAYER %02d NRMSE=%.8f%%'%(row['case'],row['hardware_layer']+1,row['nrmse_percent']),flush=True)
        print('CPU_COUNTS',json.dumps(report['cpu']),flush=True);print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        report.update(status='FAIL_E203_REAL_SHARED_SUITE',error=str(error));save(out/'report.json',report)
        print('STOP:',error,flush=True);print('REPORT',out/'report.json',flush=True);return 1
    return 0


if __name__=='__main__':raise SystemExit(main())
