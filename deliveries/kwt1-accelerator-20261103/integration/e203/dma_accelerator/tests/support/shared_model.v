`timescale 1ns/1ps
module RAMSP4096X16_rtl_top(output reg [15:0] Q,input CLK,CEN,
 input [15:0] WEN,input [11:0] A,input [15:0] D,input [2:0] EMA,
 input [1:0] EMAW,input GWEN,RET1N);
 reg [15:0] data[0:4095];integer k;
 always @(posedge CLK)if(!CEN)begin
  if(GWEN)Q<=#0.2 data[A];
  else for(k=0;k<16;k=k+1)if(!WEN[k])data[A][k]<=D[k];
 end
 // 测试替身主动令待机Q未知，避免无意依赖Q保持。
 always @(CEN)if(CEN)Q<=#0.1 16'hxxxx;
endmodule
