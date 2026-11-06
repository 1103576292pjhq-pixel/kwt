# FFN1 ASIC 交接入口（2026-11-06）

## 先读这一段
本目录是 FFN1 加速器服务器工作的交付，与仓库根目录的完整编码器工程分别管理。当前服务器实验包含 ASIC ROM 握手修正，**仓库源码尚未同步为该服务器快照**。本次更新的是状态与证据索引，不代表最新服务器源码已经上传或可直接复现。
以下数值来自运行截图转录，原始报告尚待一起归档；不能把旧 README 的 FPGA 数值与这些 ASIC 结果混用。

阅读顺序：本文 → metrics-current.json → docs/official/20261031-loading-and-timing-qa.md → 实际运行 read.tcl、sources.f、input-sha256.json。历史资料仅对其自身版本有效。

## 架构
`99×64 X · 64×256 W + bias → 99×256 Y`，每任务 25344 输出、1622016 MAC。PM=4、PN=4、CTX=4，16 个 MAC 通道。
X 为 signed16 Q12，W 为 signed16 Q16，bias 为 signed32 Q28；40 位累加、41 位加偏置，RNE 右移16位并饱和到16位。
E203 负责控制，DMA 负责共享 SRAM 与加速器之间搬运，计算由加速器完成。12 个测试是12次独立冷启动 FFN1 任务，不是完整12层网络。

## 运行流程及文件
1. 主机生成输入、参数及独立参考数据。
2. `real_loader.v` 经 ICB 接口将 X/W/B 写入共享 SRAM；CPU 此时保持复位。
3. 释放 CPU；ROM 启动指令跳转 ITCM 中的固件。
4. `start.S`、`link.ld`、`real_io.c` 启动；`shared_task.c` 做输出预填充与守卫设置，`task_test.c` 经 `kwt_mmio.h` 配置 CSR、启动、轮询。
5. DMA 读入 X/W/B，加速器计算，DMA 写回全部 Y。
6. 固件检查输出与守卫；`suite_metrics.v` 被动计时，`run_suite.py` 与审核脚本汇总。
`build.py` 生成固件；`real_shared_task.verilog` 是程序数据，不是可综合 RTL。
计时从首个 X 加载请求到最后一个 Y 写回响应，包括加载、CPU启动、调度、等待与计算；主机文件读取/一次性转换及结束后参考校验不计入。

## 配置与清单
生产顶层为 `kwt_dma_soc_top`；测试平台封装 `kwt_real_soc_top` 不作为综合顶层。
当前目标为 ASIC、约150MHz。综合定义 SYNTHESIS，未定义 FPGA；仿真使用 ARM_UD_MODEL 和 +notimingcheck。SYNTHESIS 本身并不等于 ASIC 模式。
综合 `elab/read.tcl` 定义实际 RTL、include目录、宏、顶层及库；其 analyze 使用 sverilog 解析不代表所有 .v 都是 SystemVerilog。
纯综合 `sources-asic.f` 必须搭配同次 `config.json`、库及SDC。仿真 `sources.f` 含 TB/模型，不能直接当综合清单。

## 存储器
| 用途 | 宏与数量 |
|---|---|
| 加速器内部 | 16×RAMSP128X16 + 8×RAMSP1024X16，共20KiB |
| ITCM | 32×RAMSP4096X16，共256KiB |
| DTCM | 32×RAMSP4096X16，共256KiB |
| 共享存储 | 64×RAMSP4096X16，共512KiB |
| 启动ROM | 1×ROM1KX32，共4KiB |
共152个SRAM宏，SRAM总计1044KiB。ITCM/DTCM封装名仍为 sram_wrap_32KX64 / sram_wrap_64KX32，内部采用4096×16宏拼接。

## 最新指标与边界
| 指标 | 当前记录 |
|---|---|
| ASIC功能任务 | 12/12通过，304128输出逐位比对零差异 |
| 每任务周期 | 552410.0015（计时端点换算，未强制取整） |
| 每任务耗时 | 3.68273297506 ms |
| 150MHz归一化吞吐 | 271.53744427634155 task/s |
| 最大NRMSE | 0.02214978% |
| SoC total cell area | 3919122.267743，库面积单位尚待确认 |
| macro/blackbox面积 | 3646774.761719，已包含于total |
| 非macro差值 | 272347.506024，同一库单位 |
| setup / hold | 报告显示0.00ns MET / 0.02ns MET，显示精度不保证实际裕量 |
| 首任务功耗估计 | 约40.9mW，尚非最终12任务功耗 |
不能把面积数值直接宣称为mm²；最新各模块面积尚未冻结。旧候选分项面积不代表ROMFIX版本。

## 改动范围
生产RTL和队友 Desktop/kwt_dc/ 保持保护。本轮修正位于自己的 dc 实验副本：
- ASIC ROM 初始化改为启动跳转内容（前两字7ffff297、00028067），原库文件未改。
- 实验 sirv_mrom_top.v 增加 pending/error 寄存与单事务请求/响应握手，修复同步ROM数据时序；对应新网表重新综合。
- 前序实验包含TCM宏拼接、UART锁存修正及clock-gate适配，必须按实际read.tcl依赖闭包交付。
- 加速器计算数据通路本轮未改；不能把“生产未改”解释成“实验平台RTL从未改过”。

## 服务器证据入口
公共根：`/storage1/2026contest/server2/s2_21usr/Desktop`
- 生产：`e203-integration/kwt-soc/`；其下 e203/、accelerator/rtl/、test_env/、共享SRAM与fixture子目录。
- 功能：`dc/runs/asic-rom-handshake-zsdiy719/`：suite12-report.json、case01..case12/audit-report.json、sources.f、sim/sirv_mrom_top.v。
- 综合：`dc/runs/soc-romfix-synth-jlkfngx9/`：elab/read.tcl、synth/compile.tcl、constraints.sdc、area.rpt、timing_setup.rpt、timing_hold.rpt、constraints_precise.rpt、映射网表及input-sha256.json。
- 功耗基础：`dc/runs/power-asic-romfix-task01-ecei0biq/`：power.tcl、power_total.rpt、switching_activity.rpt、units.rpt。
- SRAM Q补充：`dc/runs/asic-sram-output-activity-1i3phlqa/`。
最新read.tcl仍可依赖更早dc/runs中的适配文件，不能仅拷贝最新run目录。商业库路径记录在依赖清单中，不随仓库发布。

## 尚未完成，下一步
1. 从服务器只读导出实际文件、脚本、依赖闭包与原始报告，校验SHA后同步本地和此仓库。
2. 完成12任务相同计时窗口的SoC功耗及平均能耗：sum(P_i*T_i)/12。已准备批处理脚本不等于已运行。
3. 首任务SRAM输出活动补充后仍有默认活动及X；默认存储器驱动网络约65.08%。已识别有效读采样点未见X，不代表全部活动覆盖或门级等价通过；不能强制X为0。
4. 检查综合前后功能一致性，解决或说明 kwt_bus_clk 的min-cap违例（要求0.0005pF、实际0）。
5. 确认面积单位、最新分项面积与加速器+接口+内部SRAM≤2.25mm²口径；E203/共享SRAM/复用互连另列。
6. 按指南完成正式600样本及指定12任务；当前工程fixture不能替代官方验收。

给后续AI：先核实版本与原始证据再修改状态。不要重跑已通过工作来弥补缺失归档，不要改生产RTL或队友目录，不要将估计标为正式验收。
