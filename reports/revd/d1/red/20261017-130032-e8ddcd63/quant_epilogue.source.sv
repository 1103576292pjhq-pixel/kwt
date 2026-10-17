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
    assign in_ready = !out_valid || out_ready;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            out_valid <= 1'b0;
            out_raw <= '0; out_data <= '0;
            out_overflow <= 1'b0; out_saturated <= 1'b0;
        end else if (in_ready) begin
            out_valid <= in_valid;
            if (in_valid) begin
                out_raw <= '0; out_data <= '0;
                out_overflow <= 1'b0; out_saturated <= 1'b0;
            end
        end
    end
endmodule
