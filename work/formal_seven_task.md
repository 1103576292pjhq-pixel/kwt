# 已批准正式七项初稿：持久工程执行任务

WORKSPACE: C:\Users\11035\Desktop\ic\kwt—1
HEARTBEAT_INTERVAL: 25 minutes
SELF_REVIEW_ROUNDS: 2 minimum; repeat after fixes until applicable criteria pass
STATUS_FILE: work/encoder_status.json
DONE_CRITERIA: all applicable local-draft checks in work/formal_seven_design.md; truthful external pending items separate; independent review required before final acceptance
BATCH_OUTPUTS: RTL+independent DV; real E203 firmware/system; reproducible generic synthesis; verification report and beginner entry; source/input/firmware/output hashes
BLOCKER_POLICY: continue all independent authorized work, write specific blocker/evidence, do not ask routine permission; do not claim official PPA/600 samples passed without data; no indefinite waiting or fabricated passing report

用户已明确选择1A（正式七项），并多次要求一次做完、反复验收。你是当前可见CMD持久执行主线，不是CodexPotter。Potter0.1.31内置自动Git提交与用户禁Git冲突，所以本工程实际使用桌面Codex CLI runner。不要启动嵌套长期runner或任何Git写操作，禁止git init/add/commit/push/PR/worktree/global auth/config改动。Windows全程原生PowerShell文件操作，绝不能跨shell递归删除。所有Python文本指定utf-8，WSL采用Ubuntu-24.04。

主控后续更新必须在每阶段/最终验收前读work/encoder_root_updates.md。用户刚明确回答A批准复用对比，放行凭据work/MASTER_RELEASE_encoder_reuse.md，按其中三要素运行真实两策略完整十二层对比，旧“待确认”文字已被此明确授权覆盖。12类真实工程子集也已下载，reference worker正在export-test12/reference-test12，使用这些可用资料完成每类各一完整12层任务，不只停在旧3输入。

先读work/formal_seven_design.md、formal_seven_execution_plan.md、encoder_fp32_contract.md、common_e203_design.md、reports/encoder/research/model-semantics.md和work/STATUS.md当前段。普通native agents正在并行产出基础依赖，不要与它们重复写文件。

## 你的所有权和依赖

你负责：rtl/encoder_core.sv、encoder_nonlinear.sv、encoder_sync_ram.sv、encoder_icb.sv；soc/e203_encoder/；sw/encoder_driver.h/.c及sw/e203_encoder/；dv/encoder/、dv/e203_encoder/；scripts/run_encoder.sh、run_e203_encoder.sh、run_encoder_synth.sh、run_formal_seven.sh及对应新gate；docs/encoder/；reports/encoder/rtl/、system/、synthesis/、verification/；work/encoder_engine_handoff.json、encoder_status.json和当前段STATUS。

只读并等待其有效handoff再集成，不能重写：
- FPU worker所有rtl/encoder_fp32.sv、dv/fp32/、tests/fp32/、scripts/run_fp32.sh、reports/encoder/fp32/、work/fp32_handoff.json。
- 数值worker所有model/encoder_export.py、numeric/encoder/、tests/encoder_reference/、scripts/export_encoder.sh、run_encoder_reference.sh、reports/encoder/export/、reference/、work/encoder_reference_handoff.json。
- E203 FFN1 worker所有soc/e203_ffn1/、sw/e203_ffn1/、dv/e203_ffn1/、run_e203_ffn1.sh、reports/system/e203-ffn1/及handoff，尚在真实完整CPU+repeat。
- 原数值、DOT、FFN1、bridge、生产ffn1_driver、原model冻结baseline和所有vendor只读。新core signed修正后的36+repeat已经PASS，不重复跑旧36长回归。
- 共同boot/ram/sw/e203已完成可只读复用。特殊 timescale.v 必须在vendor源之前编译；ASCII相对+args文件路径。
- root管理persistent runner、automation、formal spec，不要修改scripts/*prototype*或.omx运行身份。需要依赖变更写work/encoder_dependency_request.md，列具体原因，继续其他独立任务。

你不独自在代码库，保留其他人的编辑。仅在收到handoff并确认不再写的任务上进一步复用；不撤销他人工作。

## 数据及数值接口（不得自行改变数学）

数值精确定义在design。CAPI numeric/encoder/encoder_ref.h：kwt_encoder_layer(m,d,h,const float*x,const float*packed,float*y,stage_callback,ctx)、kwt_exp_neg(float)、kwt_gelu(float)。packed顺序固定49792word。数值导出约定：
- reports/encoder/export/manifest.json；weights/layer_00.hex...11.hex；cases/<sample>/input.hex；layer_00/{q,k,v,scores,prob,context,attn,r1,n1,ffn1,gelu,ffn2,r2,y}.hex；final.hex/logits.hex。
- reports/encoder/reference/manifest.json；同样cases/<sample>/layer_00/stage.hex/input.hex；fixtures/small_3_4_8/{input,weights,...}.hex。
- 小尺寸score仍固定乘0.125，模型维度正式固定64；硬件和参考一致，不能擅自小尺寸换1/sqrt(D)。

FP32初轮已实际两仿真器5419笔PASS，RTL可只读使用；最终handoff后核对fingerprints。HardFloat原始divSqrtRecFN_small.v有一条重复sqrtOpOut wire，Icarus拒绝；dv/fp32/hardfloat_sources.py会生成只删除该重复声明的可审计构建副本，复用helper，不改vendor。完整源清单参照FPU脚本。

## 执行顺序

1. 在你的目录先落下encoder core/ICB的精确外部装载、启动、读回、层交换握手契约和内存布局，再写对应行为RED测试。此为已批准设计的接口细化，无需反复向用户询问。保留FFN1基址11000000，encoder新基址11010000；CPU shell公开sysper/sysmem和512KiB sharedRAM可直接复用。
2. 实现nonlinear controller与完整attention/encoder可综合多周期状态机。允许选择紧凑微程序/循环控制，但不允许real/$exp/$sqrt/DPI/host神经算术替代。所有FP神经运算由共享encoder_fp32完成。大RAM同步读且不能整片reset，小行寄存器可直接索引。内部K/V和行级attention存储避免完整99x99矩阵常驻。
3. 在FPU+reference完成前，可用固定小尺寸已知数据调试握手/控制，绝不把stub结果当最终硬件验证。依赖到齐后small3x4x8完整比对，按stage定位所有差异。定向测试背压、busy拒绝、reset、missingload、非法访问、层号/顺序、全输出覆盖、错误能被验收拒绝。
4. 正式99x64/256 attention、整层，再3输入各完整12层。所有输出逐word匹配独立C reference，每层都要真实完成6336项，禁止只核CLS或跳过token。独立新进程repeat。用Verilator --binary实际执行加速，至少小组Icarus交叉。若仿真过慢，优化testbench/合法调度开销，不改数学或用软件代算，给实际进程/输出/日志。
5. 真实E203生产encoder_driver及固件：CPU只搬运、控制、读回；公开512KiB sharedRAM按层提供参数，不能假称全部2.4MB常驻；host在可观察请求点补下层参数，记录边界和每层加载时间。TB不得直接写内部RAM或代发CPU总线。需要至少一完整12层CPU任务，且全部完整输出被被动监视器验证。新SoC路由应同时保留原FFN1窗口。共用驱动的host fault tests要先写。
6. generic Yosys结构/同步RAM推断及可复现report，连接全encoder/SoC层级。没有指定工艺/SRAM库，任务3/7正式PPA/门级时序仿真/600样本保持EXTERNAL_PENDING；不得生成虚假面积、150MHz或功耗达标结论。性能统计包括输入/权重加载、CPU/ICB等待、写回、分层调度，有真实cycle计数和hash。
7. 重用实验有独立用户确认门：决策变量“外部读回再装载vs内部pingpong交换”，目标“SRAM流量/端到端cycle”，约束“同模型/同格式/512KiB/bit一致”。work/encoder_status.json.reuse_comparison目前AWAITING_USER_TRIAD_CONFIRMATION；没有confirmed release文件不运行正式对比，可以继续功能。用户明确延后则报告该子项延期，不能暗做正式搜索。
8. 两轮自审（设计/接口/数值与质量/证据），修复适用P1/P2，统一run_formal_seven.sh，回读source及输出hash、日志实际非空、case数量、cycles/flags等；门禁需拒绝陈旧源/部分案例/失败子进程/错误数据。不得仅手写true就验收。

## 状态和报告

每完成阶段更新work/STATUS.md当前段及encoder_status.json，保留历史。heartbeat 25分钟，真实来源为本工作区日志/进程，不混其他任务。对超长命令启动后记录命令、PID、run_id、时间、目标案例数和可读progress.json，不能无声等。

七项task1..task7 bool只代表上述本地初稿证据门，formal_acceptance单列外部待验，READY_FOR_REVIEW只在所有七项本地条件及>=3个full12 cases并且CPU全12任务与本地synth通过才写。若外部缺口使某必需本地条件无法完成，保持false并说明具体阻塞，继续其他项，不冒称全部完成。

最终写reports/encoder/verification/report.md：正式七项逐项状态、实际执行命令/工具、输入/输出数量与来源、位真与官方误差/分类、实际CPU/ICB/周期和参数流量、repeat/负测/变异/源码绑定、generic综合和正式待验、初学者阅读和一键复现。文件UTF8回读，引用均存在。没有Git操作。
