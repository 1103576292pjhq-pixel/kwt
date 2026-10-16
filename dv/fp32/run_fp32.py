#!/usr/bin/env python3
"""Compile/run real standalone RTL against separately executed C oracle."""
from __future__ import annotations
import argparse
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import time
from hardfloat_sources import prepare

ROOT=Path(__file__).resolve().parents[2]
VENDOR=ROOT/'vendor/HardFloat-1-upstream'
SOURCE=VENDOR/'source'
REPORT=ROOT/'reports/encoder/fp32'

def digest(path:Path)->str:
    return hashlib.sha256(path.read_bytes()).hexdigest()

def run(cmd:list[str], where:Path, log:Path, expected:int=0)->dict:
    start=time.monotonic()
    with log.open('w',encoding='utf-8') as f:
        f.write('$ '+shlex.join(cmd)+'\n'); f.flush()
        p=subprocess.run(cmd,cwd=where,stdout=f,stderr=subprocess.STDOUT,check=False)
    result={'command':cmd,'cwd':str(where),'exit_code':p.returncode,
            'seconds':round(time.monotonic()-start,3),'log':str(log.relative_to(ROOT))}
    if p.returncode!=expected:
        print(log.read_text(encoding='utf-8',errors='replace')[-9000:])
        raise RuntimeError(f'{log.name}: expected exit {expected}, got {p.returncode}')
    return result

def input_manifest()->dict:
    manifest=json.loads((ROOT/'config/hardfloat-source-manifest.json').read_text(encoding='utf-8'))
    for entry in manifest['files']:
        path=VENDOR/entry['path']
        if digest(path)!=entry['sha256']: raise RuntimeError(f'Upstream changed: {path}')
    paths=[ROOT/'rtl/encoder_fp32.sv',ROOT/'dv/fp32/tb_encoder_fp32.sv',
           ROOT/'dv/fp32/host_reference.c',ROOT/'dv/fp32/run_fp32.py',ROOT/'dv/fp32/hardfloat_sources.py',
           ROOT/'dv/fp32/tb_fp32_cold.sv',ROOT/'dv/fp32/run_cold.py',
           ROOT/'config/hardfloat-source-manifest.json',ROOT/'work/encoder_fp32_contract.md']
    return {'upstream_files_verified':len(manifest['files']),
            'sha256':{str(p.relative_to(ROOT)):digest(p) for p in paths if p.exists()}}

def simulate(sim:str, rtl:Path, vectors:Path, target:Path, expected:int=0)->list[dict]:
    target.mkdir(parents=True,exist_ok=True)
    sources=[str(p) for p in prepare(target/'hardfloat')]+[str(rtl),str(ROOT/'dv/fp32/tb_encoder_fp32.sv')]
    includes=[f'-I{SOURCE}',f'-I{SOURCE/"RISCV"}']
    if sim=='iverilog':
        compile_cmd=['iverilog','-g2012','-s','tb_encoder_fp32','-o','sim.vvp',*includes,*sources]
        execute_cmd=['vvp','sim.vvp',f'+VECTORS={os.path.relpath(vectors,target)}','+RESULTS=results.hex']
    else:
        compile_cmd=['verilator','--binary','--timing','--top-module','tb_encoder_fp32',
                     '-Wno-fatal','-j','2','--Mdir','obj',*includes,*sources]
        execute_cmd=['./obj/Vtb_encoder_fp32',f'+VECTORS={os.path.relpath(vectors,target)}','+RESULTS=results.hex']
    return [run(compile_cmd,target,target/'compile.log'),run(execute_cmd,target,target/'run.log',expected)]

def main()->int:
    parser=argparse.ArgumentParser()
    parser.add_argument('--mode',choices=['red','green','repeat','all','synthesis','mutations'],default='all')
    parser.add_argument('--random-per-op',type=int,default=2048)
    args=parser.parse_args()
    REPORT.mkdir(parents=True,exist_ok=True)
    folder=REPORT/args.mode;folder.mkdir(parents=True,exist_ok=True)
    commands=[]
    result={'status':'RUNNING','started_utc':dt.datetime.now(dt.timezone.utc).isoformat(),
            'mode':args.mode,'pid':os.getpid(),'commands':commands,'inputs':input_manifest()}
    status=folder/'status.json'
    def save(): status.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    save()
    try:
        if args.mode=='synthesis':
            sources=[str(p) for p in prepare(folder/'hardfloat')]+[str(ROOT/'rtl/encoder_fp32.sv')]
            script='read_verilog -sv '+f'-I{SOURCE} -I{SOURCE/"RISCV"} '+' '.join(sources)+'; hierarchy -check -top encoder_fp32; proc; opt; check -assert; stat; write_json design.json'
            commands.append(run(['yosys','-p',script],folder,folder/'yosys.log'))
            result['limitation']='Generic structural elaboration only; no technology mapping, PPA, or formal IEEE proof.'
        else:
            commands.append(run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Wno-unknown-pragmas',
                '-frounding-math','-ffp-contract=off','-fno-fast-math','-fsignaling-nans',
                str(ROOT/'dv/fp32/host_reference.c'),'-lm','-o','host_reference'],folder,folder/'oracle-build.log'))
            commands.append(run(['./host_reference','vectors.hex',str(args.random_per_op)],folder,folder/'oracle.log'))
            vectors=folder/'vectors.hex'
            result['vector_count']=len(vectors.read_text(encoding='utf-8').splitlines())
            result['vector_sha256']=digest(vectors)
            if args.mode=='red':
                commands+=simulate('iverilog',ROOT/'dv/fp32/mutants/zero_result.sv',vectors,folder/'zero_result',1)
                fail_log=(folder/'zero_result/run.log').read_text(encoding='utf-8')
                if 'MISMATCH' not in fail_log: raise RuntimeError('RED did not fail expected arithmetic assertion')
                result['status']='EXPECTED_BEHAVIORAL_RED'
            elif args.mode=='mutations':
                original=(ROOT/'rtl/encoder_fp32.sv').read_text(encoding='utf-8')
                # Each changes a real logic behavior and is compiled/executed.
                mutants={
                 'drop_flags':('rsp_flags<=fast_flags;','rsp_flags<=5\'b0;','MISMATCH'),
                 'signed_zero_lost':('fast_data=mul_data;',"fast_data=(mul_data==32'h80000000)?32'h0:mul_data;",'MISMATCH'),
                 'response_not_held':('RESPONSE: if(rsp_ready) state<=IDLE;',
                    'RESPONSE: if(rsp_ready) state<=IDLE; else rsp_data<=req_a;','STALLED_RESPONSE_CHANGED'),
                 'div_pulse_lost':('DIV_WAIT: if(div_valid) begin',
                    'DIV_WAIT: if(div_valid && rsp_ready) begin','RESPONSE_TIMEOUT'),
                 'fma_addend_lost':('fast_data=fma_data;','fast_data=mul_data;','MISMATCH'),
                }
                result['mutations']={}
                for name,(old,new,diagnostic) in mutants.items():
                    if original.count(old)!=1: raise RuntimeError('Mutation anchor drift: '+name)
                    target=folder/name;target.mkdir(parents=True,exist_ok=True)
                    mutant=target/'encoder_fp32.sv'
                    mutant.write_text(original.replace(old,new),encoding='utf-8')
                    commands+=simulate('iverilog',mutant,vectors,target,1)
                    if diagnostic not in (target/'run.log').read_text(encoding='utf-8'):
                        raise RuntimeError('Wrong behavioral failure: '+name)
                    result['mutations'][name]={'compiled':True,'killed':True,
                        'expected_diagnostic':diagnostic,'source_sha256':digest(mutant)}
                cold_mutants={
                    'cold_zero_decode_bypassed':('assign div_data=canonical_ieee(div_rec,div_ieee_raw);',
                        'assign div_data=div_ieee_raw;',
                        ['--mode','red','--case','positive_zero_div_two'],'COLD_MISMATCH'),
                    'unknown_class_casex_masked':('case(recoded[31:29])','casex(recoded[31:29])',
                        ['--mode','unknown','--expect-unknown-masked'],'COLD_UNKNOWN_CLASS_MASKED'),
                }
                for name,(old,new,options,diagnostic) in cold_mutants.items():
                    if original.count(old)!=1: raise RuntimeError('Mutation anchor drift: '+name)
                    target=folder/name;target.mkdir(parents=True,exist_ok=True)
                    mutant=target/'encoder_fp32.sv'
                    mutant.write_text(original.replace(old,new),encoding='utf-8')
                    label='mutation-'+name
                    commands.append(run([sys.executable,str(ROOT/'dv/fp32/run_cold.py'),*options,
                        '--rtl',str(mutant),'--label',label],folder,target/'driver.log'))
                    cold_status_path=REPORT/label/'status.json'
                    cold=json.loads(cold_status_path.read_text(encoding='utf-8'))
                    if cold['status']!='EXPECTED_BEHAVIORAL_RED': raise RuntimeError('Cold mutant survived: '+name)
                    child_compiles=[cmd for cmd in cold['commands'] if 'compile.log' in cmd['log']]
                    if not child_compiles or any(cmd['exit_code']!=0 for cmd in child_compiles):
                        raise RuntimeError('Cold mutant compilation failed: '+name)
                    result['mutations'][name]={'compiled':True,'killed':True,
                        'expected_diagnostic':diagnostic,'source_sha256':digest(mutant),
                        'cold_status_path':str(cold_status_path.relative_to(ROOT)),
                        'cold_status_sha256':digest(cold_status_path)}
            else:
                commands+=simulate('verilator',ROOT/'rtl/encoder_fp32.sv',vectors,folder/'verilator')
                result['results_sha256']=digest(folder/'verilator/results.hex')
                if args.mode in ('all','green'):
                    # Same independent vectors in two real event-driven executions.
                    commands+=simulate('iverilog',ROOT/'rtl/encoder_fp32.sv',vectors,folder/'iverilog')
                    if digest(folder/'iverilog/results.hex')!=result['results_sha256']:
                        raise RuntimeError('Cross-simulator results differ')
                if args.mode=='repeat':
                    original=REPORT/'all/status.json'
                    prior=json.loads(original.read_text(encoding='utf-8'))
                    if prior['status']!='PASS' or prior['inputs']!=result['inputs']:
                        raise RuntimeError('Repeat source binding differs from passed all run')
                    if (prior['vector_sha256'],prior['results_sha256'])!=(result['vector_sha256'],result['results_sha256']):
                        raise RuntimeError('Independent repeat differs')
        if result['inputs']!=input_manifest(): raise RuntimeError('Sources changed during verification')
        if result['status']=='RUNNING': result['status']='PASS'
        result['finished_utc']=dt.datetime.now(dt.timezone.utc).isoformat()
        result['artifacts']={str(p.relative_to(ROOT)):digest(p) for p in folder.rglob('*')
             if p.is_file() and p.name!='status.json' and 'obj' not in p.parts and p.suffix not in ('.vvp',)}
        save();print(f'FP32 {args.mode} {result["status"]}');return 0
    except Exception as exc:
        result['status']='FAIL';result['error']=str(exc);save();raise

if __name__=='__main__': sys.exit(main())
