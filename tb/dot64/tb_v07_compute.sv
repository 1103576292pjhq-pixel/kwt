`timescale 1ns/1ps
// 对照独立Python整数期望，检查所有累加位置、数值结果和输出协议。
module tb_v07_compute;
    localparam BLOCKS=39;
    reg clk=0;
    always #5 clk=~clk;
    reg rst_n=0, abort_i=0, block_start_i=0, block_release_i=0;
    reg in_valid_i=0;
    wire in_ready_o,block_ready_o,acc_ready_o,pipeline_empty_o;
    reg [63:0] x_i=0,w_i=0;
    reg [1:0] ctx_i=0;
    reg [3:0] row_mask_i=0;
    reg block_last_i=0;
    reg read_valid_i=0;
    wire read_ready_o;
    reg [1:0] sel_ctx_i=0,sel_row_i=0,sel_col_i=0;
    wire signed [47:0] selected_sum_o;
    reg signed [47:0] bias_i=0;
    reg [31:0] tag_i=0;
    reg last_i=0;
    wire out_valid_o;
    reg out_ready_i=0;
    wire signed [31:0] out_data_o;
    wire [31:0] out_tag_o;
    wire [2:0] out_flags_o;
    wire out_overflow_o,out_saturated_o,out_last_o;
    reg [63:0] xs[0:BLOCKS*256-1],ws[0:BLOCKS*256-1];
    reg [3:0] masks[0:BLOCKS-1];
    reg signed [47:0] sums[0:BLOCKS*64-1],biases[0:BLOCKS*16-1];
    reg signed [31:0] ys[0:BLOCKS*64-1];
    reg [2:0] flags[0:BLOCKS*64-1];
    integer blk,beat,pos,cycle,outputs=0,blocks_done=0;
    reg [31:0] held_tag;
    reg signed [31:0] held_data;
    reg [2:0] held_flags;
    reg was_stalled=0;
    reg force_stall=0;
    integer expected_tags[0:4095];
    integer queue_head=0,queue_tail=0;
    dot64_tile_core dut(.*);

    // 输出端用确定性背压；监视器在上升沿采样有效握手。
    always @(negedge clk) begin
        if(!rst_n || abort_i || force_stall) out_ready_i=0;
        else out_ready_i=(cycle%5==0 || cycle%5==4);
    end
    always @(posedge clk) begin
        if(!rst_n || abort_i) begin
            cycle=0;was_stalled=0;queue_head=0;queue_tail=0;
        end
        else begin
            cycle=cycle+1;
            // 以真正接收的请求排队，不能用返回tag自己挑选期望来掩盖乱序/重复。
            if(read_valid_i && read_ready_o) begin
                if(queue_tail>=4096) $fatal(1,"scoreboard queue overflow");
                expected_tags[queue_tail]=tag_i;
                queue_tail=queue_tail+1;
            end
            if(was_stalled && (!out_valid_o || out_data_o!==held_data ||
                 out_flags_o!==held_flags || out_tag_o!==held_tag))
                $fatal(1,"output changed under backpressure");
            was_stalled=out_valid_o && !out_ready_i;
            held_data=out_data_o;held_flags=out_flags_o;held_tag=out_tag_o;
            if(out_valid_o && out_ready_i) begin
                if(queue_head>=queue_tail || out_tag_o!==expected_tags[queue_head])
                    $fatal(1,"unexpected, repeated or reordered output tag=%0d",out_tag_o);
                queue_head=queue_head+1;
                if(out_tag_o>=BLOCKS*64 || out_data_o!==ys[out_tag_o] ||
                    out_flags_o!==flags[out_tag_o])
                    $fatal(1,"output tag=%0d got=%0d flags=%b expected=%0d/%b",
                        out_tag_o,out_data_o,out_flags_o,ys[out_tag_o],flags[out_tag_o]);
                if({out_last_o,out_saturated_o,out_overflow_o}!==out_flags_o)
                    $fatal(1,"flag sidebands disagree");
                outputs=outputs+1;
            end
        end
    end

    task start_block;
        begin
            @(negedge clk);
            if(block_ready_o!==1 || acc_ready_o!==0) $fatal(1,"not idle");
            block_start_i=1;
            @(negedge clk);block_start_i=0;
            wait(in_ready_o===1);
        end
    endtask

    task send_beat(input integer b,input integer n);
        begin
            @(negedge clk);
            x_i=xs[b*256+n];w_i=ws[b*256+n];ctx_i=n%4;
            row_mask_i=masks[b];block_last_i=(n==255);in_valid_i=1;
            @(posedge clk);
            if(in_ready_o!==1) $fatal(1,"unexpected input stall");
            #1;
            if(n==255 && acc_ready_o!==0) $fatal(1,"last input completed too early");
        end
    endtask

    task run_block(input integer b);
        integer n,p,r,c,old_outputs,expected_outputs;
        begin
            old_outputs=outputs;expected_outputs=0;
            start_block;
            for(n=0;n<256;n=n+1) begin
                // 非连续输入，以及每个k内部上下文交替之间的暂停。
                if(n%7==2) begin
                    @(negedge clk);in_valid_i=0;
                    repeat(2) @(negedge clk);
                end
                send_beat(b,n);
            end
            @(negedge clk);in_valid_i=0;block_last_i=0;
            wait(acc_ready_o===1);
            if(pipeline_empty_o!==1 || in_ready_o!==0) $fatal(1,"drain failed");
            // 读全部64个累加位置，包括未激活的尾行；不能串扰。
            for(p=0;p<64;p=p+1) begin
                r=p/16;c=p%16;
                @(negedge clk);sel_ctx_i=c/4;sel_row_i=r;sel_col_i=c%4;
                #1;
                if(selected_sum_o!==sums[b*64+p])
                    $fatal(1,"sum block=%0d row=%0d col=%0d expected=%0d got=%0d",
                         b,r,c,sums[b*64+p],selected_sum_o);
                if(masks[b][r]) begin
                    bias_i=biases[b*16+c];tag_i=b*64+p;
                    last_i=(b==BLOCKS-1 && p==63);read_valid_i=1;
                    // 请求遇到背压时保持地址、偏置和标签稳定。
                    @(posedge clk);
                    while(read_ready_o!==1) @(posedge clk);
                    #1;
                    @(negedge clk);read_valid_i=0;
                    expected_outputs=expected_outputs+1;
                end
            end
            wait(out_valid_o===0);
            @(negedge clk);
            if(outputs-old_outputs!=expected_outputs) $fatal(1,"output count mismatch");
            if(queue_head!=queue_tail) $fatal(1,"missing queued output");
            block_release_i=1;
            @(negedge clk);block_release_i=0;
            if(block_ready_o!==1) $fatal(1,"block not released");
            blocks_done=blocks_done+1;
        end
    endtask

    task cancel_and_check(input integer use_reset);
        begin
            @(negedge clk);in_valid_i=0;read_valid_i=0;block_start_i=0;block_release_i=0;
            if(use_reset) rst_n=0;else abort_i=1;
            @(posedge clk);#1;
            if(out_valid_o!==0 || acc_ready_o!==0 || pipeline_empty_o!==1)
                $fatal(1,"cancel left live result");
            @(negedge clk);rst_n=1;abort_i=0;#1;
            if(block_ready_o!==1) $fatal(1,"cancel not idle");
        end
    endtask

    initial begin
        cycle=0;
        if($test$plusargs("VCD")) begin
            $dumpfile("out/v07_compute.vcd");$dumpvars(0,tb_v07_compute);
        end
        $readmemh("out/v07-vectors/x.hex",xs);$readmemh("out/v07-vectors/w.hex",ws);
        $readmemh("out/v07-vectors/mask.hex",masks);$readmemh("out/v07-vectors/sum.hex",sums);
        $readmemh("out/v07-vectors/bias.hex",biases);$readmemh("out/v07-vectors/y.hex",ys);
        $readmemh("out/v07-vectors/flags.hex",flags);
        for(pos=0;pos<BLOCKS*64;pos=pos+1)
            if((^sums[pos]===1'bx)||(^ys[pos]===1'bx)||(^flags[pos]===1'bx))
                $fatal(1,"missing/unknown expected vector");
        repeat(2) @(negedge clk);rst_n=1;
        // 空闲时的读请求不应产生结果。
        read_valid_i=1;repeat(2) @(negedge clk);
        if(read_ready_o!==0 || out_valid_o!==0) $fatal(1,"read accepted before compute");
        read_valid_i=0;
        for(blk=0;blk<BLOCKS;blk=blk+1) run_block(blk);
        // 分别检查在途乘积、最后输入后的排空、结果阶段的中止恢复。
        start_block;send_beat(0,0);cancel_and_check(0);run_block(0);
        start_block;send_beat(0,0);cancel_and_check(1);run_block(1);
        start_block;
        for(beat=0;beat<256;beat=beat+1) send_beat(0,beat);
        cancel_and_check(0);run_block(2);
        start_block;
        for(beat=0;beat<256;beat=beat+1) send_beat(0,beat);
        wait(acc_ready_o);cancel_and_check(1);run_block(3);
        // 输出受阻时，提前release不能覆盖旧结果；中止后必须能重算。
        start_block;
        for(beat=0;beat<256;beat=beat+1) send_beat(0,beat);
        @(negedge clk);in_valid_i=0;block_last_i=0;
        wait(acc_ready_o);
        @(negedge clk);force_stall=1;
        @(negedge clk);read_valid_i=1;sel_ctx_i=0;sel_row_i=0;sel_col_i=0;
        bias_i=biases[0];tag_i=0;last_i=0;
        @(posedge clk);#1;
        if(out_valid_o!==1) $fatal(1,"blocked result setup failed");
        @(negedge clk);read_valid_i=0;block_release_i=1;
        repeat(2) begin
            @(posedge clk);#1;
            if(block_ready_o!==0 || acc_ready_o!==1 || out_valid_o!==1)
                $fatal(1,"early release destroyed blocked result");
        end
        cancel_and_check(0);force_stall=0;run_block(4);
        // CLEAR阶段中止也不得把旧有效标志带入下一块。
        @(negedge clk);block_start_i=1;
        @(posedge clk);#1;
        cancel_and_check(0);run_block(5);
        $display("PASS: V07 top: %0d blocks, %0d output handshakes; sums/masks/flags/stalls/recovery",blocks_done,outputs);
        $finish;
    end
    initial begin #3000000;$fatal(1,"V07 top timeout");end
endmodule
