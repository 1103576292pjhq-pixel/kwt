# KWT RevD D0—D2 试执行任务与验收门

> 已获用户批准开始试执行。使用测试先行、逐任务实现、规格审查和质量审查；完成本批全部适用检查后才报 READY_FOR_REVIEW。此文件是执行任务，不是教学文档。

## 授权和唯一工作区

工作区 `D:\github\kwt`，Git 分支必须是 `v2`，来源基线 `3d9d0fc77457b8869cbf525d826dafb114f2a8e1`。放行文件 `work/revd/MASTER_RELEASE.json`；用户最新约束：本轮不写教学文档，测试须贴合题目。不要再次询问是否开始/继续，在本范围内修复并推进。

本批只做 D0、D1、D2：保持原 signed16 数值，先 PM4/PN4 micro、全 X/full W、公开有序输入/独立输出流的完整 FFN1。保留参数化接口，可用 PM2 作基本正确性检查，但不开展最优参数搜索。D3 CTX4、分块/双缓冲/XP2、ICB/CPU/DMA/NICE、综合/工艺/PDK/PPA、完整定点编码器都不在本批。禁止以“长期”扩展范围。

不允许 git init、checkout/switch、worktree add、commit、push、PR、merge/rebase/reset/clean、自动提交或修改远程。Git 只读。工作区里还有其他人；保留现有合法更改，不撤销他人文件。不要启动嵌套持久 runner。

允许新增/修改：`rtl/revd/`、`dv/revd/`、`config/revd/`、`work/revd/`、`reports/revd/`，及新的 `scripts/run_revd_trial.sh`、`scripts/revd_trial_gate.py`。现有 RTL/数值 golden、所有旧报告/数据、CPU/driver/vendor、既有门禁、旧状态和旧 manifest 不修改。不批量格式化，不改全局 AGENTS/skills/环境/模型。根控已放入的 `docs/revd/` 是原包只读快照，不在其中写结果或修改 MANIFEST。

唯一当前状态：`work/revd/STATUS.json`。`work/STATUS.md` 等是旧历史，不能作为本批进度，不要覆盖。新运行使用 `reports/revd/<stage>/<profile>/<run_id>/`，拒绝覆盖旧 run_id。状态不得靠手填 PASS 代替实际退出码/输出检查。

## 启动与环境

1. 读本任务、MASTER_RELEASE、`docs/revd/PLAN.md`、INTERFACE/VERIFICATION/IMPLEMENTATION_TICKETS 和 `work/revd/requirements.json`。包内 `AGENT_TASK.md` 的另建分支/worktree命令已经被当前授权覆盖，不能照抄执行。
2. 读原题：`work/report_cycle_sources/2026赛题指南.pdf`；原题共15物理页，重点4、8、11—14。来源/测试映射存 JSON 即可，不生成讲义、教程、长技术报告、HTML展示页、PPT或论文。
3. 已验证工具在 WSL `Ubuntu-24.04`：Icarus12.0、Verilator5.020、Yosys0.33。已有DV解释器：`/mnt/c/Users/11035/Desktop/ic/kwt—1/.venv-dv/bin/python`，Python3.12.3、NumPy2.4.6、cocotb2.0.1；Windows 系统Python3.12.4也有NumPy。可只读使用，不覆盖旧环境，不升级TensorFlow，不为本批下载模型或安装PDK。WSL默认 `/usr/bin/python3` 没有NumPy，别误判整个环境缺失。
4. Linux仓库路径 `/mnt/d/github/kwt`。先检查准备脚本 `--check`；确需恢复其固定四个链接时，可在WSL运行已有prepare再只读verify，记录创建与检查，不能在Windows Python运行Linux准备。不要使用会覆盖旧固定reports的旧总回归入口。
5. 优先 SV TB＋Python scoreboard＋Icarus，避免生产尺寸每拍 Python 回调开销；cocotb可用于短例。运行必须真的编译/仿真。工具缺失、失败、超时、SKIP、未知值、少输出均不能算通过。

## 不可变的数值与接口

- golden：`numeric/fixedpoint.py`，Git blob `116dfb84c51a6847cb10678c9e5a7230fb796598`；不更换、不修改。
- 每输出64个 signed16 乘积、按k递增精确累加；signed49临时加 signed48 bias；sat48；RNE右移0—47；sat32。`overflow`表示加bias后48位溢出，`saturated`仅表示最终32位截断；不能混淆或漏比。
- raw48观察点：D1 quant_epilogue独立单元的公开测试接口，或明确命名的被动退休trace。D2生产结果流本来没有raw字段；其验收为Y/两类flags/task/index/last，不虚构“公开流已比raw”。
- K=64，生产 M=99/N=256；N是16倍数，小尺寸覆盖M1/3/4/5，N16/32，生产覆盖尾3行。当前主要PM4，PN4，N_TILE16。量化scale/shift/bias不随结构改变。
- 有序事件流 BEGIN/LOAD_X/TILE_OPEN/LOAD_W/LOAD_B/TILE_COMMIT/START；输入accept与实际write/retire区分。V1_full在START前装齐X和全部W/b，COMMIT不能越过未完成写入，不能仅把收到条数当写完。
- 同步有效低复位，清valid/owner/标签/计数，不整体清大RAM；全X/W按16位SP同步bank实现。先读延迟1拍，再用2拍变体验证返回保留/标签，不拿软件解析数字充硬件周期。
- D1先单快照、无后处理重叠；最后乘积退休后再处理bias/量化/发布。每笔流水身份和row mask随数据走，停顿不能凭时间推进k/g。
- 结果顺序为 tile→row_group→有效row→tile内column，`y_index=m*N+n`，不是输出时序序号。含task_id、Y、overflow、saturated、last。M*N唯一结果全部out_fire、内部缓存空、无fault才core_done。未握手valid/payload稳定，last唯一且只在末条；fault不伪成功，已valid输出保持至握手或reset。
- 禁止 TB 直写DUT私有RAM、force内部状态、答案回灌或CPU/Python代算DUT工作。golden数学索引与DUT scheduler不能复用同一个候选地址函数掩盖共同错误。

## D0：冻结、重排与验收入口

- [ ] 核查当前分支、HEAD、dirty差异、192项旧源码冻结以及输入manifest；存本批 baseline/source manifest，连新未跟踪代码也纳入来源哈希。
- [ ] 实跑 `docs/revd/tools/compare_v0.py --source numeric/fixedpoint.py --out <new> --full`（从repo根调用，用合适Python），保留768个标量向量及一个全99×64×256合成矩阵的真实结果。不要用上轮回执代替本轮执行。
- [ ] 重排冻结工程数据：旧packed W索引 `n*64+k`，新tile公开流 `k*16+j`，数学元素是W[k,nt+j]。全部16384个W及256个bias逐值核对，覆盖列0/15/16/255。建立独立测试先证明错误转置/少元素/错dtype/错误shape会被拒绝。
- [ ] 旧36案例来源 `reports/prototype/vectors/manifest.json`，读取 `numeric.artifacts` 的验证/加载接口和旧numeric_handoff。只读完整验证数值源/配置/数组SHA/shape/finite及12层覆盖，然后消费。不调用会重生成覆盖旧数据的脚本。
- [ ] 新批次门禁应检查基线为当前HEAD祖先、golden与保护源字节不变、当前新源/配置/工具/输入身份；原包repo_preflight锁死旧HEAD只作起点检查，不能为了后续合法提交而放宽其原锁。
- [ ] 存必要的 `requirements.json`、`contracts.json`、`baseline.json`、`run_manifest`；不额外写教材/教程。来源/接口或原题有实质矛盾则记录准确缺口并解决已确定部分，不编造。

## D1：数值单元和最小micro（先红后绿）

建议文件：`rtl/revd/mac_lane.sv`、`micro_tile.sv`、`quant_epilogue.sv`；对应 `dv/revd/` 短例、独立golden及runner。可以据真实接口调整内部拆分，但不能引入CTX4或新数值格式。

- [ ] 先写可观察的功能/握手断言。记录真正RED；缺工具/缺模块编译失败只能叫环境或编译RED，不能代替一整套功能失败证明。
- [ ] 量化单元对raw48/Y/overflow/saturated逐值；所有shift0—47、正负端点、正负RNE半值、bias48极值、48位溢出与32位饱和的区别、全零/抵消/仅k63非零。
- [ ] 4×4 micro跟踪64个有效乘加和末项退休；无效尾lane不读未初始化行，不把padded MAC算有效MAC。
- [ ] 测输入停顿、已有out_valid后撤ready、末输出有限堵塞、连续任务、reset打断累加/后处理/输出。必须证明数据/flags/标签稳定、无漏末项或重复。
- [ ] RED→实现→GREEN后做规格审查，再做质量审查；保留实际命令、退出码、失败和修复证据。至少两轮自审，不以测试数量替代检查质量。

## D2：全缓存X4/W完整FFN1

建议文件：`rtl/revd/banked_x4.sv`、`banked_w_full.sv`、`ffn_scheduler.sv`、`core_stream_frontend.sv`，一个清楚的独立核心top；`dv/revd/`公开流TB、scoreboard、重排和gate。

- [ ] 有序装载与写退休，真实同步RAM读取，先单结果块/快照无重叠。公开流填X/W/b；不预填私有RAM。
- [ ] 小矩阵先通过，再跑一个完整99×64×256。生产每任务必须25344唯一有效结果、1622016有效MAC、一个正确last，Y/flags/task/index/次序全核对。
- [ ] 跑原36工程案例，明确是3个输入×12层的工程覆盖；每个案例均冷任务清有效/重装参数，层切换不可沿用残余W/b。总输出应912384；有失败就不填“36通过”。
- [ ] 新独立进程重编译/复跑至少一个完整生产案例，输出摘要与主跑一致；不能只把同一文件读两遍叫复跑。
- [ ] Icarus主功能通过后Verilator短例或编译/lint交叉检查；警告逐项说明真实影响，不压掉signed/width问题凑绿。不能把lint叫STA或正式综合。
- [ ] 至少做能实际检测的独立负测/变异，优先漏k63、signed变unsigned、输出漏/重索引、未握手提前done或reset残留；记录是否真实RTL编译运行还是仅软件scoreboard负测，不混称。
- [ ] 真实RTL计数分别记录load/compute/output/wait、各bank真实CE、issue/retire、有效/虚拟lane、core/frontend周期；读延迟1/2拍实际重跑。无实际数据则null/NOT_RUN。
- [ ] 脚本真实失败、超时、缺输出/未知hex、被篡改输入、来源hash变化、SKIP等要在门禁中被拒绝；保留至少一项已知坏输出/缺失证据使门禁失败的实测，防“文件叫PASS就通过”。

## 与题目的对应和不能宣称的事项

本批覆盖任务1点积/数值处理、任务2完整FFN1和12层参数切换的本地工程RTL实现。正式任务3 E203集成、指定宏/库、综合前后功能、150MHz、2.25mm²、功耗/能耗、官方600样本和正式12次性能任务仍NOT_RUN/外部待验。

结构实现必须对原整数参考零位差；不能用NRMSE≤3%容忍RTL错误。旧工程数据的浮点误差不是官方600评测；只能在当前样本身份下报告它。旧FP32十二层284353480/290627429周期与新整数FFN1不是同一工作负载，不能作新加速比分母。150MHz行为仿真时钟不能当时序通过。

后续P1必须解决单核CPU被MMIO写卡住而无法排空Y的源汇活性：nonblocking容量/状态查询、CPU交错喂入排空、accept与retire分离；W/Y满及有限公平假设下真实E203完成，system_done等最后写响应。这里只记录要求，不现在加MMIO/DMA或发明正式地址表。

## 运行、自审、停止与回传

HEARTBEAT_INTERVAL：20—30分钟或每阶段完成，4行内写当前阶段/本批完成/下一步/阻塞，并更新STATUS；终端/日志显示真实进度。

SELF_REVIEW_ROUNDS：至少2轮；规格与数值/协议先审，质量与来源/验收门再审；有条件使用独立子智能体只负责不同文件或只读review，不开第二条持久实现线。

BATCH_OUTPUTS：新RTL、公开流TB、必要接口/验收JSON、全36例与独立复跑证据、红绿与变异/负测记录、来源/配置/工具绑定及STATUS。不要讲义、论文、长教学报告。

DONE_CRITERIA：本批所有实际通过后STATUS写`READY_FOR_REVIEW`，布尔字段`d0,d1,d2,numeric,micro,full_matrix,independent_repeat,spec_review,quality_review,requirements_met`全部true；`full_matrix_cases`为整数≥36；列出当前source/input/output摘要与真实证据路径；`parent_accepted=false`、`official_contest_acceptance=false`。这只是待根控独立验收，不自授正式接受。

BLOCKER_POLICY：常规编译/功能失败在本批自主定位修复；工具和依赖可用时不因小错问用户。不够证据不升级阶段；核心数值/题意/允许范围变更停止依赖项并记录。预算/轮次耗尽或确有外部阻塞就保留最后通过点与准确NOT_RUN，不伪装完成。不要跳到D3+填充时间。

每次新run_id，不覆盖旧输出。离开前检查旧冻结源码、RevD快照和输入仍原哈希，git无任何提交/分支/远程变化；当前new diff完整留给用户。完成后仅简洁说明D0/D1/D2实际结果、失败/剩余和证据入口。


## 根控独立验收退回与串行修复（2026-10-17 第2轮）

上一轮CLI实际exit0，但根控独立审查后 **不接受** 当前结果。必须先处理以下已实际仿真复现的P1缺陷，不能读旧READY就退出，不重做架构优化，也不新建持久runner。

- 独立RTL审查 `work/revd/root_rtl_review.json`、测试审查 `work/revd/root_test_review.json` 均为ITERATE。
- 根控自己的全36输出解析已直接对照冻结Yq/flags，912384输出零差；旧12313 tracked文件逐一哈希未变。但这不足以覆盖完成协议。
- 功能RED证据：`reports/revd/root/20261017-052347-6bb5c3/final_fire_red/receipt.json`；其同目录 core_tb.sv 是只通过公开接口注入的最短复现：M5/N32，最后out_valid/out_last握手同拍，in_valid/op7/旧task且原入口q_valid=0。编译exit0，vvp exit1，明确打印 `REPRO_BAD_INPUT_ACCEPTED_ON_LAST last=1` 和 `DONE_WITH_PENDING_INPUT`。
- 根因：入口同拍接收命令形成新q_valid，但DRAIN终端直接core_done=1；下一拍非法事件才退休并fault。完成时存在已接受未退休输入，违反核心成功完成判据。

授权修复仅限该完成/入口竞争及必需测试、门禁和新鲜证据，不得更改数值、增加CTX4/SoC/PPA或写教学文档。先读现状和RED，再写正式定向回归，证明旧实现确实功能失败，然后做最小正确修复。可依据ready-valid契约在终端阶段合理阻止新接受，或等待所有已接受事件退休再决定完成；必须清楚区分“输入有效”与真正in_fire。不能只把失败断言删掉、只对测试特殊值打补丁、宽松化门禁或压掉fault。

必须补充的覆盖：
1. 最后out_fire同拍有非法旧task输入（同时记录in_ready与真实in_fire），只有入口/内部缓存空且无fault才允许成功done。
2. 非法事件已被接受而将在最后输出附近退休；不得先成功done再为同一已接受事件fault。含最后输出堵塞/解除。
3. 合法下一任务BEGIN与最后输出靠近，明确握手归属，后续普通连续改参任务仍正常完成，不残留q_valid或错标task。
4. 在生产TB加入“done不携带未退休旧task事件”的适当公开接口/被动检查，真实检测已复现竞态。
5. 新定向用例必须纳入聚合门禁required集合与有效证据/源哈希核验，不能只写独立未调用测试。增加至少一项负测确保删去新边界用例会被gate拒绝。

修复后源码改变，旧D2证据均作历史。为当前源码重新编译并执行small、完整production LAT1/LAT2、36工程案例、独立新进程生产复跑、protocol和lint、相关RTL变异、gate负测；D1未变时可按当前完整source绑定判断复用，但遇证据绑定变化则重跑。新的spec/quality独立复审须核对本条缺陷关闭，不能复用旧无阻塞结论覆盖新源码。保留旧RED/旧所有运行目录，全部新run_id。必要时更新source_manifest、evidence bundle和STATUS。

最终仍只能报READY_FOR_REVIEW且parent_accepted=false，列出修复的文件/源码哈希/真实新运行证据；等待根控再次独立接受。旧work/revd/root_*审查由根控维护，不能自行改成PASS；可新写独立修复说明JSON供根控复核。
