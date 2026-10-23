`timescale 1ns/1ps
module tb_buffers;
    reg clk=0; always #5 clk=~clk;
    reg rst_n=0,abort_i=0;
    reg x_load=0; reg [15:0] x_index=0; reg signed [15:0] x_value=0;
    reg x_read=0; reg [4:0] group_id=0; reg [5:0] k=0;
    reg [3:0] mask=15; wire x_valid; wire [63:0] xs;
    reg w_load=0,b_load=0,load_slot=0,read_slot=0;
    reg [9:0] w_index=0; reg [3:0] b_index=0,b_sel=0;
    reg signed [15:0] w_value=0; reg signed [31:0] b_value=0;
    reg w_read=0; reg [1:0] ctx=0; wire w_valid; wire [63:0] ws;
    wire signed [47:0] bias;
    integer i,s,g,j,lane,checks=0;
    x_buffer #(.READ_LATENCY(`TEST_LATENCY),.USE_MACRO(`TEST_MACRO)) xb(
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.load_i(x_load),
        .load_index_i(x_index),.load_data_i(x_value),.read_i(x_read),
        .row_group_i(group_id),.k_i(k),.row_mask_i(mask),.read_valid_o(x_valid),.x_o(xs));
    w_tile_buffer #(.READ_LATENCY(`TEST_LATENCY),.USE_MACRO(`TEST_MACRO)) wb(
        .clk(clk),.rst_n(rst_n),.abort_i(abort_i),.load_slot_i(load_slot),
        .w_load_i(w_load),.w_index_i(w_index),.w_data_i(w_value),
        .bias_load_i(b_load),.bias_index_i(b_index),.bias_data_i(b_value),
        .read_i(w_read),.active_slot_i(read_slot),.ctx_i(ctx),.k_i(k),
        .read_valid_o(w_valid),.w_o(ws),.bias_col_i(b_sel),.bias_o(bias));
    function automatic signed [15:0] xv(input integer row,input integer kk);
        xv=16'(row*173-kk*29-32000);
    endfunction
    function automatic signed [15:0] wv(input integer slot,input integer kk,input integer col);
        wv=16'(slot*15001+kk*67-col*211-17000);
    endfunction
    initial begin
        repeat(2) @(negedge clk);rst_n=1;
        for(i=0;i<6336;i=i+1)begin
            @(negedge clk);x_load=1;x_index=i;x_value=xv(i/64,i%64);
        end
        @(negedge clk);x_load=0;
        for(s=0;s<2;s=s+1)begin
            for(i=0;i<1024;i=i+1)begin
                @(negedge clk);w_load=1;load_slot=s;w_index=i;w_value=wv(s,i/16,i%16);
            end
            @(negedge clk);w_load=0;
            for(i=0;i<16;i=i+1)begin
                @(negedge clk);b_load=1;b_index=i;b_value=s?(-2147483647+i):(2147483647-i);
            end
            @(negedge clk);b_load=0;
        end
        for(g=0;g<25;g=g+1)for(j=0;j<64;j=j+1)begin
            @(negedge clk);group_id=g;k=j;mask=g==24?7:15;x_read=1;
            @(negedge clk);x_read=0;
            while(!x_valid) @(negedge clk);
            for(lane=0;lane<4;lane=lane+1)begin
                if($signed(xs[lane*16+:16])!==(mask[lane]?xv(g*4+lane,j):16'sd0))
                    $fatal(1,"X address/mask mismatch group=%0d k=%0d lane=%0d",g,j,lane);
                checks++;
            end
        end
        for(s=0;s<2;s=s+1)for(g=0;g<4;g=g+1)for(j=0;j<64;j=j+1)begin
            @(negedge clk);read_slot=s;ctx=g;k=j;w_read=1;
            @(negedge clk);w_read=0;
            while(!w_valid) @(negedge clk);
            for(lane=0;lane<4;lane=lane+1)begin
                if($signed(ws[lane*16+:16])!==wv(s,j,g*4+lane))
                    $fatal(1,"W slot/bank mismatch slot=%0d ctx=%0d k=%0d",s,g,j);
                checks++;
            end
        end
        for(s=0;s<2;s=s+1)for(i=0;i<16;i=i+1)begin
            @(negedge clk);read_slot=s;b_sel=i;#1;
            if(bias!==$signed(s?(-48'sd2147483647+i):(48'sd2147483647-i)))
                $fatal(1,"bias sign extension mismatch");
            checks++;
        end
        // 一个槽读、另一个槽写：必须没有单端口冲突，也不能串槽。
        @(negedge clk);read_slot=0;load_slot=1;ctx=0;k=0;w_read=1;
        w_load=1;w_index=0;w_value=1234;
        @(negedge clk);w_read=0;w_load=0;
        while(!w_valid) @(negedge clk);
        if($signed(ws[15:0])!==wv(0,0,0))$fatal(1,"inactive slot write damaged active slot");
        @(negedge clk);abort_i=1;
        @(negedge clk);abort_i=0;
        if(x_valid||w_valid)$fatal(1,"abort left stale read valid");
        $display("PASS: buffers latency=%0d macro=%0d: %0d lane/bias checks",`TEST_LATENCY,`TEST_MACRO,checks);
        $finish;
    end
    initial begin #1000000;$fatal(1,"buffer timeout");end
endmodule
