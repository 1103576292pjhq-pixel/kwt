`timescale 1ns/1ps
// Passive observer. Counts shared ICB transactions, not physical macro accesses.
module kwt_suite_metrics;
 `define SOC tb_top.u_e203_soc_top
 `define TIM tb_top.u_timing_probe
 integer host_reads=0,host_writes=0,host_wait=0;
 integer cpu_reads=0,cpu_writes=0,dma_reads=0,dma_writes=0;
 integer cpu_wait=0,dma_wait=0,ram_wait=0,response_wait=0,cfg_ops=0;
 integer host_bytes=0,read_bytes=0,write_bytes=0;
 integer printed=0,checked=0,i;
 integer wave=0;
 function integer bytes(input [3:0] m);
   begin bytes=m[0]+m[1]+m[2]+m[3];end
 endfunction
 initial begin
   i=$value$plusargs("activity=%d",wave);
   if(wave!=0)begin
     wait(tb_top.u_real_loader.measure_enable);
     $dumpfile("activity.vcd");
     $dumpvars(0,tb_top.u_e203_soc_top);
     wait(`TIM.finished);#0.001;$dumpoff;
   end
 end
 always @(posedge tb_top.clk)begin
   if(tb_top.kwt_load_mode && tb_top.u_real_loader.measure_enable)begin
     if(tb_top.kwt_load_cmd_valid && !tb_top.kwt_load_cmd_ready)host_wait=host_wait+1;
     if(tb_top.kwt_load_cmd_valid && tb_top.kwt_load_cmd_ready)begin
       if(tb_top.kwt_load_cmd_read)host_reads=host_reads+1;
       else begin host_writes=host_writes+1;host_bytes=host_bytes+bytes(tb_top.kwt_load_cmd_wmask);end
     end
   end
 end
 always @(posedge `SOC.kwt_bus_clk)begin
   if(!tb_top.kwt_load_mode && `TIM.started && !printed)begin
     if(`SOC.sysmem_icb_cmd_valid && `SOC.sysmem_icb_cmd_ready)begin
       if(!checked)begin
         if(`SOC.u_kwt_accelerator.u_engine.u_load.session_valid!==0 ||
            `SOC.u_kwt_accelerator.u_engine.u_load.x_count!==0 ||
            `SOC.u_kwt_accelerator.u_engine.u_load.w_count!==0 ||
            `SOC.u_kwt_accelerator.u_engine.u_load.bias_count!==0 ||
            `SOC.u_kwt_accelerator.u_engine.u_results.session_valid!==0)
            $fatal(1,"CLEAR_CACHE_FAIL");
         for(i=0;i<2;i=i+1)begin
           if(`SOC.u_kwt_accelerator.u_engine.u_load.slot_state_reg[i]!==0 ||
              `SOC.u_kwt_accelerator.u_engine.u_results.state[i]!==0)$fatal(1,"CLEAR_SLOT_FAIL");
         end
         checked=1;$display("CLEAR_CACHE_PASS invalidation=1 internal_sram_physical_zero=0");
       end
       if(`SOC.sysmem_icb_cmd_read)cpu_reads=cpu_reads+1;else cpu_writes=cpu_writes+1;
     end
     if(`SOC.kwt_dma_mem_cmd_valid && `SOC.kwt_dma_mem_cmd_ready)begin
       if(`SOC.kwt_dma_mem_cmd_read)dma_reads=dma_reads+1;else dma_writes=dma_writes+1;
     end
     if(`SOC.sysmem_icb_cmd_valid && !`SOC.sysmem_icb_cmd_ready)cpu_wait=cpu_wait+1;
     if(`SOC.kwt_dma_mem_cmd_valid && !`SOC.kwt_dma_mem_cmd_ready)dma_wait=dma_wait+1;
     if(`SOC.kwt_dma_shared_cmd_valid && !`SOC.kwt_dma_shared_cmd_ready)ram_wait=ram_wait+1;
     if(`SOC.u_dma_shared_arbiter.pending && !`SOC.kwt_dma_shared_rsp_valid)response_wait=response_wait+1;
     if(`SOC.sysper_icb_cmd_valid && `SOC.sysper_icb_cmd_ready)cfg_ops=cfg_ops+1;
     if(`SOC.kwt_dma_shared_cmd_valid && `SOC.kwt_dma_shared_cmd_ready)begin
       if(`SOC.kwt_dma_shared_cmd_read)read_bytes=read_bytes+4;
       else write_bytes=write_bytes+bytes(`SOC.kwt_dma_shared_cmd_wmask);
     end
   end
   // Sample finished after the timing monitor's active-region bookkeeping.
   #0.001;
   if(`TIM.finished && !printed)begin
     printed=1;
     if(!checked)$fatal(1,"Missing cache check");
     $display("SUITE_METRICS host_reads=%0d host_writes=%0d host_bytes=%0d host_wait=%0d cpu_reads=%0d cpu_writes=%0d dma_reads=%0d dma_writes=%0d cpu_wait=%0d dma_wait=%0d ram_wait=%0d response_wait=%0d cfg_ops=%0d read_bytes=%0d write_bytes=%0d",host_reads,host_writes,host_bytes,host_wait,cpu_reads,cpu_writes,dma_reads,dma_writes,cpu_wait,dma_wait,ram_wait,response_wait,cfg_ops,read_bytes,write_bytes);
   end
 end
 `undef SOC
 `undef TIM
endmodule
