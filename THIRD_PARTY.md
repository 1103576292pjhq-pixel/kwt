# 第三方源码、模型与数据

供应商快照与来源清单按原目录保留。修改、再分发或公开发布前，应阅读对应完整许可证和文件内通知；本文件不替代许可证。

| 目录 | 用途 | 许可证入口 | 版本与校验来源 |
| --- | --- | --- | --- |
| `vendor/e203_hbirdv2-upstream/` | 公开 E203 / Hummingbird SoC 原型 | [LICENSE](vendor/e203_hbirdv2-upstream/LICENSE) | [E203 来源清单](config/e203-source-manifest.json) |
| `vendor/hbird-sdk-upstream/` | SDK 与启动代码参考 | [LICENSE](vendor/hbird-sdk-upstream/LICENSE) | [E203 / SDK 来源清单](config/e203-source-manifest.json) |
| `vendor/HardFloat-1-upstream/` | 浮点计算模块 | [COPYING.txt](vendor/HardFloat-1-upstream/COPYING.txt) | [HardFloat 来源清单](config/hardfloat-source-manifest.json) |
| `vendor/keyword-transformer/` | 官方模型代码与权重参考 | [LICENSE.txt](vendor/keyword-transformer/LICENSE.txt) | [模型来源清单](config/source-manifest.json) |
| `data/encoder_test_subset/` | Speech Commands 12 类工程测试子集 | [来源、选择与许可信息](data/encoder_test_subset/manifest.json) | 本地工程子集，不等于正式比赛测试集 |
| `data/speech_commands_subset/` | 首批模型验证输入 | [来源清单](data/speech_commands_subset/manifest.json) | 原始来源与选择记录保留 |

E203 / SDK 内还含其他来源的测试、软件与文档，许可证以各子目录及文件头为准。仓库保留这些原始通知和冻结快照，不据此为本项目自有代码另行指定许可证。

赛题指南位于 [work/report_cycle_sources/2026赛题指南.pdf](work/report_cycle_sources/2026赛题指南.pdf)，作为需求核对来源保留；其权利归原权利人。
