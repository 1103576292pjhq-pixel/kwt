`timescale 1ns/1ps
module tb_arbiter;
 reg clk=0;always #2 clk=~clk;
 reg rst_n=0,a_valid=0,b_valid=0,a_rsp_ready=0,b_rsp_ready=0;
 wire a_ready,b_ready,a_rsp_valid,b_rsp_valid,a_rsp_err,b_rsp_err;
 reg [31:0] a_addr=0,b_addr=0,a_data=0,b_data=0;
 wire [31:0] a_rsp_data,b_rsp_data;
 wire a_read=1,b_read=1;wire [3:0] a_mask=15,b_mask=15;
 wire m_valid,m_read,m_rsp_ready,idle;wire [31:0] m_addr,m_data;wire[3:0]m_mask;
 reg m_ready=0,m_rsp_valid=0,m_rsp_err=0;reg[31:0]m_rsp_data=0;
 reg pending=0;reg[31:0]tag=0;integer delay_count=0,tick=0,acount=0,bcount=0;
 reg[31:0]rng=32'h13579bdf;reg stalled=0;reg[68:0]held;
 kwt_icb_arbiter2 dut(.*);
 always @(negedge clk)begin
   rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);
   m_ready=!pending && !m_rsp_valid && rng[1:0]!=0;
 end
 always @(posedge clk)begin
   tick=tick+1;if(tick>20000)$fatal(1,"Arbiter watchdog");
   if(!rst_n)begin pending<=0;m_rsp_valid<=0;stalled<=0;end
   else begin
     if(stalled && (!m_valid || held!=={m_addr,m_data,m_read,m_mask}))$fatal(1,"Arbiter switched stalled request");
     stalled<=m_valid&&!m_ready;held<={m_addr,m_data,m_read,m_mask};
     if(m_valid&&m_ready)begin
       if(pending||m_rsp_valid)$fatal(1,"Multiple outstanding");
       pending<=1;delay_count<=1+rng[4:2];tag<=m_addr^32'hcafebabe;
     end
     if(pending)begin
       if(delay_count==0)begin pending<=0;m_rsp_valid<=1;m_rsp_data<=tag;end
       else delay_count<=delay_count-1;
     end
     if(m_rsp_valid&&m_rsp_ready)m_rsp_valid<=0;
     if(a_rsp_valid&&a_rsp_ready)acount<=acount+1;
     if(b_rsp_valid&&b_rsp_ready)bcount<=bcount+1;
   end
 end
 task source_a;
 integer n,stall;
 begin
   for(n=0;n<100;n=n+1)begin
     @(negedge clk);a_valid=1;a_addr=32'ha0000000+n*4;
     @(posedge clk);while(!a_ready)@(posedge clk);
     @(negedge clk);a_valid=0;
     while(!a_rsp_valid)@(negedge clk);
     stall=n%7;
     repeat(stall)begin @(negedge clk);if(!a_rsp_valid||a_rsp_data!==(a_addr^32'hcafebabe))$fatal(1,"A response changed");end
     if(a_rsp_err||a_rsp_data!==(a_addr^32'hcafebabe))$fatal(1,"A routed wrong");
     a_rsp_ready=1;@(negedge clk);a_rsp_ready=0;
   end
 end endtask
 task source_b;
 integer n,stall;
 begin
   for(n=0;n<100;n=n+1)begin
     @(negedge clk);b_valid=1;b_addr=32'ha0010000+n*4;
     @(posedge clk);while(!b_ready)@(posedge clk);
     @(negedge clk);b_valid=0;
     while(!b_rsp_valid)@(negedge clk);
     stall=n%5;
     repeat(stall)begin @(negedge clk);if(!b_rsp_valid||b_rsp_data!==(b_addr^32'hcafebabe))$fatal(1,"B response changed");end
     if(b_rsp_err||b_rsp_data!==(b_addr^32'hcafebabe))$fatal(1,"B routed wrong");
     b_rsp_ready=1;@(negedge clk);b_rsp_ready=0;
   end
 end endtask
 initial begin
   repeat(3)@(negedge clk);rst_n=1;
   fork source_a;source_b;join
   repeat(3)@(negedge clk);
   if(acount!=100||bcount!=100||!idle)$fatal(1,"Arbiter ledger");
   $display("PASS ARBITER randomized_backpressure=1 a=100 b=100");$finish;
 end
endmodule
