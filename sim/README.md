# 仿真与参数加载导航

## 2026-11-09 当前服务器入口更新

先读 [服务器目录、当前仿真入口与限制](../docs/server-layout-20261109/README.md)。本次同步四份服务器已确认更新的说明文档；没有修改设计 RTL、E203 或工艺库，也没有同步完整服务器环境。下方原交付路径保留用于历史源码导航，旧运行命令不能直接套用于整理后的服务器。


这是分类导航目录，实际文件仍在原位置，以保持脚本相对路径和已有清单有效。不要把本目录作为编译或运行工作目录。

- [12任务环境说明](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/README.md)
- [run_suite.py](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/run_suite.py)：已有12任务入口。
- [real_loader.v](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/real_loader.v)：参数和输入加载。
- [suite_metrics.v](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/suite_metrics.v)：被动测量。
- [timing_tools.py](../deliveries/kwt1-accelerator-20261103/integration/e203/dma_suite/timing_tools.py)：计时处理。
- [12任务验证资料](../deliveries/kwt1-accelerator-20261103/integration/e203/real12_validation/)

按原README及原目录执行；不从本导航目录启动程序。服务器外部模型、输入数据及顶层必须配套，现有包不意味着含全部服务器依赖。12次独立FFN1任务不是完整12层网络。

## 已恢复的ASIC原始脚本

[ASIC仿真、综合与功耗脚本](../deliveries/kwt1-accelerator-20261103/integration/asic_flow/README.md)：22份，来源为此前聊天代码块及本地保存文件，已做语法检查。服务器生成的RTL、TB、清单及Tcl文件仍未完整取回；该目录是原始脚本归档，不是完整服务器镜像。

## 2026-11-07 已核对快照

[9个参数加载、计时、运行及驱动文件](../deliveries/kwt1-accelerator-20261103/integration/asic_flow/verified-testenv/README.md)已通过服务器截图摘要核对（统一LF换行）。平台连接封装和ASIC TB尚未补齐，快照不作为独立运行入口。未增加E203源码。
