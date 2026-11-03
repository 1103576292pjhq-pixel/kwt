`timescale 1ns/1ps
// 先用手算字面期望固定数值及握手行为，不通过DUT自身生成期望。
module tb_result_convert;
    reg clk = 0;
    always #5 clk = ~clk;
    reg rst_n = 0, in_valid = 0, out_ready = 0, in_global_last = 0;
    reg signed [39:0] in_acc = 0;
    reg signed [31:0] in_bias = 0;
    wire in_ready, out_valid;
    wire signed [15:0] out_y;
    wire [2:0] out_flags;
    integer cases = 0;
    result_convert dut (
        .clk(clk), .rst_n(rst_n), .in_valid(in_valid), .in_ready(in_ready),
        .in_acc(in_acc), .in_bias(in_bias), .in_global_last(in_global_last),
        .out_valid(out_valid), .out_ready(out_ready), .out_y(out_y), .out_flags(out_flags)
    );

    task check;
        input signed [15:0] y;
        input [2:0] flags;
        begin
            if (out_valid !== 1'b1 || out_y !== y || out_flags !== flags)
                $fatal(1,"FAIL case=%0d got=%b/%0d/%b expected=1/%0d/%b",cases,out_valid,out_y,out_flags,y,flags);
        end
    endtask

    task convert;
        input signed [39:0] acc;
        input signed [31:0] bias;
        input last;
        input signed [15:0] y;
        input [2:0] flags;
        integer i;
        begin
            @(negedge clk);
            in_valid=1; in_acc=acc; in_bias=bias; in_global_last=last; out_ready=0;
            #1;
            if (in_ready !== 1'b1) $fatal(1,"FAIL empty slot not ready");
            @(posedge clk); #1;
            cases=cases+1;
            check(y,flags);
            // 输出阻塞时扰动输入，不允许覆盖Y/flags，也不允许继续接收。
            @(negedge clk);
            in_valid=1; in_acc=40'sd123456789; in_bias=-32'sd7654321; in_global_last=~last;
            for (i=0;i<3;i=i+1) begin
                @(posedge clk); #1;
                check(y,flags);
                if (in_ready !== 1'b0) $fatal(1,"FAIL accepted while full");
            end
            @(negedge clk); in_valid=0; out_ready=1;
            @(posedge clk); #1;
            if (out_valid !== 1'b0) $fatal(1,"FAIL consumed result remained valid");
        end
    endtask

    // 文件中的每行是acc40、bias32、last、期望Y16、期望flags。
    // 正常流测试严格遵守发送方受阻保持，按真实握手建一个独立单槽记分板。
    integer vector_fd, trace_fd, fields;
    integer stream_cycles, accepted, consumed, canceled, stall_count, replacements;
    integer stream_seed = 20261028;
    reg [31:0] random_bits;
    reg [4095:0] vector_path, trace_path;
    reg source_pending, source_asserted, file_ended, model_valid;
    reg signed [39:0] vector_acc;
    reg signed [31:0] vector_bias;
    reg vector_last;
    reg signed [15:0] vector_y, model_y;
    reg [2:0] vector_flags, model_flags;
    integer model_id;
    reg input_fire, output_fire;
    reg [19:0] before_output;

    task stream_test;
        begin
            if (!$value$plusargs("vectors=%s",vector_path))
                $fatal(1,"FAIL missing +vectors");
            if (!$value$plusargs("trace=%s",trace_path))
                $fatal(1,"FAIL missing +trace");
            vector_fd=$fopen(vector_path,"r");
            trace_fd=$fopen(trace_path,"w");
            if (!vector_fd || !trace_fd) $fatal(1,"FAIL cannot open vectors/trace");
            source_pending=0; source_asserted=0; file_ended=0; model_valid=0;
            stream_cycles=0; accepted=0; consumed=0; canceled=0; stall_count=0; replacements=0;
            while (!file_ended || source_pending || model_valid) begin
                @(negedge clk);
                before_output={out_valid,out_y,out_flags};
                if (!source_pending && !file_ended) begin
                    fields=$fscanf(vector_fd,"%h %h %d %h %h\n",
                        vector_acc,vector_bias,vector_last,vector_y,vector_flags);
                    if (fields==-1) file_ended=1;
                    else begin
                        if (fields!=5) $fatal(1,"FAIL malformed vector");
                        source_pending=1;
                        source_asserted=0;
                    end
                end
                random_bits=$random(stream_seed);
                // 前64拍连续满速；随后长阻塞，并在阻塞中间明确插入一次复位。
                // 后半段随机空拍/背压，另周期性复位，检查旧结果不会重新冒出来。
                rst_n=!(stream_cycles==123 ||
                        (stream_cycles>200 && stream_cycles%503==0));
                if (stream_cycles<64) out_ready=1;
                else if (stream_cycles>=100 && stream_cycles<180) out_ready=0;
                else out_ready=(random_bits[2:0]!=0);
                if (!rst_n) begin
                    in_valid=0;
                    source_asserted=0;
                end else if (source_pending) begin
                    if (!source_asserted)
                        source_asserted=(stream_cycles<64 || random_bits[5:4]!=0);
                    in_valid=source_asserted;
                end else in_valid=0;
                if (source_pending) begin
                    in_acc=vector_acc;
                    in_bias=vector_bias;
                    in_global_last=vector_last;
                end
                #1;
                if ({out_valid,out_y,out_flags} !== before_output)
                    $fatal(1,"FAIL output changed between clock edges");
                if (in_ready !== (rst_n && (!model_valid || out_ready)))
                    $fatal(1,"FAIL ready cycle=%0d",stream_cycles);
                input_fire=rst_n && in_valid && in_ready;
                output_fire=rst_n && out_valid && out_ready;
                if (rst_n && out_valid && !out_ready) stall_count=stall_count+1;
                if (input_fire && output_fire) replacements=replacements+1;
                if (output_fire) begin
                    if (!model_valid || out_y !== model_y || out_flags !== model_flags)
                        $fatal(1,"FAIL retired output id=%0d",model_id);
                    $fdisplay(trace_fd,"OUTPUT %0d %04h %h",model_id,out_y,out_flags);
                    consumed=consumed+1;
                end
                @(posedge clk); #1;
                stream_cycles=stream_cycles+1;
                if (!rst_n) begin
                    if (model_valid) begin
                        $fdisplay(trace_fd,"CANCEL %0d",model_id);
                        canceled=canceled+1;
                    end
                    model_valid=0;
                end else begin
                    if (output_fire) model_valid=0;
                    if (input_fire) begin
                        model_valid=1;
                        model_y=vector_y;
                        model_flags=vector_flags;
                        model_id=accepted;
                        $fdisplay(trace_fd,"ACCEPT %0d %010h %08h %b %04h %h",
                            model_id,vector_acc,vector_bias,vector_last,vector_y,vector_flags);
                        accepted=accepted+1;
                        source_pending=0;
                        source_asserted=0;
                    end
                end
                if (out_valid !== model_valid)
                    $fatal(1,"FAIL stream valid cycle=%0d",stream_cycles);
                if (model_valid && (out_y !== model_y || out_flags !== model_flags))
                    $fatal(1,"FAIL stream value id=%0d got=%0d/%h expected=%0d/%h",
                        model_id,out_y,out_flags,model_y,model_flags);
            end
            if (accepted==0 || accepted!=consumed+canceled || canceled==0 || replacements<60 || stall_count<70)
                $fatal(1,"FAIL handshake counts/coverage");
            $fclose(vector_fd);
            $fclose(trace_fd);
            $display("PASS_STREAM cycles=%0d accepted=%0d consumed=%0d canceled=%0d stalls=%0d replacements=%0d",
                stream_cycles,accepted,consumed,canceled,stall_count,replacements);
        end
    endtask

    initial begin
        @(posedge clk); #1;
        if (out_valid !== 1'b0 || in_ready !== 1'b0) $fatal(1,"FAIL reset");
        @(negedge clk); rst_n=1;
        convert(0,0,1,0,4);
        convert(0,163840,0,2,0);
        convert(0,229376,0,4,0);
        convert(0,-163840,0,-2,0);
        convert(0,-229376,0,-4,0);
        convert(0,32768,0,0,0);
        convert(0,32769,0,1,0);
        convert(0,-32768,0,0,0);
        convert(0,-32769,0,-1,0);
        convert(0,2147450879,0,32767,0);
        convert(0,2147450880,0,32767,2);
        convert(0,32'sh80000000,0,-32768,0);
        convert(-65536,32'sh80000000,0,-32768,2);
        convert(40'sh7fffffffff,1,0,32767,3);
        convert(40'sh8000000000,-1,1,-32768,7);
        convert(40'sh8000000000,0,0,-32768,2);
        // 旧结果被接收的同一个沿，可以换入下一项。
        @(negedge clk); in_valid=1; out_ready=1; in_acc=0; in_bias=163840; in_global_last=0;
        @(posedge clk); #1; check(2,0);
        @(negedge clk); in_bias=-229376; in_global_last=1;
        @(posedge clk); #1; check(-4,4);
        // 复位允许取消尚未退休的算术输出。
        @(negedge clk); out_ready=0; rst_n=0;
        @(posedge clk); #1;
        if (out_valid !== 1'b0) $fatal(1,"FAIL reset did not cancel output");
        @(negedge clk); rst_n=1; in_valid=0;
        @(posedge clk); #1;
        if (out_valid !== 1'b0) $fatal(1,"FAIL stale result after reset");
        $display("PASS directed_cases=%0d stall_cycles=%0d replacement=PASS reset=PASS",cases,cases*3);
        stream_test();
        $finish;
    end
    initial begin #10000000; $fatal(1,"FAIL timeout"); end
endmodule
