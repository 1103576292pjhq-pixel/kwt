`timescale 1ns/1ps
// Positive MMIO flag evidence: 64*1*1 + MAX48 overflows raw48 and sat32.
module soc_flags_tb;
  reg clk=0,rst_n=0;
  always #5 clk=~clk;
  reg icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=1;
  wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
  reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
  reg [3:0] icb_cmd_wmask=15;
  wire [31:0] icb_rsp_rdata;
  revd_opt_icb #(.M(1),.N(16)) dut(.*);
  integer i;reg [31:0] value;
  task bus(input bit rd,input [7:0] addr,input [31:0] data,output [31:0] got);
    begin
      @(negedge clk);icb_cmd_valid=1;icb_cmd_read=rd;icb_cmd_addr=32'h11000000+{24'b0,addr};icb_cmd_wdata=data;
      do @(posedge clk);while(!icb_cmd_ready);
      @(negedge clk);icb_cmd_valid=0;while(!icb_rsp_valid)@(negedge clk);
      if(icb_rsp_err)$fatal(1,"unexpected ICB error");got=icb_rsp_rdata;@(posedge clk);@(negedge clk);
    end
  endtask
  task wr(input [7:0] addr,input [31:0] data);begin bus(0,addr,data,value);end endtask
  task emit(input [3:0] op,input integer idx,input signed [47:0] data);
    begin
      wr(4,32'h10|{28'b0,op});wr(8,55);wr(12,32'(idx));wr(16,data[31:0]);wr(20,{16'b0,data[47:32]});wr(24,1);
    end
  endtask
  initial begin
    repeat(3)@(negedge clk);rst_n=1;
    emit(0,0,0);for(i=0;i<64;i++)emit(1,i,1);emit(2,0,0);
    for(i=0;i<1024;i++)emit(3,i,1);
    for(i=0;i<16;i++)emit(4,i,48'sh7fffffffffff);
    emit(5,0,0);emit(6,0,0);
    for(i=0;i<16;i++)begin
      value=0;while(!(value&2))bus(1,0,0,value);
      bus(1,28,0,value);if(value!==i)$fatal(1,"flag test index mismatch");
      bus(1,32,0,value);if(value!==32'h7fffffff)$fatal(1,"flag test saturated data mismatch");
      bus(1,36,0,value);if(value!==(i==15?7:3))$fatal(1,"positive overflow/saturated/last not preserved");
      bus(1,40,0,value);if(value!==55)$fatal(1,"flag test task mismatch");wr(44,1);
    end
    bus(1,0,0,value);if((value&12)!==4)$fatal(1,"flag test did not complete");
    $display("REVD_SOC_FLAGS_PASS outputs=16 overflow=16 saturated=16 last=1");$finish;
  end
  initial begin #10000000;$fatal(1,"flag test timeout");end
endmodule
