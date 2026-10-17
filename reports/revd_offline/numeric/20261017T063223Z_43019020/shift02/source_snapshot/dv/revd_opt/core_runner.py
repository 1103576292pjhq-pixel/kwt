"""Public stream simulation; dense numeric oracle never calls hardware address logic."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import re
import sys
from functools import lru_cache
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
import numpy as np
from numeric.fixedpoint import ffn1_reference
from scripts.revd_offline_common import command, put, sha, run_id, utc

def commands(x, w, b, shift, task=27, layer=1):
    lines = [f'0 {task:x} 0 0 0 {shift:x} {layer:x}']
    for i, v in enumerate(x.flat): lines.append(f'1 {task:x} 0 {i:x} {int(v)&((1<<48)-1):012x} 0 0')
    for t in range(w.shape[1]//16):
        lines.append(f'2 {task:x} {t:x} 0 0 0 0')
        for k in range(64):
            for j in range(16):
                lines.append(f'3 {task:x} {t:x} {k*16+j:x} {int(w[k,t*16+j])&((1<<48)-1):012x} 0 0')
        for j in range(16): lines.append(f'4 {task:x} {t:x} {j:x} {int(b[t*16+j])&((1<<48)-1):012x} 0 0')
        lines.append(f'5 {task:x} {t:x} 0 0 0 0')
    return '\n'.join(lines + [f'6 {task:x} 0 0 0 0 0', 'f 0 0 0 0 0 0']) + '\n'

def expected_records(x, w, b, shift, pm, task=27):
    ref = ffn1_reference(x, w, b, shift)
    m, n = x.shape[0], w.shape[1]
    return [[task, r*n+c, int(ref.output[r,c]), int(ref.overflow[r,c]),
             int(ref.output_saturated[r,c]), int(r==m-1 and c==n-1)]
            for t in range(0,n,16) for r0 in range(0,m,pm)
            for r in range(r0,min(r0+pm,m)) for c in range(t,t+16)]

def check_output(path, expected):
    lines = Path(path).read_text().splitlines()
    if len(lines) != len(expected): raise ValueError(f'output count {len(lines)} != {len(expected)}')
    seen = set()
    for pos, (line, want) in enumerate(zip(lines, expected)):
        if not re.fullmatch(r'[0-9a-fA-F]{8} [0-9a-fA-F]{8} [0-9a-fA-F]{8} [01] [01] [01]', line):
            raise ValueError(f'unknown/malformed output {pos}: {line}')
        fields = line.split()
        got = [int(s,16) for s in fields[:3]] + list(map(int,fields[3:]))
        if got[2] >= 1<<31: got[2] -= 1<<32
        if tuple(got[:2]) in seen: raise ValueError(f'duplicate task/index {pos}')
        seen.add(tuple(got[:2]))
        if got != want: raise ValueError(f'output {pos}: {got} != {want}')
    return {'outputs': len(lines), 'unique': len(seen), 'last_count': sum(v[-1] for v in expected), 'sha256': sha(path)}

def synthetic(m, n, seed=91):
    rng = np.random.default_rng(seed)
    return (rng.integers(-32768,32768,(m,64),dtype=np.int16),
            rng.integers(-32768,32768,(64,n),dtype=np.int16),
            rng.integers(-(1<<47),1<<47,(n,),dtype=np.int64))

@lru_cache(maxsize=1)
def tools():
    import subprocess
    result = {'python': sys.version, 'numpy': np.__version__}
    for name, flags in [('iverilog',['-V']), ('vvp',['-V']), ('verilator',['--version'])]:
        p = subprocess.run([name,*flags], stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                           text=True, timeout=15, check=True)
        result[name] = p.stdout
    return result

def run_case(out,x,w,b,shift,pm=4,latency=1,task=27,layer=1,baseline=False,
             mutation=None,stream=None,expected_override=None,task_count=1,
             raw_check=True,simulator='icarus'):
    out = Path(out); out.mkdir(parents=True,exist_ok=False)
    cmd = out/'commands.hex'
    cmd.write_text(stream if stream is not None else commands(x,w,b,shift,task,layer),encoding='ascii')
    expected = expected_records(x,w,b,shift,pm,task) if expected_override is None else expected_override
    put(out/'expected.json', expected)
    for name,a in [('X',x),('W',w),('b',b)]: np.save(out/(name+'.npy'),a,allow_pickle=False)
    config = {'M':x.shape[0], 'N':w.shape[1], 'PM':pm,'PN':4,'READ_LATENCY':latency,
              'schedule':'accepted_micro' if baseline else 'tagged_CTX4_pipeline',
              'weights':'full_W','results':'Y1','x_storage':f'X{pm}',
              'source_gap':'3 cycles after accept%13==7','sink_seed':'0xca05e123',
              'simulator':simulator,'mutation':mutation,'shift':shift,'task':task,'layer':layer}
    put(out/'config.json',config)
    hdl = [ROOT/'rtl/revd/banked_sp16.sv',ROOT/'rtl/revd/quant_epilogue.sv',
           ROOT/('rtl/revd/core_stream_frontend.sv' if baseline else 'rtl/revd_opt/core_stream_frontend_opt.sv')]
    tb=ROOT/'dv/revd_opt/core_tb.sv'
    py=[Path(__file__),ROOT/'scripts/revd_offline_common.py',ROOT/'numeric/fixedpoint.py']
    if simulator=='icarus':
        build=['iverilog','-g2012','-s','core_tb',*[f'-Pcore_tb.{k}={config[k]}' for k in ('M','N','PM','READ_LATENCY')],'-o',out/'sim.vvp']
        exe=['vvp',out/'sim.vvp']
    else:
        build=['verilator','--binary','--timing','-Wno-fatal','--top-module','core_tb','--Mdir',out/'obj','-j','2',
               *[f'-G{k}={config[k]}' for k in ('M','N','PM','READ_LATENCY')]]
        exe=[out/'obj/Vcore_tb']
    if baseline: build+=['-DBASELINE']
    if mutation: build+=['-D'+mutation]
    build += [tb,*hdl]
    receipt={'status':'FAIL','started_utc':utc(),'config':config,'config_sha256':sha(out/'config.json'),
             'expected_tasks':task_count,'tools':tools(),
             'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in [*hdl,tb,*py]},
             'input_sha256':{p.name:sha(p) for p in [cmd,out/'X.npy',out/'W.npy',out/'b.npy',out/'expected.json']},'commands':[]}
    # The run retains exact source bytes, including untracked candidate code.
    for p in [*hdl,tb,*py]:
        dst=out/'source_snapshot'/p.relative_to(ROOT);dst.parent.mkdir(parents=True,exist_ok=True);dst.write_bytes(p.read_bytes())
    try:
        receipt['commands'].append(command(build,out/'compile.log',timeout=180))
        if receipt['commands'][-1]['exit_code']: raise ValueError('RTL compilation failed')
        binary=out/('sim.vvp' if simulator=='icarus' else 'obj/Vcore_tb')
        receipt['binary_sha256']=sha(binary)
        receipt['commands'].append(command([*exe,f'+CMD={cmd}',f'+OUT={out/"output.hex"}',f'+STATS={out/"stats.txt"}'],out/'sim.log',timeout=240))
        if receipt['commands'][-1]['exit_code']: raise ValueError('RTL simulation failed')
        if 'RTL_COMPLETE' not in (out/'sim.log').read_text(): raise ValueError('missing simulator completion')
        receipt['comparison']=check_output(out/'output.hex',expected)
        stats=(out/'stats.txt').read_text().splitlines()
        keys=['task','load_cycles','compute_cycles','output_cycles','wait_cycles','core_cycles','frontend_cycles','issue','retire','effective_macs','virtual_macs','input_accepts','event_retires']
        counters=[dict(zip(keys,map(int,s.split()[1:]))) for s in stats if s.startswith('TASK ')]
        if len(counters)!=task_count: raise ValueError('missing/extra task stats')
        m,n=x.shape[0],w.shape[1]
        for c in counters:
            if c['effective_macs']!=m*n*64: raise ValueError('incorrect effective MAC counter')
            if c['issue']!=((m+pm-1)//pm)*(n//4)*64 or c['retire']!=c['issue']: raise ValueError('issue/retire mismatch')
            if c['input_accepts']!=c['event_retires']: raise ValueError('accepted command not retired')
            if c['core_cycles']!=c['compute_cycles']+c['output_cycles']: raise ValueError('core cycle partition mismatch')
            if c['frontend_cycles']!=c['load_cycles']+c['core_cycles']: raise ValueError('frontend partition mismatch')
        receipt['task_counters']=counters;receipt['counters']=counters[-1] if counters else None
        windows=[list(map(int,s.split()[1:])) for s in stats if s.startswith('WINDOW ')]
        if len(windows)!=task_count: raise ValueError('missing cold window timestamps')
        for c,v in zip(counters,windows):
            if len(v)!=6 or v[0]!=c['task'] or v[4]!=v[3]-v[1] or v[5]!=v[3]-v[2] or v[5]!=c['core_cycles']:
                raise ValueError('cold window timestamp mismatch')
            if v[4]!=c['frontend_cycles']+1: raise ValueError('frontend cycle boundary mismatch')
        receipt['cold_windows']=[dict(zip(('task','begin_accept_cycle','start_retire_cycle','last_output_fire_cycle','frontend_elapsed_cycles','core_elapsed_cycles'),v)) for v in windows]
        banks={k:[list(map(int,s.split()[1:])) for s in stats if s.startswith(k+' ')] for k in ('X','W')}
        receipt['banks']=banks
        if task_count:
            xfactor=n//4 if baseline else n//16
            if sum(v[1] for v in banks['X'])!=task_count*m*64*xfactor: raise ValueError('X CE reuse mismatch')
            if sum(v[2] for v in banks['X'])!=task_count*m*64: raise ValueError('X writes mismatch')
            if sum(v[1] for v in banks['W'])!=task_count*((m+pm-1)//pm)*n*64: raise ValueError('W CE mismatch')
            if sum(v[2] for v in banks['W'])!=task_count*n*64: raise ValueError('W writes mismatch')
        if raw_check and stream is None:
            dot=x.astype(np.int64)@w.astype(np.int64);ref=ffn1_reference(x,w,b,shift)
            raw_lines=[s.split() for s in stats if s.startswith('RAW ')]
            if len(raw_lines)!=m*n: raise ValueError('raw trace count mismatch')
            seen=set()
            for s in raw_lines:
                t,i=int(s[1]),int(s[2]);r,c=divmod(i,n)
                vals=[int(v,16) for v in s[3:]]
                vals=[v-(1<<48) if v&(1<<47) else v for v in vals]
                if (t,i) in seen or t!=task or not (0<=r<m and 0<=c<n): raise ValueError('raw trace identity')
                seen.add((t,i))
                if vals!=[int(dot[r,c]),int(ref.raw[r,c])]: raise ValueError(f'raw48 trace mismatch {i}: {vals}')
            receipt['raw48_trace_checked']=len(seen)
        receipt['output_sha256']={p.name:sha(p) for p in (out/'output.hex',out/'stats.txt',out/'compile.log',out/'sim.log')}
        if any(sha(ROOT/p)!=v for p,v in receipt['source_sha256'].items()): raise ValueError('source changed while running')
        if any(sha(out/p)!=v for p,v in receipt['input_sha256'].items()): raise ValueError('input changed while running')
        receipt['status']='PASS'
    except (ValueError,OSError,RuntimeError) as exc:
        receipt['error']=str(exc)
    receipt['finished_utc']=utc();put(out/'run_manifest.json',receipt)
    return receipt

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--profile',choices=['small','production','full36','repeat','red','cross'],default='small')
    ap.add_argument('--run-id');ap.add_argument('--latency',type=int,default=1);ap.add_argument('--pm',type=int,choices=[2,4],default=4)
    ap.add_argument('--baseline',action='store_true');args=ap.parse_args()
    out=ROOT/'reports/revd_offline/core'/(args.run_id or run_id());out.mkdir(parents=True,exist_ok=False)
    if args.profile in ('small','red','cross'):
        shapes=[(1,16,0),(3,16,16),(4,32,47),(5,32,8)] if args.profile=='small' else [(5,32,8)]
        cases=[(f'm{m}n{n}',*synthetic(m,n,m*n+args.pm),s,1) for m,n,s in shapes]
    elif args.profile=='production': cases=[('synthetic99',*synthetic(99,256),8,1)]
    else:
        from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
        manifest,verification=verify_frozen_inputs(ROOT)
        put(out/'validated_inputs.json',{'verification':verification,'manifest_sha256':sha(ROOT/'reports/prototype/vectors/manifest.json')})
        cases=[]
        for c in manifest['cases'] if args.profile=='full36' else manifest['cases'][:1]:
            a=validated_case(ROOT,c)
            cases.append((c['case_id'].replace('/','_'),a['Xq'],a['Wq'],a['bq'],c['config']['output_shift'],c['layer']))
    results=[]
    for label,x,w,b,s,layer in cases:
        r=run_case(out/label,x,w,b,s,args.pm,args.latency,layer=layer,baseline=args.baseline,simulator='verilator' if args.profile=='cross' else 'icarus')
        results.append({'case':label,'manifest':str((out/label/'run_manifest.json').relative_to(ROOT)),'status':r['status'],'error':r.get('error')})
        print(label,r['status'],r.get('error',r.get('comparison')),flush=True)
        if r['status']!='PASS': break
    ok=len(results)==len(cases) and all(r['status']=='PASS' for r in results)
    put(out/'summary.json',{'status':'PASS' if ok else 'FAIL','profile':args.profile,'baseline':args.baseline,'pm':args.pm,'latency':args.latency,'cases':results})
    print(out,flush=True)
    return 0 if ok else 1

if __name__=='__main__': raise SystemExit(main())
