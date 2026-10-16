# 原型集成问题记录

## 2026-10-15：交接撤回时禁止启动

- 数值交接从 PASS 改为 REVIEW_FIX（输出路径保护与源码哈希清单待修）。FFN1 `--mode full` 已按门禁退出 1，尚未启动 vvp；没有全尺寸运行证据。
- 基础件归数值 worker 修正，集成器不修改其文件。恢复 PASS 后核查真实文件再启动。
- FFN1 本地协议测试退出 0，Verilator lint 退出 0（仅豁免有意未连接的 debug 输出与 RAM 高地址未使用位）。

处理结果：数值worker完成路径保护与源码哈希清单修复，67项测试及完整向量复核后恢复PASS。顶层preflight已实际复核通过；FFN1独立full/repeat入口也执行完整来源验证。此项关闭。

## Icarus运行时Unicode路径（关闭）

- 首轮全尺寸vvp退出1，Icarus将工作区长横线破坏为`\377`，jobs文件打不开；尚未运行第1例矩阵。
- 不更改工作区或外部环境，jobs和hex路径改为vvp当前目录下的ASCII相对路径。原失败日志/status保留在`reports/prototype/attempts/path-failure/`。
- 修复后真实全尺寸案例已连续通过，当前唯一回归继续运行，成功总数以最终gate为准。

## 入口Python启动失败残留旧成功状态（关闭）

- 独立只读审查指出旧入口依赖同一Python清旧状态及处理失败，解释器缺失/失败时可能保留READY。
- 新增2项真实故障注入，先RED（2失败12通过），改shell原生原子写RUNNING/FAILED后14项全绿。证据在`ffn1/gate-startup-red.log`、`integration-gate.xml`。

## 协议未知值与独立入口来源绑定（关闭）

- 所有SV失败断言严格拒绝X/Z；完整数值比较同时由SV和Python核查。
- full/repeat在启动前完整verify_vectors，拒绝已经过期的源码/配置/数组绑定；不只比较运行前后是否变化。
- 独立只读复核确认修正，无未解决重大问题。
