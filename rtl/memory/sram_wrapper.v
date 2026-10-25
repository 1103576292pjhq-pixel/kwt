`timescale 1ns/1ps
// 一个逻辑16位单端口bank。READ_LATENCY按请求被时钟采样后到返回有效计数。
// USE_MACRO=0用于快速自检；=1接本地已有的2048x32 LVT试验宏。
module sram_wrapper #(
    parameter integer DEPTH=1600,
    parameter integer ADDR_W=$clog2(DEPTH),
    parameter integer READ_LATENCY=1,
    parameter integer USE_MACRO=0
)(
    input wire clk,rst_n,abort_i,
    input wire wr_en_i,rd_en_i,
    input wire [ADDR_W-1:0] addr_i,
    input wire [15:0] wr_data_i,
    output wire [15:0] rd_data_o,
    output wire rd_valid_o
);
    wire enabled=rst_n&&!abort_i;
    wire write_en=enabled&&wr_en_i;
    wire read_en=enabled&&rd_en_i&&!wr_en_i;
    reg [READ_LATENCY-1:0] valid_pipe;
    integer p;
    assign rd_valid_o=enabled&&valid_pipe[READ_LATENCY-1];
    // reset/abort只撤销在途请求，不能通过复位循环把SRAM综合成触发器。
    always @(posedge clk) begin
        if(!rst_n||abort_i) valid_pipe<={READ_LATENCY{1'b0}};
        else begin
            valid_pipe[0]<=read_en;
            for(p=1;p<READ_LATENCY;p=p+1)valid_pipe[p]<=valid_pipe[p-1];
        end
    end
    generate if(USE_MACRO==0)begin:behavioral
        reg [15:0] mem[0:DEPTH-1];
        reg [15:0] data_pipe[0:READ_LATENCY-1];
        integer d;
        always @(posedge clk)begin
            if(write_en)mem[addr_i]<=wr_data_i;
            if(read_en)data_pipe[0]<=mem[addr_i];
            for(d=1;d<READ_LATENCY;d=d+1)
                if(valid_pipe[d-1])data_pipe[d]<=data_pipe[d-1];
        end
        assign rd_data_o=data_pipe[READ_LATENCY-1];
    end else begin:local_macro
        wire [31:0] macro_q;
        wire [10:0] macro_addr={{(11-ADDR_W){1'b0}},addr_i};
        // CEB/WEB/BWEB均低有效。只使用低16位，高16位禁止写入。
        // 每个逻辑bank独立一颗宏，容量虽有浪费，但不会制造读写端口冲突。
        // 宏模块名使用库中的cell名；tt0p9v25c等工况由仿真/综合脚本选择。
        TS1N28HPCPL2LVTB2048X32M4MWBASO ram(
            .CLK(clk),.CEB(!(write_en||read_en)),.WEB(!write_en),
            .A(macro_addr),.D({16'b0,wr_data_i}),.BWEB(32'hffff0000),.Q(macro_q),
            .SLP(1'b0),.SD(1'b0),.AWT(1'b0),.BIST(1'b0),
            .CEBM(1'b1),.WEBM(1'b1),.AM(11'b0),.DM(32'b0),.BWEBM(32'hffffffff));
        if(READ_LATENCY==1)begin:direct_return
            // 宏在采样上升沿之后更新Q，下游在下一上升沿使用Q和valid。
            assign rd_data_o=macro_q[15:0];
        end else begin:extra_latency
            reg [15:0] extra[0:READ_LATENCY-2];
            integer d;
            always @(posedge clk)begin
                if(valid_pipe[0])extra[0]<=macro_q[15:0];
                for(d=1;d<READ_LATENCY-1;d=d+1)
                    if(valid_pipe[d])extra[d]<=extra[d-1];
            end
            assign rd_data_o=extra[READ_LATENCY-2];
        end
    end endgenerate
`ifndef SYNTHESIS
    initial begin
        if(READ_LATENCY<1||READ_LATENCY>2||DEPTH<2||DEPTH>2048||ADDR_W>11)
            $fatal(1,"unsupported SRAM geometry/latency");
    end
    always @(posedge clk)if(enabled)begin
        if(wr_en_i&&rd_en_i)$fatal(1,"single port SRAM read/write conflict");
        if((wr_en_i||rd_en_i)&&addr_i>=DEPTH)$fatal(1,"SRAM address out of range");
    end
`endif
endmodule
