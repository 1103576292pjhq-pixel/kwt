# DV 环境 smoke

本例用一个 4 位计数器验证 Linux RTL 工具链，不涉及 MAC、量化或加速器设计。

从 WSL/Linux 的项目目录运行：

```bash
bash scripts/setup_dv.sh
bash scripts/run_smoke.sh
```

也可在任意工作目录用脚本绝对路径运行。脚本自行定位项目，Python 使用项目 `.venv-dv/bin/python`，Icarus/Verilator/GTKWave 使用 `/usr/bin` 中的 Linux 安装。

从 Windows PowerShell 运行：

```powershell
wsl.exe -d Ubuntu-24.04 -- bash /mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_smoke.sh
```

`test_counter.py` 的检查包括：两次时钟边沿之间的异步复位、35 次连续递增与两次模 16 回绕、5 次禁用保持、运行中复位与 3 次复位保持、5 次重新递增。断言在 `ReadOnly` 阶段读取时序结果，避免与非阻塞赋值竞争。

`run_smoke.py` 先执行 Verilator lint，再以 Icarus 运行 cocotb。独立 runner 不把测试断言失败自动变成 Python 错误，因此入口另行核对结果 XML；无测试或存在 failure/error 均返回非零。

运行证据在 `reports/environment/`：`smoke.log`、`smoke-results.xml`、`smoke-result.json`、`environment.json`。Icarus runner 原生生成 `smoke-build/counter.fst`，随后由 GTKWave 的 `fst2vcd` 转成 `smoke-counter.vcd`。生成波形不代表已经人工打开 GUI 查看；具体完成状态以报告为准。

可重复的路径与失败出口检查：

```bash
/usr/bin/python3 dv/smoke/check_portability.py
```

检查会在 `/tmp` 创建一个真实含空格与 Unicode 的临时项目副本，从 `/tmp` 调用入口，并设置外部 `WAVES=0`、`GUI=1` 验证脚本仍强制生成本轮波形。随后只移除副本中的 venv 符号链接，验证入口退出 2 且状态从旧 `passed` 更新为 `failed`；真实 `.venv-dv` 不受影响。

Python 依赖只装入 `.venv-dv`。`config/requirements-dv.txt` 固定依赖版本，`pip-freeze.txt` 记录本机实际组合；系统包与版本记录在 `environment.json` 和 `setup.log`。该 venv 是 Linux 环境，不能用 Windows Python 直接运行。
