# 512KiB共享SRAM：一次上传包

**当前状态更新：**服务器活动目录为`shared_sram_bundle_01/kwt-shared-sram-v2`，官方单宏及64宏组件、E203共享访存和真实case3共享链路均已有通过凭据。下文保留打包时的设计/命令说明；VCS负向退出码兼容已在v2修复，新安装应使用交付`server-packages/kwt-shared-sram-v2.tar.gz`。当前目录和综合入口见[共享与SoC交接](../../../docs/handoff/shared-sram-and-soc-20261103.md)。维护源码README可能较服务器封存包新，不改写封存包身份。

2026-11-03。本包把单颗4096宏、64宏拼接、ICB封装与测试、E203接线准备工具、CPU内存测试源码/预编译镜像放在一起，避免逐文件补传。现有独立加速器RTL、数值和rtl/kwt.f不改。官方商业模型继续只读引用服务器，不打入包中。

## 文件及职责

| 文件 | 做什么 |
|---|---|
| run_all.py | 顺序执行官方单宏验证、64宏ICB验证及故意改错黄金的检错；有一步失败即停止 |
| single/run_sram4096_smoke.py | 已准备的单颗宏脚本原样封装，不必单独上传 |
| rtl/kwt_shared_ram_icb.v | 原共享RAM原型控制器的字节一致副本；地址译码、单笔在途、返回保持 |
| rtl/kwt_shared_sram_array.v | 32组×每组两颗4096×16；组/行锁存、四字节掩码映射 |
| rtl/kwt_shared_sram.v | 可综合共享SRAM的ICB顶层 |
| rtl/shared_sram.f | 仅3个生产共享模块，不包含TB或合同替身；从包根运行时使用 |
| tb/tb_shared_sram.v | 全容量、所有组、全部字节掩码、背压、越界及复位验证 |
| prepare_shared_soc.py | 从已有kwt_soc_top生成新kwt_shared_soc_top；先preview，校验后可apply |
| firmware/shared_ram_smoke.c | CPU访问32组首尾、逐字节/半字写入及最后一个字 |
| firmware/start.S、link.ld | 复用已验证的ITCM启动/异常/结束协议 |
| firmware/build-01/shared_ram_smoke.verilog | 本地已交叉编译的CPU镜像，不需要在服务器安装编译器 |
| firmware/build-01/build-report.json | 编译器、ABI、入口、结束PC、内存边界和镜像哈希；不是CPU执行PASS |
| package-sha256.json | 封存文件哈希，运行前后检查；不要改包内源码后继续沿用旧PASS |

## 拼接与时序原理

512KiB=131072个32位字。字地址[16:12]选择32组，[11:0]选择组内4096行；每组一颗低16位宏加一颗高16位宏，共64颗。逻辑读返回为{高半字,低半字}。ICB字节写使能1表示写，对应宏WEN逐位低有效，因此每个字节使能先复制8位再取反。

接口控制器接受一笔请求后等待宏返回，再保存ICB响应直到主机接收。阵列保存已接受请求的组与行，不用等待期间变化的当前总线地址选择返回。读时保持所选宏到接收沿，避免依赖待机Q保持；可能产生同地址重复宏读，后续功耗/访问统计必须纳入，当前不声称最优性能。写不重复发出。

控制复位取消待处理/未退休响应，但不清SRAM。TB覆盖响应已有效时复位，以及WAIT_MEM中读/写两种复位；已接受的宏写入应保留。还验证合法主机在背压期间保持第二笔命令，前一响应退休后才接受，不丢请求。

开发窗口0xa0000000～0xa007ffff，不是官方分配。它与原ITCM80000000、DTCM90000000分开，最终须核对平台正式地址图。共享512KiB与加速器内部20KiB是不同存储；独立加速器综合仍用原rtl/kwt.f。共享存储综合另用本包清单与真实宏库，不能用仿真数组代替。指南对复用共享512KB面积要求单列，不能漏计实际功耗。

本轮只读单ICB主接口。CPU与未来加载主机如何仲裁/分时仍须按平台访问接口落实；当前没有悄悄增加DMA或并行加载口，不把组件测试当成正式数据加载环境已完成。

## 一次上传和组件验证

只上传kwt-shared-sram.tar.gz到FileZilla远端/e203-integration/kwt-soc/，无需再传上一轮单独的py。

在服务器执行整段，新目录已存在时改为新的编号，不删除旧运行：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
mkdir shared_sram_bundle_01 && \
tar -xzf kwt-shared-sram.tar.gz -C shared_sram_bundle_01 && \
cd shared_sram_bundle_01/kwt-shared-sram && \
python3 run_all.py
```

脚本输出STEP1_SINGLE_MACRO→STEP1_PASS→STEP2_64_MACRO_FULL_CAPACITY_ICB→PASS SHARED_SRAM_OFFICIAL。单宏或阵列不通过即停止。官方模型在/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP4096X16/verilog的_rtl.v和.v，使用ARM_UD_MODEL快速功能模式，20ns测试时钟、EMA2/EMAW0待测候选。可用--sram-root/--ema/--emaw显式指定；改配置使用新--output目录并保留依据，不自动扫到通过。

结果保存在本包official-run-01/。report.json、single.log、compile-shared.log、run-shared.log、negative-shared.log保留命令/退出码/哈希。单宏的细分结果在official-run-01/single/run/。负向日志中的故意FAIL应被runner捕获，最终状态需同时正向通过和负向检出。

全容量统计为requests656397、responses656394、read_checks393735、holds1264、errors3、canceled3、mask_cases512。3次errors是主动越界，3笔响应被主动复位取消，并非丢事务；请求数应恰多3。每个实际输出与独立黄金检查，X也报错。单宏另有reads12336等自己的统计，不混同。

## 同一包内后续E203接线步骤

先让组件验证PASS，再执行接线预览。以下是后续按步骤使用的工具，不是run_all.py自动执行的变更：

```sh
python3 prepare_shared_soc.py preview --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

生成kwt-soc/verification/shared_sram_wiring_01/下的before/after、wiring.diff和shared_sram_additions.f。此时原RTL/TB未修改。新顶层接已有kwt_bus_clk和kwt_bus_rst_n，SysPer仍连原加速器，SysMem接共享RAM；旧kwt_soc_top保留。模型路径优先取本次官方PASS报告，防止组件与SoC编译使用不同库。

核对预览后再运行apply，工具检查输入、候选、追加清单、整包和官方模型哈希，并要求匹配的官方组件PASS，才新增顶层并切换TB类型，u_e203_soc_top实例名不变：

```sh
python3 prepare_shared_soc.py apply --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

已有新顶层/预览拒绝覆盖；更换预览用--stage新路径。组件使用其他输出目录时传--validation-run，使用其他配置时preview传相同--ema/--emaw。apply保留备份，但不是操作系统级多文件原子事务；失败时检查日志和before备份，不盲目重跑。

随后须重新编译整个SoC：采用服务器原本成功的VCS参数和文件清单，追加shared_sram_additions.f。该清单包含新顶层、3份共享RTL和两份4096官方模型，不能把同一文件重复加入。保留现有E203/加速器/1024与128宏的原编译输入。旧simv中没有共享SRAM，不能拿它运行新CPU镜像宣称已接入。

本包不假定服务器原SoC编译清单的文件名或脚本位置；这一步需要核对服务器实际成功命令后组合，所需新增源码和镜像已经全在包内，不需要再次补传代码。

新SoC仿真器生成后，使用本包firmware/build-01/shared_ram_smoke作为TESTCASE（不带.verilog），x3=1为成功，0x61～0x64为具体访存失败，0xe0为CPU异常。启动0x80000000、结束循环0x80000086，至少留1KiB栈。只验证真实CPU共享访存，不代表CPU真实模型任务或完整结果写回已完成。

## 当前验证身份

本地Icarus仅使用独立合同宏替身，替身主动将待机Q变X以检查读返回保持。合同替身没有打进生产清单或官方runner。源码与测试准备完成不等于官方宏、真实CPU或STA通过；官方结果待用户运行后归档。

服务器组件功能即使PASS，也不证明150MHz建立保持、历史hold修复、面积、功耗/能耗或赛事正式600/12任务验收。正式加载仍需通过实际平台接口搬入参数，由CPU搬运加速器并完整写回共享存储，从装载开始至最后写回结束计时。
