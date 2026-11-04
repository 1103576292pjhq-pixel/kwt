"""Full generated server TB wiring with a CPU bus BFM, independent SRAM models."""
from pathlib import Path
import json
import subprocess
import shutil
import sys

HERE=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(HERE))
from source_fixture import fixture
from prepare_soc import BUS
from server_wiring import prepare_wiring
from throughput_tools import add_profile_wiring,audit_profile
from timing_tools import audit_timing
from real_tools import audit_trace,sha,save

def testbench():
    text='''`timescale 1ns/1ps
module tb_top;
reg clk=0;
always #2 clk=~clk;
reg rst_n;
'''
    for prefix in ['sysper_icb','sysmem_icb']:
        for name in BUS:
            driven=name not in ['cmd_ready','rsp_valid','rsp_rdata','rsp_err']
            width='[31:0] ' if name in ['cmd_addr','cmd_wdata','rsp_rdata'] else ('[3:0] ' if name=='cmd_wmask' else '')
            text+=('reg ' if driven else 'wire ')+width+prefix+'_'+name+('=0;' if driven else ';')+'\n'
    ports=['.kwt_bus_clk(clk)','.kwt_bus_rst_n(rst_n)']
    for prefix in ['sysper_icb','sysmem_icb']:
        ports+=['.'+prefix+'_'+name+'('+prefix+'_'+name+')' for name in BUS]
    text+='kwt_shared_soc_top u_e203_soc_top(\n'+',\n'.join(ports)+'\n);\n'
    text+='''
initial begin rst_n=0;#120 rst_n <=1;end
initial begin #40000000;$fatal(1,"Generated DMA wiring timeout");end
reg [31:0] gold[0:25343];reg [4095:0] folder;
reg [31:0] value;integer i,polls;
'''
    for task,prefix in [('cfg','sysper_icb'),('ram','sysmem_icb')]:
        text+='''
task TASK(input [31:0] address,input rd,input [31:0] data,output [31:0] result);
begin
 @(negedge clk);PREFIX_cmd_valid=1;PREFIX_cmd_read=rd;PREFIX_cmd_addr=address;
 PREFIX_cmd_wdata=data;PREFIX_cmd_wmask=15;
 @(posedge clk);while(!PREFIX_cmd_ready)@(posedge clk);
 @(negedge clk);PREFIX_cmd_valid=0;
 while(!PREFIX_rsp_valid)@(negedge clk);
 if(PREFIX_rsp_err)$fatal(1,"Generated wiring bus error address=%h",address);
 result=PREFIX_rsp_rdata;PREFIX_rsp_ready=1;
 @(negedge clk);PREFIX_rsp_ready=0;
end endtask
'''.replace('TASK',task).replace('PREFIX',prefix)
    text+='''
initial begin
 if(!$value$plusargs("real_data=%s",folder))$fatal(1,"Missing test data");
 $readmemh({folder,"/gold.hex"},gold);
 wait(rst_n);repeat(4)@(negedge clk);
 for(i=0;i<25344;i=i+1)ram(32'ha0020000+4*i,0,32'hdeadbeef,value);
 ram(32'ha001fffc,0,32'h13579bdf,value);ram(32'ha0038c00,0,32'h2468ace0,value);
 cfg(32'h11000000,1,0,value);if(value!==32'h4b444d31)$fatal(1,"DMA ID missing");
 cfg(32'h11000010,0,32'ha0000000,value);cfg(32'h11000014,0,32'ha0008000,value);
 cfg(32'h11000018,0,32'ha0018000,value);cfg(32'h1100001c,0,32'ha0020000,value);
 cfg(32'h11000020,0,32'h51200010,value);cfg(32'h11000024,0,2,value);
 cfg(32'h11000008,0,1,value);
 value=1;polls=0;
 while(value[0])begin
   cfg(32'h11000004,1,0,value);polls=polls+1;
   if(polls>200000)$fatal(1,"DMA polling timeout");
 end
 if(value!==2)$fatal(1,"DMA failed status=%h",value);
 for(i=0;i<25344;i=i+1)begin
   ram(32'ha0020000+4*i,1,0,value);
   if(value!==gold[i])$fatal(1,"Generated wiring data mismatch index=%0d",i);
 end
 ram(32'ha001fffc,1,0,value);if(value!==32'h13579bdf)$fatal(1,"Low guard");
 ram(32'ha0038c00,1,0,value);if(value!==32'h2468ace0)$fatal(1,"High guard");
 $display("PASS GENERATED_DMA_SERVER_WIRING outputs=25344 bit_mismatches=0");$finish;
end
endmodule
'''
    return text

def main():
    out=Path(sys.argv[1]).resolve();out.mkdir(parents=True,exist_ok=False)
    shutil.copytree(HERE/'tests/fixtures',out/'data')
    source=fixture();tb=testbench()
    soc,tb=prepare_wiring(source,tb)
    tb=add_profile_wiring(tb).replace('u_e203_soc_top.sysmem_icb_','u_e203_soc_top.kwt_dma_shared_')
    (out/'generated_soc.v').write_text(soc,encoding='utf-8')
    (out/'generated_tb.v').write_text(tb,encoding='utf-8')
    before={str(p.relative_to(HERE)):sha(p) for p in (HERE/'rtl').rglob('*') if p.is_file()}
    sources=list((HERE/'rtl').rglob('*.v'))
    command=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),
        '-s','tb_top','-o',str(out/'sim.vvp'),*map(str,sources),str(HERE/'tests/support/sram_contract_models.v'),
        str(HERE/'tests/support/shared_model.v'),str(HERE/'real_loader.v'),str(out/'generated_soc.v'),str(out/'generated_tb.v')]
    compiled=subprocess.run(command,capture_output=True,text=True)
    (out/'compile.log').write_text(compiled.stdout+compiled.stderr);compiled.check_returncode()
    with (out/'run.log').open('w') as log:
        run=subprocess.run(['vvp',str(out/'sim.vvp'),'+real_data=data',
            '+real_trace=shared-y.txt'],stdout=log,stderr=log,cwd=out,timeout=600)
    output=(out/'run.log').read_text();print(output,flush=True);run.check_returncode()
    assert 'PASS GENERATED_DMA_SERVER_WIRING' in output
    assert output.count('REAL_SHARED_READBACK_DONE writes=25344 reads=25344')==1
    timing=audit_timing(output);profile=audit_profile(output,timing)
    gold=[int(line,16) for line in (HERE/'tests/fixtures/gold.hex').read_text().splitlines()]
    audit=audit_trace(out/'shared-y.txt',gold,HERE/'tests/fixtures/reference.f32')
    for name,want in before.items():assert sha(HERE/name)==want
    save(out/'report.json',dict(status='PASS_GENERATED_DMA_SERVER_WIRING',timing=timing,profile=profile,audit=audit,
        cpu_executed=False,official_sram=False,scope='Generated server loader mux, DMA arbitration and merged-bus monitors using CPU BFM',
        source_sha256=before))

if __name__=='__main__':main()
