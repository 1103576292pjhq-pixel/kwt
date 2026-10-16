# 主控追加事实与只读入口

2026-10-15 更新，供持久执行主线读取。所有权仍按formal_seven_task.md，以下依赖已经可用，不需要重做旧长仿真。

- work/fp32_handoff.json=PASS，21,291事务×Verilator/Icarus/独立重复，全部五flags逐位一致；5mutants killed，131官方文件不变。基础源已冻结，helper prepare(build_dir)可用。
- work/icb_handoff.json=PASS，36例+独立repeat，912384输出零差；桥源码冻结。
- 真实E203 FFN1首例已PASS，8,595,787周期、25344Y和flags、22976装载、99ACK；其唯一pipeline正独立repeat，work/e203_ffn1_handoff.json未PASS前不要提前接受。
- root已完成当前intcore新signed版本36+repeat；generic核及ICB结构通过，scripts/run_ffn1_synth.sh，reports/system/synthesis-{core,icb}/status.json。四个同步RAM为X16x6336、W16x16384、bias48x256、Y34x256。无正式工艺/PPA结论。
- 新增12类真实公开测试工程子集 data/encoder_test_subset/manifest.json，reports/encoder/dataset/status.json=PASS。完整官方test gzip 112,563,277B streaming SHA+MD5/ETag已核；只保存12个WAV，无按预测正确性筛选。包括官方_silence_、_unknown_及十命令。不是组委会600样本，不是正式准确率估计。
- reference worker会先保留原3输入导出，再独立输出reports/encoder/export-test12和reports/encoder/reference-test12，交接后应使用每类一个完整12层任务补足12类性能工程覆盖；原3及repeat仍保留。
- 只读审查发现run_e203_ffn1.sh直接execPython，若argparse非法或导入NumPy缺失，历史PASS可能留存；正常执行已先写RUNNING且失败变FAIL。新统一gate务必检查当前命令退出码+run_id/开始时间+handoff/result/来源/输出hash，不能只看旧status=PASS。显式复用旧有效证据要核查完整绑定，并明确其历史执行身份；不必为纯wrapper重跑所有CPU。
- 通用runner readiness已从旧3flag扩展到新7flag+cases>=3并通过19实际Windows tests。只读审查另发现多round不能用worker启动时间放过上个失败round的旧READY；root会修复未来worker，新engine gate自身同样要按本次run绑定，不能借旧READY误接受。
- **用户已明确回答A批准复用对比三要素。总控放行凭据work/MASTER_RELEASE_encoder_reuse.md，覆盖原先待确认状态。仅放行外部reload与内部pingpong二选一的真实同口径完整十二层对比，不扩展参数搜索。**
- CPU完整FFN1两轮最终均PASS，work/e203_ffn1_handoff.json和result.json已冻结；root只读审查确认无代算路径。20项Windows runner回归也已通过，未来worker已按roundStarted限定报告新鲜度。
- 独立临时encoder审查看到两项待处理：缺独立attention-only启动/完成/公开读回模式（内部stage6 trace不等于独立外部功能）；run_encoder.py需将全部input/weight/output/trace expected hex与manifest的既有bin/npy摘要绑定，再记录运行前后相同，不能只现场采hash。详见encoder_dependency_request.md最后段和reports/system/review/encoder-advisory.md。
- 最新总gate审查阻断项：reference_release两次attempt返回未加入ready，可能errors已有reference失败仍READY；cpu_record须把CPU实际写回文件逐word比C参考，policy1最终6336/policy2全部76032，不能仅hash+passive neural；checks/status绑定旧source，最终应重跑受影响短checks。详见dependency_request最新段及encoder-system-advisory.md，修复前根控不接受READY。
- root当前给整数原batch刷新review/gate39绑定及--reuse-verified，勿重复该回归。新增总gate必须核对当前实际命令或显式历史复用绑定，CPU --help零退出不代表仿真。

### root 独立参考回读已通过（12:29 UTC）

根控新运行 work/root_reference_readback.py（退出0），独立核71项发布文件SHA、15输入/180层的全部1,140,480个Y words的bin/hex/有限值、每层输入等于前层Y、最终输出等于第12层、12类WAV及标签绑定。证据reports/system/root-reference-readback.json，handoff SHA96841d46...不变。此为冻结软件参考完整性核验，不是RTL/SoC通过；可纳入最终证据索引，无需重复模型推理。

### root 记录已有 E203 仿真配置边界（不要求更改冻结源）

新CPU编译沿用common boot/FFN1已有 -Diverilog -DDISABLE_SV_ASSERTION=1；这是既有编译口径，并非本轮O3优化新加的设置。最终报告请明确：上游条件SVA未启用，验证依据为真实CPU执行、测试台显式$fatal/握手/输出核对、参考位真和负测；不声称已运行上游全部SVA或获得CPU形式化认证。固定两策略编译口径；不要为了速度再关闭现有显式检查，不需仅为补文档重跑已绑定证据。

### root 当前generic SoC产物独立回读（12:42 UTC）

已独立核验reports/encoder/synthesis/soc/status.json的170项当前源SHA、design.json与yosys.log SHA，从e203_encoder_soc真实cell递归可达278个模块；cpu、encoder、ffn1、ram四cell有连接，sharedRAM唯一$mem_v2为131072×32=524288B。证据reports/system/root-encoder-synth-readback.json。仅generic保留层级和存储推断，不含150MHz/物理面积/功耗验收。后续若生产源再变，此回读也必须按源失效处理。

### root 心跳独立回收：原3完整十二层通过

已实际运行work/root_encoder_completed_readback.py，退出0。全部192冻结源及FP32/两套reference manifest匹配；原3新执行的source/input/compiled-source/binary/build/日志/输出全SHA、run_id/时间与freeze绑定均通过。根控独立逐word比较228096个Y，并逐条重比首例1603800个trace（完整168层-阶段、地址唯一无缺），全部对C零差。证据reports/system/root-encoder-completed-readback.json，仅已完成RTL记录通过，不是CPU或七项接受。无需重复这些硬件；继续test12+repeat+真实CPU两策略。CPU当前首层完整、仍计算后续层，禁止从layers=已加载层数误报已完成层数。40tests/schema/finalreview新版本由根控复核agent做只读快照审查中，不影响冻结长跑。

### root 最终统计标签精度

新tb_e203_encoder.sv 的 instructions 字段实际在 CORE.ifu_o_valid && CORE.ifu_o_ready 时递增（第53行），不是从minstret读取的退休指令数。最终报告请标“IFU输出握手次数”，保留原始summary字段不改冻结TB，不写成已退休指令或用它计算退休IPC。端到端cycle与firmware rdcycle按各自既有计时边界报告。

### root 40项门禁边界只读复核完成

reports/system/review/encoder-gate-40-check.md已冻结（5cc5ca18...），当前gate ac30661b/tests fdee6061前后稳定，40tests PASS；内存复制真实PENDING review仅将status改PASS会拒绝，七类固定schema删必需字段均拒绝（包括legacy FFN1综合）。最终review绑定freeze+gate、15case/repeat/双CPU/双综合/checks/FPU/reference的证据集合。约定正常路径无确认P1/P2；没有碰状态或长跑。可纳入最终review索引，但不是对尚未完成CPU/新case的验收。

### root 本次心跳：9个完整案例独立回读

根控重新运行work/root_encoder_completed_readback.py，9个当前freeze完整12层案例/684288 Y words及首例1603800 trace均独立逐word对C一致，source/input/compiled/binary/log/build SHA匹配。reports/system/root-encoder-completed-readback.json已更新并保留前次历史。两种活跃CPU的已落盘完整层前缀也各核12672神经word、reload另12672真实CPU写回word，与同C前缀一致；只读观测reports/system/root-encoder-cpu-prefix.json，不把运行中前缀当全CPU PASS（stdio文件缓冲可能落后neural计数）。192源不变，CLI/runner和实际665/716 CPU、3个RTL binary都已核活跃，继续长跑。最终performance reporter计数口径的窄只读复核由根控reviewer进行中，不干预执行。

### root 15个唯一RTL完整十二层独立回收通过

本次实际运行work/root_encoder_completed_readback.py退出0，已读15个唯一full12案例：1140480个完整Y word+首例1603800 trace对C逐word一致；各case当前freeze、sources/compiled/input/binary/build/log与实际执行身份完整绑定。报告reports/system/root-encoder-completed-readback.json，scope仍非CPU/七项接受。独立repeat还在跑，双CPU第五层，继续完成而不重跑已验证15个案例。root正在窄复核新增51tests消费物P1闭环，性能CPU-only标签P2已前段明确需修（仅报告器），不改冻结硬件。

### root 新51项消费物门禁只读复核通过

reports/system/review/encoder-gate-consumption-check.md已冻结（eb8168b7...），gate dc2483a4/tests6e31edc2前后稳定，51tests PASS。canonical input/expected/12weights、ELF实际objcopy派生bin/hex、BYTES、区间内唯一实际命令已由cpu_record正式接入且与frozen run_system生成路径一致，原消费物P1在正常路径关闭，无新增P1/P2；未要求补造事前快照/未触碰运行中暂存物。唯一仍开的是性能报告“CPU侧”流量限定/host单列P2，reporter c79bb0c7快照尚未修。请仅报告器修复并保留不含host的CPU侧统计真实边界，最终review再接受。CPU和repeat继续，不改192源。

### root 完整RTL+独立repeat最终回收通过

根控实际再次运行completed readback退出0：16进程、15唯一输入，合计1216512个Y word（唯一1140480+repeat76032）及首例1603800 trace全部逐word对C一致，source/input/compiled/binary/build/log SHA与当前192冻结绑定。另独立检查baseline PID749与repeat PID2590不同、启动时间不同、case/reference/source完全相同、完整output bytes及SHA一致。证据reports/system/root-encoder-completed-readback.json与root-encoder-repeat-readback.json。无需重跑RTL；双CPU7层仍RUNNING，整体不接受。报告器性能P2当前已按CPU/host/逻辑合计分列，根控正做最后窄复核闭环，不改冻结源。

### root 性能口径 P2 最终独立关闭

reports/system/review/encoder-performance-closure.md已冻结（23f70c4f...），reporter19bcaa1e及原审查c023e58c前后未变。CPU侧标签/host597504参数+12ready写+12请求读单列、同窗逻辑合计及其自身reload分母正确；不含fixture/内部RAM/被动探针边界明确。reviewer用精确源码AST指标段隔离验证不同分母/CPU零分母/负收益三组PASS、byte比例一致。原性能P2关闭，没有要求新硬件或声称实际收益。该报告可纳入最终两轮review索引，剩余双CPU及其实际收益/最终统一验收继续。

### root 用户合规进度问询已回答

用户刚询问进度与赛题吻合度，根控已重新直读赛题PDF物理页4–5/8–14并做只读交叉复核。已向用户明确：计算结构、NN全部RTL、E203控制/搬运、逐层共享SRAM供参符合方向；本地1–5门通过不等于正式五项通过。本科必做1–3，正式第3仍缺组委会平台/指定SRAM宏、工艺映射SDC/网表、150MHz/面积功耗及综合后功能证据；600数值评测与正式12性能任务尚未进行。第6/7本地初稿双CPU和最终验收继续。用户问询未取消或暂停长跑，不扩大目标、不改冻结源。最新实际两CPU仍活跃、约215M/209Mcycles、192源不变，无新本地阻塞。

### root 最终CPU独立回收已安排

现两CPU实际第11层、192源仍CURRENT。根控已安排普通native只读reviewer有界观察现有两份status（最多30分钟，单次等待≤45秒）；两PASS后独立回读两份76032 neural、policy1最终6336 CPU写回、policy2全部76032 CPU写回，以及身份/消费物/冻结/输出hash和真实统计，写reports/system/review/encoder-final-cpu-readback.md及自有证据。该审查不启动仿真、不改生产/gate/你的报告，不是第二执行主线。你继续按计划自审/最终统一入口；根控最后接受仍须当前round成功退出和最新七门证据，别等人工回复才继续。

### root 共同基础证据最终刷新

已在WSL正确工作区实际运行work/root_common_readback.py退出0：当前源ICB36完整案例912384输出与两flags、真实E203 FFN1完整25344输出+独立repeat25344输出/flags、实际binary/stdout/命令/源/产物和generic四RAM均独立回读通过，reports/system/root-readback.json已刷新；这是显式历史证据重验，没有重启任何硬件仿真。首次误用Windows解释器不能解析记录的/mnt/c路径而检查器失败，已独立保留reports/system/root-readback-history/windows-host-20261015.json；它不是硬件失败，未重绑定旧结果。

### root 两CPU全任务独立回收PASS（最终统一入口仍须完成）

根控native只读reviewer于15:52:36 UTC实际脚本exit0：两份neural合152064word、真实CPU合82368word均对C逐word零差且finite，同input与同neural SHA；192freeze前后全SHA匹配；各178 own/172 compiled/30 input和18消费物及ELF派生/实际命令通过；原实际binary716/665已退出。证据自有reports/system/review/encoder-final-cpu-readback/，最终md正在写（即将可读）。

实测reload290627429 vs ping284353480拍，节省6273949（2.1587601%）；CPU共享799426 vs660034，节省139392（17.4365107%）；含供参host逻辑合计1396954 vs1257562，同差139392（9.9782813%）。仅本地同输入各一次full12，不外推正式12项/PPA。root已读两份PASS原summary确认相符。请继续你自己的最终独立审查/正式回读/统一入口，别等待用户批准或手写true；root最后还须当前round命令成功退出、READY新鲜度与全部最终证据一致才接受。本条不是最终整体接受。
### root 用户已批准报告方案A（2026-10-16）

用户回复a批准首批约6小时、docs/encoder/reports/七份技术报告+需求表/总报告/复现指南、至少两轮独立审查和复用25分钟定时。上游work/report_cycle_plan.md、后续持久任务work/report_cycle_task.md、独立状态work/report_cycle_status.json已保存；自动化ffn1已更新，不会在旧初稿接受时误停新报告任务。你继续当前正式七项最终统一验收，按原任务正常退出，勿接管新报告或等待人工。root当前普通作者只写新目录各自文件，不碰你的源/报告/状态。旧主线真正结束、root独立接受后，root会串行接续后续唯一CMD；不新开并行持久主线，不改变已批准性能三要素。

### root 报告方案A已真实串行接续（2026-10-16 00:50北京时间）

旧硬件CLI于16:44:40Z实际exit0；root实际运行work/root_accept_formal.py退出0并写reports/system/root-formal-acceptance.json（ACCEPTED_LOCAL_DRAFT），当前统一84ef...、192源/15+repeat/双CPU/59审查绑定完整。17个接受证据在新指针替换后全部回读仍当前，旧runner绑定的是reports/system/formal-baseline/runner-state.json，不是动态.omx指针。

11篇技术报告初稿全部存在，作者全释放。新唯一可见CMD已启动并实核：run_id20261015-165042-884，CMD50060/worker69628/CLI63812，session01a14079-2a4c-72a1-bee7-2f17d9a833d1。任务work/report_cycle_task.md，完成门work/report_cycle_status.json，启动事实work/report_cycle_launch.json；旧CMD71400仅保留完成日志，不是活动执行主线。ffn1已更新为本报告方案，勿在旧基线接受时暂停它。

原生cycle_spec_review正在补齐全11第一轮与问题关闭，文件reports/system/report-cycle/review-spec-all.md/.json归它，不能重复派第一轮。01—05原三P3已修；新09的6个输出目录已改为reports/encoder/reproduction/（符合真实runner限制），LN归属已改core；06已精确忙时配置拒绝/ERROR W1C例外。机械检查全11 PASS；checker现9个负例selftest PASS，output路径负例有真实RED→GREEN日志。root已释放所有阅读文件给新CLI，后续文档修复由新CLI负责，不改192生产源、不重跑长硬件。独立第二轮、修复回读、最终manifest和根控接受继续。
