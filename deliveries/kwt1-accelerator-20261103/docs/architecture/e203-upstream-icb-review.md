# E203公开框架的ICB接入资料核对

2026-10-31来源规则更新：只采用下列直接读取的框架事实。此前从交接包继承的接口协议已撤回默认采用，按[当前来源规则](../workflow/design-sources.md)重新讨论。

日期：2026-10-31。用户明确指出交接包不是赛方平台，并提供赛方要求使用的公开仓库。本次直接从GitHub读取源码，不用交接包替代上游事实。只做源码核对，不编写或修改RTL，不声明SoC集成通过。

仓库：[riscv-mcu/e203_hbirdv2](https://github.com/riscv-mcu/e203_hbirdv2)。本次master为`9f3e34f337f5d0a1236a285871ffa2032491617a`，与10月27日记录一致；以下链接固定到该提交。读取文件身份见[清单](e203-upstream-source-manifest-20261031.json)。

## 直接支持ICB开发的源码事实

| 项目 | 核实结果 | 上游出处 |
|---|---|---|
| 默认地址和数据位宽 | config启用ADDR_SIZE32，XLEN32 | [config.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/core/config.v#L23)、[e203_defines.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/core/e203_defines.v#L65) |
| 外设扩展口 | sysper命令valid/ready/read，地址32、写数据32、写掩码4；响应valid/ready/err和读数据32 | [e203_subsys_top.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_top.v#L140) |
| SysPer译码 | 0x1100_0000～0x11FF_FFFF，通过16路分发器O12导出 | [e203_subsys_perips.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_perips.v#L343)、[O12参数](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_perips.v#L389) |
| 外设总线缓冲 | ICB_FIFO_DP=2、CUT_READY=1、SPLT_FIFO_OUTS_NUM=1 | [分发器参数](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_perips.v#L345) |
| 原版顶层SysPer状态 | 地址/写数据等未连接，rsp_valid接cmd_valid、rsp_ready接cmd_ready、err=0、rdata=0，是占位响应 | [e203_soc_top.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/soc/e203_soc_top.v#L135) |
| 握手与背压参考 | 请求接受使用cmd_valid&&cmd_ready，响应退休使用rsp_valid&&rsp_ready，buffer用FIFO保存命令和响应 | [sirv_gnrl_icbs.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/general/sirv_gnrl_icbs.v#L351) |
| 读写方向参考 | SRAM控制器ram_we=~uop_cmd_read，因此read=1读、0写；掩码由总线侧传到SRAM控制端 | [sirv_1cyc_sram_ctrl.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/general/sirv_1cyc_sram_ctrl.v#L89) |
| 外设时钟复位 | 外设模块clk接hfclk；bus_rst_n/per_rst_n来自main_rst_n，main_rst经hfclk复位同步单元生成 | [main复位](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_main.v#L328)、[外设连接](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_main.v#L832) |

CPU是ICB请求发起方，我们的加速器寄存器接口是从设备：cmd_valid/addr/read/wdata/wmask输入，cmd_ready输出；rsp_valid/rdata/err输出，rsp_ready输入。ICB写掩码是字节通路，与内部SRAM16位低有效WEN不是同一种信号。哪些寄存器允许部分写、如何处理非法掩码，需要自行明确，不能由旧接口约定代替设计。

## 对本工程的影响

可以根据上述公开接口继续讨论ICB从设备。E203只规定传输接口，不替加速器规定命令FIFO深度、BEGIN/X/W、PAIR_NEXT、结果ACK或寄存器偏移；这些均需按赛方任务与本工程功能重新分析，不能默认采用旧协议。

0x1100_0000是上游SysPer窗口起点，但上游没有把整个16MiB窗口指定为赛事加速器独占区，也没有规定自定义子窗口。最终基址和寄存器偏移需要依据赛方集成约束及本工程需求确定；不得从旧工程直接继承。

将加速器接到该框架时，要用真实请求/响应连接替换顶层SysPer占位，且提供匹配hfclk及同步复位域。hfextclk是晶振输入，不能仅因它名字有clk就直接当内部总线工作时钟；外部SoC顶层目前没有直接导出所需全部工作时钟复位端口，具体集成位置/端口引出需按实际工程确定。源码中的时钟生成配置也不是150MHz STA证据。

## SysMem与512KiB共享RAM的边界

上游[e203_subsys_mems.v](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_mems.v#L119)把0x8000_0000～0xFFFF_FFFF的一部分访问导向SysMem，TCM区域有更高优先的匹配；默认ITCM在0x8000_0000、DTCM在0x9000_0000。

但[e203_soc_top.v的SysMem](https://github.com/riscv-mcu/e203_hbirdv2/blob/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/soc/e203_soc_top.v#L160)同样是返回零的占位，不能据此认定已接好赛事512KiB共享RAM。此前提出的0xa000_0000基址只能作为待讨论的开发假设，容量/保留区/host装载/赛事宏集成需要另外核对，不再参考交接实现。

## 仍需要用户提供的最小补充

本地ICB开发不必再等通用端口说明。后续若赛方要求使用服务器的`e203_hbirdv2-master_1013_update_sim.zip`，优先取得该包里的config.v、e203_subsys_top/main/perips/mems和e203_soc_top，用于与本提交比较；不推测服务器版必然等同公开master。官方另有地址分配、共享RAM及提交顶层约定时也要对照。

两种内部SRAM完整Verilog模型仍是独立待补资料，不阻塞本轮总线接口讨论，但正式宏回归必须取得。
