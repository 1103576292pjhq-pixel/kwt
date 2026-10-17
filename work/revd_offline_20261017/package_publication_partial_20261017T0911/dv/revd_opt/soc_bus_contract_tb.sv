`timescale 1ns/1ps
// Response ownership and reset under external ICB backpressure.
module soc_bus_contract_tb;
  reg clk=0,rst_n=0;
  always #5 clk=~clk;
  reg icb_cmd_valid=0,icb_cmd_read=1,icb_rsp_ready=0;
  wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
  reg [31:0] icb_cmd_addr=32'h11000000,icb_cmd_wdata=0;
  reg [3:0] icb_cmd_wmask=15;
  wire [31:0] icb_rsp_rdata;
  revd_opt_icb #(.M(1),.N(16)) dut(.*);
  integer i;
  initial begin
    repeat(3)@(negedge clk);rst_n=1;icb_cmd_valid=1;
    @(posedge clk);@(negedge clk);
    if(!icb_rsp_valid||icb_rsp_err||icb_rsp_rdata!==1)$fatal(1,"initial response missing");
    icb_cmd_addr=32'h110000fc;icb_cmd_wdata=32'hffffffff;icb_cmd_read=0;
    for(i=0;i<20;i++)begin
      @(negedge clk);
      if(icb_cmd_ready||!icb_rsp_valid||icb_rsp_err||icb_rsp_rdata!==1)$fatal(1,"response changed or command accepted while response blocked");
    end
    icb_cmd_valid=0;icb_rsp_ready=1;@(posedge clk);@(negedge clk);
    if(icb_rsp_valid||!icb_cmd_ready)$fatal(1,"response not retired");
    icb_cmd_valid=1; // Previously held unknown write is now actually accepted.
    @(posedge clk);@(negedge clk);
    if(!icb_rsp_valid||!icb_rsp_err)$fatal(1,"unknown write accepted");
    icb_cmd_valid=0;@(posedge clk);@(negedge clk);
    icb_cmd_valid=1;icb_cmd_read=1;icb_cmd_addr=32'h11000009;
    @(posedge clk);@(negedge clk);
    if(!icb_rsp_valid||!icb_rsp_err)$fatal(1,"misaligned access accepted");
    icb_cmd_valid=0;@(posedge clk);@(negedge clk);icb_cmd_read=0;
    // Partial writes are rejected without modifying the staging registers.
    icb_cmd_valid=1;icb_cmd_addr=32'h11000008;icb_cmd_wmask=1;
    @(posedge clk);@(negedge clk);
    if(!icb_rsp_valid||!icb_rsp_err)$fatal(1,"partial write accepted");
    icb_cmd_valid=0;@(posedge clk);@(negedge clk);
    icb_cmd_valid=1;icb_cmd_read=1;icb_cmd_wmask=15;
    @(posedge clk);@(negedge clk);
    if(icb_rsp_err||icb_rsp_rdata!==0)$fatal(1,"partial write leaked");
    icb_rsp_ready=0;icb_cmd_valid=0;rst_n=0;
    repeat(3)@(negedge clk);
    if(icb_rsp_valid||!icb_cmd_ready)$fatal(1,"reset did not clear blocked response");
    rst_n=1;@(negedge clk);
    $display("REVD_SOC_BUS_PASS checks=27");$finish;
  end
  initial begin #100000;$fatal(1,"bus test timeout");end
endmodule
