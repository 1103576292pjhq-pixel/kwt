import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1];ROOT=HERE.parents[2];sys.path.insert(0,str(HERE))
from suite_tools import prepare_suite

TB='''`timescale 1ns/1ps
module tb;
reg freeclk=0;always #2 freeclk=~freeclk;
wire first,done,mode,reset_n,valid,rd,ready;wire[31:0]addr,wdata;wire[3:0]mask;
wire cpuclk=done?freeclk:1'b0;
wire clk=first?freeclk:cpuclk;
reg[3:0]request=0;reg rv=0;wire cr=!rv;
integer writes=0,cases=0;
kwt_suite_loader #(.NUM_TASKS(2),.FIRST_CASE(3)) dut(clk,request,first,done,mode,reset_n,valid,cr,addr,rd,wdata,mask,rv,ready,1'b0,32'b0);
always @(posedge clk)begin
 if(!reset_n)rv<=0;
 else begin
   if(rv&&ready)rv<=0;
   if(valid&&cr)begin
     rv<=1;writes=writes+1;
     if(mask!==15||rd!==0)$fatal(1,"LOADER bad transfer");
     if(addr==32'ha0000000 && wdata!==(cases==0?FIRST_X:SECOND_X))$fatal(1,"LOADER stale input");
     if(addr==32'ha001f000 && wdata!==(cases+2))$fatal(1,"LOADER wrong layer");
     if(addr==32'ha001f008)begin
       if(wdata!==(cases+1))$fatal(1,"LOADER wrong ready sequence");
       cases=cases+1;
     end
   end
 end
end
always @(negedge clk)if(done&&mode&&!reset_n)$fatal(1,"LOADER runtime reset");
initial begin
 wait(done);repeat(4)@(negedge cpuclk);request=2;
 wait(cases==2);wait(!mode);repeat(3)@(negedge cpuclk);
 if(writes!=96646)$fatal(1,"LOADER write count");
 $display("LOADER_GATED_CLOCK_HANDOFF_PASS tasks=2 writes=96646 runtime_resets=0");$finish;
end
initial begin #10000000;$fatal(1,"LOADER startup clock/reset deadlock");end
endmodule
'''


class LoaderTest(unittest.TestCase):
    def test_cpu_clock_gated_until_initial_done_and_runtime_reload(self):
        with tempfile.TemporaryDirectory(prefix='kwt-suite-loader-') as temp:
            root=Path(temp)
            data=prepare_suite(ROOT/'verification/real12-20261102-02/fixtures',root/'data',json.loads((HERE/'fixture-identity.json').read_text()))
            text=TB.replace('FIRST_X',"32'h%08x"%data[2]['x'][0]).replace('SECOND_X',"32'h%08x"%data[3]['x'][0])
            (root/'tb.v').write_text(text)
            subprocess.run(['iverilog','-g2012','-s','tb','-o',str(root/'sim'),str(HERE/'suite_loader.v'),str(root/'tb.v')],check=True,capture_output=True)
            run=subprocess.run(['vvp',str(root/'sim'),'+real_data=data'],cwd=root,capture_output=True,text=True,timeout=60)
            self.assertEqual(run.returncode,0,run.stdout+run.stderr)
            self.assertIn('LOADER_GATED_CLOCK_HANDOFF_PASS tasks=2 writes=96646 runtime_resets=0',run.stdout)


if __name__=='__main__':unittest.main()
