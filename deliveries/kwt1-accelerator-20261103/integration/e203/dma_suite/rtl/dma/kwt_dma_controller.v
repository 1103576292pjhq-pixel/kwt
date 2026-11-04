`include "kwt_icb_config.vh"
`default_nettype none
// Independent input loader and result writer. FORWARD_* removes staging cycles.
module kwt_dma_controller #(
 parameter FORWARD_INPUT=1,parameter FORWARD_RESULT=1
)(
 input wire clk,rst_n,start,abort_request,
 input wire [31:0] x_base,w_base,b_base,y_base,task_id,
 input wire [3:0] layer_id,
 output reg busy,done,failed,aborted,output reg [7:0] error,
 output reg [31:0] cycles,output reg [15:0] output_words,output reg [8:0] blocks,
 output wire load_cmd_valid,input wire load_cmd_ready,output wire [2:0] load_cmd_op,
 output wire [3:0] load_cmd_layer_id,load_cmd_tile_id,
 output wire [31:0] load_cmd_task_id,load_cmd_data,output wire [12:0] load_cmd_index,
 output wire result_cmd_valid,input wire result_cmd_ready,output wire result_cmd_ack,
 output wire [31:0] result_cmd_task_id,output wire [8:0] result_cmd_sequence,output wire [6:0] result_cmd_count,
 input wire result_rsp_valid,output wire result_rsp_ready,input wire [31:0] result_rsp_data,input wire result_rsp_error,
 input wire result_block_valid,input wire [31:0] result_block_task_id,
 input wire [6:0] result_block_row,result_block_count,input wire [3:0] result_block_tile,
 input wire [8:0] result_block_sequence,
 input wire engine_done,engine_fault,engine_abort_done,input wire [7:0] engine_error,
 output wire engine_abort,output wire transport_empty,
 output wire rd_valid,input wire rd_ready,output wire [31:0] rd_addr,
 input wire rd_rsp_valid,output wire rd_rsp_ready,input wire [31:0] rd_rsp_data,input wire rd_rsp_err,
 output wire wr_valid,input wire wr_ready,output wire [31:0] wr_addr,wr_data,
 input wire wr_rsp_valid,output wire wr_rsp_ready,input wire wr_rsp_err
);
 localparam L_IDLE=0,L_CONTROL=1,L_READ=2,L_RESPONSE=3,L_DATA=4,L_DONE=5;
 localparam R_IDLE=0,R_REQUEST=1,R_RESPONSE=2,R_WRITE=3,R_WRITE_RESPONSE=4,R_ACK=5,R_ACK_RESPONSE=6;
 reg [2:0] lstate,rstate,operation;
 reg [12:0] index;
 reg [3:0] tile;
 reg [31:0] input_data,output_data;
 reg [31:0] xb,wb,bb,yb,tag;
 reg [3:0] layer;
 reg [6:0] position,count,row;
 reg [3:0] result_tile;
 reg [8:0] block_sequence_tag;
 reg [4:0] row_group;
 reg [3:0] expected_tile;
 reg stopping,abort_seen,abort_sent;
 wire stop_now=stopping || abort_request || engine_fault;
 assign engine_abort=busy && stop_now && !abort_sent;
 assign load_cmd_valid=busy && !stop_now &&
     (lstate==L_CONTROL || lstate==L_DATA ||
      (FORWARD_INPUT && lstate==L_RESPONSE && rd_rsp_valid && !rd_rsp_err));
 assign load_cmd_op=operation;
 assign load_cmd_layer_id=layer;
 assign load_cmd_task_id=tag;
 assign load_cmd_tile_id=tile;
 assign load_cmd_index=index;
 assign load_cmd_data=(FORWARD_INPUT && lstate==L_RESPONSE) ? rd_rsp_data : input_data;
 assign rd_valid=busy && lstate==L_READ;
 assign rd_addr=operation==`KWT_CMD_X ? xb+{17'd0,index,2'b0} :
                operation==`KWT_CMD_W ? wb+({26'd0,index[9:4]}<<10)+({28'd0,tile}<<6)+({28'd0,index[3:0]}<<2) :
                bb+({28'd0,tile}<<6)+({19'd0,index}<<2);
 // Always release the shared bus response. If OPEN is waiting for a free W
 // slot, retain this word locally so result writes can acquire the shared bus.
 assign rd_rsp_ready=busy && lstate==L_RESPONSE;
 assign result_cmd_valid=busy && !stop_now && (rstate==R_REQUEST || rstate==R_ACK);
 assign result_cmd_ack=rstate==R_ACK;
 assign result_cmd_task_id=tag;
 assign result_cmd_sequence=block_sequence_tag;
 assign result_cmd_count=count;
 assign result_rsp_ready=busy && (rstate==R_ACK_RESPONSE ||
     (rstate==R_RESPONSE && (!FORWARD_RESULT || result_rsp_error || wr_ready)));
 assign wr_valid=busy && (rstate==R_WRITE ||
     (FORWARD_RESULT && rstate==R_RESPONSE && result_rsp_valid && !result_rsp_error));
 assign wr_addr=yb+(({25'd0,row}+{29'd0,position[6:4]})<<10)+
                      ({28'd0,result_tile}<<6)+({28'd0,position[3:0]}<<2);
 assign wr_data=(FORWARD_RESULT && rstate==R_RESPONSE) ? result_rsp_data : output_data;
 assign wr_rsp_ready=busy && rstate==R_WRITE_RESPONSE;
 // Core BEGIN may coexist with queued new-task input commands. Its transport
 // guard concerns result ownership; DMA completion separately waits for L_DONE.
 assign transport_empty=rstate==R_IDLE;

 // Advance only when an actual load command is accepted. W uses row-major shared layout.
 task advance_input;
 begin
   if(operation==`KWT_CMD_X && index==6335)begin operation<=`KWT_CMD_OPEN;index<=0;lstate<=L_CONTROL;end
   else if(operation==`KWT_CMD_W && index==1023)begin operation<=`KWT_CMD_BIAS;index<=0;lstate<=L_READ;end
   else if(operation==`KWT_CMD_BIAS && index==15)begin operation<=`KWT_CMD_COMMIT;index<=0;lstate<=L_CONTROL;end
   else begin index<=index+1'b1;lstate<=L_READ;end
 end
 endtask

 always @(posedge clk)begin
   if(!rst_n)begin
     busy<=0;done<=0;failed<=0;aborted<=0;error<=0;cycles<=0;output_words<=0;blocks<=0;
     lstate<=L_IDLE;rstate<=R_IDLE;operation<=0;index<=0;tile<=0;stopping<=0;abort_seen<=0;abort_sent<=0;
     xb<=0;wb<=0;bb<=0;yb<=0;tag<=0;layer<=0;input_data<=0;output_data<=0;
     position<=0;count<=0;row<=0;result_tile<=0;block_sequence_tag<=0;row_group<=0;expected_tile<=0;
   end else if(start && !busy)begin
     busy<=1;done<=0;failed<=0;aborted<=0;error<=0;cycles<=0;output_words<=0;blocks<=0;
     xb<=x_base;wb<=w_base;bb<=b_base;yb<=y_base;tag<=task_id;layer<=layer_id;
     lstate<=L_CONTROL;operation<=`KWT_CMD_BEGIN;index<=0;tile<=0;rstate<=R_IDLE;
     stopping<=0;abort_seen<=0;abort_sent<=0;row_group<=0;expected_tile<=0;position<=0;
   end else if(busy)begin
     cycles<=cycles+1'b1;
     if(abort_request)begin stopping<=1;aborted<=1;end
     if(engine_fault)begin stopping<=1;failed<=1;error<=engine_error;end
     if(engine_abort_done)abort_seen<=1;
     if(engine_abort)abort_sent<=1;
     if(stop_now)begin
       // Accepted ICB requests and responses drain before the descriptor becomes reusable.
       if(lstate!=L_READ && lstate!=L_RESPONSE)lstate<=L_IDLE;
       if(rstate!=R_RESPONSE && rstate!=R_WRITE && rstate!=R_WRITE_RESPONSE && rstate!=R_ACK_RESPONSE)rstate<=R_IDLE;
       if(lstate==L_IDLE && rstate==R_IDLE && (abort_seen || engine_abort_done))busy<=0;
     end else if(lstate==L_DONE && rstate==R_IDLE && blocks==400 && engine_done)begin busy<=0;done<=1;end
     case(lstate)
       L_CONTROL:if(load_cmd_valid && load_cmd_ready)begin
         case(operation)
           `KWT_CMD_BEGIN:begin operation<=`KWT_CMD_X;index<=0;lstate<=L_READ;end
           `KWT_CMD_OPEN:begin operation<=`KWT_CMD_W;index<=0;lstate<=L_READ;end
           `KWT_CMD_COMMIT:begin
             if(tile==0)begin operation<=`KWT_CMD_START;lstate<=L_CONTROL;end
             else if(tile==15)lstate<=L_DONE;
             else begin tile<=tile+1'b1;operation<=`KWT_CMD_OPEN;lstate<=L_CONTROL;end
           end
           `KWT_CMD_START:begin tile<=1;operation<=`KWT_CMD_OPEN;lstate<=L_CONTROL;end
           default:begin stopping<=1;failed<=1;error<=8'he1;end
         endcase
       end
       L_READ:if(rd_valid && rd_ready)lstate<=L_RESPONSE;
       L_RESPONSE:if(rd_rsp_valid && rd_rsp_ready)begin
         if(rd_rsp_err)begin stopping<=1;failed<=1;error<=8'he2;lstate<=L_IDLE;end
         else if(stop_now)lstate<=L_IDLE;
         else if(FORWARD_INPUT && load_cmd_ready)advance_input;
         else begin input_data<=rd_rsp_data;lstate<=L_DATA;end
       end
       L_DATA:if(load_cmd_valid && load_cmd_ready)advance_input;
       default:begin end
     endcase
     case(rstate)
       R_IDLE:if(!stop_now && result_block_valid && blocks<400)begin
         if(result_block_task_id!=tag || result_block_sequence!=blocks+1'b1 ||
            result_block_row!={row_group,2'b0} || result_block_tile!=expected_tile ||
            result_block_count!=(row_group==24 ? 48 : 64))begin stopping<=1;failed<=1;error<=8'he3;end
         else begin
           row<=result_block_row;result_tile<=result_block_tile;count<=result_block_count;
           block_sequence_tag<=result_block_sequence;position<=0;rstate<=R_REQUEST;
         end
       end
       R_REQUEST:if(result_cmd_valid && result_cmd_ready)rstate<=R_RESPONSE;
       R_RESPONSE:if(result_rsp_valid && result_rsp_ready)begin
         if(result_rsp_error)begin stopping<=1;failed<=1;error<=8'he4;rstate<=R_IDLE;end
         else if(FORWARD_RESULT)rstate<=R_WRITE_RESPONSE;
         else if(stop_now)rstate<=R_IDLE;
         else begin output_data<=result_rsp_data;rstate<=R_WRITE;end
       end
       R_WRITE:if(wr_valid && wr_ready)rstate<=R_WRITE_RESPONSE;
       R_WRITE_RESPONSE:if(wr_rsp_valid && wr_rsp_ready)begin
         if(wr_rsp_err)begin stopping<=1;failed<=1;error<=8'he5;rstate<=R_IDLE;end
         else begin
           output_words<=output_words+1'b1;
           if(stop_now)rstate<=R_IDLE;
           else if(position+1'b1==count)rstate<=R_ACK;
           else begin position<=position+1'b1;rstate<=R_REQUEST;end
         end
       end
       R_ACK:if(result_cmd_valid && result_cmd_ready)rstate<=R_ACK_RESPONSE;
       R_ACK_RESPONSE:if(result_rsp_valid && result_rsp_ready)begin
         rstate<=R_IDLE;
         if(result_rsp_error)begin stopping<=1;failed<=1;error<=8'he6;end
         else if(!stop_now)begin
           blocks<=blocks+1'b1;
           if(row_group==24)begin row_group<=0;expected_tile<=expected_tile+1'b1;end
           else row_group<=row_group+1'b1;
         end
       end
       default:begin end
     endcase
   end
 end
endmodule
`default_nettype wire
