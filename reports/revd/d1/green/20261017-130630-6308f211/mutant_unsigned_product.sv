`timescale 1ns/1ps
// One registered signed16 product followed by an exact signed48 accumulator.
// clear owns the lane for a fresh snapshot; in_k follows the product register.
module mac_lane (
    input logic clk,rst_n,clear,
    input logic in_valid,
    input logic signed [15:0] in_x,in_w,
    input logic [5:0] in_k,
    output logic retire_valid,
    output logic [5:0] retire_k,
    output logic signed [47:0] sum
);
    logic product_valid;
    logic [5:0] product_k;
    logic signed [31:0] product;
    assign retire_valid=product_valid;
    assign retire_k=product_k;
    always_ff @(posedge clk) begin
        if(!rst_n || clear) begin
            product_valid<=1'b0;product_k<='0;product<='0;sum<='0;
        end else begin
            product_valid<=in_valid;
            if(in_valid) begin
                product <= $unsigned(in_x)*$unsigned(in_w);
                product_k <= in_k;
            end
            if(product_valid) sum <= sum + {{16{product[31]}},product};
        end
    end
endmodule
