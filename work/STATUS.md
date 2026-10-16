<!-- report-cycle-stage:start -->
## 已完成：方案A七项技术报告（2026-10-16）

- 状态：ACCEPTED_LOCAL_REPORT_BATCH。外层CLI于01:23:37北京时间实际exit0，根控退出后只读验收通过；记录reports/system/report-cycle/root-acceptance.json。
- 交付：docs/encoder/reports/共11篇，含正式七项技术报告、需求矩阵/总报告/复现指南；两轮独立审查和13项问题闭环通过，313链接/9448文件指纹当前。
- 硬件：192冻结源未变；旧正式七项本地基线已接受。正式平台/指定库与宏/150MHz/面积功耗/综合后功能/600样本/正式12性能任务仍外部待验。
- 本轮执行已结束，CMD仅保留日志；定时按完成流程暂停。最终根控报告reports/system/report-cycle/root-verification-report.md。

<!-- report-cycle-stage:end -->

# 工程状态

## 当前主线：正式七项本地初稿（用户1A已批准）

- 阶段：READY_FOR_REVIEW。本批统一入口真实退出0，run_id=84ef1f97e1394486b11b5510f79716d4；七项本地门全部通过，保留正式外部待验。
- RTL：15唯一输入各12层，180层/1140480word对独立C零差；独立新进程repeat另12层/76032word同SHA。首例1603800阶段trace已独立逐值核验。FP32冷启动136进程及完整组、短测/负测/变异、encoder与SoC generic均通过。
- 真实E203：两策略各完整12层，neural各76032word；CPU实际写回6336/76032word，全部位真且finite。CPU只搬运/控制，host按12次真实请求逐层供参；没有十二层参数全部常驻512KiB。
- 实测：端到端284353480/290627429cycle，内部交换节省6273949（2.1587601%）；CPU侧共享事务节省139392（17.4365107%），含供参host同窗逻辑合计节省9.9782813%。仅本次同输入双策略算例，不外推正式平台。
- 独立与文件验收：两轮自审及最终独立RTL/CPU审查无未关闭P1/P2；6审查/12来源/41稳定工件绑定。最后final-readback实际退出0，192冻结来源、34命令、51新单测、180/15 CSV、35报告链接及全部产物摘要一致。
- 证据：reports/encoder/verification/{report.md,gate.json,review.json,final-readback.json,performance.json}；unified/status.json为PASS。入门docs/encoder/README.md；设计work/formal_seven_design.md、执行计划formal_seven_execution_plan.md。
- 冻结：work/encoder_source_freeze.json仍192项，SHA4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17。本批硬件和统一命令均已结束；桌面可见CMD/后续主线由root管理，非Potter，未启动嵌套长期runner，无Git写操作。
- 正式待验：组委会平台/指定工艺与SRAM宏、150MHz/面积/功耗/能量、综合网表功能与门级时序、600样本与Top1口径、目标平台正式十二项整机性能评测。源码状态仍READY_FOR_REVIEW供root最终接受，不把这些外部条件宣称通过。

以下保留历史批次记录；当前正式七项本地完成情况以上述记录和新门禁为准。

## 当前批次：前三项基本功能雏形（2026-10-15）

- 授权：用户要求长时间完成数值模型、DOT64、完整FFN1三个功能，先有可运行基本雏形，后续用于学习。
- 当前阶段：ACCEPTED。前三项基本功能完成；主控独立回读及修补后统一入口均通过，验收记录 reports/prototype/parent-acceptance.json。本轮持久执行与计算已结束，CMD仅保留日志。
- 规格与任务：`approved_prototype_v01.md`、`prototype_execution_plan.md`、`prototype_task.md`、`prototype_interfaces.md`。
- 执行方式：Potter0.1.31内置自动提交要求与默认不提交规则冲突；改用当前桌面Codex CLI0.162的可见CMD持久执行。旧npmCLI/gpt5.5调用失败已保留；当前桌面CLI/gpt6.1-sol已实际完成UTF-8写入smoke，退出0。
- 范围：singleMAC、16位X/W、48位bias/acc、32位输出、固定尺度规则、逐行缓冲与ACK；36个默认完整尺寸案例终验，官方源与float证据只读。不做E203、PPA、研究生扩展或参数搜索。
- 新功能进度：numeric67项、gate38项、DOT64八项/52笔通过；36个全尺寸案例、912384输出零差，实测58392576次有效MAC；独立完整尺寸复跑25344输出哈希一致。
- 进度入口：`numeric_handoff.json`、`dot64_handoff.json`、`prototype_status.json`；启动后的真实状态为 `../.omx/prototype-run.json` 与 `../.omx/prototype-run.log`。
- 当前阻塞：无。数值路径保护/代码绑定、DOT哈希清单及单元XML执行绑定问题均已修复并独立复核；三轮审查及统一入口复验通过。仅当前36案例子集，不代表600样本/E203/150MHz/PPA。

## 本轮交接：前三项基础功能

- 主入口：`scripts/run_prototype.sh`（WSL /tmp调用绝对路径）；退出码0。preflight/numeric/gate-tests/dot64/protocol/full/repeat/lint/finalize各阶段均0，详见`reports/prototype/command-results.tsv`。
- 本轮主文件：`rtl/ffn1_top.sv`、`rtl/prototype_sync_ram.sv`、`dv/ffn1/{tb_ffn1.sv,run_ffn1.py,test_gate.py}`、`scripts/{run_prototype.sh,prototype_gate.py}`、`docs/prototype/`、README。
- 报告：`reports/prototype/summary.md`、`case-results.csv`（36行）、`layer-results.csv`（12行）、`ffn1/{full,repeat,protocol}/status.json`、`review-{spec,quality}.md`、`review.json`；最终门禁在`work/prototype_status.json`。
- 行为仿真36例周期合计：装载1654343、计算62954496、行等待39257、读回1821204；不含全部控制拍，不代表时序签核。
- 独立复跑数组SHA256：`b6ef91b483286a3826dc25e9a53d0a7946ec388d3f112dcd2fe7a01122fbe599`。源码/配置/向量/每例输出哈希已记录，源文件与旧float证据只读，未做Git写操作。
- 历史失败：numeric交接REVIEW_FIX时full入口退出1；Icarus路径首轮退出1且未进行矩阵运算；门禁10项真实RED、缺失/失败解释器2项RED。全部保留并已修正，见`integration_issues.md`及`reports/prototype/attempts/path-failure/`。
- 下一入口：主控复核`work/prototype_status.json`与汇总。需重验当前文件可用`bash scripts/run_prototype.sh --reuse-verified`，不重复36例；RTL/数值/向量/FFN1测试源码变化则默认完整命令重跑。当前批次不自动进入E203/PPA/扩展。

## 已完成批次：本地环境配置收尾（2026-10-15）

- 授权：用户要求“继续先完成环境的配置”，其他任务先预留。
- 状态：完成，本地前端开发与验证环境检查通过。
- 本轮变更：验证环境新增并固定 NumPy 2.4.6；安装入口列齐 build-essential/Git；新增实际环境自检；VS Code 默认使用 Linux 验证解释器并排除大体积缓存目录。
- 隔离边界：DV 为 Python 3.12.3 / cocotb 2.0.1 / pytest 8.4.2 / NumPy 2.4.6；模型仍为 Python 3.8.20 / TensorFlow 2.4.0 / Addons 0.12.1 / NumPy 1.19.5，43 个模型依赖按原锁验证。
- 本轮验收：真实 WSL 自检退出 0，10 项系统工具、124 个官方文件和 2 个真实 WAV 哈希通过；8 项自检回归通过；新 NumPy 下 10 项数组契约检查通过；Icarus/cocotb 490 ns 仿真及 FST/VCD 生成通过；完整模型入口退出 0，36 个独立 FFN1 案例和 153 个数组重复哈希再次通过。
- 修正记录：自检首次枚举到 setuptools 内置包的元数据，造成版本误报；已限定当前环境安装目录并核对实际导入版本，新增回归防止误覆盖，同时拒绝真实重复安装。首次失败保存在 `../reports/environment/diagnostic-vendored-metadata.json` 和同名 `.log`。
- 扩展预留：本科必做优先，研究生组及其他扩展待评估。本轮未实施算术方案、加速器 RTL 或新的硬件接口。
- 后续外部输入：正式 E203 平台到位后匹配 RISC-V 裸机工具链；指定 SRAM 和工艺库与负责综合/PPA 的同学对齐。
- 已知限制：cocotb 启动日志问题、旧 TensorFlow 兼容告警仍保留；未验收编辑器远程交互或 GTKWave GUI。当前通过的是命令行环境和小样本浮点基准，不代表硬件、正式 SoC 或 PPA 通过。
- 主要入口：`../scripts/check_environment.sh`、`../scripts/run_smoke.sh`、`../scripts/run_model_baseline.sh`。
- 当前证据：`../reports/environment/readiness.json`、`../reports/environment/smoke-result.json`、`../reports/environment/numpy-compatibility.log`、`../reports/model/STATUS.json`。
- 下一步：确认数值格式、目标和约束，再进入逐位软件模型与长度 64 点积模块设计；尚未自动实施。

## 第一批历史：环境闭环与官方模型基准

- 批次：环境闭环与官方模型基准
- 授权：用户于 2026-10-14 回复“开始”，执行已提出的第一批。
- 工作区：`C:\Users\11035\Desktop\ic\kwt—1`
- 范围：Linux 仿真 smoke、指定 KWT-1 源码与权重恢复、真实样本十二层 FFN1 数据导出及核验。
- 当前阶段：第一批完成，TensorFlow 2.4.0 兼容运行时验收通过。
- 已完成：官方指定提交 124 文件校验；Linux 仿真 smoke 独立复跑通过；43 依赖检查与锁重放通过；162 数值变量逐一精确恢复；36 FFN1 案例导出；153 数组重复哈希一致；16 项模型检查无跳过通过；主线程独立复算和规格/质量审查通过。
- 输入范围：两个真实 validation WAV（不同说话人的 eight，在十二类任务中属于 unknown）及一个明确标注的全零静音。
- 本批进行中：无。
- 下一批入口：先确认数值格式、目标与约束，再建立 bit-true 软件模型和长度 64 点积模块。当前未自动执行下一批。
- 未包含：加速器 RTL、量化参数搜索、E203 正式集成、综合/PPA、Git 提交或远程发布。
- 完成标准：仿真与自动检查成功；恢复官方 best_weights；真实验证样本的十二层 X/W/b/Y 形状与有限值通过；Y 与官方层输出一致；重复运行结果可核验；记录实际测试范围和版本。
- 兼容事项：官方 PyPI 与已检查镜像当前没有 `tensorflow==2.4.0rc1`，实际使用明确标注的 TensorFlow 2.4.0 兼容环境，不声称与 RC1 数值逐位等价；原始源码与权重保持不变。
- 模型环境：WSL 原生用户目录，经项目 `.venv-model` 链接访问；`config/model-environment-location.json` 记录位置，源码、数据、报告仍在当前工作区。
- 后续外部输入：正式 E203 平台、SRAM 宏与工艺库。
- 已知限制：Dense/GELU Trackable 引用告警保留；checkpoint 含本次推理未消费的额外对象，不能据此宣称对象图完全兼容。所有实际模型数值变量精确匹配，FFN1 W/b 经独立回读；不声称 RC1 严格数值复现、完整数据集准确率或硬件验收。
- 主要证据：`../reports/environment/DV_ENVIRONMENT.md`、`../reports/model/baseline/SUMMARY.md`、`../reports/model/baseline/verification.json`、`../reports/first-batch-independent.json`。

## 当前清单

- [x] 官方源码与权重来源及 SHA-256 固定
- [x] Linux 仿真和波形 smoke 通过
- [x] 官方 TensorFlow checkpoint 恢复（上述兼容运行时与警告边界）
- [x] 真实 validation 音频与样本来源固定
- [x] 十二层独立 FFN1 输入/权重/偏置/输出导出
- [x] 独立数值、形状、有限值及可重复性核验
- [x] README、运行入口、依赖与证据清单齐全












