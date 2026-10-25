# 独立FFN1 V07加速器

本分支只保留本次实现的独立加速器及其验证、数值参考和综合入口。
计算为 `X[99,64] × W[64,256] + bias[256] → Y[99,256]`。
结构为PM4/PN4/CTX4、tile16、双槽权重，输出带索引和flags。

**综合顶层：`accelerator_top`。源码清单：[`synth/rtl.f`](synth/rtl.f)。**

2026-10-25更新：设计源码统一为Verilog-2005 `.v`，SRAM改为LVT型号
`TS1N28HPCPL2LVTB2048X32M4MWBASO`，默认工况为`tt0p9v25c`。
Synopsys综合加载对应的`TS1N28HPCPL2LVTB2048X32M4MWBASO_tt0p9v25c.db`，
并设置`USE_MACRO=1`；库文件由队友本机提供。

## 队友先看这里

- **综合：**[综合说明](synth/README.md)，列出文件、参数、宏、命令和正式综合所需条件。
- **接口：**[独立加速器说明](docs/shared/accelerator-v07-interface.md)。
- **计算核心：**[计算块接口](docs/shared/dot64-v07-interface.md)。
- **数值：**[数值规则](docs/shared/numeric-format-v0.1.md)。
- **来源与验证范围：**[独立版本说明](docs/shared/standalone-v07.md)。

## 目录

```text
rtl/          只含新版设计源码：顶层、控制、存储、计算、输出
synth/        RTL清单、Tcl读取变量、目标时钟和综合说明
tb/           加速器和计算核心自检
scripts/rtl/  向量生成、仿真和结构试综合脚本
scripts/model/ 软件整数数值参考
tests/        固定向量和软件模型测试
docs/         当前接口、数值约定和相关验证记录
```

## 快速验证

在WSL/Linux的仓库根目录运行，需要Python3、Bash及Icarus Verilog：

```bash
python3 -B scripts/rtl/check_v07_import.py
bash scripts/rtl/run_v07_tests.sh
bash scripts/rtl/run_accelerator_tests.sh
TEST_M=99 TEST_N=256 TEST_LAYERS=12 bash scripts/rtl/run_accelerator_tests.sh
```

各配置串行执行，生成结果放在忽略的`out/`。
SRAM商业库留在本机，通过环境变量指定，具体见综合说明。
旧工程保留在团队`main`、`v2`及Git历史，本分支没有CPU/总线/驱动适配。
当前功能测试和通用门级试综合不代表正式150MHz、面积或功耗验收。
