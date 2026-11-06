# ASIC 仿真、综合与功耗脚本（历史原文恢复）

本目录恢复此前实际给出的脚本代码，不是凭记忆重写。共22份：8份来自此前聊天的Python代码块，14份来自本地保存的原始脚本。逐文件SHA256、来源、聊天时间见 [provenance.json](provenance.json)。

**恢复日期：2026-11-06；未直接读取服务器，未核对服务器字节一致性。**
本地已做全部Python文件AST语法检查；没有重跑仿真、综合或功耗。现有结果不因归档恢复而重新获得验收。

## 当前流程入口
| 顺序/用途 | 原始脚本 | 前置条件 |
|---|---|---|
| ASIC加载与150MHz仿真准备 | [run_asic_suite12_150mhz.py](scripts/run_asic_suite12_150mhz.py) | 原生产test_env、ASIC适配与库；名字含suite12，但原文件说明为单任务准备，不能据文件名判断12任务已完成 |
| ASIC ROM握手修正及首任务 | [test_asic_rom_handshake.py](scripts/test_asic_rom_handshake.py) | 既有asic-suite12-150mhz运行；创建实验副本 |
| ROMFIX后继续12任务 | [continue_asic_rom_suite12.py](scripts/continue_asic_rom_suite12.py) | 固定的ROMFIX首任务运行和audit-report.json；含防重复执行检查 |
| 对应ROMFIX重新综合 | [synth_asic_romfix.py](scripts/synth_asic_romfix.py) | suite12-report.json通过；原候选elab/read.tcl、synth/compile.tcl及SDC |
| 首任务功耗 | [power_asic_romfix_task1.py](scripts/power_asic_romfix_task1.py) | ROMFIX网表、活动与既有功耗脚本 |
| SRAM实例映射 | [check_asic_memory_paths.py](scripts/check_asic_memory_paths.py) | 网表、波形和PrimeTime环境 |
| 生成152宏活动辅助程序 | [prepare_asic_sram_activity.py](scripts/prepare_asic_sram_activity.py) | annotate_measured_sram_q.py；生成annotate_asic_sram_q.py后运行它 |
| 12任务窗口功耗估算 | [power12_estimate.py](scripts/power12_estimate.py) | 既有12任务波形、网表、首任务功耗配置及生成的annotate_asic_sram_q.py |

这些脚本不是一条可从空目录顺序执行的流水线；部分是特定运行的继续/迁移脚本。读取前置条件后再使用，不要为“同步文件”而重新运行。最新估算记录见 [交接说明](../../START_HERE.md)。

## 配套生成与诊断脚本
- 源与TCM准备：prepare_soc_sources.py、prepare_soc_tcm.py、verify_asic_itcm_preload.py。
- 综合前序：read_soc_design.py、run_soc_synthesis.py、review_soc_clock_constraints.py、rebuild_soc_task_candidate.py。
- UART实验副本修正：test_uart_latch_fix.py。
- 前序活动/功耗准备：run_asic_activity_pilot.py、prepare_final_soc_power.py、run_power_150mhz_task01.py、annotate_measured_sram_q.py。
- 读活动诊断：check_dtcm_activity.py、check_all_sram_activity.py。

前序脚本可能选择旧候选或历史配置，它们是当前脚本的来源/依赖资料，不代表全部都应该重跑。

## 路径与运行环境
所有脚本保留原文。其目标根目录为：
`/storage1/2026contest/server2/s2_21usr/Desktop/dc`
生产根目录为：
`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`

服务器约定配套脚本位于dc/scripts；本目录scripts保持同名文件并列，以保留互相导入关系。仓库中的位置只是归档位置，不会自动覆盖服务器文件。既有run路径和源哈希检查均保留；改机器或路径前须另作移植，不应删除检查来强行运行。

## 仍缺什么
这些是原始生成/运行脚本，不能替代服务器实际生成的文件：
- 最新sources.f、compile-command.json、生成TB、ITCM预载include。
- 实验sirv_mrom_top.v与实际TCM/UART适配副本。
- 最新elab/read.tcl、synth/compile.tcl、constraints.sdc、input-sha256.json。
- 生产test_env迁移后的完整源快照，以及外部宏模型/库。

此前已交付的DMA源与加载环境仍在 [dma_accelerator](../e203/dma_accelerator/) 和 [dma_suite](../e203/dma_suite/)；不要把这些历史副本自动标为服务器最新配置。商业库、网表、波形未纳入此次恢复。

## 已与服务器截图哈希核对的生成文件

新增 [verified-adapters](verified-adapters/README.md)：ITCM、DTCM封装及TCM配置检查模块，三个文件SHA256均与服务器截图一致。其余上述缺失项仍待核对；已有脚本及原源码路径未修改。
