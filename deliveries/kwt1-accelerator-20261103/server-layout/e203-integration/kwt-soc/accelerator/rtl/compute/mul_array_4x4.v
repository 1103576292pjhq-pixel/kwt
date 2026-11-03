`include "kwt_compute_config.vh"

`default_nettype none

// 每组输入对应同一个k和上下文ctx，包含四个X值与四个W值。
// 打包总线的第0个元素放在最低位，按当前冻结位宽举例：
// x[p] = in_x[16*p +: 16], w[q] = in_w[16*q +: 16].
// 乘积编号lane = 4*p + q；out_product[32*lane +: 32]保存x[p]*w[q]。
// X为Q12，W为Q16，完整32位乘积为Q28，本模块不移位、不量化。
// 打包总线只组织位图；拆出的操作数及下游取出的乘积须按有符号数解释。
//
// 固定一级流水，不设置ready、不支持背压；下游必须接收每组有效输出。
// 输入必须是已经对齐的SRAM返回数据与标签，不能直接使用当前请求标签。
// rst_n=1且in_valid=1时，在时钟上升沿寄存乘积和标签。
// 该沿之后输出更新，下游时序累加模块在下一个上升沿消费这组乘积。
//
// rst_n为低有效同步复位，必须在时钟上升沿保持低电平才执行复位。
// 复位清除输出有效位与标签，不清乘积寄存器；仅out_valid=1时乘积有效。
// 非复位的无效输入拍使out_valid=0，乘积和标签保持原值。
//
// in_block_last标记当前块的k63/ctx3，与Y输出flags中的global_last含义不同。
// 行mask在此只随乘积传递；下游累加模块依据out_row_mask禁止无效行更新。
// 其他身份标签由控制器通过并行路径传递，延迟及复位行为必须与本模块对齐。
module mul_array_4x4 (
    input  wire         clk,           // 时钟，上升沿更新寄存器
    input  wire         rst_n,         // 低有效同步复位

    input  wire         in_valid,     // 当前输入数据与标签有效
    input  wire [`KWT_X_GROUP_WIDTH-1:0] in_x, // 四个X，共64位
    input  wire [`KWT_W_GROUP_WIDTH-1:0] in_w, // 四个W，共64位
    input  wire [`KWT_CTX_WIDTH-1:0] in_ctx,   // 上下文编号0..3
    input  wire [`KWT_ROW_MASK_WIDTH-1:0] in_row_mask, // 位p=1表示第p行有效
    input  wire         in_block_last, // 当前块最后一组，即k63/ctx3

    output reg          out_valid,    // 当前乘积及输出标签有效
    output reg [`KWT_PRODUCT_GROUP_WIDTH-1:0] out_product, // 16个32位乘积
    output reg [`KWT_CTX_WIDTH-1:0] out_ctx, // 与乘积同拍寄存的上下文
    output reg [`KWT_ROW_MASK_WIDTH-1:0] out_row_mask, // 与乘积对应的行mask
    output reg          out_block_last // 随最后一组乘积传递的块结束标记
);

    // 每一路从总线拆出两个signed16操作数，形成完整signed32组合乘积。
    // 两层生成循环展开为16路并行乘法；p、q是展开时的常量，不是硬件计数器。
    genvar p;
    genvar q;
    generate//此关键词用于批量生成16个乘法器从而实现并行计算
        for (p = 0; p < `KWT_PM; p = p + 1) begin : gen_row
            for (q = 0; q < `KWT_PN; q = q + 1) begin : gen_col
                wire signed [`KWT_X_WIDTH-1:0] x_lane;
                wire signed [`KWT_W_WIDTH-1:0] w_lane;
                wire signed [`KWT_PRODUCT_WIDTH-1:0] product_comb;

                assign x_lane = in_x[`KWT_X_WIDTH*p +: `KWT_X_WIDTH];
                assign w_lane = in_w[`KWT_W_WIDTH*q +: `KWT_W_WIDTH];
                assign product_comb = x_lane * w_lane;

                // 一级乘积寄存，全部16路在同一个上升沿采样。
                // 复位期间禁止写入，但不清零512位乘积数据。
                // 每个生成的时序过程仅驱动自身的32位切片，互不重叠。
                always @(posedge clk) begin
                    if (rst_n && in_valid) begin
                        out_product[`KWT_PRODUCT_WIDTH*(`KWT_PN*p+q)
                                    +: `KWT_PRODUCT_WIDTH] <= product_comb;
                    end
                end
            end
        end
    endgenerate

    // 每拍传递valid，包括in_valid=0的空拍，避免旧乘积被重复消费。
    // 标签仅在输入有效时更新，寄存时刻与对应乘积一致。
    always @(posedge clk) begin
        if (!rst_n) begin
            out_valid      <= 1'b0;
            out_ctx        <= {`KWT_CTX_WIDTH{1'b0}};
            out_row_mask   <= {`KWT_ROW_MASK_WIDTH{1'b0}};
            out_block_last <= 1'b0;
        end else begin
            out_valid <= in_valid;
            if (in_valid) begin
                out_ctx        <= in_ctx;
                out_row_mask   <= in_row_mask;
                out_block_last <= in_block_last;
            end
        end
    end

endmodule

`default_nettype wire
