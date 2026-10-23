`timescale 1ns/1ps
module matrix_ctrl #(parameter integer M=99,N=256)(
    input wire clk,rst_n,abort_i,start_i,
    input wire active_valid_i,
    input wire [3:0] active_tile_i,
    output wire tile_acquire_o,tile_done_o,
    input wire block_ready_i,block_done_i,
    output wire block_start_o,block_begin_o,
    output reg [6:0] row_base_o,
    output wire [3:0] row_mask_o,
    output wire [4:0] row_group_o,
    output wire x_read_o,w_read_o,
    output reg [5:0] k_o,
    output reg [1:0] ctx_o,
    input wire x_valid_i,w_valid_i,
    input wire [63:0] x_i,w_i,
    output wire in_valid_o,input wire in_ready_i,
    output wire [63:0] core_x_o,core_w_o,
    output wire block_last_o,
    output reg task_done_o
);
    localparam [2:0] IDLE=0,WAIT_TILE=1,START_BLOCK=2,READ_REQ=3,READ_WAIT=4,SEND=5,WAIT_OUTPUT=6;
    reg [2:0] state;
    reg [63:0] x_hold,w_hold;
    assign row_group_o=row_base_o[6:2];
    assign row_mask_o={({1'b0,row_base_o}+8'd3<M),({1'b0,row_base_o}+8'd2<M),
                       ({1'b0,row_base_o}+8'd1<M),({1'b0,row_base_o}<M)};
    wire enabled=rst_n&&!abort_i;
    assign tile_acquire_o=enabled&&state==WAIT_TILE&&!active_valid_i;
    assign block_start_o=enabled&&state==START_BLOCK&&block_ready_i;
    assign block_begin_o=block_start_o;
    assign w_read_o=enabled&&state==READ_REQ;
    assign x_read_o=w_read_o&&ctx_o==0;
    assign in_valid_o=enabled&&state==SEND;
    assign core_x_o=x_hold;assign core_w_o=w_hold;
    assign block_last_o=k_o==63&&ctx_o==3;
    assign tile_done_o=enabled&&state==WAIT_OUTPUT&&block_done_i&&({1'b0,row_base_o}+8'd4>=M);
    always @(posedge clk)begin
        if(!rst_n||abort_i)begin
            state<=IDLE;row_base_o<=0;k_o<=0;ctx_o<=0;x_hold<=0;w_hold<=0;task_done_o<=0;
        end else begin
            task_done_o<=0;
            case(state)
                IDLE:if(start_i)begin row_base_o<=0;state<=WAIT_TILE;end
                WAIT_TILE:if(active_valid_i)begin row_base_o<=0;state<=START_BLOCK;end
                START_BLOCK:if(block_ready_i)begin k_o<=0;ctx_o<=0;state<=READ_REQ;end
                READ_REQ:state<=READ_WAIT;
                // 一次仅有一个读请求在途，所以返回标签就是保持不动的k/ctx。
                // X和W使用同一wrapper延迟；ctx0读X，ctx1..3复用x_hold。
                READ_WAIT:if(w_valid_i&&(ctx_o!=0||x_valid_i))begin
                    w_hold<=w_i;if(ctx_o==0)x_hold<=x_i;state<=SEND;
                end
                SEND:if(in_valid_o&&in_ready_i)begin
                    if(block_last_o)state<=WAIT_OUTPUT;
                    else begin
                        if(ctx_o==3)begin ctx_o<=0;k_o<=k_o+1'b1;end
                        else ctx_o<=ctx_o+1'b1;
                        state<=READ_REQ;
                    end
                end
                WAIT_OUTPUT:if(block_done_i)begin
                    if({1'b0,row_base_o}+8'd4<M)begin row_base_o<=row_base_o+4;state<=START_BLOCK;end
                    else if(active_tile_i==N/16-1)begin task_done_o<=1;state<=IDLE;end
                    else begin row_base_o<=0;state<=WAIT_TILE;end
                end
                default:state<=IDLE;
            endcase
        end
    end
endmodule
