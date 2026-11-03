# E203 完整计算功能测试

本阶段接在已通过的 mmio_smoke 后面。CPU 通过 ICB 完成一个完整任务：6336 个 X、16384 个 W、256 个 bias；先 BEGIN，按 tile OPEN/W/BIAS/COMMIT，第一 tile 提交后 START，读取并 ACK 400 块、25344 个输出。共享 RAM 继续不接，所有输入直接由 CPU 公式生成。

生产 RTL、40 位累加器、24 颗内部 SRAM、总线连接和服务器 simv 均保持原样。本次新增的是固件和验证工具，因此不产生新的硬件面积或时序测量结果。程序包含软件参考计算/逐项比较，运行周期不能当作赛事性能成绩。

## 每段代码做什么

- `fixture.c`：生成整数 X/W/bias；利用求和公式求期望点积，执行 RNE16 和 sat16。前两列使用极值权重，产生 133 个饱和输出；2..7 列专门检查正负奇偶 tie。所有输入都合法，raw overflow 应为零，最后一项的 last flag 应为一。没有用参考结果代替读取硬件输出。
- `task_test.c`：实际装载与结果处理。`send_command` 写暂存字段后轮询，只有 ready 才写 COMMAND；轮询时优先读走结果。`drain_block` 检查 task/seq/row/tile/count/cursor，逐项比较完整32位结果，最后写身份匹配的 ACK。所有等待有上限；只有400块且25344项均通过、完成状态可见、无 fault/ERROR 才返回1。
- `real_io.c`：把抽象读写落实为 32 位 volatile load/store 与 fence。原生测试和 CPU 使用同一份任务驱动，仅 I/O backend 不同。
- `../mmio_smoke/start.S`、`link.ld`：复用已在真实 E203 验证的启动/异常/结束机制。程序从80000000开始，结束循环80000086，成功 x3=1，异常 x3=e0。代码+bss在前3KiB以内，栈顶80001000，至少保留1KiB栈；本次最深调用链静态栈约128字节以内。
- `build.py`：检查 C/RTL 寄存器和命令数值一致，交叉编译，检查 ELF/入口/结束指令/未定义符号/内存范围，导出字节 hex 和哈希。拒绝覆盖已有构建目录。
- `tests/check_numeric.py`：独立构造矩阵，与现有 Python 黄金模型比较全部输出；另测30个转换边界。
- `tests/check_driver.py`：主机执行同一 C 驱动，通过 FIFO 与15个生产 RTL 文件联调。仅 SRAM 使用现有本地合同模型；不模拟 E203，不能代替服务器官方模型验证。另注入输出值、序号、fault、游标、永不 ready 五种故障，检查驱动不会假通过。

## 2026-11-02 本地证据

- `PASS C_NUMERIC outputs=25344 conversion_cases=30 saturated=133`。
- `verification/c-task-driver-20261102-03/report.json`：完整任务 `code=1 blocks=400 outputs=25344 status=d error=0`。122893次本地ICB事务、368683个本地RTL周期；这两个数不等于 E203 上运行的耗时。
- 同目录5种故障场景均被捕获：输出54、描述符51、fault41、读游标55、命令等待超时42，均为十六进制返回码。
- 原有33项软件测试、7项接线脚本测试通过。
- 最终源码再次验证：`verification/c-task-driver-20261102-04/report.json`，同样6场景全部通过；独立代码审查无Critical/Important问题。
- `task-build-01/build-report.json`：1976字节机器码，bss_end800007d8，诊断结构800007b8；交叉编译成功。构建时打开 `-fstack-usage`，`.su` 文件保留。
- 第一次本地编译遗漏合同模型启用宏、第二次 FIFO 扫描末尾空白导致两端等待，均只涉及新验证环境；保留01/02目录，03为通过结果。

## 2026-11-02 服务器真实 CPU 结果

用户19:09:07结果截图显示 **TEST_PASS、x3=1**。运行目录为 `verification/soc_compile_01/task_run_02/`，完整日志为其中的 `run.log`。

| 指标 | 截图结果 |
| --- | ---: |
| 总周期 | 8,120,871 |
| 有效指令 | 5,227,662 |
| 首次到达结束位置的周期 | 8,120,854 |
| 最终 x3 | 1 |
| VCS CPU耗时 | 687.720秒，约11分28秒 |
| 仿真时间 | 32,483,614,000ps |

按这份固件的成功判定，真实E203已通过ICB装载X/W/bias、启动计算、检查400块25344个输出的Y/flags/描述符/读游标并ACK，最后读到完成且无ERROR。这是一个完整合成数据任务的功能通过，使用已有集成中的官方SRAM功能模型配置。依据是用户截图；未直接读取全部服务器日志，不据此声称零警告。

SRAM hold 问题、正式共享 RAM、完整比赛参数/音频环境、150MHz STA 与赛事性能仍独立待办。VCS在服务器上运行约11分钟不表示芯片计算要11分钟；上述周期也包含CPU生成数据与逐项计算参考值，不能用作赛事成绩。

## 本地重建

在 WSL 项目根目录，使用 Python3 + GCC + Icarus Verilog；Nuclei工具链位置记录在已安装的 installation.json。每次选择新的输出目录：

```sh
python3 integration/e203/task_smoke/tests/check_numeric.py
python3 integration/e203/task_smoke/tests/check_driver.py --output verification/c-task-driver-next
python3 integration/e203/task_smoke/build.py --output task-build-next
```

## 上传和服务器执行

FileZilla 本地文件：

`D:/嵌赛芯片设计赛道/kwt1-accelerator/integration/e203/task_smoke/task-build-01/task_smoke.verilog`

只需此镜像。上传到远程 `/e203-integration/kwt-soc/`，即服务器 Desktop 下的 kwt-soc 根目录。保留既有 build-01/mmio_smoke.verilog 和所有已通过日志。镜像 SHA256 见同构建目录 build-report.json。

以下留存已执行命令（服务器 csh/tcsh），无需重跑；TESTCASE 不带 .verilog。原task_run_01已存在，创建失败后换用task_run_02。mkdir不加-p，避免覆盖日志；以后重跑须选择新的目录。

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
ls -l task_smoke.verilog && \
mkdir verification/soc_compile_01/task_run_02 && \
cd verification/soc_compile_01/task_run_02 && \
../simv +DUMPWAVE=0 +SIM_TOOL=vcs \
  +TESTCASE=/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/task_smoke \
  -l run.log
```

实际已得到 TEST_PASS、x3=1。既有10M-cycle watchdog保持原样；本次8,120,871周期内正常结束。保留run.log与之前的MMIO基线。

## 失败码及诊断

TB显示x3为十进制，下表为十六进制：40初始状态；41fault/abort；42命令等待超时；50结果任务身份/多余块；51块元数据/顺序；52读前cursor；54数值/flags；55读后cursor；56等结果超时；57完成不一致；58完成超时；e0 CPU异常。

`kwt_diag` 为8个32位字段，依序 phase、blocks、outputs、position、expected、actual、status、error。此构建地址800007b8；失败时供波形/调试读取，不额外要求修改官方TB。全局输出位置为row*256+column。
