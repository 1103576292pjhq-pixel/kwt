# 本科 FFN1 加速器、共享SRAM与SoC工作交接

更新日期：2026-11-03。当前合同：`KWT1-FFN1`；生产顶层：`kwt_accelerator`；源码清单：`rtl/kwt.f`。

本文对应本地 `D:/嵌赛芯片设计赛道/kwt1-accelerator` 及其服务器集成副本，只负责本科任务1–3。共享仓库根目录的其他工程及其扩展任务有各自的接口和证据，不能与本交付混用。本次在原交付目录更新，独立加速器生产RTL与数值保持不变。

队友先读[服务器目录与仓库对应表](server-folder-map-20261103.md)，再读[新增共享SRAM及SoC连接](shared-sram-and-soc-20261103.md)和[两种综合入口](synthesis-handoff-20261103.md)。现有源代码可以交付开始独立块或完整SoC综合；综合文件/库/SDC由队友按平台配置，实际通过与否以工具报告为准。

## 1. 当前做到哪里

已经完成固定数值模型、完整独立加速器RTL、内部24颗SRAM封装、ICB接口、E203顶层接线和C驱动；新增32组×2颗4096×16宏拼成512KiB共享SRAM，以及ICB控制器/顶层。当前服务器生产SoC顶层为`kwt_shared_soc_top`。

真实case3的“文件经TB实际ICB加载→共享SRAM→E203→加速器→结果完整写回/回读”已通过。12组连续CPU验证最后确认前3组完成、第4组加载，用户要求停止，未取得全12最终PASS。完整规定计时仍待补齐；指定工艺综合、STA、面积、功耗和能耗尚无结果。计时工具草稿已按用户要求暂停，不在本轮交付中作为可运行功能。

## 2. 架构与数值

单任务固定：`X[99,64] × W[64,256] + bias[256] → Y[99,256]`。十二层分别换参数执行十二项独立任务，不是片上执行整个Transformer。

| 对象 | 位宽/小数位 | 用途 |
|---|---|---|
| X | signed16 / Q12 | 输入矩阵 |
| W | signed16 / Q16 | 权重 |
| product | signed32 / Q28 | 精确16×16乘积 |
| bias | signed32 / Q28 | 与乘积相同尺度 |
| accumulator | signed40 / Q28 | 64项顺序累加 |
| 加bias临时值 | signed41 / Q28 | 保留加法进位后限幅到40位 |
| Y | signed16 / Q12 | RNE右移16，再sat16 |

flags：bit0原始值溢出、bit1输出饱和、bit2整个任务最后一项。合法K=64任务的累加及加bias范围可由40位覆盖，raw溢出不可达；组件测试仍覆盖转换器边界。没有48位累加器，也没有运行时可变shift。

计算结构：PM=4、PN=4、CTX=4，16个乘法器、64个40位累加上下文；每块4行×16列，每块256组操作数。每任务400块、25,344个有效输出、1,622,016次有效MAC；末行组只有3行有效。

内部X：8×1024×16宏，16KiB；内部W：16×128×16宏，4KiB，分双槽；bias为两槽共32项32位寄存器；另有双结果块。内部SRAM物理容量合计20KiB，与已经接入的512KiB共享SRAM是两个概念。CPU负责搬运，无DMA。

## 3. 已完成的15个生产模块

| 文件（相对rtl/） | 职责 |
|---|---|
| compute/mul_array_4x4.v | 4×4有符号乘法、一级乘积和标签寄存 |
| compute/acc_context_bank.v | 四上下文累加、按ctx和mask更新、完成与选读 |
| compute/result_convert.v | 加bias、sat40、RNE16、sat16、flags和背压保持 |
| compute/dot_product_block_core.v | 单块清零、256组乘加、排空、量化与尾行mask |
| memory/kwt_storage_array.v | 24颗官方宏的实例与bias寄存器 |
| memory/kwt_storage_wrapper.v | 逻辑bank映射、深度拼接、读返回与冲突/越界检查 |
| control/kwt_operand_feeder.v | 按k/g发读、对齐返回、保持X并向核供数 |
| control/kwt_load_ctrl.v | BEGIN/X/OPEN/W/BIAS/COMMIT/START、完整性与双W槽状态 |
| control/kwt_result_blocks.v | 双结果块的分配、填充、发布、读取和身份匹配释放 |
| control/kwt_task_ctrl.v | 任务/行组/tile调度、W槽切换、完成和abort排空 |
| interface/kwt_command_fifo.v | 一项命令快照，避免后续暂存寄存器写改变已接收命令 |
| interface/kwt_icb_regs.v | ICB寄存器、请求/响应保持、地址与掩码检查 |
| interface/kwt_result_access.v | 结果描述符、游标推进与ACK访问适配 |
| interface/kwt_icb.v | 连接寄存器、命令缓冲、结果访问与状态 |
| kwt_accelerator.v | 连接ICB、控制、存储和计算核的生产顶层 |

公共头文件为 `kwt_compute_config.vh`、`kwt_storage_config.vh`、`kwt_control_config.vh`、`kwt_icb_config.vh`。综合只使用 `rtl/kwt.f`，不要递归收集所有`.v`。完整接口见[ICB说明](../rtl/accelerator/icb-interface.md)。

## 4. 已验证内容与当前可引用指标

以下均为已有运行记录；本次整理核对报告和哈希，不把历史PASS描述成今天重新执行的RTL测试。

| 项目 | 结果 | 范围及证据 |
|---|---|---|
| 算术与单块核 | 乘法、累加、量化、背压、复位及检错回归通过 | 组件报告见verification；早期记录绑定各自源码版本 |
| 当前ICB完整合成任务 | 2任务、800块、50,688项Y/flags一致 | `verification/icb-20261101T183419-018e9e/`，本地合同SRAM模型 |
| C驱动对RTL | 400块25,344项通过；5种故障正确拒绝 | `verification/c-task-driver-20261102-04/report.json`，CPU由主机C替代 |
| 真实E203寄存器访问 | TEST_PASS、x3=1；6,202周期、1,066条有效指令 | 服务器截图结果转录在mmio_smoke/README；不是计算性能 |
| 真实E203完整合成数据任务 | TEST_PASS、x3=1；400块25,344项全检查；8,120,871周期、5,227,662条有效指令 | `verification/e203-task-server-20261102-01/receipt.json`，含CPU数据生成和软件对照，不是正式性能 |
| 512KiB共享SRAM组件 | 单宏及64宏阵列通过；131072字、两轮容量扫描、512种组/掩码组合 | `verification/shared-sram-official-server-20261103-01/receipt.json`；官方功能模型，含预期越界与复位取消 |
| 真实E203共享访存/原MMIO回归 | 分别6311周期/1015指令、6202周期/1066指令，x3=1 | `verification/e203-shared-ram-server-20261103-01/`及`e203-shared-mmio-server-20261103-01/` |
| 真实E203人工数据共享全任务 | 400块、25344项共享写回与完整回读，10338730测试程序周期 | `verification/e203-shared-task-server-20261103-01/receipt.json` |
| 真实E203录音case3共享全任务 | 400块、25344项差异0，NRMSE **0.01737469%**，**6079053**测试程序周期/3622111指令 | `verification/e203-real-shared-case3-server-20261103-01/receipt.json`；窗口含初始化/软件检查，非正式性能 |
| CPU连续12组（本轮） | 用户要求停止；截图仅确认case1..3完成、第4组加载 | 服务器`verification/real_shared_suite_01/`保留，不标记全12通过；本地同C实际RTL两个任务另有50688项通过证据 |
| 软件真实精度 | 4,445条验证索引、4,075个唯一输入、12层；最差第7层NRMSE **0.0211091260%** | `verification/precision-20261102-01/`，按层汇总误差能量；不是分类准确率或官方600条 |
| 真实12任务完整RTL | 4,800块、304,128项Y/flags逐位一致，差异0；最大单任务NRMSE **0.02214978%** | 本地报告与服务器官方SRAM功能模型截图凭据；发起方是TB |
| 正常ICB性能基线 | 12任务合计 **4,435,377周期**，平均 **369,614.75周期/任务** | `verification/performance-baseline-20261102-01/`，本地合同模型，无真实CPU或共享SRAM |
| 150MHz目标折算 | 平均 **2.46409833ms/任务**，**405.827960任务/秒** | 仅为上述TB基线按目标频率换算，不能当已实现频率或正式吞吐量 |
| 核忙碌时间 | **155,280周期/任务** | 包括清零/乘加/排空/量化；与总线活动重叠，不与总周期相加 |
| 正常性能基线协议 | 1,478,467笔请求/响应；错误响应0、响应保持0 | 实际装载/轮询/读回/正确ACK计入，文件读取和golden比较在窗外 |
| 当前交付软件复核 | 51项软件测试通过（原48项＋3项服务器源码核对工具测试） | 在本次交付副本实际执行；不替代新的SoC仿真 |

软件全验证的X/W/bias裁剪、输出饱和和raw溢出均为0。4,445条索引含重复静音：4,074个WAV加一个全零输入，静音按371次权重累计，并非删样本。完整原验证划分最差单样本单层NRMSE为0.0319907069%。

真实12任务功能压力回归的4,212次错误响应为4,200次故意忙写重试加12次故意早ACK拒绝，另有一次ABORT和随机响应背压；不能把4,296,926个功能压力周期拿来当正常性能。正常性能基线已去掉这些故意异常，固定TB事务间隔仍计入。

**证据限制：**服务器E203和真实12任务结果依据用户截图，完整服务器日志/JSON尚未独立下载读取。浮点提取使用TF2.4.0替代2.4.0rc1，等价性未证明；已核对checkpoint参数并与float64 affine交叉检查。官方600样本和官方12个性能任务未验收。当前不存在可报告的最终面积、功耗、能耗或STA最高频率。

## 5. SRAM与E203状态

官方SRAM功能模式采用`ARM_UD_MODEL`，已通过配置为EMA=2、EMAW=0。**独立加速器顶层kwt_accelerator默认EMA仍是0，复测/集成时须显式传2，不能以为默认值已改。**功能模式不证明物理时序。

历史SRAM时序模型运行曾出现hold违例和X结果，已知TB在CLK与控制同一时间戳变化，模型hold要求500ps。需要结合波形、激励时序及真实约束核查；未凭功能模式通过、改EMA或屏蔽检查宣称解决。

E203在工作副本`kwt-soc`中先生成`kwt_soc_top`连接SysPer ICB，随后生成当前`kwt_shared_soc_top`连接SysMem与共享阵列，并沿用引出的原hfclk和bus_rst_n。原始工程和旧顶层保留。加速器开发基址0x11000000、共享基址0xa0000000；无中断，CPU轮询。固件由本地Nuclei 2024.06 GCC13.1.1构建，服务器使用预编译镜像。

当前共享生产源码在服务器`shared_sram_bundle_01/kwt-shared-sram-v2/rtl/`，仓库对应`integration/e203/shared_sram/rtl/`，并有`server-layout`同名路径副本。旧`shared_ram_dev/sim`行为数组只作历史开发材料，不用于当前综合。SRAM宏实现来自赛方，我们自行编写拼接和ICB逻辑。

## 6. 没做的工作与建议顺序

1. 队友开始独立加速器或整SoC综合，按下面入口取当前源码，配置工艺库、宏映射及有效SDC，形成150MHz时序、面积、综合网表及综合前后功能结果。
2. 本轮CPU连续12组测试由用户要求暂停，按团队需要恢复到新输出目录；当前不重复声称已有全12通过。真实case3已完成完整共享链路。
3. 单独统计第一笔输入/参数装载到最后实际结果写回完成的周期，包含加载、等待、调度；CPU测试程序结束周期不是这个窗口。计时开发目前暂停。
4. 同一计时窗生成活动文件，估算整SoC平均功耗和单任务能耗；独立块基线仅供分析，服务器该基线包亦无最终PASS凭据。
5. 提交冻结后配合组委会600样本和统一12个性能任务评测；本地自选任务不代替正式样本。赛题不要求布局布线、物理验证或流片。

## 7. 队友从哪里开始

先看本文，再看[当前服务器对应表](server-folder-map-20261103.md)、[新增共享结构](shared-sram-and-soc-20261103.md)和[综合交接](synthesis-handoff-20261103.md)。独立综合取`rtl/kwt.f`、顶层`kwt_accelerator`；整SoC使用服务器`kwt-soc`的`kwt_shared_soc_top`及其完整平台依赖。源码一致性可用`tools/check_server_sources.py`只读核对。不要使用仓库根目录另一套驱动替换本工程接口。

GitHub交付是按清单选择的自有源文件、说明、报告和封存包，包含SHA256清单与服务器路径映射；未上传商业SRAM/工艺库、EDA运行时、音频全库、checkpoint全库或大型trace，也未伪造未取回的服务器顶层。历史报告保留原状态，早期交接文档在history中存档；当前状态以本文和新增对应表为准。VCS清理已释放226.10MiB，954保护文件哈希保持；源码/日志/数据保留，重跑要重新编译。
