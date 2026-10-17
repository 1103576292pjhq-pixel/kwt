`timescale 1ns/1ps
module quant_epilogue (
    input logic clk, rst_n,
    input logic in_valid, output logic in_ready,
    input logic signed [47:0] in_sum, in_bias,
    input logic [5:0] in_shift,
    output logic out_valid, input logic out_ready,
    output logic signed [47:0] out_raw,
    output logic signed [31:0] out_data,
    output logic out_overflow, out_saturated
);
    logic signed [48:0] added;
    logic signed [47:0] clipped;
    logic [47:0] magnitude, quotient, remainder, half;
    logic signed [48:0] rounded;
    logic signed [31:0] result;
    logic overflow, saturated;
    always @* begin
        added = $signed({in_sum[47],in_sum}) + $signed({in_bias[47],in_bias});
        overflow = 1'b0;
        if (added > 49'sd140737488355327) begin
            clipped = 48'sh7fffffffffff; overflow = 1'b1;
        end else if (added < -49'sd140737488355328) begin
            clipped = 48'sh800000000000; overflow = 1'b1;
        end else clipped = added[47:0];
        magnitude = clipped[47] ? (~$unsigned(clipped) + 48'd1) : $unsigned(clipped);
        quotient = magnitude;
        remainder = '0; half = '0;
        if (in_shift != 0) begin
            quotient = magnitude >> in_shift;
            remainder = magnitude & ((48'd1 << in_shift) - 48'd1);
            half = 48'd1 << (in_shift - 6'd1);
            if ((remainder > half) || ((remainder == half) && quotient[0]))
                quotient = quotient + 48'd1;
        end
        rounded = clipped[47] ? -$signed({1'b0,quotient}) : $signed({1'b0,quotient});
        saturated = 1'b0;
        if (rounded > 49'sd2147483647) begin result = 32'sh7fffffff; saturated = 1'b1; end
        else if (rounded < -49'sd2147483648) begin result = 32'sh80000000; saturated = 1'b1; end
        else result = rounded[31:0];
    end
    assign in_ready = !out_valid || out_ready;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            out_valid <= 1'b0;
            out_raw <= '0; out_data <= '0;
            out_overflow <= 1'b0; out_saturated <= 1'b0;
        end else if (in_ready) begin
            out_valid <= in_valid;
            if (in_valid) begin
                out_raw <= clipped; out_data <= result;
                out_overflow <= overflow; out_saturated <= saturated;
            end
        end
    end
endmodule
