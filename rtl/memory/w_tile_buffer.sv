`timescale 1ns/1ps
module w_tile_buffer #(
    parameter integer READ_LATENCY=1,USE_MACRO=0
)(
    input wire clk,rst_n,abort_i,
    input wire load_slot_i,w_load_i,
    input wire [9:0] w_index_i,
    input wire signed [15:0] w_data_i,
    input wire bias_load_i,
    input wire [3:0] bias_index_i,
    input wire signed [31:0] bias_data_i,
    input wire read_i,active_slot_i,
    input wire [1:0] ctx_i,
    input wire [5:0] k_i,
    output wire read_valid_o,
    output wire [63:0] w_o,
    input wire [3:0] bias_col_i,
    output wire signed [47:0] bias_o
);
    wire [7:0] valids;
    wire [15:0] data[0:7];
    reg [READ_LATENCY-1:0] slot_pipe;
    reg signed [31:0] biases[0:31];
    integer p;
    // 偏置只有32项，存逻辑32位即可；到核心接口时再符号扩展为48位。
    wire signed [31:0] selected_bias=biases[{active_slot_i,bias_col_i}];
    assign bias_o={{16{selected_bias[31]}},selected_bias};
    always @(posedge clk)begin
        if(rst_n&&!abort_i)begin
            if(bias_load_i)biases[{load_slot_i,bias_index_i}]<=bias_data_i;
            slot_pipe[0]<=active_slot_i;
            for(p=1;p<READ_LATENCY;p=p+1)slot_pipe[p]<=slot_pipe[p-1];
        end
    end
    // 返回槽号也要延迟，不能在切槽时把旧返回值从另一槽取出。
    assign read_valid_o=rst_n&&!abort_i&&(slot_pipe[READ_LATENCY-1]?valids[4]:valids[0]);
    genvar b,c;
    generate for(b=0;b<8;b=b+1)begin:banks
        wire wr=w_load_i&&(load_slot_i==(b/4))&&(w_index_i[1:0]==(b%4));
        wire rd=read_i&&(active_slot_i==(b/4));
        // 加载index=k*16+c；bank=c%4，地址=(c/4)*64+k。
        wire [7:0] address=wr?{w_index_i[3:2],w_index_i[9:4]}:{ctx_i,k_i};
        sram_wrapper #(.DEPTH(256),.ADDR_W(8),.READ_LATENCY(READ_LATENCY),.USE_MACRO(USE_MACRO)) ram(
            .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.wr_en_i(wr),.rd_en_i(rd),
            .addr_i(address),.wr_data_i(w_data_i),.rd_data_o(data[b]),.rd_valid_o(valids[b]));
    end
    for(c=0;c<4;c=c+1)begin:lanes
        assign w_o[c*16+:16]=slot_pipe[READ_LATENCY-1]?data[c+4]:data[c];
    end endgenerate
endmodule
