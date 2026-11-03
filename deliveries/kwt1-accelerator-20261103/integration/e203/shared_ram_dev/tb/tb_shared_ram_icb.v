`timescale 1ns/1ps
module tb_shared_ram_icb;
  localparam [31:0] BASE = 32'ha0000000;
  reg clk=0;
  always #5 clk=~clk;
  reg rst_n=0;
  reg cmd_valid=0, cmd_read=1, rsp_ready=0;
  reg [31:0] cmd_addr=0, cmd_wdata=0;
  reg [3:0] cmd_wmask=0;
  wire cmd_ready, rsp_valid, rsp_err;
  wire [31:0] rsp_rdata;
  integer requests=0, responses=0, holds=0, errors=0, i;
  reg [31:0] address, pattern;

  kwt_shared_ram_sim #(.BASE_ADDR(BASE)) dut(
    .clk(clk), .rst_n(rst_n),
    .icb_cmd_valid(cmd_valid), .icb_cmd_ready(cmd_ready),
    .icb_cmd_addr(cmd_addr), .icb_cmd_read(cmd_read),
    .icb_cmd_wdata(cmd_wdata), .icb_cmd_wmask(cmd_wmask),
    .icb_rsp_valid(rsp_valid), .icb_rsp_ready(rsp_ready),
    .icb_rsp_rdata(rsp_rdata), .icb_rsp_err(rsp_err)
  );

  always @(posedge clk) if(rst_n) begin
    if(cmd_valid && cmd_ready) requests=requests+1;
    if(rsp_valid && rsp_ready) responses=responses+1;
  end
  initial begin #1000000; $fatal(1,"TIMEOUT SHARED_RAM"); end

  task transact;
    input rd;
    input [31:0] addr, data;
    input [3:0] mask;
    input [31:0] expected;
    input expected_err;
    input integer hold_cycles;
    integer n;
    begin
      @(negedge clk);
      cmd_valid=1; cmd_read=rd; cmd_addr=addr;
      cmd_wdata=data; cmd_wmask=mask; rsp_ready=0;
      @(posedge clk);
      while(!cmd_ready) @(posedge clk);
      @(negedge clk); cmd_valid=0;
      while(!rsp_valid) @(negedge clk);
      for(n=0;n<hold_cycles;n=n+1) begin
        // A second offered command must not be accepted while response is held.
        cmd_valid=1;
        if(cmd_ready !== 1'b0) $fatal(1,"accepted command during held response");
        if(rsp_rdata !== expected || rsp_err !== expected_err)
          $fatal(1,"unstable response addr=%h got=%h err=%b expected=%h err=%b",
                   addr,rsp_rdata,rsp_err,expected,expected_err);
        holds=holds+1;
        @(negedge clk);
      end
      cmd_valid=0;
      if(rsp_rdata !== expected || rsp_err !== expected_err)
        $fatal(1,"SHARED_RAM addr=%h got=%h err=%b expected=%h err=%b",
                 addr,rsp_rdata,rsp_err,expected,expected_err);
      if(expected_err) errors=errors+1;
      rsp_ready=1;
      @(posedge clk);
      @(negedge clk); rsp_ready=0;
    end
  endtask

  initial begin
    repeat(4) @(negedge clk);
    rst_n=1;
    transact(0,BASE,32'h11223344,4'hf,0,0,2);
    transact(1,BASE,0,0,32'h11223344,0,3);
    transact(0,BASE,32'haabbccdd,4'h5,0,0,1);
    transact(1,BASE,0,0,32'h11bb33dd,0,2);
    // Byte/halfword-addressed ICB transfers: lane placement is already in wdata.
    transact(0,BASE+1,32'h0000ee00,4'h2,0,0,2);
    transact(1,BASE+3,0,0,32'h11bbeedd,0,1);
    transact(0,BASE+2,32'h76540000,4'hc,0,0,2);
    transact(0,BASE,32'hffffffff,4'h0,0,0,1);
    transact(1,BASE,0,0,32'h7654eedd,0,2);
    transact(0,BASE+32'h7fffc,32'h89abcdef,4'hf,0,0,1);
    transact(1,BASE+32'h7ffff,0,0,32'h89abcdef,0,4);
    transact(0,BASE-1,32'hffffffff,4'hf,0,1,2);
    transact(1,BASE+32'h80000,0,0,0,1,3);
    transact(0,BASE+32'h80000,32'hffffffff,4'hf,0,1,1);
    transact(1,BASE,0,0,32'h7654eedd,0,1);
    transact(1,BASE+32'h7fffc,0,0,32'h89abcdef,0,2);
    // Exercise widely separated words through the public bus, including bank edges.
    for(i=0;i<64;i=i+1) begin
      address=BASE+(((i*104729)%131072)*4);
      pattern=32'h5a3c0000 ^ (i*32'h10203);
      transact(0,address,pattern,4'hf,0,0,i%4);
      transact(1,address,0,0,pattern,0,(i+1)%5);
    end
    // Hard reset drops an unretired response, but keeps an accepted RAM write.
    @(negedge clk);
    cmd_valid=1; cmd_read=0; cmd_addr=BASE+16;
    cmd_wdata=32'hfeedface; cmd_wmask=4'hf; rsp_ready=0;
    @(posedge clk); while(!cmd_ready) @(posedge clk);
    @(negedge clk); cmd_valid=0;
    while(!rsp_valid) @(negedge clk);
    rst_n=0;
    repeat(3) @(negedge clk);
    if(rsp_valid !== 0 || cmd_ready !== 0) $fatal(1,"reset protocol outputs");
    rst_n=1;
    transact(1,BASE+16,0,0,32'hfeedface,0,3);
    repeat(2) @(negedge clk);
    // One response was deliberately canceled by reset.
    if(requests !== responses+1) $fatal(1,"transaction accounting");
    $display("PASS SHARED_RAM_ICB requests=%0d responses=%0d holds=%0d errors=%0d bytes=524288 resets=1",
             requests,responses,holds,errors);
    $finish;
  end
endmodule
