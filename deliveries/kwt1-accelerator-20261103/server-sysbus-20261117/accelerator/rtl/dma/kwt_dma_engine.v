`include "kwt_icb_config.vh"
`default_nettype none
// Existing arithmetic, storage and control instances with direct DMA handshakes.
module kwt_dma_engine #(
 parameter [2:0] SRAM_EMA=3'd2, parameter [1:0] SRAM_EMAW=2'd0
)(input wire clk,input wire rst_n,
 output wire busy,compute_done,task_done,fault,
 output wire [7:0] error_code,output wire abort_pending,abort_done,
 input wire load_cmd_valid,
 output wire load_cmd_ready,
 input wire [`KWT_CMD_OP_WIDTH-1:0] load_cmd_op,
 input wire [`KWT_LAYER_ID_WIDTH-1:0] load_cmd_layer_id,
 input wire [31:0] load_cmd_task_id,
 input wire [`KWT_CMD_TILE_WIDTH-1:0] load_cmd_tile_id,
 input wire [`KWT_CMD_INDEX_WIDTH-1:0] load_cmd_index,
 input wire signed [31:0] load_cmd_data,
 input wire result_cmd_valid,
 output wire result_cmd_ready,
 input wire result_cmd_ack,
 input wire [31:0] result_cmd_task_id,
 input wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_cmd_sequence,
 input wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_cmd_count,
 output wire result_rsp_valid,
 input wire result_rsp_ready,
 output wire [31:0] result_rsp_data,
 output wire result_rsp_error,
 output wire result_block_valid,
 output wire [31:0] result_block_task_id,
 output wire [`KWT_RESULT_ROW_WIDTH-1:0] result_block_row,
 output wire [`KWT_CMD_TILE_WIDTH-1:0] result_block_tile,
 output wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_block_count,
 output wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_block_sequence,
 input wire abort_req,
 input wire input_fifo_empty,
 input wire transport_empty
);
    // ============================================================
    // 1. 内部连线：全部数据位宽引用公共宏；模块间不共享寄存器赋值职责。
    // ============================================================
    // ---- ICB命令与结果访问 ----
    // ---- 任务调度与会话身份 ----
    wire load_begin_valid;
    wire load_begin_ready;
    wire [`KWT_TASK_ID_WIDTH-1:0] load_begin_task_id;
    wire [`KWT_LAYER_ID_WIDTH-1:0] load_begin_layer_id;
    wire load_start_valid;
    wire load_start_ready;
    wire load_session_valid;
    wire [`KWT_TASK_ID_WIDTH-1:0] load_session_task_id;
    wire [`KWT_LAYER_ID_WIDTH-1:0] load_session_layer_id;
    wire load_x_ready;
    wire [`KWT_W_SLOT_COUNT*`KWT_SLOT_STATE_WIDTH-1:0] load_slot_state;
    wire [`KWT_W_SLOT_COUNT*`KWT_TILE_ID_WIDTH-1:0] load_slot_tile;
    wire load_command_empty;
    wire load_fault;
    wire [`KWT_ERROR_CODE_WIDTH-1:0] load_error_code;
    wire load_activate_valid;
    wire load_activate_ready;
    wire load_activate_slot;
    wire load_release_valid;
    wire load_release_ready;
    wire load_release_slot;
    wire worker_rst_n;
    wire session_valid;
    wire [`KWT_TASK_ID_WIDTH-1:0] task_id;
    wire [`KWT_LAYER_ID_WIDTH-1:0] layer_id;
    wire active_w_slot;
    wire [`KWT_ROW_GROUP_WIDTH-1:0] current_row_group;
    wire [`KWT_TILE_ID_WIDTH-1:0] current_tile;
    wire load_task_started;
    wire load_command_done;
    // ---- 块启动、返回供数与计算结果 ----
    wire feeder_start_valid;
    wire feeder_start_ready;
    wire [`KWT_ROW_GROUP_WIDTH-1:0] feeder_start_row_group;
    wire feeder_start_w_slot;
    wire feeder_busy;
    wire feeder_done;
    wire feeder_fault;
    wire core_start_valid;
    wire core_start_ready;
    wire [`KWT_ROW_MASK_WIDTH-1:0] core_start_row_mask;
    wire core_start_is_final_block;
    wire core_busy;
    wire core_block_done;
    wire operands_valid;
    wire operands_ready;
    wire [`KWT_X_GROUP_WIDTH-1:0] operands_x;
    wire [`KWT_W_GROUP_WIDTH-1:0] operands_w;
    wire core_out_valid;
    wire core_out_ready;
    wire [`KWT_RESULT_INDEX_WIDTH-1:0] core_out_index;
    wire signed [`KWT_Y_WIDTH-1:0] core_out_y;
    wire [`KWT_FLAGS_WIDTH-1:0] core_out_flags;
    wire core_out_block_last;
    wire [`KWT_BIAS_ADDR_WIDTH-1:0] core_bias_addr;
    wire signed [`KWT_BIAS_WIDTH-1:0] core_bias_data;
    // ---- 结果块分配、发布、描述符与恢复 ----
    wire result_block_read_complete;
    wire [`KWT_RESULT_COUNT_WIDTH-1:0] result_block_cursor;
    wire result_begin_valid;
    wire result_begin_ready;
    wire [`KWT_TASK_ID_WIDTH-1:0] result_begin_task_id;
    wire result_alloc_valid;
    wire result_alloc_ready;
    wire [`KWT_TASK_ID_WIDTH-1:0] result_alloc_task_id;
    wire [`KWT_RESULT_ROW_WIDTH-1:0] result_alloc_row;
    wire [`KWT_CMD_TILE_WIDTH-1:0] result_alloc_tile;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_alloc_count;
    wire result_alloc_final;
    wire result_publish_valid;
    wire result_publish_ready;
    wire [`KWT_RESULT_BLOCK_COUNT-1:0] result_owned;
    wire result_response_empty;
    wire result_compute_done;
    wire result_fault;
    wire [`KWT_ERROR_CODE_WIDTH-1:0] result_error_code;
    wire result_abort_req;
    wire result_abort_done;
    wire [`KWT_RESULT_PAYLOAD_WIDTH-1:0] result_peek_data;
    wire result_abort_pending;
    // ---- 存储写通路与读取返回 ----
    wire [`KWT_X_BANK_COUNT-1:0] load_x_wr_en;
    wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] load_x_addr;
    wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] load_x_wr_data;
    wire [`KWT_W_BANK_COUNT-1:0] load_w_wr_en;
    wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] load_w_addr;
    wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] load_w_wr_data;
    wire load_bias_wr_en;
    wire load_bias_wr_slot;
    wire [`KWT_BIAS_ADDR_WIDTH-1:0] load_bias_wr_addr;
    wire signed [`KWT_BIAS_WIDTH-1:0] load_bias_wr_data;
    wire [`KWT_X_BANK_COUNT-1:0] feeder_x_rd_en;
    wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] feeder_x_addr;
    wire [`KWT_X_GROUP_WIDTH-1:0] storage_x_rd_data;
    wire [`KWT_X_BANK_COUNT-1:0] storage_x_rd_valid;
    wire [`KWT_X_BANK_COUNT-1:0] storage_x_access_error;
    wire [`KWT_W_BANK_COUNT-1:0] feeder_w_rd_en;
    wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] feeder_w_addr;
    wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] storage_w_rd_data;
    wire [`KWT_W_BANK_COUNT-1:0] storage_w_rd_valid;
    wire [`KWT_W_BANK_COUNT-1:0] storage_w_access_error;
    wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] storage_x_addr;
    wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] storage_w_addr;

    // ============================================================
    // 2. 单端口bank地址选择：读写地址互斥时，写使能选择装载地址。
    // ============================================================
    // 装载控制只写LOADING槽，供数器只读ACTIVE槽；X必须先装完再计算。
    // 每个bank单独mux，允许不同bank/不同槽同拍一读一写。
    // 不能将两条地址总线按位或，也不能用一个全局写使能切换全部bank。
    genvar xb, wb;
    generate
        for (xb=0; xb<`KWT_X_BANK_COUNT; xb=xb+1) begin : gen_x_address
            assign storage_x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH] =
                load_x_wr_en[xb]
                ? load_x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH]
                : feeder_x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH];
        end
        for (wb=0; wb<`KWT_W_BANK_COUNT; wb=wb+1) begin : gen_w_address
            assign storage_w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH] =
                load_w_wr_en[wb]
                ? load_w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH]
                : feeder_w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH];
        end
    endgenerate

    // ============================================================
    // 3. 模块例化：结果/ICB使用全局复位，工作通路使用worker_rst_n。
    // ============================================================
    // 结果模块保留已接受响应直到退休；不能在普通ABORT时随worker一起复位。

    // ---- 总线事务及一项命令缓冲 ----


    // ---- 会话/400块调度/中止恢复 ----
    kwt_task_ctrl u_task (
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

    // ---- 命令合法性与操作数写入 ----
    kwt_load_ctrl u_load (
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

    // ---- 同步SRAM返回到计算核有序输入 ----
    kwt_operand_feeder u_feeder (
        .clk(clk),
        .rst_n(worker_rst_n),
        .start_valid(feeder_start_valid),
        .start_ready(feeder_start_ready),
        .start_row_group(feeder_start_row_group),
        .start_w_slot(feeder_start_w_slot),
        .x_rd_en(feeder_x_rd_en),
        .x_addr(feeder_x_addr),
        .x_rd_data(storage_x_rd_data),
        .x_rd_valid(storage_x_rd_valid),
        .x_access_error(storage_x_access_error),
        .w_rd_en(feeder_w_rd_en),
        .w_addr(feeder_w_addr),
        .w_rd_data(storage_w_rd_data),
        .w_rd_valid(storage_w_rd_valid),
        .w_access_error(storage_w_access_error),
        .out_valid(operands_valid),
        .out_ready(operands_ready),
        .out_x(operands_x),
        .out_w(operands_w),
        .busy(feeder_busy),
        .feed_done(feeder_done),
        .fault(feeder_fault)
    );

    // ---- 结果双块与CPU读取/ACK ----
    kwt_result_blocks u_results (
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
        .fill_valid(core_out_valid),
        .fill_ready(core_out_ready),
        .fill_index(core_out_index),
        .fill_y(core_out_y),
        .fill_flags(core_out_flags),
        .fill_block_last(core_out_block_last),
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

    // ---- X/W物理宏封装及bias寄存器 ----
    kwt_storage_wrapper #(.SRAM_EMA(SRAM_EMA), .SRAM_EMAW(SRAM_EMAW)) u_storage (
        .clk(clk),
        .rst_n(worker_rst_n),
        .x_rd_en(feeder_x_rd_en),
        .x_wr_en(load_x_wr_en),
        .x_addr(storage_x_addr),
        .x_wr_data(load_x_wr_data),
        .x_rd_data(storage_x_rd_data),
        .x_rd_valid(storage_x_rd_valid),
        .x_access_error(storage_x_access_error),
        .w_rd_en(feeder_w_rd_en),
        .w_wr_en(load_w_wr_en),
        .w_addr(storage_w_addr),
        .w_wr_data(load_w_wr_data),
        .w_rd_data(storage_w_rd_data),
        .w_rd_valid(storage_w_rd_valid),
        .w_access_error(storage_w_access_error),
        .bias_wr_en(load_bias_wr_en),
        .bias_wr_slot(load_bias_wr_slot),
        .bias_wr_addr(load_bias_wr_addr),
        .bias_wr_data(load_bias_wr_data),
        .bias_rd_slot(active_w_slot),
        .bias_rd_addr(core_bias_addr),
        .bias_rd_data(core_bias_data)
    );

    // ---- 已完成的16MAC/CTX4点积核 ----
    dot_product_block_core u_core (
        .clk(clk),
        .rst_n(worker_rst_n),
        .start_valid(core_start_valid),
        .start_ready(core_start_ready),
        .start_row_mask(core_start_row_mask),
        .start_is_final_block(core_start_is_final_block),
        .in_valid(operands_valid),
        .in_ready(operands_ready),
        .in_x(operands_x),
        .in_w(operands_w),
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

endmodule
`default_nettype wire
