#!/usr/bin/env python3
"""Every directed input is the first operation in a fresh simulator process."""
from pathlib import Path
import argparse
import datetime as dt
import json
import os
import subprocess
import sys
from hardfloat_sources import prepare,SOURCE,ROOT
from run_fp32 import run,digest,input_manifest

REPORT=ROOT/'reports/encoder/fp32'
CASES=[
 ('positive_zero_div_two',4,0,0x40000000),
 ('negative_zero_div_two',4,0x80000000,0x40000000),
 ('positive_zero_div_negative_two',4,0,0xc0000000),
 ('negative_zero_div_negative_two',4,0x80000000,0xc0000000),
 ('one_div_positive_inf',4,0x3f800000,0x7f800000),
 ('one_div_negative_inf',4,0x3f800000,0xff800000),
 ('negative_one_div_positive_inf',4,0xbf800000,0x7f800000),
 ('negative_one_div_negative_inf',4,0xbf800000,0xff800000),
 ('sqrt_positive_zero',5,0,0),('sqrt_negative_zero',5,0x80000000,0),
 ('zero_div_zero',4,0,0),('negative_zero_div_zero',4,0x80000000,0),
 ('positive_inf_div_inf',4,0x7f800000,0x7f800000),
 ('negative_inf_div_inf',4,0xff800000,0x7f800000),
 ('one_div_zero',4,0x3f800000,0),('negative_one_div_zero',4,0xbf800000,0),
 ('one_div_negative_zero',4,0x3f800000,0x80000000),
 ('inf_div_one',4,0x7f800000,0x3f800000),
 ('negative_inf_div_one',4,0xff800000,0x3f800000),
 ('quiet_nan_div_one',4,0x7fc12345,0x3f800000),
 ('signaling_nan_div_one',4,0x7f812345,0x3f800000),
 ('one_div_quiet_nan',4,0x3f800000,0x7fc12345),
 ('one_div_signaling_nan',4,0x3f800000,0x7f812345),
 ('sqrt_quiet_nan',5,0x7fc12345,0),('sqrt_signaling_nan',5,0x7f812345,0),
 ('sqrt_negative_one',5,0xbf800000,0),('sqrt_positive_inf',5,0x7f800000,0),
 ('sqrt_negative_inf',5,0xff800000,0),
 ('normal_division',4,0x3f800000,0x3fc00000),('normal_sqrt',5,0x40000000,0),
 ('integer_result_is_not_float',6,0xbfc00000,0),
 ('integer_max_result_is_not_nan',6,0x4f000000,0),
 ('integer_min_result_is_not_float',6,0xcf000000,0),
 ('integer_min_to_float',7,0x80000000,0),
]

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--mode',choices=['red','green','repeat','unknown'],default='green')
    p.add_argument('--rtl',type=Path,default=ROOT/'rtl/encoder_fp32.sv')
    p.add_argument('--case',default=None)
    p.add_argument('--label',default=None)
    p.add_argument('--expect-unknown-masked',action='store_true')
    args=p.parse_args()
    folder=REPORT/(args.label or ('cold-'+args.mode))
    if folder.resolve().parent!=REPORT.resolve(): raise RuntimeError('Report label must be one safe directory name')
    folder.mkdir(parents=True,exist_ok=True)
    commands=[];inputs=input_manifest()
    inputs['sha256']['dv/fp32/tb_fp32_cold.sv']=digest(ROOT/'dv/fp32/tb_fp32_cold.sv')
    inputs['sha256']['dv/fp32/run_cold.py']=digest(Path(__file__))
    status={'status':'RUNNING','started_utc':dt.datetime.now(dt.timezone.utc).isoformat(),
            'pid':os.getpid(),'inputs':inputs,'commands':commands,'cases':{},
            'rtl_path':str(args.rtl),'rtl_sha256':digest(args.rtl)}
    def save(): (folder/'status.json').write_text(json.dumps(status,indent=2)+'\n',encoding='utf-8')
    save()
    try:
        commands.append(run(['gcc','-std=c11','-O0','-frounding-math','-ffp-contract=off',
            '-fno-fast-math','-fsignaling-nans',str(ROOT/'dv/fp32/host_reference.c'),
            '-lm','-o','host_reference'],folder,folder/'oracle-build.log'))
        commands.append(run(['./host_reference','vectors.hex','0'],folder,folder/'oracle.log'))
        vectors={}
        for line in (folder/'vectors.hex').read_text(encoding='utf-8').splitlines():
            row=[int(v,16) for v in line.split()];vectors.setdefault(tuple(row[:3]),row)
        case_filter='normal_division' if args.mode=='unknown' else args.case
        selected=[case for case in CASES if case_filter is None or case[0]==case_filter]
        if not selected: raise RuntimeError('No matching case')
        simulators=['iverilog'] if args.mode=='unknown' else ['iverilog','verilator']
        for sim in simulators:
            build=folder/sim;build.mkdir(parents=True,exist_ok=True)
            files=[str(f) for f in prepare(build/'hardfloat')]+[str(args.rtl.resolve()),str(ROOT/'dv/fp32/tb_fp32_cold.sv')]
            includes=[f'-I{SOURCE}',f'-I{SOURCE/"RISCV"}']
            if sim=='iverilog':
                cc=['iverilog','-g2012','-s','tb_fp32_cold','-o','sim.vvp',*includes,*files]
            else:
                cc=['verilator','--binary','--timing','--top-module','tb_fp32_cold','-Wno-fatal',
                    '-j','2','--Mdir','obj',*includes,*files]
            commands.append(run(cc,build,build/'compile.log'))
            status['cases'][sim]={};save()
            for name,op,a,b in selected:
                row=vectors[(op,a,b)];_,_,_,c,y,flags,error=row
                case_folder=build/name;case_folder.mkdir(parents=True,exist_ok=True)
                exe=['vvp','../sim.vvp'] if sim=='iverilog' else ['../obj/Vtb_fp32_cold']
                cmd=exe+[f'+OP={op:x}',f'+A={a:08x}',f'+B={b:08x}',f'+C={c:08x}',
                    f'+EXPECTED={y:08x}',f'+FLAGS={flags:02x}',f'+ERROR={error:x}','+RESULTS=results.hex']
                if args.mode=='unknown': cmd.append('+INJECT_UNKNOWN_CLASS')
                # Initial RED deliberately requires the real cold arithmetic failure.
                expected_exit=1 if ((args.mode=='red' and sim=='iverilog') or args.expect_unknown_masked) else 0
                result=run(cmd,case_folder,case_folder/'run.log',expected_exit)
                commands.append(result)
                log=(case_folder/'run.log').read_text(encoding='utf-8')
                if expected_exit:
                    diagnostic='COLD_UNKNOWN_CLASS_MASKED' if args.expect_unknown_masked else 'COLD_MISMATCH'
                    if diagnostic not in log: raise RuntimeError('Unexpected RED failure reason')
                    status['cases'][sim][name]={'behavioral_red':True,'expected':[y,flags,error]}
                else:
                    marker='FP32_COLD_UNKNOWN_PROPAGATED' if args.mode=='unknown' else 'FP32_COLD_PASS accepted_requests=1'
                    if marker not in log: raise RuntimeError('Missing cold pass marker')
                    status['cases'][sim][name]={'pass':True,'expected':[y,flags,error],
                         'results_sha256':digest(case_folder/'results.hex')}
                save()
        if args.mode not in ('red','unknown'):
            if status['cases']['iverilog']!=status['cases']['verilator']:
                raise RuntimeError('Cold cross-simulator mismatch')
            if args.mode=='repeat':
                old=json.loads((REPORT/'cold-green/status.json').read_text(encoding='utf-8'))
                if old['inputs']!=status['inputs'] or old['cases']!=status['cases']:
                    raise RuntimeError('Cold repeat source/input/output mismatch')
        if digest(args.rtl)!=status['rtl_sha256']: raise RuntimeError('Production source changed during cold run')
        for relative,sha in status['inputs']['sha256'].items():
            if digest(ROOT/relative)!=sha: raise RuntimeError('Dependency changed during cold run: '+relative)
        status['status']='EXPECTED_BEHAVIORAL_RED' if args.mode=='red' or args.expect_unknown_masked else 'PASS'
        status['finished_utc']=dt.datetime.now(dt.timezone.utc).isoformat()
        status['artifacts']={str(f.relative_to(ROOT)):digest(f) for f in folder.rglob('*')
            if f.is_file() and 'obj' not in f.parts and f.name!='status.json' and f.suffix!='.vvp'}
        save();print(f'FP32_COLD_{status["status"]} cases={len(selected)} new_processes={len(simulators)*len(selected)}')
    except Exception as exc:
        status['status']='FAIL';status['error']=str(exc);save();raise

if __name__=='__main__': main()
