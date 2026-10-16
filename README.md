# KWT-1：E203 神经网络加速器工程

本工程将 Keyword Transformer 的 KWT-1 计算映射到可综合 RTL，并通过公开 E203 RISC-V 处理器完成控制、参数搬运和结果写回。它包含本科必做的整数 FFN1 加速器，以及扩展的 FP32 单头注意力、PostNorm 编码器和完整十二层调度，适合沿着“数值模型 → RTL → 总线 → 固件 → SoC 验证”学习 AI 芯片实现。

**当前状态：七项任务已有对应的本地实现与证据，硬件初稿及技术报告批次已获本地接受；正式赛题验收仍有外部待验项。** 本仓库保留已接受的历史源码、输入、输出和审查记录。复制到新路径不代表已在新路径重新完成硬件验收。

## 从哪里开始

- 了解赛题与完成边界：[赛题要求与验收对应表](docs/encoder/reports/00_赛题要求与验收对应表.md)。
- 学习设计与代码：[七项技术报告导航](docs/encoder/reports/README.md)，建议按 01 → 02 → 03 学习本科主线，再按 04 → 05 → 06 阅读扩展。
- 核对现有结论：[总体验收报告](docs/encoder/reports/08_总体验收报告.md)、[技术报告批次最终验收记录](reports/system/report-cycle/root-verification-report.md)。
- 开始动手：[复现与学习指南](docs/encoder/reports/09_复现与学习指南.md)，新仓库路径与命令以本 README 为准。
- 核对本次整理范围：[本地仓库交付说明](docs/repository-delivery.md)、[第三方来源与许可](THIRD_PARTY.md)。

## 架构与数据流

硬件边界从完整的 `99×64` 编码器输入开始。音频处理、MFCC、输入投影、CLS 与位置编码在主机侧离线完成；末层 CLS 的统一分类头也由主机执行。生产 E203 固件只执行搬运与控制，神经网络算术在 RTL 中完成，主机 C 参考只用于验证。

```text
离线音频与官方模型 → 固定输入 / 每层参数
                         ↓
                512 KiB 共享 SRAM
                         ↕
              E203 + 生产 C 驱动
                         ↕ ICB / MMIO
         ┌───────────────┴────────────────┐
         │                               │
  整数 FFN1 加速器                FP32 编码器加速器
  99×64 · 64×256 + b             Q/K/V → 注意力 → 输出投影
         ↓                               ↓
  全部 25344 个输出              残差 → LN1 → FFN1 → GELU
                                         ↓
                                FFN2 → 残差 → LN2
                                         ↓
                         每层 6336 word，顺序执行十二层
                                         ↓
                           末层完整输出 → 主机分类头
```

整数 FFN1 使用冻结的定点数值契约；完整编码器使用逐操作 IEEE binary32 与独立 C 参考。点积从 `+0` 开始按 `k` 递增执行 FMA，最后单独加偏置。当前 GELU 为 tanh 近似，官方模型为 erf GELU，因此“RTL 对本设计参考逐位一致”与“相对官方模型精度达标”分别核对。

完整编码器每层使用 `49792` 个 FP32 参数 word，即 `199168 B`，逐层供参并复用共享窗口。层间可由 CPU 读回并重装，或在加速器内部交换 X/Y 银行。接口、状态机命令与 SRAM 布局见[外部契约](docs/encoder/interface.md)；数值顺序与权重布局见[C 位真参考说明](numeric/encoder/README.md)。

## 七项任务的本地状态

本科必做为第 1—3 项；第 4—7 项为本工程扩展。下表的“本地”仅指已冻结运行及独立回读覆盖的范围。

| 任务与报告 | 当前本地完成范围 | 正式验收边界 |
|---|---|---|
| [1 乘累加与数值处理模块](docs/encoder/reports/01_乘累加与数值处理模块.md) | 64 项点积、偏置、转换；整数边界、复位和连续任务；FP32 基元及冷启动验证 | 正式向量与提交数值模型仍须按比赛条件核对 |
| [2 前馈线性加速器](docs/encoder/reports/02_前馈线性加速器.md) | `99×64 · 64×256+b`；36 个完整工程案例、独立重复及 12 套参数切换 | 工程案例不替代正式 600 样本或 12 个性能任务 |
| [3 前馈线性加速器 SoC 集成与综合](docs/encoder/reports/03_前馈线性加速器SoC集成与综合.md) | 真实 E203 生产驱动、全部输出及 flags；generic 结构综合 | 组委会平台、指定库/宏、正式综合与 PPA 待验 |
| [4 单头注意力模块](docs/encoder/reports/04_单头注意力模块.md) | 独立 ATTENTION 模式、完整 6336 word 公开读回及阶段对照 | 正式平台与评测输入复核 |
| [5 单层编码器](docs/encoder/reports/05_单层编码器.md) | 全 99 token 的 PostNorm、两残差、两 LN、FFN/GELU；阶段和输出位真 | 官方模型近似误差与正式精度要求单列 |
| [6 十二层编码器与参数调度](docs/encoder/reports/06_十二层编码器与参数调度.md) | 15 个输入的完整十二层 RTL、独立重复；同一输入双策略真实 E203 与供参/激活复用 | 正式 600 样本分类和 12 个整机性能任务待验 |
| [7 编码器加速器综合与性能分析](docs/encoder/reports/07_编码器加速器综合与性能分析.md) | generic 核心/SoC 层级与同步 RAM；实际周期、逻辑访问和参数开销 | 指定库映射、综合后功能、时序/面积/功耗/能耗待验 |

关键证据入口包括[硬件总报告](reports/encoder/verification/report.md)、[硬件本地接受记录](reports/system/root-formal-acceptance.json)、[报告批次接受记录](reports/system/report-cycle/root-acceptance.json)和[双 CPU 独立回读](reports/system/review/encoder-final-cpu-readback.md)。历史动态状态保存在[编码器状态](work/encoder_status.json)及[报告批次状态](work/report_cycle_status.json)，阅读时应与其接受记录对应。

完整编码器 RTL 的 15 个输入共核对 `1140480` 个输出 word，独立重复另核 `76032` 个；均与本设计 C 参考逐 word 一致且有限。真实 E203 两策略均完整执行十二层：内部交换策略只由 CPU 写回最后 `6336` word，外部重载策略由 CPU 写回全部 `76032` word；两者的被动神经监视器分别核对全部 `76032` word。监视器输出与 CPU 实际写回分别计数。

已接受的复用对照只覆盖同一输入、两策略各一次完整十二层：

| 指标 | 内部交换 | 外部重载 | 相对外部重载节省 |
|---|---:|---:|---:|
| 端到端周期 | 284353480 | 290627429 | 2.158760% |
| CPU 侧共享 SRAM 事务 | 660034 | 799426 | 17.436511% |
| 含供参 host 的逻辑共享事务 | 1257562 | 1396954 | 9.978281% |

该计时从首个 MMIO 到末结果写回，初始 host fixture 预载在窗外；访问量是逻辑事务，不能换算成物理 SRAM 能耗。工程输入中的“与官方预测相同”也不能解释为全部标签正确或正式分类精度通过。详细分母、输入身份和限制见[性能数据](reports/encoder/verification/performance.json)。

## 目录说明

| 目录 | 内容与用途 |
|---|---|
| [`rtl/`](rtl/) | 点积、整数 FFN1、FP32 运算、非线性、编码器核心、同步 RAM 与 ICB 接口 |
| [`numeric/`](numeric/) | 整数数值模型、编码器独立 C 参考、向量与位模式校验 |
| [`soc/`](soc/) / [`sw/`](sw/) | E203 集成、共享 SRAM、启动代码、链接脚本和生产驱动 |
| [`dv/`](dv/) / [`tests/`](tests/) | RTL testbench、仿真/综合入口、CPU 系统验证、单元测试与验收门测试 |
| [`scripts/`](scripts/) | 环境、模型导出、仿真、综合、历史门禁与仓库完整性入口 |
| [`model/`](model/) / [`config/`](config/) | 官方模型导出/诊断、模型与数值契约、依赖锁及上游指纹 |
| [`docs/`](docs/) | 七项技术报告、需求对照、接口和学习说明 |
| [`vendor/`](vendor/) | 固定上游源码及原始许可，包括 Keyword Transformer、E203、HardFloat 和 SDK |
| [`data/`](data/) | 工程样本、来源清单及模型/输入相关数据 |
| [`reports/`](reports/) | 冻结参考、仿真输出、日志、generic 综合、独立回读与接受证据 |
| [`work/`](work/) | 与证据闭包配套的冻结源清单、数值/接口交接和历史状态文件 |

虚拟环境、下载工具运行时和缓存需在使用机器上重建。为兼容 Windows Git，四个 E203 Linux 符号链接不直接纳入 Git，而由已提交的固定来源清单完整描述；Linux 准备命令会恢复它们。其余交付文件纳入版本管理，上游 `.gitignore` 保持原样。详见[仓库交付说明](docs/repository-delivery.md)。

## 快速开始：先验证交付，再运行小案例

### 1. 进入仓库并只读核对

以下 Bash 命令从仓库根目录运行。以 Windows D 盘的本地仓库为例：

```bash
cd /mnt/d/github/kwt
python3 scripts/prepare_repository.py
python3 scripts/verify_repository.py
```

两条命令都只使用 Python 标准库。准备命令按固定清单补齐四个链接，不下载文件、不覆盖已有普通文件；重复执行不会改变正确链接。校验器随后只读检查文件哈希、符号链接和报告链接。它核对交付完整性，不启动 RTL 仿真，也不重新授予硬件或比赛验收通过。应在开始产生新结果前先执行。

### 2. 准备 Linux 验证环境

历史验证使用 WSL2 Ubuntu 24.04、Python 3.12.3、Icarus 12.0、Verilator 5.020 和 Yosys 0.33；记录见[环境说明](reports/environment/DV_ENVIRONMENT.md)。下面建立本机隔离环境；APT 具体版本由本机发行版决定，不能仅凭安装成功宣称复现了历史工具版本。

```bash
sudo apt-get update
sudo apt-get install -y --no-install-recommends \
  python3 python3-venv build-essential iverilog verilator gtkwave yosys \
  gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
python3 -m venv --copies .venv-dv
.venv-dv/bin/python -m pip install -r config/requirements-dv.txt
.venv-dv/bin/python -m pip check
```

独立 RTL 小案例使用 Icarus/Verilator 和现有冻结参考，不需要 TensorFlow。RISC-V 工具链用于后面的真实 E203 固件任务，Yosys 用于 generic 综合。先查看实际入口参数：

```bash
bash scripts/run_encoder.sh --help
bash scripts/run_e203_encoder.sh --help
```

### 3. 用两个模拟器运行小案例

每次使用新的输出目录，保留历史接受证据：

```bash
bash scripts/run_encoder.sh --mode small --case small_3_4_8 \
  --sim icarus --trace --output reports/encoder/reproduction/small-icarus
bash scripts/run_encoder.sh --mode small --case small_3_4_8 \
  --sim verilator --trace --output reports/encoder/reproduction/small-verilator
```

小案例为 3 token、4 维、FFN 隐藏维 8，一层输出 `3×4=12 word`。其 attention 缩放按冻结硬件契约固定为 `0.125`。查看新目录中的 `status.json`、编译/运行日志、公开输出与 trace：成功需要实际退出码为 0、完整输出比较通过及本次来源绑定；旧 PASS 或 `--help` 退出 0 不代表仿真通过。

## 完整复现与历史证据的区别

原技术报告、manifest、源哈希与命令记录保留其历史内容，其中可能包含原机器绝对路径。保留这些路径是为了追溯原运行；无需把历史记录改写成当前目录。尤其是原统一门禁会核对历史命令和绝对路径，不能假定迁到 D 盘后 `--gate-only` 可原样通过。

仓库完整性校验、在新目录进行单项复现、重新形成一套硬件接受证据，是三个不同动作。本次本地整理没有执行新一轮长硬件验收。以下入口可在依赖与冻结源匹配后按需执行；完整十二层与真实 CPU 任务耗时明显高于小案例：

```bash
# 独立完整 attention：公开读回 6336 word
bash scripts/run_encoder.sh --mode layer --attention --trace \
  --output reports/encoder/reproduction/attention-full

# 单个输入的完整十二层：逐层输出共 76032 word
bash scripts/run_encoder.sh --mode full --trace \
  --output reports/encoder/reproduction/full12

# 真实 E203：策略 1 内部交换；策略 2 CPU 读回重载
bash scripts/run_e203_encoder.sh --policy 1 \
  --output reports/encoder/reproduction/e203-pingpong
bash scripts/run_e203_encoder.sh --policy 2 \
  --output reports/encoder/reproduction/e203-reload
```

这些入口要求 `--output` 位于 `reports/encoder/` 内。需要再次重复实验时换一个新目录，不复用以上示例目录。新增输出不会改变已接受历史的含义；修改冻结源码、固件或依赖后，必须重新验证受影响链路。

以下入口会写固定报告、状态或配置，建议在保留原交付的工作副本中使用，并先读脚本：

| 目的 | 实际入口与注意点 |
|---|---|
| 环境安装/计数器 smoke | `scripts/setup_dv.sh`、`scripts/run_smoke.sh`；会写 `reports/environment/`，快速开始采用手动建环境以保留冻结报告 |
| 官方 TensorFlow 模型环境 | `scripts/setup_model.sh`；独立 Python 3.8.20 / TensorFlow 2.4.0 环境，与 DV 环境分离，并写模型环境配置 |
| 官方模型导出/独立 C 参考重建 | `scripts/export_encoder.sh`、`scripts/run_encoder_reference.sh`；即使另指定输出，参考脚本仍会写固定测试日志；详见[数值参考说明](numeric/encoder/README.md) |
| generic 综合 | `scripts/run_ffn1_synth.sh`、`scripts/run_encoder_synth.sh`、`dv/encoder/run_soc_synth.py`；输出位置固定，结果只证明本地结构综合 |
| 原统一硬件回归 | `scripts/run_formal_seven.sh`；`--reuse-verified` 会核历史，失配时可能重跑昂贵任务；`--gate-only` 仍是历史硬件门，不能用仓库迁移校验代替 |

如果出现失败，先读本次编译日志或第一个输出差异，核输入、权重、操作顺序、IEEE flags 与设备 fault。不要重写历史 SHA 或忽略缺失结果来恢复 PASS。门禁问题与计算结果问题分别定位，具体检查顺序见[复现指南](docs/encoder/reports/09_复现与学习指南.md)。

## 正式待验项

后续仍需在同一冻结设计与规定条件下完成：

1. 组委会 E203 平台、总线/外设/复位适配及指定 `16bit×128/1024/4096` SRAM 宏组合。
2. 指定工艺/标准单元库、有效 SDC、映射网表、综合后功能与 `150 MHz` 时序及裕量。
3. 新增加速器、接口与内部 SRAM 宏面积 `≤2.25 mm²`，以及规定活动窗口的整 SoC 功耗和单任务能耗。
4. 正式 600 样本精度与冻结后统一抽取的 12 个性能任务。

当前 generic 综合不能证明最终频率、面积或功耗；仿真时钟与逻辑访问次数也不能替代这些指标。赛题不要求布局布线、物理验证或流片。正式边界与交付要求以[需求对照表](docs/encoder/reports/00_赛题要求与验收对应表.md)为入口。

## 来源与许可

官方模型固定上游提交见[模型来源指纹](config/upstream-commit.json)，其余上游绑定见 [`config/`](config/) 中的来源清单。保留的主要原始许可如下，各子组件与文件自身声明仍适用：

- Keyword Transformer：[Apache-2.0](vendor/keyword-transformer/LICENSE.txt)。
- E203/Hummingbird：[Apache-2.0](vendor/e203_hbirdv2-upstream/LICENSE)。
- Hummingbird SDK：[主许可](vendor/hbird-sdk-upstream/LICENSE)，其内第三方组件另见各自许可。
- Berkeley HardFloat Release 1：[三条款 BSD 许可](vendor/HardFloat-1-upstream/COPYING.txt)。

本仓库尚未为自主编写部分统一授予开源许可证；上游许可证不会自动覆盖全部工程。模型权重、音频样本及赛题材料按各自来源条件使用，正式发布或再分发前应分别核对。
