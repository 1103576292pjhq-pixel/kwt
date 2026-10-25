`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 四组不同输出列的累加上下文，不是一个点积的四个部分和。
// 使用寄存器数组；当前小块计算结束后才允许外围使用选读结果。
module acc_context_bank (
    input wire clk,
    input wire rst_n,

    input wire abort_i,//放弃当前块：与复位/清零并列，清空全部累加器
    input wire acc_clear_i,//块开始清零：顶层在CLEAR状态拉高
    input wire product_valid_i,//上游16个乘积有效（mul_array延迟一拍后的输出）

    input wire [16*`KWT_FFN_PRODUCT_WIDTH-1:0] product_i,//16个乘积，按row*4+col打包
    input wire [1:0] ctx_i,//组选择：本拍乘积写入第ctx组（每组16个寄存器）
    input wire [3:0] row_mask_i,//行有效掩码：无效行的乘积不累加
    input wire block_last_i,//最后一组乘积标记：与乘积同步延迟，写回同沿产生done
    output reg block_acc_done_o,//最后16个乘积已写回的脉冲，顶层据此进入READOUT
    
    input wire [1:0] sel_ctx_i,//选读地址：组
    input wire [1:0] sel_row_i,//选读地址：行
    input wire [1:0] sel_col_i,//选读地址：列；输出列号=4*sel_ctx+sel_col
    output wire signed [`KWT_FFN_V07_ACC_WIDTH-1:0] sum_o//组合读出所选累加值（偏置前）
);
    localparam AW = `KWT_FFN_V07_ACC_WIDTH;
    localparam PW = `KWT_FFN_PRODUCT_WIDTH;
    reg signed [AW-1:0] acc [0:63];//64个48位累加寄存器=4组×4行×4列；真正的数组存储
    integer index, row, col;
    reg signed [PW-1:0] lane_product;
    wire [5:0] read_index = {sel_ctx_i, sel_row_i, sel_col_i};//6位地址：组/行/列
    assign sum_o = acc[read_index];//组合64选1；块完成后读到的才算完整结果

    always @(posedge clk) begin
        if (!rst_n || abort_i || acc_clear_i) begin//三个清零源并列：复位/中止/块开始
            block_acc_done_o <= 1'b0;
            for (index=0; index<64; index=index+1) acc[index] <= 0;
        end else begin
            block_acc_done_o <= 1'b0;//每拍默认清0，仅最后一组乘积写回那拍为1
            if (product_valid_i) begin
                for (row=0; row<4; row=row+1)
                    for (col=0; col<4; col=col+1)
                        if (row_mask_i[row]) begin
                            lane_product = product_i[(row*4+col)*PW +: PW];//取第row*4+col个乘积
                            acc[ctx_i*16+row*4+col] <= acc[ctx_i*16+row*4+col]
                                + {{(AW-PW){lane_product[PW-1]}}, lane_product};//32位乘积符号扩展到48位后再累加
                        end
                // 与最后一组乘积的写回同一边沿产生，顶层下一拍观察。
                block_acc_done_o <= block_last_i;
            end
        end
    end
endmodule
