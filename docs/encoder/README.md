# 完整编码器入门与复现

编码器把 99 个 token、每个 64 个 FP32 特征变成同形状输出。CPU 负责搬运和启动；全部点积、Softmax、残差、LayerNorm、GELU 在可综合 RTL 中执行。官方模型为 PostNorm、单头、12 层，FFN 宽度256。GELU 使用冻结的公开 tanh 近似，官方模型使用 erf；逐位一致的目标是独立 C 参考，与官方模型的误差另外报告。

先读 [接口](interface.md)，再看 `rtl/encoder_sync_ram.sv` 的一拍读取、`rtl/encoder_fp32.sv` 的请求响应、`rtl/encoder_nonlinear.sv` 的固定公式序列，最后跟随 `rtl/encoder_core.sv` 的 phase。大 RAM 从不整体复位；BEGIN、装载计数、done 和银行位决定哪些内容有效。

数据链为：输入 X → 全部 K/V 投影 → 逐行 Q → 99 个 score → 稳定 Softmax → context → Wo 与偏置 → 第一残差/LN → FFN1/GELU/FFN2 → 第二残差/LN → 输出 Y。K/V 完整保留，score/prob 只保留当前 query 行，因此不常驻 99×99 矩阵。每个点积从 +0 开始，按维度递增调用 FMA，偏置随后单独 ADD。

小尺寸使用 M3/D4/H8；attention scale 仍固定0.125。硬件支持 D4 和 D64，其余 D 在 elaboration 拒绝。生产默认 M99/D64/H256，每层权重49792word。共享 SRAM 只有512KiB，所以 host 在公开 CPU 邮箱请求后逐层提供权重；不存在十二层参数全部常驻。

在 Ubuntu-24.04 WSL 中，从工程根目录执行：

```bash
bash scripts/run_encoder.sh --mode small --sim icarus --trace --output reports/encoder/rtl/small-icarus
bash scripts/run_encoder.sh --mode small --trace --output reports/encoder/rtl/small-verilator
bash scripts/run_encoder.sh --mode layer --attention --trace --output reports/encoder/rtl/attention-full
bash scripts/run_encoder.sh --mode full --trace --output reports/encoder/rtl/full/original-0
bash scripts/run_e203_encoder.sh --policy 1 --output reports/encoder/system/pingpong
bash scripts/run_e203_encoder.sh --policy 2 --output reports/encoder/system/reload
bash scripts/run_encoder_synth.sh
bash scripts/run_formal_seven.sh --reuse-verified
```

最终命令会核对当前源码、输入、固件、binary、日志、完整输出与案例数。显式复用只接受仍与当前文件绑定的历史证据；`--help`、失败子进程、部分输出和旧 PASS 不构成新执行。失败日志留在对应目录的 attempts 内。当前是否通过以 `work/encoder_status.json` 和总报告为准，不能从上面列出的命令推断已经成功运行。

练习：追踪一个 PATTN 点积，写出 k=0、k=1 两笔 FMA 的 a/b/c 来源，再观察 PBO 如何加入偏置。答案：a 为 context_row[k]，b 为同步 weight[WO+k×D+col]，c 为前一次 acc；从 +0 起逐项累加，最后 PBO 用 ADD(acc,bo[col])，不把偏置并入第一笔 FMA。

练习：为什么 SWAP 不需要复制6336word？答案：Y 已写入另一银行；SWAP 只翻转银行选择、递增层号并清权重有效计数。RELOAD 则由真实 CPU 读回、写入共享 SRAM，再装入下一层。正式对比只按 `work/MASTER_RELEASE_encoder_reuse.md` 的二选一放行运行，计时边界与原始握手计数见总报告。

没有指定工艺和 SRAM 宏时，generic Yosys 只能证明结构可展开、连线完整及同步 RAM 推断，不能证明150MHz、面积、功耗或门级时序。公开12类工程样本也不能替代组委会600样本准确率。

真实E203仿真沿用共同启动环境的 `-Diverilog -DDISABLE_SV_ASSERTION=1`。上游条件SVA未启用；本项目的测试台显式fatal、总线/完整输出监视和错误变异仍实际执行。该口径不能视为CPU形式化认证，两种复用策略使用相同编译选项和时钟。

学习时先运行3×4×8小案例，逐项看 `input.hex`、`weights.hex`、`output.hex` 和 `trace.txt`。hex保存IEEE binary32位模式：`3f800000`表示1.0，`00000000`表示+0，不是十进制整数输入。正式尺寸是99行token、64个特征、256个FFN隐藏单元；一次完整层必须写出99×64=6336word。

FP异常flags按位为invalid=16、divide-by-zero=8、overflow=4、underflow=2、inexact=1。正常FP32计算常见flags=01，表示发生舍入；设备fault、ICB事务error和IEEE flags是不同状态。发现fault时先读ERROR/STATUS、看首个失败阶段，再BEGIN并完整重装；不能只清sticky error就把未完成输出当有效数据。

练习：W1第2行、第3列的packed地址是多少，编号从0开始？答案：W1起点为4D²+3D=16576，行主序地址为16576+2×256+3=17091；字节偏移为68364。先核对这类地址，再看同步RAM读取和FMA，可避免把矩阵方向错误误认为浮点舍入差异。

真实长回归进度可以只读查看：

```bash
.venv-dv/bin/python dv/encoder/check_live.py
```

该命令同时核对当前/proc进程与progress中的命令，写出 `work/encoder_live_checkpoint.json`。它用于判断实际是否仍在跑；最终接受仍须看 `work/encoder_status.json`、完整报告及统一命令退出结果。观察到某层完成不等于整项通过。
