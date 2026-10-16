# FFN1 基本功能 Implementation Plan

> 已获用户批准，按本文件连续执行；使用 test-driven-development、systematic-debugging、verification-before-completion。无需再次让用户选择执行方式，不做Git动作。

**Goal:** 完成 `approved_prototype_v01.md` 的三个基本功能及实际完整尺寸验证。
**Architecture:** 平台无关的单路MAC、同步存储、逐行输出；整数参考与RTL分开实现。
**Tech Stack:** WSL Ubuntu-24.04、Python3.12/NumPy/cocotb、Icarus12、SystemVerilog。

## Task 1 数值规范与参考

文件：`numeric/`或`model/fixedpoint/`独立于原float基准；`config/prototype-numeric.json`；`tests/numeric/`。

- [ ] 先写RNE/饱和/溢出失败测试并运行保存RED，例如：
```python
def test_negative_ties():
    assert rshift_rne(-3, 1) == -2
    assert rshift_rne(-5, 1) == -2
    assert rshift_rne(3, 1) == 2
    assert rshift_rne(5, 1) == 2
```
- [ ] 实现规格中的整数编码、固定尺度范围推导、dot64/matrix参考和可追溯向量生成；标注无训练/样本调参。
- [ ] 将36案例生成到`reports/prototype/vectors`或`data/prototype-vectors`，不覆盖float源，输出来源哈希和数值结果；软件检查GREEN。

## Task 2 DOT64 RTL + cocotb

文件：`rtl/dot64.sv`及必要数值处理模块；`dv/dot64/`；统一runner脚本。

- [ ] 先写手算dot（前三项1,-2,3与2,4,-1，其余0，bias1，应-8）和握手/边界/复位测试，空/错误DUT下保存真实RED。
- [ ] 实现固定singleMAC、64次已接受输入、48位点积与49位偏置检查、RNE+32位饱和、输出等待稳定。
- [ ] 检查signed扩展、最后一项nonblocking求和、负数半值和复位终止；运行Icarus GREEN、Verilator lint及小波形。

## Task 3 完整FFN1控制与同步存储

文件：`rtl/ffn1_top.sv`、`rtl/`存储wrapper/调度模块；`dv/ffn1/`。

- [ ] 写装载完整性、行阻塞、首尾地址、参数切换、中途复位和完整矩阵对照测试；小参数仅用于快速RED。
- [ ] 实现公开load/start/read/ack端口、m/n/k调度和同步存储读延迟，复用已验证DOT64。
- [ ] 跑36个默认完整尺寸案例；公开接口实际装载并读回全部912,384个输出，逐位零差；固定随机种子并记录各阶段周期。
- [ ] 如58M周期回归慢，减少Python逐拍轮询和完整波形，不减少矩阵尺寸、案例和真实运算；ROW_READY可等待若干计算周期后检查。
- [ ] 至少完整复跑1个真实尺寸案例，输出哈希一致；保持float来源124文件校验。

## Task 4 一键入口与交付

文件：`scripts/run_prototype.sh`（推荐）、`reports/prototype/`、`docs/prototype/`、README、`work/STATUS.md`。

- [ ] 入口不依赖调用cwd；每次开始清除旧成功状态，失败非零，验证测试数量/输出数量/哈希/案例覆盖，不允许skip。
- [ ] 先规格审查，再代码质量审查，两轮自审修正并保存证据。若有原生subagents能力可用只读review；不要另起长期worker。
- [ ] 一条命令演示数值模型、DOT64、全矩阵；写清成功信号、结果目录、接口、数据流和学习顺序。
- [ ] 更新 `work/prototype_status.json`；仅当全部验证真实通过时写 `READY_FOR_REVIEW`，字段 `numeric=true,dot64=true,ffn1=true,full_matrix_cases>=36`。这表示待主控最终复核，不冒充比赛正式验收。

## 每轮交接

- 每轮结束更新 `work/STATUS.md`、任务勾选、已跑命令/退出码、失败根因、下一步。
- 若测试仍运行，保留准确PID和日志，不重复启动同一回归；每轮先检查已有进程和状态。
- 不得因轮次将尽降低验收或宣称完成；真实外部阻塞写清并停止相关项，继续可完成项。
