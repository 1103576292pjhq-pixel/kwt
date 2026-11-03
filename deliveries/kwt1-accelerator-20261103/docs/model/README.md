# 数值参考模型：每段代码为什么这样写

本模型是后续RTL的结果标准。它计算编码整数，不模拟周期、bank或FIFO。正式格式见 [numeric-contract.json](../../model/numeric-contract.json)，对应 [fixed_numeric.py](../../model/fixed_numeric.py)。

## 1. 怎样读代码

| 函数/对象 | 输入和输出 | 原因 |
|---|---|---|
| `_signed_integer` | 原始标量→经过范围检查的Python int | 在窄化前拒绝非法高位、浮点和bool，避免错误被转换掩盖 |
| `Conversion` | raw、rounded、y、flags四个只读字段 | 同时看到加偏置后、舍入后、饱和后三个值，便于手算及RTL对照 |
| `convert_accumulator` | acc40+bias32→Conversion | 41位等效临时和、sat40、正负对称RNE16、sat16 |
| `dot64_scalar` | 两个64项signed16序列+bias32→Conversion | 最直接按k顺序写的整数定义，便于组件检查 |
| `_task_arrays` | 检查X/W/bias的dtype和shape | 拒绝将int64非法数据直接astype成int16，固定正式矩阵尺寸 |
| `ffn1_int16` | 完整X/W/bias→Y int16和flags uint8 | 高效生成完整矩阵黄金，供未来RTL逐项比较 |
| `encode_finite` | 有限浮点数组+角色→编码数组/裁剪计数 | 负责参数格式转换，不负责训练或修改尺度 |
| `decode_fixed` | 合法编码数组+角色→float64 | 解码到真实数值后才能与浮点参考比较 |
| `load_contract` | 冻结JSON→经过一致性检查的合同 | 不允许只改一个文件就悄悄变成acc48、sat32或另一种尺度 |

## 2. 哪些位宽由数值推导

X实数为Xq×2^-12，W实数为Wq×2^-16，所以乘积是XqWq×2^-28；bias以Q28编码，才能直接加到乘积和。输出Q12，需要右移28−12=16位。

64项乘积加任意signed32 bias的编码范围为[-70,864,863,232，70,866,960,383]，在signed40内。所有合法前缀也在范围内，因此完整任务中raw溢出不会发生。CTX4保存不同输出，不扩大一个点积的长度。

## 3. 舍入和饱和必须分开

raw取绝对值后除65536：余数超过32768时进位，恰等于32768且商为奇数时进位，再恢复符号。这样+2.5→2、+3.5→4、−2.5→−2、−3.5→−4。

舍入后才限幅到[-32768,32767]。例如bias=2147483647、点积0，RNE得到32768，最终Y=32767且saturated=1；bias=−2147483648则恰好Y=−32768，saturated=0。

`convert_accumulator`允许任意合法acc40，便于压力验证。acc最大值+bias1会触发raw40溢出；该组件输入不是合法K64任务可达到的点积。flags[0]检查raw40溢出，flags[1]检查最终Y16饱和，flags[2]由任务坐标决定。

## 4. 为什么矩阵模型能用NumPy int64

标量路径显式逐k做sat40。矩阵路径先用精确int64矩阵乘法，再转换：由于合法输入的每个前缀都已证明不会触发sat40，两者在这个合法域完全等价。此优化不是对任意位宽、任意K都成立。

矩阵接口只接受native int16 X/W和native int32 bias，尺寸固定99×64、64×256、256。它不接受列表自动窄化，也不把较小矩阵接口误当成硬件动态变尺寸。

## 5. 编码、裁剪与解码

```python
import numpy as np
from model.fixed_numeric import encode_finite, decode_fixed, ffn1_int16

encoded_x = encode_finite(np.zeros((99, 64), dtype=np.float32), 'x')
encoded_w = encode_finite(np.zeros((64, 256), dtype=np.float32), 'w')
encoded_b = encode_finite(np.zeros(256, dtype=np.float32), 'bias')
y, flags = ffn1_int16(encoded_x.values, encoded_w.values, encoded_b.values)
y_real = decode_fixed(y, 'y')
```

编码拒绝NaN、Inf、复数和整数输入。有限浮点先裁到可表示实数端点，再按ties-to-even编码；避免大浮点乘尺度溢出。`endpoint_clipped_count`统计原浮点超出端点的项数，即使未裁剪时舍入可能回到端点，也计为一次端点裁剪。需要保留此统计，不能宣称该步骤总是无损。

解码Y须除4096；共享32位容器只保存16位结果的符号扩展。解码后与指定浮点参考的精度评估仍需实际参考数组，本轮只做数值合同和既有整数黄金对照，没有新做官方精度评测。

## 6. 共享布局为何单独放layout.py

数学W为[64,256]，共享字节却按列主序W[col×64+k]，因此打包使用W.T的行主序。X和Y均按行主序。

| 对象 | 有效类型 | 共享容器 | 字节数 |
|---|---|---|---:|
| X | int16[99,64] | 小端int16 | 12672 |
| W | int16[64,256] | 转置后小端int16 | 32768 |
| bias | int32[256] | 符号扩展小端int64 | 2048 |
| Y | int16[99,256] | 符号扩展小端int32 | 101376 |
| flags | uint8[99,256] | 一项一字节 | 25344 |

`pack_inputs/unpack_inputs`和`pack_outputs/unpack_outputs`互转这些数据对象，尚未给它们分配正式物理地址。unpack bias64时先检查signed32范围；unpack Y32时先检查signed16符号扩展；完整任务flags要求raw溢出0、保留位0且last仅在[98,255]出现一次。

## 7. 怎样证明实现没有自说自话

- 手算字面值覆盖正负tie、饱和先后、极值、k63贡献和有符号乘法。
- 随机矩阵选点使用独立Python求和和Decimal ROUND_HALF_EVEN生成期望，不调用被测转换器来算期望。
- CLI测试使用独立构造的零输入/零黄金，并故意破坏黄金、loader覆盖或bias容器，确认工具拒绝。
- 实际读取原DEV12十二套loader还原X/W/bias，重算并逐项比较原expected/flags，结果和来源SHA256单独记录。

本目录三个实现阶段都保存了先失败、后通过的测试日志。软件对照通过的范围是当前整数数值合同，不包含实际RTL时序、总线错误恢复、宏模型或正式PPA。
