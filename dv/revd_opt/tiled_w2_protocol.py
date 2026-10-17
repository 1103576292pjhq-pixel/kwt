"""Public-stream W1 ownership, reset, completion and compiled mutant checks."""
import argparse
from pathlib import Path
import sys
import numpy as np
from tiled_w2_runner import ROOT,commands,expected_records,run_case
from scripts.revd_offline_common import put,sha,run_id

def main():
    p=argparse.ArgumentParser();p.add_argument('--run-id');p.add_argument('--pm',type=int,choices=[2,4],default=4);args=p.parse_args()
    out=ROOT/'reports/revd_offline/tiled'/(args.run_id or run_id());out.mkdir(parents=True,exist_ok=False);results=[]
    x=np.zeros((5,64),dtype=np.int16);w=np.zeros((64,32),dtype=np.int16)
    x[:,63]=[-32768,-3,1,4,32767];w[63]=np.arange(-16,16,dtype=np.int16);b=np.arange(-16,16,dtype=np.int64)
    complete=commands(x,w,b,0);full=complete.rsplit('f 0 0 0 0 0 0',1)[0]
    preload=full.split('6 1b 0 0 0 0 0',1)[0];first=preload+'6 1b 0 0 0 0 0\n'
    expected=expected_records(x,w,b,0,args.pm)
    second=commands(-x,(7-w).astype(np.int16),123-b,7,28,12)
    second_expected=expected_records(-x,(7-w).astype(np.int16),123-b,7,args.pm,28)
    def test(name,**kw):
        r=run_case(out/name,x,w,b,0,pm=args.pm,**kw)
        results.append({'name':name,'status':r['status'],'manifest':str((out/name/'run_manifest.json').relative_to(ROOT))})
        print(name,r['status'],r.get('error',''),flush=True);return r
    for latency in (1,2):
        test(f'premature_future_OPEN_l{latency}',latency=latency,stream=preload+'2 1b 1 0 0 0 0\nc 0 0 0 0 0 0\n',expected_override=[],task_count=0)
        test(f'wrong_future_tile_l{latency}',latency=latency,stream=first+'2 1b 2 0 0 0 0\nc 0 0 0 0 0 0\n',expected_override=[],task_count=0)
        lines=preload.splitlines()
        for name,prefix in (('partial_X','\n'.join(lines[:17])+'\n'),('partial_W','\n'.join(lines[:1+5*64+1+17])+'\n')):
            test(f'reset_{name}_l{latency}',latency=latency,stream=prefix+'e 0 0 0 0 0 0\n'+second,expected_override=second_expected)
        for phase in (1,2,3,4,5):
            prefix=first+('2 1b 1 0 0 0 0\n' if phase==6 else '')
            test(f'reset_l{latency}_phase{phase}',latency=latency,stream='b 0 0 0 0 0 0\n'+prefix+f'e 0 0 {phase:x} 0 0 0\n'+second,expected_override=second_expected)
        # WAIT_TILE requires all tile0 outputs to have actually drained.
        test(f'reset_wait_tile_l{latency}',latency=latency,stream=first+'e 0 0 7 0 0 0\n'+second,
             expected_override=expected[:5*16]+second_expected)
        for mode,name in ((0,'last_invalid'),(1,'pending_last_fire'),(2,'pending_last_blocked'),(3,'next_BEGIN')):
            if mode==0:stream=full+'9 1b 0 0 0 0 0\n';want=expected;count=1
            elif mode in (1,2):stream=full+f'9 1b 0 {mode:x} 0 0 0\nc 0 0 0 0 0 0\n';want=expected;count=0
            else:stream=full+'9 1c 0 3 0 7 c\n'+'\n'.join(second.splitlines()[1:])+'\n';want=expected+second_expected;count=2
            test(f'{name}_l{latency}',latency=latency,stream=stream,expected_override=want,task_count=count)
        aligned='b 0 0 0 0 0 0\n'+complete.rsplit('5 1b 1 0 0 0 0',1)[0]+'8 1b 1 0 0 0 0\nf 0 0 0 0 0 0\n'
        test(f'commit_last_Y_l{latency}',latency=latency,stream=aligned,expected_override=expected)
    test('continuous_cold_params',stream=complete+second,expected_override=expected+second_expected,task_count=2)
    # No precomputed result enters the source stream. The published final-tile
    # block is preserved even when a subsequently accepted event faults.
    count=min(args.pm,5)*16
    test('fault_preserves_tile_block',stream='b 0 0 0 0 0 0\n'+first+'d 0 0 0 0 0 0\n7 1b 0 0 0 0 0\nc 0 0 0 0 0 0\n',expected_override=expected[:count],task_count=0)
    # Hold Y while loading the other physical bank, then queue a third OPEN.
    # Reset cancels the active, ready, and deferred owners together.
    lx=np.zeros((13,64),dtype=np.int16);lx[:,63]=[32767,-32768,-3,1,4,5,-7,0,8,-9,11,-13,17]
    lw=np.zeros((64,48),dtype=np.int16);lw[63]=np.arange(-24,24,dtype=np.int16);lb=np.arange(-24,24,dtype=np.int64)
    lp=commands(lx,lw,lb,0).split('2 1b 2 0 0 0 0\n',1)[0]+'2 1b 2 0 0 0 0\n'
    ls='b 0 0 0 0 0 0\n'+lp+'e 0 0 6 0 0 0\n'+commands(-lx,(7-lw).astype(np.int16),123-lb,7,28,12)
    le=expected_records(-lx,(7-lw).astype(np.int16),123-lb,7,args.pm,28)
    for latency in (1,2):
        name=f'reset_l{latency}_phase6';r=run_case(out/name,lx,lw,lb,0,pm=args.pm,latency=latency,stream=ls,expected_override=le)
        results.append({'name':name,'status':r['status'],'manifest':str((out/name/'run_manifest.json').relative_to(ROOT))});print(name,r['status'],r.get('error',''),flush=True)
    for mutation in ('MUT_DROP_K63','MUT_UNSIGNED','MUT_TAG_G','MUT_WRONG_INDEX','MUT_EARLY_DONE','MUT_NO_OUTPUT_CREDIT','MUT_W_OWNER_EARLY','MUT_W_SLOT_ALIAS','MUT_W_SWITCH_EARLY'):
        r=test(mutation,mutation=mutation)
        log=(out/mutation/'sim.log').read_text() if (out/mutation/'sim.log').exists() else ''
        detected=r['status']=='FAIL' and len(r['commands'])==2 and r['commands'][0]['exit_code']==0 and (
            (r['commands'][1]['exit_code']==0 and r.get('error','').startswith(('output ','raw48'))) or
            (r['commands'][1]['exit_code']!=0 and any(s in log for s in ('early done','unstable blocked output','DONE_WITH_PENDING_INPUT','PIPE_','TILE_OWNER','W2_','unexpected fault'))))
        results[-1].update(status='PASS' if detected else 'FAIL',mutation_detected=detected)
    mutation='MUT_W_NO_DEFER';r=run_case(out/mutation,lx,lw,lb,0,pm=args.pm,stream=ls,expected_override=le,mutation=mutation)
    log=(out/mutation/'sim.log').read_text() if (out/mutation/'sim.log').exists() else ''
    detected=r['status']=='FAIL' and len(r['commands'])==2 and r['commands'][0]['exit_code']==0 and r['commands'][1]['exit_code']not in(0,124) and 'unexpected fault' in log
    results.append({'name':mutation,'status':'PASS' if detected else 'FAIL','mutation_detected':detected,'manifest':str((out/mutation/'run_manifest.json').relative_to(ROOT))});print(mutation,r['status'],r.get('error',''),flush=True)
    summary={'status':'PASS' if all(t['status']=='PASS' for t in results) else 'FAIL','pm':args.pm,'tests':results,
             'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__)},'RTL_mutation_classes':10}
    put(out/'summary.json',summary);print(out,flush=True);return 0 if summary['status']=='PASS' else 1

if __name__=='__main__':raise SystemExit(main())
