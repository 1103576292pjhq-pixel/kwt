# 截图恢复候选：待服务器代码摘要核对

此处为用户2026-11-06所发截图的转录候选，不是服务器逐字节原件。ROM许可证保留；通用单元包含截图中的15个有效模块及Synopsys dc_script注释，排版重新整理，已注释掉的旧模块未转录。

- sirv_mrom_top.v：ASIC ROM pending/accept握手、ROM1KX32接口及保留的FPGA分支。
- GENERIC_RVT_SMIC.v：通用单元映射；时钟门控选择CLKLANAQV4_12TH40。

**尚未通过服务器有效代码摘要核对，也未编译/功能验证。不要替换生产文件或加入现有编译清单。** 与verified-adapters的三个逐字节哈希匹配文件分开存放。

provenance.json同时记录本地完整SHA256与去注释、去空白后的代码摘要。后者相同仅证明这种规范化后的文本相同，不证明原文件字节一致或硬件等价；Synopsys注释另按截图保留。
