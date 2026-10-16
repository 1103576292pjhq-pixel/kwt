# Freestanding C 驱动验收报告

本批实现 `sw/ffn1_driver.h/.c`，对接 `work/common_e203_design.md` 的固定 MMIO 契约，不依赖 SDK，不执行软件乘加，不修改原数值或 RTL 基准。调用说明见 `tests/driver/README.md`。

最新完整命令：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/test_driver.sh'
```

实际退出码 **0**；host 输出 **DRIVER_TESTS=1060 FAILURES=0**；变异验证 **DRIVER_MUTATIONS=8 KILLED=8**。GCC 13.3.0 使用 C11、`-Wall -Wextra -Werror -Wpedantic` 与 UndefinedBehaviorSanitizer。实际 RISC-V GCC 13.2.0 已编译 `rv32imac/ilp32` freestanding 对象；`nm -u` 为空，无 libc 或编译器运行时符号依赖。

## 验收覆盖

| 类别 | 实际证据 |
|---|---|
| 成功路径 | 2×64×3 的完整访问顺序、flags 可空、输出 signed32 边界与正负值 |
| 参数 | 空指针/回调、零/超范围几何、shift=48、零轮询限额、bias48 正负越界 |
| 数据搬运 | signed16 最小/最大/−1 等符号扩展；bias48 最小、−1、最大独立预期 LO/HI |
| 失败传播 | 成功路径全部 **1,014 个总线访问点**逐一注入回调失败，要求立即非零返回，不继续访问 |
| 协议 | 错误 ID/几何/K、busy、sticky error、保留状态位、提前 DONE、错误行号、无效/保留 flags、DONE+busy |
| 超时 | loaded、每行 ready、最终 DONE 均耗尽固定轮询次数后退出 |
| ACK 顺序 | mock 收到 ACK 时检查整行 Y/flags 已写入调用方缓冲；禁止半行释放 |
| 连续任务 | 1×64×1、shift=0、两次连续调用，第二次进入时旧 DONE=1 |
| 测试有效性 | 八类可编译逻辑变异全部被拒绝，含负值转换、缺高字、错误 ACK、吞 I/O 错误和多一次轮询 |

先运行编译成功的接口桩（只返回参数错误），实际观察到 **1,058 项测试、2,087 项断言失败，退出码 1**，原始输出保存在 `red.log`。实现后通过，再补充 ACK 可见性和连续小任务，当前共 1,060 项通过；没有把缺文件或编译错误当作 RED 证据。

## 证据文件

- `result.json`：本次状态、用例数、UBSan 与 RV32 编译结果；脚本开始先写 RUNNING，失败写 FAIL。
- `host.log`、`mutations.log`、`mutations.json`：host 与故障注入结果。
- `commands.log`、`tool-versions.log`：实际编译/运行命令、时间与工具版本。
- `hashes.sha256`：驱动、测试、入口脚本与 RV32 对象哈希。
- `ffn1_driver.rv32.o`、`ffn1_driver.rv32.dis`：真实目标架构对象与反汇编。
- `PASS`：全部检查通过后才写入，重新执行前删除，失败不会沿用。

## 结果边界

这里通过的是驱动协议和真实目标架构编译；host mock 不替代 E203 执行或 RTL 仿真。系统级证据由 CPU/桥接集成单独提供。`poll_limit` 只限制 STATUS 轮询，平台回调自身仍须保证返回。失败后已有部分输出和运行中任务可能保留，调用者必须显式记录、复位恢复；驱动不自动清历史错误或重试 ACK。
