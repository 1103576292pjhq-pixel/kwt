// Platform-neutral FFN1 prototype. K is fixed at 64; M/N may shrink for DV.
module ffn1_top #(parameter integer M=99,N=256)(
 input wire clk,rst_n,load_begin,load_valid,start,row_ack,row_rd_en,
 input wire [1:0] load_kind,
 input wire [31:0] load_addr,row_ack_index,row_rd_addr,
 input wire signed [47:0] load_data,
 input wire [5:0] shift,
 output wire load_ready,loaded,busy,
 output reg done,command_error,
 output wire row_ready,
 output reg row_rd_valid,
 output wire [31:0] row_index,
 output wire signed [31:0] row_rd_data,
 output wire row_rd_overflow,row_rd_saturated
);
 localparam [3:0] IDLE=0, B_REQ=1, DOT_START=2, PRIME=3, FEED=4, RESULT=5, ROW_WAIT=6;
 reg [3:0] state;
 reg loading;
 reg [31:0] xcount,wcount,bcount;
 reg [31:0] m,n,k;
 reg [5:0] task_shift;
 wire dot_start_ready,dot_in_ready,dot_valid,dot_overflow,dot_saturated,dot_error;
 wire signed [31:0] dot_data;
 wire signed [47:0] bias_q;
 wire [15:0] x_q,w_q;
 wire [33:0] y_q;
 wire load_ok;
 assign loaded=loading && xcount==M*64 && wcount==N*64 && bcount==N;
 assign busy=state!=IDLE;
 assign load_ready=state==IDLE && loading && !load_begin && !start;
 assign load_ok=load_valid && load_ready &&
   ((load_kind==0 && load_addr==xcount && xcount<M*64 && load_data=={{32{load_data[15]}},load_data[15:0]}) ||
    (load_kind==1 && load_addr==wcount && wcount<N*64 && load_data=={{32{load_data[15]}},load_data[15:0]}) ||
    (load_kind==2 && load_addr==bcount && bcount<N));
 assign row_ready=state==ROW_WAIT;
 assign row_index=m;
 wire ack_ok=row_ack && row_ready && row_ack_index==m;
 wire read_ok=row_rd_en && row_ready && row_rd_addr<N && !ack_ok;
 assign row_rd_data=$signed(y_q[31:0]);
 assign row_rd_overflow=y_q[32];
 assign row_rd_saturated=y_q[33];
 wire operand_read=(state==PRIME)||(state==FEED && dot_in_ready && k<63);
 wire [31:0] operand_k=(state==PRIME)?0:k+1;
 prototype_sync_ram #(.WIDTH(16),.DEPTH(M*64)) xram(
   .clk(clk),.wr_en(load_ok && load_kind==0),.wr_addr(load_addr),.wr_data(load_data[15:0]),
   .rd_en(operand_read),.rd_addr(m*64+operand_k),.rd_data(x_q));
 prototype_sync_ram #(.WIDTH(16),.DEPTH(N*64)) wram(
   .clk(clk),.wr_en(load_ok && load_kind==1),.wr_addr(load_addr),.wr_data(load_data[15:0]),
   .rd_en(operand_read),.rd_addr(n*64+operand_k),.rd_data(w_q));
 prototype_sync_ram #(.WIDTH(48),.DEPTH(N)) bram(
   .clk(clk),.wr_en(load_ok && load_kind==2),.wr_addr(load_addr),.wr_data(load_data),
   .rd_en(state==B_REQ),.rd_addr(n),.rd_data(bias_q));
 prototype_sync_ram #(.WIDTH(34),.DEPTH(N)) yram(
   .clk(clk),.wr_en(state==RESULT && dot_valid && !dot_error),.wr_addr(n),
   .wr_data({dot_saturated,dot_overflow,dot_data}),
   .rd_en(read_ok),.rd_addr(row_rd_addr),.rd_data(y_q));
 dot64 mac(
   .clk(clk),.rst_n(rst_n),.start_valid(state==DOT_START),.start_ready(dot_start_ready),
   .start_bias(bias_q),.start_shift(task_shift),
   .in_valid(state==FEED),.in_ready(dot_in_ready),.in_x($signed(x_q)),.in_w($signed(w_q)),
   .out_valid(dot_valid),.out_ready(state==RESULT),.out_data(dot_data),.out_raw(),
   .out_overflow(dot_overflow),.out_saturated(dot_saturated),.out_error(dot_error),.busy());
 always @(posedge clk or negedge rst_n) begin
   if(!rst_n) begin
     state<=IDLE; loading<=0; xcount<=0; wcount<=0; bcount<=0;
     m<=0; n<=0; k<=0; task_shift<=0; done<=0; command_error<=0; row_rd_valid<=0;
   end else begin
     command_error<=0;
     row_rd_valid<=read_ok;
     if(load_valid && !load_ok) command_error<=1;
     if(row_ack && !ack_ok) command_error<=1;
     if(row_rd_en && !read_ok) command_error<=1;
     if(load_begin) begin
       if(state!=IDLE || start || load_valid) command_error<=1;
       else begin loading<=1; xcount<=0; wcount<=0; bcount<=0; done<=0; m<=0; end
     end
     if(load_ok) case(load_kind)
       0: xcount<=xcount+1;
       1: wcount<=wcount+1;
       2: bcount<=bcount+1;
       default: command_error<=1;
     endcase
     if(start) begin
       if(state!=IDLE || !loaded || shift>47 || load_begin || load_valid) command_error<=1;
       else begin
         state<=B_REQ; m<=0; n<=0; k<=0; task_shift<=shift; done<=0;
         loading<=0; // Every new task must explicitly reload X/W/b.
       end
     end
     case(state)
       IDLE: begin end
       B_REQ: state<=DOT_START;
       DOT_START: if(dot_start_ready) begin state<=PRIME; k<=0; end
       PRIME: state<=FEED;
       FEED: if(dot_in_ready) begin
         if(k==63) state<=RESULT;
         else k<=k+1;
       end
       RESULT: if(dot_valid) begin
         if(dot_error) begin state<=IDLE; command_error<=1; end
         else if(n==N-1) state<=ROW_WAIT;
         else begin n<=n+1; state<=B_REQ; end
       end
       ROW_WAIT: if(ack_ok) begin
         if(m==M-1) begin state<=IDLE; done<=1; end
         else begin m<=m+1; n<=0; state<=B_REQ; end
       end
       default: begin state<=IDLE; loading<=0; done<=0; command_error<=1; end
     endcase
   end
 end
endmodule
