`include "kwt_icb_config.vh"
`default_nettype none

// 独立ICB接口顶层：寄存器/一项命令缓冲/结果适配，不包含计算或存储实例。
// 总线格式匹配指定E203 sysper，局部寄存器协议由本工程独立设计。
// 连接task_ctrl：input_fifo_empty/transport_empty、abort_req/abort_pending/done。
// 子模块的数据流连接在生产加速器顶层完成；不能把本模块当成整个加速器。
module kwt_icb #(
    parameter [`KWT_ICB_ADDR_WIDTH-1:0] BASE_ADDR = `KWT_ICB_DEFAULT_BASE
) (
    input wire clk,
    input wire rst_n,
    input wire icb_cmd_valid,
    output wire icb_cmd_ready,
    input wire [`KWT_ICB_ADDR_WIDTH-1:0] icb_cmd_addr,
    input wire icb_cmd_read,
    input wire [`KWT_ICB_DATA_WIDTH-1:0] icb_cmd_wdata,
    input wire [`KWT_ICB_MASK_WIDTH-1:0] icb_cmd_wmask,
    output wire icb_rsp_valid,
    input wire icb_rsp_ready,
    output wire [`KWT_ICB_DATA_WIDTH-1:0] icb_rsp_rdata,
    output wire icb_rsp_err,

    output wire load_cmd_valid,
    input wire load_cmd_ready,
    output wire [`KWT_CMD_OP_WIDTH-1:0] load_cmd_op,
    output wire [`KWT_LAYER_ID_WIDTH-1:0] load_cmd_layer_id,
    output wire [`KWT_TASK_ID_WIDTH-1:0] load_cmd_task_id,
    output wire [`KWT_CMD_TILE_WIDTH-1:0] load_cmd_tile_id,
    output wire [`KWT_CMD_INDEX_WIDTH-1:0] load_cmd_index,
    output wire signed [`KWT_CMD_DATA_WIDTH-1:0] load_cmd_data,

    output wire result_cmd_valid,
    input wire result_cmd_ready,
    output wire result_cmd_ack,
    output wire [`KWT_TASK_ID_WIDTH-1:0] result_cmd_task_id,
    output wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_cmd_sequence,
    output wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_cmd_count,
    input wire result_rsp_valid,
    output wire result_rsp_ready,
    input wire [`KWT_ICB_DATA_WIDTH-1:0] result_rsp_data,
    input wire result_rsp_error,

    input wire busy,
    input wire compute_done,
    input wire task_done,
    input wire fault,
    input wire [`KWT_ERROR_CODE_WIDTH-1:0] error_code,
    input wire block_valid,
    input wire block_read_complete,
    input wire [`KWT_TASK_ID_WIDTH-1:0] block_task_id,
    input wire [`KWT_RESULT_ROW_WIDTH-1:0] block_row,
    input wire [`KWT_CMD_TILE_WIDTH-1:0] block_tile,
    input wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] block_count,
    input wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] block_sequence,
    input wire [`KWT_RESULT_COUNT_WIDTH-1:0] block_cursor,
    input wire abort_pending,
    input wire abort_done,
    input wire external_abort_req,
    output wire abort_req,
    output wire input_fifo_empty,
    output wire transport_empty
);
    wire command_valid, command_ready, clear_commands;
    wire [`KWT_ICB_COMMAND_WIDTH-1:0] command_data, queued_data;
    wire local_abort_req;
    wire request_valid, request_ready, request_ack;
    wire [`KWT_TASK_ID_WIDTH-1:0] request_task;
    wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] request_sequence;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] request_count;
    wire access_rsp_valid, access_rsp_ready, access_rsp_error, access_idle;
    wire [`KWT_ICB_DATA_WIDTH-1:0] access_rsp_data;
    wire regs_empty;
    assign abort_req = local_abort_req || external_abort_req;
    assign clear_commands = abort_pending || abort_req || fault;
    assign transport_empty = regs_empty && access_idle;
    assign {load_cmd_op,load_cmd_layer_id,load_cmd_task_id,load_cmd_tile_id,load_cmd_index,load_cmd_data} = queued_data;

    kwt_command_fifo u_commands (
        .clk(clk),.rst_n(rst_n),.clear(clear_commands),
        .in_valid(command_valid),.in_ready(command_ready),.in_data(command_data),
        .out_valid(load_cmd_valid),.out_ready(load_cmd_ready),.out_data(queued_data),
        .empty(input_fifo_empty)
    );
    kwt_icb_regs #(.BASE_ADDR(BASE_ADDR)) u_regs (
        .clk(clk),.rst_n(rst_n),
        .icb_cmd_valid(icb_cmd_valid),.icb_cmd_ready(icb_cmd_ready),
        .icb_cmd_addr(icb_cmd_addr),.icb_cmd_read(icb_cmd_read),
        .icb_cmd_wdata(icb_cmd_wdata),.icb_cmd_wmask(icb_cmd_wmask),
        .icb_rsp_valid(icb_rsp_valid),.icb_rsp_ready(icb_rsp_ready),
        .icb_rsp_rdata(icb_rsp_rdata),.icb_rsp_err(icb_rsp_err),
        .command_valid(command_valid),.command_ready(command_ready),.command_data(command_data),
        .result_req_valid(request_valid),.result_req_ready(request_ready),
        .result_req_ack(request_ack),.result_req_task_id(request_task),
        .result_req_sequence(request_sequence),.result_req_count(request_count),
        .result_rsp_valid(access_rsp_valid),.result_rsp_ready(access_rsp_ready),
        .result_rsp_data(access_rsp_data),.result_rsp_error(access_rsp_error),
        .busy(busy),.compute_done(compute_done),.task_done(task_done),.fault(fault),.error_code(error_code),
        .block_valid(block_valid),.block_read_complete(block_read_complete),
        .block_task_id(block_task_id),.block_row(block_row),.block_tile(block_tile),
        .block_count(block_count),.block_sequence(block_sequence),.block_cursor(block_cursor),
        .abort_pending(abort_pending),.abort_done(abort_done),.external_abort_req(external_abort_req),
        .abort_req(local_abort_req),.transport_empty(regs_empty)
    );
    kwt_result_access u_result_access (
        .clk(clk),.rst_n(rst_n),
        .req_valid(request_valid),.req_ready(request_ready),.req_ack(request_ack),
        .req_task_id(request_task),.req_sequence(request_sequence),.req_count(request_count),
        .access_enable(!fault && !abort_pending && !abort_req),.block_valid(block_valid),
        .rsp_valid(access_rsp_valid),.rsp_ready(access_rsp_ready),
        .rsp_data(access_rsp_data),.rsp_error(access_rsp_error),
        .result_cmd_valid(result_cmd_valid),.result_cmd_ready(result_cmd_ready),
        .result_cmd_ack(result_cmd_ack),.result_cmd_task_id(result_cmd_task_id),
        .result_cmd_sequence(result_cmd_sequence),.result_cmd_count(result_cmd_count),
        .result_rsp_valid(result_rsp_valid),.result_rsp_ready(result_rsp_ready),
        .result_rsp_data(result_rsp_data),.result_rsp_error(result_rsp_error),.idle(access_idle)
    );
endmodule
`default_nettype wire
