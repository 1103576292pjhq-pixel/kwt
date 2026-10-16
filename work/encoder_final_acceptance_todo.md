# 当前冻结版最后验收入口

## 最新恢复点：最终统一入口与文件回读均通过

- 实际统一session11670已退出0（最后chunk f2d2cb），run_id84ef1f97e1394486b11b5510f79716d4；34命令=5实际退出0+29typed历史，最终gate七项true/15case，state READY_FOR_REVIEW。
- 最终postcheck `work/encoder_postcheck.py --run-id 84ef1f97e1394486b11b5510f79716d4` 实际退出0。final-readback.json存192源/6审查/12source/41input/输出/35链接及源SHA；unified/status SHA fb24b88d...，gate4c17693b...，最终report2fb236c2...，review f14e6c2e...，freeze4c11f4fa...。
- current_stage已改LOCAL_DRAFT_COMPLETE_READY_FOR_ROOT_REVIEW，unified/progress已真实PASS/COMPLETE，STATUS当前段与handoff已更新。首次原子File.Replace空备份参数失败，四份已验证临时文件随后用Windows原生Move-Item白名单替换成功；未改任何验收源或产物。外层工具观察保存在work/encoder_unified_tool_exit.json（明确不是完整历史stdout日志）。
- 独立reviewer只读做最后新生成物交叉核对，唯一可写post-unified-independent.json；不要再改6审查MD、12绑定源或41稳定工件，也不要重新运行会改观察时间的postcheck主函数。等它返回后只汇报root依赖文件并正常退出；root另有已批准后续报告任务，严禁接管/停全局automation/新开runner。

下述“正在运行”表述是本次执行的前阶段记录，以上最终状态优先。

- 全部硬件已经结束：15唯一输入180层/1140480word及独立repeat76032word全PASS；真实E203两策略各完整12层均exit0，被动各76032word，CPU实际6336/76032word，对C全部零差。
- CPU端到端284353480/290627429cycle；独立计算、实际performance、180/15 CSV及报告UTF8/链接全部通过。差6273949cycle（2.1587601%），CPU事务差139392（17.4365107%），CPU+host逻辑合计差比例9.9782813%。仅同输入两策略各一次本地任务。
- 最终独立RTL文档SHA7acd85aa...、CPU文档SHA035028ee...均已冻结，无未关闭P1/P2；review.json已真实绑定6审查/12来源/41稳定工件，SHA f14e6c2e95ff9fdc1402e327ba625a0e9d00cbcd4ee01815ec188d3510ba5b1e。不要再改这些绑定源/文档/数据。
- 当前真实统一命令：`bash scripts/run_formal_seven.sh --reuse-verified`，工具session11670，Linux父PID314，run_id `84ef1f97e1394486b11b5510f79716d4`。状态与命令在reports/encoder/verification/unified/。已实际51tests PASS（6.52s）、schema变异运行；短记录和原3均已通过typed history，正在深核test12参考。必须等真实退出0及同runid最终gate PASS后才能说完成。
- source freeze仍192项/4c11f4fa...；gate dc2483a4...；reporter现在7c58df30...（仅新增CPU输入列/正式十二项性能外部待验文字）；unified源93f145eb...。性能算法未改，performance.json SHA c671f0e16beb748e0d2fea6426c679afd0b397ce10a57cd99ed7e246c3a83b04。
- 下一步：继续监控实际session11670（不新开第二条统一/硬件），结束后核unified status/PASS+实际exit0+fresh final gate七项/15case/READY、report-artifact全部SHA/UTF8/链接、review41工件摘要未变、CSV180/15、source freeze仍当前。可请原独立reviewer做只读最终产物复查，禁止改其冻结MD。
- 最后更新STATUS当前段/encoder_status.current_stage/heartbeat和handoff，保留历史；给root工作区依赖文件真实完成事实。正式平台/工艺/SRAM/150MHz/PPA/综合网表功能和门级时序/600样本/正式十二项整机性能均外部待验。没有Git操作，不改.omx或prototype脚本。

以下为前阶段恢复历史，仅供追溯；以上最新恢复点优先。

这是本工程当前状态备忘，不是完成报告。遵守formal_seven_task/design/plan及用户禁Git、禁嵌套runner规则。

## 已启动真实进程

- source freeze：`work/encoder_source_freeze.json`，192项，SHA256 `4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17`。
- WSL Ubuntu-24.04；RTL batch父PID401，工具session38064，run_id `5dfbbc274c4f4f1a8a2cc0fadc4c45fb`。15个不同输入各12层，加独立新进程repeat，共16项。进度reports/encoder/verification/case-batch/progress.json。
- CPU policy1 wrapper PID404、binary PID716、session82706，目录reports/encoder/system/pingpong。
- CPU policy2 wrapper PID408、binary PID665、session4179，目录reports/encoder/system/reload。
- PID仅是启动身份，后续必须核验真实进程；不能以旧RUNNING推断活跃。一次只读入口：`.venv-dv/bin/python dv/encoder/check_live.py`，输出work/encoder_live_checkpoint.json。
- 最新已完成：batch16/16 PASS，15唯一输入180层1140480word；独立repeat另12层76032word，与baseline同输出SHA且不同进程。两CPU仍活跃，最新进度以checkpoint/日志为准。

## 当前已经核实

- 新FP32 e9d83e2e源最终PASS，136个零暖机冷启动进程，完整21291×3及7变异。FP32、参考和vendor全部只读。
- 原3与公开test12数值参考冻结；原3独立软件重复、test12独立软件重复、独立Fraction小尺寸均已交接。
- 当前短checks、双模拟器NL/小尺寸、独立attention、3算术mutants、encoder及SoC generic全部PASS。
- 原3完整RTL共36层/228096word PASS；首例14阶段共1603800word PASS。公开test批次继续。
- 当前完成门task1..5=true，task6/7=false。不得为提前收尾修改bool。
- 独立审查修复CPU命令身份、FPU子证据指纹、删schema绕过、最终review接线。当前gate40 tests PASS，gate源ac30661b；原生reviewer和总控均独立复验。
- 后续实际消费物审查新增P1并仅gate修复，当前51 tests PASS：input/expected/weights实际副本核canonical，ELF重建bin/hex，BYTES及commands.jsonl交叉；cpu_record接线已测。旧40测试审查保留历史身份，最新51与该补丁还需最终独立复核。没有伪造暂存副本运行前摘要，只有最终回读与canonical来源原有前后绑定。
- schema可执行变异已真实编译并在五种坏记录上暴露旧行为，当前逻辑拒绝；已加入统一入口。
- root独立复核入口：reports/system/review/encoder-final-rtl.md、encoder-gate-40-check.md、encoder-gate-final-closure.md；只代表各自快照，不能冒充尚未结束的CPU/新案例验收。

## 等待命令期间

1. 禁止编辑freeze包含的任何生产、firmware、CPU TB、run_encoder/run_system、HardFloat或numeric导入文件。gate/docs/report独立文件可修真实问题。
2. 心跳25分钟，更新当前段STATUS、encoder_status.current_stage和work/encoder_heartbeat.json；保留历史。只依据本工作区真实PID/日志。
3. 失败时读实际simulation/compile日志并记录具体问题。必要冻结依赖修复前先结束/归档受影响旧运行，修复重验再freeze；不能把旧输出改绑新源。
4. 不重跑旧signed36长回归、FFN1 CPU或FPU完整组；有效冻结handoff由类型门禁重新核指纹即可。

## 长命令全部结束后的顺序

1. 核case-batch/status.json：16项全部PASS，15不同输入+独立repeat。每个full status须经accepted_rtl，12层、76032word、每层6336、当前source/input/compiled-source/binary/build/log/结果绑定。不能只读status字符串。
2. 核CPU两目录status：真实退出0、full12、neural_words=76032；policy1实际CPU6336输出，policy2实际CPU76032输出。两个neural-output逐word比C且摘要相同；host/CPU每次权重597504word，12个真实host请求/START。
3. 新运行freeze_sources.py --verify。禁止通过重建不同freeze给已完成案例改身份；相同freeze普通调用有REUSED保护。
4. 让独立reviewer读最终硬件证据及当前gate/report/unified。写reports/encoder/verification/review-final-evidence.md，只写实际核过的项和适用局限；两轮自审修复后必须复审。已有两个自审文件保持历史修复记录。
5. 只有真实最终独立审查通过后更新review.json。必须包含：status=PASS、rounds>=2、independent=true、open_p1/open_p2=0、final_evidence_review_pending=false；review_sha256至少两篇非空文档（包含最终证据审查）；source_sha256至少当前freeze和scripts/formal_seven_gate.py；input_sha256包含15个full status、repeat、两CPU、两generic、checks、FP32/reference handoff。建议同时纳入NL/小尺寸/attention/mutation与root只读证据。所有摘要真实回读。
6. 不把会被重写的gate.json或encoder_status.json放进review输入摘要，避免循环；绑定稳定完成工件。
7. 执行完整统一入口 `bash scripts/run_formal_seven.sh --reuse-verified`。只在其他同输出目录写者结束后运行。它会真实跑gate51和schema变异，其余只显式核验仍有效的历史。失败不能借旧PASS；最终gate必须本次run_id/时间且PASS。
8. encoder_report.py按最终gate生成报告、逐层/逐例CSV、两策略performance.json、报告产物摘要。cpu_timing要求12个host load与START，并核四段之和恰等于端到端周期；bus_waits仅命令端背压，响应等待包含在START后段；比例以reload为基准，有零分母保护。
9. 核unified/status.json实际PASS、命令退出、report UTF8/全部相对链接/CSV行数/实际周期和输出摘要；gate/work状态7项true、15个full案例才READY_FOR_REVIEW。交总控独立接受，不自动Git。

## 报告边界

- 正式平台、工艺/SRAM宏、150MHz、面积/功耗/能量、门级时序、官方600样本仍EXTERNAL_PENDING。
- 公开test12与官方预测一致12/12，silence官方和参考均预测unknown，其余11例与标签一致；不能称全部分类正确或正式准确率。
- C固定tanh GELU近似、逐操作FP32，与官方erf误差单列；RTL位真目标是独立C。
- CPU上游条件SVA未启用（共同环境-Diverilog/-DDISABLE_SV_ASSERTION=1），显式fatal/输出/协议检查实际执行；不声称CPU形式化认证。
- instructions是IFU有效握手计数，不是退休计数。仿真激励频率不代表工艺时序。
- 不生成假PPA、假600样本PASS、假CPU任务或host代算神经输出。
