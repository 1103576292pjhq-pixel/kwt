"""Independent real final proof validation; never publish or alter the stage."""
from pathlib import Path
import sys,types,json,copy,os,time
from unittest.mock import patch
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks,identity
import scripts.revd_offline_reproduce as reproduce
out=Path(__file__).resolve().parent
python_binary=Path(sys.executable).resolve();python_sha_before=sha(python_binary)
if (out/'summary.json').exists():raise FileExistsError('refuse overwriting independent review evidence')
stage=(ROOT/sys.argv[1]).resolve();proof_path=(ROOT/sys.argv[2]).resolve()
assert ROOT in stage.parents and ROOT in proof_path.parents
sources=['scripts/package_revd_candidate.py','scripts/revd_offline_reproduce.py','scripts/revd_offline_package_check.py','scripts/revd_offline_final_regression.py']
before={p:sha(ROOT/p) for p in sources};p=ROOT/sources[0];data=p.read_bytes();(out/'publisher_snapshot.txt').write_bytes(data);m=types.ModuleType('publisher_snapshot');m.__file__=str(p);exec(compile(data,str(p),'exec'),m.__dict__)
original_manifest=reproduce.manifest_check
manifest_before=original_manifest(stage,allow_runtime=False)
proof_sha_before=sha(proof_path);probe_sha_before=sha(Path(__file__));proof=m.read_json(proof_path);detail_path=(ROOT/proof['portable_result']).resolve();detail=m.read_json(detail_path)
checks=Checks(m)
class ValidationReached(Exception):pass
original_exists=Path.exists
target=ROOT/'deliverables'/m.NAME;archive=target.with_suffix('.zip')
def exists_view(path):
 return False if path in (target,archive) else original_exists(path)
def validation():
 # All actual validation runs. Only the final filesystem mutation is replaced.
 with patch.object(Path,'exists',exists_view),patch.object(m.shutil,'copytree',side_effect=ValidationReached):
  try:m.publish(stage,proof_path)
  except ValidationReached:return {'status':'VALIDATION_REACHED_BEFORE_PUBLICATION'}
  raise AssertionError('publication did not stop at the expected mutation boundary')
# Stage is immutable in this metadata-only batch. Avoid repeatedly hashing tens
# of thousands of identical files for each proof mutation; independently hash
# the complete exact inventory again after every semantic probe has finished.
def cached_manifest(root=None,allow_runtime=True):
 if Path(root).resolve()!=stage or allow_runtime is not False:raise AssertionError('unexpected manifest guard invocation')
 if sha(stage/'MANIFEST.json')!=manifest_before['manifest_sha256']:raise ValueError('stage manifest changed during proof probes')
 return manifest_before

def proof_negative(name,mutate,coherent=True):
 a=copy.deepcopy(proof);mutate(a);overrides={proof_path:a}
 if coherent and a.get('commands'):
  c=a['commands'][0];overrides[(ROOT/c['log']).with_suffix('.log.command.json')]=c
 return checks.run(name,validation,reject=True,json_overrides=overrides)
with patch.object(reproduce,'manifest_check',cached_manifest):
 checks.run('positive_actual_final_portable_proof',validation)
 proof_negative('missing_real_command',lambda a:a.update(commands=[]))
 proof_negative('fake_interpreter_true',lambda a:a['commands'][0]['argv'].__setitem__(0,'/usr/bin/true'))
 proof_negative('wrong_child_suite_smoke',lambda a:a['commands'][0]['argv'].__setitem__(a['commands'][0]['argv'].index('--suite')+1,'smoke'))
 proof_negative('nonzero_actual_exit',lambda a:a['commands'][0].update(exit_code=1))
 proof_negative('missing_real_PID',lambda a:a['commands'][0].update(pid=0))
 proof_negative('excessive_child_timeout',lambda a:a['commands'][0].update(timeout_seconds=9999))
 proof_negative('wrong_child_cwd_original_ROOT',lambda a:a['commands'][0].update(cwd=str(ROOT)))
 proof_negative('missing_required_numeric_suite',lambda a:a.update(suites=['manifest','smoke']))
 proof_negative('source_changed_flag',lambda a:a.update(source_unchanged=False))
 proof_negative('missing_isolation_flag',lambda a:a.update(python_isolated_flag=False))
 proof_negative('omitted_checker_source',lambda a:a['source_sha256'].pop('scripts/revd_offline_package_check.py'))
 proof_negative('wrong_archive_SHA',lambda a:a.update(archive_sha256='0'*64))
 proof_negative('wrong_package_manifest_SHA',lambda a:a.update(package_manifest_sha256='0'*64))
 proof_negative('wrong_entry_SHA',lambda a:a.update(entry_sha256='0'*64))
 proof_negative('outside_extraction_ROOT',lambda a:a.update(extraction='.'))
 proof_negative('portable_result_outside_extraction',lambda a:a.update(portable_result='work/revd_offline_20261017/STATUS.json'))
 for name,mutate in [('detail_claimed_FAIL',lambda a:a.update(status='FAIL')),('detail_wrong_suite',lambda a:a.update(suite='smoke')),('detail_missing_numeric_phase',lambda a:a.update(completed_phases=['manifest','smoke'])),('detail_wrong_manifest_SHA',lambda a:a['manifest'].update(manifest_sha256='0'*64)),('detail_python_not_actual_interpreter',lambda a:a.update(python='/usr/bin/true')),('detail_tools_changed',lambda a:a.update(tools_unchanged=False)),('detail_empty_tool_inventory',lambda a:a.update(tool_binary_sha256_before={},tool_binary_sha256_after={})),('detail_tool_before_after_mismatch',lambda a:next(iter(a['tool_binary_sha256_after'])) and a['tool_binary_sha256_after'].__setitem__(next(iter(a['tool_binary_sha256_after'])),'0'*64))]:
  a=copy.deepcopy(detail);mutate(a);checks.run(name,validation,reject=True,json_overrides={detail_path:a})
 log=ROOT/proof['commands'][0]['log']
 checks.run('missing_actual_success_log_marker',validation,reject=True,text_overrides={log:lambda text:text.replace(str(detail_path.parent)+' PASS','NO_PORTABLE_SUCCESS')})
 sidecar=log.with_suffix('.log.command.json');a=copy.deepcopy(proof['commands'][0]);a['pid']+=1
 checks.run('actual_command_receipt_disagrees',validation,reject=True,json_overrides={sidecar:a})
manifest_after=original_manifest(stage,allow_runtime=False)
changed=[p for p,d in before.items() if sha(ROOT/p)!=d]
ok=all(t['passed'] for t in checks.results) and manifest_after==manifest_before and not changed and sha(proof_path)==proof_sha_before and sha(Path(__file__))==probe_sha_before and sha(python_binary)==python_sha_before
result={'schema_version':1,'status':'PASS' if ok else 'FAIL','created_utc':utc(),'pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'stage':str(stage.relative_to(ROOT)),'probe_source_sha256':probe_sha_before,'proof_sha256_before':proof_sha_before,'proof_unchanged':sha(proof_path)==proof_sha_before,'proof':identity(proof_path),'portable_detail':identity(detail_path),'python_tool':{'executable':sys.executable,'resolved':str(python_binary),'version':sys.version,'sha256_before':python_sha_before,'sha256_after':sha(python_binary)},'source_sha256':before,'changed_sources':changed,'complete_manifest_before':manifest_before,'complete_manifest_after':manifest_after,'tests':checks.results,'test_count':len(checks.results),'positive_count':sum(t['expected']=='ACCEPT' for t in checks.results),'negative_count':sum(t['expected']=='REJECT' for t in checks.results),'actual_publication_performed':False,'mutation_policy':'Actual publisher proof validation positive; final copytree replaced by sentinel. All proof probes use in-memory JSON/text and a cached successful immutable-stage manifest guard; complete actual manifest independently validated before and after. No original file changed.','parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result);print(json.dumps({'status':result['status'],'tests':len(checks.results),'failed':[t['name'] for t in checks.results if not t['passed']],'source_changed':changed}),flush=True);raise SystemExit(0 if ok else 1)
