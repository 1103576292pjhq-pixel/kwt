`include "kwt_icb_config.vh"
`default_nettype none

// 首版只保留一项待执行命令：用于把总线响应与内部执行解耦，不预设深度8。
// 下游阻塞时保持完整快照；同拍取走旧项和写入新项可保持valid不变。
module kwt_command_fifo (
    input wire clk,
    input wire rst_n,
    input wire clear, // 中止取消旧输入；清valid，不清数据阵列
    input wire in_valid,
    output wire in_ready,
    input wire [`KWT_ICB_COMMAND_WIDTH-1:0] in_data,
    output wire out_valid,
    input wire out_ready,
    output wire [`KWT_ICB_COMMAND_WIDTH-1:0] out_data,
    output wire empty
);
    reg valid;
    reg [`KWT_ICB_COMMAND_WIDTH-1:0] data;
    assign in_ready = rst_n && !clear && (!valid || out_ready);
    assign out_valid = rst_n && !clear && valid;
    assign out_data = data;
    // 本拍正入队也不能对任务控制报告输入已空。
    assign empty = !valid && !(in_valid && in_ready);
    always @(posedge clk) begin
        if (!rst_n || clear) valid <= 1'b0;
        else if (in_ready) begin
            valid <= in_valid;
            if (in_valid) data <= in_data;
        end
    end
endmodule
`default_nettype wire
