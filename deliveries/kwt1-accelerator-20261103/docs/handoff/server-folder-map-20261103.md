# 服务器目录与仓库对应表

更新：2026-11-03。本表以用户终端/文件管理器截图和已有运行凭据为准。服务器完整源码盘点JSON尚未取回；仓库不是整个服务器或完整E203平台的逐字镜像。

## 从哪里进入

服务器Desktop根：`/storage1/2026contest/server2/s2_21usr/Desktop`。FileZilla右侧`/`对应这个Desktop。

```text
Desktop/
├── kwt1-accelerator/                 独立加速器工程
└── e203-integration/
    ├── e203_hbirdv2-master/          集成前的E203参考工程
    └── kwt-soc/                     当前E203+加速器+512KiB共享SRAM工作工程
```

两份工程不会自动同步。队友做整SoC综合使用`kwt-soc`；做独立块综合使用`kwt1-accelerator`的`rtl/kwt.f`，也可在核对源码一致后复用SoC中的`accelerator/rtl`副本。

## kwt-soc逐项解释

| 服务器相对kwt-soc的路径 | 内容 | 综合/整理用途 |
|---|---|---|
| `rtl/` | E203核心、子系统、总线外设及生成的SoC顶层 | 完整SoC生产依赖；不按大小随意删除 |
| `rtl/e203/soc/kwt_shared_soc_top.v` | 当前生产SoC顶层，连接E203、加速器和共享SRAM | 整SoC顶层选`kwt_shared_soc_top` |
| `rtl/e203/soc/kwt_soc_top.v` | 较早只接加速器的顶层 | 历史对照；不是当前带共享SRAM的顶层 |
| `rtl/e203/mem_gen/` | 平台自带存储宏相关模型/库及物理资料，约228MiB | CPU存储及库依赖需综合队友核对；本轮保留 |
| `accelerator/rtl/` | 我们的15个加速器生产模块和4个头文件 | 对应本交付根`rtl/`，详见主交接模块表 |
| `shared_sram_bundle_01/kwt-shared-sram-v2/rtl/` | 我们拼好的512KiB共享SRAM三个生产模块及清单 | 当前活动源码，被共享filelist绝对路径引用，不能直接删/搬 |
| `tb/` | SoC仿真测试平台、ITCM程序加载和结果判断 | 仿真使用，不加入综合RTL |
| `build-01/`、`task_smoke.verilog` | 较早MMIO/合成任务的预编译CPU测试镜像 | 复现资料，不是RTL源文件 |
| `real12_verify_01/kwt-real12-validation/fixtures/` | case1..12的X/W/bias/整数黄金/浮点参考及manifest | 当前真实数据测试复用，保留 |
| `real_shared_case3_test_01/kwt-real-shared-case3-v2/` | 已通过的真实case3 CPU驱动、加载器和镜像 | 验证代码；测试加载mux不是生产综合模块 |
| `real_shared_suite_test_01/kwt-real-shared-suite/` | 12组不复位连续验证程序 | 用户要求停止；最后仅确认前三组完成、第4组加载 |
| `shared_task_test_01/` | CPU人工数据的共享SRAM完整任务验证 | 历史功能证据和可复现源 |
| `verification/` | `.f`输入、生成仿真top、日志、报告及运行数据 | 其中的生成测试top不综合；`.f`和证据保留 |
| `verification/soc_compile_01/soc.f` | 原SoC仿真源码清单 | 是仿真入口资料；不是已确认的ASIC综合清单 |
| `verification/shared_sram_wiring_01/shared_sram_additions.f` | 追加共享SRAM三个模块、生产顶层及官方宏模型的清单 | 活动依赖含绝对路径，改目录必须同步引用 |
| `wiring_01/` | 首次接线前后快照、diff和报告 | 保留修改来源，非综合入口 |
| `prepare_kwt_soc.py` | 生成/应用E203接加速器的接线工具 | 工具源，保留，不加入综合 |
| `cleanup_vcs_20261103.py` | 仅清理指定VCS生成物的工具 | 默认预览，已执行过一次清理；无需重复运行 |
| `cleanup-vcs-20261103.json` | 删除目标及保护文件哈希凭据 | 保留 |
| `soc-file-inventory-20261103.json` | 服务器生成的源/库/清单盘点 | 可直接在服务器读取，无需传到本机 |

当前测试生成顶层`kwt_real_soc_top`、`kwt_suite_soc_top`位于验证输出，包含TB加载协调；整SoC综合选择生产`kwt_shared_soc_top`。

## 仓库如何对应服务器

本分支交付根是`deliveries/kwt1-accelerator-20261103/`：

| 仓库交付根内路径 | 服务器位置/对应关系 |
|---|---|
| `rtl/` | 独立`kwt1-accelerator/rtl/`，以及集成副本`kwt-soc/accelerator/rtl/`的生产代码基线 |
| `integration/e203/shared_sram/rtl/` | `kwt-soc/shared_sram_bundle_01/kwt-shared-sram-v2/rtl/`的共享代码基线 |
| `server-layout/e203-integration/kwt-soc/accelerator/rtl/` | 为方便查找，按服务器同名路径另存加速器生产源码子集 |
| `server-layout/e203-integration/kwt-soc/shared_sram_bundle_01/kwt-shared-sram-v2/rtl/` | 按服务器同名路径另存共享SRAM生产源码子集 |
| `integration/e203/prepare_kwt_soc.py`、`shared_sram/prepare_shared_soc.py` | 生成服务器接线的工具；服务器实际E203/顶层仍取服务器工程 |
| `integration/e203/real_shared_task/` | case3工具的当前维护源；核心驱动/镜像沿用已通过版本，附加文档和测试可能多于服务器封存包 |
| `integration/e203/real_shared_suite/` | 已上传12组工具的维护源；全12服务器结果未取得 |
| `verification/*server*/receipt.json` | 对应服务器运行结果的截图转录，含原路径/范围；不是完整服务器日志下载件 |

`server-layout`是自有RTL的路径镜像子集，**没有伪造或搬入完整E203平台、生成顶层原文或商业工艺库**。综合队友在服务器使用已有完整`kwt-soc`。仓库中的同名源码副本不能与根目录另一套工程混用。

## 在服务器核对版本

在仓库交付根执行（只读，不会复制或覆盖服务器代码）：

```sh
python3 tools/check_server_sources.py --soc-root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

工具核对我们新增的19份加速器RTL/头和3份共享RTL的SHA256；不把仅检查E203/库路径存在说成逐文件内容核验。独立加速器副本如需一起核对，可追加`--standalone-root /storage1/2026contest/server2/s2_21usr/Desktop/kwt1-accelerator`。对应关系和预期哈希保存在`server-source-map.json`。

VCS清理已删除五个运行目录中的csrc、simv.daidir和simv，共15项226.10MiB，954个保护文件哈希保持；以后重跑要重新编译。五个重复上传tar.gz和Python pyc仅建议删除，尚无删除完成截图，均不作为当前运行依赖。不要把解压后的共享源码目录与可删除压缩包混为一谈。
