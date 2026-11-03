`timescale 1ns/1ps
// Same C driver talks to actual production RTL; no mock command/compute engine.
module tb_c_driver;
    reg clk=0; always #10 clk=~clk;
    reg rst_n=0,icb_cmd_valid=0,icb_cmd_read=0,icb_rsp_ready=0,external_abort_req=0;
    wire icb_cmd_ready,icb_rsp_valid,icb_rsp_err;
    reg [31:0] icb_cmd_addr=0,icb_cmd_wdata=0;
    reg [3:0] icb_cmd_wmask=15;
    wire [31:0] icb_rsp_rdata;
    wire busy,compute_done,task_done,fault,abort_pending,abort_done;
    wire [7:0] error_code;
    kwt_accelerator #(.SRAM_EMA(3'd2)) dut(.*);
    reg [4095:0] request_path,response_path;
    integer req, rsp, rc, rd, offset, mutation=0, altered=0, guard;
    integer cycles=0, transactions=0, responses=0, result_reads=0, status_reads=0;
    reg [31:0] value, result;
    reg error;
    always @(posedge clk) begin
        cycles=cycles+1;
        if(cycles>4000000) $fatal(1,"RTL driver watchdog");
    end
    initial begin
        if (!$value$plusargs("request=%s",request_path) ||
            !$value$plusargs("response=%s",response_path)) $fatal(1,"pipe paths missing");
        rc=$value$plusargs("mutation=%d",mutation);
        req=$fopen(request_path,"r"); rsp=$fopen(response_path,"w");
        if(!req||!rsp) $fatal(1,"pipe open failed");
        repeat(4) @(negedge clk); rst_n=1;
        forever begin
            // No trailing whitespace: a FIFO scan would wait for the NEXT
            // request's first non-space before returning this request.
            rc=$fscanf(req,"%d %h %h",rd,offset,value);
            if(rc!=3) $fatal(1,"bad request");
            if(rd==2) begin
                if(transactions!=responses) $fatal(1,"missing responses");
                $display("RTL_DRIVER_DONE cycles=%0d transactions=%0d result_reads=%0d mutation=%0d altered=%0d",cycles,transactions,result_reads,mutation,altered);
                $finish;
            end
            @(negedge clk);icb_cmd_valid=1;icb_cmd_read=rd;
            icb_cmd_addr=32'h11000000+offset;icb_cmd_wdata=value;
            guard=0;
            @(posedge clk);while(!icb_cmd_ready)begin
                @(posedge clk);guard=guard+1;if(guard>1000)$fatal(1,"cmd timeout");
            end
            transactions=transactions+1;
            @(negedge clk);icb_cmd_valid=0;
            guard=0;
            while(!icb_rsp_valid)begin
                @(negedge clk);guard=guard+1;if(guard>1000)$fatal(1,"rsp timeout");
            end
            result=icb_rsp_rdata;error=icb_rsp_err;
            if(rd==1 && offset=='h30) result_reads=result_reads+1;
            if(rd==1 && offset=='h00) status_reads=status_reads+1;
            // Mutate only at response boundary, never compute expectations here.
            if(rd==1 && !altered)begin
                if(mutation==1 && offset=='h30)begin result=result^1;altered=1;end
                if(mutation==2 && offset=='h28)begin result=result+1;altered=1;end
                if(mutation==3 && offset=='h00)begin result=result|'h10;altered=1;end
                if(mutation==4 && offset=='h2c && result_reads>0)begin result=result+1;altered=1;end
            end
            if(mutation==5 && rd==1 && offset=='h00 && status_reads>1)begin result=result&~1;altered=1;end
            icb_rsp_ready=1;@(posedge clk);responses=responses+1;
            @(negedge clk);icb_rsp_ready=0;
            $fdisplay(rsp,"%08h %0d",result,error);$fflush(rsp);
        end
    end
endmodule
