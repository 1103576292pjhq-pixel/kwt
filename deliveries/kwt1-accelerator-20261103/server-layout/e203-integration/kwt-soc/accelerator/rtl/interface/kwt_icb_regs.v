`include "kwt_icb_config.vh"
`default_nettype none

// E203 sysper型32位ICB从接口。寄存器表由当前工程定义，不沿用旧包ABI。
// 一次一笔响应；LOCAL保存配置/状态响应，RESULT转发结果模块的原响应。
// 仅接受4字节对齐的整字写，非法访问响应err=1且不产生副作用。
module kwt_icb_regs #(
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

    output wire command_valid,
    input wire command_ready,
    output wire [`KWT_ICB_COMMAND_WIDTH-1:0] command_data,
    output wire result_req_valid,
    input wire result_req_ready,
    output wire result_req_ack,
    output wire [`KWT_TASK_ID_WIDTH-1:0] result_req_task_id,
    output wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] result_req_sequence,
    output wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_req_count,
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
    output wire abort_req, // 合法ABORT写接受沿的一次事件，不额外延迟一拍
    output wire transport_empty
);
    localparam [1:0] R_IDLE=0,R_LOCAL=1,R_RESULT=2;
    reg [1:0] route;
    reg [`KWT_ICB_DATA_WIDTH-1:0] response_data;
    reg response_error;
    reg completion_seen; // 记录曾经达到任务完成，避免STATUS访问本身掩盖实时task_done
    reg abort_wait; // 避免ABORT判断依赖其自身发出的组合abort_pending形成环路
    reg [`KWT_TASK_ID_WIDTH-1:0] cfg_task, ack_task;
    reg [`KWT_LAYER_ID_WIDTH-1:0] cfg_layer;
    reg [`KWT_CMD_TILE_WIDTH-1:0] cfg_tile;
    reg [`KWT_CMD_INDEX_WIDTH-1:0] cfg_index;
    reg [`KWT_CMD_DATA_WIDTH-1:0] cfg_data;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] ack_sequence;
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] ack_count;
    wire [`KWT_ICB_OFFSET_WIDTH-1:0] offset;
    wire address_ok, enabled, result_read, result_ack, want_result, fire;
    reg read_bad, write_bad;
    reg [`KWT_ICB_DATA_WIDTH-1:0] read_data;
    assign offset = icb_cmd_addr[0 +: `KWT_ICB_OFFSET_WIDTH];
    // BASE_ADDR要求256字节对齐；完整高地址比较，不能仅看低偏移产生别名。
    assign address_ok = ((icb_cmd_addr & 32'hffff_ff00) == BASE_ADDR) && (icb_cmd_addr[1:0] == 0);
    assign enabled = !fault && !abort_pending && !abort_wait && !external_abort_req;
    assign result_read = address_ok && icb_cmd_read && (offset == `KWT_ICB_RESULT_DATA);
    assign result_ack = address_ok && !icb_cmd_read && (offset == `KWT_ICB_ACK) && !write_bad;
    assign want_result = enabled && (result_read || result_ack);
    assign result_req_valid = rst_n && (route == R_IDLE) && icb_cmd_valid && want_result;
    assign icb_cmd_ready = rst_n && (route == R_IDLE) && (!want_result || result_req_ready);
    assign fire = icb_cmd_valid && icb_cmd_ready;
    assign result_req_ack = result_ack;
    assign result_req_task_id = result_ack ? ack_task : cfg_task;
    assign result_req_sequence = ack_sequence;
    assign result_req_count = ack_count;
    assign command_data = {icb_cmd_wdata[0 +: `KWT_CMD_OP_WIDTH],cfg_layer,cfg_task,cfg_tile,cfg_index,cfg_data};
    assign command_valid = fire && address_ok && !icb_cmd_read && !write_bad && (offset == `KWT_ICB_COMMAND);
    assign abort_req = fire && address_ok && !icb_cmd_read && !write_bad && (offset == `KWT_ICB_ABORT);
    assign icb_rsp_valid = rst_n && ((route == R_LOCAL) || ((route == R_RESULT) && result_rsp_valid));
    assign icb_rsp_rdata = (route == R_RESULT) ? result_rsp_data : response_data;
    assign icb_rsp_err = (route == R_RESULT) ? result_rsp_error : response_error;
    // 不能提前消费结果模块响应，否则读游标会在CPU接收之前推进。
    assign result_rsp_ready = rst_n && (route == R_RESULT) && icb_rsp_ready;
    assign transport_empty = (route == R_IDLE) && !icb_cmd_valid;

    // ---------- 地址译码与完整字段检查：检查高位之后再截取 ----------
    always @(*) begin
        read_bad = 1'b0;
        read_data = 0;
        case (offset)
            `KWT_ICB_STATUS: begin
                read_data[0]=command_ready;read_data[1]=busy && !(completion_seen || task_done);read_data[2]=compute_done;
                read_data[3]=(completion_seen || task_done) && !fault && !abort_pending && !abort_wait;
                read_data[4]=fault;read_data[5]=block_valid;
                read_data[6]=block_read_complete;read_data[7]=abort_pending || abort_wait;
            end
            `KWT_ICB_TASK: read_data=cfg_task;
            `KWT_ICB_LAYER: read_data[0 +: `KWT_LAYER_ID_WIDTH]=cfg_layer;
            `KWT_ICB_TILE: read_data[0 +: `KWT_CMD_TILE_WIDTH]=cfg_tile;
            `KWT_ICB_INDEX: read_data[0 +: `KWT_CMD_INDEX_WIDTH]=cfg_index;
            `KWT_ICB_DATA: read_data=cfg_data;
            `KWT_ICB_ERROR: read_data[0 +: `KWT_ERROR_CODE_WIDTH]=error_code;
            `KWT_ICB_RESULT_TASK: if (block_valid) read_data=block_task_id;
            `KWT_ICB_RESULT_META: if (block_valid) begin
                read_data[0 +: `KWT_RESULT_ROW_WIDTH]=block_row;
                read_data[8 +: `KWT_CMD_TILE_WIDTH]=block_tile;
                read_data[16 +: `KWT_RESULT_COUNT_CONTAINER_WIDTH]=block_count;
            end
            `KWT_ICB_RESULT_SEQ: if (block_valid) read_data[0 +: `KWT_RESULT_SEQUENCE_WIDTH]=block_sequence;
            `KWT_ICB_RESULT_CURSOR: if (block_valid) read_data[0 +: `KWT_RESULT_COUNT_WIDTH]=block_cursor;
            `KWT_ICB_RESULT_DATA: read_bad=!enabled;
            `KWT_ICB_ACK_TASK: read_data=ack_task;
            `KWT_ICB_ACK_SEQ: read_data[0 +: `KWT_RESULT_SEQUENCE_WIDTH]=ack_sequence;
            `KWT_ICB_ACK_COUNT: read_data[0 +: `KWT_RESULT_COUNT_CONTAINER_WIDTH]=ack_count;
            default: read_bad=1'b1;
        endcase
        write_bad = (icb_cmd_wmask != {`KWT_ICB_MASK_WIDTH{1'b1}});
        if (offset == `KWT_ICB_ABORT)
            write_bad = write_bad || (icb_cmd_wdata != 1) || abort_wait || external_abort_req;
        else begin
            write_bad = write_bad || !enabled;
            case (offset)
                `KWT_ICB_TASK,`KWT_ICB_DATA,`KWT_ICB_ACK_TASK: begin end
                `KWT_ICB_LAYER: write_bad=write_bad || (|icb_cmd_wdata[`KWT_ICB_DATA_WIDTH-1:`KWT_LAYER_ID_WIDTH]);
                `KWT_ICB_TILE: write_bad=write_bad || (|icb_cmd_wdata[`KWT_ICB_DATA_WIDTH-1:`KWT_CMD_TILE_WIDTH]);
                `KWT_ICB_INDEX: write_bad=write_bad || (|icb_cmd_wdata[`KWT_ICB_DATA_WIDTH-1:`KWT_CMD_INDEX_WIDTH]);
                `KWT_ICB_COMMAND: write_bad=write_bad || !command_ready || (icb_cmd_wdata > `KWT_CMD_START);
                `KWT_ICB_ACK_SEQ: write_bad=write_bad || (|icb_cmd_wdata[`KWT_ICB_DATA_WIDTH-1:`KWT_RESULT_SEQUENCE_WIDTH]);
                `KWT_ICB_ACK_COUNT: write_bad=write_bad || (|icb_cmd_wdata[`KWT_ICB_DATA_WIDTH-1:`KWT_RESULT_COUNT_CONTAINER_WIDTH]);
                `KWT_ICB_ACK: write_bad=write_bad || (icb_cmd_wdata != 1);
                default: write_bad=1'b1;
            endcase
        end
    end

    // ---------- 总线响应：接受后保存，ready拉低时保持 ----------
    always @(posedge clk) begin
        if (!rst_n) begin
            route <= R_IDLE;
            response_data <= 0;
            response_error <= 1'b0;
        end else begin
            if (icb_rsp_valid && icb_rsp_ready) route <= R_IDLE;
            if (fire) begin
                if (want_result) route <= R_RESULT;
                else begin
                    route <= R_LOCAL;
                    response_data <= icb_cmd_read ? read_data : 0;
                    response_error <= !address_ok || (icb_cmd_read ? read_bad : write_bad);
                end
            end
        end
    end
    // ---------- 暂存配置：中止只清配置，不清已经接受的响应 ----------
    always @(posedge clk) begin
        if (!rst_n || abort_pending || abort_wait || abort_req || external_abort_req || fault ||
            (command_valid && command_ready && (icb_cmd_wdata[0 +: `KWT_CMD_OP_WIDTH] == `KWT_CMD_BEGIN)))
            completion_seen <= 1'b0;
        else if (task_done) completion_seen <= 1'b1;
        if (!rst_n) abort_wait <= 1'b0;
        else if (abort_req || external_abort_req) abort_wait <= 1'b1;
        else if (abort_done) abort_wait <= 1'b0;
        if (!rst_n || abort_pending || abort_wait || abort_req || external_abort_req) begin
            cfg_task<=0;cfg_layer<=0;cfg_tile<=0;cfg_index<=0;cfg_data<=0;
            ack_task<=0;ack_sequence<=0;ack_count<=0;
        end else if (fire && address_ok && !icb_cmd_read && !write_bad) begin
            case (offset)
                `KWT_ICB_TASK: cfg_task<=icb_cmd_wdata;
                `KWT_ICB_LAYER: cfg_layer<=icb_cmd_wdata[0 +: `KWT_LAYER_ID_WIDTH];
                `KWT_ICB_TILE: cfg_tile<=icb_cmd_wdata[0 +: `KWT_CMD_TILE_WIDTH];
                `KWT_ICB_INDEX: cfg_index<=icb_cmd_wdata[0 +: `KWT_CMD_INDEX_WIDTH];
                `KWT_ICB_DATA: cfg_data<=icb_cmd_wdata;
                `KWT_ICB_ACK_TASK: ack_task<=icb_cmd_wdata;
                `KWT_ICB_ACK_SEQ: ack_sequence<=icb_cmd_wdata[0 +: `KWT_RESULT_SEQUENCE_WIDTH];
                `KWT_ICB_ACK_COUNT: ack_count<=icb_cmd_wdata[0 +: `KWT_RESULT_COUNT_CONTAINER_WIDTH];
                default: begin end
            endcase
        end
    end
endmodule
`default_nettype wire
