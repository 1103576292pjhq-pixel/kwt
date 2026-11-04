from pathlib import Path
import os,subprocess,sys,tempfile
HERE=Path(__file__).resolve().parents[1]
from support_tools import prepare_fixture,sha,save,audit_trace
from timing_tools import audit_timing


def main():
    out=Path(sys.argv[1]).resolve();out.mkdir(parents=True,exist_ok=False)
    firmware=HERE/'firmware'
    data=prepare_fixture(out/'data')
    (out/'loader.v').write_bytes((HERE/'tests/support/real_loader.v').read_bytes())
    native=out/'native-driver'
    subprocess.run(['gcc','-std=c11','-O2','-flto','-Wall','-Wextra','-Werror',str(firmware/'tests/native_io.c'),
                    str(firmware/'task_test.c'),str(firmware/'shared_task.c'),'-o',str(native)],check=True)
    (out/'shared_model.v').write_bytes((HERE/'tests/support/shared_model.v').read_bytes())
    sources=list((HERE/'rtl').rglob('*.v'))
    command=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),'-s','tb_shared_task_driver',
       '-o',str(out/'sim.vvp'),*map(str,sources),str(HERE/'tests/support/sram_contract_models.v'),
       str(out/'shared_model.v'),str(out/'loader.v'),str(HERE/'tests/support/timing_probe.v'),str(HERE/'tests/tb_dma_firmware.v')]
    proc=subprocess.run(command,capture_output=True,text=True)
    (out/'compile.log').write_text(proc.stdout+proc.stderr);proc.check_returncode()
    with tempfile.TemporaryDirectory(prefix='kwt-dma-fw-') as temp:
        req,rsp=Path(temp)/'req',Path(temp)/'rsp';os.mkfifo(req);os.mkfifo(rsp)
        fds=[os.open(p,os.O_RDWR) for p in [req,rsp]];sim=host=None
        try:
            with (out/'rtl.log').open('w') as log:
                sim=subprocess.Popen(['vvp',str(out/'sim.vvp'),'+request='+str(req),'+response='+str(rsp),
                    '+real_data=data','+trace=shared-y.txt'],cwd=out,stdout=log,stderr=log)
                host=subprocess.Popen([str(native),str(req),str(rsp)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
                for _ in range(900):
                    try:stdout,stderr=host.communicate(timeout=1);break
                    except subprocess.TimeoutExpired:
                        if sim.poll() is not None:raise RuntimeError((out/'rtl.log').read_text())
                else:raise RuntimeError('DMA firmware timeout')
                sim.wait(timeout=30)
        finally:
            for p in [sim,host]:
                if p is not None and p.poll() is None:p.kill();p.wait()
            for fd in fds:os.close(fd)
    (out/'native.log').write_text(stdout+stderr)
    assert host.returncode==0 and sim.returncode==0,(stdout,stderr,(out/'rtl.log').read_text())
    assert 'code=1 blocks=400 outputs=25344 verified=25344' in stdout,stdout
    audit=audit_trace(out/'shared-y.txt',data['gold'],out/'data/reference.f32')
    timing=audit_timing((out/'rtl.log').read_text())
    save(out/'report.json',dict(status='PASS_DMA_C_FIRMWARE_RTL',audit=audit,timing=timing,cpu_executed=False,official_sram=False,
        firmware_sources={name:sha(firmware/name) for name in ['task_test.c','shared_task.c','real_io.c']},
        native_summary=stdout.strip()))
    print(stdout.strip());print('PASS DMA_FIRMWARE actual_shared_readback=25344 bit_mismatches=0')

if __name__=='__main__':main()
