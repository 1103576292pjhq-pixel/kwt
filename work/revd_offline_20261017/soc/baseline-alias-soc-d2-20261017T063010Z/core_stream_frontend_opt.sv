`timescale 1ns/1ps
module core_stream_frontend_opt #(
 parameter integer M=99,N=256,PM=4,READ_LATENCY=1,K=64,PN=4,N_TILE=16
)(
 input wire clk,rst_n,in_valid,output wire in_ready,
 input wire [3:0] in_op,in_layer_id,input wire [31:0] in_task_id,
 input wire [7:0] in_tile_id,input wire [15:0] in_index,
 input wire signed [47:0] in_data,input wire [5:0] in_shift,
 output wire out_valid,input wire out_ready,
 output wire [31:0] out_task_id,out_y_index,output wire signed [31:0] out_data,
 output wire out_overflow,out_saturated,out_last,
 output reg core_done,output reg fault,output reg [7:0] error_code
);
 localparam integer XD=((M+PM-1)/PM)*64,WD=N*16,XAW=$clog2(XD),WAW=$clog2(WD);
 localparam [3:0] IDLE=0,LOAD=1,CLEAR=2,READ=3,WAIT_READ=4,ACC=5,QISSUE=6,QWAIT=7,DRAIN=8;
 reg [3:0] state;
 reg q_valid;reg [3:0] q_op,q_layer;reg [31:0] q_task;
 reg [7:0] q_tile;reg [15:0] q_index;reg signed [47:0] q_data;reg [5:0] q_shift;
 reg [31:0] task_id;reg [5:0] shift;
 integer x_count,w_count,b_count,next_tile,committed;
 reg tile_open;
 integer row0,tile,g,k,qrow,qcol,out_pos;
 reg signed [47:0] acc[0:PM-1][0:3];
 reg signed [31:0] product[0:PM-1][0:3];reg [PM-1:0] product_mask;reg [5:0] product_k;
 reg signed [47:0] biases[0:N-1];
 reg signed [31:0] result_data[0:PM*16-1];
 reg result_overflow[0:PM*16-1],result_saturated[0:PM*16-1];
 wire [PM-1:0] x_valid;wire [PM-1:0] row_mask;wire [3:0] w_valid;
 wire signed [15:0] x_data[0:PM-1],w_data[0:3];
 wire [PM-1:0] x_rd,x_wr;wire [3:0] w_rd,w_wr;
 wire [XAW-1:0] x_addr[0:PM-1];wire [WAW-1:0] w_addr[0:3];
 wire retire_event=q_valid&&!fault;
 reg command_ok;
 wire int16_ok=q_data=={{32{q_data[15]}},q_data[15:0]};
 wire x_write=retire_event&&state==LOAD&&q_op==1&&command_ok;
 wire w_write=retire_event&&state==LOAD&&q_op==3&&command_ok;
 integer row,col;
 // Registered ordered entry: acceptance precedes actual RAM retirement.
 // Close ingress while the final record is published, including backpressure.
 // An earlier accepted event still retires (and may fault) before success.
 // BEGIN held across this boundary belongs to the next task after the done pulse.
 assign in_ready=!fault&&!core_done&&!(state==DRAIN&&out_last)&&(!q_valid||retire_event);
 always @* begin
  command_ok=0;
  if(q_op==0) command_ok=state==IDLE&&q_shift<=47&&q_layer>=1&&q_layer<=12;
  else if(state==LOAD&&q_task==task_id) begin
   case(q_op)
    1:command_ok=!tile_open&&next_tile==0&&32'(q_index)==x_count&&x_count<M*64&&int16_ok;
    2:command_ok=x_count==M*64&&!tile_open&&next_tile<N/16&&32'(q_tile)==next_tile;
    3:command_ok=tile_open&&32'(q_tile)==next_tile&&32'(q_index)==w_count&&w_count<1024&&b_count==0&&int16_ok;
    4:command_ok=tile_open&&32'(q_tile)==next_tile&&w_count==1024&&32'(q_index)==b_count&&b_count<16;
    5:command_ok=tile_open&&32'(q_tile)==next_tile&&w_count==1024&&b_count==16;
    6:command_ok=!tile_open&&committed==N/16&&x_count==M*64;
    default:command_ok=0;
   endcase
  end
 end
 genvar xb,wb;
 generate for(xb=0;xb<PM;xb=xb+1) begin:xbank
  assign x_wr[xb]=x_write&&((32'(q_index)/64)%PM==xb);
  assign row_mask[xb]=(row0+xb<M);
  assign x_rd[xb]=(state==READ)&&!fault&&row_mask[xb];
  assign x_addr[xb]=x_write?XAW'((32'(q_index)/64/PM)*64+32'(q_index)%64):XAW'((row0/PM)*64+k);
  banked_sp16 #(.DEPTH(XD),.ADDR_W(XAW),.READ_LATENCY(READ_LATENCY)) ram(
   .clk(clk),.rst_n(rst_n),.wr_en(x_wr[xb]),.rd_en(x_rd[xb]),.addr(x_addr[xb]),
   .wr_data(q_data[15:0]),.rd_data(x_data[xb]),.rd_valid(x_valid[xb]));
 end
 for(wb=0;wb<4;wb=wb+1) begin:wbank
  assign w_wr[wb]=w_write&&(32'(q_index)%4==wb);
  assign w_rd[wb]=(state==READ)&&!fault;
  assign w_addr[wb]=w_write?WAW'(next_tile*256+(32'(q_index)%16/4)*64+32'(q_index)/16):WAW'(tile*256+g*64+k);
  banked_sp16 #(.DEPTH(WD),.ADDR_W(WAW),.READ_LATENCY(READ_LATENCY)) ram(
   .clk(clk),.rst_n(rst_n),.wr_en(w_wr[wb]),.rd_en(w_rd[wb]),.addr(w_addr[wb]),
   .wr_data(q_data[15:0]),.rd_data(w_data[wb]),.rd_valid(w_valid[wb]));
 end endgenerate
 wire qe_ready,qe_valid;wire signed [47:0] unused_qe_raw;wire signed [31:0] qe_data;wire qe_overflow,qe_saturated;
 quant_epilogue quant(.clk(clk),.rst_n(rst_n),.in_valid(state==QISSUE&&!fault),.in_ready(qe_ready),
  .in_sum(acc[qrow][qcol]),.in_bias(biases[tile*16+g*4+qcol]),.in_shift(shift),
  .out_valid(qe_valid),.out_ready(state==QWAIT&&!fault),.out_raw(unused_qe_raw),.out_data(qe_data),
  .out_overflow(qe_overflow),.out_saturated(qe_saturated));
 assign out_valid=state==DRAIN;assign out_task_id=task_id;
 assign out_y_index=32'((row0+out_pos/16)*N+tile*16+out_pos%16);
 assign out_data=result_data[out_pos];assign out_overflow=result_overflow[out_pos];
 assign out_saturated=result_saturated[out_pos];
 assign out_last=row0+out_pos/16==M-1&&tile==N/16-1&&out_pos%16==15;
 // Passive counters count actual CE/fire/retirement, not software predictions.
 reg [63:0] load_cycles,compute_cycles,output_cycles,wait_cycles,core_cycles,frontend_cycles;
 reg [63:0] issue_count,retire_count,effective_macs,virtual_macs,input_accepts,event_retires;
 reg [63:0] x_reads[0:PM-1],x_writes[0:PM-1],w_reads[0:3],w_writes[0:3];
 reg core_active;integer effective_rows;
 always @* effective_rows=(M-row0<PM)?M-row0:PM;
 initial begin
  if(M<1||M>99||N<16||N>256||N%16!=0||(PM!=1&&PM!=2&&PM!=4)||K!=64||PN!=4||N_TILE!=16||READ_LATENCY<1||READ_LATENCY>2)
   $fatal(1,"unsupported RevD geometry");
 end
 always @(posedge clk) begin
  if(!rst_n) begin
   state<=IDLE;q_valid<=0;fault<=0;error_code<=0;core_done<=0;core_active<=0;
   task_id<=0;shift<=0;x_count<=0;w_count<=0;b_count<=0;next_tile<=0;committed<=0;tile_open<=0;
   row0<=0;tile<=0;g<=0;k<=0;qrow<=0;qcol<=0;out_pos<=0;product_mask<=0;product_k<=0;
   load_cycles<=0;compute_cycles<=0;output_cycles<=0;wait_cycles<=0;core_cycles<=0;frontend_cycles<=0;
   issue_count<=0;retire_count<=0;effective_macs<=0;virtual_macs<=0;input_accepts<=0;event_retires<=0;
   for(row=0;row<PM;row=row+1) begin x_reads[row]<=0;x_writes[row]<=0;end
   for(col=0;col<4;col=col+1) begin w_reads[col]<=0;w_writes[col]<=0;end
  end else begin
   core_done<=0;
   if(retire_event) q_valid<=0;
   if(in_valid&&in_ready) begin
    q_valid<=1;q_op<=in_op;q_task<=in_task_id;q_layer<=in_layer_id;q_tile<=in_tile_id;q_index<=in_index;q_data<=in_data;q_shift<=in_shift;
    input_accepts<=input_accepts+1;
   end
   if(state!=IDLE) frontend_cycles<=frontend_cycles+1;
   if(state==LOAD) load_cycles<=load_cycles+1;
   if(core_active) core_cycles<=core_cycles+1;
   if(state>=CLEAR&&state<=QWAIT) compute_cycles<=compute_cycles+1;
   if(state==DRAIN) output_cycles<=output_cycles+1;
   if(state==WAIT_READ||(state==DRAIN&&!out_ready)) wait_cycles<=wait_cycles+1;
   for(row=0;row<PM;row=row+1) begin
    if(x_rd[row]) x_reads[row]<=x_reads[row]+1;
    if(x_wr[row]) x_writes[row]<=x_writes[row]+1;
   end
   for(col=0;col<4;col=col+1) begin
    if(w_rd[col]) w_reads[col]<=w_reads[col]+1;
    if(w_wr[col]) w_writes[col]<=w_writes[col]+1;
   end
   if(retire_event) begin
    event_retires<=event_retires+1;
    if(!command_ok) begin fault<=1;error_code<=8'h10+{4'b0,q_op};end
    else case(q_op)
     0:begin
      state<=LOAD;task_id<=q_task;shift<=q_shift;
      x_count<=0;w_count<=0;b_count<=0;next_tile<=0;committed<=0;tile_open<=0;core_active<=0;
      row0<=0;tile<=0;g<=0;k<=0;qrow<=0;qcol<=0;out_pos<=0;product_mask<=0;
      load_cycles<=0;compute_cycles<=0;output_cycles<=0;wait_cycles<=0;core_cycles<=0;frontend_cycles<=0;
      issue_count<=0;retire_count<=0;effective_macs<=0;virtual_macs<=0;
      input_accepts<=1+(in_valid&&in_ready?64'd1:64'd0);event_retires<=1;
      for(row=0;row<PM;row=row+1) begin x_reads[row]<=0;x_writes[row]<=0;end
      for(col=0;col<4;col=col+1) begin w_reads[col]<=0;w_writes[col]<=0;end
     end
     1:x_count<=x_count+1;
     2:begin tile_open<=1;w_count<=0;b_count<=0;end
     3:w_count<=w_count+1;
     4:begin biases[next_tile*16+b_count]<=q_data;b_count<=b_count+1;end
     5:begin tile_open<=0;next_tile<=next_tile+1;committed<=committed+1;end
     6:begin state<=CLEAR;row0<=0;tile<=0;g<=0;k<=0;core_active<=1;end
     default:begin end
    endcase
   end
   if(!fault&&!(retire_event&&!command_ok)) case(state)
    CLEAR:begin
     for(row=0;row<PM;row=row+1) for(col=0;col<4;col=col+1) acc[row][col]<=0;
     k<=0;state<=READ;
    end
    READ:state<=WAIT_READ;
    WAIT_READ:if((&w_valid)&&(&(x_valid|~row_mask))) begin
     for(row=0;row<PM;row=row+1) begin
      product_mask[row]<=row0+row<M;
      for(col=0;col<4;col=col+1) begin
`ifdef MUT_UNSIGNED
       product[row][col]<=row0+row<M?$unsigned(x_data[row])*$unsigned(w_data[col]):32'sd0;
`else
       product[row][col]<=row0+row<M?$signed(x_data[row])*$signed(w_data[col]):32'sd0;
`endif
      end
     end
     product_k<=6'(k);issue_count<=issue_count+1;state<=ACC;
    end
    ACC:begin
     for(row=0;row<PM;row=row+1) for(col=0;col<4;col=col+1)
      if(product_mask[row]) begin
`ifdef MUT_DROP_K63
       if(product_k!=63)
`endif
       acc[row][col]<=acc[row][col]+{{16{product[row][col][31]}},product[row][col]};
      end
     retire_count<=retire_count+1;effective_macs<=effective_macs+64'(effective_rows*4);
     virtual_macs<=virtual_macs+64'(32'((PM-effective_rows)*4));
     if(product_k==63) begin qrow<=0;qcol<=0;state<=QISSUE;end
     else begin k<=k+1;state<=READ;end
    end
    QISSUE:if(qe_ready) state<=QWAIT;
    QWAIT:if(qe_valid) begin
     result_data[qrow*16+g*4+qcol]<=qe_data;
     result_overflow[qrow*16+g*4+qcol]<=qe_overflow;result_saturated[qrow*16+g*4+qcol]<=qe_saturated;
     if(qcol<3) begin qcol<=qcol+1;state<=QISSUE;end
     else if(qrow+1<effective_rows) begin qrow<=qrow+1;qcol<=0;state<=QISSUE;end
     else if(g<3) begin g<=g+1;state<=CLEAR;end
     else begin out_pos<=0;state<=DRAIN;end
    end
    DRAIN:if(out_ready) begin
     if(out_pos+1<effective_rows*16) out_pos<=out_pos+1;
     else if(row0+PM<M) begin row0<=row0+PM;g<=0;state<=CLEAR;end
     else if(tile+1<N/16) begin tile<=tile+1;row0<=0;g<=0;state<=CLEAR;end
     else begin state<=IDLE;core_active<=0;core_done<=1;end
    end
    default:begin end
   endcase
   // Fault retains a published block until its handshakes; never report success.
   if((fault||(retire_event&&!command_ok))&&state==DRAIN&&out_ready&&out_valid) begin
    if(out_pos+1<effective_rows*16) out_pos<=out_pos+1;else state<=IDLE;
   end
  end
 end
endmodule
