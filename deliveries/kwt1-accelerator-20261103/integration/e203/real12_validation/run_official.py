#!/usr/bin/env python3
"""Run a sealed real12 bundle against server official SRAM functional models."""
import argparse
import csv
import hashlib
import json
import math
from pathlib import Path
import re
import struct
import subprocess
import sys
from real12_audit import audit_result_trace


def digest(path): return hashlib.sha256(path.read_bytes()).hexdigest()
def save(path,value): path.write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=Path('official-run-01'))
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    args=parser.parse_args();root=Path(__file__).resolve().parent
    receipts=json.loads((root/'package-sha256.json').read_text())
    for rel,want in receipts.items():
        path=(root/rel).resolve()
        if root not in path.parents or digest(path)!=want:
            raise ValueError('Bundle changed: '+rel)
    models=[args.sram_root/part/'verilog'/name for part in ('RAMSP1024X16','RAMSP128X16')
            for name in (part+'_rtl.v',part+'.v')]
    for path in models:
        if not path.is_file(): raise FileNotFoundError(path)
    out=(root/args.output).resolve()
    if root not in out.parents: raise ValueError('Run output must remain inside extracted bundle')
    out.mkdir(parents=True,exist_ok=False)
    report=dict(status='RUNNING',soc_cpu_executed=False,official_model_mode='ARM_UD_MODEL fast functional',
                source_sha256=receipts,official_model_sha256={str(p):digest(p) for p in models},commands=[])
    def run(name,argv):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            process=subprocess.run(list(map(str,argv)),cwd=out,stdout=log,stderr=subprocess.STDOUT,timeout=1800)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),code=process.returncode))
        save(out/'report.json',report)
        if process.returncode:
            raise RuntimeError(name+' failed; inspect '+str(out/(name+'.log')))
        return (out/(name+'.log')).read_text(errors='replace')
    try:
        files=[root/line.strip() for line in (root/'rtl/kwt.f').read_text().splitlines()
               if line.strip() and not line.startswith('+')]
        run('compile',['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all',
                       '+define+ARM_UD_MODEL','+incdir+'+str(root/'rtl/include'),
                       '-top','tb_icb_real12','-Mdir='+str(out/'csrc'),'-o',out/'simv',
                       *files,root/'tb/interface/tb_icb_real12.v',*models])
        print('COMPILE_PASS; running12 real-data tasks with official functional models',flush=True)
        text=run('run',[out/'simv','+fixtures='+str(root/'fixtures'),'+trace='+str(out/'icb-trace.txt')])
        match=re.search(r'^PASS ICB_REAL12_CONTRACT (.*)$',text,re.M)
        if not match: raise RuntimeError('Missing RTL pass summary; inspect run.log')
        totals={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])}
        if totals.get('tasks')!=12 or totals.get('blocks')!=4800 or totals.get('outputs')!=304128:
            raise ValueError('Wrong real12 totals')
        gold=[];references=[]
        for case in range(1,13):
            gold.append([int(line,16) for line in (root/('fixtures/case%d-y.hex'%case)).read_text().splitlines()])
            raw=(root/('fixtures/case%d-ref.f32'%case)).read_bytes()
            if len(raw)!=25344*4: raise ValueError('Floating reference length mismatch')
            references.append(struct.unpack('<25344f',raw))
        audit=audit_result_trace(out/'icb-trace.txt',gold,references)
        if not audit['all_tasks_within_3_percent'] or any(row['last_flags']!=1 for row in audit['tasks']):
            raise ValueError('Actual RTL result precision/last flags failed')
        if any(digest(root/rel)!=want for rel,want in receipts.items()): raise ValueError('Bundle changed during run')
        if any(digest(p)!=report['official_model_sha256'][str(p)] for p in models): raise ValueError('Official models changed during run')
        report.update(status='PASS_REAL12_OFFICIAL_FUNCTIONAL',rtl=totals,audit=audit,
                      official_macro_functional_verified=True,
                      limitations=['Local representative12tasks, not official12performance tasks or organizer600samples.',
                                   'ICB source is TB; not real E20312task firmware execution.',
                                   'Fast functional model does not resolve prior hold violations or replace STA.'])
        save(out/'report.json',report)
        with (out/'layers.csv').open('w',encoding='utf-8-sig',newline='') as stream:
            writer=csv.DictWriter(stream,fieldnames=['layer','outputs','nrmse_percent','max_abs_error','output_saturations','raw_overflows'],extrasaction='ignore')
            writer.writeheader();writer.writerows(audit['tasks'])
        print(match[0],flush=True)
        print('PASS REAL12_OFFICIAL outputs=304128 bit_mismatches=0 max_nrmse_percent=%.8f'%audit['max_task_nrmse_percent'],flush=True)
        for row in audit['tasks']: print('LAYER %02d NRMSE=%.8f%%'%(row['layer'],row['nrmse_percent']),flush=True)
        print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        report.update(status='FAIL_REAL12_OFFICIAL',error=str(error));save(out/'report.json',report);raise


if __name__=='__main__':main()
