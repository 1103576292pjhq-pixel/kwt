#!/usr/bin/env python3
"""Compare actual indexed writeback and cold windows for full-W and W2 C flows."""
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

def actual_values(folder,filename):
    values={}
    for line in (folder/'cpu'/filename).read_text().splitlines():
        task,index,value=line.split();key=(int(task),int(index))
        if key in values:raise RuntimeError('duplicate actual indexed writeback')
        values[key]=int(value,16)
    if len(values)!=2*99*256:raise RuntimeError('incomplete actual writeback')
    return values

def main():
    p=argparse.ArgumentParser();p.add_argument('--full-w',required=True);p.add_argument('--w2',required=True);args=p.parse_args()
    paths=[ROOT/args.full_w,ROOT/args.w2];full,w2=[read_json(p) for p in paths]
    for report in [full,w2]:
        if report['status']!='PASS' or not report['source_unchanged'] or report['profile']['stage']!='full' or report['profile']['pm']!=4 or report['profile']['tasks']!=2:
            raise RuntimeError('comparison requires complete PM4 full-size two-task real CPU passes')
        for source,digest in report['source_sha256'].items():
            if sha(ROOT/source)!=digest:raise RuntimeError('source changed '+source)
        command=report['results']['cpu']['command']
        if command['exit_code']!=0 or sha(ROOT/command['log'])!=command['log_sha256']:raise RuntimeError('actual CPU process/log mismatch')
    for field in ['cases','input_sha256','tool_sha256']:
        if full[field]!=w2[field]:raise RuntimeError('different comparison binding '+field)
    for name in ['fixture/shared.hex','fixture/expected.hex','fixture/expected-flags.hex']:
        a,b=[p.parent/name for p in paths]
        if sha(a)!=sha(b) or sha(a)!=full['artifacts_sha256'][name] or sha(b)!=w2['artifacts_sha256'][name]:raise RuntimeError('different input/golden image '+name)
    for name in ['cpu-output.txt','cpu-flags.txt']:
        if actual_values(paths[0].parent,name)!=actual_values(paths[1].parent,name):raise RuntimeError('different actual indexed results '+name)
    normal=(ROOT/'soc/revd_opt/revd_opt_icb.sv').read_text()
    derived=(ROOT/'soc/revd_opt/revd_opt_icb_w2.sv').read_text().replace('revd_opt_icb_w2','revd_opt_icb').replace('core_stream_tiled_w2_opt','core_stream_frontend_opt')
    if normal!=derived:raise RuntimeError('W2 adapter differs beyond namespace/core selection')
    normal_driver=(ROOT/'sw/revd_opt/revd_opt_driver.c').read_text()
    derived_driver=(ROOT/'sw/revd_opt/revd_opt_driver_w2.c').read_text().replace('revd_opt_driver_w2.h','revd_opt_driver.h').replace('revd_opt_run_w2','revd_opt_run')
    schedule='        EMIT(5,tile,0,0);\n        if(tile==0u)EMIT(6,0,0,0);\n    }'
    original='        EMIT(5,tile,0,0);\n    }\n    EMIT(6,0,0,0);'
    if derived_driver.count(schedule)!=1 or derived_driver.replace(schedule,original)!=normal_driver:
        raise RuntimeError('W2 C differs beyond namespace and required START placement')
    rows=[]
    for a,b,case in zip(full['results']['cpu']['task_metrics'],w2['results']['cpu']['task_metrics'],full['cases'],strict=True):
        if a['effective_macs']!=1622016 or b['effective_macs']!=1622016:raise RuntimeError('MAC/geometry mismatch')
        rows.append({'case_id':case['case_id'],'full_w_cold_cycles':a['cold_cycles'],'w2_cold_cycles':b['cold_cycles'],
          'cycles_saved':a['cold_cycles']-b['cold_cycles'],'cycle_reduction':1-b['cold_cycles']/a['cold_cycles'],
          'public_cpu_speedup':a['cold_cycles']/b['cold_cycles'],
          'full_w_core_window_with_cpu_backpressure':a['core_cycles'],'w2_core_window_with_param_supply_and_cpu_backpressure':b['core_cycles']})
    out=ROOT/'reports/revd_offline/soc'/('w2-comparison-'+run_id());out.mkdir(parents=True,exist_ok=False)
    put(out/'result.json',{'status':'PASS','checked_utc':utc(),'scope':'Same raw X/W/bias, task descriptors, output contract, bus and public E203. Driver START placement differs as required by each architecture.',
      'actual_indexed_y_flags_equal':True,'single_icb_adapter_namespace_equivalent':True,'c_driver_diff_only_namespace_and_start_placement':True,'tasks':rows,
      'w2_lifecycle':w2['results']['cpu']['lifecycle'],'formal_contest_score':None,'physical_area_mm2':None,'energy_joules':None,
      'physical_winner':'UNRESOLVED','default_profile':'D3_FULL_W_PM4',
      'limitations':['W2 CPU evidence covers two independent full-size cold FFN1 tasks, not all 12 layers or full encoder.',
        'Core windows have different parameter-supply overlap and both include CPU result backpressure; only cold task windows are compared.',
        'No specified-library timing/area/energy measurement; RAM logical bytes do not establish physical PPA.'],
      'report_sha256':{str(p.relative_to(ROOT)):sha(p) for p in paths},'script_sha256':sha(Path(__file__))})
    print('SOC_W2_COMPARISON',out.relative_to(ROOT),rows,flush=True)
if __name__=='__main__':main()
