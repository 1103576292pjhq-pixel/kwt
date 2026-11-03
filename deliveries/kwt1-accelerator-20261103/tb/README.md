# RTL测试平台目录

当前独立加速器系统TB为 `interface/tb_icb_system.v`，实例化生产顶层 `kwt_accelerator`，由 `scripts/verify_icb.py --contract-models` 调用。`system/`中的旧草稿不适配当前独立寄存器协议，不作为当前测试入口。以下保留各阶段说明；本次名字整理见[接收记录](../verification/naming-20261101-3ac1b5/README.md)。

2026-10-31新增：[四个控制模块与内部联合TB](control/README.md)。运行`/usr/bin/python3 -B scripts/verify_controls.py --contract-models`；该联合模式使用测试专用存储模型，不能作为官方宏、ICB或平台通过证据。下面保留计算核阶段说明。

当前组件测试为 `compute/tb_mul_array_4x4.v`，逐拍检查4×4有符号乘法、乘积位置、有效位、标签、空拍保持和同步复位。

在Ubuntu WSL的工程根目录运行 `/usr/bin/python3 -B scripts/verify_mul_array.py`，会生成独立输入/期望向量，实际编译与仿真，并在新的 `verification/mul-array-*` 目录保存命令、日志和SHA256。首次通过记录为 `verification/mul-array-20261027T213804-ee2726/`。

累加组件测试为 `compute/tb_acc_context_bank.v`。运行 `/usr/bin/python3 -B scripts/verify_acc_context.py`，执行逐拍扫描全部64个acc的自检、640项最终acc与Python黄金对照，以及错误副本检错。首次完整证据见 `verification/acc-context-20261028T131043-851d21/`。

量化自检为 `compute/tb_result_convert.v`。运行 `/usr/bin/python3 -B scripts/verify_result_convert.py`，保留原16例手算检查，另生成5788组独立黄金向量，执行合法发送方保持、连续流、随机背压、复位取消及事务ID账本核对。当前用户版证据见 `verification/result-convert-20261028T200650-af0cd6/`。

顶层自检为 `compute/tb_dot_product_block_core.v`。运行 `/usr/bin/python3 -B scripts/verify_block_core.py`，执行23块定向/随机/复位用例、既有手算完整任务400块、本地真实样例12层4800块，逐项比较Y/flags并重建矩阵；检查背压保持、末组排空、位置/bias映射及6种故意错误。正式证据见 [顶层验证说明](../verification/block-core-20261028T211900-669e21/README.md)。

当前Python测试仍位于 `tests/`。计算顶层通过对应回归；存储、整机及PPA仍未验证。
