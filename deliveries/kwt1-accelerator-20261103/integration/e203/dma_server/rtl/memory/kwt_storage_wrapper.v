`timescale 1ns/1ps
`include "kwt_storage_config.vh"
`default_nettype none

// 本地操作数存储的逻辑bank接口：地址拆分、宏选通、返回选择及valid对齐。
// 内部只例化一次kwt_storage_array，由它保留24颗官方SRAM和bias寄存器。
// X有4个1600×16逻辑bank；W有8个256×16逻辑bank，即两槽各4个。
// 每个bank的两颗宏沿深度拼接，一次访问最终只有一个16位读返回。
//
// 上层在上升沿给出一次请求；合法请求无需等待ready即可被接受。
// 读请求接受后，rd_valid和对应宏选择位在沿后更新；
// 官方Q经过访问延时稳定，下游在下一上升沿采样rd_valid/rd_data。
// 本层没有返回FIFO或out_ready，不会暂停已接受的读请求。
// 连续每拍读允许；上层必须安排好返回接收能力。
//
// 同bank同时读写或地址越界：两颗宏均不访问，沿后报告access_error；
// 没有非法请求的下一沿清error。写周期、空拍和非法请求均不产生rd_valid。
// 复位只清valid、返回选择和error，不清SRAM/bias，不给Q增加数据寄存级。
//
// 装载完整性、尾行mask、W槽owner及k/g/x_hold属于上层控制职责。
// W总线bank编号=slot*4+bank，槽0占编号0..3，槽1占4..7。
// 所有打包字段的编号0均在最低位。
module kwt_storage_wrapper #(
    // 用户摘要中的首个待验证配置；需要匹配宏库及后续STA，不能据此声称150MHz通过。
    parameter [`KWT_SRAM_EMA_WIDTH-1:0]  SRAM_EMA  = 3'b000,
    parameter [`KWT_SRAM_EMAW_WIDTH-1:0] SRAM_EMAW = 2'b00
) (
    // ---- 时钟与复位 ----
    input  wire clk,   // 公共时钟，上升沿接受bank请求
    input  wire rst_n, // 低有效同步复位；复位期间禁止实际访问

    // ---- X逻辑bank接口：每bank一个共用读写地址 ----
    input  wire [`KWT_X_BANK_COUNT-1:0]                        x_rd_en,        // 每位请求读一个bank；尾行无效bank须置0
    input  wire [`KWT_X_BANK_COUNT-1:0]                        x_wr_en,        // 每位请求向一个bank写一项16位数据
    input  wire [`KWT_X_BANK_COUNT*`KWT_X_BANK_ADDR_WIDTH-1:0] x_addr,         // 每bank11位地址0..1599，共44位
    input  wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0]           x_wr_data,      // 每bank16位写数据，共64位
    output wire [`KWT_X_BANK_COUNT*`KWT_X_WIDTH-1:0]           x_rd_data,      // 每bank16位读返回，仅对应valid为1时可用
    output reg  [`KWT_X_BANK_COUNT-1:0]                        x_rd_valid,     // 每位标记对应bank的本次读返回有效
    output reg  [`KWT_X_BANK_COUNT-1:0]                        x_access_error, // 每位报告对应bank刚接受到的非法访问请求

    // ---- W逻辑bank接口：两槽各四bank，访问相互独立 ----
    input  wire [`KWT_W_BANK_COUNT-1:0]                        w_rd_en,        // 每位请求读一个W bank
    input  wire [`KWT_W_BANK_COUNT-1:0]                        w_wr_en,        // 每位请求写一个W bank；活动槽保护由上层实现
    input  wire [`KWT_W_BANK_COUNT*`KWT_W_BANK_ADDR_WIDTH-1:0] w_addr,         // 每bank8位地址0..255，共64位
    input  wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0]           w_wr_data,      // 每bank16位写数据，共128位
    output wire [`KWT_W_BANK_COUNT*`KWT_W_WIDTH-1:0]           w_rd_data,      // 按固定bank位置返回，不使用当前请求槽号选旧数据
    output reg  [`KWT_W_BANK_COUNT-1:0]                        w_rd_valid,     // 每位对应一个bank的读返回有效标记
    output reg  [`KWT_W_BANK_COUNT-1:0]                        w_access_error, // 同bank同时读写等非法请求的错误标记

    // ---- bias接口：保持原有同步写、组合读 ----
    input  wire                              bias_wr_en,   // 写使能，复位期间由存储实体禁止写入
    input  wire                              bias_wr_slot, // 写入槽号0或1
    input  wire [`KWT_BIAS_ADDR_WIDTH-1:0]   bias_wr_addr, // 槽内列号0..15
    input  wire signed [`KWT_BIAS_WIDTH-1:0] bias_wr_data, // 已通过上层范围检查的signed32/Q28偏置
    input  wire                              bias_rd_slot, // 组合选读的W槽号
    input  wire [`KWT_BIAS_ADDR_WIDTH-1:0]   bias_rd_addr, // 组合选读的槽内列号
    output wire signed [`KWT_BIAS_WIDTH-1:0] bias_rd_data  // 直接来自bias寄存器，不增加流水级
);

    // ============================================================
    // 内部信号
    // ============================================================
    // ---- 连接存储实体的物理宏总线，字段编号与kwt_storage_array一致 ----
    wire [`KWT_X_SRAM_COUNT-1:0]                          x_cen, x_gwen;  // 8位片选/读写选择，每颗占1位
    wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     x_wen;          // 每颗16位写掩码，共128位
    wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     x_macro_write;  // 每颗16位写数据，共128位
    wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     x_macro_read;   // 每颗16位读输出，共128位
    wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_1024_ADDR_WIDTH-1:0] x_macro_addr;  // 每颗10位宏内地址，共80位
    wire [`KWT_W_SRAM_COUNT-1:0]                          w_cen, w_gwen;  // 16位片选/读写选择，每颗占1位
    wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     w_wen;          // 每颗16位写掩码，共256位
    wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     w_macro_write;  // 每颗16位写数据，共256位
    wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0]     w_macro_read;   // 每颗16位读输出，共256位
    wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_128_ADDR_WIDTH-1:0]  w_macro_addr;  // 每颗7位宏内地址，共112位

    // ---- 每bank读返回选择状态 ----
    // 每bank保存一位“本次读的是哪颗宏”，不保存或复制SRAM读数据。
    reg [`KWT_X_BANK_COUNT-1:0] x_return_part;
    reg [`KWT_W_BANK_COUNT-1:0] w_return_part;

    // ============================================================
    // X通路：11位逻辑地址 -> 1位宏选择 + 10位宏内地址
    // ============================================================
    genvar xb; // 编译期循环变量：X逻辑bank编号0..3
    genvar xp; // 编译期循环变量：bank内宏编号0..1
    generate
        for (xb=0; xb<`KWT_X_BANK_COUNT; xb=xb+1) begin : gen_x_bank
            // ---- 1. 逻辑地址切片与请求合法性检查 ----
            wire [`KWT_X_BANK_ADDR_WIDTH-1:0] bank_addr;            // 本bank的逻辑地址
            wire bad_access, bank_read, bank_write;                 // 非法请求、净化读请求、净化写请求
            assign bank_addr = x_addr[xb*`KWT_X_BANK_ADDR_WIDTH +: `KWT_X_BANK_ADDR_WIDTH];
            assign bad_access = (x_rd_en[xb] && x_wr_en[xb]) ||
                                ((x_rd_en[xb] || x_wr_en[xb]) && (bank_addr >= `KWT_X_BANK_DEPTH));
            assign bank_read  = x_rd_en[xb] && !bad_access;
            assign bank_write = x_wr_en[xb] && !bad_access;

            // ---- 2. 宏选通与打包字段驱动：每bank两颗宏，按地址最高位二选一 ----
            for (xp=0; xp<`KWT_SRAMS_PER_BANK; xp=xp+1) begin : gen_part
                localparam integer ID = xb*`KWT_SRAMS_PER_BANK + xp; // 当前宏在打包总线中的字段编号
                wire selected, write_selected;
                // 当前请求的地址高位只负责本次宏选通，不直接选择上一份读返回。
                assign selected = rst_n && (bank_read || bank_write) &&
                                  (bank_addr[`KWT_X_BANK_ADDR_WIDTH-1] == xp); // bank地址最高位选两颗宏之一
                assign write_selected = selected && bank_write;
                assign x_cen[ID]  = !selected;       // CEN低有效：选中才使能
                assign x_gwen[ID] = !write_selected; // GWEN为0时表示写
                // 正式装载按16位整项写；读或待机时掩码固定全1。
                assign x_wen[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH] =
                    {`KWT_SRAM_DATA_WIDTH{!write_selected}}; // 位级掩码，低有效
                // 两颗宏接相同低地址和写数据，仅被选中的宏实际访问。
                assign x_macro_addr[ID*`KWT_SRAM_1024_ADDR_WIDTH +: `KWT_SRAM_1024_ADDR_WIDTH] =
                    bank_addr[`KWT_SRAM_1024_ADDR_WIDTH-1:0];
                assign x_macro_write[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH] =
                    x_wr_data[xb*`KWT_X_WIDTH +: `KWT_X_WIDTH];
            end

            // ---- 3. valid/error/返回选择寄存器：沿后报告给上层 ----
            always @(posedge clk) begin
                if (!rst_n) begin
                    x_rd_valid[xb]     <= 1'b0;
                    x_return_part[xb]  <= 1'b0;
                    x_access_error[xb] <= 1'b0;
                end else begin
                    x_rd_valid[xb]     <= bank_read;
                    x_access_error[xb] <= bad_access;
                    if (bank_read)
                        x_return_part[xb] <= bank_addr[`KWT_X_BANK_ADDR_WIDTH-1];
                end
            end

            // ---- 4. 读返回mux：用读请求同沿保存的part选择Q ----
            // 连续跨1023/1024读取也保持配对。
            assign x_rd_data[xb*`KWT_X_WIDTH +: `KWT_X_WIDTH] = x_return_part[xb]
                ? x_macro_read[(xb*`KWT_SRAMS_PER_BANK+1)*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]
                : x_macro_read[(xb*`KWT_SRAMS_PER_BANK)*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH];
        end
    endgenerate

    // ============================================================
    // W通路：8位逻辑地址 -> 1位宏选择 + 7位宏内地址
    // ============================================================
    genvar wb; // 编译期循环变量：W总线bank编号0..7
    genvar wp; // 编译期循环变量：bank内宏编号0..1
    generate
        for (wb=0; wb<`KWT_W_BANK_COUNT; wb=wb+1) begin : gen_w_bank
            // ---- 1. 逻辑地址切片与请求合法性检查 ----
            wire [`KWT_W_BANK_ADDR_WIDTH-1:0] bank_addr;            // 本bank的逻辑地址
            wire bad_access, bank_read, bank_write;                 // 非法请求、净化读请求、净化写请求
            assign bank_addr = w_addr[wb*`KWT_W_BANK_ADDR_WIDTH +: `KWT_W_BANK_ADDR_WIDTH];
            // 当前W深度256恰好覆盖全部8位地址，范围判断在此配置下恒合法。
            assign bad_access = (w_rd_en[wb] && w_wr_en[wb]) ||
                                ((w_rd_en[wb] || w_wr_en[wb]) && (bank_addr >= `KWT_W_BANK_DEPTH));
            assign bank_read  = w_rd_en[wb] && !bad_access;
            assign bank_write = w_wr_en[wb] && !bad_access;

            // ---- 2. 宏选通与打包字段驱动：每bank两颗宏，按地址最高位二选一 ----
            for (wp=0; wp<`KWT_SRAMS_PER_BANK; wp=wp+1) begin : gen_part
                localparam integer ID = wb*`KWT_SRAMS_PER_BANK + wp; // 当前宏在打包总线中的字段编号
                wire selected, write_selected;
                assign selected = rst_n && (bank_read || bank_write) &&
                                  (bank_addr[`KWT_W_BANK_ADDR_WIDTH-1] == wp); // bank地址最高位选两颗宏之一
                assign write_selected = selected && bank_write;
                assign w_cen[ID]  = !selected;       // CEN低有效：选中才使能
                assign w_gwen[ID] = !write_selected; // GWEN为0时表示写
                assign w_wen[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH] =
                    {`KWT_SRAM_DATA_WIDTH{!write_selected}}; // 位级掩码，低有效
                assign w_macro_addr[ID*`KWT_SRAM_128_ADDR_WIDTH +: `KWT_SRAM_128_ADDR_WIDTH] =
                    bank_addr[`KWT_SRAM_128_ADDR_WIDTH-1:0];
                assign w_macro_write[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH] =
                    w_wr_data[wb*`KWT_W_WIDTH +: `KWT_W_WIDTH];
            end

            // ---- 3. valid/error/返回选择寄存器：沿后报告给上层 ----
            always @(posedge clk) begin
                if (!rst_n) begin
                    w_rd_valid[wb]     <= 1'b0;
                    w_return_part[wb]  <= 1'b0;
                    w_access_error[wb] <= 1'b0;
                end else begin
                    w_rd_valid[wb]     <= bank_read;
                    w_access_error[wb] <= bad_access;
                    if (bank_read)
                        w_return_part[wb] <= bank_addr[`KWT_W_BANK_ADDR_WIDTH-1];
                end
            end

            // ---- 4. 读返回mux：每个W bank都有独立返回选择 ----
            // 槽0和槽1的返回不混合。
            assign w_rd_data[wb*`KWT_W_WIDTH +: `KWT_W_WIDTH] = w_return_part[wb]
                ? w_macro_read[(wb*`KWT_SRAMS_PER_BANK+1)*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]
                : w_macro_read[(wb*`KWT_SRAMS_PER_BANK)*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH];
        end
    endgenerate

    // ============================================================
    // 存储实体例化：沿用x_write/x_read、w_write/w_read端口名
    // ============================================================
    kwt_storage_array u_storage (
        // 时钟与复位
        .clk(clk), .rst_n(rst_n),
        // X物理宏总线
        .x_cen(x_cen), .x_gwen(x_gwen), .x_wen(x_wen), .x_a(x_macro_addr),
        .x_write(x_macro_write), .x_read(x_macro_read),
        // W物理宏总线
        .w_cen(w_cen), .w_gwen(w_gwen), .w_wen(w_wen), .w_a(w_macro_addr),
        .w_write(w_macro_write), .w_read(w_macro_read),
        // 宏公共配置
        .sram_ema(SRAM_EMA), .sram_emaw(SRAM_EMAW), .sram_ret1n(1'b1),
        // bias寄存器
        .bias_wr_en(bias_wr_en), .bias_wr_slot(bias_wr_slot),
        .bias_wr_addr(bias_wr_addr), .bias_wr_data(bias_wr_data),
        .bias_rd_slot(bias_rd_slot), .bias_rd_addr(bias_rd_addr), .bias_rd_data(bias_rd_data)
    );

endmodule

`default_nettype wire
