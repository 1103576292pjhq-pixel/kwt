# 我们做过什么

更新：2026-11-04。按用户要求，只记清已做、正在做和未完成的事；具体证据放verification。

## 已完成

- 独立FFN1加速器、内部SRAM封装和ICB接口。
- E203与加速器顶层接线；用64颗4096×16宏拼成512KiB共享SRAM并接入SoC。
- CPU驱动、参数加载环境和完整任务测试包；真实case3已跑通输入加载、计算、结果写回及回读检查，400块、25344项逐位一致。
- 服务器无用VCS生成物清理；共享SRAM/整SoC交接推送到原分支，commit a04994b。
- **本次周期测量通过：5106213周期=91902输入/参数装载+5014311后续CPU路径。**按目标150MHz折算34.04142ms/任务、约29.38任务/秒（单任务延时倒数，并非连续吞吐实测）。误差NRMSE0.01737469%。

本次服务器测试包在`kwt-soc/real_shared_timing_test_01/kwt-real-shared-timing/`；结果在`kwt-soc/verification/real_shared_timing_01/`。截图确认最终PASS并返回终端，原始服务器报告/日志尚未取回。本地[截图及结果记录](../../verification/e203-real-shared-timing-server-20261103-01/receipt.json)。当前计时工具及这份新结果尚未更新到GitHub旧交付快照。

这次5106213是“第一笔输入开始装载→最后结果写响应完成”的窗口；6079053是整个CPU测试程序周期，包含后续检查。之前本地native C合同模型的751172周期不属于实际E203成绩。150MHz尚未由STA验证。

## 第一轮驱动优化已通过服务器测试

2026-11-03收到服务器截图，最终PASS且PERFORMANCE IMPROVED。完整窗口从5106213降到2799866周期，减少45.1675%，相同频率下加速1.823735倍。按目标150MHz折算18.665773ms/任务、延时倒数53.573992任务/秒。400块/25344项位差异0，NRMSE0.01737469%。此次收益来自CPU驱动与编译优化。

窗口分为91902加载+2707964后续CPU路径。后者中，加载结束到首笔CPU输入读取258105周期，首笔输入读取到最后结果写回2449859周期。结果区初始化写入跨度253430周期，输入读取跨度2416970周期，结果写回跨度1835507周期，后两者与计算相互重叠。整个程序周期3493817，指令1622229，区别于2799866计时窗口。

服务器包`throughput_driver_test_01/kwt-throughput-driver/`，结果`verification/throughput_driver_01/`。[本地截图及转录](../../verification/e203-throughput-driver-server-20261103-01/receipt.json)。原始报告未取回，150MHz仍待STA。此结果尚未同步GitHub。

## 第二轮ICB连续装载已通过服务器测试

2026-11-04收到截图，最终PASS且PERFORMANCE IMPROVED。完整窗口2799866→2486736周期，减少313130周期（11.1837%），同频率任务率提升12.5920%。按目标150MHz折算16.578240ms/任务、延时倒数60.320034任务/秒，相对最初5106213周期累计加速约2.05338倍。400块、25344项逐位一致，NRMSE0.01737469%。

当前窗口91902加载+2394834后续CPU路径。整个程序3180685周期、1506475条指令。profile记录初始化/设置跨度283462周期、输入首读至结果末写2111372周期，输入读取跨度2078481与结果写回跨度1601305相互重叠。黄金数值与完整检查通过。

实际使用服务器`throughput_icb_test_02/kwt-throughput-icb/rtl`及同包固件，结果在`verification/throughput_icb_02/`。新仿真清单选取候选RTL，原`kwt-soc/accelerator/rtl`仍是原版本，后续综合交接需明确选用哪一版。[本地截图与结果](../../verification/e203-throughput-icb-server-20261104-01/receipt.json)。原始服务器JSON/日志未直接取回。150MHz仍待STA，本轮更新尚未同步GitHub。

## 尚未完成

- DMA完整E203服务器验证包已准备。`upload/kwt-dma-server.tar.gz`含接线、源码清单选择、882字节固件及合并总线计时/结果监视器。生成接线已在本地完整任务通过，25344项逐位一致，并通过3项脚本检查。基线选`verification/throughput_icb_02/report.json`，预定新包目录`dma_server_test_01/kwt-dma-server`、结果`verification/dma_soc_01`。当前进行第一步上传，尚未收到上传确认或实际E203 DMA运行结果。
- DMA版已完成本地添加和四组参数迭代，推荐输入直送带暂存、结果直送、轮询仲裁。固定TB完整窗口372257周期，150MHz归一化402.95 task/s；配套native C控制同一RTL为372176周期。这些是本地合同模型结果，实际E203 DMA版平台成绩待测。旧ICB版服务器60.32 task/s仍是已确认平台成绩。
- DMA验证通过400块25344项逐位一致、两个完整任务、CPU共享竞争8870次、中止/读写错误恢复、在途复位及数据保持、错移输出地址检错和配套C固件完整回读。882字节RV32镜像已生成。代码在`integration/e203/dma_accelerator/`，包为`upload/kwt-dma-accelerator.tar.gz`。[方案和复现说明](../../integration/e203/dma_accelerator/README.md)。本轮CPU/平台顶层迁移工具已提供，实际服务器完整SoC运行及综合待完成。
- VCD/SAIF活动文件导出，交给队友做功耗分析。
- 12组实际E203连续验证：用户中止，最后确认前3组完成、第4组已加载；没有全12最终PASS。
- 全部规定任务的最终性能/精度验收，以及指定工艺综合、STA、面积、功耗和能耗结果。

## 后续怎么记

2026-11-03服务器截图显示本轮命令在`mkdir throughput_icb_test_01`处因目录已存在而停止，后续解压/测试由`&&`短路。截图可见上传包kwt-throughput-icb.tar.gz及旧目录，但未显示本次编译或运行结果。接下来使用新解压目录`throughput_icb_test_02`和新输出`verification/throughput_icb_02`，继续比较`verification/throughput_driver_01/report.json`。

服务器每次新增、修改或测试后，简单补充“做了什么、放在哪里、结果如何、下一步”。失败和中止也记录，不把未完成写成通过。[服务器目录说明](server-folder-map-20261103.md)、[当前主交接](team-handoff-20261103.md)。

## 2026-11-04 DMA服务器首次运行
用户截图确认已上传并运行 dma_server_test_01/kwt-dma-server。DATA_IDENTITY_PASS、COMPILE_PASS；随后 STOP: Missing unique TEST_PASS or failure/timeout。结果目录 verification/dma_soc_01，尚未通过实际E203 DMA验证，不能更新吞吐成绩。下一步查看 run.log 末尾定位失败原因；原始服务器日志尚未取回。


DMA首次失败日志截图：REAL_LOADER_DONE writes=48320；791006000 ps 时 timing_probe 报 TIMING CPU response without command/error。尚不能区分无请求响应与 rsp_err 非零/未知。维护源码 real_loader.v 增加失败现场字段，保留原检查，不改RTL或计时规则；下一步服务器诊断重跑 dma_soc_02。


DMA诊断重跑未开始：package-sha256.json 仍为修改前校验值，入口拒绝 real_loader.v，未生成 dma_soc_02/run.log。原因是诊断步骤漏同步单文件哈希；下一步验证备份仍匹配原清单且只有一行诊断差异，再仅更新 real_loader.v 项，保留全部校验。


DMA诊断校验补充：用户收到 Backup mismatch，仿真仍未启动。本地确认原压缩包 real_loader.v 全部231行使用CRLF；之前 read_text/write_text 备份在Linux会转换为LF，不能用备份字节哈希判断内容。下一步直接验证压缩包原文件哈希，并逐行核对仅诊断行不同，再更新该项。


诊断清单更新再次未执行：压缩包同时含主目录和 tests/support 下的 real_loader.v，后缀搜索匹配两项导致数量断言失败。已本地核对精确成员 kwt-dma-server/real_loader.v 的原始哈希及唯一诊断行差异通过。后续命令改为精确路径，仍保留原校验。


DMA dma_soc_02已编译并运行，截图显示791006000ps停止：pending=1 err=1 cmd_valid=0 cmd_ready=0 addr=00000000 previous_addr=00000000 previous_read=0 rsp_valid=1 rsp_ready=1。确认是已记录写请求的错误响应，尚不知零地址来自CPU/仲裁选择/接线。下一步只读检查服务器生成顶层及编译警告；不关闭错误检查，不认定通过。


服务器compile.log截图显示IPDW：kwt_dma_mem_cmd_addr等在实例处隐式声明，后续显式声明被VCS忽略。已修正dma_server及dma_accelerator的prepare_soc.py，将20个DMA总线声明移到模块端口之后、所有实例之前；增加声明首次出现顺序回归检查，3项本地脚本测试通过。实际VCS修复结果待dma_soc_03运行确认。


用户截图显示 DMA declaration order fixed，但runner因verification/dma_soc_03已存在拒绝启动。随后tail显示该目录已有的零地址错误日志，不代表本次修复后运行结果。保留03目录；下一步仅启动新输出目录dma_soc_04，不重复应用补丁。


DMA dma_soc_04：用户截图确认DATA_IDENTITY_PASS、COMPILE_PASS，实际运行后仍STOP: Missing unique TEST_PASS or failure/timeout。详细失败原因尚未提供；下一步读取04的run.log末尾并计数IPDW声明警告，不假设与前次根因相同。


DMA04详细截图：IPDW=0，声明顺序修复已消除该类警告；但791006000ps仍pending=1 err=1 previous_addr=0。因此先前声明位宽假设不能解释全部故障。下一步在计时监视器命令握手处增加前8笔CPU/DMA/仲裁选择/输出地址跟踪，保留错误检查，输出到dma_soc_05。


DMA05截图：a_valid=1 a_addr=a0020000 b_valid=0 b_addr=00000000 choose=0 locked=0 m_addr=a0020000 observed=00000000；随后pending=1 err=1 previous_addr=0。CPU及仲裁器端口地址正确，而计时监视器地址为零；下一步核对生成顶层的kwt_dma_shared_cmd_addr及TB cpu_addr连接，不改计算RTL。


DMA05编译警告截图确认PCWM-W：tb_real.v中的kwt_dma_shared_cmd_addr、cmd_wdata、cmd_wmask、rsp_rdata均被VCS识别为1bit，分别接到32/32/4/32bit监视端口；不存在共享地址force。源文本显示32bit但编译解析为1bit，需检查声明所在预处理/注释上下文及顶层实际选取。


DMA05根因确认：截图显示20根DMA声明被插到Apache版权块注释内，原因是修复脚本用全文首次右括号分号定位模块头，误匹配License行。已将两个维护版prepare_soc.py改为先定位实际kwt_dma_soc_top模块，再找端口列表结束；新增带License文本的回归，4项测试全部通过。下一步服务器更新生成器并在dma_soc_06重新验证；不得把本地脚本通过当成服务器通过。


用户prepare_soc.py截图确认55–64行声明移动块重复两遍，header_end出现两次，导致上一条要求匹配一次的补丁拒绝执行。服务器06尚未启动。下一步将首个declaration_block至return text之前的两个重复块统一替换为一个模块定位块，并同步单文件清单；备份保留。


## 2026-11-04 DMA实际E203验证通过
服务器verification/dma_soc_06截图确认PASS_E203_DMA_SOC：400块、25344输出、逐位差异0、NRMSE 0.01737469%。完整加载到最后写响应554138周期，旧ICB版2486736周期，提速4.487575倍、周期减少77.7163%。150MHz目标归一化3.694253ms、270.690694 task/s（单任务延迟倒数，非持续吞吐，STA未完成）。CPU程序总周期1247993另含初始化/校验等，不能替代规定计时窗口。声明顺序及版权注释定位错误修复后完整通过；候选源码仍在dma_server_test_01/kwt-dma-server，原生产目录不覆盖。本地证据verification/e203-dma-server-20261104-01/receipt.json及server-pass.png；原始服务器report.json未取回。本轮未同步GitHub。


## 指南吞吐计时口径核对
已读取D:/嵌赛芯片设计赛道/2026赛题指南.pdf，PDF第12页（印刷页11/14）：冻结后组委会统一抽12任务；本科覆盖12层参数的12次线性计算，每次单独满足3%误差门槛。每任务开始前清空任务数据与参数缓存，从输入/参数开始装载到全部结果写回计时；装载、总线等待、E203调度计入，任务间测试平台复位不计入。吞吐=12/各任务有效时间之和，非12个瞬时吞吐的算术平均。现有DMA06的554138周期及270.69task/s仅case3单任务，不能标作正式12任务吞吐；需补按上述规则的12任务测试与每项误差审计。原文未指定必须逐地址清零整个512KB共享SRAM，不应自行增加此要求。


## 三任务清空回归（本地，尚未服务器运行）
新增integration/e203/dma_accelerator/tests/run_three_clear.py。同一RTL仿真实例执行case1/2/3，模型层1/2/3不同输入参数。每次复位后检查DMA状态、装载计数、session有效位及权重/结果槽，逐地址经ICB清零X/W/bias/Y共48320个32位容器并全部回读零值；内部SRAM物理位保留，元数据失效。三个任务各400块、25344输出，合计76032输出逐位一致，各项NRMSE低于3%。每次清空检查386572本地BFM周期单列，每次加载到写回372172本地BFM周期，不是E203实测，不能替换DMA06成绩。正常报告verification/dma-three-clear-20261104-01/report.json；反向测试故意跳过第二任务前复位，成功检出CLEAR_STATE_FAIL，报告verification/dma-three-clear-negative-20261104-01/report.json。生产RTL未改，服务器加载环境尚未同步本轮三任务流程，正式12任务测试仍未完成。


## 2026-11-04 DMA十二任务服务器包准备
新增integration/e203/dma_suite，入口run_suite.py。一次编译、同一固件依次执行12个独立复位仿真；每项在测量前经ICB清零并回读X/W/bias/Y48320位置，检查内部缓存计数/有效位/槽位复位。900字节固件读取层号元数据，每项完整黄金回读并单独审计NRMSE。累计12个加载到最后写响应的窗口计算吞吐；不计任务间复位/清空准备/最终校验。统计加载器与CPU/DMA共享总线访问、字节数、命令等待和响应等待，并逐项导出/压缩SoC VCD。物理宏访问数、功耗、面积、STA不由此直接得到。数据是现有验证集，非组委会冻结抽样。
本地verification/dma-suite-wiring-20261104-01三任务通过，76032输出逐位一致；5项报告审计测试通过。activity-check完整任务通过且VCD含定义与关闭标记，原始1204338397字节；本地均为BFM和合同SRAM模型。服务器尚未运行。
上传包upload/kwt-dma-suite12.tar.gz，98961字节，63文件，SHA256 e400e178ff6b5a8a3fcf65e5835fa0846e0f14ddc710ea4034b142e5fa29e1ea。预定解压dma_suite_test_01，结果verification/dma_suite12_01。包不覆盖原服务器RTL，也未同步GitHub。


待提醒：用户要求本次服务器12任务运行结束后提醒整理测试程序目录。收到完成结果时，先核对PASS/失败及保存指标，再提醒统一整理测试程序、驱动/加载环境说明、报告与活动文件；运行期间不移动依赖文件。当前无自动服务器状态读取，不宣称已设置自动完成监控。


队友交接整理：新增docs/handoff/current-team-status.md，汇总DMA开发、模块、服务器与本地路径、DMA06实测、三任务本地回归和12任务待填指标；根README与旧交接文档增加新版入口，防止队友误用旧rtl。未移动正在运行的服务器文件。用户授权在12任务结果收到并补齐后更新GitHub仓库1103576292pjhq-pixel/kwt的handoff/ffn1-accelerator分支；当前尚未推送。


## DMA12服务器完成
用户截图确认12/12通过，每项554144周期，总6649728，304128输出，最大NRMSE 0.02214978%，150MHz归一化270.687763 task/s、平均3.694293ms；STA待完成。activity=all运行最终通过。原始report.json、总线细项及波形尚未取回，证据保存在verification/e203-dma-suite12-server-20261104-01。本轮已提醒测试结束可以整理目录，但未移动服务器文件。准备同步GitHub原交接分支。
