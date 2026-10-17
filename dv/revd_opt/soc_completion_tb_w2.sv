`timescale 1ns/1ps
// Distinguish MMIO capture, core ingress acceptance and ordered retirement.
module soc_completion_tb_w2;
  reg clk=0,rst_n=0;
  always #5 clk=~clk;
  reg icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=1;
  wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
  reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
  reg [3:0] icb_cmd_wmask=15;
  wire [31:0] icb_rsp_rdata;
  revd_opt_icb_w2 #(.M(1),.N(16)) dut(.*);
  integer captures=0,accepts=0,retires=0,i,before_accepts,before_retires;
  reg [31:0] value;reg err;
  always @(posedge clk)if(rst_n)begin
    if(icb_cmd_valid&&icb_cmd_ready&&!icb_cmd_read&&icb_cmd_addr==32'h11000018&&!dut.event_valid&&!dut.fault)captures++;
    if(dut.event_valid&&dut.core_ready)accepts++;
    if(dut.core.retire_event)retires++;
  end
  task bus(input bit rd,input [7:0] addr,input [31:0] data,output [31:0] got,output bit error);
    begin
      @(negedge clk);icb_cmd_valid=1;icb_cmd_read=rd;icb_cmd_addr=32'h11000000+{24'b0,addr};icb_cmd_wdata=data;
      do @(posedge clk);while(!icb_cmd_ready);
      @(negedge clk);icb_cmd_valid=0;
      while(!icb_rsp_valid)@(negedge clk);
      got=icb_rsp_rdata;error=icb_rsp_err;@(posedge clk);@(negedge clk);
    end
  endtask
  task wr(input [7:0] addr,input [31:0] data);
    begin bus(0,addr,data,value,err);if(err)$fatal(1,"write failed %h",addr);end
  endtask
  task emit(input [3:0] op,input integer idx,input signed [47:0] data);
    begin
      wr(4,32'h10|{28'b0,op});wr(8,32'h1234);wr(12,32'(idx));
      wr(16,data[31:0]);wr(20,{16'b0,data[47:32]});wr(24,1);
    end
  endtask
  task load;
    begin
      emit(0,0,0);for(i=0;i<64;i++)emit(1,i,0);emit(2,0,0);
      for(i=0;i<1024;i++)emit(3,i,0);
      for(i=0;i<16;i++)emit(4,i,19);
      emit(5,0,0);emit(6,0,0);
      value=0;while(!(value&2))bus(1,0,0,value,err);
    end
  endtask
  task reset_dut;
    begin rst_n=0;repeat(3)@(negedge clk);rst_n=1;end
  endtask
  initial begin
    reset_dut();load();
    // An illegal core-accepted event faults the active task. Published payload
    // stays stable under the fault, and draining it cannot create success.
    emit(7,0,0);repeat(6)@(negedge clk);
    for(i=0;i<8;i++)begin
      bus(1,0,0,value,err);if((value&14)!==10)$fatal(1,"fault did not retain Y or incorrectly signaled done");
      bus(1,28,0,value,err);if(value!==0)$fatal(1,"fault changed held index");
      bus(1,32,0,value,err);if(value!==19)$fatal(1,"fault changed held payload");
    end
    for(i=0;i<16;i++)wr(44,1);
    bus(1,0,0,value,err);if((value&14)!==8)$fatal(1,"fault drain signaled success");
    reset_dut();load();for(i=0;i<15;i++)wr(44,1);
    before_accepts=accepts;before_retires=retires;
    emit(7,0,0);repeat(6)@(negedge clk);
    if(accepts!=before_accepts||retires!=before_retires||captures!=accepts+1)
      $fatal(1,"MMIO capture incorrectly attributed as core acceptance/retirement");
    bus(1,0,0,value,err);if((value&15)!==2)$fatal(1,"final capture changed old task result ownership");
    bus(1,36,0,value,err);if(value!==4)$fatal(1,"final result lost last");
    wr(44,1);repeat(8)@(negedge clk);
    bus(1,0,0,value,err);
    if((value&8)==0||accepts!=before_accepts+1||retires!=before_retires+1||captures!=accepts)
      $fatal(1,"queued invalid event not retired after final-output barrier");
    // done is a sticky old-task fact. The new fault takes precedence in C;
    // capturing a command at MMIO does not make it an old-task core event.
    $display("REVD_SOC_COMPLETION_PASS captures=%0d core_accepts=%0d retires=%0d",captures,accepts,retires);$finish;
  end
  initial begin #20000000;$fatal(1,"completion test timeout");end
endmodule
