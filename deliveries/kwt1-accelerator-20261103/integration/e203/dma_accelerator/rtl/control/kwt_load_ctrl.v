`include "kwt_control_config.vh"
`default_nettype none

// X/W/bias装载控制：接收ICB/FIFO解析后的命令，不直接接CPU总线地址。
// 职责：先检查完整容器，再按逻辑bank写入；记录装载完整性和W槽生命周期。
// 不例化存储/供数器/计算核，不读取X/W或CPU结果，不生成整机task_done。
// 固定顺序：BEGIN -> X6336 -> OPEN0 -> W1024/bias16 -> COMMIT0 -> START；
// 随后可装载tile1..15，活动槽读取和另一槽写入由顶层连接并行进行。
// X、W、bias各自必须按index从0递增；W和bias两条流可交错装载。
// 命令进入单项q后才执行语义检查；MMIO入FIFO成功不等于装载成功。
// 两种等待：BEGIN等整机会话可重开，OPEN等空槽，START等任务调度器接收。
// fault锁存后停止执行/接收；恢复须由上层统一取消计算并同步复位控制状态。
module kwt_load_ctrl (
    input wire clk,
    input wire rst_n, // 同步低有效复位；清状态和计数，不清SRAM/bias

    // ---- 上游命令：valid受阻时保持所有字段 ----
    input wire cmd_valid,
    output wire cmd_ready,
    input wire [`KWT_CMD_OP_WIDTH-1:0] cmd_op,
    input wire [`KWT_LAYER_ID_WIDTH-1:0] cmd_layer_id,
    input wire [`KWT_TASK_ID_WIDTH-1:0] cmd_task_id,
    input wire [`KWT_CMD_TILE_WIDTH-1:0] cmd_tile_id,
    input wire [`KWT_CMD_INDEX_WIDTH-1:0] cmd_index,
    input wire signed [`KWT_CMD_DATA_WIDTH-1:0] cmd_data,

    // ---- 与后续任务控制的命令握手 ----
    // begin_ready必须涵盖旧计算、结果owner及相关事务已可安全切换会话。
    // 新BEGIN握手只清本模块状态；上层同沿完成其他模块的新会话初始化。
    output wire begin_valid,
    input wire begin_ready,
    output wire [`KWT_TASK_ID_WIDTH-1:0] begin_task_id,
    output wire [`KWT_LAYER_ID_WIDTH-1:0] begin_layer_id,
    output wire start_valid, // 首tile提交后请求开始整个矩阵任务
    input wire start_ready, // 不是直接连接点积核的start_ready

    // ---- W槽事件：任务控制必须保持valid/slot直到ready握手 ----
    input wire activate_valid,
    input wire activate_slot, // READY -> ACTIVE；一次只有一个ACTIVE槽
    output wire activate_ready,
    input wire release_valid,
    input wire release_slot, // 最后行组成功publish后才ACTIVE -> FREE
    output wire release_ready,

    // ---- 连接存储wrapper的写通路：合法执行沿才有使能 ----
    output reg [`KWT_X_BANK_COUNT-1:0] x_wr_en,
    output reg [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] x_addr,
    output reg [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0] x_wr_data,
    output reg [`KWT_W_BANK_COUNT-1:0] w_wr_en,
    output reg [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] w_addr,
    output reg [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] w_wr_data,
    output wire bias_wr_en,
    output wire bias_wr_slot,
    output wire [`KWT_BIAS_ADDR_WIDTH-1:0] bias_wr_addr,
    output wire signed [`KWT_BIAS_WIDTH-1:0] bias_wr_data,

    // ---- 状态输出：供任务控制/状态寄存器使用 ----
    output reg session_valid,
    output reg [`KWT_TASK_ID_WIDTH-1:0] session_task_id,
    output reg [`KWT_LAYER_ID_WIDTH-1:0] session_layer_id,
    output reg task_started, // START握手后保持，直到新BEGIN或复位
    output wire x_ready,
    output wire [`KWT_W_SLOT_COUNT*`KWT_SLOT_STATE_WIDTH-1:0] slot_state,
    output wire [`KWT_W_SLOT_COUNT*`KWT_TILE_ID_WIDTH-1:0] slot_tile,
    output wire command_empty, // 仅表示本地q为空，不包括上游FIFO
    output reg command_done, // 一条合法命令执行后的单拍，非CPU总线响应
    output reg fault,
    output reg [`KWT_ERROR_CODE_WIDTH-1:0] error_code
);

    // ============================================================
    // 1. 单项命令q：接收与执行分离，阻塞期间字段保持
    // ============================================================
    reg q_valid;
    reg [`KWT_CMD_OP_WIDTH-1:0] q_op;
    reg [`KWT_LAYER_ID_WIDTH-1:0] q_layer_id;
    reg [`KWT_TASK_ID_WIDTH-1:0] q_task_id;
    reg [`KWT_CMD_TILE_WIDTH-1:0] q_tile_id;
    reg [`KWT_CMD_INDEX_WIDTH-1:0] q_index;
    reg signed [`KWT_CMD_DATA_WIDTH-1:0] q_data;

    // ============================================================
    // 2. 装载进度与槽身份；只允许一个槽处于LOADING
    // ============================================================
    reg [`KWT_X_LOAD_COUNT_WIDTH-1:0] x_count; // 0..6336
    reg [`KWT_W_LOAD_COUNT_WIDTH-1:0] w_count; // 当前装载槽0..1024
    reg [`KWT_BIAS_LOAD_COUNT_WIDTH-1:0] bias_count; // 当前装载槽0..16
    reg [`KWT_TILE_COUNT_WIDTH-1:0] next_tile; // 下一次OPEN的tile，16为已全开完
    reg load_open, load_slot;
    reg [`KWT_SLOT_STATE_WIDTH-1:0] slot_state_reg [0:`KWT_W_SLOT_COUNT-1];
    reg [`KWT_TILE_ID_WIDTH-1:0] slot_tile_reg [0:`KWT_W_SLOT_COUNT-1];

    wire free_exists, free_slot, active_exists, first_tile_ready;
    assign free_exists = (slot_state_reg[0] == `KWT_SLOT_FREE) ||
                         (slot_state_reg[1] == `KWT_SLOT_FREE);
    assign free_slot = (slot_state_reg[0] == `KWT_SLOT_FREE) ? 1'b0 : 1'b1;
    assign active_exists = (slot_state_reg[0] == `KWT_SLOT_ACTIVE) ||
                           (slot_state_reg[1] == `KWT_SLOT_ACTIVE);
    assign first_tile_ready = ((slot_state_reg[0] == `KWT_SLOT_READY) && (slot_tile_reg[0] == 0)) ||
                              ((slot_state_reg[1] == `KWT_SLOT_READY) && (slot_tile_reg[1] == 0));
    assign slot_state = {slot_state_reg[1],slot_state_reg[0]};
    assign slot_tile = {slot_tile_reg[1],slot_tile_reg[0]};
    assign x_ready = session_valid && !fault && (x_count == `KWT_X_WORD_COUNT);
    assign command_empty = !q_valid;

    // 当前装载槽的组合选读；集中命名便于阅读命令检查部分。
    wire [`KWT_SLOT_STATE_WIDTH-1:0] loading_state;
    wire [`KWT_TILE_ID_WIDTH-1:0] loading_tile;
    wire [`KWT_CMD_TILE_WIDTH-1:0] loading_tile_extended;
    assign loading_state = slot_state_reg[load_slot];
    assign loading_tile = slot_tile_reg[load_slot];
    assign loading_tile_extended = {{(`KWT_CMD_TILE_WIDTH-`KWT_TILE_ID_WIDTH){1'b0}},loading_tile};

    // X/W检查完整32位是否为signed16的正确符号扩展，再取低16位。
    // bias端口本身就是完整signed32，所有位图均合法，不重复做范围检查。
    wire scalar_fits;
    assign scalar_fits = (q_data == {{(`KWT_CMD_DATA_WIDTH-`KWT_X_WIDTH){q_data[`KWT_X_WIDTH-1]}},q_data[`KWT_X_WIDTH-1:0]});

    // ============================================================
    // 3. 命令合法性：bad表示错误，wait表示合法但暂时不能执行
    // ============================================================
    reg command_bad, command_wait;
    reg [`KWT_ERROR_CODE_WIDTH-1:0] command_error;
    always @(*) begin
        command_bad = 1'b0;
        command_wait = 1'b0;
        command_error = `KWT_LOAD_ERR_OP;
        if (q_op == `KWT_CMD_BEGIN) begin
            command_wait = !begin_ready;
        end else if (!session_valid) begin
            command_bad = 1'b1;
            command_error = `KWT_LOAD_ERR_SESSION;
        end else if ((q_task_id != session_task_id) || (q_layer_id != session_layer_id)) begin
            command_bad = 1'b1;
            command_error = `KWT_LOAD_ERR_ID;
        end else begin
            case (q_op)
                `KWT_CMD_X: begin
                    command_error = `KWT_LOAD_ERR_X;
                    command_bad = task_started || load_open || (next_tile != 0) ||
                        (q_tile_id != 0) || (x_count >= `KWT_X_WORD_COUNT) ||
                        (q_index != x_count) || !scalar_fits;
                end
                `KWT_CMD_OPEN: begin
                    command_error = `KWT_LOAD_ERR_OPEN;
                    // START前只允许OPEN0；否则OPEN1可能挡住队列后面的START。
                    command_bad = !x_ready || load_open || (next_tile >= `KWT_TILE_COUNT) ||
                        (q_tile_id != next_tile) || (!task_started && (next_tile != 0));
                    command_wait = !free_exists;
                end
                `KWT_CMD_W: begin
                    command_error = `KWT_LOAD_ERR_W;
                    command_bad = !load_open || (loading_state != `KWT_SLOT_LOADING) ||
                        (q_tile_id != loading_tile_extended) ||
                        (w_count >= `KWT_W_WORDS_PER_TILE) || (q_index != w_count) || !scalar_fits;
                end
                `KWT_CMD_BIAS: begin
                    command_error = `KWT_LOAD_ERR_BIAS;
                    command_bad = !load_open || (loading_state != `KWT_SLOT_LOADING) ||
                        (q_tile_id != loading_tile_extended) ||
                        (bias_count >= `KWT_BIAS_WORDS_PER_SLOT) || (q_index != bias_count);
                end
                `KWT_CMD_COMMIT: begin
                    command_error = `KWT_LOAD_ERR_COMMIT;
                    command_bad = !load_open || (loading_state != `KWT_SLOT_LOADING) ||
                        (q_tile_id != loading_tile_extended) ||
                        (w_count != `KWT_W_WORDS_PER_TILE) || (bias_count != `KWT_BIAS_WORDS_PER_SLOT);
                end
                `KWT_CMD_START: begin
                    command_error = `KWT_LOAD_ERR_START;
                    command_bad = task_started || !x_ready || load_open ||
                                  (next_tile != 1) || !first_tile_ready;
                    command_wait = !start_ready;
                end
                default: begin
                    command_bad = 1'b1;
                    command_error = `KWT_LOAD_ERR_OP;
                end
            endcase
        end
    end

    wire execute, retire, accept, begin_fire, activate_fire, release_fire;
    // 错误命令也退休，但不execute；错误检查优先于等待，避免非法命令永久挂起。
    assign retire = rst_n && q_valid && !fault && (command_bad || !command_wait);
    assign execute = retire && !command_bad;
    // 允许旧q执行与新命令接收同沿；若旧q非法，停止接收下一条。
    assign cmd_ready = rst_n && !fault && (!q_valid || (retire && !command_bad));
    assign accept = cmd_valid && cmd_ready;
    // valid不能依赖对方ready；execute则只在握手沿为真。
    assign begin_valid = rst_n && q_valid && !fault && !command_bad && (q_op == `KWT_CMD_BEGIN);
    assign begin_task_id = q_task_id;
    assign begin_layer_id = q_layer_id;
    assign start_valid = rst_n && q_valid && !fault && !command_bad && (q_op == `KWT_CMD_START);
    assign begin_fire = execute && (q_op == `KWT_CMD_BEGIN);
    assign activate_ready = rst_n && !fault && session_valid && task_started && !begin_valid &&
                            !(q_valid && command_bad) && !active_exists &&
                            (slot_state_reg[activate_slot] == `KWT_SLOT_READY);
    assign release_ready = rst_n && !fault && session_valid && task_started && !begin_valid &&
                           !(q_valid && command_bad) &&
                           (slot_state_reg[release_slot] == `KWT_SLOT_ACTIVE);
    assign activate_fire = activate_valid && activate_ready;
    assign release_fire = release_valid && release_ready;

    // q的数据字段不复位：q_valid=0时不可使用；每次接收都会完整覆盖。
    always @(posedge clk) begin
        if (!rst_n) q_valid <= 1'b0;
        else begin
            if (retire) q_valid <= 1'b0;
            if (accept) begin
                q_valid <= 1'b1;
                q_op <= cmd_op;
                q_layer_id <= cmd_layer_id;
                q_task_id <= cmd_task_id;
                q_tile_id <= cmd_tile_id;
                q_index <= cmd_index;
                q_data <= cmd_data;
            end
        end
    end

    // ============================================================
    // 4. 写地址映射（组合）：输入索引先通过上面的完整范围/顺序检查
    // ============================================================
    // X输入index=row*64+k：bank=row%4=index[7:6]；地址={row/4,k}。
    // W输入index=k*16+c：bank=c%4=index[1:0]；地址={c/4,k}。
    // q_index的高位已参与完整比较，不能仅截低位后再做合法性检查。
    integer xb, wb;
    always @(*) begin
        x_wr_en = 0;
        x_addr = 0;
        x_wr_data = 0;
        w_wr_en = 0;
        w_addr = 0;
        w_wr_data = 0;
        for (xb=0; xb<`KWT_X_BANK_COUNT; xb=xb+1) begin
            x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH] =
                {q_index[`KWT_X_LOAD_COUNT_WIDTH-1:`KWT_K_INDEX_WIDTH+`KWT_ROW_INDEX_WIDTH],
                 q_index[0 +: `KWT_K_INDEX_WIDTH]};
            x_wr_data[xb*`KWT_X_WIDTH +: `KWT_X_WIDTH] = q_data[0 +: `KWT_X_WIDTH];
            x_wr_en[xb] = execute && (q_op == `KWT_CMD_X) &&
                (q_index[`KWT_K_INDEX_WIDTH +: `KWT_ROW_INDEX_WIDTH] == xb);
        end
        for (wb=0; wb<`KWT_W_BANK_COUNT; wb=wb+1) begin
            w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH] =
                {q_index[`KWT_COL_INDEX_WIDTH +: `KWT_CTX_WIDTH],
                 q_index[`KWT_BIAS_ADDR_WIDTH +: `KWT_K_INDEX_WIDTH]};
            w_wr_data[wb*`KWT_W_WIDTH +: `KWT_W_WIDTH] = q_data[0 +: `KWT_W_WIDTH];
            w_wr_en[wb] = execute && (q_op == `KWT_CMD_W) &&
                ((wb / `KWT_W_BANKS_PER_SLOT) == load_slot) &&
                ((wb % `KWT_W_BANKS_PER_SLOT) == q_index[0 +: `KWT_COL_INDEX_WIDTH]);
        end
    end
    assign bias_wr_en = execute && (q_op == `KWT_CMD_BIAS);
    assign bias_wr_slot = load_slot;
    assign bias_wr_addr = q_index[0 +: `KWT_BIAS_ADDR_WIDTH];
    assign bias_wr_data = q_data[0 +: `KWT_BIAS_WIDTH];

    // ============================================================
    // 5. 状态更新（时序）：写入存储与进度推进发生在同一个上升沿
    // ============================================================
    integer si;
    always @(posedge clk) begin
        if (!rst_n) begin
            session_valid <= 1'b0;
            session_task_id <= 0;
            session_layer_id <= 0;
            task_started <= 1'b0;
            x_count <= 0;
            w_count <= 0;
            bias_count <= 0;
            next_tile <= 0;
            load_open <= 1'b0;
            load_slot <= 1'b0;
            command_done <= 1'b0;
            fault <= 1'b0;
            error_code <= 0;
            for (si=0; si<`KWT_W_SLOT_COUNT; si=si+1) begin
                slot_state_reg[si] <= `KWT_SLOT_FREE;
                slot_tile_reg[si] <= 0;
            end
        end else begin
            command_done <= execute;
            if (retire && command_bad) begin
                fault <= 1'b1;
                error_code <= command_error;
            end
            if (begin_fire) begin
                session_valid <= 1'b1;
                session_task_id <= q_task_id;
                session_layer_id <= q_layer_id;
                task_started <= 1'b0;
                x_count <= 0;
                w_count <= 0;
                bias_count <= 0;
                next_tile <= 0;
                load_open <= 1'b0;
                load_slot <= 1'b0;
                for (si=0; si<`KWT_W_SLOT_COUNT; si=si+1) begin
                    slot_state_reg[si] <= `KWT_SLOT_FREE;
                    slot_tile_reg[si] <= 0;
                end
            end else begin
                if (execute) begin
                    case (q_op)
                        `KWT_CMD_X: x_count <= x_count + 1'b1;
                        `KWT_CMD_OPEN: begin
                            load_open <= 1'b1;
                            load_slot <= free_slot;
                            slot_state_reg[free_slot] <= `KWT_SLOT_LOADING;
                            slot_tile_reg[free_slot] <= q_tile_id[0 +: `KWT_TILE_ID_WIDTH];
                            w_count <= 0;
                            bias_count <= 0;
                            next_tile <= next_tile + 1'b1;
                        end
                        `KWT_CMD_W: w_count <= w_count + 1'b1;
                        `KWT_CMD_BIAS: bias_count <= bias_count + 1'b1;
                        `KWT_CMD_COMMIT: begin
                            slot_state_reg[load_slot] <= `KWT_SLOT_READY;
                            load_open <= 1'b0;
                        end
                        `KWT_CMD_START: task_started <= 1'b1;
                        default: begin end
                    endcase
                end
                // 不与OPEN/COMMIT写同一槽：FREE/LOADING/READY/ACTIVE状态前提互斥。
                // 一个ACTIVE槽释放后，下一拍才能激活另一槽，边界保留一拍便于理解。
                if (activate_fire) slot_state_reg[activate_slot] <= `KWT_SLOT_ACTIVE;
                if (release_fire) slot_state_reg[release_slot] <= `KWT_SLOT_FREE;
            end
        end
    end
endmodule
`default_nettype wire
