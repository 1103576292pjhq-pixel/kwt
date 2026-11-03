`timescale 1ns/1ps
`include "kwt_control_config.vh"
module tb_task_ctrl;
reg  clk = 0;
reg  rst_n = 0;
reg  load_begin_valid = 0;
wire  load_begin_ready;
reg [`KWT_TASK_ID_WIDTH-1:0] load_begin_task_id = 0;
reg [`KWT_LAYER_ID_WIDTH-1:0] load_begin_layer_id = 0;
reg  load_start_valid = 0;
wire  load_start_ready;
reg  load_session_valid = 0;
reg [`KWT_TASK_ID_WIDTH-1:0] load_session_task_id = 0;
reg [`KWT_LAYER_ID_WIDTH-1:0] load_session_layer_id = 0;
reg  load_x_ready = 0;
reg [`KWT_W_SLOT_COUNT*`KWT_SLOT_STATE_WIDTH-1:0] load_slot_state = 0;
reg [`KWT_W_SLOT_COUNT*`KWT_TILE_ID_WIDTH-1:0] load_slot_tile = 0;
reg  load_command_empty = 0;
reg  load_fault = 0;
reg [`KWT_ERROR_CODE_WIDTH-1:0] load_error_code = 0;
wire  load_activate_valid;
reg  load_activate_ready = 0;
wire  load_activate_slot;
wire  load_release_valid;
reg  load_release_ready = 0;
wire  load_release_slot;
wire  feeder_start_valid;
reg  feeder_start_ready = 0;
wire [`KWT_ROW_GROUP_WIDTH-1:0] feeder_start_row_group;
wire  feeder_start_w_slot;
reg  feeder_busy = 0;
reg  feeder_done = 0;
reg  feeder_fault = 0;
wire  core_start_valid;
reg  core_start_ready = 0;
wire [`KWT_ROW_MASK_WIDTH-1:0] core_start_row_mask;
wire  core_start_is_final_block;
reg  core_busy = 0;
reg  core_block_done = 0;
wire  result_begin_valid;
reg  result_begin_ready = 0;
wire [`KWT_TASK_ID_WIDTH-1:0] result_begin_task_id;
wire  result_alloc_valid;
reg  result_alloc_ready = 0;
wire [`KWT_TASK_ID_WIDTH-1:0] result_alloc_task_id;
wire [`KWT_RESULT_ROW_WIDTH-1:0] result_alloc_row;
wire [`KWT_CMD_TILE_WIDTH-1:0] result_alloc_tile;
wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_alloc_count;
wire  result_alloc_final;
wire  result_publish_valid;
reg  result_publish_ready = 0;
reg [`KWT_RESULT_BLOCK_COUNT-1:0] result_owned = 0;
reg  result_response_empty = 0;
reg  result_compute_done = 0;
reg  result_fault = 0;
reg [`KWT_ERROR_CODE_WIDTH-1:0] result_error_code = 0;
reg  input_fifo_empty = 0;
reg  transport_empty = 0;
reg  abort_req = 0;
wire  result_abort_req;
reg  result_abort_done = 0;
wire  abort_pending;
wire  abort_done;
wire  worker_rst_n;
wire  session_valid;
wire [`KWT_TASK_ID_WIDTH-1:0] task_id;
wire [`KWT_LAYER_ID_WIDTH-1:0] layer_id;
wire  busy;
wire  compute_done;
wire  task_done;
wire  active_w_slot;
wire [`KWT_ROW_GROUP_WIDTH-1:0] current_row_group;
wire [`KWT_TILE_ID_WIDTH-1:0] current_tile;
wire  fault;
wire [`KWT_ERROR_CODE_WIDTH-1:0] error_code;

// 调度器外部协议模型：只观察端口，按独立400块账本核对，不读DUT状态。
always #10 clk=~clk;
kwt_task_ctrl dut(.*);
integer cyc=0, allocations=0, publishes=0, fs=0, cs=0, releases=0;
integer matrix_pub=0, matrix_alloc=0, next_load=0, ft=0, ct=0, sample_id=0;
integer rstate[0:1], rslot_tile[0:1], ostate[0:1], ap=0,hp=0, fill_owner=0;
integer rstalls=0, astalls=0, ffirst=0,cfirst=0, aborts=0, faults=0, s;
reg model_run=1, auto_start=1, start_sent=0, allocated=0, fstarted=0,cstarted=0;
reg ffinished=0,cfinished=0, hold_final=1;
reg [7:0] expected_error;
task reset_all;
begin
 @(negedge clk);rst_n=0;load_begin_valid=0;load_fault=0;feeder_fault=0;result_fault=0;abort_req=0;
 repeat(3)@(negedge clk);rst_n=1;
end endtask
task new_begin;input integer id;
begin
 @(negedge clk);load_begin_valid=1;load_begin_task_id=id;load_begin_layer_id=2;
 @(posedge clk);while(!load_begin_ready)@(posedge clk);
 @(negedge clk);load_begin_valid=0;
end endtask
task cancel;
begin
 @(negedge clk);abort_req=1;transport_empty=0;input_fifo_empty=0;
 @(negedge clk);abort_req=0;
 repeat(7)begin @(negedge clk);if(!abort_pending||abort_done)$fatal(1,"FAIL TASK abort lost external wait");end
 transport_empty=1;input_fifo_empty=1;
 wait(abort_done);@(negedge clk);
 if(session_valid||fault||!worker_rst_n)$fatal(1,"FAIL TASK abort recovery");
 aborts=aborts+1;
end endtask
always @(negedge clk)if(rst_n)begin
 // 固定可重现的不同时刻ready，强制两路启动握手错拍。
 result_begin_ready=(cyc%5!=0);
 feeder_start_ready=!feeder_busy && ((cyc%7)==1 || (cyc%7)==2);
 core_start_ready=!core_busy && ((cyc%5)==3);
 load_activate_ready=(cyc%4!=0);
 load_release_ready=(cyc%6!=0);
 result_alloc_ready=(ostate[ap]==0)&&!allocated&&(cyc%9>2);
 result_publish_ready=(cyc%5!=0);
 load_start_valid=auto_start&&load_session_valid&&!start_sent;
 load_x_ready=load_session_valid&&(cyc%19!=0);
 if(model_run&&!abort_pending)begin
   if(next_load<16 && (next_load==0||start_sent) && cyc%23==2)begin
     if(rstate[0]==0)begin rstate[0]=2;rslot_tile[0]=next_load;next_load=next_load+1;end
     else if(rstate[1]==0)begin rstate[1]=2;rslot_tile[1]=next_load;next_load=next_load+1;end
   end
 end
 load_slot_state={rstate[1][1:0],rstate[0][1:0]};
 load_slot_tile={rslot_tile[1][3:0],rslot_tile[0][3:0]};
 result_owned={(ostate[1]!=0),(ostate[0]!=0)};
end
always @(posedge clk)begin
 cyc=cyc+1;
 if(cyc>250000)$fatal(1,"FAIL TASK timeout alloc=%0d pub=%0d",allocations,publishes);
 feeder_done<=0;core_block_done<=0;result_abort_done<=0;
 if(!rst_n||!worker_rst_n)begin
   load_session_valid<=0;load_session_task_id<=0;load_session_layer_id<=0;
   feeder_busy<=0;core_busy<=0;ft=0;ct=0;
   for(s=0;s<2;s=s+1)begin rstate[s]=0;rslot_tile[s]=0;end
   next_load=0;start_sent=0;
   if(!rst_n)begin
     matrix_pub=0;matrix_alloc=0;allocated=0;ap=0;hp=0;ostate[0]=0;ostate[1]=0;
     result_compute_done<=0;result_response_empty<=1;load_command_empty<=1;
     input_fifo_empty<=1;transport_empty<=1;
   end
 end else begin
   if(fault)$fatal(1,"FAIL TASK unexpected fault %h",error_code);
   if(load_begin_valid&&load_begin_ready)begin
     if(!result_begin_valid||!result_begin_ready)$fatal(1,"FAIL TASK non-atomic begin");
     load_session_valid<=1;load_session_task_id<=load_begin_task_id;load_session_layer_id<=load_begin_layer_id;
     matrix_pub=0;matrix_alloc=0;result_compute_done<=0;
     ap=0;hp=0;ostate[0]=0;ostate[1]=0;allocated=0;start_sent=0;
   end
   if(load_start_valid&&load_start_ready)start_sent=1;
   if(load_activate_valid&&load_activate_ready)begin
     if(rstate[load_activate_slot]!=2||rslot_tile[load_activate_slot]!=matrix_pub/25)
       $fatal(1,"FAIL TASK activate wrong tile");
     if(rstate[!load_activate_slot]==3)$fatal(1,"FAIL TASK two active slots");
     rstate[load_activate_slot]=3;
   end
   if(result_alloc_valid&&!result_alloc_ready)astalls=astalls+1;
   if(result_alloc_valid&&result_alloc_ready)begin
     if(allocated||ostate[ap]!=0)$fatal(1,"FAIL TASK result allocation owner");
     if(result_alloc_task_id!==load_session_task_id||result_alloc_row!==(matrix_alloc%25)*4||
       result_alloc_tile!==matrix_alloc/25||result_alloc_count!==((matrix_alloc%25==24)?48:64)||
       result_alloc_final!==(matrix_alloc==399))$fatal(1,"FAIL TASK descriptor block %0d",matrix_alloc);
     fill_owner=ap;ostate[ap]=1;ap=1-ap;allocated=1;
     sample_id=matrix_alloc;matrix_alloc=matrix_alloc+1;allocations=allocations+1;
     fstarted=0;cstarted=0;ffinished=0;cfinished=0;
   end
   if(feeder_start_valid&&feeder_start_ready)begin
     if(!allocated||fstarted||feeder_start_row_group!==sample_id%25||rstate[feeder_start_w_slot]!=3)
       $fatal(1,"FAIL TASK feeder duplicate/identity");
     fstarted=1;fs=fs+1;feeder_busy<=1;ft=11;
     if(!cstarted)ffirst=ffirst+1;
   end
   if(core_start_valid&&core_start_ready)begin
     if(!allocated||cstarted||core_start_row_mask!==((sample_id%25==24)?4'b0111:4'b1111)||
       core_start_is_final_block!==(sample_id==399))$fatal(1,"FAIL TASK core duplicate/metadata");
     cstarted=1;cs=cs+1;core_busy<=1;ct=29;
     if(!fstarted)cfirst=cfirst+1;
   end
   if(ft>0)begin ft=ft-1;if(ft==0)begin feeder_busy<=0;feeder_done<=1;ffinished=1;end end
   if(ct>0)begin ct=ct-1;if(ct==0)begin core_busy<=0;core_block_done<=1;cfinished=1;end end
   if(result_publish_valid&&result_publish_ready)begin
     if(!allocated||!ffinished||!cfinished)$fatal(1,"FAIL TASK premature publish");
     ostate[fill_owner]=2;allocated=0;matrix_pub=matrix_pub+1;publishes=publishes+1;
     if(matrix_pub==400)result_compute_done<=1;
   end
   if(load_release_valid&&load_release_ready)begin
     if(rstate[load_release_slot]!=3 || matrix_pub%25!=0 || matrix_pub/25!=rslot_tile[load_release_slot]+1)
       $fatal(1,"FAIL TASK early/wrong W release");
     rstate[load_release_slot]=0;releases=releases+1;
   end
   // 模拟慢CPU。最终块刻意保留，检查compute_done不会被当成task_done。
   if(ostate[hp]==2 && cyc%73==0 && !(hold_final && matrix_pub==400))begin
     ostate[hp]=0;hp=1-hp;
   end
 end
 if(result_abort_req)begin
   result_abort_done<=1;result_compute_done<=0;ostate[0]=0;ostate[1]=0;
   result_response_empty<=1;allocated=0;
 end
end
initial begin
 reset_all;new_begin(32'h10203040);
 wait(publishes==400);repeat(15)begin @(negedge clk);if(task_done)$fatal(1,"FAIL TASK task_done before ACK");end
 if(!compute_done)$fatal(1,"FAIL TASK missing compute_done");
 hold_final=0;wait(result_owned==0);
 @(negedge clk);transport_empty=0;load_command_empty=0;input_fifo_empty=0;
 repeat(12)begin @(negedge clk);if(task_done)$fatal(1,"FAIL TASK task_done before input/transport drain");end
 transport_empty=1;load_command_empty=1;input_fifo_empty=1;
 wait(task_done);@(negedge clk);
 if(allocations!=400||fs!=400||cs!=400||releases!=16||ffirst==0||cfirst==0||astalls==0)
   $fatal(1,"FAIL TASK coverage counters");
 // 新BEGIN允许装载q中本来有BEGIN，不以command_empty形成死锁。
 load_command_empty=0;auto_start=0;new_begin(32'h20304050);
 if(task_id!==32'h20304050||task_done)$fatal(1,"FAIL TASK new session identity");
 load_command_empty=1;cancel;
 // 子模块错误必须锁存，源错误消失也不能恢复旧任务。
 reset_all;auto_start=0;new_begin(32'h30405060);
 @(negedge clk);load_fault=1;load_error_code=8'h14;
 @(negedge clk);load_fault=0;
 repeat(3)@(negedge clk);
 if(!fault||error_code!==8'h14||worker_rst_n)$fatal(1,"FAIL TASK error not latched");
 faults=faults+1;cancel;
 reset_all;new_begin(32'h40506070);
 @(negedge clk);feeder_fault=1;
 @(negedge clk);feeder_fault=0;
 repeat(3)@(negedge clk);
 if(!fault||error_code!==8'h31)$fatal(1,"FAIL TASK feeder error");
 faults=faults+1;cancel;
 if(aborts!=3||faults!=2)$fatal(1,"FAIL TASK fault/abort coverage");
 $display("PASS CONTROL_TASK cycles=%0d blocks=%0d feeder_starts=%0d core_starts=%0d releases=%0d feeder_first=%0d core_first=%0d allocation_stalls=%0d aborts=%0d faults=%0d",cyc,publishes,fs,cs,releases,ffirst,cfirst,astalls,aborts,faults);
 $finish;
end

endmodule
