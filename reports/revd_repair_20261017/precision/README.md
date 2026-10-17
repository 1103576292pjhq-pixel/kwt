# KWT-1 局部精度复测（2026-10-17）

本批工程样本复测完成；正式 600 样本验收仍待验证。冻结官方权重、量化尺度、RTL 和分类头后，本轮 15 个不同输入的 FFN1 最坏层 NRMSE 为 **0.0008930708722084597（0.089307%）**，低于当前局部 3% 算子门槛。全 FP32 编码器在相同输入和分类头上与官方 Top1 **15/15 一致**；14 条真实音频官方与设计均 **13/14 正确（92.8571%）**，观察到的下降为 **0 个百分点**。

这组样本按工程覆盖选取，不能估计总体准确率，也不能替代正式 600 样本。INT16 结果只覆盖独立 FFN1 算子，未测端到端 INT16 分类准确率；全 FP32 结果是 host C 验证模型，未运行本轮 RTL/E203 完整编码器。

## 输入与来源

- 2 条 Google Speech Commands V2 官方 validation WAV，来自不同说话人，均映射为 `_unknown_`。
- 12 条官方发布 test WAV，各覆盖一个类别；仅评测，未调参。
- 1 条显式人工全零音频 `synthetic_zero_silence`，真值 `_silence_`，单列统计。
- 归一化音频 float32 原始比特 SHA 和 encoder input 比特 SHA 的去重数量均为 **15**。
- 公开 test 的 `test_silence_f5468c2d20ff` 有 **15997/16000** 个非零 PCM16 采样，范围 **[-9004,6874]**，与人工全零输入不同。官方和设计都把该真实样本判为 `_unknown_`，标签正确率均计为错误。
- 本地仓库及原工作区的 `data` 都只有 14 条 WAV，没有额外本地 validation 样本。本轮未下载完整数据集。

官方来源 commit：`237e4097afd4f6851e0b82f0a8d65c2dfe8eae30`。checkpoint、源文件、RTL、数值模型和数据 manifest 的 SHA 绑定在 [summary.json](run_20261017_04/summary.json)。

## 两条精度链路

**FFN1 算子：** 本轮当前官方完整图实际产生的每层 `n1` → 冻结的 input scale、W/b 量化与 RNE/saturation → 当前 INT16/48/32 数值模型 → 与同一次官方图的该层 `ffn1` 比较。没有把旧缓存的 X 与本轮 Y 配对。

**全 FP32 分类：** 本轮当前官方 frontend/token input → 当前 C 编码器 12 层 → 同一个官方分类头 → 同批官方 logits 和真实标签。Top1 一致率衡量参考一致性，标签正确率衡量分类是否答对。

| 链路 | 覆盖 | 完成证据 |
|---|---|---|
| INT16 FFN1 | 15 输入 × 12 层；4,561,920 个输出值 | 180 组当前官方 X/floatY、定点输出与逐 case 误差 |
| 原 prototype36 | 旧 3 输入 × 12 层，单独重算 | 当前整数输出、raw48 和两类 flags 与冻结 vectors 全相等 |
| 全 FP32 编码器 | 15 个官方 token input → 12 层 → 分类头 | 当前重编 C library、final/logits、正确性与一致性 |

NRMSE 以每层所有案例的 SSE 和参考平方和汇总，再取 12 层最大值：

$$e_l=\frac{\sqrt{\mathrm{SSE}_l/N_l}}{\max(\sqrt{\sum Y_{\mathrm{ref},l}^2/N_l},10^{-8})},\qquad e=\max_l e_l.$$

| 层 | 汇总 NRMSE | 百分数 |
|---|---:|---:|
| 1 | 0.0007054499880 | 0.070545% |
| 2 | 0.0007179193199 | 0.071792% |
| 3 | 0.0007863357937 | 0.078634% |
| 4 | 0.0008293752445 | 0.082938% |
| 5 | 0.0008171562207 | 0.081716% |
| 6 | 0.0007227412019 | 0.072274% |
| 7 | 0.0007371729830 | 0.073717% |
| 8 | 0.0007332648457 | 0.073326% |
| 9 | 0.0007665808227 | 0.076658% |
| 10 | 0.0008200343901 | 0.082003% |
| 11 | 0.0008789087002 | 0.087891% |
| 12 | 0.0008930708722 | 0.089307% |

最坏单 case 为 `synthetic_zero_silence` 第 7 层，NRMSE **0.0010805270868167786（0.108053%）**。180 case 的 input/weight/bias/raw48/output32 饱和数均为 **0**。原 prototype36 单独重算的最坏层 NRMSE 为 **0.0009342248801263425**，没有与扩展输入混合汇总。

| 分类集合 | 官方正确数 | 当前设计正确数 | 正确率 | 下降 | Top1 一致 |
|---|---:|---:|---:|---:|---:|
| 2 条真实 validation | 2/2 | 2/2 | 100% | 0 百分点 | 2/2 |
| 12 类 published test | 11/12 | 11/12 | 91.6667% | 0 百分点 | 12/12 |
| 14 条真实音频 | 13/14 | 13/14 | 92.8571% | 0 百分点 | 14/14 |
| 人工全零静音 | 1/1 | 1/1 | 100% | 0 百分点 | 1/1 |

当前 C 相对本轮官方模型的最大 final NRMSE 为 **0.000513838042935309**，最大 logits NRMSE 为 **0.0012011445950627928**；Top1 没有改变。

## 历史缓存与调用路径差异

D 仓库原 `reports/encoder/export*` 是精简历史缓存，原 manifest 引用的 input/logits/逐层数组并不完整。首次 run01 因实际缺失 `input.npy` 失败，已保留 [failure.json](run_20261017_01/failure.json)。run02 要求新图与历史缓存全 bit 相同，遇到首个 validation 微差后失败，日志保留。

最终 evaluator 从 D 的 WAV 和官方源码/权重重新生成全部所需张量到本轮目录，不依赖 C 工作区数据缓存。C 完整历史缓存仅用于额外只读核对，manifest 与所有参与比较的数组均核对 SHA。

- 本轮保存的 405 个核心 tensor 与历史缓存比较，**351 个等位，54 个有微差**。54 个均来自两个 validation，差异已从 encoder input 出现；原波形解码 float32 与 baseline audio.npy 完全等位。
- 直接执行未修改的 `model/encoder_export.py` 到新的 `reports/encoder/export-recheck-20261017` 后，原 3 输入的 **81 个核心 tensor 与历史缓存全等位**；它与本精度 evaluator 的比较为 **27/81 等位**，非等位部分仍是两个 validation。
- 当前完整取样与缩减 fetch 的同图实验也出现微差；这证明 fetch 边界可改变本机数值结果。Grappler/fusion 仅是待证机制假设，不能据此声称历史 54 项差异已被完全解释。原诊断结果保留，修正说明见 [narrative_correction.json](trace_diagnosis_01/narrative_correction.json)。
- 主模型、参数和分类头未改动，162 个 checkpoint tensor 都逐项验证。54 项差异最坏 NRMSE 为 **7.578027824309163e-7**，最大绝对差为 **7.033348083496094e-6**，所有 15 项 Top1 不变。具体内核/内存触发原因尚未完全隔离。

逐 tensor 的 maxabs、NRMSE、首个不同元素位置、当前/历史 SHA，以及原入口对照见 [historical_tensor_comparisons.json](run_20261017_04/historical_tensor_comparisons.json)。旧结果不因微差自动失效；本轮误差始终使用同批新 X/Y。

## 原始证据与复现

- [summary.json](run_20261017_04/summary.json)：指标、本地准入门、模型/数据/RTL SHA 和边界。
- [official_current](run_20261017_04/official_current/)：本轮重新生成的 180 组 n1/floatY、完整层权重、分类头、输入、final/logits，各有 manifest。
- [fixed_ffn1_cases.json](run_20261017_04/fixed_ffn1_cases.json)、[layer_metrics.csv](run_20261017_04/layer_metrics.csv)：量化配置、饱和、逐 case 和汇总误差。
- [classification.csv](run_20261017_04/classification.csv)：真值、官方/设计预测、一致性、正确性。
- [array_integrity_manifest.json](run_20261017_04/array_integrity_manifest.json)：本轮 **680 个 NPY** 的相对路径、大小与 SHA。
- [self_audit.json](run_20261017_04/self_audit.json)：180 case 的所有 4,561,920 输出值重新计算误差并核对统计。
- [run_20261017_04.log](run_20261017_04.log)：实际执行日志；[run_20261017_04_audit_final.log](run_20261017_04_audit_final.log)：自审实际执行日志。

主 evaluator SHA256：`8346bb2f00a9b67bafb73ea83d1ba9deaeefbb4c426f7386cd9003311adf8030`。官方/RTL/数值模型与所有量化尺度冻结；未训练、微调、搜索或用 test 选择参数。summary 先判断本地 FFN1 门槛再写 PASS/FAIL，失败仍保存结果并返回非零。本地通过不代表正式比赛通过。

在 PowerShell 执行；新 output 目录必须此前不存在：

```powershell
wsl -d Ubuntu-24.04 -- bash -lc 'cd /mnt/d/github/kwt && PYTHONDONTWRITEBYTECODE=1 /home/user/.local/share/kwt1-envs/dccf0f98c456/model/bin/python scripts/recheck_precision_20261017.py --output reports/revd_repair_20261017/precision/run_fresh'
```

环境沿用 `config/model-environment-location.json`：WSL Ubuntu-24.04，Python 3.8、TensorFlow 2.4.0、NumPy 1.19.5，GCC 依源脚本以 `-O2 -ffp-contract=off -fno-fast-math` 编译当前 host C。主复现不需要历史缓存或 C 盘数据路径。

额外历史比对/自审命令（此步骤才需要只读历史缓存）：

```powershell
wsl -d Ubuntu-24.04 -- bash -lc 'cd /mnt/d/github/kwt && PYTHONDONTWRITEBYTECODE=1 /home/user/.local/share/kwt1-envs/dccf0f98c456/model/bin/python scripts/audit_precision_outputs_20261017.py --run reports/revd_repair_20261017/precision/run_20261017_04 --cache-workspace /mnt/c/Users/11035/Desktop/ic/kwt—1 --current-original-export reports/encoder/export-recheck-20261017'
```
