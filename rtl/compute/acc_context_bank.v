`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 四组不同输出列的累加上下文，不是一个点积的四个部分和。
// 使用寄存器数组；当前小块计算结束后才允许外围使用选读结果。
module acc_context_bank (
    input wire clk,
    input wire rst_n,
    input wire abort_i,
    input wire acc_clear_i,
    input wire product_valid_i,
    input wire [16*`KWT_FFN_PRODUCT_WIDTH-1:0] product_i,
    input wire [1:0] ctx_i,
    input wire [3:0] row_mask_i,
    input wire block_last_i,
    output reg block_acc_done_o,
    input wire [1:0] sel_ctx_i,
    input wire [1:0] sel_row_i,
    input wire [1:0] sel_col_i,
    output wire signed [`KWT_FFN_V07_ACC_WIDTH-1:0] sum_o
);
    localparam AW = `KWT_FFN_V07_ACC_WIDTH;
    localparam PW = `KWT_FFN_PRODUCT_WIDTH;
    reg signed [AW-1:0] acc [0:63];
    integer index, row, col;
    reg signed [PW-1:0] lane_product;
    wire [5:0] read_index = {sel_ctx_i, sel_row_i, sel_col_i};
    assign sum_o = acc[read_index];

    always @(posedge clk) begin
        if (!rst_n || abort_i || acc_clear_i) begin
            block_acc_done_o <= 1'b0;
            for (index=0; index<64; index=index+1) acc[index] <= 0;
        end else begin
            block_acc_done_o <= 1'b0;
            if (product_valid_i) begin
                for (row=0; row<4; row=row+1)
                    for (col=0; col<4; col=col+1)
                        if (row_mask_i[row]) begin
                            lane_product = product_i[(row*4+col)*PW +: PW];
                            acc[ctx_i*16+row*4+col] <= acc[ctx_i*16+row*4+col]
                                + {{(AW-PW){lane_product[PW-1]}}, lane_product};
                        end
                // 与最后一组乘积的写回同一边沿产生，顶层下一拍观察。
                block_acc_done_o <= block_last_i;
            end
        end
    end
endmodule
