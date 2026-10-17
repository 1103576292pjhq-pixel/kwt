#!/usr/bin/env python3
"""Bounded, fresh-path E203 integration; never invokes the frozen old runner."""
from __future__ import annotations
import argparse
import json
import os
from pathlib import Path
import re
import shutil
import sys
import numpy as np

sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,command,put,read_json,run_id,sha,utc

UP=ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203'
IMPLEMENTATION=[
    'rtl/revd_opt/core_stream_frontend_opt.sv','rtl/revd/banked_sp16.sv','rtl/revd/quant_epilogue.sv',
    'soc/revd_opt/revd_opt_icb.sv','soc/e203_common/e203_cpu_shell.sv','soc/e203_common/icb_shared_ram.sv',
    'sw/e203/start.S','sw/e203/link.ld','sw/revd_opt/main.c','sw/revd_opt/revd_opt_driver.c',
    'sw/revd_opt/revd_opt_driver.h','dv/revd_opt/soc_cpu_tb.sv','dv/revd_opt/soc_adapter_tb.sv',
    'dv/revd_opt/soc_red_stub.c','dv/e203_boot/timescale.v','scripts/revd_offline_soc_run.py',
    'scripts/revd_offline_common.py','config/e203-source-manifest.json',
    'reports/prototype/vectors/manifest.json']

def inventory():
    paths=[ROOT/p for p in IMPLEMENTATION]+sorted(UP.rglob('*.v'))
    return {str(p.relative_to(ROOT)):sha(p) for p in paths}

def verify_upstream():
    manifest=read_json(ROOT/'config/e203-source-manifest.json');count=0
    for repo in manifest['repositories']:
        for entry in repo['files']:
            path=ROOT/repo['root']/entry['path']
            if entry['type']=='symlink':
                if not path.is_symlink() or str(path.readlink())!=entry['target']:
                    raise RuntimeError('upstream link mismatch '+str(path))
            elif sha(path)!=entry['sha256']:raise RuntimeError('upstream source mismatch '+str(path))
            count+=1
    return count

class Run:
    def __init__(self,path):self.path=path;self.records=[]
    def cmd(self,name,argv,timeout=240,cwd=None,negative=None):
        record=command(argv,self.path/(name+'.log'),timeout=timeout,cwd=cwd or self.path)
        self.records.append(record)
        text=(self.path/(name+'.log')).read_text(errors='replace')
        if negative:
            if record['exit_code']==0 or negative not in text or 'E203_REVD_PASS' in text:
                raise RuntimeError(name+' negative control did not fail for intended reason')
        elif record['exit_code']!=0:raise RuntimeError(name+' failed; see '+record['log'])
        print(utc(),name,'exit',record['exit_code'],'seconds',round(record['seconds'],3),flush=True)
        return text,record

def fixture(path,m,n,tasks):
    path.mkdir(exist_ok=False)
    manifest=read_json(ROOT/'reports/prototype/vectors/manifest.json')
    image=bytearray(524288);expected=[];flags=[];cases=[];bound={}
    def place(offset,payload):image[offset:offset+len(payload)]=payload
    place(0x100,np.array([m,n,tasks,0],dtype='<u4').tobytes())
    for t in range(tasks):
        case=manifest['cases'][t];arrays={}
        for key in ['Xq','Wq_packed','bq','Yq','overflow','output_saturated']:
            info=case['arrays'][key];source=ROOT/'reports/prototype/vectors'/info['path']
            if sha(source)!=info['sha256']:raise RuntimeError('fixture source mismatch '+str(source))
            bound[str(source.relative_to(ROOT))]=sha(source)
            arrays[key]=np.load(source,allow_pickle=False)
        x=arrays['Xq'][:m,:].astype('<i2');w=arrays['Wq_packed'][:n,:].astype('<i2');b=arrays['bq'][:n].astype('<i8')
        y=arrays['Yq'][:m,:n].astype('<i4')
        f=arrays['overflow'][:m,:n].astype('u1')|(arrays['output_saturated'][:m,:n].astype('u1')<<1)
        f[-1,-1]|=4
        bank=t*0x40000;xo=0x1000+bank;wo=0x5000+bank;bo=0xd000+bank
        yo=0x10000+bank;fo=0x30000+bank
        place(0x120+t*32,np.array([0x100+t,case['layer'],case['config']['output_shift'],xo,wo,bo,yo,fo],dtype='<u4').tobytes())
        place(xo,x.tobytes());place(wo,w.tobytes());place(bo,b.tobytes())
        place(yo,b'\xa5'*(m*n*4));place(fo,b'\xa5'*(m*n))
        expected.extend(int(v)&0xffffffff for v in y.flat);flags.extend(int(v) for v in f.flat)
        cases.append({'task':t,'case_id':case['case_id'],'layer':case['layer'],'shift':case['config']['output_shift'],
                      'outputs':m*n,'x_sha256':sha(ROOT/'reports/prototype/vectors'/case['arrays']['Xq']['path']),
                      'w_sha256':sha(ROOT/'reports/prototype/vectors'/case['arrays']['Wq_packed']['path'])})
    (path/'shared.hex').write_text(''.join(f'{int(v):08x}\n' for v in np.frombuffer(image,dtype='<u4')))
    (path/'expected.hex').write_text(''.join(f'{v:08x}\n' for v in expected))
    (path/'expected-flags.hex').write_text(''.join(f'{v:02x}\n' for v in flags))
    put(path/'fixture.json',{'m':m,'n':n,'tasks':tasks,'cases':cases,'input_sha256':bound,
                            'generated_sha256':{p.name:sha(p) for p in path.iterdir() if p.is_file()}})
    return {'m':m,'n':n,'tasks':tasks,'cases':cases,'inputs':bound,'y':expected,'flags':flags}

def firmware(run,name,red=False):
    elf=run.path/(name+'.elf');sources=[ROOT/'sw/e203/start.S']
    sources+=[ROOT/'dv/revd_opt/soc_red_stub.c'] if red else [ROOT/'sw/revd_opt/main.c',ROOT/'sw/revd_opt/revd_opt_driver.c']
    run.cmd('build-'+name,['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
       '-mcmodel=medany','-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax',
       '-Os','-g','-Wall','-Wextra','-Werror','-I',ROOT/'sw/revd_opt','-T',ROOT/'sw/e203/link.ld',
       f'-Wl,-Map,{run.path/(name+".map")}',*sources,'-o',elf])
    attrs,_=run.cmd('attributes-'+name,['riscv64-unknown-elf-readelf','-h','-A',elf])
    if not all(t in attrs for t in ['ELF32','RISC-V','0x80000000','rv32i','_m2','_a2','_c2','_zicsr','_zifencei']):
        raise RuntimeError('unexpected CPU firmware ISA/ABI')
    run.cmd('disassemble-'+name,['riscv64-unknown-elf-objdump','-d','-S',elf])
    run.cmd('binary-'+name,['riscv64-unknown-elf-objcopy','-O','binary',elf,run.path/(name+'.bin')])
    payload=(run.path/(name+'.bin')).read_bytes()
    if not 0<len(payload)<=65536:raise RuntimeError('firmware does not fit ITCM')
    hexpath=run.path/(name+'.hex');hexpath.write_text(''.join(f'{v:02x}\n' for v in payload))
    return hexpath,len(payload)

def compile_cpu(run,m,n,tasks,pm,latency,sim):
    extra=[ROOT/p for p in IMPLEMENTATION[:6]]+[ROOT/'dv/revd_opt/soc_cpu_tb.sv']
    sources=[ROOT/'dv/e203_boot/timescale.v',*sorted(UP.rglob('*.v')),*extra]
    inc=[UP/'core',UP/'perips',UP/'perips/apb_i2c']
    if sim=='icarus':
        binary=run.path/'cpu.vvp'
        argv=['iverilog','-g2012','-Diverilog','-DDISABLE_SV_ASSERTION=1','-s','soc_cpu_tb',
          '-P',f'soc_cpu_tb.M={m}','-P',f'soc_cpu_tb.N={n}','-P',f'soc_cpu_tb.TASKS={tasks}',
          '-P',f'soc_cpu_tb.PM={pm}','-P',f'soc_cpu_tb.READ_LATENCY={latency}',
          '-o',binary,*['-I'+str(d) for d in inc],*sources]
    else:
        obj=run.path/'obj';binary=obj/'Vsoc_cpu_tb'
        argv=['verilator','--binary','--timing','--build-jobs','4','-Wno-fatal','-CFLAGS','-O3',
          '-Diverilog','-DDISABLE_SV_ASSERTION=1','--top-module','soc_cpu_tb',
          f'-GM={m}',f'-GN={n}',f'-GTASKS={tasks}',f'-GPM={pm}',f'-GREAD_LATENCY={latency}',
          '--Mdir',obj,*['-I'+str(d) for d in inc],*sources]
    run.cmd('compile-cpu-'+sim,argv,timeout=600)
    return binary

def simulate(run,name,binary,sim,fw,info,negative=None):
    folder=run.path/name;folder.mkdir(exist_ok=False)
    for filename in ['shared.hex','expected.hex','expected-flags.hex']:
        (folder/filename).write_bytes((run.path/'fixture'/filename).read_bytes())
    (folder/fw[0].name).write_bytes(fw[0].read_bytes())
    if negative=='corrupt':
        lines=(folder/'expected.hex').read_text().splitlines();lines[0]=f'{int(lines[0],16)^1:08x}'
        (folder/'expected.hex').write_text('\n'.join(lines)+'\n')
    cmd=(['vvp',binary] if sim=='icarus' else [binary])+[f'+FIRMWARE={fw[0].name}',f'+FIRMWARE_BYTES={fw[1]}']
    text,record=run.cmd(name,cmd,timeout=880,cwd=folder,
                       negative='CPU_EXIT_FAILURE' if negative=='return' else 'CPU output mismatch task=0 index=0' if negative=='corrupt' else None)
    if negative:return {'status':'EXPECTED_FAIL','command':record,'reason':negative}
    match=re.search(r'E203_REVD_PASS ([^\n]+)',text)
    if not match:raise RuntimeError('missing explicit CPU pass')
    metrics={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])}
    task_metrics=[{k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',line)} for line in re.findall(r'E203_REVD_TASK ([^\n]+)',text)]
    if len(task_metrics)!=info['tasks']:raise RuntimeError('missing task windows')
    output_hashes={}
    for filename,key in [('cpu-output.txt','y'),('cpu-flags.txt','flags')]:
        lines=(folder/filename).read_text().splitlines();wanted=info[key];seen=set()
        if len(lines)!=len(wanted):raise RuntimeError('incomplete actual output '+filename)
        for line in lines:
            t,index,value=line.split();t=int(t);index=int(index);value=int(value,16)
            if not (0<=t<info['tasks'] and 0<=index<info['m']*info['n']):raise RuntimeError('wrong index')
            flat=t*info['m']*info['n']+index
            if flat in seen or value!=wanted[flat]:raise RuntimeError('duplicate or wrong actual data '+filename)
            seen.add(flat)
        output_hashes[filename]=sha(folder/filename)
    return {'status':'PASS','metrics':metrics,'task_metrics':task_metrics,'output_sha256':output_hashes,'command':record}

def main():
    p=argparse.ArgumentParser();p.add_argument('--stage',choices=['adapter','small','full'],default='small')
    p.add_argument('--sim',choices=['icarus','verilator'],default='verilator');p.add_argument('--tasks',type=int,choices=[1,2],default=2)
    p.add_argument('--pm',type=int,choices=[2,4],default=4);p.add_argument('--latency',type=int,choices=[1,2],default=1)
    p.add_argument('--run-id',default=None);args=p.parse_args()
    rid=args.run_id or run_id();out=ROOT/'reports/revd_offline/soc'/rid;out.mkdir(parents=True,exist_ok=False)
    run=Run(out);report={'status':'RUNNING','started_utc':utc(),'run_id':rid,'run_identity':os.environ.get('KWT_OFFLINE_RUN_ID'),
                       'profile':vars(args),'scope':'Public E203 executes new C event/retirement driver; no official platform/PPA acceptance.'}
    put(out/'result.json',report)
    try:
        frozen=inventory();report['source_sha256']=frozen;report['upstream_entries_verified']=verify_upstream()
        toolnames=['riscv64-unknown-elf-gcc','riscv64-unknown-elf-objcopy','riscv64-unknown-elf-objdump',
                   'riscv64-unknown-elf-readelf','verilator','iverilog','vvp','g++','make']
        toolpaths=[Path(sys.executable).resolve()]+[Path(shutil.which(name)).resolve() for name in toolnames]
        report['tool_sha256']={str(path):sha(path) for path in toolpaths}
        for tool,cmd in [('gcc',['riscv64-unknown-elf-gcc','--version']),('verilator',['verilator','--version']),('iverilog',['iverilog','-V'])]:
            text,_=run.cmd(tool+'-version',cmd);report[tool+'_version']=text.splitlines()[0]
        if args.stage=='adapter':
            binary=out/'adapter.vvp'
            run.cmd('compile-adapter',['iverilog','-g2012','-s','soc_adapter_tb','-o',binary,
                    *[ROOT/p for p in IMPLEMENTATION[:4]],ROOT/'dv/revd_opt/soc_adapter_tb.sv'])
            text,_=run.cmd('simulate-adapter',['vvp',binary],timeout=120)
            if 'REVD_SOC_ADAPTER_PASS checks=' not in text:raise RuntimeError('adapter test no pass')
            report['adapter']='PASS'
        else:
            m,n=(3,16) if args.stage=='small' else (99,256)
            info=fixture(out/'fixture',m,n,args.tasks);report['cases']=info['cases'];report['input_sha256']=info['inputs']
            binary=compile_cpu(run,m,n,args.tasks,args.pm,args.latency,args.sim)
            fw=firmware(run,'revd-driver')
            results={}
            if args.stage=='small':
                red=firmware(run,'red-stub',red=True)
                results['negative_cpu_return']=simulate(run,'negative-return',binary,args.sim,red,info,'return')
            results['cpu']=simulate(run,'cpu',binary,args.sim,fw,info)
            if args.stage=='small':results['negative_wrong_expected']=simulate(run,'negative-wrong-expected',binary,args.sim,fw,info,'corrupt')
            report['results']=results
        report['source_unchanged']=inventory()==frozen
        if not report['source_unchanged']:raise RuntimeError('bound sources changed during run; evidence is stale and cannot accept current RTL')
        report.update(status='PASS',finished_utc=utc(),commands=run.records)
        report['artifacts_sha256']={str(p.relative_to(out)):sha(p) for p in out.rglob('*') if p.is_file() and p.name!='result.json' and 'obj' not in p.relative_to(out).parts}
        put(out/'result.json',report)
    except Exception as exc:
        report.update(status='FAIL',error=str(exc),finished_utc=utc(),commands=run.records);put(out/'result.json',report);raise
    print('SOC_REPORT',out.relative_to(ROOT),report['status'],flush=True)
if __name__=='__main__':main()
