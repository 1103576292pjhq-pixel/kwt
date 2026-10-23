`ifndef KWT_NUMERIC_CONFIG_VH
`define KWT_NUMERIC_CONFIG_VH

// 个人项目共享的 FFN 第一线性层数值基线：i16_w16_a40_o16_rne，版本 v0.1。
// 依据：docs/shared/numeric-format-v0.1.json 及配套 Markdown 说明。
// 计算核心、矩阵调度和存储接口可共同引用，统一同一数据对象的数值格式。
// 本文件只约定 FFN 第一线性层格式，其他算子使用前须另行确认数值规格。
// 以下常量须与共享规格一致，不能作为可随意调整的开关。
// 点积长度、加法临时位宽、状态编码和流水线级数由对应模块内部定义。
// SRAM 地址宽度、总线宽度和 CPU 寄存器地址由各自接口规格定义。

// 逻辑数值位宽：同时保留为旧点积核心的接口，不能直接改成V07容器宽度。
// 有符号补码：使用这些常量的模块仍须将相应信号声明为 signed。
`define KWT_FFN_X_WIDTH          16
`define KWT_FFN_W_WIDTH          16
`define KWT_FFN_PRODUCT_WIDTH    (`KWT_FFN_X_WIDTH + `KWT_FFN_W_WIDTH)
`define KWT_FFN_BIAS_WIDTH       32
`define KWT_FFN_ACC_WIDTH        40
`define KWT_FFN_OUT_WIDTH        16

// 尺度为 2^(-FRAC_BITS)；两个数相乘时，小数位数相加。
`define KWT_FFN_X_FRAC_BITS      12
`define KWT_FFN_W_FRAC_BITS      16
`define KWT_FFN_PRODUCT_FRAC_BITS (`KWT_FFN_X_FRAC_BITS + `KWT_FFN_W_FRAC_BITS)
`define KWT_FFN_BIAS_FRAC_BITS   (`KWT_FFN_PRODUCT_FRAC_BITS)
`define KWT_FFN_ACC_FRAC_BITS    (`KWT_FFN_PRODUCT_FRAC_BITS)
`define KWT_FFN_OUT_FRAC_BITS    12
`define KWT_FFN_OUT_SHIFT        (`KWT_FFN_ACC_FRAC_BITS - `KWT_FFN_OUT_FRAC_BITS)

// V07物理容器，依据20261023队友交接包的02_数值与接口契约.md、
// reference/fixed_numeric.py及quant_epilogue.sv；不改变上述v0.1逻辑格式。
// 新模块使用以下容器位宽，X/W/精确乘积仍使用上方的16/16/32位宏。
`define KWT_FFN_V07_BIAS_WIDTH   48
`define KWT_FFN_V07_ACC_WIDTH    48
`define KWT_FFN_V07_OUT_WIDTH    32

// bias：逻辑signed32必须符号扩展到48位，不能接受任意48位偏置。
// acc：48位保存原Q28整数，合法64项点积及偏置不会溢出逻辑signed40。
// out：先按原规则RNE右移16位并sat16，再符号扩展到32位，仍为Q12。
// 位宽扩大不意味着扩大输出饱和范围，也不允许改变尺度或舍入规则。

// V07输出flags有效字段；与oracle的bit定义一致。
// 本字段为3位；若外围使用8位存储容器，高5位应补0。
`define KWT_FFN_V07_FLAGS_WIDTH          3
`define KWT_FFN_V07_FLAG_OVERFLOW_BIT    0
`define KWT_FFN_V07_FLAG_SATURATED_BIT   1
`define KWT_FFN_V07_FLAG_LAST_BIT        2
`define KWT_FFN_V07_FLAGS_VALID_MASK     3'b111
// overflow：原始结果溢出标志；约定的合法输入范围内应为0。
// saturated：RNE后超出signed16范围并发生输出限幅。
// last：整个任务的最后一个输出记录，由外围生成或随结果透传；
//       不等于第64项乘积标志，也不等于当前计算小块的末项标志。

// PM/PN/CTX、打包总线顺序、流水级数和握手属于结构/接口约定，
// 尚未冻结，不在此数值头文件中定义；各模块不能自行改变共享数值规则。

// 运算规则：按 k=0..63 累加，每次加法及最后的偏置加法后均执行 sat40。
// 随后按 KWT_FFN_OUT_SHIFT 右移并进行 RNE 舍入（最近取整，中间值取偶数），
// 最后执行 sat16。以下宏只提供常量，不实现舍入或饱和电路。

`endif // 公共头文件包含保护结束
