`timescale 1ns/1ps
module tb_dma;
 parameter FORWARD_INPUT=0,FORWARD_RESULT=0,RESULT_PRIORITY=0;
 reg clk=0;always #2 clk=~clk;
 reg rst_n=0;
 reg cfg_cmd_valid=0,cfg_cmd_read=0,cfg_rsp_ready=0;
 reg [31:0] cfg_cmd_addr=0,cfg_cmd_wdata=0;
 reg [3:0] cfg_cmd_wmask=15;
 wire cfg_cmd_ready,cfg_rsp_valid,cfg_rsp_err;wire [31:0] cfg_rsp_rdata;
 wire load_done,load_mode,load_reset,load_valid,load_read,load_rsp_ready;
 wire [31:0] load_addr,load_data;wire [3:0] load_mask;
 reg host_valid=0,host_read=0,host_rsp_ready=0;
 reg [31:0] host_addr=0,host_data=0;
 wire cpu_cmd_valid=load_mode ? load_valid : host_valid;
 wire cpu_cmd_read=load_mode ? load_read : host_read;
 wire [31:0] cpu_cmd_addr=load_mode ? load_addr : host_addr;
 wire [31:0] cpu_cmd_wdata=load_mode ? load_data : host_data;
 wire [3:0] cpu_cmd_wmask=15;
 wire cpu_rsp_ready=load_mode ? load_rsp_ready : host_rsp_ready;
 wire cpu_cmd_ready,cpu_rsp_valid,cpu_rsp_err,irq;wire [31:0] cpu_rsp_rdata;
 kwt_dma_system #(.FORWARD_INPUT(FORWARD_INPUT),.FORWARD_RESULT(FORWARD_RESULT),.RESULT_PRIORITY(RESULT_PRIORITY)) dut(.*);
 kwt_real_loader loader(.clk(clk),.done(load_done),.mode(load_mode),.reset_n(load_reset),
 .cmd_valid(load_valid),.cmd_ready(cpu_cmd_ready),.cmd_addr(load_addr),.cmd_read(load_read),
 .cmd_wdata(load_data),.cmd_wmask(load_mask),.rsp_valid(cpu_rsp_valid),.rsp_ready(load_rsp_ready),
 .rsp_err(cpu_rsp_err),.rsp_rdata(cpu_rsp_rdata));
 reg [31:0] gold[0:25343],x[0:6335],w[0:16383],bias[0:255];
 reg [4095:0] folder;
 integer tick=0,start_tick=-1,end_tick=-1,start_dma_tick=-1,load_end_tick=-1;
 integer writes=0,loads=0,poisons=0,reads=0,i,guard,idx,scenario=0,repeat_tasks=1,task_number=0,stress=0,contended_reads=0;
 reg [25343:0] written=0;
 reg pending=0,pending_read;reg [31:0] pending_addr,pending_data;reg [3:0] pending_mask;
 reg [31:0] value;
 integer core_busy_cycles=0,operand_stalls=0,result_space_stalls=0,tile_wait_cycles=0;
 reg old_stall=0;reg [68:0] held;
 // Observe actual requests/responses at the shared SRAM ICB boundary.
 always @(posedge clk)begin
   tick=tick+1;
   if(tick>6000000)$fatal(1,"DMA watchdog lstate=%0d rstate=%0d words=%0d blocks=%0d error=%h",
       dut.u_accelerator.u_dma.lstate,dut.u_accelerator.u_dma.rstate,dut.u_accelerator.output_words,dut.u_accelerator.blocks,dut.u_accelerator.error);
   if(!rst_n)begin pending=0;old_stall=0;end
   else begin
     if(dut.u_accelerator.busy && scenario==0 && end_tick<0)begin
       if(dut.u_accelerator.u_engine.core_busy)core_busy_cycles=core_busy_cycles+1;
       if(dut.u_accelerator.u_engine.operands_ready && !dut.u_accelerator.u_engine.operands_valid)operand_stalls=operand_stalls+1;
       if(dut.u_accelerator.u_engine.result_alloc_valid && !dut.u_accelerator.u_engine.result_alloc_ready)result_space_stalls=result_space_stalls+1;
       if(dut.u_accelerator.u_engine.u_task.state==2 && !dut.u_accelerator.u_engine.u_task.tile_available)tile_wait_cycles=tile_wait_cycles+1;
     end
     if(old_stall && (!dut.dma_cmd_valid || {dut.dma_cmd_addr,dut.dma_cmd_wdata,dut.dma_cmd_read,dut.dma_cmd_wmask}!==held))
       $fatal(1,"DMA master changed command under backpressure");
     old_stall=dut.dma_cmd_valid&&!dut.dma_cmd_ready;
     held={dut.dma_cmd_addr,dut.dma_cmd_wdata,dut.dma_cmd_read,dut.dma_cmd_wmask};
     if(start_tick<0 && cpu_cmd_valid && !cpu_cmd_read && cpu_cmd_addr==32'ha0000000)start_tick=tick;
     if(dut.ram_rsp_valid && dut.ram_rsp_ready)begin
       if(!pending)$fatal(1,"Unexpected shared response");
       if(!pending_read && pending_addr>=32'ha0020000 && pending_addr<32'ha0038c00)begin
         if(pending_data==32'hdeadbeef)poisons=poisons+1;
         else if(scenario==0)begin
           idx=(pending_addr-32'ha0020000)/4;
           if(written[idx] || pending_mask!=15 || pending_data!==gold[idx])$fatal(1,"DMA wrong/duplicate result index=%0d data=%h gold=%h",idx,pending_data,gold[idx]);
           written[idx]=1;writes=writes+1;
           if(writes==25344)end_tick=tick;
         end
       end
       if(!pending_read && ((pending_addr>=32'ha0000000 && pending_addr<32'ha0006300) ||
             (pending_addr>=32'ha0008000 && pending_addr<32'ha0018400)))begin
         loads=loads+1;if(loads==22976)load_end_tick=tick;
       end
       pending=0;
     end
     if(dut.ram_cmd_valid && dut.ram_cmd_ready)begin
       if(pending)$fatal(1,"Two shared commands outstanding");
       pending=1;pending_read=dut.ram_cmd_read;pending_addr=dut.ram_cmd_addr;
       pending_data=dut.ram_cmd_wdata;pending_mask=dut.ram_cmd_wmask;
     end
   end
 end
 task cfg(input integer offset,input rd,input[31:0] data,input expected_error,output[31:0] result);
 begin
   @(negedge clk);cfg_cmd_valid=1;cfg_cmd_read=rd;cfg_cmd_addr=32'h11000000+offset;cfg_cmd_wdata=data;
   @(posedge clk);while(!cfg_cmd_ready)@(posedge clk);
   @(negedge clk);cfg_cmd_valid=0;
   while(!cfg_rsp_valid)@(negedge clk);
   if(cfg_rsp_err!==expected_error)$fatal(1,"CSR error offset=%h data=%h got=%b want=%b x=%h w=%h b=%h y=%h valid=%b",offset,data,cfg_rsp_err,expected_error,dut.u_accelerator.x_base,dut.u_accelerator.w_base,dut.u_accelerator.b_base,dut.u_accelerator.y_base,dut.u_accelerator.u_csr.descriptor_ok);
   result=cfg_rsp_rdata;
   repeat(2)@(negedge clk);
   if(cfg_rsp_rdata!==result || !cfg_rsp_valid)$fatal(1,"CSR response unstable");
   cfg_rsp_ready=1;@(negedge clk);cfg_rsp_ready=0;
 end endtask
 task ram(input[31:0] address,input rd,input[31:0] data,output[31:0] result);
 begin
   @(negedge clk);host_valid=1;host_read=rd;host_addr=address;host_data=data;
   @(posedge clk);while(!cpu_cmd_ready)@(posedge clk);
   @(negedge clk);host_valid=0;
   while(!cpu_rsp_valid)@(negedge clk);
   if(cpu_rsp_err)$fatal(1,"Host shared error");
   result=cpu_rsp_rdata;host_rsp_ready=1;
   @(negedge clk);host_rsp_ready=0;
 end endtask
 task setup(input integer tag);
 begin
   cfg('h10,0,32'ha0000000,0,value);cfg('h14,0,32'ha0008000,0,value);
   cfg('h18,0,32'ha0018000,0,value);cfg('h1c,0,32'ha0020000,0,value);
   cfg('h20,0,tag,0,value);cfg('h24,0,2,0,value);
 end endtask
 task wait_finish;
 begin
   guard=0;
   while(!irq)begin @(negedge clk);guard=guard+1;if(guard>1500000)$fatal(1,"DMA task timeout load=%0d result=%0d words=%0d blocks=%0d error=%h",dut.u_accelerator.u_dma.lstate,dut.u_accelerator.u_dma.rstate,dut.u_accelerator.output_words,dut.u_accelerator.blocks,dut.u_accelerator.error);end
 end endtask
 task contend;
 reg [31:0] scratch;
 begin
   while(!irq)begin
     repeat(37)@(negedge clk);
     if(!irq)begin
       ram(32'ha0070000,1,0,scratch);
       if(scratch!==32'hcafebabe)$fatal(1,"CPU/DMA response routing failed");
       contended_reads=contended_reads+1;
     end
   end
 end endtask
 task exercise_cancellation;
 begin
   scenario=1;setup(32'hd0000010);cfg(8,0,1,0,value);
   repeat(30)@(negedge clk);cfg(8,0,2,0,value);wait_finish;
   cfg(4,1,0,0,value);if(value!==8)$fatal(1,"Abort failed status=%h",value);
   if(dut.dma_cmd_valid)$fatal(1,"DMA request after aborted completion");
   if(stress!=0)begin
     setup(32'hd0000011);cfg(8,0,1,0,value);
     fork
       begin
         wait(dut.ram_rsp_valid && dut.u_shared_arbiter.owner);
         force dut.ram_rsp_err=1'b1;
         @(posedge clk);@(negedge clk);release dut.ram_rsp_err;
       end
       begin wait_finish;end
     join
     cfg(4,1,0,0,value);if(value!==4)$fatal(1,"DMA bus-error status=%h",value);
     cfg('h30,1,0,0,value);if(value!==32'he2)$fatal(1,"DMA bus-error cause=%h",value);
     setup(32'hd0000012);cfg(8,0,1,0,value);
     fork
       begin
         wait(dut.u_accelerator.write_rsp_valid);
         force dut.ram_rsp_err=1'b1;
         @(posedge clk);@(negedge clk);release dut.ram_rsp_err;
       end
       begin wait_finish;end
     join
     cfg(4,1,0,0,value);if(value!==4)$fatal(1,"DMA write-error status=%h",value);
     cfg('h30,1,0,0,value);if(value!==32'he5)$fatal(1,"DMA write-error cause=%h",value);
     setup(32'hd0000013);cfg(8,0,1,0,value);
     wait(dut.u_accelerator.write_cmd_valid);
     cfg(8,0,2,0,value);wait_finish;
     cfg(4,1,0,0,value);if(value!==8)$fatal(1,"Late abort failed status=%h",value);
     setup(32'hd0000014);cfg(8,0,1,0,value);
     wait(dut.u_shared_arbiter.pending && dut.u_shared_arbiter.owner);
     @(negedge clk);rst_n=0;
     repeat(3)@(negedge clk);rst_n=1;
     cfg(4,1,0,0,value);if(value!==0)$fatal(1,"Reset status not clear");
     ram(32'ha0000000,1,0,value);if(value!==x[0])$fatal(1,"Reset lost shared data");
   end
   scenario=0;
 end endtask
 initial begin
   i=$value$plusargs("repeat_tasks=%d",repeat_tasks);
   i=$value$plusargs("stress=%d",stress);
   if(!$value$plusargs("real_data=%s",folder))$fatal(1,"Missing data");
   $readmemh({folder,"/gold.hex"},gold);$readmemh({folder,"/x.hex"},x);
   $readmemh({folder,"/w.hex"},w);$readmemh({folder,"/b.hex"},bias);
   repeat(2)@(negedge clk);rst_n=1;
   wait(load_done);
   // Invalid descriptor, misalignment and overlapping output must reject START.
   cfg(8,0,1,1,value);setup(32'hd0000001);
   cfg('h1c,0,32'ha0000000,0,value);cfg(8,0,1,1,value);
   cfg('h1c,0,32'ha007fffc,0,value);cfg(8,0,1,1,value);
   cfg('h1c,0,32'ha0020001,0,value);cfg(8,0,1,1,value);
   cfg('h1c,0,32'ha0020000,0,value);cfg('h24,0,12,1,value);
   ram(32'ha0070000,0,32'hcafebabe,value);
   for(task_number=0;task_number<repeat_tasks;task_number=task_number+1)begin
     if(task_number>0)begin
       if(stress!=0)exercise_cancellation;
       start_tick=-1;end_tick=-1;loads=0;poisons=0;writes=0;written=0;
       core_busy_cycles=0;operand_stalls=0;result_space_stalls=0;tile_wait_cycles=0;
       for(i=0;i<6336;i=i+1)ram(32'ha0000000+4*i,0,x[i],value);
       for(i=0;i<16384;i=i+1)ram(32'ha0008000+4*i,0,w[i],value);
       for(i=0;i<256;i=i+1)ram(32'ha0018000+4*i,0,bias[i],value);
     end
     for(i=0;i<25344;i=i+1)ram(32'ha0020000+4*i,0,32'hdeadbeef,value);
     ram(32'ha001fffc,0,32'h13579bdf,value);ram(32'ha0038c00,0,32'h2468ace0,value);
     setup(32'hd0000001+task_number);
     start_dma_tick=tick;cfg(8,0,1,0,value);
     cfg('h10,0,0,1,value);cfg(8,0,1,1,value);
     if(stress!=0)begin fork wait_finish;contend;join end
     else wait_finish;
     cfg(4,1,0,0,value);if(value!==2)$fatal(1,"DMA status=%h error=%h",value,dut.u_accelerator.error);
     if(writes!=25344 || loads!=22976 || poisons!=25344 || end_tick<start_dma_tick)$fatal(1,"Incomplete DMA ledger");
     cfg('h28,1,0,0,value);if(value!=25344)$fatal(1,"Wrong output count");
     cfg('h34,1,0,0,value);if(value!=400)$fatal(1,"Wrong block count");
     for(i=0;i<25344;i=i+1)begin
       ram(32'ha0020000+4*i,1,0,value);
       if(value!==gold[i])$fatal(1,"Shared readback mismatch index=%0d",i);
     end
     ram(32'ha001fffc,1,0,value);if(value!==32'h13579bdf)$fatal(1,"Low guard");
     ram(32'ha0038c00,1,0,value);if(value!==32'h2468ace0)$fatal(1,"High guard");
     $display("DMA_METRIC task=%0d input_forward=%0d result_forward=%0d full_cycles=%0d load_cycles=%0d init_config_cycles=%0d dma_to_writeback_cycles=%0d writes=%0d outputs=25344 blocks=400 period_ps=4000",
         task_number,FORWARD_INPUT,FORWARD_RESULT,end_tick-start_tick,load_end_tick-start_tick,start_dma_tick-load_end_tick,end_tick-start_dma_tick,writes);
     $display("DMA_PROFILE core_busy=%0d operand_wait=%0d result_space_wait=%0d weight_tile_wait=%0d result_priority=%0d",core_busy_cycles,operand_stalls,result_space_stalls,tile_wait_cycles,RESULT_PRIORITY);
   end
   // Abort in flight and prove descriptor can be reused after draining.
   exercise_cancellation;
   $display("PASS DMA_SYSTEM tasks=%0d bit_mismatches=0 abort=1 descriptor_checks=1 stress=%0d contended_reads=%0d",repeat_tasks,stress,contended_reads);
   $finish;
 end
endmodule
