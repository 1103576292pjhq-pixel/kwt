# kwt_task_ctrl：任务调度首版阅读说明

2026-10-31接口收窄及ICB连接更新：load无shift、数据32位；结果row/count7、tile4、sequence9。控制独立回归见[新报告](../../../verification/controls-20261031T223423-e0e67e/README.md)。生产顶层已实现，详细连接与总线协议见[ICB说明](icb-interface.md)；下段早先三任务报告按其旧源码身份保留。

日期：2026-10-31。用户授权编写第四个控制模块后，已按要求完成独立400块调度TB及三任务内部联合测试：[验证记录](../../../verification/controls-20261031T211136-aba7c3/README.md)。覆盖两路启动错拍、槽释放、完成排空与中止；生产RTL未修改。内部联合共1200块，使用测试合同存储模型，生产顶层/ICB/平台尚未验证。

源码：[kwt_task_ctrl.v](../../../rtl/control/kwt_task_ctrl.v)。公共位宽沿用[kwt_control_config.vh](../../../rtl/include/kwt_control_config.vh)，新增4位状态宽度和任务错误码。模块不例化其他模块，数据连线及存储bank地址选择留给后续顶层。

## 调度顺序

```text
IDLE → BEGIN同沿初始化 → WAIT_START
     → WAIT_TILE → ACTIVATE → ALLOC → START_BLOCK → RUN → PUBLISH
                                  ↑                       │
                                  └────下一行组─────────────┤
                                                         ↓ 最后行组
                   下一tile ← WAIT_TILE ← RELEASE → DRAIN → COMPLETE
```

tile外层0..15，行组内层0..24，共400块。正常mask1111、count64；行组24对应row0=96，mask0111、count48。仅tile15/行组24的final为1。

先等装载控制某槽为READY且tile身份匹配，再请求激活；激活后先分配结果块，成功后再启动计算核和供数器。每个tile的25个行组复用同一个ACTIVE槽，最后行组成功publish之后才请求release。下一tile未装完或双结果块满时正常等待。

## 接口对应关系

| 本模块端口组 | 连接对象与作用 |
|---|---|
| load_begin_*/load_start_* | 装载控制的BEGIN/整个任务START握手 |
| load_session_*、load_x_ready、load_slot_* | 装载控制的身份及就绪状态；task32、layer4、槽状态4、槽tile8 |
| load_activate_*/load_release_* | 装载控制槽事件；valid/ready/slot各1位 |
| feeder_start_* | 供数器启动；row_group5、slot1，握手各1 |
| core_start_* | 核启动；mask4、final1，握手各1 |
| feeder_done/core_block_done、busy | 完成脉冲及运行状态，全部1位 |
| result_begin_* | 结果模块会话初始化；与装载BEGIN同沿成交 |
| result_alloc_* | 结果块分配；task32、row7、tile4、count7、final1 |
| result_publish_* | 结果发布valid/ready；数据fill通路由顶层直接连接核 |
| result_owned/response_empty/compute_done | 结果owner2位、响应空及最终发布状态 |
| 子模块fault/error_code | 错误停止；错误码8位，供数异常使用任务码31 |
| input_fifo_empty/transport_empty | 后续ICB提供，必须覆盖pair半项、响应及本拍新accept |
| abort_req/result_abort_*/abort_pending/done | 中止并协调结果响应与上游事务排空 |
| worker_rst_n | 接装载、供数、核、存储wrapper复位；结果模块保持全局rst_n |

active_w_slot同时用于顶层bias组合读槽。current_row_group与current_tile供状态观察，task_id和layer_id保存当前会话身份。块启动到发布期间元数据保持。

## 启动与完成不能混淆

START_BLOCK用feeder_started/core_started分别记录握手。例：E0核接受启动，E1供数器仍未ready，E1核启动valid已撤销，供数器valid继续保持；供数器接受后进入RUN，不会对已启动的核重复发送启动。

feed_done_seen和core_done_seen保存完成脉冲。RUN等待供数与核输出均完成后才进入PUBLISH；feed_done不能提前释放bias/W。核输出、结果写入、valid/ready的数据连接不经过任务控制。

compute_done来自结果模块最终块成功publish。task_done还要求最后W槽已释放、核和供数器空闲、结果owner清空、最后ACK响应及输入命令排空。task_done是满足条件的电平，不是单拍，也不是guard COMPLETE；后者仍有模式、共享内存及token等系统条件。

## BEGIN与恢复接线

load_begin_ready=本地安全条件与result_begin_ready；result_begin_valid=load_begin_valid与本地安全条件。这样装载、结果和任务在同沿BEGIN成交，且valid不依赖接收方ready。

BEGIN安全条件不要求load_command_empty，因为该BEGIN正占装载q；也不要求后续FIFO为空，因为后面可能已排入新任务的X命令。旧owner和响应必须排空，核和供数器必须空闲。正常软件仍应在前任务完成后提交新BEGIN，不能在旧tile未装完时把BEGIN塞到装载队首。

错误被锁存后停止新调度，worker_rst_n拉低取消旧内部计算。结果模块不能用该复位，以免吞掉已接受响应。普通ABORT由result_abort_req传给结果模块，并记忆它的单拍abort_done；接口层在abort_pending期间停止新访问、排空响应并清除旧FIFO。全部排空后task abort_done单拍完成，允许新BEGIN。

接口层不能等待worker继续消费旧FIFO，因为中止期间worker处于复位。硬复位rst_n只能按整个系统共同复位协议使用，不能当作普通总线取消。

## 当前检查与待验证

[首版编译记录](../../../verification/task-ctrl-20261031-review/README.md)保留当时编译证据，当前功能报告见本文开头链接。

独立TB已核对400块元数据、两路启动错拍（226次供数先启动、174次核先启动）、结果分配等待、16次W槽释放、最终排空、连续BEGIN及中止/错误锁存。联合TB用实际子模块完成三任务并取消一个供数中途任务。未穷举所有状态的ABORT排列；真实ICB事务和FIFO清理仍需集成验证。
