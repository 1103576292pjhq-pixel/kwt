"""Actual standalone RTL execution, source-bound evidence, no computed RTL outputs."""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import shutil
import sys
import time
import uuid

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
sys.path.insert(0,str(ROOT/'dv/fp32'))
from hardfloat_sources import prepare,SOURCE
RTL=['rtl/encoder_sync_ram.sv','rtl/encoder_fp32.sv','rtl/encoder_nonlinear.sv','rtl/encoder_core.sv']
ACTIVE_OUT=None

def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def write(p,obj):
    p.parent.mkdir(parents=True,exist_ok=True)
    p.write_text(json.dumps(obj,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
def hashes(paths):return {str(p.relative_to(ROOT)):sha(p) for p in paths}

def archive(out):
    files=[p for p in out.iterdir() if p.is_file() and p.suffix in ('.log','.json','.hex','.txt')]
    if not files:return
    dest=out/'attempts'/str(time.time_ns());dest.mkdir(parents=True,exist_ok=False)
    for path in files:shutil.copy2(path,dest/path.name)

def fp32_release():
    path=ROOT/'work/fp32_handoff.json'
    hand=json.loads(path.read_text(encoding='utf-8'))
    if hand['status']!='PASS':raise ValueError('FP32 dependency is not released: '+hand['status'])
    for rel,digest in hand['source_sha256'].items():
        if sha(ROOT/rel)!=digest:raise ValueError('stale FP32 dependency: '+rel)
    return sha(path)

def verify_source_freeze():
    path=ROOT/'work/encoder_source_freeze.json'
    data=json.loads(path.read_text(encoding='utf-8'))
    if data['status']!='FROZEN_FOR_LONG_VALIDATION' or data['fp32_handoff_sha256']!=fp32_release():raise ValueError('long validation source freeze not released')
    for rel,digest in data['source_sha256'].items():
        if sha(ROOT/rel)!=digest:raise ValueError('production changed after source freeze: '+rel)
    return sha(path)

def reference_release(bundle='reference'):
    path=ROOT/('work/encoder_reference_core_ready.json' if bundle=='reference' else 'work/encoder_reference_handoff.json')
    if not path.exists():path=ROOT/'work/encoder_reference_handoff.json'
    if not path.exists():raise ValueError('Reference dependency not released')
    hand=json.loads(path.read_text(encoding='utf-8-sig'))
    if hand['status']!='PASS':raise ValueError('Reference dependency not PASS')
    for key in ('source_hashes','source_sha256','input_sha256','source_fingerprints','frozen_files_sha256','artifacts_sha256'):
        for rel,digest in hand.get(key,{}).items():
            if sha(ROOT/rel)!=digest:raise ValueError('stale reference handoff '+rel)
    from numeric.encoder.verify_bundle import verify
    ref=ROOT/'reports/encoder'/bundle
    verified=verify(ref)
    manifest=json.loads((ref/'manifest.json').read_text(encoding='utf-8'))
    for key in (('reference_manifest_sha256','manifest_sha256') if bundle=='reference' else ('test12_reference_manifest_sha256',)):
        if key in hand and isinstance(hand[key],str) and hand[key]!=sha(ref/'manifest.json'):
            raise ValueError('reference manifest differs from handoff')
    verified['release_file']=str(path.relative_to(ROOT));verified['release_sha256']=sha(path)
    return ref,manifest,verified

def run(cmd,cwd,log,timeout=1800):
    with (cwd/'commands.jsonl').open('a',encoding='utf-8') as f:
        f.write(json.dumps({'command':list(map(str,cmd)),'cwd':str(cwd),'time':time.time()})+'\n')
    with log.open('w',encoding='utf-8') as f:
        process=subprocess.Popen(list(map(str,cmd)),cwd=cwd,stdout=f,stderr=subprocess.STDOUT,text=True,encoding='utf-8')
        write(cwd/'progress.json',{'status':'RUNNING','pid':process.pid,'command':list(map(str,cmd)),
                                 'started_unix':time.time(),'run_id':f'{os.getpid()}-{time.time_ns()}',
                                 'log':str(log),'target_cases':1})
        try:code=process.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            process.kill();process.wait();raise
    if code:raise RuntimeError(f'{log}: child exit {code}; {log.read_text(encoding="utf-8")[-1500:]}')
    return log.read_text(encoding='utf-8')

def main():
    global ACTIVE_OUT
    invocation_started=time.time();invocation_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
    p=argparse.ArgumentParser()
    p.add_argument('--mode',choices=['protocol','small','layer','full'],default='small')
    p.add_argument('--sim',choices=['verilator','icarus'],default='verilator')
    p.add_argument('--output',default='reports/encoder/rtl/small')
    p.add_argument('--case')
    p.add_argument('--reference',choices=['reference','reference-test12'],default='reference')
    p.add_argument('--trace',action='store_true')
    p.add_argument('--attention',action='store_true')
    p.add_argument('--reuse-build',action='store_true')
    a=p.parse_args();out=(ROOT/a.output).resolve()
    if (ROOT/'reports/encoder').resolve() not in out.parents:raise ValueError('output outside encoder reports')
    out.mkdir(parents=True,exist_ok=True)
    ACTIVE_OUT=out
    archive(out)
    write(out/'status.json',{'status':'RUNNING','mode':a.mode,'simulator':a.sim})
    fp_handoff=fp32_release()
    freeze=verify_source_freeze() if a.mode=='full' else None
    src=[ROOT/x for x in RTL]+[ROOT/'dv/encoder/tb_encoder.sv',Path(__file__),ROOT/'dv/fp32/hardfloat_sources.py']
    src+=[p for p in SOURCE.rglob('*') if p.is_file()]
    bound=hashes(src)
    hard=prepare(out/'hardfloat');inputs={'work/fp32_handoff.json':fp_handoff}
    if freeze:inputs['work/encoder_source_freeze.json']=freeze
    params=(99,64,256) if a.mode in ('full','layer') else (3,4,8)
    cmdargs=[]
    if a.mode!='protocol':
        ref,manifest,verified=reference_release(a.reference)
        handoff=ROOT/verified['release_file']
        write(out/'reference-readback.json',verified)
        inputs[str(handoff.relative_to(ROOT))]=sha(handoff)
        inputs[str((ref/'manifest.json').relative_to(ROOT))]=sha(ref/'manifest.json')
        for rel,digest in manifest['source_hashes'].items():
            if sha(ROOT/rel)!=digest:raise ValueError('stale reference: '+rel)
        if a.mode=='small':
            case=ref/'fixtures'/ (a.case or 'small_3_4_8');weights=case;layers=1
            cmdargs=['+CASE=case','+WEIGHTS=case','+LAYERS=1']
            paths=list(case.glob('*.hex'))
        else:
            sid=a.case or manifest['samples'][0]['sample_id'];sample=ref/'cases'/sid;weights=ref/'weights';layers=12
            if a.mode=='layer':
                case=sample/'layer_00';layers=1
                # ASCII aliases preserve the released layer_00 weights and source.
                staging=out/'single-layer';staging.mkdir(exist_ok=True)
                (staging/'weights.hex').write_bytes((weights/'layer_00.hex').read_bytes())
                weights=staging
                cmdargs=['+CASE=case','+WEIGHTS=weights','+LAYERS=1']
                paths=list(case.glob('*.hex'))+[ref/'weights/layer_00.hex']
            else:
                case=sample;cmdargs=['+CASE=case','+WEIGHTS=weights','+LAYERS=12']
                paths=[case/'input.hex']+[case/f'layer_{l:02d}/y.hex' for l in range(12)]+list(weights.glob('*.hex'))
                if a.trace:paths+=list(case.glob('layer_*/*.hex'))
        for path in paths:inputs[str(path.relative_to(ROOT))]=sha(path)
        for link,target in [('case',case),('weights',weights)]:
            dest=out/link
            if dest.is_symlink():
                if dest.resolve()!=target.resolve():dest.unlink()
                else:continue
            dest.symlink_to(target,target_is_directory=True)
        cmdargs+=['+OUTPUT=output.hex']
        if a.trace:cmdargs+=['+TRACE']
        if a.attention:
            if a.mode not in ('small','layer'):raise ValueError('attention mode requires standalone small or layer')
            cmdargs+=['+ATTENTION']
    source=hard+[ROOT/x for x in RTL]+[ROOT/'dv/encoder/tb_encoder.sv']
    compiled_snapshot=hashes(source)
    if freeze:
        frozen=json.loads((ROOT/'work/encoder_source_freeze.json').read_text(encoding='utf-8'))
        if sha(out/'hardfloat/divSqrtRecFN_small.v')!=frozen['source_sha256']['reports/encoder/verification/frozen-hardfloat/divSqrtRecFN_small.v']:raise ValueError('generated HardFloat differs from frozen compatibility source')
    inc=['-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV')]
    define=[f'-G{x}={v}' for x,v in zip(('M','D','H'),params)]
    build_key={'source_sha256':bound,'params':params,'sim':a.sim,'fp_handoff':sha(ROOT/'work/fp32_handoff.json')}
    if a.sim=='verilator':
        binary=out/'obj/Vtb_encoder'
        command=['verilator','--binary','--timing','-Wno-fatal','--top-module','tb_encoder','--Mdir',str(out/'obj'),'-j','4',*define,*inc,*source]
    else:
        binary=out/'test.vvp'
        command=['iverilog','-g2012','-s','tb_encoder','-o',binary,
                 *[f'-Ptb_encoder.{x}={v}' for x,v in zip(('M','D','H'),params)],*inc,*source]
    keyfile=out/'build.json'
    build_key['command']=list(map(str,command))
    if not(a.reuse_build and binary.exists() and keyfile.exists() and json.loads(keyfile.read_text(encoding='utf-8'))==json.loads(json.dumps(build_key))):
        print('Compile',a.sim,params,flush=True)
        run(command,out,out/'compile.log',600);write(keyfile,build_key)
    cmd=([str(binary)] if a.sim=='verilator' else ['vvp',str(binary)])+cmdargs
    if fp32_release()!=fp_handoff:raise ValueError('FP32 release changed during build')
    if hashes(source)!=compiled_snapshot:raise ValueError('compiled source changed during build')
    if freeze and verify_source_freeze()!=freeze:raise ValueError('source freeze changed before simulation')
    print('Execute',a.mode,a.case or '',flush=True)
    executed_binary=sha(binary)
    start=time.time();log=run(cmd,out,out/'simulation.log',14400)
    if a.mode=='protocol':
        if 'ENCODER_PROTOCOL_PASS checks=5' not in log:raise ValueError('incomplete protocol test')
        result={'protocol_checks':5}
    else:
        marker=f'ENCODER_PASS layers={layers} words={layers*params[0]*params[1]}'
        if marker not in log:raise ValueError('incomplete RTL run')
        lines=(out/'output.hex').read_text(encoding='utf-8').splitlines()
        if len(lines)!=layers*params[0]*params[1]:raise ValueError('partial output')
        expected=[]
        for l in range(layers):expected+=(case/(('attn.hex' if a.attention else 'y.hex') if layers==1 else f'layer_{l:02d}/y.hex')).read_text(encoding='utf-8').splitlines()
        if lines!=expected:raise ValueError('independent output file check differs')
        result={'layers':layers,'output_words':len(lines),'output_sha256':sha(out/'output.hex'),'bit_mismatches':0}
        if a.trace:
            names=('q','k','v','scores','prob','context','attn','r1','n1','ffn1','gelu','ffn2','r2','y')
            seen=set();arrays={}
            for line in (out/'trace.txt').read_text(encoding='utf-8').splitlines():
                layer,stage,addr,bits=line.split();key=(int(layer),int(stage));idx=int(addr)
                if key not in arrays:
                    stagepath=case/(names[key[1]]+'.hex') if layers==1 else case/f'layer_{key[0]:02d}'/(names[key[1]]+'.hex')
                    arrays[key]=stagepath.read_text(encoding='utf-8').splitlines()
                token=(*key,idx)
                if token in seen or idx>=len(arrays[key]) or bits!=arrays[key][idx]:
                    raise ValueError('trace mismatch or duplicate: '+line)
                seen.add(token)
            target=sum(len(v) for v in arrays.values())
            if len(arrays)!=(7 if a.attention else 14)*layers or len(seen)!=target:raise ValueError('partial trace')
            result.update(trace_words=len(seen),trace_sha256=sha(out/'trace.txt'))
    if bound!=hashes(src):raise ValueError('sources changed while simulation ran')
    if hashes(source)!=compiled_snapshot:raise ValueError('compiled source changed during simulation')
    if sha(binary)!=executed_binary:raise ValueError('executed binary changed')
    for rel,digest in inputs.items():
        if sha(ROOT/rel)!=digest:raise ValueError('inputs changed during run: '+rel)
    result.update(status='PASS',mode=a.mode,simulator=a.sim,source_sha256=bound,input_sha256=inputs,
                  wall_seconds=time.time()-start,log_sha256=sha(out/'simulation.log'),
                  command=cmd,pid=os.getpid(),completed_unix=time.time(),exit_code=0,
                  started_unix=invocation_started,run_id=invocation_id,
                  case=a.case or (locals().get('case',Path('protocol')).name),reference=a.reference,
                  attention=a.attention,geometry=list(params))
    result['binary_sha256']=sha(binary)
    result['compiled_source_sha256']=compiled_snapshot
    result['compile_log_sha256']=sha(out/'compile.log');result['build_key_sha256']=sha(keyfile)
    write(out/'status.json',result);write(out/'progress.json',{'status':'PASS','completed_unix':time.time()})
    print(json.dumps({k:v for k,v in result.items() if k not in ('source_sha256','input_sha256')},indent=2),flush=True)

if __name__=='__main__':
    try:main()
    except Exception as exc:
        if ACTIVE_OUT is not None:write(ACTIVE_OUT/'status.json',{'status':'FAIL','error':str(exc)})
        print(str(exc),file=sys.stderr);sys.exit(1)
