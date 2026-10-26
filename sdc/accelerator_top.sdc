# =============================================================================
# accelerator_top: logical synthesis / ideal clock, NOT post-CTS sign-off SDC.
# kwt/feat/standalone-ffn-v07, reference 78f63dec27f6cf3d5853ffcbc54a2d1dd98cd9b9
# Source once AFTER elaborate/link. Do not also source synth/clock.sdc.
# rst_n: synchronous active-low. abort_i: synchronous active-high.
# 中文说明：预算集中在本文件顶部；150 MHz 及 I/O 数值仍是初跑假设。
# =============================================================================

# 可在 source 本文件前设置同名变量覆盖默认值。单位换算依据 report_units。
foreach {_name _default} {
    SYNTH_FREQUENCY_MHZ             150.0
    SYNTH_TIME_UNIT_NS              1.0
    SYNTH_CAP_UNIT_PF               1.0
    SYNTH_SETUP_UNCERTAINTY_NS       0.20
    SYNTH_HOLD_UNCERTAINTY_NS        0.05
    SYNTH_CLOCK_TRANSITION_NS        0.10
    SYNTH_INPUT_DELAY_MAX_NS         1.00
    SYNTH_INPUT_DELAY_MIN_NS         0.10
    SYNTH_OUTPUT_DELAY_MAX_NS        1.00
    SYNTH_OUTPUT_DELAY_MIN_NS       -0.10
    SYNTH_INPUT_TRANSITION_NS        0.10
    SYNTH_OUTPUT_LOAD_PF            0.02
    SYNTH_CONTROL_DELAY_MAX_NS       1.00
    SYNTH_CONTROL_DELAY_MIN_NS       0.10
    SYNTH_BUDGET_CONFIRMED           0
} {
    if {![info exists $_name]} {set $_name $_default}
}
# SYNTH_TIME_UNIT_NS: 一个工具时间单位等于多少 ns；ps 填 0.001。
# SYNTH_CAP_UNIT_PF: 一个工具电容单位等于多少 pF；fF 填 0.001。
# 先核对 00_units.rpt；这里的 1 ns / 1 pF 不是从 .db 自动检测的结果。
# OUTPUT_DELAY_MIN=-0.10 暂按下游 hold=0.10 ns 建模，有意使用负号。
# OUTPUT_LOAD=0.02 pF = 20 fF，表示 block 外部负载，不是 SRAM 内部负载。
# CONTROL_DELAY 单独约束 rst_n/abort_i，由其上游同步控制逻辑决定。
# CONFIRMED=1 仅表示预算已确认，不能据此声明时序或功耗 sign-off。

foreach _name {
    SYNTH_FREQUENCY_MHZ SYNTH_TIME_UNIT_NS SYNTH_CAP_UNIT_PF
    SYNTH_SETUP_UNCERTAINTY_NS SYNTH_HOLD_UNCERTAINTY_NS
    SYNTH_CLOCK_TRANSITION_NS SYNTH_INPUT_DELAY_MAX_NS SYNTH_INPUT_DELAY_MIN_NS
    SYNTH_OUTPUT_DELAY_MAX_NS SYNTH_OUTPUT_DELAY_MIN_NS
    SYNTH_INPUT_TRANSITION_NS SYNTH_OUTPUT_LOAD_PF
    SYNTH_CONTROL_DELAY_MAX_NS SYNTH_CONTROL_DELAY_MIN_NS
} {
    set _value [set $_name]
    if {![string is double -strict $_value] ||
        [regexp -nocase {nan|inf} $_value]} {
        error "$_name must be a finite number, got: $_value"
    }
}
foreach _name {SYNTH_FREQUENCY_MHZ SYNTH_TIME_UNIT_NS SYNTH_CAP_UNIT_PF} {
    if {[set $_name] <= 0.0} {error "$_name must be positive"}
}
foreach _name {
    SYNTH_SETUP_UNCERTAINTY_NS SYNTH_HOLD_UNCERTAINTY_NS
    SYNTH_CLOCK_TRANSITION_NS SYNTH_INPUT_TRANSITION_NS SYNTH_OUTPUT_LOAD_PF
} {
    if {[set $_name] < 0.0} {error "$_name must be nonnegative"}
}
foreach {_minimum _maximum} {
    SYNTH_INPUT_DELAY_MIN_NS SYNTH_INPUT_DELAY_MAX_NS
    SYNTH_OUTPUT_DELAY_MIN_NS SYNTH_OUTPUT_DELAY_MAX_NS
    SYNTH_CONTROL_DELAY_MIN_NS SYNTH_CONTROL_DELAY_MAX_NS
} {
    if {[set $_minimum] > [set $_maximum]} {
        error "$_minimum must be <= $_maximum"
    }
}
if {![string is boolean -strict $SYNTH_BUDGET_CONFIRMED]} {
    error "SYNTH_BUDGET_CONFIRMED must be Boolean"
}
proc ffn_ns {value} {return [expr {$value / $::SYNTH_TIME_UNIT_NS}]}

# 依据真实 accelerator_top 端口检查。总线名用 *，不用未转义的 [n]。
foreach _pattern {
    clk rst_n abort_i in_valid in_ready in_op* in_layer_id* in_task_id*
    in_tile_id* in_index* in_data* in_shift* out_valid out_ready
    out_task_id* out_y_index* out_data* out_flags* task_done busy fault error_code*
} {
    if {[sizeof_collection [get_ports -quiet $_pattern]] == 0} {
        error "Missing accelerator_top port group: $_pattern; check top/RTL revision"
    }
}
foreach _port {clk rst_n abort_i} {
    if {[sizeof_collection [get_ports $_port]] != 1} {
        error "Expected exactly one scalar port: $_port"
    }
}
if {[sizeof_collection [all_clocks]] != 0} {
    error "Clocks already exist. Source this SDC once; do not also source synth/clock.sdc"
}
set _ffn_clk [get_ports clk]
set _ffn_sync_controls [get_ports {rst_n abort_i}]
set _ffn_inputs [remove_from_collection [all_inputs] $_ffn_clk]
set _ffn_data_inputs [remove_from_collection $_ffn_inputs $_ffn_sync_controls]
set _ffn_outputs [all_outputs]
if {[sizeof_collection $_ffn_data_inputs] == 0 ||
    [sizeof_collection $_ffn_outputs] == 0} {
    error "Empty accelerator_top interface collection"
}

set SYNTH_CLOCK_NAME accel_clk
set SYNTH_CLOCK_PERIOD_NS [expr {1000.0 / $SYNTH_FREQUENCY_MHZ}]
create_clock -name $SYNTH_CLOCK_NAME \
    -period [ffn_ns $SYNTH_CLOCK_PERIOD_NS] $_ffn_clk
set_clock_uncertainty -setup [ffn_ns $SYNTH_SETUP_UNCERTAINTY_NS] \
    [get_clocks $SYNTH_CLOCK_NAME]
set_clock_uncertainty -hold [ffn_ns $SYNTH_HOLD_UNCERTAINTY_NS] \
    [get_clocks $SYNTH_CLOCK_NAME]
set_clock_transition [ffn_ns $SYNTH_CLOCK_TRANSITION_NS] \
    [get_clocks $SYNTH_CLOCK_NAME]

# 包含 out_ready、in_valid 和所有命令/数据输入。in_shift 也不能固定成常量，
# 因为非法 shift 的检测属于模块功能的一部分。
set_input_delay -max [ffn_ns $SYNTH_INPUT_DELAY_MAX_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_data_inputs
set_input_delay -min [ffn_ns $SYNTH_INPUT_DELAY_MIN_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_data_inputs
set_input_delay -max [ffn_ns $SYNTH_CONTROL_DELAY_MAX_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_sync_controls
set_input_delay -min [ffn_ns $SYNTH_CONTROL_DELAY_MIN_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_sync_controls
set_input_transition [ffn_ns $SYNTH_INPUT_TRANSITION_NS] $_ffn_inputs
set_output_delay -max [ffn_ns $SYNTH_OUTPUT_DELAY_MAX_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_outputs
set_output_delay -min [ffn_ns $SYNTH_OUTPUT_DELAY_MIN_NS] \
    -clock $SYNTH_CLOCK_NAME $_ffn_outputs
set_load [expr {$SYNTH_OUTPUT_LOAD_PF / $SYNTH_CAP_UNIT_PF}] $_ffn_outputs

# 不切掉 rst_n/abort_i：同步控制要检查 setup/hold，另有组合握手门控路径。
# SRAM 地址/数据/使能的 setup/hold 和 CLK->Q 使用宏 .db 自带时序弧。
# 不对 SRAM CLK 设置独立 generated clock，不将 SRAM 端口视作顶层 I/O。
# READ_LATENCY=1/2、64 项点积和 3/4 拍供数间隔都不是 multicycle 的依据。
# 此处不加 false_path、case_analysis、multicycle、propagated_clock 或 fix_hold。
# 库自带 DRV 约束继续生效；不凭空加 max_fanout/max_area/全局 dont_touch。
if {!$SYNTH_BUDGET_CONFIRMED} {
    puts "WARNING: PROVISIONAL clock/I-O/control/slew/load budgets; confirm with SoC integration."
}
puts "INFO: $SYNTH_CLOCK_NAME = $SYNTH_CLOCK_PERIOD_NS ns; configured units = $SYNTH_TIME_UNIT_NS ns / $SYNTH_CAP_UNIT_PF pF"
