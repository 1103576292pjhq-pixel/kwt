# FFN1 独立 DV 审查：运行前及首轮诊断快照

日期：2026-10-15。此报告只审查 DV、来源绑定及防假 PASS；RTL 控制与 RAM 另有独立审查。本报告不是完整 FFN1 通过结论，未启动或重复任何仿真。

被审源码快照：

|文件|SHA-256|
|---|---|
|`dv/ffn1/run_ffn1.py`|`677e790c7231f8fb8e2ddde330de208f7b26f961598aa79a1a89d1c1ea65aa55`|
|`dv/ffn1/tb_ffn1.sv`|`53bc89c911a39524ce02a7278203cbe2828c52d98273bba63adf5fab05379618`|

后续改动使上述快照结论失效，应以重审和新运行证据收敛。

## 已检查的防假通过机制

- 输入、权重和偏置通过公开 load 接口逐字装载；结果通过公开同步行读取接口消费。测试台的 `$readmemh` 仅写测试台数组，不写 DUT 内存。
- `accepted_pairs` 在时钟沿只读监测 `dut.mac.in_valid && dut.mac.in_ready`，每个完整任务取差并断言等于 `M*N*64`，再打印实际差值。因此日志的 1,622,016 来自真实握手观测；Python 中的固定期望值必须与该日志匹配才能通过。
- 完整模式强制 99×64×256，要求恰好覆盖 3 输入×12层；每例读出 25,344 个包含数值和溢出/饱和标志的结果。SV 逐项断言后，Python 再独立读实际输出文件，拒绝缺行、X/Z、非法字符和整数或标志差异。
- 日志必须每案例恰好一条 CASE_PASS，且全局完成案例数正确；进程非零退出、超时、哈希变化和缺失输出均失败。入口先将状态置为 RUNNING，异常再置 FAIL。
- `repeat` 模式在新进程实际执行一例完整矩阵，要求当前指纹等于完整回归指纹且结果哈希一致。
- 已加入启动前 `verify_vectors`，将原先仅检查 handoff/manifest 状态的陈旧向量风险修复到源码；它会重新检查数值源码、配置、固定来源及完整向量。仍需新运行证明该路径成功。

## 当前真实运行状态

小参数协议回归已有 `PROTOCOL_PASS M=3 N=4`，覆盖非法/未完整装载启动、乱序与非法 bank/数值装载、忙时命令、错误和重复 ACK、越界读、行保持、复位及溢出标志传播。此结果不能替代完整矩阵回归。

本快照观察到的完整模式为 **FAIL**：Icarus 将 `+jobs=` 中工作区 em dash 的 Unicode 绝对路径变成不可打印字符，`$fopen` 报 `jobs absent`，进程退出码 1。需要将 jobs 参数及 jobs 文件内各 hex 路径改成相对仿真 cwd 的 ASCII 路径，再执行完整 36 案例及独立完整尺寸重跑。未将未完成任务记为 PASS。

## 报告口径与剩余检查

- 当前 load/compute/wait/read 四项没有包括 launch 与每行 ACK 的控制周期，四项之和不能称为任务完整周期。应补观测 total/control 或明确标注缺口。
- 完整回归及重跑完成后须再次独立核对：36 个不同案例、912,384 个输出、58,392,576 次实际 MAC 握手、每例输出哈希与文件哈希、0 差异、全部来源指纹和完整尺寸重跑一致。
- 命令行中读回成功不等于已验证 E203、SRAM 工艺宏、综合、PPA 或 150 MHz 时序。本轮不做这些声明。

## 第二轮快照：完整仿真运行中与总验收入口审查

当前阶段：完整 36 案例回归真实运行中，本轮只读观察已超过 20 个 CASE_PASS，未重复启动完整仿真。Unicode 路径问题已修复为相对仿真 cwd 的 ASCII jobs/hex 路径；`verify_vectors` 已在完整运行前执行。两项历史问题不能再当作当前阻塞，但完整回归和重跑成功证据仍须等待。

本轮新增审查的源码 SHA-256：

|文件|SHA-256|
|---|---|
|`scripts/prototype_gate.py`|`ef559ef721b71e5943f682c770baba33e557bc2b4077ea49fa370c8f1450bd93`|
|`scripts/run_prototype.sh`|`7352c9ed6ebd2fd795a4c98fb85c4cc0b3617956ab55270e95265fde284df74d`|
|`dv/ffn1/test_gate.py`|`ee9b866c396f4d6c5c81d38dd317eed6a5a65938196f230bfb052e31e18de279`|
|`dv/ffn1/run_ffn1.py`|`9f86d4a464ac3f973a41d472a0c92e1ca1cd4d61ff2585d7d8eaf46a709485fb`|
|`dv/ffn1/tb_ffn1.sv`|`7105397e1bb7e0e1f446242b7fc6313d21c1bbb34f1ce6be67d4ea5b42ad9edd`|

### 已关闭：数值两项 P2

独立核对 `numeric/artifacts.py` 的输出路径保护在任何目录创建及状态写入前执行，拒绝保留输入的相等、祖先、后代及目录符号链接重叠。代码哈希验证现在要求恰好三个必需路径，不允许空、缺键或额外键。新增负例使用临时目录，并检查原文件快照不变，不触碰真实基线。

修补源绑定：`numeric/artifacts.py` 为 `fa367d9c149885e46ec469b534579437e9baac54bb2828ff76593abc8f269175`；生成入口为 `d4c0b3c34046b5c4ac79a8441720b006c7b95191268ac3ca1d6a5347968e807a`；`tests/numeric/test_artifacts.py` 为 `42540944a29a68093cebb703d192d229ce3b75e0f89fba42fc9a0c62ac1ed29b`；`test_generator_safety.py` 为 `7ea7c26e668d96290777e4f9fbdff1380ab522826da35e0d57361bb33896f85f`。

已读 `review-fix-green.log` 的 67 项通过以及 `review-fix-verify.log` 的 36 案例、288 数组、124 官方文件通过记录。另独立运行 `pytest tests/numeric dv/ffn1/test_gate.py -q -p no:cacheprovider`，81 项通过（数值67、gate14），无跳过；没有指定 XML 输出，也未覆盖集成或完整仿真报告。

### 未解决 P2：DOT64 必需哈希清单可以缺失

`prototype_gate.py` 的 finalize 仅遍历 `dot['hashes'].items()`；空字典或删除某个键会跳过对应当前代码/证据绑定。应在任何逐项计算前要求键集合恰好等于：

```text
rtl/dot64.sv
dv/dot64/test_dot64.py
dv/dot64/run_dot64.py
dv/dot64/inspect_wave.py
reports/prototype/dot64/results.xml
reports/prototype/dot64/build/dot64.fst
reports/prototype/dot64/dot64.vcd
```

最小修复：独立 helper 固定上述七项集合，检查 dict 与完整集合相等，再读取固定路径验证 SHA-256；增加空字典、缺一个必需键、额外键、文件缺失、内容改变的负例。不要用声明字典本身决定需要验证哪些文件。

### 未解决 P2：两类单元 XML 缺少执行时源码绑定

`integration-numeric.xml` 与 `integration-gate.xml` 当前仅检查用例数量以及 failure/error/skipped。若这些 XML 来自旧代码，而修改后的测试数量不变，直接 finalize 可接受旧结果；新 review 绑定当前源码不能证明旧 XML 跑过当前源码。标准 shell 入口会重新执行这两组测试，风险主要出现在单独 finalize 或复用已有报告时。

最小修复：在 unit-start 时记录本类生产/测试源码 hash；成功运行 pytest 后，unit-finish 要求启动前后 hash 相等，记录 XML hash、实际通过数量、失败/跳过为零及对应源码集合；finalize 必须要求这些文件存在，XML hash 与当前内容匹配，源码集合及 hash 与当前完全相等。数值组至少绑定 `numeric/*.py`、`tests/numeric/*.py`、数值配置；gate 组绑定 gate、入口脚本及 gate 测试。补旧源码快照、缺失绑定文件、缺 XML、XML 改动、错误数量和遗漏必需源码键的负例。可同时拒绝重复 testcase 标识，防止以重复项凑数量。

这两项修补属于总验收层，不必修改已冻结的计算 RTL/矩阵测试台，也不需要因此重跑全部 58,392,576 次 MAC；快测、新单元证据及最终来源/输出回读即可重新收敛。此报告只记录问题与建议，没有并发修改集成执行器所有的 gate 文件。

## 最终门禁修补复核：两项 P2 已关闭

最终只读复核日期：2026-10-15。以下新快照取代前节被指出问题的旧门禁快照，未修改任何 RTL、生产数值实现、向量或门禁文件，也未重新运行仿真。

|文件|最新被审 SHA-256|
|---|---|
|`scripts/prototype_gate.py`|`b042366367c889ea399678698dff1810f67cb8cc17247da12ab0906301c0c902`|
|`scripts/run_prototype.sh`|`48771746c1c282bd10b7b700e84c69357fd5053155fb68a8f3fa8ec1fcb9daa1`|
|`dv/ffn1/test_gate.py`|`287ac3b6f9a201cc59338965677af410c6fd5208436b5446178f44b3a8b1487c`|

1. `DOT_REQUIRED_PATHS` 精确列出前述七项必需文件。`validate_dot_hashes` 先要求字典键集合完全相等，再按固定集合读取文件校验；空/缺键/额外键/内容改变/文件缺失均有负例。该 P2 已关闭。
2. `unit-start` 先将旧 binding 置 RUNNING、删除旧 XML，再记录固定必需源码集合和额外数值源码的完整快照及 run_id。`unit-finish` 要求当前未消费 start、相同 run_id/group、前后源码及测试数量一致、XML 不早于本次 start、完整且不重复的测试标识、无失败/错误/跳过；将 start 置 FINISHED 后保存 XML hash 和执行前后源码。`finalize` 强制对 numeric/gate 两组调用 `verify_unit_binding`，重新比对当前完整源码、run_id、测试数量、XML路径及内容hash。入口已正确包围实际 pytest 执行。该 P2 已关闭。

独立解析实际 `gate-hardening/gate-results.xml`：38 个不同测试标识，0 failure/error/skipped，与 `green.log` 的 38 passed 一致。负例覆盖缺少或陈旧 binding/XML、执行时和执行后源码改变、源码缺键、错误计数、重复测试、run_id 改变、旧 XML 时间戳、重复 finish、重新 start 使旧 PASS 失效和缺失必需数值源码。

另外只读检查 `gate-hardening/unit-cli-results.json` 及对应隔离 CLI 检查程序：实际临时工程内完整执行 numeric=67、gate=38 的 start→pytest→finish→verify；两组 before/after hash 相等，且逐项重新计算后都匹配当前工作区源码。该检查明确没有启动 full/repeat。此隔离验证不冒充主工作区的新生产 unit binding；主控仍需用新入口形成当前主工作区绑定并完成最终 finalize。

### 完整矩阵与重跑当前状态

当前完整和重跑状态均为 PASS。只读核对 full 的 36 案例、912,384 输出、58,392,576 实际 MAC 记录，以及 repeat 的 1 个完整案例、25,344 输出、1,622,016 MAC；full/repeat 来源指纹相等且逐项符合当前文件 SHA-256，首案例输出 hash 相同。主控另已独立逐项回读全部结果和标志；本审查没有重复该仿真或将状态读取称为重新仿真。

审查结论：前述四项数值/总门禁 P2 均已修复并有针对性证据，当前审查范围内无剩余阻塞性代码问题。交付前尚须由主控生成新主工作区 unit binding、更新两轮 review 来源绑定并成功 finalize，不能将仍处 REVIEW_FIX 的顶层状态提前宣布为最终通过。仍仅覆盖固定 36 案例，不扩大到正式 600 样本、E203、工艺宏、150 MHz 或 PPA。
