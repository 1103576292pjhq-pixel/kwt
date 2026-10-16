// Synchronous 1R1W storage. Validity is held by the controller, never RAM reset.
module encoder_sync_ram #(parameter WORDS=6336, AW=(WORDS<=1?1:$clog2(WORDS)))(
 input wire clk,input wire we,input wire [AW-1:0] waddr,
 input wire [31:0] wdata,input wire [AW-1:0] raddr,output reg [31:0] rdata);
 reg [31:0] mem[0:WORDS-1];
 always @(posedge clk) begin
  if(we)mem[waddr]<=wdata;
  rdata<=mem[raddr];
 end
endmodule
