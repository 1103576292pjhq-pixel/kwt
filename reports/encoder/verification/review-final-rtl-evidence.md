# 独立最终 RTL 证据审查：15 个完整输入与独立重复

审查人：`/root/encoder_independent_review`。记录日期：2026-10-15。源码与稳定记录哈希回读：`2026-10-15T14:36:44Z`；总控扩展回读记录的当前绑定复核：`2026-10-15T14:40:06Z`。

本轮在下述冻结快照和证据范围内未发现新的 P1/P2。15 个唯一输入均真实完成 12 层，另有独立进程重复任务；本审查直接逐 word 比对全部最终 RTL 层输出，并核对执行、源文件、输入和产物绑定。**本记录只关闭这部分 RTL 最终证据审查，整体七项本地初稿尚未接受，正式外部验收也未接受。** 两条 E203 CPU 完整任务在本次观察时仍在运行，不从其局部进度推导完整通过或性能收益。

## 1. 范围、所有权与证据归属

本轮只读检查已结束的 RTL 任务、当前 gate/report/unified 源码以及相关稳定记录；唯一写入文件是本 Markdown。未改生产源码、冻结清单、运行产物、状态或其他报告；未启动仿真、长期 runner、综合或 Git 操作。

证据分为两类：

- 本审查直接执行：15 个完整输入及独立 repeat 的最终输出逐 word 比对；192 条层完成日志；源、输入、构建、执行命令和输出哈希；首例 trace 的文件哈希和行数；总控逐值回读记录与当前产物绑定。
- 明确复用：首例 trace 的 1,603,800 项逐阶段数值比较由总控实际完成，见[总控独立回读记录的稳定快照](root-rtl-readback-snapshot.json)。本审查没有重新逐值比较这些 trace 项；仅在确认该记录的 case 状态哈希、冻结哈希和当前 trace 摘要仍匹配后复用其结论。该记录自身不是 CPU 或整体通过证明。

本轮未重新执行 FP32 回归、非线性双仿真、负测、变异、综合、官方误差或分类测试；这些只能由各自有效记录和统一门禁承担，不能算作本审查新增执行次数。

## 2. 实际命令与核验方法

实际执行的是 PowerShell 向 Ubuntu-24.04 的 Python 标准库只读探针传入 stdin。所有文本按 `encoding='utf-8'` 读取，Python 使用 `-B`；探针没有保存文件或调用硬件仿真器。命令外形如下，其中 here-string 为本轮实际执行的校验代码，并非一个已落盘的复现脚本：

```powershell
$reviewProbe = @'
# Python 标准库：pathlib/json/hashlib/re/time；只读核对下述全部约束
'@
$reviewProbe | wsl.exe -d Ubuntu-24.04 --exec python3 -B -

Get-FileHash -LiteralPath work/encoder_source_freeze.json -Algorithm SHA256
Get-FileHash -LiteralPath scripts/formal_seven_gate.py -Algorithm SHA256
Get-FileHash -LiteralPath scripts/encoder_report.py -Algorithm SHA256
Get-FileHash -LiteralPath scripts/run_formal_seven.py -Algorithm SHA256
```

成功探针的实际回读耗时为 22.82 秒，读取并计算 714 个不同文件的 SHA-256，写文件数为 0，启动仿真数为 0。每个被缓存的文件均记录 `(size, mtime_ns)`，再次访问及结束时复核，未见校验过程中变化。stdout 每完成 4/16、8/16、12/16、16/16 个任务打印进度，最终打印计数与摘要；本报告没有补造一份历史运行日志。

具体检查包括：

1. [batch/status.json](case-batch/status.json) 为 PASS，目标和结果均为 16；每项 exit code 为 0、状态记录 SHA 匹配。最终 `*-process.json` 与对应 batch 结果相等，外层 wrapper 日志摘要匹配并含对应 case wrapper PID。
2. 15 个 `(reference, sample_id)` 与已放行的原始 3 例及 test12 manifest 集合完全相等，无重复或遗漏。全部任务为 Verilator/full、几何 `[99,64,256]`、12 层、76,032 word、零 bit mismatch。
3. 每项 case 的 `run_id` 属于本 batch，且起止时间落在外层记录区间。全部 `source_sha256`、`compiled_source_sha256`、`input_sha256` 指向当前文件；冻结清单和 FP32 handoff 绑定一致。
4. 实际 binary、compile log、build key、output、simulation log 摘要一致。`build.json` 源映射、参数和仿真器一致；`commands.jsonl` 中在记录时间区间内恰有一条匹配实际 binary、cwd、完整 12 层及 CASE/WEIGHTS/OUTPUT 参数的执行。case/weights 别名解析到对应的已放行目录。
5. 每个 `output.hex` 与对应独立 C reference 的 `layer_00/y.hex` 至 `layer_11/y.hex` 顺序拼接结果逐 word 相等；检查 8 位十六进制格式和有限 FP32 值。该检查覆盖每层全部 6,336 项，不只检查 CLS 或最终层。
6. 每个日志恰有层号 0..11 的完成条目、非零 cycles、6,336 word 及有效 flags，并有整任务完成标记。未以手工 PASS 字段替代这些核验。
7. repeat 与 baseline 的 wrapper PID 不同，repeat 开始时间晚于 baseline 完成时间，全部输出及其摘要相同。

一次早期只读探针假设最终 `*-process.json` 仍含启动阶段的 `pid` 字段，因 `KeyError` 停止。查阅 `dv/encoder/run_cases.py` 后确认该文件按设计被最终 batch 结果覆盖；成功探针依据实际最终格式，并交叉核对 case status 与 wrapper stdout 的 PID。此探针错误不是硬件失败，也没有据此补造 PID 或历史记录。

## 3. 实际数量、独立重复与 trace

| 核验项 | 实际结果 |
| --- | --- |
| 唯一完整输入 | 15：原始 3 例与已放行 test12 的 12 类 |
| 完成进程 | 16：15 个 full12 与 1 个独立 repeat |
| 唯一输入完成层数 | 180 |
| 含 repeat 的层完成日志 | 192 |
| 每层完整输出 | 6,336 word |
| 每个 full12 输出 | 76,032 word |
| 直接比对的唯一输入输出 | 1,140,480 word，即 15 × 76,032 |
| 直接比对的 repeat 输出 | 76,032 word |
| 层日志 cycles 范围 | 21,195,605 至 21,215,415 |
| 观察到的层 flags | `01`；不把该 flags 字符串解释为零异常 |
| 本审查核 trace 长度/摘要 | 1,603,800 行；逐值结论按第 1 节复用总控 |

唯一输入集合为：`eight_750e3e75_nohash_0`、`eight_d3831f6a_nohash_3`、`synthetic_zero_silence`，以及 `test_silence_f5468c2d20ff`、`test_unknown_e91f8064d134`、`test_yes_795e7f0e313a`、`test_no_8aff1c5be5cd`、`test_up_881a2c08ed53`、`test_down_1152a0e46d9d`、`test_left_d655cc09599d`、`test_right_8b391618c74c`、`test_on_635ab4eca05d`、`test_off_82e3b78115e2`、`test_stop_fe3ae7607e96`、`test_go_18d77869a349`。

本 batch 的 `run_id` 为 `5dfbbc274c4f4f1a8a2cc0fadc4c45fb`。[baseline](../rtl/full/original-0/status.json) wrapper PID 为 749，记录区间为 `1792069153.332566` 至 `1792069922.9352493`；[repeat](../rtl/repeat/status.json) wrapper PID 为 2590，区间为 `1792073338.999183` 至 `1792073970.5414186`。上述是本审查实际交叉核过的 wrapper 身份，不将其冒充仿真 binary 的 PID。repeat 是后续新进程，输出 SHA-256 与 baseline 相同：

```text
ae7f60afa77bd974c7f82c3b3333cc9c746768cea90efc71eb53725c48198fea
```

[首例 trace](../rtl/full/original-0/trace.txt) 当前 SHA-256 为 `91cf5bbe1439ed6333c4488b2c34dd0c1bb5915a588dded0fb2d84c32751989a`。初次 22.82 秒探针绑定的总控记录摘要为 `a5080ceda780602ad6b30bccebb287599973eb4e50f3923fa397d35cd01b90a1`，当时记录 15 例、1,140,480 个输出 word 和 1,603,800 项 trace 逐值比较。

该总控记录于 `14:37:41Z` 更新为额外纳入 repeat 的 16 进程、1,216,512 个输出 word，trace 数量保持不变。最终文件回读识别了这次变化，没有把旧摘要冒充当前值。`14:40:06Z` 补充只读探针核对新摘要 `d58c377a4fec0e74e7d5f66e90b67a29b940820c3a9a919f587b54e0414a3d18`、全部 16 份当前 status SHA、16 个实际 output SHA、冻结 SHA 和当前 trace SHA 均匹配，且 `overall_local_draft_accepted=false`；未重跑硬件或 trace 逐值计算。原记录可能由总控继续更新，因此主线另外复制了[稳定快照](root-rtl-readback-snapshot.json)，本审查独立只读核对快照与当时原件 SHA 完全相同。本文当前引用绑定该快照，同时保留旧摘要的观察历史。最终 review 应绑定稳定 case/repeat/trace、快照和本独立审查文件，避免把会周期更新的原总控 JSON 作为长期不变输入。

## 4. 绑定的审查快照

以下 SHA-256 对本轮结论的适用范围作精确限定；源码改变或对应产物被改写后，应重新核相关证据。

| 文件 | SHA-256 |
| --- | --- |
| [source freeze](../../../work/encoder_source_freeze.json)，含 192 个文件 | `4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17` |
| [formal_seven_gate.py](../../../scripts/formal_seven_gate.py) | `dc2483a43acd314f783d274d61946c9c904a595700f4cf6b2060ae87cd16c494` |
| [encoder_report.py](../../../scripts/encoder_report.py) | `19bcaa1ea765eef403ed2cebd2398d0cce48e6923251b6f4597c0ea1a5dcafd7` |
| [run_formal_seven.py](../../../scripts/run_formal_seven.py) | `93f145eb3a527a1ec89e6ddc5f5744300dfcf428a44c944ccc8d84ebe85ceb8f` |
| [run_encoder.py](../../../dv/encoder/run_encoder.py) | `ac79d63160a1b15702cd13d305ffd2b9ab7de8a34f1a3e792a5227071f909b95` |
| [run_cases.py](../../../dv/encoder/run_cases.py) | `5d867dfda8e44cf6d5c873410bb70c65e71383dcf81c09a1b4f87c115395eed6` |
| [case-batch/status.json](case-batch/status.json) | `b52c9840a5129ce2de3bd76d3814731a4e92348c72cd02b6ed0ebdc86f1d8835` |
| [baseline status](../rtl/full/original-0/status.json) | `adced1dd6bf4e0a275d151a98031ae605a62136c31e99738198a6b79a1828513` |
| [repeat status](../rtl/repeat/status.json) | `22a5f87f4c08c1112cec0eeb98ba1ac5f69e02a3c5e49d3c5a5143c044a2a7c0` |
| [总控逐值回读记录稳定快照](root-rtl-readback-snapshot.json)，与 14:40:06Z 原件相同 | `d58c377a4fec0e74e7d5f66e90b67a29b940820c3a9a919f587b54e0414a3d18` |

## 5. gate/report/unified 静态收敛审查

在第 4 节快照内，未发现需要改变冻结生产源或当前门禁/报告接线的新 P1/P2。这里是源码静态结论，并不表示已执行最终统一流程。

**Gate。** 已知记录路径或显式 expected kind 在可选检查前选择必需 schema，不能用仅含 PASS 与 source 的残缺记录通过 checks/nonlinear/synth/mutants/FP32。RTL 分支检查当前输入、编译源、binary/build/log/output、full12 几何与 C 输出、15 例集合和独立 repeat。CPU 分支在身份检查后实际调用 `validate_cpu_consumed_files`，核对暂存 input/expected、已放行 weights 目标及 12 层文件、由实际 ELF 经 objcopy 派生的 bin/hex、精确 BYTES，以及时间区间内唯一的匹配命令。最终 review 要求明确 `pending=false`、至少两份非空审查文档、当前 freeze/gate 源和全部必需最终证据输入绑定；15 个 RTL 输入通过本身不足以升级整体状态。

**重要的历史绑定边界。** CPU gate 计算的 `verified_runtime_artifacts_sha256` 是执行完成后对实际暂存文件的回读。冻结 runner 没有生成暂存副本的运行前哈希；本轮没有补造该历史证据，也不把执行后回读描述成运行前快照。已有 canonical reference 和生产源的运行前/后绑定仍按原记录保留。ELF/命令/暂存产物一致性检查能验证当前证据的自洽性，不能证明整个运行区间内从未有外部改写。

**Unified。** 复用路径使用 typed validators；新运行检查 exit code、run_id 与时间新鲜性。相同源码 freeze 具有幂等复用路径，避免无意改写冻结摘要使已结束 case 失效。最终 gate 必须属于本次调用且 PASS，之后才生成报告。两条 CPU writer 完成并完成最终独立 review 后才可进行最终统一复用验收；`--gate-only` 只是证据回读，不能算一次新增硬件执行。最终 review 应绑定稳定的原始状态记录，不绑定会重写的 `gate.json` 或总状态来制造循环依赖。

**Report。** 现有计数明确区分 CPU sysmem 读写与 host 逻辑内存动作；host 参数写入使用实际 host_words，ready 写与 request 读按完成的 HOST_LAYER_LOAD 事件各计一次，模型总量使用各部分相加。预置 fixture、RAM 内部流量和物理 SRAM/byte-mask 不是这些计数。reload 比值使用对应指标的 reload 分母，零分母不输出伪收益，负值保留。CPU timing 的四个不重叠区间应等于端到端周期；命令背压作为其中的诊断计数，不另加到总周期；响应等待已包含在区间内。core busy、CPU 端到端和 IFU handshake 指令计数的含义分开。当前源码能展开 180 层/15 例结果，但仍需最终运行后的 CSV、性能 JSON、报告哈希和链接回读。

## 6. 尚未接受的 CPU 与整体边界

本次约 `2026-10-15T14:34Z` 的只读进度观察：pingpong 为 154,000,000 cycles、已启动 7 层、40,320 neural word、0 CPU output；reload 为 150,000,000 cycles、已启动 7 层、38,016 neural word、38,016 CPU output。live checkpoint 的较早采样显示两条实际 binary 进程仍匹配对应 policy（pingpong PID 716、reload PID 665）。这些是运行中的局部快照，不能作为完整 12 层结果或性能收益。

随后直接回读的[当前 gate](gate.json) 仍为 `INCOMPLETE`：task1..task5 为 true，task6/task7 为 false；缺失 RTL case 列表为空，错误为 pingpong 未 PASS、reload 未 PASS、review 未 PASS。[review.json](review.json) 保持最终证据审查 pending，本 Markdown 不改写它。该 gate 文件和进度会随主线更新，本节记录的是本次观察，不能替代后续最终状态。

两条 CPU 完成后的最短收尾核验应包括：

1. 两条完整 status/exit、实际执行身份与区间、每层请求/加载/完成和 12 层计数；全部输出覆盖、被动监视结果及独立 C 逐 word 一致性。
2. 对当前 ELF 派生镜像、实际暂存 input/expected/weights/bin/hex、BYTES、命令记录与冻结源完成 gate 回读；明确暂存摘要只有执行后证据。
3. 由完整日志重建四段不重叠 CPU 时间，核对其和、真实 host 参数流量、CPU 与模型总量及各自 reload 分母；不重复加命令背压，不把局部层数外推为完整性能。
4. 绑定两条 CPU、15 full12、repeat、FP32/reference、checks/synth 等最终稳定记录，完成至少两轮适用独立审查后，再执行统一门禁及报告生成；回读 exit code、run_id、非空产物、哈希、UTF-8、数量和引用。

本审查没有指定工艺/SRAM 库下的正式 PPA、150 MHz、门级时序仿真、功耗或官方 600 样本证据；这些继续按正式外部待验处理。bit 一致的本地参考结果不能替代官方误差、分类或正式验收。
