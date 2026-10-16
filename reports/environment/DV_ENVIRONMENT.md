# 第一批 DV 环境闭环

## 2026-10-15 环境配置收尾

在原环境基础上，验证虚拟环境补装并锁定 NumPy 2.4.6，模型环境仍保留 NumPy 1.19.5。`../../scripts/check_environment.sh` 每次重新检查两套隔离解释器、实际模块版本、精确依赖、10 项工具、124 个官方文件和 2 个真实 WAV；本轮从 `/tmp` 运行退出 0，结果为 `readiness.json` 的 PASS。

8 项自检回归和新 NumPy 下 10 项数组契约检查通过。仿真重新运行至 490 ns，1 项通过、0 失败，实际 FST/VCD 再生成。完整模型入口重新通过，36 个案例、153 个数组重复哈希一致。上述证据证明本地命令行开发与验证环境可用，不代表加速器、SoC 或 PPA 已通过。

自检首次把 setuptools 的 `_vendor` 元数据当作环境安装包，产生版本误报。修复限定虚拟环境顶层安装目录，并将实际导入版本与安装版本核对；真实重复安装仍拒绝。首次失败保存在 `diagnostic-vendored-metadata.log` 和 `.json`，没有通过修改依赖锁来绕过检查。

研究生组及其他扩展已预留，当前优先本科必做。正式 E203 平台到位后再匹配 RISC-V 工具链；SRAM/工艺库由综合/PPA 分工对齐。GTKWave GUI 和 VS Code 远程交互未验收；原 cocotb GPI 启动日志及 TensorFlow 兼容限制仍保留。

NumPy 版本依据：[官方 2.4.6 发行页](https://pypi.org/project/numpy/2.4.6/)。精确 Python 版本组合可复装，APT 包记录实际版本，未冻结整机镜像。

## 第一批验收记录

本批完成工具安装、4 位计数器自动仿真和实际波形生成。仅证明环境可重复运行，不证明加速器、数值方案、综合或 PPA 已通过。

| 项目 | 实测结果 | 证据 |
|---|---|---|
| WSL/Linux | WSL2，Ubuntu 24.04.4 LTS，内核 6.6.87.2 | `environment.json` |
| Python | CPython 3.12.3，项目 `.venv-dv`，隔离环境 | `environment.json` |
| Icarus | 12.0；APT 包 `12.0-2build2` | `setup.log`、`environment.json` |
| GTKWave | 3.3.116；`fst2vcd` 已执行成功 | `environment.json`、`smoke-counter.vcd` |
| Verilator | 5.020；计数器 lint 已通过 | `smoke.log` |
| Python 依赖 | cocotb 2.0.1、pytest 8.4.2，包含传递依赖的固定组合 | `../../config/requirements-dv.txt`、`pip-freeze.txt` |
| 安装命令 | 退出 0；`pip check` 无依赖冲突 | `setup.log` |
| 预期 RED | 10 ns 时计数应为 1、实际为 0；1 个断言失败，退出 1 | `red-counter.sv`、`smoke-red.log`、`smoke-red-results.xml` |
| 正式 GREEN | 490 ns，1 项测试通过，0 失败，退出 0 | `smoke.log`、`smoke-results.xml`、`smoke-result.json` |
| 实际波形 | FST 与 VCD；VCD 1715 字节，包含 clk/en/rst_n/count 和时间变化 | `smoke-build/counter.fst`、`smoke-counter.vcd` |
| 路径复现 | 真实含空格与 Unicode 的临时项目，从 `/tmp` 调用，退出 0 | `path-portability.json`、`path-portability.log` |
| 失败出口 | 副本 venv 缺失时退出 2，旧 passed 变为 failed | `missing-venv.log`、`path-portability.json` |

正式入口：

```bash
bash scripts/setup_dv.sh
bash scripts/run_smoke.sh
```

PowerShell 可直接调用 WSL：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp -- /usr/bin/bash /mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_smoke.sh
```

自动检查覆盖异步复位、35 次连续递增、两次 4 位回绕、5 次使能暂停保持、3 次复位保持和 5 次复位后递增。测试设 2 us 超时；读取发生在 `ReadOnly` 阶段。

入口使用明确的 Linux 工具目录与隔离 Python，XML 出现失败/error 或无测试均非零退出。每轮先删除旧 XML/FST/VCD，强制波形开、GUI 关，避免外部环境变量关闭波形后沿用旧文件。Shell 状态门使用系统 Python 标准库，venv 缺失或导入失败也会覆盖旧成功状态。

安装没有运行 `apt upgrade`，没有卸载软件或在系统 Python 中 pip 混装。安装 `python3.12-venv` 时，APT 为满足精确依赖将 5 个既有 Python 3.12 系统包从 `3.12.3-1ubuntu0.12` 更新为 `3.12.3-1ubuntu0.17`，其余 203 个包未升级；完整操作在 `setup.log`。

两项路径诊断：

- Icarus 拒绝 runner 生成的 Unicode 绝对 `$dumpfile` 文件名。入口已通过 `+dumpfile_path=counter.fst` 和明确运行目录解决；实际空格/Unicode 副本复现通过。最初诊断保存在 `smoke-red-unicode-diagnostic.log`、`unicode-diagnostic.fst`。
- cocotb 初始化前仍打印 `Log message construction failed: (error code) -1`，随后 Python 初始化、仿真、断言和波形均成功。这是尚未消除的启动日志问题，不能把本环境称为完全无告警。2.0.1 官方源码在 Python 初始化前用 `%ls` 输出 Unicode 解释器路径，与当前症状相符；C locale 导致格式化失败仍属有依据的根因推断，未做完整对照证明。

未运行 GTKWave GUI 人工查看、Verilator cocotb 仿真、加速器 RTL、综合、PPA。主仿真为 Icarus；Verilator 5.020 仅用于本例 lint，不与 cocotb 仿真绑定。

官方核对：[cocotb 2.0.1 平台支持](https://docs.cocotb.org/en/v2.0.1/platform_support.html)、[模拟器支持](https://docs.cocotb.org/en/v2.0.1/simulator_support.html)、[Icarus runner 源码](https://docs.cocotb.org/en/v2.0.1/_modules/cocotb_tools/runner.html#Icarus)、[fst2vcd](https://gtkwave.github.io/gtkwave/man/fst2vcd.1.html)、[GPI 初始化日志源码](https://github.com/cocotb/cocotb/blob/v2.0.1/src/cocotb/share/lib/embed/gpi_embed.cpp#L85)。
