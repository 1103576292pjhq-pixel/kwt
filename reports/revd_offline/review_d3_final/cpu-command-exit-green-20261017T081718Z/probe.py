from pathlib import Path
import os,sys,types,copy,json
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks
out=Path(__file__).resolve().parent;p=ROOT/'scripts/revd_offline_gate.py';b=p.read_bytes();(out/'gate_snapshot.txt').write_bytes(b);gate=types.ModuleType('gate_snapshot');gate.__file__=str(p);exec(compile(b,str(p),'exec'),gate.__dict__);checks=Checks(gate)
path=ROOT/'reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json';base=gate.read_json(path);checks.run('positive_current_source_full_PM4_CPU',lambda:gate.check_cpu(path))
for code in (124,1):
 a=copy.deepcopy(base);c=a['commands'][0];assert c['argv']==['riscv64-unknown-elf-gcc','--version'];c['exit_code']=code;side=(ROOT/c['log']).with_suffix('.log.command.json')
 checks.run('real_tool_version_subprocess_exit_'+str(code),lambda:gate.check_cpu(path),reject=True,json_overrides={path:a,side:c})
small=ROOT/'reports/revd_offline/soc/soc-current-small-20261017T081500Z/result.json';small_r=gate.read_json(small)
checks.run('positive_current_source_small_real_CPU_and_both_controls',lambda:gate.check_cpu(small))
for key in ('negative_cpu_return','negative_wrong_expected'):
 for code in (124,0):
  a=copy.deepcopy(small_r);old=copy.deepcopy(a['results'][key]['command']);new=copy.deepcopy(old);new['exit_code']=code;a['results'][key]['command']=new
  for i,c in enumerate(a['commands']):
   if c==old:a['commands'][i]=new
  side=(ROOT/new['log']).with_suffix('.log.command.json')
  checks.run(key+'_coherent_wrong_exit_'+str(code),lambda:gate.check_cpu(small),reject=True,fragments=('CPU negative must fail functionally',),json_overrides={small:a,side:new})
 log=ROOT/small_r['results'][key]['command']['log'];marker_text='CPU_EXIT_FAILURE' if key=='negative_cpu_return' else 'CPU output mismatch task=0 index=0'
 checks.run(key+'_missing_functional_failure_marker',lambda:gate.check_cpu(small),reject=True,fragments=('CPU negative must fail functionally',),text_overrides={log:lambda text,marker_text=marker_text:text.replace(marker_text,'NO_EXPECTED_FAILURE_MARKER')})
for folder in ['soc-layers03-04-20261017T064820Z','soc-layers05-06-20261017T070120Z','soc-layers07-08-20261017T071130Z','soc-layers09-10-20261017T071950Z','soc-layers11-12-20261017T073140Z']:
 cp=ROOT/'reports/revd_offline/soc'/folder/'result.json';checks.run('positive_rebind_'+folder,lambda cp=cp:gate.check_cpu(cp))
# Prove pure gate change does not change the source/numeric/protocol/role
# functions already independently exercised in the101-case e3f705 batch.
import ast,hashlib
old_path=ROOT/'reports/revd_offline/review_d3_final/cpu-accepted-20261017T075635Z/gate_snapshot.txt'
def function_map(text):
 return {node.name:hashlib.sha256(ast.dump(node,include_attributes=False).encode()).hexdigest() for node in ast.parse(text).body if isinstance(node,(ast.FunctionDef,ast.AsyncFunctionDef))}
old_functions=function_map(old_path.read_text());new_functions=function_map(b.decode())
unchanged={name:old_functions[name]==new_functions.get(name) for name in old_functions if name!='check_cpu'}
assert all(unchanged.values()),unchanged
put(out/'semantic_rebinding.json',{'old_gate_sha256':sha(old_path),'new_gate_sha256':sha(p),'unchanged_non_CPU_function_AST_SHA':{name:new_functions[name] for name in unchanged},'all_non_CPU_functions_unchanged':True,'CPU_known_fix_dynamic_tests':len(checks.results),'existing101_evidence':'reports/revd_offline/review_d3_final/d3-accepted-20261017T075635Z/summary.json','hardware_rerun_performed':False})
result={'status':'PASS' if all(t['passed'] for t in checks.results) else 'FAIL','created_utc':utc(),'pid':os.getpid(),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'tests':checks.results,'test_count':len(checks.results),'small_evidence_sha256':sha(small),'semantic_rebinding_sha256':sha(out/'semantic_rebinding.json'),'scope':'Current-source strict real full PM4 positive. Only actual GCC-version receipt exit+matching JSON sidecar overlaid; no historical relaxations or old file writes.','parent_accepted':False,'official_contest_acceptance':False};put(out/'summary.json',result);print(json.dumps({'status':result['status'],'false_accepts':[t['name'] for t in checks.results if t['actual']=='ACCEPT' and t['expected']=='REJECT']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
