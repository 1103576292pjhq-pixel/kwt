`include "kwt_control_config.vh"
`default_nettype none

// 双结果块：每块64项，每项{flags3,Y16}，不重复量化，不使用X/W SRAM宏。
// 正常块64项，尾行块48项；核按g/p/q发射，按fill_index写入行优先位置。
// 生命周期：FREE --alloc--> FILL --publish--> READY --匹配ACK--> FREE。
// 一次只有一个FILL生产者；alloc_ptr/head_ptr轮转保证CPU按发布顺序读取。
// CPU读请求接受时快照，成功响应退休时cursor才加一；ACK接受沿释放owner。
// ACK响应仍需排空，不能因owner已释放就开始新会话或声明整机完成。
// rst_n为共同硬复位；普通ABORT用abort_req，保留已接受响应直到退休后清状态。
// CPU的MMIO访问由本工程ICB接口解析，本模块只处理读结果和确认事务。
module kwt_result_blocks #(
    // 9位序号不回绕；当前固定任务只有400块，默认只允许1..400。
    parameter [`KWT_RESULT_SEQUENCE_WIDTH-1:0] SEQUENCE_MAX = `KWT_TASK_BLOCK_COUNT
) (
    input wire clk,
    input wire rst_n,

    // ---- 新会话：只有无owner、无响应且旧会话已计算完时才ready ----
    input wire begin_valid,
    output wire begin_ready,
    input wire [`KWT_TASK_ID_WIDTH-1:0] begin_task_id,

    // ---- 任务控制分配描述符；alloc成功后再启动对应计算块 ----
    input wire alloc_valid,
    output wire alloc_ready,
    input wire [`KWT_TASK_ID_WIDTH-1:0] alloc_task_id,
    input wire [`KWT_RESULT_ROW_WIDTH-1:0] alloc_row, // 全局行起点0,4,..96
    input wire [`KWT_CMD_TILE_WIDTH-1:0] alloc_tile, // 全局tile0..15
    input wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] alloc_count, // 64或48
    input wire alloc_final, // 仅row96/tile15为1

    // ---- 计算核填写：直接连接out_valid/out_ready及数据/位置/块末标记 ----
    input wire fill_valid,
    output wire fill_ready,
    input wire [`KWT_RESULT_INDEX_WIDTH-1:0] fill_index,
    input wire signed [`KWT_Y_WIDTH-1:0] fill_y,
    input wire [`KWT_FLAGS_WIDTH-1:0] fill_flags,
    input wire fill_block_last, // 与全局最后项flags[2]不同
    input wire publish_valid, // 任务控制在最后项填写之后请求发布
    output wire publish_ready,

    // ---- CPU结果事务，由ICB适配后传入；同一通道读/ACK，一次一笔响应 ----
    input wire cmd_valid,
    output wire cmd_ready,
    input wire cmd_ack, // 0读下一项；1确认整个块，释放owner
    input wire [`KWT_TASK_ID_WIDTH-1:0] cmd_task_id,
    input wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] cmd_sequence, // ACK检查，读时忽略
    input wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] cmd_count, // ACK检查
    output reg rsp_valid,
    input wire rsp_ready, // 本地响应退休边界；SoC中可能由guard接收
    output reg [`KWT_RESULT_RESPONSE_WIDTH-1:0] rsp_data,
    output reg rsp_error, // 非法读/ACK仅返回错误，不释放owner/推进cursor

    // ---- 当前最早发布结果块的只读描述符和观察数据 ----
    output wire block_valid,
    output wire block_read_complete,
    output wire [`KWT_TASK_ID_WIDTH-1:0] block_task_id,
    output wire [`KWT_RESULT_ROW_WIDTH-1:0] block_row,
    output wire [`KWT_CMD_TILE_WIDTH-1:0] block_tile,
    output wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] block_count,
    output wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0] block_sequence,
    output wire [`KWT_RESULT_COUNT_WIDTH-1:0] block_cursor, // 含64完成哨兵
    output wire [`KWT_RESULT_PAYLOAD_WIDTH-1:0] peek_data, // 当前读取位置的组合观察值

    // ---- 中止与状态 ----
    input wire abort_req, // 单拍；停止新操作，排空已接受响应，再清owner/会话/错误
    output reg abort_pending,
    output reg abort_done,
    output wire [`KWT_RESULT_BLOCK_COUNT-1:0] owned,
    output wire response_empty, // 仅本地无响应；上游FIFO/ICB另行判断
    output reg compute_done, // 最终块成功publish后保持；不是B task_done
    output reg fault, // 生产侧分配/填写/发布错误锁存；ABORT或共同复位恢复
    output reg [`KWT_ERROR_CODE_WIDTH-1:0] error_code
);

    // ============================================================
    // 1. 数据存储与描述符；数据阵列不逐项复位
    // ============================================================
    // 两个独立寄存器阵列，共2*64*19=2432 bit；仅写对应FILL块。
    reg [`KWT_RESULT_PAYLOAD_WIDTH-1:0] payload0 [0:`KWT_RESULT_WORDS-1];
    reg [`KWT_RESULT_PAYLOAD_WIDTH-1:0] payload1 [0:`KWT_RESULT_WORDS-1];
    reg [`KWT_RESULT_STATE_WIDTH-1:0] state [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_TASK_ID_WIDTH-1:0] desc_task [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_RESULT_ROW_WIDTH-1:0] desc_row [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_CMD_TILE_WIDTH-1:0] desc_tile [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] desc_count [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] desc_sequence [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg desc_final [0:`KWT_RESULT_BLOCK_COUNT-1];
    reg [`KWT_RESULT_COUNT_WIDTH-1:0] cursor [0:`KWT_RESULT_BLOCK_COUNT-1];

    reg session_valid;
    reg [`KWT_TASK_ID_WIDTH-1:0] session_task_id;
    reg alloc_ptr, head_ptr; // 两块固定环：分配与ACK分别翻转指针
    reg filling, fill_slot; // 当前FILL块身份，不依赖CPU当前读取哪块
    reg [`KWT_RESULT_WORDS-1:0] written_mask;
    reg [`KWT_RESULT_COUNT_WIDTH-1:0] written_count;
    reg last_seen;
    reg [`KWT_RESULT_SEQUENCE_WIDTH-1:0] next_sequence;
    reg sequence_exhausted; // 防止最大序号之后回绕为0
    reg rsp_is_read, rsp_slot; // 响应快照身份，退休时更新对应块游标

    wire aborting, enabled;
    wire begin_fire, alloc_fire, fill_fire, publish_fire, cmd_fire, rsp_retire;
    wire alloc_bad, fill_bad, publish_bad;
    wire [`KWT_RESULT_WORDS-1:0] expected_mask;
    wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] filling_count;
    wire filling_final;
    assign aborting = abort_req || abort_pending;
    assign enabled = rst_n && session_valid && !fault && !aborting;
    assign owned = {(state[1] != `KWT_RESULT_FREE),(state[0] != `KWT_RESULT_FREE)};
    assign response_empty = !rsp_valid;
    // 本地条件只是新会话条件的一部分；上层还需确认核心和其他事务已安静。
    assign begin_ready = rst_n && !fault && !aborting && (owned == 0) &&
                         !filling && !rsp_valid && (!session_valid || compute_done);
    assign begin_fire = begin_valid && begin_ready;
    assign alloc_ready = enabled && !begin_fire && !compute_done && !filling &&
                         (state[alloc_ptr] == `KWT_RESULT_FREE);
    assign fill_ready = enabled && filling;
    // 最后一项填写与publish分开，fill优先，publish等待其下一拍。
    assign publish_ready = enabled && filling && !fill_valid;
    assign cmd_ready = enabled && !begin_fire && !rsp_valid;
    assign alloc_fire = alloc_valid && alloc_ready;
    assign fill_fire = fill_valid && fill_ready;
    assign publish_fire = publish_valid && publish_ready;
    assign cmd_fire = cmd_valid && cmd_ready;
    // 即使fault/ABORT也继续交付已经接受的响应，不吞响应。
    assign rsp_retire = rsp_valid && rsp_ready;

    // ============================================================
    // 2. 当前消费块：组合描述符/peek；CPU响应另行寄存，不直接暴露变化
    // ============================================================
    assign block_valid = enabled && (state[head_ptr] == `KWT_RESULT_READY);
    assign block_task_id = block_valid ? desc_task[head_ptr] : 0;
    assign block_row = block_valid ? desc_row[head_ptr] : 0;
    assign block_tile = block_valid ? desc_tile[head_ptr] : 0;
    assign block_count = block_valid ? desc_count[head_ptr] : 0;
    assign block_sequence = block_valid ? desc_sequence[head_ptr] : 0;
    assign block_cursor = block_valid ? cursor[head_ptr] : 0;
    assign block_read_complete = block_valid && (cursor[head_ptr] == desc_count[head_ptr]);
    // cursor能到64，不能直接用其低6位在完成后重新显示第0项。
    assign peek_data = (block_valid && !block_read_complete)
        ? (head_ptr ? payload1[cursor[head_ptr][0 +: `KWT_RESULT_INDEX_WIDTH]]
                    : payload0[cursor[head_ptr][0 +: `KWT_RESULT_INDEX_WIDTH]])
        : {`KWT_RESULT_PAYLOAD_WIDTH{1'b0}};

    // ============================================================
    // 3. 生产侧检查：描述符、每个位置、块末标记与完整性
    // ============================================================
    assign filling_count = desc_count[fill_slot];
    assign filling_final = desc_final[fill_slot];
    assign expected_mask = {`KWT_RESULT_WORDS{1'b1}} >> (`KWT_RESULT_WORDS - filling_count);
    assign alloc_bad = (alloc_task_id != session_task_id) ||
        (alloc_row > (`KWT_M-1)) || ((alloc_row % `KWT_PM) != 0) ||
        (alloc_tile >= `KWT_TILE_COUNT) ||
        (alloc_count != ((alloc_row == (`KWT_M-(`KWT_M % `KWT_PM)))
            ? ((`KWT_M % `KWT_PM)*`KWT_BLOCK_COLS) : `KWT_RESULT_WORDS)) ||
        (alloc_final != ((alloc_row == (`KWT_M-(`KWT_M % `KWT_PM))) &&
                         (alloc_tile == (`KWT_TILE_COUNT-1)))) || sequence_exhausted ||
        (SEQUENCE_MAX == 0) || (next_sequence > SEQUENCE_MAX);
    assign fill_bad = (state[fill_slot] != `KWT_RESULT_FILL) ||
        (fill_index >= filling_count) || written_mask[fill_index] || last_seen ||
        (written_count >= filling_count) ||
        (fill_block_last != (written_count == (filling_count-1'b1))) ||
        (fill_block_last && (fill_index != (filling_count-1'b1))) ||
        (fill_flags[`KWT_FLAG_GLOBAL_LAST_BIT] != (filling_final && fill_block_last));
    assign publish_bad = (state[fill_slot] != `KWT_RESULT_FILL) ||
        (written_mask != expected_mask) || (written_count != filling_count) ||
        !last_seen || sequence_exhausted || (SEQUENCE_MAX == 0) || (next_sequence > SEQUENCE_MAX);

    // 数据阵列只在合法填写沿更新；复位/BEGIN/ABORT不清payload。
    always @(posedge clk) begin
        if (fill_fire && !fill_bad) begin
            if (fill_slot) payload1[fill_index] <= {fill_flags,fill_y};
            else payload0[fill_index] <= {fill_flags,fill_y};
        end
    end

    // ============================================================
    // 4. 响应快照：接受时保存，退休时才推进读游标
    // ============================================================
    // CPU错误只返回rsp_error，不锁存生产fault；错误ACK不能释放owner。
    wire read_ok, ack_ok;
    assign read_ok = block_valid && !block_read_complete && (cmd_task_id == block_task_id);
    assign ack_ok = block_valid && block_read_complete && (cmd_task_id == block_task_id) &&
                    (cmd_sequence == block_sequence) && (cmd_count == block_count);
    always @(posedge clk) begin
        if (!rst_n) begin
            rsp_valid <= 1'b0;
            rsp_data <= 0;
            rsp_error <= 1'b0;
            rsp_is_read <= 1'b0;
            rsp_slot <= 1'b0;
        end else begin
            if (rsp_retire) rsp_valid <= 1'b0;
            if (cmd_fire) begin
                rsp_valid <= 1'b1;
                rsp_data <= 0;
                rsp_error <= 1'b0;
                rsp_is_read <= 1'b0;
                rsp_slot <= head_ptr;
                if (cmd_ack) begin
                    if (!ack_ok) rsp_error <= 1'b1;
                end else if (read_ok) begin
                    // 本工程结果响应为{零扩展13位,flags3,Y16}。
                    rsp_data <= {{(`KWT_RESULT_RESPONSE_WIDTH-`KWT_RESULT_PAYLOAD_WIDTH){1'b0}},peek_data};
                    rsp_is_read <= 1'b1;
                end else rsp_error <= 1'b1;
            end
        end
    end

    // ============================================================
    // 5. 所有权、序号及恢复状态；payload和无效描述符均无需清零
    // ============================================================
    integer b;
    always @(posedge clk) begin
        if (!rst_n) begin
            session_valid <= 1'b0;
            session_task_id <= 0;
            alloc_ptr <= 1'b0;
            head_ptr <= 1'b0;
            filling <= 1'b0;
            fill_slot <= 1'b0;
            written_mask <= 0;
            written_count <= 0;
            last_seen <= 1'b0;
            next_sequence <= 1;
            sequence_exhausted <= 1'b0;
            compute_done <= 1'b0;
            fault <= 1'b0;
            error_code <= 0;
            abort_pending <= 1'b0;
            abort_done <= 1'b0;
            for (b=0; b<`KWT_RESULT_BLOCK_COUNT; b=b+1) begin
                state[b] <= `KWT_RESULT_FREE;
                cursor[b] <= 0;
            end
        end else begin
            abort_done <= 1'b0;
            // 响应退休身份使用rsp_slot快照，不能根据新请求改游标。
            if (rsp_retire && rsp_is_read && !rsp_error)
                cursor[rsp_slot] <= cursor[rsp_slot] + 1'b1;

            if (aborting) begin
                abort_pending <= 1'b1;
                // 响应在本沿退休时，下一拍才看到rsp_valid=0并执行清理。
                if (!rsp_valid) begin
                    abort_pending <= 1'b0;
                    abort_done <= 1'b1;
                    session_valid <= 1'b0;
                    session_task_id <= 0;
                    alloc_ptr <= 1'b0;
                    head_ptr <= 1'b0;
                    filling <= 1'b0;
                    fill_slot <= 1'b0;
                    written_mask <= 0;
                    written_count <= 0;
                    last_seen <= 1'b0;
                    next_sequence <= 1;
                    sequence_exhausted <= 1'b0;
                    compute_done <= 1'b0;
                    fault <= 1'b0;
                    error_code <= 0;
                    for (b=0; b<`KWT_RESULT_BLOCK_COUNT; b=b+1) begin
                        state[b] <= `KWT_RESULT_FREE;
                        cursor[b] <= 0;
                    end
                end
            end else if (begin_fire) begin
                session_valid <= 1'b1;
                session_task_id <= begin_task_id;
                alloc_ptr <= 1'b0;
                head_ptr <= 1'b0;
                filling <= 1'b0;
                fill_slot <= 1'b0;
                written_mask <= 0;
                written_count <= 0;
                last_seen <= 1'b0;
                next_sequence <= 1;
                sequence_exhausted <= 1'b0;
                compute_done <= 1'b0;
                for (b=0; b<`KWT_RESULT_BLOCK_COUNT; b=b+1) begin
                    state[b] <= `KWT_RESULT_FREE;
                    cursor[b] <= 0;
                end
            end else begin
                if (alloc_fire) begin
                    if (alloc_bad) begin
                        fault <= 1'b1;
                        error_code <= `KWT_RESULT_ERR_ALLOC;
                    end else begin
                        state[alloc_ptr] <= `KWT_RESULT_FILL;
                        desc_task[alloc_ptr] <= alloc_task_id;
                        desc_row[alloc_ptr] <= alloc_row;
                        desc_tile[alloc_ptr] <= alloc_tile;
                        desc_count[alloc_ptr] <= alloc_count;
                        desc_final[alloc_ptr] <= alloc_final;
                        cursor[alloc_ptr] <= 0;
                        fill_slot <= alloc_ptr;
                        alloc_ptr <= !alloc_ptr;
                        filling <= 1'b1;
                        written_mask <= 0;
                        written_count <= 0;
                        last_seen <= 1'b0;
                    end
                end
                if (fill_fire) begin
                    if (fill_bad) begin
                        fault <= 1'b1;
                        error_code <= `KWT_RESULT_ERR_FILL;
                    end else begin
                        written_mask[fill_index] <= 1'b1;
                        written_count <= written_count + 1'b1;
                        if (fill_block_last) last_seen <= 1'b1;
                    end
                end
                if (publish_fire) begin
                    if (publish_bad) begin
                        fault <= 1'b1;
                        error_code <= `KWT_RESULT_ERR_PUBLISH;
                    end else begin
                        state[fill_slot] <= `KWT_RESULT_READY;
                        desc_sequence[fill_slot] <= next_sequence;
                        filling <= 1'b0;
                        if (next_sequence == SEQUENCE_MAX) sequence_exhausted <= 1'b1;
                        else next_sequence <= next_sequence + 1'b1;
                        if (desc_final[fill_slot]) compute_done <= 1'b1;
                    end
                end
                // ACK接受沿即可释放；成功响应随后独立排空。
                // 与合法alloc/publish不会写同一块：各自要求FREE/FILL/READY。
                if (cmd_fire && cmd_ack && ack_ok) begin
                    state[head_ptr] <= `KWT_RESULT_FREE;
                    head_ptr <= !head_ptr;
                end
            end
        end
    end
endmodule
`default_nettype wire
