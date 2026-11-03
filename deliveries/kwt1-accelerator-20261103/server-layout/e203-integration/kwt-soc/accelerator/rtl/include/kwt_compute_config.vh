// 头文件保护：第一次引用时定义下面的标记，重复引用时跳过整个文件，
// 避免同一批宏被重复定义。这两行本身不描述任何硬件。
`ifndef KWT_COMPUTE_CONFIG_VH
`define KWT_COMPUTE_CONFIG_VH

// 计算底座的公共常量，绑定冻结规格 KWT1-FFN1。
// 这些宏用于统一命名、消除重复数字，不表示支持任意修改配置。
// 数值来源：model/numeric-contract.json；结构来源：docs/architecture/。
// 后续编译时将 rtl/include 加入头文件搜索路径，例如 -I rtl/include。
// 本文件没有输入输出端口：`define定义常量，模块用反引号加宏名引用。
// 例如 wire signed [`KWT_X_WIDTH-1:0] x_lane; 表示一个16位有符号信号。

// -------- 内部算术位宽（均为二进制补码有符号数） --------
// 宏只定义位数；实际算术信号仍须显式声明 signed。
// 总位宽已经包含符号位，不需要再额外增加一位。
// 单个X元素的位宽；对应乘法模块拆出的x_lane，取值-32768..32767。
`define KWT_X_WIDTH          16
// 单个W元素的位宽；对应w_lane，取值同X。相同位宽不代表小数位相同。
`define KWT_W_WIDTH          16
// 单路完整乘积的位宽；对应product_comb，16×16乘法保留全部32位。
`define KWT_PRODUCT_WIDTH    32
// 每个输出列的bias有效位宽；在量化模块中加到该列的点积结果上。
`define KWT_BIAS_WIDTH       32
// 单个累加值acc的位宽；保存一个输出的64项乘积和，沿用已确认的40位。
// 乘积进入acc前须从32位符号扩展到40位，不得按无符号补零。
`define KWT_ACC_WIDTH        40
// 加bias的临时和为41位；acc40和bias32均先符号扩展到41位再相加，
// 用额外的一位检测是否超出signed40范围，再执行sat40。
`define KWT_ADD_WIDTH        (`KWT_ACC_WIDTH + 1)
// 最终内部Y的有效位宽；RNE舍入后饱和到-32768..32767，再保存为16位。
`define KWT_Y_WIDTH          16

// -------- 固定小数位与量化尺度 --------
// 小数位数表示缩放关系：真实数值 = 有符号编码整数 / 2^小数位数。
// RTL存放的是整数位图，没有单独的“小数点”信号。
// X有12个小数位，例如编码4096表示真实值1.0。
`define KWT_X_FRAC           12
// W有16个小数位，例如编码16384表示真实值0.25。
`define KWT_W_FRAC           16
// 乘积小数位数为12+16=28；乘法之后保留Q28精度，不逐项提前右移。
`define KWT_PRODUCT_FRAC     28
// bias也为Q28，与乘积和尺度相同，因此可以直接做整数加法。
`define KWT_BIAS_FRAC        28
// 累加不改变尺度，acc仍为Q28；增加总位宽用于容纳更大的和。
`define KWT_ACC_FRAC         28
// Y为Q12，最终编码除以4096才能还原为真实数值。
`define KWT_Y_FRAC           12
// Q28 -> Q12需要右移28-12=16位；结合被丢弃的低位执行RNE最近偶数舍入。
// 这是固定转换尺度，不是运行时shift端口，不能只截高位代替舍入。
`define KWT_OUTPUT_SHIFT     (`KWT_ACC_FRAC - `KWT_Y_FRAC)

// -------- flags有效位；全局last不是乘法流水的block_last --------
// 一个Y结果对应3位flags。它们是独立标志，不是有符号数。
`define KWT_FLAGS_WIDTH      3
// flags[0]：acc加bias的41位临时和超出signed40范围时置1。
// 合法K64任务不会触发；量化组件仍保留任意acc40输入的溢出测试语义。
`define KWT_FLAG_RAW_OVF_BIT  0
// flags[1]：RNE舍入后的结果超出signed16范围、发生最终限幅时置1。
`define KWT_FLAG_Y_SAT_BIT    1
// flags[2]：整个矩阵最后一个Y，即Y[98,255]时置1，由外围坐标决定。
// 它不等于当前4×16块的结束标记in_block_last/out_block_last。
`define KWT_FLAG_GLOBAL_LAST_BIT 2

// -------- 正式任务与16MAC/CTX4计算结构 --------
// M是X/Y的总行数：X[99,64]，Y[99,256]。
`define KWT_M                99
// K是每个点积的乘积项数，也是X的列数、W的行数；k按0..63递增。
`define KWT_K                64
// N是W/Y的总列数：W[64,256]，每列对应一个bias，共256个bias。
`define KWT_N                256
// PM是每组并行处理的X行数：一次输入四个X，尾行组只有三行有效。
`define KWT_PM               4
// PN是每组并行处理的W列数：一次输入四个W，与四个X交叉形成16个乘积。
`define KWT_PN               4
// CTX是独立累加上下文数量：g0..g3各保存一组4×4的acc。
// 固定k时轮转四个g，再进入下一个k；上下文增加状态，不增加乘法器。
`define KWT_CTX              4
// 上下文编号的位宽：2位可表示0..3，对应in_ctx/out_ctx。
// 这是编号宽度；若另设包含“4”这个完成值的计数器，则不能只用2位。
`define KWT_CTX_WIDTH        2
// 块内行p、并行列q各为0..3；用于顶层拆分acc地址及映射结果位置。
`define KWT_ROW_INDEX_WIDTH  2
`define KWT_COL_INDEX_WIDTH  2
// k索引的位宽：6位可表示0..63；它不能表示完成计数64。
`define KWT_K_INDEX_WIDTH    6
// 每行一位的有效掩码，共PM=4位，对应in_row_mask/out_row_mask。
// 位p=1表示第p行有效；普通行组为4'b1111，最后三行为4'b0111。
`define KWT_ROW_MASK_WIDTH   `KWT_PM

// -------- 由上述常量推导的数据量与打包总线位宽 --------
// 并行乘法通路数：PM×PN=4×4=16，对应16个乘法器及16个乘积位置。
`define KWT_MAC_LANES        (`KWT_PM * `KWT_PN)
// 当前输出块覆盖的列数：四个上下文各覆盖四列，总共16列。
`define KWT_BLOCK_COLS       (`KWT_CTX * `KWT_PN)
// 累加值总数：CTX×16=64，每个acc为40位；不是64个乘法器。
`define KWT_ACC_COUNT        (`KWT_CTX * `KWT_MAC_LANES)
// 累加选读/写入地址的位宽：6位覆盖64个acc的编号0..63。
// 地址=ctx*16+p*4+q；这是acc内部顺序，最终Y的块内排列由后续控制映射。
// 它只表示元素地址，若另设计数器需要表示完成值64，则应使用7位。
`define KWT_ACC_ADDR_WIDTH   6
// 块内bias列号=g*4+q，共16列，需要4位；同一列的各行复用同一个bias。
`define KWT_BIAS_ADDR_WIDTH  (`KWT_CTX_WIDTH + `KWT_COL_INDEX_WIDTH)
// 结果位置=row*16+g*4+q，共64个位置；位宽同为6，但含义不同于acc地址。
`define KWT_RESULT_INDEX_WIDTH (`KWT_ROW_INDEX_WIDTH + `KWT_BIAS_ADDR_WIDTH)
// 接收组计数要表示0..256（含完成值），需要9位，不能使用只有8位的索引。
`define KWT_GROUP_COUNT_WIDTH 9
// 一个块需要的有效计算组数：K×CTX=64×4=256，不包含清零、排空或量化。
// 这是组数常量，不是计数器位宽，也不代表完成整个块只需256个时钟。
`define KWT_GROUPS_PER_BLOCK (`KWT_K * `KWT_CTX)
// X打包输入总线宽度：4×16=64位，对应in_x；它装四个16位数。
`define KWT_X_GROUP_WIDTH    (`KWT_PM * `KWT_X_WIDTH)
// W打包输入总线宽度：4×16=64位，对应in_w；它装四个16位数。
`define KWT_W_GROUP_WIDTH    (`KWT_PN * `KWT_W_WIDTH)
// 乘积打包输出宽度：16×32=512位，对应out_product。
// 第lane个乘积占[lane*32 +: 32]；lane=p*PN+q，p选X行、q选W列。
`define KWT_PRODUCT_GROUP_WIDTH (`KWT_MAC_LANES * `KWT_PRODUCT_WIDTH)

// legacy命令48位、共享bias64位、共享Y32位属于外围传输容器，
// 不用于推导本文件中的内部算术位宽；本阶段不实现这些外围接口。

// 结束头文件保护范围。
`endif // KWT_COMPUTE_CONFIG_VH
