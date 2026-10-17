from pathlib import Path
import sys,os,json,shutil,hashlib
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
out=Path(__file__).resolve().parent;started=utc()
def read(p):return json.loads(Path(p).read_text(encoding='utf-8-sig'))
def ident(p):return {'path':str(p.relative_to(ROOT)),'sha256':sha(p),'bytes':p.stat().st_size}
inv_path=ROOT/'work/revd_offline_20261017/technology_inventory.json';inv=read(inv_path)
early_path=ROOT/inv['tool_hash_retry']['path'];early=read(early_path)
cpu_path=ROOT/'reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json';cpu=read(cpu_path)
first_compile=min(c['started_utc'] for c in cpu['commands'] if c['argv'][0] in ('iverilog','verilator'))
captures=[{'name':'stage_A_inventory_actual_sha256sum','receipt':ident(early_path),'capture_started_utc':early['start_utc'],'capture_finished_utc':early['end_utc'],'real_pid':early['pid'],'real_exit_code':early['exit_code'],'tool_sha256':{r['path']:r['sha256'] for r in inv['tool_binary_sha256']}}, {'name':'earliest_accepted_real_CPU_run_tool_inventory','receipt':ident(cpu_path),'capture_started_utc_lower_bound':cpu['started_utc'],'capture_finished_utc_upper_bound':first_compile,'exact_per_tool_capture_time':'NOT_RECORDED; interval bounds from bound runner/commands only','tool_sha256':cpu['tool_sha256']}]
paths=set().union(*(c['tool_sha256'] for c in captures))
for name in ('iverilog','vvp','verilator','verilator_bin','yosys','riscv64-unknown-elf-gcc','riscv64-unknown-elf-objcopy','riscv64-unknown-elf-objdump','riscv64-unknown-elf-readelf','g++','make'):
 p=shutil.which(name)
 if p:paths.add(p)
paths.add(sys.executable)
import numpy as np
paths.add(np._core._multiarray_umath.__file__)
for p in ('/usr/lib/x86_64-linux-gnu/ivl/ivl','/usr/lib/x86_64-linux-gnu/ivl/ivlpp'):
 if Path(p).is_file():paths.add(p)
current=[]
for p in sorted(paths):
 path=Path(p);r={'path':p,'exists':path.is_file(),'captured_started_utc':utc()}
 if path.is_file():r.update(resolved_path=str(path.resolve()),sha256=sha(path),bytes=path.stat().st_size)
 r['captured_finished_utc']=utc();r['early_comparisons']=[{'capture':c['name'],'sha256':c['tool_sha256'][p],'matches':r.get('sha256')==c['tool_sha256'][p]} for c in captures if p in c['tool_sha256']];current.append(r)
groups={'PM4_full36':ROOT/'reports/revd_offline/core/ctx4-full36-l1-final-001/summary.json','PM2_full36':ROOT/'reports/revd_offline/core/ctx4-full36-pm2-l1-001/summary.json','protocol':ROOT/'reports/revd_offline/protocol/20261017T062232Z_d44560d2/summary.json','numeric':ROOT/'reports/revd_offline/numeric/20261017T063223Z_43019020/summary.json','comparison':ROOT/'reports/revd_offline/comparison/20261017T064410Z_e3c17acd/summary.json','cross_simulator_independent':ROOT/'reports/revd_offline/crosscheck/20261017T070407Z_11b4dece/summary.json'}
bound=[];seen={};checks=[]
for group,p in groups.items():
 j=read(p);group_record={'group':group,'summary':ident(p),'status_reported':j['status'],'runs':[],'tool_binary_SHA_was_not_captured_in_each_old_run':True}
 entries=j.get('cases',j.get('tests',j.get('runs',[])))
 for t in entries:
  if 'manifest' not in t:continue
  m=ROOT/t['manifest'];r=read(m)
  run={**ident(m),'started_utc':r.get('started_utc'),'finished_utc':r.get('finished_utc'),'status_reported':r['status'],'mutation':r.get('config',{}).get('mutation'),'simulator':r.get('config',{}).get('simulator'),'archival_tools_versions':r.get('tools',{}),'current_tool_capture_references':sorted(paths),'in_run_tool_binary_SHA_available':bool(r.get('tool_sha256')),'commands':[]}
  for c in r.get('commands',[]):
   cp=(ROOT/c['log']).with_suffix('.log.command.json');same=read(cp)==c
   run['commands'].append({'receipt':ident(cp),'matches_manifest':same,'real_pid':c['pid'],'exit_code':c['exit_code'],'argv0':c['argv'][0],'started_utc':c['started_utc'],'finished_utc':c['finished_utc']});checks.append(same)
  # Bind compact version inventory SHA, avoiding pretending text hashes are binary hashes.
  run['archival_tools_versions_sha256']=hashlib.sha256(json.dumps(run.pop('archival_tools_versions'),sort_keys=True).encode()).hexdigest()
  group_record['runs'].append(run);seen[str(m)]=ident(m)
 if group=='numeric':
  group_record['unit_commands']=[{'receipt':ident((ROOT/c['log']).with_suffix('.log.command.json')),'matches_summary':read((ROOT/c['log']).with_suffix('.log.command.json'))==c,'real_pid':c['pid'],'exit_code':c['exit_code']} for c in j['commands']]
  checks.extend(c['matches_summary'] for c in group_record['unit_commands'])
 bound.append(group_record)
all_matches=all(e['matches'] for r in current for e in r['early_comparisons'])
result={'schema_version':1,'status':'POST_RUN_CAPTURE_MATCHES_AVAILABLE_EARLY_CAPTURES' if all_matches and all(checks) else 'MISMATCH_REVIEW_REQUIRED','created_utc':utc(),'capture_started_utc':started,'real_pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'scope':'Honest post-run tool-binary attestation for already-created D3 engineering evidence; this is not retroactive per-run capture.','limitation':'Equal binary SHA at early and current observations cannot prove that every tool/plugin/shared library stayed identical throughout every old run. Exact per-run before/after binary capture is unavailable for these old core/protocol/numeric/comparison/cross runs. No old receipt/source/report was modified.','proves_each_old_run_tools_at_execution':False,'available_early_captures':captures,'current_tool_binaries':current,'all_available_early_SHA_equal_current':all_matches,'old_run_command_receipts_equal_manifests':all(checks),'bound_groups':bound,'unique_bound_run_manifests':len(seen),'unit_and_run_command_receipt_count':len(checks),'parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result);put(ROOT/'work/revd_offline_20261017/tool_attestation_postrun.json',{'status':result['status'],'created_utc':utc(),'evidence':ident(out/'summary.json'),'unique_bound_run_manifests':len(seen),'all_available_early_SHA_equal_current':all_matches,'old_run_command_receipts_equal_manifests':all(checks),'proves_each_old_run_tools_at_execution':False,'scope':result['scope'],'limitation':result['limitation']})
print(json.dumps({'status':result['status'],'tools':len(current),'runs':len(seen),'command_receipts':len(checks)}),flush=True)
raise SystemExit(0 if all_matches and all(checks) else 1)
