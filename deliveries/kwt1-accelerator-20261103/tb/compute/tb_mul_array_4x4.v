`timescale 1ns / 1ps
`include "kwt_compute_config.vh"
`include "kwt_compute_config.vh" // 同时检查头文件可重复引用

// 自检平台：期望值由独立Python整数计算生成，不读取RTL内部乘积。
// 降沿驱动输入，上升沿后检查输出，避开非阻塞赋值的仿真调度竞争。
module tb_mul_array_4x4;
    reg clk = 1'b0;
    reg rst_n = 1'b0;
    reg in_valid = 1'b0;
    reg [63:0] in_x = 0;
    reg [63:0] in_w = 0;
    reg [1:0] in_ctx = 0;
    reg [3:0] in_row_mask = 0;
    reg in_block_last = 0;
    wire out_valid;
    wire [511:0] out_product;
    wire [1:0] out_ctx;
    wire [3:0] out_row_mask;
    wire out_block_last;

    mul_array_4x4 dut (
        .clk(clk), .rst_n(rst_n),
        .in_valid(in_valid), .in_x(in_x), .in_w(in_w),
        .in_ctx(in_ctx), .in_row_mask(in_row_mask),
        .in_block_last(in_block_last),
        .out_valid(out_valid), .out_product(out_product),
        .out_ctx(out_ctx), .out_row_mask(out_row_mask),
        .out_block_last(out_block_last)
    );

    always #5 clk = ~clk; // 仿真激励时钟，不是STA频率结论

    integer fd, fields, cycles, accepted, lane;
    integer expected_valid, check_payload, expected_last;
    reg [511:0] expected_product;
    reg [1:0] expected_ctx;
    reg [3:0] expected_mask;
    reg [519:0] held_output;
    reg [4095:0] vector_path;

    initial begin
        // 端口宽度采用冻结规格的字面值，避免错误宏同步改变TB而掩盖问题。
        if (`KWT_X_WIDTH != 16 || `KWT_W_WIDTH != 16 ||
            `KWT_PRODUCT_WIDTH != 32 || `KWT_BIAS_WIDTH != 32 ||
            `KWT_ACC_WIDTH != 40 || `KWT_ADD_WIDTH != 41 || `KWT_Y_WIDTH != 16 ||
            `KWT_X_FRAC != 12 || `KWT_W_FRAC != 16 ||
            `KWT_PRODUCT_FRAC != 28 || `KWT_BIAS_FRAC != 28 ||
            `KWT_ACC_FRAC != 28 || `KWT_Y_FRAC != 12 || `KWT_OUTPUT_SHIFT != 16 ||
            `KWT_FLAGS_WIDTH != 3 || `KWT_FLAG_RAW_OVF_BIT != 0 ||
            `KWT_FLAG_Y_SAT_BIT != 1 || `KWT_FLAG_GLOBAL_LAST_BIT != 2 ||
            `KWT_M != 99 || `KWT_K != 64 || `KWT_N != 256 ||
            `KWT_PM != 4 || `KWT_PN != 4 || `KWT_CTX != 4 ||
            `KWT_CTX_WIDTH != 2 || `KWT_K_INDEX_WIDTH != 6 ||
            `KWT_ROW_MASK_WIDTH != 4 || `KWT_MAC_LANES != 16 ||
            `KWT_BLOCK_COLS != 16 || `KWT_ACC_COUNT != 64 ||
            `KWT_GROUPS_PER_BLOCK != 256 || `KWT_X_GROUP_WIDTH != 64 ||
            `KWT_W_GROUP_WIDTH != 64 || `KWT_PRODUCT_GROUP_WIDTH != 512)
            $fatal(1, "FAIL: frozen macro contract mismatch");

        if (!$value$plusargs("vectors=%s", vector_path))
            $fatal(1, "FAIL: missing +vectors=...");
        fd = $fopen(vector_path, "r");
        if (!fd) $fatal(1, "FAIL: cannot open vectors");
        cycles = 0;
        accepted = 0;

        while (!$feof(fd)) begin
            @(negedge clk);
            held_output = {out_valid, out_product, out_ctx,
                           out_row_mask, out_block_last};
            fields = $fscanf(fd, "%d %d %h %h %h %h %d %d %d %h %h %h %d\n",
                rst_n, in_valid, in_x, in_w, in_ctx, in_row_mask, in_block_last,
                expected_valid, check_payload, expected_product,
                expected_ctx, expected_mask, expected_last);
            if (fields != -1) begin
                if (fields != 13) $fatal(1, "FAIL: malformed vector row");
                cycles = cycles + 1;
                // 改输入或在两沿之间拉低复位，不应使同步寄存输出立即变化。
                #1;
                if ({out_valid, out_product, out_ctx, out_row_mask, out_block_last}
                    !== held_output)
                    $fatal(1, "FAIL: output changed without rising edge, cycle=%0d", cycles);

                @(posedge clk);
                #1;
                if ({out_valid, out_ctx, out_row_mask, out_block_last} !==
                    {expected_valid[0], expected_ctx, expected_mask, expected_last[0]})
                    $fatal(1, "FAIL: valid/tag mismatch, cycle=%0d got=%b/%h/%h/%b expected=%b/%h/%h/%b",
                        cycles, out_valid, out_ctx, out_row_mask, out_block_last,
                        expected_valid[0], expected_ctx, expected_mask, expected_last[0]);
                // 首次有效输入之前，未复位的乘积允许为X；之后连保持值也检查。
                if (check_payload) begin
                    for (lane = 0; lane < 16; lane = lane + 1) begin
                        if (out_product[32*lane +: 32] !== expected_product[32*lane +: 32])
                            $fatal(1, "FAIL: product mismatch, cycle=%0d lane=%0d got=%0d expected=%0d",
                                cycles, lane, $signed(out_product[32*lane +: 32]),
                                $signed(expected_product[32*lane +: 32]));
                    end
                end
                if (rst_n && in_valid) accepted = accepted + 1;
            end
        end
        $fclose(fd);
        if (cycles == 0 || accepted == 0) $fatal(1, "FAIL: empty test");
        $display("PASS cycles=%0d accepted_groups=%0d product_checks=%0d", cycles, accepted, accepted*16);
        $finish;
    end

    initial begin
        #1000000;
        $fatal(1, "FAIL: simulation timeout");
    end
endmodule
