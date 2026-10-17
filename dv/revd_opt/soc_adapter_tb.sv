`timescale 1ns/1ps
// Public MMIO contract tests; no accelerator RAM writes or forced signals.
module soc_adapter_tb;
  reg clk=0,rst_n=0;
  always #5 clk=~clk;
  reg icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=1;
  wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
  reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
  reg [3:0] icb_cmd_wmask=15;
  wire [31:0] icb_rsp_rdata;
  revd_opt_icb #(.M(1),.N(16)) dut(.*);
  integer checks=0,i; reg [31:0] value; reg err;
  task bus(input bit rd,input [7:0] addr,input [31:0] data,output [31:0] got,output bit error);
    begin
      @(negedge clk);icb_cmd_valid=1;icb_cmd_read=rd;
      icb_cmd_addr=32'h11000000+{24'b0,addr};icb_cmd_wdata=data;
      do @(posedge clk);while(!icb_cmd_ready);
      @(negedge clk);icb_cmd_valid=0;
      while(!icb_rsp_valid) @(negedge clk);
      got=icb_rsp_rdata;error=icb_rsp_err;
      @(posedge clk);@(negedge clk);
    end
  endtask
  task wr(input [7:0] addr,input [31:0] data);
    begin bus(0,addr,data,value,err);if(err)$fatal(1,"unexpected write error %h",addr);end
  endtask
  task emit(input [3:0] op,input integer tile,input integer idx,input signed [47:0] data);
    begin
      wr(4,32'h10|{28'b0,op});
      wr(8,32'h1234);wr(12,{8'b0,8'(tile),16'(idx)});
      wr(16,data[31:0]);wr(20,{16'b0,data[47:32]});wr(24,1);
    end
  endtask
  initial begin
    repeat(3)@(negedge clk);rst_n=1;
    bus(1,0,0,value,err);
    if(err||value!==1)$fatal(1,"empty capacity status missing: %h",value);checks++;
    bus(1,8'hfc,0,value,err);if(!err)$fatal(1,"unknown register accepted");checks++;
    bus(0,44,1,value,err);if(!err)$fatal(1,"empty result POP accepted");checks++;
    emit(0,0,0,0);
    for(i=0;i<64;i++)emit(1,0,i,0);
    emit(2,0,0,0);
    for(i=0;i<1024;i++)emit(3,0,i,0);
    for(i=0;i<16;i++)emit(4,0,i,48'sd19);
    emit(5,0,0,0);emit(6,0,0,0);
    for(i=0;i<16;i++)begin
      value=0;while(!(value&2))bus(1,0,0,value,err);
      bus(1,28,0,value,err);if(value!==i)$fatal(1,"index %0d got %0d",i,value);
      bus(1,32,0,value,err);if(value!==19)$fatal(1,"result not computed");
      bus(1,36,0,value,err);if(value!==(i==15?4:0))$fatal(1,"last/flags wrong");
      if(i==15)begin
        // Last result holds ingress closed. A queued BEGIN may not block MMIO.
        emit(0,0,0,0);bus(1,0,0,value,err);
        if(value&1)$fatal(1,"event queue full capacity not reported");
        bus(0,24,1,value,err);if(!err)$fatal(1,"full commit did not fail immediately");checks++;
      end
      wr(44,1);checks++;
    end
    repeat(8)@(negedge clk);
    bus(1,0,0,value,err);if(value&8)$fatal(1,"next BEGIN faulted");checks++;
    // Active-task reset clears the queue, sticky completion and result ownership.
    rst_n=0;repeat(3)@(negedge clk);rst_n=1;
    bus(1,0,0,value,err);if(value!==1)$fatal(1,"reset leaked ownership");checks++;
    $display("REVD_SOC_ADAPTER_PASS checks=%0d",checks);$finish;
  end
  initial begin #10000000;$fatal(1,"adapter test timeout");end
endmodule
