# FFN1 DMA版交接（2026-11-04）

**当前唯一服务器工程：** `/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`。
当前RTL为 `accelerator/rtl/`，生产SoC顶层为 `rtl/e203/soc/kwt_dma_soc_top.v`，测试入口为 `accelerator/run_suite.py`。
正式迁移已完成，迁移后3任务均通过（每项554144周期）；不要重复执行迁移脚本。
先读[当前状态](docs/handoff/current-team-status.md)及[当前综合交接](docs/handoff/synthesis-handoff-current.md)。
本地根 `rtl/` 和旧 `server-layout` 为历史实现；DMA维护源码在 `integration/e203/`，不是服务器完整镜像。
12任务共6649728周期，150MHz归一化270.687763 task/s；STA、面积、功耗尚无通过报告。
服务器结果仍为截图转录，原始报告及详细访存计数待取回。


队友先读[当前工作、模块、服务器路径与指标](docs/handoff/current-team-status.md)。

12任务服务器验证已通过：每项554144周期，总6649728周期，304128输出逐位一致，最大NRMSE 0.02214978%。
按目标150MHz换算270.687763 task/s，平均3.694293ms；尚无STA/面积/功耗结论。
证据是[服务器截图转录](verification/e203-dma-suite12-server-20261104-01/receipt.json)，不是已下载原始报告。

- [DMA架构、模块、CSR和注意事项](integration/e203/dma_accelerator/README.md)
- [12任务加载、清空、计时、访存与活动导出](integration/e203/dma_suite/README.md)
- [服务器可直接解压的12任务包](server-packages/kwt-dma-suite12.tar.gz)
- [我们做过什么](docs/handoff/server-work-log.md)
- [共享SRAM拼接及旧平台路径](docs/handoff/shared-sram-and-soc-20261103.md)

原根rtl/和旧server-layout仍保留历史CPU搬运版本，没有覆盖为DMA。
DMA源码位于integration/e203/dma_suite/rtl；新固件、程序镜像和环境在同一目录。
服务器当前正式入口为 accelerator/；原 dma_suite_test_01/kwt-dma-suite 已移出工程。12任务结果仍在 verification/dma_suite12_01。
生产SoC顶层由prepare_soc.py生成，完整E203平台和官方SRAM/工艺库仍在服务器，未转载到此交付。
仿真清单不能直接作为ASIC综合配置；队友需选对新版并配置库/SDC。

任务数据采用现有验证集，非组委会冻结后抽样；12次冷启动之间复位，非无复位连续运行。
内部缓存是有效状态复位，未物理逐地址清零。VCD还需映射、覆盖检查及SRAM功耗建模。
旧交接入口保存在docs/handoff/history/20261103-before-dma，按版本理解历史报告。
