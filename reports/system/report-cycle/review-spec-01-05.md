# 第一轮独立赛题与机制审查：00、01—05

审查者：`cycle_spec_review`，非报告作者。审查日期：2026-10-16（Asia/Shanghai）。结论：**本次范围未发现 P1/P2；有 3 项 P3 文档建议。01—05 的赛题、数学与实现机制可以进入第二轮证据审查。** 这不是七份报告或整项工程的最终接受。

## 发现

### P3-S01：01—03 的赛题链接宜统一到工程内同摘要副本

- 位置：`docs/encoder/reports/01_乘累加与数值处理模块.md:21`、`02_前馈线性加速器.md:19`、`03_前馈线性加速器SoC集成与综合.md:20`。
- 事实：三处仍链接到用户 `Documents/xwechat_files/.../2026赛题指南.pdf`。当前机器可以解析，并非失效链接；但复制工程后该路径通常不随工程迁移。00 已改为工程内的 `../../../work/report_cycle_sources/2026赛题指南.pdf`。
- 核对依据：工程副本实际 SHA-256 为 `b73a5414b4dcdb2cca337778a133be88705e207bec080687731d63b413ea927c`，与来源 manifest 所记原件一致。
- 修复期望：由作者或总控将上述三个链接统一到工程副本，保留印刷页码和来源指纹。只需文档与链接回验，无需重跑硬件。
- 严重性：不改变赛题解释、实现或当前机器复现，不阻塞本轮机制审查。

### P3-S02：参考包 CLI 回验会写结果文件，04 的“只读”措辞不准确

- 位置：`docs/encoder/reports/04_单头注意力模块.md:244`；同类命令在 `05_单层编码器.md:289`、`:290`。
- 事实：`numeric/encoder/verify_bundle.py:98` 的 CLI `main()` 在验证后调用 `json_write(directory/'readback-verification.json',result)`。04称其为“只读回验”，读者可能据此与使用相同证据的主线同时执行。05未声称只读，但也未在这两条命令处说明写入副作用。
- 修复期望：若要提供真正只读的快验，调用 `verify()` 函数并仅向stdout打印返回值，不调用写入结果的 `main()`；或明确命令会更新该结果文件，待总控安排串行后执行。不要为修复文档而修改生产检查器。
- 严重性：当前两份原始参考包已有文件为确定性基础结果字段，同源正常回验预计保持同字节；没有证据表明现有数值产物损坏，因此列P3，不升为硬件/位真失败。

### P3-S03：05 待验项宜使用赛题的逻辑综合口径

- 位置：`docs/encoder/reports/05_单层编码器.md:308`。
- 事实：末段使用“物理面积/功耗/能量”并将“门级时序仿真”并入待验清单。赛题印刷页3明确不含布局布线/物理验证/流片，页12按指定库映射标准单元和指定SRAM宏面积核验；页9/11要求综合前后功能和150MHz时序，而未限定必须用某一种门级时序仿真方式证明。
- 修复期望：改为“指定库映射及SRAM宏面积、功耗/单任务能耗、综合前后功能与150MHz时序检查”；门级时序仿真可列为验证方法选择，不暗示额外P&R验收。其余报告已有的正式待验边界保持。
- 严重性：上下文已明确generic不证明PPA，未虚报任何结果；此为消歧建议，P3。该线索由root提出后，本审查者另行对照赛题文字确认。

## 范围与独立性

完整阅读了已释放的 01—05 以及 00 要求矩阵，对照 `work/report_cycle_plan.md`、`work/report_cycle_sources/guide-text.txt` 的所有相关条款。页码采用印刷页，物理页=印刷页+1。读取原始 RTL、Python/C 数值模型、生产驱动、关键 TB、运行摘要与稳定 handoff，独立核算主要公式、张量/存储数量和报告列出的代表性数据。

本轮未修改作者报告、生产 RTL、固件、全局/硬件/报告状态或 Git；未运行仿真、综合或长回归。只写本审查文件及其机器摘要。没有将旧日志存在当成新运行，也没有把 generic 结构、公开 E203、工程子集升级为正式比赛通过。

06/07 尚由另一作者编写，不在此次接受范围；README/08/09 也未作整体审查。00 中指向 06/07 的三个暂缺链接只记录为本次快照，待作者释放后由总控和第二轮检查闭合，未作为已释放分册的缺陷。

## 逐项覆盖与判断

| 分册/题意 | 独立核查的机制 | 证据与判定 |
|---|---|---|
| 00：条款与边界 | 本科 1—3、研究生/选做 4—7；150MHz、512KiB、内部指定 SRAM 宏、2.25mm²范围；600 样本、12 个正式任务；同冻结配置与完整计时 | 与指南印刷页3—14一致。共享容量和内部存储分列；功耗与面积范围不同；正式缺项保持待验，不造 PPA。 |
| 01：dot64、bias、转换 | signed16×signed16→signed32→signed48；64次真实输入握手；偏置最后加、signed49 检出范围超限；sat48→对称 RNE→sat32；非法 shift；复位和连续任务 | `rtl/dot64.sv`、`numeric/fixedpoint.py`、`dv/dot64/test_dot64.py` 与报告一致。核过 −8、正负 half-even、MIN48、raw overflow 与 output saturation 区分、末项计入、结果背压和中途复位机制。 |
| 02：99×64×256 | W 数学[k,n]→存储[n,k]；X/W/b 顺序装载及有效计数；同步 PRIME/FEED；完整行才 row_ready；读完 Y/flags 再 ACK；12组独立 FFN1 参数不错误串联 | `rtl/ffn1_top.sv`、`prototype_sync_ram.sv`、`dv/ffn1/tb_ffn1.sv`、数值参考与报告一致。四银行容量 384512bit=48064B；每例25344输出、1622016 MAC；69控制拍/输出的局部口径正确。 |
| 03：真实 E203 与综合 | 实例化真实上游 `e203_subsys_top`，sysper ICB 命令、共享 SRAM；新 LO/HI、延迟核心反馈、同步行读、sticky vs 本次错误；生产阻塞驱动与明确恢复责任 | 读取 `soc/e203_common/e203_cpu_shell.sv`、`rtl/ffn1_icb.sv`、`sw/ffn1_driver.c`、`sw/e203_ffn1/main.c`，对照 CPU/TB/结果。一个 CPU 全尺寸案例+repeat 与 BFM36分列，取指握手不当退休数；generic283/590 cell不当工艺面积，任务3正式待验准确。 |
| 04：完整独立 attention | Q/K/V无bias→QKᵀ→0.125→逐行稳定Softmax→PV→Wo+bo；全K/V与一行query/score/prob；K和V的精确地址；op6公开启动/全6336 READ_Y、独立完成状态 | `rtl/encoder_core.sv`、`encoder_nonlinear.sv`、`numeric/encoder/encoder_ref.c`、`contracts.py`、`dv/encoder/tb_encoder.sv` 与报告一致。核过 Wq/Wk/Wv/Wo/bo 的0/4096/8192/12288/16384起址、完整49792装载门、attention后禁止SWAP/RELOAD、不置job_done。 |
| 05：完整 PostNorm | R1=X+A、N1=LN1(R1)、64→256→64、GELU、R2=N1+F2、LN2；全99token；每行64维总体方差、eps=1e−6、独立gamma/beta、精确顺序和权重访问 | 对照 core 的 PR1/LN/PFF1/PBH/PGELU/PFF2/PB2/PR2；特别核对 PLNMUL 预取 beta、PLAFF 取 gamma 并FMA。与独立C相同。硬件tanh GELU与官方erf、RTL对C位真与C对官方误差分列，没有混同。 |

## 代表性证据抽核

- **整数数值规则与覆盖**：逐行对照 `derive_layer_config` 的最小二幂权重尺度、固定输入尺度2⁻⁸、保守界和最小合法 shift；DOT64 测试独立任意精度期望未调用生产数值模块。`dot64/status.json` 与 handoff 支持8测试/52完整结果事务、首笔64对后 raw/data=−8。数值交接支持67测试、36例最大案例NRMSE=0.0010805182139773971、最大层聚合NRMSE=0.0009342248801263425及0饱和；不是600样本结论。
- **FFN1数量与周期**：对 `ffn1/full/status.json` 的36例重新求和，load/compute/row_wait/readback 分别1654343/62954496/39257/1821204；报告准确说明分类未覆盖全部控制拍。36×25344=912384，×64=58392576，与实际握手统计一致。
- **真实 E203**：`reports/system/e203-ffn1/result.json` 支持完整案例 `eight_750e3e75_nohash_0/layer_01` 和repeat，各25344 Y/flags；8595787外部周期、74159/94633 MMIO读写、22976装载、1 START/99 ACK。报告的原始结果摘要 `194817bb...46e368` 与 handoff 一致。代码中的 CPU 不执行神经矩阵计算，完成魔数之外还检查main返回值和完整写回。
- **attention公开输出**：`attention-full/status.json`、实际仿真日志与 TB 源支持 op6、6336输出、51282 trace、位差0、9316780 core周期、flags01。51282=5×6336+2×9801，独立模式读回的是A，未误用LN2输出。输出SHA为 `75951d8f...69974`。
- **整层和trace**：`full/original-0/status.json` 与日志支持12层76032个Y、首例1603800 trace、layer0周期21210556、首例输出SHA `ae7f60af...98fea`。每层14阶段=10×6336+2×9801+2×25344=133650。报告将15输入180层的全部Y与仅首例全stage trace分开计数，不伪称所有案例均保存全trace。
- **近似误差**：直接读取参考 manifest 的 `nonlinear_validation` 与首例 `layer_00/comparisons`；exp100001点最大相对差7.0829376545e−8，GELU40001点最大绝对差0.0004734134403；首层q/k/v/scores确实bit_equal，A最大绝对差1.3411045074e−7、N1为1.1920928955e−6、GELU为0.000473229214549、Y为0.000419043004513。与04/05的表一致，且报告正确限定为本算例观察。
- **参考与官方边界**：检查 `model/encoder_export.py` 的语义取参列表及hook观察原张量路径，`contracts.py` 的13参数布局与RTL一致。参考handoff/验证报告支持162张量607308参数、原三输入与test12最终Y最大NRMSE=0.0004071640494/0.0005138380429；silence双方预测unknown，报告未将12/12预测一致写成12/12标签正确。
- **冷启动/故障**：读取 FP32 handoff、core故障TB和checks状态；报告引用的34组×两模拟器×两轮=136新进程和21291主事务有明确来源。C未实现FP异常flags oracle的额外结论没有被加入报告。core中非有限/故障终止与重新BEGIN/复位恢复机制、同步读/未消费响应复位均有对应检查。
- **复现与读者可学性**：所列入口/参数与脚本argparse吻合，01—03说明会更新既有证据并须串行，04/05的RTL重跑使用独立输出目录；参考包CLI写回副作用另见P3-S02。手算、张量/模块表、运行成功失败信号、自检答案存在。轻量只读链接检查解析197个本地链接，除00指向尚未释放的06/07共3处外均存在；UTF-8解码未出现替代字符。未执行这些长复现命令。

## 已审快照与漂移处理

下表的“定稿核查前/后”以本轮完整机制阅读后的定稿快照开始，结束时再次计算实际文件摘要；01—05均未变。00首次阅读摘要是 `08b6d3deea266db606455ab9912e58c32f48fd39d402f4dcea460ca1262de64d`；审查期间root仅把第5行PDF入口改为同字节工程副本，已回读该行并确认条款矩阵未变。此处接受的是下表所列更新后00快照。

| 文件 | 定稿核查前 SHA-256 | 定稿核查后 SHA-256 |
|---|---|---|
| 00_赛题要求与验收对应表.md | 539bf0212aded25b30a206eb48b79a449edab7a0f2ac36b5d0d550d4862f9e51 | 539bf0212aded25b30a206eb48b79a449edab7a0f2ac36b5d0d550d4862f9e51 |
| 01_乘累加与数值处理模块.md | d21e4c41bb30454a7832ab03fefa3e2b3ec430f0b9c8db0dfed4de476bd2cf3e | d21e4c41bb30454a7832ab03fefa3e2b3ec430f0b9c8db0dfed4de476bd2cf3e |
| 02_前馈线性加速器.md | 256577be6408d294f36dd654b171757cda81209e4291895722fa742cb207d252 | 256577be6408d294f36dd654b171757cda81209e4291895722fa742cb207d252 |
| 03_前馈线性加速器SoC集成与综合.md | 24f2c7a99d34766dc874d384521f6db5028395e31e77fc5db8124aeeb74ef994 | 24f2c7a99d34766dc874d384521f6db5028395e31e77fc5db8124aeeb74ef994 |
| 04_单头注意力模块.md | 43555690008e1002d7c2e940fdda2993ddcf8b1a560f7670b4d1f363c348f854 | 43555690008e1002d7c2e940fdda2993ddcf8b1a560f7670b4d1f363c348f854 |
| 05_单层编码器.md | 93d2003bc8c9180f41aeafde37e30236534174dd3a73fd574d75c4a4fd1b74e6 | 93d2003bc8c9180f41aeafde37e30236534174dd3a73fd574d75c4a4fd1b74e6 |

实际核心源摘要与报告/稳定handoff吻合：DOT64=`7abcca0b102c351a0c8979a8b2ed7c131e79f44f672aec2aa039862d8986bccc`；FFN1=`177cbc5e5e589f00e665460c691ea656f398c857911502a9508fdd6038286dce`；ICB=`99ce0d0ce989abc15a70ee1072ed30fc55d9485bd22f91e3ae9e2f4f3762335f`；core=`95b611aabff1f939e7f052d25d5a6b83d8984db57a683751d0cdd9448badead2`；nonlinear=`5862a8383fc93ab4e289d84eee5ccac63957bd7b7e300d6c5ac6beb0d3aa7501`；FP32=`e9d83e2e1d5263a77e3fa830b2e4a395a8d0b1d3b7f59a7771120e77d77b47bb`；同步RAM=`00bc129034fa6e415ed753c5d5ab9f5e44c6e40670e307f92eff6df4b96edab4`；独立C=`fc6b92a7f531ab3bddec97532940207d76c90b367d37591950b769b87fde6ea8`。

## 交回总控

本范围P1=0、P2=0、P3=3；建议关闭上述文档建议后进入第二轮完整证据、数量、冻结绑定和复现审查。01—05若再改动正文机制，应按新摘要回读受影响部分。06/07完成、全文件链接/manifest、旧硬件运行真实退出、根控接受和第二轮独立结论仍分别验收；本文件不替代这些完成门。
