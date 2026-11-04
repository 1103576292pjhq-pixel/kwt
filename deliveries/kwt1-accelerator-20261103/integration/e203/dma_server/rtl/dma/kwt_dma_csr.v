`default_nettype none
module kwt_dma_csr #(
 parameter [31:0] BASE_ADDR=32'h11000000,
 parameter [31:0] RAM_BASE=32'ha0000000
)(
 input wire clk,rst_n,
 input wire cmd_valid,output wire cmd_ready,input wire [31:0] cmd_addr,cmd_data,
 input wire cmd_read,input wire [3:0] cmd_mask,
 output reg rsp_valid,input wire rsp_ready,output reg [31:0] rsp_data,output reg rsp_err,
 output reg start,abort_request,output reg [31:0] x_base,w_base,b_base,y_base,task_id,
 output reg [3:0] layer_id,
 input wire busy,done,failed,aborted,input wire [7:0] error,
 input wire [31:0] cycles,input wire [15:0] output_words,input wire [8:0] blocks
);
 wire fire=cmd_valid && cmd_ready;
 wire address_ok=(cmd_addr[31:8]==BASE_ADDR[31:8]) && cmd_addr[1:0]==0;
 wire [7:0] offset=cmd_addr[7:0];
 reg bad;reg [31:0] read_value;
 function in_range;
 input [31:0] address;input [31:0] length;
 begin in_range=address[1:0]==0 && {1'b0,address}>={1'b0,RAM_BASE} &&
             ({1'b0,address}+{1'b0,length})<=({1'b0,RAM_BASE}+33'd524288);end
 endfunction
 function disjoint;
 input [31:0] source;input [31:0] length;input [31:0] destination;
 begin disjoint=({1'b0,destination}+33'd101376)<={1'b0,source} ||
                ({1'b0,source}+{1'b0,length})<={1'b0,destination};end
 endfunction
 wire descriptor_ok=in_range(x_base,25344) && in_range(w_base,65536) &&
     in_range(b_base,1024) && in_range(y_base,101376) &&
     disjoint(x_base,25344,y_base) && disjoint(w_base,65536,y_base) && disjoint(b_base,1024,y_base);
 assign cmd_ready=rst_n && !rsp_valid;
 always @(*)begin
   bad=!address_ok;read_value=0;
   if(cmd_read)begin
     case(offset)
       8'h00:read_value=32'h4b444d31;
       8'h04:read_value={28'b0,aborted,failed,done,busy};
       8'h10:read_value=x_base;
       8'h14:read_value=w_base;
       8'h18:read_value=b_base;
       8'h1c:read_value=y_base;
       8'h20:read_value=task_id;
       8'h24:read_value={28'b0,layer_id};
       8'h28:read_value={16'b0,output_words};
       8'h2c:read_value=cycles;
       8'h30:read_value={24'b0,error};
       8'h34:read_value={23'b0,blocks};
       default:bad=1;
     endcase
   end else begin
     bad=bad || cmd_mask!=4'hf;
     case(offset)
       8'h08:bad=bad || (cmd_data==1 ? (busy || start || !descriptor_ok) :
                                       (cmd_data==2 ? !busy : 1'b1));
       8'h10,8'h14,8'h18,8'h1c,8'h20:bad=bad || busy || start;
       8'h24:bad=bad || busy || start || cmd_data>11;
       default:bad=1;
     endcase
   end
 end
 always @(posedge clk)begin
   if(!rst_n)begin
     rsp_valid<=0;rsp_data<=0;rsp_err<=0;start<=0;abort_request<=0;
     x_base<=0;w_base<=0;b_base<=0;y_base<=0;task_id<=0;layer_id<=0;
   end else begin
     start<=0;abort_request<=0;
     if(rsp_valid && rsp_ready)rsp_valid<=0;
     if(fire)begin
       rsp_valid<=1;rsp_err<=bad;rsp_data<=cmd_read ? read_value : 0;
       if(!cmd_read && !bad)begin
         case(offset)
           8'h08:begin start<=cmd_data==1;abort_request<=cmd_data==2;end
           8'h10:x_base<=cmd_data;
           8'h14:w_base<=cmd_data;
           8'h18:b_base<=cmd_data;
           8'h1c:y_base<=cmd_data;
           8'h20:task_id<=cmd_data;
           8'h24:layer_id<=cmd_data[3:0];
           default:begin end
         endcase
       end
     end
   end
 end
endmodule
`default_nettype wire
