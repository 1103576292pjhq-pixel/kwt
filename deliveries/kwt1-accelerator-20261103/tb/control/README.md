# 四控制模块及内部联合测试

2026-10-31最终证据：[controls-20261031T211136-aba7c3](../../verification/controls-20261031T211136-aba7c3/README.md)。四独立TB及三任务内部联合通过，源码身份和适用范围以该报告为准。

测试源是本目录五个`.v`，与旧`tb/system/`草稿接口分开。RTL保持用户当前文件；TB采用固定种子、外部事务记分板，不读取DUT内部存储/计数计算黄金。

| TB | 核对内容 |
|---|---|
| tb_operand_feeder | 两槽×25行组、256组k/g、X复用、固定L1返回、暂停保持、末组暂停、复位取消与异常返回 |
| tb_load_ctrl | X6336项及16tile W/bias写地址、数值和身份检查、q快照、装载进度、槽满等待及29种非法命令 |
| tb_result_blocks | 按g/p/q非线性填写、normal64/tail48、双块满、并行填读、响应快照、错误ACK、ABORT及序号耗尽 |
| tb_task_ctrl | 独立协议端点模拟400块，强制两路启动错拍、结果空间等待、W槽释放、完成排空与错误恢复 |
| tb_control_internal | 四个实际控制模块+实际点积核+存储wrapper/实体，三任务逐项核对Y/flags，另一个任务中途ABORT |

## 运行

Ubuntu WSL的活动工程根目录：

```bash
# 仅四个控制模块独立TB
/usr/bin/python3 -B scripts/verify_controls.py

# 显式启用测试专用存储模型，增加完整内部联合测试
/usr/bin/python3 -B scripts/verify_controls.py --contract-models
```

每次生成独立`verification/controls-时间-编号/`，保存源码快照、SHA256、命令/退出码、编译和运行日志。默认还运行故意错误副本检错与软件基线。`--skip-mutations`仅用于缩小调试范围，不能冒充完整检错回归。

内部TB仅为验证接线，不是生产顶层；不经过ICB或真正输入FIFO。载入命令直接送装载控制，读结果直接送结果事务口。SP bank地址逐bank选择装载或供数，检查无同bank读写冲突。核前后插入一致的valid/ready门控以产生随机暂停；两路启动采用不同门控时刻。CPU独立消费，装载等待期间仍读取结果，避免循环等待。

## 联合数据来源与黄金

`verify_controls.py`用固定种子生成三组99×64的X、64×256的W和256项bias，保存`fixtures/*.hex`及`source.json`。数据不是官方音频/模型输入：

1. 仅k63有贡献，X/W编码绑定行列身份，bias带半数舍入，适合手算及末项/映射检查。
2. 稠密较小随机有符号输入，主要检查不饱和结果，防止饱和掩盖错误数据。
3. 全signed16及signed32 bias随机范围，加入端点行列，覆盖正负饱和。

Python用任意精度整数直接计算64项点积+bias，再用`divmod(abs(raw),65536)`独立执行ties-to-even和sat16。每个TB读响应按描述符重建全局索引，与Python黄金逐项比较。事务账本记录实际响应，脚本二次核查每任务25344个位置恰好一次、400次发布。

## 范围

联合模式显式编译`tb/memory/support/sram_contract_models.v`，不是官方宏。其同步读、0.2ns读延时及待机Q保持是测试合同假设。默认20ns功能周期不证明150MHz。正式SRAM模型、生产顶层、ICB/FIFO/PAIR、guard/E203/共享RAM、官方样本和PPA均另行验证。

第一同步复位沿之前寄存器可能未知；复位隔离按同步复位沿后核对。各TB有超时断言，脚本另设600秒进程上限，不能以延长TB拍数掩盖协议死锁。实际通过情况以某次报告绑定的源码和日志为准。
