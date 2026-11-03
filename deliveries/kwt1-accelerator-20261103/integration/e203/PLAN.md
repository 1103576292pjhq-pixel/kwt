# E203 集成接线计划（2026-11-02）

目标：按用户确认的新顶层方案，在服务器 `kwt-soc` 副本中连接现有加速器和官方 E203 子系统。沿用独立加速器架构、协议和数值方案。

依据：用户指定 GitHub 仓库、服务器源码截图。截图已核实 main 模块生成 hfclk；bus_rst_n = main_rst_n；外围总线 clk=hfclk、reset=bus_rst_n。服务器源码仍以服务器运行脚本的实际检查为准。

方案：以原 e203_soc_top 为模板新建 kwt_soc_top；完整连接 SysPer ICB。main 新增总线复位输出，subsys 新增时钟与总线复位输出；不修改 CPU 逻辑。测试平台只替换 SoC 模块类型，保留实例名和层级宏。实例固定 BASE_ADDR=0x11000000、EMA=2、EMAW=0、外部 abort=0。此基址是本项目开发地址，未宣称赛方最终地址。

保留：原 e203_soc_top、原工程、baseline_01、加速器 RTL。未接中断，软件通过寄存器轮询。

限制：本阶段不接共享 RAM、不编写驱动、不声明 SRAM 时序收敛或赛事性能达标。

## 实施步骤

- [x] 先写工具行为测试：预览不改输入；不支持的源码拒绝；过期预览拒绝应用；输出已存在拒绝覆盖；应用保留原 SoC 和加速器。
- [x] 实现 prepare_kwt_soc.py：先完整检查再生成 before/after、diff 和哈希记录；单独 apply 时重新检查所有输入哈希。
- [x] 使用固定提交的官方上游源码测试脚本，记录结果。上游样本不冒充服务器同版本。7 项工具测试、原有 33 项软件测试通过（2026-11-02）。
- [x] 用户上传单文件脚本，在服务器副本执行 preview，截图显示 PREVIEW_READY。
- [x] 确认实际输出后应用，使用官方宏功能模型重新编译并先跑原 add 程序。截图显示 APPLY_DONE、VCS 生成 simv、集成后 add 为 TEST_PASS（cycle_count=25804、x3=1）。服务器结果依据用户截图，未独立读取全部日志。
- [x] 原程序通过之后进入 CPU MMIO 验证；2026-11-02 的真实 CPU 寄存器测试已 TEST_PASS。完整计算驱动验证仍见下方进展。

工具测试只证明接线生成和保护行为，不代替 VCS 编译、SoC 仿真或 STA。工程没有 Git；保留路径和哈希快照，不执行 git/reset/clean。

测试源码来源：riscv-mcu/e203_hbirdv2 固定提交 9f3e34f337f5d0a1236a285871ffa2032491617a 的 rtl/e203/soc/e203_soc_top.v、rtl/e203/subsys/e203_subsys_top.v、rtl/e203/subsys/e203_subsys_main.v 和 tb/tb_top.v。

## 2026-11-02 最新用户决定

先不接共享 SRAM，使用已有 TCM/生成的小数据做真实 CPU MMIO 测试。shared_ram_dev 中已完成本地组件仅保留备用，不加入当前服务器 SoC。当前 CPU 执行自写 C 程序的主要阻塞是交叉编译器安装位置/环境尚未确认；得到工具后还需准备与当前 ITCM 加载和测试结束判定匹配的启动代码、链接脚本和测试程序。原 add 的 TEST_PASS 不替代此验证。

## 最新进展：本地工具链已可用

用户授权先下载后，已从芯来官网下载 2024.06 Linux 裸机工具链（580752874 字节）；MD5 与官网下载响应值一致，SHA256 为 8cea2d10310150d8591d00eb8430377cc28865e76decbaca2abefea7dad80d89。WSL 安装于 /home/juhui/.local/opt/nuclei-2024.06/gcc，GCC 13.1.1 可执行名为 riscv64-unknown-elf-gcc（新版前缀不同于旧工程）。已实际按 rv32imac_zicsr_zifencei、ilp32 编译和链接，验证 ELF32 little-endian/RISC-V/入口 0x80000000，并导出起始 @00000000 的字节镜像。证据：verification/toolchain-20261102-01/report.json。

因此不再等待服务器编译器路径。后续本地编译本项目专用 CPU 测试程序，只上传生成的程序到服务器。上述 probe 仅检查工具链，没有启动/结束代码，不可当 CPU 测试程序上传；实际 MMIO 测试尚待编写与运行。未安装服务器软件，未更改全局 PATH，未接共享 RAM。

2026-11-02 后续：已完成 mmio_smoke/ 下可供 E203 实际执行的最小 MMIO 测试；7 种原生逻辑场景通过，交叉编译和固定结束地址检查通过。镜像为 mmio_smoke/build-01/mmio_smoke.verilog，机器码 876 字节；待用户上传并用既有 verification/soc_compile_01/simv 执行。服务器 MMIO 验证仍未通过确认。不要把之前的 toolchain-probe.verilog 当作此程序。

2026-11-02 18:09:30 用户结果更新：已在真实服务器 E203 运行 kwt-soc/build-01/mmio_smoke，TEST_PASS、x3=1；总周期 6202、有效指令 1066、结束周期 6185，日志位于 verification/soc_compile_01/mmio_run_01/run.log。编译器和最小寄存器 MMIO 链路已验证；接下来仍需 CPU 命令/数据装载/计算结果读取验证。共享 RAM 继续暂缓，SRAM hold 时序问题仍另由综合/STA 检查，不因本次功能通过而消除。

2026-11-02 后续：新增 task_smoke/，完整计算 C 固件已交叉编译（1976字节机器码、bss_end800007d8）。主机同一驱动连接15个生产RTL+本地SRAM合同模型，400块/25344项均通过，5种错误注入均被拒绝；最终证据verification/c-task-driver-20261102-04/report.json。原33项软件与7项接线测试通过。完成独立只读代码审查，无Critical/Important；计划勾选已更新。待用户上传task-build-01/task_smoke.verilog到服务器kwt-soc根目录，运行新的task_run_01。服务器完整CPU计算仍未验证，不能以本地周期推算CPU周期或认定10M-cycle watchdog有余量。

2026-11-02 19:09:07最新结果覆盖上段待办状态：用户已在真实E203运行task_smoke，verification/soc_compile_01/task_run_02/run.log对应截图显示TEST_PASS、x3=1；总周期8120871，有效指令5227662，结束周期8120854，VCS CPU耗时687.720秒。task_run_01已存在而未覆盖，改用02。CPU装载/启动/完整400块25344项检查与ACK/完成轮询这一功能链路已通过；本次包含软件生成与参考比较，不是赛事性能。共享RAM仍暂缓，官方SRAM功能模型通过不消除此前hold问题或替代150MHz STA。证据归档verification/e203-task-server-20261102-01/，来自用户截图，未直接下载/读取服务器完整日志。
