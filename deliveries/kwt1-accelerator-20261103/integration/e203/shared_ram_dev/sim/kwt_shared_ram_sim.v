`timescale 1ns/1ps
`default_nettype none
// 仅用于功能仿真。不可作为真实共享 SRAM 的面积、功耗或时序依据。
// 主要保护措施是独立仿真文件清单；SYNTHESIS 宏下再提供误用阻断。
`ifdef SYNTHESIS
`include "ERROR_SHARED_RAM_MODEL_IS_SIMULATION_ONLY.vh"
`endif
module kwt_shared_ram_sim #(
  parameter [31:0] BASE_ADDR = 32'ha0000000
) (
  input wire clk, input wire rst_n,
  input wire icb_cmd_valid, output wire icb_cmd_ready,
  input wire [31:0] icb_cmd_addr, input wire icb_cmd_read,
  input wire [31:0] icb_cmd_wdata, input wire [3:0] icb_cmd_wmask,
  output wire icb_rsp_valid, input wire icb_rsp_ready,
  output wire [31:0] icb_rsp_rdata, output wire icb_rsp_err
);
  wire mem_req_valid, mem_req_write;
  wire [16:0] mem_req_addr;
  wire [31:0] mem_req_wdata;
  wire [3:0] mem_req_wmask;
  reg mem_rsp_valid;
  reg [31:0] mem_rsp_rdata;
  // 131072 个 32 位字 = 524288 字节；不对未装载内容假定为零。
  reg [31:0] mem_r [0:131071];
  integer lane;

  initial begin
    if(BASE_ADDR[18:0] !== 19'b0)
      $fatal(1,"Shared RAM BASE_ADDR must align to 512 KiB");
  end

  kwt_shared_ram_icb #(.BASE_ADDR(BASE_ADDR)) u_icb (
    .clk(clk), .rst_n(rst_n),
    .icb_cmd_valid(icb_cmd_valid), .icb_cmd_ready(icb_cmd_ready),
    .icb_cmd_addr(icb_cmd_addr), .icb_cmd_read(icb_cmd_read),
    .icb_cmd_wdata(icb_cmd_wdata), .icb_cmd_wmask(icb_cmd_wmask),
    .icb_rsp_valid(icb_rsp_valid), .icb_rsp_ready(icb_rsp_ready),
    .icb_rsp_rdata(icb_rsp_rdata), .icb_rsp_err(icb_rsp_err),
    .mem_req_valid(mem_req_valid), .mem_req_ready(1'b1),
    .mem_req_write(mem_req_write), .mem_req_addr(mem_req_addr),
    .mem_req_wdata(mem_req_wdata), .mem_req_wmask(mem_req_wmask),
    .mem_rsp_valid(mem_rsp_valid), .mem_rsp_rdata(mem_rsp_rdata)
  );

  // 同步后端：请求接受后的周期给出响应；每次写按字节掩码更新。
  // 控制复位不清空存储阵列，避免伪造整块 SRAM 的硬件复位能力。
  always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
      mem_rsp_valid<=1'b0;
      mem_rsp_rdata<=32'b0;
    end else begin
      mem_rsp_valid<=mem_req_valid;
      if(mem_req_valid) begin
        if(mem_req_write) begin
          for(lane=0;lane<4;lane=lane+1)
            if(mem_req_wmask[lane]) mem_r[mem_req_addr][lane*8+:8]<=mem_req_wdata[lane*8+:8];
          mem_rsp_rdata<=32'b0;
        end else mem_rsp_rdata<=mem_r[mem_req_addr];
      end
    end
  end
endmodule
`default_nettype wire
