# 服务器文件与上传状态

**本文件下方为共享SRAM接入前的早期盘点，保留历史。当前目录、共享SRAM路径、测试状态及清理结果以[服务器目录与仓库对应表](server-folder-map-20261103.md)和[主交接](team-handoff-20261103.md)为准。** 原文中的“共享未接/真实CPU未完成”不能覆盖后来case3及512KiB通过记录。

更新：2026-11-03；依据既有上传/截图记录整理，未在本次远程列目录。这里的“已有”指截至最近一次记录，不保证队友之后没有移动文件。

## 路径对应

服务器账号home：`/storage1/2026contest/server2/s2_21usr`；工作区位于其`Desktop`。

| 内容 | 服务器Linux路径（以下以Desktop为根） | FileZilla右侧路径 |
|---|---|---|
| 已上传独立加速器 | `kwt1-accelerator/` | `/kwt1-accelerator/` |
| 活动E203集成副本 | `e203-integration/kwt-soc/` | `/e203-integration/kwt-soc/` |
| 保留的原始E203 | `e203-integration/e203_hbirdv2-master/` | `/e203-integration/e203_hbirdv2-master/` |

FileZilla的`/`映射到账号Desktop，不是Linux系统根目录；列表不更新时F5刷新。服务器csh/tcsh执行命令时使用本文的`&&`写法，不复制Bash专用重定向。

## 已上传、已生成或已有通过记录

以下`kwt-soc/`均指完整Linux路径`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/`。

| 文件/目录 | 来源及作用 | 已知状态 |
|---|---|---|
| Desktop/kwt1-accelerator/ | 普通命名独立加速器，含rtl、tb、脚本和报告 | 已上传；SRAM功能复测曾通过；不要假定包含后来新增的所有本地文档 |
| kwt-soc/中的加速器源码副本 | 供E203集成编译使用 | 已用于成功编译及CPU任务；修改前核对文件清单和哈希 |
| kwt-soc/prepare_kwt_soc.py | 本地接线生成工具 | 已上传并执行preview/apply |
| kwt-soc/wiring_01/ | 在服务器生成的before/after、diff与报告 | 记录原文件及接线变更，不是待综合顶层清单 |
| kwt-soc/rtl/e203/soc/kwt_soc_top.v | 在服务器生成的新SoC顶层 | 连接SysPer ICB与加速器；保留原soc_top |
| kwt-soc/verification/soc_compile_01/simv | 服务器VCS编译产物 | 原add、MMIO、合成计算任务用的仿真器；不能作为RTL源码交付 |
| kwt-soc/verification/soc_compile_01/add_run_01/ | 集成后原add测试 | TEST_PASS，25,804周期；不访问加速器 |
| kwt-soc/build-01/mmio_smoke.verilog | 本地mmio_smoke/build-01镜像，用户上传整个build-01 | TEST_PASS，x3=1；日志在soc_compile_01/mmio_run_01/run.log |
| kwt-soc/task_smoke.verilog | 本地task_smoke/task-build-01镜像 | TEST_PASS，x3=1；日志在soc_compile_01/task_run_02/run.log |
| kwt-soc/kwt-real12-validation.tar.gz | 完整真实12任务官方SRAM功能复测包 | 用户已上传并成功运行 |
| kwt-soc/real12_verify_01/kwt-real12-validation/official-run-01/ | 上一包解压后运行输出 | 截图PASS REAL12_OFFICIAL；report.json/编译与运行日志在此 |

`prepare_kwt_soc.py`不包含E203源码或加速器全部源码，它读取服务器已有文件并生成接线。因此此前只需传一个py是因为依赖已经在服务器，不表示最终交付只要py。

## 待上传/待跑，不能记成服务器已通过

`kwt-performance-baseline.tar.gz`已在本地生成；本次尚无用户确认上传或服务器运行结果。

- 本地：`verification/performance-baseline-20261102-01/kwt-performance-baseline.tar.gz`。
- 建议远端：`kwt-soc/kwt-performance-baseline.tar.gz`。
- 2,509,997字节，SHA256：`fd23a749d306e4bb007f10644a8d57f7b2df92edbc570aa91bab3fe363609242`。
- 功能包2,507,451字节，SHA256：`c59e99bab546013b19793894d32e7a54912660de5ace778c98d524e08337a0db`。
- GitHub交付的`server-packages/`保存这两个原包及其清单，不需要从历史目录重新拼装。

上传性能包后在服务器执行以下整段。若`perf_baseline_01`已存在，请使用新的编号，不删除或覆盖旧目录：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
sha256sum kwt-performance-baseline.tar.gz && \
mkdir perf_baseline_01 && \
tar -xzf kwt-performance-baseline.tar.gz -C perf_baseline_01 && \
cd perf_baseline_01/kwt-performance-baseline && \
python3 run_official.py
```

先核对上面SHA256；成功应出现`PASS PERF_BASELINE_OFFICIAL`，错误响应0。输出为新的`official-run-01/report.json`、`metrics.csv`、`performance.csv`与日志。该测试仍不包含真实CPU/共享RAM，不是正式系统吞吐量。

## 仅本地存在，尚未接入服务器活动SoC

`integration/e203/shared_ram_dev/`是512KiB共享RAM的独立开发组件，按用户决定暂不接入。GitHub保留其源码供后续参考，不代表它已在服务器综合或联调通过。本地完整精度评估数据、原始音频和模型权重同样没有证据表明已上传；不能因为本地算过就认为服务器也有。

## 服务器只读引用的赛方资料

```text
/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP1024X16/verilog/RAMSP1024X16_rtl.v
/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP1024X16/verilog/RAMSP1024X16.v
/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP128X16/verilog/RAMSP128X16_rtl.v
/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP128X16/verilog/RAMSP128X16.v
/storage1/admin_public_dir/SOC_RTL_2025/e203_hbirdv2-master_1013_update_sim.zip
```

这些资料不复制到GitHub。Verilog功能模型不等于综合时的工艺timing/area库；综合队友还需核对对应宏库、corner与单位。

## 可直接发队友的说明

请在新分支的独立交付目录读取工作总结和综合交接。独立加速器顶层kwt_accelerator，清单rtl/kwt.f，15个.v加4个.vh；内部8颗1024×16加16颗128×16，外接ICB。官方SRAM功能模型EMA2/EMAW0已通过真实12任务，E203合成计算任务已TEST_PASS；SRAM历史hold、150MHz STA、面积/功耗仍待核查。先综合独立加速器，后续另做完整SoC指标。不要将TB合同模型、临时共享RAM数组或整个verification目录加入综合。
