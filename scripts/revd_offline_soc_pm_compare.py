#!/usr/bin/env python3
"""Fixed PM2/PM4 real-CPU comparison; unknown physical axes remain unknown."""
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

def main():
    p=argparse.ArgumentParser();p.add_argument('--pm4',required=True);p.add_argument('--pm2',required=True);args=p.parse_args()
    paths=[ROOT/args.pm4,ROOT/args.pm2];r4,r2=[read_json(path) for path in paths]
    for report,path,pm in [(r4,paths[0],4),(r2,paths[1],2)]:
        if report['status']!='PASS' or not report['source_unchanged'] or report['profile']['pm']!=pm:
            raise RuntimeError('missing fixed-profile CPU pass')
        record=read_json(path.parent/'compile-cpu-verilator.log.command.json')
        if f'-GPM={pm}' not in record['argv'] or record['exit_code']!=0:raise RuntimeError('actual compile profile not verified')
        if report['results']['cpu']['command']['exit_code']!=0:raise RuntimeError('CPU process failed')
    for field in ['cases','source_sha256','input_sha256','tool_sha256']:
        if r4[field]!=r2[field]:raise RuntimeError('different comparison binding '+field)
    for item in ['fixture/shared.hex','fixture/expected.hex','fixture/expected-flags.hex','revd-driver.bin']:
        if r4['artifacts_sha256'][item]!=r2['artifacts_sha256'][item]:raise RuntimeError('different comparison fixture/firmware')
    if r4['results']['cpu']['output_sha256']!=r2['results']['cpu']['output_sha256']:raise RuntimeError('different actual Y/flags')
    rows=[]
    for w4,w2,case in zip(r4['results']['cpu']['task_metrics'],r2['results']['cpu']['task_metrics'],r4['cases'],strict=True):
        rows.append({'case_id':case['case_id'],'pm4_cold_cycles':w4['cold_cycles'],'pm2_cold_cycles':w2['cold_cycles'],
          'pm2_over_pm4_cycles':w2['cold_cycles']/w4['cold_cycles'],'pm2_over_pm4_throughput':w4['cold_cycles']/w2['cold_cycles'],
          'pm4_core_cycles_with_cpu_backpressure':w4['core_cycles'],'pm2_core_cycles_with_cpu_backpressure':w2['core_cycles']})
    out=ROOT/'reports/revd_offline/soc'/('pm-compare-'+run_id());out.mkdir(parents=True,exist_ok=False)
    put(out/'result.json',{'status':'PASS','checked_utc':utc(),'scope':'Fixed PM2 versus PM4, same exact C/adapter/images/tools and real public E203 cold windows.',
      'actual_y_flags_bytes_equal':True,'tasks':rows,'nominal_product_lanes':{'PM2':8,'PM4':16},
      'physical_area_mm2':None,'energy_joules':None,'competition_score':None,
      'physical_pareto_status':'UNRESOLVED_PHYSICAL_METRICS','default_profile':'PM4',
      'interpretation':'Retain verified alternatives until actual specified-library area/energy/timing exist. MAC count and generic cells do not establish the physical winner.',
      'report_sha256':{str(path.relative_to(ROOT)):sha(path) for path in paths},'comparison_script_sha256':sha(Path(__file__))})
    print('SOC_PM_COMPARISON',out.relative_to(ROOT),rows,flush=True)
if __name__=='__main__':main()
