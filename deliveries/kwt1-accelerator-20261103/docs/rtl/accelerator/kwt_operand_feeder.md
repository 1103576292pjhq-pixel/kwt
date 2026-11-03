# kwt_operand_feeder供数控制：首版阅读说明

首版日期：2026-10-29。2026-10-31验证更新：独立TB完成53块/13568组、长暂停、异常返回与复位取消；并随实际核完成三任务内部联合测试。证据见[控制模块验证记录](../../../verification/controls-20261031T211136-aba7c3/README.md)。生产RTL未修改；联合存储使用测试合同模型，官方宏、ICB及平台未验证。下文保留首版设计说明。

源码：[kwt_operand_feeder.v](../../../rtl/control/kwt_operand_feeder.v)。新增公共常量：[kwt_control_config.vh](../../../rtl/include/kwt_control_config.vh)。未修改点积核、存储RTL及旧外围草稿，未接入旧整机文件列表。

## 本次实现选择

本模块仅处理一个4×16块。启动输入为行组号0..24和W槽号；行组号不是row0，row0=行组号×4。尾行组24自动使用0111，其他使用1111。上层启动计算核时必须传递相同的行mask，并保证槽已装载且受到保护。

每块发256组请求，顺序由issued的低2位g、其上6位k决定。X地址={行组,k}，W地址={g,k}。g0读X与W，g1..g3只读W并复用x_hold。X无效行不发请求且送核数据补零。W仅使能选定槽的四个bank。

采用两项完整X/W队列，而不是只寄存W并始终引用当前x_hold：后续k的X更新时，队列里旧组仍必须保留自己的X。每项128位，共256位数据寄存器，另有64位x_hold及计数/身份状态。无输出背压时可连续每拍供一组，启动含读返回和入队延迟；尚未仿真确认吞吐。

## 信号分组

| 信号 | 位宽 | 用法 |
|---|---|---|
| start_valid/start_ready | 各1 | 握手启动；受阻时保持启动参数 |
| start_row_group/start_w_slot | 5/1 | 行组0..24、W槽0或1 |
| x_rd_en/x_addr | 4/44 | 接wrapper的X逻辑读请求 |
| x_rd_data/x_rd_valid/x_access_error | 64/4/4 | 接wrapper的X返回 |
| w_rd_en/w_addr | 8/64 | 接wrapper的两槽逻辑读请求 |
| w_rd_data/w_rd_valid/w_access_error | 128/8/8 | 接wrapper的W返回，只检查本次活动槽 |
| out_valid/out_ready/out_x/out_w | 1/1/64/64 | 对应计算核in_valid/in_ready/in_x/in_w |
| busy/feed_done/fault | 各1 | 供数忙、输入交付完成单拍、异常锁存 |

bias不经过供数器：由上层保持活动槽号，核bias_addr连接存储的组合bias读地址。不能在feed_done后立即覆盖W/bias槽，因为核随后仍需量化并读取bias。

## 代码阅读顺序与时序

1. 块身份寄存器锁存行组、W槽和mask；issued记录已发请求，delivered记录已交付组数，均9位以表示256。
2. pending标记上一沿发出的读；pending_x记录它是否为g0。固定L1返回不能随意等待更晚的valid，否则身份会错位。
3. 两项队列由1位读写指针及2位count管理。reserved=count+pending把在途请求也算进容量。本沿若pop，可预留释放的空间再发一次请求。
4. 组合块生成地址、读使能及尾行补零数据。
5. 时序块更新计数、捕获返回、读写队列；数据阵列不需要复位，因为count/valid决定能否使用。

例如E0启动握手，E1接受k0/g0读请求，E2捕获g0返回并可接受g1请求，E3核最早消费g0，同时捕获g1。g1的返回使用E2已保存的x_hold。同进同出时count不变。核暂停时输出队头保持，同时按剩余容量停止发新读，不撤销已接受请求。

非法行组启动，或期待的L1返回缺valid/报访问错误时，fault锁存并停止供数，不产生成功完成。恢复要求供数器、wrapper和计算核共同同步复位；不支持只重启其中一个模块。故障停止属于异常取消，不属于正常valid/ready流量。

feed_done仅在第256组out_valid&&out_ready之后产生。它不表示核量化结束、结果发布、CPU读完或整项任务完成。上层仍须等待核start_ready并协调新块，不能仅凭供数器start_ready重启整条计算路径。

## 当前检查与后续验证

首版仅编译记录保留在[历史编译记录](../../../verification/operand-feeder-20261029-review/README.md)。当前功能证据见本文开头链接。

独立TB已覆盖256组顺序、两槽、25行组及尾行屏蔽、X复用、随机暂停、队列容量、末组暂停、连续块、复位取消及6类故障；联合TB进一步核对三任务实际结果。正式宏合同、生产顶层和ICB仍需补验。
