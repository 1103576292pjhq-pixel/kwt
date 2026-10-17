"""Fail-closed local evidence gate. It does not grant contest/PPA acceptance."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import re
import shutil
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import read_json,sha,put,utc
import numpy as np
from numeric.fixedpoint import ffn1_reference

def require(condition,message):
    if not condition: raise ValueError(message)

def verify_hashes(base,items):
    require(isinstance(items,dict) and bool(items),'empty SHA inventory')
    for name,digest in items.items():
        p=base/name
        require(p.is_file() and sha(p)==digest,f'SHA mismatch/missing {p}')

def oracle_records(x,w,b,shift,pm,task):
    ref=ffn1_reference(x,w,b,shift);m,n=x.shape[0],w.shape[1]
    return [[task,i*n+j,int(ref.output[i,j]),int(ref.overflow[i,j]),int(ref.output_saturated[i,j]),int(i==m-1 and j==n-1)]
            for t in range(0,n,16) for r0 in range(0,m,pm) for i in range(r0,min(r0+pm,m)) for j in range(t,t+16)]

def check_case(path,current=True,expect_pm=None):
    path=Path(path);out=path.parent;r=read_json(path);c=r['config']
    require(r['status']=='PASS','case is not PASS')
    require(c['PM'] in (2,4) and c['PN']==4 and c['READ_LATENCY'] in (1,2),'unsupported geometry')
    require(c['mutation'] is None,'mutant cannot be selected')
    require(c['schedule'] in ('accepted_micro','tagged_CTX4_pipeline'),'unknown schedule')
    if expect_pm is not None: require(c['PM']==expect_pm,'mixed profile PM')
    require(sha(out/'config.json')==r['config_sha256'] and read_json(out/'config.json')==c,'mixed configuration')
    require(set(r['input_sha256'])=={'commands.hex','X.npy','W.npy','b.npy','expected.json'},'incomplete/aliased input inventory')
    require(set(r['output_sha256'])=={'output.hex','stats.txt','compile.log','sim.log'},'incomplete/aliased output inventory')
    verify_hashes(out,r['input_sha256']);verify_hashes(out,r['output_sha256'])
    require(len(r['commands'])==2,'missing compile/sim subprocess')
    for cmd in r['commands']:
        require(cmd['exit_code']==0,'nonzero real subprocess exit')
        require(cmd['pid']>0 and cmd['seconds']>=0 and 0<cmd['timeout_seconds']<900,'missing process bounds')
        log=ROOT/cmd['log']
        require(log.is_file() and sha(log)==cmd['log_sha256'],'command log changed')
        require(read_json(log.with_suffix(log.suffix+'.command.json'))==cmd,'subprocess receipt mismatch')
    compile_argv=r['commands'][0]['argv'];sim_argv=r['commands'][1]['argv']
    for k in ('M','N','PM','READ_LATENCY'):
        flag=f'-Pcore_tb.{k}={c[k]}' if c['simulator']=='icarus' else f'-G{k}={c[k]}'
        require(flag in compile_argv,'compile parameter differs from config '+k)
    require(('-DBASELINE' in compile_argv)==(c['schedule']=='accepted_micro'),'mixed baseline configuration')
    binary=out/('sim.vvp' if c['simulator']=='icarus' else 'obj/Vcore_tb')
    require(binary.is_file() and sha(binary)==r['binary_sha256'],'compiled binary changed/missing')
    if c['simulator']=='icarus':require('-o' in compile_argv and compile_argv[compile_argv.index('-o')+1]==str(binary),'compile output binary binding')
    else:require('--Mdir' in compile_argv and compile_argv[compile_argv.index('--Mdir')+1]==str(out/'obj'),'Verilator object directory binding')
    wanted_sim=([str(binary)] if c['simulator']=='verilator' else ['vvp',str(binary)])+[f'+CMD={out/"commands.hex"}',f'+OUT={out/"output.hex"}',f'+STATS={out/"stats.txt"}']
    require(sim_argv==wanted_sim,'simulation did not execute bound binary/input/output/stats')
    require('RTL_COMPLETE' in (out/'sim.log').read_text(),'missing real simulator terminal marker')
    core='rtl/revd/core_stream_frontend.sv' if c['schedule']=='accepted_micro' else 'rtl/revd_opt/core_stream_frontend_opt.sv'
    required_sources={'rtl/revd/banked_sp16.sv','rtl/revd/quant_epilogue.sv',core,
                      'dv/revd_opt/core_tb.sv','dv/revd_opt/core_runner.py','scripts/revd_offline_common.py','numeric/fixedpoint.py'}
    require(set(r['source_sha256'])==required_sources,'incomplete/aliased source inventory')
    for name,digest in r['source_sha256'].items():
        require(sha(out/'source_snapshot'/name)==digest,'source snapshot mismatch '+name)
        if current: require(sha(ROOT/name)==digest,'stale current source '+name)
        if name.endswith('.sv'): require(str(ROOT/name) in compile_argv,'unbound/shadow compile source '+name)
    x=np.load(out/'X.npy',allow_pickle=False);w=np.load(out/'W.npy',allow_pickle=False);b=np.load(out/'b.npy',allow_pickle=False)
    require(x.shape==(c['M'],64) and w.shape==(64,c['N']) and b.shape==(c['N'],),'input geometry mismatch')
    require(x.dtype==np.int16 and w.dtype==np.int16 and b.dtype==np.int64,'input dtype mismatch')
    require(np.all(b>=-(1<<47)) and np.all(b<(1<<47)),'bias domain')
    # Ordinary runs are independently recomputed. Directed protocol overrides are
    # checked separately by the aggregate required-test inventory and bound bytes.
    ordinary=(out/'commands.hex').read_text().splitlines()
    control=any(int(s.split()[0],16)>=9 and int(s.split()[0],16)!=15 for s in ordinary)
    require(r['expected_tasks']>=0,'missing expected task count')
    expected=read_json(out/'expected.json')
    if not control and r['expected_tasks']==1:
        ref=ffn1_reference(x,w,b,c['shift']);m,n,pm=c['M'],c['N'],c['PM']
        recomputed=oracle_records(x,w,b,c['shift'],pm,c['task'])
        require(expected==recomputed,'expected artifact is not the fixed numeric oracle')
        # Reconstruct all public production events, independent of driver addresses.
        active=False;xc=0;wc=0;bc=0;tile=-1
        for line in ordinary:
            op,task,t,idx,data,shift,layer=[int(v,16) for v in line.split()]
            signed=data-(1<<48) if data&(1<<47) else data
            if op==0:
                require(not active and task==c['task'] and shift==c['shift'] and layer==c['layer'],'BEGIN identity')
                active=True
            elif op==1:
                require(task==c['task'] and idx==xc and signed==int(x.flat[xc]),'public X stream mismatch');xc+=1
            elif op==2:
                tile+=1;wc=0;bc=0;require(t==tile,'public tile mismatch')
            elif op==3:
                require(t==tile and idx==wc and signed==int(w[wc//16,tile*16+wc%16]),'public W stream mismatch');wc+=1
            elif op==4:
                require(t==tile and idx==bc and signed==int(b[tile*16+bc]),'public bias stream mismatch');bc+=1
            elif op==5: require(wc==1024 and bc==16,'public COMMIT incomplete')
            elif op==6: require(xc==m*64 and tile==n//16-1,'public START incomplete')
            elif op!=15: raise ValueError('unknown ordinary event')
    seen=set();lines=(out/'output.hex').read_text().splitlines()
    require(len(lines)==len(expected),'missing/extra output including terminal record')
    for pos,(line,want) in enumerate(zip(lines,expected)):
        require(bool(re.fullmatch(r'[0-9a-fA-F]{8} [0-9a-fA-F]{8} [0-9a-fA-F]{8} [01] [01] [01]',line)),'X/Z/malformed output')
        f=line.split();got=[int(v,16) for v in f[:3]]+list(map(int,f[3:]))
        if got[2]>=1<<31:got[2]-=1<<32
        require(tuple(got[:2]) not in seen,'duplicate output identity');seen.add(tuple(got[:2]))
        require(got==want,f'output/flags/index/last mismatch {pos}')
    require(r['comparison']['outputs']==len(lines) and r['comparison']['unique']==len(seen),'author comparison count mismatch')
    stats=(out/'stats.txt').read_text().splitlines()
    task_lines=[list(map(int,s.split()[1:])) for s in stats if s.startswith('TASK ')]
    require(len(task_lines)==r['expected_tasks'],'terminal task count mismatch')
    for t in task_lines:
        require(len(t)==13 and t[-1]==t[-2],'completion with unretired input')
        require(t[5]==t[2]+t[3] and t[6]==t[1]+t[5],'cycle window partition mismatch')
        require(t[7]==t[8] and t[9]==c['M']*64*c['N'],'MAC retirement mismatch')
    windows=[list(map(int,s.split()[1:])) for s in stats if s.startswith('WINDOW ')]
    require(len(windows)==len(task_lines),'missing directly timestamped cold window')
    for t,v in zip(task_lines,windows):
        require(len(v)==6 and v[0]==t[0] and v[4]==v[3]-v[1] and v[5]==v[3]-v[2] and v[5]==t[5] and v[4]==t[6]+1,'cold window boundary mismatch')
    if not control and r['expected_tasks']==1:
        raw=[s.split() for s in stats if s.startswith('RAW ')];dot=x.astype(np.int64)@w.astype(np.int64)
        require(len(raw)==c['M']*c['N'],'missing raw48 trace')
        raw_seen=set()
        for s in raw:
            task,index=int(s[1]),int(s[2]);i,j=divmod(index,c['N'])
            require(task==c['task'] and 0<=i<c['M'] and 0<=j<c['N'] and index not in raw_seen,'raw48 identity')
            raw_seen.add(index);vals=[int(v,16) for v in s[3:]];vals=[v-(1<<48) if v&(1<<47) else v for v in vals]
            require(vals==[int(dot[i,j]),int(ref.raw[i,j])],'raw48 value mismatch')
    require(bool(r['tools'].get('iverilog')) and bool(r['tools'].get('numpy')),'missing tools')
    return {'status':'PASS','outputs':len(lines),'manifest':str(path.relative_to(ROOT)),'sha256':sha(path),'config':c}

def check_protocol(path):
    path=Path(path);j=read_json(path);require(j['status']=='PASS','protocol suite failed')
    entries={t['name']:t for t in j['tests']}
    required=[f'{n}_l{l}' for l in (1,2) for n in ('last_fire_invalid','pending_last_fire','pending_last_blocked','next_begin_boundary')]
    required += [f'reset_l{l}_phase{p}' for l in (1,2) for p in (1,2,3,4,5)]
    required += ['continuous','early_commit','duplicate_x','bad_dtype_value','bad_layer','wrong_tile','fault_preserves_block','fault_on_fire']
    mutants=['MUT_DROP_K63','MUT_UNSIGNED','MUT_TAG_G','MUT_WRONG_INDEX','MUT_EARLY_DONE','MUT_NO_OUTPUT_CREDIT']
    require(len(entries)==len(j['tests']) and set(entries)==set(required+mutants),'missing/duplicate/unexpected protocol tests')
    require(len({t['manifest'] for t in entries.values()})==len(entries),'aliased protocol manifests')
    require(all(n in entries and entries[n]['status']=='PASS' for n in required+mutants),'missing boundary/reset/mutant evidence')
    verify_hashes(ROOT,j['source_sha256'])
    for n in required:
        manifest=ROOT/entries[n]['manifest'];check_case(manifest)
        r=read_json(manifest);c=r['config'];out=manifest.parent
        stream=(out/'commands.hex').read_text();stats=(out/'stats.txt').read_text().splitlines()
        require(c['M']==5 and c['N']==32 and c['PM']==4 and c['schedule']=='tagged_CTX4_pipeline','mixed protocol geometry')
        x=np.load(out/'X.npy',allow_pickle=False);w=np.load(out/'W.npy',allow_pickle=False);b=np.load(out/'b.npy',allow_pickle=False)
        pinned_x=np.zeros((5,64),dtype=np.int16);pinned_x[:,63]=[-32768,-3,1,4,32767]
        pinned_w=np.zeros((64,32),dtype=np.int16);pinned_w[63]=np.arange(-16,16,dtype=np.int16)
        require(np.array_equal(x,pinned_x) and np.array_equal(w,pinned_w) and np.array_equal(b,np.arange(-16,16,dtype=np.int64)),'protocol input test identity changed')
        expected=oracle_records(x,w,b,0,4,27)
        if n.startswith('reset_'): expected=oracle_records(-x,w,-b,0,4,28)
        elif n=='continuous' or n.startswith('next_begin_'):expected+=oracle_records(-x,(7-w).astype(np.int16),123-b,7,4,28)
        elif n in ('early_commit','duplicate_x','bad_dtype_value','bad_layer','wrong_tile'):expected=[]
        elif n in ('fault_preserves_block','fault_on_fire'):expected=expected[:64]
        require(read_json(out/'expected.json')==expected,'directed oracle/identity mismatch '+n)
        latency_match=re.search(r'_l([12])(?:$|_)',n)
        if latency_match:
            require(c['READ_LATENCY']==int(latency_match[1]),'protocol latency alias')
        if n.startswith(('last_fire','pending_last','next_begin')):
            mode={'last_fire_invalid':0,'pending_last_fire':1,'pending_last_blocked':2,'next_begin_boundary':3}[n.rsplit('_l',1)[0]]
            ctl=[s.split() for s in stream.splitlines() if s.startswith('9 ')]
            require(len(ctl)==1 and int(ctl[0][3],16)==mode,'boundary command identity mismatch')
            boundary=[list(map(int,s.split()[1:])) for s in stats if s.startswith('BOUNDARY ')]
            require(boundary and all(v[0]==mode and len(v)==10 for v in boundary),'missing/mixed boundary trace')
            first=boundary[0]
            if mode in (0,3): require(first[2:6]==[0,0,1,1],'last boundary accepted forbidden input')
            else:
                require(first[2:6]==[1,1,1,0],'pending boundary not accepted before last')
                require(any(v[1]==1 and v[8]==1 for v in boundary),'missing accepted-event fault retirement')
                if mode==2:require(any(v[1]==1 and v[4:7]==[1,1,0] for v in boundary),'missing blocked terminal fault trace')
            if mode==3:require(any(v[1]==2 and v[2]==1 and v[3]==1 and v[4]==0 and v[7:9]==[0,0] for v in boundary),'missing next BEGIN after done trace')
        elif n.startswith('reset_'):
            phase=int(n.rsplit('phase',1)[1])
            resets=[s.split() for s in stats if s.startswith('RESET ')]
            require(len(resets)==1 and int(resets[0][1])==phase,'reset phase trace missing')
            require(any(s.startswith('e 0 0 '+format(phase,'x')+' ') for s in stream.splitlines()),'reset command identity mismatch')
        elif n=='continuous':require(sum(s.startswith('0 ') for s in stream.splitlines())==2 and r['expected_tasks']==2,'continuous task identity')
        elif n in ('early_commit','duplicate_x','bad_dtype_value','bad_layer','wrong_tile','fault_preserves_block','fault_on_fire'):
            require('c 0 0 0 0 0 0' in stream and r['expected_tasks']==0,'fault test not exercised')
            if n=='early_commit':require(stream.startswith('0 1b 0 0 0 0 1\n5 '),'early commit alias')
            if n=='duplicate_x':require(stream.count('1 1b 0 0 0 0 0\n')==2,'duplicate X alias')
            if n=='bad_dtype_value':require('1 1b 0 0 8000 0 0' in stream,'dtype alias')
            if n=='bad_layer':require(stream.startswith('0 1b 0 0 0 0 d'),'layer alias')
            if n=='wrong_tile':require('2 1b 1 0 0 0 0' in stream,'tile alias')
            if n.startswith('fault_'):require('d 0 0 0 0 0 0' in stream and '7 1b ' in stream,'fault output alias')
            if n=='fault_on_fire':require('a 0 0 0 0 0 0' in stream,'fault fire alias')
    for n in mutants:
        t=entries[n];r=read_json(ROOT/t['manifest'])
        require(t.get('mutation_detected') is True and r['status']=='FAIL','mutant was not rejected')
        require(len(r['commands'])==2 and r['commands'][0]['exit_code']==0,'mutant not compiled')
        require(r['config']['mutation']==n and '-D'+n in r['commands'][0]['argv'],'mutant identity alias')
        for p,d in r['source_sha256'].items():
            require(sha((ROOT/t['manifest']).parent/'source_snapshot'/p)==d and sha(ROOT/p)==d,'mutant stale source')
        for cmd in r['commands']:
            require(read_json((ROOT/cmd['log']).with_suffix('.log.command.json'))==cmd,'mutant subprocess receipt changed')
        log=ROOT/r['commands'][1]['log']
        verify_hashes(ROOT,{str(log.relative_to(ROOT)):r['commands'][1]['log_sha256']})
        require(r['commands'][1]['exit_code']!=124,'timeout is not functional mutant evidence')
        require(r['commands'][1]['exit_code']!=0 or r.get('error','').startswith(('output ','raw48')),'mutant was not functionally detected')
    return {'status':'PASS','functional_mutants':len(mutants),'tests':len(required)}

def check_suite(path,minimum_cases=1,expect_pm=None):
    j=read_json(path);require(j['status']=='PASS','suite failed')
    require(len(j['cases'])>=minimum_cases,'missing required cases')
    results=[check_case(ROOT/t['manifest'],expect_pm=expect_pm) for t in j['cases']]
    require(len({r['manifest'] for r in results})==len(results),'duplicate case manifests')
    if j['profile']=='full36':
        frozen=read_json(ROOT/'reports/prototype/vectors/manifest.json')
        require(len(j['cases'])==36 and sum(r['outputs'] for r in results)==912384,'full36 coverage/output count')
        want={c['case_id'].replace('/','_'):c for c in frozen['cases']}
        require(set(t['case'] for t in j['cases'])==set(want),'full36 sample/layer identity set mismatch')
        for t,res in zip(j['cases'],results):
            case=want[t['case']];r=read_json(ROOT/t['manifest']);out=(ROOT/t['manifest']).parent
            require(r['config']['M']==99 and r['config']['N']==256 and r['config']['layer']==case['layer'] and r['config']['shift']==case['config']['output_shift'],'frozen layer geometry/config')
            for local,key in [('X.npy','Xq'),('W.npy','Wq'),('b.npy','bq')]:
                require(sha(out/local)==case['arrays'][key]['sha256'],'frozen input identity differs '+t['case']+'/'+key)
    return {'status':'PASS','cases':len(results),'outputs':sum(r['outputs'] for r in results),'results':results}

def check_numeric(path):
    path=Path(path);out=path.parent;j=read_json(path)
    require(j['status']=='PASS' and j.get('unit_source_unchanged') is True,'numeric suite not fresh PASS')
    expected={'quant_all_shifts_extrema_ties_reset'}|{f'shift{s:02d}' for s in range(48)}|{f'signed_extreme_s{s}' for s in (0,1,16,47)}
    require(len(j['tests'])==53 and {t['name'] for t in j['tests']}==expected,'numeric coverage/shift identity')
    require(set(j['unit_source_sha256'])=={'rtl/revd/quant_epilogue.sv','dv/revd/d1_quant_tb.sv','dv/revd/d1_runner.py','dv/revd_opt/numeric_checks.py'},'numeric unit source inventory')
    verify_hashes(ROOT,j['unit_source_sha256']);verify_hashes(out,j['artifacts'])
    for p,d in j['unit_source_sha256'].items():require(sha(out/'unit_source_snapshot'/p)==d,'quant source snapshot')
    require(len(j['commands'])==2 and all(c['exit_code']==0 for c in j['commands']),'quant actual subprocess')
    for c in j['commands']:
        require(read_json((ROOT/c['log']).with_suffix('.log.command.json'))==c and sha(ROOT/c['log'])==c['log_sha256'],'quant process receipt/log')
    require(j['commands'][0]['argv']==['iverilog','-g2012','-s','d1_quant_tb','-o',str(out/'quant.vvp'),str(ROOT/'rtl/revd/quant_epilogue.sv'),str(ROOT/'dv/revd/d1_quant_tb.sv')],'quant compile source/output binding')
    require(j['commands'][1]['argv']==['vvp',str(out/'quant.vvp'),f'+VECTORS={out/"quant_vectors.hex"}',f'+OUTPUT={out/"quant_output.txt"}'],'quant binary/vector binding')
    vectors=(out/'quant_vectors.hex').read_text().splitlines();outputs=(out/'quant_output.txt').read_text().splitlines()
    from dv.revd.d1_runner import quant_vectors
    pinned_vectors=quant_vectors()
    require(len(vectors)==len(outputs)==len(pinned_vectors),'quant missing/aliased boundary vectors')
    shifts=set()
    for i,(v,o) in enumerate(zip(vectors,outputs)):
        s,b,shift,raw,y,ov,sat=[int(t,16) for t in v.split()]
        s=s-(1<<48) if s&(1<<47) else s;b=b-(1<<48) if b&(1<<47) else b
        require((s,b,shift)==tuple(pinned_vectors[i]),'quant boundary/tie vector identity')
        shifts.add(shift);add=s+b;clipped=max(-(1<<47),min((1<<47)-1,add))
        q,rem=divmod(abs(clipped),1<<shift)
        if shift and (rem>(1<<(shift-1)) or (rem==(1<<(shift-1)) and q%2)):q+=1
        rounded=-q if clipped<0 else q;answer=max(-(1<<31),min((1<<31)-1,rounded))
        want=[i,clipped&((1<<48)-1),answer&((1<<32)-1),int(clipped!=add),int(answer!=rounded)]
        fields=o.split();require(len(fields)==5 and all(re.fullmatch(r'[0-9a-fA-F]+',f) for f in fields),'quant unknown output')
        got=[int(fields[0])]+[int(f,16) for f in fields[1:]]
        require(got==want,'quant raw/data/flag mismatch')
    require(shifts==set(range(48)),'quant all shift coverage')
    seen_manifests=set()
    for t in j['tests']:
        require(t['passed'] is True,'numeric case failed')
        if t['name']=='quant_all_shifts_extrema_ties_reset':
            require('manifest' not in t and t['vectors']==len(pinned_vectors),'quant unit identity')
            continue
        manifest=(ROOT/t['manifest']).resolve()
        require(manifest==(out/t['name']/'run_manifest.json').resolve() and manifest not in seen_manifests,'numeric manifest identity/alias')
        seen_manifests.add(manifest);check_case(manifest)
        receipt=read_json(manifest);c=receipt['config'];extreme=t['name'].startswith('signed_extreme_s')
        shift=int(t['name'].removeprefix('signed_extreme_s' if extreme else 'shift'))
        require(c['M']==3 and c['N']==16 and c['PM']==4 and c['shift']==shift and c['task']==27 and c['layer']==1
                and c['READ_LATENCY']==(1 if extreme else 1+shift%2) and c['schedule']=='tagged_CTX4_pipeline'
                and receipt['expected_tasks']==1,'numeric public core configuration identity')
        x=np.load(manifest.parent/'X.npy',allow_pickle=False);w=np.load(manifest.parent/'W.npy',allow_pickle=False);b=np.load(manifest.parent/'b.npy',allow_pickle=False)
        if extreme:
            px=np.full((3,64),-32768,dtype=np.int16)
            pw=np.tile(np.array([-32768,32767,0,1]*4,dtype=np.int16),(64,1))
            pb=np.array([(1<<47)-1,-(1<<47),-5,5]*4,dtype=np.int64)
        else:
            px=np.zeros((3,64),dtype=np.int16);pw=np.zeros((64,16),dtype=np.int16)
            half=(1<<(shift-1)) if shift else 0
            values=[0,1,-1,(1<<47)-1,-(1<<47),(1<<31)-1,-(1<<31)]
            values += [sign*((q<<shift)+half+d) for q in (0,1,2,3) for sign in (-1,1) for d in (-1,0,1)]
            values=[v for v in values if -(1<<47)<=v<(1<<47)]
            pb=np.array((values*16)[:16],dtype=np.int64)
        require(np.array_equal(x,px) and np.array_equal(w,pw) and np.array_equal(b,pb),'numeric public core input identity')
    return {'status':'PASS','unit_vectors':len(vectors),'public_core_cases':52,'all_shifts':48}

def check_cpu(path,current=True):
    path=Path(path);out=path.parent;r=read_json(path)
    require(r['status']=='PASS' and r.get('source_unchanged') is True,'CPU run not fresh PASS')
    profile=r['profile'];require(profile['stage'] in ('small','full') and profile['tasks'] in (1,2),'CPU scope identity')
    require(profile['pm'] in (2,4) and profile['latency'] in (1,2),'CPU geometry')
    sources=r['source_sha256']
    from scripts import revd_offline_soc_run as normal_cpu
    expected_sources=set(normal_cpu.IMPLEMENTATION)|{str(p.relative_to(ROOT)) for p in normal_cpu.UP.rglob('*.v')}
    if profile.get('case_offset',0):expected_sources.add('scripts/revd_offline_soc_layers.py')
    require(set(sources)==expected_sources,'CPU exact source inventory including selection wrapper')
    for p in ('soc/revd_opt/revd_opt_icb.sv','soc/e203_common/e203_cpu_shell.sv','soc/e203_common/icb_shared_ram.sv',
              'sw/revd_opt/main.c','sw/revd_opt/revd_opt_driver.c','sw/revd_opt/revd_opt_driver.h','dv/revd_opt/soc_cpu_tb.sv'):
        require(p in sources,'missing real CPU/driver dependency '+p)
    require(any(p.endswith('/e203_cpu.v') for p in sources),'CPU vendor source not bound')
    if current:verify_hashes(ROOT,sources)
    verify_hashes(ROOT,r['input_sha256']);verify_hashes(out,r['artifacts_sha256'])
    for c in r['commands']:
        require(c['pid']>0 and 0<c['timeout_seconds']<900 and c['exit_code'] is not None,'CPU subprocess not bounded/completed')
        log=ROOT/c['log'];require(sha(log)==c['log_sha256'] and read_json(log.with_suffix('.log.command.json'))==c,'CPU command receipt/log changed')
    require(bool(r.get('tool_sha256')),'CPU tool binary hashes missing')
    toolnames=['riscv64-unknown-elf-gcc','riscv64-unknown-elf-objcopy','riscv64-unknown-elf-objdump',
               'riscv64-unknown-elf-readelf','verilator','iverilog','vvp','g++','make']
    require(all(shutil.which(name) for name in toolnames),'CPU required tools unavailable')
    required_tools={str(Path(p).resolve()) for p in [sys.executable,*[shutil.which(name) for name in toolnames]]}
    require(set(r['tool_sha256'])==required_tools,'CPU exact tool binary inventory')
    for p,d in r['tool_sha256'].items():require(sha(Path(p))==d,'CPU tool changed')
    cpu=r['results']['cpu'];cmd=cpu['command'];require(cpu['status']=='PASS' and cmd['exit_code']==0,'CPU simulation real exit')
    require(cmd in r['commands'],'CPU run detached from actual subprocess inventory')
    binary=out/('obj/Vsoc_cpu_tb' if profile['sim']=='verilator' else 'cpu.vvp')
    expected_argv=([str(binary)] if profile['sim']=='verilator' else ['vvp',str(binary)])
    require(cmd['argv'][:len(expected_argv)]==expected_argv and Path(cmd['cwd'])==out/'cpu','CPU executable/cwd binding')
    fw=out/'cpu/revd-driver.hex';require(fw.is_file(),'real firmware missing')
    require(cmd['argv'][len(expected_argv):]==['+FIRMWARE=revd-driver.hex',f'+FIRMWARE_BYTES={len(fw.read_text().splitlines())}'],'CPU firmware binding')
    compile_records=[c for c in r['commands'] if c['argv'][0] in ('iverilog','verilator') and any('soc_cpu_tb.sv' in a for a in c['argv'])]
    require(len(compile_records)==1 and compile_records[0]['exit_code']==0,'missing actual real CPU compilation')
    m,n=(3,16) if profile['stage']=='small' else (99,256)
    parameters={'M':m,'N':n,'TASKS':profile['tasks'],'PM':profile['pm'],'READ_LATENCY':profile['latency']}
    hdl=[ROOT/'dv/e203_boot/timescale.v',*sorted(normal_cpu.UP.rglob('*.v')),
         *[ROOT/p for p in normal_cpu.IMPLEMENTATION[:6]],ROOT/'dv/revd_opt/soc_cpu_tb.sv']
    includes=['-I'+str(normal_cpu.UP/p) for p in ('core','perips','perips/apb_i2c')]
    if profile['sim']=='verilator':
        expected_compile=['verilator','--binary','--timing','--build-jobs','4','-Wno-fatal','-CFLAGS','-O3',
            '-Diverilog','-DDISABLE_SV_ASSERTION=1','--top-module','soc_cpu_tb',
            *[f'-G{k}={v}' for k,v in parameters.items()],'--Mdir',out/'obj',*includes,*hdl]
    else:
        expected_compile=['iverilog','-g2012','-Diverilog','-DDISABLE_SV_ASSERTION=1','-s','soc_cpu_tb',
            *[token for k,v in parameters.items() for token in ('-P',f'soc_cpu_tb.{k}={v}')],
            '-o',out/'cpu.vvp',*includes,*hdl]
    require(compile_records[0]['argv']==list(map(str,expected_compile)),'CPU exact compiled source/parameter/output binding')
    expected_c=['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
        '-mcmodel=medany','-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax',
        '-Os','-g','-Wall','-Wextra','-Werror','-I',ROOT/'sw/revd_opt','-T',ROOT/'sw/e203/link.ld',
        f'-Wl,-Map,{out/"revd-driver.map"}',ROOT/'sw/e203/start.S',ROOT/'sw/revd_opt/main.c',
        ROOT/'sw/revd_opt/revd_opt_driver.c','-o',out/'revd-driver.elf']
    require(any(c['exit_code']==0 and c['argv']==list(map(str,expected_c)) for c in r['commands']),'CPU exact formal C startup/driver/output binding')
    expected_copy=['riscv64-unknown-elf-objcopy','-O','binary',str(out/'revd-driver.elf'),str(out/'revd-driver.bin')]
    require(any(c['exit_code']==0 and c['argv']==expected_copy for c in r['commands']),'CPU firmware objcopy identity')
    fw_bytes=(out/'revd-driver.bin').read_bytes()
    require(fw.read_text()==''.join(f'{v:02x}\n' for v in fw_bytes) and fw.read_bytes()==(out/'revd-driver.hex').read_bytes(),'CPU firmware bytes do not match compiled binary')
    log=(ROOT/cmd['log']).read_text();match=re.search(r'E203_REVD_PASS ([^\n]+)',log)
    require(bool(match),'CPU terminal write-response completion missing')
    metrics={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])};require(metrics==cpu['metrics'],'CPU metrics differ from simulator')
    task_metrics=[{k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',s)} for s in re.findall(r'E203_REVD_TASK ([^\n]+)',log)]
    require(task_metrics==cpu['task_metrics'] and len(task_metrics)==profile['tasks'],'CPU cold task window identity')
    m,n=(3,16) if profile['stage']=='small' else (99,256);count=m*n
    require(all(metrics.get(k)==count*profile['tasks'] for k in ('outputs','flags','response_outputs','response_flags','pops')),'CPU missing final output/flag/write response')
    require(metrics.get('tasks')==profile['tasks'] and metrics.get('starts')==profile['tasks'],'CPU task count')
    for t in task_metrics:
        require(t['cold_start']<t['last_write_response'] and t['cold_cycles']==t['last_write_response']-t['cold_start']+1,'CPU cold window boundary')
        require(t['issue_count']==t['retire_count'] and t['effective_macs']==m*n*64,'CPU effective MAC retirement')
    frozen=read_json(ROOT/'reports/prototype/vectors/manifest.json');wanted={}
    offset=profile.get('case_offset',0)
    require(offset in (0,2,4,6,8,10),'CPU case selection offset')
    if offset:
        binding=r.get('pair_binding',{})
        require(binding==read_json(out/'pair-binding.json'),'CPU pair metadata differs from actual bound artifact')
        require(binding.get('case_indices')==[offset,offset+1] and binding.get('original_manifest_sha256')==sha(ROOT/'reports/prototype/vectors/manifest.json'),'CPU pair selection binding')
        require(binding.get('case_ids')==[case['case_id'] for case in frozen['cases'][offset:offset+2]],'CPU pair case identity binding')
        require(binding.get('normal_sources_modified') is False and profile['stage']=='full' and profile['tasks']==2,'CPU pair scope')
        require(binding.get('wrapper_sha256')==sha(ROOT/'scripts/revd_offline_soc_layers.py'),'CPU pair wrapper source')
        require(binding.get('actual_simulator_executable')==str(binary.relative_to(ROOT)),'CPU pair executable path binding')
        require(binding.get('actual_simulator_executable_sha256')==sha(binary),'CPU pair binary binding')
        require(binding.get('firmware_binary_sha256')==sha(out/'revd-driver.bin'),'CPU pair firmware binary binding')
        require(binding.get('normal_soc_runner_sha256')==sha(ROOT/'scripts/revd_offline_soc_run.py'),'CPU pair normal runner source binding')
    require(len(r['cases'])==profile['tasks'],'CPU frozen task coverage')
    for t,c in enumerate(r['cases']):
        case=frozen['cases'][offset+t];require(c['case_id']==case['case_id'] and c['layer']==case['layer'] and c['shift']==case['config']['output_shift'],'CPU frozen case/layer identity')
        arr={}
        for key in ('Xq','Wq','bq'):
            d=case['arrays'][key];p=ROOT/'reports/prototype/vectors'/d['path'];require(sha(p)==d['sha256'],'CPU frozen array SHA')
            arr[key]=np.load(p,allow_pickle=False)
        ref=ffn1_reference(arr['Xq'][:m],arr['Wq'][:,:n],arr['bq'][:n],c['shift'])
        for i in range(m):
            for j in range(n):
                wanted[(t,i*n+j)]=(int(ref.output[i,j])&0xffffffff,int(ref.overflow[i,j])|(int(ref.output_saturated[i,j])<<1)|(4 if i==m-1 and j==n-1 else 0))
    for name,field in [('cpu-output.txt',0),('cpu-flags.txt',1)]:
        p=out/'cpu'/name;require(sha(p)==cpu['output_sha256'][name],'CPU public memory trace hash')
        lines=p.read_text().splitlines();require(len(lines)==len(wanted),'CPU output/flag trace missing final write')
        seen=set()
        for line in lines:
            fields=line.split();require(len(fields)==3 and bool(re.fullmatch(r'[0-9a-fA-F]+',fields[2])),'CPU unknown public memory value')
            key=(int(fields[0]),int(fields[1]));require(key in wanted and key not in seen,'CPU output index duplicate/invalid');seen.add(key)
            require(int(fields[2],16)==wanted[key][field],'CPU shared-SRAM value/flag mismatch')
    return {'status':'PASS','tasks':profile['tasks'],'outputs':len(wanted),'scope':'public E203 cold load-to-final-shared-write-response; organizer platform untested',
            'cpu_binary_sha256':sha(binary),'cold_task_metrics':task_metrics,'source_manifest_sha256':sha(path)}

def main():
    ap=argparse.ArgumentParser();ap.add_argument('kind',choices=['case','suite','protocol','numeric','cpu']);ap.add_argument('path');ap.add_argument('--out');ap.add_argument('--minimum-cases',type=int,default=1);ap.add_argument('--pm',type=int,choices=[2,4]);a=ap.parse_args()
    try:
        result=check_case(ROOT/a.path,expect_pm=a.pm) if a.kind=='case' else check_protocol(ROOT/a.path) if a.kind=='protocol' else check_numeric(ROOT/a.path) if a.kind=='numeric' else check_cpu(ROOT/a.path) if a.kind=='cpu' else check_suite(ROOT/a.path,a.minimum_cases,a.pm)
        result['checked_utc']=utc();code=0
    except (ValueError,KeyError,IndexError,OSError) as e: result={'status':'FAIL','error':str(e),'checked_utc':utc()};code=1
    if a.out: put(ROOT/a.out,result)
    print(json.dumps(result),flush=True);return code
if __name__=='__main__':raise SystemExit(main())
