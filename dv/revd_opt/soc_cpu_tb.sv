`timescale 1ns/1ps
`include "e203_defines.v"
// CPU-visible SRAM contains firmware inputs and poisoned destinations only.
// Expected values remain in testbench-only arrays, never fed into the datapath.
module soc_cpu_tb;
  parameter integer M=99,N=256,TASKS=2,PM=4,READ_LATENCY=1;
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
    .clk(bus_clk),.rst_n(bus_rst_n),.icb_cmd_valid(sysmem_icb_cmd_valid),
    .icb_cmd_ready(sysmem_icb_cmd_ready),.icb_cmd_addr(sysmem_icb_cmd_addr),
    .icb_cmd_read(sysmem_icb_cmd_read),.icb_cmd_wdata(sysmem_icb_cmd_wdata),
    .icb_cmd_wmask(sysmem_icb_cmd_wmask),.icb_rsp_valid(sysmem_icb_rsp_valid),
    .icb_rsp_ready(sysmem_icb_rsp_ready),.icb_rsp_rdata(sysmem_icb_rsp_rdata),.icb_rsp_err(sysmem_icb_rsp_err));
  revd_opt_icb #(.M(M),.N(N),.PM(PM),.READ_LATENCY(READ_LATENCY)) accelerator(
    .clk(bus_clk),.rst_n(bus_rst_n),.icb_cmd_valid(sysper_icb_cmd_valid),
    .icb_cmd_ready(sysper_icb_cmd_ready),.icb_cmd_addr(sysper_icb_cmd_addr),
    .icb_cmd_read(sysper_icb_cmd_read),.icb_cmd_wdata(sysper_icb_cmd_wdata),
    .icb_cmd_wmask(sysper_icb_cmd_wmask),.icb_rsp_valid(sysper_icb_rsp_valid),
    .icb_rsp_ready(sysper_icb_rsp_ready),.icb_rsp_rdata(sysper_icb_rsp_rdata),.icb_rsp_err(sysper_icb_rsp_err));
  `define ITCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_itcm_ram.u_e203_itcm_gnrl_ram.u_sirv_sim_ram
  `define DTCM cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_dtcm_ram.u_e203_dtcm_gnrl_ram.u_sirv_sim_ram
  `define CORE cpu.u_subsys.u_e203_subsys_main.u_e203_cpu_top.u_e203_cpu.u_e203_core
  reg [7:0] firmware[0:65535];
  reg [31:0] expected[0:TASKS*M*N-1];
  reg [7:0] expected_flags[0:TASKS*M*N-1];
  reg y_seen[0:TASKS*M*N-1],f_seen[0:TASKS*M*N-1];
  reg [4095:0] path;
  integer firmware_bytes,i,j,t,index,lane,outfile,flagfile;
  integer cycles=0,instructions=0,mmio_reads=0,mmio_writes=0;
  integer commits=0,starts=0,pops=0,output_writes=0,flag_writes=0;
  integer response_outputs=0,response_flags=0;
  integer cold_start[0:TASKS-1],last_response[0:TASKS-1],task_outputs[0:TASKS-1],task_flags[0:TASKS-1];
  integer finished_tasks=0,pending_kind=0,pending_task=0;
  reg pending_terminal=0,terminal_seen=0,system_done=0;
  reg [31:0] ybase,fbase;
  initial begin
    if(!$value$plusargs("FIRMWARE=%s",path))$fatal(1,"missing FIRMWARE");
    if(!$value$plusargs("FIRMWARE_BYTES=%d",firmware_bytes))$fatal(1,"missing FIRMWARE_BYTES");
    if(firmware_bytes<1||firmware_bytes>65536)$fatal(1,"invalid firmware size");
    for(i=0;i<65536;i++)firmware[i]=0;
    $readmemh(path,firmware,0,firmware_bytes-1);
    for(i=0;i<`E203_ITCM_RAM_DP;i++)
      `ITCM.mem_r[i]={firmware[8*i+7],firmware[8*i+6],firmware[8*i+5],firmware[8*i+4],firmware[8*i+3],firmware[8*i+2],firmware[8*i+1],firmware[8*i]};
    for(i=0;i<`E203_DTCM_RAM_DP;i++)`DTCM.mem_r[i]=32'ha5a5a5a5;
    $readmemh("shared.hex",ram.mem);$readmemh("expected.hex",expected);
    $readmemh("expected-flags.hex",expected_flags);
    for(i=0;i<TASKS*M*N;i++)begin y_seen[i]=0;f_seen[i]=0;end
    for(i=0;i<TASKS;i++)begin cold_start[i]=-1;last_response[i]=-1;task_outputs[i]=0;task_flags[i]=0;end
    outfile=$fopen("cpu-output.txt","w");flagfile=$fopen("cpu-flags.txt","w");
    if(!outfile||!flagfile)$fatal(1,"output log open failure");
    #120 rst_n=1;
  end
  always @(posedge clk)if(rst_n)begin
    cycles<=cycles+1;
    if(`CORE.ifu_o_valid&&`CORE.ifu_o_ready)instructions<=instructions+1;
    if(cycles%2000000==0)$display("CPU_PROGRESS cycles=%0d instructions=%0d events=%0d pops=%0d outputs=%0d",cycles,instructions,commits,pops,output_writes);
    if(sysper_icb_cmd_valid&&sysper_icb_cmd_ready)begin
      if(sysper_icb_cmd_read)mmio_reads<=mmio_reads+1;
      else begin
        mmio_writes<=mmio_writes+1;
        if(sysper_icb_cmd_addr==32'h11000018)begin
          commits<=commits+1;
          if(accelerator.meta[3:0]==6)starts<=starts+1;
        end
        if(sysper_icb_cmd_addr==32'h1100002c)pops<=pops+1;
      end
    end
    if(sysmem_icb_cmd_valid&&sysmem_icb_cmd_ready)begin
      if(pending_kind!=0||pending_terminal)$fatal(1,"multiple outstanding shared transaction");
      pending_kind<=0;
      if(!sysmem_icb_cmd_read)begin
        if(sysmem_icb_cmd_addr==32'ha0000040)begin
          if(sysmem_icb_cmd_wdata>=1&&sysmem_icb_cmd_wdata<=TASKS)cold_start[sysmem_icb_cmd_wdata-1]<=cycles;
          else if(sysmem_icb_cmd_wdata>=32'h100&&sysmem_icb_cmd_wdata<32'h100+TASKS)begin
            t=sysmem_icb_cmd_wdata-32'h100;
            if(task_outputs[t]!=M*N||task_flags[t]!=M*N||last_response[t]<cold_start[t]||!accelerator.done)
              $fatal(1,"task ended before complete CPU writes/responses");
            finished_tasks<=finished_tasks+1;
            $display("E203_REVD_TASK task=%0d cold_start=%0d last_write_response=%0d cold_cycles=%0d core_cycles=%0d frontend_cycles=%0d effective_macs=%0d issue_count=%0d retire_count=%0d",t,cold_start[t],last_response[t],last_response[t]-cold_start[t]+1,accelerator.core.core_cycles,accelerator.core.frontend_cycles,accelerator.core.effective_macs,accelerator.core.issue_count,accelerator.core.retire_count);
          end
        end
        for(t=0;t<TASKS;t++)begin
          ybase=32'ha0010000+t*32'h40000;fbase=32'ha0030000+t*32'h40000;
          if(sysmem_icb_cmd_addr>=ybase&&sysmem_icb_cmd_addr<ybase+4*M*N)begin
            index=(sysmem_icb_cmd_addr-ybase)/4;
            if(sysmem_icb_cmd_wmask!==4'hf||y_seen[t*M*N+index])$fatal(1,"duplicate/index/output mask");
            if(sysmem_icb_cmd_wdata!==expected[t*M*N+index])$fatal(1,"CPU output mismatch task=%0d index=%0d got=%h expected=%h",t,index,sysmem_icb_cmd_wdata,expected[t*M*N+index]);
            y_seen[t*M*N+index]<=1;output_writes<=output_writes+1;task_outputs[t]<=task_outputs[t]+1;
            pending_kind<=1;pending_task<=t;
            $fdisplay(outfile,"%0d %0d %08x",t,index,sysmem_icb_cmd_wdata);
          end
          // A byte store address identifies the actual logical flag index.
          if(sysmem_icb_cmd_addr>=fbase&&sysmem_icb_cmd_addr<fbase+M*N)begin
            index=sysmem_icb_cmd_addr-fbase;lane={30'b0,sysmem_icb_cmd_addr[1:0]};
            if(sysmem_icb_cmd_wmask!==(4'b0001<<lane)||f_seen[t*M*N+index])$fatal(1,"duplicate/flag mask");
            if(((sysmem_icb_cmd_wdata>>(8*lane))&255)!=={24'b0,expected_flags[t*M*N+index]})$fatal(1,"CPU flag mismatch task=%0d index=%0d",t,index);
            f_seen[t*M*N+index]<=1;flag_writes<=flag_writes+1;task_flags[t]<=task_flags[t]+1;
            pending_kind<=2;pending_task<=t;
            $fdisplay(flagfile,"%0d %0d %08x",t,index,(sysmem_icb_cmd_wdata>>(8*lane))&255);
          end
        end
        if(sysmem_icb_cmd_addr==32'ha0000000)begin pending_terminal<=1;terminal_seen<=1;end
      end
    end
    if(sysmem_icb_rsp_valid&&sysmem_icb_rsp_ready)begin
      if(sysmem_icb_rsp_err)$fatal(1,"shared response error");
      if(pending_kind!=0)begin
        last_response[pending_task]<=cycles;
        if(pending_kind==1)response_outputs<=response_outputs+1;
        else response_flags<=response_flags+1;
        pending_kind<=0;
      end
      if(pending_terminal)begin
        pending_terminal<=0;system_done<=1;
        if(ram.mem[0]!==32'h424f4f54||ram.mem[1]!==0)$fatal(1,"CPU_EXIT_FAILURE magic=%h code=%h mcause=%h mepc=%h",ram.mem[0],ram.mem[1],ram.mem[2],ram.mem[3]);
        if(!terminal_seen||finished_tasks!=TASKS||output_writes!=TASKS*M*N||flag_writes!=TASKS*M*N||response_outputs!=output_writes||response_flags!=flag_writes||pops!=output_writes||starts!=TASKS||instructions<100)
          $fatal(1,"CPU coverage incomplete outputs=%0d flags=%0d responses=%0d/%0d pops=%0d starts=%0d tasks=%0d",output_writes,flag_writes,response_outputs,response_flags,pops,starts,finished_tasks);
        for(t=0;t<TASKS;t++)for(j=0;j<M*N;j++)begin
          if(!y_seen[t*M*N+j]||!f_seen[t*M*N+j])$fatal(1,"missing shared index");
          if(ram.mem['h4000+t*'h10000+j]!==expected[t*M*N+j])$fatal(1,"final shared data mismatch");
          if(((ram.mem['hc000+t*'h10000+j/4]>>(8*(j%4)))&255)!=={24'b0,expected_flags[t*M*N+j]})$fatal(1,"final shared flags mismatch");
        end
        $fclose(outfile);$fclose(flagfile);
        $display("E203_REVD_PASS cycles=%0d instructions=%0d cpu_mcycle=%0d mmio_reads=%0d mmio_writes=%0d outputs=%0d flags=%0d events=%0d starts=%0d pops=%0d tasks=%0d response_outputs=%0d response_flags=%0d",cycles,instructions,ram.mem[4],mmio_reads,mmio_writes,output_writes,flag_writes,commits,starts,pops,finished_tasks,response_outputs,response_flags);
        $finish;
      end
    end
    if(cycles==80000000)$fatal(1,"CPU_TIMEOUT pc=%h outputs=%0d",`CORE.ifu_o_pc,output_writes);
  end
endmodule
