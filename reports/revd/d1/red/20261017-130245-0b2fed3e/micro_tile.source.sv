`timescale 1ns/1ps
module micro_tile #(parameter integer PM=4, PN=4) (
    input logic clk,rst_n,
    input logic cfg_valid, output logic cfg_ready,
    input logic [31:0] cfg_task_id,
    input logic [PM-1:0] cfg_row_mask,
    input logic [5:0] cfg_shift,
    input logic [PN*48-1:0] cfg_bias,
    input logic in_valid, output logic in_ready,
    input logic [PM*16-1:0] in_x,
    input logic [PN*16-1:0] in_w,
    output logic out_valid, input logic out_ready,
    output logic [31:0] out_task_id,
    output logic [7:0] out_row,out_col,
    output logic signed [47:0] out_raw,
    output logic signed [31:0] out_data,
    output logic out_overflow,out_saturated,out_last,done,
    output logic trace_issue_valid,trace_retire_valid,
    output logic [5:0] trace_retire_k,
    output logic [PM-1:0] trace_valid_lanes,
    output logic [31:0] effective_macs,padded_macs
);
    assign cfg_ready=1'b1;
    assign in_ready=1'b1;
    assign trace_issue_valid=in_valid;
    assign trace_retire_valid=1'b0;
    assign trace_retire_k='0;
    assign trace_valid_lanes='0;
    assign effective_macs='0; assign padded_macs='0;
    always_ff @(posedge clk) begin
        if(!rst_n) begin
            out_valid<=0; done<=0; out_task_id<=0; out_row<=0; out_col<=0;
            out_raw<=0; out_data<=0; out_overflow<=0; out_saturated<=0; out_last<=0;
        end else begin
            done<=0;
            if(cfg_valid) begin out_valid<=1; out_task_id<=cfg_task_id; end
            else if(out_valid&&out_ready) begin out_valid<=0; done<=1; end
        end
    end
endmodule
