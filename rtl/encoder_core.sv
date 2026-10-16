// Sequential encoder: one shared IEEE FP32 unit, synchronous bulk RAM,
// row-local scratch, full K/V, and X/Y ping-pong. No host neural arithmetic.
module encoder_core #(parameter integer M=99,D=64,H=256)(
 input wire clk,rst_n,req_valid,output wire req_ready,input wire [2:0] req_op,
 input wire [31:0] req_addr,req_data,output reg rsp_valid,input wire rsp_ready,
 output reg [31:0] rsp_data,output reg rsp_error,output reg busy,done,job_done,fault,
 output reg [31:0] x_count,w_count,layer_index,output reg [63:0] cycles,
 output reg [4:0] flags,output reg trace_valid,output reg [3:0] trace_stage,
 output reg [31:0] trace_addr,trace_data);
 localparam WORDS=4*D*D+2*D*H+H+6*D;
 localparam XA=(M*D<=1?1:$clog2(M*D)),WA=(WORDS<=1?1:$clog2(WORDS));
 localparam WQ=0,WK=D*D,WV=2*D*D,WO=3*D*D,BO=4*D*D,
 G1=BO+D,B1=G1+D,W1=B1+D,BH=W1+D*H,W2=BH+H,B2=W2+H*D,G2=B2+D,BN2=G2+D;
 localparam PK=0,PV=1,PQ=2,PSCORE=3,PSCALE=4,PDELTA=5,PEXP=6,PSUM=7,
 PPROB=8,PCTX=9,PATTN=10,PBO=11,PR1=12,PLSUM=13,PLMEAN=14,
 PLCENTER=15,PLVAR=16,PLVMUL=17,PLEPS=18,PLSQRT=19,PLINV=20,
 PLNMUL=21,PLAFF=22,PFF1=23,PBH=24,PGELU=25,PFF2=26,PB2=27,PR2=28;
 reg [5:0] phase;reg [1:0] step,read_state;
 reg job_active,x_bank,second_norm,attention_only;
 initial begin
  if(M<1||M>99||(D!=4&&D!=64)||H<1||H>256)$error("Supported geometry: 1<=M<=99, D=4 or 64, 1<=H<=256");
 end
 integer row,col,k;
 reg [31:0] acc,maximum,total,mean,invstd,center,scaled,expval;
 reg [31:0] q[0:D-1],context_row[0:D-1],tmp[0:D-1],n1[0:D-1];
 reg [31:0] score[0:M-1],prob[0:M-1],hidden[0:H-1];
 reg [31:0] xraddr,wraddr,kraddr,vraddr,read_addr;
 wire [31:0] xd0,xd1,wd,kd,vd;
 wire [31:0] xd=x_bank?xd1:xd0;
 wire accept=req_valid&&req_ready;
 wire load_x=accept&&!busy&&job_active&&!done&&req_op==1&&req_addr==x_count&&x_count<M*D;
 wire load_w=accept&&!busy&&job_active&&!done&&req_op==2&&req_addr==w_count&&w_count<WORDS;
 wire fp_valid,fp_ready,fp_rvalid,fp_rready,fp_error,fp_busy;
 wire [31:0] fp_result;wire [4:0] fp_flags;
 reg [3:0] op;reg [31:0] a,b,c;
 wire nonlinear=(phase==PEXP||phase==PGELU);
 wire nl_valid,nl_ready,nl_error;wire [31:0] nl_result;wire [4:0] nl_flags;
 wire nl_fvalid,nl_fready,nl_frready;wire [3:0] nl_op;wire [31:0] nl_a,nl_b,nl_c;
 wire result_valid=nonlinear?nl_valid:fp_rvalid;
 wire [31:0] result=nonlinear?nl_result:fp_result;
 wire result_error=nonlinear?nl_error:fp_error;
 wire [4:0] result_flags=nonlinear?nl_flags:fp_flags;
 wire finish_op=busy&&step==2&&result_valid;
 wire kwrite=finish_op&&phase==PK&&k==D-1;
 wire vwrite=finish_op&&phase==PV&&k==D-1;
 wire ywrite=finish_op&&((phase==PLAFF&&second_norm)||(phase==PBO&&attention_only));
 wire [31:0] x_read_address=read_state!=0?read_addr:xraddr;
 wire [31:0] x_write_address=load_x?req_addr:row*D+col;
 wire [31:0] x_write_data=load_x?req_data:result;
 assign req_ready=!rsp_valid&&read_state==0;
 assign fp_valid=nonlinear?nl_fvalid:(busy&&step==1);
 assign nl_fready=nonlinear&&fp_ready;
 assign fp_rready=nonlinear?nl_frready:(busy&&step==2);
 encoder_fp32 fpu(.clk(clk),.rst_n(rst_n),.req_valid(fp_valid),.req_ready(fp_ready),
  .req_op(nonlinear?nl_op:op),.req_a(nonlinear?nl_a:a),.req_b(nonlinear?nl_b:b),
  .req_c(nonlinear?nl_c:c),.rsp_valid(fp_rvalid),.rsp_ready(fp_rready),
  .rsp_data(fp_result),.rsp_flags(fp_flags),.rsp_error(fp_error),.busy(fp_busy));
 encoder_nonlinear nl(.clk(clk),.rst_n(rst_n),.req_valid(busy&&step==1&&nonlinear),
  .req_ready(nl_ready),.req_gelu(phase==PGELU),.req_x(phase==PGELU?hidden[col]:scaled),
  .rsp_valid(nl_valid),.rsp_ready(busy&&step==2&&nonlinear),.rsp_data(nl_result),
  .rsp_flags(nl_flags),.rsp_error(nl_error),.fp_req_valid(nl_fvalid),.fp_req_ready(nl_fready),
  .fp_req_op(nl_op),.fp_req_a(nl_a),.fp_req_b(nl_b),.fp_req_c(nl_c),
  .fp_rsp_valid(fp_rvalid&&nonlinear),.fp_rsp_ready(nl_frready),.fp_rsp_data(fp_result),
  .fp_rsp_flags(fp_flags),.fp_rsp_error(fp_error));
 encoder_sync_ram #(.WORDS(WORDS),.AW(WA)) weights_ram(clk,load_w,req_addr[WA-1:0],req_data,wraddr[WA-1:0],wd);
 encoder_sync_ram #(.WORDS(M*D),.AW(XA)) x0(clk,(load_x&&!x_bank)||(ywrite&&x_bank),x_write_address[XA-1:0],x_write_data,x_read_address[XA-1:0],xd0);
 encoder_sync_ram #(.WORDS(M*D),.AW(XA)) x1(clk,(load_x&&x_bank)||(ywrite&&!x_bank),x_write_address[XA-1:0],x_write_data,x_read_address[XA-1:0],xd1);
 wire [31:0] kvwaddr=row*D+col;
 encoder_sync_ram #(.WORDS(M*D),.AW(XA)) keys(clk,kwrite,kvwaddr[XA-1:0],result,kraddr[XA-1:0],kd);
 encoder_sync_ram #(.WORDS(M*D),.AW(XA)) values_ram(clk,vwrite,kvwaddr[XA-1:0],result,vraddr[XA-1:0],vd);
 // Numeric ordering for finite FP32, treating both signed zeros as equal.
 function automatic greater(input [31:0] lhs,rhs);
  if(lhs[30:0]==0&&rhs[30:0]==0)greater=0;
  else if(lhs[31]!=rhs[31])greater=!lhs[31];
  else greater=lhs[31]?(lhs[30:0]<rhs[30:0]):(lhs[30:0]>rhs[30:0]);
 endfunction
 task emit(input [3:0] stage,input [31:0] addr,value);
  begin trace_valid<=1;trace_stage<=stage;trace_addr<=addr;trace_data<=value;end
 endtask
 always @* begin
  xraddr=row*D+k;wraddr=0;kraddr=col*D+k;vraddr=k*D+col;
  op=0;a=0;b=0;c=0;
  case(phase)
   PK,PV,PQ:begin
    wraddr=(phase==PK?WK:phase==PV?WV:WQ)+k*D+col;
    op=3;a=xd;b=wd;c=acc;
   end
   PSCORE:begin op=3;a=q[k];b=kd;c=acc;end
   PSCALE:begin op=2;a=acc;b=32'h3e000000;end
   PDELTA:begin op=1;a=score[col];b=maximum;end
   PSUM:begin a=total;b=expval;end
   PPROB:begin op=4;a=prob[col];b=total;end
   PCTX:begin op=3;a=prob[k];b=vd;c=acc;end
   PATTN:begin wraddr=WO+k*D+col;op=3;a=context_row[k];b=wd;c=acc;end
   PBO:begin wraddr=BO+col;a=acc;b=wd;end
   PR1:begin xraddr=row*D+col;a=tmp[col];b=xd;end
   PLSUM:begin a=total;b=tmp[col];end
   PLMEAN:begin op=2;a=total;b=(D==64?32'h3c800000:D==4?32'h3e800000:32'h3f800000);end
   PLCENTER:begin op=1;a=tmp[col];b=mean;end
   PLVAR:begin op=3;a=center;b=center;c=acc;end
   PLVMUL:begin op=2;a=acc;b=(D==64?32'h3c800000:D==4?32'h3e800000:32'h3f800000);end
   PLEPS:begin a=scaled;b=32'h358637bd;end
   PLSQRT:begin op=5;a=scaled;end
   PLINV:begin op=4;a=32'h3f800000;b=scaled;end
   PLNMUL:begin op=2;a=tmp[col];b=invstd;end
   PLAFF:begin wraddr=(second_norm?G2:G1)+col;op=3;a=scaled;b=wd;c=center;end
   PFF1:begin wraddr=W1+k*H+col;op=3;a=n1[k];b=wd;c=acc;end
   PBH:begin wraddr=BH+col;a=acc;b=wd;end
   PFF2:begin wraddr=W2+k*D+col;op=3;a=hidden[k];b=wd;c=acc;end
   PB2:begin wraddr=B2+col;a=acc;b=wd;end
   PR2:begin a=n1[col];b=tmp[col];end
   default:begin end
  endcase
  // Beta uses the same single synchronous weight read port as gamma. It is
  // fetched in PLNMUL, captured at response, then gamma is fetched in PLAFF.
  if(phase==PLNMUL)wraddr=(second_norm?BN2:B1)+col;
 end
 always @(posedge clk)begin
  if(!rst_n)begin
   rsp_valid<=0;rsp_data<=0;rsp_error<=0;busy<=0;done<=0;job_done<=0;fault<=0;
   job_active<=0;x_count<=0;w_count<=0;layer_index<=0;x_bank<=0;cycles<=0;attention_only<=0;
   flags<=0;read_state<=0;phase<=PK;step<=0;row<=0;col<=0;k<=0;trace_valid<=0;
  end else begin
   trace_valid<=0;
   if(rsp_valid&&rsp_ready)rsp_valid<=0;
   if(read_state==1)read_state<=2;
   if(read_state==2)begin
    rsp_valid<=1;rsp_data<=x_bank?xd0:xd1;rsp_error<=0;read_state<=0;
   end
   if(accept)begin
    rsp_valid<=1;rsp_data<=0;rsp_error<=0;
    if(busy)rsp_error<=1;
    else case(req_op)
     0:begin job_active<=1;x_bank<=0;x_count<=0;w_count<=0;layer_index<=0;done<=0;job_done<=0;fault<=0;attention_only<=0;end
     1:if(load_x)x_count<=x_count+1;else rsp_error<=1;
     2:if(load_w)w_count<=w_count+1;else rsp_error<=1;
     3,6:if(job_active&&!done&&!fault&&x_count==M*D&&w_count==WORDS&&req_data==layer_index&&layer_index<12&&(req_op==3||layer_index==0))begin
      busy<=1;phase<=PK;step<=0;row<=0;col<=0;k<=0;acc<=0;cycles<=0;flags<=0;second_norm<=0;
      attention_only<=req_op==6;
     end else rsp_error<=1;
     4:if(done&&req_addr<M*D)begin rsp_valid<=0;read_addr<=req_addr;read_state<=1;end else rsp_error<=1;
     5:if(done&&!attention_only&&layer_index<11)begin x_bank<=!x_bank;layer_index<=layer_index+1;w_count<=0;done<=0;end else rsp_error<=1;
     7:if(done&&!attention_only&&layer_index<11)begin layer_index<=layer_index+1;w_count<=0;x_count<=0;done<=0;end else rsp_error<=1;
     default:rsp_error<=1;
    endcase
   end
   if(busy)begin
    cycles<=cycles+1;
    if(step==0)step<=1;
    else if(step==1&& (nonlinear?nl_ready:fp_ready))step<=2;
    if(finish_op)begin
     step<=0;flags<=flags|result_flags;
     if(result_error||result[30:23]==8'hff)begin busy<=0;fault<=1;flags<=flags|result_flags;end
     else case(phase)
      PK,PV,PQ:begin
       if(k+1<D)begin k<=k+1;acc<=result;end
       else begin
        emit(phase==PK?1:phase==PV?2:0,row*D+col,result);
        if(phase==PQ)q[col]<=result;
        k<=0;acc<=0;
        if(col+1<D)col<=col+1;
        else begin
         col<=0;
         if(phase==PQ)phase<=PSCORE;
         else if(row+1<M)row<=row+1;
         else begin row<=0;phase<=phase==PK?PV:PQ;end
        end
       end
      end
      PSCORE:begin acc<=result;if(k+1<D)k<=k+1;else begin k<=0;phase<=PSCALE;end end
      PSCALE:begin
       score[col]<=result;emit(3,row*M+col,result);acc<=0;
       if(col==0||greater(result,maximum))maximum<=result;
       if(col+1<M)begin col<=col+1;phase<=PSCORE;end
       else begin col<=0;total<=0;phase<=PDELTA;end
      end
      PDELTA:begin scaled<=result;phase<=PEXP;end
      PEXP:begin expval<=result;prob[col]<=result;phase<=PSUM;end
      PSUM:begin
       total<=result;
       if(col+1<M)begin col<=col+1;phase<=PDELTA;end
       else begin col<=0;phase<=PPROB;end
      end
      PPROB:begin
       prob[col]<=result;emit(4,row*M+col,result);
       if(col+1<M)col<=col+1;else begin col<=0;k<=0;acc<=0;phase<=PCTX;end
      end
      PCTX:begin
       if(k+1<M)begin k<=k+1;acc<=result;end
       else begin
        context_row[col]<=result;emit(5,row*D+col,result);k<=0;acc<=0;
        if(col+1<D)col<=col+1;else begin col<=0;phase<=PATTN;end
       end
      end
      PATTN,PFF1,PFF2:begin
       acc<=result;
       if(k+1<(phase==PFF2?H:D))k<=k+1;
       else begin k<=0;phase<=phase==PATTN?PBO:phase==PFF1?PBH:PB2;end
      end
      PBO:begin
       tmp[col]<=result;emit(6,row*D+col,result);acc<=0;
       if(col+1<D)begin col<=col+1;phase<=PATTN;end
       else begin
        col<=0;
        if(!attention_only)phase<=PR1;
        else if(row+1<M)begin row<=row+1;phase<=PQ;end
        else begin busy<=0;done<=1;job_done<=0;end
       end
      end
      PR1:begin
       tmp[col]<=result;emit(7,row*D+col,result);
       if(col+1<D)col<=col+1;else begin col<=0;total<=0;second_norm<=0;phase<=PLSUM;end
      end
      PLSUM:begin total<=result;if(col+1<D)col<=col+1;else begin col<=0;phase<=PLMEAN;end end
      PLMEAN:begin mean<=result;acc<=0;phase<=PLCENTER;end
      PLCENTER:begin center<=result;tmp[col]<=result;phase<=PLVAR;end
      PLVAR:begin
       acc<=result;
       if(col+1<D)begin col<=col+1;phase<=PLCENTER;end else begin col<=0;phase<=PLVMUL;end
      end
      PLVMUL:begin scaled<=result;phase<=PLEPS;end
      PLEPS:begin scaled<=result;phase<=PLSQRT;end
      PLSQRT:begin scaled<=result;phase<=PLINV;end
      PLINV:begin invstd<=result;phase<=PLNMUL;end
      PLNMUL:begin scaled<=result;center<=wd;phase<=PLAFF;end
      PLAFF:begin
       emit(second_norm?13:8,row*D+col,result);
       if(!second_norm)n1[col]<=result;
       if(col+1<D)begin col<=col+1;phase<=PLNMUL;end
       else begin
        col<=0;k<=0;acc<=0;
        if(!second_norm)phase<=PFF1;
        else if(row+1<M)begin row<=row+1;phase<=PQ;end
        else begin busy<=0;done<=1;job_done<=layer_index==11;end
       end
      end
      PBH:begin hidden[col]<=result;emit(9,row*H+col,result);phase<=PGELU;end
      PGELU:begin
       hidden[col]<=result;emit(10,row*H+col,result);acc<=0;
       if(col+1<H)begin col<=col+1;phase<=PFF1;end else begin col<=0;phase<=PFF2;end
      end
      PB2:begin
       tmp[col]<=result;emit(11,row*D+col,result);acc<=0;
       if(col+1<D)begin col<=col+1;phase<=PFF2;end else begin col<=0;phase<=PR2;end
      end
      PR2:begin
       tmp[col]<=result;emit(12,row*D+col,result);
       if(col+1<D)col<=col+1;else begin col<=0;total<=0;second_norm<=1;phase<=PLSUM;end
      end
      default:begin busy<=0;flags<=flags|5'b10000;end
     endcase
    end
   end
  end
 end
endmodule
