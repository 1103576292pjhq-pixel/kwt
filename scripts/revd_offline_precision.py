"""Re-evaluate current RTL Y against pinned FP32 references, local subset only."""
from pathlib import Path
import argparse
import math
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
import numpy as np
from scripts.revd_offline_common import read_json,put,sha,run_id,utc
from scripts.revd_offline_gate import check_suite

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--suite',required=True);args=ap.parse_args()
    suite=ROOT/args.suite;check_suite(suite,36,4)
    out=ROOT/'reports/revd_offline/precision'/run_id();out.mkdir(parents=True,exist_ok=False)
    frozen=read_json(ROOT/'reports/prototype/vectors/manifest.json');runs=read_json(suite)
    entries={e['case']:e for e in runs['cases']};totals={l:[0.,0.,0] for l in range(1,13)};records=[]
    for case in frozen['cases']:
        entry=entries[case['case_id'].replace('/','_')];run=(ROOT/entry['manifest']).parent
        d=case['source_arrays']['Y'];reference=ROOT/'reports/model/baseline'/d['path']
        if sha(reference)!=d['sha256']:raise ValueError('FP32 reference SHA')
        truth=np.load(reference,allow_pickle=False).astype(np.float64);actual=np.empty((99,256),dtype=np.float64)
        for line in (run/'output.hex').read_text().splitlines():
            _,idx,y,*_=line.split();idx=int(idx,16);y=int(y,16);y=y-(1<<32) if y&(1<<31) else y
            actual.flat[idx]=y*case['config']['output_scale']
        if not np.isfinite(truth).all() or not np.isfinite(actual).all():raise ValueError('nonfinite actual/reference')
        sse=float(np.sum((actual-truth)**2));rsq=float(np.sum(truth**2));count=int(truth.size)
        metric=math.sqrt(sse/count)/max(math.sqrt(rsq/count),1e-8)
        values=totals[case['layer']];values[0]+=sse;values[1]+=rsq;values[2]+=count
        records.append({'case_id':case['case_id'],'layer':case['layer'],'nrmse':metric,'sse':sse,'reference_square_sum':rsq,'count':count,
                        'rtl_output_sha256':sha(run/'output.hex'),'reference_sha256':sha(reference)})
    layers=[{'layer':l,'sse':v[0],'reference_square_sum':v[1],'count':v[2],
             'nrmse':math.sqrt(v[0]/v[2])/max(math.sqrt(v[1]/v[2]),1e-8)} for l,v in totals.items()]
    error=max(v['nrmse'] for v in layers)
    result={'status':'PASS_LOCAL_ENGINEERING_SUBSET' if error<=.03 else 'FAIL','scope':'Two actual validation unknown WAVs and synthetic silence, 3 inputs x12 layers; not official600 or selected official12.',
            'formula':'e_l=sqrt(SSE_l/count_l)/max(sqrt(sum_reference_square_l/count_l),1e-8); e=max_l e_l',
            'worst_layer_nrmse':error,'layers':layers,'cases':records,'formal_score':None,'official_contest_acceptance':False,
            'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in [Path(__file__),ROOT/'scripts/revd_offline_gate.py',suite,ROOT/'reports/prototype/vectors/manifest.json']},'finished_utc':utc()}
    put(out/'summary.json',result);print(out,result['status'],error,flush=True);return 0 if error<=.03 else 1
if __name__=='__main__':raise SystemExit(main())
