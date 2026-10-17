# CPU 二进制身份门修复

软件修复与负测已通过；全新解压包内的真实 CPU 集成由总控接续，不将历史通过升级为当前源码通过。

## 红测与绿测

同一不可变真实 E203 full-PM4 记录 `reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json` 用于回归。测试显式调用 `check_cpu(current=False)`，仅跳过“历史源码等于当前源码”的判断，保留真实工具、命令、文件、输出和数值核验。篡改通过只读内存视图注入；二进制替换摘要来自一个实际写出的临时文件，原 CPU 文件没有改动。

- 红测：17 项，13 失败、1 错误，实际进程退出码 1。旧门误接受缺失 binding、替换 binary 以及被篡改的 binding 字段；旧 helper 将 Icarus 的 `vvp` 当成 payload。
- 最终绿测：22/22 通过，实际进程退出码 0。包括历史真实正测、11 项原始门负测、4 项明确的 current-source 语义视图测试，以及 6 项 helper / source inventory 测试。
- 审查补充红测：旧 creator 降级、helper 缺 source inventory、非零层对未核编译摘要，分别留下 18/19/21 项测试中唯一失败的实测记录。三项现均通过。
- 语法：9 个本批 Python 文件 AST 解析通过，退出码 0；`git diff --check` 退出码 0。
- 历史 result、aux、binary、firmware、CPU log 与 command sidecar 的前后 SHA 全部一致。

命令：

```sh
cd /mnt/d/github/kwt
/mnt/c/Users/11035/Desktop/ic/kwt—1/.venv-dv/bin/python -B tests/test_revd_cpu_binary_identity.py --out reports/revd_repair_20261017/cpu_identity/green_frozen.json
```

红测相同入口，输出为 `red.json`。实际命令、时间和退出码见 `red.execution.json`、`green_frozen.execution.json`；全部判定和最终源码指纹见 `summary.json`。

## 修改与绑定链

`soc_run` 编译后、执行前捕获 `compiled_simulator_sha256`。正常 CPU 与规定的功能负控执行完毕后，先写最终报告，再由 helper 生成一次性外部 binding。helper 核对真实 CPU 成功状态、退出码、命令记录、日志成功标记，以及编译时摘要和当前 payload 是否相同；拒绝覆写已存在 binding。Icarus 绑定 `cpu.vvp`，Verilator 绑定 `obj/Vsoc_cpu_tb`。

`soc_layers`、`soc_baseline`、`soc_edges` 显式延迟绑定，等各自补完最终报告后生成，避免主 runner 的早绑定因包装器改写而过期。binding 不放入报告 artifact inventory，避免 report 与 binding 相互引用的哈希循环。

offset0 gate 只读取 binding，比较报告路径与原始字节 SHA、执行文件路径与预期 SHA、固件、CPU command sidecar、CPU log、creator source 和历史未改标志。缺失即拒绝，不在检查时补签。所有 current=True 报告（包括非零层对）都先核对编译时摘要。已审计旧 helper 和旧缺 helper 的 inventory 只在显式 current=False 时允许，且返回值标记历史复用；current=True 必须绑定当前 helper 和完整依赖清单。非零 offset 的 pair gate 继续额外核验原 pair 绑定。

`reproduce` 要求生产 runner 自行生成 binding，再从严格 gate 的返回值记录 binding 路径与 SHA。它不会为缺失 binding 的结果补签。

## 交接与边界

总控需用最终源码生成新 stage、新 ZIP、新解压目录，运行 `portable --with-cpu`，核对新报告编译时摘要、aux 预期 payload 摘要和 gate 返回摘要相等。此步骤尚未计入本报告完成声明。Icarus 只完成 payload 选择的单元验证，本轮真实集成仍用 Verilator。没有重跑完整 12 层 CPU，没有改 RTL、量化、旧 budget、原 accepted 基线、历史证据、全局设置，也没有 Git 提交或推送。

真实 fresh 结果生成后，可运行 `tests/probe_revd_fresh_cpu_identity.py --package-root <新解压目录> --report <相对 CPU result.json> --out <绝对新报告路径>`，对实际新报告执行 1 个正测和旧 creator 降级、编译摘要篡改、缺 binding、替换 binary 的 4 个只读负测。该入口从指定解压目录导入 gate，不修改包内文件。

本机制验证文件与运行收据的一致性，不提供抵御同时改写所有可信源码及收据的密码学签名。
