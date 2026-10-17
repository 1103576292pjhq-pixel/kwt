"""Read-only independent final candidate ZIP inventory and payload closure."""
from pathlib import Path,PurePosixPath
import hashlib,json,os,sys,zipfile,stat,time
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from scripts.revd_offline_reproduce import manifest_check
out=Path(__file__).resolve().parent
python_binary=Path(sys.executable).resolve();python_sha_before=sha(python_binary)
if (out/'summary.json').exists():raise FileExistsError('refuse evidence overwrite')
stage=(ROOT/sys.argv[1]).resolve();folder=(ROOT/sys.argv[2]).resolve();archive=(ROOT/sys.argv[3]).resolve();proof_path=(ROOT/sys.argv[4]).resolve()
assert all(ROOT in p.parents for p in (stage,folder,archive,proof_path))
proof=json.loads(proof_path.read_text());manifest_bytes=(stage/'MANIFEST.json').read_bytes();manifest=json.loads(manifest_bytes);expected=manifest['files'];tests=[]
def test(name,okay,detail=None):
 tests.append({'name':name,'passed':bool(okay),'detail':detail})
 if not okay:raise AssertionError(name+': '+str(detail))
 test_output=None
# Published bytes must match the actual isolated stage proof, including its
# root manifest. The ZIP is read directly; no host extraction/deletion occurs.
test('stage_folder_manifest_identical',(folder/'MANIFEST.json').read_bytes()==manifest_bytes)
folder_manifest=manifest_check(folder,allow_runtime=False)
test('complete_published_folder_inventory_and_SHA',folder_manifest['manifest_sha256']==sha(stage/'MANIFEST.json'),folder_manifest)
test('proof_stage_manifest_binding',proof['status']=='PASS' and proof['package_manifest_sha256']==sha(stage/'MANIFEST.json'))
with zipfile.ZipFile(archive) as z:
 infos=z.infolist();names=[i.filename for i in infos];prefix=folder.name+'/'
 test('unique_zip_members',len(names)==len(set(names))==len({n.casefold() for n in names}))
 test('canonical_contained_regular_members',all(n.startswith(prefix) and n==PurePosixPath(n).as_posix() and not any(x in ('','.', '..') for x in n.split('/')) and '\\' not in n and ':' not in n and not stat.S_ISLNK(i.external_attr>>16) and not i.is_dir() for n,i in zip(names,infos)))
 actual={n[len(prefix):] for n in names};test('exact_manifest_member_set',actual==set(expected)|{'MANIFEST.json'},{'expected':len(expected)+1,'actual':len(actual)})
 test('zip_manifest_identical',z.read(prefix+'MANIFEST.json')==manifest_bytes)
 wrong=[]
 for name,digest in expected.items():
  h=hashlib.sha256()
  with z.open(prefix+name) as f:
   for block in iter(lambda:f.read(1048576),b''):h.update(block)
  if h.hexdigest()!=digest:wrong.append(name)
 test('every_zip_payload_SHA',not wrong,{'verified_files':len(expected),'mismatched':wrong})
 # Narrow closure of the root-confirmed missing baseline comparison evidence.
 comparison_path='reports/revd_offline/soc/comparison-20261017T064142Z_6f7686d3/result.json'
 comparison=json.loads(z.read(prefix+comparison_path))
 test('CPU_comparison_report_references_present_and_bound',all(expected.get(n)==h for n,h in comparison['report_sha256'].items()))
 baseline_path='reports/revd_offline/soc/soc-d2-20261017T063010Z/result.json';baseline=json.loads(z.read(prefix+baseline_path));baseline_dir=str(PurePosixPath(baseline_path).parent)
 ref=baseline['baseline_reference']
 test('frozen_D2_and_alias_bytes_bound',expected.get(ref['source'])==ref['source_sha256'] and expected.get(ref['alias'])==ref['alias_sha256'] and ref['new_profile'] is False)
 test('baseline_real_output_input_artifact_closure',all(expected.get(n)==h for n,h in baseline['input_sha256'].items()) and all(expected.get(baseline_dir+'/'+n)==h for n,h in baseline['artifacts_sha256'].items()))
 source_aliases={'config/e203-source-manifest.json':'evidence/original-e203-source-manifest.json'}
 test('baseline_source_inventory_closure',all(expected.get(source_aliases.get(n,n))==h for n,h in baseline['source_sha256'].items()))
 for run in ('soc-w2-small-20261017T080450Z','soc-w2-full-20261017T080700Z'):
  report=json.loads(z.read(prefix+'reports/revd_offline/soc/'+run+'/result.json'));exe=PurePosixPath(report['results']['cpu']['command']['argv'][0]).relative_to(str(ROOT)).as_posix()
  test('W2_actual_simulator_binary_'+run,expected.get(exe)==report['actual_simulator_executable_sha256'])
 cpu_closure_path=ROOT/'work/revd_offline_20261017/review_package_cpu_closure.json';cpu_closure=json.loads(cpu_closure_path.read_text())
 test('independent_CPU_closure_required_members_in_actual_ZIP',all(expected.get(q['path'])==q['current_sha256'] for q in cpu_closure['required_members']),{'plan_sha256':cpu_closure['new_plan_green']['sha256'],'review_sha256':sha(cpu_closure_path),'required_count':len(cpu_closure['required_members'])})
 test('required_licenses_present',all(p in expected for p in ['THIRD_PARTY.md','licenses/CC-BY-4.0.txt','licenses/provenance.json','vendor/keyword-transformer/LICENSE.txt','vendor/e203_hbirdv2-upstream/LICENSE']))
 package=json.loads(z.read(prefix+'PACKAGE.json'));summary=json.loads(z.read(prefix+'SUMMARY.json'))
 test('local_candidate_scope_retained',package['parent_accepted'] is False and package['official_contest_acceptance'] is False and package['formal_score'] is None and summary['official_contest_acceptance'] is False and summary['formal_score'] is None)
 readme=z.read(prefix+'README.md').decode('utf-8');third=z.read(prefix+'THIRD_PARTY.md').decode('utf-8')
 test('reader_entrypoints_and_limits',all(x in readme for x in ['scripts/revd_offline_reproduce.py','--suite manifest','--suite smoke','--suite numeric','--suite full36','--suite cpu-small','600','150 MHz']))
 test('third_party_derived_inventory_scope','evidence/original-*' in third and 'licenses/CC-BY-4.0.txt' in third and 'config/e203-source-manifest.json' in third)
test('python_binary_unchanged',sha(python_binary)==python_sha_before)
result={'schema_version':1,'status':'PASS' if all(t['passed'] for t in tests) else 'FAIL','created_utc':utc(),'pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'python_tool':{'executable':sys.executable,'resolved':str(python_binary),'version':sys.version,'sha256_before':python_sha_before,'sha256_after':sha(python_binary)},'probe_source_sha256':sha(Path(__file__)),'stage':str(stage.relative_to(ROOT)),'published_folder':str(folder.relative_to(ROOT)),'archive':str(archive.relative_to(ROOT)),'archive_sha256':sha(archive),'archive_bytes':archive.stat().st_size,'manifest_sha256':sha(stage/'MANIFEST.json'),'complete_folder_manifest':folder_manifest,'zip_member_count':len(names),'payload_verified_files':len(expected),'proof_sha256':sha(proof_path),'tests':tests,'test_count':len(tests),'mutation_policy':'Read-only stage/folder/ZIP/proof audit; no extraction, publication, source edits, or EDA.','parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result);print(json.dumps({'status':result['status'],'tests':len(tests),'files':len(expected),'zip_sha256':result['archive_sha256']}),flush=True)
