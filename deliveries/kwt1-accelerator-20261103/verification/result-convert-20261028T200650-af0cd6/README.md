# 用户修改版结果转换模块：组件回归

日期：2026-10-28，Asia/Shanghai。状态：`PASS_QUANTIZER_COMPONENT_REGRESSION`。

本次直接接收磁盘上的用户版本 `rtl/compute/result_convert.v`，接口仍为acc40、bias32、global_last和单槽valid/ready结果输出。测试期间未修改该RTL。`source/`保存本次DUT、TB、脚本、宏及黄金的确切源码快照；SHA256见 `report.json`。

## 实际结果

| 项目 | 结果 |
|---|---|
| 生产模块Verilog-2001编译 | 退出码0 |
| TB编译和vvp自检仿真 | 均退出码0 |
| 原手算定向例 | 16例通过，另含48拍阻塞保持、同拍替换、复位取消检查 |
| 文件数值向量 | 5788组，接收后Y16/flags3逐项一致 |
| 流式检查 | 8390拍 |
| 成功接收 / 输出 / 复位取消 | 5788 / 5773 / 15，账目完全对应 |
| 流式背压保持 | 872拍通过 |
| 旧输出消费与新输入接收同拍 | 4489次通过 |
| 故意错误副本 | 7个全部被检出 |
| 原软件测试 | 33项通过，退出码0 |

工具：Ubuntu WSL、Python 3.10.12、Icarus Verilog/vvp 11.0。

15项没有送达下游，是TB按计划执行同步复位取消的在途结果，不是丢项。每一项输入接收后的数值也已被检查。正常运行阶段不会把取消当成成功输出，最后核对接受项集合恰好分解成输出项与取消项，且无重复、无交集。

## 数据来源与独立黄金

没有使用音频、权重或DEV12，也没有改动冻结合同或黄金模型。

| 来源 | 数量 |
|---|---:|
| 手算字面例 | 16 |
| 正负RNE tie邻点与Y16端点附近，三种bias拆分 | 336 |
| raw40两端及bias边界 | 60 |
| 任意signed40 acc与signed32 bias随机组合 | 4096 |
| Y饱和阈值附近的随机组合 | 1024 |
| 由64项合法signed16乘积求和得到的acc及随机bias | 256 |

Python刺激种子为20261028；完整实际向量保存为 `vectors.txt`，因此不依赖记住随机发生器当前状态。`golden-vectors.jsonl`逐项记录来源、acc、bias、last、raw、rounded、y、flags。

期望先由独立Python算法计算：使用任意精度整数加法、40位范围裁剪，再用Decimal的 `ROUND_HALF_EVEN`处理正负舍入，最后限幅到signed16。每项再与原有 `convert_accumulator` 的全部四个字段独立核对；RTL通过公开输出比较Y和flags，不读取其内部信号来生成期望。

向量中含60项恰好半单位、23项raw40溢出、4335项最终Y16饱和。raw溢出例属于任意acc40组件压力，合法K64整任务不会触发。global_last在组件中取两种值以检查标签同步，不声称已验证矩阵任务只产生一个全局last。

## TB如何检查时序

`tb/compute/tb_result_convert.v`保留原16例定向检查，并增加文件向量流：前64拍连续发送/接收，随后施加长阻塞、随机空拍、随机背压及中途复位。流式阶段发送方一旦拉高valid，在ready为0时保持输入及valid；复位期间允许取消呈现，再恢复未接收的向量。

下降沿驱动，沿前核对寄存输出不应随输入变化，采样真实input/output握手；上升沿后检查单槽记分板中的valid、Y、flags。输出账本 `tb-transactions.txt`按ID记录ACCEPT、OUTPUT和CANCEL，Python再次核对所有输入只接受一次，并且只输出或取消一次。定向测试中的故意扰动受阻输入属于额外输出隔离压力，不能当作实际发送方的合法写法。

## 检错能力

仅在报告目录内生成副本，原RTL保持不动。七种错误分别为：tie一律进位、丢负号、忽略raw溢出、不舍入、背压时覆盖输出、丢global_last、舍入值误作无符号比较。副本均编译成功，再因真实数值或握手不符以退出码1停止；这些是预期失败，见各 `mutant-*-simulate.log`。

## 复现与边界

```bash
cd '/mnt/d/嵌赛芯片设计赛道/kwt1-a40-accelerator'
python3 -B scripts/verify_result_convert.py
```

每次新建独立目录。实际命令、退出码和源文件/向量SHA256见 `report.json` / `commands.json`；主输出见 `tb-simulate.log`，软件回归见 `software-baseline.log`。

本结果针对当前用户版本的组件数值与握手行为。未穷举整个输入域，未验证单块顶层连接、真实SRAM、完整矩阵或STA/PPA；没有综合证据就不能认定该次优化带来了面积或频率收益。旧的 `result-convert-20261028T184028-3b2659`保留为早期16例记录，不替代本次用户版本身份。
