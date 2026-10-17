"""All public shift values and signed-dot/bias edges for the W1 namespace."""
import argparse
from pathlib import Path
import numpy as np
from tiled_runner import ROOT,run_case
from scripts.revd_offline_common import put,sha,run_id

def main():
    p=argparse.ArgumentParser();p.add_argument('--run-id');args=p.parse_args()
    out=ROOT/'reports/revd_offline/tiled'/(args.run_id or run_id());out.mkdir(parents=True,exist_ok=False);tests=[]
    # Nonzero signed dot exercises W ownership/addressing in each of two tiles;
    # bias values include clipping extrema and exact/below/above half-way ties.
    x=np.zeros((3,64),dtype=np.int16);x[:,63]=[-32768,-3,32767]
    w=np.zeros((64,32),dtype=np.int16);w[63]=np.array([-32768,32767,0,1,-1,0,0,0]*4,dtype=np.int16)
    for shift in range(48):
        half=1<<(shift-1) if shift else 0
        vals=[0,1,-1,(1<<47)-1,-(1<<47),(1<<31)-1,-(1<<31)]
        vals += [sign*((q<<shift)+half+d) for q in (0,1,2,3) for sign in (-1,1) for d in (-1,0,1)]
        vals=[v for v in vals if -(1<<47)<=v<(1<<47)]
        b=np.array((vals*32)[:32],dtype=np.int64)
        r=run_case(out/f'shift{shift:02d}',x,w,b,shift,latency=1+(shift%2))
        tests.append({'name':f'shift{shift:02d}','status':r['status'],'manifest':str((out/f'shift{shift:02d}'/'run_manifest.json').relative_to(ROOT))})
        print(f'shift{shift:02d}',r['status'],r.get('error',''),flush=True)
        if r['status']!='PASS':break
    summary={'status':'PASS' if len(tests)==48 and all(t['status']=='PASS' for t in tests) else 'FAIL','tests':tests,
             'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__)},'scope':'Public W1 namespace signed/k63/bias/shift edges; shared frozen epilogue unit already separately checked by main lane.'}
    put(out/'summary.json',summary);print(out,flush=True);return 0 if summary['status']=='PASS' else 1

if __name__=='__main__':raise SystemExit(main())
