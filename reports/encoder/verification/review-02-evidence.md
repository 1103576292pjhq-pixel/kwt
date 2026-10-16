# 独立质量与证据审查：修复记录

审查者：原生独立 reviewer `encoder_independent_review`；同时吸收总控的只读临时审查，见reports/system/review。未修改实现，未将静态审查当成完整仿真。

复审指出部分记录只核源文件，删掉checks日志、nonlinear向量或Yosys design仍可能接受旧PASS。已增加按类型的必需工件、摘要、完成marker及覆盖数校验，并用独立隔离文件验证删除工件必须失败。ICB_RUN的新公开完成/attention/reload日志也纳入必需集。

复审指出actual子命令退出0之后仍可能借旧结果。现每个可验收的actual任务都重新调用类型验证器，核对本轮run_id、开始/结束时间；历史路径只有显式reuse且全部来源/产物当前有效时可用。CPU实际写回文件和被动neural-output均逐word比独立C，不能只比被动trace。

门禁TDD证据：初始无校验版本实际10项拒绝失败；补工件后又保留6项删除工件RED；CPU历史身份缺口另保留6项RED，修复后29项拒绝/成功测试通过。覆盖失败子进程、help/no-op、部分层或输出、陈旧源、错误输出、不同binary、空日志、零周期、缺输入、删除日志/向量/design、旧run_id与错误时间。总控独立复跑原隔离夹具，policy1/2均合法接受、help和缺身份拒绝；详见 `reports/system/review/encoder-gate-final-closure.md`。

长回归之前，最终生产源、CPU全部编译输入、实际导入Python、生成HardFloat兼容副本和工具版本由work/encoder_source_freeze.json冻结。冻结后不编辑这些文件；必需修复先结束受影响旧任务、保留记录，再修复与重验。文档与不属于编译闭包的独立gate可继续审查。

当前结论：生产与CPU路径可进入冻结验证；最终十五输入/独立repeat/真实CPU两策略、正式收益数字、统一回归及最终独立证据审查尚须真实完成。review.json在这些证据未完成前保持未放行状态，不以手写true替代。

## 冻结后门禁复审

独立reviewer再次在内存隔离环境复现：删除checks、nonlinear、synthesis记录的类型字段后，旧版只剩PASS和当前源摘要也会被接受。现按约定记录路径先强制必需schema，FP32与算术mutants也适用，历史FFN1综合要求实际工件/内存/退出。五种删schema负测均拒绝；最终review还须显式pending=false、两份非空文档、当前freeze/gate源与十五案例/repeat/CPU两策略/综合等稳定产物绑定，避免把每次重写的gate.json绑定造成循环。

当前40项测试PASS，含最终review正例和缺项拒绝。独立reviewer已复验原三项最小假PASS并确认关闭，复验gate SHA为ac30661beaff6b7cd59d8837a03d0a1dfeeb1f66d0323f1c117f00627d376d0b。未改192项冻结闭包；当前长仿真仍运行，最终硬件证据审查未放行。

另实际编译一份仅关闭schema识别的gate变异，五种相同坏记录均被变异接受、被当前gate拒绝；运行入口 `dv/encoder/run_gate_schema_mutation.py`，证据 `reports/encoder/verification/gate/schema-mutation/status.json`。这是可执行行为差异，不把旧API缺失或语法失败计作该变异捕获。

## 实际消费文件绑定补审

独立reviewer在/tmp隔离完整CPU门禁夹具中，实际复现两策略均接受错误暂存input/expected/bin/hex、错误weights链接及BYTES与命令不符；控制项修改ELF会拒绝。这是旧门禁缺口，不是正在运行CPU的数学失败。补丁仅在独立gate：暂存input/expected及12层weights与canonical核对；已绑定ELF用实际objcopy临时重建image并逐byte比bin/hex；BYTES精确等于image长度且匹配时间区间内唯一实际command记录。cpu_record已实际接线，哨兵集成测试验证不能漏调用。

当前51项测试PASS，新增微型真实RISC-V ELF构建夹具验证正例和九种错误消费物。runner/RTL冻结闭包未改动；未补写不存在的运行前副本摘要。验收时回读摘要由gate派生保存，暂存副本缺少单独历史前后快照这一界限在报告明列。最终真实CPU任务仍待结束和独立回读。

该P1已由同一独立reviewer实际闭环复验：两策略合法夹具各接受并返回18个工件摘要，六种原漂移、bin/hex自洽篡改、时间越界和重复命令均拒绝，恢复后再接受。源快照dc2483a43acd314f783d274d61946c9c904a595700f4cf6b2060ae87cd16c494前后稳定；只改/tmp夹具，没有运行或改写真实CPU任务。

## 完整 RTL 与报告口径的最终回读

15 个唯一输入各 12 层、1,140,480 个完整输出 word 和独立新进程 repeat 的 76,032 个 word，已经由独立 reviewer 逐 word 回读对 C 零差；192 层日志、714 个去重文件摘要、执行命令及 wrapper 身份交叉一致。基准 PID749 与 repeat PID2590 分离且输出 SHA 相同。首例 1,603,800 项 trace 的逐值比对由总控完成，独立 reviewer 核其当前状态、输出和 trace 绑定后明确复用。独立文档为 [review-final-rtl-evidence.md](review-final-rtl-evidence.md)，观察到的总控记录保存在 [稳定快照](root-rtl-readback-snapshot.json)，不依赖总控后续周期更新文件。

总控报告审查指出 CPU sysmem 计数曾被误称为全部共享 SRAM 流量，这是 P2。报告器现分列 CPU 读写、host 参数写、ready 写和请求层号读，逻辑总量使用同边界各项相加；CPU 与逻辑总量分别使用各自 reload 分母。fixture 预置、内部 RAM、被动探针和物理 byte-mask 不在此口径内。独立 reviewer 与总控均通过隔离源码指标段的零分母、负收益、不同分母检查，P2 已关闭；总控冻结闭环为 [encoder-performance-closure.md](../../system/review/encoder-performance-closure.md)。源快照为 reporter19bcaa1e，不修改 192 项冻结依赖。

上述是已经完成的审查，不从运行中的 CPU 局部计数外推收益。最终 review 仍待两条真实 CPU 全 12 层输出、实际计时及流量回读，之后才填写稳定证据绑定并执行完整统一入口。

## 最终收尾复查

两条真实 E203 任务现均完整退出 0，独立 reviewer 直接逐 word 核对 152,064 个 neural 输出及 82,368 个 CPU 写回，全部对 C 零差且有限。两任务各 178 项源、172 项编译源、30 项输入、18 项实际暂存工件以及 192 项冻结源均匹配；ELF 实际派生镜像、命令、时间区间及两策略相同 binary/clock 均通过。原有历史 GCC 多次构建按本次执行区间筛选，未补造或删除历史。

独立重算四段周期与报告器实际纯函数、生成的 performance.json 完全匹配：pingpong 为 284353480，reload 为 290627429，差 6273949（2.1587601%）。CPU 侧共享事务 660034/799426，含供参 host 的同窗逻辑合计 1257562/1396954；分别以各自 reload 作分母，节省 17.4365107%/9.9782813%，不将二者混用。24 条 CPU 层边界、10 项指标、180/15 行 RTL CSV、34 个报告链接和 303 项摘要也已回读。

最终独立文档为 [review-final-cpu-evidence.md](review-final-cpu-evidence.md)，SHA256 为 `035028ee07650c358b97b6900547c29a30cdf0aac53017cebdcacfce1f0a4b7b`；其结论是无未关闭 P1/P2、允许进入统一门禁，整体接受仍以该入口实际退出 0 为准。暂存副本摘要仍只有执行后回读，正式平台/PPA/600样本/十二项整机性能继续外部待验。以上替代前述历史阶段的待执行清单；统一入口尚须实际执行并回读，不由本段文字宣告通过。
