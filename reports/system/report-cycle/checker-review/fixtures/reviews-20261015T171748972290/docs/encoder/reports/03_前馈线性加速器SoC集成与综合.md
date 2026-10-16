# 03 前馈线性加速器SoC集成与综合

SoC集成要证明真实E203能装载输入、启动硬件、等到完整结果并写回共享存储。当前公开E203已执行生产C驱动，完成一个99×64×256整数FFN1案例及独立复跑，各25344项Y与flags逐项一致；generic综合已检查通用逻辑及四个同步存储银行。正式比赛平台、指定工艺库、时序约束、面积/功耗及综合后功能仍属外部待验，因此正式任务3尚不能整体宣布达标。

## 本章知识全景图

| 问题 | 本设计的回答 | 可检查对象 |
|---|---|---|
| CPU怎样使用加速器 | 通过ICB映射寄存器，逐字搬运，不用软件代算 | CPU总线事务、生产驱动 |
| 结果怎样可靠返回 | 同步行读完成后响应，数据与flags存好后ACK | 桥状态机、驱动、CPU共享SRAM写口 |
| 错误怎样传播 | 本次总线err、历史sticky error、驱动返回码分别处理 | 错误寄存器、负测和故障注入 |
| 怎样证明真实CPU执行 | 运行RV32固件，观察取指、MMIO、输出与完成邮箱 | ELF、真实仿真输出、逐项回读 |
| 综合证明了什么 | RTL可转换为通用逻辑，保持有符号乘法与同步存储结构 | Yosys JSON、日志和源绑定 |
| 还缺什么 | 指定平台和库下的完整综合、时序、面积、功耗及综合后验证 | 正式网表、SDC、工艺报告 |

学习路径：先看系统数据流，再看寄存器和驱动调用，最后判断不同测试证据能支持多强的结论。

## 1. 正式任务与本地交付范围

《2026赛题指南》印刷第7页任务3（1）要求将任务1—2接入E203，完成驱动、数据交换、启动与完成状态管理，并通过SoC仿真；印刷第8页任务3（2）要求逻辑综合，并提交RTL、测试平台、综合网表、时序约束、面积和功耗估算，记录任务周期和吞吐量。完成任务1—3才完成本科全部必做内容。来源见[指南PDF](../../../work/report_cycle_sources/2026赛题指南.pdf)。

指南印刷第4页给出加速器2.25mm²面积上限；印刷第9页任务7列出150MHz和综合前后功能检查，印刷第11页的SoC/综合评分还明确要求两组工程均满足150MHz，并评价综合前后功能一致性。本工程把正式平台/库下的这些指标统一列为待验，不能将本科任务3解释为只需生成generic网表。

本地使用公开上游E203/HBirdv2固定提交9f3e34f337f5d0a1236a285871ffa2032491617a，SDK固定提交0e0e9083569721578c42f07a95b05a26c0760db6。上游保持只读，薄外壳接出系统总线；官方源与SDK共1459个清单条目。公开版本不等于组委会专用平台包，详见[平台来源](../../../docs/platform/official-sources.md)和[上游清单](../../../config/e203-source-manifest.json)。

数值任务仍是

$$
Y[99,256]=X[99,64]W[64,256]+b[256].
$$

实际硬件采用signed16输入/权重、signed48累加和偏置、signed49偏置临时和、先sat48再RNE右移和sat32的规则。CPU只搬运整数编码，不执行该矩阵运算。每个结果附raw48溢出与output32饱和标志；完整规则见[报告1](01_乘累加与数值处理模块.md)、[报告2](02_前馈线性加速器.md)。

## 2. 系统架构与真实数据流

数据流：主机离线生成冻结X/W_pack/b → 初始化共享SRAM原始输入 → E203执行生产驱动 → sysper ICB写加速器寄存器 → FFN1内部同步RAM与DOT64计算 → ICB逐项读Y/flags → E203写共享SRAM → main返回 → 启动代码写完成邮箱 → 被动监视与独立文件回读逐项验算。

| 组件 | 接口与责任 | 源码入口 |
|---|---|---|
| 上游E203子系统 | 执行真实RV32指令，含原有ITCM/DTCM与外设 | [固定源清单](../../../config/e203-source-manifest.json) |
| CPU薄外壳 | 实例化上游e203_subsys_top，接出sysper/sysmem；保持默认PLL旁路与PMU配置 | [e203_cpu_shell.sv](../../../soc/e203_common/e203_cpu_shell.sv) |
| 共享SRAM模型 | 0xa0000000起512KiB，一笔在途，支持字节写掩码、同步读 | [icb_shared_ram.sv](../../../soc/e203_common/icb_shared_ram.sv) |
| FFN1 ICB桥 | 0x11000000起256字节窗口，一笔在途，寄存器协议及错误管理 | [ffn1_icb.sv](../../../rtl/ffn1_icb.sv) |
| FFN1核心 | 完整装载、矩阵计算、逐行保持与ACK | [ffn1_top.sv](../../../rtl/ffn1_top.sv) |
| 可移植驱动 | 固定寄存器次序、有限轮询、输出复制和错误传播 | [头文件](../../../sw/ffn1_driver.h)、[实现](../../../sw/ffn1_driver.c) |
| E203适配层 | volatile 32位MMIO，前后fence iorw,iorw；指定共享地址 | [main.c](../../../sw/e203_ffn1/main.c) |
| 系统验证台 | 初始化固件/输入，被动观察真实总线，不代发加速器命令 | [tb_e203_ffn1.sv](../../../dv/e203_ffn1/tb_e203_ffn1.sv) |

没有DMA：CPU从共享SRAM取X/W/b，逐字提交到加速器内部RAM，再从行缓冲读取输出并存回共享SRAM。内部四银行约46.94KiB逻辑容量与外部512KiB共享容量分别存在。存储模型不逐字复位，测试或固件必须初始化所有被读取的字；控制有效性复位不等于SRAM内容清零。

### 2.1 完整案例的共享地址

| 区域 | 地址范围 | 格式或用途 |
|---|---|---|
| 完成邮箱 | 0xa0000000…0xa0000013 | BOOT/TRAP魔数、main返回值、mcause、mepc、mcycle低32位 |
| 配置 | 0xa0000100…0xa000010f | M、N、shift等固定配置 |
| X | 0xa0001000…0xa000417f | 6336个int16 |
| W_pack | 0xa0005000…0xa000cfff | 16384个int16，按[n][64] |
| bias | 0xa000d000…0xa000d7ff | 256个int64容器，实际值限制signed48 |
| Y | 0xa0010000…0xa0028bff | 25344个int32 |
| flags | 0xa0030000…0xa00362ff | 25344个uint8 |
| 共享容量边界 | 0xa0000000…0xa007ffff | 524288字节 |

ITCM位于0x80000000，DTCM位于0x90000000；本固件入口0x80000000。这些地址是当前公开平台的初稿映射，迁移比赛平台时必须重新核对译码与链接布局。

## 3. ICB命令、同步读与错误契约

### 3.1 寄存器映射

所有偏移相对0x11000000。访问必须字对齐；写操作要求wmask=0xf。RO只读，WO只写，RW可读写。

| 偏移 | 名称/权限 | 值与作用 |
|---:|---|---|
| 0x00 | ID，RO | 0x4b575431 |
| 0x04 | STATUS，RO | bit0 busy、bit1 loaded、bit2 row_ready、bit3 done、bit4任一sticky error |
| 0x08 | COMMAND，WO | 写1开始新装载；写2启动计算，其余值非法 |
| 0x0c | ERROR，RW/W1C | 低5位写1清对应历史错误；高位非零非法 |
| 0x10 | SHIFT，RW | 0…47，busy时禁止改 |
| 0x14 | LOAD_KIND，RW | 0=X、1=W_pack、2=b；busy时禁止改 |
| 0x18 | LOAD_ADDR，RW | 当前银行字地址，busy时禁止改 |
| 0x1c | LOAD_LO，RW | 低32位暂存，每次写成功置fresh_lo |
| 0x20 | LOAD_HI，RW | 偏置高16位，写入高16位必须为0；成功置fresh_hi |
| 0x24 | LOAD_COMMIT，WO | 写1提交一个元素，并消费本次LO/HI新鲜标记 |
| 0x28 | ROW_INDEX，RO | 当前行号 |
| 0x2c | ROW_ADDR，RW | 0…N−1；计算未到row_ready时禁止改 |
| 0x30 | ROW_DATA，RO | 发起同步行读，等待真实读有效后才返回 |
| 0x34 | ROW_FLAGS，RO | bit0 overflow、bit1 saturated、bit2 valid；对应最近成功ROW_DATA |
| 0x38 | ROW_ACK，WO | 写当前行号释放该行 |
| 0x3c | GEOMETRY，RO | 高16位N，低16位M |
| 0x40 | DOT_LENGTH，RO | 64 |

未定义偏移、越出256字节窗口、权限错误、掩码错误及非法值都返回本次icb_rsp_err，并记录原因。ERROR位分别为：bit0地址、bit1访问类型/掩码、bit2值、bit3缺少新LO/HI、bit4核心/忙状态错误。STATUS.bit4表示历史错误存在，不等同于每个后续合法事务都要返回err。

### 3.2 为什么要等待核心的延迟反馈

桥状态链为 IDLE → EXEC → CORE_WAIT → CORE_CHECK → RESPONSE → IDLE。

IDLE只在cmd_valid且cmd_ready时捕获地址、方向、数据和掩码。EXEC作寄存器检查，普通寄存器可直接登记响应；核心命令只脉冲一次load_begin、load_valid、start、row_rd_en或row_ack，再等待核心时序。

FFN1的command_error与row_rd_valid在时钟沿更新。若EXEC发命令后立即答成功，可能错过下一拍错误，或把旧行数据当新结果。CORE_WAIT/CORE_CHECK为核心完成同步处理留出时间；读操作只有row_rd_valid为1才锁存Y与flags并发响应。

响应未消费时cmd_ready=0，rsp_valid、rdata和err保持。消费者反压不能改变已提交的响应。复位撤销在途事务并清控制状态，恢复后须从新任务完整装载。

### 3.3 新LO/HI防止拼入旧偏置

X/W的LO必须是signed16的正确32位符号扩展，如−1必须写0xffffffff，而非0x0000ffff。偏置是signed48，拆成LO32与HI16；−1的两部分分别为0xffffffff和0x0000ffff。

每个X/W提交必须有新LO；每个偏置提交必须同时有新LO和新HI。对齐且在窗口内的LOAD_COMMIT写尝试会消费两者，包括错误值、错误掩码、忙时或核心拒绝；失败后必须重新写本元素的全部必要部分，不能直接重试COMMIT。

ROW_FLAGS在成功ROW_DATA后锁存有效位及数值标志；开始新装载、START或ACK后清除。软件不能在尚未成功读DATA时把旧flags当成当前列的结果。

## 4. 生产C驱动怎样完成一个任务

调用入口为

~~~c
int kwt1_run(const kwt1_io *io, uint32_t m, uint32_t n,
             const int16_t *x, const int16_t *w_pack,
             const int64_t *bias, uint32_t shift,
             int32_t *y, uint8_t *flags, uint32_t poll_limit);
~~~

调用者分配不重叠且运行期间有效的数组；flags可为空，其他数据指针不可空。m/n必须与硬件GEOMETRY精确一致，K必须64，bias必须能表示为signed48，shift为0…47。驱动是阻塞、单拥有者接口，不提供并发仲裁。

实际执行链：

参数/bias48检查 → 读ID/GEOMETRY/K → 检查空闲和历史ERROR → COMMAND=1 → 写SHIFT → 装满X/W/b → 等loaded → COMMAND=2 → 等每行row_ready → 核对行号 → 每列写ROW_ADDR、读DATA、读FLAGS并检查valid → 拷贝完整行Y/flags → ACK当前行 → 等最终DONE且不busy → 检查ERROR=0。

驱动有意不自动清历史错误，避免把上一次失败伪装成正常开始；不自动重试I/O或ACK，避免事务是否已生效不明时重复释放一行。失败后已有部分输出和仍busy的任务可能保留，调用者应记录并显式恢复。

| 返回码 | 触发含义 |
|---|---|
| 0，KWT1_OK | 任务完整完成，最终ERROR=0 |
| −1，ARGUMENT | 指针/维度/shift/poll_limit/bias非法，或RV32输出容量界超限 |
| −2，IO | 回调报告本次总线失败，立即停止 |
| −3/−4，ID/GEOMETRY | IP标识或M/N/K不匹配 |
| −5，BUSY | 调用开始时前一任务未结束 |
| −6，CORE | 硬件状态或ERROR报告错误 |
| −7，TIMEOUT | 一次loaded/行/DONE等待耗尽轮询额度 |
| −8，PROTOCOL | 保留状态位、提前DONE、错行号、无效flags等违约 |

poll_limit限制的是每次等待中的STATUS读取次数，不是整个任务周期；一个不返回的底层回调不能被它中断。E203适配层用volatile访问与fence保持顺序，但平台总线故障的异常恢复仍需平台定义。

负偏置先转uint64再拆位，避免负有符号数右移的实现差异；负ROW_DATA通过明确定义的算术恢复int32，避免依赖超范围unsigned转signed。详见[驱动调用说明](../../../tests/driver/README.md)。

## 5. 验证覆盖与真实CPU结果

### 5.1 先区分三类测试

| 层级 | 实际覆盖与结果 | 能证明什么 |
|---|---|---|
| C host协议 | 1060项通过；1014个成功路径I/O位置逐一注入失败；UBSan；8种可编译变异全拒绝 | 驱动次序、数据拆装、错误传播、轮询和ACK责任 |
| ICB BFM | 5720笔协议事务、两个连续小任务、24输出；36个完整任务912384输出零差；4种行为变异全拒绝 | 桥与核心公开总线功能，不是CPU执行 |
| 真实E203 | 小矩阵Icarus/Verilator交叉运行；一个完整案例及独立进程复跑 | 上游CPU实际执行生产固件与驱动的系统闭环 |

证据分别见[驱动结果](../../../reports/system/driver/result.json)、[ICB验证](../../../reports/system/icb/verification.md)、[CPU机器结果](../../../reports/system/e203-ffn1/result.json)。驱动还真实编译为RV32IMAC/ILP32 freestanding对象，未定义符号为空；目标架构编译不能单独替代真实CPU运行。

正常、边界、复位和连续任务分层覆盖：DOT64测试有正负极值/舍入/复位中断及连续任务；核心和ICB测试有busy拒绝、错行/重复ACK、同步读、响应反压、在途响应/运算中复位和重新完整装载；驱动测试有旧DONE进入下一任务、部分输出失败、最终错误及三类超时。真实CPU完整案例不冒称覆盖全部这些故障组合。

### 5.2 真实CPU怎样排除测试台代算

系统测试台只向ITCM初始化固件、向共享SRAM初始化原始输入，参考Y与flags保留在CPU不可见的测试环境。共享输出区用0xa5毒化；所有装载、START、行ACK与结果写回都来自E203真实ICB端口。

结果逐项经过三次核对：CPU向共享SRAM写事务时比较每个索引/数值/掩码；完成后再比较最终SRAM；Python读取全部文本记录再核对索引和值。文件SHA用于独立复跑一致性，不替代逐项比较。具体观测边界见[observability.md](../../../reports/system/e203-ffn1/observability.md)。

完成条件同时要求main返回0、邮箱BOOT=0x424f4f54、完整输出和flags数量、装载数、一次START及99个顺序ACK。DONE由生产驱动wait_status(WAIT_DONE)和最终ERROR检查读取；测试台没有独立的“DONE响应次数”计数字段，不能把它写成另一次独立被动观测。

| 实际运行 | 结果 |
|---|---|
| main故意返回−77 | 真实CPU运行后验收非零退出1；BOOT魔数没有掩盖错误返回 |
| M=3、N=4，Icarus | 12项Y和flags一致，67423周期，退出0 |
| 同一小矩阵，Verilator | 相同67423周期、数值、flags、事务计数与文件SHA，退出0 |
| 验证环境参考第0项翻转一位 | CPU实际写回时检测ffffc9bc与ffffc9bd不符，非零退出−6 |
| M=99、N=256，Verilator | 25344项Y和flags全部一致，8595787周期，退出0 |
| 独立进程完整复跑 | 再次25344项Y和flags一致，周期与计数相同，文件SHA相同 |

完整案例是 eight_750e3e75_nohash_0/layer_01，来自现有unknown类validation输入；虽然文件名含eight，不把它标成赛题十二个输出类中的“eight类”。真实CPU只覆盖这一个完整案例加复跑，不是36案例或官方600样本。

### 5.3 周期与吞吐量边界

每个完整CPU进程的观测如下，首次运行和复跑一致：

| 指标 | 实测值 | 计数边界 |
|---|---:|---|
| 外部cycles | 8595787 | 复位释放至完成邮箱响应 |
| CPU mcycle快照 | 8591418 | main返回后启动代码读取CSR |
| 取指/派发握手 | 4865042 | ifu_o_valid且ifu_o_ready，**不是退休指令数** |
| 加速器MMIO读/写 | 74159 / 94633 | E203真实sysper端口握手 |
| 输入装载提交 | 22976 | 6336+16384+256 |
| START/行ACK | 1 / 99 | 真实命令写握手 |
| 数值/flags写回 | 25344 / 25344 | 真实共享SRAM写口 |
| 首次MMIO/START周期 | 7598 / 3006437 | 相对外部cycles |
| 最后数值写回/最后ACK | 8595544 / 8595581 | 同上 |

首次MMIO到完成邮箱为8588189周期，包含CPU、装载、总线等待、轮询、计算、逐行读回/写回和返回开销。它不能与仅计START后内核活动的2107743周期混作同一口径。

指南印刷第11页的正式性能窗口从输入和参数开始装载计时，至结果全部写回结束；每任务开始前清空任务数据与参数缓存，装载、总线等待与E203调度全部计入。正式本科12任务覆盖12层参数，且每次各满足3%误差门槛。当前首次MMIO至邮箱还包含标识检查和返回等额外开销，既不是该窗口的精确起止记录，也不是指定12任务测量，须在正式冻结配置上另行采集。

已知某个签核频率 \(f\) 与相同任务计数 \(C\) 后，时延为 \(C/f\)，单任务批量1的吞吐量为 \(f/C\)。当前只有行为周期，尚无工艺时序签核频率，故不把仿真时钟设置或仿真器墙钟速度当作150MHz能力或正式吞吐量。

两个完整CPU输出文本SHA分别为：Y为4c821e0e77cc29b9d6bb9d85e4c5d56be211215350a1191b5475e45d9128b230；flags为c6e16e719898323d0f4d7756a9164980cdef69b484f81ee711451ed82d4d1022。完整result.json SHA为194817bb7c5743077b17baf58ebcdfa857e26d100741e44cec9046d8fb46e368；[独立回读记录](../../../reports/system/e203-ffn1/independent-readback.md)核对两轮全部输出与冻结输入。

## 6. Generic综合：结构结果与正式缺口

### 6.1 实际执行的综合检查

[run_ffn1_synth.py](../../../dv/synthesis/run_ffn1_synth.py)用Yosys0.33依次执行两个顶层。流程为读取SystemVerilog → hierarchy -check → proc → opt → memory_dff → memory_collect → opt_clean → check -assert → 输出统计、JSON和generic Verilog。

| 顶层 | 退出码 | Generic cells | 乘法单元 | 存储 |
|---|---:|---:|---|---|
| ffn1_top | 0 | 283 | 1个16×16→32的有符号`$mul` | 4个`$mem_v2` |
| ffn1_icb | 0 | 590 | 同上 | 同样4个`$mem_v2` |

四银行分别为6336×16、16384×16、256×48、256×34；每个存储的RD_CLK_ENABLE=1。乘法单元的A_SIGNED与B_SIGNED均为1，输入位宽均16、结果位宽32。该结构与源代码的单MAC/同步RAM设计一致，检查器还精确要求这四种存储几何，并比对综合前后源哈希。

证据：[核心状态](../../../reports/system/synthesis-core/status.json)、[核心统计](../../../reports/system/synthesis-core/stats.json)、[核心generic网表](../../../reports/system/synthesis-core/generic.v)、[桥状态](../../../reports/system/synthesis-icb/status.json)、[桥统计](../../../reports/system/synthesis-icb/stats.json)、[桥generic网表](../../../reports/system/synthesis-icb/generic.v)。JSON的memory已收进`$mem_v2` cell，因此顶层统计num_memories=0不能解读为没有RAM。

### 6.2 这些输出尚未构成正式工艺综合

283和590是通用中间cell数量，不是标准单元门数或mm²面积。`$mem_v2`仍是抽象存储，没有指定SRAM宏；generic.v是可检查结构产物，不是比赛工艺库映射的最终综合网表。本流程没有提供SDC、库角、线负载/布线寄生、时序分析、功耗活动回标或门级仿真。

| 正式任务3相关交付 | 当前证据 | 仍需的验收材料 |
|---|---|---|
| RTL与测试平台 | 已有源码及真实CPU/ICB功能验证 | 比赛平台适配后重新形成绑定 |
| 综合网表 | 已有generic.v与design.json | 指定工艺和SRAM库下的映射网表 |
| 时序约束 | 当前未提供正式工艺SDC | 指定时钟、I/O延迟、时钟不确定度、例外与库角 |
| 面积 | 逻辑存储容量与通用cell统计 | 规定统计范围内的单元/存储面积，核对2.25mm² |
| 功耗与能耗 | 尚无正式估算 | 同网表/频率/活动窗口/电压温度下的功耗及单任务能耗 |
| 周期和吞吐量 | 行为仿真周期有明确起止点 | 与正式网表及测试条件一致的时延/吞吐量 |
| 综合后功能 | 当前未完成正式门级检查 | 映射网表功能仿真或等价性及所需时延检查 |

指定平台、库与条件未获得时，以上保持EXTERNAL_PENDING。已有功能结果可供本地学习和后续迁移，不能把缺少条件的指标补成估计PASS。

## 7. 可复现入口与失败定位

以下为已有工程入口，复现将更新证据。当前统一长任务仍在使用这些目录时，先由总控安排串行运行，本文写作没有重新启动它们。

~~~bash
bash scripts/test_driver.sh
bash scripts/run_icb.sh --mode protocol
bash scripts/run_icb.sh --mode full36
bash scripts/run_icb.sh --mode repeat
bash scripts/run_e203_upstream_smoke.sh
bash scripts/run_e203_ffn1.sh
bash scripts/run_ffn1_synth.sh --top both
~~~

Windows中实际CPU入口可从任意目录调用：

~~~powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_e203_ffn1.sh'
~~~

成功应同时满足：本次命令退出0、CPU完整数量与顺序满足、Y及flags逐项零差、完整复跑一致、源/输入/固件/输出哈希匹配；综合还要求两个顶层退出0、四银行同步读与精确几何匹配。历史PASS或看到BOOT魔数不够。

失败定位先读[CPU命令记录](../../../reports/system/e203-ffn1/commands.jsonl)和对应日志，再查main返回码/邮箱mcause及mepc、装载/START/ACK/写回计数、最后进度；协议问题先用小矩阵复现，数值问题核对W_pack和符号扩展，综合问题查对应yosys.log。

当前独立CPU入口的运行期异常会写RUNNING/FAIL；但非法CLI参数或Python/NumPy导入前失败的基础设施分支，尚不能保证撤销历史PASS。必须同时检查本次退出码和新鲜日志，不能仅凭result.json状态判断新运行，详见[CPU报告边界](../../../reports/system/e203-ffn1/README.md)。

Verilator已有非致命警告保存在[告警说明](../../../reports/system/e203-ffn1/verilator-warnings.md)，不能把“退出0”写成“零告警”。当前公开上游源、行为SRAM、无正式平台/库和仅一个CPU完整案例，都是结果使用时必须保留的边界。七项总体验收是否接受由总报告统一确认。

## 8. 自检与答案

1. **写入偏置−1的LO/HI是什么？** LO=0xffffffff，HI=0x0000ffff；HI寄存器的高16位必须0。
2. **COMMIT因掩码错被拒绝后能直接重试吗？** 不能；该对齐窗口内提交尝试已消费fresh，须重写该元素必要的LO/HI。
3. **为什么只等row_ready还不能ACK？** 必须先读完并保存整行Y及有效flags；ACK会允许核心复用行缓冲。
4. **驱动超时意味着硬件已停止吗？** 不意味着；它只停止轮询并返回错误，硬件可能仍busy，需显式恢复。
5. **BFM完成36例，能写成E203完成36例吗？** 不能；真实E203只完成一个完整案例及复跑，两类证据分别计数。
6. **generic cell数能否直接换算2.25mm²？** 不能；需要指定工艺单元、SRAM宏、映射结果及规定的面积统计范围。
7. **为什么取指握手数不是退休指令数？** 取指/派发发生在执行完成之前，可能包含未退休的路径；需退休接口才能给退休统计。
8. **怎样判断任务3正式完成？** 除真实SoC功能外，还须有比赛平台/工艺条件下的网表、约束、面积/功耗和周期/吞吐量等适用证据；当前只能报告本地功能与generic结构通过。
