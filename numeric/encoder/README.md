# 完整编码器位真参考

这里的 C 程序只用于主机验证。E203 生产固件负责搬运和命令，不调用这里的神经网络计算。

`encoder_ref.c` 把每个点积固定为从 `+0` 开始、按 k 递增的 `fmaf(a,b,acc)`，偏置另做一次加法；普通加、减、乘、除、平方根各按 binary32 舍入。编译必须保留 `-ffp-contract=off -fno-fast-math`，并使用最近偶数舍入。显式 `fmaf` 保留融合，普通表达式不能被隐式融合或重排。

完整链路为：

```text
完整 [99,64] 输入
 → Q/K/V投影 → QKᵀ×0.125 → 减行最大值 → exp_neg → 逐行归一化
 → 概率×V → 输出投影及偏置 → 第一残差 → LN1
 → FFN1及偏置 → GELU近似 → FFN2及偏置 → 第二残差 → LN2
 → 下一层完整 [99,64] 输入，重复12层 → 第0个token → 主机分类头
```

LN 用总体方差、居中平方和、epsilon=1e-6 和两套独立的训练 gamma/beta。第二残差基底是 LN1 输出。`scores` 的缩放在小尺寸测试中仍固定 0.125，以服从被冻结的硬件协议；小尺寸只是该硬件的可控测试，不能当作另一套官方模型。

`kwt_exp_neg` 使用固定范围约减和八阶 Taylor Horner；`kwt_gelu` 使用原 GELU 论文的 tanh 近似，并通过 exp_neg 的稳定分式实现。官方参考仍为精确 erf GELU。因此 RTL 应当逐位对齐这里的 C 参考，而这里的输出与官方 TF 比较 NRMSE、绝对差和分类变化。三个样本或每类一个样本都不能替代正式 600 样本 Top1 判据。

## 可复现入口

从工作区执行，使用 WSL Ubuntu-24.04：

```bash
bash scripts/export_encoder.sh
bash scripts/run_encoder_reference.sh
bash scripts/run_encoder_reference.sh --output reports/encoder/reference-repeat --compare reports/encoder/reference
.venv-dv/bin/python numeric/encoder/verify_bundle.py reports/encoder/export
.venv-dv/bin/python numeric/encoder/verify_bundle.py reports/encoder/reference
```

公开 test 的另一个独立工程批次：

```bash
bash scripts/export_encoder.sh --dataset-manifest data/encoder_test_subset/manifest.json --output reports/encoder/export-test12
bash scripts/run_encoder_reference.sh --export reports/encoder/export-test12 --output reports/encoder/reference-test12
bash scripts/run_encoder_reference.sh --export reports/encoder/export-test12 --output reports/encoder/reference-test12-repeat --compare reports/encoder/reference-test12
```

导出只读固定 checkpoint 和官方源码，逐项检查 162 个张量、607308 个标量。导出观察原始完整模型里的实际 Dense、LN、attention 张量，返回原 tensor，不重构神经运算；检查每层输出确实逐位进入下一层，并检查实际末层 CLS 经原分类对象得到的 logits 等于原始完整模型输出。旧 `reports/model/baseline` 不会被改写。

`verify_bundle.py` 会回读每个 NPY、二进制和 hex 的每个 word，核对三者相同，检查来源哈希、162 参数覆盖、语义权重打包、12 层边界和最终输出。篡改 hex 后即使重新计算其文件 SHA，也会被它与 NPY 的内容对照捕获。

## 文件与参数布局

每个浮点 word 是一个 IEEE binary32 原始位，hex 每行八位十六进制，bin 为小端连续 word。NPY 用于分析，不作为 RTL 的隐式输入。文件清单为 `manifest.json`；每份数组记录 shape、word 数、三个文件路径及各自 SHA。

| 参数 | shape | 起始 word |
|---|---|---:|
| Wq | 64×64 | 0 |
| Wk | 64×64 | 4096 |
| Wv | 64×64 | 8192 |
| Wo | 64×64 | 12288 |
| bo | 64 | 16384 |
| LN1 gamma | 64 | 16448 |
| LN1 beta | 64 | 16512 |
| W1 | 64×256 | 16576 |
| b1 | 256 | 32960 |
| W2 | 256×64 | 33216 |
| b2 | 64 | 49600 |
| LN2 gamma | 64 | 49664 |
| LN2 beta | 64 | 49728 |

总长 49792 words，全部 row-major。矩阵索引为 `W[input_feature,output_feature]`。每层只使用其对应权重；输入 `cases/<sample>/input.hex` 是首个完整编码器的输入，不能用旧 FFN1 的 LN1 之后 X 代替。

`fixtures/small_3_4_8` 是固定随机种子生成的非零小测试；`small_zero_3_4_8` 用于均匀 softmax、归一化 epsilon 和阶段连通性。每个完整输入在 `cases/<sample>/layer_00` 到 `layer_11` 保存全部 14 个阶段。`constants.json` 是固定常数的 FP32 原始位清单，供 RTL 逐一对照。

成功需要运行退出码 0、`status.json` 和当前 manifest 绑定、独立重复逐 word 一致，以及回读报告 PASS。失败日志和可编译行为变异保存在 `reports/encoder/reference/tests`；TensorFlow 旧 API 与 Trackable 别名告警被保留，恢复是否正确由所有 live 参数与 checkpoint 实际值的逐项相等决定。
