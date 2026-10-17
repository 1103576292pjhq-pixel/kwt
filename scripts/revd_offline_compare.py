"""Finite released PM/latency comparisons on identical cold input streams."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT));sys.path.insert(0,str(ROOT/'dv/revd_opt'))
from core_runner import run_case,synthetic
from scripts.revd_offline_common import put,sha,run_id,utc

def main():
    out=ROOT/'reports/revd_offline/comparison'/run_id();out.mkdir(parents=True,exist_ok=False)
    x,w,b=synthetic(99,256);results=[]
    for label,pm,latency,baseline in [('D2_pm4_l1',4,1,True),('CTX4_pm4_l1',4,1,False),
                                      ('D2_pm4_l2',4,2,True),('CTX4_pm4_l2',4,2,False),
                                      ('CTX4_pm2_l1',2,1,False),('CTX4_pm2_l2',2,2,False)]:
        r=run_case(out/label,x,w,b,8,pm,latency,baseline=baseline)
        results.append({'profile':label,'new_profile':not baseline,'status':r['status'],
                        'manifest':str((out/label/'run_manifest.json').relative_to(ROOT)),
                        'counters':r.get('counters'),'cold_windows':r.get('cold_windows'),
                        'actual_banks':r.get('banks'),'error':r.get('error')})
        print(label,r['status'],r.get('cold_windows',r.get('error')),flush=True)
        if r['status']!='PASS':break
    comparisons=[]
    if len(results)==6 and all(r['status']=='PASS' for r in results):
        for base,opt in [(results[0],results[1]),(results[2],results[3])]:
            a,b=base['cold_windows'][0],opt['cold_windows'][0]
            comparisons.append({'baseline':base['profile'],'candidate':opt['profile'],
              'scope':'public stream frontend/core proxy, not CPU or contest throughput',
              'cold_frontend_speedup':a['frontend_elapsed_cycles']/b['frontend_elapsed_cycles'],
              'cold_frontend_reduction_fraction':1-b['frontend_elapsed_cycles']/a['frontend_elapsed_cycles'],
              'core_speedup':a['core_elapsed_cycles']/b['core_elapsed_cycles'],
              'x_reads_baseline':sum(v[1] for v in base['actual_banks']['X']),
              'x_reads_candidate':sum(v[1] for v in opt['actual_banks']['X']),
              'physical_area_mm2':None,'power_W':None,'energy_J':None,'formal_score':None})
    result={'status':'PASS' if len(results)==6 and all(r['status']=='PASS' for r in results) else 'FAIL',
            'finished_utc':utc(),'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__)},
            'cases':results,'comparisons':comparisons,'selection_note':'Retain PM2/PM4 Pareto options while technology area/energy are unknown; PM4 is throughput-oriented local default only.'}
    put(out/'summary.json',result);print(out,flush=True)
    return 0 if result['status']=='PASS' else 1
if __name__=='__main__':raise SystemExit(main())
