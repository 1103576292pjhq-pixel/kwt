# KWT RevD｜外部评估核对与优化合并包

**打开顺序：先读 `docs/REVIEW_AUDIT.md`，再读 `PLAN.md`，实际开发复制 `AGENT_TASK.md`。**

本包以RevC为基础合并用户提供的评估。继续按本科FFN1独立核主线推进：4×4、CTX4、分块与双缓冲；新增两X存储体预取候选XP2、容量/端口/生存期核查、精度得分工具和长期算子复用路线。

这不是已经实现的新RTL仓库。总线、驱动、DMA、NICE、逻辑综合和正式SRAM宏映射仍在后续；不要求现在重写整个FP32编码器。已有FP32源码、C参考和CPU对照保留，未来本科硬件配置单独裁剪，不把“保留源码”混作“必须例化两套硬件”。

## 这次的关键合并

| 外部意见 | RevD处理 |
|---|---|
| SRAM、数据复用、算子复用需要提升 | 采纳，增加可计算的容量/端口账本和分阶段任务 |
| 两个16×4096可放99×64 INT16特征 | 容量成立；进一步提出CTX4下分两拍预取四行的XP2候选，不误判为完全不可行 |
| 必须立刻淘汰FP32、定点统一全部编码器 | 不直接执行；保留基线，未来逐步替换矩阵核/非线性，并单独验证精度 |
| 已经接通NICE、使用PyTorch、没有复用实验 | 与当前核对源码不符；详见审查表 |
| NRMSE≤3%、Top-1下降≤2%是满分 | 修正：是门槛；Top-1是2个百分点，满分要求误差/下降为零 |

## 解压后可直接执行

Python 3.10及以上；基本工具只依赖标准库。先在未修改文件时校核完整性。

```bash
python3 tools/verify_package.py
python3 tools/self_check.py
python3 tools/analyze.py
python3 tools/memory_review.py
python3 tools/precision_metrics.py
```

保存新结果使用不同的新目录；已有目录会拒绝覆盖：

```bash
python3 tools/self_check.py --out local_runs/check_01
python3 tools/memory_review.py --out local_runs/memory_01
python3 tools/precision_metrics.py --out local_runs/metrics_01
```

`tools/compare_v0.py`是继承的可选本地原数值模型对照，需要NumPy和你自己的原始仓库。它本次未执行：

```bash
python3 tools/compare_v0.py --source /absolute/path/to/kwt/numeric/fixedpoint.py --out local_runs/v0_01 --full
```

## 包内导航

- `PLAN.md`：本轮唯一有效的总执行方案。
- `docs/REVIEW_AUDIT.md`：逐项区分事实、采纳、修正及后续事项。
- `docs/MEMORY_PORTS.md`：两块SRAM例子、XP2预取与逻辑/宏/面积账本。
- `docs/REUSE_ROADMAP.md`：未来共享矩阵核、K=64/99/256、混合精度与FP32退役门槛。
- `docs/NUMERICAL_GATES.md`：门槛与评分、数据集纪律、误差/位真双验收。
- `docs/INTERFACE.md`、`docs/VERIFICATION.md`：继承的RevC契约及RevD补充。
- `docs/IMPLEMENTATION_TICKETS.md`：按模块分解的具体任务与通过条件。
- `configs/`：原七组核心对照及两个XP2补充配置；均为候选，不是已实现RTL。
- `tools/`、`tests/`：软件模型、检查器与36项测试；不会启动仿真器、修改GitHub或安装工艺库。
- `evidence/`、`reports/`：原包来源、审查摘要及本次真实软件检查日志。
- `index.html`：离线阅读入口；`figures/architecture.pdf`是两页矢量图备用。

## 已完成与未完成

本轮实际执行：原RevC包完整性检查、继承的整数/矩阵/协议模型测试、XP2预取规格模型、bank映射、评分公式及分段点积反例测试、图稿渲染与新包解压校核。

未执行：原V0文件运行、官方权重/600样本、新RTL、E203新版、NICE、综合/STA/宏映射/功耗。代码和JSON中的PASS都带适用范围，不等于正式比赛通过。

本包来源见 `SOURCE_LOCK.json`。历史 `docs/REVC_BASELINE.md`只供追溯；冲突时以本轮PLAN与AGENT_TASK为准。
