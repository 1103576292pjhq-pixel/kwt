# 正式七项本地初稿验证报告

此报告只统计完成门已经核对的当前源码证据。正式比赛平台、工艺/SRAM库、门级时序和600样本验收单列外部待验。

生成时间：2026-10-15T16:31:28.600649+00:00。当前状态：**READY_FOR_REVIEW**；通过本地门 7/7。

| 项 | 本地交付 | 当前完成门 |
|---|---|---|
| 1 | 乘累加与数值处理 | PASS |
| 2 | 前馈线性加速器 | PASS |
| 3 | 前馈SoC集成与generic综合 | PASS |
| 4 | 独立单头注意力 | PASS |
| 5 | 单层编码器 | PASS |
| 6 | 十二层与参数调度 | PASS |
| 7 | 编码器综合与性能分析 | PASS |

唯一完成状态：[work/encoder_status.json](../../../work/encoder_status.json)；逐项检查和缺口：[reports/encoder/verification/gate.json](gate.json)。旧源 PASS 不重新绑定到新源；修复后重新执行受影响验证。

## 数据、数学与位真边界

输入是官方离线预处理后的完整99×64序列。RTL先生成全部K/V，逐query计算Q、score×0.125、稳定Softmax、context、Wo与偏置，再做两次残差/PostNorm和FFN。每层所有6336个输出必须验证，不能只验证CLS。生产CPU仅搬运、发命令、逐层加载参数和读回。

独立C参考固定逐操作binary32舍入和左到右FMA顺序；RTL必须逐word零差。官方GELU为erf，初稿采用冻结的tanh近似；与官方模型的误差和分类变化单独报告，不混作位真门。

| 参考批次 | 输入 | 完整层 | 层输出word | 最大最终NRMSE | 与官方预测相同 |
|---|---:|---:|---:|---:|---:|
| 原三输入 | 3 | 36 | 228096 | 0.0004071640493761876 | 3 |
| 公开test十二类工程子集 | 12 | 144 | 912384 | 0.000513838042935309 | 12 |

原三输入为两个真实unknown音频及合成零静音；公开test十二类按类别抽取，不按预测正确性筛选。预测与官方相同不等于分类正确，十二类工程覆盖也不构成600样本Top1结论。

来源、162张量/607308参数、49792word逐层打包及全部bin/NPY/hex回读：[work/encoder_reference_handoff.json](../../../work/encoder_reference_handoff.json)；模型语义：[reports/encoder/research/model-semantics.md](../research/model-semantics.md)。

## 当前冻结源的RTL覆盖

| 参考批次 | 输入 | 完整层 | 输出word | 计算周期合计 | flags | 输出SHA-256 |
|---|---|---:|---:|---:|---|---|
| reference | eight_750e3e75_nohash_0 | 12 | 76032 | 254491585 | 01 | `ae7f60afa77bd974c7f82c3b3333cc9c746768cea90efc71eb53725c48198fea` |
| reference | eight_d3831f6a_nohash_3 | 12 | 76032 | 254492436 | 01 | `30215ae04a74c897ca7cc163792f84d134134bd7a53bb8d2db1810818801da6a` |
| reference | synthetic_zero_silence | 12 | 76032 | 254468303 | 01 | `74a86f237a136607ca713eb6648e3d9b5ada2880c2d79fbe391aff62afe58bb5` |
| reference-test12 | test_silence_f5468c2d20ff | 12 | 76032 | 254501639 | 01 | `ec14f9e4e300fc780e1b4072e1bebabfd47e6a1c667f2f71082c8733abde5450` |
| reference-test12 | test_unknown_e91f8064d134 | 12 | 76032 | 254500990 | 01 | `6bf0215fc34ddcc598f6b7049bad9bb43f0e50bb34d090db31e33b0d5cd83c5a` |
| reference-test12 | test_stop_fe3ae7607e96 | 12 | 76032 | 254496514 | 01 | `cd5ad919b1ac066ec693b27dadcfa42904abf21d07d8c55c4f705e0b367b25dc` |
| reference-test12 | test_go_18d77869a349 | 12 | 76032 | 254502493 | 01 | `ec96852364b437b2876cc36e4030b90386f0d44de636a811d0b7b067d9fac375` |
| reference-test12 | test_yes_795e7f0e313a | 12 | 76032 | 254485338 | 01 | `aa101cdc1fe4d1a64bb3662575d906d5574e5ec5815ffa70b5be23b1fdcce509` |
| reference-test12 | test_no_8aff1c5be5cd | 12 | 76032 | 254496546 | 01 | `04c2a4bf9c68ac965fb7ade3622df5001b137e3c477d55534099e2339fd149f9` |
| reference-test12 | test_up_881a2c08ed53 | 12 | 76032 | 254506386 | 01 | `d02a0c2a107ab8c274fa339db74ac677bafb305e50248ce401d514332d8fa0c4` |
| reference-test12 | test_down_1152a0e46d9d | 12 | 76032 | 254494100 | 01 | `b02bcd4cb0d720069a012054665523bd84baeff60c3622e73a61aa73211ce41c` |
| reference-test12 | test_left_d655cc09599d | 12 | 76032 | 254493411 | 01 | `75e09104b7704dff238d7129a02569dcea4c3550269f913849f15cceee0016f5` |
| reference-test12 | test_right_8b391618c74c | 12 | 76032 | 254507214 | 01 | `7e06f8fcba2e7ce037043b518117bb9dded8ef0ea72b1cbfe356f9e75291ddf0` |
| reference-test12 | test_on_635ab4eca05d | 12 | 76032 | 254492598 | 01 | `5973d76687925e86a4c6426469ce1f64aa50f3955d960a3972d7529adaf17625` |
| reference-test12 | test_off_82e3b78115e2 | 12 | 76032 | 254498531 | 01 | `37082ec5099843d6f157ac7ec08ccee15e3faefba00ef819db8474cc8de686c2` |

实际逐层数据：[reports/encoder/verification/rtl-layer-results.csv](rtl-layer-results.csv)；逐例汇总与输出摘要：[reports/encoder/verification/rtl-case-results.csv](rtl-case-results.csv)。计算周期只统计core busy区间；CPU端到端周期另含装载、等待、换层和写回，不能直接混用。

完整案例的每层都通过公开READ_Y握手读出6336word，并独立再次比较输出文件。首个原始输入还核对全部14阶段；独立新进程repeat必须与基准输出哈希相同。阶段trace是旁路证据，实际功能读回仍由公开接口完成。

小尺寸3×4×8保留0.125缩放，随机/全零两组在Icarus和Verilator交叉；非线性各2030向量含±0、次正规、截断边界、非法域、背压和内部复位中断。source绑定和当前通过范围只由完成门确认。

## 真实E203、512KiB与参数流量

公开E203同时保留FFN1的0x11000000窗口和encoder的0x11010000窗口。共享SRAM基址0xa0000000，输入偏移0x1000、单层权重0x8000、输出0x40000。49792word权重占199168B；十二层encoder参数共2390016B，逐层提供，不能宣称全部常驻512KiB。

host仅在CPU请求层号后写公开共享RAM参数区，每word耗一个真实仿真周期；CPU再通过生产driver搬入MMIO。TB不写encoder内部RAM，不代发CPU总线，不执行神经算术。WAIT_DONE持有真实CPU读事务直到完成或fault，40M拍watchdog；普通STATUS保持即时可读。

本地整机覆盖为同一输入的两种策略各一次完整12层任务；其余输入的硬件覆盖见RTL表。组委会目标平台的正式十二项整机性能评测单列待验。

| 策略 | 实际输入 | 当前记录 | CPU写回word | 被动核对神经word | 实测统计 |
|---|---|---|---:|---:|---|
| 内部pingpong | eight_750e3e75_nohash_0 | PASS | 6336 | 76032 | [记录](../system/pingpong/status.json) |

`E203_ENCODER_PASS layers=12 outputs=6336 neural_words=76032 cycles=284358108 instructions=16716244 mmio_reads=6437 mmio_writes=603879 bus_waits=0 host_words=597504 cpu_weight_words=597504 shared_reads=653640 shared_writes=6394 begin_cycle=4543 final_write_cycle=284358022 end_to_end_cycles=284353480 policy=1`

| 外部readback/reload | eight_750e3e75_nohash_0 | PASS | 76032 | 76032 | [记录](../system/reload/status.json) |

`E203_ENCODER_PASS layers=12 outputs=76032 neural_words=76032 cycles=290632057 instructions=20271323 mmio_reads=76133 mmio_writes=673597 bus_waits=0 host_words=597504 cpu_weight_words=597504 shared_reads=723336 shared_writes=76090 begin_cycle=4543 final_write_cycle=290631971 end_to_end_cycles=290627429 policy=2`


同输入逐层及最终位真一致；外部重载减内部交换：CPU侧共享SRAM事务差=139392，端到端周期差=6273949。这些是当前实现算例，不外推工艺PPA。

| 指标 | 内部pingpong | 外部reload基准 | 节省绝对值 | 相对reload节省比例 |
|---|---:|---:|---:|---:|
| CPU侧共享SRAM读事务 | 653640 | 723336 | 69696 | 9.635356% |
| CPU侧共享SRAM写事务 | 6394 | 76090 | 69696 | 91.596793% |
| CPU侧共享SRAM总事务 | 660034 | 799426 | 139392 | 17.436511% |
| CPU侧32位字事务折算字节 | 2640136 | 3197704 | 557568 | 17.436511% |
| Host参数写word | 597504 | 597504 | 0 | 0.000000% |
| Host ready写word | 12 | 12 | 0 | 0.000000% |
| Host请求层号读word | 12 | 12 | 0 | 0.000000% |
| CPU与供参host逻辑共享SRAM事务合计 | 1257562 | 1396954 | 139392 | 9.978281% |
| CPU与供参host逻辑32位字节合计 | 5030248 | 5587816 | 557568 | 9.978281% |
| 端到端周期 | 284353480 | 290627429 | 6273949 | 2.158760% |

CPU侧按sysmem实际握手计数，包含控制/参数/激活访问。Host参数写由实际写循环计数；每个已完成HOST_LAYER_LOAD事件在冻结TB中包含一次请求层号读和一次ready写，控制访问由这些事件回收。Host访问不是CPU ICB握手。逻辑合计仅含同一计时边界内CPU与供参host，不含复位前fixture预置、encoder内部RAM或被动核验探针；不冒称物理SRAM端口或逐byte掩码测量。差值为reload减pingpong，比例分母采用对应reload口径。

| 真实周期分段 | 内部pingpong | 外部reload |
|---|---:|---:|
| 首个MMIO至首层host请求（含输入搬运） | 285547 | 285547 |
| 十二层host参数供给 | 597504 | 597504 |
| 参数就绪至START（CPU检查、参数搬运和总线） | 28685484 | 28685484 |
| START至下一次请求/最终写回（计算、CPU/ICB等待、读回和换层） | 254784945 | 261058894 |
| 端到端合计 | 284353480 | 290627429 |
| 另列：ICB命令端背压 | 0 | 0 |

四段互不重叠，逐层时间戳及摘要绑定见 [reports/encoder/verification/performance.json](performance.json)。响应等待已包含在START后的区段，未冒充单独测量；bus_waits只统计命令端背压。仿真时钟激励不代表工艺时序达标。

放行与一致边界：[work/MASTER_RELEASE_encoder_reuse.md](../../../work/MASTER_RELEASE_encoder_reuse.md)。计时从首个MMIO到最终完整输出写回，含输入搬运、按层host/CPU参数加载、CPU/ICB等待和调度；离线预处理与主机分类头排除。host加载起止、MMIO读写、共享SRAM读写、真实cycle均在日志记录。

## 负测、源码与实际执行绑定

完成门拒绝陈旧源码、失败子进程、--help/no-op与旧PASS拼接、部分层/输出、错误数据、零周期和不同binary。实际执行必须携带本轮run_id、开始/结束时间；显式历史复用必须重新核对全部来源和产物。

协议覆盖连续装载/缺载拒绝、忙时拒绝、地址/掩码/类型错误、响应背压、同步读、层号和换层次序。定向复位覆盖计算中、同步读等待和未消费响应；故障后完整重装可以恢复。溢出保留真实overflow/inexact，不丢当前异常，也不把终止故障伪装成额外IEEE invalid。

错误ICB响应、错误attention scale、LN偏置和漏末token均由可编译变异验证；错误算法必须在真实仿真中因独立逐word比较失败。门禁单测另覆盖删日志/向量/design、替换输出/binary、假本轮身份。

当前短测：[reports/encoder/verification/checks/status.json](checks/status.json)；算术变异：[reports/encoder/verification/mutations/status.json](mutations/status.json)；FP32冷启动修复：[reports/encoder/fp32/cold-revalidation.md](../fp32/cold-revalidation.md)。

冻结清单：[work/encoder_source_freeze.json](../../../work/encoder_source_freeze.json)。各实际case记录source/input/compiled-source/binary/build-key/结果/日志SHA，CPU另存ELF、map、反汇编、固件image及neural-output。所有需要引用的文件在首次运行后才进入完成门。

## Generic结构与正式外部待验

完整encoder结构及同步RAM：[reports/encoder/synthesis/status.json](../synthesis/status.json)；完整E203/原FFN1/encoder/共享RAM层级：[reports/encoder/synthesis/soc/status.json](../synthesis/soc/status.json)。共享存储的数据进程不含复位，响应状态单独复位。generic综合检查不是工艺映射。

EXTERNAL_PENDING：组委会定制E203平台与接口确认、工艺和SRAM库、150MHz时序、物理面积、功耗/能量、综合后门级时序仿真、官方600样本与Top1下降≤2个百分点，以及目标平台正式十二项整机性能评测。未生成面积、频率或功耗达标数值。

## 初学者入口与一键复现

先读 [入门说明](../../../docs/encoder/README.md) 和 [接口契约](../../../docs/encoder/interface.md)，再追踪同步RAM、FP32请求响应、非线性微程序及core phase。

在Ubuntu-24.04 WSL、工程根目录运行：

```bash
bash scripts/run_formal_seven.sh --reuse-verified
```

该入口逐项核对可复用历史证据；缺失或过期时执行真实回归。当前源码的短测通过后才冻结，随后运行原3+公开12类各十二层、独立repeat和真实CPU两策略。统一命令最后必须退出0，不能从本说明推断当前已经通过。

统一命令与实际退出记录：[reports/encoder/verification/unified/commands.json](unified/commands.json)；有限案例批次进度：[reports/encoder/verification/case-batch/progress.json](case-batch/progress.json)。

自测：为何不同时保存十二层权重？答案：encoder十二层权重约2.39MB，超过512KiB，必须逐层调度。自测：为何不能把旧报告改成新源码哈希？答案：新源码尚未产生那份运行输出，哈希替换会切断执行与产物的证据链，必须重验受影响路径。

独立审查与修复记录：[reports/encoder/verification/review.json](review.json)。未通过项保持false；最终本地接受仍由总控独立复核，正式外部待验不升级为通过。

## 工具与执行边界

| 工具 | 冻结时实际版本 |
|---|---|
| python | Python 3.12.3 |
| verilator | Verilator 5.020 2024-01-01 rev (Debian 5.020-1) |
| iverilog | Icarus Verilog version 12.0 (stable) () |
| gcc | gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0 |
| riscv-gcc | riscv64-unknown-elf-gcc (13.2.0-11ubuntu1+12) 13.2.0 |
| yosys | Yosys 0.33 (git sha1 2584903a060) |

CPU沿用共同启动环境的 `-Diverilog -DDISABLE_SV_ASSERTION=1`，上游条件SVA未启用。验证依据是实际CPU执行、测试台显式fatal、握手/完整输出核对、独立参考和负测；不据此声称运行了上游全部SVA或获得CPU形式化认证。两种策略使用相同Verilator/C++ O3选项和仿真时钟。

逐阶段误差、GELU近似误差和原模型对照：[reports/encoder/reference/VERIFICATION.md](../reference/VERIFICATION.md)；十二类逐层指标：[reports/encoder/reference-test12/manifest.json](../reference-test12/manifest.json)。这些指标来自数值参考，硬件逐位验收另见前文。

| 任务 | 实际命令和日志 | 来源与产物指纹 |
|---|---|---|
| RTL原始首例 | [命令](../rtl/full/original-0/commands.jsonl)；[逐层日志](../rtl/full/original-0/simulation.log) | [摘要与SHA-256](../rtl/full/original-0/status.json) |
| 独立重复 | [命令](../rtl/repeat/commands.jsonl)；[逐层日志](../rtl/repeat/simulation.log) | [摘要与SHA-256](../rtl/repeat/status.json) |
| CPU内部交换 | [命令](../system/pingpong/commands.jsonl)；[逐层日志](../system/pingpong/simulation.log) | [摘要与SHA-256](../system/pingpong/status.json) |
| CPU外部重载 | [命令](../system/reload/commands.jsonl)；[逐层日志](../system/reload/simulation.log) | [摘要与SHA-256](../system/reload/status.json) |

固件文件以每个CPU目录内的 `firmware.elf`、`firmware.map`、`firmware.bin`、`firmware.hex` 和 `firmware-disassembly.log` 保存；ELF、实际binary、输入权重、输出及日志SHA均在对应status记录。所有生成兼容源、实际导入源与编译选项绑定到运行记录，HardFloat vendor保持只读。

日志中的instructions是IFU向执行级交付的有效握手计数，不作为退休指令计数。bus_waits仅是ICB命令端背压；完成读的响应等待包含在真实端到端周期及START后区段内。

测试台在复位前把初始输入预置到共享RAM，这次host预置不计仿真周期；计时包含CPU把6336word搬入encoder。每层host权重供给实际耗一word/周期并计入；离线预处理、初次文件读取和软件分类头排除。固件rdcycle区间从各层参数就绪之后开始，本表使用测试台端到端边界，不把两者混称同一延时。

CPU暂存的input/expected、十二层weights目标与内容，在最终门与冻结参考核对；bin/hex由已绑定ELF重新objcopy派生并逐byte比较，BYTES及命令记录也交叉核验。摘要在gate的verified_runtime_artifacts_sha256中。这些是验收时回读摘要；冻结runner没有为暂存副本单独保存运行前/后快照，未补造该类历史记录。canonical参考和生产来源的前后绑定仍按原运行记录验证。

## 近似误差与工程子集分类

| 数值检查 | 点数 | 误差 |
|---|---:|---|
| exp_neg与double exp | 100001 | max_relative=7.082937654517834e-08 |
| tanh GELU与精确erf | 40001 | max_abs=0.00047341344033435817 |

以下分类来自冻结数值参考与原模型。硬件案例通过完整位真门后，其encoder输出与该参考一致；未过门的硬件案例不因此获得分类验证。

| 样本 | 真实标签 | 参考预测 | 官方预测 | 最终输出NRMSE |
|---|---|---|---|---:|
| test_silence_f5468c2d20ff | _silence_ | _unknown_ | _unknown_ | 0.0004409688557559576 |
| test_unknown_e91f8064d134 | _unknown_ | _unknown_ | _unknown_ | 0.00044962512664722097 |
| test_yes_795e7f0e313a | yes | yes | yes | 0.00040783891773741747 |
| test_no_8aff1c5be5cd | no | no | no | 0.0005076488997145909 |
| test_up_881a2c08ed53 | up | up | up | 0.000435350332204606 |
| test_down_1152a0e46d9d | down | down | down | 0.0004832567400670222 |
| test_left_d655cc09599d | left | left | left | 0.00040731165863615835 |
| test_right_8b391618c74c | right | right | right | 0.0003877071457806996 |
| test_on_635ab4eca05d | on | on | on | 0.0004900900014933154 |
| test_off_82e3b78115e2 | off | off | off | 0.000513838042935309 |
| test_stop_fe3ae7607e96 | stop | stop | stop | 0.0005106392332309515 |
| test_go_18d77869a349 | go | go | go | 0.0004836404470461088 |

当前公开工程子集silence的官方和参考预测均为unknown，其余11项与标签一致；该事实描述不构成正式准确率估计。
