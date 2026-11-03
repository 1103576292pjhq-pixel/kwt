`include "kwt_compute_config.vh"

`default_nettype none

// ================================================================
// result_convert —— 单份偏置/量化模块（Verilog-2001）
// ================================================================
// KWT1-FFN1
// 固定流程：acc40+bias32 -> 41位临时和 -> sat40 -> RNE右移16 -> sat16。
// 算术部分为组合逻辑，仅最终Y、flags和valid设置一级输出寄存。
//
// 握手约定：
//   - 输入在in_valid && in_ready的上升沿接收，沿后产生对应的有效输出。
//   - 输出在out_valid && out_ready的上升沿消费；受阻时保持Y/flags/valid。
//   - 旧输出消费与新输入接收可以同拍发生，本模块仅缓存一个结果。
//   - 输入被阻塞时，上游也必须保持acc/bias/global_last及in_valid。
//
// 复位约定：
//   - rst_n为低有效同步复位；复位清out_valid，允许取消在途算术结果。
//   - 数据寄存器不要求复位，仅out_valid=1时Y及flags有效。
//
// 其他：
//   - 顶层仍按既定QISSUE/QWAIT逐项服务，不据此增加并行量化器或重叠计算。
//   - 全局结果坐标由外围控制器保存到输出握手完成；这里仅随数值保存global_last。
module result_convert (
    // ---- 时钟与复位 ----
    input  wire clk,                             // 时钟，上升沿接受输入、更新输出寄存器
    input  wire rst_n,                           // 低有效同步复位

    // ---- 上游握手与数据 ----
    input  wire in_valid,                        // 输入acc、bias和global_last有效
    output wire in_ready,                        // 有空间接收当前输入
    input  wire signed [`KWT_ACC_WIDTH-1:0] in_acc,   // 完整64项累加结果，signed40/Q28
    input  wire signed [`KWT_BIAS_WIDTH-1:0] in_bias, // 对应输出列的signed32/Q28偏置
    input  wire in_global_last,                  // 整个矩阵最后一个Y；不是乘法的block_last

    // ---- 下游握手与输出 ----
    output reg out_valid,                        // 当前寄存的Y和flags有效
    input  wire out_ready,                       // 下游能在本沿接收结果
    output reg signed [`KWT_Y_WIDTH-1:0] out_y,  // 最终signed16/Q12编码
    output reg [`KWT_FLAGS_WIDTH-1:0] out_flags  // 位0=raw溢出，位1=Y饱和，位2=全局last
);

    // ============================================================
    // 常量定义
    // ============================================================
    localparam integer QUOT_WIDTH = `KWT_ACC_WIDTH - `KWT_OUTPUT_SHIFT;

    // signed40 的饱和边界
    localparam signed [`KWT_ACC_WIDTH-1:0] ACC_MAX =
        {1'b0, {(`KWT_ACC_WIDTH-1){1'b1}}};
    localparam signed [`KWT_ACC_WIDTH-1:0] ACC_MIN =
        {1'b1, {(`KWT_ACC_WIDTH-1){1'b0}}};

    // signed16 的饱和边界
    localparam signed [`KWT_Y_WIDTH-1:0] Y_MAX =
        {1'b0, {(`KWT_Y_WIDTH-1){1'b1}}};
    localparam signed [`KWT_Y_WIDTH-1:0] Y_MIN =
        {1'b1, {(`KWT_Y_WIDTH-1){1'b0}}};

    // RNE 舍入的"半单位"阈值，固定为 16'h8000
    localparam [`KWT_OUTPUT_SHIFT-1:0] HALF =
        {1'b1, {(`KWT_OUTPUT_SHIFT-1){1'b0}}};

    // ============================================================
    // 第1步：符号扩展 + 加 bias + sat40
    // ============================================================
    // 易混淆点1：输入是已经累加完64项的acc，不是一个32位乘积。
    //   acc和bias都是Q28，不需要先移位来对齐；先分别符号扩展到41位再加。
    //   如果先做40位加法，结果可能已经回绕，之后无法恢复真实溢出信息。
    // 易混淆点2：加bias后先做sat40，再做舍入，不能只在最后检查一次溢出。
    //   41位和能装入signed40时，最高两位应相同；不同则超出40位范围。
    wire signed [`KWT_ADD_WIDTH-1:0] acc_ext;    // acc 符号扩展到41位
    wire signed [`KWT_ADD_WIDTH-1:0] bias_ext;   // bias 符号扩展到41位
    wire signed [`KWT_ADD_WIDTH-1:0] sum_ext;    // 41位临时和
    wire raw_overflow;                           // 41位和超出signed40范围
    wire signed [`KWT_ACC_WIDTH-1:0] raw;        // sat40 之后的累加值

    assign acc_ext = {in_acc[`KWT_ACC_WIDTH-1], in_acc};
    assign bias_ext = {
        {(`KWT_ADD_WIDTH-`KWT_BIAS_WIDTH){in_bias[`KWT_BIAS_WIDTH-1]}}, in_bias
    };
    assign sum_ext = acc_ext + bias_ext;
    assign raw_overflow = sum_ext[`KWT_ADD_WIDTH-1] ^ sum_ext[`KWT_ACC_WIDTH-1];
    assign raw = raw_overflow
        ? (sum_ext[`KWT_ADD_WIDTH-1] ? ACC_MIN : ACC_MAX)
        : sum_ext[`KWT_ACC_WIDTH-1:0];

    // ============================================================
    // 第2步：取绝对值，拆成商与余数（为 RNE 做准备）
    // ============================================================
    // 易混淆点3：右移前必须保留低16位作为舍入依据，不能先截断再找回余数。
    //   这里先取绝对值，再分成商和余数，正负数采用同一套最近偶数规则。
    //   magnitude必须是无符号40位：abs(-2^39)=2^39，不能放入signed40正数域。
    wire [`KWT_ACC_WIDTH-1:0] magnitude;         // raw 的绝对值（无符号40位）
    wire [QUOT_WIDTH-1:0] quotient;              // 除以2^16的商（高24位）
    wire [`KWT_OUTPUT_SHIFT-1:0] remainder;      // 除以2^16的余数（低16位）

    assign magnitude = raw[`KWT_ACC_WIDTH-1]
        ? (~raw + {{(`KWT_ACC_WIDTH-1){1'b0}}, 1'b1}) : raw;
    assign quotient = magnitude[`KWT_ACC_WIDTH-1:`KWT_OUTPUT_SHIFT];
    assign remainder = magnitude[`KWT_OUTPUT_SHIFT-1:0];

    // ============================================================
    // 第3步：RNE 舍入 + 恢复符号
    // ============================================================
    // 易混淆点4：RNE不是一律加0.5；恰好一半时，只有商为奇数才进位。
    //   例如+2.5->2、+3.5->4；恢复负号后，-2.5->-2、-3.5->-4。
    // 位宽说明：商为24位，补一位后再加进位，加法不会回绕；
    //   保留25位也使signed正数范围足够（舍入结果最大0x800000，
    //   在24位signed里正好是符号位，会被误读成负数）。
    wire round_up;                               // 1位，是否进位（RNE规则判断）
    wire [QUOT_WIDTH:0] rounded_magnitude;       // 25位无符号，商补0扩展后加上进位
    wire signed [QUOT_WIDTH:0] rounded;          // 25位有符号，恢复原来的符号

    assign round_up = (remainder > HALF) || ((remainder == HALF) && quotient[0]);
    assign rounded_magnitude = {1'b0, quotient} + {{QUOT_WIDTH{1'b0}}, round_up};
    assign rounded = raw[`KWT_ACC_WIDTH-1]
        ? -$signed(rounded_magnitude) : $signed(rounded_magnitude);

    // ============================================================
    // 第4步：sat16 + 输出 flags
    // ============================================================
    // 易混淆点5：先恢复符号并完成RNE，最后再sat16，不能提前截成16位。
    //   截断会丢掉"是否越界"的信息；所以比较两边都使用signed25，
    //   先把16位边界符号扩展到25位，判完溢出再钳位/截断。
    // 易混淆点6：global_last是整个矩阵最后一个Y，由坐标决定，与数值无关。
    localparam signed [QUOT_WIDTH:0] Y_MAX_EXT =
        {{(QUOT_WIDTH+1-`KWT_Y_WIDTH){Y_MAX[`KWT_Y_WIDTH-1]}}, Y_MAX};
    localparam signed [QUOT_WIDTH:0] Y_MIN_EXT =
        {{(QUOT_WIDTH+1-`KWT_Y_WIDTH){Y_MIN[`KWT_Y_WIDTH-1]}}, Y_MIN};

    wire output_saturated;                       // 舍入结果超出signed16范围
    wire signed [`KWT_Y_WIDTH-1:0] y_next;       // 最终16位结果
    wire [`KWT_FLAGS_WIDTH-1:0] flags_next;      // 位0=raw溢出，位1=Y饱和，位2=全局last

    assign output_saturated = (rounded > Y_MAX_EXT) || (rounded < Y_MIN_EXT);
    assign y_next = (rounded > Y_MAX_EXT) ? Y_MAX
                  : (rounded < Y_MIN_EXT) ? Y_MIN : rounded[`KWT_Y_WIDTH-1:0];
    assign flags_next[`KWT_FLAG_RAW_OVF_BIT] = raw_overflow;
    assign flags_next[`KWT_FLAG_Y_SAT_BIT] = output_saturated;
    assign flags_next[`KWT_FLAG_GLOBAL_LAST_BIT] = in_global_last;

    // ============================================================
    // 第5步：输出寄存 + valid/ready 握手
    // ============================================================
    // in_ready为组合逻辑：没有旧结果占着（!out_valid），或者旧结果
    // 这一拍恰好被下游取走（out_ready），本模块就能收新数据。
    // 复位中（rst_n=0）不能接收。时序上是否需要调整，在顶层连接与STA时核对。
    assign in_ready = rst_n && (!out_valid || out_ready);
    always @(posedge clk) begin
        if (!rst_n) begin
            out_valid <= 1'b0;
        end else if (in_ready) begin
            out_valid <= in_valid;
            if (in_valid) begin
                out_y     <= y_next;
                out_flags <= flags_next;
            end
        end
        // out_valid=1且out_ready=0时不赋值，Y/flags/valid全部保持。
    end

endmodule

`default_nettype wire
