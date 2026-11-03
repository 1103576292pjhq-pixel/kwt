`timescale 1ns/1ps
`include "kwt_icb_config.vh"
// 完成状态读回回归：真实task_done在总线访问时受transport_empty抑制。
// 若仅把实时task_done直接拼入STATUS，CPU会永远读不到它曾经完成。
module tb_icb_completion;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,icb_cmd_valid=0,icb_rsp_ready=0;
    wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err,transport_empty;
    wire [31:0] icb_rsp_rdata;
    wire task_done=transport_empty;
    kwt_icb_regs dut(
        .clk(clk),.rst_n(rst_n),.icb_cmd_valid(icb_cmd_valid),.icb_cmd_ready(icb_cmd_ready),
        .icb_cmd_addr(`KWT_ICB_DEFAULT_BASE),.icb_cmd_read(1'b1),.icb_cmd_wdata(32'd0),.icb_cmd_wmask(4'hf),
        .icb_rsp_valid(icb_rsp_valid),.icb_rsp_ready(icb_rsp_ready),.icb_rsp_rdata(icb_rsp_rdata),.icb_rsp_err(icb_rsp_err),
        .command_ready(1'b1),.result_req_ready(1'b1),.result_rsp_valid(1'b0),.result_rsp_data(32'd0),.result_rsp_error(1'b0),
        .busy(!task_done),.compute_done(1'b1),.task_done(task_done),.fault(1'b0),.error_code(8'd0),
        .block_valid(1'b0),.block_read_complete(1'b0),.block_task_id(32'd0),.block_row(7'd0),.block_tile(4'd0),
        .block_count(7'd0),.block_sequence(9'd0),.block_cursor(7'd0),
        .abort_pending(1'b0),.abort_done(1'b0),.external_abort_req(1'b0),.transport_empty(transport_empty)
    );
    initial begin
        repeat(3)@(negedge clk);rst_n=1;repeat(3)@(negedge clk);
        icb_cmd_valid=1;@(posedge clk);if(!icb_cmd_ready)$fatal(1,"FAIL COMPLETION not ready");
        @(negedge clk);icb_cmd_valid=0;
        if(!icb_rsp_valid||icb_rsp_err||!icb_rsp_rdata[3]||icb_rsp_rdata[1])
            $fatal(1,"FAIL COMPLETION STATUS completion unreadable %h",icb_rsp_rdata);
        repeat(5)@(negedge clk);icb_rsp_ready=1;@(posedge clk);@(negedge clk);
        $display("PASS ICB_COMPLETION reads=1 holds=5");$finish;
    end
endmodule
