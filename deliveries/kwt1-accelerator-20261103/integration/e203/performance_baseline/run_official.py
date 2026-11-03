#!/usr/bin/env python3
"""Official SRAM functional-model performance baseline, excluding CPU/shared RAM."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
from performance import analyse_metrics
from real12_audit import audit_result_trace


def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def save(path,value):path.write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=Path('official-run-01'))
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    args=parser.parse_args();root=Path(__file__).resolve().parent
    hashes=json.loads((root/'package-sha256.json').read_text())
    for rel,want in hashes.items():
        path=(root/rel).resolve()
        if root not in path.parents or digest(path)!=want:raise ValueError('Bundle changed: '+rel)
    models=[args.sram_root/part/'verilog'/name for part in ('RAMSP1024X16','RAMSP128X16')
            for name in (part+'_rtl.v',part+'.v')]
    for path in models:
        if not path.is_file():raise FileNotFoundError(path)
    out=(root/args.output).resolve()
    if root not in out.parents:raise ValueError('Output must remain inside extracted bundle')
    out.mkdir(parents=True,exist_ok=False)
    report=dict(status='RUNNING',source_sha256=hashes,soc_cpu_executed=False,shared_ram_included=False,
                official_model_mode='ARM_UD_MODEL fast functional',
                official_model_sha256={str(p):digest(p) for p in models},commands=[])
    def run(name,argv):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            result=subprocess.run(list(map(str,argv)),cwd=out,stdout=log,stderr=subprocess.STDOUT,timeout=1800)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=result.returncode))
        save(out/'report.json',report)
        if result.returncode:raise RuntimeError(name+' failed: '+str(out/(name+'.log')))
        return (out/(name+'.log')).read_text(errors='replace')
    try:
        files=[root/line.strip() for line in (root/'rtl/kwt.f').read_text().splitlines()
               if line.strip() and not line.startswith('+')]
        run('compile',['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all',
                       '+define+ARM_UD_MODEL','+incdir+'+str(root/'rtl/include'),'-top','tb_icb_perf12',
                       '-Mdir='+str(out/'csrc'),'-o',out/'simv',*files,
                       root/'tb/interface/tb_icb_perf12.v',*models])
        print('COMPILE_PASS; measuring12 accelerator-only ICB tasks; no CPU/sharedRAM',flush=True)
        text=run('run',[out/'simv','+fixtures='+str(root/'fixtures'),
                        '+trace='+str(out/'icb-trace.txt'),'+metrics='+str(out/'metrics.csv')])
        match=re.search(r'^PASS ICB_PERF12 (.*)$',text,re.M)
        if not match:raise RuntimeError('No performance PASS summary')
        totals={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])}
        if totals.get('tasks')!=12 or totals.get('outputs')!=304128 or totals.get('errors')!=0:
            raise ValueError('Wrong performance totals')
        gold=[];references=[]
        for case in range(1,13):
            gold.append([int(v,16) for v in (root/('fixtures/case%d-y.hex'%case)).read_text().splitlines()])
            data=(root/('fixtures/case%d-ref.f32'%case)).read_bytes()
            if len(data)!=25344*4:raise ValueError('Reference size mismatch')
            references.append(struct.unpack('<25344f',data))
        audit=audit_result_trace(out/'icb-trace.txt',gold,references)
        performance=analyse_metrics(out/'metrics.csv',12,150.)
        if not audit['all_tasks_within_3_percent'] or performance['total_cycles']!=totals['window_cycles']:
            raise ValueError('Numerical or cycle audit failed')
        if sum(t['mmio_requests'] for t in performance['tasks'])!=totals['requests'] or totals['requests']!=totals['responses']:
            raise ValueError('Transaction totals differ')
        if any(digest(root/rel)!=want for rel,want in hashes.items()):raise ValueError('Bundle changed during run')
        if any(digest(p)!=report['official_model_sha256'][str(p)] for p in models):raise ValueError('Model changed during run')
        report.update(status='PASS_PERFORMANCE_BASELINE_OFFICIAL_FUNCTIONAL',rtl=totals,audit=audit,performance=performance,
                      limitations=performance['exclusions']+['Not official organizer12tasks/600samples.','Fast functional mode does not prove setup/hold or150MHz STA.'])
        save(out/'report.json',report)
        names=['layer','span_cycles','normalized_time_ms','normalized_tasks_per_second','core_busy_cycles',
               'load_bus_cycles','status_bus_cycles','output_bus_cycles','ack_bus_cycles','tb_gap_cycles',
               'useful_mac_utilization_total','useful_mac_utilization_core_busy']
        with (out/'performance.csv').open('w',encoding='utf-8-sig',newline='') as stream:
            writer=csv.DictWriter(stream,fieldnames=names,extrasaction='ignore');writer.writeheader();writer.writerows(performance['tasks'])
        print(match[0],flush=True)
        print('PASS PERF_BASELINE_OFFICIAL tasks=12 cycles=%d normalized_tasks_per_second_at150MHz=%.6f errors=0'%
              (performance['total_cycles'],performance['normalized_tasks_per_second']),flush=True)
        for row in performance['tasks']:
            print('LAYER %02d cycles=%d core_busy=%d load_bus=%d status_bus=%d output_bus=%d ack_bus=%d gap=%d'%
                  (row['layer'],row['span_cycles'],row['core_busy_cycles'],row['load_bus_cycles'],row['status_bus_cycles'],
                   row['output_bus_cycles'],row['ack_bus_cycles'],row['tb_gap_cycles']),flush=True)
        print('SCOPE excludesCPU/sharedRAM;150MHz is normalization target, not STA proof',flush=True)
        print('REPORT',out/'report.json',flush=True)
    except Exception as error:
        report.update(status='FAIL_PERFORMANCE_BASELINE',error=str(error));save(out/'report.json',report);raise


if __name__=='__main__':main()
