# 整个加速器的资料分类与后续扩展

整理：2026-10-29。本文规划资料归档，不重新设计架构，也不因为某个文件存在就认定模块或整机通过。讨论/实现方式遵循[协作流程](../../workflow/rtl-collaboration.md)。

## 1. 三种内容分开存放

| 内容 | 归属 | 维护方法 |
|---|---|---|
| 整体结构、冻结规则、为什么这样选 | [architecture](../../architecture/README.md)及[decisions](../../architecture/decisions.md) | 跨模块规则在这里统一修改，其余文件引用 |
| 一个模块怎么讨论、编写和优化 | docs/rtl下对应模块记录 | 按[模板](../module-record-template.md)增量记录 |
| 实际测过什么 | verification下每次独立运行目录 | 保存源码身份、命令、退出码、数据和范围；索引链接原证据 |

进度写“目前完成哪一步”，计划写“后续如何推进”，交接写“接手需要知道什么”，不把三者当同一份正文反复复制。

## 2. 当前目录观察：实现与验证必须分别看

以下是2026-10-29整理时的目录观察，没有在本任务中重新编译、审查或修改外围RTL。旧进度表中的“外围尚未实现”属于早期阶段，不能据此忽略已经出现的源码。

| 层次 | 已观察到的源码 | 已有资料/证据与限制 |
|---|---|---|
| 计算核 | rtl/compute下四模块与公共宏 | 有组件与完整端口回归，见[模块索引](../README.md) |
| 本地存储 | rtl/memory/kwt_sp16_l1.v、kwt_operand_store.v | 源码、tb/system/tb_operand_store.v已存在；有L1/映射测试日志，不代表已适配正式物理SRAM宏 |
| 矩阵调度 | rtl/control/kwt_matrix_core.v | 源码和对应TB已存在；需补用户讨论、请求/返回标签及块推进说明 |
| 结果管理 | rtl/control/kwt_result_blocks.v | 源码和对应TB已存在；需补owner、fill/publish、响应退休与ACK合同记录 |
| 命令/ICB | rtl/interface/kwt_icb.v、rtl/kwt.f | 有显式清单、tb_icb.v及verify_accelerator.py；独立B端与SoC联调范围不同 |
| 平台与交付 | 当前平台资料见architecture/platform-sources.md | E203、共享RAM、guard/固件、正式宏、综合/STA/PPA需分别登记实际证据 |

已找到的独立B端记录：

- [accelerator-20261028T230347-9901f9/report.json](../../../verification/accelerator-20261028T230347-9901f9/report.json)记录 `PASS_STANDALONE_B_SYNTHETIC_ONLY`：2项任务、800块、50688项输出，real_layers=0。这是合成/手算数据仿真记录，不是12层真实数据或正式综合报告。
- 后一目录的[commands.json](../../../verification/accelerator-20261028T230633-d0cf65/commands.json)含存储/矩阵/结果/ICB退出0日志；但w_slot_alias故意错误副本预期非0而实际退出0，整理时该目录没有最终report.json。该检错缺口应由相应开发/验证任务处理；不能据此宣称该轮完整回归通过，也不能直接推断生产RTL存在同一错误。
- 上述都是旧运行记录，不自动证明当前字节身份。重新接收外围时须核对报告快照、现有源码及实际覆盖，再更新[进度](../../implementation/progress.md)与[验证索引](../../../verification/README.md)。

## 3. 后续资料具体怎么增加

下面列的是归档规划；未链接的文件名尚未创建，不表示已有接口已经讨论完成。按真实模块推进时再创建正文，不先批量放空文件。

| 资料类别 | 后续位置 | 必须记录什么 | 何时补 |
|---|---|---|---|
| 单端口L1存储 | docs/rtl/memory/kwt_sp16_l1.md | 读写互斥、地址深度、返回有效、复位、行为模型与物理宏差异 | 阅读该模块前 |
| 操作数存储 | docs/rtl/memory/kwt_operand_store.md | X/W bank与槽映射、bias保存、尾行读保护、装载与读冲突 | 讨论存储模块时 |
| 矩阵控制 | docs/rtl/control/kwt_matrix_core.md | task/tile/row/k/g、请求/返回、x_hold、W槽生命周期、块启动和排空 | 接入计算核时 |
| 结果双块 | docs/rtl/control/kwt_result_blocks.md | owner分配、非线性fill、written_mask、publish、响应快照/退休、ACK释放 | 讨论结果模块时 |
| ICB前端 | docs/rtl/interface/kwt_icb.md | FIFO8、半字pair、寄存器ABI、错误与等待、响应背压及flush | 讨论前端时 |
| 跨模块连接 | docs/rtl/accelerator/interfaces.md | 每组信号的生产者/消费者、寄存边界、ready/valid、复位与保持责任 | 第一次跨模块联调前 |
| 一次任务全流程 | docs/rtl/accelerator/task-flow.md | BEGIN/装载/START/块计算/结果消费/ACK/结束的先后关系，示例地址与周期 | 串接任务时 |
| 异常与恢复 | docs/rtl/accelerator/reset-and-errors.md | 非法命令、旧标签、已接受响应、flush取消/排空、重启边界 | 错误合同讨论时 |
| CPU与队友接口 | docs/rtl/accelerator/soc-integration.md | 已确认平台事实、接线表、时钟复位、共享RAM、固件和完成语义 | 拿到平台资料时 |
| 物理实现 | docs/rtl/accelerator/physical-validation.md | 库/宏身份、SDC、工具版本、面积/频率/功耗结果与约束 | 实际综合/STA时 |

以上是文档分类，不能机械地据此拆分或重命名RTL模块。原[独立B端实现计划](../../implementation/full-accelerator-plan.md)保留为实现任务账本；本文只规划资料怎样归档。

## 4. 每次推进后需要同步哪些入口

1. 开始讨论：建立对应模块记录，写用户思路、接口问题和待确认项。
2. 解释并达成共识：补理由、最小代码片段、状态或逐拍表。
3. 写RTL/用户优化：记录真实修改及影响，当前阶段可为“已写供阅读”或“待验证”。
4. 实际验证后：报告留verification，模块记录只链接证据并写适用版本，不复制大段日志。
5. 同步docs/rtl/README.md模块目录和implementation/progress.md状态；换阶段时更新handoff。

一条消息的阶段不能因文档模板或总体授权自动跳过。用户要求先阅读或先讨论时，先记录，再继续解释。

## 5. 状态词统一

| 状态 | 可以说明什么 | 还不能说明什么 |
|---|---|---|
| 已规划 | 责任与候选资料位置已列出 | RTL或接口已经存在 |
| 源码已存在 | 磁盘中找到该文件 | 已理解、审阅或验证 |
| 已讨论/供阅读 | 本轮已解释或写好供用户看 | 功能通过 |
| 指定回归通过 | 报告记录的输入范围与源码身份通过 | 任意修改后版本或未测平台也通过 |
| 集成通过 | 指定组件/任务及平台连接被实际验证 | 官方资格及PPA自动通过 |
| 正式指标已验证 | 有对应工具、平台、数据与测量证据 | 超出测量条件的结论 |
