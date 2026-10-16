# FP32 首笔特殊除法冷启动复验

## 缺陷与影响

实际集成的首个 GELU(+0) 在最终 DIV(+0,2) 返回未知位。独立最小测试在真正全新 Icarus 进程中复现：编译成功，复位后仅一条 DIV 请求，recoded class=000，部分指数、有效数和舍入寄存器为 X，输出 Xxxxxxxx，flags=00。Verilator 的二态执行返回零，因此单独使用二态模拟不能暴露此问题。

旧主向量测试之前做了正常 DIV/SQRT 的复位中断。这些操作写过官方除法器 normalCase 字段；后续复位只复位控制状态，没有恢复寄存器到最初未知状态，因而旧回归漏掉此角落。旧 PASS 具有测试覆盖局限，已经归档，没有改写成新源结论。

## 修复边界

生产源仅修改 rtl/encoder_fp32.sv。保留官方 HardFloat 原件与五异常旗标；在 recoded→IEEE 浮点边界精确识别 000 零、110 无穷、111 NaN。零/无穷保留 recoded 符号；NaN 按既有 RISC-V 契约规范化。其他分类使用官方原转换。普通 case 不把 X/Z 当通配符，未知分类继续可见。F32_TO_I32 的整数输出不经过该函数。

修复是在 root 保存并确认依赖旧源的长仿真全部暂停后开始，确认记录为 work/fp32_pause_confirmation.json。没有暖机、没有给 HardFloat 添加虚拟运算、没有修改 vendor、没有改非线性或编码器以绕过此错误。

## 验证证据入口

| 证据 | 验收内容 |
|---|---|
| history/20261015T122103Z-before-cold-special-fix/initial-cold-red/ | 修改前可编译真实冷启动 RED，保留当时命令/源哈希/失败日志 |
| cold-red/status.json | 用冻结旧 RTL 与最终冷启动 TB 再现 Icarus X 失败，Verilator 对照 |
| cold-green/status.json | 34 组定向 × 两模拟器，68 个全新进程，无暖机 |
| cold-repeat/status.json | 再次 68 个全新进程，源/输入/输出与首轮一致 |
| cold-unknown/status.json | Icarus 四态未知分类注入仍传播 X |
| all/status.json、repeat/status.json | 21,291 事务 × 双模拟器和独立重复，逐位数据/五旗标；输出与旧同输入回归保持一致 |
| mutations/status.json | 五个既有行为 mutant + 冷零规范化移除 + casex 掩盖，共七个编译成功后被杀死 |
| synthesis/status.json | 当前 RTL 的 Yosys proc/opt/check -assert/stat，一般结构检查 |
| pytest.log | 23 个独立主机参考固定真值与官方不可变源兼容处理检查 |
| ../../../work/fp32_handoff.json | 最终可消费放行记录；仅此文件最终 PASS 后才恢复集成 |

每条冷启动定向均由独立 C 参考提供输出及五旗标，包含正负零/正负有限数、有限数/正负无穷、平方根正负零、零除零、无穷除无穷、安静与信号 NaN、非法平方根、正常 DIV/SQRT、整数负值/边界输出。每条响应再施加七拍背压。完整主回归仍覆盖 0–7 拍背压、动态输入干扰及四次在途/响应复位。

## 局限

本轮修复确认了特殊值边界和四态传播，不构成全部 binary32 输入空间的形式证明或 TestFloat 全量认证。结构综合未使用正式工艺库，不给出 150 MHz、面积、功耗承诺。完整编码器与 CPU 运行必须按新 FP32 源/交接哈希重新构建并验收，旧集成结果继续留作历史。
