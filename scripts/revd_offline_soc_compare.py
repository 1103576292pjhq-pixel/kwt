#!/usr/bin/env python3
"""Compare actual same-input CPU cold windows, without predicting contest scores."""
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--candidate',required=True);parser.add_argument('--baseline',required=True);args=parser.parse_args()
    paths=[ROOT/args.candidate,ROOT/args.baseline];new,old=[read_json(p) for p in paths]
    for report in [new,old]:
        if report['status']!='PASS' or not report['source_unchanged'] or report['results']['cpu']['command']['exit_code']!=0:
            raise RuntimeError('comparison requires actual successful stable-source CPU runs')
    for key in ['cases','input_sha256','tool_sha256']:
        if new[key]!=old[key]:raise RuntimeError('comparison binding differs '+key)
    for field in ['fixture/shared.hex','fixture/expected.hex','fixture/expected-flags.hex','revd-driver.bin']:
        if new['artifacts_sha256'][field]!=old['artifacts_sha256'][field]:raise RuntimeError('different fixture/firmware '+field)
    for name,digest in new['source_sha256'].items():
        if name=='rtl/revd_opt/core_stream_frontend_opt.sv':continue
        if name not in old['source_sha256'] or old['source_sha256'][name]!=digest:
            raise RuntimeError('different shared implementation '+name)
    if new['results']['cpu']['output_sha256']!=old['results']['cpu']['output_sha256']:
        raise RuntimeError('different actual output stream bytes')
    rows=[]
    for a,b in zip(new['results']['cpu']['task_metrics'],old['results']['cpu']['task_metrics'],strict=True):
        if a['task']!=b['task'] or a['effective_macs']!=1622016 or b['effective_macs']!=1622016:
            raise RuntimeError('task geometry or MAC accounting differs')
        rows.append({'task':a['task'],'case_id':new['cases'][a['task']]['case_id'],
          'baseline_cold_cycles':b['cold_cycles'],'candidate_cold_cycles':a['cold_cycles'],
          'cycles_saved':b['cold_cycles']-a['cold_cycles'],'cycle_reduction':1-a['cold_cycles']/b['cold_cycles'],
          'speedup':b['cold_cycles']/a['cold_cycles'],
          'baseline_core_cycles_with_cpu_output_backpressure':b['core_cycles'],
          'candidate_core_cycles_with_cpu_output_backpressure':a['core_cycles']})
    out=ROOT/'reports/revd_offline/soc'/('comparison-'+run_id());out.mkdir(parents=True,exist_ok=False)
    result={'status':'PASS','checked_utc':utc(),'comparison_scope':'Two independent FFN1 layer tasks in the same public E203 boot, each with cold X/W/bias loading; actual C/ICB/shared-memory responses.',
      'conditions':'Same exact shared image, firmware, adapter, SRAM response policy, tools and deterministic CPU supply/drain policy; no additional random stalls.',
      'baseline_new_profile':False,'baseline':'Accepted D2 micro, module identifier alias only','candidate':'CTX4 full-W PM4',
      'actual_output_bytes_equal':True,'tasks':rows,'competition_score':None,'physical_area_mm2':None,'energy_joules':None,
      'limitations':['Public behavioral E203/SRAM prototype, not contest platform acceptance.','Core window includes real CPU output backpressure; it is not a standalone core latency.','No measured physical timing, area or energy; no official score inference.'],
      'report_sha256':{str(p.relative_to(ROOT)):sha(p) for p in paths},'comparison_script_sha256':sha(Path(__file__))}
    put(out/'result.json',result);print('SOC_COMPARISON',out.relative_to(ROOT));print(rows)
if __name__=='__main__':main()
