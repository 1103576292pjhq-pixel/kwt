# FFN1 公开 ICB 总线验证

`rtl/ffn1_icb.sv` 外包既有 `ffn1_top`，全部数据装载和逐行结果读回经公开 32 位 ICB 端口。测试平台只准备原始输入、给总线请求、检查参考结果；不修改 DUT 存储器，不把期望结果注入加速器。

## 运行

在工作区之外运行也可：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_icb.sh' --mode protocol
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_icb.sh' --mode full
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_icb.sh' --mode repeat
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_icb.sh' --mode full36
```

- `protocol`：3×64×4，固定随机种子 `0x20261016`，命令间隔与响应反压；两个连续完整任务、负偏置极值与溢出/饱和、reset、非法访问和错误恢复。小波形 `protocol/protocol.vcd`。
- `full`：99×64×256，冻结数值清单第一例。
- `repeat`：独立仿真进程重做第一例，优先以当前源码下 `full36` 为基准；没有有效 `full36` 时才使用当前有效 `full`。源指纹与输出文件 SHA-256 必须一致，无需为复跑额外做一次重复的单例基准。
- `full36`：三份固定输入 × 十二层独立参数，共 36 例；同一实例连续装载执行。它与原核心 36 例回归分开保存，不覆盖原证据。

每次模式运行先将该模式状态置 `RUNNING`，全部真实命令成功、来源校验、完整输出逐位比较、输出数量、实际 MAC 计数与源文件前后哈希一致后才写 `PASS`；任何失败写 `FAIL`。同一时间只允许一个本桥回归，不与本桥其他模式争用证据。完整模式在仿真前后分别调用数值 `verify_vectors` 校验来源与全部固定整数数组；不训练，不校准，不调整缩放。

长仿真每个案例结束都刷写 `run.log` 与 `progress.json`，`process.json` 保存真实 vvp PID、父进程、启动命令、时间和最终退出码。`status.json` 的 PASS 必须等全部案例和仿真后再校验通过，单个 CASE_PASS 只表示当时的局部进度。

## 行为性故障注入

`dv/icb/run_mutations.py` 在 `mutations/` 生成临时 RTL 副本，不改生产源码。四个变异分别忽略延迟核心错误、在响应反压时改变数据、忽略 LO/HI fresh、把同步行结果替换成零。每个副本必须正常编译并由协议 testbench 的预期行为断言非零退出，才算该变异被拒绝。fixture、编译日志、失败断言与源码哈希均保留；原始“模块缺失 RED”历史仍保留，行为性 RED 作为额外证明。

## 协议约束

默认基址 `0x11000000`，`M=99`、`N=256`，单 outstanding。命令握手一次后，在该响应被消费前 `cmd_ready=0`；响应数据、错误与 valid 在反压期间稳定。核心 load/start/ACK/read 信号均只发一拍，额外等待核心同步处理再检查 `command_error` 或 `row_rd_valid`。历史 sticky error 不会把后续合法响应误标为错误。

完整寄存器表以 `work/common_e203_design.md` 为接口契约。48 位偏置的 LO、HI 必须分别新写；每次对齐的 LOAD_COMMIT 写尝试都消费 fresh，包括值错、掩码错和核心拒绝。X/W 的 LO 必须完整 32 位符号扩展其低 16 位。reset 撤销在途事务、清控制状态，下一次任务必须重新装载。

## 证据边界

这是公开总线 BFM 验证；真实 E203 CPU 固件执行的证据另由系统集成报告提供。行为仿真的周期不能证明 150 MHz、面积或功耗。默认完整数据来自两份真实验证音频和合成静音，覆盖范围不等于官方 600 样本。

各模式 `status.json` 保存精确源/向量/输出哈希、数量、完成时间；`commands.json`、`compile.log`、`lint.log`、`run.log` 保存真实工具命令和输出。lint 允许已有未连接观测端口、RAM 不使用的高地址位与桥观测线警告；任何 lint error 都非零退出。

目录可能保留早期单例 `full/` 的历史证据。最终交接使用 `work/icb_handoff.json` 所列报告，且须逐项匹配当前源码指纹；历史 PASS 不能自动用于修改后的源代码。本轮新核心以 `protocol/`、`full36/` 和随后 `repeat/` 为准。
