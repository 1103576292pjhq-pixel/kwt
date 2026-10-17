#!/usr/bin/env python3
"""Directed numeric-contract edges through real E203 and unchanged C/RTL/TB."""
from __future__ import annotations
from pathlib import Path
import sys
import numpy as np
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,put,read_json,run_id,sha
from numeric import ffn1_reference

def edge_fixture(path,m,n,tasks):
    if (m,n,tasks)!=(3,16,2):raise RuntimeError('directed fixture is explicitly 3x64x16, two tasks')
    path.mkdir(exist_ok=False);raw_dir=path/'directed-inputs';raw_dir.mkdir()
    image=bytearray(524288);ys=[];fs=[];cases=[];inputs={};stats=[]
    def place(offset,payload):image[offset:offset+len(payload)]=payload
    place(0x100,np.array([3,16,2,0],dtype='<u4').tobytes())
    for task,shift in enumerate([47,0]):
        x=np.empty((3,64),dtype='<i2');x[0,:]=32767;x[1,:]=-32768
        x[2,:]=np.tile(np.array([32767,-32768],dtype='<i2'),32) if task==0 else 1
        w=np.zeros((64,16),dtype='<i2');bias=np.zeros(16,dtype='<i8')
        for col in range(16):
            if task==0:
                w[:,col]=32767 if col%4<2 else -32768
                bias[col]=(1<<47)-2 if col%4 in [0,2] else -(1<<47)+1
            else:
                group=col%8
                w[:,col]=32767 if group<3 else 0
                bias[col]=[0,(1<<47)-2,-(1<<47)+1,(1<<31)-1,1<<31,-(1<<31),-(1<<31)-1,0][group]
        # The final tail-row result also carries a real arithmetic flag, so
        # completion checks exercise last|overflow and last|both combinations.
        w[:,15]=-32768 if task==0 else 32767;bias[15]=(1<<47)-2
        reference=ffn1_reference(x,w,bias,shift)
        y=reference.output.astype('<i4')
        flags=reference.overflow.astype('u1')|(reference.output_saturated.astype('u1')<<1)
        categories={str(value):int((flags==value).sum()) for value in range(4)}
        if task==0 and (categories['1']==0 or categories['2'] or categories['3']):raise RuntimeError('overflow-only directed coverage missing')
        if task==1 and (categories['2']==0 or categories['3']==0 or categories['0']==0):raise RuntimeError('sat32-only/both/exact-bound directed coverage missing')
        if int(flags[-1,-1])!=(1 if task==0 else 3):raise RuntimeError('final-result arithmetic flag coverage missing')
        if not np.any(y>0) or not np.any(y<0):raise RuntimeError('positive/negative outputs missing')
        flags[-1,-1]|=4
        for key,array in [('Xq',x),('Wq_packed',w.T.copy()),('bq',bias)]:
            p=raw_dir/f'task{task}-{key}.npy';np.save(p,array,allow_pickle=False);inputs[str(p.relative_to(ROOT))]=sha(p)
        bank=task*0x40000;xo=0x1000+bank;wo=0x5000+bank;bo=0xd000+bank;yo=0x10000+bank;fo=0x30000+bank
        place(0x120+task*32,np.array([0x100+task,task+1,shift,xo,wo,bo,yo,fo],dtype='<u4').tobytes())
        place(xo,x.tobytes());place(wo,w.T.copy().tobytes());place(bo,bias.tobytes())
        place(yo,b'\xa5'*(3*16*4));place(fo,b'\xa5'*(3*16))
        ys.extend(int(v)&0xffffffff for v in y.flat);fs.extend(int(v) for v in flags.flat)
        cases.append({'task':task,'case_id':f'directed_numeric_edges/shift_{shift:02d}',
          'layer':task+1,'shift':shift,'outputs':48,'official_contest_sample':False,
          'x_sha256':inputs[str((raw_dir/f'task{task}-Xq.npy').relative_to(ROOT))],
          'w_sha256':inputs[str((raw_dir/f'task{task}-Wq_packed.npy').relative_to(ROOT))]})
        stats.append({'task':task,'shift':shift,'flag_categories_before_last':categories,
          'positive_outputs':int((y>0).sum()),'negative_outputs':int((y<0).sum()),
          'scalar_checks':reference.scalar_checks,'tail_rows':3})
    (path/'shared.hex').write_text(''.join(f'{int(v):08x}\n' for v in np.frombuffer(image,dtype='<u4')))
    (path/'expected.hex').write_text(''.join(f'{v:08x}\n' for v in ys))
    (path/'expected-flags.hex').write_text(''.join(f'{v:02x}\n' for v in fs))
    put(path/'directed-contract.json',{'scope':'Directed numeric-contract validation, not frozen engineering vectors or contest samples.',
      'numeric_format_unchanged':True,'quantization_tuning':False,'oracle':'Unchanged numeric.ffn1_reference',
      'numeric_source_sha256':sha(ROOT/'numeric/fixedpoint.py'),'tasks':stats,'inputs_sha256':inputs,
      'construction':'X signed16 extrema plus a third tail row; W signed16 extrema/zero; bias fixed near signed48 and signed32 bounds; shifts fixed at 47 and 0.'})
    put(path/'fixture.json',{'m':m,'n':n,'tasks':tasks,'cases':cases,'input_sha256':inputs,
         'generated_sha256':{str(p.relative_to(path)):sha(p) for p in path.rglob('*') if p.is_file()}})
    return {'m':m,'n':n,'tasks':tasks,'cases':cases,'inputs':inputs,'y':ys,'flags':fs}

def main():
    rid='directed-edges-'+run_id();soc.fixture=edge_fixture
    soc.IMPLEMENTATION.extend(['numeric/__init__.py','numeric/fixedpoint.py','scripts/revd_offline_soc_edges.py'])
    sys.argv=[sys.argv[0],'--stage','small','--tasks','2','--sim','verilator','--run-id',rid]
    soc.main()
    out=ROOT/'reports/revd_offline/soc'/rid;folder=out/'negative-wrong-flags';folder.mkdir(exist_ok=False)
    for filename in ['shared.hex','expected.hex','expected-flags.hex']:(folder/filename).write_bytes((out/'fixture'/filename).read_bytes())
    (folder/'revd-driver.hex').write_bytes((out/'revd-driver.hex').read_bytes())
    words=(folder/'expected-flags.hex').read_text().splitlines()
    if (int(words[0],16)&3)!=1:raise RuntimeError('first directed output must exercise overflow-only')
    words[0]=f'{int(words[0],16)^1:02x}';(folder/'expected-flags.hex').write_text('\n'.join(words)+'\n')
    run=soc.Run(out);size=len((out/'revd-driver.bin').read_bytes())
    text,record=run.cmd('negative-wrong-flags',[out/'obj/Vsoc_cpu_tb','+FIRMWARE=revd-driver.hex',f'+FIRMWARE_BYTES={size}'],
                        timeout=120,cwd=folder,negative='CPU flag mismatch task=0 index=0')
    report=read_json(out/'result.json');report['validation_kind']='DIRECTED_NUMERIC_EDGES'
    report['scope']='Real E203 executes unchanged C driver for signed16/48-bit numeric edges, shifts47/0 and nonzero overflow/saturated flags; not contest or frozen model samples.'
    report['directed_contract']=read_json(out/'fixture/directed-contract.json')
    report['results']['negative_wrong_flags']={'status':'EXPECTED_FAIL','reason':'Actual CPU shared flag write rejected after one verification-only overflow-bit corruption.','command':record}
    report['actual_simulator_executable_sha256']=sha(out/'obj/Vsoc_cpu_tb')
    report['commands'].extend(run.records)
    report['artifacts_sha256']={str(p.relative_to(out)):sha(p) for p in out.rglob('*') if p.is_file() and p.name!='result.json' and 'obj' not in p.relative_to(out).parts}
    put(out/'result.json',report);print('SOC_EDGES_REPORT',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
