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
result={'status':'PASS' if all(t['passed'] for t in checks.results) else 'FAIL','created_utc':utc(),'pid':os.getpid(),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'tests':checks.results,'test_count':len(checks.results),'scope':'Current-source strict real full PM4 positive. Only actual GCC-version receipt exit+matching JSON sidecar overlaid; no historical relaxations or old file writes.','parent_accepted':False,'official_contest_acceptance':False};put(out/'summary.json',result);print(json.dumps({'status':result['status'],'false_accepts':[t['name'] for t in checks.results if t['actual']=='ACCEPT' and t['expected']=='REJECT']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
