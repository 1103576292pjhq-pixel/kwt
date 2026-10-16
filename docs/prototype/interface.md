# FFN1 公开接口

所有命令在 `clk` 上升沿采样；`rst_n` 为异步低有效复位。默认 M=99、N=256、K 固定为64；小 M/N 只用于快速协议测试。没有 E203 MMIO 地址约定。

## 任务装载

| 端口 | 方向/宽度 | 含义 |
|---|---|---|
| load_begin | 输入1 | IDLE 脉冲，清装载计数、DONE 与有效状态 |
| load_valid / load_ready | 输入1 / 输出1 | 提交一个装载请求 / 当前允许检查请求 |
| load_kind | 输入2 | 0=X，1=W_pack，2=b，3非法 |
| load_addr | 输入32 | 当前银行从0连续递增的字地址 |
| load_data | 输入 signed48 | X/W 必须是正确符号扩展的 signed16；b 使用完整 signed48 |
| loaded | 输出1 | 三个银行都已完整装载，允许 START |
| start / shift | 输入1 / 输入6 | START 脉冲采样当前合法 shift=0..47 |
| command_error | 输出1 | 当前命令被拒绝时的单周期脉冲 |

调用顺序：复位释放 → load_begin 一拍 → 按银行顺序写足 X/W/b → 确认 loaded → start 一拍。每个银行自己的地址必须连续递增；三个银行可交错装载。load_ready 表示可检查请求，非法银行、跳号、重复、超长或不合法的 signed16 数据仍会返回 command_error，不增加计数。观察错误脉冲后修正当前请求即可。

地址映射：X 的 `load_addr=m*64+k`；W 的 `load_addr=n*64+k`，数据为数学 W[k,n]；b 的地址为 n。X/W/b 数量分别为 M×64、N×64、N。没有 load_end，最后一个必需字接受后 loaded 自动有效。

START 只在 IDLE、完整装载且 shift 合法时接受；与 load_begin/load_valid 同拍则拒绝。接受后 loaded 清除，本任务数据锁定。下一任务需要新的 load_begin 和完整装载。运行及等待行消费期间，装载和重复 START 均拒绝。load_begin、start、row_ack 均按单周期命令使用。

## 行读取与确认

| 端口 | 方向/宽度 | 含义 |
|---|---|---|
| busy | 输出1 | 计算或等待行消费中 |
| row_ready / row_index | 输出1 / 输出32 | 缓冲区完整有效及其行号0..M−1 |
| row_rd_en / row_rd_addr | 输入1 / 输入32 | 读取当前行的一列，地址0..N−1 |
| row_rd_valid | 输出1 | 对应本次同步读取的结果有效 |
| row_rd_data | 输出 signed32 | RNE 与饱和后的输出 |
| row_rd_overflow | 输出1 | 偏置相加导致 raw48 饱和 |
| row_rd_saturated | 输出1 | 最后输出到 signed32 时饱和 |
| row_ack / row_ack_index | 输入1 / 输入32 | 确认消费指定当前行 |
| done | 输出1 | 最后一行被正确 ACK，保持到新装载或复位 |

在 ROW_READY 时提交 row_rd_en，紧随该上升沿、非阻塞更新完成后，row_rd_valid 与读取数据有效。可连续每拍读取不同列，也可停顿和重复读取；row_rd_data 本身保持最后一次同步读值，必须按 row_rd_valid 判断。

只有 row_ack_index 等于当前 row_index 才消费；错误行号、计算期间 ACK、消费后的重复 ACK 均报错。有效 ACK 与读取同拍时，ACK 优先，读取被拒绝并返回 command_error；上层应先取完数据，再单独 ACK。ACK 不检查软件是否真的读完所有列，消费责任属于调用方。

所有行等待允许任意长停顿；测试为了识别死锁设了计算超时和有限消费者等待，这不是硬件对 ACK 的周期上限。复位在计算中、ROW_READY 或 DONE 时都中止任务，清除全部公开有效标记；不逐字清 RAM，必须重载。

## 同步流水

| 状态 | 本拍处理 | 后继 |
|---|---|---|
| IDLE | 校验装载或 START | B_REQ |
| B_REQ | 提交 b[n] 同步读 | DOT_START |
| DOT_START | 向 DOT64 提交 bias/shift | PRIME |
| PRIME | 提交 X[m,0]、W_pack[n,0] 读 | FEED |
| FEED | 消费当前项，同时预取下一项 | 64 次接受后 RESULT |
| RESULT | 等待并写当前 n 的结果和两个标记 | 下一列 B_REQ 或 ROW_WAIT |
| ROW_WAIT | 只读当前行，等待匹配 ACK | 下一行 B_REQ 或 IDLE/DONE |

同步 RAM 是单端口读写分时 wrapper，数据寄存器不复位。所有大数组只通过上升沿读取，公开测试未层次写内存、force 数据或用 Python 结果替代计算。
