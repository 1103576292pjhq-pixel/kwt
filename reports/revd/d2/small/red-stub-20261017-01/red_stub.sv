module core_stream_frontend #(parameter integer M=5,N=32,PM=4,READ_LATENCY=1)(
input wire clk,rst_n,in_valid,output wire in_ready,input wire [3:0] in_op,in_layer_id,
input wire [31:0] in_task_id,input wire [7:0] in_tile_id,input wire [15:0] in_index,
input wire signed [47:0] in_data,input wire [5:0] in_shift,
output wire out_valid,input wire out_ready,output wire [31:0] out_task_id,out_y_index,
output wire signed [31:0] out_data,output wire out_overflow,out_saturated,out_last,
output reg core_done,output wire fault,output wire [7:0] error_code);
integer task_id=0,load_cycles=0,compute_cycles=0,output_cycles=0,wait_cycles=0,core_cycles=0,frontend_cycles=0;
integer issue_count=0,retire_count=0,effective_macs=0,virtual_macs=0,input_accepts=0,event_retires=0;
integer x_reads[PM],x_writes[PM],w_reads[4],w_writes[4];
assign in_ready=1;assign out_valid=0;assign out_task_id=0;assign out_y_index=0;
assign out_data=0;assign out_overflow=0;assign out_saturated=0;assign out_last=0;assign fault=0;assign error_code=0;
always @(posedge clk) if(!rst_n) core_done<=0;else core_done<=in_valid&&in_op==6;
endmodule
