#!/usr/bin/env python3
"""Directed W2 flags through unchanged C, reusing a verified M3/N32 binary."""
from pathlib import Path
import argparse
import sys
import re
import numpy as np
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import revd_offline_soc_w2_run as w2
import revd_offline_soc_edges as edges
from numeric import ffn1_reference
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

def fixture(path):
    path.mkdir(exist_ok=False);seed=edges.edge_fixture(path/'seed',3,16,2)
    raw=path/'directed-inputs';raw.mkdir();image=bytearray(524288)
    cases=[];ys=[];fs=[];inputs=dict(seed['inputs']);stats=[]
    def place(offset,payload):image[offset:offset+len(payload)]=payload
    place(0x100,np.array([3,32,2,0],dtype='<u4').tobytes())
    for task,shift in enumerate([47,0]):
        seed_dir=path/'seed/directed-inputs'
        x=np.load(seed_dir/f'task{task}-Xq.npy',allow_pickle=False).astype('<i2')
        w16=np.load(seed_dir/f'task{task}-Wq_packed.npy',allow_pickle=False).astype('<i2')
        b16=np.load(seed_dir/f'task{task}-bq.npy',allow_pickle=False).astype('<i8')
        wp=np.concatenate([w16,w16],axis=0);bias=np.concatenate([b16,b16])
        reference=ffn1_reference(x,wp.T.copy(),bias,shift);y=reference.output.astype('<i4')
        flags=reference.overflow.astype('u1')|(reference.output_saturated.astype('u1')<<1)
        stats.append({'task':task,'shift':shift,'flag_categories_before_last':{str(v):int((flags==v).sum()) for v in range(4)},
          'positive_outputs':int((y>0).sum()),'negative_outputs':int((y<0).sum()),'scalar_checks':reference.scalar_checks})
        if int(flags[-1,-1])!=(1 if task==0 else 3):raise RuntimeError('missing final tail-row arithmetic flags')
        flags[-1,-1]|=4
        for key,array in [('Xq',x),('Wq_packed',wp),('bq',bias)]:
            source=raw/f'task{task}-{key}.npy';np.save(source,array,allow_pickle=False);inputs[str(source.relative_to(ROOT))]=sha(source)
        bank=task*0x40000;xo=0x1000+bank;wo=0x5000+bank;bo=0xd000+bank;yo=0x10000+bank;fo=0x30000+bank
        place(0x120+task*32,np.array([0x100+task,task+1,shift,xo,wo,bo,yo,fo],dtype='<u4').tobytes())
        place(xo,x.tobytes());place(wo,wp.tobytes());place(bo,bias.tobytes())
        place(yo,b'\xa5'*(3*32*4));place(fo,b'\xa5'*(3*32))
        ys.extend(int(v)&0xffffffff for v in y.flat);fs.extend(int(v) for v in flags.flat)
        cases.append({'task':task,'case_id':f'directed_w2_numeric_edges/shift_{shift:02d}','layer':task+1,'shift':shift,
          'outputs':96,'official_contest_sample':False,'x_sha256':inputs[str((raw/f'task{task}-Xq.npy').relative_to(ROOT))],
          'w_sha256':inputs[str((raw/f'task{task}-Wq_packed.npy').relative_to(ROOT))]})
    if (fs[0]&3)!=1:raise RuntimeError('first result must have overflow-only for directed negative')
    (path/'shared.hex').write_text(''.join(f'{int(v):08x}\n' for v in np.frombuffer(image,dtype='<u4')))
    (path/'expected.hex').write_text(''.join(f'{v:08x}\n' for v in ys))
    (path/'expected-flags.hex').write_text(''.join(f'{v:02x}\n' for v in fs))
    contract={'scope':'Directed numeric contract, not frozen model or contest samples. Two tiles repeat the fixed signed16/48/sat32 edge columns; no parameter tuning.',
      'numeric_format_unchanged':True,'oracle':'Frozen numeric.ffn1_reference','construction_source':'scripts/revd_offline_soc_edges.py',
      'tasks':stats,'inputs_sha256':inputs,'last_result_flags':[fs[95],fs[191]]}
    put(path/'directed-contract.json',contract)
    return {'m':3,'n':32,'tasks':2,'cases':cases,'inputs':inputs,'y':ys,'flags':fs},contract

def main():
    p=argparse.ArgumentParser();p.add_argument('--small-report',required=True);args=p.parse_args()
    source=ROOT/args.small_report;small=read_json(source)
    if small['status']!='PASS' or not small['source_unchanged'] or small['profile']['stage']!='small' or small['profile']['architecture']!='CTX4_W2_Y1_X4':
        raise RuntimeError('requires verified W2 M3/N32 two-task small report')
    for name,digest in small['source_sha256'].items():
        if sha(ROOT/name)!=digest:raise RuntimeError('compiled source changed '+name)
    for name,digest in small['tool_sha256'].items():
        if sha(Path(name))!=digest:raise RuntimeError('compiled tool changed '+name)
    compile_record=read_json(source.parent/'compile-cpu-verilator.log.command.json')
    if compile_record['exit_code']!=0 or not all(arg in compile_record['argv'] for arg in ['soc_cpu_tb_w2','-GM=3','-GN=32','-GTASKS=2','-GPM=4','-GREAD_LATENCY=1']):
        raise RuntimeError('reused actual binary configuration mismatch')
    binary=source.parent/'obj/Vsoc_cpu_tb_w2';fw=(source.parent/'revd-w2-driver.hex',len((source.parent/'revd-w2-driver.bin').read_bytes()))
    if sha(binary)!=small['actual_simulator_executable_sha256'] or sha(source.parent/'revd-w2-driver.bin')!=small['firmware_binary_sha256']:
        raise RuntimeError('reused binary/firmware bytes changed')
    out=ROOT/'reports/revd_offline/soc'/('soc-w2-edges-'+run_id());out.mkdir(parents=True,exist_ok=False);run=w2.Run(out)
    frozen=dict(small['source_sha256'])
    for name in ['scripts/revd_offline_soc_w2_edges.py','scripts/revd_offline_soc_edges.py','numeric/__init__.py','numeric/fixedpoint.py']:frozen[name]=sha(ROOT/name)
    report={'status':'RUNNING','started_utc':utc(),'scope':'Real E203 two-tile directed arithmetic flags, unchanged W2 C driver; not official or frozen model samples.',
      'profile':{'m':3,'n':32,'tasks':2,'pm':4,'latency':1,'validation_kind':'DIRECTED_NUMERIC_EDGES'},
      'source_sha256':frozen,'tool_sha256':small['tool_sha256'],'reused_compile_report':str(source.relative_to(ROOT)),
      'reused_compile_report_sha256':sha(source),'actual_simulator_executable_sha256':sha(binary),
      'firmware_binary_sha256':sha(source.parent/'revd-w2-driver.bin'),'fresh_compile':False}
    put(out/'result.json',report)
    try:
        info,contract=fixture(out/'fixture');report.update(cases=info['cases'],input_sha256=info['inputs'],directed_contract=contract)
        report['results']={'cpu':w2.soc.simulate(run,'cpu',binary,'verilator',fw,info)}
        log=(out/'cpu.log').read_text();match=re.search(r'E203_W2_LIFECYCLE ([^\n]+)',log)
        if not match:raise RuntimeError('missing W2 lifecycle evidence')
        report['results']['cpu']['lifecycle']={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])}
        folder=out/'negative-wrong-flags';folder.mkdir(exist_ok=False)
        for filename in ['shared.hex','expected.hex','expected-flags.hex']:(folder/filename).write_bytes((out/'fixture'/filename).read_bytes())
        (folder/fw[0].name).write_bytes(fw[0].read_bytes())
        words=(folder/'expected-flags.hex').read_text().splitlines();words[0]=f'{int(words[0],16)^1:02x}'
        (folder/'expected-flags.hex').write_text('\n'.join(words)+'\n')
        text,record=run.cmd('negative-wrong-flags',[binary,f'+FIRMWARE={fw[0].name}',f'+FIRMWARE_BYTES={fw[1]}'],
          timeout=120,cwd=folder,negative='CPU flag mismatch task=0 index=0')
        report['results']['negative_wrong_flags']={'status':'EXPECTED_FAIL','command':record,'reason':'Actual CPU shared flag write rejected after verification-only overflow-bit corruption.'}
        report['source_unchanged']=all(sha(ROOT/name)==digest for name,digest in frozen.items())
        if not report['source_unchanged']:raise RuntimeError('W2 source changed')
        report.update(status='PASS',finished_utc=utc(),commands=run.records)
        report['artifacts_sha256']={str(path.relative_to(out)):sha(path) for path in out.rglob('*') if path.is_file() and path.name!='result.json'}
        put(out/'result.json',report)
    except Exception as exc:
        report.update(status='FAIL',error=str(exc),commands=run.records,finished_utc=utc());put(out/'result.json',report);raise
    print('SOC_W2_EDGES',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
