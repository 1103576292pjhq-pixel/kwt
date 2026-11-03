# X/W/bias存储模块总结

更新：2026-10-29。依据当前源码、用户提供的SRAM接口摘要及已保存的验证记录整理。

## 当前范围和阅读顺序

1. [存储实体 kwt_storage_array](kwt_storage_array.md)：24颗SRAM的例化、物理端口及bias寄存器。
2. [逻辑bank封装 kwt_storage_wrapper](kwt_storage_wrapper.md)：地址拆分、宏选通、返回数据选择及有效信号。
3. [TB使用说明](../../../tb/memory/README.md)：测试方法、运行方式和官方模型要求。

公共位宽在 [kwt_storage_config.vh](../../../rtl/include/kwt_storage_config.vh)，沿用计算核公共定义。当前模块没有修改已确认的数值方案。

```text
后续供数/装载控制（尚需逐模块讨论）
              │ 逻辑bank请求、bias地址
    kwt_storage_wrapper
              │ 每颗宏的CEN/GWEN/WEN/A/D；返回Q
      kwt_storage_array
              ├─ 8 × RAMSP1024X16_rtl_top：X
              ├─16 × RAMSP128X16_rtl_top ：W
              └─32 × signed32寄存器     ：bias
```

官方rtl_top封装与本工程wrapper职责不同：前者连接厂商宏；后者把两颗宏组织成工程需要的一个逻辑bank，并提供读返回协议。每个bank沿深度拼接，一次读返回仍是16位，不是把两颗Q拼成32位。

## 容量与矩阵位置

| 内容 | 逻辑组织 | 物理实现 | 地址映射 |
|---|---|---|---|
| X | 4个bank，每个1600×16 | 每bank两颗1024×16，共8颗 | bank=row%4；addr=floor(row/4)×64+k |
| W | 2槽，每槽4个bank，每bank256×16 | 每bank两颗128×16，共16颗 | 槽内bank=c%4；addr=floor(c/4)×64+k，c为tile内列0..15 |
| bias | 2槽，每槽16×32 | 32项寄存器，共128B | 寄存器索引={slot,column} |

SRAM物理分配共20KiB，不含bias寄存器及结果块。X为signed16/Q12，W为signed16/Q16，bias为signed32/Q28；存储只保存位模式，不做量化或数值运算。

X的bank0/1/2各保存25行，bank3只有24行。bank3地址1536..1599虽然通过wrapper的通用容量检查，但不属于本任务有效矩阵数据，必须由上层尾行mask禁止读取。X地址1600..2047由wrapper直接拒绝。

W每槽存一个16列tile；两个槽支持活动槽读取、另一槽装载。当前wrapper提供独立通道，但不实现槽所有权和活动槽写保护。

## 已完成与未完成的边界

已编写存储实体、逻辑bank封装、两个TB及运行脚本。bias属于当前存储实体；双结果块不在这两个模块中。

还需要后续控制提供装载完整性、W槽owner、尾行mask、k/g顺序、X复用保持和计算核输入握手。wrapper没有返回FIFO或ready，控制必须确保已接受的读返回有地方接收。当前存储测试没有证明这些供数控制已经完成，也没有证明独立加速器、ICB或平台联调通过。

## 验证结论与证据

当前保存的[自检报告](../../../verification/storage-20261029T184551-78d19d/README.md)状态为 `PASS_STORAGE_TB_CONTRACT_SELFTEST_ONLY`：使用测试专用合同模型，**没有使用官方SRAM模型**。

| 测试 | 实际覆盖与结果 |
|---|---|
| tb_storage_array | 3160周期；遍历24颗宏的物理地址；16位低有效掩码、写时Q保持、待机/复位不误写 |
| tb_storage_wrapper | 9398周期；6400个X逻辑位置、2048个W位置；跨宏返回、槽隔离、越界、冲突、复位取消及bias |
| 故障副本 | 当前地址误选旧返回、W槽别名、非法X读产生valid、bias写错槽，4种均被检出 |
| 软件基线 | 33项通过；报告记录生产RTL运行前后字节一致 |

数据来自TB边界常量与固定种子生成，期望值由独立记分板按合法请求更新，不使用DUT内部数组计算。wrapper的4000周期随机激励补充定向测试；读请求数与返回数之差对应17次复位取消。容量测试主动装载X bank3尾部64项，不代表真实矩阵可使用这些位置。

测试专用模型位于 `tb/memory/support/sram_contract_models.v`，仅显式启用 `--contract-models` 时使用。其读延时0.2ns和待机Q保持是测试假设，不能作为官方宏结论。默认周期20ns只用于功能测试。

官方模型目前仅在服务器。缺模型的[正式入口记录](../../../verification/storage-20261029T184640-b5fd69/README.md)为 `BLOCKED_MISSING_OFFICIAL_MODELS`。后续需要两种SRAM完整Verilog、官方封装及include依赖，运行同一套TB；EMA/EMAW配置、150MHz、STA/PVT、面积功耗另行验证。源码身份、命令和日志以各次报告中的report.json、commands.json及source快照为准。
