# E203 基础启动验证

本批完成公开 E203 的可复用 CPU 外壳、freestanding 启动和 512 KiB 同步 ICB 共享 RAM。完整入口实际退出码 0；最终结果在 `result.json`，带输入和产物 SHA256 的交接在 `../../../work/e203_boot_handoff.json`。

| 检查 | 真实结果 |
|---|---|
| 原版 E203 `rv32ui/add.S` + 原版 `tb_top` | PASS，25,798 行为周期，原版 x3 判据值 1 |
| 自建 C 正常启动 | PASS，5,695 外部周期，CPU `mcycle=1326`，共享写 6 笔、读 2 笔 |
| 自建 C 非法指令异常 | PASS，5,701 外部周期，`mcause=2`、`mepc=0x80000218` |
| 独立共享 RAM | 12 笔检查 PASS，含同步读、5 周期响应反压、byte mask、末字、越界、复位撤销响应并保留内存 |
| 新共享 RAM Verilator 检查 | `--lint-only -Wall`，无 warning，退出码 0 |
| 架构与 ABI | `ELF32`、入口 `0x80000000`、RVC、soft-float、RV32IMAC + zicsr/zifencei，机器读取 ELF 属性验证 |
| 固件真实指令 | 反汇编包含 AMO、MUL、DIVU、REMU、MTVEC、MCYCLE；CPU 执行检查对应结果 |
| 官方来源保护 | 两份官方源共 1,459 个文件/链接，执行前后逐项校验完全一致 |
| 重复运行 | 初次与最终运行的 `.bin`、逐字节 hex、两类 Verilog image 共 4 份哈希一致，正常与 trap 的周期一致 |
| 交接回读 | Windows 独立进程核对 10 份实现输入、8 份产物与最终结果哈希全部通过 |

固件 564 字节。`boot-smoke.bin` SHA256 为 `5b2e6d5e8b0a67144d91b1bf4fe7b15d48c300faba1b8afbb1ca955227e3aaab`。ELF/map 含编译临时对象文件名，因此重复验收比较可执行 image，不声称 ELF/map 哈希跨构建恒定。

自建启动不使用固定 PC、x3 或 CPU 寄存器注入判 PASS；C 执行数据复制、BSS 清零、栈、全局变量、AMO、乘除、字节写和共享 RAM 回读，最终状态由 CPU 写邮箱。测试台只初始化固件、启动数据毒值和模式输入。所有数字均为行为仿真，不能换算成已通过的芯片频率或 PPA。

两轮自审已检查规格与实现：① ROM/ITCM/DTCM 均复用上游，系统总线真实导出；② RAM 命令只接受一次，反压时响应保持，非法地址不写内存；③ main 返回和异常均写明确邮箱；④ 错误、缺 PASS、hash 变化会让入口失败；⑤ 固定源码、旧 FFN1 核心和数值证据没有改动。

真实问题及恢复记录保留：`red-build-upstream-add.log` 是缺 zifencei；`red-simulate-upstream-add-unicode.log` 是 Icarus packed-string UTF-8 路径损坏；`red-compile-mixed-timescale.log` 是上游 `#1` 与 ns 测试台混用时标。恢复办法分别为显式 ISA 扩展、ASCII 相对 image 文件名、在 vendor 前读 `timescale.v`，均未编辑上游代码。

连接与启动约定见 `../../../soc/e203_common/README.md`。本批没有接 FFN1 最终系统、确认比赛定制平台、构建完整 SDK、执行综合或证明 150 MHz/面积/功耗，也没有作比赛全部七项完成结论。
