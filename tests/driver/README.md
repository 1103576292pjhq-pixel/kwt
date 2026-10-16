# FFN1 C 驱动：调用与验收

`sw/ffn1_driver.c` 只完成输入搬运、控制和结果回读；乘法、累加、舍入和饱和仍由 RTL 执行。驱动仅依赖 C11 的 `<stdint.h>`、`<stddef.h>`，没有 libc、堆或 SDK/NMSIS 依赖。

## 调用约束

调用 `kwt1_run(io,m,n,x,w_pack,bias,shift,y,flags,poll_limit)`。`m`、`n` 必须分别等于硬件 `GEOMETRY` 低、高 16 位，且非零；内积长度固定 64。数组按头文件约定由调用者分配并在运行期间保持有效，输入和输出不得重叠：

| 数组 | 元素类型与数量 | 索引 |
|---|---|---|
| x | int16_t[m*64] | x[row*64+k] |
| w_pack | int16_t[n*64] | w_pack[column*64+k] |
| bias | int64_t[n]，值须在 signed48 范围 | bias[column] |
| y | int32_t[m*n] | y[row*n+column] |
| flags | 可空 uint8_t[m*n] | bit0 累加溢出、bit1 输出饱和、bit2 有效 |

回调接收**相对基址的偏移**，由平台适配层加 `KWT1_MMIO_BASE=0x11000000`。每次回调必须消费本次总线响应后返回，0 表示成功，非零表示失败。E203 适配层使用对齐的 volatile 32 位读写，并使用适当 RISC-V `fence iorw,iorw` 保证 MMIO 与普通存储的顺序；测试回调提供可控的寄存器事务响应。

驱动次序：参数与 bias48 检查 → ID/GEOMETRY/K/空闲/历史错误检查 → load_begin → SHIFT → 连续装载 X/W/b → 有界等待 loaded → START → 有界等待每行 row_ready → 核对 row_index → 每列写 ROW_ADDR、读 ROW_DATA、读有效 ROW_FLAGS → 写入整行输出 → ACK 当前行 → 最终有界等待 DONE 与 ERROR=0。

X/W 写入正确的 32 位符号扩展。负 bias 先转换成 `uint64_t`，再拆成新 LO32 和 HI16，每次明确提交，不依赖上一次暂存值。ROW_DATA 的负结果通过可移植的算术转换恢复 `int32_t`，不依赖溢出或 unsigned→signed 超范围转换。

`poll_limit` 是每次 loaded/row/done 等待允许的 STATUS 读取次数，必须大于零；它不代表 RTL 周期数，也不能中断一个本身不返回的回调。驱动不负责并发仲裁和复位恢复。失败时可能已有部分输出，当前任务也可能仍 busy；调用者应记录错误并显式恢复，不能自动重试 ACK 或清除错误掩盖问题。

| 返回值 | 意义 |
|---|---|
| KWT1_OK | 整个任务完成，最终无错误 |
| KWT1_ERR_ARGUMENT | 空指针、尺寸/shift/poll_limit 非法、bias 超范围或 RV32 输出容量溢出 |
| KWT1_ERR_IO | 任一读写回调失败，不重试、不吞错 |
| KWT1_ERR_ID / GEOMETRY | IP 标识、矩阵几何或 K 不匹配 |
| KWT1_ERR_BUSY | 进入驱动时上一个任务仍 busy |
| KWT1_ERR_CORE | sticky error 或核心错误状态 |
| KWT1_ERR_TIMEOUT | 某个等待耗尽轮询额度 |
| KWT1_ERR_PROTOCOL | 状态组合、行号或结果有效标志违约 |

## 实际验证入口

从任何目录执行 `bash /绝对路径/scripts/test_driver.sh`。脚本先撤销旧 PASS，再进行 host GCC 严格警告/UBSan、总线顺序测试、八类故障注入、真实 RV32IMAC/ILP32 freestanding 编译与未定义符号检查。任一步失败均非零退出，`result.json` 写 FAIL，不保留成功标记。

host mock 是按协议编写的严格寄存器访问记录，独立给出结果响应，没有软件矩阵代算：

- signed16 全范围代表值，signed48 最小值、−1、最大值的独立 LO/HI 常量；超范围正负 bias 在首次 I/O 前拒绝。
- 逐事务核对地址、读写方向、写入值与次数；每个成功路径 I/O 都逐一注入错误，要求立即退出且不继续读写。
- 三类等待超时；loaded 前 busy、提前 DONE、错误行号、无效/保留位 flags、末行后多余 row_ready、DONE+busy、历史和最终 sticky 错误。
- 在 mock 接收 ACK 的瞬间检查整行 Y/flags 已经存好；flags 可空；1×64×1、shift=0、连续两个任务（第二次初始 DONE=1）。
- 故意破坏符号扩展、bias 高字、ACK 行号、flags 校验、I/O 错误传播、负结果转换、轮询上界及最终错误检查；八种变异必须全部被测试拒绝。

报告位于 `reports/system/driver/`。这些证据证明 C 驱动协议行为和目标架构可编译，**不替代真实 E203 执行或 RTL 仿真**；系统级闭环另行验收。
