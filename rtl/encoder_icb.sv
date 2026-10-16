// One-outstanding ICB bridge; each response reports only its own transaction.
module encoder_icb #(parameter integer M=99,D=64,H=256,parameter [31:0] BASE_ADDR=32'h11010000)(
 input wire clk,rst_n,icb_cmd_valid,output wire icb_cmd_ready,
 input wire [31:0] icb_cmd_addr,input wire icb_cmd_read,input wire [31:0] icb_cmd_wdata,
 input wire [3:0] icb_cmd_wmask,output reg icb_rsp_valid,input wire icb_rsp_ready,
 output reg [31:0] icb_rsp_rdata,output reg icb_rsp_err);
 localparam IDLE=0,SEND=1,WAIT=2,WAIT_DONE=3;
 reg [1:0] state;reg [31:0] address,sticky;
 reg [25:0] wait_cycles;
 reg [2:0] req_op;reg [31:0] req_addr,req_data;reg increment;
 wire req_ready,rsp_valid,rsp_error,busy,done,job_done,fault;
 wire [31:0] rsp_data,x_count,w_count,layer_index;wire [63:0] cycles;wire [4:0] flags;
 wire trace_valid;wire [3:0] trace_stage;wire [31:0] trace_addr,trace_data;
 wire [31:0] offset=icb_cmd_addr-BASE_ADDR;
 wire address_ok=icb_cmd_addr>=BASE_ADDR&&offset<256&&offset[1:0]==0;
 assign icb_cmd_ready=state==IDLE&&!icb_rsp_valid;
 encoder_core #(.M(M),.D(D),.H(H)) core(.clk(clk),.rst_n(rst_n),.req_valid(state==SEND),
  .req_ready(req_ready),.req_op(req_op),.req_addr(req_addr),.req_data(req_data),
  .rsp_valid(rsp_valid),.rsp_ready(state==WAIT),.rsp_data(rsp_data),.rsp_error(rsp_error),
  .busy(busy),.done(done),.job_done(job_done),.fault(fault),.x_count(x_count),.w_count(w_count),
  .layer_index(layer_index),.cycles(cycles),.flags(flags),.trace_valid(trace_valid),
  .trace_stage(trace_stage),.trace_addr(trace_addr),.trace_data(trace_data));
 task reject;
  begin icb_rsp_err<=1;sticky<=sticky|1;end
 endtask
 task submit(input [2:0] operation,input [31:0] value,input inc);
  begin req_op<=operation;req_addr<=address;req_data<=value;increment<=inc;state<=SEND;icb_rsp_valid<=0;end
 endtask
 always @(posedge clk)begin
  if(!rst_n)begin state<=IDLE;address<=0;sticky<=0;icb_rsp_valid<=0;icb_rsp_rdata<=0;icb_rsp_err<=0;req_op<=0;req_addr<=0;req_data<=0;increment<=0;wait_cycles<=0;end
  else begin
   if(fault)sticky<=sticky|4;
   if(icb_rsp_valid&&icb_rsp_ready)icb_rsp_valid<=0;
   if(state==SEND&&req_ready)state<=WAIT;
   if(state==WAIT&&rsp_valid)begin
    state<=IDLE;icb_rsp_valid<=1;icb_rsp_rdata<=rsp_data;icb_rsp_err<=rsp_error;
    if(rsp_error)sticky<=sticky|2;
    else if(increment)address<=address+1;
   end
   if(state==WAIT_DONE)begin
    wait_cycles<=wait_cycles+1'b1;
    if(!busy||wait_cycles==26'd40000000)begin
     state<=IDLE;icb_rsp_valid<=1;
     icb_rsp_rdata<={28'b0,(|sticky)||fault,job_done,done,busy};
     icb_rsp_err<=wait_cycles==26'd40000000;
     if(wait_cycles==26'd40000000)sticky<=sticky|1;
    end
   end
   if(icb_cmd_valid&&icb_cmd_ready)begin
    icb_rsp_valid<=1;icb_rsp_rdata<=0;icb_rsp_err<=0;
    if(!address_ok || (!icb_cmd_read&&icb_cmd_wmask!=15))reject();
    else if(icb_cmd_read)case(offset)
     0:icb_rsp_rdata<=32'h454e4331;
     4:icb_rsp_rdata<={28'b0,(|sticky)||fault,job_done,done,busy};
     12:icb_rsp_rdata<=sticky;
     16:icb_rsp_rdata<=address;
     28:submit(4,0,1);
     32:icb_rsp_rdata<=layer_index;
     36:icb_rsp_rdata<=x_count;
     40:icb_rsp_rdata<=w_count;
     44:icb_rsp_rdata<=cycles[31:0];
     48:icb_rsp_rdata<=cycles[63:32];
     52:icb_rsp_rdata<={27'b0,flags};
     56:icb_rsp_rdata<=(M<<16)|D;
     60:icb_rsp_rdata<=H;
     64:icb_rsp_rdata<=4*D*D+2*D*H+H+6*D;
     68:if(busy)begin state<=WAIT_DONE;icb_rsp_valid<=0;wait_cycles<=0;end
       else icb_rsp_rdata<={28'b0,(|sticky)||fault,job_done,done,busy};
     default:reject();
    endcase
    else case(offset)
     8:if(icb_cmd_wdata==0||icb_cmd_wdata==3||icb_cmd_wdata==5||icb_cmd_wdata==6||icb_cmd_wdata==7)
       submit(icb_cmd_wdata[2:0],layer_index,0);else reject();
     12:if(icb_cmd_wdata[31:3]!=0)reject();else sticky<=sticky&~icb_cmd_wdata;
     16:if(busy)reject();else address<=icb_cmd_wdata;
     20:submit(1,icb_cmd_wdata,1);
     24:submit(2,icb_cmd_wdata,1);
     default:reject();
    endcase
   end
  end
 end
endmodule
