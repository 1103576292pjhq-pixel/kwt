# 给新对话的交接词：开始编写FFN1点积计算RTL

2026-10-29资料入口补充：[RTL协作流程](../workflow/rtl-collaboration.md)、[通用学习笔记](../learning/rtl-basics.md)、[点积四模块开发记录](../rtl/README.md)。本文保留历史；后续整机信息按[归档规划](../rtl/accelerator/README.md)持续补充，不重复编写点积核。

> 2026-10-28阶段更新：点积核已经完成并接收验证。新对话请改读[整个独立加速器交接词](full-accelerator-new-chat.md)。本文件下文保留历史形成过程，其中“尚未实现/未验证/从点积开始”等旧任务不再适用。

最新追加：顶层已按用户要求改成三段式FSM，状态寄存、组合下一状态、组合控制输出分别整理，计数/元数据独立时序保存。当前源码对应 `verification/block-core-20261028T215423-d9c5a6/` 的完整回归，再次通过真实样例12层304128项Y及flags比较。与修改前版本额外逐拍比较185433拍一致，证据见 `verification/fsm-three-stage-20261028/`。下面的首轮顶层报告保留历史身份，不代表当前三段式源码。

## 最新状态优先：2026-10-28顶层已验证

按用户要求新增 `tb/compute/tb_dot_product_block_core.v` 和 `scripts/verify_block_core.py`。当前四个生产RTL及宏保持原样，Verilog-2001编译与端口级回归通过。正式证据在 `verification/block-core-20261028T211900-669e21/README.md`、`report.json`。包含23块定向/随机/复位用例、既有手算完整任务400块，以及本地一条真实音频所保存的12层输入4800块；真实层共304128项Y及flags逐位一致，6种故意错误被检出，33项软件测试通过。

本次由TB外围拆块供数并重建矩阵，仍没有硬件矩阵调度器、真实SRAM或整机验收。接下来等待用户选择工作，不重复写顶层或把下文较早“尚无TB/未仿真”当成当前状态。下文保留形成过程与冻结要求；当前源码身份以最新报告SHA256为准。

以下内容可作为新对话的任务说明。先读取文件、核对当前状态，再协助我逐步编写点积计算部分；不要重新设计已确认的整体架构。

状态更新（2026-10-28）：乘法阵列和四上下文累加组件已分别自检通过；偏置/量化模块 `rtl/compute/result_convert.v` 已写入，六处易混淆点有对应中文注释，并通过16例初步定向自检。下一步先审阅量化代码并补完整回归，再连接流水。最新入口为 `README.md`、`docs/implementation/progress.md` 与 `verification/README.md`；不要按早期“RTL为空”的状态重新开始。

进一步更新：`rtl/compute/dot_product_block_core.v`已按用户批准的单块状态流程连接三个算术模块，用户要求先写代码供阅读、先不验证，目前没有顶层编译或仿真记录。输入是有序且已对齐的256组操作数返回流，ctx/last由真实接收计数派生；bias为组合选读接口。先审阅这些边界，再按用户要求验证，不凭组件PASS推导顶层PASS。

最新量化状态：已直接接收用户修改的 `result_convert.v`，没有改写其RTL，补充TB/脚本后通过5788组数值与8390拍流式回归。证据在 `verification/result-convert-20261028T200650-af0cd6/`，含本次确切源码快照。旧16例记录仍保留为历史身份；下一步是按用户指示审阅/验证顶层。

## 1. 我的目标与协作方式

我参加2026年嵌入式芯片设计竞赛本科组，主要负责RTL。我现在先写点积计算部分，必须知道每段代码为什么存在、每个信号和位宽的原因，以及复位、握手、流水排空怎样工作。

请先讲清模块分工和建议接口，再按小模块、短代码段帮助我编写、解释和验证。不要未经我要求一次性代写整个独立加速器或SoC。遇到原因不清的设计先查证和解释；能证明多余或不符合数值规格的再修改，不能因为没看懂就删除必要控制。

本阶段只做计算底座与对应测试：有符号乘法、累加上下文、bias/量化转换、必要的计算流水控制。X/W SRAM、双W槽、命令FIFO、双结果owner、MMIO、E203驱动、共享RAM、G编码器均为外围背景，不在本次起步范围。

## 2. 唯一活动工程与环境

- Windows新工程：`D:/嵌赛芯片设计赛道/kwt1-accelerator`。
- WSL新工程：`/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator`。
- WSL发行版：Ubuntu。已观察到`/usr/bin/python3`为3.10.12、NumPy可用、`/usr/bin/iverilog`和`/usr/bin/vvp`存在。具体本次验证见`verification/wsl-environment.json`。
- 编辑器使用VS Code的WSL连接，在上述WSL路径工作。
- Windows数值验证环境为Python3.12.4、NumPy1.26.4；WSL不要直接调用Windows的Anaconda路径。
- 新工程目前未初始化Git；不要把“没有.git”误判为文件缺失，也不要自行提交或推送。

当前源码为 `rtl/include/kwt_compute_config.vh`，以及 `rtl/compute/` 下的 `mul_array_4x4.v`、`acc_context_bank.v`、`result_convert.v`、`dot_product_block_core.v`。前三者的对应TB在 `tb/compute/`，顶层尚无TB。乘法证据在 `verification/mul-array-20261027T213804-ee2726/`，累加证据在 `verification/acc-context-20261028T131043-851d21/`（640项最终acc与Python黄金对照），量化初步定向证据在 `verification/result-convert-20261028T184028-3b2659/`。只对报告记录的源码SHA256及相应覆盖范围作通过声明，不把组件结果当作连接流水或整机通过，也不把旧目录实现当作本工程成果。

## 3. 必须先读的文件

以下路径均相对唯一活动工程根目录，按顺序读取：

1. `README.md`：阶段、范围和入口。
2. `model/numeric-contract.json`：冻结数值合同，身份`KWT1-FFN1`。
3. `docs/model/README.md`：数值模型逐段原理。
4. `model/fixed_numeric.py`：重点读`convert_accumulator`、`dot64_scalar`、`ffn1_int16`。
5. `tests/test_numeric.py`：手算、极值、k63、有符号乘法和RNE测试的既有期望。
6. `docs/architecture/README.md`：整体修订规格，尤其数值、存储/计算结构和时序。
7. `docs/architecture/module-guide.md`：重点读第6—10节的计算、状态、量化和结果边界。
8. `docs/architecture/decisions.md`：16MAC/CTX4、40位和各种常量的依据。
9. `verification/summary.json`、`verification/dev12-compatibility.json`、`verification/review.md`：现有软件验证身份和边界。

按需再读：

- `model/layout.py`：小端、W列主序、bias64/Y32容器。不要把传输容器当内部算术位宽。
- `examples/hand-check/example.json`及同目录`x.bin/w.bin/bias.bin/y.bin/flags.bin`：完整任务中的可手算首4×16块。
- `docs/data-sources.md`、`verification/local-float-reference.json`：原始音频/模型来源及本地单样例误差。
- `docs/architecture/platform-sources.md`：共享SRAM暂行条件。该资料缺口不阻止点积算术模块开发。

WSL中第一份必读文件的绝对路径是：
`/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator/README.md`。

## 4. 数值方案已经确定，禁止退回48位算术

| 数据 | 位宽 | 小数位 |
|---|---:|---:|
| X | signed16 | 12 |
| W | signed16 | 16 |
| 精确乘积 | signed32 | 28 |
| bias | signed32 | 28 |
| acc | signed40 | 28 |
| 加bias临时和 | signed41 | 28 |
| 内部Y | signed16 | 12 |

固定K64，按k0..63累加，数学规则每前缀sat40；加bias后sat40；RNE右移16，再sat16。正式配置不支持任意shift0..47，不使用sat32输出。

64项乘积加bias的合法范围为[-70,864,863,232，70,866,960,383]，严格在signed40内。所有前缀也安全，所以可以依据范围证明实现40位普通累加，不必为合法域永不发生的前缀溢出增加复杂饱和逻辑。不要擅自继续缩到38位；40位是已确认规格。

加bias时必须先符号扩展到41位，再检测和裁剪为40位。乘积进入acc时符号扩展到40位，不能按无符号解释。Python int64用于软件计算，不意味着硬件acc64。

RNE对负数也取最近偶数：+2.5→2，+3.5→4，−2.5→−2，−3.5→−4。最终饱和范围[-32768,32767]，发生在舍入之后。

flags：bit0=raw40加偏置溢出；bit1=最终Y16饱和；bit2=整个矩阵任务最后一个输出。合法K64任务bit0恒0；组件`convert_accumulator`允许任意acc40，用来单独测试raw溢出语义。

global_last由外围任务位置决定，不能对每个点积或每个4×16块都置1。最后一组乘积的block_last、点积计算结束与全局Y最后项是不同概念。

外部legacy命令48位、共享bias64位、共享Y32位可以为接口兼容保留。它们不是acc/bias继续使用48位的理由；X/W/bias在边界先检查范围，再取有效位。核心输出保持16位，外部需要时再符号扩展为32位。

## 5. 点积部分必须服务现有16MAC架构

整体计算为X[99,64]×W[64,256]+bias→Y[99,256]。PM4、PN4、CTX4，总16个16×16乘法器，处理4行×4列外积；四个g上下文各存4×4个acc，合计64个40位累加值，覆盖一个4行×16列块。

`acc[g,p,q] += X[row0+p,k] * W[k,16*tile+4*g+q]`。

固定k时g0、g1、g2、g3轮转，随后k++，一个块共256个有效读/计算组。CTX4增加的是独立累加状态，不是64个乘法器；不同上下文不能相加成同一个输出。

已有完整架构是固定延迟SRAM读请求标签→乘积寄存→acc累加，生产基线L1；请求和返回的k/g/mask/身份必须分清。最后请求发出后仍有乘积在途，必须排空后才报告累加完成。

可以先用单个64项点积作数学学习/局部测试，但不能把它直接变成替代正式16MAC/CTX4的单乘法器主架构，也不能把Python标量接口机械当成最终核心端口。

建议先按职责理解并逐个实现：16路乘法阵列→四上下文累加→偏置/量化转换→计算流水和排空连接。文件名和小模块具体端口尚未在新目录冻结，应先提出与现有数据流一致的最小接口并解释，不声称已经确认某套现成端口。可使用可综合Verilog/SystemVerilog，与Icarus `-g2012`兼容。

## 6. 测试要求及软件黄金用法

先在WSL运行本工程软件基线：

```bash
cd '/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator'
python3 -B -m unittest discover -s tests -v
```

已有33项软件测试，以及原DEV12十二套共304128项Y和同数flags的逐项一致记录。这些不是新RTL通过记录，实际重跑结果另存，不覆盖原证据。

写RTL前先用手算向量确定期望，再与`dot64_scalar`/`convert_accumulator`一致。硬件位图比较时统一有符号解释，不能把16'hffff错误当成+65535。

最少覆盖：

- 全零、正负组合和有符号乘法；只有k63非零，检测漏尾。
- 64项最大正/负累加、正负抵消；保持32位乘积精度，不能逐项先右移再累加。
- bias0、正负bias，正负2.5/3.5 ties，刚好达到输出端点及舍入后越界。
- 16个lane与四上下文对应关系、行mask、复位中断、连续块不串结果。
- 若模块采用valid/ready，统计真实握手，受阻时载荷保持；不能只按时钟拍数推进计数。
- 乘积valid与ctx/mask/last一同延迟；最后乘积真正更新acc后才完成。
- 量化输出背压时不跳项、不重复消费。

要实际编译、运行自检TB，并保存明确命令/工具/退出码。只读波形或“编译没报错”不算功能通过。不要改黄金迎合错误RTL。全任务Y/flags回归要等相关矩阵外围完成后再做，不把当前点积TB称为整机验收。

## 7. 只读参考旧工程，禁止覆盖

旧个人工程：
`D:/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core`；WSL为`/mnt/d/嵌赛芯片设计赛道/kwt1-accelerator-2026/worktrees/dot64-core`。

其中`rtl/compute/mul_array_4x4.v`、`acc_context_bank.v`、`result_convert_v07.v`、`dot64_tile_core.v`可按需只读借鉴。该目录有大量未提交/未跟踪成果，不reset、不clean、不覆盖，不拿旧HEAD代替真实工作区；也不要因可参考就整目录复制。

队友冻结包：
`D:/嵌赛芯片设计赛道/KWT1_前端工程交付包/KWT1_frontend`。

可参考其`rtl/bachelor/rtl/revd_opt/core_stream_tiled_w2_opt.sv`和`rtl/bachelor/rtl/revd/quant_epilogue.sv`理解流水，但它们仍用acc48/bias48和可变shift；不是本工程数值规格。该包保持只读。

## 8. 已知范围和后续交付

原始数据已在datasets/，模型权重在keyword-transformer/；不要为点积模块重新下载、训练或改尺度。已有一条验证音频的12层浮点检查最差NRMSE约0.0201543%，仅本地单样例，不是官方600样本资格。

正式内部SRAM宏映射、共享512KiB平台接口、E203联调、150MHz、2.25mm²和功耗都尚待后续验证；不阻止本阶段点积算术RTL，但不能提前宣称赛事全部通过。

每完成一个小模块，请给我：代码及每段原理、信号/位宽依据、输入到输出的时序、实际测试命令与结果，以及延迟/吞吐/寄存器数量等可证实指标。没有综合和STA时不要编造mm²、MHz或功耗。

新对话第一步：读上述必读文件和最新实现进度，核对现有三个算术模块及其各自验证边界，复述固定数值规则，先从量化代码审阅与后续回归开始。继续采用“用户先讲思路，助手解释纠正，共识后写代码”的方式，不重复实现已完成模块，不跳到整个SoC实现。
