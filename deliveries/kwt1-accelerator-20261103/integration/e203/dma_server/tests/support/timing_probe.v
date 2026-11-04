`timescale 1ns/1ps
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
     if(host_period_ps>0 && now_ps-last_host_ps!=host_period_ps)$fatal(1,"TIMING changing host clock");
     host_period_ps=now_ps-last_host_ps;
   end
   last_host_ps=now_ps;
   if(host_mode)begin
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
     if(cpu_period_ps>0 && $realtime*1000.0-last_cpu_ps!=cpu_period_ps)$fatal(1,"TIMING changing CPU clock");
     cpu_period_ps=$realtime*1000.0-last_cpu_ps;
   end
   last_cpu_ps=$realtime*1000.0;
   if(!host_mode)begin
     if(cpu_rsp_valid && cpu_rsp_ready)begin
       if(!cpending || cpu_rsp_err!==0)$fatal(1,"TIMING CPU response without command/error");
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
           $display("TIMING_WINDOW start_cycle=%.6f first_accept_cycle=%.6f end_cycle=%.6f cycles=%.6f load_cycles=%.6f cpu_path_cycles=%.6f elapsed_ps=%.0f period_ps=%.0f host_period_ps=%.0f load_words=%0d result_words=%0d",
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
