# 脚本入口

2026-11-01普通命名后，当前完整独立加速器入口为 `/usr/bin/python3 -B scripts/verify_icb.py --contract-models`，DUT为 `kwt_accelerator`，系统TB为 `tb/interface/tb_icb_system.v`。`verify_accelerator.py`及`tb/system/`属于旧接口草稿，不是当前验收入口；本次未将其旧协议改成新协议。具体接收范围见[改名记录](../verification/naming-20261101-3ac1b5/README.md)。

全部从工程根目录运行。RTL工具在Ubuntu WSL中使用 `/usr/bin/python3`、`iverilog`、`vvp`；不要从WSL调用Windows Anaconda。

| 脚本 | 用途 | 生成内容 |
|---|---|---|
| `verify_mul_array.py` | 乘法组件自检、错误注入检错、33项软件回归 | 新的 `verification/mul-array-日期时间-标识/` |
| `verify_acc_context.py` | 累加自检、640项Python黄金对照、错误注入检错、33项软件回归 | 新的 `verification/acc-context-日期时间-标识/` |
| `verify_result_convert.py` | 量化16例手算、5788组独立黄金、随机背压/复位事务账本、7种错误检错、33项软件回归 | 新的 `verification/result-convert-日期时间-标识/`，含本次源码快照 |
| `verify_block_core.py` | 顶层定向/握手/复位、手算任务、本地真实样例12层分块重放、6种错误检错、33项软件回归 | 新的 `verification/block-core-日期时间-标识/`；含整数编码、重建结果、事务账本、源码快照 |
| `verify_storage.py` | 当前存储实体/wrapper；官方模型需显式提供，合同自检需`--contract-models` | 独立`verification/storage-*`及模型身份 |
| `verify_controls.py` | 四控制模块独立TB；`--contract-models`增加实际核及当前存储的三任务联合自检 | 独立`verification/controls-*`、固定种子向量、实际响应账本及源码快照；不是ICB/官方宏验收 |
| `verify_icb.py` | 独立设计的ICB接口TB；`--contract-models`通过生产顶层执行两任务装载、计算、读/释放及中止 | 独立`verification/icb-*`、实际总线响应账本；发起者为TB，不是E203固件运行 |
| `run_example.py` | 生成可手算完整任务数据及共享容器 | `--output`指定目录；建议使用临时输出 `out/example/` |
| `check_dev12.py` | 只读重算显式指定的DEV12，逐项比较Y/flags | `--report`指定JSON；新运行使用新文件名，保留历史报告 |
| `evaluate_precision.py` | 当前冻结数值模型与真实浮点参考比较；`--mode cache`读取221条验证子集，`--mode full`从原始音频重新推理完整验证划分 | `--output`新的目录；按层汇总NRMSE、JSON/CSV/中文说明及源哈希；不改数值尺度或RTL |
| `verify_real12.py` | 12层真实数据的完整加速器ICB回归；连续换参数、逐位比Y/flags、从实际结果计算每任务NRMSE | `--output`新的验证目录；实际ICB账本、来源/源码快照、负向检错、官方SRAM功能复验上传包；本地后端为合同模型 |
| `measure_baseline.py` | 不含CPU/共享SRAM的正常ICB性能基线；无故意错误/随机延迟，分开总周期互斥分类与重叠的core观察量 | `--output`新的目录；每任务metrics.csv、实际结果账本、150MHz目标折算及官方SRAM功能复测包；不代表正式系统吞吐或STA |

真实精度评测示例（每次选择新的输出目录）：

```bash
python3 -B scripts/evaluate_precision.py --mode cache --output '/mnt/d/嵌赛芯片设计赛道/generated/validation/current-ffn1-next/subset'
/home/juhui/miniconda3/envs/kwt1/bin/python -B scripts/evaluate_precision.py --mode full --output '/mnt/d/嵌赛芯片设计赛道/generated/validation/current-ffn1-next/full'
```

full模式使用已安装的TensorFlow环境和个人旧项目的浮点提取器，只读原始模型/数据；整数运算仅调用当前`model/fixed_numeric.py`。其结果属于本地验证划分的软件数值精度，不能称为官方600条或新的RTL精度通过。具体身份、进展见[精度计划](../docs/implementation/20261102-real-data-precision-plan.md)。

```bash
cd '/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator'
python3 -B scripts/verify_mul_array.py
python3 -B scripts/verify_acc_context.py
python3 -B -m unittest discover -s tests -v
```

四个RTL脚本均显式选择DUT和TB，不扫描整个工程的 `.v`，避免将验证目录里的故意错误副本当成正式RTL编译。保留 `-B` 避免额外生成Python缓存。顶层运行命令为 `python3 -B scripts/verify_block_core.py`；加 `--synthetic-only` 仅调试定向及手算数据，默认额外读取本地冻结提取目录的12层真实输入。

验证后先读该运行目录的 `README.md`（已整理的运行）和 `report.json`，再按需要查看单项日志。历史失败运行与较早版本的用途见 [验证索引](../verification/README.md)。
