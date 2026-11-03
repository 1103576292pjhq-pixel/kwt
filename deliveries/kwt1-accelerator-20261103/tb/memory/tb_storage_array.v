`timescale 1ns/1ps
`include "kwt_storage_config.vh"
`default_nettype none

// 物理存储实体自检：分别驱动24颗宏的原生接口，检查数据打包及逐位写掩码。
// 本TB不依赖wrapper，不假设待机Q一定保持；只检查合法读及连续写的已知Q。
module tb_storage_array;
    parameter real CLK_HALF=10.0;
    reg clk=0;always #(CLK_HALF)clk=~clk;
    reg rst_n=0;
    reg [7:0] x_cen='1,x_gwen='1;
    reg [127:0] x_wen='1,x_write=0;reg [79:0] x_a=0;wire [127:0] x_read;
    reg [15:0] w_cen='1,w_gwen='1;
    reg [255:0] w_wen='1,w_write=0;reg [111:0] w_a=0;wire [255:0] w_read;
    reg [2:0] sram_ema=0;reg [1:0] sram_emaw=0;reg sram_ret1n=1;
    reg bias_wr_en=0,bias_wr_slot=0,bias_rd_slot=0;
    reg [3:0] bias_wr_addr=0,bias_rd_addr=0;reg signed [31:0] bias_wr_data=0;
    wire signed [31:0] bias_rd_data;
    kwt_storage_array dut(.*);
    reg [15:0] golden_x[0:8191],golden_w[0:2047];
    reg known_x[0:8191],known_w[0:2047];
    reg [15:0] last_x_q[0:7],last_w_q[0:15],expected_x[0:7],expected_w[0:15];
    reg [7:0] known_x_q=0,check_x;
    reg [15:0] known_w_q=0,check_w;
    integer i,b,bit_index,cycles=0,x_reads=0,w_reads=0,writes=0,masked_writes=0,q_hold_checks=0,reads_after_standby=0;
    integer trace_fd=0;reg [4095:0] trace_path,vcd_path;
    task fail;input [1023:0] reason;begin $display("FAIL STORAGE_ARRAY cycle=%0d: %0s",cycles,reason);$fatal(1);end endtask
    function [15:0] pattern;input integer bank,address,kind;begin pattern=((address*37)^(bank*16'h6719)^16'h9a53)^(kind*16'h24bd);end endfunction
    task idle;begin x_cen='1;x_gwen='1;x_wen='1;w_cen='1;w_gwen='1;w_wen='1;bias_wr_en=0;end endtask
    task step;
        integer p,a,idx;
        reg [15:0] m,d;
        begin
            @(posedge clk);cycles=cycles+1;check_x=0;check_w=0;
            for(p=0;p<8;p=p+1)begin
                a=x_a[p*10+:10];idx=p*1024+a;
                if(!rst_n||x_cen[p])known_x_q[p]=0;
                else if(x_gwen[p])begin
                    if(!known_x[idx])fail("TB read unwritten physical X");
                    expected_x[p]=golden_x[idx];check_x[p]=1;last_x_q[p]=golden_x[idx];known_x_q[p]=1;x_reads=x_reads+1;
                end else begin
                    expected_x[p]=last_x_q[p];check_x[p]=known_x_q[p];if(check_x[p])q_hold_checks=q_hold_checks+1;
                    m=x_wen[p*16+:16];d=x_write[p*16+:16];
                    golden_x[idx]=(golden_x[idx]&m)|(d&~m);if(m==0)known_x[idx]=1;
                    writes=writes+1;if(m!=0&&m!=16'hffff)masked_writes=masked_writes+1;
                end
            end
            for(p=0;p<16;p=p+1)begin
                a=w_a[p*7+:7];idx=p*128+a;
                if(!rst_n||w_cen[p])known_w_q[p]=0;
                else if(w_gwen[p])begin
                    if(!known_w[idx])fail("TB read unwritten physical W");
                    expected_w[p]=golden_w[idx];check_w[p]=1;last_w_q[p]=golden_w[idx];known_w_q[p]=1;w_reads=w_reads+1;
                end else begin
                    expected_w[p]=last_w_q[p];check_w[p]=known_w_q[p];if(check_w[p])q_hold_checks=q_hold_checks+1;
                    m=w_wen[p*16+:16];d=w_write[p*16+:16];
                    golden_w[idx]=(golden_w[idx]&m)|(d&~m);if(m==0)known_w[idx]=1;
                    writes=writes+1;if(m!=0&&m!=16'hffff)masked_writes=masked_writes+1;
                end
            end
            // 宏可有非零访问延时，采样留在下一个上升沿之前，不把Q当零延时组合读。
            #(CLK_HALF-1.0);
            for(p=0;p<8;p=p+1)if(check_x[p])begin
                if(x_read[p*16+:16]!==expected_x[p])begin
                    $display("physical X id=%0d addr=%0d got=%h expected=%h",p,x_a[p*10+:10],x_read[p*16+:16],expected_x[p]);fail("physical X read/write-thru");
                end
                if(trace_fd&&x_gwen[p])$fdisplay(trace_fd,"AXR %0d %0d %0d %h",cycles,p,x_a[p*10+:10],x_read[p*16+:16]);
            end
            for(p=0;p<16;p=p+1)if(check_w[p])begin
                if(w_read[p*16+:16]!==expected_w[p])fail("physical W read/write-thru");
                if(trace_fd&&w_gwen[p])$fdisplay(trace_fd,"AWR %0d %0d %0d %h",cycles,p,w_a[p*7+:7],w_read[p*16+:16]);
            end
            @(negedge clk);#1;
        end
    endtask
    task read_all;
        begin
            idle;
            for(i=0;i<1024;i=i+1)begin
                x_cen=0;x_gwen='1;w_cen=i<128?0:16'hffff;w_gwen='1;
                for(b=0;b<8;b=b+1)x_a[b*10+:10]=i;
                for(b=0;b<16;b=b+1)w_a[b*7+:7]=i%128;
                step;
            end
            idle;step;
        end
    endtask
    initial begin
        for(i=0;i<8192;i=i+1)known_x[i]=0;
        for(i=0;i<2048;i=i+1)known_w[i]=0;
        if($value$plusargs("trace=%s",trace_path))begin trace_fd=$fopen(trace_path,"w");if(!trace_fd)fail("trace open");end
        if($value$plusargs("vcd=%s",vcd_path))begin $dumpfile(vcd_path);$dumpvars(0,dut);end
        step;step;rst_n=1;
        // 每颗宏的每个物理地址都写入不同模式；这包括X物理宏中未供逻辑bank使用的容量。
        for(i=0;i<1024;i=i+1)begin
            x_cen=0;x_gwen=0;x_wen=0;w_cen=i<128?0:16'hffff;w_gwen=0;w_wen=0;
            for(b=0;b<8;b=b+1)begin x_a[b*10+:10]=i;x_write[b*16+:16]=pattern(b,i,0);end
            for(b=0;b<16;b=b+1)begin w_a[b*7+:7]=i%128;w_write[b*16+:16]=pattern(b,i,1);end
            step;
        end
        read_all;
        // 遍历16个写掩码位：先读出已知Q，再写单个位，再读取，检查写时Q保持。
        for(bit_index=0;bit_index<16;bit_index=bit_index+1)begin
            x_cen=0;w_cen=0;x_gwen='1;w_gwen='1;
            for(b=0;b<8;b=b+1)x_a[b*10+:10]=(b*113+bit_index*17)%1024;
            for(b=0;b<16;b=b+1)w_a[b*7+:7]=(b*19+bit_index*7)%128;
            step;
            x_gwen=0;w_gwen=0;
            for(b=0;b<8;b=b+1)begin
                x_wen[b*16+:16]=~(16'h0001<<bit_index);x_write[b*16+:16]=~last_x_q[b];
            end
            for(b=0;b<16;b=b+1)begin
                w_wen[b*16+:16]=~(16'h0001<<bit_index);w_write[b*16+:16]=~last_w_q[b];
            end
            step;x_gwen='1;w_gwen='1;x_wen=0;w_wen=0;step; // 读周期忽略写掩码
            x_gwen=0;w_gwen=0;x_wen='1;w_wen='1;x_write='1;w_write='1;step; // 全1掩码禁止各位写入
            x_gwen='1;w_gwen='1;step;
        end
        // CEN禁用时即使GWEN/WEN表示写，也不能改数据；不要求待机Q保持。
        x_cen='1;w_cen='1;x_gwen=0;w_gwen=0;x_wen=0;w_wen=0;x_a=0;w_a=0;x_write='1;w_write='1;step;
        x_cen=0;w_cen=0;x_gwen='1;w_gwen='1;
        reads_after_standby=-(x_reads+w_reads);step;
        reads_after_standby=reads_after_standby+x_reads+w_reads;
        // 复位覆盖写请求；之后全量回读，检查RAM没有被误写或清零。
        rst_n=0;x_cen=0;w_cen=0;x_gwen=0;w_gwen=0;x_wen=0;w_wen=0;x_write=0;w_write=0;step;step;
        idle;rst_n=1;read_all;
        if(masked_writes!=384 || q_hold_checks==0 || reads_after_standby!=24)fail("physical coverage");
        $display("PASS STORAGE_ARRAY cycles=%0d x_reads=%0d w_reads=%0d writes=%0d masked_writes=%0d q_hold_checks=%0d reads_after_standby=%0d",cycles,x_reads,w_reads,writes,masked_writes,q_hold_checks,reads_after_standby);
        if(trace_fd)$fclose(trace_fd);$finish;
    end
endmodule
`default_nettype wire
