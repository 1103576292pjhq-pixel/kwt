# 点积计算核接收验证：2026-10-28

本次为用户从点积开发转向整个独立加速器前，对磁盘现有实现重新接收验证。结果：`PASS_BLOCK_CORE_PORT_LEVEL_REGRESSION`。生产RTL、宏、TB、验证脚本和数值模型均未修改。

当前顶层相对 `block-core-20261028T215423-d9c5a6/source/` 仅补充注释和分段说明，字节哈希已不同；本次重新绑定当前版本，不沿用旧报告哈希。当前顶层SHA256：`75495f70abc319ecadcc44e40bd2ce1008a5fe6dab249fbb744e2af57195fc9e`。

| 检查 | 本次结果 |
|---|---|
| 设计Verilog-2001编译 | 退出0，日志空，无警告 |
| 定向/随机/复位 | 23块，20完成、3故意取消 |
| 已有手算完整任务 | 400块、25344项Y及flags一致 |
| 本地真实样例12层 | 4800块、304128项Y及flags一致 |
| 全部测试块 | 5223启动、5220完成、3取消 |
| 背压保持检查 | 156184拍 |
| 故意错误副本 | 6种均检出，编译退出0，仿真按预期退出1 |
| 软件基线 | 33项全部通过 |
| 验证后源码身份 | report中10份文件SHA256与磁盘全部一致 |

总输入1336869组、输出330703项、仿真2297793拍；输出包含复位取消场景中已经交付的63项。上述总拍数包含全部套件和人为随机等待，不是单任务延迟、整机冷窗或实际频率。报告中的full_rate=14是各套件标志求和，不是14 MAC/拍之类的吞吐数值。

实际运行：

```bash
cd '/mnt/d/嵌赛芯片设计赛道/kwt1-a40-accelerator'
/usr/bin/python3 -B scripts/verify_block_core.py
```

环境：Ubuntu WSL、Python3.10.12、NumPy2.2.6、Icarus Verilog11.0。详情见 [report.json](report.json)、[commands.json](commands.json)、[软件日志](software-baseline.log) 和本目录源码快照 `source/`。

真实输入来自既有 `generated/ffn_fp32/validation_right_a69b9b3e_nohash_0/layer_00..11`；脚本对原输入及manifest检查历史哈希，按冻结格式编码，用整数黄金及独立Decimal舍入核对后送TB。没有重新提取音频、训练或改黄金。

边界：TB负责分块供数和重建矩阵，仅验证计算核端口行为。未验证真实SRAM请求/返回、硬件矩阵调度、MMIO/CPU/owner集成、官方600样本或综合/STA/PPA。下一阶段入口为 [整个加速器交接词](../../docs/handoff/full-accelerator-new-chat.md)。
