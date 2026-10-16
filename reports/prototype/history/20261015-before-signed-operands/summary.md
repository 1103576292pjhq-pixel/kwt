# 前三项基础原型验收汇总

状态：ACCEPTED；完整回归、一键入口与主控独立复核均通过。本轮长时间执行已结束，验收记录见 [parent-acceptance.json](parent-acceptance.json)。

| 检查 | 实际结果 |
|---|---|
| 数值单元测试 | 67通过，无失败/跳过 |
| 验收门禁与故障注入 | 38通过，无失败/跳过；固定DOT哈希清单及单元执行/源码/XML绑定 |
| DOT64 | 8项测试、52笔结果对照、真实波形检查、lint通过 |
| FFN1完整矩阵 | 36个99×64×256案例，912384输出，RTL对整数参考零差 |
| 实际有效MAC | 58392576次，由RTL握手监视计数 |
| 独立完整尺寸复跑 | 1例，25344输出；输出SHA-256匹配 |
| 最大案例NRMSE | 0.001080518214（0.108052%） |
| 最大逐层NRMSE | 0.000934224880（0.093422%） |
| 本36案例饱和 | X/W/b/raw48/output32全部0次；极值行为另由单元/协议测试覆盖 |
| 来源与自审 | 124官方文件及冻结float/代码/配置/向量绑定；两轮自审通过 |

## 周期与复跑哈希

四类周期分别累加，不包含全部装载命令/ACK控制拍，不代表端到端时延或时序签核。

| 类别 | 36例周期总数 |
|---|---|
| load | 1654343 |
| compute | 62954496 |
| row_wait | 39257 |
| readback | 1821204 |

首案例及独立复跑的输出数组SHA-256（int32小端连续字节，不含npy头）：`b6ef91b483286a3826dc25e9a53d0a7946ec388d3f112dcd2fe7a01122fbe599`。

## 证据入口

- [逐案例误差、周期、计数与哈希](case-results.csv)
- [逐层误差、饱和数](layer-results.csv)
- [完整矩阵状态及全部实际输出索引](ffn1/full/status.json)
- [独立复跑](ffn1/repeat/status.json)
- [每案例/每层数值与来源](vectors/manifest.json)
- [执行阶段退出码](command-results.tsv)
- [规格自审](review-spec.md)、[代码与测试自审](review-quality.md)、[审查哈希](review.json)
- [FFN1学习入口](../../docs/prototype/README.md)

## 执行记录

```bash
bash scripts/run_prototype.sh
```

本轮从WSL /tmp调用同一绝对入口，preflight/numeric/gate-tests/dot64/protocol/full/repeat/lint/finalize全部退出0。主回归完成后未重复启动同样的36例；复跑仅首个完整尺寸案例。初次Icarus路径失败与各RED证据仍保留，路径修正后才计入成功。

主控随后修复两项验收绑定缺口，从`/tmp`再次以`--reuse-verified`调用统一入口，全部阶段退出0；数值67项、门禁38项、DOT64八项及矩阵协议重新通过，36案例及完整尺寸复跑的实际输出重新回读且哈希一致。计算RTL、FFN1测试台和向量未改变，因此没有重复整批矩阵仿真。主控还用独立程序回读全部912384输出及标志位，逐项一致。

3%仅适用于当前两份真实unknown validation WAV和一份合成silence的36层案例；不声明官方600样本、E203、150MHz时序或PPA通过。
