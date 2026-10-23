`timescale 1ns/1ps
module tb_v07_units;
    localparam N=251;
    reg clk=0;
    always #5 clk=~clk;
    reg rst_n=0,abort_i=0;
    reg accept_en_i=1,in_valid_i=0;
    wire in_ready_o,product_valid_o;
    reg [63:0] x_i=0,w_i=0;
    reg [1:0] ctx_i=0;
    reg [3:0] row_mask_i=0;
    reg block_last_i=0;
    wire [511:0] product_o;
    wire [1:0] ctx_o;
    wire [3:0] row_mask_o;
    wire block_last_o;
    mul_array_4x4 mul(.*);
    reg cv=0,cr=0,cl=0;
    wire ci,ov;
    reg signed [47:0] cs=0,cb=0;
    reg [31:0] ct=0;
    wire signed [31:0] cy;
    wire [31:0] ot;
    wire [2:0] of;
    wire oo,os,ol;
    result_convert_v07 cvt(.clk(clk),.rst_n(rst_n),.abort_i(abort_i),
        .in_valid_i(cv),.in_ready_o(ci),.sum_i(cs),.bias_i(cb),.tag_i(ct),.last_i(cl),
        .out_valid_o(ov),.out_ready_i(cr),.out_data_o(cy),.out_tag_o(ot),
        .out_flags_o(of),.out_overflow_o(oo),.out_saturated_o(os),.out_last_o(ol));
    reg signed [47:0] ss[0:N-1],bs[0:N-1];
    reg signed [31:0] yy[0:N-1];
    reg [2:0] ff[0:N-1];
    integer n,r,c,checks=0,got=0;
    reg signed [15:0] xv,wv;
    reg signed [31:0] expected;
    reg [31:0] hy,ht;
    reg [2:0] hf;

    initial begin
        $readmemh("out/v07-vectors/cvt_sum.hex",ss);$readmemh("out/v07-vectors/cvt_bias.hex",bs);
        $readmemh("out/v07-vectors/cvt_y.hex",yy);$readmemh("out/v07-vectors/cvt_flags.hex",ff);
        for(n=0;n<N;n=n+1) if((^ss[n]===1'bx)||(^bs[n]===1'bx)||
            (^yy[n]===1'bx)||(^ff[n]===1'bx)) $fatal(1,"unknown converter vector");
        repeat(2) @(negedge clk);rst_n=1;
        // 连续拍检查每个乘法lane、符号边界、四种上下文及行mask。
        for(n=0;n<32;n=n+1) begin
            @(negedge clk);in_valid_i=(n%5!=1);ctx_i=n%4;
            row_mask_i=n%16;block_last_i=(n==31);
            for(r=0;r<4;r=r+1) begin
                x_i[r*16+:16]=(n%2)?(-32768+r):(32767-r);
                w_i[r*16+:16]=(n%3)?(-32768+r):(32767-r);
            end
            @(posedge clk);#1;
            if(product_valid_o!==in_valid_i) $fatal(1,"product valid mismatch");
            if(in_valid_i) begin
                if(ctx_o!==ctx_i || row_mask_o!==row_mask_i || block_last_o!==block_last_i)
                    $fatal(1,"product tags misaligned");
                for(r=0;r<4;r=r+1) for(c=0;c<4;c=c+1) begin
                    xv=x_i[r*16+:16];wv=w_i[c*16+:16];
                    expected=row_mask_i[r] ? xv*wv : 0;
                    if($signed(product_o[(r*4+c)*32+:32])!==expected)
                        $fatal(1,"lane mismatch r=%0d c=%0d",r,c);
                    checks=checks+1;
                end
            end
        end
        @(negedge clk);accept_en_i=0;in_valid_i=1;
        @(posedge clk);#1;
        if(in_ready_o!==0 || product_valid_o!==0) $fatal(1,"disabled input accepted");
        @(negedge clk);in_valid_i=0;
        // 每个转换输入都检查结果、flags、标签及背压稳定性。
        for(n=0;n<N;n=n+1) begin
            @(negedge clk);cv=1;cs=ss[n];cb=bs[n];ct=n;cl=n%2;cr=0;
            if(ci!==1) $fatal(1,"converter should be empty");
            @(posedge clk);#1;
            if(ov!==1 || cy!==yy[n] || of!==ff[n] || ot!==n || {ol,os,oo}!==ff[n])
                $fatal(1,"converter case=%0d got=%0d/%b expected=%0d/%b sum=%0d bias=%0d added=%0d clipped=%0d quotient=%0d",
                    n,cy,of,yy[n],ff[n],cs,cb,cvt.added,cvt.clipped,cvt.quotient);
            hy=cy;ht=ot;hf=of;
            @(negedge clk);cv=0;cs=0;cb=0;
            repeat(2) begin
                @(posedge clk);#1;
                if(ci!==0 || ov!==1 || cy!==hy || ot!==ht || of!==hf)
                    $fatal(1,"converter did not hold blocked result");
            end
            @(negedge clk);cr=1;
            @(posedge clk);#1;if(ov!==0) $fatal(1,"converter valid not cleared");
            got=got+1;
        end
        // 旧输出被接收的同一拍装入下一项，检查每拍吞吐与标签对齐。
        for(n=0;n<12;n=n+1) begin
            @(negedge clk);cr=1;cv=1;cs=ss[n];cb=bs[n];ct=n;cl=n%2;
            @(posedge clk);
            if(n>0 && (ov!==1 || cy!==yy[n-1] || ot!==n-1 || of!==ff[n-1]))
                $fatal(1,"streaming output mismatch at %0d",n);
            #1;
            if(ov!==1 || cy!==yy[n] || ot!==n || of!==ff[n])
                $fatal(1,"streaming replacement mismatch at %0d",n);
        end
        @(negedge clk);cv=0;
        @(posedge clk);#1;
        if(ov!==0) $fatal(1,"streaming did not drain");
        // 输出被阻塞时中止，下一拍不允许留下旧valid。
        @(negedge clk);cr=0;cv=1;cs=65536;cb=0;
        @(posedge clk);#1;
        @(negedge clk);abort_i=1;cv=0;
        @(posedge clk);#1;
        if(ov!==0 || product_valid_o!==0) $fatal(1,"abort failed");
        $display("PASS: V07 units: %0d lane products, %0d converter cases + 12 streaming; tags/backpressure/abort",checks,got);
        $finish;
    end
    initial begin #100000;$fatal(1,"V07 units timeout");end
endmodule
