# ICB接口测试

当前通过证据：[icb-20261031T224503-e273cf](../../verification/icb-20261031T224503-e273cf/README.md)。4独立TB及实际生产顶层两个完整任务通过；范围及源码身份以报告为准。

| TB | 内容 |
|---|---|
| tb_command_fifo | 固定一项缓冲的随机出入、同拍替换、快照保持、clear/reset优先及事务账本 |
| tb_icb_regs | 地址/写掩码/字段高位、配置与快照、满提交、响应背压、结果路由及中止 |
| tb_result_access | 连接实际结果模块，读/释放、空读、后端等待、使能下降及ABORT不吞响应 |
| tb_icb_completion | 完成状态被总线读本身遮蔽的回归 |
| tb_icb_system | 通过ICB访问实际生产顶层；两个完整任务、稠密不饱和/端点饱和数据、错误ACK、满缓冲重试、中止及连续会话 |

运行：`/usr/bin/python3 -B scripts/verify_icb.py --contract-models`。不加此参数只运行独立TB，不自动用替身冒充官方宏。联合测试发起端是TB不是E203 CPU，后端SRAM为显式测试合同模型；不作为官方SoC/CPU或赛事验收结论。

源文件、命令/退出码、实际响应账本、向量来源及SHA256按每次新建verification/icb-*保存。[接口说明](../../docs/rtl/accelerator/icb-interface.md)给出自定义寄存器协议及与E203事实的边界。
