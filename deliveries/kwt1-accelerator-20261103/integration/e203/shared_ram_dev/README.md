# 临时共享 RAM（开发功能模型）

本目录是单独的开发组件，不修改独立加速器生产 RTL 或其 `rtl/kwt.f`，也没有自动修改服务器上的 SoC 顶层。当前服务器已通过的 add 基线保持原状。

## 文件与原理

| 文件 | 职责 | 综合用途 |
|---|---|---|
| rtl/kwt_shared_ram_icb.v | 可综合 ICB 控制器：窗口译码、一笔在途、等待同步存储响应、保持返回数据直到响应退休 | 可单独评估控制器；不包含存储阵列 |
| sim/kwt_shared_ram_sim.v | 控制器加 131072×32 位行为数组，按字节写入，复位保留已写数据 | 仅仿真，禁止作为正式 SRAM 综合输入 |
| tb/tb_shared_ram_icb.v | 通过真实 ICB 握手驱动测试，不直接替代加速器计算 | 仅仿真 |
| sim.f | 上述三个文件，供组件功能仿真使用 | 不用于综合 |
| controller_only.f | 仅列控制器，不列仿真数组或 TB | 不是完整共享 SRAM 或完整 SoC 的综合工程 |

主生产清单仍是项目原来的 rtl/kwt.f，15 个生产 RTL 文件未改。队友综合独立加速器时继续用该清单。不得递归收集项目所有 .v 文件作为综合输入。模型在 SYNTHESIS 宏下会因保护头文件 ERROR_SHARED_RAM_MODEL_IS_SIMULATION_ONLY.vh 不存在而明确报错；文件清单隔离仍是主要措施。

完整 SoC 的面积、功耗和时序仍需正式共享 SRAM 库和平台实现，不能用本行为模型声称通过。正式宏替换时需要复核延迟、接口、复位与仲裁，接口隔离不能保证完全没有适配改动。

## 临时约定

- 容量：512 KiB = 524288 字节 = 131072 个 32 位字。
- 本次开发暂定地址：0xa0000000～0xa007ffff，**不是赛方确认地址**。BASE_ADDR 必须按 512 KiB 对齐；实际服务器 SysMem 路由及 CPU 访问尚待验证。
- ICB 为 32 位数据、4 位字节掩码。CPU LSU 负责数据通路摆放和读字节选择；RAM 根据地址定位包含该字节的完整 32 位字，不拒绝 sb/sh 使用的低位字节地址。
- 单请求在途；同步存储后端可暂停接受请求，但必须在请求接受后的周期或更晚给响应，不支持同周期零延迟返回。响应可被 CPU 背压，保持数据和错误标志。
- 越界返回 err=1、rdata=0，且不访问后端。零写掩码为无内容变化的成功访问。
- 控制复位取消未退休响应，不清 RAM；未写入内容为未知值。本模型没有加载端第二接口或仲裁，也不自动预加载任何参数。
- 这是功能开发延迟，不能当官方带搬运的性能测试环境。

## 当前验证证据

本地 WSL Icarus：3 项测试通过。总线动态测试输出：

```text
PASS SHARED_RAM_ICB requests=146 responses=145 holds=259 errors=3 bytes=524288 resets=1
```

3 次 errors 是主动测试的越界访问；1 笔响应被测试中的硬复位故意取消，因此 requests 比 responses 多 1。覆盖首尾地址、多个远距离地址、byte/halfword 掩码、零掩码、非法地址无副作用、响应背压及复位后内容保留。另检查 SYNTHESIS 误用会失败、生产加速器文件清单未引入共享 RAM。

尚未验证：实际 E203 读写本 RAM、CPU 经 RAM 搬运加速器数据、真实加载环境和最终宏映射。

## 分层验证顺序

CPU 程序不需要等待共享 SRAM 接好。已有 ITCM 可以存放程序，少量数据可用 ITCM/DTCM 或由程序生成，先通过 ICB 测试加速器寄存器、启动和结果；随后再接共享 RAM 验证装载、搬运和写回。当前交叉编译器仍待平台确认安装路径。

服务器上传/解压后先做组件仿真，使用新目录保存输出，不覆盖任何已通过的测试：

```text
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
mkdir -p verification/shared_ram_01
vcs -full64 -sverilog -timescale=1ns/1ps -top tb_shared_ram_icb -f shared_ram_dev/sim.f -Mdir=verification/shared_ram_01/csrc -o verification/shared_ram_01/simv -l verification/shared_ram_01/compile.log
./verification/shared_ram_01/simv -l verification/shared_ram_01/run.log
```

此处组件模型不需要官方宏库，且没有编译或运行 CPU。
