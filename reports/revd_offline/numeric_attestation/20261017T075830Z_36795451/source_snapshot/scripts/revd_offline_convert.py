"""Reproduce the frozen dyadic conversion without calibration or parameter search."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
import numpy as np
from numeric.fixedpoint import quantize_signed
from scripts.revd_offline_common import read_json,put,sha,run_id,utc

def main():
    out=ROOT/'reports/revd_offline/conversion'/run_id();out.mkdir(parents=True,exist_ok=False)
    manifest=read_json(ROOT/'reports/prototype/vectors/manifest.json');records=[]
    for case in manifest['cases']:
        dest=out/case['case_id'];dest.mkdir(parents=True)
        record={'case_id':case['case_id'],'layer':case['layer'],'config':case['config'],'inputs':{},'outputs':{}}
        for name,key,scale,bits,dtype in [('X','Xq','input_scale',16,np.int16),('W','Wq','weight_scale',16,np.int16),('b','bq','product_scale',48,np.int64)]:
            info=case['source_arrays'][name];source=ROOT/'reports/model/baseline'/info['path']
            if sha(source)!=info['sha256']:raise ValueError('float source SHA '+str(source))
            converted,stats=quantize_signed(np.load(source,allow_pickle=False),case['config'][scale],bits)
            target=dest/(key+'.npy');np.save(target,converted.astype(dtype),allow_pickle=False)
            if sha(target)!=case['arrays'][key]['sha256']:raise ValueError('frozen conversion differs '+case['case_id']+'/'+key)
            record['inputs'][str(source.relative_to(ROOT))]=sha(source)
            record['outputs'][key]={'path':str(target.relative_to(out)),'sha256':sha(target),'stats':stats}
        records.append(record)
    result={'status':'PASS','scope':'Frozen existing layer scales/shift, no fitting or search; validation/test labels unused.',
            'cases':records,'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in [Path(__file__),ROOT/'numeric/fixedpoint.py',ROOT/'reports/prototype/vectors/manifest.json']},'finished_utc':utc()}
    put(out/'summary.json',result);print(out,'PASS',len(records),flush=True);return 0
if __name__=='__main__':raise SystemExit(main())
