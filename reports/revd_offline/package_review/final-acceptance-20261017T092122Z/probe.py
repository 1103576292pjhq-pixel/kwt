"""Metadata/receipt final review; no EDA, tree walk or source edits."""
from pathlib import Path
import json,os,sys,hashlib
from datetime import datetime,timezone
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
out=Path(__file__).resolve().parent;target=ROOT/'work/revd_offline_20261017/review_package_final.json'
if target.exists() or (out/'summary.json').exists():raise FileExistsError('refuse final review overwrite')
def get(p):return json.loads((ROOT/p).read_text())
def ident(p):return {'path':str(p),'sha256':sha(ROOT/p)}
proof_path='work/revd_offline_20261017/package_checks/20261017T091521Z_81edc325/result.json'
material_path='work/revd_offline_20261017/materializations/20261017T091444Z_aba21dd0/result.json'
zip_review_path='reports/revd_offline/package_review/zip-final-20261017T082419Z/summary.json'
rebind_path='reports/revd_offline/package_review/package-final-rebind-20261017T084744Z/summary.json'
negative_path='reports/revd_offline/package_review/package-final-proof-20261017T074946Z/summary.json'
p=get(proof_path);mat=get(material_path);zr=get(zip_review_path);rb=get(rebind_path);neg=get(negative_path)
handoff_path='work/revd_offline_20261017/final_archive_timeout_handoff_final.json';handoff=get(handoff_path);initial_handoff=get(handoff['initial_handoff']);exit_observation=get(handoff['checker_exit_evidence'])
assert initial_handoff['checker_pid']==420 and initial_handoff['portable_pid']==467 and initial_handoff['candidate_sources_changed'] is False and initial_handoff['numeric_or_simulation_timeouts_removed'] is False
assert handoff['checker_exit_code']==exit_observation['checker_exit_code']==0 and handoff['portable_exit_code']==0
assert handoff['outer_exit_code']==1 and handoff['source_or_gate_changed'] is False and handoff['hard_deadline_changed'] is False
assert sha(ROOT/handoff['checker_exit_evidence'])==handoff['checker_exit_evidence_sha256']
assert hashlib.sha256(exit_observation['proc_stat'].encode()).hexdigest()==exit_observation['proc_stat_sha256'] and os.waitstatus_to_exitcode(int(exit_observation['proc_stat'].split()[-1]))==0
assert p['status']=='PASS' and p['archive']=='deliverables/kwt_revd_v2_candidate_20261017.zip'
assert zr['status']=='PASS' and zr['test_count']==20 and all(q['passed'] for q in zr['tests'])
assert rb['status']=='PASS' and neg['status']=='PASS' and neg['negative_count']==26
assert p['archive_sha256']==mat['archive_sha256']==zr['archive_sha256']=='949037af1a6b32176ddcd80d671702e32763b04d83e624165ea613484a876795'
assert sha(ROOT/p['archive'])==p['archive_sha256']
assert p['package_manifest_sha256']==zr['manifest_sha256']==mat['manifest_after']['manifest_sha256']=='e1366b19888466c9026e038074ede60325edbb9c3bef803f123e265238829ef2'
assert mat['manifest_after']==mat['manifest_before']==rb['manifest']==zr['complete_folder_manifest']
assert mat['independent_review_sha256']==sha(ROOT/rebind_path) and mat['proof_sha256']==sha(ROOT/mat['proof'])
for k in ('independent_execution',):assert sha(ROOT/mat[k])==mat[k+'_sha256']
assert mat['materializer_source_sha256']==sha(ROOT/'scripts/revd_offline_materialize.py')
assert rb['source_sha256']==neg['source_sha256']==mat['validator_source_sha256']
assert all(sha(ROOT/n)==h for n,h in rb['source_sha256'].items())
assert p['source_unchanged'] and set(p['source_sha256'])=={'scripts/revd_offline_package_check.py','scripts/revd_offline_common.py'} and all(sha(ROOT/n)==h for n,h in p['source_sha256'].items())
assert p['suites']==['manifest','smoke','numeric','cpu-small'] and p['python_isolated_flag'] and p['original_root_excluded_from_pythonpath']
assert len(p['commands'])==1
c=p['commands'][0];extracted=(ROOT/p['extraction']).resolve();detail_path=ROOT/p['portable_result'];d=json.loads(detail_path.read_text());log=ROOT/c['log']
assert c['exit_code']==0 and c['pid']>0 and 0<c['timeout_seconds']<=899
assert c['argv'][1:]==['-I','-B',str(extracted/'scripts/revd_offline_reproduce.py'),'--suite','portable','--with-cpu'] and Path(c['cwd']).resolve()==extracted
assert sha(log)==c['log_sha256'] and json.loads(log.with_suffix('.log.command.json').read_text())==c
assert str(detail_path.parent)+' PASS' in log.read_text()
assert d['status']=='PASS' and d['suite']=='portable' and d['completed_phases']==p['suites'] and d['python']==c['argv'][0]
assert d['manifest']['manifest_sha256']==p['package_manifest_sha256'] and d['manifest']['members']==6936
assert d['tools_unchanged'] is True and d['tool_binary_sha256_before']==d['tool_binary_sha256_after'] and len(d['tool_binary_sha256_before'])==12
assert all(extracted in Path(v).resolve().parents for v in d['local_module_origins'].values())
phases={q['phase']:q for q in d['phase_results']};assert set(phases)=={'smoke','numeric','cpu-small'}
smoke=phases['smoke']['runs'];assert len(smoke)==2 and {q['config']['READ_LATENCY'] for q in smoke}=={1,2}
for q in smoke:assert q['status']=='PASS' and q['outputs']==160 and sha(extracted/q['manifest'])==q['sha256']
assert phases['numeric']['gate']=={'status':'PASS','unit_vectors':2170,'public_core_cases':52,'all_shifts':48}
assert phases['cpu-small']['gate']['status']=='PASS' and phases['cpu-small']['gate']['tasks']==2 and phases['cpu-small']['gate']['outputs']==96
phase_bound=[]
for name in ('numeric','cpu-small'):
 q=phases[name];e=extracted/q['evidence'];cmd=q['command'];ll=extracted/cmd['log']
 assert sha(e)==q['evidence_sha256'] and cmd['exit_code']==0 and cmd['pid']>0 and sha(ll)==cmd['log_sha256'] and json.loads(ll.with_suffix('.log.command.json').read_text())==cmd
 phase_bound.append({'phase':name,'evidence':ident(str(e.relative_to(ROOT))),'gate':q['gate'],'actual_child_pid':cmd['pid'],'exit_code':cmd['exit_code']})
closeout=ROOT/'scripts/revd_offline_closeout.py';closeout_sha=sha(closeout)
assert closeout_sha=='5bcc5f1f163e9542616af247911181f8065e43fd06ed6f8f96c5f3fc7461ea65'
text=closeout.read_text();assert 'require(now < soft_finish,' in text and text.count('soft_finish')>=5
budget=get('work/revd_offline_20261017/budget.json');soft=datetime.fromisoformat(budget['soft_finish_utc'].replace('Z','+00:00'))
before_soft=datetime.now(timezone.utc)<soft
assert not before_soft,'this late review must not be backdated as before soft deadline'
ver=get('work/revd_offline_20261017/review_verification_round2.json');assert ver['status']=='RECOMMEND_LOCAL_ACCEPTANCE_WITH_LIMITS' and ver['D3_review_passed']
assert sha(ROOT/'scripts/revd_offline_gate.py')==ver['current_final_gate_sha256']
pack=get('deliverables/kwt_revd_v2_candidate_20261017/SUMMARY.json')
assert pack['formal_score'] is None and pack['official_contest_acceptance'] is False
for key in ('verification_review','W1_review','W2_review','W2_soc_review'):
 item=pack['evidence'][key];assert sha(ROOT/item['path'])==item['sha256'],'frozen prior review changed: '+key
r={'schema_version':1,'review_round':'final_actual_artifact','status':'RECOMMEND_LOCAL_PACKAGE_ACCEPTANCE_WITH_LIMITS','created_utc':utc(),'reviewer':'independent non-author submission_inventory','pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'review_scope_passed':True,'actual_final_artifact_review_complete':True,'actual_final_zip_proof':ident(proof_path),'native_materialization':ident(material_path),'outer_timeout_control_handoff':ident(handoff_path),'outer_timeout_control_detail':{'checker_pid':420,'actual_checker_exit_code':0,'portable_pid':467,'outer_timeout_pid':initial_handoff['stopped_timeout_pid'],'outer_exit_code':1,'simulation_timeouts_unchanged':True,'source_unchanged':True,'control_finish_deadline':initial_handoff['control_finish_deadline'],'note':'Only outer filesystem supervisor was stopped and terminated. Actual Windows wsl.exe client exit1 is recorded; Linux SIGKILL would conventionally imply137 but no Linux shell137 was observed. Actual checker/portable0 and original inner880s functional timeouts remain authoritative; original outer envelope is not claimed as PASS.'},'closeout_source':ident('scripts/revd_offline_closeout.py'),'zip_sha256':p['archive_sha256'],'manifest_sha256':p['package_manifest_sha256'],'package_folder':'deliverables/kwt_revd_v2_candidate_20261017','package_zip':p['archive'],'zip_bytes':zr['archive_bytes'],'manifest_members':6936,'zip_entries':6937,'selected_profile':pack['selected_profile'],'source_sha256':rb['source_sha256'],'D3_gate_sha256':sha(ROOT/'scripts/revd_offline_gate.py'),'source_logic_negative_review':ident(negative_path),'final_stage_positive_review':ident(rebind_path),'actual_payload_review':ident(zip_review_path),'materializer_source_receipt_review':ident('reports/revd_offline/package_review/package-final-rebind-20261017T084744Z/materializer_source_receipt_review.json'),'CPU_dependency_closure_review':ident('work/revd_offline_20261017/review_package_cpu_closure.json'),'verification_round2':ident('work/revd_offline_20261017/review_verification_round2.json'),'actual_final_portable':{'pid':c['pid'],'exit_code':c['exit_code'],'detail':ident(str(detail_path.relative_to(ROOT))),'completed_phases':d['completed_phases'],'smoke_L1_L2_outputs_each':160,'numeric_unit_vectors':2170,'numeric_public_cases':52,'shifts':48,'real_E203_C_tasks':2,'real_shared_memory_outputs_and_flags':96,'phase_receipt_binding':phase_bound,'before_after_tool_count':12,'tools_unchanged':True,'local_module_origins':d['local_module_origins']},'fixed_packaging_findings':['Preserved superseded stage missing CPU comparison counterpart/D2 alias and W2-named simulator binaries; v3 plan adds existing byte-identical dependencies, independently closure-reviewed and actual ZIP SHA-checked.','Slow WSL publication stopped and partial tree preserved. Native control helper copies full validated directory and exact tested ZIP bytes; actual final ZIP separately extracted and executed.','Closeout now guards09:35 soft_finish both before checks and immediately before SUMMARY writes, in addition to hardstop and architecture freeze.'],'test_accounting':{'fixed_source_proof_software_negatives':26,'final_archive_payload_positive_checks':20,'final_stage_real_positive':True,'actual_final_zip_new_extraction_and_fresh_suites':True,'additional_EDA_launched_by_this_reviewer':False,'materializer_synthetic_negative_campaign':False},'limitations':pack['formal_gaps']+['Default CPU covers12 frozen layers for one engineering input across six boots; not all36 CPU cases or official selected12. W2 CPU scope is2full tasks plus directed flags; W1 CPU NOT_RUN.','Alternative repeated protocol histories are summarized rather than all raw histories archived; fresh package-relative source entrypoints remain available. Historical absolute command paths are provenance only.','Old tool evidence has explicit post-run attestation limits; fresh final core/package wrappers bind actual before/after tools.','Final archive filesystem supervisor was intentionally stopped and killed. Observed Windows wsl.exe client exit1 is recorded; no shell137 was observed. Actual checker420 and portable467 exited0; the outer wrapper is not a PASS.','Control materializer source/actual receipt and closeout source were reviewed; fixed26 software negatives exercise unchanged publisher/proof validation and are not claimed as new materializer negative tests.'],'deadline_reviewed_before_soft_finish':False,'deadline_respected':False,'ready_for_review_eligible':False,'overall_run_status_required':'TIMEBOX_ENDED_PARTIAL','timing_limitation':'Actual final archive proof/checker completed09:34:28 before soft_finish, but this independent final receipt review and root closure completed after09:35. Do not backdate or grant READY; artifact-local acceptance does not satisfy the overall timebox.','frozen_prior_reviews_unchanged':True,'parent_accepted':False,'official_contest_acceptance':False,'formal_score':None,'unresolved_confirmed_local_blockers':[],'overall_run_blockers':['Final independent review/closure missed09:35 soft deadline.'],'generator_source_sha256':sha(Path(__file__))}
put(target,r);put(out/'summary.json',{'status':'PASS','created_utc':utc(),'review':ident(str(target.relative_to(ROOT))),'actual_final_zip_proof':r['actual_final_zip_proof'],'native_materialization':r['native_materialization'],'closeout_source':r['closeout_source'],'generator_source_sha256':sha(Path(__file__))});print(json.dumps({'status':r['status'],'review':str(target.relative_to(ROOT)),'sha256':sha(target),'proof_sha256':r['actual_final_zip_proof']['sha256'],'zip_sha256':r['zip_sha256']}),flush=True)
