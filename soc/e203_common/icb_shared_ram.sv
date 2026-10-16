// 512 KiB shared SRAM model, synchronous read, one outstanding transaction.
// No memory reset: firmware/test fixture must initialize every word it reads.
module icb_shared_ram #(
  parameter [31:0] BASE_ADDR=32'ha0000000,
  parameter integer BYTES=524288
)(
  input wire clk, rst_n,
  input wire icb_cmd_valid,
  output wire icb_cmd_ready,
  input wire [31:0] icb_cmd_addr,
  input wire icb_cmd_read,
  input wire [31:0] icb_cmd_wdata,
  input wire [3:0] icb_cmd_wmask,
  output reg icb_rsp_valid,
  input wire icb_rsp_ready,
  output reg [31:0] icb_rsp_rdata,
  output reg icb_rsp_err
);
  localparam integer WORDS=BYTES/4;
  localparam integer WORD_AW=(WORDS<=1) ? 1 : $clog2(WORDS);
  reg [31:0] mem [0:WORDS-1];
  wire [31:0] offset=icb_cmd_addr-BASE_ADDR;
  wire address_ok=(icb_cmd_addr>=BASE_ADDR) && (offset<BYTES);
  wire [WORD_AW-1:0] word_index=offset[WORD_AW+1:2];
  integer lane;
  assign icb_cmd_ready=~icb_rsp_valid;
  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      icb_rsp_valid<=0;
      icb_rsp_rdata<=0;
      icb_rsp_err<=0;
    end else begin
      if (icb_rsp_valid && icb_rsp_ready) icb_rsp_valid<=0;
      if (icb_cmd_valid && icb_cmd_ready) begin
        icb_rsp_valid<=1;
        icb_rsp_err<=~address_ok;
        icb_rsp_rdata<=0;
        if (address_ok) begin
          if (icb_cmd_read) icb_rsp_rdata<=mem[word_index];
          else for (lane=0; lane<4; lane=lane+1)
            if (icb_cmd_wmask[lane]) mem[word_index][lane*8+:8]<=icb_cmd_wdata[lane*8+:8];
        end
      end
    end
  end
endmodule
