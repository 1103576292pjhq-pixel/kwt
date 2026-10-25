`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 固定4行×4列乘法阵列。低位为第0路，乘积按row*4+col打包。
// 下游累加器每拍都能接收，因而乘积级无需反压；空拍仍向后传播。
module mul_array_4x4 (
    input wire clk,
    input wire rst_n,

    input wire abort_i,//模拟"中途放弃"
    input wire accept_en_i,//只有下游全部接收16个输出之后才能计算下一组
    input wire in_valid_i,//外界的输入有效
    output wire in_ready_o,//可以接受下一组输入

    input wire [4*`KWT_FFN_X_WIDTH-1:0] x_i,
    input wire [4*`KWT_FFN_W_WIDTH-1:0] w_i,

    input wire [1:0] ctx_i,//context上下文表示4组输出的哪一组
    input wire [3:0] row_mask_i,//掩码，99行不能被4整除最后会剩下一个三行的尾部块，4'b0111表示只有三行有效
    input wire block_last_i,//最后一组输入的标签信号，下游必须知道结束这个信息

    output reg product_valid_o,
    output reg [16*`KWT_FFN_PRODUCT_WIDTH-1:0] product_o,
    output reg [1:0] ctx_o,
    output reg [3:0] row_mask_o,
    output reg block_last_o
);
    assign in_ready_o = rst_n && !abort_i && accept_en_i;
    wire fire = in_valid_i && in_ready_o;
    integer row, col;

    always @(posedge clk) begin
        if (!rst_n || abort_i) begin
            product_valid_o <= 1'b0;
            product_o <= 0;
            ctx_o <= 0;
            row_mask_o <= 0;
            block_last_o <= 0;
        end else begin
            product_valid_o <= fire;
            if (fire) begin
                ctx_o <= ctx_i;
                row_mask_o <= row_mask_i;
                block_last_o <= block_last_i;//标签数据流动
                // [base +: width]索引部分选择：从第base位起向上取width位，
                // 起点可为变量、宽度须为常量；切片默认无符号，故用$signed()转有符号再乘。
                for (row=0; row<4; row=row+1)
                    for (col=0; col<4; col=col+1) begin
                        if (row_mask_i[row])
                            product_o[(row*4+col)*`KWT_FFN_PRODUCT_WIDTH +: `KWT_FFN_PRODUCT_WIDTH]
                                <= $signed(x_i[row*`KWT_FFN_X_WIDTH +: `KWT_FFN_X_WIDTH])
                                 * $signed(w_i[col*`KWT_FFN_W_WIDTH +: `KWT_FFN_W_WIDTH]);
                        else
                            product_o[(row*4+col)*`KWT_FFN_PRODUCT_WIDTH +: `KWT_FFN_PRODUCT_WIDTH] <= 0;
                    end
            end
        end
    end
endmodule
