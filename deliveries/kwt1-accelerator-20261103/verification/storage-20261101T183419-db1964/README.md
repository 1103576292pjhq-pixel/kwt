# X/W/bias存储验证记录

**仅为测试专用合同模型自检，未使用官方宏；不能宣称官方SRAM集成通过。**

状态：`PASS_STORAGE_TB_CONTRACT_SELFTEST_ONLY`。

周期为20.0ns，仅是功能仿真条件，不是最高工作频率测量。
向量由TB的字面边界和固定种子生成；黄金存储按真实合法请求更新，不使用DUT内部存储数组算期望。

| 套件 | 实测统计 |
|---|---|
| tb_storage_array | cycles=3160, x_reads=16776, w_reads=4880, writes=11008, masked_writes=384, q_hold_checks=768, reads_after_standby=24 |
| tb_storage_wrapper | cycles=9398, x_writes=9209, x_reads=15714, x_returns=15708, w_writes=10241, w_reads=12778, w_returns=12767, x_errors=9827, w_errors=7985, canceled=17, bias_writes=2022, bias_checks=9396, resets=6, parallel_rw_cycles=4034 |

错误副本检出：current_x_address, w_slot_alias, bad_x_read_valid, wrong_bias_slot。
软件基线33项通过；生产RTL及公共宏在本次运行前后字节一致。

物理实体测试覆盖24颗宏全部物理地址、16个低有效掩码位、写时Q保持、待机不误写及复位禁止写入。
wrapper测试覆盖全部6400个X逻辑位置和2048个W逻辑位置、连续跨宏返回、bank/槽独立性、所有X越界地址、冲突、复位取消和两槽bias。
bank3尾64项在容量测试中由TB主动装载；尾行屏蔽仅测试接口驱动，不代表已经验证硬件矩阵调度器。

完整命令、模型路径/哈希、源码快照、仿真日志和事务账本分别见commands.json、report.json、source/及*-trace.txt。
尚未覆盖：150MHz/STA/PVT/宏面积功耗；矩阵供数与任务调度；结果owner/ICB/SoC；完整输入域形式证明；官方宏Verilog及待机Q实际行为。
