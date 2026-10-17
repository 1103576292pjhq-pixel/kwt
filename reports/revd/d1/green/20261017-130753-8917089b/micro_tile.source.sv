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
    typedef enum logic [2:0] {IDLE,ACCUM,DRAIN,FINAL_SUM,SELECT,QREQ,QWAIT} state_t;
    state_t state;
    logic [PM-1:0] row_mask;
    logic [5:0] issue_k,shift;
    logic [PN*48-1:0] biases;
    logic [31:0] task_id;
    localparam integer ROW_W=(PM>1)?$clog2(PM):1;
    localparam integer COL_W=(PN>1)?$clog2(PN):1;
    logic [ROW_W-1:0] row,last_row;
    logic [COL_W-1:0] col;
    wire signed [47:0] sums[0:PM-1][0:PN-1];
    wire lane_retire[0:PM-1][0:PN-1];
    wire [5:0] lane_k[0:PM-1][0:PN-1];
    logic [31:0] active_mac_count;
    wire clear=cfg_valid&&cfg_ready;
    wire q_in_ready,q_valid;
    wire q_ready=(state==QWAIT)&&out_ready;
    assign cfg_ready=(state==IDLE)&&(|cfg_row_mask);
    assign in_ready=(state==ACCUM);
    assign trace_issue_valid=in_valid&&in_ready;
    assign out_task_id=task_id;
    assign out_row=8'(row);
    assign out_col=8'(col);
    assign out_last=(row==last_row)&&(col==COL_W'(PN-1));
    assign out_valid=(state==QWAIT)&&q_valid;
    assign trace_valid_lanes=trace_retire_valid?row_mask:'0;
    integer i;
    always @* begin
        active_mac_count=0;
        trace_retire_valid=0;trace_retire_k=0;
        for(integer ri=0;ri<PM;ri=ri+1) begin
            if(row_mask[ri]) begin
                active_mac_count=active_mac_count+32'(PN);
                trace_retire_valid=lane_retire[ri][0];
                trace_retire_k=lane_k[ri][0];
            end
        end
    end
    for(genvar rr=0;rr<PM;rr=rr+1) begin: rows
        for(genvar cc=0;cc<PN;cc=cc+1) begin: cols
            wire signed [15:0] lane_x=row_mask[rr]?$signed(in_x[rr*16+:16]):16'sd0;
            mac_lane lane(.clk(clk),.rst_n(rst_n),.clear(clear),
                .in_valid(trace_issue_valid&&row_mask[rr]),.in_x(lane_x),
                .in_w($signed(in_w[cc*16+:16])),.in_k(issue_k),
                .retire_valid(lane_retire[rr][cc]),.retire_k(lane_k[rr][cc]),.sum(sums[rr][cc]));
        end
    end
    quant_epilogue quant(.clk(clk),.rst_n(rst_n),.in_valid(state==QREQ),.in_ready(q_in_ready),
        .in_sum(sums[row][col]),.in_bias($signed(biases[col*48+:48])),.in_shift(shift),
        .out_valid(q_valid),.out_ready(q_ready),.out_raw(out_raw),.out_data(out_data),
        .out_overflow(out_overflow),.out_saturated(out_saturated));
    always_ff @(posedge clk) begin
        if(!rst_n) begin
            state<=IDLE;row_mask<='0;issue_k<='0;shift<='0;biases<='0;task_id<='0;
            row<='0;col<='0;last_row<='0;done<=0;effective_macs<=0;padded_macs<=0;
        end else begin
            done<=0;
            if(trace_retire_valid) begin
                effective_macs<=effective_macs+active_mac_count;
                padded_macs<=padded_macs+(32'(PM*PN)-active_mac_count);
            end
            case(state)
                IDLE: if(clear) begin
                    row_mask<=cfg_row_mask;shift<=cfg_shift;biases<=cfg_bias;task_id<=cfg_task_id;
                    issue_k<=0;row<=0;col<=0;effective_macs<=0;padded_macs<=0;
                    for(i=0;i<PM;i=i+1) if(cfg_row_mask[i]) last_row<=ROW_W'(i);
                    state<=ACCUM;
                end
                ACCUM: if(trace_issue_valid) begin
                    if(issue_k==63) state<=DRAIN;
                    else issue_k<=issue_k+6'd1;
                end
                DRAIN: if(trace_retire_valid&&trace_retire_k==63) state<=FINAL_SUM;
                FINAL_SUM: state<=SELECT;
                SELECT: begin
                    if(row_mask[row]) state<=QREQ;
                    else row<=row+ROW_W'(1);
                end
                QREQ: if(q_in_ready) state<=QWAIT;
                QWAIT: if(out_valid&&out_ready) begin
                    if(out_last) begin state<=IDLE;done<=1;end
                    else if(col==COL_W'(PN-1)) begin col<=0;row<=row+ROW_W'(1);state<=SELECT;end
                    else begin col<=col+COL_W'(1);state<=QREQ;end
                end
                default: state<=IDLE;
            endcase
        end
    end
endmodule
