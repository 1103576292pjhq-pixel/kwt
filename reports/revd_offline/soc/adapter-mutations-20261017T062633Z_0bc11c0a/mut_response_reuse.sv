`timescale 1ns/1ps
// One response and one captured input event. MMIO never waits for a core slot:
// software observes capacity, and a full COMMIT returns an immediate bus error.
// Result fields remain owned by the frontend until the explicit POP handshake.
module revd_opt_icb #(
  parameter integer M=99,N=256,PM=4,READ_LATENCY=1
)(
  input wire clk,rst_n,icb_cmd_valid,
  output wire icb_cmd_ready,
  input wire [31:0] icb_cmd_addr,
  input wire icb_cmd_read,
  input wire [31:0] icb_cmd_wdata,
  input wire [3:0] icb_cmd_wmask,
  output reg icb_rsp_valid,
  input wire icb_rsp_ready,
  output reg [31:0] icb_rsp_rdata,
  output reg icb_rsp_err
);
  reg [31:0] meta,task_id,position,data_lo;
  reg [15:0] data_hi;
  reg event_valid,done;
  reg [31:0] event_meta,event_task,event_position;
  reg signed [47:0] event_data;
  wire core_ready,out_valid,core_done,fault;
  wire [7:0] error_code;
  wire [31:0] out_task_id,out_y_index;
  wire signed [31:0] out_data;
  wire out_overflow,out_saturated,out_last;
  reg [31:0] accepted_events,popped_results;
  wire address_ok=icb_cmd_addr[31:8]==24'h110000&&icb_cmd_addr[1:0]==0;
  wire fire=icb_cmd_valid&&icb_cmd_ready;
  wire write_ok=address_ok&&!icb_cmd_read&&icb_cmd_wmask==4'hf;
  wire pop=fire&&write_ok&&icb_cmd_addr[7:0]==8'h2c&&out_valid;
  assign icb_cmd_ready=1'b1;
  core_stream_frontend_opt #(.M(M),.N(N),.PM(PM),.READ_LATENCY(READ_LATENCY)) core(
    .clk(clk),.rst_n(rst_n),.in_valid(event_valid),.in_ready(core_ready),
    .in_op(event_meta[3:0]),.in_layer_id(event_meta[7:4]),
    .in_task_id(event_task),.in_tile_id(event_position[23:16]),
    .in_index(event_position[15:0]),.in_data(event_data),.in_shift(event_meta[13:8]),
    .out_valid(out_valid),.out_ready(pop),.out_task_id(out_task_id),
    .out_y_index(out_y_index),.out_data(out_data),.out_overflow(out_overflow),
    .out_saturated(out_saturated),.out_last(out_last),.core_done(core_done),
    .fault(fault),.error_code(error_code));
  always @(posedge clk)begin
    if(!rst_n)begin
      icb_rsp_valid<=0;icb_rsp_err<=0;icb_rsp_rdata<=0;
      meta<=0;task_id<=0;position<=0;data_lo<=0;data_hi<=0;
      event_valid<=0;event_meta<=0;event_task<=0;event_position<=0;event_data<=0;
      done<=0;accepted_events<=0;popped_results<=0;
    end else begin
      if(icb_rsp_valid&&icb_rsp_ready)icb_rsp_valid<=0;
      if(core_done)done<=1;
      if(event_valid&&core_ready)begin
        event_valid<=0;accepted_events<=accepted_events+1;
        if(event_meta[3:0]==0)begin done<=0;popped_results<=0;end
      end
      if(pop)popped_results<=popped_results+1;
      if(fire)begin
        icb_rsp_valid<=1;icb_rsp_err<=0;icb_rsp_rdata<=0;
        if(!address_ok||(!icb_cmd_read&&icb_cmd_wmask!=4'hf))icb_rsp_err<=1;
        else if(icb_cmd_read)case(icb_cmd_addr[7:0])
          8'h00:icb_rsp_rdata<={28'b0,fault,done,out_valid,!event_valid};
          8'h04:icb_rsp_rdata<=meta;
          8'h08:icb_rsp_rdata<=task_id;
          8'h0c:icb_rsp_rdata<=position;
          8'h10:icb_rsp_rdata<=data_lo;
          8'h14:icb_rsp_rdata<={16'b0,data_hi};
          8'h1c:icb_rsp_rdata<=out_y_index;
          8'h20:icb_rsp_rdata<=out_data;
          8'h24:icb_rsp_rdata<={29'b0,out_last,out_saturated,out_overflow};
          8'h28:icb_rsp_rdata<=out_task_id;
          8'h30:icb_rsp_rdata<={24'b0,error_code};
          8'h34:icb_rsp_rdata<=accepted_events;
          8'h38:icb_rsp_rdata<=popped_results;
          default:icb_rsp_err<=1;
        endcase
        else case(icb_cmd_addr[7:0])
          8'h04:meta<=icb_cmd_wdata;
          8'h08:task_id<=icb_cmd_wdata;
          8'h0c:position<=icb_cmd_wdata;
          8'h10:data_lo<=icb_cmd_wdata;
          8'h14:data_hi<=icb_cmd_wdata[15:0];
          8'h18:begin
            if(event_valid||fault)icb_rsp_err<=1;
            else begin
              event_valid<=1;event_meta<=meta;event_task<=task_id;
              event_position<=position;event_data<={data_hi,data_lo};
            end
          end
          8'h2c:if(!out_valid)icb_rsp_err<=1;
          default:icb_rsp_err<=1;
        endcase
      end
    end
  end
endmodule
