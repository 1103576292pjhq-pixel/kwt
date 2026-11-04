# 当前DMA综合交接（2026-11-04）

可以开始综合；当前只有功能仿真通过证据，尚无ASIC综合、150MHz STA、面积或功耗通过报告。

服务器根目录：`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`。

| 对象 | 顶层及源码入口 | 需要核对 |
|---|---|---|
| 独立DMA加速器 | kwt_dma_accelerator；accelerator/rtl/dma/kwt_dma_accelerator.v | 计算、控制、内部存储及DMA依赖；不把共享SRAM计入此顶层实例 |
| 整SoC | kwt_dma_soc_top；rtl/e203/soc/kwt_dma_soc_top.v | E203配置、互连仲裁、加速器和共享SRAM完整依赖 |

accelerator/rtl/dma.f 从 kwt-soc 解析，包含组合/共享模块，仍需根据顶层建立ASIC清单。
accelerator/platform/base-*.f 是仿真模板，不能直接用作ASIC清单。
kwt_real_soc_top 含加载复用器，不能作为生产顶层；TB、合同模型、官方功能行为模型不作为综合逻辑输入。
不能照搬 FPGA、ARM_UD_MODEL 仿真宏。上游 E203 仅是参考，不能替换当前已验证平台。

内部SRAM共20KiB：8颗RAMSP1024X16、16颗RAMSP128X16；共享512KiB为64颗RAMSP4096X16，位于 shared_sram_bundle_01/kwt-shared-sram-v2/rtl/。
沿官方封装核对实际库cell及实例数量，避免漏计或重复计入。库目录为 /storage1/admin_public_dir/SRAM_Lib_2025/；实际.lib、工艺角、工作电压温度与标准单元库待队友确认。
本地DMA顶层参数默认 SRAM_EMA=2、SRAM_EMAW=0；正式服务器参数及宏工作条件仍须核对，功能配置不代表物理时序结论。

固定数值为signed16输入、signed32偏置、40位累加、41位加偏置临时和、RNE右移16及sat16；PM=4、PN=4、CTX=4。不修改计算结构。

队友返回的首次综合资料应包括：实际顶层/源码清单/宏/参数及哈希，工具版本、库与PVT、SDC、未解析引用/黑盒/锁存器/未约束路径检查，以及时序和面积报告。
150MHz对应周期约6.666667ns，输入输出延迟、不确定度和时钟关系需根据实际系统确定，不能凭空填约束。
后续完成综合前后功能检查、活动映射与覆盖率检查，再形成含SRAM模型的功耗和能耗；缺失宏功耗模型不能按零处理。

12任务活动文件位置为 verification/dma_suite12_01/case01..case12/activity.vcd.gz；截图确认activity=all及最终PASS，文件内容和映射覆盖率尚未独立检查。
功耗窗口与 TIMING_WINDOW 对齐；迁移后3任务activity=none，不提供新活动文件。
面积计入口径及比赛合规性需重新阅读本地赛题指南PDF第12页（印刷11/14），本次只整理综合输入，未重新作合规验收。

迁移后3任务截图回执见 verification/e203-dma-promotion-server-20261104-01/receipt.json。
DMA_CURRENT.json 中可能仍是迁移时的PENDING状态；取回原始 report.json 后核对，不能靠改状态代替测试。
服务器桌面另一份 kwt1-accelerator 尚待检查队友新增内容后归档，不作为当前入口；本地D盘同名维护目录继续保留。
