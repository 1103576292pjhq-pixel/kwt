`timescale 1ns/1ps
module x_buffer #(
    parameter integer M=99,READ_LATENCY=1,USE_MACRO=0
)(
    input wire clk,rst_n,abort_i,
    input wire load_i,
    input wire [15:0] load_index_i,
    input wire signed [15:0] load_data_i,
    input wire read_i,
    input wire [4:0] row_group_i,
    input wire [5:0] k_i,
    input wire [3:0] row_mask_i,
    output wire read_valid_o,
    output wire [63:0] x_o
);
    localparam integer DEPTH=((M+3)/4)*64,AW=$clog2(DEPTH);
    wire [3:0] valids;
    // mask跟随读请求一起延迟，不能用后续请求的mask解释旧数据。
    reg [3:0] mask_pipe[0:READ_LATENCY-1];
    reg [READ_LATENCY-1:0] request_pipe;
    integer p;
    always @(posedge clk)begin
        if(!rst_n||abort_i)request_pipe<='0;
        else begin
            request_pipe[0]<=read_i;
            if(read_i)mask_pipe[0]<=row_mask_i;
            for(p=1;p<READ_LATENCY;p=p+1)begin
                request_pipe[p]<=request_pipe[p-1];
                if(request_pipe[p-1])mask_pipe[p]<=mask_pipe[p-1];
            end
        end
    end
    assign read_valid_o=rst_n&&!abort_i&&request_pipe[READ_LATENCY-1];
    genvar bank;
    generate for(bank=0;bank<4;bank=bank+1)begin:banks
        wire wr=load_i&&(load_index_i[7:6]==bank);
        // i*64+k：bank=i%4；bank内地址=(i/4)*64+k。
        wire [13:0] load_address={load_index_i[15:8],load_index_i[5:0]};
        wire [10:0] read_address={row_group_i,k_i};
        wire [AW-1:0] address=wr?load_address[AW-1:0]:read_address[AW-1:0];
        wire [15:0] data;
        sram_wrapper #(.DEPTH(DEPTH),.ADDR_W(AW),.READ_LATENCY(READ_LATENCY),.USE_MACRO(USE_MACRO)) ram(
            .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.wr_en_i(wr),
            .rd_en_i(read_i&&row_mask_i[bank]),.addr_i(address),.wr_data_i(load_data_i),
            .rd_data_o(data),.rd_valid_o(valids[bank]));
        // 尾组不存在的行不读SRAM，也不把未初始化的Q传播进计算阵列。
        assign x_o[bank*16+:16]=mask_pipe[READ_LATENCY-1][bank]?data:16'b0;
    end endgenerate
endmodule
