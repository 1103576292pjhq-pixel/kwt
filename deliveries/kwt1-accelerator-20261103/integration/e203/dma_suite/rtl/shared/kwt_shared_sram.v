`default_nettype none
// SoC侧共享存储顶层，与独立加速器内部X/W存储分开。
// BASE_ADDR为开发选择，不宣称是赛方地址；须按512KiB对齐。
module kwt_shared_sram #(
    parameter [31:0] BASE_ADDR=32'ha0000000,
    parameter [2:0] SRAM_EMA=3'd2,
    parameter [1:0] SRAM_EMAW=2'd0
) (
    input wire clk,input wire rst_n,
    input wire icb_cmd_valid,output wire icb_cmd_ready,
    input wire [31:0] icb_cmd_addr,input wire icb_cmd_read,
    input wire [31:0] icb_cmd_wdata,input wire [3:0] icb_cmd_wmask,
    output wire icb_rsp_valid,input wire icb_rsp_ready,
    output wire [31:0] icb_rsp_rdata,output wire icb_rsp_err
);
    wire mem_req_valid,mem_req_ready,mem_req_write,mem_rsp_valid;
    wire [16:0] mem_req_addr;
    wire [31:0] mem_req_wdata,mem_rsp_rdata;
    wire [3:0] mem_req_wmask;
    kwt_shared_ram_icb #(.BASE_ADDR(BASE_ADDR)) u_icb(
        .clk(clk),.rst_n(rst_n),.icb_cmd_valid(icb_cmd_valid),.icb_cmd_ready(icb_cmd_ready),
        .icb_cmd_addr(icb_cmd_addr),.icb_cmd_read(icb_cmd_read),.icb_cmd_wdata(icb_cmd_wdata),
        .icb_cmd_wmask(icb_cmd_wmask),.icb_rsp_valid(icb_rsp_valid),.icb_rsp_ready(icb_rsp_ready),
        .icb_rsp_rdata(icb_rsp_rdata),.icb_rsp_err(icb_rsp_err),
        .mem_req_valid(mem_req_valid),.mem_req_ready(mem_req_ready),.mem_req_write(mem_req_write),
        .mem_req_addr(mem_req_addr),.mem_req_wdata(mem_req_wdata),.mem_req_wmask(mem_req_wmask),
        .mem_rsp_valid(mem_rsp_valid),.mem_rsp_rdata(mem_rsp_rdata));
    kwt_shared_sram_array #(.SRAM_EMA(SRAM_EMA),.SRAM_EMAW(SRAM_EMAW)) u_array(
        .clk(clk),.rst_n(rst_n),.mem_req_valid(mem_req_valid),.mem_req_ready(mem_req_ready),
        .mem_req_write(mem_req_write),.mem_req_addr(mem_req_addr),.mem_req_wdata(mem_req_wdata),
        .mem_req_wmask(mem_req_wmask),.mem_rsp_valid(mem_rsp_valid),.mem_rsp_rdata(mem_rsp_rdata));
`ifndef SYNTHESIS
    initial if(BASE_ADDR[18:0]!=0)$fatal(1,"Shared SRAM base must align to512KiB");
`endif
endmodule
`default_nettype wire
