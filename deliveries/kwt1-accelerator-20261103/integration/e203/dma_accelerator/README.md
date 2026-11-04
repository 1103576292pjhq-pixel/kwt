# DMA搬运加速器推荐方案

更新日期为2026-11-04。本轮完成硬件搬运控制器、CPU配置寄存器、共享SRAM仲裁、内部直连接口及配套C驱动，并进行了四种配置的本地比较。

推荐配置为FORWARD_INPUT=1、FORWARD_RESULT=1、RESULT_PRIORITY=0，已设为顶层默认值。输入读响应能够被装载模块立即接收时直接转交，内部阻塞时存入一个字的暂存寄存器并释放共享总线。结果响应直接交给写总线，在最后写响应完成后才确认释放结果块。输入和输出采用轮询仲裁，CPU和DMA共享SRAM也采用轮询仲裁。

## 测量结果和选择理由

以下为真实case3输入和参数，实际DMA、计算控制、存储封装、仲裁和共享SRAM RTL的本地仿真。SRAM采用独立合同模型，CPU由总线发起器模拟配置和初始化。150MHz数值由周期归一化计算，实际E203指令执行、赛方宏及STA尚待平台验证。

| 本地配置 | 输入至最后写回周期 | DMA启动至最后写回周期 | 150MHz折算任务率 |
|---|---:|---:|---:|
| 基础版，读写均先暂存 | 379681 | 186280 | 395.07 task/s |
| 输入直送，阻塞时暂存 | 372305 | 178904 | 402.90 task/s |
| 输入和结果直送，轮询仲裁 | **372257** | **178856** | **402.95 task/s** |
| 输入和结果直送，结果优先 | 372257 | 178856 | 402.95 task/s |

推荐版完整窗口为91902输入/参数装载周期、101499初始化和配置周期、178856 DMA工作周期，合计372257周期，按150MHz折算2.481713ms。黄金预装在窗口之前，最后结果的写响应退休后结束计时，随后继续完整回读校验。初始化仍实际写入25344个poison值和guard，配置阶段包括测试专用的非法配置检查。

计算核在DMA工作窗口内busy共155280周期。无CPU共享访问竞争时，等待权重tile和等待结果空间均为0，操作数等待400周期。这表明本轮搬运已能及时服务计算核。结果优先没有额外周期收益，因此选用公平的轮询仲裁，避免增加使用约束。若继续大幅提高性能，需针对计算调度或数据表示建立新的测量和设计，而当前搬运参数继续调整收益已很小。

使用实际配套C函数、native程序通过总线模型配置同一RTL，完整窗口测得372176周期、25344项共享回读逐位一致、NRMSE0.017374693962688842%。它与固定TB的81周期差异来自配置/检查流程，两者都保留实际输入装载与poison初始化。上述表格统一采用固定TB口径。此前服务器ICB版2486736周期、60.32 task/s仍是实际E203平台成绩，新DMA的完整平台成绩等待同口径实测。

## 工作流程

CPU将输入、参数准备到共享SRAM后，写入六项配置并启动。控制器装入全部X，然后装第0个tile的W和bias、提交并启动计算。后续tile装载与结果写回并行推进。结果模块发布一块后，DMA核对task、sequence、row、tile和count，读取其所有结果并逐项写回共享SRAM，等待最后写响应后发送ACK。400块、25344项写回以及引擎排空后，DMA置done并可产生IRQ。

输入等待空闲W槽期间，结果写回仍可运行。输入暂存缓冲保证内部装载停顿时共享读响应能够退休。实验中曾发现无暂存直连会占住共享总线并阻塞结果写回，已修正，相关失败日志保存在工程verification历史目录。

## 文件和顶层

| 路径 | 内容 |
|---|---|
| rtl/dma/kwt_dma_controller.v | 独立输入、结果状态机，地址生成，计数，ACK，错误和中止排空 |
| rtl/dma/kwt_dma_csr.v | CPU ICB从接口、配置、地址合法性检查和状态 |
| rtl/dma/kwt_icb_arbiter2.v | 两主设备仲裁，一笔在途，从请求等待到响应退休锁定归属 |
| rtl/dma/kwt_dma_engine.v | 将已有装载/结果握手暴露给DMA的计算引擎连接顶层 |
| rtl/dma/kwt_dma_accelerator.v | DMA加速器顶层，含配置从接口和共享访问主接口 |
| rtl/dma/kwt_dma_system.v | 加速器、CPU共享访问仲裁和512KiB共享SRAM的子系统顶层 |
| rtl/compute、rtl/control、rtl/memory | 已有16MAC/CTX4计算、调度和内部存储模块 |
| rtl/shared | 已有512KiB共享SRAM三个模块 |
| rtl/dma.f | 本包完整RTL清单，路径相对本包根目录 |
| firmware | 实际C驱动、启动汇编、链接脚本及预编译RV32镜像 |
| prepare_soc.py | 从现有kwt_shared_soc_top生成独立kwt_dma_soc_top候选文件 |
| tests | 完整任务、故障恢复、共享竞争、仲裁、固件和接线生成测试 |
| tests/fixtures、tests/support | 已绑定哈希的case3数据和自有SRAM合同模型 |
| reports | 随包本地结果和迭代汇总 |

独立加速器综合选择kwt_dma_accelerator。包含共享SRAM的子系统选择kwt_dma_system。完整E203平台需要生成kwt_dma_soc_top后，组合平台E203源码和本包RTL清单，并配置赛方SRAM/工艺库。一次编译中各生产模块只保留一份定义。测试用合同模型放在tests/support，正式综合使用对应宏库。

## CPU寄存器

基址沿用开发地址0x11000000，32位整字访问，完整写掩码1111。

| 偏移 | 内容 |
|---|---|
| 0x00 | ID，固定0x4b444d31，标识DMA ABI |
| 0x04 | STATUS，bit0 busy、bit1 done、bit2 failed、bit3 aborted |
| 0x08 | CONTROL，写1启动，写2请求中止 |
| 0x10、0x14、0x18、0x1c | X、W、bias、Y的共享SRAM字节地址 |
| 0x20、0x24 | task_id、layer_id，layer为0至11 |
| 0x28 | 成功写响应退休的结果字数 |
| 0x2c | DMA busy阶段周期，包括最后ACK及内部排空 |
| 0x30、0x34 | 错误码、完成ACK的块数 |

每项X/W仍用32位符号扩展容器传输，bias32，结果为Y16和flags3。X6336字、W16384字、bias256字、Y25344字，W在共享SRAM按64×256行优先排列。计算保持X16/Q12、W16/Q16、bias32/Q28、acc40、原RNE/sat16和flags。

地址必须四字节对齐，整个区域位于0xa0000000至0xa007ffff，Y区域须与所有输入区域分离。启动时快照配置，busy期间配置写入及重复启动返回err。CPU可访问不相交的共享区域，活跃任务的输入/输出区域由该任务独占。驱动用volatile及每次访问后的fence维持顺序。

done在最后结果写响应、最后ACK以及引擎排空后置位。0x2c计数起点为DMA启动，完整赛事窗口需继续使用输入开始装载至最后结果写响应的总线观察计时。中止和总线错误会停止新工作，并排空已接受事务后释放busy，部分结果视为无效。硬复位由CPU/DMA/仲裁/共享控制共同接收，存储内容保留。若总线永久不响应，已接受事务需要系统复位恢复。

## 验证范围

已检查完整400块25344项逐位输出及共享回读，两个任务连续执行，CPU与DMA共享访问竞争，错误地址配置，重复启动，忙时配置保护，中止后重启，读/写响应错误后恢复，以及在途硬复位和共享内容保留。压力测试有8870次竞争读访问，两次完整任务仍正确。错移输出地址的错误副本被黄金检查检出。仲裁独立测试完成双方各100笔请求，含随机请求等待和响应背压。整套引擎及生成SoC连接可按Verilog2001展开。

配套C驱动通过native C与实际RTL总线联合测试，882字节RV32镜像已交叉编译并绑定源码，入口0x80000000、结束PC0x80000086、栈顶0x80001000。实际E203执行该DMA镜像、赛方宏模型、正式数据集验收、完整SoC综合/STA/面积/功耗仍需平台工具证据。本轮工作和包尚未同步GitHub。

## 本地复现

在WSL/Linux中解压后进入包根目录，需要python3、iverilog/vvp，固件联合测试另需gcc。以下命令各用新输出目录，保留已有结果。

```sh
python3 -m unittest discover -s tests -p 'test_*.py'
python3 tests/run_local.py --output out/recommended --variant 2
python3 tests/run_local.py --output out/recovery --variant 2 --repeat 2 --stress
python3 tests/run_local.py --output out/negative --variant 2 --mutation
python3 tests/check_firmware.py out/firmware
```

--variant 0、1、2、3分别选择表中四种配置。生成平台顶层时执行`python3 prepare_soc.py --source 原kwt_shared_soc_top.v路径 --output 新目录`。工具验证现有连接并生成候选文件和来源哈希，完整平台编译与仿真仍需使用服务器实际工程。
