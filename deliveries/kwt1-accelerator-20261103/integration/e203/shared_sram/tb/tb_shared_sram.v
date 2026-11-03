`timescale 1ns/1ps
`default_nettype none
`ifndef KWT_TEST_EMA
`define KWT_TEST_EMA 2
`endif
`ifndef KWT_TEST_EMAW
`define KWT_TEST_EMAW 0
`endif
module tb_shared_sram;
    localparam [31:0] BASE=32'ha0000000;
    reg clk=0;always #10 clk=~clk;
    reg rst_n=0,cmd_valid=0,cmd_read=1,rsp_ready=0;
    reg [31:0] cmd_addr=BASE,cmd_wdata=0;
    reg [3:0] cmd_wmask=0;
    wire cmd_ready,rsp_valid,rsp_err;
    wire [31:0] rsp_rdata;
    kwt_shared_sram #(.BASE_ADDR(BASE),.SRAM_EMA(`KWT_TEST_EMA),.SRAM_EMAW(`KWT_TEST_EMAW)) dut(
        .clk(clk),.rst_n(rst_n),.icb_cmd_valid(cmd_valid),.icb_cmd_ready(cmd_ready),
        .icb_cmd_addr(cmd_addr),.icb_cmd_read(cmd_read),.icb_cmd_wdata(cmd_wdata),
        .icb_cmd_wmask(cmd_wmask),.icb_rsp_valid(rsp_valid),.icb_rsp_ready(rsp_ready),
        .icb_rsp_rdata(rsp_rdata),.icb_rsp_err(rsp_err));
    reg [31:0] golden[0:131071];
    integer requests=0,responses=0,holds=0,errors=0,read_checks=0,mask_cases=0;
    integer phase,index,bank,edge_id,mask_id,j,lane,word_index;
    integer quick=0,corrupt_first=0,words_per_sweep;
    reg [31:0] value,expected;
    always @(posedge clk) if(rst_n)begin
        if(cmd_valid&&cmd_ready)requests=requests+1;
        if(rsp_valid&&rsp_ready)responses=responses+1;
    end
    initial begin #200000000;$fatal(1,"Shared SRAM watchdog");end

    function [31:0] pattern;
        input integer pos,kind;
        begin
            pattern=(pos*32'h00010003)^32'h5ac36917;
            if(kind!=0)pattern=~pattern;
        end
    endfunction
    function integer mapped_word;
        input integer pos;
        begin
            if(quick)mapped_word=(pos/2)*4096+((pos%2)?4095:0);
            else mapped_word=pos;
        end
    endfunction
    task falling;
        begin @(negedge clk);#1;end
    endtask
    task transact;
        input rd;
        input [31:0] addr,data;
        input [3:0] byte_mask;
        input [31:0] want;
        input want_error;
        input integer stall;
        integer wait_count,n;
        reg [31:0] comparison;
        begin
            falling;cmd_valid=1;cmd_read=rd;cmd_addr=addr;cmd_wdata=data;
            cmd_wmask=byte_mask;rsp_ready=0;
            @(posedge clk);wait_count=0;
            while(!cmd_ready)begin
                @(posedge clk);wait_count=wait_count+1;
                if(wait_count>30)$fatal(1,"Shared command timeout");
            end
            falling;cmd_valid=0;
            // 接受后故意改变当前地址，返回必须使用保存的组和行标签。
            cmd_addr=BASE+((addr^32'h00040000)&32'h0007ffff);
            wait_count=0;
            while(!rsp_valid)begin
                falling;wait_count=wait_count+1;
                if(wait_count>30)$fatal(1,"Shared response timeout");
            end
            comparison=want;
            if(rd&&!want_error&&corrupt_first&&read_checks==0)comparison=want^32'h1;
            for(n=0;n<stall;n=n+1)begin
                if(cmd_ready!==0)$fatal(1,"Accepted next request while response held");
                if(rsp_rdata!==comparison||rsp_err!==want_error)begin
                    $display("FAIL SHARED_SRAM_READ addr=%h actual=%h expected=%h err=%b",addr,rsp_rdata,comparison,rsp_err);
                    $fatal(1,"Held response mismatch");
                end
                holds=holds+1;falling;
            end
            cmd_valid=0;
            if(rsp_rdata!==comparison||rsp_err!==want_error)begin
                $display("FAIL SHARED_SRAM_READ addr=%h actual=%h expected=%h err=%b",addr,rsp_rdata,comparison,rsp_err);
                $fatal(1,"Shared read/mask/address/return mismatch or X");
            end
            if(rd&&!want_error)read_checks=read_checks+1;
            if(want_error)errors=errors+1;
            rsp_ready=1;@(posedge clk);falling;rsp_ready=0;
        end
    endtask
    task write_word;
        input integer pos;
        input [31:0] data;
        input [3:0] byte_mask;
        input integer offset,stall;
        integer k;
        begin
            transact(0,BASE+pos*4+offset,data,byte_mask,0,0,stall);
            for(k=0;k<4;k=k+1)if(byte_mask[k])golden[pos][k*8+:8]=data[k*8+:8];
        end
    endtask
    task read_word;
        input integer pos,offset,stall;
        begin transact(1,BASE+pos*4+offset,0,0,golden[pos],0,stall);end
    endtask
    task cancel_wait;
        input rd;
        input [31:0] data;
        begin
            falling;cmd_valid=1;cmd_read=rd;cmd_addr=BASE;cmd_wdata=data;cmd_wmask=4'hf;rsp_ready=0;
            @(posedge clk);while(!cmd_ready)@(posedge clk);
            // 请求已接受，下一采样沿尚未接收后端返回，此时异步控制复位。
            falling;cmd_valid=0;rst_n=0;
            if(!rd)golden[0]=data;
            repeat(3)falling;
            if(rsp_valid!==0||cmd_ready!==0)$fatal(1,"WAIT_MEM reset failed");
            rst_n=1;read_word(0,0,0);
        end
    endtask
    task queued_reads;
        begin
            falling;cmd_valid=1;cmd_read=1;cmd_addr=BASE;cmd_wmask=0;rsp_ready=0;
            @(posedge clk);while(!cmd_ready)@(posedge clk);
            // 第一笔接受后立即提供第二笔，合法地保持valid和载荷直到它被接受。
            falling;cmd_addr=BASE+32'h7fffc;
            while(!rsp_valid)falling;
            for(j=0;j<3;j=j+1)begin
                if(cmd_ready!==0||rsp_rdata!==golden[0]||rsp_err!==0)$fatal(1,"Queued first response changed");
                holds=holds+1;falling;
            end
            read_checks=read_checks+1;rsp_ready=1;@(posedge clk);falling;
            @(posedge clk);if(cmd_ready!==1)$fatal(1,"Queued command not accepted after retirement");
            falling;cmd_valid=0;rsp_ready=0;
            while(!rsp_valid)falling;
            if(rsp_rdata!==golden[131071]||rsp_err!==0)$fatal(1,"Queued second response mismatch");
            read_checks=read_checks+1;rsp_ready=1;@(posedge clk);falling;rsp_ready=0;
        end
    endtask
    initial begin
        quick=$test$plusargs("quick");corrupt_first=$test$plusargs("corrupt_first");
        words_per_sweep=quick?64:131072;
        repeat(4)falling;rst_n=1;
        for(phase=0;phase<2;phase=phase+1)begin
            for(index=0;index<words_per_sweep;index=index+1)begin
                word_index=mapped_word(index);
                write_word(word_index,pattern(word_index,phase),4'hf,0,0);
            end
            for(index=0;index<words_per_sweep;index=index+1)begin
                word_index=mapped_word(index);read_word(word_index,0,0);
            end
        end
        // 每个组的首尾交替访问，遍历16种字节使能和所有字节地址低位。
        for(bank=0;bank<32;bank=bank+1)begin
            for(mask_id=0;mask_id<16;mask_id=mask_id+1)begin
                word_index=bank*4096+((mask_id%2)?4095:0);
                value=32'h96a53c78^(bank*32'h01030507)^(mask_id*32'h11223344);
                write_word(word_index,value,mask_id,mask_id%4,mask_id%3);
                read_word(word_index,(mask_id+1)%4,(mask_id+1)%4);mask_cases=mask_cases+1;
            end
        end
        transact(0,BASE-1,32'hffffffff,4'hf,0,1,2);
        transact(1,BASE+32'h80000,0,0,0,1,3);
        transact(0,BASE+32'h80000,32'hffffffff,4'hf,0,1,1);
        read_word(0,0,2);read_word(131071,3,2);

        // 写已落入宏但响应尚未退休时复位，取消响应，不清已写数据。
        falling;cmd_valid=1;cmd_read=0;cmd_addr=BASE;cmd_wdata=32'hfeedface;cmd_wmask=4'hf;rsp_ready=0;
        @(posedge clk);while(!cmd_ready)@(posedge clk);
        falling;cmd_valid=0;while(!rsp_valid)falling;
        rst_n=0;golden[0]=32'hfeedface;
        repeat(3)falling;
        if(rsp_valid!==0||cmd_ready!==0)$fatal(1,"Reset response/request not canceled");
        rst_n=1;read_word(0,0,3);
        cancel_wait(1,0);cancel_wait(0,32'h12345678);queued_reads;
        for(index=0;index<words_per_sweep;index=index+1)begin
            word_index=mapped_word(index);read_word(word_index,0,0);
        end
        if(requests!=responses+3||errors!=3||mask_cases!=512||holds==0)$fatal(1,"Shared coverage/accounting mismatch");
        $display("PASS SHARED_SRAM words=131072 macros=64 full_sweeps=%0d initialized_words=%0d requests=%0d responses=%0d read_checks=%0d holds=%0d errors=%0d canceled=3 wait_resets=2 queued_reads=2 mask_cases=%0d ema=%0d emaw=%0d period_ns=20",
                 quick?0:2,words_per_sweep,requests,responses,read_checks,holds,errors,mask_cases,`KWT_TEST_EMA,`KWT_TEST_EMAW);
        $finish;
    end
endmodule
`default_nettype wire
