// Compilable RED: implements the handshake, but incorrectly returns zero.
module encoder_fp32(
 input clk,rst_n,req_valid,output req_ready,input[3:0]req_op,
 input[31:0]req_a,req_b,req_c,output reg rsp_valid,input rsp_ready,
 output reg[31:0]rsp_data,output reg[4:0]rsp_flags,output reg rsp_error,output busy);
 assign busy=rsp_valid;
 assign req_ready=!rsp_valid;
 always @(posedge clk) begin
  if(!rst_n) begin rsp_valid<=0;rsp_data<=0;rsp_flags<=0;rsp_error<=0;end
  else if(req_valid&&req_ready) begin rsp_valid<=1;rsp_data<=0;rsp_flags<=0;rsp_error<=0;end
  else if(rsp_valid&&rsp_ready) rsp_valid<=0;
 end
endmodule
