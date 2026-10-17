# CURRENT_ROOT_CLOSURE_ONLY_20261017T0927Z

If this task is loaded in a continuation after the previous CLI has ended, prioritize ONLY the two confirmed root review repairs before any broader work. Original hard stop stays2026-10-17T09:45:00Z; no new architecture or optimization search. Read current STATUS and root_cpu_binding_repair_spec_0847.json, ROOT_FEEDBACK.json and root_final_package_review_0907.json.

1. ROOT-CPU-GATE-IDENTITY-HARDENING-001: implement the precise minimal strict check_cpu offset0 aux-binding plus reproduce consumer bind-before-check, retaining production soc_run.py and all proven RTL/CPU/numeric source bytes. Add missing-binding and changed-executable-digest negatives plus valid existing/fresh positives. Do not repeat twelve-layer arithmetic or36core runs for this validator-only change.
2. ROOT-PKG-W2-README-CLI-001: remove unsupported --sim/--tasks from the generated W2 README command (actual W2 parser accepts --stage small, not these extra options). Validate documented argument acceptance.
3. Preserve previous ZIP and proofs, then refresh final changed-source/manifest/package identity and run one bounded extracted portable --with-cpu if enough time. Existing native exact-byte materialization avoids slow WSL copytree. Keep all old arithmetic evidence, source-hash/AST equivalence and separate targeted gate tests truthful. Independent root acceptance still required.
4. If insufficient time or hard cutoff occurs, save TIMEBOX_ENDED_PARTIAL and explicit last valid candidate ZIP/profile/remaining defects; no fake READY, no deadline extension, no Git writes or global configuration.

The original approved task and scope follow unchanged below.

# KWT RevD/V2 离线评分导向持续执行任务

用户已明确批准立即执行3—4小时，并要求不汇报。工作区只有 D:\github\kwt，分支 v2。先读本任务、同目录 MASTER_RELEASE.json / budget.json / baseline_guard.json 和 score_audit.json、architecture_priority.json、verification_risk.json（后者可能稍后落盘）。沿用执行计划、测试先行、系统调试及独立 RTL/验证审查；不要再问是否开始或继续，不要发布普通过程消息到用户聊天。真实进度只写本轮STATUS、日志和可见CMD。

## 1. 目标、评分与边界

本轮新增授权覆盖 D3—D7 有界候选、赛题提交闭包及必要的本科 P0/P1 本地集成；旧任务的“仅D0-D2”是上一轮范围，不再阻塞本轮。完整定点/混合精度Transformer、额外注意力/分类头重写、新数值格式、无界自动研究仍不做。不要为了凑时间重写大量教学文档。

源题唯一依据 work/report_cycle_sources/2026赛题指南.pdf 和 guide-text.txt（15物理页）；阅物理8—14及来源manifest。务必使用本科评分：功能数值40、SoC/综合/复现20、吞吐8、单任务能耗8、面积4、创新20。后40分先以全部必做、数值/位真、150MHz、面积≤2.25mm²合格为门。先减少硬门/提交缺口，再增加可核对性能/创新证据。不得把最小core周期当总分最大，竞争队最高吞吐/最低面积能耗未知时不报正式分数。

有界变量在 MASTER_RELEASE 中：PM2/4、PN4、micro/CTX4、full-W/W1/W2、Y1/Y2、X4/可选XP2；ICB只一套。不改固定 signed16 输入/权重、64积精确48累加、49位bias加法→sat48→RNE0..47→sat32及两flags。当前误差已小，优先真正系统/架构收益，不用验证/测试数据重新调量化参数。

比较采用分层目标：先功能/数值/提交资格，再同输入/同接口/同停顿种子的实际冷任务窗口；有真实CPU时包括输入参数装载、E203/总线等待、最后写响应。无真实CPU时只标frontend/core代理，不能捏造比赛分值、能耗或面积。面积/功耗未知时保留Pareto候选，不能用理论16MAC或CE比例直接定赢家。若改架构无实测收益，保留已验收方案并报告真实负结果。

## 2. 不可修改项、允许目录和状态

所有旧tracked12313文件及 baseline_guard.json 中的既有 D2/源包/报告/工作记录均只读。尤其 rtl/revd、dv/revd、config/revd、work/revd、reports/revd、docs/revd 全部冻结；D2完成协议缺陷已经独立修复，不能回退其最后输出/完成脉冲入口屏障。既有 numeric/fixedpoint.py、CPU/vendor、数据、驱动和全局配置也不改。

新实现仅放 rtl/revd_opt、dv/revd_opt、soc/revd_opt、sw/revd_opt、config/revd_opt、work/revd_offline_20261017、reports/revd_offline。新增脚本只用 scripts/run_revd_offline.sh、scripts/revd_offline_gate.py、scripts/package_revd_candidate.py（可以按职责新增同前缀revd_offline_*）。候选成品放 deliverables/kwt_revd_v2_candidate_20261017/ 和同名ZIP，过程/构建/失败日志不混进读者根。可只读复用冻结quant/RAM/CPU源，按当前实际文件清单绑定；不能通过修改旧记录让新硬件通过。

Git只读：禁止commit/push/PR、checkout/switch/worktree、reset/clean、Git配置修改或远程发布。禁止覆盖旧fixed OUT的回归脚本：旧 dv/e203_ffn1/run_system.py 会写 reports/system/e203-ffn1 与 work/e203_ffn1_handoff.json，必须改造为本轮新入口/新输出，不能直接运行。旧完整十二层encoder两策略各约2.8h，不在本轮重跑。

唯一新状态 work/revd_offline_20261017/STATUS.json。每阶段进度、候选/选择/失败、剩余、证据与真实PID写入。旧 work/revd/STATUS.json 是接受基线，不得动。所有新run_id全新且拒绝覆盖；每运行绑定包括未跟踪候选源、配置、输入、工具和真实输出的SHA。

不要启动第二条持久runner/Potter，不开别的用户对话、不向外部发消息。可用普通子代理做独立只读审查或明确不同文件所有权的短子任务；它们不是Potter，也不得擅改目标/数值。当前根控已写的audit/priority/risk及MASTER_RELEASE/budget/baseline_guard由根控所有，不能改成自授通过。

## 3. 时间与资源

准确截止以 budget.json 为准。2026-10-17 17:00（Asia/Shanghai，UTC09:00）停止引入新架构；17:35（UTC09:35）前完成选择、回归、交付闭包和两轮审查；17:45（UTC09:45）硬停止，最后35—45分钟只冻结、验证、修复确定缺陷和保留结果。重启不能延长截止。外部watchdog会终止本run所有标记的Windows/WSL子进程。

目标是使用本预算解决更多真实问题，不要完成一个小例就宣告整轮成功。阶段结束且仍有时间，按评分优先级继续。若本地可做项已经全部有新鲜接受证据且后续只缺外部正式资料，可如实提前结束，不空转或反复跑同一已通过测试消耗时间。预算用尽不是通过；未过项标PARTIAL/NOT_RUN并留下最后可恢复版本。

WSL Ubuntu-24.04，/mnt/d/github/kwt；Icarus12、Verilator5.020、Yosys0.33均已验证。DV Python可只读借用 /mnt/c/Users/11035/Desktop/ic/kwt—1/.venv-dv/bin/python（Py3.12/NumPy2.4.6/cocotb2）。WSL默认Python缺NumPy，不要误判整体环境缺失。模型环境独立，不升级TensorFlow，不安装PDK、不下载大库/大数据。确需外部文档只看官方一手，不让联网成为主线。新提交入口必须可选择本机解释器，不能硬编码这个C盘绝对路径。

每个编译、仿真、CPU和综合子进程都必须有小于剩余时间的实际timeout，适当process-group清理并记录PID/起止/退出码。不要留下脱离主线的大仿真；环境中 KWT_OFFLINE_RUN_ID 为本run身份，WSLENV会转发，不能移除它。真实E203完整FFN1/复跑历史各约7min，可在预留时间内做，不能在最后几分钟开长任务。

## 4. 任务与阶段门

### A. 开始冻结及评分/提交映射（尽快，约前15分钟）

- 核 baseline_guard 全部保护字节/HEAD/分支；保护D2仍可复现。
- 将本科必交物逐项映射现有/缺少/可本地补/外部待验，精确公式与物理页写JSON。正式600样本尚未公布/缺少时不拿36例冒充。
- 盘点指定库、SRAM模型/面积表、SDC、RISC-V工具、公开E203缓存；只记录实际存在和SHA。宏仅支持指定16位深度128/1024/4096，容量/端口分账。没有官方库不声称150MHz/2.25mm²/功耗通过。
- 建立可执行离线gate与候选配置/运行清单。原D2 gate硬编码PM4/禁止重叠，只能作冻结对照，不能放宽后拿来签新架构。

### B. 最高收益候选：full-W CTX4 标签流水

- 在新namespace实现CTX4：每个k的X四行向量保持供g0..3使用，各上下文48位部分和，k/g/rowmask/task/valid随流水，最后乘积退休后才能量化。先full W隔离调度，不一次叠加所有优化。
- 当前micro每k是READ→WAIT_READ→ACC，不能假定已有一拍一发射；要追踪真实sync RAM返回、W标签、反馈RAW及停顿信用。能流水才计实际收益；后处理/快照先安全后重叠。
- 先红后绿，覆盖全shift/边界、k63-only、尾3行、连续改参、reset各在途阶段、输入/输出有限停顿、payload/标签稳定、最后输出附近非法已接受事件和下一BEGIN。禁止TB写私有RAM/force/回灌答案。
- 小例→一完整99x64x256→36冻工程例（3输入×12层，总912384唯一结果）→独立进程重新编译至少一个完整例；Y及overflow/saturated/task/index/last全比。raw48在明确公开单元或被动trace核，不虚构顶层raw字段。
- 与D2冻结基线以同数据/同窗口/同输出ready/输入供给比较。实际X/W CE、issue/retire、有效MAC1622016、虚拟lane、load/compute/output/wait/cold frontend全部来自RTL事件，不拿解析数字填实测。

### C. 本科提交资格优先：新核的E203/ICB薄集成与真实写回

- 在上述核心稳定后，优先用现有公开E203接新核，不能把旧SoC PASS挪用。只新建适配/驱动/CPU TB，不改CPU/vendor/旧SoC。
- 新tile结果按y_index=m*N+n写回共享SRAM，不能复用旧TB的index==output_writes行序断言。全部结果/flags与共享内存实际写回逐值核对；system_done必须等最后写响应。
- 单核CPU不能在等待W空槽的阻塞MMIO写中无法排Y；使用非阻塞容量/状态查询、CPU交错喂入/排空、accept和retire分离；测试W/Y满、有界供给/排空公平条件、复位/故障、最后输出与命令同拍。
- 真实CPU执行正式C驱动，不用BFM或Python替代CPU伪装集成。先小例，再完整尺寸与至少一次真实冷参数切换；时间允许则12层冷任务。全36可用于核心，CPU用明确小而完整的层集合。未完成全部CPU范围逐项写PARTIAL，不阻塞已经正确独立核的交付。
- 同一profile收集从输入/参数开始装载到最后共享写响应的CPU/总线计时。core、frontend与SoC窗口分开，不拿FP32十二层旧周期当INT16 FFN1加速比分母。

### D. 剩余预算才扩展D4/D5/D6/D7

- 单W1/Y1分块→W2/Y1→W2/Y2分开比较。仅tile0预载然后START再后续OPEN，防队首OPEN挡START。W末bias引用退休才能释放；Y末握手才能释放；读返回前须留槽。源汇必须并发运行。
- 若阶段B/C仍有确定缺陷，先修/验证而不是叠加新功能。XP2只在CTX4/资格工作稳定且有时间才做，可真实不胜/失败后回退X4。
- PM2×4与PM4×4做固定候选比较，不无界搜索；X4/XP2、full/tiled/W2/Y2必须只发布真正编译/跑完的配置。L1/L2是读取延迟敏感性，不是版本提速对照；更长延迟允许真实气泡且必须正确。
- 有条件做Yosys通用逻辑/寄存器/存储结构检查及真实指定宏组合账本。generic cells、容量或CE只能作代理，不能当mm²/瓦/STA。库/模型缺失则NOT_RUN，避免大阵列错误展开成触发器导致资源耗尽。

### E. 反复检测、选型及本地提交闭包（预留35—45分钟）

- 选择当前最好且完整通过的profile。必做资格、数值、接口失败的候选不得凭低cycle胜出；保留至少一个可靠回退。没有新候选通过也必须保留D2并明确本轮未达架构收益，不能把baseline再跑说成新优化完成。
- 对当前源码再次核完整36/flags/唯一性/尾行/有界停顿/复位/连续任务/非法完成边界与独立新进程复跑；源码变化则其相关结果失效并按影响补跑。少输出、X/Z、timeout、SKIP、缺工具、源码/配置变化均拒绝。
- 至少两轮独立审查：规格/数值/生命周期一轮，测试/来源/交付闭包一轮，修复要有红绿记录。实际编译运行多类RTL变异（漏k63、signed错误、错索引/重复、提前done、返回无槽/owner提前释放等按已实现机制）并说明数量；软件gate负测单列，不能混算。
- 新gate验证真实子进程退出码、参数/源/输入/输出SHA、缺证/错flags/删末输出/错索引/缺末输出边界/假CPU结束/混配置等确实失败。不要只检查文件名PASS或作者手填字段。
- 本地候选包包含所选RTL/数值模型/转换脚本/驱动及真实CPU依赖（如已通过）、测试/运行入口/依赖锁/相应SDC与网表（只在实际生成且核实后包含）、结果/对照/源码和运行manifest/第三方许可/已知正式缺口。README仅写复现和提交操作，不写教学讲义。没有官方工艺内容时提交清单明确缺失，不用占位网表/SDC伪装完整。
- 打包 deliverables/kwt_revd_v2_candidate_20261017.zip 并实际解压至本轮work的全新目录，脱离原ROOT/PYTHONPATH用包内相对入口至少跑数值/短RTL和manifest闭包检查。硬编码C盘venv/原D盘路径不得成为依赖；日志中的历史来源路径可以保留。不要把整个旧0.9GB报告库或虚拟环境塞进候选包，也不能删除复现必需源/权重/许可证。
- 生成 SUMMARY.json：本轮真正完成/不完整、全部候选统一指标、selected profile、实测收益与负结果、正式hard gate缺口、每项证据入口。不要宣称全球最优、比赛全部完成、正式分数或全PPA通过。

## 5. 退出、审查和诚实状态

HEARTBEAT_INTERVAL：20—30分钟更新文件/终端，不给用户发送常规汇报。
SELF_REVIEW_ROUNDS：至少2轮并修复确定问题；根控另作接受。
DONE_CRITERIA：当前所有本地承诺检查通过且包解压复现通过才 STATUS=READY_FOR_REVIEW；submission_checked/regression_checked/score_evaluated/reviews_passed/baseline_preserved/deadline_respected 均为布尔true；completed_candidates为实际通过候选数（含明确冻结对照也要分别标new_profile）；parent_accepted=false、official_contest_acceptance=false。附当前源码/配置/输入/工具与结果哈希及新证据。若只完成一部分，status=TIMEBOX_ENDED_PARTIAL，字段按实际填写，不为了runner退出伪造READY。
BATCH_OUTPUTS：新候选实现/验证/接口和分数资格矩阵、同条件真实周期/访问对照、CPU及工艺缺口、独立审查/修复、便携候选文件夹/ZIP/解压复跑、SUMMARY和STATUS。
BLOCKER_POLICY：已授权范围内普通错误自主定位修复；外部平台/库/正式数据缺失准确记录并继续其他可做项。不问离线用户常规问题。接近截止回退到最后接受profile、保留进度和失败、终止有界任务；预算到期绝不是完成。

本轮根控记录由根控所有；根控独立接受前不得改旧root_acceptance或声称正式验收。完成后安静退出，所有用户可读结论保存在本轮SUMMARY/STATUS和候选包内。

## ROOT_ACCEPTANCE_FOLLOWUP_20261017T0747Z

Before READY_FOR_REVIEW or the next continuation, read ROOT_FEEDBACK.json and root_cpu_gate_review_0747.json. The root-owned independent review confirms current CPU arithmetic/bytes remain valid and the compile/profile/tool/firmware improvements are real. One remaining final gate condition is offset0 expected executable binding: check_cpu must require and consume the existing binary-binding.json, comparing report/executable/firmware/CPU receipt/log digests, and reject missing expected binding plus changed actual binary digest. Preserve normal positives and current-source negative evidence. This is a narrow verification closure within the existing scope, not a request to rerun unchanged CPU arithmetic.

For final packaging include all current runtime dependencies (in particular revd_offline_final_regression.py tool_inventory imported by reproduce.py), use a fresh plan/manifest bound to final bytes, and actually test extracted CPU-small for the selected CPU profile. Old basic preflight has no CPU proof. Final package and two reviews remain root acceptance prerequisites; official gaps stay NOT_RUN. Original budget and single implementation lane stay unchanged.

## ROOT_MINIMAL_CLOSURE_REPAIR_20261017T0847Z

Before final acceptance apply the concrete, bounded specification in root_cpu_binding_repair_spec_0847.json for ROOT-CPU-GATE-IDENTITY-HARDENING-001. Preserve production soc_run.py and existing CPU/RTL reports; prefer strict gate plus reproduce consumer auto-binding after the completed final CPU report. Missing/changed expected binary binding must reject, normal old/fresh CPU must pass. Do not put early auto-binding in soc.main because later layer/baseline/edges wrappers rewrite their final report.

Also read root_package_review_0847.json: current v3 already fixes both W2 executable omissions, so do not repeat that repair. The remaining concrete README command defect is W2 --sim/--tasks arguments unsupported by its parser. Remove those two options in the README generator/documented command, verify argument acceptance, and bind the final package proof to final source/manifest. Preserve previous proofs as history. These are verification/reproduction fixes within the original budget, not new architecture. No Git writes or deadline extension.
