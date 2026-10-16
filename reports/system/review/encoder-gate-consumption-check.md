# CPU 消费物闭环：窄复核

时间：2026-10-15 14:14 UTC。只读审查新增消费物校验、现有短测及冻结生成器接线；不重审数学/schema，不运行硬件，不修改真实 staging、源码或状态。既有报告保持冻结。

## 结论

本次新增 CPU 消费物验证范围内未发现未关闭的 P1/P2。`cpu_record()` 无条件调用新增校验，实际读取文件与已放行 canonical 数据、ELF 派生固件及记录命令建立了检查链；此前“仅绑定源数据/ELF，未核对模拟器实际读取的 staging 文件”的缺口在该快照中已封闭。已有 **51 tests 全部通过，3.82s，退出码0**。这不是正在运行的 CPU 长任务完成声明。

另：旧性能 P2 **仍待关闭**。当前 reporter 虽有其他更新，`:95`、`:100`、`:113` 仍把 CPU sysmem 访问标为未限定的“共享SRAM总事务/字节”，尚未单列 host 参数及 ready 写；详见已冻结的 `encoder-performance-readout.md`，本次不重复扩展该问题。

## 实际消费链与正常生成器接线

| 消费项 | 新 gate 检查 | 与正常生产路径的对应关系 |
|---|---|---|
| input.hex | `formal_seven_gate.py:182`–`:188` 将 record case 限于 reference/cases 下，实际文件逐 byte 等于该 case 的 canonical input。 | `run_system.py:54`–`:58` 复制该文件；冻结 TB `:31` 从当前运行目录装入公开共享 RAM 输入区。 |
| expected.hex | gate `:189`–`:191` 拼接该 case 十二层 y.hex，实际 staged 文本必须相同。 | runner `:59`–`:62` 使用相同层序、相同 UTF-8 文本拼接；TB `:32` 用此文件作比较数据。 |
| 十二层 weights | gate `:192` 必须解析到 canonical reference/weights，`:193` 检查全部 12 个实际层文件。 | runner `:63`–`:66` 创建相同目录链接、绑定每层来源；TB `:43`–`:45` 从该目录逐层读取并写公开共享 RAM。 |
| 实际固件镜像 | gate `:194`–`:200` 在独立临时目录真实执行 objcopy，从已绑定 ELF 重新派生 bin；实际 bin 和按 byte 每行两位 hex 的 firmware.hex 必须一致且非空。 | runner `:74`–`:78` 生成 ELF→bin→hex，TB `:21`–`:28` 按 BYTES 读取 firmware.hex 后装 ITCM。并未假设缺失的运行前快照存在。 |
| BYTES | gate `:201` 要求实际 command 中的 BYTES 等于重新派生的 ELF 镜像长度。 | runner `:77`、`:89` 从实际 bin 长度生成同一参数。 |
| 实际执行记录 | gate `:202`–`:204` 要求 commands.jsonl 中恰有一条 command 完全相同、cwd 为当前输出目录、时间处于 invocation 起止范围内的记录。 | `run_encoder.run():68`–`:72` 在 Popen 前追加实际命令/cwd/time；runner `:28`、`:89`–`:90`、`:108` 分别记录开始时间、调用命令和完成时间。正常编译/objcopy 的其他命令行不会匹配模拟器 command；历史同名调用在本次时间范围外。 |
| 校验接入 | gate `:209`–`:211` 在 `cpu_record()` 内经过身份检查后立即调用 `validate_cpu_consumed_files()`；返回值含 18 个运行消费物 SHA 摘要。 | `evaluate():274`–`:275` 对 pingpong/reload 均调用 cpu_record，成功才将增强后的 record 放进 gate details；任何新增校验失败均阻断该 CPU 项。 |

gate `:213`–`:228` 随后仍校验输入/编译源、实际 binary/ELF/build/log/output，以及真实 CPU 写回与独立 C 的逐 word 一致。消费物回读不是用来替代这些已有执行和数值证据。

## 执行的短测

```text
wsl.exe -d Ubuntu-24.04 --cd '/mnt/c/Users/11035/Desktop/ic/kwt—1' --exec .venv-dv/bin/python -m pytest -q dv/encoder/test_formal_gate.py -p no:cacheprovider
51 passed in 3.82s
exit_code=0
```

新增 `staged_cpu` 夹具真实调用 RV32 gcc 和 objcopy 构造微型 ELF，不使用伪造的固定 ELF 字节。正例验证完整消费物；九种负例分别改变 input、expected、bin、hex、weights 链接、BYTES、command、command 时间及“bin/hex 同步改变但 ELF 未变”，均被拒绝。另一个测试将消费物校验替换为必拒绝函数，确认 `cpu_record()` 的正式路径确实调用它。这些测试均在 pytest 临时目录内执行；没有调用写正式状态的 `evaluate()`。

## 源码快照

gate、tests、run_system、reporter 的 SHA 在短测前与静态复核结束时一致；共同 run() 辅助文件记录复核结束快照。只对该快照作结论，后续编辑不自动继承本报告。

| 文件 | SHA-256 |
|---|---|
| scripts/formal_seven_gate.py | `dc2483a43acd314f783d274d61946c9c904a595700f4cf6b2060ae87cd16c494` |
| dv/encoder/test_formal_gate.py | `6e31edc27ba05a52f8a77fd239ba3cad3420097a58337b9f358a147597ba444e` |
| dv/e203_encoder/run_system.py | `7330b0328c1b1e6e62deb7a3fc5a0968c704f468674166d824f6a4928405abd0` |
| dv/encoder/run_encoder.py | `ac79d63160a1b15702cd13d305ffd2b9ab7de8a34f1a3e792a5227071f909b95` |
| scripts/encoder_report.py | `c79bb0c7e2948e0733593cf5a83ca140329c8a079d9fdb2df2141276168c0dc9` |

边界：本次未把运行中的 CPU staging 当成已接受证据，也未重新执行真实 staging 回读；真实长任务仍须正常结束并经当前 gate 与总控验收。本报告不推断性能收益、正式 PPA 或600样本结果。
