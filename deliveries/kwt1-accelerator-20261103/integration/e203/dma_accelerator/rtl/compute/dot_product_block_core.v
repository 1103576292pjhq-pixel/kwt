`include "kwt_compute_config.vh"

`default_nettype none

// 连接16路乘法、四上下文累加和单份量化器；不实现SRAM、任务FIFO或结果owner。
//
// 单块时序：IDLE -> CLEAR -> RUN -> FLUSH -> QISSUE/QWAIT -> DONE -> IDLE。
// FSM分为状态寄存、组合下一状态、组合控制输出三段；计数与元数据另行寄存。
// 每块先完成全部乘加，再逐项量化；只有一套acc，不重叠前块量化与后块乘加。
// 本块所有输出成功传给下游后才产生block_done，不表示CPU已经读完或整机完成。
//
// 输入边界是“已经对齐的操作数返回流”，不是SRAM请求接口：
//   每组包含当前k的四个X及当前g的四个W，必须按k0/g0,g1,g2,g3,...,k63/g3到达。
//   group_count只统计in_valid&&in_ready接收的返回组，不是当前SRAM请求计数。
//   由该有序返回流派生ctx/last，再与乘积一起寄存；空拍不推进计数。
//   g0..g3复用同一组X由外围供数器保证，本模块不保存x_hold或产生SRAM地址。
//   一旦启动，RUN期间持续可接收，外围每块只能发出256组所需的读请求。
//   固定延迟SRAM不能根据这里的in_ready随意停止已在途返回，外围必须管理在途量。
//
// bias采用最小组合选读合同：bias_addr给出块内列号，bias_data返回相应signed32。
// 外围保证活动块的bias已就绪，并保持到最后一项量化输入被接收。
// 若以后接同步SRAM，必须适配请求/返回延迟，不能直接把延迟数据接到本端口。
//
// 正式行mask为1111（四行）或0111（最后三行）。全局task/row0/tile由外围保存，
// 本模块输出块内位置。start_is_final_block必须仅在整个矩阵最后一块置1。
// 复位取消未完成计算和输出；恢复后外围必须隔离旧SRAM返回，再开启新块。
module dot_product_block_core (
    // ---- 时钟与复位 ----
    input  wire clk,                 // 时钟
    input  wire rst_n,               // 低有效同步复位，与三个子模块一致

    // ---- 启动握手与块元数据 ----
    input  wire start_valid,         // 请求开始一块；阻塞时保持本组元数据
    output wire start_ready,         // 回到IDLE状态可接受开始请求
    input  wire [`KWT_ROW_MASK_WIDTH-1:0] start_row_mask, // 本块行有效信息
    input  wire start_is_final_block, // 本块是否为整个矩阵最后一块

    // ---- 操作数输入 ----
    input  wire in_valid,            // 一组已经对齐的X/W返回数据有效
    output wire in_ready,            // RUN可接收；握手成功才算一组
    input  wire [`KWT_X_GROUP_WIDTH-1:0] in_x, // 四个X16，第0项放低位
    input  wire [`KWT_W_GROUP_WIDTH-1:0] in_w, // 四个W16，第0项放低位

    // ---- bias 组合选读 ----
    output wire [`KWT_BIAS_ADDR_WIDTH-1:0] bias_addr, // 组合选读本块bias[0..15]
    input  wire signed [`KWT_BIAS_WIDTH-1:0] bias_data, // 与当前bias_addr对应

    // ---- 量化结果输出 ----
    output wire out_valid,           // Y、flags和位置有效，必须一起接收
    input  wire out_ready,           // 下游可接收当前项
    output wire signed [`KWT_Y_WIDTH-1:0] out_y,
    output wire [`KWT_FLAGS_WIDTH-1:0] out_flags,
    output wire [`KWT_RESULT_INDEX_WIDTH-1:0] out_index, // row*16+g*4+q，非连续发射顺序
    output wire out_block_last,      // 本块最后一个有效输出；与flags[2]含义不同

    // ---- 块级状态 ----
    output wire busy,                // 开始请求接受后直到DONE结束保持忙
    output wire block_done           // 最后一个有效输出已被接收的单拍完成状态
);

    // ============================================================
    // 常量定义：状态编码与遍历边界
    // ============================================================
    localparam [2:0] S_IDLE   = 3'd0; // 空闲：等待启动握手，仅此态start_ready=1
    localparam [2:0] S_CLEAR  = 3'd1; // 一拍：清零64个acc，为RUN做准备
    localparam [2:0] S_RUN    = 3'd2; // 接收256组操作数，乘加流水持续流入
    localparam [2:0] S_FLUSH  = 3'd3; // 等最后乘积真正写入acc，流水排空
    localparam [2:0] S_QISSUE = 3'd4; // 逐项发起量化；无效行跳过不握手
    localparam [2:0] S_QWAIT  = 3'd5; // 等下游消费当前项；受阻时计数与Y全部保持
    localparam [2:0] S_DONE   = 3'd6; // 一拍打出block_done完成脉冲，随后回IDLE
    localparam [`KWT_CTX_WIDTH-1:0] LAST_CTX = `KWT_CTX-1;       // g3
    localparam [`KWT_COL_INDEX_WIDTH-1:0] LAST_COL = `KWT_PN-1;  // q3

    // ============================================================
    // 内部寄存器
    // ============================================================
    reg [2:0] state;                              // FSM当前状态（第一段寄存）
    reg [2:0] next_state;                         // 组合算出的下一状态
    // 块元数据：启动握手时锁存，整块有效
    reg [`KWT_ROW_MASK_WIDTH-1:0] row_mask;       // 本块行有效位图
    reg is_final_block;                           // 本块是否为整个矩阵最后一块
    reg [`KWT_ROW_INDEX_WIDTH-1:0] last_row;      // 最后一个有效行，量化终点用
    // 两个计数器
    reg [`KWT_GROUP_COUNT_WIDTH-1:0] group_count; // 已接收的操作数组（0..256）
    reg [`KWT_ACC_ADDR_WIDTH-1:0] quant_index;    // 量化扫描的acc地址（0..63）

    // ============================================================
    // 组合辅助：last_row 扫描 + 握手事件
    // ============================================================
    // 找出最后一个有效行，避免尾行组把global_last错误地放到无效的第4行。
    // 正式mask=1111时为3，mask=0111时为2；循环是组合优先选择，不消耗多拍。
    reg [`KWT_ROW_INDEX_WIDTH-1:0] start_last_row;
    integer row_scan;
    always @(*) begin
        start_last_row = {`KWT_ROW_INDEX_WIDTH{1'b0}};
        for (row_scan=0; row_scan<`KWT_PM; row_scan=row_scan+1) begin
            if (start_row_mask[row_scan]) start_last_row = row_scan;
        end
    end

    wire start_fire;    // 启动握手成交的本拍
    wire group_fire;    // 一组操作数（4个X+4个W）被接收的本拍
    wire input_last;    // 正在接收的这组是本块最后一组（第256组，k63/g3）
    assign start_fire = start_valid && start_ready;
    assign group_fire = in_valid && in_ready;
    assign input_last = (group_count == (`KWT_GROUPS_PER_BLOCK-1));

    // ============================================================
    // 数据通路一：输入组 -> 乘积寄存（乘法阵列，一级流水）
    // ============================================================
    // ctx来自已接收组编号低2位，顺序为g0..g3。
    // 第256组的last与这组操作数同拍进入乘法模块，不能晚一拍或使用下一组计数。
    wire mul_valid;
    wire [`KWT_PRODUCT_GROUP_WIDTH-1:0] mul_product;
    wire [`KWT_CTX_WIDTH-1:0] mul_ctx;
    wire [`KWT_ROW_MASK_WIDTH-1:0] mul_row_mask;
    wire mul_block_last;
    mul_array_4x4 u_mul (
        .clk(clk), .rst_n(rst_n),
        .in_valid(group_fire), .in_x(in_x), .in_w(in_w),
        .in_ctx(group_count[`KWT_CTX_WIDTH-1:0]),
        .in_row_mask(row_mask), .in_block_last(input_last),
        .out_valid(mul_valid), .out_product(mul_product),
        .out_ctx(mul_ctx), .out_row_mask(mul_row_mask), .out_block_last(mul_block_last)
    );

    // ============================================================
    // 数据通路二：乘积寄存 -> 四上下文累加
    // ============================================================
    // FLUSH期间仍然允许在途mul_valid写入acc。
    // 不能再用state==RUN去门控mul_valid，否则最后一组可能在进入FLUSH后被丢弃。
    wire acc_clear;
    wire acc_done;
    wire signed [`KWT_ACC_WIDTH-1:0] selected_acc;
    acc_context_bank u_acc (
        .clk(clk), .rst_n(rst_n), .clear(acc_clear),
        .in_valid(mul_valid), .in_product(mul_product), .in_ctx(mul_ctx),
        .in_row_mask(mul_row_mask), .in_block_last(mul_block_last),
        .block_done(acc_done), .rd_addr(quant_index), .rd_acc(selected_acc)
    );

    // ============================================================
    // 数据通路三：量化寻址解码（acc地址 -> g/p/q -> bias列/输出位置）
    // ============================================================
    // acc地址顺序是{g,p,q}；最终块内结果位置是{p,g,q}，两者不能直接混用。
    // 例如g0/p1/q0：acc地址4，bias列0，结果位置16。
    wire [`KWT_CTX_WIDTH-1:0] quant_ctx;
    wire [`KWT_ROW_INDEX_WIDTH-1:0] quant_row;
    wire [`KWT_COL_INDEX_WIDTH-1:0] quant_col;
    wire quant_row_valid;
    wire quant_is_last;
    assign quant_col = quant_index[0 +: `KWT_COL_INDEX_WIDTH];
    assign quant_row = quant_index[`KWT_COL_INDEX_WIDTH +: `KWT_ROW_INDEX_WIDTH];
    assign quant_ctx = quant_index[(`KWT_COL_INDEX_WIDTH+`KWT_ROW_INDEX_WIDTH) +: `KWT_CTX_WIDTH];
    assign quant_row_valid = row_mask[quant_row];
    assign quant_is_last = (quant_ctx == LAST_CTX) && (quant_row == last_row)
                          && (quant_col == LAST_COL);
    assign bias_addr = {quant_ctx, quant_col};
    assign out_index = {quant_row, quant_ctx, quant_col};

    // ============================================================
    // 数据通路四：逐项量化（单槽量化器，需 QISSUE/QWAIT 逐项握手）
    // ============================================================
    // quant_index在QWAIT受阻期间不变，因此out_index与量化器保持的Y/flags一致。
    wire quant_in_valid;
    wire quant_in_ready;
    wire quant_out_valid;
    wire quant_out_ready;
    wire out_fire;   // 量化输出被下游接收的本拍
    assign out_fire = out_valid && out_ready;
    result_convert u_convert (
        .clk(clk), .rst_n(rst_n), .in_valid(quant_in_valid), .in_ready(quant_in_ready),
        .in_acc(selected_acc), .in_bias(bias_data),
        .in_global_last(is_final_block && quant_is_last),
        .out_valid(quant_out_valid), .out_ready(quant_out_ready),
        .out_y(out_y), .out_flags(out_flags)
    );

    // ============================================================
    // 状态机（三段式）
    // ============================================================

    // 第一段：状态寄存器。这里只保存当前状态，不更新计数或输出。
    // next_state在沿前由组合逻辑算好，本沿更新state，不会额外增加一拍。
    always @(posedge clk) begin
        if (!rst_n)
            state <= S_IDLE;
        else
            state <= next_state;
    end

    // 第二段：组合计算下一状态。组合逻辑用阻塞赋值“=”。
    // 先默认保持当前状态，使等待握手的分支都有确定值，避免产生锁存器。
    always @(*) begin
        next_state = state;
        case (state)
            S_IDLE: begin
                if (start_fire) next_state = S_CLEAR;
            end
            S_CLEAR: begin
                // 本沿u_acc执行clear；沿后进入RUN，才允许接收首组操作数。
                next_state = S_RUN;
            end
            S_RUN: begin
                if (group_fire && input_last) next_state = S_FLUSH;
            end
            S_FLUSH: begin
                // 等最后乘积真正写入acc，再进入量化；不能只等最后输入握手。
                if (acc_done) next_state = S_QISSUE;
            end
            S_QISSUE: begin
                if (!quant_row_valid) begin
                    // 无效行没有结果需要消费，计数逻辑会跳到下一地址。
                    // 空mask不是正式配置；仍保留扫描到末地址后结束的行为。
                    if (quant_index == (`KWT_ACC_COUNT-1)) next_state = S_DONE;
                end else if (quant_in_valid && quant_in_ready) begin
                    next_state = S_QWAIT;
                end
            end
            S_QWAIT: begin
                if (out_fire) begin
                    if (quant_is_last) next_state = S_DONE;
                    else next_state = S_QISSUE;
                end
            end
            S_DONE: begin
                // DONE只持续一拍；下一块仍需重新start和clear。
                next_state = S_IDLE;
            end
            default: next_state = S_IDLE;
        endcase
    end

    // 第三段：根据当前状态组合译码控制输出，assign同样属于组合逻辑。
    // 保留原来的组合时序，不给ready、clear、done额外加一级输出寄存器。
    assign start_ready = rst_n && (state == S_IDLE);
    assign in_ready = rst_n && (state == S_RUN);
    assign acc_clear = rst_n && (state == S_CLEAR);
    assign busy = (state != S_IDLE);
    assign block_done = rst_n && (state == S_DONE);
    assign quant_in_valid = rst_n && (state == S_QISSUE) && quant_row_valid;
    assign quant_out_ready = rst_n && (state == S_QWAIT) && out_ready;
    assign out_valid = rst_n && (state == S_QWAIT) && quant_out_valid;
    assign out_block_last = out_valid && quant_is_last;

    // ============================================================
    // 数据通路寄存：元数据与计数器
    // ============================================================
    // 三段式是状态机的职责划分，并非要求整个模块只能有三个always。
    // 条件仍使用当前state和本拍握手，不能改用next_state提前推进计数。
    always @(posedge clk) begin
        if (!rst_n) begin
            row_mask       <= {`KWT_ROW_MASK_WIDTH{1'b0}};
            is_final_block <= 1'b0;
            last_row       <= {`KWT_ROW_INDEX_WIDTH{1'b0}};
            group_count    <= {`KWT_GROUP_COUNT_WIDTH{1'b0}};
            quant_index    <= {`KWT_ACC_ADDR_WIDTH{1'b0}};
        end else if (start_fire) begin
            row_mask       <= start_row_mask;
            is_final_block <= start_is_final_block;
            last_row       <= start_last_row;
            group_count    <= {`KWT_GROUP_COUNT_WIDTH{1'b0}};
            quant_index    <= {`KWT_ACC_ADDR_WIDTH{1'b0}};
        end else begin
            // 只统计真实接收的操作数组；9位可保存最后的完成值256。
            if ((state == S_RUN) && group_fire)
                group_count <= group_count + 1'b1;

            if ((state == S_QISSUE) && !quant_row_valid &&
                (quant_index != (`KWT_ACC_COUNT-1))) begin
                quant_index <= quant_index + 1'b1;
            end else if ((state == S_QWAIT) && out_fire && !quant_is_last) begin
                // 有效输出只在被接收后推进；受阻时地址和结果位置保持。
                quant_index <= quant_index + 1'b1;
            end
        end
    end

endmodule

`default_nettype wire
