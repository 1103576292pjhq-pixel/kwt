# 编码器最终 RTL 只读审查

本轮没有发现可确认的 P1 / P2 功能缺陷。结论仅对应下列源码快照及本轮短定向检查，不代替正式尺寸矩阵、真实 E203 十二层执行或综合后验证的验收。

## 审查快照

2026-10-15 在独立目录复制源码后审查并重新编译；执行前后十个源码 / TB 文件的 SHA-256 均一致，未发生边跑边改。本轮没有修改生产源码、原有验收报告或长期任务状态。

| 文件 | SHA-256 |
|---|---|
| rtl/encoder_core.sv | `95b611aabff1f939e7f052d25d5a6b83d8984db57a683751d0cdd9448badead2` |
| rtl/encoder_nonlinear.sv | `5862a8383fc93ab4e289d84eee5ccac63957bd7b7e300d6c5ac6beb0d3aa7501` |
| rtl/encoder_icb.sv | `9dcddf676eb5ae5a7460bb3fc7cea9098b51732c91b2340e5dfd6d09a72f47ed` |
| soc/e203_encoder/encoder_shared_ram.sv | `465dc196c3f495068f25ef5072dcc728839b0b9c9b746fdb494e1507f98fa54c` |

关联 FP32 为已修复冷启动特殊结果的 `e9d83e2e1d5263a77e3fa830b2e4a395a8d0b1d3b7f59a7771120e77d77b47bb`；本轮只将其作为实际编译依赖，没有重复基础 FP32 全回归。

## 关键边界复核

- **完整装载后启动**：core 第 31–32、134–143 行以连续地址计数装载；START 同时检查有效任务、无 done/fault、完整 X / W、正确层号及上限。busy 时命令仅返回错误，不进入修改分支；同步输出读期间 req_ready 为零。没有发现缺词装载后使用旧 RAM 数据启动的路径。
- **复位与公开输出**：core 第 119–129 行清除忙态、装载有效性和在途读 / 响应；不会通过重置大 RAM 冒充有效数据。最终输出逐词写入另一银行，最后词写入的同一时钟才置 done；READ_Y 只在 done 后合法。错误结果可能在终止时写进尚未公布的目标银行，但不会置 done，READ_Y 因而拒绝；恢复必须重新 BEGIN 和完整装载，未发现旧 / 半成品输出被公布的路径。
- **FP 响应与故障**：core 第 39–64、147–154 行在对应响应握手阶段收集结果，累计真实 IEEE flags；rsp_error 或浮点结果非有限会停止 busy 并置 fault。非线性第 59–83 行累计内部运算 flags / rsp_error 后通过独立响应返回；核心固定操作码不会把整数转换结果误当成核心最终浮点结果。定向真实 NaN、溢出与复位中断检查通过。未以 X 置零、预热或 TB 答案注入绕过冷启动问题。
- **SWAP / RELOAD**：core 第 141–143 行的 SWAP 翻转银行并保留有效 X 计数，RELOAD 保持银行并清 X 计数；二者都递增层号、清 W 与 done。attention-only 和第 11 层之后均禁止继续。RELOAD 后未补齐 X 时 START 被拒绝。软件两个策略只改变读回 / 重装与交换，不改变 RTL 数学；驱动和固件没有矩阵、注意力、归一化或激活计算。
- **WAIT_DONE**：ICB 第 40–47、67–68 行仅阻塞该公开事务；!busy 时返回状态，fault 在状态 bit3 可见；40000000 的旧计数值触发超时，最长 40000001 次等待状态采样。超时返回本事务 error 并保留 busy，不伪造完成。保持响应期间不接收新事务。独立控制注入验证了阈值前一拍、超时响应背压、终止 fault 解阻塞及等待期间复位撤销。
- **共享 SRAM**：独立时钟存储进程按有效接受事务和 byte mask 写入；读数据由同步 RAM 产生，背压时没有再次接受或改写。复位清公开响应而保留 RAM。低地址位与掩码行为符合已有共享 RAM 契约，包括非对齐字节访问。未发现共享 / 内部 SRAM 中由软件代填神经输出的实现路径。

## 本轮新执行证据

执行命令（WSL Ubuntu-24.04，Icarus 实际重新编译并运行）：

```text
python3 reports/system/review/encoder-final-rtl/run_review.py
```

命令退出码 0，总墙钟约 2.41 秒。结果及前后源码哈希见 [status.json](encoder-final-rtl/status.json)，每个编译 / 执行日志和实际源码副本均在该独立目录。

| 检查 | 本轮结果 |
|---|---|
| 公开 ICB 地址、掩码、顺序、计数、响应保持与复位 | `ENCODER_ICB_PASS checks=28` |
| 实际计算中复位、NaN 终止、恢复重装、在途输出读复位、响应背压复位、溢出 flags | `ENCODER_FAULT_RESET_PASS checks=717` |
| 真实小尺寸完整层 / RELOAD / attention 完成与公开输出 | `ENCODER_ICB_RUN_PASS checks=579 full_layers=2 attention_layers=1 wait_done=3 outputs=36` |
| 共享 RAM 同步读、字节掩码、上下边界、响应背压及复位保留存储 | `ICB_SHARED_RAM_PASS checks=12` |
| 独立 WAIT_DONE 看门狗、终止故障和取消边界 | `WAIT_DONE_REVIEW_PASS checks=3` |

WAIT_DONE 的独立测试只强制控制信号及接近阈值的计数器，避免执行四千万拍；没有强制或填入任何神经数值、内部输出 RAM 或预期结果。两层小尺寸检查属于短接口 / 控制验证，没有扩展为正式矩阵或 CPU 长跑。

本报告未审 gate / runner，未重签旧矩阵结果，也未把缺少正式工艺库、官方 600 样本或尚在执行的长期回归列为代码缺陷。后续任一上述源码哈希变化，本轮结论和短检查仅保留为旧快照证据，需按变更范围重新复核。
