# E203 官方资料与本地快照

本项目已取得公开官方 E203 与 HBird SDK，用于可复现的本地初稿。公开版本和组委会定制平台分别验收，取得公开源代码不等于已经取得比赛工程。

| 项目 | 固定版本 | 上游入口 | 本地只读目录 |
|---|---|---|---|
| E203/HBirdv2 | 9f3e34f337f5d0a1236a285871ffa2032491617a | https://github.com/riscv-mcu/e203_hbirdv2 | vendor/e203_hbirdv2-upstream |
| HBird SDK | 0e0e9083569721578c42f07a95b05a26c0760db6，tag 0.1.4 | https://github.com/riscv-mcu/hbird-sdk | vendor/hbird-sdk-upstream |

两个项目许可均为 Apache-2.0，保留其许可文件。`config/e203-source-manifest.json` 记录固定ZIP URL、下载后SHA-256及全部文件/链接；E203共1051个文件或内部链接，SDK共408个。原ZIP位于tools/downloads，未运行Git写操作。

## 官方资料解决的接入问题

- [仿真说明](https://doc.nucleisys.com/hbirdv2/quick_start/simulation.html)：官方支持Icarus 12，入口为vsim/Makefile和vsim/bin/run.makefile；现有本机Icarus版本满足这一基础条件。
- [固定外设译码](https://raw.githubusercontent.com/riscv-mcu/e203_hbirdv2/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_perips.v)：sysper ICB导出0x11000000–0x11ffffff。初稿控制寄存器选0x11000000。
- [固定SoC顶层](https://raw.githubusercontent.com/riscv-mcu/e203_hbirdv2/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/soc/e203_soc_top.v)：原顶层把外部接口接回零响应。项目另建薄外壳实例化官方e203_subsys_top，接出总线，避免外设看似连接却没有真实事务。
- [固定存储译码](https://raw.githubusercontent.com/riscv-mcu/e203_hbirdv2/9f3e34f337f5d0a1236a285871ffa2032491617a/rtl/e203/subsys/e203_subsys_mems.v)：初稿共享SRAM放0xa0000000，避开ITCM 0x80000000和DTCM 0x90000000。
- SDK启动与链接参考为SoC/hbirdv2/Common/Source/GCC/startup_hbirdv2.S及SoC/hbirdv2/Board/ddr200t/Source/GCC/gcc_hbirdv2_ilm.ld。SDK含E203专用NMSIS，不能直接拿新版Nuclei NMSIS替换并声称兼容。

## 本机工具选择

已安装Ubuntu软件源GCC RISC-V 13.2、binutils 2.42、Yosys 0.33，保留现有Icarus12和Verilator lint环境。GCC实际列出了rv32imac/ilp32 multilib。初稿采用独立freestanding固件，完整SDK构建兼容性单独验证，不能从编译器名字或可下载SDK推断已通过。

[芯来官方下载中心](https://www.nucleisys.com/download.php)另提供厂商裸机工具链；当前没有为本初稿下载额外大型IDE、OpenOCD或FPGA工具。

## 尚无公开确认的比赛材料

已查比赛官网和下载入口，未找到可核实的本题定制E203工程、指定SRAM宏及工艺库。没有证据断言它们一定在登录后。指南的正式600样本清单在评测后才公布，当前不能承诺从官网取得冻结清单。

正式地址、宏接口、库角、时序/功耗口径以比赛工程为准。本地行为仿真、开源综合检查和正式PPA是不同证据，报告分别列出。
