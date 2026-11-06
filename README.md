# FFN1 DMA 加速器工程

## 按用途查找

| 入口 | 内容 |
|---|---|
| [RTL](rtl/README.md) | DMA、计算核心、接口及共享SRAM |
| [CPU固件](firmware/README.md) | 驱动、启动、链接及构建 |
| [仿真与参数加载](sim/README.md) | 加载器、12任务运行、计时与参考校验 |
| [ASIC配置](config/asic/README.md) | 配置边界、文件清单和依赖状态 |
| [架构与指标](docs/README.md) | 架构、流程、最新指标及官方说明 |
| [历史资料](archive/README.md) | 旧版本、阶段验证和部署包索引 |

**先读**：[当前交接说明](deliveries/kwt1-accelerator-20261103/START_HERE.md)。

以上一级目录是分类入口，不是第二套源码。真实工程保留在 [deliveries/kwt1-accelerator-20261103/](deliveries/kwt1-accelerator-20261103/)，已有RTL、脚本、清单和运行目录不移动、不修改。无需调整现有命令。

版本：11月4日DMA源码与环境已交付，11月6日更新说明与指标；后续服务器ASIC修正源码尚未完整同步。当前仓库不能据此宣称最新ASIC环境已完整复现。

历史根目录工程已清除。交付目录中的不同阶段资料由历史入口索引，不应递归搜集所有 .v 编译：同名模块有多个配套快照。
