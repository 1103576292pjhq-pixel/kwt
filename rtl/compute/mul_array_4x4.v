`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 固定4行×4列乘法阵列。低位为第0路，乘积按row*4+col打包。
// 下游累加器每拍都能接收，因而乘积级无需反压；空拍仍向后传播。
module mul_array_4x4 (
    input wire clk,
    input wire rst_n,
    
    input wire abort_i,
    input wire accept_en_i,
    input wire in_valid_i,
    output wire in_ready_o,
    input wire [4*`KWT_FFN_X_WIDTH-1:0] x_i,
    input wire [4*`KWT_FFN_W_WIDTH-1:0] w_i,
    input wire [1:0] ctx_i,
    input wire [3:0] row_mask_i,
    input wire block_last_i,
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
                block_last_o <= block_last_i;
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
