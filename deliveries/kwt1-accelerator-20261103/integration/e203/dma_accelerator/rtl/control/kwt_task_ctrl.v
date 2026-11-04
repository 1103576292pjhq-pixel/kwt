`include "kwt_control_config.vh"
`default_nettype none

// 固定99×64×256任务调度：tile外层0..15，行组内层0..24，共400块。
// 只协调控制接口，不例化其他模块，不传输X/W/Y，不重复保存W槽owner。
// 顺序：BEGIN -> START -> 等W槽 -> 激活 -> 分配结果 -> 分别启动核/供数器
//       -> 等块完成 -> 发布 -> 下一行组；最后行组发布后释放该W槽。
// 顶层负责：数据连线、共享bank地址选择、bias活动槽连接、ICB及FIFO。
// worker_rst_n接装载/供数/计算核/存储wrapper的rst_n；结果模块接全局rst_n，
// 普通ABORT通过result_abort_req排空结果响应，不能用worker_rst_n复位结果模块。
module kwt_task_ctrl (
    input wire clk,
    input wire rst_n,

    // ---- 装载控制发来的会话与整个矩阵START请求 ----
    input wire load_begin_valid,
    output wire load_begin_ready,
    input wire [`KWT_TASK_ID_WIDTH-1:0] load_begin_task_id,
    input wire [`KWT_LAYER_ID_WIDTH-1:0] load_begin_layer_id,
    input wire load_start_valid,
    output wire load_start_ready,
    input wire load_session_valid,
    input wire [`KWT_TASK_ID_WIDTH-1:0] load_session_task_id,
    input wire [`KWT_LAYER_ID_WIDTH-1:0] load_session_layer_id,
    input wire load_x_ready,
    input wire [`KWT_W_SLOT_COUNT*`KWT_SLOT_STATE_WIDTH-1:0] load_slot_state,
    input wire [`KWT_W_SLOT_COUNT*`KWT_TILE_ID_WIDTH-1:0] load_slot_tile,
    input wire load_command_empty,
    input wire load_fault,
    input wire [`KWT_ERROR_CODE_WIDTH-1:0] load_error_code,
    output wire load_activate_valid,
    input wire load_activate_ready,
    output wire load_activate_slot,
    output wire load_release_valid,
    input wire load_release_ready,
    output wire load_release_slot,

    // ---- 供数器的单块启动与状态 ----
    output wire feeder_start_valid,
    input wire feeder_start_ready,
    output wire [`KWT_ROW_GROUP_WIDTH-1:0] feeder_start_row_group,
    output wire feeder_start_w_slot,
    input wire feeder_busy,
    input wire feeder_done,
    input wire feeder_fault,

    // ---- 原计算核的单块启动与状态 ----
    output wire core_start_valid,
    input wire core_start_ready,
    output wire [`KWT_ROW_MASK_WIDTH-1:0] core_start_row_mask,
    output wire core_start_is_final_block,
    input wire core_busy,
    input wire core_block_done,

    // ---- 结果模块的会话、分配与发布 ----
    output wire result_begin_valid,
    input wire result_begin_ready,
    output wire [`KWT_TASK_ID_WIDTH-1:0] result_begin_task_id,
    output wire result_alloc_valid,
    input wire result_alloc_ready,
    output wire [`KWT_TASK_ID_WIDTH-1:0] result_alloc_task_id,
    output wire [`KWT_RESULT_ROW_WIDTH-1:0] result_alloc_row,
    output wire [`KWT_CMD_TILE_WIDTH-1:0] result_alloc_tile,
    output wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0] result_alloc_count,
    output wire result_alloc_final,
    output wire result_publish_valid,
    input wire result_publish_ready,
    input wire [`KWT_RESULT_BLOCK_COUNT-1:0] result_owned,
    input wire result_response_empty,
    input wire result_compute_done,
    input wire result_fault,
    input wire [`KWT_ERROR_CODE_WIDTH-1:0] result_error_code,

    // ---- 后续ICB接口提供的全局边界条件 ----
    input wire input_fifo_empty, // 包含pair半项等未执行输入；当前accept时不能报空
    input wire transport_empty, // ICB读/写/ACK响应及本拍新accept均已排除
    input wire abort_req, // 单拍中止；接口同时停止接收并安排旧FIFO清理
    output wire result_abort_req,
    input wire result_abort_done,
    output wire abort_pending,
    output reg abort_done,
    output wire worker_rst_n,

    // ---- 状态观察；不等同于guard COMPLETE ----
    output reg session_valid,
    output reg [`KWT_TASK_ID_WIDTH-1:0] task_id,
    output reg [`KWT_LAYER_ID_WIDTH-1:0] layer_id,
    output wire busy,
    output wire compute_done,
    output wire task_done,
    output wire active_w_slot, // 顶层bias读槽也连接此身份
    output wire [`KWT_ROW_GROUP_WIDTH-1:0] current_row_group,
    output wire [`KWT_TILE_ID_WIDTH-1:0] current_tile,
    output reg fault,
    output reg [`KWT_ERROR_CODE_WIDTH-1:0] error_code
);

    // ============================================================
    // 1. 状态与块身份：三段式FSM，计数/握手记录单独寄存
    // ============================================================
    localparam [`KWT_TASK_STATE_WIDTH-1:0]
        S_IDLE=0, S_WAIT_START=1, S_WAIT_TILE=2, S_ACTIVATE=3,
        S_ALLOC=4, S_START_BLOCK=5, S_RUN=6, S_PUBLISH=7,
        S_RELEASE=8, S_DRAIN=9, S_COMPLETE=10, S_FAULT=11;
    reg [`KWT_TASK_STATE_WIDTH-1:0] state, next_state;
    reg [`KWT_ROW_GROUP_WIDTH-1:0] row_group;
    reg [`KWT_TILE_ID_WIDTH-1:0] tile;
    reg active_slot;
    reg feeder_started, core_started; // 启动握手分别记忆，不要求同拍ready
    reg feed_done_seen, core_done_seen; // 单拍完成脉冲保持到本块发布
    reg abort_wait, result_abort_seen;

    wire source_fault, identity_bad, blocked, run_enable;
    wire tile_in_slot0, tile_in_slot1, tile_available;
    wire last_row_group, final_block, local_begin_safe, drained;
    wire begin_fire, start_fire, activate_fire, alloc_fire;
    wire feeder_start_fire, core_start_fire, publish_fire, release_fire;
    assign source_fault = load_fault || feeder_fault || result_fault;
    assign identity_bad = session_valid && (!load_session_valid ||
        (load_session_task_id != task_id) || (load_session_layer_id != layer_id));
    assign blocked = fault || source_fault || identity_bad;
    assign abort_pending = abort_req || abort_wait;
    assign run_enable = rst_n && !abort_pending && !blocked;
    // 子模块错误被本模块锁存；worker同步复位后即使原错误消失，也不会继续旧任务。
    assign worker_rst_n = rst_n && !abort_pending && !blocked;
    assign result_abort_req = rst_n && abort_req;

    assign tile_in_slot0 = (load_slot_state[0 +: `KWT_SLOT_STATE_WIDTH] == `KWT_SLOT_READY) &&
                          (load_slot_tile[0 +: `KWT_TILE_ID_WIDTH] == tile);
    assign tile_in_slot1 = (load_slot_state[`KWT_SLOT_STATE_WIDTH +: `KWT_SLOT_STATE_WIDTH] == `KWT_SLOT_READY) &&
                          (load_slot_tile[`KWT_TILE_ID_WIDTH +: `KWT_TILE_ID_WIDTH] == tile);
    assign tile_available = load_x_ready && (tile_in_slot0 || tile_in_slot1);
    assign last_row_group = (row_group == (`KWT_ROW_GROUP_COUNT-1));
    assign final_block = last_row_group && (tile == (`KWT_TILE_COUNT-1));
    assign active_w_slot = active_slot;
    assign current_row_group = row_group;
    assign current_tile = tile;

    // ============================================================
    // 2. 会话边界与完成：BEGIN必须让装载/结果/任务三者同沿成交
    // ============================================================
    // 不要求load_command_empty：当前BEGIN本来就占据装载q；也不要求后续FIFO空，
    // 因为有序FIFO中BEGIN之后可以排着新会话X命令。旧结果和响应必须先排空。
    assign local_begin_safe = run_enable &&
        ((state == S_IDLE) || (state == S_DRAIN) || (state == S_COMPLETE)) &&
        !core_busy && !feeder_busy && (result_owned == 0) &&
        result_response_empty && transport_empty;
    // result_begin_valid不能依赖result_begin_ready，否则可能形成互相等待。
    assign result_begin_valid = load_begin_valid && local_begin_safe;
    assign result_begin_task_id = load_begin_task_id;
    assign load_begin_ready = local_begin_safe && result_begin_ready;
    assign begin_fire = load_begin_valid && load_begin_ready;
    assign load_start_ready = run_enable && (state == S_WAIT_START) &&
                              load_x_ready && tile_available;
    assign start_fire = load_start_valid && load_start_ready;
    assign drained = !core_busy && !feeder_busy && (result_owned == 0) &&
        result_response_empty && load_command_empty && input_fifo_empty && transport_empty;
    assign compute_done = run_enable && session_valid && result_compute_done;
    // 最后publish后仍要释放W槽、读完结果、ACK及输入/响应排空，才进入COMPLETE。
    assign task_done = run_enable && session_valid && (state == S_COMPLETE) &&
                       result_compute_done && drained;
    assign busy = session_valid && !task_done;

    // ============================================================
    // 3. 组合输出：各请求在对应状态保持，握手后不再重复发送
    // ============================================================
    assign load_activate_valid = run_enable && (state == S_ACTIVATE);
    assign load_activate_slot = active_slot;
    assign load_release_valid = run_enable && (state == S_RELEASE);
    assign load_release_slot = active_slot;
    assign result_alloc_valid = run_enable && (state == S_ALLOC);
    assign result_alloc_task_id = task_id;
    // row_group0..24映射全局row0=0,4,..96；赋值左侧7位接收完整乘积。
    assign result_alloc_row = row_group * `KWT_PM;
    assign result_alloc_tile = {{(`KWT_CMD_TILE_WIDTH-`KWT_TILE_ID_WIDTH){1'b0}},tile};
    assign result_alloc_count = last_row_group
        ? ((`KWT_M % `KWT_PM)*`KWT_BLOCK_COLS) : `KWT_RESULT_WORDS;
    assign result_alloc_final = final_block;
    assign feeder_start_valid = run_enable && (state == S_START_BLOCK) && !feeder_started;
    assign feeder_start_row_group = row_group;
    assign feeder_start_w_slot = active_slot;
    assign core_start_valid = run_enable && (state == S_START_BLOCK) && !core_started;
    assign core_start_row_mask = last_row_group
        ? ({`KWT_ROW_MASK_WIDTH{1'b1}} >> (`KWT_PM-(`KWT_M % `KWT_PM)))
        : {`KWT_ROW_MASK_WIDTH{1'b1}};
    assign core_start_is_final_block = final_block;
    assign result_publish_valid = run_enable && (state == S_PUBLISH);
    assign activate_fire = load_activate_valid && load_activate_ready;
    assign alloc_fire = result_alloc_valid && result_alloc_ready;
    assign feeder_start_fire = feeder_start_valid && feeder_start_ready;
    assign core_start_fire = core_start_valid && core_start_ready;
    assign publish_fire = result_publish_valid && result_publish_ready;
    assign release_fire = load_release_valid && load_release_ready;

    // ============================================================
    // 4. FSM第一段：当前状态寄存
    // ============================================================
    always @(posedge clk) begin
        if (!rst_n) state <= S_IDLE;
        else if (abort_pending) state <= S_IDLE;
        else if (blocked) state <= S_FAULT;
        else if (begin_fire) state <= S_WAIT_START;
        else state <= next_state;
    end

    // FSM第二段：组合下一状态，所有等待默认保持
    always @(*) begin
        next_state = state;
        case (state)
            S_IDLE: begin end
            S_WAIT_START: if (start_fire) next_state = S_WAIT_TILE;
            S_WAIT_TILE: if (tile_available) next_state = S_ACTIVATE;
            S_ACTIVATE: if (activate_fire) next_state = S_ALLOC;
            S_ALLOC: if (alloc_fire) next_state = S_START_BLOCK;
            S_START_BLOCK: begin
                if ((feeder_started || feeder_start_fire) && (core_started || core_start_fire))
                    next_state = S_RUN;
            end
            S_RUN: begin
                // feed_done不能代替block_done；核还要排空乘积并量化全部结果。
                if ((feed_done_seen || feeder_done) && (core_done_seen || core_block_done))
                    next_state = S_PUBLISH;
            end
            S_PUBLISH: if (publish_fire) begin
                if (last_row_group) next_state = S_RELEASE;
                else next_state = S_ALLOC;
            end
            S_RELEASE: if (release_fire) begin
                if (tile == (`KWT_TILE_COUNT-1)) next_state = S_DRAIN;
                else next_state = S_WAIT_TILE;
            end
            S_DRAIN: if (result_compute_done && drained) next_state = S_COMPLETE;
            S_COMPLETE: begin end
            S_FAULT: begin end // 只有共同复位或ABORT可恢复
            default: next_state = S_IDLE;
        endcase
    end
    // FSM第三段为上面的assign控制输出，不给valid额外加寄存级。

    // ============================================================
    // 5. 身份/计数/握手记录与中止恢复
    // ============================================================
    always @(posedge clk) begin
        if (!rst_n) begin
            session_valid <= 1'b0;
            task_id <= 0;
            layer_id <= 0;
            row_group <= 0;
            tile <= 0;
            active_slot <= 1'b0;
            feeder_started <= 1'b0;
            core_started <= 1'b0;
            feed_done_seen <= 1'b0;
            core_done_seen <= 1'b0;
            abort_wait <= 1'b0;
            result_abort_seen <= 1'b0;
            abort_done <= 1'b0;
            fault <= 1'b0;
            error_code <= 0;
        end else begin
            abort_done <= 1'b0;
            if (abort_req) begin
                abort_wait <= 1'b1;
                result_abort_seen <= 1'b0;
            end else if (abort_wait) begin
                if (result_abort_done) result_abort_seen <= 1'b1;
                // 接口须在abort_pending期间排响应并清旧FIFO；不能等worker继续执行旧命令。
                if ((result_abort_seen || result_abort_done) && transport_empty && input_fifo_empty) begin
                    abort_wait <= 1'b0;
                    result_abort_seen <= 1'b0;
                    abort_done <= 1'b1;
                    session_valid <= 1'b0;
                    task_id <= 0;
                    layer_id <= 0;
                    row_group <= 0;
                    tile <= 0;
                    active_slot <= 1'b0;
                    feeder_started <= 1'b0;
                    core_started <= 1'b0;
                    feed_done_seen <= 1'b0;
                    core_done_seen <= 1'b0;
                    fault <= 1'b0;
                    error_code <= 0;
                end
            end else if (!fault && (source_fault || identity_bad)) begin
                fault <= 1'b1;
                if (load_fault) error_code <= load_error_code;
                else if (feeder_fault) error_code <= `KWT_TASK_ERR_FEED;
                else if (result_fault) error_code <= result_error_code;
                else error_code <= `KWT_TASK_ERR_SESSION;
            end else if (begin_fire) begin
                session_valid <= 1'b1;
                task_id <= load_begin_task_id;
                layer_id <= load_begin_layer_id;
                row_group <= 0;
                tile <= 0;
                active_slot <= 1'b0;
                feeder_started <= 1'b0;
                core_started <= 1'b0;
                feed_done_seen <= 1'b0;
                core_done_seen <= 1'b0;
            end else if (run_enable) begin
                if ((state == S_WAIT_TILE) && tile_available)
                    active_slot <= tile_in_slot0 ? 1'b0 : 1'b1;
                if (alloc_fire) begin
                    feeder_started <= 1'b0;
                    core_started <= 1'b0;
                    feed_done_seen <= 1'b0;
                    core_done_seen <= 1'b0;
                end
                if (feeder_start_fire) feeder_started <= 1'b1;
                if (core_start_fire) core_started <= 1'b1;
                if ((state == S_START_BLOCK) || (state == S_RUN)) begin
                    if (feeder_started && feeder_done) feed_done_seen <= 1'b1;
                    if (core_started && core_block_done) core_done_seen <= 1'b1;
                end
                if (publish_fire && !last_row_group) row_group <= row_group + 1'b1;
                if (release_fire && (tile != (`KWT_TILE_COUNT-1))) begin
                    tile <= tile + 1'b1;
                    row_group <= 0;
                end
            end
        end
    end
endmodule
`default_nettype wire
