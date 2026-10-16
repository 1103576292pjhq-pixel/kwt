# 独立设计审查：问题与修复

审查者：原生独立 reviewer `encoder_independent_review`；首轮及复审均为只读，未实现被审代码。首次结论 REQUEST_CHANGES，后续只允许进入冻结验证，尚非最终验收。

首轮检查了点积、Softmax、PostNorm、GELU次序、共享FPU所有权、同步RAM预取、X/Y银行及全token循环。未发现确定数学顺序或默认几何的数据取数错误，但要求修复以下具体缺口：

1. CPU构建缓存未列共同shell/RAM、FFN1、HardFloat和include。修复为实际编译输入及include的完整指纹，保存并前后检查binary、build key和编译日志。
2. 原先只现场采hex哈希。修复为先核已放行handoff/manifest，调用独立数值worker的verify_bundle逐bin/NPY/hex核对，再捕获所有实际消费的oracle；full trace期望也纳入运行前后绑定。
3. 计算失败只清busy，驱动退化超时。新增独立fault状态和立即可观察状态；NaN/溢出与故障后重装恢复纳入短测。
4. 复位只覆盖空闲。已补计算途中、同步读等待、未消费响应及NL内部范围缩减/DIV等待中断。
5. 新增独立attention-only公共启停/完成/读回；attention结果不能误当完整encoder激活SWAP。

后续独立复审发现当前异常flags被第二个NBA覆盖，已用真实最大有限数×2的RED失败证明，再保留当前overflow/inexact；终止fault独立表达，不伪造IEEE invalid。

独立NL定向测试另外发现真正冷启动首DIV(+0,2)的X传播。reviewer独立重放最小vvp，退出1，并追踪至HardFloat特殊值路径未写的don’t-care字段。原FP32所有者在recoded到IEEE边界修复，未改vendor、未加暖机；新handoff的136冷进程、21291×3和7变异由root及engine分别独立回读验收。

最新冻结前审查原文结论：“可以冻结生产及 CPU 依赖，本轮未发现需要修改这些文件的未关闭 P1/P2。”审查者回读ICB_RUN 579项、fault/reset 717项日志，检查WAIT_DONE、40M watchdog、背压、attention/reload、共享RAM、SoC路由、两策略驱动与输出监视器。该结论仅授权进入冻结后的实际长验证，不代表最终功能已经通过。
