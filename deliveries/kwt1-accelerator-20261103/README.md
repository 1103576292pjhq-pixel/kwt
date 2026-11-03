# KWT1 本科FFN1：加速器、共享SRAM与SoC交接

更新：2026-11-03。本目录继续上次交付，仍位于同一handoff/ffn1-accelerator分支、同一deliveries/kwt1-accelerator-20261103目录。仓库根目录另一套工程保留。原15个加速器RTL和4个头文件未改变；本轮主要新增64宏512KiB共享SRAM、CPU真实数据链路及服务器对照说明。

队友按下面顺序看：

1. [当前工作总结、15个模块职责、数值与已有结果](docs/handoff/team-handoff-20261103.md)
2. [服务器每个文件夹是什么、仓库路径如何对应](docs/handoff/server-folder-map-20261103.md)
3. [新增共享SRAM三个模块、拼接原理及E203连接](docs/handoff/shared-sram-and-soc-20261103.md)
4. [独立块/整SoC综合入口、库/约束和报告要求](docs/handoff/synthesis-handoff-20261103.md)
5. [当前ICB寄存器与驱动协议](docs/rtl/accelerator/icb-interface.md)

| 综合对象 | 生产顶层 | 从哪里取源码 |
|---|---|---|
| 独立加速器 | kwt_accelerator | 本交付rtl/kwt.f；服务器Desktop/kwt1-accelerator |
| 完整SoC | kwt_shared_soc_top | 服务器Desktop/e203-integration/kwt-soc，含E203、accelerator/rtl及活动共享SRAM目录 |

可以交给队友开始两种综合。队友按平台配置源清单、标准单元/SRAM库和SDC，实际是否通过及150MHz/面积结论以工具报告为准。测试生成top kwt_real_soc_top、kwt_suite_soc_top含加载mux，不作为生产综合顶层。

已通过：共享64宏全容量/ICB、E203共享访存、真实case3完整计算和25344项共享写回/回读（差异0，NRMSE0.01737469%）。本轮CPU连续12组用户要求停止，最后仅确认前三组完成、第4组加载；不能记全12通过。较早TB驱动加速器12组通过另有独立证据。正式完整计时、指定库STA/面积/功耗和官方600/12仍待各自结果，计时草稿未发布为完成工具。

在交付根先核对文件完整性：

```sh
python3 -B tools/verify_delivery.py
```

仓库放在服务器可访问的位置后，可直接只读核对自有RTL，无需下载服务器盘点JSON：

```sh
python3 tools/check_server_sources.py --soc-root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

server-layout按服务器目录名称保存22份自有RTL子集；不是完整E203平台镜像，商业库不在仓库。server-source-map.json记录预期对应和哈希；未运行服务器核对前不声称全部服务器文件逐字一致。

VCS生成物已清理15项226.10MiB，954保护文件哈希保持，源码/日志/数据保留；旧仿真需重新编译。服务器共享SRAM仍位于shared_sram_bundle_01/kwt-shared-sram-v2/rtl，文件清单含绝对引用，未擅自搬动。

早期交接在docs/handoff/history/20261103-before-shared-sram保存；历史报告按自身版本/范围解释。最早草稿里的PAIR、FIFO8或48位兼容容器不用于当前生产接口。
