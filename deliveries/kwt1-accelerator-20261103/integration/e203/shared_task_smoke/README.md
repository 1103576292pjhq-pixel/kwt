# CPU共享数据完整任务功能测试

本包接在已通过的共享RAM访存和加速器MMIO之后。只新增测试固件和独立仿真运行目录，不修改加速器、共享SRAM或E203生产RTL。

## 这次真正检查的链路

CPU生成合成整数X/W/bias → 实际写共享SRAM → CPU逐字读共享SRAM → ICB装载加速器 → 400块计算 → CPU逐项将实际Y/flags写共享SRAM → ACK释放结果块 → 全任务完成 → 从共享SRAM回读全部25344项并独立对照。每块结果写回完成才ACK，最后完整读回和guard都正确才x3=1。

Y预填DEADBEEF，不允许漏写靠旧值通过。共享W为row-major，装载时按原tile/k/column顺序读出；expected使用原fixture闭式公式，不从被测共享输入生成黄金。数值仍是X16/Q12、W16/Q16、bias32/Q28、acc40、RNE16、Y16/Q12及原3位flags；本轮没有改变任何算术。

## 共享布局

基址a0000000仍是开发选择，所有对象使用32位容器。

| 对象 | 偏移 | 字数 |
|---|---:|---:|
| X | 00000 | 6336 |
| W，row-major | 08000 | 16384 |
| bias | 18000 | 256 |
| guard-before | 1fffc | 1 |
| Y/flags打包字 | 20000 | 25344 |
| guard-after | 38c00 | 1 |

全部小于512KiB且互不重叠；存储中使用32位容器不改变内部有效位宽。

## 文件与原理

- task_test.c/h：原task_smoke驱动的独立副本。三处输入来源改为共享读，实际结果写共享；BEGIN/槽调度/读游标/身份ACK/完成检查不变，原文件保留。driver-changes.diff给出差异。
- fixture.c/h：与旧任务逐字节相同的生成器及独立闭式期望，已对当前Python数值模型核对。
- shared_task.c/h：共享初始化、Y poison、完整任务及共享结果回读、guard检查。
- real_io.c：实际CPU的volatile lw/sw与fence；初始化/结果数据均真实访问共享总线，不用软件数组冒充。
- start.S、link.ld：原ITCM启动和结束机制。入口80000000、结束PC80000086；代码/bss小于80000c00，栈顶80001000。当前镜像2460字节、bss_end800009d0。
- build.py及build-01/：本地已安装Nuclei13.1.1交叉编译记录及预编译verilog字节镜像。服务器无需安装编译器。源码和镜像哈希在运行前关联核对，避免旧镜像配新C。
- run_server.py：从服务器实际TB和原soc.f生成独立副本，编译并运行；只在新验证目录写文件。
- tests/：同一C通过FIFO访问真实加速器与共享RTL的本地测试；宏为独立合同替身，不是CPU仿真或官方宏结果。它依赖原工程的生产源码和模型工具，包内保留供审阅，不声称可在脱离原工程时直接运行这些开发单测。

## 看门狗与结果判定

原平台TB的#40000000约对应1000万周期。新测试增加初始化、共享读取和完整结果写回/再读回，可能超过该上限。脚本生成新的tb_shared_task.v，将该唯一看门狗改为#160000000；不改原tb_top.v、不改时钟、不改TEST_PASS或结束地址，也不改变RTL。

采用真实服务器已成功的FPGA/ARM_UD_MODEL、原soc.f和shared_sram_additions.f及四个1024/128宏文件；4096宏由已有追加清单引入。所有实际E203/加速器/共享源码、头文件和官方模型哈希前后核对。旧simv保留，不能用旧镜像替代新任务。

VCS即使退出0也可能发生失败；脚本必须同时看到唯一TEST_PASS、最终x3=1、完整统计，并拒绝TEST_FAIL、Time Out及Fatal。

## 上传及执行

只上传kwt-shared-task-test.tar.gz到FileZilla/e203-integration/kwt-soc/，不重传任何RTL。然后复制整段：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
mkdir shared_task_test_01 && \
tar -xzf kwt-shared-task-test.tar.gz -C shared_task_test_01 && \
cd shared_task_test_01/kwt-shared-task-test && \
python3 run_server.py --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

新输出在kwt-soc/verification/shared_task_compile_01/，含原TB备份、新TB/filelist、compile.log、run.log和report.json。脚本打印COMPILE_PASS及FULL_SHARED_TASK_RUNNING后在后台日志中记录模拟器输出，可能需10～20分钟或更久，取决服务器负载；不是6311周期的简单访存测试。重复实验用新的--output，不覆盖旧目录。

成功标志PASS E203_SHARED_TASK blocks=400 stored_outputs=25344 verified_outputs=25344 x3=1。0x70表示共享结果回读不一致，0x71是guard被破坏；0xe0是CPU异常，其余0x40～0x58沿原驱动诊断。失败时保留日志并发最后输出，不通过屏蔽比较或放宽数值恢复PASS。

## 已有本地证据与边界

本地同一C代码对实际acc+64宏共享RTL，通过400块/25344项真实共享写回和回读；当前Python固定模型独立核对25344项逐位一致。共享读48322笔、写73666笔，其中Y实际写25344、回读25344；native总243528次总线事务，852576个TB周期。故意禁止首项结果写入时，最终回读DEADBEEF，code0x70、verified0，正确拒绝。

首次本地运行因Icarus无法打开中文绝对路径trace失败，原目录保留；改为相对trace路径后通过。该问题不涉及生产RTL或数值。

服务器真实CPU仍待执行。本轮CPU自己生成合成数据并写共享RAM，用于功能闭环；不等于正式真实音频/模型数据加载或host接口计时。包括CPU造数、软件比较等开销的周期不能当赛事正式FFN性能，不能与之前8,120,871周期测试直接算硬件加速比。150MHz STA/hold/面积/功耗及官方600/12任务仍单列。
