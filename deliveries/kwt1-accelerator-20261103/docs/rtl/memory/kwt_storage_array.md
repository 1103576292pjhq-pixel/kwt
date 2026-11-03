# kwt_storage_array：物理存储实体

更新：2026-10-29。源码：[kwt_storage_array.v](../../../rtl/memory/kwt_storage_array.v)。当前处于已写RTL、合同模型自检通过、待官方模型验证阶段；[证据与范围](README.md#验证结论与证据)。

## 思路与共识

用户提出先例化8颗1024×16和16颗128×16，再映射到bank并用wrapper转换接口。采用两层组织：本层保留宏原生接口与bias寄存器；wrapper承担逻辑地址、选通和返回valid。本层复用官方rtl_top，不重写厂商存储实现。

用户询问bias和结果块是否属于这一部分：bias与W槽绑定，放在本层；双结果块涉及输出缓存和所有权，不包含在本模块。用户对端口及注释的修改予以保留，当前数据端口名为x_write/x_read、w_write/w_read。

## 接口和位宽

所有字段编号0放在总线最低位。字段切片 `bus[ID*宽度 +: 宽度]` 表示从该位置向高位取一颗宏的字段。

| 信号 | 方向、总位宽 | 含义 |
|---|---|---|
| clk / rst_n | 输入，各1 | 上升沿操作；低有效复位期间禁止访问，不清存储 |
| x_cen / x_gwen | 输入，各8 | 每颗X宏的片选、读写选择 |
| x_wen | 输入128 | 8颗×16位低有效写掩码 |
| x_a | 输入80 | 8颗×10位地址 |
| x_write / x_read | 输入/输出，各128 | 8颗×16位D/Q |
| w_cen / w_gwen | 输入，各16 | 每颗W宏的片选、读写选择 |
| w_wen | 输入256 | 16颗×16位低有效写掩码 |
| w_a | 输入112 | 16颗×7位地址 |
| w_write / w_read | 输入/输出，各256 | 16颗×16位D/Q |
| sram_ema / sram_emaw / sram_ret1n | 输入，3/2/1 | 公共宏配置；正常工作RET1N=1 |
| bias_wr_en / bias_wr_slot | 输入，各1 | bias写使能、写槽号 |
| bias_wr_addr / bias_wr_data | 输入，4/32 | 槽内列号、signed32/Q28数据 |
| bias_rd_slot / bias_rd_addr | 输入，1/4 | 组合读槽号和列号 |
| bias_rd_data | 输出，signed32 | 组合读结果，没有valid |

## 代码分段与硬件含义

1. X的两层generate按bank、part展开8颗官方宏，编号 `ID=bank*2+part`。
2. W的三层generate按slot、bank、part展开16颗，编号 `ID=(slot*4+bank)*2+part`。
3. 每个实例将自身的总线切片接到官方端口。generate属于编译展开，不是用计数器轮流访问宏。
4. `.CEN(rst_n ? cen[ID] : 1'b1)` 在复位低电平期间禁用宏。宏没有清零复位输入，RET1N也不是清零端口。
5. bias的posedge块在 `rst_n && bias_wr_en` 时写一项；组合assign按 `{slot,addr}` 选读。没有复位清零循环。

当CEN=0时，GWEN=0写、GWEN=1读；写时WEN的每个0允许对应位更新。写周期Q保持旧值，不能把它解释为新读返回。待机Q的官方行为仍待完整模型确认。

bias同地址写入沿之前读到旧值，非阻塞赋值更新后组合读看到新值。计算期间保护活动槽由上层负责。上电及复位后没有装载过的位置内容不保证为0。

## 验证与限制

[tb_storage_array.v](../../../tb/memory/tb_storage_array.v)直接驱动物理接口，绕过wrapper，检查宏编号、数据/地址切片、掩码及复位隔离；这样可以与逻辑bank层分开定位问题。当前测试模型不代表官方宏，详见[总览](README.md)。本层不产生rd_valid，不检查逻辑地址范围，也不管理装载进度、槽owner或计算任务。
