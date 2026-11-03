import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2]
sys.path.insert(0,str(HERE))
from real_tools import prepare_data,prepare_wiring

SOURCE='''module kwt_shared_soc_top(
 input kwt_bus_clk,kwt_bus_rst_n,
 input sysmem_icb_cmd_valid,sysmem_icb_cmd_read,sysmem_icb_rsp_ready,
 input [31:0] sysmem_icb_cmd_addr,sysmem_icb_cmd_wdata,
 input [3:0] sysmem_icb_cmd_wmask,
 output sysmem_icb_cmd_ready,sysmem_icb_rsp_valid,sysmem_icb_rsp_err,
 output [31:0] sysmem_icb_rsp_rdata);
 kwt_shared_sram #(.BASE_ADDR(32'ha0000000),.SRAM_EMA(3'd2),.SRAM_EMAW(2'd0)) u_shared_sram(
 .clk(kwt_bus_clk),.rst_n(kwt_bus_rst_n),
 .icb_cmd_valid(sysmem_icb_cmd_valid),.icb_cmd_ready(sysmem_icb_cmd_ready),
 .icb_cmd_read(sysmem_icb_cmd_read),.icb_cmd_addr(sysmem_icb_cmd_addr),
 .icb_cmd_wdata(sysmem_icb_cmd_wdata),.icb_cmd_wmask(sysmem_icb_cmd_wmask),
 .icb_rsp_valid(sysmem_icb_rsp_valid),.icb_rsp_ready(sysmem_icb_rsp_ready),
 .icb_rsp_err(sysmem_icb_rsp_err),.icb_rsp_rdata(sysmem_icb_rsp_rdata));
endmodule
'''

TB='''`timescale 1ns/1ps
module tb;
reg loadclk=0,cpuclk=0;always #2 loadclk=~loadclk;always #3 cpuclk=~cpuclk;
reg cpurst=0,valid=0,ready=0;reg[31:0]addr=0;
wire done,mode,lrst,lv,ldir,lready,lc_ready,lrv,lerr;
wire[31:0]la,ld,lrdata;wire[3:0]lm;
wire cmd_ready,rsp_valid,rsp_err;wire[31:0]rsp_data;
kwt_real_loader loader(loadclk,done,mode,lrst,lv,lc_ready,la,ldir,ld,lm,lrv,lready,lerr,lrdata);
kwt_real_soc_top dut(
 .kwt_load_clk(loadclk),.kwt_load_mode(mode),.kwt_load_rst_n(lrst),
 .kwt_load_cmd_valid(lv),.kwt_load_cmd_read(ldir),.kwt_load_cmd_addr(la),
 .kwt_load_cmd_wdata(ld),.kwt_load_cmd_wmask(lm),.kwt_load_cmd_ready(lc_ready),
 .kwt_load_rsp_valid(lrv),.kwt_load_rsp_ready(lready),.kwt_load_rsp_err(lerr),.kwt_load_rsp_rdata(lrdata),
 .kwt_bus_clk(cpuclk),.kwt_bus_rst_n(cpurst),.sysmem_icb_cmd_valid(valid),.sysmem_icb_cmd_read(1'b1),
 .sysmem_icb_cmd_addr(addr),.sysmem_icb_cmd_wdata(32'b0),.sysmem_icb_cmd_wmask(4'hf),
 .sysmem_icb_cmd_ready(cmd_ready),.sysmem_icb_rsp_valid(rsp_valid),.sysmem_icb_rsp_ready(ready),
 .sysmem_icb_rsp_err(rsp_err),.sysmem_icb_rsp_rdata(rsp_data));
task check_word(input[31:0]a,input[31:0]v);
begin
 @(negedge cpuclk);valid=1;addr=a;
 @(posedge cpuclk);while(cmd_ready!==1'b1)@(posedge cpuclk);
 @(negedge cpuclk);valid=0;
 while(rsp_valid!==1'b1)@(negedge cpuclk);
 if(rsp_err!==0||rsp_data!==v)$fatal(1,"MUX handoff data mismatch addr=%h actual=%h expected=%h",a,rsp_data,v);
 ready=1;@(negedge cpuclk);ready=0;
end endtask
initial begin
 wait(done);repeat(4)@(negedge cpuclk);cpurst=1;
 CHECKS
 $display("MUX_HANDOFF_PASS different_clocks=1 reset_retains_data=1");$finish;
end
initial begin #10000000;$fatal(1,"MUX timeout");end
endmodule
'''


class MuxTest(unittest.TestCase):
    def test_generated_mux_loader_to_cpu_with_clock_change_and_reset(self):
        with tempfile.TemporaryDirectory(prefix='real-mux-') as temp:
            root=Path(temp)
            d=prepare_data(ROOT/'verification/real12-20261102-02/fixtures',root/'data',json.loads((HERE/'fixture-identity.json').read_text()))
            top,_=prepare_wiring(SOURCE,'module tb_top();\nreg clk;\nreg rst_n;\n#120 rst_n <=1;\n#40000000\nkwt_shared_soc_top u_e203_soc_top();\nendmodule')
            (root/'top.v').write_text(top)
            checks=[]
            for base,values in [(0xa0000000,d['x']),(0xa0008000,d['w']),(0xa0018000,d['b']),(0xa0040000,d['gold'])]:
                for index in [0,1,len(values)-1]:
                    checks.append("check_word(32'h%08x,32'h%08x);"%(base+4*index,values[index]))
            (root/'tb.v').write_text(TB.replace('CHECKS','\n'.join(checks)))
            spec=importlib.util.spec_from_file_location('shared_contract',ROOT/'integration/e203/shared_sram/tests/test_shared.py')
            mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
            (root/'model.v').write_text(mod.CONTRACT)
            sources=list((ROOT/'integration/e203/shared_sram/rtl').glob('*.v'))
            compiled=subprocess.run(['iverilog','-g2012','-s','tb','-o',str(root/'sim'),*map(str,sources),
                str(root/'model.v'),str(HERE/'real_loader.v'),str(root/'top.v'),str(root/'tb.v')],capture_output=True,text=True)
            self.assertEqual(compiled.returncode,0,compiled.stderr)
            run=subprocess.run(['vvp',str(root/'sim'),'+real_data=data'],cwd=root,capture_output=True,text=True,timeout=120)
            self.assertEqual(run.returncode,0,run.stdout+run.stderr)
            self.assertIn('MUX_HANDOFF_PASS different_clocks=1 reset_retains_data=1',run.stdout)


if __name__=='__main__':unittest.main()
