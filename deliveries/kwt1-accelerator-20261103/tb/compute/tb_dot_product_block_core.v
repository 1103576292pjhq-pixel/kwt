`timescale 1ns/1ps
`include "kwt_compute_config.vh"
`default_nettype none

// 顶层自检：只通过公开端口供数/核对，不读取DUT内部acc或状态机。
// Python把整数黄金结果写入向量；TB负责真实的逐拍握手和协议检查。
module tb_dot_product_block_core;
    reg clk=0;
    always #5 clk=~clk;
    reg rst_n=0, start_valid=0, in_valid=0, out_ready=0;
    reg [3:0] start_row_mask=0;
    reg start_is_final_block=0;
    reg [63:0] in_x=0, in_w=0;
    wire start_ready, in_ready, out_valid, out_block_last, busy, block_done;
    wire [3:0] bias_addr;
    wire signed [15:0] out_y;
    wire [2:0] out_flags;
    wire [5:0] out_index;
    reg signed [31:0] bias [0:15];
    wire signed [31:0] bias_data=bias[bias_addr];
    dot_product_block_core dut (
        .clk(clk), .rst_n(rst_n), .start_valid(start_valid), .start_ready(start_ready),
        .start_row_mask(start_row_mask), .start_is_final_block(start_is_final_block),
        .in_valid(in_valid), .in_ready(in_ready), .in_x(in_x), .in_w(in_w),
        .bias_addr(bias_addr), .bias_data(bias_data), .out_valid(out_valid),
        .out_ready(out_ready), .out_y(out_y), .out_flags(out_flags),
        .out_index(out_index), .out_block_last(out_block_last), .busy(busy), .block_done(block_done)
    );

    reg [63:0] xs[0:255], ws[0:255];
    reg [15:0] expected_y[0:63];
    reg [2:0] expected_flags[0:63];
    reg [63:0] seen;
    reg active=0, held=0, previous_done=0;
    reg [26:0] held_payload;
    integer fd, trace_fd, rc, id, mask, final_block, mode, rows, last_index;
    integer i, guard, accepted=0, consumed=0, done_seen=0, block_stalls=0, final_stalls=0;
    integer cycles=0, total_inputs=0, total_outputs=0, total_stalls=0;
    integer completed=0, canceled=0, reset_count=0, blocks=0, full_rate_blocks=0;
    integer expected_index, expected_last, drain_cycle, first_cycle, last_cycle;
    reg [4095:0] vectors_path, trace_path;

    task fail;
        input [1023:0] reason;
        begin
            $display("FAIL block=%0d cycle=%0d accepted=%0d consumed=%0d: %0s",
                     id,cycles,accepted,consumed,reason);
            $fatal(1);
        end
    endtask

    // 在上升沿之前的稳定值上统计握手，#1之后才允许驱动下一拍。
    // 因此不会把非阻塞赋值更新后的valid误当成本沿已接收的数据。
    task step;
        begin
            @(posedge clk);
            cycles=cycles+1;
            if (!rst_n) begin
                active=0;
                held=0;
                previous_done=0;
            end else begin
                if (held && ({out_valid,out_y,out_flags,out_index,out_block_last} !== held_payload))
                    fail("backpressure payload/valid changed");
                if (block_done && previous_done) fail("block_done longer than one cycle");
                previous_done=block_done;
                if (start_ready !== !busy) fail("start_ready/busy inconsistent");
                if (active && start_ready) fail("accepted start while busy");
                if (in_ready && (!active || accepted>=256)) fail("unexpected operand ready");
                if (start_valid && start_ready) begin
                    if (active) fail("overlapping blocks");
                    active=1;
                    $fdisplay(trace_fd,"START %0d",id);
                end
                if (in_valid && in_ready) begin
                    if (in_x !== xs[accepted] || in_w !== ws[accepted]) fail("driver operand order");
                    if (accepted==0) first_cycle=cycles;
                    last_cycle=cycles;
                    accepted=accepted+1;
                    total_inputs=total_inputs+1;
                end
                if (out_valid) begin
                    if (!active || accepted!=256 || !busy) fail("output before complete input block");
                    if (out_index >= rows*16) fail("invalid masked output row");
                    // acc遍历{g,p,q}，输出位置为{p,g,q}，不能假定位置0..63递增。
                    expected_index=(consumed/(rows*4))*4+((consumed/4)%rows)*16+consumed%4;
                    if (out_index !== expected_index[5:0]) fail("output order/index mapping");
                    if (seen[out_index]) fail("duplicate output index");
                    if (out_y !== expected_y[out_index] || out_flags !== expected_flags[out_index]) begin
                        $display("index=%0d got y=%0d flags=%h expected y=%0d flags=%h",
                            out_index,$signed(out_y),out_flags,$signed(expected_y[out_index]),expected_flags[out_index]);
                        fail("golden Y/flags mismatch");
                    end
                    expected_last=(out_index==last_index);
                    if (out_block_last !== expected_last[0]) fail("block_last position");
                    if (bias_addr !== out_index[3:0]) fail("bias column mapping");
                    if (out_ready) begin
                        seen[out_index]=1;
                        consumed=consumed+1;
                        total_outputs=total_outputs+1;
                        $fdisplay(trace_fd,"OUTPUT %0d %0d %04h %01h %0d",id,out_index,out_y,out_flags,out_block_last);
                    end else begin
                        block_stalls=block_stalls+1;
                        if (out_block_last) final_stalls=final_stalls+1;
                        total_stalls=total_stalls+1;
                    end
                end
                held=out_valid && !out_ready;
                held_payload={out_valid,out_y,out_flags,out_index,out_block_last};
                if (block_done) begin
                    if (!active || accepted!=256 || consumed!=rows*16 || !busy)
                        fail("early or unsolicited block_done");
                    for (i=0;i<rows*16;i=i+1)
                        if (!seen[i]) fail("missing output coverage");
                    done_seen=done_seen+1;
                    active=0;
                    completed=completed+1;
                    $fdisplay(trace_fd,"DONE %0d %0d %0d",id,accepted,consumed);
                end
            end
            #1;
        end
    endtask

    task reset_dut;
        begin
            @(negedge clk);
            rst_n=0; start_valid=0; in_valid=0; out_ready=0;
            step;
            step;
            @(negedge clk); rst_n=1;
            step;
            if (!start_ready || busy || out_valid || block_done) fail("reset did not return idle");
            reset_count=reset_count+1;
        end
    endtask

    task cancel_block;
        begin
            $fdisplay(trace_fd,"CANCEL %0d %0d %0d",id,accepted,consumed);
            canceled=canceled+1;
            reset_dut;
        end
    endtask

    task run_block;
        begin
            accepted=0; consumed=0; seen=0; done_seen=0; block_stalls=0; final_stalls=0;
            @(negedge clk);
            if (!start_ready) fail("not idle for next start");
            start_valid=1; start_row_mask=mask[3:0]; start_is_final_block=final_block[0];
            step;
            // 元数据只在start握手时采样；忙时故意保持另一份start请求数拍。
            @(negedge clk);
            start_row_mask=~mask[3:0]; start_is_final_block=~final_block[0];
            in_valid=1; in_x=xs[0]; in_w=ws[0];
            step; // CLEAR期间不应接收操作数
            guard=0;
            while (accepted<256 && !(mode==1 && accepted==37)) begin
                @(negedge clk);
                start_valid=(guard<5);
                // 首块无空拍，核对RUN确实可连续每拍接收；其他块插入确定性空拍。
                in_valid=(id==0 || guard%13!=4);
                in_x=xs[accepted]; in_w=ws[accepted];
                step;
                guard=guard+1;
                if (guard>400) fail("input handshake timeout");
            end
            if (mode==1) cancel_block;
            else begin
                if (id==0) begin
                    if (last_cycle-first_cycle!=255) fail("full-rate input took bubbles");
                    full_rate_blocks=full_rate_blocks+1;
                end
                guard=0; drain_cycle=0;
                // in_valid保留为1并放入毒值，验证第256组之后不会误收第257组。
                while (done_seen==0 && !((mode==2 || mode==3) && block_stalls>=7)) begin
                    @(negedge clk);
                    start_valid=0; in_valid=1; in_x=64'hdeadbeefdeadbeef; in_w=~in_x;
                    if (mode==2) out_ready=0;
                    else if (mode==3) out_ready=!(out_valid && out_block_last);
                    else begin
                        // 第一个和最后一个输出各阻塞至少7拍，中间间歇阻塞。
                        if ((consumed==0 && block_stalls<7) ||
                            (consumed==rows*16-1 && final_stalls<7))
                            out_ready=0;
                        else out_ready=(drain_cycle%11!=3 && drain_cycle%11!=4);
                    end
                    step;
                    drain_cycle=drain_cycle+1;
                    guard=guard+1;
                    if (guard>2000) fail("output/done timeout");
                end
                if (mode==2 || mode==3) begin
                    if (!out_valid || out_ready || done_seen!=0) fail("reset scenario missed pending output");
                    cancel_block;
                end else begin
                    if (done_seen!=1) fail("missing done pulse");
                    @(negedge clk); in_valid=0; out_ready=1;
                    step;
                    if (out_valid || block_done || busy || !start_ready) fail("extra output/done after completion");
                end
            end
        end
    endtask

    initial begin
        if (!$value$plusargs("vectors=%s",vectors_path)) $fatal(1,"missing vectors");
        if (!$value$plusargs("trace=%s",trace_path)) $fatal(1,"missing trace");
        fd=$fopen(vectors_path,"r"); trace_fd=$fopen(trace_path,"w");
        if (!fd || !trace_fd) $fatal(1,"cannot open fixture/trace");
        reset_dut;
        rc=$fscanf(fd,"%d %d %d %d\n",id,mask,final_block,mode);
        while (rc==4) begin
            if (mask!=15 && mask!=7) fail("fixture row mask");
            rows=(mask==15)?4:3;
            last_index=rows*16-1;
            for (i=0;i<16;i=i+1) begin
                rc=$fscanf(fd,"%h\n",bias[i]);
                if (rc!=1) fail("truncated bias fixture");
            end
            for (i=0;i<256;i=i+1) begin
                rc=$fscanf(fd,"%h %h\n",xs[i],ws[i]);
                if (rc!=2) fail("truncated operand fixture");
            end
            for (i=0;i<64;i=i+1) begin
                rc=$fscanf(fd,"%h %h\n",expected_y[i],expected_flags[i]);
                if (rc!=2) fail("truncated golden fixture");
            end
            run_block;
            blocks=blocks+1;
            rc=$fscanf(fd,"%d %d %d %d\n",id,mask,final_block,mode);
        end
        if (rc!=-1) fail("malformed trailing fixture");
        if (blocks==0) fail("empty test suite");
        $display("PASS_TOP blocks=%0d completed=%0d canceled=%0d inputs=%0d outputs=%0d stalls=%0d resets=%0d cycles=%0d full_rate=%0d",
            blocks,completed,canceled,total_inputs,total_outputs,total_stalls,reset_count,cycles,full_rate_blocks);
        $fclose(fd); $fclose(trace_fd); $finish;
    end
    initial begin #1000000000; $fatal(1,"watchdog timeout"); end
endmodule
`default_nettype wire
