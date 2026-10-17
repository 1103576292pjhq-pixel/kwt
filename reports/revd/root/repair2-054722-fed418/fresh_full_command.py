import json,sys
from pathlib import Path
sys.path[:0]=['.','dv/revd']
from d2_runner import run_case
from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
root=Path('.').resolve();manifest,_=verify_frozen_inputs(root)
c=next(c for c in manifest['cases'] if c['layer']==12)
a=validated_case(root,c)
r=run_case(root/'reports/revd/root/repair2-054722-fed418/fresh_full_layer12_lat2',a['Xq'],a['Wq'],a['bq'],c['config']['output_shift'],pm=4,latency=2,task=172,layer=12)
print(json.dumps({'status':r['status'],'outputs':r.get('comparison'),'counters':r.get('counters'),'case_id':c['case_id']}))
raise SystemExit(0 if r['status']=='PASS' else 1)
