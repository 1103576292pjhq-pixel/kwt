from pathlib import Path
import copy,json,sys,types,os,time,hashlib
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks,protocol_negatives,frozen_negatives,numeric_negatives,cpu_negatives
out=Path(__file__).resolve().parent
sources=['scripts/revd_offline_gate.py','scripts/revd_offline_soc_layers.py','dv/revd_opt/gate_negatives.py']
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
checks.run('positive_fresh_numeric53',lambda:gate.check_numeric(numeric))
nj=gate.read_json(numeric)
for name,mutate in [('missing_numeric_shift47',lambda a:a.update(tests=[t for t in a['tests'] if t['name']!='shift47'])),('alias_numeric_shift_name',lambda a:next(t for t in a['tests'] if t['name']=='shift47').update(name='shift46')),('alias_numeric_shift47_manifest',lambda a:next(t for t in a['tests'] if t['name']=='shift47').update(manifest=next(t['manifest'] for t in a['tests'] if t['name']=='shift46'))),('missing_numeric_unit_source',lambda a:a['unit_source_sha256'].pop('dv/revd_opt/numeric_checks.py'))]:
 a=copy.deepcopy(nj);mutate(a);checks.run(name,lambda:gate.check_numeric(numeric),reject=True,json_overrides={numeric:a})
checks.run('missing_quant_terminal_output',lambda:gate.check_numeric(numeric),reject=True,fragments=('quant missing/aliased boundary vectors',),text_overrides={numeric.parent/'quant_output.txt':lambda text:'\n'.join(text.splitlines()[:-1])+'\n'})
a=copy.deepcopy(nj);a['commands'][0]['argv']=['/usr/bin/true'];sidecar=(ROOT/a['commands'][0]['log']).with_suffix('.log.command.json')
checks.run('fake_quant_compile_argv_coherent_receipt',lambda:gate.check_numeric(numeric),reject=True,fragments=('quant compile source/output binding',),json_overrides={numeric:a,sidecar:a['commands'][0]})
checks.run('changed_quant_boundary_vector',lambda:gate.check_numeric(numeric),reject=True,fragments=('quant boundary/tie vector identity',),text_overrides={numeric.parent/'quant_vectors.hex':lambda text:'1'+text[1:]})
cpu_negatives(checks,cpu0)
checks.run('positive_real_CPU_offset2_layers03_04',lambda:gate.check_cpu(cpu2))
checks.run('positive_real_CPU_offset4_layers05_06',lambda:gate.check_cpu(cpu4))
def negative(name,mutate,fragments=(),path=cpu2):
 a=copy.deepcopy(gate.read_json(path));mutate(a)
 checks.run(name,lambda:gate.check_cpu(path),reject=True,fragments=(),json_overrides={path:a})
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

# Coherent pair metadata changes bypass only JSON read, preserving original disks;
# individual semantic bindings must reject even when the embedded and file view agree.
for name,key,value in [('case_ids','case_ids',['forged/layer_03','forged/layer_04']),('executable_path','actual_simulator_executable','/usr/bin/true'),('firmware_SHA','firmware_binary_sha256','0'*64),('normal_runner_SHA','normal_soc_runner_sha256','0'*64),('wrapper_SHA','wrapper_sha256','0'*64),('case_indices','case_indices',[4,5])]:
 a=copy.deepcopy(gate.read_json(cpu2));a['pair_binding'][key]=value
 checks.run('CPU_coherent_pair_forgery_'+name,lambda:gate.check_cpu(cpu2),reject=True,fragments=('CPU pair',),json_overrides={cpu2:a,cpu2.parent/'pair-binding.json':a['pair_binding']})
cpu6=ROOT/'reports/revd_offline/soc/soc-layers07-08-20261017T071130Z/result.json'
if cpu6.is_file() and gate.read_json(cpu6)['status']=='PASS':checks.run('positive_real_CPU_offset6_layers07_08',lambda:gate.check_cpu(cpu6))
for offset,folder in [(8,'soc-layers09-10-20261017T071950Z'),(10,'soc-layers11-12-20261017T073140Z')]:
 path=ROOT/'reports/revd_offline/soc'/folder/'result.json';checks.run('positive_real_CPU_offset'+str(offset),lambda path=path:gate.check_cpu(path))
fresh=ROOT/'reports/revd_offline/final_regression/20261017T073654Z_195af115/result.json';fresh_report=gate.read_json(fresh)
assert fresh_report['status']=='PASS' and fresh_report['source_unchanged'] and fresh_report['tools_unchanged']
checks.run('positive_fresh_tool_bound_selected_full36',lambda:gate.check_suite(ROOT/fresh_report['full36'],36,4))
changed=[p for p,d in before.items() if sha(ROOT/p)!=d]
evidence_paths=[protocol,pm4,pm2,numeric,cpu0,cpu2,cpu4,fresh,ROOT/'reports/revd_offline/soc/soc-layers09-10-20261017T071950Z/result.json',ROOT/'reports/revd_offline/soc/soc-layers11-12-20261017T073140Z/result.json']
result={'schema_version':1,'status':'PASS' if all(t['passed'] for t in checks.results) and not changed else 'FAIL','scope':'Independent D3 final current-source gate positives and software negative probes; no heavy RTL run or actual publication.','pid':os.getpid(),'finished_utc':utc(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'source_sha256':before,'changed_sources':changed,'evidence_sha256':{str(p.relative_to(ROOT)):sha(p) for p in evidence_paths},'tests':checks.results,'test_count':len(checks.results),'positive_count':sum(t['expected']=='ACCEPT' for t in checks.results),'negative_count':sum(t['expected']=='REJECT' for t in checks.results),'parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result)
print(json.dumps({'status':result['status'],'test_count':result['test_count'],'failed':[t['name'] for t in checks.results if not t['passed']],'changed_sources':changed}),flush=True)
raise SystemExit(0 if result['status']=='PASS' else 1)
