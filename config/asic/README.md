# ASIC 配置导航

这是分类导航目录，实际文件仍在原位置，以保持脚本相对路径和已有清单有效。不要把本目录作为编译或运行工作目录。

[完整配置与服务器证据位置](../../deliveries/kwt1-accelerator-20261103/START_HERE.md)。

- 生产顶层 kwt_dma_soc_top；测试平台 kwt_real_soc_top 不能当作生产综合顶层。
- 当前目标150MHz；ASIC分支不定义FPGA。仿真ARM_UD_MODEL与SYNTHESIS是不同用途的宏，不能互换。
- 仿真清单含TB和模型；纯RTL清单需要搭配include路径、宏、顶层和外部宏模型。
- 最新ROM握手、TCM适配与初始化资料尚未完整同步。此处只是已知配置说明，未伪造可运行的config.json或最新sources.f。
- 外部商业模型不随导航整理引入。

## 已恢复的ASIC原始脚本

[ASIC仿真、综合与功耗脚本](../../deliveries/kwt1-accelerator-20261103/integration/asic_flow/README.md)：22份，来源为此前聊天代码块及本地保存文件，已做语法检查。服务器生成的RTL、TB、清单及Tcl文件仍未完整取回；该目录是原始脚本归档，不是完整服务器镜像。
