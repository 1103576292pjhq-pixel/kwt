`timescale 1ns/1ps
`include "kwt_compute_config.vh"

// 自检平台：参考值采用64位有符号整数，独立保存全部上下文。
// 每次写入后通过公开rd_addr/rd_acc接口检查全部64项，不读取DUT内部状态。
module tb_acc_context_bank;
    reg clk = 0;
    always #5 clk = ~clk;
    reg rst_n = 0, clear = 0, in_valid = 0, in_block_last = 0;
    reg [511:0] in_product = 0;
    reg [1:0] in_ctx = 0;
    reg [3:0] in_row_mask = 0;
    reg [5:0] rd_addr = 0;
    wire signed [39:0] rd_acc;
    wire block_done;

    acc_context_bank dut (
        .clk(clk), .rst_n(rst_n), .clear(clear), .in_valid(in_valid),
        .in_product(in_product), .in_ctx(in_ctx), .in_row_mask(in_row_mask),
        .in_block_last(in_block_last), .block_done(block_done),
        .rd_addr(rd_addr), .rd_acc(rd_acc)
    );

    reg signed [63:0] reference [0:3][0:3][0:3];
    reg reference_active = 0, known = 0, expected_done;
    reg signed [63:0] term;
    reg [40:0] held;
    integer cycles = 0, checks = 0, accepted = 0, done_count = 0;
    integer rr, cc, gg, address;
    integer seed = 20261028;
    integer k, g, p, q, m, test_id, value;
    reg [511:0] products;
    reg signed [15:0] x_group [0:3];
    reg signed [15:0] w_tile [0:15];
    reg [255:0] w_trace;
    integer trace_fd;
    reg [4095:0] trace_path;

    // 一次step对应一个上升沿：下降沿驱动，沿后检查，避免仿真竞争。
    task step;
        input reset_value, clear_value, valid_value;
        input [1:0] ctx_value;
        input [3:0] mask_value;
        input last_value;
        input [511:0] payload;
        begin
            @(negedge clk);
            held = {block_done, rd_acc};
            rst_n = reset_value;
            clear = clear_value;
            in_valid = valid_value;
            in_ctx = ctx_value;
            in_row_mask = mask_value;
            in_block_last = last_value;
            in_product = payload;
            #1;
            if ({block_done, rd_acc} !== held)
                $fatal(1, "FAIL output changed before clock, cycle=%0d", cycles);
            expected_done = 0;
            if (!reset_value) begin
                reference_active = 0;
            end else if (clear_value) begin
                for (gg=0; gg<4; gg=gg+1)
                    for (rr=0; rr<4; rr=rr+1)
                        for (cc=0; cc<4; cc=cc+1)
                            reference[gg][rr][cc] = 0;
                known = 1;
                reference_active = 1;
            end else if (reference_active && valid_value) begin
                accepted = accepted + 1;
                for (rr=0; rr<4; rr=rr+1)
                    for (cc=0; cc<4; cc=cc+1)
                        if (mask_value[rr]) begin
                            term = $signed(payload[(rr*4+cc)*32 +: 32]);
                            reference[ctx_value][rr][cc] = reference[ctx_value][rr][cc] + term;
                        end
                if (last_value) begin
                    reference_active = 0;
                    expected_done = 1;
                end
            end
            @(posedge clk);
            #1;
            cycles = cycles + 1;
            if (block_done !== expected_done)
                $fatal(1, "FAIL done cycle=%0d got=%b expected=%b", cycles, block_done, expected_done);
            if (block_done) done_count = done_count + 1;
            if (known) begin
                for (address=0; address<64; address=address+1) begin
                    rd_addr = address;
                    #0.01;
                    term = $signed(rd_acc);
                    if (term !== reference[address/16][(address%16)/4][address%4])
                        $fatal(1, "FAIL acc cycle=%0d address=%0d got=%0d expected=%0d",
                            cycles, address, term, reference[address/16][(address%16)/4][address%4]);
                    checks = checks + 1;
                end
            end
        end
    endtask

    task bubble;
        begin step(1,0,0,3,0,1,{512{1'bx}}); end
    endtask

    initial begin
        if (!$value$plusargs("trace=%s", trace_path))
            $fatal(1, "FAIL missing +trace=...");
        trace_fd = $fopen(trace_path, "w");
        if (!trace_fd) $fatal(1, "FAIL cannot open trace");
        if (`KWT_ACC_WIDTH != 40 || `KWT_PRODUCT_WIDTH != 32 ||
            `KWT_ACC_COUNT != 64 || `KWT_ACC_ADDR_WIDTH != 6 ||
            `KWT_PM != 4 || `KWT_PN != 4 || `KWT_CTX != 4)
            $fatal(1, "FAIL frozen configuration");

        // 初始复位优先于clear；未clear时忽略输入。
        step(0,1,1,3,15,1,{512{1'b1}});
        step(1,0,1,0,15,1,512'd1);

        // 4个ctx × 16种mask；定向检查所有地址与符号扩展。
        // last用于组件控制压力，不声称这些短事务是完整K64调度。
        for (g=0; g<4; g=g+1) begin
            for (m=0; m<16; m=m+1) begin
                step(1,1,1,g,m,1,{512{1'b1}}); // clear优先，不累加本拍数据
                for (p=0; p<4; p=p+1)
                    for (q=0; q<4; q=q+1) begin
                        value = -(1 + g*100 + p*4 + q);
                        products[(p*4+q)*32 +: 32] = value;
                    end
                bubble(); // 无效last不能完成
                step(1,0,1,g,m,1,products);
                step(1,0,1,g,15,1,products); // 完成后锁住结果，不能重复累加
                bubble();
            end
        end

        // 完整块：全零、手算、仅k63、正负极值、抵消、随机及尾行mask。
        for (test_id=0; test_id<10; test_id=test_id+1) begin
            step(1,1,0,0,0,0,0);
            for (k=0; k<64; k=k+1) begin
                // 固定k时四个ctx复用同一组X，W共有16列，符合正式外积输入结构。
                for (p=0; p<4; p=p+1) begin
                    case (test_id)
                        0: x_group[p] = 0;
                        1: x_group[p] = k==0 ? 4096*(p+1) : 0;
                        2: x_group[p] = k==63 ? -4096*(p+1) : 0;
                        3,4: x_group[p] = -32768;
                        5: x_group[p] = k<32 ? 32767 : -32767;
                        default: x_group[p] = $random(seed);
                    endcase
                end
                for (q=0; q<16; q=q+1) begin
                    case (test_id)
                        0: w_tile[q] = 32767;
                        1: w_tile[q] = 16*(q+1);
                        2: w_tile[q] = 96+q;
                        3,5: w_tile[q] = -32768;
                        4: w_tile[q] = 32767;
                        default: w_tile[q] = $random(seed);
                    endcase
                    w_trace[q*16 +: 16] = w_tile[q];
                end
                for (g=0; g<4; g=g+1) begin
                    for (p=0; p<4; p=p+1) begin
                        for (q=0; q<4; q=q+1) begin
                            value = $signed(x_group[p]) * $signed(w_tile[g*4+q]);
                            products[(p*4+q)*32 +: 32] = value;
                        end
                    end
                    $fdisplay(trace_fd, "INPUT %0d %0d %0d %016h %064h", test_id,k,g,
                        {x_group[3],x_group[2],x_group[1],x_group[0]},w_trace);
                    step(1,0,1,g,test_id==9 ? 7 : 15,k==63 && g==3,products);
                    if (test_id>=6 && (k+g)%7==0) bubble();
                end
            end
            // 独立字面期望锚点，不用参考模型自身证明自己。
            for (address=0; address<64; address=address+1) begin
                rd_addr = address;
                #0.01;
                $fdisplay(trace_fd, "RESULT %0d %0d %010h", test_id,address,rd_acc);
                case (test_id)
                    0,5: if (rd_acc !== 40'sd0) $fatal(1,"FAIL literal zero/cancel");
                    1: begin
                        term = 65536*((address%16)/4+1)*((address/16)*4+address%4+1);
                        if ($signed(rd_acc) !== term) $fatal(1,"FAIL literal hand matrix");
                    end
                    2: begin
                        term = -4096*((address%16)/4+1)*(96+(address/16)*4+address%4);
                        if ($signed(rd_acc) !== term) $fatal(1,"FAIL literal k63");
                    end
                    3: if (rd_acc !== 40'sd68719476736) $fatal(1,"FAIL positive K64 bound");
                    4: if (rd_acc !== -40'sd68717379584) $fatal(1,"FAIL negative K64 bound");
                    default: begin end
                endcase
            end
            bubble();
            step(1,0,1,0,15,1,products); // 新块clear前旧结果必须保持
        end

        // 中途复位：保留数据但关闭active，必须重新clear才能开始。
        step(1,1,0,0,0,0,0);
        step(1,0,1,2,15,0,{16{32'hffffffff}});
        step(0,1,1,2,15,1,0);
        step(1,0,1,2,15,1,{16{32'h7fffffff}});
        bubble();
        step(1,1,0,0,0,0,0);
        step(1,0,1,3,7,1,{16{32'h80000000}}); // 额外的signed32组件输入压力
        bubble();
        $fclose(trace_fd);
        $display("PASS cycles=%0d accepted_groups=%0d acc_read_checks=%0d done_pulses=%0d seed=20261028",
                 cycles, accepted, checks, done_count);
        $finish;
    end

    initial begin
        #1000000;
        $fatal(1, "FAIL timeout");
    end
endmodule
