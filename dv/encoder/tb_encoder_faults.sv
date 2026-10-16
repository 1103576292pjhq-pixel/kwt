`timescale 1ns/1ps
module tb_encoder_faults;
 reg clk=0;always #5 clk=~clk;
 reg rst_n=0,req_valid=0,rsp_ready=1;reg [2:0] req_op=0;reg [31:0] req_addr=0,req_data=0;
 wire req_ready,rsp_valid,rsp_error,busy,done,job_done,fault;
 wire [31:0] rsp_data,x_count,w_count,layer_index;wire [63:0] cycles;wire [4:0] flags;
 wire trace_valid;wire [3:0] trace_stage;wire [31:0] trace_addr,trace_data;
 encoder_core #(.M(3),.D(4),.H(8)) dut(.*);
 integer checks=0,i,watchdog=0;
 always @(posedge clk)begin watchdog<=watchdog+1;if(watchdog>100000)$fatal(1,"fault test timeout");end
 task command(input [2:0] op,input [31:0] addr,value,input bit expect_error);
  begin
   @(negedge clk);req_valid=1;req_op=op;req_addr=addr;req_data=value;
   do @(posedge clk);while(!req_ready);
   @(negedge clk);req_valid=0;
   while(!rsp_valid)@(negedge clk);
   if(rsp_error!==expect_error)$fatal(1,"fault-test command error");
   @(negedge clk);checks=checks+1;
  end
 endtask
 task reset_core;
  begin
   @(negedge clk);rst_n=0;req_valid=0;rsp_ready=1;
   repeat(2)@(negedge clk);rst_n=1;
   @(negedge clk);
   if(rsp_valid||busy||done||fault||x_count||w_count)$fatal(1,"reset leaked transaction or validity");
   checks=checks+1;
  end
 endtask
 task load(input bit poison);
  begin
   command(0,0,0,0);
   for(i=0;i<12;i=i+1)command(1,i,(i==0&&poison)?32'h7f800001:0,0);
   for(i=0;i<160;i=i+1)command(2,i,0,0);
  end
 endtask
 initial begin
  reset_core();load(0);command(3,0,0,0);
  repeat(4)@(negedge clk);if(!busy)$fatal(1,"not actually computing before reset");
  reset_core();command(3,0,0,1);
  load(1);command(3,0,0,0);wait(!busy);@(negedge clk);
  if(!fault||done||!flags[4])$fatal(1,"nonfinite must be observable terminal fault");
  command(3,0,0,1);command(0,0,0,0);if(fault)$fatal(1,"BEGIN did not clear fault");
  load(0);command(3,0,0,0);wait(done);@(negedge clk);
  for(i=0;i<12;i=i+1)begin command(4,i,0,0);if(rsp_data!==0)$fatal(1,"post-fault reload output");end
  // Reset after accepting a synchronous output read but before its response.
  @(negedge clk);req_op=4;req_addr=0;req_valid=1;rsp_ready=0;
  do @(posedge clk);while(!req_ready);
  @(negedge clk);req_valid=0;rst_n=0;
  repeat(2)@(negedge clk);rst_n=1;rsp_ready=1;
  repeat(4)@(negedge clk);if(rsp_valid||done)$fatal(1,"read survived reset");checks=checks+1;
  // Reset with an unconsumed response held under backpressure.
  @(negedge clk);req_op=0;req_valid=1;rsp_ready=0;
  do @(posedge clk);while(!req_ready);
  @(negedge clk);req_valid=0;
  if(!rsp_valid)$fatal(1,"no held response before reset");
  reset_core();command(3,0,0,1);
  command(0,0,0,0);
  for(i=0;i<12;i=i+1)command(1,i,i==0?32'h7f7fffff:0,0);
  for(i=0;i<160;i=i+1)command(2,i,i==16?32'h40000000:0,0);
  command(3,0,0,0);wait(!busy);@(negedge clk);
  if(!fault||flags!=5'b00101)$fatal(1,"terminal overflow must preserve only actual IEEE flags=%h",flags);
  reset_core();
  $display("ENCODER_FAULT_RESET_PASS checks=%0d",checks);$finish;
 end
endmodule
