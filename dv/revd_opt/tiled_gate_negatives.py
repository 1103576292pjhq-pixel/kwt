"""Software checker negatives only; these are not additional RTL mutants.

Clones of real receipts are rebased into labeled checker fixtures. A positive
clone must pass before each corruption, proving rejection reaches its intended
check rather than failing merely because the fixture moved.
"""
import argparse
import copy
from pathlib import Path
import shutil
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import read_json,put,sha,run_id
from scripts.revd_offline_tiled_gate import check_case,check_protocol,check_suite

def rewrite(folder,r):
    for c in r['commands']:
        log=ROOT/c['log'];put(log.with_suffix('.log.command.json'),c)
    r['output_sha256']={p.name:sha(p) for p in folder.iterdir() if p.is_file() and p.name!='run_manifest.json'}
    put(folder/'run_manifest.json',r)

def clone(source,dest):
    shutil.copytree(source,dest);r=read_json(dest/'run_manifest.json')
    old=str(source);new=str(dest);old_rel=str(source.relative_to(ROOT));new_rel=str(dest.relative_to(ROOT))
    for c in r['commands']:
        c['argv']=[a.replace(old,new) for a in c['argv']]
        c['log']=c['log'].replace(old_rel,new_rel)
    r['checker_fixture_only']=True;r['actual_run_origin']=str(source/'run_manifest.json')
    rewrite(dest,r);return r

def main():
    p=argparse.ArgumentParser();p.add_argument('--run-id');a=p.parse_args()
    out=ROOT/'reports/revd_offline/tiled'/(a.run_id or run_id());out.mkdir(parents=True,exist_ok=False);tests=[]
    source=ROOT/'reports/revd_offline/tiled/w1-production-pm4-l1-001/synthetic99'
    def mutate(name,fn):
        dest=out/name;r=clone(source,dest);check_case(dest/'run_manifest.json')
        fn(dest,r);rewrite(dest,r)
        try:check_case(dest/'run_manifest.json');tests.append({'name':name,'rejected':False})
        except (ValueError,KeyError,IndexError,OSError) as exc:tests.append({'name':name,'rejected':True,'reason':str(exc)})
    def edit_output(dest,r,change):
        lines=(dest/'output.hex').read_text().splitlines();change(lines);(dest/'output.hex').write_text('\n'.join(lines)+'\n')
    mutate('wrong_flag',lambda d,r:edit_output(d,r,lambda lines:lines.__setitem__(0,lines[0][:-5]+'1'+lines[0][-4:])))
    mutate('delete_last_output',lambda d,r:edit_output(d,r,lambda lines:lines.pop()))
    mutate('duplicate_index',lambda d,r:edit_output(d,r,lambda lines:lines.__setitem__(-1,lines[0])))
    mutate('unknown_output',lambda d,r:edit_output(d,r,lambda lines:lines.__setitem__(0,'x'+lines[0][1:])))
    mutate('missing_output_file',lambda d,r:(d/'output.hex').unlink())
    mutate('nonzero_sim_exit',lambda d,r:r['commands'][1].__setitem__('exit_code',1))
    mutate('timeout_is_not_pass',lambda d,r:r['commands'][1].__setitem__('exit_code',124))
    mutate('unfinished_subprocess',lambda d,r:r['commands'][1].pop('finished_utc'))
    mutate('wrong_compile_PM',lambda d,r:r['commands'][0]['argv'].__setitem__(r['commands'][0]['argv'].index('-Ptiled_core_tb.PM=4'),'-Ptiled_core_tb.PM=2'))
    mutate('handfilled_cycle_counter',lambda d,r:r['task_counters'][0].__setitem__('frontend_cycles',1))
    mutate('changed_python_tool_SHA',lambda d,r:r['tools'].__setitem__('python_sha256','0'*64))
    def wrong_tool_path(d,r,name):
        executable=Path(sys.executable).resolve();r['tools'][name]['path']=str(executable);r['tools'][name]['sha256']=sha(executable)
    for name in ('iverilog','vvp'):
        mutate(name+'_wrong_executable_path',lambda d,r,tool=name:wrong_tool_path(d,r,tool))
        mutate(name+'_fictitious_version',lambda d,r,tool=name:r['tools'][tool].__setitem__('version','FICTITIOUS_TOOL_VERSION'))
    mutate('wrong_sim_binary',lambda d,r:r['commands'][1]['argv'].__setitem__(1,str(d/'other.vvp')))
    mutate('binary_changed',lambda d,r:(d/'sim.vvp').write_bytes((d/'sim.vvp').read_bytes()+b'\nchanged\n'))
    mutate('missing_source_identity',lambda d,r:r['source_sha256'].pop('numeric/fixedpoint.py'))
    def stale(d,r):
        f=d/'source_snapshot/rtl/revd_opt/core_stream_tiled_opt.sv';f.write_bytes(f.read_bytes()+b'\n// stale fixture\n');r['source_sha256']['rtl/revd_opt/core_stream_tiled_opt.sv']=sha(f)
    mutate('stale_source_even_if_snapshot_rehashed',stale)
    def config(d,r):
        r['config']['PM']=2;put(d/'config.json',r['config']);r['config_sha256']=sha(d/'config.json')
    mutate('mixed_configuration',config)
    def stream(d,r):
        f=d/'commands.hex';f.write_text(f.read_text().replace('6 1b 0 0 0 0 0\n',''));r['input_sha256']['commands.hex']=sha(f)
    mutate('missing_START_even_if_stream_rehashed',stream)
    protocol=read_json(ROOT/'reports/revd_offline/tiled/w1-protocol-pm4-final-001/summary.json')
    dest=out/'missing_last_boundary';entry=next(t for t in protocol['tests'] if t['name']=='pending_last_blocked_l1');r=clone((ROOT/entry['manifest']).parent,dest)
    entry['manifest']=str((dest/'run_manifest.json').relative_to(ROOT));put(out/'protocol-positive.json',protocol);check_protocol(out/'protocol-positive.json')
    stats=dest/'stats.txt';stats.write_text('\n'.join(s for s in stats.read_text().splitlines() if not s.startswith('BOUNDARY 2 1 '))+'\n');rewrite(dest,r)
    put(out/'protocol-missing-boundary.json',protocol)
    try:check_protocol(out/'protocol-missing-boundary.json');tests.append({'name':'missing_blocked_last_fault_boundary','rejected':False})
    except (ValueError,KeyError,IndexError,OSError) as exc:tests.append({'name':'missing_blocked_last_fault_boundary','rejected':True,'reason':str(exc)})
    protocol=read_json(ROOT/'reports/revd_offline/tiled/w1-protocol-pm4-final-001/summary.json');protocol['tests'].pop();put(out/'protocol-missing-test.json',protocol)
    try:check_protocol(out/'protocol-missing-test.json');tests.append({'name':'missing_exact_protocol_test','rejected':False})
    except (ValueError,KeyError,IndexError,OSError) as exc:tests.append({'name':'missing_exact_protocol_test','rejected':True,'reason':str(exc)})
    protocol=read_json(ROOT/'reports/revd_offline/tiled/w1-protocol-pm4-final-001/summary.json');entry=next(t for t in protocol['tests'] if t['name']=='reset_partial_W_l1');dest=out/'partial_W_alias';r=clone((ROOT/entry['manifest']).parent,dest)
    entry['manifest']=str((dest/'run_manifest.json').relative_to(ROOT));put(out/'protocol-partial-positive.json',protocol);check_protocol(out/'protocol-partial-positive.json')
    wrong=next(t for t in protocol['tests'] if t['name']=='reset_partial_X_l1');(dest/'commands.hex').write_bytes(((ROOT/wrong['manifest']).parent/'commands.hex').read_bytes());r['input_sha256']['commands.hex']=sha(dest/'commands.hex');rewrite(dest,r);put(out/'protocol-partial-W-alias.json',protocol)
    try:check_protocol(out/'protocol-partial-W-alias.json');tests.append({'name':'partial_W_aliased_to_partial_X_after_rehash','rejected':False})
    except (ValueError,KeyError,IndexError,OSError) as exc:tests.append({'name':'partial_W_aliased_to_partial_X_after_rehash','rejected':True,'reason':str(exc)})
    small=read_json(ROOT/'reports/revd_offline/tiled/w1-small-pm2-l2-001/summary.json')
    check_suite(ROOT/'reports/revd_offline/tiled/w1-small-pm2-l2-001/summary.json',2,2)
    small['profile']='production';small['cases']=small['cases'][:1];small['cases'][0]['case']='synthetic99';put(out/'small-as-production.json',small)
    try:check_suite(out/'small-as-production.json',2,2);tests.append({'name':'small_suite_aliased_to_production','rejected':False})
    except (ValueError,KeyError,IndexError,OSError) as exc:tests.append({'name':'small_suite_aliased_to_production','rejected':True,'reason':str(exc)})
    result={'status':'PASS' if len(tests)==25 and all(t['rejected'] for t in tests) else 'FAIL','tests':tests,'software_checker_negative_count':len(tests),'RTL_mutation_count':0,
            'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__),'scripts/revd_offline_tiled_gate.py':sha(ROOT/'scripts/revd_offline_tiled_gate.py')},'scope':'Synthetic corruptions of labeled real-receipt clones for checker semantics only; clones are not new compiled RTL evidence.'}
    put(out/'summary.json',result);print(out,result['status'],flush=True);return 0 if result['status']=='PASS' else 1

if __name__=='__main__':raise SystemExit(main())
