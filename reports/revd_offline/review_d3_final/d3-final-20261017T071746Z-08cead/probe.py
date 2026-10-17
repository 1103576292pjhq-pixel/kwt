from pathlib import Path
import copy,json,sys,types,os,time,hashlib
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks,protocol_negatives,frozen_negatives,numeric_negatives,cpu_negatives
out=Path(__file__).resolve().parent
sources=['scripts/revd_offline_gate.py','scripts/package_revd_candidate.py','scripts/revd_offline_reproduce.py','scripts/revd_offline_package_check.py','scripts/revd_offline_soc_layers.py','dv/revd_opt/gate_negatives.py']
before={p:sha(ROOT/p) for p in sources}
def module_snapshot(relative,name):
 p=ROOT/relative;b=p.read_bytes();m=types.ModuleType(name);m.__file__=str(p);exec(compile(b,str(p),'exec'),m.__dict__);(out/(name+'.source.txt')).write_bytes(b);return m
gate=module_snapshot(sources[0],'d3_gate_snapshot');checks=Checks(gate)
protocol=ROOT/'reports/revd_offline/protocol/20261017T062232Z_d44560d2/summary.json'
pm4=ROOT/'reports/revd_offline/core/ctx4-full36-l1-final-001/summary.json'
pm2=ROOT/'reports/revd_offline/core/ctx4-full36-pm2-l1-001/summary.json'
numeric=ROOT/'reports/revd_offline/numeric/20261017T063223Z_43019020/summary.json'
cpu0=ROOT/'reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json'
cpu2=ROOT/'reports/revd_offline/soc/soc-layers03-04-20261017T064820Z/result.json'
cpu4=ROOT/'reports/revd_offline/soc/soc-layers05-06-20261017T070120Z/result.json'
protocol_negatives(checks,protocol);frozen_negatives(checks,pm4)
checks.run('positive_PM2_complete_frozen36',lambda:gate.check_suite(pm2,36,2))
a=copy.deepcopy(gate.read_json(pm2));a['cases'][-1]['manifest']=a['cases'][0]['manifest']
checks.run('PM2_alias_frozen_manifest',lambda:gate.check_suite(pm2,36,2),reject=True,fragments=('duplicate case manifests',),json_overrides={pm2:a})
checks.run('PM2_mixed_into_PM4_comparison',lambda:gate.check_suite(pm2,36,4),reject=True,fragments=('mixed profile PM',))
numeric_negatives(checks,numeric);cpu_negatives(checks,cpu0)
checks.run('positive_real_CPU_offset2_layers03_04',lambda:gate.check_cpu(cpu2))
checks.run('positive_real_CPU_offset4_layers05_06',lambda:gate.check_cpu(cpu4))
def negative(name,mutate,fragments=(),path=cpu2):
 a=copy.deepcopy(gate.read_json(path));mutate(a)
 checks.run(name,lambda:gate.check_cpu(path),reject=True,fragments=fragments,json_overrides={path:a})
negative('CPU_invalid_odd_layer_offset',lambda a:a['profile'].update(case_offset=1),('CPU case selection offset',))
negative('CPU_pair_missing_binding',lambda a:a.pop('pair_binding'),('CPU pair selection binding',))
negative('CPU_pair_wrong_indices',lambda a:a['pair_binding'].update(case_indices=[0,1]),('CPU pair selection binding',))
negative('CPU_pair_aliased_indices',lambda a:a['pair_binding'].update(case_indices=[2,2]),('CPU pair selection binding',))
negative('CPU_pair_forged_manifest_SHA',lambda a:a['pair_binding'].update(original_manifest_sha256='0'*64),('CPU pair selection binding',))
negative('CPU_pair_forged_wrapper_SHA',lambda a:a['pair_binding'].update(wrapper_sha256='0'*64),('CPU pair wrapper source',))
negative('CPU_pair_forged_executable_SHA',lambda a:a['pair_binding'].update(actual_simulator_executable_sha256='0'*64),('CPU pair binary binding',))
negative('CPU_pair_false_case_ids',lambda a:a['pair_binding'].update(case_ids=['forged/layer_03','forged/layer_04']))
negative('CPU_pair_fake_executable_path',lambda a:a['pair_binding'].update(actual_simulator_executable='/usr/bin/true'))
negative('CPU_pair_fake_firmware_SHA',lambda a:a['pair_binding'].update(firmware_binary_sha256='0'*64))
negative('CPU_pair_fake_normal_runner_SHA',lambda a:a['pair_binding'].update(normal_soc_runner_sha256='0'*64))
negative('CPU_pair_omitted_wrapper_source',lambda a:a['source_sha256'].pop('scripts/revd_offline_soc_layers.py'))
negative('CPU_mixed_PM_profile_vs_actual_compile',lambda a:a['profile'].update(pm=2))
negative('CPU_mixed_latency_vs_actual_compile',lambda a:a['profile'].update(latency=2))
negative('CPU_pair_offset_removed',lambda a:a['profile'].pop('case_offset'),('CPU frozen case/layer identity',))
negative('CPU_pair_mixed_layer_offset',lambda a:(a['profile'].update(case_offset=4),a['pair_binding'].update(case_indices=[4,5])),('CPU frozen case/layer identity',))
frozen=gate.read_json(ROOT/'reports/prototype/vectors/manifest.json')
def fake_pair(a):
 a['profile']['case_offset']=4;a['pair_binding']['case_indices']=[4,5]
 for c,fc in zip(a['cases'],frozen['cases'][4:6]):c.update(case_id=fc['case_id'],layer=fc['layer'],shift=fc['config']['output_shift'])
negative('CPU_fake_pair_labels_with_old_actual_outputs',fake_pair,('CPU shared-SRAM value/flag mismatch',))
# Isolated publication probes write only inside this new review directory. They
# exercise the real publish function, never the actual deliverables target.
pkg=module_snapshot('scripts/package_revd_candidate.py','package_snapshot');package_checks=[]
for scenario,extra in [('empty_command_proof',False),('unmanifested_code_after_proof',True)]:
 root=out/'publication_probe'/scenario;stage=root/'stage';stage.mkdir(parents=True);(stage/'valid.txt').write_text('known bytes\n')
 put(stage/'MANIFEST.json',{'schema_version':1,'files':{'valid.txt':sha(stage/'valid.txt')},'file_count':1})
 if extra:(stage/'scripts').mkdir();(stage/'scripts/unlisted.py').write_text('print("unmanifested")\n')
 proof={'status':'PASS','package_manifest_sha256':sha(stage/'MANIFEST.json'),'suites':['manifest','smoke','numeric'],'commands':[]}
 put(root/'proof.json',proof);pkg.ROOT=root
 try:target,archive=pkg.publish(stage,root/'proof.json')
 except ValueError as e:record={'name':scenario,'expected':'REJECT','actual':'REJECT','passed':True,'error':str(e)}
 except Exception as e:record={'name':scenario,'expected':'REJECT','actual':'UNEXPECTED_EXCEPTION','passed':False,'error':repr(e)}
 else:record={'name':scenario,'expected':'REJECT','actual':'ACCEPT','passed':False,'archive_sha256':sha(archive),'unmanifested_published':(target/'scripts/unlisted.py').is_file()}
 package_checks.append(record);print(json.dumps(record),flush=True)
changed=[p for p,d in before.items() if sha(ROOT/p)!=d]
evidence_paths=[protocol,pm4,pm2,numeric,cpu0,cpu2,cpu4]
result={'schema_version':1,'status':'PASS' if all(t['passed'] for t in checks.results+package_checks) and not changed else 'FAIL','scope':'Independent software gates and isolated package publish validation; no RTL mutation or actual publication.','started_process_pid':os.getpid(),'finished_utc':utc(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'source_sha256':before,'changed_sources':changed,'evidence_sha256':{str(p.relative_to(ROOT)):sha(p) for p in evidence_paths},'tests':checks.results,'package_probes':package_checks,'test_count':len(checks.results)+len(package_checks),'parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result)
print(json.dumps({'status':result['status'],'test_count':result['test_count'],'false_accepts':[t['name'] for t in checks.results+package_checks if t['actual']=='ACCEPT' and t['expected']=='REJECT'],'changed_sources':changed}),flush=True)
raise SystemExit(0 if result['status']=='PASS' else 1)
