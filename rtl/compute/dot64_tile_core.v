`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 一个4行×16列小块的计算顶层；外围负责k/g顺序、X复用及结果位置。
// 输入必须按每个k依次ctx=0,1,2,3，k=0..63，总计256次握手。
// block_last只在第256次输入置1；本模块不重复维护外围的k/g计数器。
module dot64_tile_core (
    input wire clk,
    input wire rst_n,
    input wire abort_i,
    input wire block_start_i,
    output wire block_ready_o,
    input wire block_release_i,
    input wire in_valid_i,
    output wire in_ready_o,
    input wire [4*`KWT_FFN_X_WIDTH-1:0] x_i,
    input wire [4*`KWT_FFN_W_WIDTH-1:0] w_i,
    input wire [1:0] ctx_i,
    input wire [3:0] row_mask_i,
    input wire block_last_i,
    output wire pipeline_empty_o,
    output wire acc_ready_o,
    input wire [1:0] sel_ctx_i,
    input wire [1:0] sel_row_i,
    input wire [1:0] sel_col_i,
    output wire signed [`KWT_FFN_V07_ACC_WIDTH-1:0] selected_sum_o,
    input wire read_valid_i,
    output wire read_ready_o,
    input wire signed [`KWT_FFN_V07_BIAS_WIDTH-1:0] bias_i,
    input wire [31:0] tag_i,
    input wire last_i,
    output wire out_valid_o,
    input wire out_ready_i,
    output wire signed [`KWT_FFN_V07_OUT_WIDTH-1:0] out_data_o,
    output wire [31:0] out_tag_o,
    output wire [`KWT_FFN_V07_FLAGS_WIDTH-1:0] out_flags_o,
    output wire out_overflow_o,
    output wire out_saturated_o,
    output wire out_last_o
);
    localparam [2:0] IDLE=0, CLEAR=1, COMPUTE=2, DRAIN=3, READOUT=4;
    reg [2:0] state;
    wire product_valid, product_last, block_acc_done;
    wire [16*`KWT_FFN_PRODUCT_WIDTH-1:0] products;
    wire [1:0] product_ctx;
    wire [3:0] product_mask;
    wire convert_ready;
    wire accept_en = state == COMPUTE;
    wire acc_clear = state == CLEAR;

    assign block_ready_o = rst_n && !abort_i && state == IDLE;
    assign pipeline_empty_o = !product_valid;
    assign acc_ready_o = rst_n && !abort_i && state == READOUT;
    assign read_ready_o = acc_ready_o && convert_ready;

    mul_array_4x4 mul_array_inst (
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.accept_en_i(accept_en),
        .in_valid_i(in_valid_i),.in_ready_o(in_ready_o),.x_i(x_i),.w_i(w_i),
        .ctx_i(ctx_i),.row_mask_i(row_mask_i),.block_last_i(block_last_i),
        .product_valid_o(product_valid),.product_o(products),.ctx_o(product_ctx),
        .row_mask_o(product_mask),.block_last_o(product_last)
    );
    acc_context_bank acc_bank_inst (
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.acc_clear_i(acc_clear),
        .product_valid_i(product_valid),.product_i(products),.ctx_i(product_ctx),
        .row_mask_i(product_mask),.block_last_i(product_last),.block_acc_done_o(block_acc_done),
        .sel_ctx_i(sel_ctx_i),.sel_row_i(sel_row_i),.sel_col_i(sel_col_i),.sum_o(selected_sum_o)
    );
    result_convert_v07 convert_inst (
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),
        .in_valid_i(read_valid_i && acc_ready_o),.in_ready_o(convert_ready),
        .sum_i(selected_sum_o),.bias_i(bias_i),.tag_i(tag_i),.last_i(last_i),
        .out_valid_o(out_valid_o),.out_ready_i(out_ready_i),.out_data_o(out_data_o),
        .out_tag_o(out_tag_o),.out_flags_o(out_flags_o),
        .out_overflow_o(out_overflow_o),.out_saturated_o(out_saturated_o),.out_last_o(out_last_o)
    );

    always @(posedge clk) begin
        if (!rst_n || abort_i) state <= IDLE;
        else case (state)
            IDLE: if (block_start_i) state <= CLEAR;
            CLEAR: state <= COMPUTE;
            COMPUTE: if (in_valid_i && in_ready_o && block_last_i) state <= DRAIN;
            DRAIN: if (block_acc_done && pipeline_empty_o) state <= READOUT;
            // 释放是外围声明已读完；禁止与新选读请求同拍释放。
            // 尚有未消费结果时也不释放，避免结果被下一块覆盖。
            READOUT: if (block_release_i && !read_valid_i && !out_valid_o) state <= IDLE;
            default: state <= IDLE;
        endcase
    end
endmodule
