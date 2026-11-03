# 独立ICB接口及加速器连接说明

日期：2026-10-31。用户授权：保留整体计算/存储架构，具体接口独立设计，并完成RTL和实际验证。外部信号依据用户指定E203的sysper接口；寄存器表是本工程设计，不是赛题规定。原始数据来源规则见[设计来源](../../workflow/design-sources.md)。

## 当前模块与编写理由

| 文件 | 作用 |
|---|---|
| [kwt_icb_regs.v](../../../rtl/interface/kwt_icb_regs.v) | 接受32位ICB请求，检查地址/写掩码与字段高位，配置/状态寄存器，本地响应快照，结果响应路由 |
| [kwt_command_fifo.v](../../../rtl/interface/kwt_command_fifo.v) | 固定一项待执行命令快照，最小解耦总线接受与内部执行；允许同拍出入替换 |
| [kwt_result_access.v](../../../rtl/interface/kwt_result_access.v) | 将读/释放事务转给结果块，成功响应直接透传，无隐藏提前退休；空访问由本地错误响应处理 |
| [kwt_icb.v](../../../rtl/interface/kwt_icb.v) | 上述三个模块的连接及命令字段拆包，错误/中止清旧输入，输出排空状态 |
| [kwt_accelerator.v](../../../rtl/kwt_accelerator.v) | 生产加速器连接顶层，例化ICB、四控制、既有计算核和存储wrapper；逐bank选择装载/供数地址 |

公共总线位宽与寄存器偏移见[kwt_icb_config.vh](../../../rtl/include/kwt_icb_config.vh)，当前完整源列表为[kwt.f](../../../rtl/kwt.f)，不包含测试替身或旧行为存储草稿。正式编译需要额外提供两种官方SRAM模型/库。

## 控制字段重新论证后的调整

| 字段 | 当前宽度 | 原因 |
|---|---:|---|
| cmd_data | 32 | 对接ICB写数据；X/W检查高16位符号扩展，bias直接signed32 |
| cmd_op | 3 | 七类内部操作，需要表示0..6，保留7作为非法编码 |
| cmd_tile_id | 4 | 16个tile，0..15 |
| cmd_index | 13 | X索引0..6335，含测试非法值6336..8191 |
| row/count | 各7 | 行起点最大96；结果count需包含64 |
| sequence | 9 | 单任务400块，序号1..400，任务切换重置，不回绕 |
| task_id/layer_id | 32/4 | 自定义会话身份；32位方便CPU整字写任务标签，4位可标识12组层参数，不额外做强制层编号范围假设 |

去掉48位命令容器和运行时cmd_shift，固定量化规则仍由计算核实现。没有PAIR、legacy/fast或旧ACK打包格式。初始化、写数据、申请W槽、提交完整槽、启动任务等操作有实际控制作用，仍用七类内部命令表达；编码只属于当前自定义接口。

## 总线与寄存器操作

端口为cmd_valid/ready、addr32/read/wdata32/wmask4及rsp_valid/ready、rdata32/err；read=1读、0写。接受沿为cmd_valid&&cmd_ready，响应退休沿为rsp_valid&&rsp_ready。一次仅一笔响应，不同拍复用请求；受阻时保持相同响应。

默认基址0x11000000处于公开框架SysPer窗口内，BASE_ADDR参数可修改且须256字节对齐。完整高地址比较，避免只看偏移造成别名；每次4字节对齐，写mask必须1111。无效地址、只读寄存器写、保留高位、未知命令等都返回err且无副作用。该策略是本工程整字寄存器设计，不表示ICB总线本身禁止字节写。

详细[寄存器表与设计计划](../../implementation/icb-independent-design-20261031.md)。典型装载过程：写TASK/LAYER、TILE/INDEX/DATA，然后写COMMAND=op，成功入缓冲时完整快照。之后改暂存寄存器不影响旧命令。索引不自动推进，软件显式设置。

一项命令缓冲满时，COMMAND提交返回错误，已排队内容不变，不能把失败提交当作执行。软件应服务已发布结果再重试相同提交；结果访问和状态查询不受命令满直接阻塞。该容量是首版最小解耦实现，不宣称最优吞吐。

读取RESULT_DATA获得{高13位零,flags3,Y16}，按响应退休推进结果cursor；结果内部填充顺序不会改变CPU连续读取顺序。读完全部项后，写ACK_TASK/ACK_SEQ/ACK_COUNT，再写ACK=1。只有身份和读取完整性匹配才释放块；错误ACK只返回错误，允许纠正后重试。

## 完成状态和中止

实时task_done要求内部与总线排空，CPU读取STATUS会使总线不空，因此STATUS另有completion_seen记录已达到完成的事实。新BEGIN成功入缓冲、错误或ABORT清记录。STATUS bit3表示可轮询的完成记录，bit1 busy据此消隐；外部task_done仍保留实时安全排空语义，不以状态记录代替guard条件。

该问题已用专门tb_icb_completion复现“状态读取永远看不到done”，再增加记录位修复。初始失败与修复运行日志保存在verification/icb-work-root/completion-red.log和completion-green.log，最终回归会再次执行此测试。

ABORT=1的合法写接受沿发中止，external_abort_req也可取消任务。接口清待执行命令和配置，保留已经接受的本地/结果响应；task_ctrl等待响应和输入排空后给abort_done。不能用worker_rst_n复位ICB或结果响应。fault/中止期间拒绝普通写及结果读/释放，STATUS/ERROR仍能读。重复ABORT在本次中止尚未结束时返回错误。

## SoC接线边界

在指定E203框架中，用真实sysper cmd/rsp连接替换原SoC顶层占位响应，再提供同域hfclk及匹配复位。生产顶层输入clk不是把晶振hfextclk直接冒认为工作时钟；实际导出/集成位置须以赛方平台工程确定。

当前加速器是从设备，无DMA，不主动读共享RAM。软件从共享RAM取数据写入本接口，再将读出的结果写回共享RAM。临时512KiB共享RAM尚不属于该顶层，平台RAM/CPU固件联调和赛事验收另列。

## 测试入口

`/usr/bin/python3 -B scripts/verify_icb.py --contract-models`执行接口独立TB及实际生产顶层双任务总线自检。数据为脚本固定种子合成矩阵，Python独立整数黄金；测试专用SRAM合同模型不等于官方宏。最终通过身份与统计以新建verification/icb-*报告为准，不能仅凭本说明判断通过。
