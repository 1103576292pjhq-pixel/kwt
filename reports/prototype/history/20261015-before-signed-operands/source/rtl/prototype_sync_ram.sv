// One synchronous port. Read/write are mutually exclusive; storage is not reset.
module prototype_sync_ram #(
    parameter integer WIDTH=16, DEPTH=64
)(
    input wire clk,
    input wire wr_en,
    input wire [31:0] wr_addr,
    input wire [WIDTH-1:0] wr_data,
    input wire rd_en,
    input wire [31:0] rd_addr,
    output reg [WIDTH-1:0] rd_data
);
    localparam integer AW=(DEPTH>1)?$clog2(DEPTH):1;
    reg [WIDTH-1:0] mem[0:DEPTH-1];
    always @(posedge clk) begin
        if(wr_en) mem[wr_addr[AW-1:0]] <= wr_data;
        else if(rd_en) rd_data <= mem[rd_addr[AW-1:0]];
    end
endmodule
