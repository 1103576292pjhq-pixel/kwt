`timescale 1ns/1ps
// 不复制64项累加值/结果。只生成选读地址和标签，让核心的一项弹性寄存器保持输出。
module result_ctrl #(parameter integer N=256)(
    input wire clk,rst_n,abort_i,block_begin_i,
    input wire [6:0] row_base_i,
    input wire [3:0] tile_i,row_mask_i,
    input wire acc_ready_i,read_ready_i,out_valid_i,out_ready_i,block_ready_i,
    output wire read_valid_o,
    output wire [1:0] sel_ctx_o,sel_row_o,sel_col_o,
    output wire [3:0] bias_col_o,
    output wire [31:0] tag_o,
    output wire last_o,block_release_o,
    input wire final_row_group_i,
    output reg block_done_o
);
    localparam [1:0] IDLE=0,WAIT_ACC=1,SELECT=2,RELEASE=3;
    reg [1:0] state;
    reg [6:0] row_base,scan_pos,consumed,expected;
    reg [3:0] tile,row_mask;
    reg final_group;
    wire enabled=rst_n&&!abort_i;
    assign sel_row_o=scan_pos[5:4];
    assign sel_ctx_o=scan_pos[3:2];assign sel_col_o=scan_pos[1:0];
    assign bias_col_o=scan_pos[3:0];
    assign read_valid_o=enabled&&state==SELECT&&scan_pos<64&&row_mask[scan_pos[5:4]];
    assign tag_o=({25'b0,row_base}+{30'b0,sel_row_o})*N+{28'b0,tile}*16+{28'b0,bias_col_o};
    assign last_o=final_group&&tile==N/16-1&&scan_pos==expected-1;
    assign block_release_o=enabled&&state==RELEASE;
    wire [2:0] valid_rows={2'b0,row_mask_i[0]}+{2'b0,row_mask_i[1]}+
                          {2'b0,row_mask_i[2]}+{2'b0,row_mask_i[3]};
    always @(posedge clk)begin
        if(!rst_n||abort_i)begin
            state<=IDLE;row_base<=0;tile<=0;row_mask<=0;scan_pos<=0;
            consumed<=0;expected<=0;final_group<=0;block_done_o<=0;
        end else begin
            block_done_o<=0;
            if(out_valid_i&&out_ready_i)consumed<=consumed+1'b1;
            case(state)
                IDLE:if(block_begin_i)begin
                    row_base<=row_base_i;tile<=tile_i;row_mask<=row_mask_i;
                    final_group<=final_row_group_i;scan_pos<=0;consumed<=0;
                    expected<={valid_rows,4'b0};
                    state<=WAIT_ACC;
                end
                WAIT_ACC:if(acc_ready_i)state<=SELECT;
                SELECT:begin
                    // 选读成功才推进有效位置；遇到无效尾行只跳过、不产生输出。
                    if(scan_pos<64)begin
                        if(!row_mask[scan_pos[5:4]]||(read_valid_o&&read_ready_i))scan_pos<=scan_pos+1'b1;
                    end else if(consumed==expected&&!out_valid_i)state<=RELEASE;
                end
                // release没有ready端口，以重新观察到block_ready确认它真的生效。
                RELEASE:if(block_ready_i)begin block_done_o<=1;state<=IDLE;end
                default:state<=IDLE;
            endcase
        end
    end
endmodule
