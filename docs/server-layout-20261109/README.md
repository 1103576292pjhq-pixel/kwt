# 2026-11-09 服务器目录与当前入口

本目录保存用户在服务器执行更新命令后确认成功的四份文档原文。确认标记：`PASS_CURRENT_DOCS_UPDATED`；ASIC 输入未变，未修改 RTL/配置，未重跑仿真。证据来自用户终端截图，不是直接取回的完整服务器文件系统。

## 阅读顺序

1. [服务器 kwt-soc 总入口](README_CURRENT.md)
2. [test_env 分类](test_env/README.md)
3. [SoC ASIC 当前运行方式](test_env/soc_asic/README.md)
4. [清单边界、后仿与待办](test_env/docs/CURRENT_FLOW.md)

**这些文档里的源码相对路径指服务器布局。此目录只含文档，没有对应 RTL、TB、数据或二进制程序；不能在本目录运行仿真。** 文档链接指向未随本次提交上传的服务器文件时，请在服务器访问。仓库既有源码仍保留原路径。

## 已确认的整理结果

- test_env 根目录仅保留 README.md、accelerator_dma、common、docs、soc_asic。
- kwt-soc 管理文件归类后核对 1085 个设计文件未变、256 个当前 ASIC 输入通过。
- 旧 real12_verify_01 已归档；61 个 fixture 与新位置一致；归档后单任务功能检查通过。
- 根目录 sources.f 仍保留：dc/scripts/read_soc_design.py 实际依赖它。它是候选清单，不是已验证的最终综合配置。
- 文档旧版已备份到服务器 verification/history/docs-update-20261109-151458-817430/。

本次仅同步上述四份文档与仓库导航，不同步 E203、工艺库、服务器专用配置或整个测试包。历史交付中的旧路径和脚本不应作为整理后服务器的直接入口。已有指标没有因目录整理而更新。
