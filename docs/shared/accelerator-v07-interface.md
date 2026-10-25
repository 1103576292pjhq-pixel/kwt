# V07独立FFN第一线性层加速器

本版按照个人模块边界重新实现外围，调用已验证的四个V07局部计算模块。只包含独立加速器；没有E203、总线寄存器、驱动或双模式系统。默认矩阵为M99/K64/N256，每次任务的X独立加载。

新增外围RTL和外围测试平台均使用`.v`文件及Verilog-2005语法；外围脚本使用`iverilog -g2005`，试综合读取源码也不启用SystemVerilog。

## 模块目录与阅读顺序

1. `rtl/accelerator_top.v`：查看全部连接；顶层不重复计数。
2. `rtl/control/command_frontend.v`：理解外部怎么装载和启动。
3. `rtl/control/tile_ctrl.v`：理解两个槽的所有权。
4. `rtl/memory/x_buffer.v`、`w_tile_buffer.v`、`sram_wrapper.v`：地址映射和同步读。
5. `rtl/control/matrix_ctrl.v`：理解一个块的256组供数。
6. `rtl/output/result_ctrl.v`：理解结果选读、偏置、索引、背压及释放。
7. `rtl/compute/`：现有计算模块，接口详见`dot64-v07-interface.md`。

八个新增模块文件对应此前确认的八个职责。权重槽状态只在tile_ctrl中；加载数量只在frontend中；行组/k/ctx只在matrix_ctrl中；结果扫描/消费数量只在result_ctrl中。

## 顶层端口

| 信号 | 方向/宽度 | 含义 |
|---|---|---|
| clk | 输入1 | 上升沿时钟 |
| rst_n | 输入1 | 同步低有效复位，须覆盖上升沿 |
| abort_i | 输入1 | 同步中止整任务；优先于所有握手 |
| in_valid / in_ready | 输入/输出1 | 命令握手 |
| in_op | 输入4 | 命令类型，见下表 |
| in_layer_id | 输入4 | 层号1..12，整任务保持一致 |
| in_task_id | 输入32 | 本次任务身份；整任务保持一致 |
| in_tile_id | 输入8 | 权重tile号，默认0..15 |
| in_index | 输入16 | X或tile内W/bias元素序号 |
| in_data | 输入signed48 | 元素数据容器 |
| in_shift | 输入6 | 本数值方案固定16；其他值拒绝 |
| out_valid / out_ready | 输出/输入1 | 结果消费握手 |
| out_task_id | 输出32 | 与结果对应的任务ID |
| out_y_index | 输出32 | 全局行优先线性索引i*N+j |
| out_data | 输出signed32 | RNE/sat16后符号扩展的Q12编码 |
| out_flags | 输出3 | bit0物理溢出，bit1输出饱和，bit2全任务最后结果 |
| task_done | 输出1 | 单拍完成通知，所有结果已消费且最后块已释放 |
| busy | 输出1 | 当前有任务，或存在尚未恢复的fault；task_done当拍为0 |
| fault / error_code | 输出1/8 | 粘滞协议错误；复位或abort后恢复 |

valid=1且ready=0时，发送者必须保持本项全部字段稳定。每次valid&&ready只接收一条命令或一项结果。rst_n=0、abort=1或fault取消状态下不计正常结果退休。

`task_done=1`当拍允许接收下一任务BEGIN。没有紧接BEGIN时，busy保持0；接收新BEGIN后busy重新为1。输出传输已经全部完成，因此旧任务ID不会与新输出混淆。

## 命令协议

命令直接执行，没有内部命令排队：输入握手边沿就是实际存储写入/状态更新边沿。

| op | 名称 | 合法条件和操作 |
|---:|---|---|
| 0 | BEGIN | 空闲或task_done通知周期；layer=1..12、shift=16；登记任务身份，撤销上一任务缓存所有权 |
| 1 | X | START之前且尚未OPEN首tile；index严格0..M*64-1；data必须为signed16的正确48位符号扩展 |
| 2 | OPEN | X全部加载；tile严格从0递增；首tile在START前，后续tile在START后；申请FREE槽 |
| 3 | W | 已OPEN；index严格0..1023；全部W先于bias；data必须为signed16正确符号扩展 |
| 4 | BIAS | 当前槽已收1024项W；index严格0..15；data必须为signed32正确符号扩展 |
| 5 | COMMIT | 当前槽1024项W和16项bias都完成，槽从LOADING变为READY |
| 6 | START | 完整X及tile0已经提交，无未关闭的OPEN；仅允许一次 |

op1..6的task_id、layer_id和shift必须与BEGIN一致。W/bias/COMMIT的tile必须与当前OPEN一致。

合法OPEN遇到两个槽都占用时，in_ready=0，等待一个槽真正释放；其他非法命令会在握手时锁存fault，error_code=0x10+op，且不执行该条写入。fault会中止整个后端并撤销旧输出，直到外部reset/abort。中止后必须重新BEGIN、重新加载完整X及参数，不承诺恢复半个任务。

普通任务顺序：BEGIN → X全部 → OPEN0 → W0 → bias0 → COMMIT0 → START → OPEN1/W1/bias1/COMMIT1 → … → 最后结果消费 → task_done。

### 地址与装载格式

X输入流为行优先：index=i*64+k。

每个tile输入流按k优先、tile局部列c次序：index=k*16+c，元素来自数学矩阵W[k,tile*16+c]。无需把NPY文件头送入硬件，也不依赖队友软件中可能使用的转置存储容器。

X：bank=i%4，bank内地址=(i/4)*64+k。默认各bank规划1600×16，实际X载荷6336项，尾部一个bank缺少最后一行。

W：slot由tile_ctrl指定；bank=c%4，bank内地址=(c/4)*64+k。每槽4bank×256×16，总载荷2KiB；两槽共4KiB。

偏置：每槽16×32位寄存器，共128字节；加载前验证48位容器确为signed32符号扩展。选读时再扩到48位，不改变数值范围。

## 计算与双槽生命周期

每个槽：FREE → LOADING → READY → ACTIVE → FREE。

同一tile遍历所有行组，默认row_base=0,4,…,96。普通组mask=1111，最后组mask=0111。每个块256次输入握手，k=0..63，每个k对应ctx0..3，最后一次带block_last。

matrix_ctrl采用一次一个读请求在途的初版：READ_REQ → READ_WAIT → SEND。X只在ctx0读取并保存，ctx1..3复用。READ_LATENCY=1时，稳定供数间隔约3拍；=2时约4拍。本核心可以每拍接收，但本版外围有意允许空拍，以简化读返回、稳定性及初学者调试。后续可在不改变模块职责的前提下增加带容量预留的预取。

结果全部消费后，result_ctrl撤下read_valid、请求block_release，直到block_ready重新有效才发block_done。matrix_ctrl随后推进下一行组；只在当前tile全部行组结束时发tile_done，tile_ctrl才释放权重槽。另一个槽可在当前槽ACTIVE期间独立加载。

SRAM返回和输出背压都不会使k/ctx提前推进。读请求地址在在途阶段保持，供数暂存数据在核心握手之前保持。

## 结果选读与输出顺序

不新增64项结果缓冲，也不设置Y SRAM。64个累加值留在计算核心，转换模块自身的一项弹性寄存器承受外部背压。

result_ctrl按块内row、ctx、col枚举，局部列c=4*ctx+col，偏置取对应槽的bias[c]。

全局索引=(row_base+row)*N+tile*16+c。

总体输出顺序为tile优先，每tile内行优先。默认开头输出索引0..15，接着256..271，不是0..25343整体顺序。接收方必须按索引归位，并检查重复、缺失和顺序。有效结果总数M*N；最后一个结果的flags[2]=1。尾部无效行不发选读请求。

选读接收数和结果消费数是不同事件：转换寄存器中可能还保存一项尚未消费的结果。不能用最后一次read握手代替完成通知。

## 现有宏的试验映射

USE_MACRO=0为行为模型；=1使用本地TS1N28HPCPL2LVTB2048X32M4MWBASO。四个X逻辑bank加八个W逻辑bank，暂各用一颗物理宏的低16位，高16位写屏蔽，共12颗宏。每颗8KiB，实际实例容量共96KiB，不能把4KiB权重载荷当作实际宏容量或宏面积。

2026-10-25按队友现有库将SVT替换为LVT，已核对两者模型的端口声明相同。仿真模型和Yosys试综合Liberty默认均选择tt0p9v25c（典型工艺、0.9V、25°C）。队友使用Synopsys工具时加载对应的TS1N28HPCPL2LVTB2048X32M4MWBASO_tt0p9v25c.db，并使USE_MACRO=1；RTL中的cell名不包含工况后缀或.db扩展名。其他工况应在库配置中选择，保持同一cell名。

CEB/WEB/BWEB低有效；普通写时Q保持；读请求在上升沿采样，之后Q有效。wrapper生成read_valid，支持1/2拍返回。当前宏分支不是面积优化映射，作用是先连实际库试验；赛方发布后可替换这里而不修改核心。

reset/abort仅清理有效标志与槽所有权，不给SRAM逐项清零。下一任务必须重新加载所有合法位置，不允许复用上次缓存获得冷任务性能优势。

## 验证及综合命令

从本工作树根目录在WSL运行：

```bash
# 原计算核心回归
bash scripts/rtl/run_v07_tests.sh
# 默认M5 N32，两次独立层任务
bash scripts/rtl/run_accelerator_tests.sh
# 两拍读返回
TEST_LATENCY=2 bash scripts/rtl/run_accelerator_tests.sh
# 完整12层独立任务，逐项核对304128项结果
TEST_M=99 TEST_N=256 TEST_LAYERS=12 bash scripts/rtl/run_accelerator_tests.sh
# 连接本地宏模型，默认小矩阵
TEST_MACRO=1 bash scripts/rtl/run_accelerator_tests.sh
# Yosys通用门级试综合，宏按本地Liberty作为黑盒实例
bash scripts/rtl/synth_accelerator.sh
```

测试脚本串行使用out/accelerator-vectors；不要在同一工作树同时执行不同参数的两份运行。可设置SRAM_MODEL_DIR、SRAM_LIB_DIR和YOSYS覆盖本地路径。宏/商业库文件保留在仓库外，不复制进源码。

tb_buffers逐lane检查全部X、两槽W和偏置，共8480项，并检查另一槽写入不破坏活动槽。整机TB检查数值、flags、任务身份、输出顺序/重复/丢失、连续命令、完成当拍BEGIN、非法命令、运行/输出阶段故障、同步复位、中止、背压。

宏仿真使用UNIT_DELAY，模型在仿真0时刻可能报CEB初始化/唤醒顺序警告，不能把功能模式作为真实时序验证。试综合只有RTL降级、通用门级和check结果，没有标准单元工艺映射、150MHz STA、整片面积或能耗结论。

## 计算依赖来源

外围先在独立工作树ffn-v07-peripheral中实现并验证，现按用户要求直接接入VS Code当前打开的dot64-core工作树。这里直接调用当前rtl/compute/的四个模块及共享头文件，没有覆盖计算源码。此前的完整十二层和实际宏验证记录保存在外围工作树的docs/reports/20261023-v07-accelerator/中。

本机临时Yosys工具目前保留在相邻外围工作树，可用以下命令试综合；如果已经安装Yosys则直接使用上面的命令：

```bash
YOSYS=../ffn-v07-peripheral/work/tools/root/usr/bin/yosys bash scripts/rtl/synth_accelerator.sh
```
