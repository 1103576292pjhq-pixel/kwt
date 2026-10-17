from pathlib import Path
import os,sys,types,copy,json
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
from dv.revd_opt.gate_negatives import Checks
out=Path(__file__).resolve().parent;p=ROOT/'scripts/revd_offline_gate.py';b=p.read_bytes();(out/'gate_snapshot.txt').write_bytes(b);gate=types.ModuleType('gate_snapshot');gate.__file__=str(p);exec(compile(b,str(p),'exec'),gate.__dict__)
path=ROOT/'reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json';r=gate.read_json(path);checks=Checks(gate);checks.run('positive_current_real_CPU',lambda:gate.check_cpu(path))
def cmd_negative(name,predicate,mutate):
 a=copy.deepcopy(r);matches=[c for c in a['commands'] if predicate(c)];assert len(matches)==1,(name,len(matches));cmd=matches[0];mutate(cmd['argv']);sidecar=(ROOT/cmd['log']).with_suffix('.log.command.json')
 checks.run(name,lambda:gate.check_cpu(path),reject=True,json_overrides={path:a,sidecar:cmd})
is_compile=lambda c:c['argv'][0]=='verilator' and any(x.endswith('/soc_cpu_tb.sv') for x in c['argv'])
def shadow_suffix(argv,suffix):
 index=next(i for i,x in enumerate(argv) if x.endswith(suffix));argv[index]='/tmp/independent_shadow/'+Path(argv[index]).name
for name,suffix in [('shadow_compiled_accelerator','/core_stream_frontend_opt.sv'),('shadow_compiled_adapter','/revd_opt_icb.sv'),('shadow_compiled_vendor_CPU','/e203_cpu.v')]:cmd_negative(name,is_compile,lambda argv,suffix=suffix:shadow_suffix(argv,suffix))
cmd_negative('missing_compiled_banked_SP_RAM',is_compile,lambda argv:argv.remove(str(ROOT/'rtl/revd/banked_sp16.sv')))
cmd_negative('shadow_compiler_output_Mdir',is_compile,lambda argv:argv.__setitem__(argv.index('--Mdir')+1,'/tmp/independent_shadow/obj'))
is_gcc=lambda c:c['argv'][0]=='riscv64-unknown-elf-gcc' and any(x.endswith('/revd_opt_driver.c') for x in c['argv'])
cmd_negative('shadow_GCC_production_driver',is_gcc,lambda argv:shadow_suffix(argv,'/revd_opt_driver.c'))
cmd_negative('shadow_GCC_main',is_gcc,lambda argv:shadow_suffix(argv,'/revd_opt/main.c'))
cmd_negative('missing_GCC_startup',is_gcc,lambda argv:argv.remove(str(ROOT/'sw/e203/start.S')))
cmd_negative('shadow_GCC_output_ELF',is_gcc,lambda argv:argv.__setitem__(argv.index('-o')+1,'/tmp/independent_shadow/driver.elf'))
a=copy.deepcopy(r);first=next(iter(a['tool_sha256']));a['tool_sha256']={first:a['tool_sha256'][first]}
checks.run('tool_SHA_inventory_reduced_to_one',lambda:gate.check_cpu(path),reject=True,json_overrides={path:a})
result={'status':'PASS' if all(t['passed'] for t in checks.results) and p.read_bytes()==b else 'FAIL','created_utc':utc(),'pid':os.getpid(),'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'actual_original_tool_count':len(r['tool_sha256']),'tests':checks.results,'test_count':len(checks.results),'source_scope':'Real current CPU result and cloned command plus corresponding .command.json JSON views only; no underlying artifact changed.','Icarus_parameter_branch':{'dynamic_test':'NOT_RUN_no_existing_Icarus_CPU_result_observed','static_runner':'runner generates ["-P","soc_cpu_tb.PM=..."] split tokens','static_gate':'gate requires one token -Psoc_cpu_tb.PM=...; valid Icarus run would be rejected','runner_sha256':sha(ROOT/'scripts/revd_offline_soc_run.py')},'parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result);print(json.dumps({'status':result['status'],'false_accepts':[t['name'] for t in checks.results if t['actual']=='ACCEPT' and t['expected']=='REJECT'],'source_unchanged':result['source_unchanged']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
