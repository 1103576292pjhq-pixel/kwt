`include "kwt_icb_config.vh"
`default_nettype none

// 结果访问适配：一次一笔，读/ACK均保持原结果模块的响应退休边界。
// 合法请求直接与后端同沿握手；不预先接收、不复制成功响应到第二级缓存。
// 空队列或禁止访问时，在本地保存错误事务，不向后端发送命令。
// 接受之后即使access_enable下降，也必须等已接受响应退休，不能吞响应。
// rst_n仅供整个系统硬复位；普通ABORT由后端及接口上层协调排空。
module kwt_result_access (
    input wire clk,
    input wire rst_n,
    input wire req_valid,
    output wire req_ready,
    input wire req_ack,
    input wire [`KWT_TASK_ID_WIDTH-1:0] req_task_id,
    input wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] req_sequence,
    input wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] req_count,
    input wire access_enable,
    input wire block_valid,
    output wire rsp_valid,
    input wire rsp_ready,
    output wire [`KWT_ICB_DATA_WIDTH-1:0] rsp_data,
    output wire rsp_error,

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
    output wire idle
);
    localparam [1:0] S_IDLE=2'd0, S_BACKEND=2'd1, S_LOCAL_ERROR=2'd2;
    reg [1:0] state;
    wire invalid_request, req_fire;
    assign invalid_request = !access_enable || !block_valid;
    // 上游在等待时保持字段；合法请求只有后端可以接收时才对上游ready。
    assign req_ready = rst_n && (state == S_IDLE) && (invalid_request || result_cmd_ready);
    assign req_fire = req_valid && req_ready;
    assign result_cmd_valid = rst_n && (state == S_IDLE) && req_valid && !invalid_request;
    assign result_cmd_ack = req_ack;
    assign result_cmd_task_id = req_task_id;
    assign result_cmd_sequence = req_sequence;
    assign result_cmd_count = req_count;

    // 后端响应直通：CPU/ICB尚未接收时，不允许提前令后端退休并推进cursor。
    assign rsp_valid = rst_n && ((state == S_LOCAL_ERROR) ||
                                 ((state == S_BACKEND) && result_rsp_valid));
    assign rsp_data = (state == S_BACKEND) ? result_rsp_data : {`KWT_ICB_DATA_WIDTH{1'b0}};
    assign rsp_error = (state == S_LOCAL_ERROR) || ((state == S_BACKEND) && result_rsp_error);
    assign result_rsp_ready = rst_n && (state == S_BACKEND) && rsp_ready;
    assign idle = (state == S_IDLE);

    always @(posedge clk) begin
        if (!rst_n) state <= S_IDLE;
        else begin
            case (state)
                S_IDLE: if (req_fire) begin
                    if (invalid_request) state <= S_LOCAL_ERROR;
                    else state <= S_BACKEND;
                end
                S_BACKEND: if (result_rsp_valid && rsp_ready) state <= S_IDLE;
                S_LOCAL_ERROR: if (rsp_ready) state <= S_IDLE;
                default: state <= S_IDLE;
            endcase
        end
    end
endmodule
`default_nettype wire
