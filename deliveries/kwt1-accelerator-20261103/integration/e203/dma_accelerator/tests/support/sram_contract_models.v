`timescale 1ns/1ps
// 测试专用合同模型：不是赛方模型，不能作为宏集成/时序/PVT通过证据。
// 仅在显式定义KWT_STORAGE_TEST_CONTRACT时提供同名入口，默认不参与编译。
// 假设同步读、Q在0.2ns后更新、写时Q保持、待机Q保持；待机保持这一假设
// 尚未由官方完整模型核实，所以此文件只用于自检TB与外围连接的合同逻辑。
`ifdef KWT_STORAGE_TEST_CONTRACT
`default_nettype none
module kwt_tb_sp_contract #(parameter DEPTH=128,ADDR_W=7)(
    output reg [15:0] Q,
    input wire CLK,CEN,input wire [15:0] WEN,
    input wire [ADDR_W-1:0] A,input wire [15:0] D,
    input wire [2:0] EMA,input wire [1:0] EMAW,input wire GWEN,RET1N
);
    reg [15:0] mem[0:DEPTH-1]; // 不初始化数据，也没有清零复位
    integer bit_index;
    always @(posedge CLK)begin
        if(CEN===1'b0)begin
            if(RET1N!==1'b1 || (^A)===1'bx || A>=DEPTH)$fatal(1,"contract model invalid address/mode");
            if((^EMA)===1'bx || (^EMAW)===1'bx)$fatal(1,"contract model floating margin pins");
            if(GWEN===1'b0)begin
                for(bit_index=0;bit_index<16;bit_index=bit_index+1)
                    if(WEN[bit_index]===1'b0)mem[A][bit_index]<=D[bit_index];
                    else if(WEN[bit_index]!==1'b1)$fatal(1,"contract model unknown WEN");
            end else if(GWEN===1'b1)Q<=#0.2 mem[A];
            else $fatal(1,"contract model unknown GWEN");
        end else if(CEN!==1'b1)$fatal(1,"contract model unknown CEN");
    end
endmodule
module RAMSP128X16_rtl_top(
    output wire [15:0] Q,input wire CLK,CEN,input wire [15:0] WEN,
    input wire [6:0] A,input wire [15:0] D,input wire [2:0] EMA,
    input wire [1:0] EMAW,input wire GWEN,RET1N
);
    kwt_tb_sp_contract #(.DEPTH(128),.ADDR_W(7)) u_contract(
        .Q(Q),.CLK(CLK),.CEN(CEN),.WEN(WEN),.A(A),.D(D),
        .EMA(EMA),.EMAW(EMAW),.GWEN(GWEN),.RET1N(RET1N));
endmodule
module RAMSP1024X16_rtl_top(
    output wire [15:0] Q,input wire CLK,CEN,input wire [15:0] WEN,
    input wire [9:0] A,input wire [15:0] D,input wire [2:0] EMA,
    input wire [1:0] EMAW,input wire GWEN,RET1N
);
    kwt_tb_sp_contract #(.DEPTH(1024),.ADDR_W(10)) u_contract(
        .Q(Q),.CLK(CLK),.CEN(CEN),.WEN(WEN),.A(A),.D(D),
        .EMA(EMA),.EMAW(EMAW),.GWEN(GWEN),.RET1N(RET1N));
endmodule
`default_nettype wire
`endif
