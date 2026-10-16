# 第一轮全套独立审查：赛题、机制与复现说明

**结论：PASS。** 本轮已覆盖全部11份阅读文件；开放 P1=0、P2=0、P3=0。01—05初审的3项P3及本次补审发现的1项P2、2项P3均已由root修正，再由本审查者独立回读关闭。此结论是报告第一轮审查通过；第二轮实测/来源绑定审查和报告批次最终接受仍需分别完成，不把本结论当成正式比赛通过。

审查者：`cycle_spec_review`，非作者。日期：2026-10-16，Asia/Shanghai。只写本审查文件及同名JSON；未修改作者文档、生产源、固件、状态、Git，未运行硬件仿真、综合或搜索。作者释放记录 `work/report_cycle_authors.json` 已确认三组均为RELEASED且 `all_writers_released=true`；06/07按最终释放内容及root随后修正的实际快照接受。

## 发现与关闭记录

| 编号/严重性 | 原位置与问题 | 独立关闭依据 | 状态 |
|---|---|---|---|
| P3-S01 | 01:21、02:19、03:20，赛题指向工程外Documents目录 | 三处均改为 `../../../work/report_cycle_sources/2026赛题指南.pdf`；工程副本存在，实际摘要与原件manifest一致 | CLOSED |
| P3-S02 | 04:244及05:286—290，把会写回的参考CLI当只读或未说明副作用 | 已明确CLI写入 `readback-verification.json`、须与同证据主线串行；对照 `numeric/encoder/verify_bundle.py:98` 一致 | CLOSED |
| P3-S03 | 05:308，待验项的“物理面积/门级时序仿真”可能被理解为额外P&R验收 | 改为指定库映射及SRAM宏面积、功耗/单任务能耗、综合前后功能与150MHz；门级/等价检查作为方法，明确无布局布线要求 | CLOSED |
| P2-A01 | 09:41—42、70—73，6条 `reports/reproduction/...` 输出路径被真实runner前置guard拒绝 | 六处均改 `reports/encoder/reproduction/...`；直接对照 `dv/encoder/run_encoder.py:95` 与 `dv/e203_encoder/run_system.py:31`，均满足允许父目录。静态核查全部11份共15条此类输出示例，非法路径0 | CLOSED |
| P3-A01 | 09:59，把LN序列的阅读入口指向只含exp/GELU的nonlinear模块 | 现明确nonlinear追exp/GELU，LayerNorm在encoder_core中追踪；与实际PLSUM—PLAFF位置一致 | CLOSED |
| P3-A02 | 06:154，泛称“忙时写不能成功”，遗漏ERROR的W1C例外 | 改成配置/装载/计算命令忙时拒绝，ERROR W1C及STATUS/计数按寄存器定义仍可用；与 `encoder_icb.sv` 分支一致 | CLOSED |

这些修复都是文档修改。对P2-A01没有运行长硬件任务：原路径在建立输出目录/编译之前即被guard拒绝，修复后的路径静态满足同一guard；为验证路径而重跑长仿真没有必要。原01—05详细审查保存在 [review-spec-01-05.md](review-spec-01-05.md)，其历史3项P3在本文件关闭，原审查记录保持不变。

## 全部阅读文件的覆盖判定

| 文件 | 本次核查的题意、机制和读者验收 | 判定 |
|---|---|---|
| README | 本科1—3/选做4—7导航、两条数值路径、学习顺序、工程与正式验收区分、整机同输入双策略范围 | PASS |
| 00 | 指南印刷页3—14：E203接入、共享512KiB、内部指定宏、150MHz、新增2.25mm²、模型/数据边界、7项任务、精度/12任务/计时/功耗/同配置/交付 | PASS |
| 01 | 64次握手、signed16乘积/48累加、49位后置bias、sat48/RNE/sat32、尺度推导、异常、连续任务、复位、独立期望及误差范围 | PASS |
| 02 | 99×64×256、W_pack[n,k]、X/W/b有效计数、同步PRIME/FEED、四银行、行Y/flags及ACK、12组对应参数、全部输出和真实MAC数 | PASS |
| 03 | 真实上游E203而非BFM代算、共享区/ICB/生产C驱动、fresh LO/HI、同步读与响应背压、CPU完整案例/复跑、generic283/590与正式工艺边界 | PASS |
| 04 | QKV→QKᵀ/8→Softmax→PV→Wo+bo完整链、精确weight/K/V地址、全K/V与逐行缓存、独立op6/6336公开输出、近似与位真分离 | PASS |
| 05 | 全99token的PostNorm、两残差基底/两LN、总体方差/epsilon/独立gamma-beta、beta预取、64→256→64与GELU、14阶段/完整Y证据 | PASS |
| 06 | 12层独立参数、49792word布局、共享区不重叠、真实CPU逐层mailbox供参、WAIT_DONE、SWAP/RELOAD、分类头、正式样本边界与复用对照 | PASS |
| 07 | 核心/真实SoC generic层级、同步bulk/共享几何、面积和功耗统计范围、真实inclusive计时/四段求和、CPU/host分母、条件吞吐换算、同配置与正式缺口 | PASS |
| 08 | 真实退出0与根控本地接受分层、七项局部证据、输入/层/输出/CPU写回计数、近似误差、优化收益和正式待验汇总 | PASS |
| 09 | WSL环境、先回读后小例再整机、入口参数/允许输出目录、副作用/串行、代码追踪归属、正确成功失败信号、带答案检查 | PASS |

## 赛题与模型机制的独立核查

以 `work/report_cycle_sources/guide-text.txt` 和同摘要PDF工程副本为需求源，核对了本科必做1—3、扩展4—7的准确边界。PDF物理15页，印刷页=物理页−1；副本SHA为 `b73a5414b4dcdb2cca337778a133be88705e207bec080687731d63b413ea927c`。不要求P&R/GDS，不伪造未取得指定库时的面积、时序或功耗。

整数部分逐行读过 `rtl/dot64.sv`、`ffn1_top.sv`、`ffn1_icb.sv`、`prototype_sync_ram.sv`、`numeric/fixedpoint.py`、`sw/ffn1_driver.c` 与相关DOT64/矩阵TB；报告的位宽、饱和顺序、64项末项、合法/非法shift、异步复位、完整装载、行缓冲保持与消费责任一致。量化尺度来自冻结参数和固定规则，不读取测试误差搜索。36层案例不是完整12层编码器，也不是CPU36例。

完整编码器逐行读过 `rtl/encoder_core.sv`、`encoder_nonlinear.sv`、`encoder_icb.sv`、独立 `numeric/encoder/encoder_ref.c` 及参数布局，核对全部QKV/输出投影、两LN/残差、FFN/GELU和全99token输出；精确检查PLNMUL预取beta、PLAFF读取gamma的单读端口机制。官方语义/导出按实际参数属性取162张量607308参数，报告没有按Dense偶然名字猜权重，没有把tanh GELU写成官方erf逐位计算。

新补读 `sw/e203_encoder/main.c`、`sw/encoder_driver.c`、`soc/e203_encoder/e203_encoder_soc.sv`、`encoder_shared_ram.sv`、`dv/e203_encoder/tb_e203_encoder.sv`：CPU检查旧FFN1窗口后初始化encoder；mail[8/9/10]请求/ready边界、每层host49792word逐拍供应、WEIGHT装载、START、阻塞WAIT_DONE、最终完成均与06一致。SWAP翻转银行、保留完整X有效量、清W；RELOAD清X/W计数，由CPU回读并重装。策略不改模型/权重/运算顺序，TB只向公开共享区供原始输入/参数并旁路比较，不执行必做神经计算。

一层参数49,792word=199,168B、十二层597,504word=2,390,016B，确需逐层供参。共享输入 `[0xA0001000,0xA0007300)`、参数 `[0xA0008000,0xA0038A00)`、输出 `[0xA0040000,0xA0046300)` 互不重叠；张量有效载荷249,856B不当整片占用。内部bulk75,136word=300,544B、行暂存710word=2,840B独立于共享512KiB，计新增面积而不挤占共享地址空间。

分类头取末层CLS的64维，经同权重64×12线性头；不额外LN或池化。所有完整层均输出99×64，不仅CLS。工程test12中silence双方预测unknown，12/12是与官方预测一致；正式600样本Top1下降≤2个百分点仍待验。测试划分不用于调整权重、量化参数或数值配置。

## 实测数字、结构与状态的抽核

本轮核对原始状态和日志并独立重算主要数量与比例；没有把本轮抽核冒称第二轮完整消费物回读，也没有重复硬件运行。

- **完整RTL与参考**：CSV实际15条case/180条layer，全部Y合计1,140,480word，core周期合计3,817,428,084；与05—08一致。首例trace1,603,800word、独立repeat额外76,032word分列。原3输入/test12参考最终最大NRMSE分别0.0004071640493761876/0.000513838042935309，近似误差与逐位目标分列。
- **双CPU真实范围**：两status均PASS/exit0且12层；policy1 CPU输出6336、neural76032，policy2 CPU输出76032、neural76032。相同模拟器binary摘要 `f3757e5e36e51fd8c67140ed2992f6b2074fae48a8699113880a6435ea071bf9`，不同1512B策略固件均有独立ELF绑定。报告未把被动输出当CPU写回，也未把相同输入两次运行当12个正式整机任务。
- **inclusive计时**：TB首MMIO4543；末写284358022/290631971；`末−首+1` 得284353480/290627429。四段285547、597504、28685484、254784945/261058894重新求和一致；逐层12项重加与各段相同。前11层各省570359，共6273949；末层无省。输入初始fixture在窗外、CPU搬运和host供参在窗内的边界保留，未升级为正式计时起点一致。
- **流量与比例**：CPU共享660034/799426，相差139392，比例17.4365107%；含host的1257562/1396954相差同值，比例9.9782813%。host597504参数写+12ready写+12请求读不省。读/写各69696=11×6336；逻辑事务不是物理宏端口/能耗。周期比例2.1587601%没有误名为吞吐提升。
- **条件吞吐**：仅假定150MHz换算，pingpong时延1.8956898667s/吞吐0.5275124468，reload1.9375161933s/0.5161247186；与07一致且明确未签核时序、不是官方12任务成绩。
- **generic**：实际core status为encoder_icb、5个bulk实例、75136word/300544B；SoC为e203_encoder_soc，279模块定义，独立回读278可达，cpu/ram/encoder/ffn1完整连接。读过两综合脚本，确实无指定库映射/SDC/功耗步骤；design摘要分别 `dd33ad7c...27d1eb` 与 `a9121f08...6cdce6`，报告没有将generic规模换算mm²。
- **已接受硬件基线**：读取稳定 `reports/system/formal-baseline/runner-state.json`，真实exit0、结束于北京时间2026-10-16 00:44:40；读取 `reports/system/root-formal-acceptance.json` 为ACCEPTED_LOCAL_DRAFT，unified run_id=`84ef1f97e1394486b11b5510f79716d4`。独立逐项回验其17项evidence与59项review绑定摘要，失配0。08对硬件已接受和报告仍待两轮/最终接受的区分准确。
- **当前冻结**：独立逐项计算192项生产源SHA，全部与 `work/encoder_source_freeze.json` 一致；冻结清单SHA=`4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17`。本轮文档修复不改变生产结果身份。
- **轻量机械回读**：全部11份UTF-8解码无替代字符；解析309个本地Markdown链接，失效0；15条encoder/E203输出示例全部位于runner允许的reports/encoder子树。命令参数按实际argparse、只读/写入分支核对，没有运行长命令或以`--help`充当功能验证。

正式待验项保持一致：组委会平台、指定标准单元/SRAM宏、合法SDC及映射网表、150MHz关键路径/裕量、新增≤2.25mm²、综合前后功能、同窗口活动映射和整SoC平均功耗/单任务能耗、600样本与正式12性能任务。面积不计复用CPU/共享/固定部分，功耗却需包括CPU/互连/全部SRAM；报告未混用这两个范围。

## 文档快照与前后摘要

“开始”是本次全套补审首次阅读记录；06/09在审查中发生已通知且已回读的root修复。其余9份未漂移。“结束”是本轮第一审查结论接受的快照；后续正文若再改，应按影响回读并让第二轮绑定最新版本。

| 文件 | 开始SHA-256 | 结束SHA-256 |
|---|---|---|
| README.md | 8bf55bc5edae190c60b6512d3874ff4dd4691d1ff5cb19a27a79136a48218c33 | 8bf55bc5edae190c60b6512d3874ff4dd4691d1ff5cb19a27a79136a48218c33 |
| 00_赛题要求与验收对应表.md | 539bf0212aded25b30a206eb48b79a449edab7a0f2ac36b5d0d550d4862f9e51 | 539bf0212aded25b30a206eb48b79a449edab7a0f2ac36b5d0d550d4862f9e51 |
| 01_乘累加与数值处理模块.md | 6b904f25fc743a46274d0a19832cd955ce9c5c5accb9591785fb39f685cf9760 | 6b904f25fc743a46274d0a19832cd955ce9c5c5accb9591785fb39f685cf9760 |
| 02_前馈线性加速器.md | 21dd9af59349e320e49aa9f482a3e0a5f287271c6941a39dcb13d4ea4b2a304c | 21dd9af59349e320e49aa9f482a3e0a5f287271c6941a39dcb13d4ea4b2a304c |
| 03_前馈线性加速器SoC集成与综合.md | 0ad2c46607a1bbe554abe29905957625381d5e7b32dfc9699a74d925eb07da13 | 0ad2c46607a1bbe554abe29905957625381d5e7b32dfc9699a74d925eb07da13 |
| 04_单头注意力模块.md | e182db6dacbbe58bc97ecd33ccd41808ef512b0edb50a2eec7ee6cf01b06bb64 | e182db6dacbbe58bc97ecd33ccd41808ef512b0edb50a2eec7ee6cf01b06bb64 |
| 05_单层编码器.md | 0e2e6d9736186cf4b73ee1d12021921f18d1e9c8d704f3bc31924d67bb2521b7 | 0e2e6d9736186cf4b73ee1d12021921f18d1e9c8d704f3bc31924d67bb2521b7 |
| 06_十二层编码器与参数调度.md | de207835a81d0541c4ee838dcaadc08e7bdeb4dfceb4e23974f10357dd830022 | b08e30e33c2f5689566103a0930bee7b1d3e9b45ff04744fa1c4fc0cbf721ceb |
| 07_编码器加速器综合与性能分析.md | 0e88d2305c9ce54f7c1fe9aca96003902b78db4dd69c66955c71e101cb6f0e53 | 0e88d2305c9ce54f7c1fe9aca96003902b78db4dd69c66955c71e101cb6f0e53 |
| 08_总体验收报告.md | 23c51a89955b32cee3638eb9a0e68758d4aa3cdfaf93b7a2fe4fe857088f8204 | 23c51a89955b32cee3638eb9a0e68758d4aa3cdfaf93b7a2fe4fe857088f8204 |
| 09_复现与学习指南.md | d9284cc1906dd95a9f02d3d9cc9d2fc761aa7bd61e0cf63c95accc53e8e4442c | 95b273029889a31ce7aacbd0c4e3050466a4e97eb8c89391dc6d43b28a99c9a1 |

## 交回总控

全部11份第一轮已核，累计发现1项P2、5项P3已全部独立关闭，开放问题为0。可进入第二轮独立证据/复现/读者质量审查；本轮没有替作者自行改正，也没有把第二轮、报告执行器真实退出、最终manifest及总控报告批次接受合并为已完成。
