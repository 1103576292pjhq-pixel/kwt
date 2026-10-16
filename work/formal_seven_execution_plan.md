# 正式七项 Implementation Plan

上游：formal_seven_design.md；用户已批准1A并要求一次完成初稿、反复验收。

1. root先刷新任务映射/状态，完成整数路径signed兼容修正的36+repeat再验收。共同bridge/driver/CPU按冻结接口完成；不得重复启动36长仿真。
2. FP32 worker按encoder_fp32_contract.md实现/定向和随机/独立参考/交叉仿真/变异/结构检查；所有权仅契约指定路径。
3. model/numeric worker负责新鲜官方完整层导出、权重打包、确定运算顺序的独立C参考、非线性误差及分阶段全12层参考，使用design固定公式，禁止搜索；导出和数值与RTL分离，旧float只读。
4. root/persistent实现非线性微程序、同步RAM核心、attention模式、小尺寸行为RED→GREEN，再官方99×64全尺寸attention/encoder；基元只通过冻结req/rsp调用，微程序不可将CPU带入神经算术。
5. 定义encoder ICB和C接口，增加真实E203路由、逐层参数握手和12层内部数据交换；主机仅更新公开共享512KiB参数窗口，CPU运行生产driver搬运和调度。真实CPU trace核对全部输出并记录端到端计数。
6. 统一可复现命令运行三个全12层输入和独立repeat、阶段误差/分类比较/计数，用户确认后才运行正式复用对比实验；没有确认时报告该实验待确认。
7. 固定generic综合与报告，明确正式工艺/PPA/门级/600样本待验。只读审查spec一致性、数据/源/结果绑定和失败信号；解决P1/P2后再次跑受影响门禁，主控独立回读完整证据。
8. 七项本地初稿达到design验收后更新READY_FOR_REVIEW；独立根复核后ACCEPTED_LOCAL_DRAFT。不得等于正式比赛通过。总报告必须有七项逐项表、输入覆盖、数值及协议/CPU/综合证据、命令/路径、外部待验、复现方法与初学者阅读顺序。

持久任务限定单工作区/单主线/单状态，25分钟心跳，至少两轮自审，不启动嵌套runner，不Git操作，不修改vendor/冻结source或baseline。并行agent完成释放文件后才能接管。
