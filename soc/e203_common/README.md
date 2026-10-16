# E203 公共启动外壳

`e203_cpu_shell.sv` 直接实例化固定官方 `e203_subsys_top`，保留官方 CPU、ROM、64 KiB ITCM、64 KiB DTCM、片内外设和调试模块。它导出真实 `sysper_icb_*` 与 `sysmem_icb_*`，供加速器桥和共享 SRAM 连接；没有重写 CPU，也没有使用原 SoC 顶层的零数据回环。

## 连接契约

- 输入 `clk`、`lfclk`、低有效 `rst_n`。例程使用 4 ns 主时钟、66 ns 低速时钟，这只是行为仿真，不能据此声明时序收敛。
- `bus_clk=clk`，`bus_rst_n=rst_n`。官方默认 PLL bypass 为 1，本原型软件必须保持默认 clock/PMU 设置；若要启用动态时钟、电源管理或复位域控制，需要先设计正式域间与复位连接。
- 两个 ICB 主端口均使用：`cmd_valid/ready`、32 位 `cmd_addr/wdata`、`cmd_read`、4 位 `cmd_wmask`、`rsp_valid/ready`、32 位 `rsp_rdata`、`rsp_err`。前缀分别为 `sysper_icb_`、`sysmem_icb_`。
- 未用 FIO 通路以单 outstanding、保持反压的错误响应结束，不能伪装成功。
- `icb_shared_ram.sv` 默认基址 `0xa0000000`、512 KiB、32 位宽。同步读取，命令在时钟沿接受，响应在该沿后有效。响应未消费前不收下一命令。支持 byte mask；字节/半字访存返回所在完整字，由 CPU 选择字节。非法地址报错。复位清事务状态，不清整块 RAM。

## 固件入口与内存

`sw/e203/start.S` 从 `0x80000000` 启动，设置 16 字节对齐栈顶 `0x90010000`、`gp`、直接模式 `mtvec`，关中断，把 ITCM 中 `.data` 初值复制到 DTCM，清 `.bss`，调用 `int main(void)`。`link.ld` 为 DTCM 保留至少 4 KiB 栈余量，不依赖 SDK 或 libc。主程序返回统一写完成邮箱；异常入口直接写 CSR 和错误码，不依赖尚未建立的栈。

共享 SRAM 起始邮箱必须保留：

| 偏移 | 内容 |
|---|---|
| `0x00` | 最后写入的终态魔数：`BOOT=0x424f4f54`，`TRAP=0x54524150` |
| `0x04` | main 返回值；异常为 `0xffffffff` |
| `0x08` | 异常 `mcause` |
| `0x0c` | 异常 `mepc` |
| `0x10` | 终态前读取的低 32 位 `mcycle` |
| `0x20` | 本启动 smoke 专用模式输入；0 正常、1 执行非法指令 |
| `0x60`、`0x64` | 本启动 smoke 的共享内存、栈检查结果 |

正式矩阵输入、结果区域从 `0x100` 以后另行分配，不能覆盖邮箱。固件只需提供 `main`，不要再提供 `_start`。生产主程序的 ICB 驱动由系统集成层提供，本目录不包含矩阵软件求解器。

## 复现与已解决的启动问题

在 WSL 项目任意目录运行 `bash /绝对项目路径/scripts/run_e203_upstream_smoke.sh`。入口先校验全部两份官方源码 manifest，任何 hash 或 symlink 目标变化都会失败；运行后再次复核。

1. GCC 13 将 CSR 与 `fence.i` 拆成独立 ISA 扩展，使用 `-march=rv32imac_zicsr_zifencei -mabi=ilp32`。ELF header、ISA attributes 和反汇编单独保存；没有链接 64 位库。
2. Icarus 对 packed-string 文件名中的 UTF-8 有问题。OS 工作区路径仍可含中文和长破折号，仿真在报告目录执行，只传 ASCII 相对固件文件名。
3. 上游通用触发器含 `#1` 延迟但未声明 timescale。所有系统编译先读 `dv/e203_boot/timescale.v`，统一 `1ns/1ps`，再读 vendor；上游文件保持原哈希。
4. 官方 ISA 镜像由 ELF 转 Verilog 时地址减 `0x80000000`，与上游 Makefile 的地址替换相同。自建固件由二进制导出从零开始的逐字节 hex。

原版 `tb_top` 的 PC/x3 判据只用于上游 add 自测。自建 `tb_e203_boot` 仅按 CPU 实际写入的终态邮箱、退出码、异常 CSR 和共享结果判断，完全不靠固定 PC 或 x3。测试台只初始化固件、DTCM 启动毒值和输入模式，不写 CPU 寄存器或加速器状态。

真实命令、ELF、map、hex、反汇编、失败恢复日志与结果都放在 `reports/system/upstream-smoke/`。这仅是公开平台初稿，尚未证明为比赛定制 E203 工程，也没有综合、PPA、150 MHz 或比赛 600 样本结论。
