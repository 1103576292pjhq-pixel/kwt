# 运行、证据和完成判据

完整入口与调用位置无关。在 Windows PowerShell 运行：

```powershell
wsl.exe -d Ubuntu-24.04 --cd /tmp --exec /usr/bin/bash '/mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_prototype.sh'
```

Linux 内为 `bash /mnt/c/Users/11035/Desktop/ic/kwt—1/scripts/run_prototype.sh`。已有 `.venv-dv`、Icarus 和 Verilator 即可；不重跑 TensorFlow、不下载数据集。数值与 DOT64 交接必须 PASS。

## 一次运行的证据链

1. shell 在 Python 启动前把旧成功状态置 RUNNING；任何阶段失败以非零退出并原生写 FAILED。入口锁防止重复总回归，FFN1 仿真锁防止重复 vvp。
2. preflight 完整回读冻结 float、124 个官方文件及整数向量的来源、配置、代码和数组绑定。数值67项、证据门禁38项及DOT64的8项仿真必须无失败、无跳过。前两组分别在pytest前后记录同一运行ID及源码/配置快照，删除旧XML并绑定新XML摘要和真实数量；缺少绑定、代码变化或XML过期都会失败。DOT64哈希清单必须恰好覆盖七个指定代码及证据文件。
3. 小矩阵测试从未装载 START 的真实 RED 开始，覆盖顺序装载、非法银行/地址/数据、部分装载、shift非法、busy命令、计算/等待中复位、错行/重复 ACK、重复读取、shift0/47与溢出标记。保存可直接打开的 protocol.vcd。
4. SystemVerilog 测试台从文件读取输入，逐个通过公开端口写入。36 个案例均为99×64乘64×256；测试台实际等待每一行并读回全部25344个结果，与冻结整数参考逐项严格比较。
5. 装载请求逐字带valid间隔，固定 xorshift seed=0x20261015 注入随机行消费者等待；每个案例日志记录开始、每25行进度与完成。DOT64的独立回归另有随机操作数停顿与输出反压。只读监视 DOT64 接受握手，必须每例1622016次有效MAC，总58392576次。没有 Python 每拍驱动开销，没有层次写RAM或跳过矩阵。
6. 再独立启动仿真重跑首个完整案例，25344项输出哈希必须与主回归一致。输出文件也由 Python 重新读取和逐项比较；仅有日志 PASS 不够。
7. Verilator lint、规格审查、代码/测试质量复核及当前源码哈希必须匹配，最后才生成 READY_FOR_REVIEW。

## 日志与定位

| 文件 | 查看内容 |
|---|---|
| `reports/prototype/run.log` | 当前阶段、基础测试、顶层退出码 |
| `reports/prototype/command-results.tsv` | 各阶段实际退出码 |
| `reports/prototype/ffn1/full/run.log` | CASE_START、ROW_DONE、CASE_PASS与周期 |
| `reports/prototype/ffn1/full/process.json` | 当前 vvp 的真实 PID、启动命令、退出状态 |
| `reports/prototype/ffn1/full/status.json` | 36案例输出与源码/配置/向量哈希 |
| `reports/prototype/ffn1/full/00/actual.hex` 等 | 实际公开读回，低32位结果、位32 overflow、位33 saturated |
| `reports/prototype/ffn1/repeat/status.json` | 独立完整尺寸复跑与匹配哈希 |
| `reports/prototype/vectors/manifest.json` | 每案例与每层误差、尺度、饱和数、来源 |
| `reports/prototype/review-spec.md`、`review-quality.md` | 两轮自审与修正证据 |
| `work/prototype_status.json` | 本批最终门禁结论 |

例如在 WSL 用 `tail -f reports/prototype/ffn1/full/run.log` 查看长仿真进度。full/process.json 的 EXITED 与完整日志一起判断是否仍在计算，不能只看历史 PID 或目录存在。

## 有效证据复用

默认命令每次执行36案例及复跑。正在仿真时不要重复启动。只需重查现有证据时可显式用 `bash scripts/run_prototype.sh --reuse-verified`；它仍重跑基础测试、协议和lint，并完整重读36案例/复跑的所有实际输出与哈希，不启动第二次58M次MAC回归。缺文件、哈希过期或输出计数不正确时直接失败，不自动降级为小矩阵。

RTL、FFN1测试台、数值代码、配置、向量manifest或FFN1 runner变化会使旧全尺寸证据失效。只改文档或验收门禁时，可以在重新审查和基础回归后复用保持一致的全尺寸证据。

## 结果适用范围

NRMSE采用误差RMSE除以参考RMS，分母下限为1e−8；按层先合并三个输入的误差/参考能量，不直接平均三个NRMSE。3%只评价当前两份真实unknown验证音频和一份合成silence的36层案例。整数参考对RTL要求零差；它与浮点量化误差是不同的检查。

周期分为装载、计算、ROW_READY后等待、读回。装载任务开始/命令和ACK的少量控制拍不包含在四类合计中，不把该合计称为端到端全部周期。所有数字来自行为仿真，尚未证明150MHz、SRAM宏映射、PPA或E203集成。
