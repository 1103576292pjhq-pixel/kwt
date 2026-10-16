# 共享 FP32 运算单元

`rtl/encoder_fp32.sv` 是编码器内部重复使用的基础运算接口。Softmax、GELU、LayerNorm 的控制器调用它；它自身不执行完整网络层。CPU 不参与这里的算术。

## 接口和数值语义

| req_op | 运算 | 输出位解释 |
|---|---|---|
| 0 | ADD(a+b) | binary32 |
| 1 | SUB(a-b) | binary32 |
| 2 | MUL(a*b) | binary32 |
| 3 | FMA(a*b+c)，单次舍入 | binary32 |
| 4 | DIV(a/b) | binary32 |
| 5 | SQRT(a) | binary32 |
| 6 | F32_TO_I32(a) | 有符号 int32 位模式 |
| 7 | I32_TO_F32(a) | binary32 |
| 8–15 | 无效操作 | 7fc00000，rsp_error=1，flags=0 |

所有运算采用最近偶数舍入、HardFloat tininess-after-rounding 控制配置、RISC-V canonical NaN。NaN 输出统一为 `7fc00000`，不传播 payload。符号零、次正规数和 IEEE 异常不会被清零捷径替代。

`rsp_flags[4:0]` 依次为 invalid、divide-by-zero、overflow、underflow、inexact。普通 IEEE 异常不会拉高 `rsp_error`。浮点转整数的 HardFloat 原标志为 `{invalidExc, integerOverflow, inexact}`；前两者均映射到 `rsp_flags.invalid`，整数越界不映射到浮点 overflow。NaN/+越界返回 INT_MAX，负越界返回 INT_MIN。

空闲时 `req_ready=1`；`req_valid && req_ready` 接受一个请求。请求接受后 `busy=1`、`req_ready=0`。响应数据、旗标、错误状态在背压期间保持不变，直到 `rsp_valid && rsp_ready`；消费后进入空闲，下一时钟沿可接受下一请求。无响应消费同周期旁路。ADD/SUB/MUL/FMA/转换在接受沿锁存结果；DIV/SQRT 使用多周期除法器并锁存其单周期完成脉冲。

`rst_n` 对封装状态为低有效同步复位，HardFloat 子模块直接接同一 nReset。复位中断在途请求，禁止旧响应泄漏。存储/时序约束仍需系统级设计确认。

## 官方算术源与兼容处理

使用 [Berkeley HardFloat Release 1](https://www.jhauser.us/arithmetic/HardFloat-1/doc/HardFloat-Verilog.html) 的官方 Verilog 算术，并选择 source/RISCV 专用配置，expWidth=8、sigWidth=24。原 BSD 版权和许可完整保留，`vendor/HardFloat-1-upstream` 不修改。

Release 1 的 divSqrtRecFN_small.v 在已有 ANSI `output sqrtOpOut` 后重复声明 `wire sqrtOpOut`，Icarus 拒绝编译。`hardfloat_sources.prepare(build_dir)` 生成构建副本，只删除该重复声明；无逻辑、端口、宽度变更。旁边的 compatibility.json 记录原始 SHA、生成 SHA 和变换说明。其余所需文件直接读取官方原件。整合时复用该 helper，不能直接把重复声明源混入 Icarus。

该实现同时包含普通 ADD/MUL 和 FMA 数据通路，共享于编码器各阶段，但不声称所有操作已合并为一个乘法器。快速运算是组合数据通路，尚无工艺库映射和 150 MHz 时序证明。

## 验证入口

在 WSL Ubuntu-24.04、项目根目录运行：

```bash
bash scripts/run_fp32.sh --mode red --random-per-op 0
bash scripts/run_fp32.sh --mode all
bash scripts/run_fp32.sh --mode repeat
bash scripts/run_fp32.sh --mode mutations --random-per-op 0
bash scripts/run_fp32.sh --mode synthesis
.venv-dv/bin/python dv/fp32/run_cold.py --mode green
.venv-dv/bin/python dv/fp32/run_cold.py --mode repeat
.venv-dv/bin/python dv/fp32/run_cold.py --mode unknown
.venv-dv/bin/python -m pytest tests/fp32 -q
.venv-dv/bin/python dv/fp32/accept.py
```

all 默认每操作 2048 个固定种子随机有限输入，加 31 个角落值的二元笛卡尔组合、融合消去例和全部无效 opcode，共 21,291 个真实请求。每笔比较输出 32 位和五异常旗标；每笔施加 0–7 拍背压并改变输入，检查单笔在途和锁存。每进程另做四次复位中断。完整向量分别由 Verilator 与 Icarus 实际执行；repeat 重新编译、重新执行并校验源/输入/结果 SHA。

独立参考是单独编译执行的 C 程序，使用 `fmaf`、`sqrtf`、binary32 加减乘除与 fenv；不链接进 RTL 仿真器。主机 glibc 的 `inf*0+qNaN` 可不置 invalid，RISC-V 明确要求置位，因此该角落按 [RISC-V 官方规范](https://docs.riscv.org/reference/isa/unpriv/f-st-ext.html) 显式补旗标。NaN 规范化和饱和转换同样按公开接口约定处理；tests/fp32 的固定真值例独立检查 oracle。

初始 zero-result RED 和七个可编译行为 mutant 分别验证：数值、异常旗标、乘法负零、背压保持、DIV 完成脉冲、FMA 加数、冷启动特殊零转换、未知分类不得被 casex 掩盖。全部编译日志和模拟失败诊断保留，不能将缺文件/编译错误算成行为 RED。

2026-10-15 集成复验发现：原测试在主向量前做了正常 DIV/SQRT 的复位中断，掩盖了首个特殊 DIV 的四态问题。官方顺序除法器只在 normalCase 写入部分指数/有效数/舍入寄存器；真正冷启动首个 DIV(+0,2) 的 recoded 分类 000 已知，但无关低位仍是 X，recFNToFN 比较完整指数使 X 泄漏。当前封装在浮点转换边界仅对**精确已知**的 000/110/111 分类输出带符号零、带符号无穷和 canonical NaN；普通有限值继续使用官方转换，整数结果直接保留，五异常旗标完全不改。

新增 cold TB 每个向量都启动全新模拟器进程，复位后只发一条请求，无任何暖机。34 组包括 ±0/有限数、有限数/±Inf、sqrt±0、0/0、Inf/Inf、NaN/invalid、普通除法/平方根和整数位模式保护。Icarus 与 Verilator 各执行一遍，再独立重复，共 136 个冷启动进程。另以 Icarus 四态强制未知分类，确认未知仍可观察；casex 掩盖 mutant 必须失败。冷启动真实 RED、旧源/旧报告/旧 PASS handoff 保存在 reports/encoder/fp32/history/，不得当作新源已验收。

Yosys 检查只覆盖一般结构展开、进程转化、优化、无驱动/冲突检查和未映射统计。原库默认占位参数在读取时有范围告警，日志保留；实际 8/24/32 实例通过 check。这里没有 IEEE 全空间形式证明、官方 TestFloat 全量认证、工艺 PPA 或完整编码器分类验收。
