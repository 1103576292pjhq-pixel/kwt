`include "kwt_control_config.vh"
`default_nettype none

// 单个4×16计算块的供数器：按k0/g0..g3、...、k63/g3发出256组。
// 只负责读，不例化存储或计算核，不管理装载、结果块、bias和任务完成。
// 上层先确认数据装载完整，并在整块计算（含量化）期间保护活动W/bias槽。
// 上层分别协调本模块和点积核的start握手；out_*连接核in_*。
// 本模块可先于核RUN准备数据，out_ready=0时缓存会自动限制后续请求。
// wrapper必须为固定L1：E0接受读，E1沿本模块采样返回；两者共同同步复位。
// 上层将读地址/使能与装载写口仲裁；不得静默拒绝本模块发出的读。
module kwt_operand_feeder (
    input wire clk,
    input wire rst_n, // 低有效同步复位，取消全部缓存和在途读

    // ---- 启动握手：启动时保存块身份，运行中不跟随外部输入变化 ----
    input wire start_valid, // 阻塞时保持行组号和槽号
    output wire start_ready,
    input wire [`KWT_ROW_GROUP_WIDTH-1:0] start_row_group, // 0..24，不是row0
    input wire start_w_slot, // 本块使用的W槽0或1

    // ---- X读口：4个bank各存一行 ----
    output reg [`KWT_X_BANK_COUNT-1:0] x_rd_en, // g0才读X，尾行屏蔽bank3
    output reg [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] x_addr,
    input wire [`KWT_X_GROUP_WIDTH-1:0] x_rd_data,
    input wire [`KWT_X_BANK_COUNT-1:0] x_rd_valid,
    input wire [`KWT_X_BANK_COUNT-1:0] x_access_error,

    // ---- W读口：只读取活动槽的四bank ----
    output reg [`KWT_W_BANK_COUNT-1:0] w_rd_en,
    output reg [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] w_addr,
    input wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0] w_rd_data,
    input wire [`KWT_W_BANK_COUNT-1:0] w_rd_valid,
    input wire [`KWT_W_BANK_COUNT-1:0] w_access_error,

    // ---- 交付握手：out_*连接点积核in_* ----
    output wire out_valid, // 与out_ready同时为1才交付一组
    input wire out_ready, // 接计算核in_ready
    output wire [`KWT_X_GROUP_WIDTH-1:0] out_x,
    output wire [`KWT_W_GROUP_WIDTH-1:0] out_w,

    // ---- 状态输出 ----
    output reg busy, // 仅表示本块供数未结束，不代表核仍在计算
    output reg feed_done, // 最后一组交付后的单拍脉冲，不是block_done
    output reg fault // 非法启动或L1返回异常后锁存，须共同复位恢复
);

    // ============================================================
    // 1. 块身份：启动时保存，运行中不跟随外部输入变化
    // ============================================================
    reg [`KWT_ROW_GROUP_WIDTH-1:0] row_group;
    reg w_slot;
    reg [`KWT_ROW_MASK_WIDTH-1:0] row_mask;
    // issued在请求接受时推进；delivered在核实际接收时推进，两者不能混用。
    reg [`KWT_GROUP_COUNT_WIDTH-1:0] issued, delivered; // 0..256
    wire [`KWT_K_INDEX_WIDTH-1:0] request_k;
    wire [`KWT_CTX_WIDTH-1:0] request_g;
    assign request_g = issued[0 +: `KWT_CTX_WIDTH];
    assign request_k = issued[`KWT_CTX_WIDTH +: `KWT_K_INDEX_WIDTH];

    // ============================================================
    // 2. 一拍在途标签：在发请求的沿保存，下一沿与返回配对
    // ============================================================
    reg pending;
    reg pending_x; // 该请求是否为g0，因而同时读取X
    reg [`KWT_X_GROUP_WIDTH-1:0] x_hold; // 当前k的X，供g1/g2/g3复用
    reg [`KWT_X_GROUP_WIDTH-1:0] masked_x;
    wire [`KWT_W_GROUP_WIDTH-1:0] returned_w;
    wire [`KWT_W_BANKS_PER_SLOT-1:0] selected_w_valid, selected_w_error;
    assign returned_w = w_rd_data[w_slot*`KWT_W_GROUP_WIDTH +: `KWT_W_GROUP_WIDTH];
    assign selected_w_valid = w_rd_valid[w_slot*`KWT_W_BANKS_PER_SLOT +: `KWT_W_BANKS_PER_SLOT];
    assign selected_w_error = w_access_error[w_slot*`KWT_W_BANKS_PER_SLOT +: `KWT_W_BANKS_PER_SLOT];

    // ============================================================
    // 3. 两项操作数队列：每项保存完整X/W，避免后续x_hold更新影响旧组
    // ============================================================
    reg [`KWT_X_GROUP_WIDTH-1:0] x_queue [0:`KWT_FEED_DEPTH-1];
    reg [`KWT_W_GROUP_WIDTH-1:0] w_queue [0:`KWT_FEED_DEPTH-1];
    reg read_ptr, write_ptr; // 固定两项，翻转一位即可循环
    reg [`KWT_FEED_COUNT_WIDTH-1:0] count;

    // ============================================================
    // 4. 控制信号：握手、异常判定与发请求名额
    // ============================================================
    wire start_fire, pop, push, issue, return_bad;
    wire [`KWT_FEED_COUNT_WIDTH:0] reserved; // 3位，避免count+pending截断
    assign start_ready = rst_n && !busy && !fault;
    assign start_fire = start_valid && start_ready;
    // 只检查本次请求涉及的bank；另一W槽的装载错误由装载控制处理。
    // 固定L1缺valid不能一直等待，否则会把下一笔返回错认成这一笔。
    assign return_bad = pending &&
        ((!(&selected_w_valid)) || (|selected_w_error) ||
         (pending_x && (((x_rd_valid & row_mask) != row_mask) ||
                        (|(x_access_error & row_mask)))));
    assign out_valid = rst_n && busy && !fault && !return_bad && (count != 0);
    assign out_x = x_queue[read_ptr]; // 无valid时不使用，故无需复位数据阵列
    assign out_w = w_queue[read_ptr];
    assign pop = out_valid && out_ready;
    assign push = rst_n && busy && pending && !fault && !return_bad;
    // 已缓存+在途都占名额。本沿pop释放一项，才能允许再预留一次读返回。
    // 这样ready突然拉低时，已在途返回仍有空间，稳态也可每拍交付一组。
    assign reserved = {1'b0, count} + pending;
    assign issue = rst_n && busy && !fault && !return_bad &&
                   (issued < `KWT_GROUPS_PER_BLOCK) &&
                   ((reserved < `KWT_FEED_DEPTH) || pop);

    // ============================================================
    // 5. 组合地址与请求：X={行组,k}，W={g,k}
    // ============================================================
    // 固定K=64，因此拼接等价于行组*64+k、g*64+k，不需要乘法器。
    integer xb, wb;
    always @(*) begin
        x_rd_en = {`KWT_X_BANK_COUNT{1'b0}};
        w_rd_en = {`KWT_W_BANK_COUNT{1'b0}};
        x_addr = {(`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH){1'b0}};
        w_addr = {(`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH){1'b0}};
        masked_x = {`KWT_X_GROUP_WIDTH{1'b0}};
        for (xb=0; xb<`KWT_X_BANK_COUNT; xb=xb+1) begin
            x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH] = {row_group, request_k};
            x_rd_en[xb] = issue && (request_g == 0) && row_mask[xb];
            // 无效第四行显式补零，不把未装载SRAM的未知值送入核。
            if (row_mask[xb])
                masked_x[xb*`KWT_X_WIDTH +: `KWT_X_WIDTH] = x_rd_data[xb*`KWT_X_WIDTH +: `KWT_X_WIDTH];
        end
        for (wb=0; wb<`KWT_W_BANK_COUNT; wb=wb+1) begin
            w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH] = {request_g, request_k};
            w_rd_en[wb] = issue && ((wb / `KWT_W_BANKS_PER_SLOT) == w_slot);
        end
    end

    // ============================================================
    // 6. 时序状态：计数、返回捕获和队列读写
    // ============================================================
    always @(posedge clk) begin
        if (!rst_n) begin
            busy <= 1'b0;
            feed_done <= 1'b0;
            fault <= 1'b0;
            row_group <= 0;
            w_slot <= 1'b0;
            row_mask <= 0;
            issued <= 0;
            delivered <= 0;
            pending <= 1'b0;
            pending_x <= 1'b0;
            x_hold <= 0;
            read_ptr <= 1'b0;
            write_ptr <= 1'b0;
            count <= 0;
        end else begin
            feed_done <= 1'b0;
            if (start_fire) begin
                if (start_row_group >= `KWT_ROW_GROUP_COUNT) begin
                    fault <= 1'b1; // 不发越界请求；错误启动不产生完成
                end else begin
                    busy <= 1'b1;
                    row_group <= start_row_group;
                    w_slot <= start_w_slot;
                    // 行组24对应row0=96，仅行96/97/98有效。
                    row_mask <= (start_row_group == (`KWT_ROW_GROUP_COUNT-1))
                        ? ({`KWT_ROW_MASK_WIDTH{1'b1}} >> 1)
                        : {`KWT_ROW_MASK_WIDTH{1'b1}};
                    issued <= 0;
                    delivered <= 0;
                    pending <= 1'b0;
                    pending_x <= 1'b0;
                    read_ptr <= 1'b0;
                    write_ptr <= 1'b0;
                    count <= 0;
                end
            end else if (busy) begin
                if (return_bad) begin
                    fault <= 1'b1;
                    busy <= 1'b0;
                    pending <= 1'b0;
                    count <= 0; // 丢弃本块，禁止继续向核提供错配的数据
                end else begin
                    pending <= issue;
                    if (issue) begin
                        issued <= issued + 1'b1;
                        pending_x <= (request_g == 0);
                    end
                    if (push) begin
                        // g0用本次返回并更新x_hold；后续g使用保存的同一个k。
                        x_queue[write_ptr] <= pending_x ? masked_x : x_hold;
                        w_queue[write_ptr] <= returned_w;
                        write_ptr <= !write_ptr;
                        if (pending_x) x_hold <= masked_x;
                    end
                    if (pop) begin
                        read_ptr <= !read_ptr;
                        delivered <= delivered + 1'b1;
                        if (delivered == (`KWT_GROUPS_PER_BLOCK-1)) begin
                            busy <= 1'b0;
                            feed_done <= 1'b1;
                        end
                    end
                    case ({push, pop})
                        2'b10: count <= count + 1'b1;
                        2'b01: count <= count - 1'b1;
                        default: count <= count; // 同进同出或都不发生，占用不变
                    endcase
                end
            end
        end
    end
endmodule
`default_nettype wire
