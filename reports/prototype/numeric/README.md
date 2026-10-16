# 数值模型实现与验收

本批完成：固定整数规范、Python 逐位参考、NumPy int64 加速但先证明边界的矩阵参考、36 个完整矩阵案例的生成和磁盘回读复核。没有训练、校准、样本驱动参数选择或性能搜索。

## 结果

- Linux `.venv-dv`：67 个单元测试通过，无跳过。包括 RNE 正负半值、0/47 位边界、960 个独立 Fraction 对照、16/32/48 位饱和、49 位偏置加法、极值、抵消、最后一项、非法输入、全零权重、最小覆盖尺度、路径/哈希/shape/dtype/NaN、36 案例完整性、输出目录保护与固定源码清单。
- 36 案例 × 25,344 输出 = 912,384 个输出；共 288 个实际 `.npy` 文件。每个矩阵至少 11 个位置用 Python 任意精度标量点积独立核对 NumPy int64 矩阵计算。
- 完整回读：36 案例逐数组核对哈希、shape/dtype 和数值，从原始 float32 X/W/b 独立重建整数期望；原始 124 个 vendor 文件哈希不变。
- 所有层 `sx=2^-8`；由冻结 W 范围推导的 `sw` 恰好都是 `2^-16`，并非人为统一选择；保守范围直接推导的 shift 恰好都是 5。因此 `sy=2^-19`。每层各自的保守 raw 上界保留在 manifest。
- 最大单案例 NRMSE：0.0010805182139773971（0.1080518%）。
- 最大三输入聚合逐层 NRMSE：0.0009342248801263425（0.0934225%）。
- 输入、权重、偏置、48 位原始和、32 位输出的饱和计数全部为 0。数值测试额外覆盖会饱和的人工边界。
- 现有子集通过 3% 误差门槛；仅两条真实 validation WAV（都是 unknown）与一条显式合成 silence。不能据此声称完整数据集、官方 600 样本或最终比赛验收通过。

## 逐层 NRMSE（三输入误差能量合并）

| 层 | NRMSE |
|---|---:|
| 1 | 0.0007538479065307427 |
| 2 | 0.0007523882903830604 |
| 3 | 0.0007895789968834902 |
| 4 | 0.0008743945381349849 |
| 5 | 0.0008491512073981397 |
| 6 | 0.0007921626308651612 |
| 7 | 0.0007636200925089475 |
| 8 | 0.0007307897016707924 |
| 9 | 0.0008244385183817710 |
| 10 | 0.0008877125380801155 |
| 11 | 0.0009171130343438870 |
| 12 | 0.0009342248801263425 |

## 真实运行证据

从 WSL 工作区执行，下列命令退出码均已记录：

1. `python -m pytest tests/numeric -q`：初始模块缺失，非零；日志 `red.log`。
2. `python -m pytest tests/numeric/test_artifacts.py -q`：初始 artifacts 模块缺失，非零；日志 `artifacts-red.log`。
3. `.venv-dv/bin/python -m pytest tests/numeric -q --junitxml=reports/prototype/numeric/results.xml`：退出 0，67 passed；最终日志 `review-fix-green.log` 和 XML（早期 `green.log` 保留原 48 项结果）。
4. `.venv-dv/bin/python scripts/generate_prototype_vectors.py`：退出 0；修复后重新完整生成日志 `review-fix-generate.log`；同时保存前后源文件核查和全数组回读。
5. `.venv-dv/bin/python scripts/generate_prototype_vectors.py --verify-only`：新的进程退出 0；最终日志 `review-fix-verify.log`；再次回读复算全部 36 案例。

API 与逐字段 schema 见 `numeric/README.md`。本次使用现成 `.venv-dv` 的 Linux Python3.12 / NumPy2.4.6，不使用独立的旧 TensorFlow 环境，也没有改动原始模型、权重、float baseline 或 repeat。

## 独立审查 P2 修复

1. 旧入口在验证 `--output` 前写 RUNNING 标记，错误指定输入目录可能覆盖原 manifest。现已在任何 mkdir/写入前检查输出与保留输入是否祖先/后代重叠，并解析符号链接。负例仅在 `/tmp` 模拟工作区运行；对目录、全部文件内容及状态文件做前后比较，证明拒绝过程无写入，没有对真实 baseline/repeat 运行危险负例。
2. 旧源码哈希验证只遍历清单现有键，缺项可能被绕过。现使用固定三项集合并检查集合严格相等，再逐一校验摘要。空清单、少一/两项、多项和摘要错误均有拒绝测试；精确清单和安全输出有正向测试。
3. 针对修复的 TDD RED：`review-fix-red.log`，18 failed、3 passed，退出 1。修复后完整 GREEN 为 67 passed、0 skipped。源码改变后重新生成全部 36 案例，整数规则与精度结果保持不变。
