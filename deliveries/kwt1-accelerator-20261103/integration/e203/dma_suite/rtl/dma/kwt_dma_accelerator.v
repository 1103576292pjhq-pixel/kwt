`include "kwt_icb_config.vh"
`default_nettype none
module kwt_dma_accelerator #(
 parameter FORWARD_INPUT=1,parameter FORWARD_RESULT=1,parameter RESULT_PRIORITY=0,
 parameter [31:0] BASE_ADDR=32'h11000000,
 parameter [2:0] SRAM_EMA=3'd2,parameter [1:0] SRAM_EMAW=2'd0
)(input wire clk,rst_n,
input wire icb_cmd_valid,
output wire icb_cmd_ready,
input wire [31:0] icb_cmd_addr,icb_cmd_wdata,
input wire icb_cmd_read,
input wire [3:0] icb_cmd_wmask,
output wire icb_rsp_valid,
input wire icb_rsp_ready,
output wire [31:0] icb_rsp_rdata,
output wire icb_rsp_err,
output wire mem_cmd_valid,
input wire mem_cmd_ready,
output wire [31:0] mem_cmd_addr,mem_cmd_wdata,
output wire mem_cmd_read,
output wire [3:0] mem_cmd_wmask,
input wire mem_rsp_valid,
output wire mem_rsp_ready,
input wire [31:0] mem_rsp_rdata,
input wire mem_rsp_err,
output wire irq);
wire  engine_busy;
wire  engine_compute_done;
wire  engine_done;
wire  engine_fault;
wire [7:0]  engine_error;
wire  engine_abort_pending;
wire  engine_abort_done;
wire  load_cmd_valid;
wire  load_cmd_ready;
wire [`KWT_CMD_OP_WIDTH-1:0]  load_cmd_op;
wire [`KWT_LAYER_ID_WIDTH-1:0]  load_cmd_layer_id;
wire [31:0]  load_cmd_task_id;
wire [`KWT_CMD_TILE_WIDTH-1:0]  load_cmd_tile_id;
wire [`KWT_CMD_INDEX_WIDTH-1:0]  load_cmd_index;
wire signed [31:0]  load_cmd_data;
wire  result_cmd_valid;
wire  result_cmd_ready;
wire  result_cmd_ack;
wire [31:0]  result_cmd_task_id;
wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0]  result_cmd_sequence;
wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0]  result_cmd_count;
wire  result_rsp_valid;
wire  result_rsp_ready;
wire [31:0]  result_rsp_data;
wire  result_rsp_error;
wire  result_block_valid;
wire [31:0]  result_block_task_id;
wire [`KWT_RESULT_ROW_WIDTH-1:0]  result_block_row;
wire [`KWT_CMD_TILE_WIDTH-1:0]  result_block_tile;
wire [`KWT_RESULT_COUNT_CONTAINER_WIDTH-1:0]  result_block_count;
wire [`KWT_RESULT_SEQUENCE_WIDTH-1:0]  result_block_sequence;
wire  abort_req;
wire  input_fifo_empty;
wire  transport_empty;
wire start,abort_request,busy,done,failed,aborted;
wire [31:0] x_base,w_base,b_base,y_base,task_id,cycles;
wire [3:0] layer_id;
wire [7:0] error;
wire [15:0] output_words;
wire [8:0] blocks;
assign irq=!busy && (done || failed || aborted);
assign input_fifo_empty=!load_cmd_valid;
wire read_cmd_valid,read_cmd_ready,read_cmd_read,read_rsp_valid,read_rsp_ready,read_rsp_err;
wire [31:0] read_cmd_addr,read_cmd_wdata,read_rsp_rdata;
wire [3:0] read_cmd_wmask;
wire write_cmd_valid,write_cmd_ready,write_cmd_read,write_rsp_valid,write_rsp_ready,write_rsp_err;
wire [31:0] write_cmd_addr,write_cmd_wdata,write_rsp_rdata;
wire [3:0] write_cmd_wmask;
kwt_dma_csr #(.BASE_ADDR(BASE_ADDR)) u_csr(
.clk(clk),.rst_n(rst_n),.cmd_valid(icb_cmd_valid),.cmd_ready(icb_cmd_ready),
.cmd_addr(icb_cmd_addr),.cmd_data(icb_cmd_wdata),.cmd_read(icb_cmd_read),.cmd_mask(icb_cmd_wmask),
.rsp_valid(icb_rsp_valid),.rsp_ready(icb_rsp_ready),.rsp_data(icb_rsp_rdata),.rsp_err(icb_rsp_err),
.start(start),
.abort_request(abort_request),
.x_base(x_base),
.w_base(w_base),
.b_base(b_base),
.y_base(y_base),
.task_id(task_id),
.layer_id(layer_id),
.busy(busy),
.done(done),
.failed(failed),
.aborted(aborted),
.error(error),
.cycles(cycles),
.output_words(output_words),
.blocks(blocks));
kwt_dma_engine #(.SRAM_EMA(SRAM_EMA),.SRAM_EMAW(SRAM_EMAW)) u_engine(.clk(clk),.rst_n(rst_n),
.busy(engine_busy),
.compute_done(engine_compute_done),
.task_done(engine_done),
.fault(engine_fault),
.error_code(engine_error),
.abort_pending(engine_abort_pending),
.abort_done(engine_abort_done),
.load_cmd_valid(load_cmd_valid),
.load_cmd_ready(load_cmd_ready),
.load_cmd_op(load_cmd_op),
.load_cmd_layer_id(load_cmd_layer_id),
.load_cmd_task_id(load_cmd_task_id),
.load_cmd_tile_id(load_cmd_tile_id),
.load_cmd_index(load_cmd_index),
.load_cmd_data(load_cmd_data),
.result_cmd_valid(result_cmd_valid),
.result_cmd_ready(result_cmd_ready),
.result_cmd_ack(result_cmd_ack),
.result_cmd_task_id(result_cmd_task_id),
.result_cmd_sequence(result_cmd_sequence),
.result_cmd_count(result_cmd_count),
.result_rsp_valid(result_rsp_valid),
.result_rsp_ready(result_rsp_ready),
.result_rsp_data(result_rsp_data),
.result_rsp_error(result_rsp_error),
.result_block_valid(result_block_valid),
.result_block_task_id(result_block_task_id),
.result_block_row(result_block_row),
.result_block_tile(result_block_tile),
.result_block_count(result_block_count),
.result_block_sequence(result_block_sequence),
.abort_req(abort_req),
.input_fifo_empty(input_fifo_empty),
.transport_empty(transport_empty));
kwt_dma_controller #(.FORWARD_INPUT(FORWARD_INPUT),.FORWARD_RESULT(FORWARD_RESULT)) u_dma(
.clk(clk),
.rst_n(rst_n),
.start(start),
.abort_request(abort_request),
.x_base(x_base),
.w_base(w_base),
.b_base(b_base),
.y_base(y_base),
.task_id(task_id),
.layer_id(layer_id),
.busy(busy),
.done(done),
.failed(failed),
.aborted(aborted),
.error(error),
.cycles(cycles),
.output_words(output_words),
.blocks(blocks),
.load_cmd_valid(load_cmd_valid),
.load_cmd_ready(load_cmd_ready),
.load_cmd_op(load_cmd_op),
.load_cmd_layer_id(load_cmd_layer_id),
.load_cmd_task_id(load_cmd_task_id),
.load_cmd_tile_id(load_cmd_tile_id),
.load_cmd_index(load_cmd_index),
.load_cmd_data(load_cmd_data),
.result_cmd_valid(result_cmd_valid),
.result_cmd_ready(result_cmd_ready),
.result_cmd_ack(result_cmd_ack),
.result_cmd_task_id(result_cmd_task_id),
.result_cmd_sequence(result_cmd_sequence),
.result_cmd_count(result_cmd_count),
.result_rsp_valid(result_rsp_valid),
.result_rsp_ready(result_rsp_ready),
.result_rsp_data(result_rsp_data),
.result_rsp_error(result_rsp_error),
.result_block_valid(result_block_valid),
.result_block_task_id(result_block_task_id),
.result_block_row(result_block_row),
.result_block_tile(result_block_tile),
.result_block_count(result_block_count),
.result_block_sequence(result_block_sequence),
.engine_done(engine_done),
.engine_fault(engine_fault),
.engine_abort_done(engine_abort_done),
.engine_error(engine_error),
.transport_empty(transport_empty),
.engine_abort(abort_req),
.rd_valid(read_cmd_valid),.rd_ready(read_cmd_ready),.rd_addr(read_cmd_addr),
.rd_rsp_valid(read_rsp_valid),.rd_rsp_ready(read_rsp_ready),.rd_rsp_data(read_rsp_rdata),.rd_rsp_err(read_rsp_err),
.wr_valid(write_cmd_valid),.wr_ready(write_cmd_ready),.wr_addr(write_cmd_addr),.wr_data(write_cmd_wdata),
.wr_rsp_valid(write_rsp_valid),.wr_rsp_ready(write_rsp_ready),.wr_rsp_err(write_rsp_err));
assign read_cmd_read=1'b1;
assign read_cmd_wmask=4'hf;
assign read_cmd_wdata=32'b0;
assign write_cmd_read=1'b0;
assign write_cmd_wmask=4'hf;
wire dma_bus_idle;
kwt_icb_arbiter2 #(.B_PRIORITY(RESULT_PRIORITY)) u_dma_arbiter(.clk(clk),.rst_n(rst_n),
.a_valid(read_cmd_valid),
.a_ready(read_cmd_ready),
.a_addr(read_cmd_addr),
.a_data(read_cmd_wdata),
.a_read(read_cmd_read),
.a_mask(read_cmd_wmask),
.a_rsp_valid(read_rsp_valid),
.a_rsp_ready(read_rsp_ready),
.a_rsp_data(read_rsp_rdata),
.a_rsp_err(read_rsp_err),
.b_valid(write_cmd_valid),
.b_ready(write_cmd_ready),
.b_addr(write_cmd_addr),
.b_data(write_cmd_wdata),
.b_read(write_cmd_read),
.b_mask(write_cmd_wmask),
.b_rsp_valid(write_rsp_valid),
.b_rsp_ready(write_rsp_ready),
.b_rsp_data(write_rsp_rdata),
.b_rsp_err(write_rsp_err),
.m_valid(mem_cmd_valid),
.m_ready(mem_cmd_ready),
.m_addr(mem_cmd_addr),
.m_data(mem_cmd_wdata),
.m_read(mem_cmd_read),
.m_mask(mem_cmd_wmask),
.m_rsp_valid(mem_rsp_valid),
.m_rsp_ready(mem_rsp_ready),
.m_rsp_data(mem_rsp_rdata),
.m_rsp_err(mem_rsp_err),
.idle(dma_bus_idle));
endmodule
`default_nettype wire
