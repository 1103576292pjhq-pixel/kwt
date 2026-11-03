# 真实E203+共享SRAM：case3服务器截图凭据

用户2026-11-03截图确认CLOCK_ORDER_REPAIR_READY、DATA_IDENTITY_PASS、COMPILE_PASS以及PASS E203_REAL_SHARED。修复后实际运行目录为verification/real_shared_case3_02；原失败real_shared_case3_01保留。

case3为验证划分yes/55feffd5_nohash_0.wav对应模型第3层（硬件LAYER2），400块、25344项实际共享写回/回读，bit_mismatches=0，NRMSE打印为0.01737469%。真实CPU总6079053周期、3622111条指令，结束6079036，x3=1；终端已经返回。

本地归档只有用户截图和人工转录凭据，尚未独立下载或读取完整服务器report.json/compile.log/run.log。运行使用仿真专用文件加载mux经ICB预装数据；CPU复位释放后的加速器及共享总线路径沿用原实现。不能称正式生产host接口已实现或正式加载计时通过。周期包含CPU结果初始化及软件黄金比较，不当正式FFN性能。

下一阶段为已有12组代表性任务（含静音）的CPU共享链路连续验证及参数切换；官方600/12、正式平台加载/计时、STA/hold/面积/功耗仍单列。
