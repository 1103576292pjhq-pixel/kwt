# 综合入口

本分支当前树只有新版独立FFN1加速器。顶层固定为 `accelerator_top`，
设计源码全部由 `rtl.f` 列出；测试平台和Python文件不参与综合。
从仓库根目录运行命令，避免依赖当前目录造成找不到include。

## 文件与参数

- `synth/rtl.f`：唯一RTL文件清单，含12份源码及include目录。
- `synth/sources.tcl`：读取同一份清单，生成绝对路径Tcl变量，供DC/Genus等工具接入。
- `synth/clock.sdc`：150MHz目标时钟，仅为时钟约束起点。
- 默认正式尺寸：M=99、N=256、READ_LATENCY=1。
- 使用本地试验宏时：USE_MACRO=1；USE_MACRO=0是行为存储验证配置。
- 宏名：`TS1N28HPCPL2SVTB2048X32M4MWBASO`，预期12个实例。

Tcl入口不自动选择工艺库，也不自动执行任一厂商工具的工艺综合。
在工具中执行 `source synth/sources.tcl` 后，用
`ffn_v07_sources`、`ffn_v07_include_dirs`、`ffn_v07_defines`和
`ffn_v07_parameters`设置对应工具的读取、展开命令。
`.v`和`.sv`均可按SystemVerilog读取，宏头文件由include目录解析。

## 可直接运行的结构试综合

需要Yosys、Python3和已获授权的SRAM Liberty。库文件留在本机，路径由环境变量提供：

```bash
YOSYS=/path/to/yosys \
SRAM_LIB_DIR=/path/to/tsn28hpcpl2spsrammacros_180a \
  bash scripts/rtl/synth_accelerator.sh
```

`SRAM_LIB_DIR`下应包含：

```text
TS1N28HPCPL2SVTB2048X32M4MWBASO/
  TS1N28HPCPL2SVTB2048X32M4MWBASO_tt1v25c.lib
```

产物：`out/synthesis.log`、`out/accelerator_generic.v`、
`out/accelerator_generic.json`、`out/synthesis_summary.json`。
脚本检查结构、12个宏实例和无锁存器，不产生150MHz STA通过或工艺映射面积结论。
不要将商业宏的功能Verilog展开综合为普通逻辑；技术综合应从库解析宏单元。

## 正式工艺综合还需什么

队友需要提供目标标准单元库、SRAM宏库及一致PVT，按实际接口补充I/O延迟、
负载、时钟裕量等约束，并完成映射、STA及面积统计。
当前2048×32宏每颗仅使用低16位，总容量96KiB，是功能试验映射；
赛题指定16位宏的正式组合仍需落实，不能把这一版本写成正式宏准入通过。

`task_done`是独立接收端消费完结果后的通知；本次综合边界不含CPU、总线和驱动。
