# 设计选择、常量及保留理由

配套：[规格](README.md)；[完整原理](module-guide.md)。本表区分算法要求、功能结构、接口兼容和待测参数，不把历史实现全部当成必需。

## 1. 为什么保留或修改

| 对象 | 决定 | 原因；删除或改变的后果 |
|---|---|---|
| X/W16、乘积32 | 保留 | 已确认数值格式；16×16精确乘积需要32位 |
| acc48 | 改40 | 合法范围足够，和个人冻结方案统一 |
| bias48存储 | 改32 | 正式bias仅signed32；先验高位，再保存 |
| 加偏置49位 | 改41 | 对40位结果保留一位检测空间 |
| 内部Y32 | 改16 | sat16结果不需长期多存16个符号位 |
| 共享Y32/MMIO32 | 保留 | E203与现有ABI采用32位字；边界符号扩展 |
| legacy载荷48 | 当前保留 | ABI兼容及非法高位检测；可未来单独版本化32位协议，当前不同时改ABI |
| 共享bias64 | 当前保留 | 现有描述符/数据布局；调用端先检查signed32，不能把容器当有效精度 |
| shift0..47 | 正式路径改固定16 | Q28到Q12推导所得；不为未要求的动态尺度付出功能复杂度 |
| registered out_raw48 | 移出生产合同 | 无生产消费者；保留raw40组合量和overflow语义，不为观察额外存副本 |
| 16MAC | 保留当前资源点 | 四X×四W并行；不是官方强制或已证明全局最优 |
| CTX4 | 保留 | 四组4列覆盖一个16列tile、四拍轮转；改为1会改变调度/复用/累加反馈条件 |
| X四bank | 保留 | 同拍四行供数；单个SP端口无法替代四路独立读取 |
| 全X驻留 | 保留 | 跨16个W tile复用；避免重发X，代价是12.5KiB逻辑容量 |
| W双槽 | 保留 | 最小双份存储实现活动读/下一tile写的重叠 |
| 命令FIFO8 | 保留当前兼容配置，最优性待测 | 缓冲CPU与核心；确切深度8是既有选择，不是数学推导，改动需同步CAP/指针/固件 |
| 核心单项q | 保留 | 接受与执行分开，有序执行、等待OPEN、避免组合控制跨越接口；引入一项状态 |
| 请求标签 | 保留 | SRAM返回滞后，身份必须跟数据同行；直接用当前请求计数会错位 |
| product寄存 | 保留 | 分开乘法和累加路径、保存对应标签；正式频率仍需STA |
| FLUSH | 保留 | 最后请求发出后仍有乘积在途；省略会漏最后贡献 |
| 单份量化器 | 保留当前结构 | 复用硬件、限制重写范围；其串行开销不是最优性证据 |
| 双结果块 | 保留 | 已量化结果与acc分离，CPU消费和下一块生产可重叠 |
| written_mask64 | 保留 | fill不连续；计数不能检测重复代替缺项 |
| task/sequence/count | 保留 | 区分任务、块、尾块规模，拒绝旧ACK或不完整ACK |
| RESULT响应寄存 | 保留 | 背压期间必须保持同一项，不重复消费 |
| ACK | 保留 | 明确CPU已读完并写回后才能复用owner；只看读cursor不等于共享写回完成 |
| 输入等待时服务结果 | 保留 | 打破结果满→核心停→W槽满→输入堵塞的循环等待 |
| guard/epoch/token | 系统集成保留 | 模式和恢复边界需要拒绝旧身份，并排空在途事务 |
| 不清整块RAM | 保留 | SRAM通常无逐字复位能力，清owner/valid即可阻止旧数据成为有效数据 |
| DMA | 本规格不新增 | 当前系统没有它；新增将改变总线主设备/一致性/验证范围，缺收益测量依据 |
| G | 作为既有系统端点保留 | 不套用B数值规则，不要求本科用户重写G，完整系统资源评估不能漏计 |
| 64位内部观察计数器 | 属验证观察项，不当算法必需 | 是否保留在生产网表由可观测需求和综合结果决定；0x34/38外部诊断计数另属ABI |

“保留”表示当前有已说明的功能或兼容依据；不表示参数最优、芯片已达标或永远不可改。

## 2. 数字从哪里来

| 数字 | 来源 |
|---|---|
| 99 / 64 / 256 | 当前正式任务M/K/N |
| 16路乘法 | PM4×PN4 |
| tile16 | PN4×CTX4 |
| 25行组 | ceil(99/4) |
| X bank深度1600 | 25×64 |
| W bank深度256 | 4个列上下文×64 |
| 每tile W1024 | K64×tile16 |
| bias总32项 | W两槽×每槽16列 |
| acc总64项 | CTX4×PM4×PN4 |
| 每块256次请求 | K64×CTX4 |
| 尾块48项 | 尾行3×tile16；这里的48是项数，不是位宽 |
| 400块 | 25行组×16tile |
| 25344个Y | 99×256 |
| 1622016有效MAC | 99×64×256 |
| 结果19位 | y16+overflow1+saturated1+last1 |
| payload2432 bit | 两块×64项×19位 |
| 右移16 | acc小数28−Y小数12 |
| flags有效3位 | raw溢出、最终饱和、全局最后项 |
| sequence24+count8 | 正好一字32位ACK；宽度源于接口格式 |
| task32/epoch32 | 系统身份协议，计到上限拒绝回绕 |
| FIFO8 | 当前工程兼容参数；需要性能/资源实验才能决定更优深度 |
| SRAM L1 | 当前SoC/行为存储合同；物理宏适配时须重新核对 |
| 150MHz / 2.25mm² | 赛题约束/目标，尚待正式STA与面积证明 |

## 3. 后续任何结构修改必须附上的说明

每项变更记录：要解决的现象、原行为、目标行为、合法输入、为什么现有机制不够、预期代价、如何检查、不变的接口和需要更新的接口。未经实测，面积/频率/功耗/周期变化标“待测”，不能用更少的声明bit冒充实际PPA。

依赖数据尚未取得时，记录具体缺哪项证据。例如“不知道最后用多少颗SRAM”应落实为缺宏端口/准入形状/面积/读延迟合同，而不是随机写一个宏数。

## 4. 对照来源

原包根目录：`D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend`。

- `rtl/bachelor/rtl/revd_opt/core_stream_tiled_w2_opt.sv`：原包acc/bias48、命令校验、状态、bank、量化连接、槽释放。
- `rtl/bachelor/rtl/revd/quant_epilogue.sv`：原包49位加法、sat48、可变shift、sat16。
- `rtl/bachelor/soc/revd_opt/revd_opt_icb_w2.sv`：FIFO8、PAIR_NEXT、MMIO、结果响应路由。
- `rtl/bachelor/rtl/revd_opt/v08_result_blocks.sv`：owner、written_mask、cursor、ACK接受释放。
- `rtl/dual_mode/dual_mode_icb_guard.sv`：下游响应快照、上游RESP保持、token和flush。
- `rtl/dual_mode/dual_mode_soc.sv`：E203/B/G/共享RAM及固定L1。
- `firmware/recommended_F3/revd_opt_driver_w2.c`：输入时同时drain、F3索引/seen、fence与ACK。
- `docs/ACCEPTANCE.md`、`PLATFORM_AND_RESOURCES.md`、`manifest/configuration.json`：资格及正式宏/PPA缺口。

个人数值依据根目录：`D:/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core`。

- `rtl/include/kwt_numeric_config.vh`、`docs/shared/numeric-format-v0.1.json`：16/16/32/32/40/16及固定尺度。
- `rtl/control/command_frontend.v`：原个人核已检查bias32符号扩展和shift16。
- `docs/reports/20261027-width-narrowing/README.md`：个人核既有范围证明与实测；不能转移为新架构实测。

本轮没有执行新RTL或后端验证，也没有改变团队仓库、冻结包或已有未提交代码。
