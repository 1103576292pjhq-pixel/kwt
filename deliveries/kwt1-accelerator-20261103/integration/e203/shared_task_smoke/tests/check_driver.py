import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import numpy as np

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2]
sys.path.insert(0,str(ROOT))
from model.fixed_numeric import ffn1_int16

def main():
    p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args()
    assert (HERE/'shared_task.c').is_file(),'Shared-data full-task implementation missing'
    out=args.output.resolve();out.mkdir(exist_ok=False)
    native=out/'native-driver'
    subprocess.run(['gcc','-std=c11','-Os','-Wall','-Wextra','-Werror',str(HERE/'tests/native_io.c'),
        str(HERE/'shared_task.c'),str(HERE/'task_test.c'),str(HERE/'fixture.c'),'-o',str(native)],check=True)
    spec=importlib.util.spec_from_file_location('shared_contract',ROOT/'integration/e203/shared_sram/tests/test_shared.py')
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    model=out/'contract4096.v';model.write_text(mod.CONTRACT)
    rtl=out/'driver.vvp'
    cmd=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-s','tb_shared_task_driver','-o',str(rtl),'-f','rtl/kwt.f',
         'tb/memory/support/sram_contract_models.v',*map(str,[(ROOT/'integration/e203/shared_sram/rtl'/n) for n in
           ['kwt_shared_ram_icb.v','kwt_shared_sram_array.v','kwt_shared_sram.v']]),str(model),str(HERE/'tests/tb_shared_task_driver.v')]
    built=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True);(out/'compile.log').write_text(built.stdout+built.stderr);built.check_returncode()
    reports=[]
    for mutation,want in [(0,1),(1,0x70)]:
        with tempfile.TemporaryDirectory(prefix='shared-task-') as folder:
            req,rsp=Path(folder)/'req',Path(folder)/'rsp';os.mkfifo(req);os.mkfifo(rsp)
            fds=[os.open(v,os.O_RDWR) for v in [req,rsp]]
            trace=out/('y-%d.txt'%mutation)
            try:
                with (out/('rtl-%d.log'%mutation)).open('w') as log:
                    sim=subprocess.Popen(['vvp',str(rtl),'+request='+str(req),'+response='+str(rsp),
                                          '+trace='+trace.name,'+mutation='+str(mutation)],stdout=log,stderr=log,cwd=out)
                    host=None
                    try:
                        argv=[str(native),str(req),str(rsp)]
                        host=subprocess.Popen(argv,stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
                        for wait in range(600):
                            try:
                                stdout,stderr=host.communicate(timeout=1)
                                run=subprocess.CompletedProcess(argv,host.returncode,stdout,stderr);break
                            except subprocess.TimeoutExpired:
                                if sim.poll() is not None:raise RuntimeError('RTL exited before driver: '+(out/('rtl-%d.log'%mutation)).read_text())
                        else:raise RuntimeError('C/RTL driver timeout')
                        sim.wait(timeout=20)
                    finally:
                        if host is not None and host.poll() is None:host.kill();host.wait()
                        if sim.poll() is None:sim.kill();sim.wait()
            finally:
                for fd in fds:os.close(fd)
        (out/('native-%d.log'%mutation)).write_text(run.stdout+run.stderr)
        print(run.stdout.strip(),flush=True)
        match=re.search(r'SHARED_TASK code=([0-9a-f]+)',run.stdout)
        assert match and int(match[1],16)==want and run.returncode==(0 if mutation==0 else 1),(run.stdout,run.stderr)
        assert sim.returncode==0,(out/('rtl-%d.log'%mutation)).read_text()
        rtl_text=(out/('rtl-%d.log'%mutation)).read_text()
        if mutation==0:
            for piece in ['blocks=400 outputs=25344 verified=25344','result_reads=25344','shared_reads=48322','shared_writes=73666','y_writes=25344 y_reads=25344']:
                assert piece in run.stdout+rtl_text,piece
            x=np.array([[((r-49)*8+2*k-63)*8 for k in range(64)] for r in range(99)],dtype=np.int16)
            w=np.array([[32767 if c==0 else -32768 if c==1 else 0 if c<8 else ((c-128)*8+k-32)*8 for c in range(256)] for k in range(64)],dtype=np.int16)
            special=[0,0,98304,-98304,32768,-32768,163840,-163840]
            b=np.array([special[c] if c<8 else (c-128)*1024+32736 for c in range(256)],dtype=np.int32)
            y,flags=ffn1_int16(x,w,b);expected=(y.astype(np.int32).astype(np.uint32)&65535)|(flags.astype(np.uint32)<<16)
            seen={}
            for line in trace.read_text().splitlines():
                tag,index,value=line.split();assert tag=='Y' and int(index) not in seen
                seen[int(index)]=int(value,16)
            assert len(seen)==25344 and all(seen[i]==int(expected.reshape(-1)[i]) for i in range(25344))
        else:assert 'altered=1' in rtl_text and 'actual=deadbeef' in run.stdout
        reports.append(dict(mutation=mutation,code=hex(want),native=run.stdout.strip(),rtl=rtl_text.strip()))
    (out/'report.json').write_text(json.dumps(dict(status='PASS_SHARED_TASK_C_RTL_CONTRACT_ONLY',scenarios=reports,
        outputs_audited=25344,official_sram=False,cpu_executed=False,negative_dropped_store_caught=True),indent=2)+'\n')
    print('PASS SHARED_TASK_DRIVER outputs=25344 bit_mismatches=0; real CPU run pending',flush=True)

if __name__=='__main__':main()
