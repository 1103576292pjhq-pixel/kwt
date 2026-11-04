`timescale 1ns/1ps
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
             $display("DRIVER_PROFILE poison_first_ps=%.0f poison_last_ps=%.0f input_first_ps=%.0f input_last_ps=%.0f result_first_ps=%.0f result_last_ps=%.0f poison_words=%0d input_words=%0d result_words=%0d",
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
