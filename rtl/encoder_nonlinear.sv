// Fixed-formula exp_neg / GELU microsequencer. All arithmetic uses shared FP32.
module encoder_nonlinear(
 input wire clk,rst_n,req_valid,output wire req_ready,input wire req_gelu,
 input wire [31:0] req_x,output reg rsp_valid,input wire rsp_ready,
 output reg [31:0] rsp_data,output reg [4:0] rsp_flags,output reg rsp_error,
 output wire fp_req_valid,input wire fp_req_ready,output reg [3:0] fp_req_op,
 output reg [31:0] fp_req_a,fp_req_b,fp_req_c,
 input wire fp_rsp_valid,output wire fp_rsp_ready,input wire [31:0] fp_rsp_data,
 input wire [4:0] fp_rsp_flags,input wire fp_rsp_error);
 reg active,waiting,gelu;reg [5:0] pc;
 reg [31:0] x,z,t,nf,r,p,power,e,den,num;
 reg [3:0] coefficient;
 function automatic [31:0] coeff(input [3:0] k);
  case(k)
   0,1:coeff=32'h3f800000;2:coeff=32'h3f000000;3:coeff=32'h3e2aaaab;
   4:coeff=32'h3d2aaaab;5:coeff=32'h3c088889;6:coeff=32'h3ab60b61;
   7:coeff=32'h39500d01;default:coeff=32'h37d00d01;
  endcase
 endfunction
 assign req_ready=!active&&!rsp_valid;
 assign fp_req_valid=active&&!waiting;
 assign fp_rsp_ready=active&&waiting;
 always @* begin
  fp_req_op=0;fp_req_a=0;fp_req_b=0;fp_req_c=0;
  case(pc)
   1:begin fp_req_op=2;fp_req_a=x;fp_req_b=x;end
   2:begin fp_req_op=2;fp_req_a=t;fp_req_b=x;end
   3:begin fp_req_op=3;fp_req_a=32'h3d372713;fp_req_b=t;fp_req_c=x;end
   4:begin fp_req_op=2;fp_req_a=32'h3f4c422a;fp_req_b=t;end
   5:begin fp_req_op=2;fp_req_a={1'b0,t[30:0]};fp_req_b=32'hc0000000;end
   10:begin fp_req_op=2;fp_req_a=z;fp_req_b=32'h3fb8aa3b;end
   11:begin fp_req_op=6;fp_req_a=t;end
   12:begin fp_req_op=7;fp_req_a=t;end
   13:begin fp_req_op=3;fp_req_a={~nf[31],nf[30:0]};fp_req_b=32'h3f317200;fp_req_c=z;end
   14:begin fp_req_op=3;fp_req_a={~nf[31],nf[30:0]};fp_req_b=32'h35bfbe8e;fp_req_c=r;end
   15:begin fp_req_op=3;fp_req_a=p;fp_req_b=r;fp_req_c=coeff(coefficient);end
   16:begin fp_req_op=2;fp_req_a=p;fp_req_b=power;end
   30:begin fp_req_op=0;fp_req_a=32'h3f800000;fp_req_b=e;end
   31:begin fp_req_op=2;fp_req_a=x;fp_req_b=e;end
   32:begin fp_req_op=4;fp_req_a=num;fp_req_b=den;end
   default:begin end
  endcase
 end
 always @(posedge clk) begin
  if(!rst_n)begin active<=0;waiting<=0;rsp_valid<=0;rsp_data<=0;rsp_flags<=0;rsp_error<=0;pc<=0;gelu<=0;end
  else begin
   if(rsp_valid&&rsp_ready)rsp_valid<=0;
   if(req_valid&&req_ready)begin
    x<=req_x;z<=req_x;gelu<=req_gelu;waiting<=0;rsp_flags<=0;rsp_error<=0;
    if(req_x[30:23]==255 || (!req_gelu && !req_x[31] && req_x[30:0]!=0))begin
     rsp_valid<=1;rsp_error<=1;rsp_data<=32'h7fc00000;
    end else if(req_gelu && req_x[30:0]>=31'h41200000)begin
     rsp_valid<=1;rsp_data<=req_x[31]?32'h80000000:req_x;
    end else if(!req_gelu && req_x[31] && req_x[30:0]>=31'h42a00000)begin
     rsp_valid<=1;rsp_data<=0;
    end else if(!req_gelu && req_x[30:0]==0)begin rsp_valid<=1;rsp_data<=32'h3f800000;
    end else begin active<=1;pc<=req_gelu?1:10;end
   end
   if(fp_req_valid&&fp_req_ready)waiting<=1;
   if(fp_rsp_valid&&fp_rsp_ready)begin
    waiting<=0;rsp_flags<=rsp_flags|fp_rsp_flags;rsp_error<=rsp_error|fp_rsp_error;
    case(pc)
     1,2,3,4:begin t<=fp_rsp_data;pc<=pc+1'b1;end
     5:begin
      z<=fp_rsp_data;
      if(fp_rsp_data[30:0]>=31'h42a00000)begin e<=0;pc<=30;end
      else if(fp_rsp_data[30:0]==0)begin e<=32'h3f800000;pc<=30;end
      else pc<=10;
     end
     10:begin t<=fp_rsp_data;pc<=11;end
     11:begin t<=fp_rsp_data;power<=(fp_rsp_data+32'd127)<<23;pc<=12;end
     12:begin nf<=fp_rsp_data;pc<=13;end
     13:begin r<=fp_rsp_data;pc<=14;end
     14:begin r<=fp_rsp_data;p<=coeff(8);coefficient<=7;pc<=15;end
     15:begin p<=fp_rsp_data;if(coefficient==0)pc<=16;else coefficient<=coefficient-1'b1;end
     16:begin
      if(gelu)begin e<=fp_rsp_data;pc<=30;end
      else begin rsp_data<=fp_rsp_data;rsp_valid<=1;active<=0;end
     end
     30:begin den<=fp_rsp_data;if(x[31])pc<=31;else begin num<=x;pc<=32;end end
     31:begin num<=fp_rsp_data;pc<=32;end
     32:begin rsp_data<=fp_rsp_data;rsp_valid<=1;active<=0;end
     default:begin active<=0;rsp_valid<=1;rsp_error<=1;rsp_data<=32'h7fc00000;end
    endcase
   end
  end
 end
endmodule
