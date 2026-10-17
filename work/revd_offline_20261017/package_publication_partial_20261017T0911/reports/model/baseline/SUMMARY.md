# 官方 KWT-1 浮点基准

- 验收：PASS
- 真实 validation WAV：2 个
- 明确标注的合成零输入 silence：1 个
- 十二层独立 FFN1 案例：36 个
- 运行期逐变量核对：162 个 live 模型变量全部精确等于 checkpoint reader 张量
- 独立文件回读：每一层导出的 W/b 再次精确等于指定 checkpoint 张量
- NumPy Y=XW+b 最大绝对误差：9.53674316e-07
- NumPy 最大 NRMSE（参考 RMS 分母下限 1e-8）：4.21651006e-08
- 原完整模型有/无 hook 的 logits 与 MFCC：零差
- 无 hook 中间参考复用已建立的官方层对象，状态由完整原 block 传播；回放最终 logits 与原完整模型零差
- 原完整模型 Dense/LN 观察值与无 hook 官方层对象回放的 X/W/b/Y：逐层零差
- 重复运行全部 .npy SHA-256：PASS

| 样本 | 分区 | 原始词 | 12 类目标 | 预测 |
|---|---|---|---|---|
| eight_750e3e75_nohash_0 | validation | eight | _unknown_ | _unknown_ |
| eight_d3831f6a_nohash_3 | validation | eight | _unknown_ | _unknown_ |
| synthetic_zero_silence | synthetic_silence | _silence_ | _silence_ | _silence_ |

浮点容差只用于软件对照。本批没有量化、RTL、test 集调参或完整数据集准确率测量。两个真实样本均为 eight，按官方 12 类口径属于 _unknown_，不能据此推断十二类总体准确率。

兼容限制：上游指定 TensorFlow 2.4.0rc1，当前可取得的兼容运行时为 2.4.0；不声称与 RC1 逐位等价。加载 checkpoint 时仍出现 Dense/GELU trackable 引用不一致警告，完整 checkpoint 未全部消费；实际模型数值变量均通过逐变量精确核对。保留警告，不宣称其根因已修复。

`manifest.json` 记录数组与来源/配置哈希、逐层对照、checkpoint 身份、官方 flags 和允许的推理覆盖项。`restore-verification.json` 是运行期全部 live 变量的恢复证据；文件回读独立核对导出的 FFN1 W/b。
