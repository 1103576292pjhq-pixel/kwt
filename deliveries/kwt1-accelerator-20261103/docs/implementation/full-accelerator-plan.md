# FFN1独立B端实现计划与执行账本

2026-10-29维护说明：下文为原实现计划；当前已有部分外围源码和有限合成数据报告，未勾选的任务不等于文件不存在。接续前核对[整机现状及归档规划](../rtl/accelerator/README.md)，并遵循[用户先讲思路、讨论纠正、共识后实现与用户优化](../workflow/rtl-collaboration.md)的协作方式。本次资料整理不自动勾选实现/验证完成项。

> 按交接已授权在当前无Git目录直接执行；不创建副本、提交或推送。使用writing-plans、executing-plans和test-driven-development流程。用户要求逐段解释而非重复审批。

**Goal:** 在原有点积核外完成本地存储、tile优先矩阵调度、双结果块、FIFO8及ICB。

**Architecture:** 保留一套acc40和量化器。X四bank、W双槽、bias32寄存器；L1返回与标签对齐；结果发布后推进矩阵，CPU读响应退休推进cursor，ACK释放owner。

**Tech Stack:** Verilog-2001 `.v`、中文注释、Ubuntu WSL Python3/Icarus，现有整数黄金不改。

**Spec:** `docs/handoff/full-accelerator-new-chat.md`、`docs/architecture/`、`model/numeric-contract.json`。

## 全局约束与核对

- 固定99×64×256；16/16/product32/bias32/acc40/Y16；RNE16。四个计算模块及宏零修改。
- 每次编辑前重读；新增文件不得覆盖已有文件。只读参考包控制结构可适配，标明来源。
- 复位同步低有效；只清有效位、owner及进度；不清大RAM。
- task32、sequence24、count8、FIFO8/half及MMIO ABI保持。
- 平台/宏/STA/PPA/官方样本单列，独立B端通过不扩写为赛事通过。

## Review Focus

1. g0新X与x_hold旁路、k63最终返回、复位旧返回隔离。
2. 尾行bank3不得读取未装载字；W活动槽不能被写。
3. 两结果满后OPEN/FIFO等待时CPU必须drain；非法命令不可永久等待。
4. RESULT响应背压只消费一次；错误ACK不释放，末ACK响应退休前不能done。
5. 连续任务、PAIR_NEXT失败位置不变、FIFO同拍入出、flush排响应。

## 顺序任务

### Task 1：存储与供数底座
- [ ] 新建 `rtl/memory/kwt_sp16_l1.v`、`kwt_operand_store.v`；SP读写互斥、L1返回、映射和尾mask。
- [ ] 先写 `tb/system/tb_operand_store.v`，运行缺实现失败；实现后检查全部X/W地址、两个W槽和bias。
- [ ] 证据记录至独立verification目录。

### Task 2：命令执行和矩阵调度
- [ ] 新建 `rtl/control/kwt_matrix_core.v`，包含单项q、装载规则、W owner和三段式外层FSM。
- [ ] 内部实例化原点积核；请求/接收9位计数，L1标签、x_hold、256组排空。
- [ ] 先写端口级TB检查400块tile优先、完整矩阵和非法命令，再实现。

### Task 3：双结果块
- [ ] 新建 `rtl/control/kwt_result_blocks.v`，适配参考owner控制，payload19不重算量化。
- [ ] 先测试非线性fill、重复/遗漏/越界、两槽满、快照/退休、错误/陈旧/提前ACK、尾48。

### Task 4：FIFO8与ICB
- [ ] 新建 `rtl/interface/kwt_icb.v` 和显式源清单；适配原ABI，Verilog-2001。
- [ ] 先写 `tb/system/tb_icb.v`、`scripts/verify_accelerator.py`：完整矩阵、连续12任务、fast/legacy共队列、PAIR/PAIR_NEXT、响应背压、非法地址/mask、flush。
- [ ] 独立B端done必须核心结束、FIFO/q空、结果全ACK、本地响应安静。

### Task 5：解释、复核与交付
- [ ] 保存模块端口/位宽/逐段说明、队友ICB/复位/完成接入合同。
- [ ] 跑受影响回归、现有33项软件测试，核对原10文件SHA256不变。
- [ ] 独立只读审查及必要修复，记录实际证据和未覆盖项。

## 接收记录

2026-10-28：完整交接已读；报告绑定的10份源码/宏/TB/脚本/模型SHA256全部匹配磁盘。没有交接后修改的字节证据。无`.git`，未改旧目录。现有报告5220完成/3取消仅证明计算核端口。

Ruling: 使用已冻结设计直接进入分阶段实现，省略重复架构审批；来自交接第1节明确授权。无Git脚本/commit/worktree流程以本账本和源码快照替代。
