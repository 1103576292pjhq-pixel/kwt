# RTL模块开发记录索引

更新：2026-10-29。这里记录“为什么这样写、讨论过什么、最终怎样实现”，实际源码留rtl/，原始测试证据留verification/。

## 已补录的点积模块

| 顺序 | 模块记录 | 阅读重点 |
|---|---|---|
| 1 | [4×4乘法阵列](compute/mul_array_4x4.md) | 四X/四W打包、16路并行、乘积及标签同拍寄存 |
| 2 | [四上下文累加](compute/acc_context_bank.md) | ctx地址、符号扩展、直接读取acc、clear与active、末项写回 |
| 3 | [偏置与量化](compute/result_convert.md) | acc+bias、41位临时和、RNE、sat16及单槽背压 |
| 4 | [单块计算顶层](compute/dot_product_block_core.md) | 块/k/g/p/q推进、三段式FSM、FLUSH和输出映射 |

这些记录依据本对话和既有证据补录，不声称包含所有历史问答的逐字稿。当前点积源码的最新已登记接收报告为 [block-core-20261028T223900-96b70c](../../verification/block-core-20261028T223900-96b70c/README.md)；之后源码是否变化应核对哈希。

## X/W/bias存储模块

[存储模块总结](memory/README.md)记录容量映射、当前范围与验证边界；分别阅读[存储实体](memory/kwt_storage_array.md)和[逻辑bank封装](memory/kwt_storage_wrapper.md)，了解端口位宽、组合/时序逻辑及L1读返回。目前仅合同模型自检通过，官方模型仍在服务器，未完成正式宏验证。

## 后续整个加速器

2026-10-31新接口版本：[ICB接口与生产顶层说明](accelerator/icb-interface.md)。已移除48位载荷/运行时shift，按实际范围收窄字段，独立设计寄存器和一项命令缓冲；[当前ICB回归](../../verification/icb-20261031T224503-e273cf/README.md)完成两任务800块、50688项Y/flags。旧接口报告只按其历史身份解释，实际E203 CPU/SoC和官方SRAM模型仍待验证。

[供数控制](accelerator/kwt_operand_feeder.md)：独立TB完成53块、13568组，覆盖两槽、尾行、背压与异常返回。

[装载控制](accelerator/kwt_load_ctrl.md)：独立TB核对完整16tile、108545条命令及29类非法输入。

[双结果块](accelerator/kwt_result_blocks.md)：独立TB覆盖非线性填写、响应退休、ACK、并行填读及中止排空。

[任务控制](accelerator/kwt_task_ctrl.md)：独立TB完成400块调度，核对启动错拍、W槽释放及完成边界。

四模块与实际点积核、存储wrapper/实体已通过[三任务内部联合回归](../../verification/controls-20261031T211136-aba7c3/README.md)，1200块、76032项Y/flags一致，另取消一个中途任务。存储采用显式测试合同模型；生产顶层、ICB、官方宏和平台仍待验证。

[整机资料归档与扩展规划](accelerator/README.md)列出已有外围源码、证据缺口、后续每类资料应放在哪里。文件存在、模块级测试、独立B端任务验证、SoC集成和正式PPA分别记录，不能互相代替。

## 持续维护

新增模块时复制[模块记录模板](module-record-template.md)，先写背景和用户思路，随讨论、实现、优化及验证逐步补齐，不在开工时预写“已通过”。

跨模块固定约束引用[架构决策](../architecture/decisions.md)，通用语法解释放[RTL学习笔记](../learning/rtl-basics.md)，协作方式遵循[RTL协作流程](../workflow/rtl-collaboration.md)。
