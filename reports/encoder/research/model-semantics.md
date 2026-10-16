# KWT-1 十二层编码器：冻结模型语义核对

核对日期：2026-10-15。本文只核对模型事实和导出边界，不改变冻结源码、权重、数值格式或验收阈值，也不进行参数搜索。

## 1. 结论与证据范围

当前模型为时间维注意力的 KWT-1：12 层、单头、嵌入宽度 64、FFN 中间宽度 256、99 个 token，使用 **PostNorm、精确 erf 语义 GELU、带训练得到 gamma/beta 的 LayerNorm**。Q/K/V 投影无偏置，其余 Dense 投影带偏置。每层完整输入和输出均为 `[99,64]`；FFN1 的输入是本层第一残差之后的 LN1 输出，不能当成完整 Encoder 的输入。

事实来源优先级：固定版本本地源码 → 冻结 checkpoint 的全部实际恢复变量 → 当前运行对象配置 → 官方上游同版本源码。固定提交为 `237e4097afd4f6851e0b82f0a8d65c2dfe8eae30`。实际核对 124 份冻结文件哈希未变；源清单 SHA-256 为 `984daac0310841c068eea47d1e9386ff8873ce7901b16641e849a5b45a51be34`。

2026-10-15 的独立 TF 2.4.0 会话重新执行了 `restore_and_verify`：162/162 个模型变量与 checkpoint 内容精确相等，162 个变量均不同于随机初始化。`checkpoint_fully_consumed=false` 反映训练侧额外状态未被推理图消费；全部模型变量已经逐项对照，不能据前者误判推理权重未恢复。原有 Trackable 别名告警仍会出现，未隐去。

运行对象实测：`prenorm=false`，`approximate_gelu=false`，`training=false`，`heads=1`，`dropout=0.0`，`return_softmax=0`，无 distillation token。LN 构建后 `axis=[2]`（三维 `[B,T,D]` 的最后特征维）、`epsilon=1e-6`、`center=true`、`scale=true`；两个 LN 的参数彼此独立。

## 2. 精确计算链

以下省略 batch 维，token 数 $T=99$，特征宽度 $D=64$。所有模型参数原始 dtype 为 FP32。

### 2.1 首层输入：从 MFCC 建立 token

原音频 `[1,16000]` 经官方 SpeechFeatures 得到 `[1,98,40]` MFCC。对每帧执行：

$$
P=\mathrm{MFCC}\,W_{patch}+b_{patch},\qquad P\in\mathbb{R}^{98\times64}.
$$

然后把训练得到的 class token 放在序列第 0 行，叠加所有 99 个位置的 position embedding：

$$
H_0=\operatorname{concat}_{token}(class\_emb,P)+pos\_emb.
$$

第 0 token 参与全部自注意力，不得提前摘出。没有 attention mask，没有 token 平均池化。源码：`kws_streaming/models/kws_transformer.py:125-129,152-165`；`transformer_utils.py:141-150,167-186`。

### 2.2 本层自注意力

令本层输入为 $H\in\mathbb{R}^{99\times64}$：

$$
Q=HW_Q,\quad K=HW_K,\quad V=HW_V,
$$

$$
S=QK^T/\sqrt{64}=QK^T/8,\quad
A_{ij}=\frac{\exp(S_{ij})}{\sum_{j'=0}^{98}\exp(S_{ij'})},
$$

$$
C=AV,\qquad O=CW_O+b_O.
$$

Q/K/V 是 **三个独立的 `[64,64]` Dense kernel**，均 `use_bias=False`。注意力分数与概率均为 `[99,99]`。softmax 沿最后的 key/token 轴，即逐 query 行计算。`combine_heads` 是 `[64,64]` 的输出投影，带 `[64]` bias，不能省略。

源码并未把 QKV 存成一个 kernel。若硬件采用打包格式，可把 `concat(WQ,WK,WV, axis=1)` 存为 `[64,192]`，结果按最后一维依次切成 Q/K/V；导出时必须声明排列。TF kernel 的索引顺序为 `[input_feature,output_feature]`，硬件转存为输出列连续时须显式转置，不能只更改 shape。

源码：`transformer_utils.py:33-80`，其中 QKV/输出投影定义在 43-46 行，分数缩放/softmax/AV 在 49-55 行，head 拆分和拼合在 58-79 行。

### 2.3 第一残差与 LN1

$$
R_1=H+O,\qquad U=LN_1(R_1).
$$

每个 token 独立沿其 64 个特征计算：

$$
\mu_i=\frac1{64}\sum_d R_{1,id},\quad
\sigma_i^2=\frac1{64}\sum_d(R_{1,id}-\mu_i)^2,
$$

$$
U_{id}=\gamma_{1,d}\frac{R_{1,id}-\mu_i}{\sqrt{\sigma_i^2+10^{-6}}}+\beta_{1,d}.
$$

方差使用总体方差除以 64；不采用样本方差除以 63。epsilon 加在方差上、开方之前。gamma/beta 是恢复的训练参数，不得以初始化的 1/0 代替。两个 LN 均非跨 token 归一化。

### 2.4 FFN1、GELU 与 FFN2

$$
Z=UW_1+b_1,\qquad Z\in\mathbb{R}^{99\times256},
$$

$$
G=\frac Z2\left[1+\operatorname{erf}\left(\frac Z{\sqrt2}\right)\right],
\qquad F=GW_2+b_2,\quad F\in\mathbb{R}^{99\times64}.
$$

`W1=[64,256]`，`b1=[256]`；`W2=[256,64]`，`b2=[64]`，两者均有 bias。官方显式传 `approximate_gelu=false`，TF Addons 0.12.1 在 TF 2.4 上转调 `tf.nn.gelu(x, approximate=False)`。不能把 tanh GELU 当成本模型的精确参考。

源码：`transformer_utils.py:87-93`；`kws_transformer.py:84-94,160-162`。TF Addons 官方 v0.12.1 的 `activations/gelu.py:70-88` 给出转调与 erf/tanh 两条语义。

### 2.5 第二残差、LN2 和层间传递

$$
R_2=U+F,\qquad H_{next}=LN_2(R_2).
$$

LN2 的轴、epsilon 和方差定义同 LN1，但使用独立的 gamma2/beta2。第二残差基底是 `U`，不是本层原输入 `H`。随后 `H_next` 原样成为下一完整 Encoder 的输入；不能把 256 维的 FFN1 输出直接接下一层。

PostNorm 分支源码：`transformer_utils.py:112-119`。相邻的 104-111 行是未启用的 PreNorm 分支，只用于核对，不能混用。推理 `training=false`，dropout 率也恰为 0，因此两个 dropout 无数值作用，但残差/LN 位置必须保持。

### 2.6 十二层之后的分类头

$$
logits=H_{12}[0,:]W_{cls}+b_{cls}\in\mathbb{R}^{12}.
$$

直接取最后层第 0 个 class token，经过 `[64,12]` Dense 和 `[12]` bias。没有额外 final LN，没有平均 token 池化，没有蒸馏头。本配置 `return_softmax=0`，因此输出是 logits；类别判定用 argmax，无需另做分类 softmax。

类别顺序为 `_silence_, _unknown_, yes, no, up, down, left, right, on, off, stop, go`。源码：`transformer_utils.py:185-194`，`kws_transformer.py:183-217`；标签文件：`models_data_v2_12_labels/kwt1/labels.txt`。

## 3. 完整参数取法与形状

不依赖 `dense_5` 这类易随图构造变化的显示名导出。优先按已恢复对象的语义属性取参数，并通过 `restore_and_verify` 返回的变量名 → checkpoint key 映射验证。每层 13 个参数张量，共 156 个；加 patch、token/position 与分类的 6 个，共 162 个。

| 语义对象（block 为 enc_layers[i]） | 形状 | 本层 checkpoint 路径后缀 |
|---|---|---|
| `block.att.query_dense.kernel` | `[64,64]` | `att/query_dense/kernel` |
| `block.att.key_dense.kernel` | `[64,64]` | `att/key_dense/kernel` |
| `block.att.value_dense.kernel` | `[64,64]` | `att/value_dense/kernel` |
| `block.att.combine_heads.kernel` | `[64,64]` | `att/combine_heads/kernel` |
| `block.att.combine_heads.bias` | `[64]` | `att/combine_heads/bias` |
| `block.ffn.layers[0].kernel` | `[64,256]` | `ffn/layer_with_weights-0/kernel` |
| `block.ffn.layers[0].bias` | `[256]` | `ffn/layer_with_weights-0/bias` |
| `block.ffn.layers[2].kernel` | `[256,64]` | `ffn/layer_with_weights-1/kernel` |
| `block.ffn.layers[2].bias` | `[64]` | `ffn/layer_with_weights-1/bias` |
| `block.layernorm1.gamma` | `[64]` | `layernorm1/gamma` |
| `block.layernorm1.beta` | `[64]` | `layernorm1/beta` |
| `block.layernorm2.gamma` | `[64]` | `layernorm2/gamma` |
| `block.layernorm2.beta` | `[64]` | `layernorm2/beta` |

本层完整 checkpoint key 为 `layer_with_weights-0/enc_layers/{i}/{后缀}/.ATTRIBUTES/VARIABLE_VALUE`，其中 i 为 0..11。这里 FFN2 的 Sequential 数组索引为 2，但 checkpoint 的 **带权重层**索引为 1；GELU 无权重。

| 全局语义对象 | 形状 | checkpoint key（省略末尾 `.ATTRIBUTES/VARIABLE_VALUE`） |
|---|---|---|
| `transformer.patch_proj.kernel` | `[40,64]` | `layer_with_weights-0/patch_proj/kernel/` |
| `transformer.patch_proj.bias` | `[64]` | `layer_with_weights-0/patch_proj/bias/` |
| `transformer.pos_emb` | `[1,99,64]` | `layer_with_weights-0/pos_emb/` |
| `transformer.class_emb` | `[1,1,64]` | `layer_with_weights-0/class_emb/` |
| `head.layers[0].kernel` | `[64,12]` | `layer_with_weights-1/layer_with_weights-0/kernel/` |
| `head.layers[0].bias` | `[12]` | `layer_with_weights-1/layer_with_weights-0/bias/` |

固定模型的全部实际变量名、形状和 key 已保存在 `reports/model/baseline/restore-verification.json` 的 `variables`，下方附录逐项列出。恢复代码证据为 `model/run_baseline.py:180-224`，应先初始化再恢复，恢复后禁止再次初始化。直接从 checkpoint reader 取值时也需与模型对象语义核对，不能把优化器槽或训练计数当成推理参数。

## 4. 参考中间结果的正确导出入口

冻结目录 `reports/model/baseline/cases/<sample>/layer_XX/X.npy` 是每层 **LN1 之后、FFN1 之前**的 `[99,64]`。对应 `Y.npy` 是 GELU 之前的 `[99,256]`。这些文件没有完整 Encoder 输入、QKV、softmax、FFN2 或 LN2 输出，不能改名后冒充这些量。

新导出应写独立目录，继续使用已恢复的原层对象，保留冻结报告不变。可靠入口为 `model/run_baseline.py:147-177` 的同对象官方重放和 `:227-291` 的 graph/session 结构：

1. 从 `model.layers[1].output` 获取官方 MFCC，按原 `patch_proj/class_emb/pos_emb` 计算 `H0`。
2. 每层循环开始前保存 `encoder_input = x`；通过本层原 `query_dense/key_dense/value_dense` 获取 QKV，调用 `attention` 或明确重放分数/缩放/softmax，保存注意力中间量。
3. 使用原 `combine_heads`、LN1、FFN1、原 GELU 对象、FFN2、LN2 得到各个参考量；使用原 `block(x, training=False)` 的输出作为权威 `encoder_output` 并作为下一层输入。
4. 按原分类头计算 logits，与同会话、无 hook 的完整模型输出对照；检查没有新增变量，所有模型变量仍与 checkpoint 精确相等。
5. 为每个 `[99,64]` 完整输入/输出和各阶段输出保存 shape、dtype、hash、sample、layer、source/checkpoint hash；参数可只存一份，样本结果引用它。

本次实际新图中，三份原样本均得到首层输入 `[1,99,64]`、末层输出 `[1,99,64]`，新图的同对象十二层重放最终 logits 与同会话原模型逐位相等；首层输入均不等于已有 FFN1 X。首层输入范围：真实样本 `eight_750e3e75_nohash_0` 为 `[-2.5905223,2.3082557]`，`eight_d3831f6a_nohash_3` 为 `[-4.1040020,3.5428751]`，合成静音为 `[-13.3418951,13.7924328]`。

跨独立执行时需同时记录 max-abs/NRMSE，不能仅因数学等价就承诺逐位相等。本次新图中两个真实音频的中间 LN1 与旧冻结文件存在非逐位一致，静音一致；同会话重放最终 logits 仍逐位一致。随后直接调用未修改的 `execute_graph(..., hooked=False)`，使用冻结 `audio.npy` 再验证，得到以下结果：

| 样本 | 12 层 LN1 最大 max-abs | 12 层 LN1 最大 NRMSE | 与旧 logits 逐位相等 |
|---|---:|---:|---|
| eight_750e3e75_nohash_0 | 3.3676624298095703e-6 | 5.809232329870397e-7 | 否 |
| eight_d3831f6a_nohash_3 | 4.410743713378906e-6 | 6.33308150886455e-7 | 否 |
| synthetic_zero_silence | 0 | 0 | 是 |

差异很小，但不应声称此次新执行与旧文件逐位一致。当前未定位差异来自前端还是后续浮点路径；后续正式新导出应记录新的权威来源、内部对照和误差，不能通过覆盖旧报告或放宽旧冻结验收来消除它。

## 5. 共享标量 FP32 运算器初稿的语义边界

这是功能实现可行性判断，不是正式面积/性能结论，也没有搜索参数。

- 一个可综合 FP32 标量加/乘/除/平方根运算器配合顺序控制器，可以逐项执行上述投影、QK、softmax、AV、残差、LN、FFN 和分类；共享只改变时间调度，不应删减模型阶段。
- softmax 采用逐行减最大值后计算 exp 再归一化，与原式数学等价，并有利于数值稳定；必须保留 query 行、key 列和归一化轴。
- LN 必须保留两个独立的 gamma/beta、总体方差和 `1e-6`。迭代 reciprocal/sqrt/exp/erf 的精度应分别验证，不能把“FP32 数据格式”误说成“非线性函数精确”。
- GELU 的参考目标仍为 erf 版本；若硬件用固定迭代/多项式逼近 erf，必须报告其独立误差及传播到整层/十二层的误差。直接换为 tanh GELU 是另一数值实现，需要明确声明，不能改动原参考来迁就硬件。
- TensorFlow 的矩阵归约次序、融合行为和硬件串行 FP32 加乘可能不同；功能比较应有数值误差指标，若同时要求 RTL 位真，则另建确定每步舍入/运算次序的硬件参考，并与官方 FP32 参考同时比较。一个比较证明硬件实现一致，另一个比较证明模型误差可接受。
- 原前三功能的 signed16 DOT64/FFN1 验证仍然成立；FP32 完整链不能自动证明旧定点核已接入该链。若完整链采用不同运算器，验证报告必须分别说明两条路径及真正共享的模块。
- 仿真用 `real/shortreal`、`$exp/$sqrt` 或 Python/DPI 返回计算结果，不能替代可综合 RTL 运算硬件。可以用在 testbench 参考，但综合报告需覆盖实际执行数据路径和控制器。
- 首稿应检查真实 99-token/64-feature 形状、不同层参数切换、连续十二层状态传递和 classifier。只用极小随机矩阵或独立层输入回放，不能证明完整模型级联。

## 6. 官方与本地核对入口

- [Arm 官方固定提交 Transformer 源码](https://github.com/ARM-software/keyword-transformer/blob/237e4097afd4f6851e0b82f0a8d65c2dfe8eae30/kws_streaming/models/transformer_utils.py)。本次联网读取与固定本地文件语义一致。
- [Arm 官方固定提交模型构造](https://github.com/ARM-software/keyword-transformer/blob/237e4097afd4f6851e0b82f0a8d65c2dfe8eae30/kws_streaming/models/kws_transformer.py)。
- [TensorFlow Addons v0.12.1 GELU 实现](https://github.com/tensorflow/addons/blob/v0.12.1/tensorflow_addons/activations/gelu.py)。
- 本地冻结事实：`reports/model/baseline/effective-flags.json`、`restore-verification.json`、`manifest.json`；参考构造：`model/run_baseline.py`。

## 附录：162 个实际恢复参数

| # | live variable name | shape | checkpoint key |
|---|---|---|---|
| 1 | `kws_transformer/dense/kernel:0` | `[40, 64]` | `layer_with_weights-0/patch_proj/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 2 | `kws_transformer/dense/bias:0` | `[64]` | `layer_with_weights-0/patch_proj/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 3 | `kws_transformer/transformer_block/multi_head_self_attention/dense_1/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/0/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 4 | `kws_transformer/transformer_block/multi_head_self_attention/dense_2/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/0/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 5 | `kws_transformer/transformer_block/multi_head_self_attention/dense_3/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/0/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 6 | `kws_transformer/transformer_block/multi_head_self_attention/dense_4/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/0/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 7 | `kws_transformer/transformer_block/multi_head_self_attention/dense_4/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/0/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 8 | `kws_transformer/transformer_block/sequential/dense_5/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/0/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 9 | `kws_transformer/transformer_block/sequential/dense_5/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/0/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 10 | `kws_transformer/transformer_block/sequential/dense_6/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/0/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 11 | `kws_transformer/transformer_block/sequential/dense_6/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/0/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 12 | `kws_transformer/transformer_block/layer_normalization/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/0/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 13 | `kws_transformer/transformer_block/layer_normalization/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/0/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 14 | `kws_transformer/transformer_block/layer_normalization_1/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/0/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 15 | `kws_transformer/transformer_block/layer_normalization_1/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/0/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 16 | `kws_transformer/transformer_block_1/multi_head_self_attention_1/dense_7/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/1/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 17 | `kws_transformer/transformer_block_1/multi_head_self_attention_1/dense_8/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/1/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 18 | `kws_transformer/transformer_block_1/multi_head_self_attention_1/dense_9/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/1/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 19 | `kws_transformer/transformer_block_1/multi_head_self_attention_1/dense_10/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/1/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 20 | `kws_transformer/transformer_block_1/multi_head_self_attention_1/dense_10/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/1/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 21 | `kws_transformer/transformer_block_1/sequential_1/dense_11/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/1/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 22 | `kws_transformer/transformer_block_1/sequential_1/dense_11/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/1/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 23 | `kws_transformer/transformer_block_1/sequential_1/dense_12/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/1/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 24 | `kws_transformer/transformer_block_1/sequential_1/dense_12/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/1/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 25 | `kws_transformer/transformer_block_1/layer_normalization_2/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/1/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 26 | `kws_transformer/transformer_block_1/layer_normalization_2/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/1/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 27 | `kws_transformer/transformer_block_1/layer_normalization_3/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/1/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 28 | `kws_transformer/transformer_block_1/layer_normalization_3/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/1/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 29 | `kws_transformer/transformer_block_2/multi_head_self_attention_2/dense_13/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/2/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 30 | `kws_transformer/transformer_block_2/multi_head_self_attention_2/dense_14/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/2/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 31 | `kws_transformer/transformer_block_2/multi_head_self_attention_2/dense_15/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/2/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 32 | `kws_transformer/transformer_block_2/multi_head_self_attention_2/dense_16/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/2/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 33 | `kws_transformer/transformer_block_2/multi_head_self_attention_2/dense_16/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/2/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 34 | `kws_transformer/transformer_block_2/sequential_2/dense_17/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/2/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 35 | `kws_transformer/transformer_block_2/sequential_2/dense_17/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/2/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 36 | `kws_transformer/transformer_block_2/sequential_2/dense_18/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/2/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 37 | `kws_transformer/transformer_block_2/sequential_2/dense_18/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/2/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 38 | `kws_transformer/transformer_block_2/layer_normalization_4/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/2/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 39 | `kws_transformer/transformer_block_2/layer_normalization_4/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/2/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 40 | `kws_transformer/transformer_block_2/layer_normalization_5/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/2/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 41 | `kws_transformer/transformer_block_2/layer_normalization_5/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/2/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 42 | `kws_transformer/transformer_block_3/multi_head_self_attention_3/dense_19/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/3/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 43 | `kws_transformer/transformer_block_3/multi_head_self_attention_3/dense_20/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/3/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 44 | `kws_transformer/transformer_block_3/multi_head_self_attention_3/dense_21/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/3/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 45 | `kws_transformer/transformer_block_3/multi_head_self_attention_3/dense_22/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/3/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 46 | `kws_transformer/transformer_block_3/multi_head_self_attention_3/dense_22/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/3/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 47 | `kws_transformer/transformer_block_3/sequential_3/dense_23/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/3/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 48 | `kws_transformer/transformer_block_3/sequential_3/dense_23/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/3/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 49 | `kws_transformer/transformer_block_3/sequential_3/dense_24/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/3/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 50 | `kws_transformer/transformer_block_3/sequential_3/dense_24/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/3/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 51 | `kws_transformer/transformer_block_3/layer_normalization_6/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/3/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 52 | `kws_transformer/transformer_block_3/layer_normalization_6/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/3/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 53 | `kws_transformer/transformer_block_3/layer_normalization_7/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/3/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 54 | `kws_transformer/transformer_block_3/layer_normalization_7/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/3/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 55 | `kws_transformer/transformer_block_4/multi_head_self_attention_4/dense_25/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/4/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 56 | `kws_transformer/transformer_block_4/multi_head_self_attention_4/dense_26/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/4/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 57 | `kws_transformer/transformer_block_4/multi_head_self_attention_4/dense_27/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/4/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 58 | `kws_transformer/transformer_block_4/multi_head_self_attention_4/dense_28/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/4/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 59 | `kws_transformer/transformer_block_4/multi_head_self_attention_4/dense_28/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/4/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 60 | `kws_transformer/transformer_block_4/sequential_4/dense_29/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/4/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 61 | `kws_transformer/transformer_block_4/sequential_4/dense_29/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/4/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 62 | `kws_transformer/transformer_block_4/sequential_4/dense_30/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/4/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 63 | `kws_transformer/transformer_block_4/sequential_4/dense_30/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/4/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 64 | `kws_transformer/transformer_block_4/layer_normalization_8/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/4/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 65 | `kws_transformer/transformer_block_4/layer_normalization_8/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/4/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 66 | `kws_transformer/transformer_block_4/layer_normalization_9/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/4/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 67 | `kws_transformer/transformer_block_4/layer_normalization_9/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/4/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 68 | `kws_transformer/transformer_block_5/multi_head_self_attention_5/dense_31/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/5/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 69 | `kws_transformer/transformer_block_5/multi_head_self_attention_5/dense_32/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/5/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 70 | `kws_transformer/transformer_block_5/multi_head_self_attention_5/dense_33/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/5/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 71 | `kws_transformer/transformer_block_5/multi_head_self_attention_5/dense_34/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/5/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 72 | `kws_transformer/transformer_block_5/multi_head_self_attention_5/dense_34/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/5/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 73 | `kws_transformer/transformer_block_5/sequential_5/dense_35/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/5/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 74 | `kws_transformer/transformer_block_5/sequential_5/dense_35/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/5/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 75 | `kws_transformer/transformer_block_5/sequential_5/dense_36/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/5/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 76 | `kws_transformer/transformer_block_5/sequential_5/dense_36/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/5/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 77 | `kws_transformer/transformer_block_5/layer_normalization_10/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/5/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 78 | `kws_transformer/transformer_block_5/layer_normalization_10/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/5/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 79 | `kws_transformer/transformer_block_5/layer_normalization_11/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/5/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 80 | `kws_transformer/transformer_block_5/layer_normalization_11/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/5/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 81 | `kws_transformer/transformer_block_6/multi_head_self_attention_6/dense_37/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/6/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 82 | `kws_transformer/transformer_block_6/multi_head_self_attention_6/dense_38/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/6/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 83 | `kws_transformer/transformer_block_6/multi_head_self_attention_6/dense_39/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/6/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 84 | `kws_transformer/transformer_block_6/multi_head_self_attention_6/dense_40/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/6/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 85 | `kws_transformer/transformer_block_6/multi_head_self_attention_6/dense_40/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/6/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 86 | `kws_transformer/transformer_block_6/sequential_6/dense_41/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/6/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 87 | `kws_transformer/transformer_block_6/sequential_6/dense_41/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/6/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 88 | `kws_transformer/transformer_block_6/sequential_6/dense_42/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/6/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 89 | `kws_transformer/transformer_block_6/sequential_6/dense_42/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/6/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 90 | `kws_transformer/transformer_block_6/layer_normalization_12/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/6/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 91 | `kws_transformer/transformer_block_6/layer_normalization_12/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/6/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 92 | `kws_transformer/transformer_block_6/layer_normalization_13/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/6/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 93 | `kws_transformer/transformer_block_6/layer_normalization_13/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/6/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 94 | `kws_transformer/transformer_block_7/multi_head_self_attention_7/dense_43/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/7/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 95 | `kws_transformer/transformer_block_7/multi_head_self_attention_7/dense_44/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/7/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 96 | `kws_transformer/transformer_block_7/multi_head_self_attention_7/dense_45/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/7/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 97 | `kws_transformer/transformer_block_7/multi_head_self_attention_7/dense_46/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/7/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 98 | `kws_transformer/transformer_block_7/multi_head_self_attention_7/dense_46/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/7/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 99 | `kws_transformer/transformer_block_7/sequential_7/dense_47/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/7/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 100 | `kws_transformer/transformer_block_7/sequential_7/dense_47/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/7/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 101 | `kws_transformer/transformer_block_7/sequential_7/dense_48/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/7/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 102 | `kws_transformer/transformer_block_7/sequential_7/dense_48/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/7/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 103 | `kws_transformer/transformer_block_7/layer_normalization_14/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/7/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 104 | `kws_transformer/transformer_block_7/layer_normalization_14/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/7/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 105 | `kws_transformer/transformer_block_7/layer_normalization_15/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/7/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 106 | `kws_transformer/transformer_block_7/layer_normalization_15/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/7/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 107 | `kws_transformer/transformer_block_8/multi_head_self_attention_8/dense_49/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/8/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 108 | `kws_transformer/transformer_block_8/multi_head_self_attention_8/dense_50/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/8/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 109 | `kws_transformer/transformer_block_8/multi_head_self_attention_8/dense_51/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/8/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 110 | `kws_transformer/transformer_block_8/multi_head_self_attention_8/dense_52/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/8/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 111 | `kws_transformer/transformer_block_8/multi_head_self_attention_8/dense_52/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/8/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 112 | `kws_transformer/transformer_block_8/sequential_8/dense_53/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/8/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 113 | `kws_transformer/transformer_block_8/sequential_8/dense_53/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/8/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 114 | `kws_transformer/transformer_block_8/sequential_8/dense_54/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/8/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 115 | `kws_transformer/transformer_block_8/sequential_8/dense_54/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/8/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 116 | `kws_transformer/transformer_block_8/layer_normalization_16/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/8/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 117 | `kws_transformer/transformer_block_8/layer_normalization_16/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/8/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 118 | `kws_transformer/transformer_block_8/layer_normalization_17/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/8/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 119 | `kws_transformer/transformer_block_8/layer_normalization_17/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/8/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 120 | `kws_transformer/transformer_block_9/multi_head_self_attention_9/dense_55/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/9/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 121 | `kws_transformer/transformer_block_9/multi_head_self_attention_9/dense_56/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/9/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 122 | `kws_transformer/transformer_block_9/multi_head_self_attention_9/dense_57/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/9/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 123 | `kws_transformer/transformer_block_9/multi_head_self_attention_9/dense_58/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/9/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 124 | `kws_transformer/transformer_block_9/multi_head_self_attention_9/dense_58/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/9/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 125 | `kws_transformer/transformer_block_9/sequential_9/dense_59/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/9/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 126 | `kws_transformer/transformer_block_9/sequential_9/dense_59/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/9/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 127 | `kws_transformer/transformer_block_9/sequential_9/dense_60/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/9/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 128 | `kws_transformer/transformer_block_9/sequential_9/dense_60/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/9/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 129 | `kws_transformer/transformer_block_9/layer_normalization_18/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/9/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 130 | `kws_transformer/transformer_block_9/layer_normalization_18/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/9/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 131 | `kws_transformer/transformer_block_9/layer_normalization_19/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/9/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 132 | `kws_transformer/transformer_block_9/layer_normalization_19/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/9/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 133 | `kws_transformer/transformer_block_10/multi_head_self_attention_10/dense_61/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/10/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 134 | `kws_transformer/transformer_block_10/multi_head_self_attention_10/dense_62/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/10/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 135 | `kws_transformer/transformer_block_10/multi_head_self_attention_10/dense_63/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/10/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 136 | `kws_transformer/transformer_block_10/multi_head_self_attention_10/dense_64/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/10/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 137 | `kws_transformer/transformer_block_10/multi_head_self_attention_10/dense_64/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/10/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 138 | `kws_transformer/transformer_block_10/sequential_10/dense_65/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/10/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 139 | `kws_transformer/transformer_block_10/sequential_10/dense_65/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/10/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 140 | `kws_transformer/transformer_block_10/sequential_10/dense_66/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/10/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 141 | `kws_transformer/transformer_block_10/sequential_10/dense_66/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/10/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 142 | `kws_transformer/transformer_block_10/layer_normalization_20/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/10/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 143 | `kws_transformer/transformer_block_10/layer_normalization_20/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/10/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 144 | `kws_transformer/transformer_block_10/layer_normalization_21/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/10/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 145 | `kws_transformer/transformer_block_10/layer_normalization_21/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/10/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 146 | `kws_transformer/transformer_block_11/multi_head_self_attention_11/dense_67/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/11/att/query_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 147 | `kws_transformer/transformer_block_11/multi_head_self_attention_11/dense_68/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/11/att/key_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 148 | `kws_transformer/transformer_block_11/multi_head_self_attention_11/dense_69/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/11/att/value_dense/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 149 | `kws_transformer/transformer_block_11/multi_head_self_attention_11/dense_70/kernel:0` | `[64, 64]` | `layer_with_weights-0/enc_layers/11/att/combine_heads/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 150 | `kws_transformer/transformer_block_11/multi_head_self_attention_11/dense_70/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/11/att/combine_heads/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 151 | `kws_transformer/transformer_block_11/sequential_11/dense_71/kernel:0` | `[64, 256]` | `layer_with_weights-0/enc_layers/11/ffn/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 152 | `kws_transformer/transformer_block_11/sequential_11/dense_71/bias:0` | `[256]` | `layer_with_weights-0/enc_layers/11/ffn/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 153 | `kws_transformer/transformer_block_11/sequential_11/dense_72/kernel:0` | `[256, 64]` | `layer_with_weights-0/enc_layers/11/ffn/layer_with_weights-1/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 154 | `kws_transformer/transformer_block_11/sequential_11/dense_72/bias:0` | `[64]` | `layer_with_weights-0/enc_layers/11/ffn/layer_with_weights-1/bias/.ATTRIBUTES/VARIABLE_VALUE` |
| 155 | `kws_transformer/transformer_block_11/layer_normalization_22/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/11/layernorm1/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 156 | `kws_transformer/transformer_block_11/layer_normalization_22/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/11/layernorm1/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 157 | `kws_transformer/transformer_block_11/layer_normalization_23/gamma:0` | `[64]` | `layer_with_weights-0/enc_layers/11/layernorm2/gamma/.ATTRIBUTES/VARIABLE_VALUE` |
| 158 | `kws_transformer/transformer_block_11/layer_normalization_23/beta:0` | `[64]` | `layer_with_weights-0/enc_layers/11/layernorm2/beta/.ATTRIBUTES/VARIABLE_VALUE` |
| 159 | `pos_emb:0` | `[1, 99, 64]` | `layer_with_weights-0/pos_emb/.ATTRIBUTES/VARIABLE_VALUE` |
| 160 | `class_emb:0` | `[1, 1, 64]` | `layer_with_weights-0/class_emb/.ATTRIBUTES/VARIABLE_VALUE` |
| 161 | `sequential_12/dense_73/kernel:0` | `[64, 12]` | `layer_with_weights-1/layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE` |
| 162 | `sequential_12/dense_73/bias:0` | `[12]` | `layer_with_weights-1/layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE` |

Tensor count: 162; scalar parameter count: 607308.

