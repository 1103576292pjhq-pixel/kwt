# 自有RTL的服务器同名路径子集

这里的22份文件仅是15个加速器.v、4个.vh和3个共享SRAM.v，按服务器实际目录名称保存，方便定位。它们分别与交付根rtl及integration/e203/shared_sram/rtl逐字一致。

没有完整E203平台、生成顶层原文、商业库或仿真目录；不是独立可编译的完整SoC工程。整SoC综合取服务器已有e203-integration/kwt-soc，顶层kwt_shared_soc_top。详细路径及只读核对命令见../docs/handoff/server-folder-map-20261103.md。

顶层源码在服务器生成，未被本地取回；本交付提供生成工具和路径，不用原始GitHub模板冒充服务器文件。source-map中的哈希是期望基线，运行checker后才能声明服务器当前副本一致。
