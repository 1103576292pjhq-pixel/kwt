`timescale 1ns/1ps
// 仿真专用文件加载主机：CPU保持复位时经ICB写宏，不访问宏内部数组。
module kwt_real_loader(
 input wire clk,output reg done=0,output reg mode=1,output reg reset_n=0,
 output reg cmd_valid=0,input wire cmd_ready,output reg [31:0] cmd_addr=0,
 output wire cmd_read,output reg [31:0] cmd_wdata=0,output wire [3:0] cmd_wmask,
 input wire rsp_valid,output reg rsp_ready=0,input wire rsp_err,input wire [31:0] rsp_rdata);
 assign cmd_read=0;assign cmd_wmask=4'hf;
 reg [31:0] x[0:6335],w[0:16383],b[0:255],gold[0:25343];
 reg [4095:0] folder;
 integer i,writes=0,guard;
 task write_word(input [31:0] address,input [31:0] value);
 begin
   if((^value)===1'bx)$fatal(1,"REAL_LOADER unknown input address=%h",address);
   @(negedge clk);cmd_valid=1;cmd_addr=address;cmd_wdata=value;
   @(posedge clk);guard=0;
   while(cmd_ready!==1'b1)begin @(posedge clk);guard=guard+1;if(guard>100)$fatal(1,"REAL_LOADER command timeout");end
   @(negedge clk);cmd_valid=0;guard=0;
   while(rsp_valid!==1'b1)begin @(negedge clk);guard=guard+1;if(guard>100)$fatal(1,"REAL_LOADER response timeout");end
   if(rsp_err!==1'b0)$fatal(1,"REAL_LOADER bus error");
   rsp_ready=1;@(posedge clk);@(negedge clk);rsp_ready=0;writes=writes+1;
 end
 endtask
 initial begin
   if(!$value$plusargs("real_data=%s",folder))$fatal(1,"REAL_LOADER missing prepared data path");
   $readmemh({folder,"/x.hex"},x);$readmemh({folder,"/w.hex"},w);
   $readmemh({folder,"/b.hex"},b);$readmemh({folder,"/gold.hex"},gold);
   repeat(4)@(negedge clk);reset_n=1;
   for(i=0;i<6336;i=i+1)write_word(32'ha0000000+4*i,x[i]);
   for(i=0;i<16384;i=i+1)write_word(32'ha0008000+4*i,w[i]);
   for(i=0;i<256;i=i+1)write_word(32'ha0018000+4*i,b[i]);
   for(i=0;i<25344;i=i+1)write_word(32'ha0040000+4*i,gold[i]);
   if(writes!=48320)$fatal(1,"REAL_LOADER count");
   repeat(2)@(negedge clk);reset_n=0;
   repeat(2)@(negedge clk);mode=0;
   repeat(2)@(negedge clk);done=1;
   $display("REAL_LOADER_DONE writes=%0d cpu_held_in_reset=1",writes);
 end
endmodule

// 从CPU实际共享读响应记录Y。只在响应握手退休时计数，不读取内部宏数组。
module kwt_real_monitor(
 input wire clk,rst_n,cmd_valid,cmd_ready,cmd_read,
 input wire [31:0] cmd_addr,cmd_data,input wire [3:0] cmd_mask,
 input wire rsp_valid,rsp_ready,rsp_err,input wire [31:0] rsp_data);
 reg pending=0,read_op;
 reg [31:0] address,data;reg [3:0] mask;
 reg [4095:0] trace_path;
 reg [25343:0] written=0,readback=0;
 integer trace,index,writes=0,reads=0;
 initial begin
   if(!$value$plusargs("real_trace=%s",trace_path))$fatal(1,"REAL_TRACE missing path");
   trace=$fopen(trace_path,"w");if(!trace)$fatal(1,"REAL_TRACE open failed");
 end
 always @(posedge clk)begin
   if(!rst_n)begin pending=0;written=0;readback=0;writes=0;reads=0;end
   else begin
     if(rsp_valid && rsp_ready)begin
       if(!pending || rsp_err!==1'b0)$fatal(1,"REAL_TRACE unexpected/error response");
       if(address>=32'ha0020000 && address<32'ha0038c00)begin
         index=(address-32'ha0020000)/4;
         if(read_op)begin
           if(readback[index] || !written[index] || (^rsp_data)===1'bx)$fatal(1,"REAL_TRACE duplicate/unwritten/unknown read index=%0d",index);
           readback[index]=1;reads=reads+1;
           $fdisplay(trace,"Y %0d %08h",index,rsp_data);$fflush(trace);
         end else if(data!=32'hdeadbeef)begin
           if(written[index] || mask!==4'hf)$fatal(1,"REAL_TRACE duplicate/partial result store");
           written[index]=1;writes=writes+1;
         end
       end
       if(read_op && address==32'ha0038c00)begin
         if(writes!=25344 || reads!=25344)$fatal(1,"REAL_TRACE incomplete task");
         $display("REAL_SHARED_READBACK_DONE writes=%0d reads=%0d",writes,reads);$fflush(trace);
       end
       pending=0;
     end
     if(cmd_valid && cmd_ready)begin
       if(pending)$fatal(1,"REAL_TRACE multiple outstanding");
       pending=1;read_op=cmd_read;address=cmd_addr;data=cmd_data;mask=cmd_mask;
     end
   end
 end
endmodule
