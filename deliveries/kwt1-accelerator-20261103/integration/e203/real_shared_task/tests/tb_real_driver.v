`timescale 1ns/1ps
module tb_shared_task_driver;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,valid=0,read_mode=0,ready=0;
    reg [31:0] address=0,data=0;reg [3:0] mask=15;
    wire select_ram=(address[31:19]==13'h1400);
    wire acc_ready,acc_rsp_valid,acc_err,ram_ready,ram_rsp_valid,ram_err;
    wire [31:0] acc_data,ram_data;
    wire cmd_ready=select_ram?ram_ready:acc_ready;
    wire rsp_valid=select_ram?ram_rsp_valid:acc_rsp_valid;
    wire [31:0] rsp_data=select_ram?ram_data:acc_data;
    wire rsp_error=select_ram?ram_err:acc_err;
    kwt_accelerator #(.SRAM_EMA(3'd2)) acc(
      .clk(clk),.rst_n(rst_n),.icb_cmd_valid(valid&&!select_ram),.icb_cmd_ready(acc_ready),
      .icb_cmd_addr(address),.icb_cmd_read(read_mode),.icb_cmd_wdata(data),.icb_cmd_wmask(mask),
      .icb_rsp_valid(acc_rsp_valid),.icb_rsp_ready(ready&&!select_ram),.icb_rsp_rdata(acc_data),.icb_rsp_err(acc_err),
      .external_abort_req(1'b0),.busy(),.compute_done(),.task_done(),.fault(),.error_code(),.abort_pending(),.abort_done());
    wire load_done,load_mode,load_reset,load_valid,load_read,load_rsp_ready;
    wire [31:0] load_addr,load_data;wire [3:0] load_mask;
    kwt_real_loader loader(.clk(clk),.done(load_done),.mode(load_mode),.reset_n(load_reset),
      .cmd_valid(load_valid),.cmd_ready(ram_ready),.cmd_addr(load_addr),.cmd_read(load_read),
      .cmd_wdata(load_data),.cmd_wmask(load_mask),.rsp_valid(ram_rsp_valid),.rsp_ready(load_rsp_ready),.rsp_err(ram_err),.rsp_rdata(ram_data));
    kwt_shared_sram ram(
      .clk(clk),.rst_n(load_mode?load_reset:rst_n),.icb_cmd_valid(load_mode?load_valid:valid&&select_ram),.icb_cmd_ready(ram_ready),
      .icb_cmd_addr(load_mode?load_addr:address),.icb_cmd_read(load_mode?load_read:read_mode),.icb_cmd_wdata(load_mode?load_data:data),.icb_cmd_wmask(load_mode?load_mask:mask),
      .icb_rsp_valid(ram_rsp_valid),.icb_rsp_ready(load_mode?load_rsp_ready:ready&&select_ram),.icb_rsp_rdata(ram_data),.icb_rsp_err(ram_err));
    reg [4095:0] req_path,rsp_path,trace_path;
    integer req,rsp,trace,rc,rd,mutation=0,altered=0,guard;
    integer cycles=0,transactions=0,result_reads=0,shared_reads=0,shared_writes=0,y_writes=0,y_reads=0;
    reg [31:0] addr,value,result;reg error;
    always @(posedge clk)begin cycles=cycles+1;if(cycles>4000000)$fatal(1,"Shared C-driver watchdog");end
    initial begin
        if(!$value$plusargs("request=%s",req_path)||!$value$plusargs("response=%s",rsp_path)||
           !$value$plusargs("trace=%s",trace_path))$fatal(1,"Missing pipe/trace paths");
        rc=$value$plusargs("mutation=%d",mutation);
        req=$fopen(req_path,"r");rsp=$fopen(rsp_path,"w");trace=$fopen(trace_path,"w");
        if(!req||!rsp||!trace)$fatal(1,"Pipe/trace open");
        wait(load_done);repeat(4)@(negedge clk);#1;rst_n=1;
        forever begin
            rc=$fscanf(req,"%d %h %h",rd,addr,value);
            if(rc!=3)$fatal(1,"Bad pipe request");
            if(rd==2)begin
                $display("SHARED_DRIVER_DONE cycles=%0d transactions=%0d result_reads=%0d shared_reads=%0d shared_writes=%0d y_writes=%0d y_reads=%0d mutation=%0d altered=%0d",
                    cycles,transactions,result_reads,shared_reads,shared_writes,y_writes,y_reads,mutation,altered);
                $fclose(trace);$finish;
            end
            @(negedge clk);#1;valid=1;read_mode=rd;address=addr;data=value;mask=15;
            if(addr>=32'ha0020000&&addr<32'ha0038c00&&rd==0&&value!=32'hdeadbeef)begin
                y_writes=y_writes+1;
                // 负向：首项结果写入仍握手成功，但禁止写所有字节，保留poison。
                if(mutation==1&&!altered)begin mask=0;altered=1;end
            end
            @(posedge clk);guard=0;
            while(!cmd_ready)begin @(posedge clk);guard=guard+1;if(guard>1000)$fatal(1,"Command timeout");end
            transactions=transactions+1;
            @(negedge clk);#1;valid=0;guard=0;
            while(!rsp_valid)begin @(negedge clk);#1;guard=guard+1;if(guard>1000)$fatal(1,"Response timeout");end
            result=rsp_data;error=rsp_error;
            if(rd==1&&addr==32'h11000030)result_reads=result_reads+1;
            if(addr[31:19]==13'h1400)begin
                if(rd==1)shared_reads=shared_reads+1;else shared_writes=shared_writes+1;
                if(rd==1&&addr>=32'ha0020000&&addr<32'ha0038c00)begin
                    y_reads=y_reads+1;$fdisplay(trace,"Y %0d %08h",(addr-32'ha0020000)/4,result);
                end
            end
            ready=1;@(posedge clk);@(negedge clk);#1;ready=0;
            $fdisplay(rsp,"%08h %0d",result,error);$fflush(rsp);
        end
    end
endmodule
