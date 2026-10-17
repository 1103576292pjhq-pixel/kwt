from pathlib import Path
import os,sys,types,copy,json
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks
out=Path(__file__).resolve().parent;p=ROOT/'scripts/revd_offline_gate.py';b=p.read_bytes();(out/'gate_snapshot.txt').write_bytes(b);gate=types.ModuleType('gate_snapshot');gate.__file__=str(p);exec(compile(b,str(p),'exec'),gate.__dict__);checks=Checks(gate)
numeric=ROOT/'reports/revd_offline/numeric/20261017T063223Z_43019020/summary.json';entry=next(t for t in gate.read_json(numeric)['tests'] if t['name']=='shift00');small=ROOT/entry['manifest'];checks.run('positive_real_current_small_numeric_case',lambda:gate.check_case(small))
summary=ROOT/'reports/revd_offline/core/ctx4-full36-l1-final-001/summary.json';original=gate.read_json(summary)
for role in ['production','repeat','small','cross','unknown_profile','red']:
 a=copy.deepcopy(original);a.update(profile=role);a['cases']=[{'case':'shift00','manifest':entry['manifest'],'status':'PASS','error':None}]
 checks.run('correct_small_numeric_case_mislabeled_as_'+role,lambda:gate.check_suite(summary,1,4),reject=True,json_overrides={summary:a})
# A derived checker fixture uses the real independently recompiled first
# frozen99x256 Icarus result; it is not claimed to be a new physical run.
repeat_case='reports/revd_offline/crosscheck/20261017T070407Z_11b4dece/icarus_l1/run_manifest.json'
frozen=gate.read_json(ROOT/'reports/prototype/vectors/manifest.json')['cases'][0]
base=copy.deepcopy(original);base.update(profile='repeat',cases=[{'case':frozen['case_id'].replace('/','_'),'manifest':repeat_case,'status':'PASS','error':None}])
checks.run('positive_repeat_role_with_real_independent_first_frozen_case',lambda:gate.check_suite(summary,1,4),json_overrides={summary:base})
for name,mutate in [('wrong_summary_PM',lambda a:a.update(pm=2)),('wrong_summary_latency',lambda a:a.update(latency=2)),('wrong_summary_baseline',lambda a:a.update(baseline=True)),('wrong_summary_simulator_role',lambda a:a.update(profile='cross')),('wrong_repeat_case_label',lambda a:a['cases'][0].update(case='forged/layer_01'))]:
 a=copy.deepcopy(base);mutate(a);checks.run(name,lambda:gate.check_suite(summary,1,4),reject=True,json_overrides={summary:a})
protocol=gate.read_json(ROOT/'reports/revd_offline/protocol/20261017T062232Z_d44560d2/summary.json');continuous=next(t for t in protocol['tests'] if t['name']=='continuous')
a=copy.deepcopy(base);a.update(profile='small',cases=[{'case':'m5n32','manifest':continuous['manifest'],'status':'PASS','error':None}])
checks.run('suite_case_requires_one_complete_task',lambda:gate.check_suite(summary,1,4),reject=True,fragments=('suite role requires one complete task',),json_overrides={summary:a})
roles={'small':{'case_count':4,'cases':[{'name':f'm{m}n{n}','M':m,'N':n,'shift':shift,'layer':1,'data':'synthetic(M,N,seed=M*N+PM)'} for m,n,shift in [(1,16,0),(3,16,16),(4,32,47),(5,32,8)]],'simulator':'icarus'},'production':{'case_count':1,'case':'synthetic99','M':99,'N':256,'shift':8,'layer':1,'data':'synthetic(99,256) default seed','simulator':'icarus'},'repeat':{'case_count':1,'case':'first frozen vectors manifest case','M':99,'N':256,'data':'exact frozen Xq/Wq/bq/config','simulator':'icarus'},'cross':{'case_count':1,'case':'m5n32','M':5,'N':32,'shift':8,'layer':1,'data':'synthetic(5,32,seed=5*32+PM)','simulator':'verilator'},'full36':{'case_count':36,'M':99,'N':256,'unique_outputs':912384,'data':'exact all36 frozen cases/arrays/config','simulator':'icarus'},'red':{'selectable':False,'data':'synthetic(5,32,seed=5*32+PM)','M':5,'N':32,'shift':8,'simulator':'icarus','note':'test-first failure profile, not accepted implementation'}}
result={'status':'PASS' if all(t['passed'] for t in checks.results) else 'FAIL','created_utc':utc(),'pid':os.getpid(),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'tests':checks.results,'actual_normal_core_runner_roles':roles,'distinct_full_size_cross_script':'scripts/revd_offline_crosscheck.py separately runs frozen first99x64x256 case in IcarusL1/VerilatorL1/VerilatorL2; it is not core_runner profile cross.','core_runner_sha256':sha(ROOT/'dv/revd_opt/core_runner.py'),'scope':'Only in-memory aggregate role/entries changes; actual small RTL run artifact remains byte-identical.','parent_accepted':False,'official_contest_acceptance':False};put(out/'summary.json',result);print(json.dumps({'status':result['status'],'false_accepts':[t['name'] for t in checks.results if t['expected']=='REJECT' and t['actual']=='ACCEPT'],'source_unchanged':result['source_unchanged']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
