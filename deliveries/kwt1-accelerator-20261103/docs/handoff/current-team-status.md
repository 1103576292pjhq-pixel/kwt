# 当前交接入口：DMA版加速器与12任务测试

更新日期：2026-11-04。此文是给队友的当前入口；2026-11-03交接文档保留历史信息。

> 2026-11-04 迁移后更新：服务器正式入口已提升为 accelerator/rtl、rtl/e203/soc/kwt_dma_soc_top.v 和 accelerator/run_suite.py。旧候选包目录已移出工程，以下旧路径仅供历史追溯。迁移后三任务 verification/dma_current_check_01 全部通过，每项554144周期，总1662432周期，76032输出。旧526文件/22目标归档到工程外 kwt-soc-before-dma-20261104-122733。原12任务成绩保留；本轮增量发布的实际提交以 upload/team-handoff-20261104-02/github-update-receipt.json 为准。


## 我们这轮做了什么

1. 优化CPU搬运驱动和ICB接口，减少软件指令及寄存器访问开销。
2. 新增硬件DMA搬运控制器：CPU配置任务，DMA经独立ICB主接口读取共享SRAM，向原计算引擎装载X/W/bias，并将结果写回共享SRAM。
3. 新增CPU/DMA共享SRAM仲裁及DMA状态/配置寄存器，保留原计算阵列和数值方案。
4. 在服务器完成实际E203、DMA及官方SRAM功能模型的完整单任务验证。
5. 修复顶层生成器：DMA总线须在使用前声明，且必须放在真实模块内部，不能插入版权注释。
6. 本地完成三种不同层参数的任务间清空回归，以及跳过复位的反向检错。
7. 制作12任务服务器包，加入清空检查、分任务精度、有效窗口周期、共享总线计数及VCD活动导出。服务器已完成12项，最终PASS_E203_DMA_SUITE_12；指标见下表。

## 版本状态：不要混用

| 项目 | 状态 |
|---|---|
| DMA计算/搬运RTL | 本地维护目录保留；服务器已提升至 accelerator/rtl，12任务及迁移后3任务通过 |
| DMA06单任务固件 | 882字节，固定case3层号；对应下表554138周期 |
| 新12任务固件 | 900字节，从共享内存读取层号，并检查任务初始状态；服务器12任务全部通过 |
| 服务器正式RTL与SoC顶层 | accelerator/rtl 与 rtl/e203/soc/kwt_dma_soc_top.v；旧目标已移至工程外备份 |
| GitHub交接分支 | ade9484 为迁移前发布；本轮迁移交接增量见新发布回执 |
| 150MHz、面积、功耗和能耗 | 尚无新版综合/STA/功耗报告，不得填为通过 |

计算仍为99×64乘64×256加偏置，400块、25344输出、1622016 MAC。
数值仍为X signed16/Q12、W signed16/Q16、bias32/Q28、acc40、加bias临时41、RNE右移16和sat16。
没有恢复48位方案。内部SRAM仍20KiB，共享SRAM仍512KiB。

## 本地与服务器对应

本地根目录：`D:/嵌赛芯片设计赛道/kwt1-accelerator`。
服务器根目录：`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`。

| 用途 | 本地相对路径 | 当前服务器相对路径 |
|---|---|---|
| DMA模块维护及原理 | integration/e203/dma_accelerator/ | accelerator/rtl/dma/ |
| 最新12任务环境维护版 | integration/e203/dma_suite/ | accelerator/ |
| 生产SoC顶层 | 维护生成器 prepare_soc.py；不是服务器完整镜像 | rtl/e203/soc/kwt_dma_soc_top.v |
| 测试入口 | integration/e203/dma_suite/run_suite.py（迁移前路径配置） | accelerator/run_suite.py |
| DMA06历史证据 | verification/e203-dma-server-20261104-01/ | verification/dma_soc_06/ |
| 12任务结果 | verification/e203-dma-suite12-server-20261104-01/（截图转录） | verification/dma_suite12_01/ |
| 迁移后3任务结果 | verification/e203-dma-promotion-server-20261104-01/（截图转录） | verification/dma_current_check_01/ |
| 共享SRAM拼接RTL | integration/e203/shared_sram/rtl/ | shared_sram_bundle_01/kwt-shared-sram-v2/rtl/ |

本地根 rtl/ 为历史实现；服务器 accelerator/rtl/ 已是当前DMA实现，两者不能混淆。
本地 dma_server 是DMA06历史环境维护版；dma_suite 是最新12任务维护版。
upload/dma-suite-20261104-01 与封存包保留迁移前快照；服务器迁移适配过 runner 与模板，尚未取回完整镜像。
旧 dma_server_test_01、dma_suite_test_01 等目录已移出正式工程，只用于历史追溯。
不要将 verification/ 或仿真模型递归纳入综合。综合入口见[当前综合交接](synthesis-handoff-current.md)。

## DMA新增模块

| 文件 | 职责 |
|---|---|
| kwt_dma_controller.v | 独立装载和结果写回状态机，含输入暂存、背压与在途请求处理 |
| kwt_dma_csr.v | CPU配置、状态、任务描述符范围和重叠检查 |
| kwt_icb_arbiter2.v | 两请求方仲裁；响应完成前保持事务归属 |
| kwt_dma_engine.v | 将原计算、控制和存储接入DMA装载/结果接口 |
| kwt_dma_accelerator.v | CPU配置从接口和DMA访存主接口顶层 |
| kwt_dma_system.v | 加速器、共享SRAM和CPU/DMA仲裁的组合模块 |

实际E203连接顶层由prepare_soc.py生成kwt_dma_soc_top.v。
verification/dma_soc_06/kwt_dma_soc_top.v是单任务验证时生成的生产接线；kwt_real_soc_top.v含仿真加载复用器，不是生产顶层。
完整SoC综合应由队友根据生产顶层建立ASIC源清单、库与SDC，不能把仿真FPGA宏和SRAM行为模型原样用于正式综合。

## 已确认的服务器单任务指标

同一真实case3，完整窗口从输入/参数开始装载到最后结果写响应：

| 版本 | 周期 | 150MHz归一化延迟 | 单任务延迟倒数 |
|---|---:|---:|---:|
| 原CPU搬运 | 5106213 | 34.041420ms | 29.375978 task/s |
| 优化CPU驱动 | 2799866 | 18.665773ms | 53.573992 task/s |
| 流式ICB接口 | 2486736 | 16.578240ms | 60.320034 task/s |
| DMA06 | **554138** | **3.694253ms** | **270.690694 task/s** |

DMA06：400块、25344输出、逐位错误0、NRMSE 0.01737469%；较流式ICB提速4.487575倍。
装载91902周期，后续至写回462236周期；CPU程序总周期1247993是另一窗口，不能替代554138。
数据来自服务器截图转录，原始服务器JSON尚未下载；见本地receipt.json与server-pass.png。
这些不是12任务吞吐，且150MHz仅目标频率换算。

## 12任务服务器结果

状态：用户截图确认PASS_E203_DMA_SUITE_12。304128输出，逐任务通过，最大NRMSE 0.02214978%。证据为截图转录，尚未直接读取服务器完整报告。

| 项目 | 当前值 |
|---|---|
| 完成任务数、逐任务NRMSE与位差异 | 12/12，最大0.02214978%；最终PASS要求逐位错误0 |
| 12项有效周期及总周期 | 每项554144，总6649728 |
| 12/总有效时间的吞吐、平均延迟 | 按150MHz：270.687763 task/s，平均3.694293ms，总44.331520ms；STA待完成 |
| 装载开销、CPU/DMA共享总线计数与等待 | 脚本已记录到服务器report.json；截图未列具体数值，待取回 |
| 每任务清空回读及缓存失效检查 | 最终PASS包含逐项审计；原始日志仍在服务器 |
| VCD压缩文件及计时裁剪信息 | activity=all运行通过，脚本逐项验证生成并压缩；文件及覆盖率尚未独立核对 |

现有验证集覆盖12层，非组委会冻结后抽样。任务间复位/清空准备及最终校验不纳入有效窗口。
清空方式是共享X/W/bias/Y逐地址写零并回读，内部缓存元数据复位失效，不声称内部SRAM物理逐地址清零。
12次独立冷启动仿真采用同一可执行文件/固件；不是无复位连续执行测试。
总线事务数不是物理SRAM宏访问量；各类等待可能重叠，不能当作互斥时间相加。
VCD须由队友映射综合网表、检查覆盖并使用SRAM功耗模型；波形本身不是功耗成绩。

## 本地测试结果

- 同一仿真实例三任务清空回归：76032输出逐位一致，NRMSE分别0.01590282%、0.01318576%、0.01737469%。
- 跳过第二任务前复位：成功检出残留完成状态，反向检查通过。
- 新12任务环境的前三项接线回归通过，5项报告检错用例通过，完整任务VCD导出检查通过。
- 本地CPU是总线BFM、SRAM为合同模型，不能冒充实际E203服务器结果。

## 给队友的下一步

1. 从服务器正式 accelerator/rtl 选择DMA源码，按当前综合交接核对ASIC清单、库和约束。
2. 12任务已完成并补齐截图可见指标；下一步取回服务器原始report.json和metrics.csv，保留编译/运行日志及波形。
3. 正式目录迁移与3任务回归已完成，不重复迁移；取回原始报告后核对 DMA_CURRENT.json 历史状态。
4. 本轮更新目标为1103576292pjhq-pixel/kwt的handoff/ffn1-accelerator分支；发布回执记录实际提交号。
5. 继续完成ASIC综合/STA、面积、活动映射、功耗与单任务能耗，保持同一配置。

历史细节见[工作记录](server-work-log.md)，12任务运行说明见[测试包说明](../../integration/e203/dma_suite/README.md)。
