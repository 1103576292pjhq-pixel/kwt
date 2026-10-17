"""Fail-closed W2/Y1 evidence gate. Independent from the full-W/D3 gate.

PN/K/N_TILE are fixed RTL defaults: compilation may override only M/N/PM/L.
This checker accepts local core evidence; it never grants CPU/physical signoff.
"""
from __future__ import annotations
import argparse
from functools import lru_cache
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
import numpy as np
from numeric.fixedpoint import ffn1_reference
from scripts.revd_offline_common import sha,read_json,put,utc

CORE='rtl/revd_opt/core_stream_tiled_w2_opt.sv'
TB='dv/revd_opt/tiled_w2_core_tb.sv'
SOURCES={CORE,TB,'rtl/revd/banked_sp16.sv','rtl/revd/quant_epilogue.sv','dv/revd_opt/tiled_w2_runner.py','numeric/fixedpoint.py','scripts/revd_offline_common.py'}
MUTANTS=('MUT_DROP_K63','MUT_UNSIGNED','MUT_TAG_G','MUT_WRONG_INDEX','MUT_EARLY_DONE','MUT_NO_OUTPUT_CREDIT','MUT_W_NO_DEFER','MUT_W_OWNER_EARLY','MUT_W_SLOT_ALIAS','MUT_W_SWITCH_EARLY')
OUTPUTS={'config.json','commands.hex','expected.json','X.npy','W.npy','b.npy','compile.log','compile.log.command.json','sim.vvp','sim.log','sim.log.command.json','stats.txt','output.hex'}

def need(ok,message):
    if not ok:raise ValueError(message)

@lru_cache(maxsize=2)
def current_tool(name):
    located=shutil.which(name);need(located is not None,'missing actual tool '+name)
    executable=Path(located).resolve()
    try:
        version=subprocess.run([str(executable),'-V'],text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=15,check=True).stdout
    except (OSError,subprocess.SubprocessError) as exc:raise ValueError('tool identity query failed '+name+': '+str(exc)) from exc
    return {'path':str(executable),'sha256':sha(executable),'version':version}

def hashes(base,items):
    need(isinstance(items,dict) and items,'empty hash inventory')
    for name,digest in items.items():need((base/name).is_file() and sha(base/name)==digest,'SHA/missing '+str(base/name))

def oracle(x,w,b,shift,pm,task):
    a=ffn1_reference(x,w,b,shift);m,n=x.shape[0],w.shape[1]
    return [[task,r*n+c,int(a.output[r,c]),int(a.overflow[r,c]),int(a.output_saturated[r,c]),int(r==m-1 and c==n-1)]
            for col in range(0,n,16) for row in range(0,m,pm) for r in range(row,min(row+pm,m)) for c in range(col,col+16)]

def public_stream(x,w,b,shift,task,layer):
    lines=[f'0 {task:x} 0 0 0 {shift:x} {layer:x}']
    for i,a in enumerate(x.flat):lines.append(f'1 {task:x} 0 {i:x} {int(a)&((1<<48)-1):012x} 0 0')
    for t in range(w.shape[1]//16):
        lines.append(f'2 {task:x} {t:x} 0 0 0 0')
        for i in range(1024):lines.append(f'3 {task:x} {t:x} {i:x} {int(w[i//16,t*16+i%16])&((1<<48)-1):012x} 0 0')
        for i in range(16):lines.append(f'4 {task:x} {t:x} {i:x} {int(b[t*16+i])&((1<<48)-1):012x} 0 0')
        lines.append(f'5 {task:x} {t:x} 0 0 0 0')
        if t==0:lines.append(f'6 {task:x} 0 0 0 0 0')
    return '\n'.join(lines+['f 0 0 0 0 0 0'])+'\n'

def artifacts(path,mutation=None):
    path=Path(path);out=path.parent;r=read_json(path);c=r['config']
    need(r['status']==('FAIL' if mutation else 'PASS'),'unexpected run status')
    need(c['PM'] in (2,4) and c['READ_LATENCY'] in (1,2) and 1<=c['M']<=99 and 16<=c['N']<=256 and c['N']%16==0,'unsupported geometry')
    need(c['schedule']=='CTX4' and c['weights']=='W2_two_sets_of_four_256x16_banks' and c['results']=='Y1' and c['protocol']=='tile0_COMMIT_START_then_OPEN','mixed architecture')
    need(c['red_W1_reference'] is False and c['mutation']==mutation,'wrong RTL variant')
    need(c['source_gap']=='3 cycles after accept%13==7' and c['sink_seed']=='0xca05e123','mixed source/sink policy')
    need(read_json(out/'config.json')==c and sha(out/'config.json')==r['config_sha256'],'mixed configuration')
    need(set(r['source_sha256'])==SOURCES,'missing/aliased source inventory')
    for name,digest in r['source_sha256'].items():
        need(sha(ROOT/name)==digest and sha(out/'source_snapshot'/name)==digest,'stale source '+name)
    # No implicit variable precision/geometry: the actual source default and
    # exact compile argv together establish the effective fixed parameters.
    source=(ROOT/CORE).read_text()
    need(bool(re.search(r'READ_LATENCY=1,K=64,PN=4,N_TILE=16',source)),'fixed K/PN/N_TILE default changed')
    need(set(r['input_sha256'])=={'commands.hex','X.npy','W.npy','b.npy','expected.json'},'input inventory')
    need(set(r['output_sha256'])==OUTPUTS,'output/binary/log inventory')
    hashes(out,r['input_sha256']);hashes(out,r['output_sha256'])
    need(len(r['commands'])==2,'missing actual compile/simulation')
    for record in r['commands']:
        need(record['pid']>0 and record['seconds']>=0 and 0<record['timeout_seconds']<900 and bool(record['finished_utc']),'unbounded/incomplete process')
        need(record['exit_code'] is not None and record['exit_code']!=124,'timeout/unfinished process')
        log=ROOT/record['log'];need(sha(log)==record['log_sha256'] and read_json(log.with_suffix('.log.command.json'))==record,'changed command receipt/log')
    need(r['commands'][0]['exit_code']==0,'compilation was not successful')
    binary=out/'sim.vvp';need(sha(binary)==r['binary_sha256'],'compiled binary hash')
    build=['iverilog','-g2012','-s','tiled_w2_core_tb',*[f'-Ptiled_w2_core_tb.{k}={c[k]}' for k in ('M','N','PM','READ_LATENCY')],'-o',str(binary)]
    if mutation:build+=['-D'+mutation]
    build += [str(ROOT/p) for p in (TB,'rtl/revd/banked_sp16.sv','rtl/revd/quant_epilogue.sv',CORE)]
    need(r['commands'][0]['argv']==build,'compile source/parameter/binary binding')
    need(r['commands'][1]['argv']==['vvp',str(binary),f'+CMD={out/"commands.hex"}',f'+OUT={out/"output.hex"}',f'+STATS={out/"stats.txt"}'],'simulation binary/input/output binding')
    tools=r['tools']
    need(tools['python']==sys.version and tools['numpy']==np.__version__ and tools['python_sha256']==sha(Path(sys.executable)), 'Python/NumPy tool identity changed')
    for name in ('iverilog','vvp'):
        actual=current_tool(name)
        need(tools[name]==actual and sha(Path(actual['path']))==actual['sha256'],'actual executable path/SHA/version differs '+name)
    x=np.load(out/'X.npy',allow_pickle=False);w=np.load(out/'W.npy',allow_pickle=False);b=np.load(out/'b.npy',allow_pickle=False)
    need(x.shape==(c['M'],64) and w.shape==(64,c['N']) and b.shape==(c['N'],),'input geometry')
    need(x.dtype==np.int16 and w.dtype==np.int16 and b.dtype==np.int64 and np.all(b>=-(1<<47)) and np.all(b<(1<<47)),'input numeric domain')
    return r,c,out,x,w,b

def check_case(path,expected=None,tasks=1,pm=None,latency=None):
    r,c,out,x,w,b=artifacts(path)
    if pm is not None:need(c['PM']==pm,'mixed PM')
    if latency is not None:need(c['READ_LATENCY']==latency,'mixed latency')
    ordinary=expected is None
    if ordinary:
        need((out/'commands.hex').read_text()==public_stream(x,w,b,c['shift'],c['task'],c['layer']),'public tiled stream differs from numeric inputs')
        expected=oracle(x,w,b,c['shift'],c['PM'],c['task'])
    need(read_json(out/'expected.json')==expected,'expected is not independent fixed oracle')
    need(r['commands'][1]['exit_code']==0 and 'RTL_COMPLETE' in (out/'sim.log').read_text(),'missing successful simulator completion')
    lines=(out/'output.hex').read_text().splitlines();need(len(lines)==len(expected),'missing/extra output including final record');seen=set()
    for line,want in zip(lines,expected):
        need(bool(re.fullmatch(r'[0-9a-fA-F]{8} [0-9a-fA-F]{8} [0-9a-fA-F]{8} [01] [01] [01]',line)),'malformed/XZ output')
        f=line.split();got=[int(v,16) for v in f[:3]]+list(map(int,f[3:]))
        if got[2]>=1<<31:got[2]-=1<<32
        need(tuple(got[:2]) not in seen,'duplicate task/index');seen.add(tuple(got[:2]));need(got==want,'Y/flags/task/index/last mismatch')
    need(r['comparison']=={'outputs':len(lines),'unique':len(seen),'last_count':sum(v[-1] for v in expected)},'comparison metadata differs')
    stats=(out/'stats.txt').read_text().splitlines()
    rows=[list(map(int,s.split()[1:])) for s in stats if s.startswith('TASK ')];slots=[list(map(int,s.split()[1:])) for s in stats if s.startswith('TILE_STATS ')];windows=[list(map(int,s.split()[1:])) for s in stats if s.startswith('WINDOW ')]
    need(len(rows)==len(slots)==len(windows)==tasks,'missing actual task/owner/window records')
    keys=['task','load_cycles','compute_cycles','output_cycles','wait_cycles','core_cycles','frontend_cycles','issue','retire','effective_macs','virtual_macs','input_accepts','event_retires']
    need(r['task_counters']==[dict(zip(keys,t)) for t in rows] and r['tile_counters']==slots and r['windows']==windows,'author counters differ from actual RTL trace')
    banks={k:[list(map(int,s.split()[1:])) for s in stats if s.startswith(k+' ')] for k in ('X','W')}
    need(r['banks']==banks,'author bank counters differ from RTL trace')
    need(len(banks['W'])==8*tasks and all(v[0]==i%8 for i,v in enumerate(banks['W'])),'missing/aliased physical SP bank accounting')
    w2=[list(map(int,s.split()[1:])) for s in stats if s.startswith('W2_STATS ')]
    need(r['w2_counters']==w2 and len(w2)==tasks,'missing/handfilled W2 overlap/owner evidence')
    for t,trace in zip(rows,w2):
        need(len(trace)==7 and trace[0]==t[0] and all(v>=0 for v in trace),'W2 overlap owner identity/nonnegative counters')
        need(trace[3]==trace[4] and trace[3]<=trace[1] and trace[5]<=trace[1],'W2 read/issue/retire write overlap accounting')
        if c['N']>16:need(trace[1]>0 and trace[2]==2 and trace[3]>0 and trace[5]>0,'no actual physical W2 overlap/double ownership')
    if tasks:
        need(sum(v[1] for v in banks['X'])==tasks*c['M']*64*(c['N']//16) and sum(v[2] for v in banks['X'])==tasks*c['M']*64,'actual X read/write CE')
        need(sum(v[1] for v in banks['W'])==tasks*((c['M']+c['PM']-1)//c['PM'])*c['N']*64 and sum(v[2] for v in banks['W'])==tasks*c['N']*64,'actual W read/write CE')
    for t,s,v in zip(rows,slots,windows):
        need(len(t)==13 and len(s)==6 and len(v)==6 and t[0]==s[0]==v[0],'task record schema/identity')
        need(t[-1]==t[-2] and t[7]==t[8]==((c['M']+c['PM']-1)//c['PM'])*(c['N']//4)*64 and t[9]==c['M']*c['N']*64,'pending input/MAC retirement')
        need(s[3]==s[4]==c['N']//16 and t[5]==t[2]+t[3]+s[1]+s[2],'tile owner lifetime/cycle partition')
        need(v[4]==v[3]-v[1]==t[6]+1 and v[5]==v[3]-v[2]==t[5],'cold timestamp window')
    if ordinary:
        ref=ffn1_reference(x,w,b,c['shift']);dot=x.astype(np.int64)@w.astype(np.int64);raw=[s.split() for s in stats if s.startswith('RAW ')]
        need(len(raw)==c['M']*c['N'],'raw48 count');seen_raw=set()
        for f in raw:
            task,index=int(f[1]),int(f[2]);row,col=divmod(index,c['N']);need(task==c['task'] and 0<=row<c['M'] and 0<=col<c['N'] and index not in seen_raw,'raw48 identity');seen_raw.add(index)
            values=[int(v,16) for v in f[3:]];values=[v-(1<<48) if v&(1<<47) else v for v in values]
            need(values==[int(dot[row,col]),int(ref.raw[row,col])],'raw48 arithmetic')
        if c['N']>32 and c['M']>=9:need(slots[0][-1]>0,'deferred next OPEN not exercised')
    return {'status':'PASS','manifest':str(Path(path).relative_to(ROOT)),'sha256':sha(path),'outputs':len(lines),'config':c}

def check_suite(path,pm=4,latency=1):
    j=read_json(path);need(j['status']=='PASS','suite failed');need(j['pm']==pm and j['latency']==latency,'suite profile mismatch')
    need(j['profile'] in ('small','production','full36','repeat'),'unknown suite role')
    entries=j['cases'];need(entries and all(t['status']=='PASS' for t in entries) and len({x['manifest'] for x in entries})==len(entries),'failed/aliased cases')
    results=[check_case(ROOT/t['manifest'],pm=pm,latency=latency) for t in entries]
    if j['profile'] in ('small','production'):
        profiles={'synthetic99':(99,256,8,91)} if j['profile']=='production' else {'m1n16':(1,16,0,16+pm),'m3n32':(3,32,47,96+pm),'m5n32':(5,32,8,160+pm)}
        need(len(entries)==len(profiles) and {t['case'] for t in entries}==set(profiles),'exact synthetic suite role/case inventory')
        for t in entries:
            m,n,shift,seed=profiles[t['case']];folder=(ROOT/t['manifest']).parent;c=read_json(folder/'run_manifest.json')['config']
            need((c['M'],c['N'],c['shift'],c['task'],c['layer'])==(m,n,shift,27,1),'synthetic suite geometry/parameters')
            rng=np.random.default_rng(seed)
            expected=(rng.integers(-32768,32768,(m,64),dtype=np.int16),rng.integers(-32768,32768,(64,n),dtype=np.int16),rng.integers(-(1<<47),1<<47,n,dtype=np.int64))
            need(all(np.array_equal(np.load(folder/local,allow_pickle=False),value) for local,value in zip(('X.npy','W.npy','b.npy'),expected)),'synthetic suite independent input identity')
    if j['profile']=='full36':
        frozen=read_json(ROOT/'reports/prototype/vectors/manifest.json');want={c['case_id'].replace('/','_'):c for c in frozen['cases']}
        need(len(entries)==36 and {t['case'] for t in entries}==set(want) and sum(t['outputs'] for t in results)==912384,'full36 exact identities/count')
        for t in entries:
            case=want[t['case']];folder=(ROOT/t['manifest']).parent;r=read_json(folder/'run_manifest.json')
            need(r['config']['M']==99 and r['config']['N']==256 and r['config']['layer']==case['layer'] and r['config']['shift']==case['config']['output_shift'],'frozen layer config')
            for local,key in [('X.npy','Xq'),('W.npy','Wq'),('b.npy','bq')]:need(sha(folder/local)==case['arrays'][key]['sha256'],'frozen input identity')
    elif j['profile']=='repeat':
        need(len(entries)==1,'repeat count');case=read_json(ROOT/'reports/prototype/vectors/manifest.json')['cases'][0];folder=(ROOT/entries[0]['manifest']).parent
        need(entries[0]['case']==case['case_id'].replace('/','_'),'repeat is not first full frozen case')
        c=read_json(folder/'run_manifest.json')['config'];need((c['M'],c['N'],c['layer'],c['shift'])==(99,256,case['layer'],case['config']['output_shift']),'repeat frozen geometry/parameters')
        for local,key in [('X.npy','Xq'),('W.npy','Wq'),('b.npy','bq')]:need(sha(folder/local)==case['arrays'][key]['sha256'],'repeat frozen input')
    return {'status':'PASS','cases':len(results),'outputs':sum(t['outputs'] for t in results),'results':results}

def check_protocol(path,pm=4):
    j=read_json(path);need(j['status']=='PASS' and j['pm']==pm,'protocol failed/profile mismatch');hashes(ROOT,j['source_sha256'])
    normal=[]
    for l in (1,2):normal += [f'{n}_l{l}' for n in ('premature_future_OPEN','wrong_future_tile','reset_partial_X','reset_partial_W','reset_wait_tile','last_invalid','pending_last_fire','pending_last_blocked','next_BEGIN')]+[f'reset_l{l}_phase{p}' for p in range(1,7)]
    normal += ['commit_last_Y_l1','commit_last_Y_l2']
    normal+=['continuous_cold_params','fault_preserves_tile_block'];entries={t['name']:t for t in j['tests']}
    need(len(entries)==len(j['tests'])==44 and set(entries)==set(normal)|set(MUTANTS),'protocol exact test inventory')
    need(len({t['manifest'] for t in entries.values()})==44,'aliased protocol receipts')
    x=np.zeros((5,64),dtype=np.int16);x[:,63]=[-32768,-3,1,4,32767];w=np.zeros((64,32),dtype=np.int16);w[63]=np.arange(-16,16,dtype=np.int16);b=np.arange(-16,16,dtype=np.int64)
    old=oracle(x,w,b,0,pm,27);new=oracle(-x,(7-w).astype(np.int16),123-b,7,pm,28)
    complete=public_stream(x,w,b,0,27,1);full=complete.rsplit('f 0 0 0 0 0 0',1)[0]
    preload=full.split('6 1b 0 0 0 0 0',1)[0];first=preload+'6 1b 0 0 0 0 0\n'
    second=public_stream(-x,(7-w).astype(np.int16),123-b,7,28,12)
    lx=np.zeros((13,64),dtype=np.int16);lx[:,63]=[32767,-32768,-3,1,4,5,-7,0,8,-9,11,-13,17]
    lw=np.zeros((64,48),dtype=np.int16);lw[63]=np.arange(-24,24,dtype=np.int16);lb=np.arange(-24,24,dtype=np.int64)
    lp=public_stream(lx,lw,lb,0,27,1).split('2 1b 2 0 0 0 0\n',1)[0]+'2 1b 2 0 0 0 0\n'
    large_stream='b 0 0 0 0 0 0\n'+lp+'e 0 0 6 0 0 0\n'+public_stream(-lx,(7-lw).astype(np.int16),123-lb,7,28,12)
    for name in normal:
        e=entries[name];need(e['status']=='PASS','protocol case failed');r=read_json(ROOT/e['manifest']);c=r['config'];out=(ROOT/e['manifest']).parent
        if name in ('reset_l1_phase6','reset_l2_phase6'):
            need(c['M']==13 and c['N']==48 and c['PM']==pm and c['shift']==0 and c['task']==27,'dual-full deferred-reset geometry')
            need(np.array_equal(np.load(out/'X.npy'),lx) and np.array_equal(np.load(out/'W.npy'),lw) and np.array_equal(np.load(out/'b.npy'),lb),'dual-full deferred-reset numeric identity')
            need((out/'commands.hex').read_text()==large_stream and 'RESET 6 ' in (out/'stats.txt').read_text(),'dual-full third OPEN/reset stream identity')
            check_case(ROOT/e['manifest'],oracle(-lx,(7-lw).astype(np.int16),123-lb,7,pm,28),1,pm,1 if '_l1_' in name else 2)
            continue
        need(c['M']==5 and c['N']==32 and c['PM']==pm and c['shift']==0 and c['task']==27,'directed profile identity')
        need(np.array_equal(np.load(out/'X.npy'),x) and np.array_equal(np.load(out/'W.npy'),w) and np.array_equal(np.load(out/'b.npy'),b),'directed numeric identity')
        expected=old;tasks=1
        if name.startswith(('premature_','wrong_')):expected=[];tasks=0
        elif name.startswith('reset_wait'):expected=old[:80]+new
        elif name.startswith('reset_'):expected=new
        elif name.startswith('pending_'):tasks=0
        elif name.startswith('next_BEGIN') or name=='continuous_cold_params':expected=old+new;tasks=2
        elif name=='fault_preserves_tile_block':expected=old[:pm*16];tasks=0
        m=re.search(r'_l([12])(?:$|_)',name);lat=int(m[1]) if m else 1
        check_case(ROOT/e['manifest'],expected,tasks,pm,lat)
        stream=(out/'commands.hex').read_text();stats=(out/'stats.txt').read_text()
        if name.startswith('premature_'):canonical=preload+'2 1b 1 0 0 0 0\nc 0 0 0 0 0 0\n'
        elif name.startswith('wrong_'):canonical=first+'2 1b 2 0 0 0 0\nc 0 0 0 0 0 0\n'
        elif name.startswith('reset_partial_'):
            # RESET0 is shared by the two tests, so exact pre-reset public
            # loading evidence is required to distinguish X and W ownership.
            count=17 if name.startswith('reset_partial_X') else 1+5*64+1+17
            canonical='\n'.join(preload.splitlines()[:count])+'\ne 0 0 0 0 0 0\n'+second
        elif name.startswith('reset_wait'):canonical=first+'e 0 0 7 0 0 0\n'+second
        elif name.startswith('reset_'):
            phase=int(name.rsplit('phase',1)[1]);canonical='b 0 0 0 0 0 0\n'+first+('2 1b 1 0 0 0 0\n' if phase==6 else '')+f'e 0 0 {phase:x} 0 0 0\n'+second
        elif name.startswith('last_invalid'):canonical=full+'9 1b 0 0 0 0 0\n'
        elif name.startswith('pending_'):canonical=full+('9 1b 0 1 0 0 0\n' if name.startswith('pending_last_fire') else '9 1b 0 2 0 0 0\n')+'c 0 0 0 0 0 0\n'
        elif name.startswith('next_BEGIN'):canonical=full+'9 1c 0 3 0 7 c\n'+'\n'.join(second.splitlines()[1:])+'\n'
        elif name.startswith('commit_last_Y'):canonical='b 0 0 0 0 0 0\n'+complete.rsplit('5 1b 1 0 0 0 0',1)[0]+'8 1b 1 0 0 0 0\nf 0 0 0 0 0 0\n'
        elif name=='continuous_cold_params':canonical=complete+second
        else:canonical='b 0 0 0 0 0 0\n'+first+'d 0 0 0 0 0 0\n7 1b 0 0 0 0 0\nc 0 0 0 0 0 0\n'
        need(stream==canonical,'directed public stream identity differs '+name)
        if name.startswith('premature_'):need(stream.index('2 1b 1 0 0 0 0')<stream.find('6 1b') or '6 1b' not in stream,'premature OPEN identity')
        elif name.startswith('wrong_'):need('2 1b 2 0 0 0 0' in stream,'wrong tile identity')
        elif name.startswith('reset_'):
            phase=7 if name.startswith('reset_wait') else int(name.rsplit('phase',1)[1]) if 'phase' in name else 0
            need(f'e 0 0 {phase:x} 0 0 0' in stream and f'RESET {phase} ' in stats,'reset phase not exercised')
        elif name.startswith(('last_invalid','pending_','next_BEGIN')):
            mode=0 if name.startswith('last_invalid') else 1 if name.startswith('pending_last_fire') else 2 if name.startswith('pending_last_blocked') else 3
            boundary=[list(map(int,s.split()[1:])) for s in stats.splitlines() if s.startswith('BOUNDARY ')]
            need(boundary and all(len(v)==10 and v[0]==mode for v in boundary) and any(int(s.split()[3],16)==mode for s in stream.splitlines() if s.startswith('9 ')),'boundary case identity')
            first_boundary=boundary[0]
            if mode in (0,3):need(first_boundary[2:6]==[0,0,1,1],'forbidden final-boundary input acceptance')
            else:
                need(first_boundary[2:6]==[1,1,1,0],'pending event not accepted before final output')
                need(any(v[1]==1 and v[8]==1 for v in boundary),'missing accepted-event fault retirement')
                if mode==2:need(any(v[1]==1 and v[4:7]==[1,1,0] for v in boundary),'missing blocked-last fault trace')
            if mode==3:need(any(v[1]==2 and v[2:5]==[1,1,0] and v[7:9]==[0,0] for v in boundary),'next BEGIN before done cleared/missing handoff')
        elif name=='continuous_cold_params':need(stream.count('\n0 ')==1,'continuous task identity')
        elif name=='fault_preserves_tile_block':need('d 0 0 0 0 0 0' in stream and '7 1b ' in stream and 'c 0 0 0 0 0 0' in stream,'fault held block identity')
        elif name.startswith('commit_last_Y'):
            events=[list(map(int,s.split()[1:])) for s in stats.splitlines() if s.startswith('COMMIT_LAST_Y ')]
            need(events==[[27,1,0,143]] and r['w2_counters'][0][6]==1,'COMMIT retirement/old final Y same-cycle event missing')
    for name in MUTANTS:
        e=entries[name];need(e['status']=='PASS' and e['mutation_detected'] is True,'mutant not detected');r,c,out,x,w,b=artifacts(ROOT/e['manifest'],name)
        need(c['PM']==pm and c['READ_LATENCY']==1 and c['shift']==0,'mixed mutant profile')
        if name=='MUT_W_NO_DEFER':need(c['M']==13 and c['N']==48 and (out/'commands.hex').read_text()==large_stream,'full-slot defer mutant identity')
        else:need(c['M']==5 and c['N']==32,'ordinary mutant geometry')
        log=(out/'sim.log').read_text();code=r['commands'][1]['exit_code']
        if code==0:
            need(r.get('error','').startswith(('output ','raw48')),'no numeric mutant detection')
            wanted=[f'{t:08x} {i:08x} {y&0xffffffff:08x} {ov} {sat} {last}' for t,i,y,ov,sat,last in oracle(x,w,b,c['shift'],pm,c['task'])]
            need((out/'output.hex').read_text().splitlines()!=wanted,'claimed numeric mutant did not differ')
        else:
            signals={'MUT_TAG_G':('PIPE_',),'MUT_EARLY_DONE':('early done','DONE_WITH_PENDING_INPUT'),'MUT_NO_OUTPUT_CREDIT':('unstable blocked output',),'MUT_W_NO_DEFER':('unexpected fault',),'MUT_W_OWNER_EARLY':('TILE_OWNER_RELEASED_EARLY',),'MUT_W_SLOT_ALIAS':('W2_SINGLE_PORT_COLLISION',),'MUT_W_SWITCH_EARLY':('W2_','PIPE_')}
            need(name in signals and any(s in log for s in signals[name]),'wrong mutant failure reason')
    return {'status':'PASS','directed_tests':34,'actual_RTL_mutation_classes':10,'tests':44}

def check_numeric(path):
    j=read_json(path);need(j['status']=='PASS','numeric suite failed');hashes(ROOT,j['source_sha256']);entries={t['name']:t for t in j['tests']}
    need(len(j['tests'])==48 and set(entries)=={f'shift{s:02d}' for s in range(48)},'missing/aliased all-shift tests')
    for shift in range(48):
        e=entries[f'shift{shift:02d}'];need(e['status']=='PASS','numeric case failed');r=read_json(ROOT/e['manifest']);folder=(ROOT/e['manifest']).parent;need(r['config']['shift']==shift,'wrong shift identity')
        x=np.zeros((3,64),dtype=np.int16);x[:,63]=[-32768,-3,32767];w=np.zeros((64,32),dtype=np.int16);w[63]=np.array([-32768,32767,0,1,-1,0,0,0]*4,dtype=np.int16)
        half=1<<(shift-1) if shift else 0;values=[0,1,-1,(1<<47)-1,-(1<<47),(1<<31)-1,-(1<<31)]
        values += [sign*((q<<shift)+half+d) for q in range(4) for sign in (-1,1) for d in (-1,0,1)];values=[v for v in values if -(1<<47)<=v<(1<<47)];b=np.array((values*32)[:32],dtype=np.int64)
        need(np.array_equal(np.load(folder/'X.npy'),x) and np.array_equal(np.load(folder/'W.npy'),w) and np.array_equal(np.load(folder/'b.npy'),b),'all-shift signed/bias boundary input identity')
        check_case(ROOT/e['manifest'],pm=4,latency=1+shift%2)
    return {'status':'PASS','all_shifts':48,'public_outputs':48*96}

def main():
    p=argparse.ArgumentParser();p.add_argument('kind',choices=['case','suite','full36','repeat','production','protocol','numeric']);p.add_argument('path');p.add_argument('--pm',type=int,choices=[2,4],default=4);p.add_argument('--latency',type=int,choices=[1,2],default=1);p.add_argument('--out');a=p.parse_args()
    try:
        if a.kind in ('full36','repeat','production'):need(read_json(ROOT/a.path)['profile']==a.kind,'required suite role changed')
        result=check_case(ROOT/a.path,pm=a.pm,latency=a.latency) if a.kind=='case' else check_suite(ROOT/a.path,a.pm,a.latency) if a.kind in ('suite','full36','repeat','production') else check_protocol(ROOT/a.path,a.pm) if a.kind=='protocol' else check_numeric(ROOT/a.path)
        result['checked_utc']=utc();code=0
    except (ValueError,KeyError,IndexError,OSError) as exc:result={'status':'FAIL','error':str(exc),'checked_utc':utc()};code=1
    if a.out:put(ROOT/a.out,result)
    print(json.dumps(result),flush=True);return code

if __name__=='__main__':raise SystemExit(main())
