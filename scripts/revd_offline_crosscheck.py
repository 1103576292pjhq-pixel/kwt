"""Independent fresh-process full-size repeats in two actual simulators."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT));sys.path.insert(0,str(ROOT/'dv/revd_opt'))
from core_runner import run_case
from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
from scripts.revd_offline_common import put,sha,run_id,utc
from scripts.revd_offline_gate import check_case

def main():
    out=ROOT/'reports/revd_offline/crosscheck'/run_id();out.mkdir(parents=True,exist_ok=False)
    manifest,verified=verify_frozen_inputs(ROOT);c=manifest['cases'][0];a=validated_case(ROOT,c);results=[]
    for sim,latency in [('icarus',1),('verilator',1),('verilator',2)]:
        folder=out/f'{sim}_l{latency}'
        r=run_case(folder,a['Xq'],a['Wq'],a['bq'],c['config']['output_shift'],latency=latency,layer=c['layer'],simulator=sim)
        checked=check_case(folder/'run_manifest.json') if r['status']=='PASS' else None
        results.append({'simulator':sim,'latency':latency,'status':r['status'],'manifest':str((folder/'run_manifest.json').relative_to(ROOT)),
                        'independent_check':checked,'error':r.get('error'),'output_sha256':sha(folder/'output.hex') if (folder/'output.hex').exists() else None})
        print(sim,latency,r['status'],r.get('error',''),flush=True)
        if r['status']!='PASS':break
    ok=len(results)==3 and all(r['status']=='PASS' for r in results) and len({r['output_sha256'] for r in results})==1
    put(out/'summary.json',{'status':'PASS' if ok else 'FAIL','case_id':c['case_id'],'frozen_input_verification':verified,
                          'runs':results,'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__)},'finished_utc':utc()})
    print(out,flush=True);return 0 if ok else 1
if __name__=='__main__':raise SystemExit(main())
