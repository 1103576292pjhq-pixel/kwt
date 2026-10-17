`timescale 1ns/1ps
module d1_quant_tb;
    logic clk=0; always #5 clk=~clk;
    logic rst_n=0, in_valid=0, in_ready, out_valid, out_ready=0;
    logic signed [47:0] in_sum=0,in_bias=0,out_raw;
    logic [5:0] in_shift=0;
    logic signed [31:0] out_data;
    logic out_overflow,out_saturated;
    quant_epilogue dut(.*);
    reg [47:0] sums[0:8191], biases[0:8191], raw_exp[0:8191];
    reg [31:0] y_exp[0:8191];
    reg [5:0] shifts[0:8191];
    reg ov_exp[0:8191],sat_exp[0:8191];
    reg [81:0] held;
    reg was_blocked=0;
    integer f, rc, count=0, sent=0, received=0, cyc=0, stalls=0;
    string vectors, output_path;
    integer out_f;
    initial begin
        if (!$value$plusargs("VECTORS=%s",vectors)) $fatal(1,"missing vectors");
        if (!$value$plusargs("OUTPUT=%s",output_path)) $fatal(1,"missing output");
        f=$fopen(vectors,"r"); out_f=$fopen(output_path,"w");
        if (!f || !out_f) $fatal(1,"file open");
        while (!$feof(f)) begin
            rc=$fscanf(f,"%h %h %h %h %h %h %h\n",sums[count],biases[count],shifts[count],raw_exp[count],y_exp[count],ov_exp[count],sat_exp[count]);
            if (rc==7) count=count+1;
            else if (rc!=-1) $fatal(1,"bad vector");
        end
        $fclose(f);
        repeat(3) @(negedge clk); rst_n=1;
        while (received<count) begin
            @(negedge clk);
            in_valid=(sent<count && cyc%5!=1);
            if (sent<count) begin in_sum=sums[sent]; in_bias=biases[sent]; in_shift=shifts[sent]; end
            // Ready is withdrawn after an offered result, including a long final block.
            out_ready=(cyc%9>=3) && !(received==count-1 && stalls<19);
            if (received==count-1) stalls=stalls+1;
            @(posedge clk);
            if (was_blocked && (!out_valid || {out_raw,out_data,out_overflow,out_saturated}!==held)) $fatal(1,"blocked payload changed");
            was_blocked=out_valid&&!out_ready;
            held={out_raw,out_data,out_overflow,out_saturated};
            if (in_valid&&in_ready) sent=sent+1;
            if (out_valid&&out_ready) begin
                if ({out_raw,out_data,out_overflow,out_saturated} !== {raw_exp[received],y_exp[received],ov_exp[received],sat_exp[received]})
                    $fatal(1,"NUMERIC vector=%0d got=%h/%h/%b/%b expected=%h/%h/%b/%b",received,out_raw,out_data,out_overflow,out_saturated,raw_exp[received],y_exp[received],ov_exp[received],sat_exp[received]);
                $fdisplay(out_f,"%0d %h %h %b %b",received,out_raw,out_data,out_overflow,out_saturated);
                received=received+1;
            end
            cyc=cyc+1;
            if(cyc>100000) $fatal(1,"timeout");
        end
        // An in-flight result must be discarded by synchronous reset.
        @(negedge clk); in_valid=1; in_sum=17; in_bias=-3; in_shift=0; out_ready=0;
        @(posedge clk); @(negedge clk); in_valid=0;
        @(posedge clk); @(negedge clk);
        if(!out_valid) $fatal(1,"reset setup missing output");
        rst_n=0;
        @(posedge clk); @(negedge clk);
        if(out_valid) $fatal(1,"reset did not clear valid");
        rst_n=1; out_ready=1;
        repeat(3) begin @(posedge clk); if(out_valid) $fatal(1,"stale reset output"); end
        $fclose(out_f);
        $display("D1_QUANT_PASS count=%0d cycles=%0d",received,cyc); $finish;
    end
endmodule
