`timescale 1ns/1ps
// 独立FFN1加速器。外部是命令流和带索引的结果流，不含CPU/总线/驱动。
module accelerator_top #(
    parameter integer M=99,N=256,READ_LATENCY=1,USE_MACRO=0
)(
    input wire clk,rst_n,abort_i,
    input wire in_valid,output wire in_ready,
    input wire [3:0] in_op,in_layer_id,
    input wire [31:0] in_task_id,
    input wire [7:0] in_tile_id,
    input wire [15:0] in_index,
    input wire signed [47:0] in_data,
    input wire [5:0] in_shift,
    output wire out_valid,input wire out_ready,
    output wire [31:0] out_task_id,out_y_index,
    output wire signed [31:0] out_data,
    output wire [2:0] out_flags,
    output wire task_done,busy,fault,
    output wire [7:0] error_code
);
    wire new_task,x_load,tile_open,w_load,bias_load,tile_commit,start;
    wire session,running;
    wire open_ready,load_open,load_slot,tile_available;
    wire [4:0] next_load_tile;
    wire tile_acquire,tile_done,active_valid,active_slot;
    wire [3:0] active_tile;
    wire matrix_done;
    // 协议故障取消整个任务；fault本身保持到外部abort/reset。
    wire cancel_backend=abort_i||fault;
    command_frontend #(.M(M),.N(N)) frontend(
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.in_valid(in_valid),.in_ready(in_ready),
        .in_op(in_op),.in_layer_id(in_layer_id),.in_task_id(in_task_id),
        .in_tile_id(in_tile_id),.in_index(in_index),.in_data(in_data),.in_shift(in_shift),
        .task_done_i(matrix_done),.open_ready_i(open_ready),.load_open_i(load_open),
        .tile_available_i(tile_available),.next_load_tile_i(next_load_tile),
        .new_task_o(new_task),.x_load_o(x_load),.tile_open_o(tile_open),.w_load_o(w_load),
        .bias_load_o(bias_load),.tile_commit_o(tile_commit),.start_o(start),
        .session_o(session),.running_o(running),.task_id_o(out_task_id),
        .fault_o(fault),.error_code_o(error_code));
    tile_ctrl #(.N(N)) tiles(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),.new_task_i(new_task),
        .open_i(tile_open),.commit_i(tile_commit),.open_ready_o(open_ready),
        .load_open_o(load_open),.load_slot_o(load_slot),.next_load_tile_o(next_load_tile),
        .acquire_i(tile_acquire),.tile_done_i(tile_done),.tile_available_o(tile_available),
        .active_valid_o(active_valid),.active_slot_o(active_slot),.active_tile_o(active_tile));
    wire core_block_ready,core_block_start,core_block_release,block_begin,block_done;
    wire [6:0] row_base;
    wire [3:0] row_mask;
    wire [4:0] row_group;
    wire x_read,w_read,x_valid,w_valid,core_in_valid,core_in_ready,core_block_last;
    wire [5:0] k;
    wire [1:0] ctx;
    wire [63:0] x_data,w_data,core_x,core_w;
    matrix_ctrl #(.M(M),.N(N)) matrix(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),.start_i(start),
        .active_valid_i(active_valid),.active_tile_i(active_tile),
        .tile_acquire_o(tile_acquire),.tile_done_o(tile_done),
        .block_ready_i(core_block_ready),.block_done_i(block_done),
        .block_start_o(core_block_start),.block_begin_o(block_begin),
        .row_base_o(row_base),.row_mask_o(row_mask),.row_group_o(row_group),
        .x_read_o(x_read),.w_read_o(w_read),.k_o(k),.ctx_o(ctx),
        .x_valid_i(x_valid),.w_valid_i(w_valid),.x_i(x_data),.w_i(w_data),
        .in_valid_o(core_in_valid),.in_ready_i(core_in_ready),.core_x_o(core_x),.core_w_o(core_w),
        .block_last_o(core_block_last),.task_done_o(matrix_done));
    x_buffer #(.M(M),.READ_LATENCY(READ_LATENCY),.USE_MACRO(USE_MACRO)) inputs(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),.load_i(x_load),
        .load_index_i(in_index),.load_data_i(in_data[15:0]),.read_i(x_read),
        .row_group_i(row_group),.k_i(k),.row_mask_i(row_mask),.read_valid_o(x_valid),.x_o(x_data));
    wire [3:0] bias_col;
    wire signed [47:0] selected_bias;
    w_tile_buffer #(.READ_LATENCY(READ_LATENCY),.USE_MACRO(USE_MACRO)) weights(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),.load_slot_i(load_slot),
        .w_load_i(w_load),.w_index_i(in_index[9:0]),.w_data_i(in_data[15:0]),
        .bias_load_i(bias_load),.bias_index_i(in_index[3:0]),.bias_data_i(in_data[31:0]),
        .read_i(w_read),.active_slot_i(active_slot),.ctx_i(ctx),.k_i(k),
        .read_valid_o(w_valid),.w_o(w_data),.bias_col_i(bias_col),.bias_o(selected_bias));
    wire acc_ready,read_valid,read_ready,core_out_valid,core_out_ready;
    wire [1:0] sel_ctx,sel_row,sel_col;
    wire [31:0] tag;
    wire last;
    result_ctrl #(.N(N)) results(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),.block_begin_i(block_begin),
        .row_base_i(row_base),.tile_i(active_tile),.row_mask_i(row_mask),
        .acc_ready_i(acc_ready),.read_ready_i(read_ready),.out_valid_i(core_out_valid),
        .out_ready_i(core_out_ready),.block_ready_i(core_block_ready),
        .read_valid_o(read_valid),.sel_ctx_o(sel_ctx),.sel_row_o(sel_row),.sel_col_o(sel_col),
        .bias_col_o(bias_col),.tag_o(tag),.last_o(last),.block_release_o(core_block_release),
        .final_row_group_i({1'b0,row_base}+8'd4>=M),.block_done_o(block_done));
    wire pipeline_empty;
    wire signed [47:0] selected_sum;
    wire overflow,saturated,last_flag;
    dot64_tile_core core(
        .clk(clk),.rst_n(rst_n),.abort_i(cancel_backend),
        .block_start_i(core_block_start),.block_ready_o(core_block_ready),.block_release_i(core_block_release),
        .in_valid_i(core_in_valid),.in_ready_o(core_in_ready),.x_i(core_x),.w_i(core_w),
        .ctx_i(ctx),.row_mask_i(row_mask),.block_last_i(core_block_last),
        .pipeline_empty_o(pipeline_empty),.acc_ready_o(acc_ready),
        .sel_ctx_i(sel_ctx),.sel_row_i(sel_row),.sel_col_i(sel_col),.selected_sum_o(selected_sum),
        .read_valid_i(read_valid),.read_ready_o(read_ready),.bias_i(selected_bias),.tag_i(tag),.last_i(last),
        .out_valid_o(core_out_valid),.out_ready_i(core_out_ready),.out_data_o(out_data),
        .out_tag_o(out_y_index),.out_flags_o(out_flags),
        .out_overflow_o(overflow),.out_saturated_o(saturated),.out_last_o(last_flag));
    assign out_valid=rst_n&&!cancel_backend&&core_out_valid;
    assign core_out_ready=rst_n&&!cancel_backend&&out_ready;
    assign task_done=rst_n&&!cancel_backend&&matrix_done;
    assign busy=(session&&!matrix_done)||fault;
`ifndef SYNTHESIS
    initial if(M<1||M>99||N<16||N>256||N%16!=0)$fatal(1,"unsupported accelerator dimensions");
`endif
endmodule
