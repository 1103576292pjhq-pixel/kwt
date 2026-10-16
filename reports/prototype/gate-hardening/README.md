# 最后两项 P2 门禁修复

本次只修改 `scripts/prototype_gate.py`、`scripts/run_prototype.sh`、`dv/ffn1/test_gate.py`；没有修改计算 RTL、数值生产代码、数值向量、FFN1 runner/testbench、full/repeat 数据或最终审查文件。未启动任何 full/repeat 仿真。

## 修复内容

1. DOT64 校验固定七个必需文件，先要求声明键集合严格相等，再按固定清单逐一读文件计算 SHA-256；拒绝空、缺项、多项、文件缺失及内容变化。
2. 每组单元测试增加 `unit-start --group numeric|gate` 与 `unit-finish --group numeric|gate`。start 使旧 PASS 失效并移除旧 XML，保存唯一运行标识、必需测试数和源码/配置快照。finish 检查前后源码相等、XML 不早于本次 start 记录、真实数量正确且无 failure/error/skipped，保存 XML SHA-256 和前后源码摘要。
3. `finalize` 要求 start 已完成且与 PASS binding 的运行标识一致，绑定的前后源码集合/摘要等于当前源码，XML 摘要及真实数量仍一致。numeric 至少绑定全部 `numeric/*.py`、`tests/numeric/*.py`、生成脚本和数值配置；gate 绑定 gate、shell 入口和 gate 测试三项。XML 同时拒绝无名称或重复 `(classname,name)` 标识。
4. 标准 shell 入口在两组 pytest 前后调用 start/finish，门禁数量从 14 更新为 38。数值组仍为 67；没有通过增加重复 XML 项凑数量。

## 真实验证

全部 Linux 命令在工作区执行；负例仅修改 `/tmp` 目录。

| 命令 | 退出码与结果 | 证据 |
|---|---|---|
| `.venv-dv/bin/python -m pytest dv/ffn1/test_gate.py -q -p no:cacheprovider`（实现前） | 1；7 failed、17 errors、14 passed | `red.log` |
| `.venv-dv/bin/python -m pytest dv/ffn1/test_gate.py -q -p no:cacheprovider --junitxml=reports/prototype/gate-hardening/gate-results.xml` | 0；38 passed、0 skipped | `green.log`、`gate-results.xml` |
| `/usr/bin/bash -n scripts/run_prototype.sh` | 0 | 包含于最终 CLI 验证命令 |
| `.venv-dv/bin/python reports/prototype/gate-hardening/check_unit_cli.py` | 0；隔离复制中真实 unit-start → pytest → unit-finish → verify binding，numeric 67、gate 38 全通过 | `unit-cli.log`、`unit-cli-results.json` |

负例覆盖：DOT 空/缺/多/变更/缺文件；XML 重复标识；无绑定、无 XML、XML 改动、旧源码快照、缺失必需源码键、错误数量、错误运行标识、前后源码变化、旧时间 XML、重复 finish、新 start 后旧 PASS、必需数值源码缺失。正例完整验证七项清单和两类真实单元执行绑定。

主控下一步应在冻结这些源码后，重新生成当前 numeric/gate 单元证据并完成两轮审查绑定，再用 `--reuse-verified` 重新回读已有全部输出及运行快测。不必重做已通过的全尺寸 MAC 运算。
