# 报告周期检查器与终结门独立窄审查

结论：PASS。三个检查脚本的最终版本通过独立负例、隔离 CLI 自测和真实静态证据回读；P1/P2/P3 开放问题均为 0。本文只审查检查器与终结门，不替代 11 篇正文的两轮独立审查，也不授予根验收或正式平台验收。

审查者：`cycle_checker_review`。审查范围：`work/report_cycle_document_check.py`、`work/report_cycle_evidence_check.py`、`work/report_cycle_finalize.py`。准确最终 SHA 见同名 JSON 的 `files`。

## 发现与独立关闭

| 编号 | 级别 | 原行为与后果 | 最终修正与复验 |
| --- | --- | --- | --- |
| CK2-01 | P2 | READY 复核只读取固定 11 个路径；增加第 12 个未审查文档后仍打印 `READY_VERIFIED documents=11`。 | `verify_ready()` 先核对报告目录的精确文件集合。独立 fixture 再加入 `unreviewed.md`，现在拒绝。CLOSED。 |
| CK3-01 | P3 | 机械检查只比较条目名称；以 `README.md` 目录替换文件时返回 exit 0、`PASS documents=10 errors=0`。完整终结器原已另有 11 篇数量门，但机械检查本身结论错误。 | `document_set_errors()` 另用 `is_file()` 集合判断缺失文件。相同 fixture 现在 exit 非 0，报告缺失 `README.md` 文件。CLOSED。 |
| CK3-02 | P3 | `--verify-ready` 的共用入口在检查前执行 `OUT.mkdir()`；缺少证据目录时，失败复核仍创建目录。 | 目录创建移入写入分支。空工作区 fixture 执行真实 CLI `--verify-ready`，exit 非 0 且未创建输出目录；有效 READY fixture exit 0，前后文件清单及 SHA 完全相同。CLOSED。 |

首次两项失败证据保留在 `checker-review/initial-defects.json`。最终复验在 `checker-review/independent-checker-tests.json`，共 41 项，全部通过。内部负例保持为历史证据，不表示当前仍有开放问题。

## 验收链路

- 第一轮原始 11 篇快照覆盖完整；增量审查绑定第一轮 JSON 与审查正文 SHA，只替换 00、03 两篇旧 SHA，其他 9 篇保留。当前 11 篇 SHA 与叠加后的第一轮及第二轮全量映射完全一致。独立负例拒绝旧 SHA、错误 predecessor、无放行的第三篇改动、不完整 unchanged 集合、审查正文漂移和同身份两轮审查。
- P1/P2/P3 开放数必须明确存在且为 0；未完成审查、OPEN 的正文问题、OPEN 的 delta、OPEN 的检查器问题均被拒绝。闭环输出保留第一轮和第二轮的全部 10 项关闭记录、6 项 delta 检查，并消费本次检查器关闭记录。
- 硬件基线只消费稳定的 `reports/system/root-formal-acceptance.json` 及 `formal-baseline/runner-state.json`，未用动态 `.omx` 否定旧接受。独立真实 `readback()` PASS，绑定 788 个证据文件，回读输出逐字比较、有限值、12 层、CPU 输出及时间分段。192 个冻结源文件逐项核对通过，审查前后字节 SHA 未改变。
- 第二轮 `quality-readback/evidence-inputs.json` 的 9365 项实际输入和审查者的 25 项工件均重新核对 SHA。终结器要求 inventory 本身被第二轮 JSON 绑定，逐项核对其输入，并将完整 inventory 合并入最终 manifest。
- 终结器在运行前要求本窄审查 PASS、三类开放数为 0、恰好三个检查脚本的当前 SHA 和审查正文 SHA 相符。manifest 绑定当前 11 篇、两轮审查及 delta、结果、自测、命令日志、稳定基线、实际深读证据、检查器脚本和本审查工件。
- READY 标志由实际检查结果和准确文件映射派生；7 份报告数来自逐篇验证。输出强制 `root_acceptance=false`、`formal_acceptance=EXTERNAL_PENDING`，外层真实 CLI 退出仍留给根流程观察。
- 静态 AST 核对终结器共 4 次 `run_check()`，最后一次确为无额外参数的文档检查。该调用要求真实 subprocess exit 0，随后核对 11 篇结果与审查 SHA；此后没有正文写入。审查期间未运行正式 `finalize()`，因此本审查不宣称外层终结已实际成功，最终真实命令结果由主线程产生。
- 有效 fixture 的真实 CLI `--verify-ready` exit 0 且无写入；缺文件、错误 SHA、新增未审查文件均拒绝。正式 READY 状态形成后仍应由根流程执行该只读复核。

## 测试与写入边界

使用 `D:/Program Files/Python312/python.exe -B` 运行自有测试脚本。三个 `--self-test` 在自有目录内的逐字脚本副本执行，分别拒绝 14、10、13 个负例；未对真实终结器执行无参数命令。实际静态回读仅调用证据函数，输出保存到 `checker-review/`。

本次只写本审查的 Markdown/JSON 和 `checker-review/` 内测试证据。未修改正文、生产源码、192 个冻结项、真实状态、仿真结果、Git 或持久 runner。测试证据路径、最终文件 SHA 和完成时刻见同名 JSON。
