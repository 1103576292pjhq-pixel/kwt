`include "kwt_compute_config.vh"

`default_nettype none

// KWT1-FFN1
// 四上下文累加模块：每个上下文保存4×4个acc，共64个signed40累加值。
// 输入来自mul_array_4x4的已寄存乘积与标签，保持Q28精度，不加bias、不量化。
//
// 使用顺序：复位 -> clear清零并开始新块 -> 接收有效乘积 -> 最后写回 -> 选读。
// clear必须发生在旧流水已排空、新块乘积尚未到达时；clear拍不接收乘积。
// 无ready接口，活动块中的每个in_valid都会被消费，控制器须保证输入完整有序。
// 本模块信任in_block_last，不自行检查256组计数或k/g调度顺序。
//
// 内部地址 = ctx*16 + p*4 + q；乘积lane = p*4 + q。
// 地址0..15属于ctx0，16..31属于ctx1，以此类推；不同ctx之间不相加。
// 行mask为0的位置保持原acc；clear时所有位置都清零，包括尾行组的无效行。
//
// rst_n为低有效同步复位，仅关闭累加、清block_done，不清acc数据。
// 复位后必须先clear，禁止把复位前的残留acc当成新结果读取。
// 最后一组累加与block_done在同一个上升沿写入，沿后acc已包含最后贡献。
// 下游在后续上升沿使用完整结果，不能在最后写回沿直接采样旧acc。
// block_done只持续一拍；结果保持到下一次clear，完成后的乘积不再写入。
//
// rd_acc为组合选读，没有额外寄存延迟；仅在本块完成后作为最终结果使用。
// task/row/tile/slot及全局last由外部控制器保存，不由最后一组ctx替代。
module acc_context_bank (
    input  wire clk,                 // 时钟，上升沿更新状态和累加值
    input  wire rst_n,               // 低有效同步复位，优先级最高
    input  wire clear,               // 同步清零全部acc并开启新块，优先于乘积写入

    input  wire in_valid,            // 一组16个乘积及其标签有效
    input  wire [`KWT_PRODUCT_GROUP_WIDTH-1:0] in_product, // 16个signed32乘积的位图
    input  wire [`KWT_CTX_WIDTH-1:0] in_ctx, // 本组更新的上下文编号0..3
    input  wire [`KWT_ROW_MASK_WIDTH-1:0] in_row_mask, // 位p=1才更新第p行的四个acc
    input  wire in_block_last,       // 当前块最后一组k63/ctx3，必须与乘积同拍

    output reg block_done,           // 最后一组已写入acc的单拍脉冲，不代表量化完成

    input  wire [`KWT_ACC_ADDR_WIDTH-1:0] rd_addr, // 选读地址0..63，按ctx/p/q排列
    output wire signed [`KWT_ACC_WIDTH-1:0] rd_acc // 所选acc的40位Q28值，尚未加bias
);

    // acc数组只在clear时统一清零；正常计算只更新当前ctx中的有效行。
    reg signed [`KWT_ACC_WIDTH-1:0] acc [0:`KWT_ACC_COUNT-1];
    reg active; // clear后为1；复位或最后写回后为0，使结果保持到下一块

    // 每条乘积通路选择一个旧acc并形成一个新和，共描述16路并行加法。
    // 四上下文共享这些通路；具体综合资源与时序需要后续工具验证。
    wire signed [`KWT_ACC_WIDTH-1:0] lane_sum [0:`KWT_MAC_LANES-1];
    genvar p;
    genvar q;
    //下面generate关键词中的是复制16份加法器来实现16路累加
    generate
        for (p = 0; p < `KWT_PM; p = p + 1) begin : gen_row
            for (q = 0; q < `KWT_PN; q = q + 1) begin : gen_col
                localparam integer LANE = p * `KWT_PN + q;
                wire [`KWT_ACC_ADDR_WIDTH-1:0] write_addr;
                wire signed [`KWT_PRODUCT_WIDTH-1:0] product_lane;
                wire signed [`KWT_ACC_WIDTH-1:0] product_ext;

                assign write_addr = in_ctx * `KWT_MAC_LANES + LANE;
                assign product_lane =
                    in_product[`KWT_PRODUCT_WIDTH*LANE +: `KWT_PRODUCT_WIDTH];

                // 32位负数高位补1、正数补0，扩展为40位后数值不变。
                assign product_ext = {
                    {(`KWT_ACC_WIDTH-`KWT_PRODUCT_WIDTH)
                        {product_lane[`KWT_PRODUCT_WIDTH-1]}},
                    product_lane
                };

                // 合法signed16、K64任务的每个前缀都在signed40范围内，
                // 因此普通40位加法与合同中的逐前缀sat40等价。
                assign lane_sum[LANE] = acc[write_addr] + product_ext;
            end
        end
    endgenerate

    // 64选1组合读：选读地址变化时，输出随组合路径变化。
    // 累加结束后数据保持，便于量化控制通过rd_addr逐项读取。
    assign rd_acc = acc[rd_addr];

    integer index;
    integer row;
    integer col;
    always @(posedge clk) begin
        if (!rst_n) begin
            active     <= 1'b0;
            block_done <= 1'b0;
        end else if (clear) begin
            active     <= 1'b1;
            block_done <= 1'b0;
            // 固定循环描述同一上升沿清零全部64个寄存值，不是清64拍。
            for (index = 0; index < `KWT_ACC_COUNT; index = index + 1) begin
                acc[index] <= {`KWT_ACC_WIDTH{1'b0}};
            end
        end else begin
            // 默认清零，只在最后一组有效乘积真正写回时产生一次完成脉冲。
            block_done <= 1'b0;
            if (active && in_valid) begin
                for (row = 0; row < `KWT_PM; row = row + 1) begin
                    for (col = 0; col < `KWT_PN; col = col + 1) begin
                        if (in_row_mask[row]) begin
                            acc[in_ctx * `KWT_MAC_LANES + row * `KWT_PN + col]
                                <= lane_sum[row * `KWT_PN + col];
                        end
                    end
                end

                // 非阻塞赋值让本组acc与完成标记在该沿后一起更新。
                // 同拍不会漏掉最后一组；随后关闭写入，保护等待量化的结果。
                if (in_block_last) begin
                    active     <= 1'b0;
                    block_done <= 1'b1;
                end
            end
        end
    end

endmodule

`default_nettype wire
