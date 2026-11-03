`timescale 1ns/1ps
// 测试专用加载协调，不属于生产host接口。首任务reset内预装；后续仅在CPU请求响应退休后接管。
module kwt_suite_loader #(parameter NUM_TASKS=12,FIRST_CASE=1)(
 input wire clk,input wire [3:0] request_seq,output reg first=1,
 output reg done=0,output reg mode=1,output reg reset_n=0,
 output reg cmd_valid=0,input wire cmd_ready,output reg [31:0] cmd_addr=0,
 output wire cmd_read,output reg [31:0] cmd_wdata=0,output wire [3:0] cmd_wmask,
 input wire rsp_valid,output reg rsp_ready=0,input wire rsp_err,input wire [31:0] rsp_rdata);
 assign cmd_read=0;assign cmd_wmask=4'hf;
 reg [31:0] x[0:6335],w[0:16383],b[0:255],gold[0:25343];
 reg [4095:0] folder,path;
 integer i,seq_no,writes=0,guard,case_id;
 task write_word(input [31:0] address,input [31:0] value);
 begin
   if((^value)===1'bx)$fatal(1,"SUITE_LOADER unknown input address=%h",address);
   @(negedge clk);cmd_valid=1;cmd_addr=address;cmd_wdata=value;
   @(posedge clk);guard=0;
   while(cmd_ready!==1'b1)begin @(posedge clk);guard=guard+1;if(guard>100)$fatal(1,"SUITE_LOADER command timeout");end
   @(negedge clk);cmd_valid=0;guard=0;
   while(rsp_valid!==1'b1)begin @(negedge clk);guard=guard+1;if(guard>100)$fatal(1,"SUITE_LOADER response timeout");end
   if(rsp_err!==1'b0)$fatal(1,"SUITE_LOADER bus error");
   rsp_ready=1;@(posedge clk);@(negedge clk);rsp_ready=0;writes=writes+1;
 end
 endtask
 initial begin
   if(NUM_TASKS<1||FIRST_CASE<1||FIRST_CASE+NUM_TASKS>13)$fatal(1,"SUITE_LOADER bad case range");
   if(!$value$plusargs("real_data=%s",folder))$fatal(1,"SUITE_LOADER missing data");
   repeat(4)@(negedge clk);reset_n=1;
   for(seq_no=1;seq_no<=NUM_TASKS;seq_no=seq_no+1)begin
     if(seq_no>1)begin
       wait(request_seq==seq_no);
       // monitor只在上一CPU写响应退休后发布request；下一共享请求尚未接受。
       @(negedge clk);reset_n=1;mode=1;
     end
     case_id=FIRST_CASE+seq_no-1;writes=0;
     $sformat(path,"%0s/case%0d/x.hex",folder,case_id);$readmemh(path,x);
     $sformat(path,"%0s/case%0d/w.hex",folder,case_id);$readmemh(path,w);
     $sformat(path,"%0s/case%0d/b.hex",folder,case_id);$readmemh(path,b);
     $sformat(path,"%0s/case%0d/gold.hex",folder,case_id);$readmemh(path,gold);
     for(i=0;i<6336;i=i+1)write_word(32'ha0000000+4*i,x[i]);
     for(i=0;i<16384;i=i+1)write_word(32'ha0008000+4*i,w[i]);
     for(i=0;i<256;i=i+1)write_word(32'ha0018000+4*i,b[i]);
     for(i=0;i<25344;i=i+1)write_word(32'ha0040000+4*i,gold[i]);
     write_word(32'ha001f000,case_id-1);
     write_word(32'ha001f004,NUM_TASKS);
     write_word(32'ha001f008,seq_no); // 最后发布完整数据就绪
     if(writes!=48323)$fatal(1,"SUITE_LOADER count");
     if(seq_no==1)begin
       repeat(2)@(negedge clk);reset_n=0;
       repeat(2)@(negedge clk);mode=0;
       // done发布前始终用自由运行TB时钟，避免CPU reset中bus clock被门控造成互等。
       repeat(2)@(negedge clk);done=1;first=0;
     end else begin
       // 运行期同一bus clock且不复位；最后的响应已完全排空。
       @(negedge clk);mode=0;
     end
     $display("SUITE_LOADER_DONE sequence=%0d case=%0d words=%0d runtime_reset=0",seq_no,case_id,writes);
   end
 end
endmodule

module kwt_suite_monitor #(parameter NUM_TASKS=12,FIRST_CASE=1)(
 input wire clk,rst_n,cmd_valid,cmd_ready,cmd_read,
 input wire [31:0] cmd_addr,cmd_data,input wire [3:0] cmd_mask,
 input wire rsp_valid,rsp_ready,rsp_err,input wire [31:0] rsp_data,
 output reg [3:0] reload_seq=0);
 reg pending=0,read_op,layer_seen=0;
 reg [31:0] address,data;reg [3:0] mask;
 reg [4095:0] trace_path;
 reg [25343:0] written=0,readback=0;
 integer trace,index,writes=0,reads=0,completed=0,current_layer=0;
 initial begin
   if(!$value$plusargs("real_trace=%s",trace_path))$fatal(1,"SUITE_TRACE missing path");
   trace=$fopen(trace_path,"w");if(!trace)$fatal(1,"SUITE_TRACE open");
 end
 always @(posedge clk)begin
   if(!rst_n)begin pending=0;written=0;readback=0;writes=0;reads=0;completed=0;reload_seq<=0;layer_seen=0;end
   else begin
     if(rsp_valid && rsp_ready)begin
       if(!pending || rsp_err!==1'b0)$fatal(1,"SUITE_TRACE unexpected/error response");
       if(read_op && address==32'ha001f000)begin
         if(completed>=NUM_TASKS || rsp_data!==(FIRST_CASE+completed-1))$fatal(1,"SUITE_TRACE layer mismatch");
         current_layer=rsp_data;layer_seen=1;
       end
       if(address>=32'ha0020000 && address<32'ha0038c00)begin
         if(!layer_seen)$fatal(1,"SUITE_TRACE no layer metadata");
         index=(address-32'ha0020000)/4;
         if(read_op)begin
           if(readback[index] || !written[index] || (^rsp_data)===1'bx)$fatal(1,"SUITE_TRACE duplicate/unwritten/unknown read");
           readback[index]=1;reads=reads+1;
           $fdisplay(trace,"Y %0d %0d %08h",FIRST_CASE+completed,index,rsp_data);$fflush(trace);
         end else if(data!=32'hdeadbeef)begin
           if(written[index] || mask!==4'hf)$fatal(1,"SUITE_TRACE duplicate/partial store");
           written[index]=1;writes=writes+1;
         end
       end
       if(read_op && address==32'ha0038c00)begin
         if(!layer_seen || writes!=25344 || reads!=25344 || rsp_data!==32'h2468ace0)$fatal(1,"SUITE_TRACE incomplete task/guard");
         $display("SUITE_TASK_DONE sequence=%0d case=%0d layer=%0d writes=%0d reads=%0d",completed+1,FIRST_CASE+completed,current_layer,writes,reads);
         completed=completed+1;writes=0;reads=0;written=0;readback=0;layer_seen=0;
       end
       if(!read_op && address==32'ha001f100)begin
         if(completed==0 || completed>=NUM_TASKS || data!==(completed+1) || reload_seq>=data || mask!==4'hf)
           $fatal(1,"SUITE_TRACE invalid reload sequence");
         reload_seq<=data[3:0];
       end
       pending=0;
     end
     if(cmd_valid && cmd_ready)begin
       if(pending)$fatal(1,"SUITE_TRACE outstanding overlap");
       pending=1;read_op=cmd_read;address=cmd_addr;data=cmd_data;mask=cmd_mask;
     end
   end
 end
endmodule
