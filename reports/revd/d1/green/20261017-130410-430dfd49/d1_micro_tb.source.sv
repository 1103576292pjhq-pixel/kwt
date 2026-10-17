`timescale 1ns/1ps
module d1_micro_tb;
    parameter integer PM=4, PN=4;
    logic clk=0; always #5 clk=~clk;
    logic rst_n=0,cfg_valid=0,cfg_ready;
    logic [31:0] cfg_task_id=0;
    logic [PM-1:0] cfg_row_mask=0;
    logic [5:0] cfg_shift=0;
    logic [PN*48-1:0] cfg_bias=0;
    logic in_valid=0,in_ready;
    logic [PM*16-1:0] in_x=0;
    logic [PN*16-1:0] in_w=0;
    logic out_valid,out_ready=0;
    logic [31:0] out_task_id;
    logic [7:0] out_row,out_col;
    logic signed [47:0] out_raw;
    logic signed [31:0] out_data;
    logic out_overflow,out_saturated,out_last,done;
    logic trace_issue_valid,trace_retire_valid;
    logic [5:0] trace_retire_k;
    logic [PM-1:0] trace_valid_lanes;
    logic [31:0] effective_macs,padded_macs;
    micro_tile #(.PM(PM),.PN(PN)) dut(.*);
    reg [15:0] xs[0:63][0:PM-1],ws[0:63][0:PN-1];
    reg [47:0] expected_raw[0:PM-1][0:PN-1];
    reg [31:0] expected_y[0:PM-1][0:PN-1];
    reg expected_ov[0:PM-1][0:PN-1],expected_sat[0:PM-1][0:PN-1];
    reg [47:0] bias_word;
    reg [15:0] element_word;
    reg [47:0] raw_word;
    reg [31:0] y_word;
    reg ov_word,sat_word;
    string vectors,output_path;
    integer f,out_f,rc,cases,case_id,k,r,c,got,last_row,expected_row,expected_col,retired,issued,cyc,validrows,draincycles;
    reg [130:0] held;
    reg was_blocked;

    task automatic reset_dut;
        begin
            @(negedge clk); rst_n=0;cfg_valid=0;in_valid=0;out_ready=0;
            @(posedge clk); @(negedge clk);
            if(out_valid||done||trace_retire_valid||effective_macs!=0) $fatal(1,"RESET residual valid/retire/count");
            rst_n=1;
            repeat(3) begin @(posedge clk); if(out_valid||done||trace_retire_valid) $fatal(1,"RESET stale record"); end
        end
    endtask

    task automatic configure;
        begin
            @(negedge clk); cfg_valid=1;
            if(!cfg_ready) $fatal(1,"cfg not ready in idle");
            @(posedge clk); @(negedge clk); cfg_valid=0;
        end
    endtask

    task automatic feed(input integer limit);
        begin
            k=0;cyc=0;retired=0;issued=0;
            while(k<limit) begin
                @(negedge clk);
                in_valid=(cyc%7!=2 && cyc%7!=3);
                for(r=0;r<PM;r=r+1) in_x[r*16+:16]=cfg_row_mask[r]?xs[k][r]:16'hxxxx;
                for(c=0;c<PN;c=c+1) in_w[c*16+:16]=ws[k][c];
                @(posedge clk);
                if(out_valid) $fatal(1,"MICRO premature result before k63 retirement");
                if(done) $fatal(1,"MICRO premature done");
                if(cfg_ready) $fatal(1,"MICRO cfg ready while owned");
                if(trace_retire_valid) begin
                    if(trace_retire_k!==6'(retired) || trace_valid_lanes!==cfg_row_mask) $fatal(1,"MICRO retirement tag/mask mismatch");
                    retired=retired+1;
                end
                if(in_valid&&in_ready) begin k=k+1;issued=issued+1;end
                cyc=cyc+1;
                if(cyc>1024) $fatal(1,"feed timeout");
            end
            @(negedge clk);in_valid=0;
            @(posedge clk);
            if(trace_retire_valid) begin
                if(trace_retire_k!==6'(retired) || trace_valid_lanes!==cfg_row_mask) $fatal(1,"MICRO final retirement tag/mask");
                retired=retired+1;
            end
        end
    endtask

    task automatic drain(input integer abort_on_valid);
        begin : drain_body
            got=0;draincycles=0;was_blocked=0;expected_row=0;expected_col=0;
            while(!cfg_row_mask[expected_row]) expected_row=expected_row+1;
            while(got<validrows*PN) begin
                @(negedge clk);
                // Withdraw ready only after output was valid; final result stalls 20 cycles.
                out_ready=(draincycles>12 && draincycles%7>=2);
                if(got==validrows*PN-1 && draincycles<120) out_ready=0;
                @(posedge clk);
                if(trace_retire_valid) begin
                    if(trace_retire_k!==6'(retired) || trace_valid_lanes!==cfg_row_mask) $fatal(1,"MICRO drain tag/mask");
                    retired=retired+1;
                end
                if(was_blocked && (!out_valid||{out_task_id,out_row,out_col,out_raw,out_data,out_overflow,out_saturated,out_last}!==held)) $fatal(1,"MICRO blocked payload changed");
                was_blocked=out_valid&&!out_ready;
                held={out_task_id,out_row,out_col,out_raw,out_data,out_overflow,out_saturated,out_last};
                if(done) $fatal(1,"MICRO done before final handshake");
                if(out_valid && retired!=64) $fatal(1,"MICRO output before all 64 retirements");
                if(abort_on_valid && out_valid) begin
                    out_ready=0;
                    reset_dut();
                    disable drain_body;
                end
                if(out_valid&&out_ready) begin
                    if({out_raw,out_data,out_overflow,out_saturated}!=={expected_raw[expected_row][expected_col],expected_y[expected_row][expected_col],expected_ov[expected_row][expected_col],expected_sat[expected_row][expected_col]})
                        $fatal(1,"MICRO numeric case=%0d row=%0d col=%0d got=%h/%h expected=%h/%h",case_id,expected_row,expected_col,out_raw,out_data,expected_raw[expected_row][expected_col],expected_y[expected_row][expected_col]);
                    if(out_task_id!==cfg_task_id || out_row!==8'(expected_row) || out_col!==8'(expected_col) || out_last!==(got==validrows*PN-1)) $fatal(1,"MICRO output identity/last");
                    $fdisplay(out_f,"%0d %0d %0d %h %h %b %b %b",case_id,out_row,out_col,out_raw,out_data,out_overflow,out_saturated,out_last);
                    got=got+1;
                    expected_col=expected_col+1;
                    if(expected_col==PN && got<validrows*PN) begin
                        expected_col=0;expected_row=expected_row+1;
                        while(!cfg_row_mask[expected_row]) expected_row=expected_row+1;
                    end
                end
                draincycles=draincycles+1;
                if(draincycles>2048) $fatal(1,"drain timeout");
            end
            @(negedge clk);
            if(!done || !cfg_ready || out_valid) $fatal(1,"MICRO final completion/empty");
            if(issued!=64 || retired!=64 || effective_macs!=64*validrows*PN || padded_macs!=64*(PM-validrows)*PN)
                $fatal(1,"MICRO counts issued=%0d retired=%0d effective=%0d padded=%0d",issued,retired,effective_macs,padded_macs);
        end
    endtask

    initial begin
        if(!$value$plusargs("VECTORS=%s",vectors)||!$value$plusargs("OUTPUT=%s",output_path)) $fatal(1,"missing path");
        f=$fopen(vectors,"r");out_f=$fopen(output_path,"w");
        if(!f||!out_f) $fatal(1,"open vector");
        rc=$fscanf(f,"%d\n",cases);if(rc!=1) $fatal(1,"case count");
        reset_dut();
        for(case_id=0;case_id<cases;case_id=case_id+1) begin
            rc=$fscanf(f,"%h %h %h\n",cfg_task_id,cfg_row_mask,cfg_shift); if(rc!=3) $fatal(1,"header");
            validrows=0;last_row=0;
            for(r=0;r<PM;r=r+1) if(cfg_row_mask[r]) begin validrows=validrows+1;last_row=r;end
            for(c=0;c<PN;c=c+1) begin rc=$fscanf(f,"%h\n",bias_word);if(rc!=1) $fatal(1,"bias");cfg_bias[c*48+:48]=bias_word;end
            for(k=0;k<64;k=k+1) begin
                for(r=0;r<PM;r=r+1) begin rc=$fscanf(f,"%h\n",element_word);if(rc!=1) $fatal(1,"X");xs[k][r]=element_word;end
                for(c=0;c<PN;c=c+1) begin rc=$fscanf(f,"%h\n",element_word);if(rc!=1) $fatal(1,"W");ws[k][c]=element_word;end
            end
            for(r=0;r<PM;r=r+1) for(c=0;c<PN;c=c+1) begin
                rc=$fscanf(f,"%h %h %h %h\n",raw_word,y_word,ov_word,sat_word);if(rc!=4) $fatal(1,"expected");
                expected_raw[r][c]=raw_word;expected_y[r][c]=y_word;expected_ov[r][c]=ov_word;expected_sat[r][c]=sat_word;
            end
            // Explicit aborts in accumulation, after k63, and stalled output.
            if(case_id==0) begin configure(); feed(17);reset_dut(); end
            if(case_id==1) begin configure();feed(64); @(posedge clk); reset_dut(); end
            if(case_id==2) begin configure();feed(64);drain(1); end
            configure();feed(64);drain(0);
        end
        $fclose(f);$fclose(out_f);
        $display("D1_MICRO_PASS PM=%0d PN=%0d cases=%0d",PM,PN,cases);$finish;
    end
endmodule
