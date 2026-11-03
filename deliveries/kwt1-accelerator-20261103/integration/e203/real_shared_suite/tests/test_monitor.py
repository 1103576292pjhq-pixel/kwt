from pathlib import Path
import subprocess
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1]
TB='''`timescale 1ns/1ps
module tb;
reg clk=0;always #2 clk=~clk;
reg rst_n=0,cv=0,cr=1,rd=0,rv=0,rr=0,err=0;
reg [31:0]addr=0,data=0,rdata=0;reg[3:0]mask=15;wire[3:0]reload;
integer i,c,mutation=0;
kwt_suite_monitor dut(clk,rst_n,cv,cr,rd,addr,data,mask,rv,rr,err,rdata,reload);
task transfer(input bit reading,input[31:0]a,input[31:0]d);
begin
 @(negedge clk);cv=1;rd=reading;addr=a;data=d;
 @(negedge clk);cv=0;rv=1;rdata=d;rr=0;
 repeat(2)@(negedge clk);rr=1;
 @(negedge clk);rv=0;rr=0;
end endtask
initial begin
 i=$value$plusargs("mutation=%d",mutation);
 repeat(3)@(negedge clk);rst_n=1;
 if(mutation==1)transfer(0,32'ha001f100,2);
 for(c=1;c<=12;c=c+1)begin
   transfer(1,32'ha001f000,c-1);
   for(i=0;i<25344;i=i+1)transfer(0,32'ha0020000+4*i,32'h10000+i);
   for(i=0;i<25344;i=i+1)begin
     transfer(1,32'ha0020000+4*i,32'h10000+i);
     if(mutation==2 && c==2 && i==0)transfer(1,32'ha0020000,32'h10000);
   end
   transfer(1,32'ha0038c00,32'h2468ace0);
   if(c<12)begin
     transfer(0,32'ha001f100,c+1);
     if(reload!==c+1)$fatal(1,"reload not retired");
   end
 end
 $display("SUITE_MONITOR_TEST_PASS tasks=12 inter_task_resets=0");$finish;
end
endmodule
'''


class MonitorTest(unittest.TestCase):
    def test_twelve_retirement_windows_and_bad_reload_or_duplicate(self):
        with tempfile.TemporaryDirectory(prefix='kwt-suite-mon-') as temp:
            root=Path(temp);(root/'tb.v').write_text(TB)
            subprocess.run(['iverilog','-g2012','-s','tb','-o',str(root/'sim'),str(HERE/'suite_loader.v'),str(root/'tb.v')],check=True,capture_output=True)
            for mutation in [0,1,2]:
                run=subprocess.run(['vvp',str(root/'sim'),'+real_trace=trace.txt','+mutation='+str(mutation)],cwd=root,capture_output=True,text=True,timeout=60)
                if mutation==0:
                    self.assertEqual(run.returncode,0,run.stdout)
                    self.assertEqual(run.stdout.count('SUITE_TASK_DONE'),12)
                    self.assertEqual(len((root/'trace.txt').read_text().splitlines()),304128)
                else:
                    self.assertNotEqual(run.returncode,0,run.stdout)
                    self.assertIn('SUITE_TRACE '+('invalid reload sequence' if mutation==1 else 'duplicate/unwritten/unknown read'),run.stdout)


if __name__=='__main__':unittest.main()
