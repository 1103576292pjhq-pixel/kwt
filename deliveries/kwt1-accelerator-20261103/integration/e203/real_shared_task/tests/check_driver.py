"""Run the actual C firmware against production acc/shared RTL and file loader."""
import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2]
sys.path.insert(0,str(HERE))
from real_tools import prepare_data,audit_trace,save,sha


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    assert (HERE/'shared_task.c').is_file() and (HERE/'real_loader.v').is_file(), 'Real firmware/loader not implemented'
    files=[p for folder in [ROOT/'rtl',ROOT/'integration/e203/shared_sram/rtl'] for p in folder.rglob('*') if p.is_file()]
    before={str(p):sha(p) for p in files}
    data=prepare_data(ROOT/'verification/real12-20261102-02/fixtures',out/'data',json.loads((HERE/'fixture-identity.json').read_text()))
    native=out/'native-driver'
    subprocess.run(['gcc','-std=c11','-Os','-Wall','-Wextra','-Werror',str(HERE/'tests/native_io.c'),
                    str(HERE/'shared_task.c'),str(HERE/'task_test.c'),'-o',str(native)],check=True)
    spec=importlib.util.spec_from_file_location('shared_contract',ROOT/'integration/e203/shared_sram/tests/test_shared.py')
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    model=out/'contract4096.v';model.write_text(mod.CONTRACT)
    rtl=out/'driver.vvp'
    cmd=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-s','tb_shared_task_driver','-o',str(rtl),'-f','rtl/kwt.f',
         'tb/memory/support/sram_contract_models.v',*map(str,[(ROOT/'integration/e203/shared_sram/rtl'/n) for n in
         ['kwt_shared_ram_icb.v','kwt_shared_sram_array.v','kwt_shared_sram.v']]),str(model),str(HERE/'real_loader.v'),str(HERE/'tests/tb_real_driver.v')]
    compiled=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True)
    (out/'compile.log').write_text(compiled.stdout+compiled.stderr);compiled.check_returncode()
    reports=[]
    for mutation,want in [(0,1),(1,0x70)]:
        with tempfile.TemporaryDirectory(prefix='real-shared-') as folder:
            req,rsp=Path(folder)/'req',Path(folder)/'rsp';os.mkfifo(req);os.mkfifo(rsp)
            fds=[os.open(v,os.O_RDWR) for v in [req,rsp]]
            trace=out/('y-%d.txt'%mutation)
            try:
                with (out/('rtl-%d.log'%mutation)).open('w') as log:
                    sim=subprocess.Popen(['vvp',str(rtl),'+request='+str(req),'+response='+str(rsp),
                        '+trace='+trace.name,'+real_data=data','+mutation='+str(mutation)],stdout=log,stderr=log,cwd=out)
                    host=None
                    try:
                        host=subprocess.Popen([str(native),str(req),str(rsp)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
                        for _ in range(900):
                            try: stdout,stderr=host.communicate(timeout=1);break
                            except subprocess.TimeoutExpired:
                                if sim.poll() is not None: raise RuntimeError('RTL exited: '+(out/('rtl-%d.log'%mutation)).read_text())
                        else: raise RuntimeError('C/RTL task timeout')
                        sim.wait(timeout=20)
                    finally:
                        if host is not None and host.poll() is None:host.kill();host.wait()
                        if sim.poll() is None:sim.kill();sim.wait()
            finally:
                for fd in fds:os.close(fd)
        (out/('native-%d.log'%mutation)).write_text(stdout+stderr)
        print(stdout.strip(),flush=True)
        match=re.search(r'SHARED_TASK code=([0-9a-f]+)',stdout)
        assert match and int(match[1],16)==want and host.returncode==(0 if mutation==0 else 1),(stdout,stderr)
        assert sim.returncode==0,(out/('rtl-%d.log'%mutation)).read_text()
        rtl_text=(out/('rtl-%d.log'%mutation)).read_text()
        assert 'REAL_LOADER_DONE writes=48320' in rtl_text
        if mutation==0:
            assert 'blocks=400 outputs=25344 verified=25344' in stdout
            audit=audit_trace(trace,data['gold'],ROOT/'verification/real12-20261102-02/fixtures/case3-ref.f32')
            # Independent current numerical-model audit, not only stored old golden.
            import numpy as np
            sys.path.insert(0,str(ROOT));from model.fixed_numeric import ffn1_int16
            x=np.asarray(data['x'],dtype=np.uint32).astype(np.int32).astype(np.int16).reshape(99,64)
            w=np.asarray(data['w'],dtype=np.uint32).astype(np.int32).astype(np.int16).reshape(64,256)
            b=np.asarray(data['b'],dtype=np.uint32).astype(np.int32)
            y,flags=ffn1_int16(x,w,b)
            golden=((y.astype(np.int32).astype(np.uint32)&65535)|(flags.astype(np.uint32)<<16)).reshape(-1)
            assert golden.tolist()==data['gold'],'Current Python model differs from fixture'
        else:
            assert 'altered=1' in rtl_text and 'verified=0' in stdout and 'actual=deadbeef' in stdout
        reports.append(dict(mutation=mutation,code=hex(want),native=stdout.strip(),rtl=rtl_text.strip()))
    assert before=={str(p):sha(p) for p in files},'Production inputs changed'
    save(out/'report.json',dict(status='PASS_REAL_SHARED_C_RTL_CONTRACT',case=3,cpu_executed=False,official_sram=False,
         sample=data['sample'],audit=audit,scenarios=reports,production_sha256=before,production_unchanged=True,
         negative_dropped_store_caught=True,loader_bus_handoff_and_reset_retention_exercised=True))
    print('PASS REAL_SHARED_DRIVER outputs=25344 bit_mismatches=0 nrmse_percent=%.8f'%audit['nrmse_percent'],flush=True)


if __name__=='__main__':main()
