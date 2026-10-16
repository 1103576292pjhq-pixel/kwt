`timescale 1ns/1ps
module tb_icb_shared_ram;
  reg clk=0,rst_n=0;
  always #5 clk=~clk;
  reg icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0;
  reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
  reg [3:0] icb_cmd_wmask=0;
  wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
  wire [31:0] icb_rsp_rdata;
  integer checks=0;
  icb_shared_ram dut(.*);
  task access(input bit rd,input [31:0] addr,data,input [3:0] mask,input bit error,input [31:0] expected);
    integer stall;
    begin
      @(negedge clk);
      if (!icb_cmd_ready) $fatal(1,"not ready before new command");
      icb_cmd_valid=1; icb_cmd_read=rd; icb_cmd_addr=addr;
      icb_cmd_wdata=data; icb_cmd_wmask=mask; icb_rsp_ready=0;
      @(posedge clk); #1;
      if (!icb_rsp_valid || icb_rsp_err!==error || icb_rsp_rdata!==(rd&&!error?expected:0))
        $fatal(1,"response mismatch addr=%h data=%h err=%b",addr,icb_rsp_rdata,icb_rsp_err);
      // Keep the command asserted while response stalls. It must execute once.
      for(stall=0;stall<5;stall=stall+1) begin
        @(posedge clk); #1;
        if(icb_cmd_ready || !icb_rsp_valid || icb_rsp_err!==error || icb_rsp_rdata!==(rd&&!error?expected:0))
          $fatal(1,"response changed or command accepted under backpressure");
      end
      @(negedge clk); icb_cmd_valid=0; icb_rsp_ready=1;
      @(posedge clk); #1;
      if(icb_rsp_valid) $fatal(1,"response not consumed");
      checks=checks+1;
    end
  endtask
  initial begin
    repeat(3) @(negedge clk);
    rst_n=1;
    access(0,32'ha0000000,32'h12345678,4'hf,0,0);
    access(1,32'ha0000000,0,0,0,32'h12345678);
    access(0,32'ha0000001,32'hffffaa00,4'h2,0,0);
    access(1,32'ha0000001,0,0,0,32'h1234aa78);
    access(0,32'ha0000000,32'hffffffff,0,0,0);
    access(1,32'ha0000000,0,0,0,32'h1234aa78);
    access(0,32'ha007fffc,32'hdeadbeef,4'hf,0,0);
    access(1,32'ha007ffff,0,0,0,32'hdeadbeef);
    access(0,32'h9ffffffc,32'hffffffff,4'hf,1,0);
    access(1,32'ha0080000,0,0,1,0);
    access(1,32'ha007fffc,0,0,0,32'hdeadbeef);
    @(negedge clk); icb_rsp_ready=0; icb_cmd_valid=1; icb_cmd_read=1; icb_cmd_addr=32'ha0000000;
    @(posedge clk); #1;
    if(!icb_rsp_valid) $fatal(1,"missing pending response");
    @(negedge clk); rst_n=0; icb_cmd_valid=0;
    #1; if(icb_rsp_valid) $fatal(1,"reset retained response");
    repeat(2) @(negedge clk);
    rst_n=1;
    access(1,32'ha0000000,0,0,0,32'h1234aa78);
    $display("ICB_SHARED_RAM_PASS checks=%0d synchronous_read byte_masks boundaries response_stalls reset_retains_memory",checks);
    $finish;
  end
  initial begin #100000; $fatal(1,"RAM test timeout"); end
endmodule
