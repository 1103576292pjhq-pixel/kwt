from pathlib import Path
import os,sys,types,copy,json
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks
out=Path(__file__).resolve().parent;p=ROOT/'scripts/revd_offline_gate.py';b=p.read_bytes();(out/'gate_snapshot.txt').write_bytes(b);gate=types.ModuleType('gate_snapshot');gate.__file__=str(p);exec(compile(b,str(p),'exec'),gate.__dict__);checks=Checks(gate)
path=ROOT/'reports/revd_offline/soc/soc-small-v-20261017T061810Z/result.json';base=gate.read_json(path)
checks.run('positive_historical_small_CPU_including_two_fatal_negatives',lambda:gate.check_cpu(path,current=False))
for key in ('negative_cpu_return','negative_wrong_expected'):
 a=copy.deepcopy(base);old=copy.deepcopy(a['results'][key]['command']);new=copy.deepcopy(old);new['exit_code']=124;a['results'][key]['command']=new
 for i,c in enumerate(a['commands']):
  if c==old:a['commands'][i]=new
 log=ROOT/new['log'];side=log.with_suffix('.log.command.json')
 checks.run(key+'_coherent_timeout124_with_original_fatal_marker',lambda:gate.check_cpu(path,current=False),reject=True,json_overrides={path:a,side:new})
result={'status':'PASS' if all(t['passed'] for t in checks.results) else 'FAIL','created_utc':utc(),'pid':os.getpid(),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'tests':checks.results,'test_count':len(checks.results),'historical_source_mode':True,'not_current_CPU_acceptance':True,'known_stale_historical_runner':'Only normal soc_run.py3d68c40b differs from currentf17b5f42; all original bytes preserved.','mutation_scope':'Only negative CPU subprocess exit124 in matching aggregate/result/sidecar JSON view; actual original negative process exits-6 and logs unchanged. No old source/report changed.','parent_accepted':False,'official_contest_acceptance':False};put(out/'summary.json',result);print(json.dumps({'status':result['status'],'false_accepts':[t['name'] for t in checks.results if t['actual']=='ACCEPT' and t['expected']=='REJECT']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
