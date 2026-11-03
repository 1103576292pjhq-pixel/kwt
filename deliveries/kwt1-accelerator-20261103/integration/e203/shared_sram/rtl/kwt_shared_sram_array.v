`default_nettype none
// 512KiB单端口宏阵列：32组，每组低/高半字各一颗4096x16。
// 后端一次一笔；rsp_valid在请求接受后有效，使用方在下一上升沿接收。
// 读请求的组/行保留到接收沿；保持选通会有同址重复读，不声称最优活动。
module kwt_shared_sram_array #(
    parameter [2:0] SRAM_EMA=3'd2,
    parameter [1:0] SRAM_EMAW=2'd0
) (
    input wire clk,input wire rst_n,
    input wire mem_req_valid,output wire mem_req_ready,
    input wire mem_req_write,input wire [16:0] mem_req_addr,
    input wire [31:0] mem_req_wdata,input wire [3:0] mem_req_wmask,
    output wire mem_rsp_valid,output wire [31:0] mem_rsp_rdata
);
    reg pending;
    reg return_read;
    reg [4:0] return_bank;
    reg [11:0] return_row;
    wire accept=mem_req_valid&&mem_req_ready;
    assign mem_req_ready=rst_n&&!pending;
    assign mem_rsp_valid=rst_n&&pending;
    wire [15:0] low_q[0:31];
    wire [15:0] high_q[0:31];
    assign mem_rsp_rdata=return_read?{high_q[return_bank],low_q[return_bank]}:32'b0;
    wire [11:0] row=pending?return_row:mem_req_addr[11:0];
    wire [15:0] low_wen=~{{8{mem_req_wmask[1]}},{8{mem_req_wmask[0]}}};
    wire [15:0] high_wen=~{{8{mem_req_wmask[3]}},{8{mem_req_wmask[2]}}};
    genvar b;
    generate for(b=0;b<32;b=b+1)begin:gen_bank
        wire selected=rst_n&&((accept&&(mem_req_addr[16:12]==b))||
                                     (pending&&return_read&&(return_bank==b)));
        wire write_now=accept&&mem_req_write&&(mem_req_addr[16:12]==b);
        RAMSP4096X16_rtl_top u_low(
            .Q(low_q[b]),.CLK(clk),.CEN(!selected),.GWEN(!write_now),
            .WEN(write_now?low_wen:16'hffff),.A(row),.D(mem_req_wdata[15:0]),
            .EMA(SRAM_EMA),.EMAW(SRAM_EMAW),.RET1N(1'b1));
        RAMSP4096X16_rtl_top u_high(
            .Q(high_q[b]),.CLK(clk),.CEN(!selected),.GWEN(!write_now),
            .WEN(write_now?high_wen:16'hffff),.A(row),.D(mem_req_wdata[31:16]),
            .EMA(SRAM_EMA),.EMAW(SRAM_EMAW),.RET1N(1'b1));
    end endgenerate
    always @(posedge clk or negedge rst_n)begin
        if(!rst_n)begin
            pending<=0;return_read<=0;return_bank<=0;return_row<=0;
        end else begin
            pending<=accept;
            if(accept)begin
                return_read<=!mem_req_write;
                return_bank<=mem_req_addr[16:12];
                return_row<=mem_req_addr[11:0];
            end
        end
    end
endmodule
`default_nettype wire
