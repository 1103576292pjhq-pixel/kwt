# 文档总入口

2026-11-01普通命名与当前独立加速器接收：[记录与源码入口](../verification/naming-20261101-3ac1b5/README.md)。活动工程已改为 `kwt1-accelerator`，生产顶层 `kwt_accelerator`，清单 `rtl/kwt.f`；当前协议优先读[ICB说明](rtl/accelerator/icb-interface.md)，不使用旧交接ABI。

**2026-10-31当前来源规则：[仅以赛方资料为外部设计依据](workflow/design-sources.md)。旧架构及交接中的FIFO深度、命令格式、寄存器表等不再自动作为当前规范；现有源码保留并按赛方资料逐项核对。**

分类更新：2026-10-29。文档分为协作流程、学习笔记、模块开发记录、架构与数值、验证证据、进度交接及资料来源。原文和历史报告保留原路径，方便追溯；新内容按下面职责增加。

## 先按问题找资料

| 你现在想看什么 | 直接打开 |
|---|---|
| 我先讲想法、你纠正、再写代码和优化的流程 | [RTL协作流程](workflow/rtl-collaboration.md) |
| timescale、for/generate、非阻塞赋值、背压、signed、三段式FSM | [RTL学习笔记](learning/rtl-basics.md) |
| 每个模块为什么这样写、讨论和优化过什么 | [RTL模块开发记录](rtl/README.md) |
| 四个点积模块的注意点与时序 | [乘法](rtl/compute/mul_array_4x4.md)、[累加](rtl/compute/acc_context_bank.md)、[量化](rtl/compute/result_convert.md)、[顶层](rtl/compute/dot_product_block_core.md) |
| X/W/bias容量、SRAM例化、bank封装及验证范围 | [存储模块总结](rtl/memory/README.md) |
| 后续整个加速器怎样继续归档 | [整机资料扩展规划](rtl/accelerator/README.md) |
| 新模块记录写哪些内容 | [模块开发记录模板](rtl/module-record-template.md) |
| 当前做到哪里、哪些只写了源码 | [实现进度](implementation/progress.md) |
| 某次通过的命令、数据、源码版本 | [验证索引](../verification/README.md) |

## 目录职责

```text
docs/
├── workflow/          协作步骤与持续记录规则
├── learning/          通用RTL知识和常见问答
├── rtl/
│   ├── compute/       四个点积模块的开发过程与注意点
│   ├── accelerator/   整机资料分类、接口/任务/恢复/平台等扩展规划
│   └── module-record-template.md
├── architecture/      整体冻结规格、模块原理、常量与决策
├── model/             数值黄金与数据布局解释
├── implementation/    阶段进度和实现计划
├── handoff/           换对话的接手入口，保留历史阶段
├── images/            图解与来源说明
└── data-sources.md    音频、权重、浮点提取数据来源

rtl/                   生产源码，与docs/rtl开发记录分开
verification/          每次验证的原始证据，不搬进笔记目录
```

## 设计背景与数值规则

| 文档 | 职责 |
|---|---|
| [架构规格](architecture/README.md) | 目标系统与冻结的数值、存储、时序边界 |
| [从数据到控制的模块原理](architecture/module-guide.md) | 跨模块背景与目标系统，不能当作全部RTL已完成 |
| [设计选择与常量依据](architecture/decisions.md) | acc40、16MAC/CTX4、bank/槽/owner等选择的原因 |
| [数值模型说明](model/README.md) | 定点编码、RNE/饱和及共享容器 |
| [原始数据来源](data-sources.md) | 本地音频、模型及样例，和验证用数据的关系 |
| [平台资料](architecture/platform-sources.md) | E203、共享SRAM及尚未确认的事实 |
| [图解入口](images/README.md) | 整机目标架构和点积核示意图，历史状态以源码/报告核对 |
| [旧包分析](source-review.md)、[来源清单](sources.md) | 对应时期的只读分析与参考出处 |

## 进度、计划与换对话

- [实现进度](implementation/progress.md)：当前状态，不替代验证报告。
- [独立加速器实现计划](implementation/full-accelerator-plan.md)：实现任务账本；勾选与否须结合实际源码和证据核对。
- [本次文档分类计划](implementation/20261029-documentation-plan.md)：本次整理范围、结构和检查。
- [完整加速器交接](handoff/full-accelerator-new-chat.md)：下一阶段背景；先读协作流程，再接收实际文件。
- [旧点积开发交接](handoff/dot-product-new-chat.md)：保留点积开发历史和冻结要求，不重启已完成模块。

## 后续新增规则

每个新RTL模块用一份记录，保存用户想法、纠正理由、共识、代码、用户优化和验证链接。通用问题归learning，跨模块规则归architecture，整机接口/任务/恢复/平台归rtl/accelerator。仅列为规划的文件不提前冒充已写正文。

当前已发现外围RTL及有限合成数据回归，部分旧文档仍是“尚未实现”的早期状态，详见[整机现状核对](rtl/accelerator/README.md)。文件存在、组件仿真、整机任务、SoC和PPA分别标记；具体通过身份始终追溯到verification。
