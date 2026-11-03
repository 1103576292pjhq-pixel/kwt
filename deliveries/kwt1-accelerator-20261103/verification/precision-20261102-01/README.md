# 2026-11-02 当前数值方案真实数据精度

**本地完整验证划分：最差第7层 NRMSE=0.0211091260%，低于本科3%门槛。** 当前冻结数值方案和RTL均未修改。

| 项目 | 本次实际重算结果 |
| --- | ---: |
| 原验证索引中的记录数 | 4445 |
| 唯一计算输入 | 4075（4074个WAV + 1个全零静音） |
| 静音在原索引的权重 | 371 |
| 每个样本的FFN1层数 | 12 |
| 按原索引计的任务数 | 53340 |
| 按原索引计的输出数 | 1351848960 |
| 最差层NRMSE | 第7层，0.0211091260% |
| 最差单样本单层NRMSE | 0.0319907069% |
| X/W/bias裁剪数 | 全部0 |
| 输出饱和、raw溢出 | 全部0 |
| 本次完整评测用时 | 240.707秒 |

## 12层汇总

| 编码器层的第一FFN线性层 | NRMSE (%) |
| --- | ---: |
| 1 | 0.01373547 |
| 2 | 0.01359262 |
| 3 | 0.01552826 |
| 4 | 0.01679728 |
| 5 | 0.01950925 |
| 6 | 0.01953393 |
| 7 | 0.02110913 |
| 8 | 0.01961111 |
| 9 | 0.01968927 |
| 10 | 0.01666869 |
| 11 | 0.01473999 |
| 12 | 0.01160750 |

指标按指南PDF第11页：每层汇总所有样本输出的平方误差和与参考能量，计算 `sqrt(SSE/count) / max(sqrt(reference_energy/count),1e-8)`，再取12层最大值。没有平均各样本NRMSE。上表0.02110913%是误差，不是“识别正确率99.97889%”。

## 实际执行和数据身份

先重算已有分层抽样的221条验证缓存（每个语音类20条、1条静音，seed2027，原池4445条），再实际从原始音频重推理完整原验证划分。当前软件整数计算直接调用本工程`model/fixed_numeric.py`的编码、FFN1和解码，不读取旧候选结果作为答案。W暂存采用Fortran布局仅加速主机整数matmul，不改变硬件布局、数值或累加合同。

- 模型上游固定干净提交：`237e4097afd4f6851e0b82f0a8d65c2dfe8eae30`。
- 预训练checkpoint两个文件SHA256核对；运行时162个参数张量逐一与checkpoint一致。
- 子集50个缓存文件SHA256/形状/有限值检查，220个原WAV核对。
- 完整验证4074个WAV哈希和`validation_list.txt`成员核对；没有用测试划分调参。
- 输入为各编码器层attention/残差/第一LayerNorm后的FFN1输入，参考为第一Dense偏置加法后、GELU前输出。
- 以float64重新执行每个浮点affine任务，与提取结果交叉检查；最差相对误差小于1e-6。
- 固定格式：X16/Q12、W16/Q16、bias32/Q28、acc40、RNE右移16、Y16/Q12。
- 完整原索引中的重复静音用一次相同计算，按371次权重累计误差和参考能量；不是随意删除样本。
- 单元测试38项通过，包括5项新误差汇总测试；TF环境下新5项亦通过。独立代码审查无Critical/Important。

机器可读结果与逐层CSV存放在工作区数据目录：

- [完整验证JSON](../../../generated/validation/current-ffn1-precision-20261102-01/full-validation/report.json)
- [完整验证逐层CSV](../../../generated/validation/current-ffn1-precision-20261102-01/full-validation/layers.csv)
- [完整样本清单和multiplicity](../../../generated/validation/current-ffn1-precision-20261102-01/full-validation/samples.json)
- [221条抽样验证JSON](../../../generated/validation/current-ffn1-precision-20261102-01/subset-221/report.json)：最差第7层0.0206417243%。
- [本次范围与校验摘要](summary.json)：补充区分抽样和全验证，包含源报告SHA256。

## 复现

WSL工程根目录，输出目录必须使用新名字；不会覆盖之前数据：

```sh
python3 -B scripts/evaluate_precision.py --mode cache --output '/mnt/d/嵌赛芯片设计赛道/generated/validation/current-ffn1-precision-next/subset-221'
/home/juhui/miniconda3/envs/kwt1/bin/python -B scripts/evaluate_precision.py --mode full --output '/mnt/d/嵌赛芯片设计赛道/generated/validation/current-ffn1-precision-next/full-validation'
```

## 证据边界

本次是当前软件数值模型的真实数据精度，未执行新的真实数据RTL/SoC仿真；之前合成数据的E203完整任务PASS仍是另一份证据。官方600样本名单尚未公开，本结果不冒充官方验收，不报告整网分类准确率，也不能推导综合时序/功耗/面积。

离线环境为Python3.8.20、NumPy1.19.5、TensorFlow2.4.0；替代了上游要求的TensorFlow2.4.0rc1，运行时等价性尚未证明。重推理出现12个Dense/GELU checkpoint对象引用警告和旧API弃用提示；没有屏蔽这些警告，参数张量逐项核对与浮点affine交叉检查均通过。不能把本结果写成“所有依赖完全符合原版本”或“零警告”。
