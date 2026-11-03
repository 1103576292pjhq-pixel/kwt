# 来源与版本边界

本工程由用户于2026-10-27要求新建，用于独立保存当前架构及先行数值模型。

## 已有来源

- 2026-10-31用户提供的赛事方答复截图：[参数加载与性能计时原文及项目解读](official/20261031-loading-and-timing-qa.md)，原图已按字节归档。明确队伍自建加载环境和完整装载至写回计时范围；不据此推定正式共享RAM接口或宏型号。

- 架构讨论稿原位置：`C:/Users/asus/Documents/Codex/2026-10-26/new-chat/outputs/20261027-kwt1-architecture-spec`。本工程docs/architecture保存其副本，便于后续自包含阅读。
- 原包源码阅读记录保存为 [source-review.md](source-review.md)。该文描述原包acc/bias48；本工程目标按用户确认改为acc40/bias32，二者身份不可混淆。
- 个人数值依据：`D:/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core/docs/shared/numeric-format-v0.1.json`及其数值说明；共享方案为i16_w16_a40_o16_rne。
- 原包参考及数据：`D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend/model/fixed_numeric.py`、`data/dev12`。本模型沿用同一合法域算术合同，使用重新编写的明确接口；没有复制原RTL、固件或完整数据集。
- 指定模型/数据的原始来源与局限仍由原包来源材料说明；本轮未重新提取音频、重建TensorFlow推理或训练模型。
- E203上游：[riscv-mcu/e203_hbirdv2](https://github.com/riscv-mcu/e203_hbirdv2)。此次新目录不重新下载E203，也不改变本地vendor副本。

## 本目录中的实际新增工作

固定格式的标量与矩阵软件模型、冻结合同检查、编码/解码、共享布局、测试、可运行手算例子、DEV12只读重算工具及其证据。规范不表示新RTL已实现；原包历史性能、个人旧RTL综合指标不转移为本工程实测。

原工程、冻结包、旧未提交代码与所有输入黄金保持原状；本轮没有提交或推送任何仓库。
