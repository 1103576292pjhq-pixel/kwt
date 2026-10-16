# FP32 冷启动特殊 DIV 修复与复验计划

当前状态：**REVALIDATING**。旧版 PASS 仅代表旧哈希与当时测试覆盖，不包含真正冷启动首笔特殊 DIV；不得作为当前集成放行。先保存旧源码、报告、handoff 到 reports/encoder/fp32/history/ 下，再建立新的完整证据。

## 问题与只读复现

集成实际失败为 GELU(+0) 内部首个 DIV(+0,2) 返回未知位；独立复现保留在 reports/encoder/rtl/nonlinear-debug/。初步原因是官方 HardFloat 的特殊 DIV/SQRT 不写 normalCase 才使用的 sExp_Z、roundingMode_Z、sigX_Z；这些位可以保持 X。特殊 recoded 结果的分类位已知，但 recFNToFN 的完整指数比较让不相关 X 泄漏。旧 TB 在主向量前运行正常 DIV/SQRT 复位中断，初始化了这类未复位字段，掩盖了真实冷启动。

先只读 vendor 与 RTL，并新增**每个向量独立仿真进程**的 cold TB。任何正常运算、暖机或额外状态初始化均禁止。先保存当前 RTL 可编译且因数据 X 断言失败的 RED，再修代码。

## 允许改动与协调门

- 生产源仅 rtl/encoder_fp32.sv：仅当 root 确认所有依赖旧 FP32 的活跃长跑已经停止后修改。
- DV/工具仅 dv/fp32/、tests/fp32/、scripts/run_fp32.sh；报告仅 reports/encoder/fp32/；交接仅 work/fp32_handoff.json 和本计划。
- vendor 原文件、非线性控制器、encoder、SoC、其他 worker 文件均只读。
- 修复候选是在 recoded→IEEE 边界仅当分类位**确定为** zero / inf / canonicalNaN 时输出规范形式，并保留原旗标。未知分类必须保持未知并使验证失败，不能默认当特殊值。F32_TO_I32 的整数位模式禁止经过浮点规范化。
- 最终修复以独立复现与波形/分类字段证据为准，不因建议而跳过根因确认。

## 冷启动验收

每条定向向量单独启动 Icarus 进程和 Verilator 进程，系统复位后仅发该条请求，对照独立 C 主机参考输出与五异常旗标。至少覆盖：±0/正负有限数、有限数/±Inf、sqrt±0、0/0、Inf/Inf、NaN/invalid、有限非零正常 DIV/SQRT 及整数转换。检查背压期间数据/旗标保持与 busy/ready；保留分类未知的负测，不掩盖 X。

## 修复后复验与放行

1. 真正冷启动 RED → 修改 → 双模拟器全部冷启动 GREEN；新增冷启动修复可编译 mutant 并确证旧失败重现。
2. 21,291 事务完整双模拟器回归，数据和五旗标逐位核对；保持四次在途/响应复位覆盖。
3. 独立进程重复，要求生产源、DV、输入、输出哈希一致；五个既有行为 mutant 及新增冷启动 mutant 均编译成功后被测试杀死。
4. 独立参考固定真值测试与不可变 vendor 清单检查；Yosys proc/opt/check -assert/stat 重新运行，不声称工艺 PPA。
5. 接收脚本逐文件回读/hash，全部适用门通过后发布新 PASS handoff；记录旧证据归档、实际命令/退出/冷启动覆盖和局限。通知 root 与 engine 冻结后重建依赖回归，不把旧完整 encoder/CPU 报告换成新哈希。
