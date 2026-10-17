# 来源、设计推论与本次核查边界

日期：2026-10-17。以下资料是本包的依据；本文档不复制上游完整代码、模型权重、字体或工艺库。

## S1：用户已收到的RevB计划

本对话附件 `kwt_revb/PLAN.md` 与 `AGENT_TASK.md`，已完整回读。RevC保留其先核后总线/综合的范围；明确修改其微块调度、输入应答与支持参数，不把修改后的观点说成原文已经给出。

RevB的4×16块内以j0在k外层遍历，是本次减少主X读取的对照起点。RevB未声称新RTL已经实现，本包也不把过去的软件几何检查升级成硬件结果。

## S2：KWT仓库版本

https://github.com/1103576292pjhq-pixel/kwt/tree/3d9d0fc77457b8869cbf525d826dafb114f2a8e1

本次通过GitHub连接读取main引用，仍是上述SHA。只读，没有commit、push或修改仓库。

## S3：E203子系统接口

https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_top.v

核对约122—196行：sysper请求/响应接口、条件编译的sysmem接口。它支持“以后外层接入”这一设计边界，不证明当前已经具备比赛的512KiB共享SRAM或DMA。

## S4：KWT已有CPU薄封装

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/soc/e203_common/e203_cpu_shell.sv

核对1—44行：导出sysper/sysmem，bus_clk/bus_rst_n连接及上游子系统实例化开始。本轮保留而不重写。框架固定版本沿用RevB的记录，不声称重新进行CPU仿真。

## S5：旧数值参考

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/numeric/fixedpoint.py

本次完整读取其源码；Git blob为 `116dfb84c51a6847cb10678c9e5a7230fb796598`。使用其signed16、bias48、sat48→RNE→sat32及flags语义。core_model.py是本次编写的辅助软件，不能冒充原文件执行结果。

本次尝试下载原文件到运行环境时，网络下载未成功，因此没有运行该原文件。包内compare_v0.py为用户本地提供固定blob检查和实际执行入口；本包V0_FILE_EXECUTION明确NOT_RUN。源码经连接器可读与运行环境可下载是不同能力。

## S6：FINN并行与累加组织参考

https://github.com/Xilinx/finn-hlslib/blob/master/mvau.hpp

本次读取公开源码页面，用于理解MMV/PE/SIMD及局部累加的组织。CTX4是对本任务循环的设计提案，不声称从该代码直接移植，未包含其上游文件。

## S7：Ready/valid握手参考

https://fpgacpu.ca/fpga/handshake.html

重点是握手只在valid&&ready时成立、停顿保持数据、避免源等待ready才拉valid，以及逐笔延迟握手可能破坏流水。这些原则支持接口设计；本包具体故障策略、COMMIT屏障和tile所有权是项目设计决定。

## S8：用户上传《2026赛题指南 (1).pdf》

PDF第4页：E203平台、共享SRAM、内部指定宏及150MHz；PDF第6页：本科FFN1维度；PDF第7—8页：数据划分、层输入提取、任务1—3；PDF第11—13页：数值、性能计时和面积功耗范围。当前把系统与综合后置，不取消这些最终要求。

旧36工程案例不是正式600样本；本包合成输入更不属于正式数据。训练标定/验证调试/测试不调参约束始终保留。

## S9：未来E203仿真入口参考

https://doc.nucleisys.com/hbirdv2/quick_start/simulation.html

本次读取官方文档。它用于未来系统级工作，不是本轮独立核必须运行的命令，更不代表此包已经完成该仿真流程。

## 本次原创/推导内容

CTX4循环及代价分析；七组单变量配置；统一有序逻辑流；自动权重槽选择；明确的engine参数子集；软件自测、结果schema与包完整性脚本。解析数量由包内脚本计算，不能视为源材料里的实测数字。
