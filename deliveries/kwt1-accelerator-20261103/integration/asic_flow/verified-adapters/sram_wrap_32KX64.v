`default_nettype none
// ASIC adapter; identical public TCM interface, one-cycle reads, active-high byte WEM.
// No FPGA branch: this file always instantiates official SRAM, including during its test.
module sram_wrap_32KX64 #(parameter ADDRWIDTH=15, parameter DATAWIDTH=64)(
 input wire CLK, input wire RSTN, input wire [ADDRWIDTH-1:0] ADDRESS,
 input wire CS, input wire WE, input wire [DATAWIDTH/8-1:0] WEM,
 input wire [DATAWIDTH-1:0] WDATA, output wire [DATAWIDTH-1:0] RDATA
);
localparam BANK_BITS=ADDRWIDTH-12;
localparam BANKS=1<<BANK_BITS;
localparam LANES=DATAWIDTH/16;
wire [DATAWIDTH-1:0] bank_q [0:BANKS-1];
reg [BANK_BITS-1:0] read_bank;
kwt_soc_tcm_configuration_guard u_configuration_guard();
generate if (ADDRWIDTH!=15 || DATAWIDTH!=64) begin : invalid_parameters
 KWT_TCM_WRAPPER_PARAMETER_MISMATCH stop();
end endgenerate
// Original ASIC wrapper records bank bits every clock and resets only this selector.
always @(posedge CLK or negedge RSTN) begin
 if (!RSTN) read_bank <= {BANK_BITS{1'b0}};
 else read_bank <= ADDRESS[ADDRWIDTH-1:12];
end
assign RDATA=bank_q[read_bank];
genvar b,l;
generate for(b=0;b<BANKS;b=b+1) begin : gen_bank
 localparam [BANK_BITS-1:0] BANK_ID=b;
 for(l=0;l<LANES;l=l+1) begin : gen_lane
  wire [15:0] wen=~{{8{WEM[2*l+1]}},{8{WEM[2*l]}}};
  RAMSP4096X16_rtl_top u_sram(
   .Q(bank_q[b][16*l +: 16]), .CLK(CLK),
   .CEN(!(CS && ADDRESS[ADDRWIDTH-1:12]==BANK_ID)),
   .GWEN(!WE), .WEN(wen), .A(ADDRESS[11:0]), .D(WDATA[16*l +: 16]),
   .EMA(3'd2), .EMAW(2'd0), .RET1N(1'b1));
 end
end endgenerate
endmodule
`default_nettype wire
