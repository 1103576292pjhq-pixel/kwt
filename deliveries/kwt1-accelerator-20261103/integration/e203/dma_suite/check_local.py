"""Exercise exact suite loader/probes/generated wiring, with CPU BFM only."""
from pathlib import Path
import json,sys,subprocess
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
sys.path.insert(0,str(ROOT/'integration/e203/dma_server/tests'))
from check_generated import testbench
from source_fixture import fixture
from run_suite import wire
from suite_tools import prepare_suite
from real_tools import audit_trace,save
from timing_tools import audit_timing
from throughput_tools import audit_profile

out=Path(sys.argv[1]).resolve();out.mkdir(parents=True,exist_ok=False)
fixtures=ROOT/'verification/real12-20261102-02/fixtures'
data=prepare_suite(fixtures,out/'data',json.loads((HERE/'suite-identity.json').read_text()))
tb=testbench().replace("cfg(32'h11000020,0,32'h51200010,value);cfg(32'h11000024,0,2,value);",
    "cfg(32'h11000020,0,32'h51200010,value);ram(32'ha001f000,1,0,value);cfg(32'h11000024,0,value,value);")
source='/* Copyright. Licensed under Apache (the "License");\n*/\n'+fixture()
soc,tb=wire(source,tb)
(out/'soc.v').write_text(soc);(out/'tb.v').write_text(tb)
support=ROOT/'integration/e203/dma_server/tests/support'
sources=list((HERE/'rtl').rglob('*.v'))
cmd=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),'-s','tb_top','-o',str(out/'sim.vvp'),
     *map(str,sources),str(support/'sram_contract_models.v'),str(support/'shared_model.v'),str(HERE/'real_loader.v'),
     str(HERE/'suite_metrics.v'),str(out/'soc.v'),str(out/'tb.v')]
p=subprocess.run(cmd,capture_output=True,text=True);(out/'compile.log').write_text(p.stdout+p.stderr);p.check_returncode()
results=[]
for d in data[:3]:
    case=d['case'];work=out/('case%d'%case);work.mkdir()
    print('LOCAL_TASK_START',case,flush=True)
    with (work/'run.log').open('w') as log:
        p=subprocess.run(['vvp',str(out/'sim.vvp'),'+real_data=../data/case%d'%case,'+real_trace=shared-y.txt',
                          '+layer='+str(case-1),'+activity=0'],cwd=work,stdout=log,stderr=log,timeout=1800)
    text=(work/'run.log').read_text();p.check_returncode()
    assert text.count('PASS GENERATED_DMA_SERVER_WIRING')==1
    assert text.count('CLEAR_SHARED_PASS words=48320 zero_readbacks=48320')==1
    assert text.count('CLEAR_CACHE_PASS')==1
    assert text.count('SUITE_METRICS ')==1
    timing=audit_timing(text);profile=audit_profile(text,timing)
    result=dict(case=case,timing=timing,profile=profile,audit=audit_trace(work/'shared-y.txt',d['gold'],fixtures/('case%d-ref.f32'%case)))
    results.append(result);save(work/'report.json',result)
    print('LOCAL_TASK_PASS',case,result['audit'],flush=True)
save(out/'report.json',dict(status='PASS_LOCAL_SUITE_WIRING_THREE',actual_e203=False,official_sram=False,tasks=results))
