# E203 共同工程 Implementation Plan

目标：用户已选择1A正式七项。此文保留共同底座任务，完整后续设计及计划见formal_seven_design.md和formal_seven_execution_plan.md。用户已授权继续工程，禁止Git写及重复许可询问。

1. 官方快照与工具准备（root）：固定ZIP/提交/许可/逐文件哈希；正确保存内部符号链接；实际验证GCC RV32 multilib与Yosys版本。不得修改既有124文件清单和源文件。
2. E203启动（boot worker）：只创建soc/e203_common、sw/e203启动/链接与boot_smoke、dv/e203_boot、run_e203_upstream_smoke.sh及专用报告。先使用上游真实仿真或构造失败固件看到非零，再运行最小C并观察邮箱。接口导出sysper/sysmem供后续接桥，不实现任何矩阵答案。
3. MMIO桥（bridge worker）：只创建rtl/ffn1_icb.sv、dv/icb、scripts/run_icb.sh及专用报告；依据固定表编写失败测试，再实现一事务状态机并验证。原计算核心不动。
4. C驱动（driver worker）：只创建sw/ffn1_driver.h/.c、tests/driver、scripts/test_driver.sh及专用报告；先host mock RED，再协议/拆分/错误/超时GREEN；编译RV32对象确认ABI，不写SoC最终固件。
5. 根集成：收到各PASS交接后组装真实CPU+桥+共享RAM，CPU运行至少一例完整矩阵；36例BFM系统回归、周期和来源回读。共享内存加载和加速器操作必须明确区分，禁止层次写加速器RAM。
6. 1A已确认：追加注意力、GELU/FFN2/LayerNorm/残差、十二层编码器与正式任务1—7映射；按formal_seven_design.md执行。
7. 合适时启用当前可用的真实持久执行器；先核对旧COMPLETE，任务用UTF-8文件，明确所有权、25分钟心跳、至少两轮自审及失败闭环。不得把普通agent称Potter。

验收命令入口需在各handoff给出实际退出码、XML/日志/波形/源码和固件哈希。独立根复核通过前不将新功能状态记为ACCEPTED。指定工艺/正式平台缺失只影响相应正式验收，不伪造PPA通过。
