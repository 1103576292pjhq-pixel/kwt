# kwt_load_ctrl：32位操作数装载控制

2026-10-31接口修订：装载数据32位，去掉运行时shift，op/tile/index分别收窄为3/4/13位。[当前独立回归](../../../verification/controls-20261031T223423-e0e67e/README.md)通过；早先三任务内部报告属于旧接口版本，保留作历史证据，不能覆盖本次修改。新生产顶层与ICB见[接口说明](icb-interface.md)，完整总线验证以最新icb-*报告为准。

源码：[kwt_load_ctrl.v](../../../rtl/control/kwt_load_ctrl.v)。公共位宽、命令编码、槽状态及装载错误码见[kwt_control_config.vh](../../../rtl/include/kwt_control_config.vh)。

## 用户思路与确认后的职责

用户提出接收CPU读写请求、地址、写数据，并读写存储、返回结果。讨论后确认：CPU原始总线访问先经过ICB；本模块接收已解析的有序装载命令，负责X/W/bias写入、合法性检查和装载状态。计算读取X/W由供数器负责，CPU读取结果由双结果块与ICB负责。本模块不增加任意X/W读回接口。

当前按功能定义初始化、写X、申请W槽、写W、写bias、提交完整槽、启动任务七类操作。保留单项q用于接受/执行解耦；数据口直接匹配32位ICB，没有旧载荷兼容或PAIR拆分。新生产源列表为rtl/kwt.f，旧tb/system不作为当前入口。

## 端口按连接对象分组

| 端口组 | 位宽 | 职责 |
|---|---|---|
| clk/rst_n | 各1 | 公共时钟、低有效同步复位 |
| cmd_valid/cmd_ready | 各1 | 与上游FIFO握手接受命令 |
| cmd_op/layer_id/task_id | 3/4/32 | 七类操作、自定义会话身份 |
| cmd_tile_id/index/data | 4/13/32 | tile0..15、索引容器0..8191、ICB完整数据字；总线高位在ICB层先检查 |
| begin_valid/ready、begin_task_id/layer_id | 1/1、32/4 | 与任务/会话控制握手重开会话 |
| start_valid/ready | 各1 | 首tile就绪后启动整个矩阵任务，不能直接接计算核块启动口 |
| activate_valid/slot/ready | 各1 | 任务控制将READY槽置ACTIVE |
| release_valid/slot/ready | 各1 | 任务控制在tile最后行组成功publish后释放ACTIVE槽 |
| x_wr_en/addr/wr_data | 4/44/64 | wrapper的X写端口；单条命令只写一个bank |
| w_wr_en/addr/wr_data | 8/64/128 | wrapper的W写端口；只写LOADING槽的一个bank |
| bias_wr_en/slot/addr/data | 1/1/4/32 | 同步写一项bias，signed32/Q28 |
| session_valid/task_id/layer_id | 1/32/4 | 已接受BEGIN的会话身份 |
| task_started/x_ready | 各1 | START已执行、X6336项已装完且无fault |
| slot_state/slot_tile | 4/8 | 低字段为槽0，高字段为槽1；每槽状态2位、tile4位 |
| command_empty/command_done | 各1 | 本地q为空、合法命令执行后单拍；不代表上游FIFO空或MMIO响应 |
| fault/error_code | 1/8 | 错误锁存，直到共同复位 |

BEGIN的layer_id仅作为身份字段保存，不在此限定具体层编号。算术仍由现有核执行固定量化，没有命令shift端口。BEGIN/OPEN/COMMIT/START中不使用的index/data等字段不增加额外约束。

## 命令顺序与槽生命周期

```text
BEGIN → X[0..6335] → OPEN tile0
      → W[0..1023] / bias[0..15] → COMMIT tile0 → START
      → OPEN tile1 → W/bias → COMMIT → 后续tile直到15

槽：FREE → LOADING → READY → ACTIVE → FREE
     OPEN           COMMIT   activate  release（最后块publish后）
```

X输入必须连续递增，完成前不允许OPEN。OPEN按tile0..15递增；START前只允许OPEN0，避免OPEN1等待造成后方START无法执行。每次只有一个LOADING槽，W和bias分别按各自索引递增，两条流可交错。COMMIT检查W1024项和bias16项都齐全。START要求首tile READY且只执行一次。

OPEN遇到两槽均非FREE时，在q中等待，不报错；空槽释放沿之后，下一拍可执行OPEN。activate要求无ACTIVE槽且目标READY；release要求目标ACTIVE。这些都是valid/ready握手，未满足条件时事件源保持请求。不能把单拍脉冲直接送给一个可能未ready的接口。

槽状态只由本模块保存和更新，任务控制通过事件请求改变状态，避免两处分别维护同一个owner。任务控制负责选择正确tile和确认释放条件。本模块不会自行从feed_done或block_done推导整tile已可释放。

## 地址映射与数值检查

X输入index=row×64+k。因此bank=index[7:6]，bank地址={index[12:8],index[5:0]}。例如index=6335对应row98/k63、bank2/address1599，不会写到bank3尾部未用的64项。

W输入index=k×16+c，其中c是tile内列号0..15。因此槽内bank=index[1:0]，bank地址={index[3:2],index[9:4]}。例如index=1023对应k63/c15、bank3/address255。槽号由当前OPEN分配，不由每条W命令随意选择。

X/W先检查完整32位恰好等于低16位符号扩展，通过后存16位；bias的完整32位都有效，直接signed32保存，无冗余高位检查。ICB在形成4位tile/13位index之前检查32位寄存器写入高位为0，本模块进一步检查语义范围及顺序，防止截断覆盖合法位置。

## 代码分段与一拍例子

1. 单项q保存完整命令。E0沿接收后，E0到E1之间做语义检查和写控制译码。
2. 进度寄存器记录X13位、W11位、bias5位及next_tile5位，均能表示完成哨兵。
3. 组合检查分为command_bad与command_wait：错误退休并锁存fault；合法但受阻则保持q。错误优先于等待。
4. 组合写接口在execute成立时才拉高使能。E1沿存储接受写入，计数同沿增加；可以同时接收下一条命令覆盖已退休q。
5. 时序状态处理BEGIN、进度、槽状态及错误。复位或新BEGIN不清SRAM/bias内容，重新从0装载才建立新会话数据有效性。

若E0接收合法X index0，E1写入X bank0/address0并将x_count置1，E1沿后command_done为1。若index错误或数据超范围，E1不产生写入，计数不推进，fault与对应错误码锁存。后续命令停止；不能靠新BEGIN清除fault，必须由上层统一恢复。

## 顶层集成条件

- begin_ready必须由上层在旧计算、结果owner及事务已可安全切换时提供；不能无条件拉高。BEGIN握手同沿初始化其他会话模块。
- X装载先于计算启动；W只有LOADING槽可写，活动槽读、另一槽写。wrapper每bank只有一个共用地址，顶层需按bank合并装载地址和供数地址，不能把两个打包地址总线直接按位或。
- 当前写接口无ready，意味着合法execute沿必须真正写入。上层不能静默拒绝写入；若以后加入仲裁等待，必须连同execute/计数退休条件一起适配。
- fault时上层必须停止任务并协调恢复。slot_state等身份仍可观察，但不能继续作为可启动许可。
- release来自最后行组成功publish，不来自最后MAC、feed_done或CPU ACK。bias仍在量化阶段使用，不得提前覆盖。
- 整机ABORT必须先处理已接受总线响应，再按设计统一复位内部模块；本模块rst_n不承担总线响应排空。

## 检查与待验证

[首版编译记录](../../../verification/load-ctrl-20261031-review/README.md)仅属于当时编译阶段，当前功能证据见本文开头链接。

独立TB已覆盖完整装载及地址账本、数值边界和非法高位、重复/跳号/越界索引、身份错误、非法COMMIT/START、槽等待与保护、q快照、复位和新会话。联合TB核对实际写入后计算结果；生产ICB/FIFO及官方宏仍需补验。
