# KWT1 新交接架构阅读笔记

日期：2026-10-27。本轮仅阅读和分析，未修改交接包、独立加速器 RTL 或固件，未运行包内仿真、综合或服务器命令。本文中的通过、周期与配置资格均指包内既有记录；本轮只对照源码并复算清单数字。

## 1. 工程身份与主要结论

包根：`D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend`。

当前交付为 V08 / C11 auto 硬件族，推荐 F3 固件，对照 F0 固件。F0/F3 使用同一 RTL。“前端工程”指芯片前端设计和验证交接，并非音频特征提取前端。

本科计算规模仍为 X[99,64] × W[64,256] + bias[256]，每项任务产生 25,344 个输出。十二层是分别更换数据/参数的十二项任务，不是本科核内部自动执行完整十二层 Transformer。

相对用户当前独立加速器，算力及 X/W 基本组织保持相近，重点扩展为 CPU 可调用的系统：32 位 ICB/MMIO、FIFO8、PAIR_NEXT、双结果块、结果描述符/ACK、真实 E203 与 512 KiB 共享 RAM、B/G 模式保护。新增系统收益不能全部归因于新的计算阵列。

## 2. 从输入到完成的通路

1. host/加载环境把 X、W、bias、任务描述符放入共享 RAM。共享 RAM 基址 0xa0000000，容量 512 KiB；不是本科核内部 X/W bank。
2. E203 运行驱动，从共享 RAM 读取数据，以 ICB 的 32 位 MMIO 事务发给本科窗口 0x11000000。当前没有加速器 DMA 主设备，搬运、轮询和结果写回由 CPU 完成。
3. wrapper 把 legacy 命令或打包 pair 放进八项物理命令 FIFO。pair 拆成两个 signed16 标量，依次交给核心单项 q 注册入口。
4. 核心按 BEGIN→X 全量→OPEN→当前 tile 的 W/bias→COMMIT→START 执行；START 只在首 tile 后发一次。计算启动后继续 OPEN/装载/提交后续 tile。
5. X 四 bank、W 两槽共八 bank 提供操作数。读请求标签随 SRAM 延迟流动；返回数据产生 16 个乘积，再累加到四上下文中的目标 4×4。
6. 每个 4 行×16 列块完成全部 K64 后排空最后乘积，申请空结果块；逐项加偏置、RNE 舍入、sat16，填入该结果块，完整后发布。
7. CPU 读描述符和 packed 结果，校验任务/序号/索引/唯一覆盖/last/保留位，再把符号扩展后的 Y32 和 flags8 写回共享 RAM。
8. 每块写回后 fence，再 ACK 释放该结果块。最终还要等本地和共享通道在途响应排空，由 guard 校验 token 与完成状态并 COMPLETE。

## 3. 分块与计算原理

固定 PM4、PN4、CTX4，总共 16 条 signed16×signed16 乘法通路。PM4 同时处理四行，PN4 每拍处理四列，CTX4 轮转四个列组，使四组 4×4 累加状态合起来保存 4×16 个输出。CTX4 没有使乘法器变为 64 个。

固定一个 k，四拍分别处理 g0:c0..3、g1:c4..7、g2:c8..11、g3:c12..15。每拍做四个 X 与四个 W 的外积，产生 16 个乘积。k=0..63，总计 256 个读请求；同一累加上下文每四拍更新一次。

一个 tile 覆盖 16 个输出列，256 列共 16 tile；99 行分为 25 行组，末组三行有效。全任务共 400 个结果块，通常每块 64 项，每 tile 最后一块 48 项。有效乘加数为 99×64×256=1,622,016。

当前 SRAM L1 的简化流水：e0 发 g0 请求；e1 发 g1 请求并用返回的 g0 数据形成乘积；e2 发 g2 请求、形成 g1 乘积并累加 g0 乘积。请求携带 k/g/行有效掩码/task/row/tile/slot 标签，防止数据与身份错位。g0 读取 X 并保存 x_hold，g1..3 复用，不重复读 X。

状态路径为 IDLE→LOAD→CLEAR→RUN→FLUSH→ALLOC→QISSUE/QWAIT→PUBLISH。FLUSH 必须等 k63/g3 乘积真正累加；最后请求发出不能直接当成完成。tile 间还可能进入 WAIT_TILE 等权重。

量化器只有一份，当前块先计算再逐项量化；双结果块并未使同一套 acc 同时计算下一块和量化当前块。它允许的是 CPU 消费旧块与核心生产后续块重叠。

## 4. 内部存储与复用

| 对象 | 当前逻辑组织 | 原因与限制 |
|---|---|---|
| X | 4×1600×16，合计 12,800 B | 全 X 留在内部，四行并行；6336 个实际元素，其余为尾部容量 |
| W | 2 槽×4 bank×256×16，合计 4096 B | 每槽保存 64×16 权重；活动槽读与加载槽写使用独立 SP bank |
| bias | 2×16×48，192 B | 与 W 槽绑定，直到最后行组结果成功发布才释放 |
| acc | 4×4×4×48，3072 bit | 64 个输出的未量化和，非完整 Y 缓存 |
| product | 16×32，512 bit | 乘法与累加之间的流水寄存 |
| 结果 payload | 2×64×19，2432 bit，即 304 B | 每项 y16+overflow+sat+last，另有描述符/owner/control |
| 输入 FIFO | 8×145 bit 的载荷 | pair1+meta32+task32+position32+data48，控制位另计 |

X 映射：bank=r mod 4，addr=floor(r/4)×64+k。例 X[5,7]→bank1/address71。

W tile 内列 c=0..15 映射：bank=c mod 4，addr=floor(c/4)×64+k；每槽四 bank。W tile 在内部服务该 tile 的全部 25 行组，因此无须为每四行重传权重。

W 槽状态 FREE→LOADING→READY→ACTIVE→FREE。当前 tile 的最后行组成功 PUBLISH 后，量化结果已独立，不再依赖 W/bias，可释放槽；不用等 CPU ACK。最后 MAC 完成时仍不能提前释放 bias 所属槽。

这些是逻辑 bank 数和容量，不是正式 SRAM 型号/宏数。banked_sp16 目前是行为 RAM，同步读，可配置 L1/L2，SoC 固定 L1；正式宏仍需按指南 16×128/1024/4096 的许可形状适配。不能把逻辑深度1600/256当成赛方现成宏，也不能默认一 bank 恰好一宏。

单端口 bank 上层必须保证同拍不读写冲突。结果 payload 当前组合 peek、读接受时寄存总线响应，不能直接替换为同步读 SRAM 而忽略新增延迟。

## 5. 输入接口为何这样设计

命令 FIFO8 位于 CPU 和执行核心之间，用于暂存未执行命令。用户当前独立核中的四项队列位于 SRAM 与计算核之间，保存已请求/返回的操作数；两者功能和所在位置不同，新包并非直接采用该四项预取分支。

PAIR 把两个 signed16 放进一次 32 位写，先消费低半，后消费高半。低半被核心接受后，只改变 input_half；高半接受后才释放物理 FIFO 项并减少 count。背压时半字及元数据保持。

PAIR_NEXT 在 pair 成功入队后，将 position 的低16位加2，减少 CPU 每对数据重写 position 的事务。满 FIFO、非法 op/索引、fault 时不能递增。只支持 X/W，要求偶数索引，不自动进位到下一 tile。BEGIN/OPEN 使用 legacy 暂存寄存器后，驱动重设 X/tile 起点。

MMIO 接受→FIFO 入队→核心 q 接受→q 实际执行是不同阶段；MMIO 写成功并不保证命令已合法执行。错误可能稍后在核心置 fault。

驱动等待输入容量时同时 drain 结果，避免双结果块满→核心停止→W槽不释放→OPEN堵塞→CPU只等输入、不读结果的环形等待。

## 6. 双结果块与可靠写回

每块生命周期 FREE→FILL→READY→FREE；两个块轮换。描述符记录 row/tile/count/task/sequence；首块序号1，最终400。量化按 g/row/col 枚举，填充地址是 row×16+g×4+col，因此填充不按0..63连续，written_mask 防重复及遗漏；发布后 CPU 按行顺序读取。

CPU 根据 descriptor 和 cursor 重建全局索引：

`index=(row+cursor/16)*256+tile*16+cursor%16`。

RESULT 一次返回 y16 和三个标志，无须每个结果都分别读索引、数据、flags、task。只在成功读响应的 valid&&ready 退休时推进 cursor；读命令接受只快照响应。响应被背压时不能重复消费。

ACK 校验任务、序号、数量、整块读完。匹配 ACK 在命令接受沿释放 owner，但 ACK 响应未退休时仍不安静。CPU 每块先完成共享写回及 fence，再 ACK，避免释放后误以为数据已完整写到共享 RAM。

两个结果块都占用时，核心可算完当前块后在 ALLOC 等待；缓冲是有限解耦，不意味着 CPU 再慢也不影响计算。

完成分四层：最后 MAC→最后块发布/compute_done→所有结果消费及ACK、B端点task_done→共享事务排空、token等匹配后的guard COMPLETE。核心done不是系统结果已写回。

## 7. 数值方案及48位问题

正式合同仍为 X signed16/Q12，W signed16/Q16，乘积 Q28，bias 逻辑 signed32/Q28，RNE右移16，sat16输出Q12。共享 bias 使用 int64 容器，Y 使用 int32 容器；容器宽度不改变有效数值范围。

新包物理实现仍为 acc48、bias48、49位加偏置临时和、sat48 后 RNE/sat16。q 输入 bias 不像 X/W 那样检查正确的 signed16 扩展，不能把接口能表示的任意48位 bias 当作正式合法输入。

用户当前独立核已实现 bias32/acc40/out16，外部命令48/结果32。合法 K64、signed16输入和signed32偏置下，40位足够；新包使用48位不意味着新架构算法需要48位。双结果块、命令FIFO、总线均不会增加每个输出点积的项数。未来若迁移，需要守住原冻结接口和数值合同后另作选择，本轮没有修改或恢复位宽。

## 8. E203、共享RAM与G的关系

E203 同时是输入搬运者与输出服务者；没有 DMA，CPU 的指令、轮询、MMIO、共享访问会成为整机周期的重要组成。共享 X 行主序；W 为列主序 W[col×64+k]，驱动发布时按 k/列对重排；不能把存储顺序与数学矩阵乘法方向混淆。

满尺寸共享 X/W/bias/Y/flags 容器分别为12672/32768/2048/101376/25344 B，共174208 B；描述符/mailbox/其他任务存活区间另算，不是整个共享RAM使用量。

本科 B 窗口 0x11000000；研究生 G 窗口0x11010000；guard窗口0x11020000。G是并列模式端点，不是B的自动后级。G源码为真实FP32编码器，以共享FP32单元顺序完成K/V/Q、attention/softmax、投影、残差/归一化、FFN/GELU等；不因包内含G就要求用户承担G实现。

guard 用 mode/session/epoch/task token 管理 BEGIN、COMPLETE、模式切换与 ABORT。只在相应安静边界切换；ABORT可取消未完成算术，但必须保留并排空已接受的总线响应，且不清共享RAM。共享通道一次只持有一笔全局事务，host/CPU owner保存到响应退休；不能中途换归属，也没有同拍退休再接收的新事务优化。

## 9. 优势、代价与已有数字

| 机制 | 实际优势 | 边界/代价 |
|---|---|---|
| 四上下文、请求/乘积/acc流水 | 在RUN阶段持续发读并处理乘积，四拍复访同一累加上下文 | 不是无限时钟保证，仍需STA；这部分已有历史基础 |
| 全X+双W槽 | X留片内，W跨行组复用，当前tile计算与下一tile装载重叠 | 装载太慢仍会WAIT_TILE，SP bank和slot所有权增加控制 |
| FIFO8+PAIR_NEXT | 缓冲CPU发布，双16位输入，省去重复position写 | 不消除CPU数据读取与轮询成本，不是DMA |
| 双结果块 | CPU写回旧块时核心生产后续块，较当前独立核输出阻塞更少 | 新增304 B payload及元数据，满两块仍背压 |
| 描述符/packed/ACK | 块级元数据摊销，结果与标志一起返回，身份与响应消费明确 | owner、序号、响应保持、错误恢复需严格验证 |
| F3结果循环 | 四项共用seen字读写、递增索引，减轻CPU服务开销 | 同RTL的软件优化，结果读写事务量未减少 |

本轮从 manifest/configuration.json 的12条任务周期相加复算：F0=33,310,320，F3=29,068,416，少4,241,904拍，即12.7345039%；同工作量相当于1.14593倍吞吐。它们是包内历史整机冷窗记录，含CPU装载/轮询/总线和结果共享写回，结束于最后Y/flags成功共享写响应；不含所有ACK/COMPLETE恢复尾。

这不是新包相对用户当前独立核的直接提速比例。用户原先约16.7万拍的独立核窗口不含相同CPU/总线成本，不能直接相减或排名。F0与F3的硬件相同，不能把12.73%全归给双结果块或MAC。

包内F1仅X宽读约少2.02%；F2 W重排反而约多10.67%；F4减少容量轮询反而约多2.57%。减少某种事务并不保证整机更快。F3尚未与F1合并，不能叠加两者收益。

## 10. 资格与后续边界

已有本地开发与逐项输出证据不等于官方资格。服务器完整工程运行、正式宏映射、150MHz正式STA、面积≤2.25mm²、完整功耗/能耗、官方600样本和官方性能任务尚未闭合。推荐F3同一生产固件的正常G12、B→G12→B、连续B12资格也不能从旧C11不同固件继承。真实G约300544 B逻辑bulk存储不能在完整系统面积/功耗中遗漏。

用户只负责RTL时，需要理解并实现的本科主边界是bank/SRAM适配、W槽、tag-product-acc、量化、双结果块、输入wrapper及明确的完成/quiet信号合同。CPU驱动、G和正式后端交接需分工；本轮不重新设计或写入这些模块。

## 11. 本轮对照的关键来源

- 架构及边界：包内 docs/KWT1_架构与实现说明.md、ARCHITECTURE_LINEAGE.md、PARAMETERS.md、PLATFORM_AND_RESOURCES.md、ACCEPTANCE.md。
- 本科wrapper：rtl/bachelor/soc/revd_opt/revd_opt_icb_w2.sv。
- 本科计算：rtl/bachelor/rtl/revd_opt/core_stream_tiled_w2_opt.sv。
- 结果owner：rtl/bachelor/rtl/revd_opt/v08_result_blocks.sv。
- 量化/RAM：rtl/bachelor/rtl/revd/quant_epilogue.sv、banked_sp16.sv。
- 系统：rtl/dual_mode/dual_mode_soc.sv、dual_mode_icb_guard.sv；rtl/common/soc/e203_common/icb_shared_ram.sv。
- G顶层：rtl/graduate/rtl/encoder_icb.sv、encoder_core.sv（只核对系统角色及阶段，没有全面审核HardFloat和所有G运算实现）。
- 软件：firmware/recommended_F3/revd_opt_driver_w2.c 与 reference_F0 对照。
- 配置/证据：manifest/configuration.json、evidence/DELIVERY_VALIDATION.json。
- 个人基线：D:/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core 当前源码及 docs/reports/20261027-width-narrowing/README.md；未用旧HEAD代替未提交工作区。

本笔记只解释当前架构与实现合同，不构成对全部源码无缺陷、正式宏已适配或PPA已达标的声明。
