# 给综合队友：独立加速器与完整SoC输入要求

> 历史快照：本文旧顶层及旧活动路径不再作为当前入口。请先读[当前状态](current-team-status.md)和[当前DMA综合交接](synthesis-handoff-current.md)。服务器迁移已完成，不重复执行。

日期：2026-11-03。两种综合都可以交给队友开始：独立块顶层`kwt_accelerator`，服务器完整SoC顶层`kwt_shared_soc_top`。本文件说明读取什么源码、配置什么库/约束和需要返回哪些报告；当前没有实际综合通过报告。

## 使用哪套源码

在本交付的工程根目录使用`rtl/kwt.f`，指定顶层`kwt_accelerator`，include目录`rtl/include`。清单包含15个生产`.v`和4个被include的`.vh`；`.vh`不作为独立顶层编译。文件完整性见交付根目录`delivery-manifest.json`。

参数：开发BASE_ADDR=32'h11000000；功能复测配置SRAM_EMA=3'd2、SRAM_EMAW=2'd0。顶层默认EMA=0，请显式覆盖并在综合/仿真报告记录实际值；2只是已验证功能模型配置，并非已证明所有PVT下最优或满足时序。external_abort_req由系统连接，E203当前集成中固定为0。

内部宏：8颗`RAMSP1024X16_rtl_top`和16颗`RAMSP128X16_rtl_top`，20KiB物理容量；bias和结果块为逻辑寄存器。需要赛方对应的宏封装和综合工具支持的库映射，不能把Verilog功能模型读进来就宣称已有宏的真实面积/时序。若macro wrapper含fr_top或其他层级，沿官方封装核对到实际库cell，并记录展开后的实例数，不能漏宏或重复算面积。

## 不加入综合

- `tb/`、测试合同SRAM模型、故意错误副本、`verification/`和VCS/Icarus编译产物。
- `integration/e203/shared_ram_dev/sim/`中的512KiB行为数组及其sim.f；它仅仿真，尚未接入SoC。
- GitHub仓库根目录另一套工程的RTL/驱动，或历史草稿/旧ABI。
- 独立加速器综合时不加入整个E203；整SoC综合与整SoC功耗另建明确的顶层及文件清单。

## 完整SoC从哪里开始

服务器根：`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`。

| 部分 | 服务器输入 |
|---|---|
| 当前生产顶层 | `rtl/e203/soc/kwt_shared_soc_top.v`，模块`kwt_shared_soc_top` |
| E203/子系统/总线外设 | `rtl/`中的实际集成副本；含导出hfclk/bus_rst_n的子系统修改 |
| 加速器 | `accelerator/rtl/`中的15个.v及4个.vh；与仓库独立`rtl/`基线对应 |
| 共享SRAM | `shared_sram_bundle_01/kwt-shared-sram-v2/rtl/`中的三个生产.v |
| 平台CPU存储 | `rtl/e203/mem_gen/`及平台ITCM/DTCM/ROM实现、相应库；不能漏掉 |
| 原仿真输入资料 | `verification/soc_compile_01/soc.f`及`verification/shared_sram_wiring_01/shared_sram_additions.f` |

完整SoC新增64颗`RAMSP4096X16_rtl_top`；加速器内部仍为8颗1024×16和16颗128×16。结合官方封装选择综合可用的宏wrapper/实际library cell，核对实际展开数量。外部宏资料位于`/storage1/admin_public_dir/SRAM_Lib_2025/`，不随GitHub交付复制。标准单元、PVT和CPU存储库由综合脚本按平台选择。

现有仿真命令包含`FPGA`、`ARM_UD_MODEL`和仿真TB，不能直接当ASIC综合脚本。队友要按平台说明选择正确编译分支、wrapper/库绑定和SDC；这是启动综合时的正常配置工作，不表示缺少一个新的加速器或总线模块。统一目标为系统150MHz，具体clock/PLL约束点按真实时钟树确定，不把TB的`#2`当作150MHz证据。

生产顶层不含验证加载mux。`kwt_real_soc_top`/`kwt_suite_soc_top`为生成测试top，不能取来做完整SoC综合；同样不加入testbench、合同内存或软件黄金。

当前GitHub不是服务器完整E203平台镜像：自有RTL和工具已同步，服务器实际生成顶层及原平台文件应取上述工作目录。可先在服务器运行交付中的`tools/check_server_sources.py --soc-root <上述根目录>`核对19份加速器RTL/头和3份共享RTL，再建立综合脚本。VCS缓存已清理，原`.f`/RTL/日志均保留。

## 时序需要怎么约束和核对

目标150MHz，周期约6.666667ns。建立真实clock、输入/输出延迟、时钟不确定度和复位约束；环境参数由平台和库决定，不在没有依据时编造。检查所有需要分析的路径是否有约束、是否存在未解析宏/黑盒、setup/hold是否通过及报告corner/单位。不要用扩大false_path、多周期约束或关timing checks来掩盖问题。

历史SRAM时序仿真有hold违例和X，已知激励CLK/控制同时间戳且模型hold500ps，需要通过波形/驱动边沿和真实接口约束分别定位。ARM_UD_MODEL功能模式通过不等于该问题解决，仿真时钟设置也不等于150MHz STA通过。

## 希望综合队友返回什么

| 交付 | 必须说明 |
|---|---|
| 可复现脚本 | 工具/版本、顶层、完整文件清单、宏/标准单元库及corner、参数、SDC |
| 映射网表 | 无未解析引用，保留宏实例或按官方映射方案处理 |
| 时序报告 | 时钟、关键路径、setup/hold、未约束路径、单位和PVT；150MHz结论以此为依据 |
| 面积报告 | 新增加速器+接口+内部SRAM宏合计≤2.25mm²；列出逻辑与宏分项，不漏计黑盒 |
| 综合前后功能 | 使用相同冻结输入/黄金，说明是否含SDF及库模型，结果逐位一致 |
| 功耗/能耗 | 正式活动窗口、VCD/SAIF、覆盖率、频率和PVT；整SoC口径含E203、互连和SRAM |
| 版本绑定 | 源码及关键输入哈希、命令/退出码、原始日志；输出用新目录保存 |

独立块综合能提前发现结构、资源和时序问题，但不能替代接入E203后互连、CPU、共享SRAM和完整驱动流程的系统验证；其功耗也不能直接作为赛事整SoC功耗。

真实case3共享链路已通过，但6079053是测试程序总周期，包含初始化和软件检查；也不能用较早405.827960任务/秒独立TB基线填报最终系统成绩。正式计时覆盖第一笔输入/参数真实装载到最后结果写回完成，按同一窗口计算吞吐量和能耗；专用计时工具开发目前暂停。

赛题不要求布局布线、物理验证或流片；综合、指定库STA及综合后功能仍需完成。
