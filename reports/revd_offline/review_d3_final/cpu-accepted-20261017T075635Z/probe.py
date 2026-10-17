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

# Firmware equality probes preserve old artifacts; only semantic read views change.
checks.run('CPU_loaded_hex_differs_from_compiled_binary',lambda:gate.check_cpu(path),reject=True,fragments=('CPU firmware bytes do not match compiled binary',),text_overrides={path.parent/'cpu/revd-driver.hex':lambda text:('00' if text[:2]!='00' else '01')+text[2:]})
from unittest.mock import patch
original_bytes=Path.read_bytes
def bytes_probe(target,marker):
 def replacement(p,*args,**kwargs):
  value=original_bytes(p,*args,**kwargs)
  return value+marker if p==target else value
 with patch.object(Path,'read_bytes',replacement):return gate.check_cpu(path)
checks.run('CPU_bin_bytes_changed',lambda:bytes_probe(path.parent/'revd-driver.bin',b'\x00'),reject=True,fragments=('CPU firmware bytes do not match compiled binary',))
checks.run('CPU_top_hex_bytes_differ_from_loaded_hex',lambda:bytes_probe(path.parent/'revd-driver.hex',b'\n'),reject=True,fragments=('CPU firmware bytes do not match compiled binary',))
is_copy=lambda c:c['argv'][0]=='riscv64-unknown-elf-objcopy' and c['argv'][-1].endswith('/revd-driver.bin')
cmd_negative('CPU_objcopy_shadow_ELF_input',is_copy,lambda argv:argv.__setitem__(-2,'/tmp/independent_shadow/revd-driver.elf'))
cmd_negative('CPU_objcopy_shadow_binary_output',is_copy,lambda argv:argv.__setitem__(-1,'/tmp/independent_shadow/revd-driver.bin'))
a=copy.deepcopy(r);first=next(iter(a['tool_sha256']));value=a['tool_sha256'].pop(first);a['tool_sha256'][str(Path(first).parent/'..'/Path(first).parent.name/Path(first).name)]=value
checks.run('tool_SHA_semantic_path_alias',lambda:gate.check_cpu(path),reject=True,fragments=('CPU exact tool binary inventory',),json_overrides={path:a})
result={'status':'PASS' if all(t['passed'] for t in checks.results) and p.read_bytes()==b else 'FAIL','created_utc':utc(),'pid':os.getpid(),'source_sha256':sha(p),'source_unchanged':p.read_bytes()==b,'actual_original_tool_count':len(r['tool_sha256']),'tests':checks.results,'test_count':len(checks.results),'Icarus_parameter_branch':'STATIC_FIXED_matches_real_split_-P_contract; dynamic_NOT_RUN_no_existing_Icarus_CPU_result','parent_accepted':False,'official_contest_acceptance':False}
put(out/'summary.json',result);print(json.dumps({'status':result['status'],'count':result['test_count'],'failed':[t['name'] for t in checks.results if not t['passed']],'source_unchanged':result['source_unchanged']}),flush=True);raise SystemExit(0 if result['status']=='PASS' else 1)
