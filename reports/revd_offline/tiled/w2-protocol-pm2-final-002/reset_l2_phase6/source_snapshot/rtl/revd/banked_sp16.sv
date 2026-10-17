`timescale 1ns/1ps
module banked_sp16 #(parameter integer DEPTH=1600,ADDR_W=$clog2(DEPTH),READ_LATENCY=1)(
 input wire clk,rst_n,wr_en,rd_en,input wire [ADDR_W-1:0] addr,
 input wire signed [15:0] wr_data,output wire signed [15:0] rd_data,output wire rd_valid);
 reg signed [15:0] mem[0:DEPTH-1];
 reg signed [15:0] data_pipe[0:READ_LATENCY-1];
 reg [READ_LATENCY-1:0] valid_pipe;
 integer p;
 assign rd_data=data_pipe[READ_LATENCY-1];assign rd_valid=valid_pipe[READ_LATENCY-1];
 always @(posedge clk) begin
  if(!rst_n) valid_pipe<='0;
  else begin
   valid_pipe[0]<=rd_en;
   if(wr_en) mem[addr]<=wr_data;
   else if(rd_en) data_pipe[0]<=mem[addr];
   for(p=1;p<READ_LATENCY;p=p+1) begin
    valid_pipe[p]<=valid_pipe[p-1];
    if(valid_pipe[p-1]) data_pipe[p]<=data_pipe[p-1];
   end
  end
 end
endmodule
