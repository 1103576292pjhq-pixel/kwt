# KWT RevD/V2 本地候选

所选配置见 `PACKAGE.json`。这是本地工程候选，正式赛题门槛缺口见同文件；没有正式分数、指定工艺 STA、mm² 或功耗通过声明。

依赖：Linux/WSL、Python 3.12、NumPy 2.4.6、Icarus 12、Verilator 5.020；CPU 复现另需 GNU RISC-V GCC 13.2 / Binutils 2.42、g++、make。自行选择已安装的 Python，无本机绝对 venv 依赖。

```sh
python3 -B scripts/revd_offline_reproduce.py --suite manifest
python3 -B scripts/revd_offline_reproduce.py --suite smoke
python3 -B scripts/revd_offline_reproduce.py --suite numeric
python3 -B scripts/revd_offline_reproduce.py --suite full36
python3 -B scripts/revd_offline_reproduce.py --suite cpu-small
```

`smoke` 会新编译 L1/L2 RTL 并逐值核数据、flags、索引和末项。`numeric` 包含全部 48 shifts、边界、舍入与复位。`full36` 为 3×12 工程例，共 912384 唯一结果，并非正式 600 样本。`cpu-small` 运行真实 E203/C 驱动与冷切参；完整 CPU 运行入口为 `scripts/revd_offline_soc_run.py --stage full --tasks 2`。可用选定解释器直接执行上述 Python 文件。

冻结浮点参数按现有尺度转换：`python3 -B scripts/revd_offline_convert.py`，不重新拟合量化参数。`numeric/fixedpoint.py` 是位真数值模型。历史证据的命令绝对路径仅用于追溯；复现结果写入包内 `reports/revd_offline/` 的全新 run_id，拒绝覆盖。

提交前按 `PACKAGE.json` 中的资格与工艺缺口补齐官方平台、指定库/宏模型、150 MHz STA、面积/功耗、正式样本与所选性能任务。未生成的映射网表、SDC、功耗文件均未用占位物代替。通过后的同一配置与工况再提交；Git 提交和远程发布另行授权。

许可见 `THIRD_PARTY.md`、`vendor/keyword-transformer/LICENSE.txt` 和 `vendor/e203_hbirdv2-upstream/LICENSE`。

当前证据汇总见 [SUMMARY](SUMMARY.json) 与 [候选报告](reports/revd_offline/CANDIDATE_REPORT.md)。默认 full-W PM4 有12层CPU覆盖；W2有两层完整CPU冷任务与非零flags证据，是单列的可运行备选。W2入口为 `python3 -B scripts/revd_offline_soc_w2_run.py --stage small`，固定使用 Verilator 与两项冷任务，完整尺寸用 `--stage full`。W1/W2的重复协议历史仅收录范围摘要；其原始独立审查和源码入口保留，不声称所有历史绝对命令可直接移植执行。最终ZIP解压复现收据属于外部本轮SUMMARY/STATUS，避免把尚未生成的ZIP哈希写进其自身。
