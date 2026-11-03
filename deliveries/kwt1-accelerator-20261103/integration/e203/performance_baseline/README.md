# 不含CPU/共享SRAM的加速器ICB性能基线

该包测量当前生产RTL在12个真实验证任务下的ICB装载、计算、结果读出、正确ACK和完成状态。发起者是单请求测试平台，不包含E203指令执行或共享SRAM输入/输出搬运。不是最终比赛性能或芯片频率证明。

计时起点为首笔TASK配置写请求接受沿，终点为全部结果读出并ACK后的完成STATUS响应退休沿，记录end-start；边沿计数为(start,end]。数据文件读取和黄金比较在计时窗外，但实际ICB装载/轮询/等待/结果读取/ACK均计入。每个新任务重新BEGIN、装入全部X和16个W/bias tile，不能用上一次任务的参数有效标志跳过装载。

去除了故意早ACK、故意忙写后错误重试、ABORT和随机ready延迟；COMMAND前轮询ready，遇结果及时服务。正常运行任何错误响应或响应保持周期非零均拒绝通过。所有304128项Y/flags再次逐位检查，且实际响应解码后每任务NRMSE<=3%。

metrics.csv记录互斥的load/status/output/ack/TB gap周期，五项之和严格等于每任务span。core_busy、操作数组、core输出阻塞以及各事件跨度是重叠观察量，不能与前五项相加。核心观察通过仿真层级只读获取，不增加生产RTL端口或寄存器。

仿真时钟6.667ns（1ps精度约150MHz），报告按150MHz目标统一折算毫秒和任务/秒。有效MAC数为99*256*64，峰值16MAC/周期；末尾行mask的padding不计有效MAC。所有利用率均注明分母是总窗口或core忙碌周期。吞吐量用任务数/总时间，不平均各任务吞吐率。

## 运行

包内包含15个RTL、头文件、新性能TB、与已通过真实12层测试相同的冻结向量，以及纯标准库Python脚本。不包含赛方库，也不要求NumPy。进入本目录：

```sh
python3 run_official.py
```

脚本只读引用/storage1/admin_public_dir/SRAM_Lib_2025/下的RAMSP1024X16和RAMSP128X16四个Verilog文件，使用ARM_UD_MODEL功能模式、EMA2/EMAW0。输出到新的official-run-01，已有目录拒绝覆盖。

预期PASS PERF_BASELINE_OFFICIAL、errors=0。保留report.json、metrics.csv、performance.csv、icb-trace.txt及编译/仿真日志。共享RAM和CPU性能、正式加载时间、setup/hold/STA、面积及功耗不在本次测量范围；离线浮点参考TF2.4.0替代2.4.0rc1的来源限制保持不变。
