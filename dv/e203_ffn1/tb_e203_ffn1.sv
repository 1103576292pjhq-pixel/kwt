`timescale 1ns/1ps
`include "e203_defines.v"
// Fixture initializes firmware and raw shared inputs only. Every accelerator
// transaction and every output copy below is executed by the real E203 CPU.
module tb_e203_ffn1;
  parameter integer M=99,N=256;
  reg clk=0,lfclk=0,rst_n=0;
  always #2 clk=~clk;
  always #33 lfclk=~lfclk;
  wire bus_clk,bus_rst_n;
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
  ffn1_icb #(.M(M),.N(N)) accelerator(
    .clk(bus_clk),.rst_n(bus_rst_n),
    .icb_cmd_valid(sysper_icb_cmd_valid),.icb_cmd_ready(sysper_icb_cmd_ready),
    .icb_cmd_addr(sysper_icb_cmd_addr),.icb_cmd_read(sysper_icb_cmd_read),
    .icb_cmd_wdata(sysper_icb_cmd_wdata),.icb_cmd_wmask(sysper_icb_cmd_wmask),
    .icb_rsp_valid(sysper_icb_rsp_valid),.icb_rsp_ready(sysper_icb_rsp_ready),
    .icb_rsp_rdata(sysper_icb_rsp_rdata),.icb_rsp_err(sysper_icb_rsp_err));
  `define ITCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_itcm_ram.u_e203_itcm_gnrl_ram.u_sirv_sim_ram
  `define DTCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_dtcm_ram.u_e203_dtcm_gnrl_ram.u_sirv_sim_ram
  `define CORE cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.u_e203_core
  reg [7:0] firmware[0:65535];
  reg [31:0] expected[0:M*N-1];
  reg [7:0] expected_flags[0:M*N-1];
  reg [4095:0] path;
  integer firmware_bytes,i,j,index,lane,outfile,flagfile;
  integer cycles=0,instructions=0,mmio_reads=0,mmio_writes=0;
  integer commits=0,starts=0,acks=0,output_writes=0,flag_writes=0;
  integer first_mmio=-1,start_cycle=-1,last_ack_cycle=-1,last_output_cycle=-1;
  reg terminal_seen=0;
  initial begin
    if(!$value$plusargs("FIRMWARE=%s",path)) $fatal(1,"missing FIRMWARE");
    if(!$value$plusargs("FIRMWARE_BYTES=%d",firmware_bytes)) $fatal(1,"missing FIRMWARE_BYTES");
    if(firmware_bytes<1 || firmware_bytes>65536) $fatal(1,"invalid firmware size");
    for(i=0;i<65536;i=i+1) firmware[i]=0;
    $readmemh(path,firmware,0,firmware_bytes-1);
    for(i=0;i<`E203_ITCM_RAM_DP;i=i+1)
      `ITCM.mem_r[i]={firmware[8*i+7],firmware[8*i+6],firmware[8*i+5],firmware[8*i+4],firmware[8*i+3],firmware[8*i+2],firmware[8*i+1],firmware[8*i]};
    for(i=0;i<`E203_DTCM_RAM_DP;i=i+1) `DTCM.mem_r[i]=32'ha5a5a5a5;
    // Only raw SRAM image is visible to firmware; expected answers stay here.
    $readmemh("shared.hex",ram.mem);
    $readmemh("expected.hex",expected);
    $readmemh("expected-flags.hex",expected_flags);
    outfile=$fopen("cpu-output.txt","w");
    flagfile=$fopen("cpu-flags.txt","w");
    if(outfile==0 || flagfile==0) $fatal(1,"output files cannot be opened");
    #120 rst_n=1;
  end
  always @(posedge clk) if(rst_n) begin
    cycles<=cycles+1;
    if(`CORE.ifu_o_valid && `CORE.ifu_o_ready) instructions<=instructions+1;
    if(cycles%1000000==0) $display("CPU_PROGRESS cycles=%0d instructions=%0d commits=%0d acks=%0d outputs=%0d",cycles,instructions,commits,acks,output_writes);
    if(sysper_icb_cmd_valid && sysper_icb_cmd_ready) begin
      if(first_mmio<0) first_mmio<=cycles;
      if(sysper_icb_cmd_read) mmio_reads<=mmio_reads+1;
      else begin
        mmio_writes<=mmio_writes+1;
        if(sysper_icb_cmd_addr==32'h11000024) commits<=commits+1;
        if(sysper_icb_cmd_addr==32'h11000008 && sysper_icb_cmd_wdata==2) begin
          starts<=starts+1; start_cycle<=cycles;
          $display("CPU_START cycle=%0d commits=%0d",cycles,commits);
        end
        if(sysper_icb_cmd_addr==32'h11000038) begin
          if(sysper_icb_cmd_wdata!==acks) $fatal(1,"CPU ACK order mismatch");
          acks<=acks+1;last_ack_cycle<=cycles;
          if(acks%10==0 || acks==M-1) $display("CPU_ROW_ACK row=%0d cycle=%0d outputs=%0d",acks,cycles,output_writes);
        end
      end
    end
    if(sysmem_icb_cmd_valid && sysmem_icb_cmd_ready && !sysmem_icb_cmd_read) begin
      if(sysmem_icb_cmd_addr>=32'ha0010000 && sysmem_icb_cmd_addr<32'ha0010000+4*M*N) begin
        index=(sysmem_icb_cmd_addr-32'ha0010000)/4;
        if(index!==output_writes || sysmem_icb_cmd_wmask!==4'hf) $fatal(1,"CPU output index/mask mismatch");
        if(sysmem_icb_cmd_wdata!==expected[index]) $fatal(1,"CPU output mismatch index=%0d got=%h expected=%h",index,sysmem_icb_cmd_wdata,expected[index]);
        $fdisplay(outfile,"%0d %08x",index,sysmem_icb_cmd_wdata);
        output_writes<=output_writes+1;last_output_cycle<=cycles;
      end
      if(sysmem_icb_cmd_addr>=32'ha0030000 && sysmem_icb_cmd_addr<32'ha0030000+M*N) begin
        index=(sysmem_icb_cmd_addr-32'ha0030000);
        lane={30'b0,sysmem_icb_cmd_addr[1:0]};
        if(index!==flag_writes || sysmem_icb_cmd_wmask!==(4'b0001<<lane)) $fatal(1,"CPU flag index/mask mismatch");
        if(((sysmem_icb_cmd_wdata>>(8*lane))&255)!=={24'b0,expected_flags[index]}) $fatal(1,"CPU flag mismatch index=%0d",index);
        // Use a 32-bit field width in both simulators. Icarus prints the full
        // expression width for %02x, whereas Verilator treats 2 as a minimum.
        $fdisplay(flagfile,"%0d %08x",index,(sysmem_icb_cmd_wdata>>(8*lane))&255);
        flag_writes<=flag_writes+1;
      end
      if(sysmem_icb_cmd_addr==32'ha0000000) terminal_seen<=1;
    end
    if(terminal_seen && sysmem_icb_rsp_valid && sysmem_icb_rsp_ready) begin
      $fclose(outfile);$fclose(flagfile);
      if(ram.mem[0]!==32'h424f4f54 || ram.mem[1]!==0)
        $fatal(1,"CPU_EXIT_FAILURE magic=%h code=%h mcause=%h mepc=%h",ram.mem[0],ram.mem[1],ram.mem[2],ram.mem[3]);
      if(output_writes!=M*N || flag_writes!=M*N || commits!=M*64+N*64+N || starts!=1 || acks!=M || instructions<100)
        $fatal(1,"CPU coverage incomplete outputs=%0d flags=%0d commits=%0d starts=%0d acks=%0d",output_writes,flag_writes,commits,starts,acks);
      // Also verify the final publicly written SRAM image, not merely a hash.
      for(j=0;j<M*N;j=j+1) begin
        if(ram.mem['h4000+j]!==expected[j]) $fatal(1,"final shared output mismatch %0d",j);
        if(((ram.mem['hc000+j/4]>>(8*(j%4)))&255)!=={24'b0,expected_flags[j]}) $fatal(1,"final shared flag mismatch %0d",j);
      end
      $display("E203_FFN1_PASS cycles=%0d instructions=%0d cpu_mcycle=%0d mmio_reads=%0d mmio_writes=%0d outputs=%0d flags=%0d commits=%0d starts=%0d acks=%0d first_mmio=%0d start_cycle=%0d last_output=%0d last_ack=%0d",cycles,instructions,ram.mem[4],mmio_reads,mmio_writes,output_writes,flag_writes,commits,starts,acks,first_mmio,start_cycle,last_output_cycle,last_ack_cycle);
      $finish;
    end
    if(cycles==30000000) $fatal(1,"CPU_TIMEOUT cycles=%0d pc=%h mailbox=%h output_count=%0d",cycles,`CORE.ifu_o_pc,ram.mem[0],output_writes);
  end
endmodule
