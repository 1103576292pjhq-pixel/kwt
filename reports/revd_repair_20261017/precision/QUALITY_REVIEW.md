# 本批精度交付自审

**本批通过：冻结参数下的局部算子误差和小样本 FP32 分类复测。整体仍非正式 600 样本验收。**

| 检查项 | 结果 | 证据 |
|---|---|---|
| 当前源实际执行 | 通过 | run04 exit 0；主脚本 SHA 与 summary 相同 |
| 官方源与权重冻结 | 通过 | 原官方源清单逐文件 SHA、162 个 checkpoint tensor 逐项恢复验证；数值源/RTL 前后 SHA 不变 |
| 同批 X/Y 配对 | 通过 | 180 case 均使用本轮 fresh official n1 与同轮 fresh FFN1；未将不同 trace 的输入和参考输出拼接 |
| 输入覆盖与去重 | 通过 | 2 validation unknown + 12 class-covering test + 1 synthetic；waveform/input SHA 各 15 个 distinct |
| 静音真值与重复检查 | 通过 | synthetic 全零且真值 silence；published silence 有 15997 个非零 PCM16 样本，是不同输入 |
| 量化尺度冻结 | 通过 | 每层从冻结 W/b 确定性计算，metadata 与原 prototype 每层配置相同；没有拟合、校准、搜索或 test 调参 |
| 原 prototype36 回归 | 通过 | 当前整数模型 Yq/raw48/overflow/output_saturated 与原冻结数组完全相等 |
| FFN1 结果重算 | 通过 | 180 case、4,561,920 输出全部重新计算 SSE/NRMSE，核对保存指标 |
| 分类口径 | 通过 | 同一输入与分类头；Top1 agreement 与 ground-truth correctness 分列；synthetic 单列 |
| 原始数组与完整性 | 通过 | 680 个 NPY 的相对路径、字节数、SHA manifest 已保存 |
| 历史差异披露 | 通过 | 54 个微差 tensor 均含 maxabs/NRMSE/first difference；原入口对照已实跑；不将 fetch 假设写成已证机制 |
| 失败状态准确性 | 通过 | 先判本地 NRMSE 门槛，再保存 PASS/FAIL；失败保留结果并返回 1；run01/run02 失败证据保留 |
| Markdown 交付 | 通过 | UTF-8 回读与相对资源链接存在性检查；本批无图片 |

局限：validation 只有两个 unknown，test12 按类别工程覆盖选取；未下载全量或补足正式 600 样本。INT16 为 FFN1 单算子数值精度；全 FP32 为当前 host C 参考模型，本轮没有 RTL 或 E203 完整编码器仿真。两个 validation 的当前 evaluator 与原官方 export 调用路径存在微小数值差，权重与输入波形逐位相同，具体内核触发机制仍未完全隔离；已保存独立对照，未把差异混入算子比较。

机器可核对证据：[self_audit.json](run_20261017_04/self_audit.json)、[array_integrity_manifest.json](run_20261017_04/array_integrity_manifest.json)、[historical_tensor_comparisons.json](run_20261017_04/historical_tensor_comparisons.json)、[诊断叙述修正](trace_diagnosis_01/narrative_correction.json)。
