# 独立ICB接口与加速器验证记录

状态：`PASS_ICB_AND_ACCELERATOR_CONTRACT`。

**总线发起方为自检TB，不是运行固件的E203 CPU；存储为测试合同模型，非官方宏。**

实际生产顶层kwt_accelerator连接ICB、四控制模块、既有核和存储wrapper/实体。自定义寄存器表见docs/implementation/icb-independent-design-20261031.md；不沿用交接包ABI。

| 测试 | 实测统计 |
|---|---|
| tb_command_fifo | cycles=15223, pushes=6518, pops=6466, canceled=52, replacements=4860, hold_checks=6449, clears=60 |
| tb_icb_regs | cycles=11734, accepted=1230, responses=1230, commands=7, result_requests=4, result_retired=4, errors=292, holds=8007, aborts=1, request_stalls=8 |
| tb_result_access | cycles=1358, requests=141, responses=141, backend_requests=128, backend_responses=128, local_errors=13, backend_errors=5, reads=120, stalls=477, aborts=1, enable_drops=11 |
| tb_icb_completion | reads=1, holds=5 |
| tb_icb_system | cycles=715854, tasks=2, blocks=800, outputs=50688, transactions=215297, responses=215297, busy_retries=700, errors=702, holds=13483, aborts=1 |

双任务使用固定种子的稠密小数值与全signed16范围输入；Python任意精度点积+bias、独立RNE及sat16生成黄金。实际ICB响应账本二次检查每任务25344个位置无重复且值一致。另验证一次装载中止。

错误副本均先编译成功，再由TB断言检出：fifo_overwrite, regs_ignore_mask, result_early_retire, completion_not_latched。控制模块4独立TB、4种故障副本及33项软件基线也已重跑，通过路径见report.json。

默认20ns只是功能条件；未验证E203 CPU/完整SoC、共享RAM固件、官方SRAM模型、官方样本/性能或STA/PPA。命令、日志、数据及源码快照在本目录。
