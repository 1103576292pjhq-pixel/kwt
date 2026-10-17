"""Bounded W1/Y1 experiment: public tile0 preload, START, then next tiles.

This entry never edits the frozen core/SoC reports. The RED profile compiles the
full-W core and demonstrates rejection of the newly required tiled schedule.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import re
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
import numpy as np
from numeric.fixedpoint import ffn1_reference
from scripts.revd_offline_common import command,put,sha,run_id,utc

def commands(x,w,b,shift,task=27,layer=1):
    lines=[f'0 {task:x} 0 0 0 {shift:x} {layer:x}']
    for i,v in enumerate(x.flat):lines.append(f'1 {task:x} 0 {i:x} {int(v)&((1<<48)-1):012x} 0 0')
    for t in range(w.shape[1]//16):
        lines.append(f'2 {task:x} {t:x} 0 0 0 0')
        for k in range(64):
            for c in range(16):lines.append(f'3 {task:x} {t:x} {k*16+c:x} {int(w[k,t*16+c])&((1<<48)-1):012x} 0 0')
        for c in range(16):lines.append(f'4 {task:x} {t:x} {c:x} {int(b[t*16+c])&((1<<48)-1):012x} 0 0')
        lines.append(f'5 {task:x} {t:x} 0 0 0 0')
        if t==0:lines.append(f'6 {task:x} 0 0 0 0 0')
    return '\n'.join(lines+['f 0 0 0 0 0 0'])+'\n'

def expected_records(x,w,b,shift,pm,task=27):
    ref=ffn1_reference(x,w,b,shift);m,n=x.shape[0],w.shape[1]
    return [[task,r*n+c,int(ref.output[r,c]),int(ref.overflow[r,c]),int(ref.output_saturated[r,c]),int(r==m-1 and c==n-1)]
            for t in range(0,n,16) for r0 in range(0,m,pm) for r in range(r0,min(r0+pm,m)) for c in range(t,t+16)]

def synthetic(m,n,seed=91):
    rng=np.random.default_rng(seed)
    return rng.integers(-32768,32768,(m,64),dtype=np.int16),rng.integers(-32768,32768,(64,n),dtype=np.int16),rng.integers(-(1<<47),1<<47,n,dtype=np.int64)

def run_case(out,x,w,b,shift,pm=4,latency=1,task=27,layer=1,red=False,stream=None,expected_override=None,task_count=1,mutation=None):
    out=Path(out);out.mkdir(parents=True,exist_ok=False)
    config={'M':x.shape[0],'N':w.shape[1],'PM':pm,'READ_LATENCY':latency,'shift':shift,'task':task,'layer':layer,
            'schedule':'CTX4','weights':'W1_256x16_four_banks','results':'Y1','protocol':'tile0_COMMIT_START_then_OPEN','red_fullW_reference':red,'mutation':mutation,
            'source_gap':'3 cycles after accept%13==7','sink_seed':'0xca05e123'}
    put(out/'config.json',config)
    (out/'commands.hex').write_text(stream if stream is not None else commands(x,w,b,shift,task,layer),encoding='ascii')
    expected=expected_records(x,w,b,shift,pm,task) if expected_override is None else expected_override
    put(out/'expected.json',expected)
    for name,a in [('X',x),('W',w),('b',b)]:np.save(out/(name+'.npy'),a,allow_pickle=False)
    core=ROOT/('rtl/revd_opt/core_stream_frontend_opt.sv' if red else 'rtl/revd_opt/core_stream_tiled_opt.sv')
    sources=[ROOT/'dv/revd_opt/tiled_core_tb.sv',ROOT/'rtl/revd/banked_sp16.sv',ROOT/'rtl/revd/quant_epilogue.sv',core]
    bound=sources+[Path(__file__),ROOT/'numeric/fixedpoint.py',ROOT/'scripts/revd_offline_common.py']
    receipt={'status':'FAIL','started_utc':utc(),'config':config,'config_sha256':sha(out/'config.json'),'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in bound},
             'input_sha256':{p.name:sha(p) for p in [out/'commands.hex',out/'expected.json',out/'X.npy',out/'W.npy',out/'b.npy']},'commands':[]}
    for p in bound:
        dest=out/'source_snapshot'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(p.read_bytes())
    try:
        build=['iverilog','-g2012','-s','tiled_core_tb',*[f'-Ptiled_core_tb.{k}={config[k]}' for k in ('M','N','PM','READ_LATENCY')],'-o',out/'sim.vvp']
        if red:build+=['-DTILED_RED_REFERENCE']
        if mutation:build+=['-D'+mutation]
        receipt['commands'].append(command(build+sources,out/'compile.log',timeout=120))
        if receipt['commands'][-1]['exit_code']:raise ValueError('compile failed')
        receipt['binary_sha256']=sha(out/'sim.vvp')
        receipt['commands'].append(command(['vvp',out/'sim.vvp',f'+CMD={out/"commands.hex"}',f'+OUT={out/"output.hex"}',f'+STATS={out/"stats.txt"}'],out/'sim.log',timeout=240))
        if receipt['commands'][-1]['exit_code']:raise ValueError('simulation failed')
        if 'RTL_COMPLETE' not in (out/'sim.log').read_text():raise ValueError('missing RTL completion')
        output=(out/'output.hex').read_text().splitlines()
        if len(output)!=len(expected):raise ValueError(f'output count {len(output)} != {len(expected)}')
        seen=set()
        for i,(line,want) in enumerate(zip(output,expected)):
            if not re.fullmatch(r'[0-9a-fA-F]{8} [0-9a-fA-F]{8} [0-9a-fA-F]{8} [01] [01] [01]',line):raise ValueError('malformed/XZ output')
            fs=line.split();got=[int(v,16) for v in fs[:3]]+list(map(int,fs[3:]))
            if got[2]>=1<<31:got[2]-=1<<32
            if tuple(got[:2]) in seen:raise ValueError('duplicate task/index')
            seen.add(tuple(got[:2]))
            if got!=want:raise ValueError(f'output {i}: {got} != {want}')
        stats=(out/'stats.txt').read_text().splitlines()
        keys=['task','load_cycles','compute_cycles','output_cycles','wait_cycles','core_cycles','frontend_cycles','issue','retire','effective_macs','virtual_macs','input_accepts','event_retires']
        counters=[dict(zip(keys,map(int,s.split()[1:]))) for s in stats if s.startswith('TASK ')]
        if len(counters)!=task_count:raise ValueError('missing task counters')
        m,n=x.shape[0],w.shape[1]
        for c in counters:
            if c['effective_macs']!=m*n*64 or c['issue']!=((m+pm-1)//pm)*(n//4)*64 or c['retire']!=c['issue']:raise ValueError('MAC/issue/retire mismatch')
            if c['input_accepts']!=c['event_retires']:raise ValueError('pending event at done')
        receipt['task_counters']=counters
        banks={k:[list(map(int,s.split()[1:])) for s in stats if s.startswith(k+' ')] for k in ('X','W')}
        if task_count:
            if sum(v[1] for v in banks['X'])!=task_count*m*64*(n//16) or sum(v[2] for v in banks['X'])!=task_count*m*64:raise ValueError('X CE mismatch')
            if sum(v[1] for v in banks['W'])!=task_count*((m+pm-1)//pm)*n*64 or sum(v[2] for v in banks['W'])!=task_count*n*64:raise ValueError('W CE mismatch')
        receipt['banks']=banks
        receipt['tile_counters']=[list(map(int,s.split()[1:])) for s in stats if s.startswith('TILE_STATS ')]
        receipt['windows']=[list(map(int,s.split()[1:])) for s in stats if s.startswith('WINDOW ')]
        if stream is None:
            ref=ffn1_reference(x,w,b,shift);dot=x.astype(np.int64)@w.astype(np.int64)
            raw=[s.split() for s in stats if s.startswith('RAW ')]
            if len(raw)!=m*n:raise ValueError('raw count')
            rseen=set()
            for s in raw:
                t,index=int(s[1]),int(s[2]);r,c=divmod(index,n)
                vals=[int(v,16) for v in s[3:]];vals=[v-(1<<48) if v&(1<<47) else v for v in vals]
                if (t,index) in rseen or t!=task or r>=m or c>=n:raise ValueError('raw identity')
                rseen.add((t,index))
                if vals!=[int(dot[r,c]),int(ref.raw[r,c])]:raise ValueError(f'raw48 mismatch {index}')
            receipt['raw48_checked']=len(rseen)
        if any(sha(ROOT/p)!=v for p,v in receipt['source_sha256'].items()):raise ValueError('source changed')
        if any(sha(out/p)!=v for p,v in receipt['input_sha256'].items()):raise ValueError('input changed')
        receipt['comparison']={'outputs':len(output),'unique':len(seen),'last_count':sum(v[-1] for v in expected)}
        receipt['status']='PASS'
    except (ValueError,OSError,RuntimeError) as exc:receipt['error']=str(exc)
    receipt['output_sha256']={p.name:sha(p) for p in out.iterdir() if p.is_file() and p.name not in ('run_manifest.json',)}
    receipt['finished_utc']=utc();put(out/'run_manifest.json',receipt);return receipt

def main():
    p=argparse.ArgumentParser();p.add_argument('--profile',choices=['red','small','production','full36','repeat'],default='small');p.add_argument('--run-id');p.add_argument('--pm',type=int,choices=[2,4],default=4);p.add_argument('--latency',type=int,choices=[1,2],default=1);args=p.parse_args()
    out=ROOT/'reports/revd_offline/tiled'/(args.run_id or run_id());out.mkdir(parents=True,exist_ok=False)
    if args.profile in ('red','small'):
        cases=[(f'm{m}n{n}',*synthetic(m,n,m*n+args.pm),s,1) for m,n,s in ([(5,32,8)] if args.profile=='red' else [(1,16,0),(3,32,47),(5,32,8)])]
    elif args.profile=='production':cases=[('synthetic99',*synthetic(99,256),8,1)]
    else:
        from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
        manifest,verification=verify_frozen_inputs(ROOT);put(out/'validated_inputs.json',verification);cases=[]
        for c in manifest['cases'] if args.profile=='full36' else manifest['cases'][:1]:
            a=validated_case(ROOT,c);cases.append((c['case_id'].replace('/','_'),a['Xq'],a['Wq'],a['bq'],c['config']['output_shift'],c['layer']))
    results=[]
    for label,x,w,b,s,layer in cases:
        r=run_case(out/label,x,w,b,s,args.pm,args.latency,layer=layer,red=args.profile=='red')
        results.append({'case':label,'status':r['status'],'error':r.get('error'),'manifest':str((out/label/'run_manifest.json').relative_to(ROOT))})
        print(label,r['status'],r.get('error',r.get('comparison')),flush=True)
        if r['status']!='PASS':break
    ok=len(results)==len(cases) and all(r['status']=='PASS' for r in results)
    summary={'status':'PASS' if ok else 'FAIL','profile':args.profile,'pm':args.pm,'latency':args.latency,'cases':results,'tools':{},'source_sha256':{str(Path(__file__).relative_to(ROOT)):sha(__file__)}}
    if args.profile=='red':
        r=json.loads((out/results[0]['case']/'run_manifest.json').read_text());log=(out/results[0]['case']/'sim.log').read_text()
        summary['expected_rejection_detected']=len(r['commands'])==2 and r['commands'][0]['exit_code']==0 and r['commands'][1]['exit_code']!=0 and 'unexpected fault' in log
    put(out/'summary.json',summary);print(out,flush=True);return 0 if ok else 1

if __name__=='__main__':raise SystemExit(main())
