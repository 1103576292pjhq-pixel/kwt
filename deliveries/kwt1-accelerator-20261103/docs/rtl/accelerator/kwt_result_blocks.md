# kwt_result_blocks：双结果块首版阅读说明

2026-10-31接口修订：row/count各7位、tile4位、sequence9位（单任务1..400）；使用分开的释放身份寄存器，不保留旧打包ACK或legacy/fast兼容。当前控制独立回归见[新报告](../../../verification/controls-20261031T223423-e0e67e/README.md)，ICB连接见[说明](icb-interface.md)。下段早先三任务结果是旧接口身份的历史记录。

日期：2026-10-31。用户确认结果模块思路后授权编写，随后已完成独立TB及三任务内部联合测试：[验证记录](../../../verification/controls-20261031T211136-aba7c3/README.md)。独立测试核对5457个成功读响应、错误ACK重试、并行填读、中止及序号耗尽；生产RTL未修改。联合存储使用测试合同模型，官方宏、ICB及平台未验证。

源码：[kwt_result_blocks.v](../../../rtl/control/kwt_result_blocks.v)。公共位宽和错误码：[kwt_control_config.vh](../../../rtl/include/kwt_control_config.vh)。这是按本轮讨论新写的模块，不是恢复此前删除的同名旧草稿，旧TB与ICB端口不能直接连接。

## 目标与已确认方案

本模块接收已完成量化的Y16/Q12及flags3，不再做乘加和量化。双块分别保存64项19位payload，共2432 bit。描述符、游标、状态和填写记录是另外的控制寄存器，不计入2432 bit。正常块64项，尾行块48项。

用户询问计算核输出顺序后已说明：核按g/p/q发射，但结果位置按p/g/q排列，故填写地址必须用fill_index，而不是已接收项数。正常块索引为0..3、16..19、32..35、48..51，然后4..7、20..23等；尾块跳过p3。最终正常块索引63、尾块索引47。

```text
任务控制：alloc → 启动核 → 等核输出完成 → publish
                       │
计算核 out_* → fill_* → 双结果块 → ICB读请求/响应 → CPU
                         ↑                     │
                         └─────匹配ACK释放──────┘
```

每块生命周期为FREE→FILL→READY→FREE。只允许一个FILL，与现有单核及先算后量化方案一致。另一块可由CPU读取。双块均被占用时alloc_ready=0，上层等空位后才启动下一块。

## 五组端口

| 接口组 | 主要信号及位宽 | 合同 |
|---|---|---|
| 会话 | begin_valid/ready；begin_task_id32 | 所有owner和响应均已清空，且旧会话最终块已发布时可重开；首次及ABORT后也可BEGIN |
| 分配 | alloc_valid/ready；task32、row7、tile4、count7、final1 | row是全局行起点0,4,..96；count普通64、尾48；final仅row96/tile15 |
| 填写和发布 | fill_valid/ready、index6、y16、flags3、block_last1；publish_valid/ready | 对应核out接口；先完成最后一次填写，后申请发布 |
| CPU事务 | cmd_valid/ready、ack1、task32、sequence9、count7；rsp_valid/ready、data32、error1 | 一次一笔响应；ack=0读下一项，ack=1确认并释放 |
| 描述符和状态 | block_valid/read_complete、task/row/tile/count/sequence、cursor7、peek_data19；owned2、response_empty、compute_done、fault/error | 描述符始终指向最早尚未ACK的块；无效时观察字段输出0 |

另有clk/rst_n及abort_req/pending/done。rst_n是共同硬复位；普通中止使用abort_req，不允许用局部复位吞掉已接受的CPU响应。

## 代码分段与硬件含义

### 1. payload和身份

payload0、payload1分别是64×19寄存器阵列。每块描述符保存task、row、tile、count、final和发布sequence，cursor保存0..64。无效描述符和payload不清零，通过state与valid隔离旧内容。

alloc_ptr和head_ptr各1位：分配成功翻转alloc_ptr，合法ACK翻转head_ptr。一次只有一个FILL且必须publish后才能分配下一块，因此固定两块环可以保持发布顺序，不需要再复制一份结果队列。fill_slot独立保存生产块身份，不能用head_ptr代替。

### 2. 填写完整性

每个FILL使用64位written_mask和7位written_count。首次写某位置时对应mask置1；重复、越界、写超量或块末标记不一致时不写payload，锁存生产fault。

fill_block_last必须在第64次或尾块第48次成功填写时出现，并对应最终索引63或47。flags[2]必须等于alloc_final && fill_block_last；flags[0:1]直接保存。last_seen保证完成块末标记后不能再填写。

publish检查mask、count、last_seen和序号资格；普通期望mask低64位全1，尾块低48位全1。提前publish被接受为错误，锁存fault，不发布不完整结果。fill_valid与publish_valid同时存在时填写优先，publish_ready为0，任务控制需保持发布请求。

sequence从1开始，在成功publish时分配，达到参数SEQUENCE_MAX后不回绕；当前默认上限400，用9位表示，独立TB可用较小上限测试耗尽。该模块检查描述符形状和最终标记，不独立证明任务控制已按顺序执行全部400块。

### 3. CPU响应与读取游标

CPU读请求合法时，接受沿把peek_data保存为32位响应：低16位Y、其上3位flags、高13位零。响应停顿期间保持相同data/error。成功读响应在本地rsp_valid&&rsp_ready沿退休后，cursor才增加；错误响应不推进。

例如cursor=0时E0接受读请求，E0沿后rsp_valid=1但cursor仍0；E1若rsp_ready=0则全部保持；E2握手退休，沿后cursor=1、rsp_valid=0，下一拍才接受新请求。本模块不承诺响应退休与接收新事务同拍。

当前独立ICB连接把结果响应直接交付至ICB上游，游标在该交付沿推进；peek_data仅观察不能自行推进。将来若平台额外加桥/缓冲，需要重新核对退休边界，不能假定不同层的ready为同一信号。

### 4. ACK与完成

合法ACK要求当前块已读完且task/sequence/count全部匹配。ACK接受沿立即释放state并推进head_ptr，ACK成功响应独立保留到退休。错误ACK返回rsp_error，块与游标保持，CPU可重试；消费侧错误不锁存生产fault。

读完最后一项不会自动释放。CPU必须先完成共享Y/flags写回及规定的fence，再发ACK。释放后计算侧可以复用该块，但新BEGIN仍须等待ACK响应排空。

compute_done在alloc_final块成功publish后保持，直到新BEGIN/ABORT/复位。它不表示结果全部读完、ACK全部完成或整机任务结束。owned==0和response_empty也只是局部完成条件，上游FIFO、ICB响应及其他模块仍须由任务/接口控制核对。

### 5. 中止与错误恢复

abort_req为单拍，立即阻止新分配、填写、发布和CPU事务。已有rsp_valid不清除，保持到正常退休；随后清state、游标、会话、生产fault与序号，产生单拍abort_done。payload不清零。

如果abort_req到来时无响应，可以在该沿完成清理；如果已有受阻响应，abort_pending保持，响应退休后的下一沿才清理。上层还须停止并取消核及供数器的旧计算，不能只中止结果模块后继续接旧输出。

begin_ready只包含结果模块本地条件。任务控制必须结合装载会话、计算核空闲和系统事务状态形成统一BEGIN握手，不能让多个子模块在不同沿各自接受同一BEGIN。

## 编译检查与下一步

[首版编译记录](../../../verification/result-blocks-20261031-review/README.md)保留当时编译证据，当前功能报告见本文开头链接。

独立TB已覆盖非线性填写、重复/缺项/越界及标记错误、双块满、并行填读、读响应保持与退休、错误ACK重试、会话隔离、序号耗尽和受阻响应ABORT；联合TB核对1200块结果及最后ACK排空。ICB/guard两级事务仍需后续验证。
