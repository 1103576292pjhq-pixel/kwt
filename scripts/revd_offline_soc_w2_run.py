#!/usr/bin/env python3
"""Independent, bounded W2 public-E203 integration; default source stays frozen."""
from __future__ import annotations
import argparse
import datetime as dt
import os
from pathlib import Path
import re
import shutil
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

HARDWARE=['rtl/revd_opt/core_stream_tiled_w2_opt.sv','rtl/revd/banked_sp16.sv',
 'rtl/revd/quant_epilogue.sv','soc/revd_opt/revd_opt_icb_w2.sv',
 'soc/e203_common/e203_cpu_shell.sv','soc/e203_common/icb_shared_ram.sv']
TOOLS=['riscv64-unknown-elf-gcc','riscv64-unknown-elf-objcopy','riscv64-unknown-elf-objdump',
 'riscv64-unknown-elf-readelf','verilator','iverilog','vvp','g++','make']
class Run(soc.Run):
    def cmd(self,name,argv,timeout=240,cwd=None,negative=None):
        text,record=super().cmd(name,argv,timeout,cwd,negative)
        if record['exit_code'] in [None,124,-999]:
            raise RuntimeError(name+' incomplete/timeout subprocess cannot count as expected failure')
        if negative and record['exit_code']!=-6:
            raise RuntimeError(name+' expected real Verilator fatal SIGABRT (-6), got '+str(record['exit_code']))
        return text,record

def inventory(red_only,short):
    paths=HARDWARE+['dv/revd_opt/soc_cpu_tb_w2.sv','dv/e203_boot/timescale.v',
     'sw/e203/start.S','sw/e203/link.ld','scripts/revd_offline_soc_w2_run.py',
     'scripts/revd_offline_soc_run.py','scripts/revd_offline_common.py',
     'config/e203-source-manifest.json','reports/prototype/vectors/manifest.json']
    paths+=['sw/revd_opt/main.c','sw/revd_opt/revd_opt_driver.c','sw/revd_opt/revd_opt_driver.h'] if red_only else [
     'sw/revd_opt/main_w2.c','sw/revd_opt/revd_opt_driver_w2.c','sw/revd_opt/revd_opt_driver_w2.h']
    if short and not red_only:paths+=['dv/revd_opt/soc_completion_tb_w2.sv','dv/revd_opt/soc_bus_contract_tb_w2.sv','dv/revd_opt/soc_red_stub.c','dv/revd_opt/soc_w2_zero_return.c']
    files=[ROOT/p for p in paths]+sorted(soc.UP.rglob('*.v'))
    return {str(p.relative_to(ROOT)):sha(p) for p in files}

def firmware(run,name,normal=False,stub=False):
    if stub:cfiles=[ROOT/('dv/revd_opt/soc_w2_zero_return.c' if stub=='zero' else 'dv/revd_opt/soc_red_stub.c')]
    elif normal:cfiles=[ROOT/'sw/revd_opt/main.c',ROOT/'sw/revd_opt/revd_opt_driver.c']
    else:cfiles=[ROOT/'sw/revd_opt/main_w2.c',ROOT/'sw/revd_opt/revd_opt_driver_w2.c']
    elf=run.path/(name+'.elf')
    run.cmd('build-'+name,['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
     '-mcmodel=medany','-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax',
     '-Os','-g','-Wall','-Wextra','-Werror','-I',ROOT/'sw/revd_opt','-T',ROOT/'sw/e203/link.ld',
     f'-Wl,-Map,{run.path/(name+".map")}',ROOT/'sw/e203/start.S',*cfiles,'-o',elf])
    text,_=run.cmd('attributes-'+name,['riscv64-unknown-elf-readelf','-h','-A',elf])
    if not all(t in text for t in ['ELF32','RISC-V','0x80000000','rv32i','_m2','_a2','_c2','_zicsr','_zifencei']):raise RuntimeError('unexpected ISA/ABI')
    run.cmd('disassemble-'+name,['riscv64-unknown-elf-objdump','-d','-S',elf])
    run.cmd('binary-'+name,['riscv64-unknown-elf-objcopy','-O','binary',elf,run.path/(name+'.bin')])
    payload=(run.path/(name+'.bin')).read_bytes()
    if not 0<len(payload)<=65536:raise RuntimeError('firmware exceeds ITCM')
    hexpath=run.path/(name+'.hex');hexpath.write_text(''.join(f'{v:02x}\n' for v in payload))
    return hexpath,len(payload)

def compile_cpu(run,m,n,tasks):
    obj=run.path/'obj';inc=[soc.UP/'core',soc.UP/'perips',soc.UP/'perips/apb_i2c']
    sources=[ROOT/'dv/e203_boot/timescale.v',*sorted(soc.UP.rglob('*.v')),*[ROOT/p for p in HARDWARE],ROOT/'dv/revd_opt/soc_cpu_tb_w2.sv']
    run.cmd('compile-cpu-verilator',['verilator','--binary','--timing','--build-jobs','4','-Wno-fatal','-CFLAGS','-O3',
     '-Diverilog','-DDISABLE_SV_ASSERTION=1','--top-module','soc_cpu_tb_w2',f'-GM={m}',f'-GN={n}',
     f'-GTASKS={tasks}','-GPM=4','-GREAD_LATENCY=1','--Mdir',obj,*['-I'+str(p) for p in inc],*sources],timeout=600)
    return obj/'Vsoc_cpu_tb_w2'

def short_boundaries(run):
    results={}
    for name,token in [('soc_bus_contract_tb_w2','REVD_SOC_BUS_PASS'),('soc_completion_tb_w2','REVD_SOC_COMPLETION_PASS')]:
        binary=run.path/(name+'.vvp')
        run.cmd('compile-'+name,['iverilog','-g2012','-s',name,'-o',binary,*[ROOT/p for p in HARDWARE[:4]],ROOT/'dv/revd_opt'/(name+'.sv')],timeout=120)
        text,record=run.cmd('simulate-'+name,['vvp',binary],timeout=120)
        if token not in text:raise RuntimeError('missing boundary pass '+name)
        results[name]={'status':'PASS','command':record,'token':token}
    return results

def main():
    p=argparse.ArgumentParser();p.add_argument('--stage',choices=['small','full'],default='small')
    p.add_argument('--red-only',action='store_true');p.add_argument('--run-id');p.add_argument('--cutoff-utc')
    args=p.parse_args();rid=args.run_id or 'soc-w2-'+run_id()
    if args.red_only and args.stage!='small':raise RuntimeError('red-only must be bounded small M3/N32')
    out=ROOT/'reports/revd_offline/soc'/rid;out.mkdir(parents=True,exist_ok=False)
    run=Run(out)
    if args.cutoff_utc:
        stop=dt.datetime.fromisoformat(args.cutoff_utc.replace('Z','+00:00'));original_cmd=run.cmd
        def capped(name,argv,timeout=240,cwd=None,negative=None):
            remaining=(stop-dt.datetime.now(dt.timezone.utc)).total_seconds()-10
            if remaining<1:raise RuntimeError('W2 bounded cutoff reached')
            return original_cmd(name,argv,min(timeout,remaining),cwd,negative)
        run.cmd=capped
    report={'status':'RUNNING','started_utc':utc(),'run_id':rid,'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),
      'profile':{'architecture':'CTX4_W2_Y1_X4','pm':4,'pn':4,'latency':1,'tasks':2,'stage':args.stage,'red_only':args.red_only},
      'scope':'Independent W2 core + one ICB + public E203 real C; indexed actual SRAM Y/flags and final write responses. Not full encoder or official acceptance.'}
    report['cold_window_definition']='Task phase marker immediately before driver invocation through final actual shared Y/flag write response. Includes descriptor and X/W/bias loading, CPU/bus waits, compute and draining; excludes CPU boot and the pre-phase global M/N/task-count header reads.'
    put(out/'result.json',report)
    try:
        frozen=inventory(args.red_only,args.stage=='small');report['source_sha256']=frozen
        report['upstream_entries_verified']=soc.verify_upstream()
        toolpaths=[Path(sys.executable).resolve()]+[Path(shutil.which(name)).resolve() for name in TOOLS]
        report['tool_sha256']={str(path):sha(path) for path in toolpaths}
        m,n=(3,32) if args.stage=='small' else (99,256)
        info=soc.fixture(out/'fixture',m,n,2);report['cases']=info['cases'];report['input_sha256']=info['inputs']
        binary=compile_cpu(run,m,n,2);report['actual_simulator_executable_sha256']=sha(binary)
        fw=firmware(run,'revd-w2-driver',normal=args.red_only)
        report['firmware_binary_sha256']=sha(out/'revd-w2-driver.bin')
        if args.red_only:
            folder=out/'negative-preload-before-start';folder.mkdir(exist_ok=False)
            for filename in ['shared.hex','expected.hex','expected-flags.hex']:(folder/filename).write_bytes((out/'fixture'/filename).read_bytes())
            (folder/fw[0].name).write_bytes(fw[0].read_bytes())
            text,record=run.cmd('negative-preload-before-start',[binary,f'+FIRMWARE={fw[0].name}',f'+FIRMWARE_BYTES={fw[1]}'],
              timeout=120,cwd=folder,negative='CPU_EXIT_FAILURE')
            if not re.search(r'E203_W2_FAULT error=12\b',text) or 'code=fffffff5' not in text:
                raise RuntimeError('preload red did not fail for future OPEN with CPU -11')
            report['results']={'negative_future_open_before_start':{'status':'EXPECTED_FAIL','command':record,
              'reason':'Frozen full-W driver issued future OPEN before START; real W2 rejected op2 (error0x12), real CPU returned -11.'}}
            report['status']='RED_CONFIRMED'
        else:
            results={}
            if args.stage=='small':
                results['boundaries']=short_boundaries(run)
                stub=firmware(run,'red-stub',stub=True)
                results['negative_cpu_return']=soc.simulate(run,'negative-return',binary,'verilator',stub,info,'return')
                zero=firmware(run,'zero-return',stub='zero')
                folder=out/'negative-zero-work';folder.mkdir(exist_ok=False)
                for filename in ['shared.hex','expected.hex','expected-flags.hex']:(folder/filename).write_bytes((out/'fixture'/filename).read_bytes())
                (folder/zero[0].name).write_bytes(zero[0].read_bytes())
                text,record=run.cmd('negative-zero-work',[binary,f'+FIRMWARE={zero[0].name}',f'+FIRMWARE_BYTES={zero[1]}'],timeout=120,cwd=folder,
                  negative='CPU coverage incomplete outputs=0 flags=0')
                if 'CPU_EXIT_FAILURE' in text:raise RuntimeError('zero-work firmware did not return successful CPU completion code')
                results['negative_zero_work']={'status':'EXPECTED_FAIL','command':record,'reason':'Real CPU returned zero/BOOT but wrote no Y/flags; TB rejected coverage after success-code validation.'}
            results['cpu']=soc.simulate(run,'cpu',binary,'verilator',fw,info)
            text=(out/'cpu.log').read_text();match=re.search(r'E203_W2_LIFECYCLE ([^\n]+)',text)
            if not match:raise RuntimeError('missing passive W2 lifecycle evidence')
            results['cpu']['lifecycle']={key:int(value) for key,value in re.findall(r'(\w+)=(\d+)',match[1])}
            windows=[{key:int(value) for key,value in re.findall(r'(\w+)=(\d+)',line)} for line in re.findall(r'E203_W2_TASK ([^\n]+)',text)]
            if len(windows)!=2:raise RuntimeError('missing per-task W2 coverage windows')
            if args.stage=='full' and any(w['deferred_open_cycles']<1 or w['pops_with_pending_input']<1 for w in windows):
                raise RuntimeError('full-size W2 credit/drain fairness not exercised in both cold tasks')
            results['cpu']['w2_task_coverage']=windows
            if args.stage=='small':results['negative_wrong_expected']=soc.simulate(run,'negative-wrong-expected',binary,'verilator',fw,info,'corrupt')
            report['results']=results;report['status']='PASS'
        report['source_unchanged']=inventory(args.red_only,args.stage=='small')==frozen
        if not report['source_unchanged']:raise RuntimeError('W2 bound source changed during run')
        report.update(finished_utc=utc(),commands=run.records)
        report['artifacts_sha256']={str(p.relative_to(out)):sha(p) for p in out.rglob('*') if p.is_file() and p.name!='result.json' and 'obj' not in p.relative_to(out).parts}
        put(out/'result.json',report)
    except Exception as exc:
        report.update(status='FAIL',error=str(exc),finished_utc=utc(),commands=run.records);put(out/'result.json',report);raise
    print('SOC_W2_REPORT',out.relative_to(ROOT),report['status'],flush=True)
if __name__=='__main__':main()
