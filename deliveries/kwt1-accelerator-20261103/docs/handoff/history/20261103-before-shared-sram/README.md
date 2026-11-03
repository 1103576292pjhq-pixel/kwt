# KWT1 本科FFN1加速器独立交付（2026-11-03）

本目录是独立工程快照，仅对应本科任务1–3。仓库根目录原有工程保留；两套接口、驱动和验证证据分开使用。

1. [已完成工作、模块、指标与未完成事项](docs/handoff/team-handoff-20261103.md)
2. [服务器上传清单、路径与复测命令](docs/handoff/server-inventory-20261103.md)
3. [给综合队友的输入与报告要求](docs/handoff/synthesis-handoff-20261103.md)
4. [当前ICB接口](docs/rtl/accelerator/icb-interface.md)
5. [交付范围与复现说明](DELIVERY.md)

生产顶层`kwt_accelerator`；综合清单[rtl/kwt.f](rtl/kwt.f)。先核对交付完整性：

```sh
python3 -B tools/verify_delivery.py
```

代表性真实12任务304128项Y/flags一致，服务器官方SRAM功能模型已有通过截图；完整原验证划分最差层NRMSE0.0211091260%。本地TB性能平均369614.75周期/任务，按150MHz目标折算405.827960任务/秒，**不是正式系统性能或STA通过**。

待完成实际E203真实数据、共享SRAM加载与写回、完整计时、SRAM历史hold核查、综合/STA/面积/功耗及官方600/12任务验收。性能包服务器复测仍待运行。

历史文档/报告保留各自日期、原始路径和状态；当前结论以本页前三份交接文件与各自证据范围为准。尤其早期架构文档中的FIFO8、PAIR和48位兼容容器不用于当前生产接口。
