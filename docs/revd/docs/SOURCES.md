# 来源与可追溯边界

本文件中的[Sxx]是本包便携来源编号。版本固定到提交，不把网页当前HEAD漂移混入历史结果。用户粘贴评估是待核对意见，不自动作为事实。计算例子与XP2为本轮推导。

## S01｜上传的2026赛题指南

conversation:2026赛题指南 (1).pdf

PDF物理页4—14；本科范围、数值格式、精度评分、冷启动、面积/功耗

## S02｜用户上轮RevC压缩包

conversation:kwt_revc.zip

解压逐文件阅读并通过原MANIFEST检查；本轮计划起点

## S03｜KWT main分支

https://github.com/1103576292pjhq-pixel/kwt/tree/3d9d0fc77457b8869cbf525d826dafb114f2a8e1

本轮通过GitHub连接器读取main，仍为冻结提交

## S04｜model/run_baseline.py

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/model/run_baseline.py

本轮读取1—100行；TensorFlow graph/session、官方层回放

Git blob：`03bdf8f9dc33f02de77602d5c209a8ad45d3ee50`。

## S05｜numeric/fixedpoint.py

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/numeric/fixedpoint.py

本轮读取1—160行；任意精度整数、sat48/RNE/sat32和NumPy界检查

Git blob：`116dfb84c51a6847cb10678c9e5a7230fb796598`。

## S06｜rtl/encoder_fp32.sv

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/rtl/encoder_fp32.sv

本轮全文；ADD/MUL/FMA组合结果锁存，DIV_WAIT多周期路径

Git blob：`02cb72208adcc54099d950ab24d9a3213418e2e1`。

## S07｜numeric/encoder/encoder_ref.c

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/numeric/encoder/encoder_ref.c

本轮全文；显式fmaf、tanh型GELU/exp多项式和逐阶段参考

Git blob：`aa7b9fabcb676f7d757670e83b1c8206a516ff4c`。

## S08｜numeric/encoder/run_reference.py

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/numeric/encoder/run_reference.py

本轮读取1—92行；gcc参数、host舍入模式、参考构建

Git blob：`c747dc0238b4ca4d76e113e7b3b68f6bab1c9561`。

## S09｜rtl/encoder_core.sv

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/rtl/encoder_core.sv

本轮读取1—85行；score/prob行数组、full K/V与x0/x1、FP32/非线性接口

Git blob：`99589db99157b604393dd6a43d0e4de1d71bea7f`。

## S10｜soc/e203_encoder/e203_encoder_soc.sv

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/soc/e203_encoder/e203_encoder_soc.sv

本轮全文；两个ICB从设备窗口和真实E203薄封装；不支持声称新加速器已接NICE

Git blob：`0a4036058f1ef4e0e0195f45948d9d5cdb0589d9`。

## S11｜docs/encoder/reports/08_总体验收报告.md

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/docs/encoder/reports/08_总体验收报告.md

本轮全文；已有同输入双策略CPU实验、覆盖范围、非官方验收

Git blob：`53e97a7e6f7470d99964ea39a0513f888bdd2504`。

## S12｜docs/platform/official-sources.md

https://github.com/1103576292pjhq-pixel/kwt/blob/3d9d0fc77457b8869cbf525d826dafb114f2a8e1/docs/platform/official-sources.md

本轮全文；E203固定版本及sysper/sysmem外壳，公开和比赛平台区别

Git blob：`9806c0a9b5e2b092135969fdf1d1f107a6d54e16`。

## W01｜HardFloat官方Verilog手册

https://www.jhauser.us/arithmetic/HardFloat-1/doc/HardFloat-Verilog.html

第9.7/9.8节：FMA和迭代除法/开方；不可把所有操作说成单拍

## W02｜GCC Optimize Options

https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

-ffp-contract和-f(no-)fast-math；显式fmaf语义不能与编译器自动收缩混为一谈

## W03｜NVDLA硬件架构

https://nvdla.org/hw/v1/hwarch.html

借鉴数据复用、缓存、MAC供数；不导入其完整卷积硬件

## W04｜LaForest Ready/Valid规则

https://fpgacpu.ca/fpga/handshake.html

握手与有限缓冲背压；避免延期应答破坏吞吐

## 执行边界

通过连接器读取源码与报告，未重跑旧CPU长回归。容器直接下载原始GitHub源码遇到DNS不可用；因此`compare_v0.py`本次仍未执行，不伪造下载或原模型对照。仅软件设计模型、额外审查工具和包校核已实际运行。原始源码/权重未重新打包，第三方完整文档和字体文件未分发。
