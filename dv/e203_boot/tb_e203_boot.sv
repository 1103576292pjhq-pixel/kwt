`timescale 1ns/1ps
`include "e203_defines.v"
module tb_e203_boot;
  reg clk=0, lfclk=0, rst_n=0;
  always #2 clk=~clk;
  always #33 lfclk=~lfclk;
  wire bus_clk, bus_rst_n;
  wire sysper_icb_cmd_valid,sysper_icb_cmd_ready,sysper_icb_cmd_read;
  wire [31:0] sysper_icb_cmd_addr,sysper_icb_cmd_wdata;
  wire [3:0] sysper_icb_cmd_wmask;
  wire sysper_icb_rsp_valid,sysper_icb_rsp_ready,sysper_icb_rsp_err;
  wire [31:0] sysper_icb_rsp_rdata;
  wire sysmem_icb_cmd_valid,sysmem_icb_cmd_ready,sysmem_icb_cmd_read;
  wire [31:0] sysmem_icb_cmd_addr,sysmem_icb_cmd_wdata;
  wire [3:0] sysmem_icb_cmd_wmask;
  wire sysmem_icb_rsp_valid,sysmem_icb_rsp_ready,sysmem_icb_rsp_err;
  wire [31:0] sysmem_icb_rsp_rdata;
  e203_cpu_shell cpu(.*);
  icb_shared_ram ram(
    .clk(bus_clk),.rst_n(bus_rst_n),
    .icb_cmd_valid(sysmem_icb_cmd_valid),.icb_cmd_ready(sysmem_icb_cmd_ready),
    .icb_cmd_addr(sysmem_icb_cmd_addr),.icb_cmd_read(sysmem_icb_cmd_read),
    .icb_cmd_wdata(sysmem_icb_cmd_wdata),.icb_cmd_wmask(sysmem_icb_cmd_wmask),
    .icb_rsp_valid(sysmem_icb_rsp_valid),.icb_rsp_ready(sysmem_icb_rsp_ready),
    .icb_rsp_rdata(sysmem_icb_rsp_rdata),.icb_rsp_err(sysmem_icb_rsp_err));

  reg per_pending=0;
  assign sysper_icb_cmd_ready=~per_pending;
  assign sysper_icb_rsp_valid=per_pending;
  assign sysper_icb_rsp_rdata=0;
  assign sysper_icb_rsp_err=1;
  always @(posedge clk or negedge rst_n)
    if (!rst_n) per_pending<=0;
    else if (sysper_icb_cmd_valid && sysper_icb_cmd_ready) per_pending<=1;
    else if (per_pending && sysper_icb_rsp_ready) per_pending<=0;

  `define ITCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_itcm_ram.u_e203_itcm_gnrl_ram.u_sirv_sim_ram
  `define DTCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_dtcm_ram.u_e203_dtcm_gnrl_ram.u_sirv_sim_ram
  reg [7:0] firmware [0:65535];
  reg [4095:0] path;
  reg [63:0] mode;
  integer firmware_bytes;
  integer i,cycles=0,writes=0,reads=0;
  reg terminal_seen=0;
  initial begin
    if (!$value$plusargs("FIRMWARE=%s",path)) $fatal(1,"missing FIRMWARE");
    if (!$value$plusargs("FIRMWARE_BYTES=%d",firmware_bytes)) $fatal(1,"missing FIRMWARE_BYTES");
    if (!$value$plusargs("MODE=%s",mode)) $fatal(1,"missing MODE");
    for (i=0;i<65536;i=i+1) firmware[i]=0;
    $readmemh(path,firmware,0,firmware_bytes-1);
    // Same byte-to-64-bit ITCM initialization used by upstream tb_top.
    // No CPU register, accelerator state or precomputed result is injected.
    for(i=0;i<`E203_ITCM_RAM_DP;i=i+1)
      `ITCM.mem_r[i]={firmware[8*i+7],firmware[8*i+6],firmware[8*i+5],firmware[8*i+4],firmware[8*i+3],firmware[8*i+2],firmware[8*i+1],firmware[8*i]};
    for(i=0;i<`E203_DTCM_RAM_DP;i=i+1) `DTCM.mem_r[i]=32'ha5a5a5a5;
    for(i=0;i<32;i=i+1) ram.mem[i]=0;
    ram.mem[8]=(mode=="trap") ? 1:0;
    #120 rst_n=1;
  end
  always @(posedge clk) begin
    if(rst_n) begin
      cycles<=cycles+1;
      if (sysmem_icb_cmd_valid && sysmem_icb_cmd_ready) begin
        if (sysmem_icb_cmd_read) reads<=reads+1;
        else begin
          writes<=writes+1;
          if (sysmem_icb_cmd_addr==32'ha0000000) terminal_seen<=1;
        end
      end
      if (terminal_seen && sysmem_icb_rsp_valid && sysmem_icb_rsp_ready) begin
        if (ram.mem[24]!==32'h10205a40 || ram.mem[25]!==32'h14)
          $fatal(1,"memory/stack result mismatch: %h %h",ram.mem[24],ram.mem[25]);
        if (mode=="normal") begin
          if(ram.mem[0]!==32'h424f4f54 || ram.mem[1]!==0) $fatal(1,"boot error status=%h code=%h",ram.mem[0],ram.mem[1]);
          $display("BOOT_NORMAL_PASS cycles=%0d cpu_mcycle=%0d writes=%0d reads=%0d",cycles,ram.mem[4],writes,reads);
        end else begin
          if(ram.mem[0]!==32'h54524150 || ram.mem[1]!==32'hffffffff || ram.mem[2]!==2 || ram.mem[3]<32'h80000000)
            $fatal(1,"trap mismatch status=%h code=%h cause=%h mepc=%h",ram.mem[0],ram.mem[1],ram.mem[2],ram.mem[3]);
          $display("BOOT_TRAP_PASS cycles=%0d cause=%0d mepc=%h writes=%0d reads=%0d",cycles,ram.mem[2],ram.mem[3],writes,reads);
        end
        $finish;
      end
      if(cycles==1000000) $fatal(1,"boot timeout status=%h code=%h",ram.mem[0],ram.mem[1]);
    end
  end
endmodule
