`timescale 1ns/1ps
`include "kwt_storage_config.vh"
`default_nettype none

// 本地操作数的存储实体：8颗1024×16、16颗128×16及32项bias32寄存器。
// 本轮先例化官方宏，不编写逻辑bank的wrapper。
// 因此X/W端口暂时按物理宏打包，CEN/GWEN/WEN/A/D/Q均保持宏原生含义。
// 后续wrapper负责：逻辑地址译码、两颗宏的选择、Q选择以及读返回valid。
// 本模块不产生k/g、x_hold、装载进度或W槽owner，也不包含双结果块。
//
// X宏编号：id = bank*2 + part，bank=0..3，part=0..1，共8颗。
// W宏编号：id = (slot*4 + bank)*2 + part，共两槽、八个逻辑bank、16颗宏。
// part=0对应逻辑bank的低地址半区，part=1对应高地址半区；
// 本轮只保留该实例分组，地址范围检查和part选通留到wrapper中实现。
// 各打包总线都把id=0的字段放在最低位，其余字段依id依次向高位排列。
//
// 接口合同来自用户2026-10-29提供的SRAM信息摘要：
// CEN低有效；CEN=0时GWEN=0写、GWEN=1读；WEN逐位低有效。
// 正常工作RET1N=1；EMA/EMAW作为公共输入，供后续wrapper连接固定配置。
// EMA=000/EMAW=00仅为待验证候选，本层不暗中替上层选定配置。
//
// rst_n为外围低有效同步复位约定：低电平时强制各宏CEN=1，
// 使时钟上升沿不接受访问，同时禁止bias写入；不清SRAM或bias数据。
// Q和bias读值均不带valid，只有上层确认数据属于合法装载/读返回时才能使用。
// 本文件依赖官方*_rtl_top及其fr_top和底层模型，不提供行为数组替身。
module kwt_storage_array (
    input  wire clk,   // 公共时钟；SRAM和bias均在上升沿接受操作
    input  wire rst_n, // 低有效复位；禁止访问和写入，不清存储内容

    // ---- X：8颗1024×16的物理端口，按宏编号打包 ----
    input  wire [`KWT_X_SRAM_COUNT-1:0] x_cen, // 8位片选，每颗占1位：0使能、1待机
    input  wire [`KWT_X_SRAM_COUNT-1:0] x_gwen, // 每颗的读写选择；片选有效时0写、1读
    input  wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] x_wen, // 每颗16位写掩码，共128位；写周期中0写该位、1保留
    input  wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_1024_ADDR_WIDTH-1:0] x_a, // 每颗10位宏内地址0..1023，共80位
    input  wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] x_write, // 每颗16位写数据，共128位
    output wire [`KWT_X_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] x_read, // 每颗16位读输出，共128位；不含返回valid

    // ---- W：16颗128×16的物理端口，按宏编号打包 ----
    input  wire [`KWT_W_SRAM_COUNT-1:0] w_cen, // 16位片选，每颗占1位：0使能、1待机
    input  wire [`KWT_W_SRAM_COUNT-1:0] w_gwen, // 每颗的读写选择；片选有效时0写、1读
    input  wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] w_wen, // 每颗16位写掩码，共256位；写周期中0写该位、1保留
    input  wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_128_ADDR_WIDTH-1:0] w_a, // 每颗7位宏内地址0..127，共112位
    input  wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] w_write, // 每颗16位写数据，共256位
    output wire [`KWT_W_SRAM_COUNT*`KWT_SRAM_DATA_WIDTH-1:0] w_read, // 每颗16位读输出，共256位；不含返回valid

    // ---- 宏公共配置：正常读写期间保持稳定 ----
    input  wire [`KWT_SRAM_EMA_WIDTH-1:0] sram_ema, // 3位访问时序裕量配置，供24颗宏共用；不是周期数
    input  wire [`KWT_SRAM_EMAW_WIDTH-1:0] sram_emaw, // 2位写时序裕量配置，供24颗宏共用
    input  wire sram_ret1n, // 公共保持模式控制；正常工作接1，不是清零复位

    // ---- bias：两槽各16项；同步单项写入、组合单项选读 ----
    input  wire bias_wr_en, // 写使能；rst_n=1且本信号为1时，上升沿写一项
    input  wire bias_wr_slot, // 写入槽号0或1，与对应W槽绑定
    input  wire [`KWT_BIAS_ADDR_WIDTH-1:0] bias_wr_addr, // 4位槽内写地址，选择16列中的一列
    input  wire signed [`KWT_BIAS_WIDTH-1:0] bias_wr_data, // 要保存的signed32/Q28偏置
    input  wire bias_rd_slot, // 组合选读的槽号；由上层选择活动W槽
    input  wire [`KWT_BIAS_ADDR_WIDTH-1:0] bias_rd_addr, // 4位槽内读地址，后续连接计算核bias_addr
    output wire signed [`KWT_BIAS_WIDTH-1:0] bias_rd_data // 选中的signed32偏置；地址改变后组合更新
);

    // ============================================================
    // X存储实体：四个逻辑bank，每bank两颗官方1024×16宏
    // ============================================================
    // generate循环在展开时产生8个实例，不是运行时轮流访问8颗SRAM。
    // 每颗宏具有独立控制端口；上层可让四个逻辑bank并行读取。
    genvar x_bank; // 展开用bank编号0..3，不是运行时寄存器
    genvar x_part; // 展开用宏编号0..1，区分每bank的两颗宏
    generate
        for (x_bank=0; x_bank<`KWT_X_BANK_COUNT; x_bank=x_bank+1) begin : gen_x_bank
            for (x_part=0; x_part<`KWT_SRAMS_PER_BANK; x_part=x_part+1) begin : gen_part
                localparam integer ID = x_bank*`KWT_SRAMS_PER_BANK + x_part; // 当前X宏的打包字段编号0..7

                RAMSP1024X16_rtl_top u_sram (
                    //x_read 是 128 位的模块输出，里面打包着 8 颗宏各自的 16 位 Q。
                    .Q(x_read[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                    .CLK(clk),
                    .CEN(rst_n ? x_cen[ID] : 1'b1),
                    .WEN(x_wen[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                    .A(x_a[ID*`KWT_SRAM_1024_ADDR_WIDTH +: `KWT_SRAM_1024_ADDR_WIDTH]),
                    .D(x_write[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                    .EMA(sram_ema),
                    .EMAW(sram_emaw),
                    .GWEN(x_gwen[ID]),
                    .RET1N(sram_ret1n)
                );
            end
        end
    endgenerate

    // ============================================================
    // W存储实体：两槽，每槽四bank，每bank两颗官方128×16宏
    // ============================================================
    // slot/bank/part三级实例名直接保留存储归属，便于逐颗核对连接。
    // 本层不判断哪个slot为ACTIVE；槽保护及读写调度由后续控制实现。
    genvar w_slot; // 展开用W槽号0..1
    genvar w_bank; // 展开用槽内bank编号0..3
    genvar w_part; // 展开用bank内宏编号0..1
    generate
        for (w_slot=0; w_slot<`KWT_W_SLOT_COUNT; w_slot=w_slot+1) begin : gen_w_slot
            for (w_bank=0; w_bank<`KWT_W_BANKS_PER_SLOT; w_bank=w_bank+1) begin : gen_w_bank
                for (w_part=0; w_part<`KWT_SRAMS_PER_BANK; w_part=w_part+1) begin : gen_part
                    localparam integer ID = // 当前W宏的打包字段编号0..15
                        (w_slot*`KWT_W_BANKS_PER_SLOT + w_bank)*`KWT_SRAMS_PER_BANK + w_part;

                    RAMSP128X16_rtl_top u_sram (
                        .Q(w_read[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                        .CLK(clk),
                        .CEN(rst_n ? w_cen[ID] : 1'b1),
                        .WEN(w_wen[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                        .A(w_a[ID*`KWT_SRAM_128_ADDR_WIDTH +: `KWT_SRAM_128_ADDR_WIDTH]),
                        .D(w_write[ID*`KWT_SRAM_DATA_WIDTH +: `KWT_SRAM_DATA_WIDTH]),
                        .EMA(sram_ema),
                        .EMAW(sram_emaw),
                        .GWEN(w_gwen[ID]),
                        .RET1N(sram_ret1n)
                    );
                end
            end
        end
    endgenerate

    // ============================================================
    // bias寄存器：共32项signed32，槽号与4位列号合成5位地址
    // ============================================================
    // 地址{slot,column}：槽0为0..15，槽1为16..31。
    // bias必须经过上层的合法性检查后再写入，本层只保存最终signed32。
    reg signed [`KWT_BIAS_WIDTH-1:0] bias_reg [0:`KWT_BIAS_WORD_COUNT-1]; // 32项寄存器；低16项属槽0，高16项属槽1

    always @(posedge clk) begin
        if (rst_n && bias_wr_en)
            bias_reg[{bias_wr_slot,bias_wr_addr}] <= bias_wr_data;
    end

    // 组合读不增加流水级，满足原点积核bias_addr/bias_data的选读合同。
    // 同地址写入沿之后，此处随寄存器新值更新；正常计算禁止改写活动槽。
    assign bias_rd_data = bias_reg[{bias_rd_slot,bias_rd_addr}];

endmodule

`default_nettype wire
