`default_nettype none
// Two requesters, one outstanding transaction. Ownership lasts through response.
module kwt_icb_arbiter2 #(parameter B_PRIORITY=0)(
 input wire clk,rst_n,
 input wire a_valid,output wire a_ready,input wire [31:0] a_addr,a_data,
 input wire a_read,input wire [3:0] a_mask,
 output wire a_rsp_valid,input wire a_rsp_ready,output wire [31:0] a_rsp_data,output wire a_rsp_err,
 input wire b_valid,output wire b_ready,input wire [31:0] b_addr,b_data,
 input wire b_read,input wire [3:0] b_mask,
 output wire b_rsp_valid,input wire b_rsp_ready,output wire [31:0] b_rsp_data,output wire b_rsp_err,
 output wire m_valid,input wire m_ready,output wire [31:0] m_addr,m_data,
 output wire m_read,output wire [3:0] m_mask,
 input wire m_rsp_valid,output wire m_rsp_ready,input wire [31:0] m_rsp_data,input wire m_rsp_err,
 output wire idle
);
 reg pending,owner,locked,grant,last_owner;
 wire choose=locked ? grant : (a_valid && b_valid ? (B_PRIORITY ? 1'b1 : !last_owner) : b_valid);
 assign m_valid=rst_n && !pending && (choose ? b_valid : a_valid);
 assign m_addr=choose ? b_addr : a_addr;
 assign m_data=choose ? b_data : a_data;
 assign m_read=choose ? b_read : a_read;
 assign m_mask=choose ? b_mask : a_mask;
 assign a_ready=rst_n && !pending && !choose && m_ready;
 assign b_ready=rst_n && !pending && choose && m_ready;
 assign a_rsp_valid=rst_n && pending && !owner && m_rsp_valid;
 assign b_rsp_valid=rst_n && pending && owner && m_rsp_valid;
 assign a_rsp_data=m_rsp_data;
 assign b_rsp_data=m_rsp_data;
 assign a_rsp_err=m_rsp_err;
 assign b_rsp_err=m_rsp_err;
 assign m_rsp_ready=rst_n && pending && (owner ? b_rsp_ready : a_rsp_ready);
 assign idle=!pending && !locked && !a_valid && !b_valid;
 always @(posedge clk)begin
   if(!rst_n)begin pending<=0;owner<=0;locked<=0;grant<=0;last_owner<=1;end
   else begin
     if(m_valid && !m_ready)begin locked<=1;grant<=choose;end
     if(m_valid && m_ready)begin pending<=1;owner<=choose;locked<=0;end
     if(m_rsp_valid && m_rsp_ready)begin pending<=0;last_owner<=owner;end
   end
 end
endmodule
`default_nettype wire
