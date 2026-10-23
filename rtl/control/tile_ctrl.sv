`timescale 1ns/1ps
// 只有本模块修改槽状态。存储模块不猜测谁拥有一个槽。
module tile_ctrl #(parameter integer N=256)(
    input wire clk,rst_n,abort_i,new_task_i,
    input wire open_i,commit_i,
    output wire open_ready_o,load_open_o,
    output reg load_slot_o,
    output reg [4:0] next_load_tile_o,
    input wire acquire_i,tile_done_i,
    output wire tile_available_o,
    output reg active_valid_o,active_slot_o,
    output reg [3:0] active_tile_o
);
    localparam [1:0] FREE=0,LOADING=1,READY=2,ACTIVE=3;
    reg [1:0] slot_state[0:1];
    reg [3:0] slot_tile[0:1];
    reg [4:0] next_compute_tile;
    reg load_open;
    wire free_exists=slot_state[0]==FREE||slot_state[1]==FREE;
    wire free_slot=slot_state[0]==FREE?1'b0:1'b1;
    wire ready0=slot_state[0]==READY&&{1'b0,slot_tile[0]}==next_compute_tile;
    wire ready1=slot_state[1]==READY&&{1'b0,slot_tile[1]}==next_compute_tile;
    assign open_ready_o=free_exists&&!load_open&&next_load_tile_o<N/16;
    assign load_open_o=load_open;
    assign tile_available_o=ready0||ready1;
    always @(posedge clk)begin
        if(!rst_n||abort_i||new_task_i)begin
            slot_state[0]<=FREE;slot_state[1]<=FREE;
            slot_tile[0]<=0;slot_tile[1]<=0;
            load_open<=0;load_slot_o<=0;next_load_tile_o<=0;next_compute_tile<=0;
            active_valid_o<=0;active_slot_o<=0;active_tile_o<=0;
        end else begin
            if(open_i&&open_ready_o)begin
                load_open<=1;load_slot_o<=free_slot;
                slot_state[free_slot]<=LOADING;slot_tile[free_slot]<=next_load_tile_o[3:0];
            end
            if(commit_i&&load_open)begin
                load_open<=0;slot_state[load_slot_o]<=READY;
                next_load_tile_o<=next_load_tile_o+1'b1;
            end
            if(acquire_i&&!active_valid_o&&tile_available_o)begin
                active_valid_o<=1;active_slot_o<=ready0?1'b0:1'b1;
                active_tile_o<=next_compute_tile[3:0];
                slot_state[ready0?0:1]<=ACTIVE;
            end
            // tile_done只能在该tile最后一个行组排空并释放核心后到来。
            // 完成一个普通4行块时绝不能释放权重槽。
            if(tile_done_i&&active_valid_o)begin
                slot_state[active_slot_o]<=FREE;active_valid_o<=0;
                next_compute_tile<=next_compute_tile+1'b1;
            end
        end
    end
endmodule
