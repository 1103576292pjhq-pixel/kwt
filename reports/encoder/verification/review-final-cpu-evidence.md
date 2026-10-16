# 独立最终 CPU 证据与实际性能审查

审查人：`/root/encoder_independent_review`。记录日期：2026-10-16（北京时间）。双 CPU 完整回读完成于 `2026-10-15T15:54:40Z`；最终实际报告接线回读完成于 `2026-10-15T16:03:05Z`。

**结论：本轮适用独立审查通过，未发现未关闭的 P1/P2，可以进入统一门禁。整体本地初稿最终 PASS 仍须统一入口真实退出 0；本文件不代替该退出记录，也不签署正式外部验收。** 两种策略均真实完成同一输入的全部 12 层，所有被动神经输出和规定的 CPU 写回逐 word 匹配独立 C reference。实际 performance、报告和 CSV 与独立重算结果一致。

## 1. 范围、实际执行与核验数量

本轮只读核验生产源、已结束任务和生成报告，唯一写入文件为本 Markdown。未改生产源码、冻结清单、CPU/RTL 产物、其他报告或状态；未启动硬件仿真、综合、长期 runner 或 Git 操作。`cpu_record()` 的 ELF 派生校验调用真实 `riscv64-unknown-elf-objcopy`，只在系统临时目录生成并清理镜像，没有改写工作区固件。

独立实际执行分为两轮：

1. **完整执行与数值轮。** 对两种策略实际调用当前 `formal_seven_gate.cpu_record()`，然后用独立读取、日志解析和整数计算逐 word 比对 C 输出、重建全部计时端点和流量。探针退出 0，耗时 53.574 秒。每种策略核 178 项 source、172 项 compiled source、30 项 input 和 18 项实际暂存工件；另核冻结清单 192 项。逐 word 核对共 152,064 个 neural word 与 82,368 个 CPU 写回 word，均为有限 FP32，零差。
2. **实际报告接线轮。** 不调用报告生成 `main()`，以独立实现重算两份日志的 24 条层时序和全部 10 项比较指标，逐项核对已经生成的 `performance.json` 与 Markdown 表格；核 180 条层 CSV、15 条 case CSV、34 个报告链接及产物摘要。探针退出 0，耗时 42.486 秒，对 303 个不同文件计算摘要；读回期间缓存文件的 size/mtime 未变。另曾实际调用当前 reporter 的纯函数 `cpu_timing()`，其两份结果与独立计算一致。

实际命令通过 PowerShell here-string 向 Ubuntu-24.04 的 Python stdin 传入只读校验代码，均使用 `python3 -B` 和明确 UTF-8。未额外落盘探针脚本或伪造历史日志：

```powershell
$reviewProbe = @'
# Python 标准库独立回读；完整轮另实际调用 gate.cpu_record()
'@
$reviewProbe | wsl.exe -d Ubuntu-24.04 --exec python3 -B -
```

完整轮的实际仿真命令是已结束运行记录中的下列命令，本审查没有重新执行它们。两条命令各在对应目录的 `commands.jsonl`、正确 cwd 和本次记录时间区间内唯一匹配：

```text
reports/encoder/system/pingpong/obj/Vtb_e203_encoder +BYTES=1512 +POLICY=1
reports/encoder/system/reload/obj/Vtb_e203_encoder +BYTES=1512 +POLICY=2
```

| 执行身份 | pingpong | reload |
| --- | --- | --- |
| 实际输入 | `eight_750e3e75_nohash_0` | 同左 |
| run_id | `d18f738a74a7484ea373579705c2adef` | `33b068f04ba448339d21251dec76f2c3` |
| producer wrapper PID | 404 | 408 |
| started_unix | 1792068888.0707908 | 1792068888.1627572 |
| completed_unix | 1792079029.4323976 | 1792079442.80225 |
| exit_code / 层数 | 0 / 12 | 0 / 12 |
| 完整 neural 输出 | 76,032 word | 76,032 word |
| 实际 CPU 写回 | 6,336 word，最终层 | 76,032 word，全部层 |

PID 是 producer 的 wrapper 身份，不冒充已经退出的仿真 binary 的历史 PID。实际 binary 内容、命令、时间、日志与输出均另外绑定。`commands.jsonl` 保留历史编译：pingpong 共 4 条 GCC 命令，本次区间内恰有 1 条；reload 本次也恰有 1 条。早期附加探针曾错误要求整个历史只有一条 GCC 而停止，之后按当前时间区间修正并完成回读，未修改或补造历史。

## 2. 数值、真实系统路径与公平边界

两策略的全部 76,032 个 neural word 都与 `layer_00/y.hex` 至 `layer_11/y.hex` 的独立 C reference 顺序拼接逐项相等；pingpong 的 CPU 文件等于最后 6,336 项，reload 的 CPU 文件等于全部项。两者 neural 摘要还与已通过的 RTL 原始首例实际输出相同，见[RTL 最终独立审查](review-final-rtl-evidence.md)。本轮没有把 host 参考算术替代硬件执行。

CPU 通过生产 driver 装载、启动、WAIT_DONE、读回与换层；host 在可观察的 CPU mailbox 请求点逐层向公开 shared RAM 供参。冻结 TB 的被动神经监视器核完整输出顺序，CPU 写回监视器另核地址、完整 mask 和数据。完整日志各有 12 个有序 HOST_LAYER_LOAD 与 12 个 START，每层实际提供 49,792 word；CPU 和 host 参数计数均为 597,504 word。

公平性核对包括：相同输入、相同 12 层参数、相同 FP32/格式/几何 `[99,64,256]`、相同 512KiB shared RAM 条件；两个 build key 的源映射在仅归一化各自生成兼容源目录后完全相同，compiler options、FP32 与 E203 依赖摘要相同。实际仿真 binary 的 SHA-256 也完全相同。GCC 命令仅 policy 宏及输出目录不同，生产 C 源和其余 flags 一致。两者使用同一冻结 TB 的 `always #2 clk=~clk; always #33 lfclk=~lfclk;` 时钟激励及相同 Verilator/C++ O3 选项；这不证明任何工艺频率达标。

单层权重为 199,168B，12 层为 2,390,016B；按层供给符合 512KiB 边界，没有声称全部权重常驻。输入在复位前由 fixture 预置，这次 host 文件读/预置不计周期；计时包含 CPU 把输入搬入 encoder。离线预处理、初次文件读取和软件分类头在本计时外。

## 3. 由完整日志独立重建的周期

计时起点是首个实际 MMIO 握手，终点是最终完整输出写回（含该拍）。独立重建使用半开区间 `[begin_cycle, final_write_cycle+1)`，把 12 层的 host 请求、ready 和 START 串成连续边界：

`首个 MMIO → 首层 host 请求 → host ready → START → 下一层 host 请求 → … → 最终写回后的边界`。

每层均满足 `request < ready <= START < next_boundary`，host 耗时恰为 49,792 拍；末层 next_boundary 为 final_write+1。独立检查全部 24 行逐层值，与 performance 的 layers 数组完全相等。

| 不重叠周期组成 | pingpong | reload |
| --- | ---: | ---: |
| 首个 MMIO 至首层 host 请求 | 285,547 | 285,547 |
| 12 层 host 参数供给 | 597,504 | 597,504 |
| 参数 ready 至 START | 28,685,484 | 28,685,484 |
| START 至下一请求／最终写回边界 | 254,784,945 | 261,058,894 |
| 四项之和＝端到端 | **284,353,480** | **290,627,429** |
| 另列：命令端背压 | 0 | 0 |

两者 begin_cycle 均为 4,543；final_write_cycle 分别为 284,358,022 和 290,631,971。因此各自总和严格等于 `final_write_cycle - begin_cycle + 1`。每层 ready→START 均为 2,390,457 拍；最后一层 START 后区段两策略同为 21,489,073 拍。

START 后区段包含神经计算、CPU/ICB 响应等待、输出读回与换层控制，不能称为纯计算时间。`bus_waits` 只统计 `cmd_valid && !cmd_ready`，作为诊断值单列，没有重复加到端到端总和；阻塞完成读的响应等待已在区段中。日志 instructions 是 IFU 有效交付握手计数，不是退休指令数。进程 wall time 也没有被当作策略性能比较。

## 4. 实际流量、合计与比例分母

CPU 侧读写来自 sysmem 实际握手计数，截止最后输出写回；固件在首个 MMIO 前没有 shared RAM 访问。供参 host 每层执行一次请求层号读、49,792 次参数写和一次 ready 写，均位于同一计时边界内。host 不是 CPU ICB 握手。

| 指标 | pingpong | reload | reload 减 pingpong | 相对本行 reload |
| --- | ---: | ---: | ---: | ---: |
| CPU shared 读事务 | 653,640 | 723,336 | 69,696 | 9.635356% |
| CPU shared 写事务 | 6,394 | 76,090 | 69,696 | 91.596793% |
| CPU shared 总事务 | 660,034 | 799,426 | 139,392 | 17.436511% |
| CPU 32 位字事务折算字节 | 2,640,136 | 3,197,704 | 557,568 | 17.436511% |
| host 参数写 word | 597,504 | 597,504 | 0 | 0% |
| host ready 写 word | 12 | 12 | 0 | 0% |
| host 请求层号读 word | 12 | 12 | 0 | 0% |
| CPU＋供参 host 逻辑总事务 | 1,257,562 | 1,396,954 | 139,392 | 9.978281% |
| 逻辑 32 位字节合计 | 5,030,248 | 5,587,816 | 557,568 | 9.978281% |
| 端到端周期 | 284,353,480 | 290,627,429 | 6,273,949 | 2.158760% |

合计公式是 `CPU reads + CPU writes + host_words + 12 ready writes + 12 request reads`。各行比例独立用 `(reload - pingpong) / reload`，没有用 CPU 分母替代含 host 的分母。零分母按源码返回未定义，负收益保持负值；此前隔离夹具的零分母、负收益和不同分母复核见[性能口径关闭记录](../../system/review/encoder-performance-closure.md)，本轮未把夹具数字混入真实结果。

上述逻辑总量排除复位前 fixture 预置、encoder 内部 RAM 和被动核验探针；字节量只是 32 位 word 事务折算，不冒称物理 SRAM 端口、逐 byte-mask 测量、物理带宽或能量。当前收益是这个输入、模型与实现的一次完整策略对照，不外推为正式平台全部工作负载的收益。

## 5. 实际报告、CSV 与旧问题闭环

独立接线回读确认：

- performance 的两份 status/log 摘要对应当前已结束 CPU 记录；24 条层时序、四段合计及 10 项指标与本审查独立计算相等。Markdown 中每一行数值、相对 reload 百分比与标签一致。
- 报告明确两种策略使用同一实际输入 `eight_750e3e75_nohash_0`，整机覆盖是该输入两策略各一次；没有把 15 例 RTL 覆盖改称 15 例完整 CPU 覆盖。
- 层 CSV 恰为 180 行，case CSV 恰为 15 行；键集合与 gate 的 15 个唯一输入完全相等，每例层号 0..11 无重复遗漏。逐行 cycles、word、flags 和 status 路径与实际日志相符；case 的输出/状态 SHA、76,032 word、12 层、wall time 和周期合计相符。该轮对 CSV 与原始日志/产物回读，不重复执行已完成的 RTL 数值仿真。
- `report-artifact.json` 的 generator、report、gate 和三份 derived 产物摘要均与观察时实际文件一致；报告严格 UTF-8，无替换字符，34 个本地引用全部存在。
- 报告明确 host 边界、暂存摘要的执行后性质，以及正式工艺/SRAM 库、150MHz、PPA、门级时序、官方 600 样本与目标平台正式十二项整机性能的外部待验边界。

| 先前问题 | 本轮关闭依据与局限 |
| --- | --- |
| P1：残缺记录可删除类型字段绕过工件检查 | 当前 gate 按路径/类型先强制必需 schema；原三项最小负例及变异在此前独立隔离复验中均被拒绝，见[证据修复记录](review-02-evidence.md)。本轮 gate 源仍是已关闭问题的 dc2483 快照，没有把旧错误记录放行。 |
| P1：只绑定 canonical/ELF，未核实际暂存 input/expected/weights/bin/hex/BYTES | `cpu_record()` 实际接线 `validate_cpu_consumed_files()`；本轮两条真实任务分别完成 ELF objcopy 派生及 18 项暂存检查。此前两策略原始篡改、自洽 bin/hex 篡改、时间越界和重复命令隔离负例均已独立复验拒绝。本轮未把这些历史负测计作新增硬件运行。 |
| P2：CPU shared 计数误称全共享流量、比例分母混淆 | 当前 reporter 分列 CPU、host 与逻辑合计；本轮对真实 10 项指标逐项独立重算并核报告，分别采用对应 reload 分母。 |
| 构建输入、参考释放、fault/flags 与冷启动问题 | [首轮设计修复记录](review-01-design.md)保留原问题与修复证据；当前 192 项冻结源、实际编译闭包及输出仍匹配。本轮没有重新声称执行旧 FP32/负测长回归。 |

上述范围内当前 open P1＝0、open P2＝0。执行后暂存摘要的历史局限已明确公开，不把它包装成不存在的运行前快照。

## 6. 稳定来源与 CPU 产物摘要

这些文件限定本次 CPU 与审查结论；CPU 两目录的 status 内还保留完整 source/input/compiled-source 映射。最终报告回读时已重新核对各映射当前内容。

| 来源 | SHA-256 |
| --- | --- |
| [192 项 source freeze](../../../work/encoder_source_freeze.json) | `4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17` |
| [gate 源](../../../scripts/formal_seven_gate.py) | `dc2483a43acd314f783d274d61946c9c904a595700f4cf6b2060ae87cd16c494` |
| [reporter 源](../../../scripts/encoder_report.py) | `7c58df30fe5e456fc6722f5f95e4df43fb4867c0872f3b9054847758075db748` |
| [unified 源](../../../scripts/run_formal_seven.py) | `93f145eb3a527a1ec89e6ddc5f5744300dfcf428a44c944ccc8d84ebe85ceb8f` |
| [CPU runner](../../../dv/e203_encoder/run_system.py) | `7330b0328c1b1e6e62deb7a3fc5a0968c704f468674166d824f6a4928405abd0` |
| [CPU TB](../../../dv/e203_encoder/tb_e203_encoder.sv) | `94b365ff6d4838bd31dfb9b1740c88eb1288f4cdbb342110c9bdaecf61f0387c` |
| [生产 driver C](../../../sw/encoder_driver.c) | `e1e41b1ba3d51b60e5f83251546ba1e53eaa5439c48e7daa798e9c8591d67830` |
| [生产 driver H](../../../sw/encoder_driver.h) | `42813787dce0efda8fc5d93e289525584305e7cf94c289613082cd557797d6db` |
| [固件 main](../../../sw/e203_encoder/main.c) | `00edaaa323ddb7a49be7f6fa126bcc16ec3abeb70faa6a88a3250057322d441e` |
| [已冻结的 RTL 独立审查](review-final-rtl-evidence.md) | `7acd85aa11d609841824d7a1d73c37427ed7fa983a6026a0df9d38c6faa5048a` |

下表分别对应[pingpong 目录](../system/pingpong/status.json)和[reload 目录](../system/reload/status.json)：

| 工件 | pingpong SHA-256 | reload SHA-256 |
| --- | --- | --- |
| status.json | `a7f02731525f35de51b14b704f68034f71068a61baa0a37d39da39385e1890ef` | `774e2f0b5079dd024c5f1f717612e42de39a1781bae48b9f9816d2d626bd61df` |
| simulation.log | `989a08e64020affa6889e55ea5e8ea4fc5bdb5d575b2d5d1f43df1e998b468d3` | `2273ac3e495802759bb5faab620b8c226e3f6144ccd8df75291e3a9edb133597` |
| build.json | `7b57824712d764e3fc44ca31d92b234a6b08884ea15fcb652bbcb3529c5bb4c4` | `c2f8bc40b1dcdf74aed7150a569664e7e6c88391c029b39079c41e469c67b47b` |
| firmware.elf | `2fce9e7173223b03efe5052a26d9a4313ac4160c244c7e30cb54cac324136f99` | `00cf203b6349bb9f13fa4110eef006da54a59d77235a05ca7637872e51148607` |
| firmware.bin | `495932537dc787acd0b0d70b3b22a52ee7028d333e6d2fe6ee5449245b8ea234` | `50d81ec4bc9352ba8ba96985920782c0bbe7763b1754b0e8bb06b6cb59e36e4e` |
| firmware.hex | `e99ca8c37d6c94c6b1ecae2e0661b88d896bc5a9cfa93608db2fcd053e514afb` | `4d07aa328c74fe33f0dd4cee0389729253ef27033fb86554a7c247ba1fd7fb65` |
| commands.jsonl | `861e3fa9efdfc55c15ea7d37f8455a32531087ac848f3964f8634c3ef68fa0db` | `89f6df6f848b6cc55034ef14050085f65db18570fb5acb2322a1a0d5080a7113` |
| cpu-output.hex | `fe75d03d9e95952d3ffe80440ec3b355b17d34d2ef49091e4419527c54f9ae40` | `ae7f60afa77bd974c7f82c3b3333cc9c746768cea90efc71eb53725c48198fea` |

两者 binary SHA-256 均为 `f3757e5e36e51fd8c67140ed2992f6b2074fae48a8699113880a6435ea071bf9`；neural-output.hex 与暂存 expected.hex 均为 `ae7f60afa77bd974c7f82c3b3333cc9c746768cea90efc71eb53725c48198fea`；暂存 input.hex 均为 `e9782df2afe3870050d410ed8cee38d6d4c7c67533a36232edba088a2a3186f0`。两套 bin 均由各自绑定 ELF 实际 objcopy 派生，长度均为 1,512B；hex 逐 byte 相等且 BYTES 精确匹配。12 个 weights 文件的当前目标及内容与已放行参考完全一致，其逐项摘要保存在 status 的 input 映射及 gate 派生的 18 项消费工件映射。

**历史边界：** 这些暂存工件摘要是执行后验收回读，不是运行前快照。冻结 runner 未对暂存副本单独保存运行前/后摘要；没有补造该类证据。canonical 参考、生产源和实际 binary 的原始前后绑定仍按运行记录核对。当前一致性不能证明运行全程没有任意外部改写。

## 7. 当前生成物观察快照与最终门

下表仅记录 `2026-10-15T16:03:05Z` 实际已核的生成物；它们将由统一流程合法重写，**不是必须永久保持的哈希约束**，也不作为 review 的循环输入。统一完成后由主线核当次 generator/gate/report/derived 摘要、本次 run_id 和实际 exit code；无需为报告时间戳变化改写本审查。

| 观察对象 | 当时 SHA-256 |
| --- | --- |
| [prefinal gate](gate.json) | `81aa8d7b99bdd71f6d123ba50f353ff64f9b2a8edf556f5d9b0ce4e9e05582e7` |
| [实际 performance](performance.json) | `c671f0e16beb748e0d2fea6426c679afd0b397ce10a57cd99ed7e246c3a83b04` |
| [实际报告](report.md) | `de4a49fc1a1f6257d0b43a02c90ba7e9b6e518c94f03568a524a5a1c13454eb6` |
| [报告产物摘要](report-artifact.json) | `7bb5234af8b61f7ad55763c8574402351ea5f2a3041733df792c9e790b128bae` |
| [层 CSV](rtl-layer-results.csv) | `fa9a6860bf50763f38ca4ec506094c5d78d6c7416f1db8e37bf0dcbc4fdd88ce` |
| [case CSV](rtl-case-results.csv) | `50167d6723514b65d3400ea7aef45a8691433182f6b2b27ddcd39cf8f201f495` |

实际直接回读的 prefinal gate run_id 为 `c4be7ad1e522422784b6788fead0f29b`、状态 INCOMPLETE，task1..task6 为 true，task7 为 false，missing_cases 为空，唯一未通过条件为 review pending。主线报告该次 gate 实际 exit1，与文件状态一致；本审查没有把它改称 exit0。

现有独立 RTL 审查与本 CPU/性能/报告审查共同满足本轮独立审查范围，允许主线绑定这些稳定记录、填写真实 review 元数据并执行统一入口。**只有统一入口当次实际 exit0、当前源/输入/执行/输出/日志/报告绑定均通过后，才可宣称本地七项初稿最终通过。** 本文冻结后不因统一流程重写报告而改写；若稳定 CPU、冻结源、gate/reporter/unified 源发生实质变化，则须另行审受影响部分。

正式外部待验继续保留：组委会 E203 平台/接口、工艺与 SRAM 库、150MHz 时序、面积、功耗/能量、门级时序仿真、官方 600 样本及 Top1 下降限制，以及目标平台正式十二项整机性能评测。本地 bit 一致、generic 综合和本输入的真实策略收益均不能替代这些证据。
