# 12组代表性任务：同一次E203启动的共享SRAM验证

**当前状态更新：**用户要求先停止此项长仿真，最后服务器截图只确认前三组完成、第4组已加载，未取得最终全12 PASS。本地两个任务不复位连续验证已有50688项通过证据，不扩大为服务器全12通过。下文保留测试设计和复现方法，是否恢复由团队后续安排。

这是已通过case3单任务的后续。只新增测试固件、仿真加载协调和独立输出目录；生产加速器、共享SRAM、E203 RTL与冻结数值均不改，旧case3和失败/修复记录保留。服务器已有fixtures直接复用，无需重传录音或模型数据。

## 验证内容

一次CPU启动，按case1..12顺序执行，分别对应模型层1..12、硬件LAYER0..11。case1是合成静音，case2是unknown样本，其余为yes/no/up/down/left/right/on/off/stop/go。它们是12个独立FFN1任务，不是把前一个任务输出接为下一个层输入，也不是完整Transformer或分类识别。

每任务400块/25344项，共4800块/304128项。每次完整重装X/W/bias，Y先填DEADBEEF，所有实际结果写共享并完整回读黄金，再检查guard。任务间CPU、加速器、共享SRAM都不复位，驱动清本任务诊断、换TASK ID和LAYER，允许上一任务已完成的合法就绪态，再BEGIN下一任务。

旧W文件按列保存，工具按行重排到共享；X/W有效16位符号扩展存32位容器。冻结X16/Q12、W16/Q16、bias32/Q28、acc40、RNE16、Y16/Q12及flags不变。身份文件绑定原manifest及全部60个文件哈希，任何不一致停止，不自动改黄金或尺度。

## 文件加载如何协调

首组仍由TB在CPU保持reset期间经真实共享ICB写入，保留单case已通过的初始化方法。首次done在切换到可能被门控的CPU总线时钟之前发布，避免时钟/复位互等。

后续CPU完成结果回读后，写测试邮箱NEXT=下一序号。监视器只在该写响应实际退休后发布请求；共享ICB在响应阶段不接受新命令，所以加载器在下一负沿接管模拟mux时没有未完成共享事务。CPU后续的新共享请求被背压，保持稳定。加载器沿原CPU总线时钟，完整写新X/W/bias/gold和元数据，最后发布READY序号；最后响应排空后交回CPU。运行期不换时钟、不复位共享或CPU。监视器逐任务记录实际Y读响应并验证完整写入/回读及reload序号。

这只是仿真专用加载协调；没有新增生产host接口、DMA或正式仲裁器，不宣称正式参数加载/计时环境完成。

## 地址（开发窗口）

| 内容 | 地址 |
|---|---|
| X，6336个32位字 | a0000000 |
| W，row-major，16384字 | a0008000 |
| bias，256字 | a0018000 |
| LAYER/TOTAL/READY测试元数据 | a001f000/a001f004/a001f008 |
| NEXT测试邮箱 | a001f100 |
| guard-before / Y/flags / guard-after | a001fffc / a0020000 / a0038c00 |
| 独立整数黄金，25344字 | a0040000 |

所有区间在512KiB内且互不重叠，a0000000仍待正式地址映射确认。golden不从被测结果生成。每任务的实际共享结果与黄金逐位比较，Python再从实际轨迹计算相对浮点参考的NRMSE，逐任务统计后取最大，不能平均百分比。

## 上传和运行

上传`kwt-real-shared-suite.tar.gz`到FileZilla右侧`/e203-integration/kwt-soc/`，整段复制：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
mkdir real_shared_suite_test_01 && \
tar -xzf kwt-real-shared-suite.tar.gz -C real_shared_suite_test_01 && \
cd real_shared_suite_test_01/kwt-real-shared-suite && \
python3 run_server.py --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

新输出`verification/real_shared_suite_01`，包含原文件备份、新SoC/TB、compile.log、run.log、转换数据、实际shared-y.txt及report.json。已存在目录拒绝覆盖。使用服务器已确认的FPGA/ARM_UD_MODEL和官方宏路径，独立编译，不复用旧simv。包内已编译固件，服务器无需编译器。

先显示DATA_IDENTITY_PASS及COMPILE_PASS，然后每组显示SUITE_LOADER_DONE、SUITE_TASK_DONE，可直接看到sequence=1..12进度。总时间比单组明显更长，脚本墙钟上限4小时，TB约4亿周期看门狗；这不是150MHz频率约束。

成功标记：

```text
PASS E203_REAL_SHARED_SUITE tasks=12 blocks=4800 outputs=304128 bit_mismatches=0 max_NRMSE=...%
```

最后还有12个逐任务误差和CPU统计。runner同时要求唯一TEST_PASS/x3=1、完整12组加载/回读窗口、全部304128项实际轨迹、逐位一致及每项NRMSE<=3%，VCS即使rc0仍拒绝Fatal/FAIL/Time Out。

## 本地证据与剩余范围

本地同C通过FIFO驱动实际加速器/64宏共享RTL，验证至少两个完整任务的不复位接续；后端为独立合同模型，不能称实际E203。另用当前Python冻结整数模型独立重算12组黄金、短测试覆盖12次监视器结果窗口、非法reload/重复读、启动时CPU时钟被门控及运行期加载保持。开发测试依赖本地完整工程，不声称上传包脱离原工程也能运行这些本地单测。

真实E203/官方宏全12结果必须等服务器运行；本包准备或本地两任务通过不能冒充它。代表性12组不是赛方正式性能12组或官方600精度名单。总CPU周期含共享加载等待、Y初始化和软件黄金比较，不作为正式吞吐或与旧单任务直接算硬件加速比。正式host加载/计时、150MHz/hold/STA、面积/功耗及TF2.4.0替代2.4.0rc1的等价性仍需各自证据。
