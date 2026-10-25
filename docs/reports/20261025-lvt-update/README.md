# 2026-10-25 Verilog-2005与LVT宏同步

来源：个人工程`worktrees/dot64-core`当前未提交工作树。13份RTL/头文件
与源目录逐文件SHA-256一致；综合清单只包含12份设计源码，排除学习用`rtl/test.v`。
最新导入身份见`../../shared/standalone-v07-import.json`。
`v07-compute-snapshot.json`及20261023报告属于历史快照，不替代本次身份。

## 变化

- 外围设计和外围TB使用`.v`及Verilog-2005语法，移除对应旧`.sv`路径。
- SRAM cell改为`TS1N28HPCPL2LVTB2048X32M4MWBASO`。
- 模型、Liberty和交付说明统一为`tt0p9v25c`。
- `synth/rtl.f`、根README和综合说明同步更新。
- 数值格式、矩阵尺寸、接口和双槽组织保持原约定。

## 本次在团队目录实际复跑

| 检查 | 结果 |
| --- | --- |
| 导入快照 | 65份文件校验通过；RTL/头文件另与最新源目录核对 |
| 设计清单 | 12份设计源码按Icarus `-g2005 -Wall`编译通过；Tcl清单解析通过 |
| 计算核心 | 400个lane乘积、251个转换用例加12拍连续转换、45个块/1904次输出通过 |
| 行为RAM小矩阵 | M5/N32/两层，8480项存储检查、320项Y/flags/index通过 |
| LVT宏小矩阵 | 1拍和2拍返回分别通过8480项存储检查、320项输出检查 |
| LVT宏完整矩阵 | M99/N256/一层、1拍返回，25344项Y/flags/index通过 |
| 结构试综合 | Yosys0.9，61165个通用cell，含5007个DFF和12颗LVT宏；无锁存器 |

本次完整矩阵为固定种子合成整数任务，不称为真实KWT参数或官方任务。
未重复旧版完整12层回归；其304128项结果属于此前版本的历史记录。
宏模型使用UNIT_DELAY，零时刻唤醒警告仍存在。结构试综合没有完成标准单元
映射、150MHz STA、正式面积或功耗评估。

## 队友综合

顶层`accelerator_top`；读取`synth/rtl.f`；M=99、N=256、READ_LATENCY=1、USE_MACRO=1。
Synopsys工具加载本机`TS1N28HPCPL2LVTB2048X32M4MWBASO_tt0p9v25c.db`，
RTL实例名不含工况与扩展名；Yosys脚本使用对应`.lib`。
库及工艺角由综合环境提供，商业库文件不提交。
