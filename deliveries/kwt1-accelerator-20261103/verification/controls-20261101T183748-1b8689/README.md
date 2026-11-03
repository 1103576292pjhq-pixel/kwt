# 控制模块验证记录

**内部联合使用测试专用存储模型，未验证官方SRAM、ICB或平台。**

状态：`PASS_CONTROL_UNITS_ONLY`。默认时钟周期20ns仅是功能条件。

| 测试 | 统计 |
|---|---|
| tb_operand_feeder | blocks=53, groups=13568, faults=6, canceled=2, resets=9, cycles=28806, stalls=14844, hold_checks=14843, max_outstanding=2, final_stalls=850 |
| tb_load_ctrl | cycles=158039, commands=114883, x_writes=95043, w_writes=19456, bias_writes=304, negatives=29, resets=34, sessions=32, activations=16, releases=16, begin_stalls=15, start_stalls=13, open_stalls=183, pipelined=95040, commits=18 |
| tb_result_blocks | cycles=38977, allocations=96, fills=5526, publishes=90, reads=5457, acks=88, errors=15, aborts=11, fault_cases=7, stalls=8835, blocks=87, concurrent_fill_read=7 |
| tb_task_ctrl | cycles=29269, blocks=400, feeder_starts=400, core_starts=400, releases=16, feeder_first=226, core_first=174, allocation_stalls=15413, aborts=3, faults=2 |

数据来源：fixtures/source.json及本脚本固定种子，Python任意精度整数独立计算点积、RNE和sat16。非官方数据集。
联合验证实际连接四控制模块、既有点积核和当前存储wrapper/实体；测试专用模型为显式启用的sram_contract_models.v，其待机Q保持及0.2ns读延时为假设。

错误副本检出：feeder_wrong_w_slot, loader_wrong_x_bank, result_cursor_on_accept, task_release_every_block；只修改证据目录副本。上述身份范围内的被测生产RTL运行前后字节一致。

命令、日志、源码快照与SHA256见commands.json、report.json、source/。联合结果账本见internal-trace.txt；脚本再次独立检查三任务每任务25344个位置无重复、值匹配及400次发布。

未验证：官方SRAM模型；生产顶层/ICB/FIFO/guard/SoC；官方精度性能验收；150MHz/STA/PVT/PPA。
