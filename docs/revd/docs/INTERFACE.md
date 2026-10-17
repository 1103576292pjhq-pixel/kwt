> 继承RevC契约，末尾RevD补充优先；当前总计划见根目录PLAN.md。

# RevC逻辑接口与缓冲契约

状态：待实现硬件的设计契约。`tools/protocol_model.py` 只是部分规格的可执行模型，不是完整协议仿真器或RTL。

## 1. 一个有序入口，避免不必要的一来一回

使用普通SystemVerilog信号；建议入口字段：`in_valid/in_ready`、`in_op[3:0]`、`in_task_id[31:0]`、`in_layer_id[3:0]`、`in_tile_id[7:0]`、`in_index[15:0]`、`in_data signed[47:0]`、`in_shift[5:0]`。

这是宽的内部逻辑端口，不表示E203有这么宽的数据总线。后续适配层会拆/装32位事务。unused字段置0并可检查，避免描述符含糊。

建议事件编码：BEGIN=0，LOAD_X=1，TILE_OPEN=2，LOAD_W=3，LOAD_B=4，TILE_COMMIT=5，START=6；其他编码非法。完成和故障用独立状态输出，不要求正常的每笔数据再经过一个反向应答通道。

`in_fire=in_valid&&in_ready`仅表示进入入口队列；`retire`表示有序解码后的实际动作生效。入口FIFO默认2条，不能凭高位宽堆大FIFO。可以连续接受一个逻辑元素/拍，但是否达成必须看RAM、消费端和真实仿真，不能由协议名称推定。

严格按队列顺序退休，不把命令单独走快通道。TILE_COMMIT退休前必须确认所属tile的全部W、bias和pending RAM write都完成。START在FIFO中的位置不赋予它越过写入的能力。

## 2. 装载次序

BEGIN在IDLE接受，锁存task/layer/shift。几何为编译配置，不在任务间任意改变。

LOAD_X：index=m*64+k，严格递增0..M*64-1；data必须是合法int16符号扩展。只装99行有效输入，不喂存储填充行。

TILE_OPEN：给逻辑tile_id=0..N/16-1，核心选择EMPTY槽，调用方不指定物理slot。一次只允许一个FILLING输入块；OPEN序列严格递增。

LOAD_W：块内index=k*16+j，严格递增0..1023；data为合法int16。数学W[k,nt+j]与内存bank地址不混用。

LOAD_B：在该块1024个W全部接受后，index=j递增0..15；data为signed48。不允许bias先行后再补W。

TILE_COMMIT：拒绝缺数或tile身份错误。数据完整而仍有写流水未退休，等待写完成再提交；它是内部屏障，不是错误。

V1_full：BEGIN→全部X→依次装/提交所有tile→START。全量缓存中的已提交tile不被覆盖。

V2_tiled：BEGIN→全部X→tile0装/提交→START→后续tile按空槽情况装/提交。**单W槽时不能把tile1 OPEN放在START前**，否则生产者等待空槽、计算尚未启动会形成软件使用次序死锁。两种模式使用同一事件编码，但各自的START就绪条件由编译配置决定。

## 3. 读返回信用与向量配对

同步RAM的读请求一旦发出，返回不能因后面ready变低而消失。发射前预留返回容量：

`outstanding_reads + buffered_returns <= return_capacity`

容量以完整向量项计数：每个X返回包含PM个输入、k和row标签；每个W返回包含4个权重、k/g/tile标签。不是只看输出FIFO当前是不是满。

X当前向量保持到其四个列组g=0..3都已经成功取用。W返回必须与匹配的X、k/g以及累加上下文配对。出现停顿时，k、g和valid不能按时间自动前进。

乘积已进入流水但尚未累加时，结果空间也必须有保证。简化版本在每个结果块开始前预留整个Y块及一份快照；不允许半个结果块算完后才发现没地方放。

## 4. 结果发布

输出：`out_valid/out_ready`、`task_id`、`y_index`、signed32 `data`、`overflow`、`saturated`、`last`。

固定公开顺序：tile→row_group→该组有效row→tile内column。例如M=5、N=32、PM=4：先tile0的行0..3，再行4，再tile1的行0..3、行4。不是全矩阵按行逐列的时间顺序，但y_index始终是原矩阵的m*N+n。

micro和CTX4都先填PM×16结果块，再按上述统一顺序发布。这样调度变更不改变软件可见的索引序列，也方便精确测试。

`last`只属于最后一个实际结果，并在背压下保持。25,344只是生产尺寸的数量；小尺寸按M*N计算。重复索引、错误task_id及最后一条不一致都判失败。

`compute_done`表示所有有效输出数值产生；`core_done`在全部结果通过out_fire接受、快照/后处理/结果缓冲空且无fault时成立。后续`system_done`要等待共享存储写回响应，不能直接连接core_done。

## 5. 所有权和故障

W：EMPTY→FILLING→READY→ACTIVE→EMPTY；同一时刻只允许一个ACTIVE计算tile。最后权重读取完成仍不一定能回收：必须等所有bias后处理用户完成或把bias完整快照到独立私有寄存器；首版采用前者。

Y：EMPTY→FILLING→READY→DRAINING→EMPTY；最后一笔out_fire后回收，而不是out_valid最后一次拉高时回收。

非法事件采用统一的简化处理：在可接受的错误事件退休时锁存 `fault`、`error_code`、`fault_seq`，停止新计算，本任务失败；不生成成功done。已有输出记录是部分结果，不对外承诺整任务有效。

已经拉高且未握手的输出valid和payload，除复位外仍保持；fault不能被用作任意撤回接口valid的借口。核内已发读可以返回后按任务故障状态丢弃。首版只支持复位恢复，不实现软重试、地址回滚和总线abort。

合法事件因没有EMPTY槽或没有返回信用暂时阻塞，与非法事件不同。对于非法地址/类型等，不得永远拉低ready让测试超时后还声称是“正常背压”；保留可报告首个错误的容量。

复位同步有效低，清valid、所有权、在途标签、done和fault；不整体清RAM。未来外部异步复位/跨域由封装处理，不在核心中用组合门控生成时钟。

## 6. 可执行规格模型的覆盖限制

`WeightSlots`检查部分顺序、计数、commit屏障、bias生存期、所有权和复位。
`ReadCredits`检查必然返回的读不超容量。
`StableChannel`检查被阻塞payload稳定。

它们不包含完整命令FIFO、真实RAM波形、RTL错误响应时序或SoC行为；后续TB必须实现相应监视器并观察DUT真实事件。软件规格通过仅说明这些模型和用例内部一致。

## RevD补充（优先于历史描述）

V2只预载tile0后START，再装未来tile。不得让等待空槽的未来OPEN排在启动之前，引起单有序流队首死锁。V1全缓存可在启动前装齐全W。源汇必须并发；source背压期间不能停止result接收。

XP2的X线性输入索引仍为m*64+k，只改变内部bank=m%2；两个返回向量槽分别带k/row mask/received mask，返回credit不可因为下游ready撤销而失效。长K的未截断部分和接口只是后续规划，不属于本轮公共engine参数。
