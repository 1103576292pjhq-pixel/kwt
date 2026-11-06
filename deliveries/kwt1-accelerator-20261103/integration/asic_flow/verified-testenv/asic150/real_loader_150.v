`timescale 1ns/1fs
// 仿真专用文件加载主机：CPU保持复位时经ICB写宏，不访问宏内部数组。
module kwt_real_loader(
 input wire clk,output reg done=0,output reg mode=1,output reg reset_n=0,
 output reg cmd_valid=0,input wire cmd_ready,output reg [31:0] cmd_addr=0,
 output reg cmd_read=0,output reg [31:0] cmd_wdata=0,output wire [3:0] cmd_wmask,
 input wire rsp_valid,output reg rsp_ready=0,input wire rsp_err,input wire [31:0] rsp_rdata);
 assign cmd_wmask=4'hf;
 reg [31:0] x[0:6335],w[0:16383],b[0:255],gold[0:25343];
 reg [4095:0] folder;
 integer i,writes=0,guard,layer=0,clear_words=0;
 reg measure_enable=0;
 realtime clear_begin;
 task write_word(input [31:0] address,input [31:0] value);
 begin
   if((^value)===1'bx)$fatal(1,"REAL_LOADER unknown input address=%h",address);
   @(negedge clk);cmd_read=0;cmd_valid=1;cmd_addr=address;cmd_wdata=value;
   @(posedge clk);guard=0;
   while(cmd_ready!==1'b1)begin @(posedge clk);guard=guard+1;if(guard>100)$fatal(1,"REAL_LOADER command timeout");end
   @(negedge clk);cmd_valid=0;guard=0;
   while(rsp_valid!==1'b1)begin @(negedge clk);guard=guard+1;if(guard>100)$fatal(1,"REAL_LOADER response timeout");end
   if(rsp_err!==1'b0)$fatal(1,"REAL_LOADER bus error");
   rsp_ready=1;@(posedge clk);@(negedge clk);rsp_ready=0;writes=writes+1;
 end
 endtask

 task check_zero(input [31:0] address);
 begin
   @(negedge clk);cmd_read=1;cmd_valid=1;cmd_addr=address;
   @(posedge clk);guard=0;
   while(cmd_ready!==1'b1)begin @(posedge clk);guard=guard+1;if(guard>100)$fatal(1,"CLEAR read command timeout");end
   @(negedge clk);cmd_valid=0;guard=0;
   while(rsp_valid!==1'b1)begin @(negedge clk);guard=guard+1;if(guard>100)$fatal(1,"CLEAR read response timeout");end
   if(rsp_err!==0 || rsp_rdata!==0)$fatal(1,"CLEAR readback failed addr=%h data=%h",address,rsp_rdata);
   rsp_ready=1;@(posedge clk);@(negedge clk);rsp_ready=0;cmd_read=0;
 end endtask
 task scrub(input [31:0] base,input integer count);
 begin
   for(i=0;i<count;i=i+1)write_word(base+4*i,0);
   for(i=0;i<count;i=i+1)check_zero(base+4*i);
   clear_words=clear_words+count;
 end endtask
 initial begin
   if(!$value$plusargs("real_data=%s",folder))$fatal(1,"REAL_LOADER missing prepared data path");
   $readmemh({folder,"/x.hex"},x);$readmemh({folder,"/w.hex"},w);
   $readmemh({folder,"/b.hex"},b);$readmemh({folder,"/gold.hex"},gold);
   repeat(4)@(negedge clk);reset_n=1;
   i=$value$plusargs("layer=%d",layer);
   if(layer<0 || layer>11)$fatal(1,"Invalid layer");
   clear_begin=$realtime;
   scrub(32'ha0000000,6336);scrub(32'ha0008000,16384);
   scrub(32'ha0018000,256);scrub(32'ha0020000,25344);
   $display("CLEAR_SHARED_PASS words=%0d zero_readbacks=%0d elapsed_ns=%.3f",clear_words,clear_words,$realtime-clear_begin);
   write_word(32'ha001f000,layer);writes=0;

   for(i=0;i<25344;i=i+1)write_word(32'ha0040000+4*i,gold[i]);
   @(negedge clk);measure_enable=1;
   for(i=0;i<6336;i=i+1)write_word(32'ha0000000+4*i,x[i]);
   for(i=0;i<16384;i=i+1)write_word(32'ha0008000+4*i,w[i]);
   for(i=0;i<256;i=i+1)write_word(32'ha0018000+4*i,b[i]);
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

`timescale 1ns/1fs
// Passive simulation observer only. Never drives a production signal.
module kwt_timing_probe #(
 parameter NX=6336,NW=16384,NB=256,NY=25344
)(
 input wire clk,cpu_clk,host_mode,
 input wire host_valid,host_ready,host_read,
 input wire [31:0] host_addr,host_data,input wire [3:0] host_mask,
 input wire host_rsp_valid,host_rsp_ready,host_rsp_err,
 input wire cpu_valid,cpu_ready,cpu_read,
 input wire [31:0] cpu_addr,cpu_data,input wire [3:0] cpu_mask,
 input wire cpu_rsp_valid,cpu_rsp_ready,cpu_rsp_err
);
 reg started=0,loaded=0,finished=0,hpending=0,cpending=0;
 reg hr,cr;reg [31:0] ha,ca,cd;reg [3:0] hm,cm;
 reg [NX-1:0] xs=0;reg [NW-1:0] ws=0;reg [NB-1:0] bs=0;reg [NY-1:0] ys=0;
 integer xc=0,wc=0,bc=0,yc=0,idx,kind,hindex,hkind;
 realtime start_ps=0,load_ps=0,first_accept_ps=0,last_host_ps=0,last_cpu_ps=0;
 realtime host_period_ps=0,cpu_period_ps=0,now_ps,elapsed_ps,cycles,load_cycles;
 function integer region(input [31:0] a);
 begin
   region=0;
   if(a>=32'ha0000000&&a<32'ha0000000+4*NX)region=1;
   if(a>=32'ha0008000&&a<32'ha0008000+4*NW)region=2;
   if(a>=32'ha0018000&&a<32'ha0018000+4*NB)region=3;
 end endfunction
 always @(posedge clk)begin
   now_ps=$realtime*1000.0;
   if(last_host_ps>0)begin
 if(now_ps-last_host_ps<6666.656 || now_ps-last_host_ps>6666.676)$fatal(1,"Wrong 150MHz host clock");
     if(host_period_ps>0 && ((now_ps-last_host_ps-host_period_ps>0.01)||(host_period_ps-now_ps+last_host_ps>0.01)))$fatal(1,"TIMING changing host clock");
     host_period_ps=6666.666;
   end
   last_host_ps=now_ps;
   if(host_mode && tb_top.u_real_loader.measure_enable)begin
     if(host_valid && !host_read && region(host_addr)!=0 && !started)begin
       if(host_addr!==32'ha0000000)$fatal(1,"TIMING first input must be X0");
       started=1;start_ps=now_ps;
     end
     if(host_rsp_valid && host_rsp_ready)begin
       if(!hpending || host_rsp_err!==0)$fatal(1,"TIMING host response without command/error");
       if(hkind!=0)begin
         if(hr!==0 || hm!==4'hf || ha[1:0]!==0)$fatal(1,"TIMING bad input store");
         case(hkind)
           1:begin if(xs[hindex])$fatal(1,"TIMING duplicate X");xs[hindex]=1;xc=xc+1;end
           2:begin if(ws[hindex])$fatal(1,"TIMING duplicate W");ws[hindex]=1;wc=wc+1;end
           3:begin if(bs[hindex])$fatal(1,"TIMING duplicate bias");bs[hindex]=1;bc=bc+1;end
         endcase
         if(xc==NX && wc==NW && bc==NB)begin loaded=1;load_ps=now_ps;end
       end
       hpending=0;
     end
     if(host_valid && host_ready)begin
       if(hpending)$fatal(1,"TIMING host multiple outstanding");
       hpending=1;ha=host_addr;hr=host_read;hm=host_mask;hkind=region(host_addr);
       case(hkind)
         1:hindex=(host_addr-32'ha0000000)/4;
         2:hindex=(host_addr-32'ha0008000)/4;
         3:hindex=(host_addr-32'ha0018000)/4;
         default:hindex=0;
       endcase
       if(hkind!=0 && first_accept_ps==0)first_accept_ps=now_ps;
     end
   end
 end
 always @(negedge host_mode)begin
   if(!started || !loaded || hpending)$fatal(1,"TIMING incomplete input loading");
 end
 always @(posedge cpu_clk)begin
   if(last_cpu_ps>0)begin
 if($realtime*1000.0-last_cpu_ps<6666.656 || $realtime*1000.0-last_cpu_ps>6666.676)$fatal(1,"Wrong 150MHz CPU clock");
     if(cpu_period_ps>0 && (($realtime*1000.0-last_cpu_ps-cpu_period_ps>0.01)||(cpu_period_ps-$realtime*1000.0+last_cpu_ps>0.01)))$fatal(1,"TIMING changing CPU clock");
     cpu_period_ps=6666.666;
   end
   last_cpu_ps=$realtime*1000.0;
   if(!host_mode)begin
     if(cpu_rsp_valid && cpu_rsp_ready)begin
       if(!cpending || cpu_rsp_err!==0)$fatal(1,"TIMING CPU response without command/error pending=%b err=%b cmd_valid=%b cmd_ready=%b addr=%h previous_addr=%h previous_read=%b rsp_valid=%b rsp_ready=%b",cpending,cpu_rsp_err,cpu_valid,cpu_ready,cpu_addr,ca,cr,cpu_rsp_valid,cpu_rsp_ready);
       if(!cr && ca>=32'ha0020000 && ca<32'ha0020000+4*NY && cd!==32'hdeadbeef)begin
         idx=(ca-32'ha0020000)/4;
         if(ys[idx] || cm!==4'hf || ca[1:0]!==0 || (^cd)===1'bx || cd[31:19]!==0)
           $fatal(1,"TIMING bad/duplicate result store");
         ys[idx]=1;yc=yc+1;
         if(yc==NY)begin
           if(!loaded || finished || cpu_period_ps<=0 || host_period_ps!=cpu_period_ps)
             $fatal(1,"TIMING incomplete load, repeated finish or unequal clock periods");
           elapsed_ps=$realtime*1000.0-start_ps;
           cycles=elapsed_ps/cpu_period_ps;load_cycles=(load_ps-start_ps)/cpu_period_ps;
           finished=1;
           $display("TIMING_WINDOW start_cycle=%.9f first_accept_cycle=%.9f end_cycle=%.9f cycles=%.9f load_cycles=%.9f cpu_path_cycles=%.9f elapsed_ps=%.9f period_ps=%.9f host_period_ps=%.9f load_words=%0d result_words=%0d",
             start_ps/cpu_period_ps,first_accept_ps/cpu_period_ps,$realtime*1000.0/cpu_period_ps,
             cycles,load_cycles,cycles-load_cycles,elapsed_ps,cpu_period_ps,host_period_ps,xc+wc+bc,yc);
         end
       end
       cpending=0;
     end
     if(cpu_valid && cpu_ready)begin
       if(cpending)$fatal(1,"TIMING CPU multiple outstanding");
       cpending=1;ca=cpu_addr;cr=cpu_read;cd=cpu_data;cm=cpu_mask;
     end
   end
 end
endmodule

`timescale 1ns/1fs
// Simulation-only shared-bus landmarks, based on response retirement.
// These spans overlap; they are not an additive breakdown of compute time.
module kwt_profile_probe(
 input wire clk,host_mode,cmd_valid,cmd_ready,cmd_read,
 input wire [31:0] cmd_addr,cmd_data,input wire [3:0] cmd_mask,
 input wire rsp_valid,rsp_ready,rsp_err
);
 reg pending=0,read_op;reg [31:0] address,data;reg [3:0] mask;
 integer poisons=0,inputs=0,outputs=0;
 realtime poison_first=-1,poison_last=-1,input_first=-1,input_last=-1,result_first=-1;
 always @(posedge clk)begin
   if(!host_mode)begin
     if(rsp_valid && rsp_ready)begin
       if(!pending || rsp_err!==0)$fatal(1,"PROFILE unexpected/error response");
       if(!read_op && address>=32'ha0020000 && address<32'ha0038c00)begin
         if(mask!==4'hf)$fatal(1,"PROFILE partial Y write");
         if(data===32'hdeadbeef)begin
           if(poisons==0)poison_first=$realtime*1000.0;
           poisons=poisons+1;poison_last=$realtime*1000.0;
         end else begin
           if(outputs==0)result_first=$realtime*1000.0;
           outputs=outputs+1;
           if(outputs==25344)begin
             if(poisons!=25344 || inputs!=22976)$fatal(1,"PROFILE incomplete input/poison counts");
             $display("DRIVER_PROFILE poison_first_ps=%.9f poison_last_ps=%.9f input_first_ps=%.9f input_last_ps=%.9f result_first_ps=%.9f result_last_ps=%.9f poison_words=%0d input_words=%0d result_words=%0d",
                poison_first,poison_last,input_first,input_last,result_first,$realtime*1000.0,poisons,inputs,outputs);
           end
         end
       end
       if(read_op && ((address>=32'ha0000000 && address<32'ha0006300) ||
                     (address>=32'ha0008000 && address<32'ha0018000) ||
                     (address>=32'ha0018000 && address<32'ha0018400)))begin
         if(inputs==0)input_first=$realtime*1000.0;
         inputs=inputs+1;input_last=$realtime*1000.0;
       end
       pending=0;
     end
     if(cmd_valid && cmd_ready)begin
       if(pending)$fatal(1,"PROFILE multiple outstanding");
       pending=1;read_op=cmd_read;address=cmd_addr;data=cmd_data;mask=cmd_mask;
     end
   end
 end
endmodule
