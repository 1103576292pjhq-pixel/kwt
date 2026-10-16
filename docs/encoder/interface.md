# Encoder 外部契约

固定参数 M=99、D=64、H=256；验证可缩小，score 缩放仍为 0.125。所有地址均为 32 位 word 索引。权重顺序与 work/formal_seven_design.md 一致，共 49792 word。

core 单事务 req_valid/req_ready、req_op[2:0]、req_addr[31:0]、req_data[31:0]；rsp_valid/rsp_ready、rsp_data、rsp_error。请求只在握手时执行一次，响应阻塞保持；同步低有效复位撤销在途操作与装载有效性，不清 RAM。busy 时所有命令拒绝且不打断计算。

| op | 操作 | 前置条件与结果 |
|---|---|---|
| 0 | BEGIN_JOB | 空闲；层号归零，清装载计数与完成状态，输入银行归零 |
| 1 | LOAD_X | BEGIN_JOB 或 RELOAD 后、尚未启动；addr 必须等于连续输入计数，小于 M×D |
| 2 | LOAD_W | addr 必须等于连续权重计数，小于 weight_words |
| 3 | START | 输入和本层权重全部有效、尚未完成；data 必须等于当前层号 0..11 |
| 4 | READ_Y | 本层 done；addr<M×D；同步读后返回完整 FP32 word |
| 5 | SWAP | done 且层号<11；翻转 X/Y 银行、递增层号、清本层权重计数和 done，保留有效激活 |
| 6 | ATTENTION | 同 START 装载条件、仅层号0；只完成 attention 并写满 M×D 后 done；READ_Y 读 attention，禁止 SWAP/RELOAD，不置 job_done |
| 7 | RELOAD | 完整层 done 且层号<11；递增层号，清输入与权重计数；CPU必须读回并重新装载完整 X |

done 是本层状态，job_done 仅第 11 层完成为真。拒绝命令不改变银行、计数或结果。cycles 是本层计算周期，flags 为累计 IEEE flags。计算错误或非有限输出置 fault 并终止计算，直到 BEGIN_JOB 或复位才能恢复。所有输出 M×D 均写完才置 done。

ICB 窗口 0x11010000，单 outstanding；32 位对齐、写掩码1111。非法地址、类型、数值返回本事务 error，sticky error 不污染后续合法响应。

| 偏移 | 名称 | 访问和意义 |
|---|---|---|
|00|ID|RO，0x454e4331|
|04|STATUS|RO，busy bit0、done bit1、job_done bit2、sticky_error bit3|
|08|COMMAND|WO，值0 BEGIN_JOB、3 START、5 SWAP、6 ATTENTION、7 RELOAD|
|0c|ERROR|RW1C，bit0 非法访问、bit1 核心拒绝、bit2 计算故障；活动 fault 持续置位|
|10|ADDR|RW，LOAD/READ word 地址|
|14|DATA|WO，LOAD_X；每次成功后 ADDR 自动递增|
|18|WEIGHT|WO，LOAD_W；每次成功后 ADDR 自动递增|
|1c|OUTPUT|RO，READ_Y；每次成功后 ADDR 自动递增|
|20|LAYER|RO，当前层号|
|24|X_COUNT|RO|
|28|W_COUNT|RO|
|2c|CYCLES_LO|RO|
|30|CYCLES_HI|RO|
|34|FLAGS|RO|
|38|GEOMETRY|RO，M[31:16]、D[15:0]|
|3c|H|RO|
|40|WEIGHT_WORDS|RO|
|44|WAIT_DONE|RO；busy 时持有该总线事务至计算完成或 fault，最多40000001拍；返回 STATUS 格式，超时返回事务错误。普通 STATUS 仍可即时观察|

START 使用当前 LAYER 值；底层 core 另检查 data。ADDR 在空闲时可写；busy 时拒绝配置、装载和命令。STATUS/计数读允许 busy 时观察。

SRAM 布局：共享 512KiB 基址 0xa0000000；0x0000 邮箱，0x1000 输入，0x8000 当前层权重，0x40000 完整输出。固件先发布 requested_layer，再等 host 的 ready_layer，随后通过生产驱动将公开 SRAM 权重搬到 MMIO。host 不驱动 CPU 总线、不写内部 encoder RAM。诊断策略0每层读回；已批准比较的策略1只写回最终结果、层间 SWAP，策略2每层读回共享 SRAM 并 RELOAD。两者被动监视器均验证每层全部输出，host每word占实际一拍，计时从首个MMIO到最后完整输出写回。放行凭据为 work/MASTER_RELEASE_encoder_reuse.md。
