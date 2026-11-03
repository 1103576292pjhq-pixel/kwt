# 新对话交接词：接收已完成点积核，继续完成FFN1独立加速器

> 2026-11-01阶段更新：独立加速器生产连接与自定义ICB接口已经存在，项目已改为普通命名。最新接收入口是[本次记录](../../verification/naming-20261101-3ac1b5/README.md)、[进度](../implementation/progress.md)和[当前ICB协议](../rtl/accelerator/icb-interface.md)。下文的FIFO8、PAIR、legacy等旧接口不是现行合同；旧“仅点积完成”的状态属于历史，不据此重写已完成外围。

> 2026-10-31规格资料补充：[赛事方加载/性能计时答复](../official/20261031-loading-and-timing-qa.md)。加载环境由队伍自建，无另发示例工程；真实装载传输不能跳过，完整计时从输入/参数装载开始到结果写回完成。下文历史实现状态应先与当前进度和磁盘源码核对；本补充未修改或验证RTL。

交接日期：2026-10-28。规格身份：`KWT1-FFN1`。

2026-10-29文档整理补充：先读[协作流程](../workflow/rtl-collaboration.md)及[模块记录索引](../rtl/README.md)。用户已明确采用“用户先讲想法→解释纠正→共识后写RTL→用户阅读优化→讨论修改→按要求验证”。下文的总体授权不表示跳过这一学习过程。磁盘已有外围RTL及有限合成数据报告，不能按早期“全部待写”重新开始；当前观察与证据缺口见[整机资料规划](../rtl/accelerator/README.md)。本次仅整理文档，未替外围做新的功能验收。

本文件是当前阶段的交接入口，替代旧文件 `dot-product-new-chat.md` 中“开始写点积”“尚无顶层TB”等起步任务。旧文件保留形成过程，不再用它安排下一步。交接时仅读取用户RTL并验证，没有改动生产RTL、公共宏、TB、脚本或数值模型。

## 1. 给接手助手的任务与协作要求

我是2026年嵌入式芯片设计竞赛本科组选手，主要负责RTL。我的点积计算模块已经完成，现在要在这套架构上继续完成整个独立加速器。请接收现有实现，先核对磁盘文件和最新验证，再逐模块接上外围，不能重新设计或重复编写点积核。

我需要理解每个模块、端口、位宽、状态和每段代码的原因。沿用“先讨论思路、解释接口和时序，再分段实现并验证”的协作方式；采用中文注释、Verilog `.v` 与公共 `.vh`，状态机优先沿用当前三段式组织。不要一次塞给我一大套无法讲清的代码。合理复用现有子模块，不机械地把每个概念都拆成一个新文件。

已经授权继续完成独立加速器，不必每步反复询问是否继续。需要我决定真实的架构分歧时才提问；一般实现细节先依据冻结合同解释清楚再推进。新对话初次响应应先交代“已完成什么、下一模块解决什么、怎么接入现有核”。

“完成整个加速器”按以下交付边界推进：

1. 首先实现B独立加速器：本地X/W/bias存储、读返回供数、矩阵调度、双结果块、命令前端，以及对应的完整矩阵与多任务回归。
2. 继续完成独立B端的ICB/MMIO封装和接口回归，明确提供给队友的接口、复位和完成条件。
3. E203/共享RAM/guard/固件联调与正式宏、综合、STA、PPA另列集成阶段；它们属于最终竞赛交付，不能用独立核通过冒充。接触到缺失的平台事实时逐项列出，不据此停掉可独立完成的RTL。

G是研究生模式的并列端点，不是B下游，不因这次“整个加速器”就重写G、完整Transformer或DMA。

## 2. 活动目录、环境与保护边界

- Windows：`D:/嵌赛芯片设计赛道/kwt1-accelerator`。
- Ubuntu WSL：`/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator`。
- 使用VS Code连接WSL Ubuntu，在同一目录工作，不另建一份会分叉的工程。
- 本次接收时根目录无 `.git`。不要因没有Git历史就重建工程、搬移文件或覆盖代码；不自行提交/推送。
- RTL验证脚本使用WSL的 `/usr/bin/python3`、`/usr/bin/iverilog`、`/usr/bin/vvp`，具体版本以报告为准。WSL不要调用Windows Anaconda。
- 生产RTL只有 `rtl/` 下的文件。`verification/` 中的 `mutant-*.v` 是故意错误副本，`source/` 是历史快照，不得被通配符编译进正式设计。
- 编辑前重新读取磁盘；用户可能在VS Code继续修改。禁止用旧缓冲、历史快照覆盖用户新代码。

只读参考目录：

| 目录 | 用途与限制 |
|---|---|
| `D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend` | 队友原架构、协议、驱动、平台参考；原算术仍48位，不是本工程数值基线 |
| `D:/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core` | 旧个人实现；有大量未提交/未跟踪修改，禁止reset/clean/覆盖；旧FIFO4也不是新命令FIFO8 |

不整包复制旧实现；有参考价值的控制逻辑应按当前数值和接口合同适配，并记录来源。

## 3. 必读文件与阅读顺序

以下相对路径均以活动工程根目录为基准。

| 顺序 | 文件 | 阅读目的 |
|---|---|---|
| 1 | 本文件、`README.md`、`docs/implementation/progress.md` | 明确当前任务与实际进度，区分目标架构和已完成RTL |
| 2 | `rtl/README.md`、`rtl/include/kwt_compute_config.vh` | 现有文件、公共宏、固定宽度和端口合同 |
| 3 | `rtl/compute/dot_product_block_core.v` | 已完成顶层、输入/输出握手、三段式FSM和排空 |
| 4 | `rtl/compute/mul_array_4x4.v`、`acc_context_bank.v`、`result_convert.v` | 乘积与标签、四上下文、偏置量化的真实行为 |
| 5 | `model/numeric-contract.json`、`docs/model/README.md`、`model/fixed_numeric.py`、`model/layout.py` | 唯一数值黄金、外部布局与范围检查 |
| 6 | `docs/architecture/README.md`、`module-guide.md`、`decisions.md`（后两者同目录） | 冻结架构、模块原理、bank/owner/协议/常量原因 |
| 7 | `verification/README.md`、本交接第4节的新报告、`tb/compute/tb_dot_product_block_core.v`、`scripts/verify_block_core.py` | 当前验证覆盖、未覆盖项和TB供数假设 |
| 8 | `docs/architecture/platform-sources.md`、`docs/data-sources.md` | 平台暂行条件、真实数据来源及赛事证据边界 |

配图入口为 `docs/images/README.md`。总览图 `kwt1-a40-architecture-overview.png` 描述目标整机；四模块图 `kwt1-a40-dot-product-block-core-vector.png` 描述已实现计算核。图上的历史状态文字不优先于当前源码和报告。

架构文档保留2026-10-27“先规格后RTL”的历史说明，这不再表示计算核为空。旧交接末尾仍可能要求“开始量化/顶层验证”，不要重复执行旧阶段任务。

## 4. 本次接收结果及验证身份

已接收四个生产模块和一个公共头文件：

| 文件 | 目前实现的职责 |
|---|---|
| `mul_array_4x4.v` | 16路signed16×signed16，完整product32，一级乘积及ctx/mask/block_last寄存 |
| `acc_context_bank.v` | 四上下文，每组16个acc40，共64项；clear、行mask、符号扩展、最后写回done、组合选读 |
| `result_convert.v` | 单份bias32加法、sat40、RNE16、sat16；一级Y/flags输出寄存，支持背压和同拍收发 |
| `dot_product_block_core.v` | 接受一个4×16块，连接上述三模块；三段式FSM、真实握手计数、排空、量化映射和块完成 |
| `kwt_compute_config.vh` | 固定数值、结构、地址宽度、包含完成值的计数器宽度 |

本次接收的顶层SHA256：`75495f70abc319ecadcc44e40bd2ce1008a5fe6dab249fbb744e2af57195fc9e`。

与旧报告 `verification/block-core-20261028T215423-d9c5a6/` 比较：三个算术子模块、宏、TB、验证脚本和模型哈希相同；顶层字节不同，逐行差异为注释及分段说明。为绑定实际当前文件，已另行完成完整回归，新证据目录为 `verification/block-core-20261028T223900-96b70c/`，状态为 `PASS_BLOCK_CORE_PORT_LEVEL_REGRESSION`。见该目录 [接收说明](../../verification/block-core-20261028T223900-96b70c/README.md) 与 [report.json](../../verification/block-core-20261028T223900-96b70c/report.json)。

本次实际结果：5223块中5220块完成、3块故意复位取消；包含手算完整任务400块，以及本地一条真实音频所保存的12层输入4800块、304128项Y和同数flags逐位一致。6种顶层错误注入均检出，33项软件测试通过。检查156184拍背压保持；共2297793仿真拍，不是单任务性能指标。Verilog-2001设计编译退出0且无警告，报告所列10份源码/测试/模型文件在验证后再次核对SHA256全部一致。

历史组件证据：

- `verification/mul-array-20261027T213804-ee2726/`：4849拍，62464个乘积一致。
- `verification/acc-context-20261028T131043-851d21/`：3068拍、196224次选读检查，640个最终acc与Python黄金一致。
- `verification/result-convert-20261028T200650-af0cd6/`：5788组数值、8390拍流式检查、7种错误被检出；复位取消独立记账。
- `verification/fsm-three-stage-20261028/`：重构前后185433拍公开端口比较一致，是有限仿真，不是形式等价。

**现有完整矩阵数值结果由TB分块供数、收集并重建。它没有验证真实SRAM、硬件矩阵调度器、命令FIFO、owner、ICB或CPU。** 本地一条音频的12层不能改写成12条独立音频或官方600样本通过。

## 5. 冻结数值方案：不重新讨论48位

任务固定 `X[99,64] × W[64,256] + bias[256] → Y[99,256]`，十二套层参数通过十二项独立任务更换。

| 对象 | 有符号位宽 | 小数位 |
|---|---:|---:|
| X | 16 | 12 |
| W | 16 | 16 |
| 精确乘积 | 32 | 28 |
| bias | 32 | 28 |
| acc | 40 | 28 |
| 加bias临时和 | 41 | 28 |
| 内部Y | 16 | 12 |

按k0..63乘加，数学定义逐前缀sat40；合法输入的每个前缀都不会溢出，因此现有RTL用普通40位累加等价实现。乘积先符号扩展，不逐项右移。最后acc/bias先符号扩展到41位相加，sat40，RNE右移固定16，最后sat16。

64项和加bias范围为 `[-70,864,863,232, 70,866,960,383]`，signed40范围为 `[-549,755,813,888, 549,755,813,887]`。40已确认，不退回48，也不擅自缩为38。41位只是加法临时量。

RNE：+2.5→2、+3.5→4、−2.5→−2、−3.5→−4。最终饱和到[-32768,32767]，必须先舍入再判断饱和。

flags有效3位：bit0=加bias后raw40溢出；bit1=Y16饱和；bit2=整个矩阵的最后项Y[98,255]。完整合法K64任务bit0恒0，但量化组件保留任意acc40的溢出测试语义。

外部legacy载荷48、共享bias64、共享Y32是兼容容器。外围先验证高位是否是有效位的正确符号扩展，再截取；不得先丢高位再检查。正式BEGIN只允许shift16。共享bias64的完整signed32范围必须在软件端也检查，RTL不能发现软件已经丢掉的高位。

## 6. 已完成计算核的精确连接合同

### 6.1 start、输入与复位

- `clk/rst_n`：低有效同步复位。复位取消当前计算/结果；外围必须同时失效旧请求tag或隔离旧返回，不能让复位前SRAM数据进入新块。
- `start_valid/start_ready`：仅IDLE接受启动。锁存4位 `start_row_mask` 和 `start_is_final_block`；阻塞时上游保持元数据。
- 正式mask为普通行组1111、最后row0=96的三行0111。不要把组件对其他mask的容错当作正式变尺寸支持。
- `in_valid/in_ready/in_x[63:0]/in_w[63:0]`：已经对齐的返回流，四个signed16分别打包，lane0在低16位。
- 恰好256次输入握手，顺序为k0/g0..g3，k1/g0..g3，直到k63/g3。`group_count`为9位，能保存256；ctx来自已接收组数低2位。
- **现有核不产生SRAM地址，不实现x_hold，也不接收请求侧k/g。** 同一k的四组X复用由外围负责。输入空拍不推进计数。
- RUN期间可持续接收；固定延迟RAM一旦接受请求，返回不能被临时取消。外围必须限制请求数、跟踪返回valid/身份，禁止第257组和旧任务返回越界。

### 6.2 bias与输出

- `bias_addr[3:0]` / `bias_data signed[31:0]` 是组合选读合同。选择活动W槽的16个bias寄存器，保持到最后一次量化输入接受。不要直接接有读延迟的RAM。
- `out_valid/out_ready` 连同 `out_y signed[15:0]`、`out_flags[2:0]`、`out_index[5:0]`、`out_block_last` 定义完整输出事务。受阻时有效载荷/位置必须保持。
- acc内部选读地址为 `{g,p,q}`，即 `g*16+p*4+q`；bias地址为 `{g,q}`；结果写入地址为 `{p,g,q}`，即 `p*16+g*4+q`。
- 输出顺序不是0..63递增。结果块必须按 `out_index` 写入并检查written_mask，不能用“接收到第几项”代替地址。
- 普通块64项，尾块48项，尾块合法结果位置0..47。全局Y坐标为 `(row0 + out_index/16, tile*16 + out_index%16)`。
- `out_block_last` 是本块最后有效项；`flags[2]` 仅在 `start_is_final_block` 且本块最后项时置1，两者不可混用。
- `block_done` 单拍表示最后有效输出已被下游接收。它不是publish、CPU已读完、ACK完成、B task_done或guard COMPLETE。

### 6.3 现有FSM与外围职责的衔接

当前内部流程为 `IDLE → CLEAR → RUN → FLUSH → QISSUE/QWAIT → DONE → IDLE`。FLUSH等最后乘积实际写回acc；不以“已发最后请求”代替排空。

目标总架构文档的LOAD/ALLOC/PUBLISH/WAIT_TILE等是外围职责，不要求拆开或重新复制现有计算FSM。结果owner必须在第一项填入前分配，未获owner时禁止填入/publish，可以利用现有输出背压保持结果。具体alloc请求时点、外围端口与流水暂存尚需在该模块实现时解释并定案，不能凭文档名字虚构现成端口。

只保留一套64项acc和一个量化器。当前块乘加完成后才量化，QISSUE/QWAIT交替服务；量化组件自身可每拍收发不等于当前顶层每拍输出。双结果块可使CPU消费与后续块生产重叠，不代表前块量化与后块乘加重叠。

## 7. 整个独立加速器的数据和控制流程

离线准备定点数据 → 共享RAM → CPU按协议发命令 → 命令FIFO8/单项执行q → X四bank与W双槽/bias → 矩阵调度/读请求及返回适配 → 已完成计算核 → 双结果块 → CPU读RESULT并写共享Y/flags → fence → ACK。当前无DMA直写共享RAM。

### 7.1 本地存储

| 对象 | 已确认的逻辑组织 | 地址/用途 |
|---|---|---|
| X | 4×1600×16位SP逻辑bank | bank=r%4；addr=floor(r/4)*64+k；全X只装一次并跨tile复用 |
| W | 2槽×4bank×256×16位 | tile内列c，bank=c%4；addr=floor(c/4)*64+k；活动槽读、另槽装载 |
| bias | 每槽16×32位寄存器，共两组 | 与对应W槽绑定，组合选读 |
| acc | 已实现64×40位寄存值 | 四上下文，共320B逻辑状态 |
| 结果payload | 2×64×19位 | 每项Y16+flags3，共304B；metadata/owner/mask另算 |

X逻辑容量12800B、W4096B、bias128B；X实际6336项，容量6400项包含64个尾行无效位置。尾bank不能把未装载数据当有效操作数，mask和供数行为要测试。逻辑bank数不是物理宏数。

共享W按列主序 `W[col*64+k]`，W命令流按tile内 `index=k*16+c`，物理bank地址再变为 `floor(c/4)*64+k`。三个顺序不同，驱动/装载器/读调度必须明确各自使用哪个。

### 7.2 400块的实际硬件调度

正式硬件按tile0..15，每tile遍历row0=0,4,...,96；每块256组k/g请求，使用16个乘法器和4个上下文。共400块、25344项Y、1622016个有效MAC。

现有 `verify_block_core.py` 的task_blocks由TB按row-group在外、tile在内枚举，证明单块数值和坐标，不是目标双W槽硬件调度证明。新外围回归必须实际按W驻留生命周期运行tile在外、row-group在内，不能机械照抄TB调度顺序。

内部RAM行为基线L1：请求有效和身份随固定读延迟进入返回端；g0读取X并形成x_hold，g1..g3复用同一k的X；每g读新的W。g0返回应使用当拍有效X数据，不能因非阻塞更新而误用上一k的x_hold。请求计数与已返回/被计算核接受计数分别管理。

### 7.3 W槽生命周期与装载顺序

W槽按FREE→LOADING→READY→ACTIVE→FREE。W1024和bias16装齐且COMMIT后才READY；活动槽不允许改写，同一个SP bank禁止同时读写。

输入命令为BEGIN、X、OPEN、W、bias、COMMIT、START。先BEGIN→X全量→OPEN tile0→W0/bias0→COMMIT0→START，然后CPU装后续tile并服务结果。START每任务一次，不先把两个槽都占满再让OPEN堵住START。

当前tile最后一个行组完整publish后才释放W/bias槽；不能提前到最后MAC或计算核block_done，也不必等CPU ACK。发布切断当前tile数据依赖，ACK则释放结果槽，两个owner不可混为一谈。

### 7.4 输入FIFO8及PAIR_NEXT

FIFO深度8沿用已确认配置，每项保存pair标记、meta/task/position和原始data48。保留单项执行q，区分接口接收与核心执行。MMIO写成功表示入队，语义错误可在执行退休时报告。

pair低16先、高16后；低半接受只切换half，高半接受才释放该FIFO项。PAIR_NEXT只用于X/W，索引为合法偶数，成功入队才position+2，失败不变，不跨tile自动进位。它与旧个人operand-prefetch FIFO4不是同一对象。

满槽的合法OPEN可等待；非法顺序、索引、tile、shift、数值应报错，不能无限伪装成not-ready。错误保持到明确恢复。

### 7.5 双结果块、读取与ACK

结果槽FREE→FILL→READY→FREE；alloc锁存task/row/tile/count/final。按out_index填入，written_mask检查重复、遗漏和越界；完整才publish，绑定sequence，CPU只可见READY结果。

CPU读RESULT时先快照响应，cursor在**本地B响应退休**时前进一次。经过guard时，guard先接收B响应并保存，再等CPU接收上游响应；两级ready/valid不能混用。

ACK必须匹配task/sequence/count且已读完整块；合法ACK在命令接受沿释放owner，但ACK响应仍必须排空。不匹配、提前或陈旧ACK不得释放。CPU先写共享Y32/flags8，fence后再ACK。

两个结果块满时停止进一步填入，不能覆盖旧结果。CPU输入等待循环要同时drain结果，否则可能形成“结果满→核心停→W槽不释放→OPEN堵→FIFO满→CPU只等输入”的死锁。

## 8. ICB、完成语义和待确认平台

ICB/MMIO沿用32位数据、寄存器4字节对齐、完整写mask=0xf；共享RAM支持byte-enable但不因此承诺非对齐访问。完整寄存器表见 `docs/architecture/module-guide.md` 第13节；位编码实现前对照原wrapper与F3驱动，不猜新的ABI或复用不相符的能力ID。

当前开发地址：B=0x11000000，G=0x11010000，guard=0x11020000，共享RAM=0xa0000000。共享512KiB、32位ICB、一次全局在途、同步读/响应保持均为当前模型基线，官方地址和控制器实现尚待核实。

完成次序必须区分：最后MAC → 最后结果publish/compute_done → B task_done → guard COMPLETE。B task_done还需要FIFO/q空、结果全消费/ACK、核心和本地响应安静。guard再核对session、epoch/task token、端点和共享事务安静。`!busy`不等于整机完成。

ABORT可取消算术，不能吞掉已接受总线请求的响应；响应先排空再flush。复位/flush主要清valid、owner、进度，不逐字清X/W/结果/共享RAM。恢复后不得复用旧身份或残留返回。

E203参考：https://github.com/riscv-mcu/e203_hbirdv2 ，此前查得master为 `9f3e34f337f5d0a1236a285871ffa2032491617a`；它不证明服务器包或本地副本相同。禁止拿最新master覆盖。

赛方服务器截图中的 `SOC_RTL_2025/e203_hbirdv2-master_1013_update_sim.zip` 只证明存在服务器版E203包，尚未证明带有正式共享512KiB实现。具体SoC接法、加载TB、宏端口/极性/掩码/读延迟/保持/碰撞合同仍需正式资料。

内部SRAM允许形状按已核对赛题为16×128、16×1024、16×4096，可按允许端口组合；服务器存在2048深度目录不等于获准使用。先实现清楚的逻辑bank行为合同，保留宏适配层；具体型号和数量待正式模型、库身份、面积和时序确定，不能编造“已选定几颗”。bias用寄存器；结果块的peek/响应合同也不能机械套同步SRAM。

## 9. 下一阶段推进顺序与验证重点

以下是衔接顺序，外围模块名和具体端口尚未冻结。先画出接口表与一块数据的时序，再写该阶段代码；不要把建议文件名当已存在模块。

| 阶段 | 工作 | 最少验证 |
|---|---|---|
| A | X四bank、W双槽/bias存储及装载规则 | 地址映射、范围、缺项/乱序、未装载访问、SP碰撞、活动槽保护、复位valid |
| B | SRAM请求/返回适配、x_hold、矩阵块调度 | g0/后3g、L1与tag、256次真实接收、k63排空、尾mask、400块tile优先顺序、连续块 |
| C | 双结果owner、fill/publish/read/ACK | 非线性地址、written_mask、两槽满、响应背压、陈旧/错误ACK、尾块48、最后ACK响应 |
| D | BEGIN等命令执行、FIFO8、PAIR_NEXT，连接B独立顶层 | 合法完整任务、非法shift/bias高位、FIFO同时入出/满空、低高half、等待时drain、恢复隔离 |
| E | ICB/MMIO封装和B端完整回归 | MMIO快照、响应保持、地址/mask非法、legacy/fast同队列、任务done与quiet、连续12任务 |
| F | 交给队友的综合接口/源文件清单，随后平台联调 | SRAM宏匹配、E203加载/驱动、共享RAM、guard排空、官方精度/性能及综合STA |

B和C可以按接口依赖穿插；先用明确的TB接收端验证B，最终必须换成真实结果owner并回归，不能把TB简化机制当完成品。当前核可通过输出背压等待结果槽，不需要为此增加第二套acc或重做单块核。

每阶段交付：模块职责、端口与宽度依据、逐拍时序、中文代码解释、运行命令和证据、剩余边界。延迟/吞吐用定义明确的实测边界；没有综合/STA就不填面积mm²、MHz、功耗或声称某优化提高了百分之几。

控制字段必须容纳完成值：X装载0..6336用13位；W0..1024用11位；bias0..16用5位；FIFO占用0..8用4位；fill/cursor0..64用7位；结果地址0..63才是6位。task/epoch32、sequence24、count8保留接口原因；窄索引参与加法前需适当扩展。

## 10. 可复现命令与只读参考索引

```bash
cd '/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator'
/usr/bin/python3 -B -m unittest discover -s tests -v
/usr/bin/python3 -B scripts/verify_block_core.py
```

完整顶层脚本默认读本地冻结提取数据、运行12层、错误注入和33项软件测试，每次自动建新证据目录。`--synthetic-only`只用于缩小调试，不等于完整真实数据回归。无需无修改地反复重跑所有历史套件；修改哪个边界，运行相应组件及受影响集成回归。

组件命令分别为 `scripts/verify_mul_array.py`、`scripts/verify_acc_context.py`、`scripts/verify_result_convert.py`，均用WSL python3运行。设计源码编译支持Verilog-2001，TB可用 `-g2012`；头文件目录为 `-I rtl/include`。

队友冻结包根目录下可按需只读：

| 路径 | 用途 |
|---|---|
| `rtl/bachelor/rtl/revd_opt/core_stream_tiled_w2_opt.sv` | 双W槽、bank、命令、矩阵调度与槽释放；算术仍48位 |
| `rtl/bachelor/rtl/revd_opt/v08_result_blocks.sv` | owner、mask、cursor、ACK语义 |
| `rtl/bachelor/soc/revd_opt/revd_opt_icb_w2.sv` | FIFO8、PAIR_NEXT、MMIO及响应 |
| `rtl/dual_mode/dual_mode_icb_guard.sv` | 双级响应、token、排空和flush |
| `rtl/dual_mode/dual_mode_soc.sv` | E203/B/G/共享RAM连接 |
| `firmware/recommended_F3/revd_opt_driver_w2.c` | 输入/结果同时服务、索引重建、fence/ACK |
| `docs/ACCEPTANCE.md`、`PLATFORM_AND_RESOURCES.md`、`manifest/configuration.json` | 原包验收边界、平台资源、配置身份；按实际文件位置查找 |

数值资料：

- 原DEV12：`D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend/data/dev12`，旧软件回归304128项Y和flags一致；不等于当前RTL已跑了该协议loader。
- 当前真实层输入：`D:/嵌赛芯片设计赛道/generated/ffn_fp32/validation_right_a69b9b3e_nohash_0/layer_00` 至 `layer_11` 的X/W/bias与浮点参考。
- `verification/local-float-reference.json`：本地单音频12层最差NRMSE约0.0201543%，不是官方600样本。既有提取运行时与指南指定版本的等价性未证明。
- 原始音频和权重已存在 `D:/嵌赛芯片设计赛道/datasets/`、`keyword-transformer/`。不要为写RTL重下载或训练，不改冻结尺度和黄金去适应错误RTL。
- 赛题指南：`D:/嵌赛芯片设计赛道/2026赛题指南.pdf`，已有记录SHA256为 `b73a5414b4dcdb2cca337778a133be88705e207bec080687731d63b413ea927c`。

赛事验收另需官方600样本12层NRMSE≤3%、官方12性能任务、RTL/黄金逐位一致、E203集成及150MHz STA、加速器/新增接口/内部SRAM面积≤2.25mm²等正式证据。本科必做FFN1，不把G、attention、GELU、FFN2或完整12层自动网络链加入必做范围。旧F3整机周期和旧个人核的面积降低百分比属于不同实现，不能转移到新工程。

## 11. 新对话的第一步

请读取本交接、当前源码和最新报告，确认用户没有在交接后继续改代码；简短复述现有核接口及数值合同，再列出尚未实现的外围边界。优先从“本地X/W/bias存储与读返回供数如何连接已有核”讲起：数据怎样装、bank怎样选、何时读、L1返回怎样打包、g0怎样更新x_hold、后续g怎样复用、最后一组怎样保证送达。

随后给出该模块最小端口表和时序例子，按已授权的独立加速器范围分段实现、解释和验证。不要再从乘法器或量化器重写，不宣称整个架构已经完成，也不要仅因正式共享SRAM资料未齐就停下本地开发。
