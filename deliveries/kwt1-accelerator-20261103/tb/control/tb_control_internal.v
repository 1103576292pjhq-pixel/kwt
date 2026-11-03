`timescale 1ns/1ps
`include "kwt_control_config.vh"
module tb_control_internal;
reg  clk = 0;
reg  rst_n = 0;
wire  load_begin_valid;
wire  load_begin_ready;
wire [`KWT_TASK_ID_WIDTH-1:0] load_begin_task_id;
wire [`KWT_LAYER_ID_WIDTH-1:0] load_begin_layer_id;
wire  load_start_valid;
wire  load_start_ready;
wire  load_session_valid;
wire [`KWT_TASK_ID_WIDTH-1:0] load_session_task_id;
wire [`KWT_LAYER_ID_WIDTH-1:0] load_session_layer_id;
wire  load_x_ready;
wire [`KWT_W_SLOT_COUNT*`KWT_SLOT_STATE_WIDTH-1:0] load_slot_state;
wire [`KWT_W_SLOT_COUNT*`KWT_TILE_ID_WIDTH-1:0] load_slot_tile;
wire  load_command_empty;
wire  load_fault;
wire [`KWT_ERROR_CODE_WIDTH-1:0] load_error_code;
wire  load_activate_valid;
wire  load_activate_ready;
wire  load_activate_slot;
wire  load_release_valid;
wire  load_release_ready;
wire  load_release_slot;
wire  feeder_start_valid;
wire  feeder_start_ready;
wire [`KWT_ROW_GROUP_WIDTH-1:0] feeder_start_row_group;
wire  feeder_start_w_slot;
wire  feeder_busy;
wire  feeder_done;
wire  feeder_fault;
wire  core_start_valid;
wire  core_start_ready;
wire [`KWT_ROW_MASK_WIDTH-1:0] core_start_row_mask;
wire  core_start_is_final_block;
wire  core_busy;
wire  core_block_done;
wire  result_begin_valid;
wire  result_begin_ready;
wire [`KWT_TASK_ID_WIDTH-1:0] result_begin_task_id;
wire  result_alloc_valid;
wire  result_alloc_ready;
wire [`KWT_TASK_ID_WIDTH-1:0] result_alloc_task_id;
wire [`KWT_RESULT_ROW_WIDTH-1:0] result_alloc_row;
wire [`KWT_CMD_TILE_WIDTH-1:0] result_alloc_tile;
wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_alloc_count;
wire  result_alloc_final;
wire  result_publish_valid;
wire  result_publish_ready;
wire [`KWT_RESULT_BLOCK_COUNT-1:0] result_owned;
wire  result_response_empty;
wire  result_compute_done;
wire  result_fault;
wire [`KWT_ERROR_CODE_WIDTH-1:0] result_error_code;
wire  input_fifo_empty;
wire  transport_empty;
reg  abort_req = 0;
wire  result_abort_req;
wire  result_abort_done;
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
reg  load_cmd_valid = 0;
wire  load_cmd_ready;
reg [`KWT_CMD_OP_WIDTH-1:0] load_cmd_op = 0;
reg [`KWT_LAYER_ID_WIDTH-1:0] load_cmd_layer_id = 0;
reg [`KWT_TASK_ID_WIDTH-1:0] load_cmd_task_id = 0;
reg [`KWT_CMD_TILE_WIDTH-1:0] load_cmd_tile_id = 0;
reg [`KWT_CMD_INDEX_WIDTH-1:0] load_cmd_index = 0;
reg signed [`KWT_CMD_DATA_WIDTH-1:0] load_cmd_data = 0;
wire [`KWT_X_BANK_COUNT-1:0] load_x_wr_en;
wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] load_x_addr;
wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] load_x_wr_data;
wire [`KWT_W_BANK_COUNT-1:0] load_w_wr_en;
wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] load_w_addr;
wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] load_w_wr_data;
wire  load_bias_wr_en;
wire  load_bias_wr_slot;
wire [`KWT_BIAS_ADDR_WIDTH-1:0] load_bias_wr_addr;
wire signed [`KWT_BIAS_WIDTH-1:0] load_bias_wr_data;
wire  load_task_started;
wire  load_command_done;
wire  feeder_actual_start_valid;
wire  feeder_actual_start_ready;
wire [`KWT_X_BANK_COUNT-1:0] feeder_x_rd_en;
wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] feeder_x_addr;
wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] store_x_rd_data;
wire [`KWT_X_BANK_COUNT-1:0] store_x_rd_valid;
wire [`KWT_X_BANK_COUNT-1:0] store_x_access_error;
wire [`KWT_W_BANK_COUNT-1:0] feeder_w_rd_en;
wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] feeder_w_addr;
wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] store_w_rd_data;
wire [`KWT_W_BANK_COUNT-1:0] store_w_rd_valid;
wire [`KWT_W_BANK_COUNT-1:0] store_w_access_error;
wire  feeder_out_valid;
wire  feeder_out_ready;
wire [`KWT_X_GROUP_WIDTH-1:0] feeder_out_x;
wire [`KWT_W_GROUP_WIDTH-1:0] feeder_out_w;
wire  result_fill_valid;
wire  result_fill_ready;
wire [`KWT_RESULT_INDEX_WIDTH-1:0] result_fill_index;
wire signed [`KWT_Y_WIDTH-1:0] result_fill_y;
wire [`KWT_FLAGS_WIDTH-1:0] result_fill_flags;
wire  result_fill_block_last;
reg  result_cmd_valid = 0;
wire  result_cmd_ready;
reg  result_cmd_ack = 0;
reg [`KWT_TASK_ID_WIDTH-1:0] result_cmd_task_id = 0;
reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_cmd_sequence = 0;
reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_cmd_count = 0;
wire  result_rsp_valid;
reg  result_rsp_ready = 0;
wire [`KWT_RESULT_RESPONSE_WIDTH-1:0] result_rsp_data;
wire  result_rsp_error;
wire  result_block_valid;
wire  result_block_read_complete;
wire [`KWT_TASK_ID_WIDTH-1:0] result_block_task_id;
wire [`KWT_RESULT_ROW_WIDTH-1:0] result_block_row;
wire [`KWT_CMD_TILE_WIDTH-1:0] result_block_tile;
wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_block_count;
wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_block_sequence;
wire [`KWT_RESULT_COUNT_WIDTH-1:0] result_block_cursor;
wire [`KWT_RESULT_PAYLOAD_WIDTH-1:0] result_peek_data;
wire  result_abort_pending;
wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] store_x_addr;
wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] store_w_addr;
wire [`KWT_BIAS_ADDR_WIDTH-1:0] core_bias_addr;
wire signed [`KWT_BIAS_WIDTH-1:0] core_bias_data;
wire  core_actual_start_valid;
wire  core_actual_start_ready;
wire  core_in_valid;
wire  core_in_ready;
wire [`KWT_X_GROUP_WIDTH-1:0] core_in_x;
wire [`KWT_W_GROUP_WIDTH-1:0] core_in_w;
wire  core_out_valid;
wire  core_out_ready;
wire signed [`KWT_Y_WIDTH-1:0] core_out_y;
wire [`KWT_FLAGS_WIDTH-1:0] core_out_flags;
wire [`KWT_RESULT_INDEX_WIDTH-1:0] core_out_index;
wire  core_out_block_last;
kwt_task_ctrl u_kwt_task_ctrl (
    .clk(clk),
    .rst_n(rst_n),
    .load_begin_valid(load_begin_valid),
    .load_begin_ready(load_begin_ready),
    .load_begin_task_id(load_begin_task_id),
    .load_begin_layer_id(load_begin_layer_id),
    .load_start_valid(load_start_valid),
    .load_start_ready(load_start_ready),
    .load_session_valid(load_session_valid),
    .load_session_task_id(load_session_task_id),
    .load_session_layer_id(load_session_layer_id),
    .load_x_ready(load_x_ready),
    .load_slot_state(load_slot_state),
    .load_slot_tile(load_slot_tile),
    .load_command_empty(load_command_empty),
    .load_fault(load_fault),
    .load_error_code(load_error_code),
    .load_activate_valid(load_activate_valid),
    .load_activate_ready(load_activate_ready),
    .load_activate_slot(load_activate_slot),
    .load_release_valid(load_release_valid),
    .load_release_ready(load_release_ready),
    .load_release_slot(load_release_slot),
    .feeder_start_valid(feeder_start_valid),
    .feeder_start_ready(feeder_start_ready),
    .feeder_start_row_group(feeder_start_row_group),
    .feeder_start_w_slot(feeder_start_w_slot),
    .feeder_busy(feeder_busy),
    .feeder_done(feeder_done),
    .feeder_fault(feeder_fault),
    .core_start_valid(core_start_valid),
    .core_start_ready(core_start_ready),
    .core_start_row_mask(core_start_row_mask),
    .core_start_is_final_block(core_start_is_final_block),
    .core_busy(core_busy),
    .core_block_done(core_block_done),
    .result_begin_valid(result_begin_valid),
    .result_begin_ready(result_begin_ready),
    .result_begin_task_id(result_begin_task_id),
    .result_alloc_valid(result_alloc_valid),
    .result_alloc_ready(result_alloc_ready),
    .result_alloc_task_id(result_alloc_task_id),
    .result_alloc_row(result_alloc_row),
    .result_alloc_tile(result_alloc_tile),
    .result_alloc_count(result_alloc_count),
    .result_alloc_final(result_alloc_final),
    .result_publish_valid(result_publish_valid),
    .result_publish_ready(result_publish_ready),
    .result_owned(result_owned),
    .result_response_empty(result_response_empty),
    .result_compute_done(result_compute_done),
    .result_fault(result_fault),
    .result_error_code(result_error_code),
    .input_fifo_empty(input_fifo_empty),
    .transport_empty(transport_empty),
    .abort_req(abort_req),
    .result_abort_req(result_abort_req),
    .result_abort_done(result_abort_done),
    .abort_pending(abort_pending),
    .abort_done(abort_done),
    .worker_rst_n(worker_rst_n),
    .session_valid(session_valid),
    .task_id(task_id),
    .layer_id(layer_id),
    .busy(busy),
    .compute_done(compute_done),
    .task_done(task_done),
    .active_w_slot(active_w_slot),
    .current_row_group(current_row_group),
    .current_tile(current_tile),
    .fault(fault),
    .error_code(error_code)
);
kwt_load_ctrl u_kwt_load_ctrl (
    .clk(clk),
    .rst_n(worker_rst_n),
    .cmd_valid(load_cmd_valid),
    .cmd_ready(load_cmd_ready),
    .cmd_op(load_cmd_op),
    .cmd_layer_id(load_cmd_layer_id),
    .cmd_task_id(load_cmd_task_id),
    .cmd_tile_id(load_cmd_tile_id),
    .cmd_index(load_cmd_index),
    .cmd_data(load_cmd_data),
    .begin_valid(load_begin_valid),
    .begin_ready(load_begin_ready),
    .begin_task_id(load_begin_task_id),
    .begin_layer_id(load_begin_layer_id),
    .start_valid(load_start_valid),
    .start_ready(load_start_ready),
    .activate_valid(load_activate_valid),
    .activate_slot(load_activate_slot),
    .activate_ready(load_activate_ready),
    .release_valid(load_release_valid),
    .release_slot(load_release_slot),
    .release_ready(load_release_ready),
    .x_wr_en(load_x_wr_en),
    .x_addr(load_x_addr),
    .x_wr_data(load_x_wr_data),
    .w_wr_en(load_w_wr_en),
    .w_addr(load_w_addr),
    .w_wr_data(load_w_wr_data),
    .bias_wr_en(load_bias_wr_en),
    .bias_wr_slot(load_bias_wr_slot),
    .bias_wr_addr(load_bias_wr_addr),
    .bias_wr_data(load_bias_wr_data),
    .session_valid(load_session_valid),
    .session_task_id(load_session_task_id),
    .session_layer_id(load_session_layer_id),
    .task_started(load_task_started),
    .x_ready(load_x_ready),
    .slot_state(load_slot_state),
    .slot_tile(load_slot_tile),
    .command_empty(load_command_empty),
    .command_done(load_command_done),
    .fault(load_fault),
    .error_code(load_error_code)
);
kwt_operand_feeder u_kwt_operand_feeder (
    .clk(clk),
    .rst_n(worker_rst_n),
    .start_valid(feeder_actual_start_valid),
    .start_ready(feeder_actual_start_ready),
    .start_row_group(feeder_start_row_group),
    .start_w_slot(feeder_start_w_slot),
    .x_rd_en(feeder_x_rd_en),
    .x_addr(feeder_x_addr),
    .x_rd_data(store_x_rd_data),
    .x_rd_valid(store_x_rd_valid),
    .x_access_error(store_x_access_error),
    .w_rd_en(feeder_w_rd_en),
    .w_addr(feeder_w_addr),
    .w_rd_data(store_w_rd_data),
    .w_rd_valid(store_w_rd_valid),
    .w_access_error(store_w_access_error),
    .out_valid(feeder_out_valid),
    .out_ready(feeder_out_ready),
    .out_x(feeder_out_x),
    .out_w(feeder_out_w),
    .busy(feeder_busy),
    .feed_done(feeder_done),
    .fault(feeder_fault)
);
kwt_result_blocks u_kwt_result_blocks (
    .clk(clk),
    .rst_n(rst_n),
    .begin_valid(result_begin_valid),
    .begin_ready(result_begin_ready),
    .begin_task_id(result_begin_task_id),
    .alloc_valid(result_alloc_valid),
    .alloc_ready(result_alloc_ready),
    .alloc_task_id(result_alloc_task_id),
    .alloc_row(result_alloc_row),
    .alloc_tile(result_alloc_tile),
    .alloc_count(result_alloc_count),
    .alloc_final(result_alloc_final),
    .fill_valid(result_fill_valid),
    .fill_ready(result_fill_ready),
    .fill_index(result_fill_index),
    .fill_y(result_fill_y),
    .fill_flags(result_fill_flags),
    .fill_block_last(result_fill_block_last),
    .publish_valid(result_publish_valid),
    .publish_ready(result_publish_ready),
    .cmd_valid(result_cmd_valid),
    .cmd_ready(result_cmd_ready),
    .cmd_ack(result_cmd_ack),
    .cmd_task_id(result_cmd_task_id),
    .cmd_sequence(result_cmd_sequence),
    .cmd_count(result_cmd_count),
    .rsp_valid(result_rsp_valid),
    .rsp_ready(result_rsp_ready),
    .rsp_data(result_rsp_data),
    .rsp_error(result_rsp_error),
    .block_valid(result_block_valid),
    .block_read_complete(result_block_read_complete),
    .block_task_id(result_block_task_id),
    .block_row(result_block_row),
    .block_tile(result_block_tile),
    .block_count(result_block_count),
    .block_sequence(result_block_sequence),
    .block_cursor(result_block_cursor),
    .peek_data(result_peek_data),
    .abort_req(result_abort_req),
    .abort_pending(result_abort_pending),
    .abort_done(result_abort_done),
    .owned(result_owned),
    .response_empty(result_response_empty),
    .compute_done(result_compute_done),
    .fault(result_fault),
    .error_code(result_error_code)
);
kwt_storage_wrapper u_kwt_storage_wrapper (
    .clk(clk),
    .rst_n(worker_rst_n),
    .x_rd_en(feeder_x_rd_en),
    .x_wr_en(load_x_wr_en),
    .x_addr(store_x_addr),
    .x_wr_data(load_x_wr_data),
    .x_rd_data(store_x_rd_data),
    .x_rd_valid(store_x_rd_valid),
    .x_access_error(store_x_access_error),
    .w_rd_en(feeder_w_rd_en),
    .w_wr_en(load_w_wr_en),
    .w_addr(store_w_addr),
    .w_wr_data(load_w_wr_data),
    .w_rd_data(store_w_rd_data),
    .w_rd_valid(store_w_rd_valid),
    .w_access_error(store_w_access_error),
    .bias_wr_en(load_bias_wr_en),
    .bias_wr_slot(load_bias_wr_slot),
    .bias_wr_addr(load_bias_wr_addr),
    .bias_wr_data(load_bias_wr_data),
    .bias_rd_slot(active_w_slot),
    .bias_rd_addr(core_bias_addr),
    .bias_rd_data(core_bias_data)
);
dot_product_block_core u_dot_product_block_core (
    .clk(clk),
    .rst_n(worker_rst_n),
    .start_valid(core_actual_start_valid),
    .start_ready(core_actual_start_ready),
    .start_row_mask(core_start_row_mask),
    .start_is_final_block(core_start_is_final_block),
    .in_valid(core_in_valid),
    .in_ready(core_in_ready),
    .in_x(core_in_x),
    .in_w(core_in_w),
    .bias_addr(core_bias_addr),
    .bias_data(core_bias_data),
    .out_valid(core_out_valid),
    .out_ready(core_out_ready),
    .out_y(core_out_y),
    .out_flags(core_out_flags),
    .out_index(core_out_index),
    .out_block_last(core_out_block_last),
    .busy(core_busy),
    .block_done(core_block_done)
);

// 本TB是验证专用连接，不是生产顶层；官方模型仍缺失，显式使用合同模型。
always #10 clk=~clk;
integer cyc=0, reads=0, acks=0, pubs=0, allocs=0, starts=0, feed_starts=0;
integer rxwrites=0,rwwrites=0,bwrites=0, bubbles=0, full_wait=0;
integer case_id=0, item=0, ti=0, i=0,bk,idx,addr0,rr,cc,expected_index;
integer block_reads=0, block_acks=0, check_count=0, fd=0;
reg [31:0] rng=32'h70a431ef;
reg gate_feed=0,gate_fill=0,gate_core_start=0,gate_feeder_start=0;
reg cpu_enable=0,consumer_busy=0;
reg [15:0] xv[0:6335],wv[0:16383];
reg [31:0] bv[0:255],gold[0:25343];
reg [1023:0] fixture_base,fixture_name,trace_path;
reg old_stall=0;reg [31:0] held_data;reg held_error;
reg [31:0] last_response;
reg [31:0] saved_task;reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] saved_seq;
integer saved_row,saved_tile,saved_count,expected_blocks,read_position,stall_time;
assign feeder_actual_start_valid = feeder_start_valid&&gate_feeder_start;
assign core_actual_start_valid = core_start_valid&&gate_core_start;
assign feeder_start_ready=feeder_actual_start_ready&&gate_feeder_start;
assign core_start_ready=core_actual_start_ready&&gate_core_start;
assign core_in_valid=feeder_out_valid&&gate_feed;
assign core_in_x=feeder_out_x;assign core_in_w=feeder_out_w;
assign feeder_out_ready=core_in_ready&&gate_feed;
assign result_fill_valid=core_out_valid&&gate_fill;
assign core_out_ready=result_fill_ready&&gate_fill;
assign result_fill_y=core_out_y;assign result_fill_flags=core_out_flags;
assign result_fill_index=core_out_index;assign result_fill_block_last=core_out_block_last;
assign input_fifo_empty=!load_cmd_valid;
assign transport_empty=!result_cmd_valid;
genvar mb;
generate
 for(mb=0;mb<4;mb=mb+1)begin
   assign store_x_addr[mb*11+:11]=load_x_wr_en[mb]?load_x_addr[mb*11+:11]:feeder_x_addr[mb*11+:11];
 end
 for(mb=0;mb<8;mb=mb+1)begin
   assign store_w_addr[mb*8+:8]=load_w_wr_en[mb]?load_w_addr[mb*8+:8]:feeder_w_addr[mb*8+:8];
 end
endgenerate
// 地址选择由每bank的写使能完成，断言禁止把同一SP bank读写同时提交。
always @(negedge clk)begin
 rng=rng^(rng<<13);rng=rng^(rng>>17);rng=rng^(rng<<5);
 gate_feed=(rng[2:0]!=0);gate_fill=(rng[5:3]>1);
 gate_core_start=(cyc%5==1);gate_feeder_start=(cyc%7==3);
end
always @(posedge clk)begin
 cyc=cyc+1;
 if(cyc>3000000)$fatal(1,"FAIL INTERNAL timeout case=%0d pub=%0d read=%0d state=%0d",case_id,pubs,reads,current_row_group);
 if(rst_n)begin
   if(fault||load_fault||feeder_fault||result_fault)$fatal(1,"FAIL INTERNAL fault task=%h load=%h result=%h at cycle%0d",error_code,load_error_code,result_error_code,cyc);
   if((load_x_wr_en&feeder_x_rd_en)!=0||(load_w_wr_en&feeder_w_rd_en)!=0)$fatal(1,"FAIL INTERNAL SP conflict");
   if(old_stall && (!result_rsp_valid||result_rsp_data!==held_data||result_rsp_error!==held_error))$fatal(1,"FAIL INTERNAL response changed under stall");
   old_stall=result_rsp_valid&&!result_rsp_ready;held_data=result_rsp_data;held_error=result_rsp_error;
   if(result_alloc_valid&&!result_alloc_ready)full_wait=full_wait+1;
   if(core_in_ready&&!core_in_valid)bubbles=bubbles+1;
   if(result_alloc_valid&&result_alloc_ready)begin
     if(result_alloc_row!==(allocs%400%25)*4||result_alloc_tile!==(allocs%400)/25||
       result_alloc_final!==((allocs%400)==399))$fatal(1,"FAIL INTERNAL allocation schedule");
     allocs=allocs+1;
   end
   if(result_publish_valid&&result_publish_ready)begin pubs=pubs+1;if(fd)$fdisplay(fd,"P %0d %0d %0d",case_id,current_tile,current_row_group);end
   if(core_start_valid&&core_start_ready)starts=starts+1;
   if(feeder_start_valid&&feeder_start_ready)feed_starts=feed_starts+1;
   for(bk=0;bk<4;bk=bk+1)if(load_x_wr_en[bk])rxwrites=rxwrites+1;
   for(bk=0;bk<8;bk=bk+1)if(load_w_wr_en[bk])rwwrites=rwwrites+1;
   if(load_bias_wr_en)bwrites=bwrites+1;
 end
end
task send;input integer op,tile0,index0;input signed[`KWT_CMD_DATA_WIDTH-1:0] data0;
begin
 if(op<0||op>7||tile0<0||tile0>=16||index0<0||index0>=8192)$fatal(1,"FAIL INTERNAL command does not fit current port");
 @(negedge clk);load_cmd_valid=1;load_cmd_op=op;load_cmd_tile_id=tile0;load_cmd_index=index0;load_cmd_data=data0;
 @(posedge clk);while(!load_cmd_ready)@(posedge clk);
 @(negedge clk);load_cmd_valid=0;
end endtask
task transaction;input integer is_ack;input [`KWT_RESULT_SEQUENCE_WIDTH-1:0] seq0;input integer num0,stalls0;input exp_error;input [31:0] exp_data;
integer tt;
begin
 @(negedge clk);result_cmd_valid=1;result_cmd_ack=is_ack;result_cmd_task_id=saved_task;result_cmd_sequence=seq0;result_cmd_count=num0;result_rsp_ready=0;
 @(posedge clk);while(!result_cmd_ready)@(posedge clk);
 @(negedge clk);result_cmd_valid=0;
 repeat(stalls0)begin
   @(negedge clk);
   if(!result_rsp_valid)$fatal(1,"FAIL INTERNAL lost response");
   if(task_done)$fatal(1,"FAIL INTERNAL premature taskdone during pending response");
 end
 if(result_rsp_error!==exp_error || (!exp_error&&result_rsp_data!==exp_data))
   $fatal(1,"FAIL INTERNAL payload case=%0d row=%0d tile=%0d pos=%0d got=%h expected=%h err=%b",case_id,saved_row,saved_tile,read_position,result_rsp_data,exp_data,result_rsp_error);
 last_response=result_rsp_data;result_rsp_ready=1;
 @(posedge clk);while(!result_rsp_valid)@(posedge clk);
 @(negedge clk);result_rsp_ready=0;
end endtask
// 独立消费者，装载等待期间照常服务结果，避免槽满/结果满的循环等待。
initial begin
 forever begin
   @(negedge clk);
   if(cpu_enable&&result_block_valid&&!consumer_busy)begin
     consumer_busy=1;saved_task=result_block_task_id;saved_seq=result_block_sequence;
     saved_row=result_block_row;saved_tile=result_block_tile;saved_count=result_block_count;
     if(saved_task!==load_cmd_task_id||saved_seq!==block_acks+1||saved_row!==(block_acks%25)*4||saved_tile!==block_acks/25||saved_count!==((block_acks%25==24)?48:64))
       $fatal(1,"FAIL INTERNAL descriptor order case=%0d ack=%0d",case_id,block_acks);
     // 每个任务第一块先发一次提前ACK，必须失败且不影响后续读取。
     if(block_acks==0)transaction(1,saved_seq,saved_count,4,1,0);
     for(read_position=0;read_position<saved_count;read_position=read_position+1)begin
       expected_index=(saved_row+read_position/16)*256+saved_tile*16+read_position%16;
       transaction(0,0,0,(read_position==saved_count-1)?9:(rng[1:0]),0,gold[expected_index]);
       if(fd)$fdisplay(fd,"R %0d %0d %08h",case_id,expected_index,last_response);
       reads=reads+1;block_reads=block_reads+1;
     end
     if(!result_block_read_complete)$fatal(1,"FAIL INTERNAL last read not retired");
     transaction(1,saved_seq,saved_count,(block_acks==399)?20:3,0,0);
     acks=acks+1;block_acks=block_acks+1;consumer_busy=0;
   end
 end
end
initial begin
 if(!$value$plusargs("fixtures=%s",fixture_base))$fatal(1,"FAIL INTERNAL missing fixtures");
 if($value$plusargs("trace=%s",trace_path))fd=$fopen(trace_path,"w");
 rst_n=0;load_cmd_layer_id=2;
 repeat(4)@(negedge clk);rst_n=1;
 for(case_id=0;case_id<3;case_id=case_id+1)begin
   cpu_enable=0;block_acks=0;block_reads=0;
   $sformat(fixture_name,"%0s/case%0d-x.hex",fixture_base,case_id);$readmemh(fixture_name,xv);
   $sformat(fixture_name,"%0s/case%0d-w.hex",fixture_base,case_id);$readmemh(fixture_name,wv);
   $sformat(fixture_name,"%0s/case%0d-b.hex",fixture_base,case_id);$readmemh(fixture_name,bv);
   $sformat(fixture_name,"%0s/case%0d-y.hex",fixture_base,case_id);$readmemh(fixture_name,gold);
   load_cmd_task_id=32'h40301000+case_id;
   send(0,0,0,0);
   for(i=0;i<6336;i=i+1)send(1,0,i,{{16{xv[i][15]}},xv[i]});
   for(ti=0;ti<16;ti=ti+1)begin
     send(2,ti,0,0);
     for(i=0;i<1024;i=i+1)begin
       idx=(i%16+ti*16)*64+i/16;
       send(3,ti,i,{{16{wv[idx][15]}},wv[idx]});
     end
     for(i=0;i<16;i=i+1)send(4,ti,i,bv[ti*16+i]);
     send(5,ti,0,0);
     if(ti==0)begin
       send(6,0,0,0);
       // 先允许两块填满，确认第三块等待，随后才开启慢CPU消费者。
       wait(result_owned==2'b11);repeat(350)@(negedge clk);cpu_enable=1;
     end
   end
   wait(task_done);@(negedge clk);
   if(block_acks!=400||block_reads!=25344||result_owned!=0||!result_response_empty||!load_command_empty)
     $fatal(1,"FAIL INTERNAL incomplete matrix");
   $display("CASE INTERNAL case=%0d blocks=%0d reads=%0d",case_id,block_acks,block_reads);
 end
 if(allocs!=1200||pubs!=1200||starts!=1200||feed_starts!=1200||reads!=76032||acks!=1200||rxwrites!=19008||rwwrites!=49152||bwrites!=768||full_wait==0)
   $fatal(1,"FAIL INTERNAL ledger alloc=%0d pub=%0d starts=%0d/%0d reads=%0d ack=%0d writes=%0d/%0d/%0d",allocs,pubs,starts,feed_starts,reads,acks,rxwrites,rwwrites,bwrites);
 // 第四个任务只运行到供数中途后中止，检查共同复位取消在途读和FILL owner。
 cpu_enable=0;load_cmd_task_id=32'h40301003;send(0,0,0,0);
 for(i=0;i<6336;i=i+1)send(1,0,i,{{16{xv[i][15]}},xv[i]});
 send(2,0,0,0);
 for(i=0;i<1024;i=i+1)begin idx=(i%16)*64+i/16;send(3,0,i,{{16{wv[idx][15]}},wv[idx]});end
 for(i=0;i<16;i=i+1)send(4,0,i,bv[i]);
 send(5,0,0,0);send(6,0,0,0);
 wait(core_busy&&feeder_busy);repeat(5)@(negedge clk);
 abort_req=1;@(negedge clk);abort_req=0;
 wait(abort_done);@(negedge clk);
 if(session_valid||fault||result_owned!=0||!worker_rst_n||store_x_rd_valid!=0||store_w_rd_valid!=0)
   $fatal(1,"FAIL INTERNAL abort did not isolate workers/owners/returns");
 $display("PASS CONTROL_INTERNAL_CONTRACT cycles=%0d tasks=3 blocks=%0d reads=%0d acks=%0d x_writes=%0d w_writes=%0d bias_writes=%0d bubbles=%0d allocation_stalls=%0d canceled_blocks=1",cyc,pubs,reads,acks,rxwrites,rwwrites,bwrites,bubbles,full_wait);
 if(fd)$fclose(fd);$finish;
end

endmodule
