"""Two complete tasks in one C invocation against actual RTL; server runs all12."""
import argparse
import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2]
sys.path.insert(0,str(HERE))
from suite_tools import prepare_suite,audit_suite,sha,save


def main():
    p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True)
    args=p.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    sources=[p for folder in [ROOT/'rtl',ROOT/'integration/e203/shared_sram/rtl'] for p in folder.rglob('*') if p.is_file()]
    before={str(p):sha(p) for p in sources}
    code=[HERE/p for p in ['suite_loader.v','shared_task.c','shared_task.h','task_test.c','task_test.h','kwt_mmio.h',
                          'suite_tools.py','single_tools.py','tests/native_io.c','tests/tb_suite_driver.v','tests/check_driver.py']]
    code_before={str(p):sha(p) for p in code}
    for source in code:
        target=out/'source'/source.relative_to(HERE);target.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(source,target)
    fixtures=ROOT/'verification/real12-20261102-02/fixtures'
    data=prepare_suite(fixtures,out/'data',json.loads((HERE/'fixture-identity.json').read_text()))
    # Independently recompute every fixture with the current frozen model, even though local C/RTL uses two.
    import numpy as np
    sys.path.insert(0,str(ROOT));from model.fixed_numeric import ffn1_int16
    for d in data:
        x=np.array(d['x'],dtype=np.uint32).astype(np.int32).astype(np.int16).reshape(99,64)
        w=np.array(d['w'],dtype=np.uint32).astype(np.int32).astype(np.int16).reshape(64,256)
        b=np.array(d['b'],dtype=np.uint32).astype(np.int32)
        y,f=ffn1_int16(x,w,b)
        expected=((y.astype(np.int32).astype(np.uint32)&65535)|(f.astype(np.uint32)<<16)).reshape(-1)
        assert expected.tolist()==d['gold'],'Current model differs case%d'%d['case']
    native=out/'native-driver'
    subprocess.run(['gcc','-std=c11','-Os','-Wall','-Wextra','-Werror',str(HERE/'tests/native_io.c'),str(HERE/'shared_task.c'),str(HERE/'task_test.c'),'-o',str(native)],check=True)
    spec=importlib.util.spec_from_file_location('shared_contract',ROOT/'integration/e203/shared_sram/tests/test_shared.py')
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    (out/'model.v').write_text(m.CONTRACT)
    rtl=out/'suite.vvp'
    cmd=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-s','tb_shared_task_driver','-o',str(rtl),'-f','rtl/kwt.f',
         'tb/memory/support/sram_contract_models.v',*map(str,(ROOT/'integration/e203/shared_sram/rtl').glob('*.v')),
         str(out/'model.v'),str(HERE/'suite_loader.v'),str(HERE/'tests/tb_suite_driver.v')]
    built=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True)
    (out/'compile.log').write_text(built.stdout+built.stderr);built.check_returncode()
    with tempfile.TemporaryDirectory(prefix='kwt-suite-') as temp:
        req,rsp=Path(temp)/'req',Path(temp)/'rsp';os.mkfifo(req);os.mkfifo(rsp)
        fds=[os.open(v,os.O_RDWR) for v in [req,rsp]]
        try:
            with (out/'rtl.log').open('w') as log:
                sim=subprocess.Popen(['vvp',str(rtl),'+request='+str(req),'+response='+str(rsp),'+trace=native-y.txt',
                    '+real_data=data','+real_trace=shared-y.txt'],stdout=log,stderr=log,cwd=out)
                host=None
                try:
                    host=subprocess.Popen([str(native),str(req),str(rsp)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
                    for _ in range(1800):
                        try:stdout,stderr=host.communicate(timeout=1);break
                        except subprocess.TimeoutExpired:
                            if sim.poll() is not None:raise RuntimeError('RTL early exit: '+(out/'rtl.log').read_text())
                    else:raise RuntimeError('C/RTL timeout')
                    sim.wait(timeout=20)
                finally:
                    if host is not None and host.poll() is None:host.kill();host.wait()
                    if sim.poll() is None:sim.kill();sim.wait()
        finally:
            for fd in fds:os.close(fd)
    (out/'native.log').write_text(stdout+stderr)
    print(stdout,flush=True)
    assert host.returncode==0 and sim.returncode==0,(stdout,stderr,(out/'rtl.log').read_text())
    assert 'SUITE_COUNTS completed=2 outputs=50688 verified=50688' in stdout
    audit=audit_suite(out/'shared-y.txt',data[2:4],fixtures)
    text=(out/'rtl.log').read_text()
    assert text.count('SUITE_TASK_DONE')==2 and text.count('SUITE_LOADER_DONE')==2
    assert before=={str(p):sha(p) for p in sources}
    assert code_before=={str(p):sha(p) for p in code},'Suite sources changed during run'
    save(out/'report.json',dict(status='PASS_TWO_CONTINUOUS_SHARED_C_RTL_CONTRACT',cases=[3,4],cpu_executed=False,
        official_sram=False,inter_task_resets=0,audit=audit,all12_python_golden_audited=True,
        native=stdout,rtl=text,production_sha256=before,production_unchanged=True,source_sha256=code_before))
    print('PASS CONTINUOUS_SHARED_C_RTL tasks=2 outputs=50688 inter_task_resets=0',flush=True)


if __name__=='__main__':main()
