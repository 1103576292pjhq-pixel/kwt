# FFN1 数值参考模型实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在用户新建的独立目录交付与bias32/acc40/out16规格一致、可执行且有证据的数值黄金模型。

**Architecture:** Python整数标量路径明确表达逐k累加、sat40、RNE16及sat16；NumPy矩阵路径在合法域证明下使用精确int64。模型固定99×64与64×256，输出Y及flags；编码/解码、共享布局和小型例子独立于RTL时序。

**Tech Stack:** Python 3.10+、NumPy、unittest；当前实测Python3.12.4/NumPy1.26.4。

**Spec:** [架构规格](../architecture/README.md)。

## Global Constraints

- 固定X16/Q12、W16/Q16、product32/Q28、bias32/Q28、acc40/Q28、Y16/Q12；RNE右移16，flags bit0/1/2。
- 正式矩阵尺寸99×64、64×256、bias256。标量组件固定K64；不承诺硬件运行时变尺寸。
- 不修改或覆盖旧个人工程、冻结包、既有fixture和历史报告；本轮不写RTL，不启动综合。
- 新目录独立于原Git工作树；不初始化Git、不提交、不推送。本项目自身的完整测试替代无关旧工程全套测试。
- 只需NumPy，不重新训练或标定，不改现有尺度；原始模型/音频数据不复制。
- 用户已授权“先写数值模型并建新文件夹”，本计划随实现交付，沿用本对话直接执行。

## Review Focus

- 负数RNE tie与正数一致，最终饱和发生在舍入之后。
- 非法整数、bool、float、超宽bias必须拒绝，不能先窄化后验证。
- 所有K64前缀可由40位表示；vector/scalar必须一致。
- W列主序、Y符号扩展32位、flags最后项唯一，打包不能改数学方向。
- 冻结DEV12对照必须读取输入重算，不改黄金，也不将软件通过冒称RTL/官方精度通过。

### Task 1: 算术、范围和类型

**Files:** model/fixed_numeric.py、tests/test_numeric.py。

**Interfaces:** convert_accumulator(sum_i,bias_i,is_last=False)返回raw/rounded/y/flags；dot64_scalar(x,w,bias,is_last=False)固定64项；ffn1_int16(x,w,bias)返回int16 Y及uint8 flags。

- [x] 先写包含预期字面值的RNE、边界、非法输入和完整矩阵测试；无实现时确认缺功能失败。
- [x] 实现Python-int精确标量、固定shift16转换、严格dtype/shape矩阵模型。
- [x] 全部测试通过，包含k63非零、最大负输入乘积和正负抵消。

### Task 2: 编码、数据布局和冻结规格

**Files:** model/fixed_numeric.py、model/numeric-contract.json、model/layout.py、tests/test_formats.py。

**Interfaces:** encode_finite返回编码与端点裁剪计数；decode_fixed返回实数；pack_shared/unpack_shared按固定小端布局互转；load_contract验证冻结规格而非提供可变数值开关。

- [x] 先写浮点tie、NaN/Inf、巨大有限数、非法dtype、列主序和有符号容器测试，确认失败。
- [x] 实现这些行为，明确X/W/bias与Y/flags的容器和范围校验。
- [x] 运行本项目全部unittest，确认通过。

### Task 3: 可运行例子、DEV12对照和说明

**Files:** scripts/run_example.py、scripts/check_dev12.py、tests/test_tools.py、README.md、docs/model/README.md、verification/*。

**Interfaces:** run_example输出手算块和JSON；check_dev12接收原冻结data/dev12路径，独立解包X/W/bias并对照全部expected/flags，输出身份哈希及统计。

- [x] 先写CLI行为测试，使用实际子进程和临时fixture，确认缺功能失败。
- [x] 实现脚本；复制用户架构文档，记录源文件身份，不复制完整模型数据。
- [x] 全套测试、手算例子和原DEV12十二项实际对照全部完成；写入结果与未运行边界。
- [x] 按executing-plans技能要求做一次独立只读最终审查；无实质代码问题，更新计划状态后完成最终验证。

本计划不包含RTL实现。保留rtl/与tb/目录说明后续用途，不放未经验证的假RTL。
