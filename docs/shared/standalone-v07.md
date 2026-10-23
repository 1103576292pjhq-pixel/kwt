# 独立 FFN1 V07：团队分支入口

本分支以团队 `v2` 的 `7a029a5` 为基础，导入个人工程
`mywayjpo/kwt1-accelerator-2026` 中 `worktrees/ffn-v07-peripheral`
的未提交工作树快照。逐文件 SHA-256 见 `standalone-v07-import.json`。
导入没有修改计算或外围 RTL。该快照是独立加速器，不包含新的 CPU、ICB、寄存器或驱动适配。

## 目录与模块

| 入口 | 职责 |
| --- | --- |
| `rtl/accelerator_top.sv` | 命令流输入、带索引和 flags 的结果流输出 |
| `rtl/control/` | 命令合法性、双槽所有权、矩阵供数调度 |
| `rtl/memory/` | X 四 bank、W 双槽及偏置、同步 SRAM 封装 |
| `rtl/compute/` | 4×4 乘法阵列、CTX4 累加、数值转换、块控制 |
| `rtl/output/result_ctrl.sv` | 选读、偏置配对、索引、结果消费及块释放 |
| `tb/accelerator/`、`tb/dot64/` | 外围及计算核心自检 |
| `scripts/rtl/` | 向量生成、功能仿真、参考交叉检查及试综合 |
| `scripts/model/fixed_point.py` | RTL 对应的软件整数数值模型 |

完整接口见 [加速器规格](accelerator-v07-interface.md)、
[计算块接口](dot64-v07-interface.md)和[数值规则](numeric-format-v0.1.md)。

## 数值与原工程的区别

X signed16/Q12，W signed16/Q16，bias 逻辑 signed32/Q28；逻辑累加
signed40/Q28，以 signed48 物理容器实现。固定 RNE 右移16位、sat16，
再将结果符号扩展到 signed32。flags 是 overflow、saturated、last 三位。

团队旧V07的可变 shift、signed48 bias 和 sat32 数值契约不能用来驱动本入口。
旧工程仍可从团队 `main`、`v2` 或Git历史查看，本分支当前文件树只保留新版。
未来接入须显式适配并重新验证，不能仅重命名替换。
使用本分支下列脚本运行新入口，不沿用旧 runner 的冻结 golden 或层级探针。

几何默认99×64×256，PM4/PN4/CTX4、tile16、双权重槽。外围一次一个
读请求在途，1/2拍存储返回时供数间隔约3/4拍，没有每拍供数的性能声明。
输出握手代表独立接收端已消费，不代表未来 SoC 共享 SRAM 已写回。

## 功能验证

在 WSL/Linux 中，从本分支仓库根目录运行。Python3 标准库、Icarus
Verilog 和 Bash 足以执行两个 RTL 入口，无需 TensorFlow、模型权重或音频。

```bash
python3 -B scripts/rtl/check_v07_import.py
bash scripts/rtl/run_v07_tests.sh
bash scripts/rtl/run_accelerator_tests.sh
TEST_LATENCY=2 bash scripts/rtl/run_accelerator_tests.sh
TEST_M=99 TEST_N=256 TEST_LAYERS=12 bash scripts/rtl/run_accelerator_tests.sh
```

不同配置串行执行：脚本共享并覆盖 `out/` 下相同向量与可执行文件。
完整尺寸为固定种子合成整数任务，12层共304128项Y/flags/index；不是
12套真实模型参数、官方性能或精度验收。

以下交叉检查另外需要 NumPy；先运行完整尺寸脚本以生成相应向量：

```bash
python3 -B scripts/rtl/check_accelerator_vectors.py
python3 -B -m unittest discover -s tests/model -p 'test_fixed_point.py' -v
```

可以给交叉检查脚本提供 `--teammate-oracle /path/to/reference/fixed_numeric.py`，
进一步比较队友 oracle 的Y和flags。原导入测试记录见
[20261023局部记录](../reports/20261023-v07-accelerator/README.md)；
本次团队目录复跑范围在提交说明中单独列出。

## SRAM 与试综合

商业模型、Liberty、工具二进制和大规模生成结果不入库。行为 RAM 是默认入口。
使用已获授权的本地宏时，设置模型目录：

```bash
SRAM_MODEL_DIR=/path/to/tsn28hpcpl2spsrammacros_180a \
  TEST_MACRO=1 bash scripts/rtl/run_accelerator_tests.sh
```

目录下应包含
`TS1N28HPCPL2SVTB2048X32M4MWBASO/TS1N28HPCPL2SVTB2048X32M4MWBASO_tt1v25c.v`。
这是12颗2048×32宏的试验映射，每颗仅使用低16位，共96KiB实例容量；
不是赛题指定16位宏的正式映射。UNIT_DELAY功能仿真会报告零时刻的
CEB唤醒警告，不能当作上电/睡眠或工艺时序验收。

`scripts/rtl/synth_accelerator.sh` 可通过 `SRAM_LIB_DIR` 和 `YOSYS` 指定
本机路径；仅检查通用逻辑、宏数量和锁存器。没有150MHz STA、正式面积
和功耗结论。生成产物位于已忽略的 `out/`。

外部依赖及个人工作区仍保留原位置。以后继续开发时，明确当前入口和
数值契约，避免将本次分支误认作旧 SoC 的兼容替换。
