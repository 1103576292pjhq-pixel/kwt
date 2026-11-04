`timescale 1ns/1ps
`default_nettype none
// 可综合的临时共享 RAM 接口控制器；不包含存储阵列。
// BASE_ADDR 必须按 512 KiB 对齐。本项目开发暂用 0xa0000000，非赛方分配。
// 后端为单端口同步存储：req_valid&&req_ready 接受请求，随后周期返回 rsp_valid。
// 不支持后端零周期响应；一次最多一笔在途，ICB 响应可背压。
module kwt_shared_ram_icb #(
  parameter [31:0] BASE_ADDR = 32'ha0000000
) (
  input wire clk, input wire rst_n,
  input wire icb_cmd_valid, output wire icb_cmd_ready,
  input wire [31:0] icb_cmd_addr, input wire icb_cmd_read,
  input wire [31:0] icb_cmd_wdata, input wire [3:0] icb_cmd_wmask,
  output wire icb_rsp_valid, input wire icb_rsp_ready,
  output wire [31:0] icb_rsp_rdata, output wire icb_rsp_err,
  output wire mem_req_valid, input wire mem_req_ready,
  output wire mem_req_write, output wire [16:0] mem_req_addr,
  output wire [31:0] mem_req_wdata, output wire [3:0] mem_req_wmask,
  input wire mem_rsp_valid, input wire [31:0] mem_rsp_rdata
);
  localparam [1:0] IDLE=2'd0, WAIT_MEM=2'd1, RESPONSE=2'd2;
  reg [1:0] state;
  reg [31:0] response_data;
  reg response_error;
  wire address_valid = (icb_cmd_addr[31:19] == BASE_ADDR[31:19]);

  // 字节地址低两位由 CPU LSU 选择通路；RAM 读返回完整对齐字。
  // 写数据及掩码已经由总线主设备摆放到相应字节位置。
  assign mem_req_addr = icb_cmd_addr[18:2];
  assign mem_req_write = ~icb_cmd_read;
  assign mem_req_wdata = icb_cmd_wdata;
  assign mem_req_wmask = icb_cmd_wmask;
  assign mem_req_valid = rst_n && (state==IDLE) && icb_cmd_valid && address_valid;
  assign icb_cmd_ready = rst_n && (state==IDLE) && (!address_valid || mem_req_ready);
  assign icb_rsp_valid = rst_n && (state==RESPONSE);
  assign icb_rsp_rdata = response_data;
  assign icb_rsp_err = response_error;

  always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
      state<=IDLE;
      response_data<=32'b0;
      response_error<=1'b0;
    end else begin
      case(state)
        IDLE: if(icb_cmd_valid && icb_cmd_ready) begin
          if(!address_valid) begin
            // 非法窗口不向后端发请求，因此不会产生存储副作用。
            response_data<=32'b0;
            response_error<=1'b1;
            state<=RESPONSE;
          end else begin
            response_error<=1'b0;
            state<=WAIT_MEM;
          end
        end
        WAIT_MEM: if(mem_rsp_valid) begin
          response_data<=mem_rsp_rdata;
          response_error<=1'b0;
          state<=RESPONSE;
        end
        RESPONSE: if(icb_rsp_ready) state<=IDLE;
        default: state<=IDLE;
      endcase
    end
  end
endmodule
`default_nettype wire
