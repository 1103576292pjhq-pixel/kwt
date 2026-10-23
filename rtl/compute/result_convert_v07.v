`timescale 1ns/1ps
`include "kwt_numeric_config.vh"

// 一项弹性结果寄存器：输入接收时加偏置、RNE、sat16、符号扩展。
// 偏置必须是逻辑signed32的符号扩展；last/tag由外围给出并同步保存。
module result_convert_v07 (
    input wire clk,
    input wire rst_n,
    input wire abort_i,
    input wire in_valid_i,
    output wire in_ready_o,
    input wire signed [`KWT_FFN_V07_ACC_WIDTH-1:0] sum_i,
    input wire signed [`KWT_FFN_V07_BIAS_WIDTH-1:0] bias_i,
    input wire [31:0] tag_i,
    input wire last_i,
    output reg out_valid_o,
    input wire out_ready_i,
    output reg signed [`KWT_FFN_V07_OUT_WIDTH-1:0] out_data_o,
    output reg [31:0] out_tag_o,
    output reg [`KWT_FFN_V07_FLAGS_WIDTH-1:0] out_flags_o,
    output wire out_overflow_o,
    output wire out_saturated_o,
    output wire out_last_o
);
    localparam AW = `KWT_FFN_V07_ACC_WIDTH;
    localparam OW = `KWT_FFN_OUT_WIDTH;
    localparam SHIFT = `KWT_FFN_OUT_SHIFT;
    localparam signed [AW:0] RAW_MAX = {2'b00, {(AW-1){1'b1}}};
    localparam signed [AW:0] RAW_MIN = {2'b11, {(AW-1){1'b0}}};
    localparam signed [AW:0] Y_MAX = (1 << (OW-1))-1;
    localparam signed [AW:0] Y_MIN = -(1 << (OW-1));
    localparam [AW-1:0] REM_MASK = {AW{1'b1}} >> (AW-SHIFT);
    localparam [AW-1:0] HALF = {{(AW-1){1'b0}},1'b1} << (SHIFT-1);
    wire signed [AW:0] added;
    wire signed [AW:0] rounded;
    wire signed [AW-1:0] clipped;
    wire [AW-1:0] magnitude, quotient, remainder, q_rounded;
    wire signed [`KWT_FFN_V07_OUT_WIDTH-1:0] converted;
    wire overflow, saturated;

    assign in_ready_o = rst_n && !abort_i && (!out_valid_o || out_ready_i);
    assign out_overflow_o = out_flags_o[`KWT_FFN_V07_FLAG_OVERFLOW_BIT];
    assign out_saturated_o = out_flags_o[`KWT_FFN_V07_FLAG_SATURATED_BIT];
    assign out_last_o = out_flags_o[`KWT_FFN_V07_FLAG_LAST_BIT];
    // 组合数据路径用连续赋值，输入从初始时保持0也能正确求值。
    assign added = $signed({sum_i[AW-1],sum_i}) + $signed({bias_i[AW-1],bias_i});
    assign overflow = (added > RAW_MAX) || (added < RAW_MIN);
    assign clipped = (added > RAW_MAX) ? RAW_MAX[AW-1:0] :
                     (added < RAW_MIN) ? RAW_MIN[AW-1:0] : added[AW-1:0];
    // unsigned48能容纳最小负数的幅值2^47。
    assign magnitude = clipped[AW-1] ? (~$unsigned(clipped) + 1'b1) : $unsigned(clipped);
    assign quotient = magnitude >> SHIFT;
    assign remainder = magnitude & REM_MASK;
    assign q_rounded = quotient + (((remainder > HALF) ||
                       ((remainder == HALF) && quotient[0])) ? 1'b1 : 1'b0);
    assign rounded = clipped[AW-1] ? -$signed({1'b0,q_rounded}) : $signed({1'b0,q_rounded});
    assign saturated = (rounded > Y_MAX) || (rounded < Y_MIN);
    assign converted = (rounded > Y_MAX) ? Y_MAX : (rounded < Y_MIN) ? Y_MIN :
                       {{(`KWT_FFN_V07_OUT_WIDTH-OW){rounded[OW-1]}},rounded[OW-1:0]};

    always @(posedge clk) begin
        if (!rst_n || abort_i) begin
            out_valid_o <= 1'b0;
            out_data_o <= 0;
            out_tag_o <= 0;
            out_flags_o <= 0;
        end else if (in_ready_o) begin
            out_valid_o <= in_valid_i;
            if (in_valid_i) begin
                out_data_o <= converted;
                out_tag_o <= tag_i;
                out_flags_o[`KWT_FFN_V07_FLAG_OVERFLOW_BIT] <= overflow;
                out_flags_o[`KWT_FFN_V07_FLAG_SATURATED_BIT] <= saturated;
                out_flags_o[`KWT_FFN_V07_FLAG_LAST_BIT] <= last_i;
            end
        end
    end
endmodule
