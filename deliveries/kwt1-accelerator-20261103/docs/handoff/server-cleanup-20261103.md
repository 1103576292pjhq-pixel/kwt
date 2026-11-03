# 服务器整理与整SoC综合交付：现状记录

2026-11-03，用户授权整理服务器文件并删除不需要资料，目的是队友后续综合整个SoC。服务器仍由用户执行命令，不直接操作远程桌面。计时工具开发此前已暂停，现阶段专注文件整理。

## 当前证据

用户目录截图：kwt-soc根目录共约492MiB；rtl约230MiB、verification约237MiB、real12_verify_01约16MiB、shared_sram_bundle_01约5.2MiB、accelerator约216KiB。已看到多个上传tar包、Python字节码、固件和独立测试目录。尚未对目录深层内容及队友新增内容完成盘点，未执行删除或移动。

活动路径：/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc。

关键依赖由用户cat结果确认：verification/shared_sram_wiring_01/shared_sram_additions.f包含绝对路径，引用同一根目录下shared_sram_bundle_01/kwt-shared-sram-v2/rtl中的kwt_shared_ram_icb.v、kwt_shared_sram_array.v、kwt_shared_sram.v，以及rtl/e203/soc/kwt_shared_soc_top.v。4096宏模型只读引用/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP4096X16/verilog。

因此不能把shared_sram_bundle_01当成普通可删测试目录，也不能直接移动该目录或verification中的源文件清单。base soc.f也仍在verification/soc_compile_01/soc.f，被现有runner引用。

## 综合交付原则

- 整SoC的生产顶层为kwt_shared_soc_top（E203＋ICB加速器＋512KiB共享SRAM），不是verification中的kwt_real_soc_top或kwt_suite_soc_top；后两者含测试专用加载mux。
- 生产依赖包括rtl、accelerator/rtl、活动共享SRAM的三个模块及正确的官方宏/工艺库映射。TB、golden、仿真加载器、合同模型、simv/csrc不作为综合源。
- 仿真soc.f及FPGA/ARM_UD_MODEL宏是已通过的仿真配置，不能直接宣称它们就是完整ASIC综合配置；需明确CPU ITCM/DTCM、标准单元、SRAM和时钟/复位库绑定，队友按综合库落实。
- 先形成源码/依赖/证据清单，再限定删除已确认可再生成的编译中间物。运行中的输出、源文件、.f、库、固件、数据、报告及失败证据保留；历史源码需要归档时先处理路径引用。
- 删除仅针对确认属于本项目且已列明的绝对路径；不触碰队友其他目录或admin_public_dir。当前没有删除命令，也未声称服务器已整理完成。

## 当前验证状态

case3真实E203/shared完整任务已通过；12组连续任务用户要求先停止，截图只确认前3组已完成及第4组加载，未取得最终PASS。保留日志，不能记全12通过。单任务计时新工具仍为暂停的未完成草稿，不作为综合交付完成项。

下一步：针对rtl/verification/real12_verify_01/shared_sram_bundle_01的深层大小和大文件只读盘点，再确定具体清理列表及综合交付结构。

## 第二轮目录截图确认

rtl/e203/mem_gen约228MiB，占rtl的绝大部分；大文件包括RAMSP8KX32.bitmap、RAMSP4KX64.bitmap/lef、ROM2KX32.gds等平台存储宏资料。此目录还可能含整SoC综合所需库和模型，不整体删除。

verification中五个主要VCS运行目录的csrc各约16MiB、simv.daidir各约29～30MiB，内含生成的archive_1.a/.so。明确清理候选仅为soc_compile_01、soc_shared_compile_01、shared_task_compile_01、real_shared_case3_02、real_shared_suite_01中的csrc、simv.daidir和经ELF签名确认的simv。不删除整个verification，不删除soc.f、报告、日志或实际结果轨迹。

已准备upload/server-cleanup-20261103-01/cleanup_vcs_20261103.py。默认只预览，并生成soc-file-inventory-20261103.json，包含原仿真清单、源/库路径与哈希、配置/CPU存储源码，供进一步整理完整SoC综合交付。只有显式--apply才执行上述限定删除。

工具会拒绝运行中的simv/VCS/runner、目标或祖先符号链接、越出kwt-soc的路径和无法识别的生成目录。清理前后检查保护文件哈希，清理凭据独占创建；源码盘点输出拒绝符号链接及覆盖不同现有数据。五项临时目录行为测试通过，其中盘点输出符号链接缺口先红后绿；独立只读审查及该修复复审无Critical/Important。尚未在真实服务器运行或删除文件。

后续需要用户上传脚本并运行默认预览；得到实际目标清单及源码盘点后，再完成整理与清理。原12组运行是否已退出由进程检查确认，不凭截图中的shell提示符断言。

## 实际服务器清理已完成

用户运行默认预览后显示15项候选，共226.10MiB，受保护文件954；随后执行--apply。新截图确认CLEANUP_PASS removed=15 reclaimed_MiB=226.10 protected_files=954，源码/数据/报告等保护文件哈希保持；verification从约237MiB降到9.3MiB，工程总量约265MiB。rtl及mem_gen、共享SRAM活动源码目录、真实测试fixtures、固件及日志保留。

[截图凭据](../../verification/server-cleanup-20261103-01/receipt.json)已归档；完整服务器cleanup-vcs-20261103.json尚未下载。旧VCS可执行文件和生成库已清理，以后重跑对应仿真须重新编译。

当前仅完成编译产物清理；完整SoC综合输入的结构化整理尚未完成，等待用户把soc-file-inventory-20261103.json下载到本地。已检查本机Downloads、Desktop及D:/嵌赛芯片设计赛道，暂未找到该盘点文件。建议接收目录为kwt1-accelerator/server-downloads，下载后继续核对真实文件清单、CPU存储与工艺库绑定，不把仿真FPGA配置直接冒称ASIC综合配置。

## 当前协作方式更新

用户随后选择直接通过服务器终端查看资料，无需下载盘点JSON。当前交接已改用[服务器目录与仓库对应表](server-folder-map-20261103.md)、自有RTL同名路径子集和只读源码核对工具，支持队友直接在服务器确认版本；上段下载建议作为过程历史保留，不再作为继续交接的前置条件。未取回的实际服务器顶层及商业库不伪造、不上传。
