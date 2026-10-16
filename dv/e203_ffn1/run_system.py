"""Real official E203 executes the production C MMIO driver, without a BFM."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import subprocess
import sys
import time
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'reports/system/e203-ffn1'
UP=ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203'
sys.path.insert(0,str(ROOT))
from numeric.artifacts import verify_vectors

def digest(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def save(path,value): Path(path).write_text(json.dumps(value,indent=2)+'\n',encoding='utf-8')
def inputs():
    files=['sw/e203/start.S','sw/e203/link.ld','sw/ffn1_driver.c','sw/ffn1_driver.h',
        'soc/e203_common/e203_cpu_shell.sv','soc/e203_common/icb_shared_ram.sv',
        'rtl/ffn1_icb.sv','rtl/ffn1_top.sv','rtl/dot64.sv','rtl/prototype_sync_ram.sv',
        'dv/e203_boot/timescale.v','dv/e203_ffn1/tb_e203_ffn1.sv',
        'dv/e203_ffn1/red_stub.c','dv/e203_ffn1/run_system.py','scripts/run_e203_ffn1.sh',
        'config/e203-source-manifest.json','config/source-manifest.json',
        'reports/prototype/vectors/manifest.json']
    if (ROOT/'sw/e203_ffn1/main.c').exists(): files.append('sw/e203_ffn1/main.c')
    return {p:digest(ROOT/p) for p in files}

def run(name,cmd,cwd=OUT,expected=0,timeout=1200):
    start=time.monotonic()
    with (OUT/'commands.jsonl').open('a') as f:
        f.write(json.dumps(dict(name=name,cwd=str(cwd),command=list(map(str,cmd))))+'\n')
    print(f'[{name}] START',flush=True)
    log=OUT/(name+'.log')
    with log.open('w') as f:
        process=subprocess.Popen(list(map(str,cmd)),cwd=cwd,stdout=f,stderr=subprocess.STDOUT,text=True)
        print(f'[{name}] PID={process.pid} log={log.relative_to(ROOT)}',flush=True)
        seen=0
        while process.poll() is None:
            time.sleep(0.5)
            if time.monotonic()-start>timeout:
                process.kill();process.wait();raise RuntimeError(f'{name} wall timeout')
            text=log.read_text(errors='replace')
            if len(text)>seen:
                for line in text[seen:].splitlines():
                    if any(token in line for token in ['CPU_', 'E203_FFN1_', '%Error', 'error:']): print(line,flush=True)
                seen=len(text)
        rc=process.returncode
    text=log.read_text(errors='replace')
    elapsed=time.monotonic()-start
    with (OUT/'commands.jsonl').open('a') as f:
        f.write(json.dumps(dict(name=name,exit_code=rc,elapsed_seconds=elapsed,log_sha256=digest(log)))+'\n')
    print(f'[{name}] EXIT={rc} seconds={elapsed:.3f}',flush=True)
    if (expected==0 and rc!=0) or (expected!=0 and rc==0):
        print(text[-6000:],flush=True);raise RuntimeError(f'{name} unexpected exit {rc}')
    return text,elapsed,rc

def check_dependencies():
    for name in ['boot','driver']:
        handoff=json.loads((ROOT/f'work/{"e203_boot" if name=="boot" else name}_handoff.json').read_text(encoding='utf-8-sig'))
        if handoff['status']!='PASS': raise RuntimeError(name+' handoff not PASS')
        hashes=handoff.get('input_sha256',handoff.get('hashes',{}))
        for path,sha in hashes.items():
            if digest(ROOT/path)!=sha: raise RuntimeError('dependency hash changed '+path)
    spec=importlib.util.spec_from_file_location('upstream_checks',ROOT/'dv/e203_boot/run_boot.py')
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    return mod.verify_sources()

def fixture(path,m,n):
    path.mkdir(parents=True,exist_ok=True)
    manifest=json.loads((ROOT/'reports/prototype/vectors/manifest.json').read_text())
    case=manifest['cases'][0]
    arrays={k:np.load(ROOT/'reports/prototype/vectors'/v['path'],allow_pickle=False) for k,v in case['arrays'].items()}
    x=arrays['Xq'][:m,:].astype('<i2');w=arrays['Wq_packed'][:n,:].astype('<i2');b=arrays['bq'][:n].astype('<i8')
    y=arrays['Yq'][:m,:n].astype('<i4')
    flags=(4|arrays['overflow'][:m,:n].astype(np.uint8)|(arrays['output_saturated'][:m,:n].astype(np.uint8)<<1))
    image=bytearray(524288)
    def place(offset,payload): image[offset:offset+len(payload)]=payload
    place(0x100,np.array([m,n,case['config']['output_shift'],0],dtype='<u4').tobytes())
    place(0x1000,x.tobytes());place(0x5000,w.tobytes());place(0xd000,b.tobytes())
    # Unwritten outputs are poisoned. All zero bytes would hide missing writes.
    place(0x10000,b'\xa5'*(m*n*4));place(0x30000,b'\xa5'*(m*n))
    words=np.frombuffer(image,dtype='<u4')
    (path/'shared.hex').write_text(''.join(f'{int(v):08x}\n' for v in words))
    (path/'expected.hex').write_text(''.join(f'{int(v)&0xffffffff:08x}\n' for v in y.flat))
    (path/'expected-flags.hex').write_text(''.join(f'{int(v):02x}\n' for v in flags.flat))
    return dict(case_id=case['case_id'],m=m,n=n,outputs=m*n,shift=case['config']['output_shift'],
        input_array_sha256={k:case['arrays'][k]['sha256'] for k in ['Xq','Wq_packed','bq']},
        expected_y=y,expected_flags=flags)

def firmware(name,source):
    elf=OUT/(name+'.elf')
    cmd=['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32','-mcmodel=medany',
         '-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax','-Os','-g',
         '-Wall','-Wextra','-Werror','-I',ROOT/'sw','-T',ROOT/'sw/e203/link.ld',
         f'-Wl,-Map,{OUT/(name+".map")}',ROOT/'sw/e203/start.S',source]
    if name!='red-stub': cmd.append(ROOT/'sw/ffn1_driver.c')
    run('build-'+name,[*cmd,'-o',elf])
    run('disassemble-'+name,['riscv64-unknown-elf-objdump','-d','-S',elf])
    attributes,_,_=run('attributes-'+name,['riscv64-unknown-elf-readelf','-h','-A',elf])
    if not all(t in attributes for t in ['ELF32','RISC-V','0x80000000','soft-float ABI','rv32i','_m2','_a2','_c2','_zicsr','_zifencei']):
        raise RuntimeError('firmware ISA/ABI mismatch')
    run('binary-'+name,['riscv64-unknown-elf-objcopy','-O','binary',elf,OUT/(name+'.bin')])
    data=(OUT/(name+'.bin')).read_bytes()
    if len(data)>65536: raise RuntimeError('firmware exceeds ITCM')
    (OUT/(name+'.hex')).write_text(''.join(f'{b:02x}\n' for b in data))
    return name+'.hex',len(data)

def compile_rtl(sim,m,n):
    extra=[ROOT/'soc/e203_common/e203_cpu_shell.sv',ROOT/'soc/e203_common/icb_shared_ram.sv',
        *[ROOT/'rtl'/p for p in ['ffn1_icb.sv','ffn1_top.sv','dot64.sv','prototype_sync_ram.sv']],ROOT/'dv/e203_ffn1/tb_e203_ffn1.sv']
    sources=[ROOT/'dv/e203_boot/timescale.v',*sorted(UP.rglob('*.v')),*extra]
    include=[v for d in [UP/'core',UP/'perips',UP/'perips/apb_i2c'] for v in ['-I',str(d)]]
    name=f'{sim}-{m}x{n}'
    if sim=='icarus':
        binary=OUT/(name+'.vvp')
        cmd=['iverilog','-g2012','-Diverilog','-DDISABLE_SV_ASSERTION=1','-s','tb_e203_ffn1',
            '-P',f'tb_e203_ffn1.M={m}','-P',f'tb_e203_ffn1.N={n}','-o',binary,*include,*sources]
    else:
        obj=OUT/('obj-'+name);binary=obj/'Vtb_e203_ffn1'
        # Verilator requires the include directory joined to -I; Icarus also
        # accepts separate -I directory arguments, which are not portable here.
        include=['-I'+str(d) for d in [UP/'core',UP/'perips',UP/'perips/apb_i2c']]
        cmd=['verilator','--binary','--timing','--build-jobs','4','-Wno-fatal',
            '-Diverilog','-DDISABLE_SV_ASSERTION=1','--top-module','tb_e203_ffn1',
            f'-GM={m}',f'-GN={n}','--Mdir',obj,*include,*sources]
    run('compile-'+name,cmd,timeout=1200)
    return binary

def simulate(name,binary,sim,fw,fixture_info,expected=0):
    folder=OUT/name
    folder.mkdir(exist_ok=True)
    for filename in ['shared.hex','expected.hex','expected-flags.hex']:
        (folder/filename).write_bytes((OUT/'fixture'/filename).read_bytes())
    if expected==2:
        # Negative control alters only the copied verification expectation,
        # never the frozen numeric vectors or any CPU-visible input.
        words=(folder/'expected.hex').read_text().splitlines()
        words[0]=f'{int(words[0],16)^1:08x}'
        (folder/'expected.hex').write_text('\n'.join(words)+'\n')
    (folder/fw[0]).write_bytes((OUT/fw[0]).read_bytes())
    cmd=(['vvp','-i',binary] if sim=='icarus' else ['stdbuf','-oL',binary])+[f'+FIRMWARE={fw[0]}',f'+FIRMWARE_BYTES={fw[1]}']
    log,elapsed,rc=run(name,cmd,cwd=folder,expected=expected,timeout=1800)
    if expected:
        if expected==1 and ('CPU_EXIT_FAILURE' not in log or 'code=ffffffb3' not in log): raise RuntimeError('RED did not fail for intended nonzero main exit')
        if expected==2 and 'CPU output mismatch index=0' not in log: raise RuntimeError('wrong expectation was not detected at actual CPU output')
        if 'E203_FFN1_PASS' in log: raise RuntimeError('negative case published PASS')
        return dict(status='EXPECTED_FAIL',exit_code=rc,elapsed_seconds=elapsed,
            reason='nonzero main return' if expected==1 else 'one-bit wrong verifier expectation caught at CPU output index 0')
    match=re.search(r'E203_FFN1_PASS ([^\n]+)',log)
    if not match: raise RuntimeError('no explicit CPU integration pass')
    metrics={key:int(value) for key,value in re.findall(r'(\w+)=(\d+)',match[1])}
    for file,key in [('cpu-output.txt','expected_y'),('cpu-flags.txt','expected_flags')]:
        lines=(folder/file).read_text().splitlines()
        expected_values=fixture_info[key].reshape(-1)
        if len(lines)!=len(expected_values): raise RuntimeError('incomplete '+file)
        for index,(line,value) in enumerate(zip(lines,expected_values)):
            actual_index,actual_value=line.split()
            bits=int(value)&(0xffffffff if key=='expected_y' else 255)
            if int(actual_index)!=index or int(actual_value,16)!=bits: raise RuntimeError('independent result mismatch '+file)
    return dict(status='PASS',exit_code=rc,elapsed_seconds=elapsed,simulator=sim,
        metrics=metrics,cycles_per_second=metrics['cycles']/elapsed,
        simulator_binary_sha256=digest(binary),y_sha256=digest(folder/'cpu-output.txt'),flags_sha256=digest(folder/'cpu-flags.txt'))

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--red-only',action='store_true');args=parser.parse_args()
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'commands.jsonl').write_text('')
    save(OUT/'result.json',dict(status='RUNNING'))
    save(ROOT/'work/e203_ffn1_handoff.json',dict(status='RUNNING',report='reports/system/e203-ffn1/result.json'))
    print('[verify-dependencies] checking frozen inputs and official upstream inventory',flush=True)
    source_count=check_dependencies();frozen=inputs()
    print('[verify-vectors] recomputing all 36 frozen integer cases',flush=True)
    vector_verification=verify_vectors(ROOT,ROOT/'reports/model/baseline',ROOT/'reports/prototype/vectors')
    run('gcc-version',['riscv64-unknown-elf-gcc','--version'])
    run('iverilog-version',['iverilog','-V'])
    run('verilator-version',['verilator','--version'])
    info=fixture(OUT/'fixture',3,4)
    small_i=compile_rtl('icarus',3,4)
    red=firmware('red-stub',ROOT/'dv/e203_ffn1/red_stub.c')
    results=dict(red=simulate('red-nonzero-main',small_i,'icarus',red,info,expected=1))
    save(OUT/'red.json',results)
    if args.red_only: return
    fw=firmware('ffn1-driver',ROOT/'sw/e203_ffn1/main.c')
    results['small_icarus']=simulate('small-icarus',small_i,'icarus',fw,info)
    small_v=compile_rtl('verilator',3,4)
    results['small_verilator']=simulate('small-verilator',small_v,'verilator',fw,info)
    for key in ['y_sha256','flags_sha256']:
        if results['small_icarus'][key]!=results['small_verilator'][key]: raise RuntimeError('simulator disagreement '+key)
    if results['small_icarus']['metrics']!=results['small_verilator']['metrics']:
        raise RuntimeError('simulator cycle/transaction disagreement')
    results['negative_corrupt_expected']=simulate('negative-corrupt-expected',small_v,'verilator',fw,info,expected=2)
    full_info=fixture(OUT/'fixture',99,256)
    full_v=compile_rtl('verilator',99,256)
    results['full']=simulate('full-verilator',full_v,'verilator',fw,full_info)
    results['repeat']=simulate('repeat-verilator',full_v,'verilator',fw,full_info)
    for key in ['y_sha256','flags_sha256','metrics']:
        if results['full'][key]!=results['repeat'][key]: raise RuntimeError('independent rerun disagreement '+key)
    if inputs()!=frozen: raise RuntimeError('source changed during run; full repeat required')
    if check_dependencies()!=source_count: raise RuntimeError('upstream changed')
    report=dict(status='PASS',scope='Real public E203 CPU executes production C driver; one full 99x64x256 case and independent repeat, plus cross-simulator 3x4 fixture. Not CPU36 or competition platform acceptance.',
        source_entries_verified=source_count,input_sha256=frozen,vector_verification=vector_verification,
        case_id=full_info['case_id'],full_case_count=1,full_output_count=25344,repeat_output_count=25344,
        full_input_array_sha256=full_info['input_array_sha256'],results=results,
        memory_map={'mailbox':'0xa0000000..0xa0000013','configuration':'0xa0000100..0xa000010f',
        'X':'0xa0001000..0xa000417f','W_packed':'0xa0005000..0xa000cfff','bias64':'0xa000d000..0xa000d7ff',
        'Y':'0xa0010000..0xa0028bff','flags':'0xa0030000..0xa00362ff','shared_total_bytes':524288},
        artifacts={str(p.relative_to(OUT)):digest(p) for p in OUT.rglob('*') if p.is_file() and p.suffix in ['.elf','.map','.bin','.hex','.txt']},
        limitations=['Public upstream E203, not confirmed contest platform package','Behavioral SRAM models; no 150MHz timing/PPA evidence','No CPU36 or official600 claim','Verilator warnings saved in compile log; Icarus and Verilator same small fixture data/flags agree'])
    save(OUT/'result.json',report)
    save(ROOT/'work/e203_ffn1_handoff.json',dict(status='PASS',command='bash scripts/run_e203_ffn1.sh',exit_code=0,
        report='reports/system/e203-ffn1/result.json',result_sha256=digest(OUT/'result.json'),input_sha256=frozen,
        full_case_count=1,full_output_count=25344,repeat_output_count=25344,source_entries_verified=source_count,
        case_id=full_info['case_id'],limitations=report['limitations']))
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':
    try: main()
    except Exception as exc:
        OUT.mkdir(parents=True,exist_ok=True)
        save(OUT/'result.json',dict(status='FAIL',error=str(exc)))
        save(ROOT/'work/e203_ffn1_handoff.json',dict(status='FAIL',error=str(exc),report='reports/system/e203-ffn1/result.json'))
        print(str(exc),file=sys.stderr);sys.exit(1)
