// One-outstanding 32-bit ICB wrapper. Core commands are pulsed exactly once;
// their delayed error/row data are checked before any bus response is issued.
module ffn1_icb #(parameter integer M=99,N=256,
 parameter [31:0] BASE_ADDR=32'h11000000)(
 input wire clk,rst_n,
 input wire icb_cmd_valid,output wire icb_cmd_ready,
 input wire [31:0] icb_cmd_addr,input wire icb_cmd_read,
 input wire [31:0] icb_cmd_wdata,input wire [3:0] icb_cmd_wmask,
 output reg icb_rsp_valid,input wire icb_rsp_ready,
 output reg [31:0] icb_rsp_rdata,output reg icb_rsp_err
);
 localparam [2:0] IDLE=0,EXEC=1,CORE_WAIT=2,CORE_CHECK=3,RESPONSE=4;
 localparam [2:0] OP_COMMAND=0,OP_COMMIT=1,OP_READ=2,OP_ACK=3;
 reg [2:0] state,pending_op;
 reg [31:0] addr,wdata;
 reg rd;reg [3:0] wmask;
 reg [4:0] errors;
 reg [5:0] shift_reg;
 reg [1:0] kind_reg;
 reg [31:0] load_addr_reg,lo_reg,row_addr_reg;
 reg [15:0] hi_reg;
 reg fresh_lo,fresh_hi;
 reg [2:0] row_flags;
 reg load_begin,load_valid,start,row_ack,row_rd_en;
 reg signed [47:0] load_data;
 reg [31:0] ack_index;
 wire load_ready,loaded,busy,done,command_error,row_ready,row_rd_valid;
 wire [31:0] row_index;
 wire signed [31:0] row_rd_data;
 wire row_rd_overflow,row_rd_saturated;
 wire [31:0] offset=addr-BASE_ADDR;
 assign icb_cmd_ready=state==IDLE;
 ffn1_top #(.M(M),.N(N)) core(
   .clk(clk),.rst_n(rst_n),.load_begin(load_begin),.load_valid(load_valid),
   .start(start),.row_ack(row_ack),.row_rd_en(row_rd_en),
   .load_kind(kind_reg),.load_addr(load_addr_reg),.row_ack_index(ack_index),
   .row_rd_addr(row_addr_reg),.load_data(load_data),.shift(shift_reg),
   .load_ready(load_ready),.loaded(loaded),.busy(busy),.done(done),
   .command_error(command_error),.row_ready(row_ready),.row_rd_valid(row_rd_valid),
   .row_index(row_index),.row_rd_data(row_rd_data),
   .row_rd_overflow(row_rd_overflow),.row_rd_saturated(row_rd_saturated));
 task respond(input [31:0] data);begin
   icb_rsp_rdata<=data;icb_rsp_err<=0;icb_rsp_valid<=1;state<=RESPONSE;
 end endtask
 task reject(input [4:0] cause);begin
   errors<=errors|cause|(command_error?5'b10000:5'b0);
   icb_rsp_rdata<=0;icb_rsp_err<=1;icb_rsp_valid<=1;state<=RESPONSE;
 end endtask
 task core_command(input [2:0] op);begin pending_op<=op;state<=CORE_WAIT;end endtask
 always @(posedge clk or negedge rst_n)begin
   if(!rst_n)begin
     state<=IDLE;pending_op<=0;addr<=0;wdata<=0;rd<=0;wmask<=0;
     errors<=0;shift_reg<=0;kind_reg<=0;load_addr_reg<=0;lo_reg<=0;hi_reg<=0;
     row_addr_reg<=0;fresh_lo<=0;fresh_hi<=0;row_flags<=0;
     load_begin<=0;load_valid<=0;start<=0;row_ack<=0;row_rd_en<=0;load_data<=0;ack_index<=0;
     icb_rsp_valid<=0;icb_rsp_rdata<=0;icb_rsp_err<=0;
   end else begin
     load_begin<=0;load_valid<=0;start<=0;row_ack<=0;row_rd_en<=0;
     if(command_error)errors<=errors|5'b10000;
     if(state==RESPONSE && !icb_rsp_ready) icb_rsp_rdata<=icb_rsp_rdata+1;
     case(state)
       IDLE:if(icb_cmd_valid)begin
         addr<=icb_cmd_addr;wdata<=icb_cmd_wdata;rd<=icb_cmd_read;wmask<=icb_cmd_wmask;
         state<=EXEC;
       end
       EXEC:begin
         if(!rd && addr>=BASE_ADDR && offset<256 && addr[1:0]==0 && offset=='h24)begin
           fresh_lo<=0;fresh_hi<=0;
         end
         if(addr[1:0]!=0 || addr<BASE_ADDR || offset>=256)reject(5'b00001);
         else if(!rd && wmask!=15)reject(5'b00010);
         else if(rd)begin
           case(offset)
             'h00:respond(32'h4b575431);
             'h04:respond({27'b0,(|errors),done,row_ready,loaded,busy});
             'h08,'h24,'h38:reject(5'b00010);
             'h0c:respond({27'b0,errors});
             'h10:respond({26'b0,shift_reg});
             'h14:respond({30'b0,kind_reg});
             'h18:respond(load_addr_reg);
             'h1c:respond(lo_reg);
             'h20:respond({16'b0,hi_reg});
             'h28:respond(row_index);
             'h2c:respond(row_addr_reg);
             'h30:if(!row_ready)reject(5'b10000);else begin
               row_rd_en<=1;core_command(OP_READ);
             end
             'h34:respond({29'b0,row_flags});
             'h3c:respond((N<<16)|M);
             'h40:respond(32'd64);
             default:reject(5'b00001);
           endcase
         end else begin
           case(offset)
             'h00,'h04,'h28,'h30,'h34,'h3c,'h40:reject(5'b00010);
             'h08:if(wdata!=1&&wdata!=2)reject(5'b00100);else begin
               if(wdata==1)load_begin<=1;else start<=1;
               core_command(OP_COMMAND);
             end
             'h0c:if(wdata[31:5]!=0)reject(5'b00100);else begin
               errors<=(errors&~wdata[4:0])|(command_error?5'b10000:5'b0);respond(0);
             end
             'h10:if(busy)reject(5'b10000);else if(wdata>47)reject(5'b00100);
               else begin shift_reg<=wdata[5:0];respond(0);end
             'h14:if(busy)reject(5'b10000);else if(wdata>2)reject(5'b00100);
               else begin kind_reg<=wdata[1:0];respond(0);end
             'h18:if(busy)reject(5'b10000);else begin load_addr_reg<=wdata;respond(0);end
             'h1c:if(busy)reject(5'b10000);else begin lo_reg<=wdata;fresh_lo<=1;respond(0);end
             'h20:if(busy)reject(5'b10000);else if(wdata[31:16]!=0)reject(5'b00100);
               else begin hi_reg<=wdata[15:0];fresh_hi<=1;respond(0);end
             'h24:begin
               // Every aligned/full-word commit attempt consumes both halves.
               fresh_lo<=0;fresh_hi<=0;
               if(wdata!=1)reject(5'b00100);
               else if(busy)reject(5'b10000);
               else if(!fresh_lo || (kind_reg==2 && !fresh_hi))reject(5'b01000);
               else if(kind_reg!=2 && lo_reg!={{16{lo_reg[15]}},lo_reg[15:0]})reject(5'b00100);
               else begin
                 load_data<=kind_reg==2?{hi_reg,lo_reg}:{{32{lo_reg[15]}},lo_reg[15:0]};
                 load_valid<=1;core_command(OP_COMMIT);
               end
             end
             'h2c:if(busy&&!row_ready)reject(5'b10000);else if(wdata>=N)reject(5'b00100);
               else begin row_addr_reg<=wdata;respond(0);end
             'h38:begin ack_index<=wdata;row_ack<=1;core_command(OP_ACK);end
             default:reject(5'b00001);
           endcase
         end
       end
       CORE_WAIT:state<=CORE_CHECK;
       CORE_CHECK:begin
         if(command_error)reject(5'b10000);
         else if(pending_op==OP_READ)begin
           if(!row_rd_valid)reject(5'b10000);
           else begin row_flags<={1'b1,row_rd_saturated,row_rd_overflow};respond(row_rd_data);end
         end else begin
           if(pending_op==OP_COMMAND || pending_op==OP_ACK)row_flags<=0;
           if(pending_op==OP_COMMAND && wdata==1)begin fresh_lo<=0;fresh_hi<=0;end
           respond(0);
         end
       end
       RESPONSE:if(icb_rsp_ready)begin icb_rsp_valid<=0;state<=IDLE;end
       default:begin state<=IDLE;icb_rsp_valid<=0;errors<=errors|5'b10000;end
     endcase
   end
 end
endmodule
