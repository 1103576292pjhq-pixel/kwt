"""Fresh actual proof positive for metadata-only archive closure revision."""
from pathlib import Path
from unittest.mock import patch
import sys,types,os,json
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
import scripts.revd_offline_reproduce as reproduce
out=Path(__file__).resolve().parent
if (out/'summary.json').exists():raise FileExistsError('refuse review overwrite')
stage=(ROOT/sys.argv[1]).resolve();proof_path=(ROOT/sys.argv[2]).resolve();old=ROOT/'reports/revd_offline/package_review/package-final-proof-20261017T074946Z/summary.json'
assert ROOT in stage.parents and ROOT in proof_path.parents
negative=json.loads(old.read_text());assert negative['status']=='PASS' and negative['test_count']==27 and negative['negative_count']==26
source0={name:sha(ROOT/name) for name in negative['source_sha256']};assert source0==negative['source_sha256'],'proof validator sources differ from independently negative-tested bytes'
python_binary=Path(sys.executable).resolve();python0=sha(python_binary);probe0=sha(Path(__file__))
manifest=reproduce.manifest_check(stage,allow_runtime=False);manifest0=sha(stage/'MANIFEST.json');proof0=sha(proof_path)
publisher=ROOT/'scripts/package_revd_candidate.py';code=publisher.read_bytes();(out/'publisher_snapshot.txt').write_bytes(code);m=types.ModuleType('publisher');m.__file__=str(publisher);exec(compile(code,str(publisher),'exec'),m.__dict__)
original_exists=Path.exists;target=ROOT/'deliverables'/m.NAME;archive=target.with_suffix('.zip')
class ReachedPublication(Exception):pass
def exists_view(p):return False if p in (target,archive) else original_exists(p)
def cached_manifest(root=None,allow_runtime=True):
 assert Path(root).resolve()==stage and allow_runtime is False
 assert sha(stage/'MANIFEST.json')==manifest0
 return manifest
with patch.object(Path,'exists',exists_view),patch.object(m.shutil,'copytree',side_effect=ReachedPublication),patch.object(reproduce,'manifest_check',cached_manifest):
 try:m.publish(stage,proof_path)
 except ReachedPublication:validated=True
 else:raise AssertionError('unexpected publication boundary')
proof=json.loads(proof_path.read_text());extracted=(ROOT/proof['extraction']).resolve();detail_path=(ROOT/proof['portable_result']).resolve();detail=json.loads(detail_path.read_text())
assert detail['completed_phases']==['manifest','smoke','numeric','cpu-small']
phases={q['phase']:q for q in detail['phase_results']};assert set(phases)=={'smoke','numeric','cpu-small'}
assert len(phases['smoke']['runs'])==2 and all(q['status']=='PASS' and q['outputs']==160 for q in phases['smoke']['runs'])
assert phases['numeric']['gate']=={'status':'PASS','unit_vectors':2170,'public_core_cases':52,'all_shifts':48}
assert phases['cpu-small']['gate']['status']=='PASS' and phases['cpu-small']['gate']['tasks']==2 and phases['cpu-small']['gate']['outputs']==96
actual_phase_evidence=[]
for name in ('numeric','cpu-small'):
 q=phases[name];evidence=extracted/q['evidence'];command=q['command'];log=extracted/command['log']
 assert evidence.is_file() and sha(evidence)==q['evidence_sha256'] and command['exit_code']==0 and command['pid']>0
 assert sha(log)==command['log_sha256'] and json.loads(log.with_suffix('.log.command.json').read_text())==command
 actual_phase_evidence.append({'phase':name,'evidence':str(evidence.relative_to(ROOT)),'sha256':sha(evidence),'actual_child_pid':command['pid'],'actual_child_exit_code':command['exit_code']})
assert all(extracted in Path(p).resolve().parents for p in detail['local_module_origins'].values())
assert sha(stage/'MANIFEST.json')==manifest0 and sha(proof_path)==proof0 and source0=={n:sha(ROOT/n) for n in source0} and sha(python_binary)==python0 and sha(Path(__file__))==probe0
r={'schema_version':1,'status':'PASS','created_utc':utc(),'pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'stage':str(stage.relative_to(ROOT)),'proof':str(proof_path.relative_to(ROOT)),'proof_sha256':proof0,'manifest':manifest,'source_sha256':source0,'negative_test_reused':{'path':str(old.relative_to(ROOT)),'sha256':sha(old),'positive_count':1,'negative_count':26,'source_identity_exact':True},'actual_portable_detail':str(detail_path.relative_to(ROOT)),'actual_portable_detail_sha256':sha(detail_path),'actual_portable_pid':proof['commands'][0]['pid'],'actual_portable_exit_code':proof['commands'][0]['exit_code'],'actual_completed_phases':detail['completed_phases'],'actual_phase_evidence':actual_phase_evidence,'python_tool':{'executable':sys.executable,'resolved':str(python_binary),'sha256_before':python0,'sha256_after':sha(python_binary)},'probe_source_sha256':probe0,'source_unchanged':True,'proof_unchanged':True,'actual_publication_performed':False,'mutation_policy':'One actual complete immutable-stage manifest hash, then original publisher proof validation with only final copytree sentinel and cached completed manifest guard. No stage/publication edits. All26 negatives reuse identical source bytes; actual new portable child and phase receipts bound.','parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',r);print(json.dumps({'status':'PASS','members':manifest['members'],'manifest_sha256':manifest0,'actual_portable_pid':r['actual_portable_pid']}),flush=True)
