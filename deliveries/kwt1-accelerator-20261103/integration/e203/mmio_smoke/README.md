# E203 实际 CPU 的加速器寄存器测试

当前阶段：本地 C 检查逻辑和交叉编译已通过。用户随后上传整个 build-01 目录，在服务器真实 E203 运行该镜像，截图显示 **TEST_PASS、x3=1**。没有修改任何生产 RTL，也没有接共享 SRAM。此测试不启动加速器计算，不证明完整驱动或计算任务通过。

## 为什么这样测

现成 add 镜像不访问加速器；本测试让真实 E203 执行 lw/sw，通过 SysPer ICB 访问 0x11000000 的现有加速器接口。程序、常量和少量诊断数据使用 ITCM，栈顶为 0x80001000，不依赖 DTCM 或共享 SRAM。

检查 STATUS=1、ERROR=0；对 TASK、LAYER、TILE、INDEX、DATA、ACK_TASK、ACK_SEQ、ACK_COUNT 八个暂存寄存器写三组合法字段值（全 1、不同模式、全 0）。每组先全写再逐个读回，检查地址别名与相互干扰。合计 28 次读、24 次写。最后配置恢复为零。不写 COMMAND、ACK 或 ABORT。

INDEX/ACK_COUNT 的全 1 仅检查暂存字段的位宽，并未提交装载或释放命令，因此不代表硬件允许对应范围的真实数据索引/结果长度。

## 每个文件做什么

| 文件 | 原理 |
|---|---|
| kwt_mmio.h | 当前工程 ABI 的基址和寄存器偏移；构建时与生产 kwt_icb_config.vh 自动核对 |
| real_io.c | 使用 volatile 的整字 lw/sw 及 fence 访问实际 MMIO；main 调用检查逻辑 |
| register_test.c | 比较状态与三组读回值，失败返回具体代码；诊断字段保存在 ITCM bss |
| start.S | 设置栈、禁止中断、设置异常向量、清 bss、调用 main，把结果写 x3，进入固定地址循环 |
| link.ld | 入口 0x80000000，结束循环 0x80000086，正文从 0x80000100；保证 bss 以下内容不超过 3 KiB，给栈留至少 1 KiB |
| tests/native.c | 在主机检查测试逻辑，包含零响应、异常状态、错误码、坏读回、丢写和地址别名；不模拟 E203 |
| build.py | 使用本地已固定的工具链构建，保留命令、版本、ELF、二进制、反汇编和哈希 |

## 已有检查结果

- 主机测试：PASS MMIO_TEST_LOGIC scenarios=7 valid_reads=28 valid_writes=24。
- 编译：Nuclei 2024.06 GCC 13.1.1；rv32imac_zicsr_zifencei、ilp32，ELF32 小端。
- 机器码 876 字节，bss 结束 0x8000037c，栈顶 0x80001000，使用 ITCM 前 4 KiB 范围。
- 结束地址恰为 0x80000086，该处为 2 字节 c.j 自循环，编码 01 A0。
- 已检查无未解析符号、无 gp-relative 数据访问，镜像字节与 objcopy 导出的二进制一致。
- build-01/build-report.json 保存具体构建命令、输出、源文件和镜像哈希。

实际服务器 ITCM 容量和程序路径仍以运行检查确认；该小程序只要求首 4 KiB ITCM 可用。编译成功与主机逻辑检查都不是 CPU MMIO 已通过的证据。

## 上传与运行

只上传 build-01/mmio_smoke.verilog 到服务器：

`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/`

FileZilla 左侧目录：`D:\嵌赛芯片设计赛道\kwt1-accelerator\integration\e203\mmio_smoke\build-01`

右侧目录：`/e203-integration/kwt-soc/`

使用已编译并通过 add 的 simv，不需要重新编译 RTL。命令中 TESTCASE 不带 .verilog，测试平台会自动追加扩展名。

```text
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
ls -l mmio_smoke.verilog && \
mkdir verification/soc_compile_01/mmio_run_01 && \
cd verification/soc_compile_01/mmio_run_01 && \
../simv +DUMPWAVE=0 +SIM_TOOL=vcs +TESTCASE=/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/mmio_smoke -l run.log
```

成功应出现 TEST_PASS，最终 x3=1。

### 已收到的服务器结果

用户截图（2026-11-02 18:09:30）：实际 TESTCASE 为 kwt-soc/build-01/mmio_smoke，日志目录为 verification/soc_compile_01/mmio_run_01。TEST_PASS，最终 x3=1，总周期 6202，有效指令数 1066，首次到结束地址周期 6185。证据来自用户截图，未独立读取完整服务器日志。总周期包含 CPU 启动和测试结束循环，不是加速器计算性能指标。

由于用户上传整个 build-01，运行命令中的 TESTCASE 必须使用服务器 kwt-soc/build-01/mmio_smoke；前面的直接上传单文件到根目录的命令是另一种放置方式，不能混用路径。

## 失败代码

| x3（十六进制） | 含义 |
|---|---|
| 0x10 / 0x11 | 初始 STATUS / ERROR 不符 |
| 0x20～0x27 | 对应上述八个暂存寄存器的读回不符 |
| 0x40 / 0x41 | 最终 STATUS / ERROR 不符 |
| 0xe0 | 发生 CPU 异常；异常处理把 mcause/mepc/mtval 留在 a1/a2/a3 |

既有 TB 的最终 x3 按十进制显示，例如 0xe0 为 224。
