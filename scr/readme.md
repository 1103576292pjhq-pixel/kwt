accelerator\_top 综合脚本使用说明

这两份脚本由你上传的 flow(4).tcl、dot64.sdc 改写，目标是新版独立 FFN1 的 accelerator\_top，不再适用于旧单核 dot64。对应源码基线为 kwt/feat/standalone-ffn-v07 的 78f63dec27f6cf3d5853ffcbc54a2d1dd98cd9b9。

1\. 文件放置

保留该分支完整的 rtl/ 和 synth/ 目录；将本次的 flow.tcl 放入项目的 scr/，将 accelerator\_top.sdc 放入 sdc/。项目根目录可以继续叫 DOT64，无需改名。

文件/目录	用途

scr/flow.tcl	本次 DC 主流程

sdc/accelerator\_top.sdc	本次完整 block 约束

synth/sources.tcl、synth/rtl.f	新分支提供的标准 RTL 清单，必须保留

rtl/include/kwt\_numeric\_config.vh	公共数值格式头文件，必须保留

rtl/compute/、rtl/memory/、rtl/control/、rtl/output/、rtl/accelerator\_top.sv	实际综合 RTL

hook/	可选扩展；默认不执行

rpt/、work/	自动创建每轮报告、中间文件和输出目录





不要同时加载仓库的 synth/clock.sdc，也不要再加载旧 dot64.sdc。 如果下载后的文件名仍保留上传时名称，按上表重命名后放入工程。

2\. 开跑前必须配置

在 flow.tcl 顶部检查以下两项，或通过对应环境变量覆盖：

set STD\_CELL\_DB "/你的标准单元库路径/standard\_cell.db"

set SRAM\_DB "/你的SRAM库路径/sram.db"

标准单元默认路径沿用你这次上传文件中的 ...tt0p8v25c.db，并未擅自换成之前对话里的另一种文件名。SRAM 路径留空，未配置会在分析 RTL 前终止，不会自动切换到行为 RAM。



SRAM 库必须真正包含 TS1N28HPCPL2SVTB2048X32M4MWBASO，与 wrapper 的引脚/功能一致。target\_library 只有标准单元；link\_library 包含标准单元、SRAM、可选额外库及 DesignWare。不要读入商业 SRAM 的功能仿真 .v 来代替 .db。



你的标准单元路径标注 0.8 V，仓库实验 SRAM Liberty 文件名标注 tt1v25c。请核实工艺选项、供电和 corner：脚本能检查文件、实例和库绑定，不能仅凭文件名判断两个库的电气兼容性。它也不会用一个全局 operating condition 强行覆盖不同库的定义。当前是单套 mapping 库的初步综合，不是 MCMM sign-off。



默认参数为 M=99 N=256 READ\_LATENCY=1 USE\_MACRO=1。Flow 显式把参数传给 elaborate；仅 source sources.tcl 不会应用参数。宏模式在本 Flow 中固定为 1。改变 M/N 或 RTL 后，如综合优化移除了无用 SRAM，需要重新审核预期宏数量，不能简单删掉检查。默认完整任务期望 12 个宏。



全部 12 个 RTL 都按 -format sverilog 分析，因此其中 .v 与 .sv 的扩展名不会改变语言解析模式。公共 include 目录和 SYNTHESIS 宏均显式传递。

3\. 运行方法

推荐首先打开一个全新、非 topographical 的 DC 会话：

\# dc\_shell 内；脚本位置可以是任何绝对路径。

source /home/EDA/Desktop/DOT64/scr/flow.tcl

Flow 根据自身位置计算 project\_dir，不依赖启动时所在目录。运行期间进入专用 work 目录，结束或报错后恢复原目录。不要在保留旧设计的 DC 会话直接重跑；脚本会拒绝复用，避免旧设计/约束污染新结果。



也可以在 bash 批处理，并通过 Tcl catch 明确返回退出码：

export FFN\_PROJECT\_DIR=/home/EDA/Desktop/DOT64

export FFN\_STD\_CELL\_DB=/实际路径/standard\_cell.db

export FFN\_SRAM\_DB=/实际路径/sram.db

mkdir -p "$FFN\_PROJECT\_DIR/rpt"

set -o pipefail

dc\_shell -x 'if {\[catch {source \[file join $env(FFN\_PROJECT\_DIR) scr flow.tcl]} msg]} {puts stderr $msg; exit 1}; exit 0' \\

&#x20; 2>\&1 | tee "$FFN\_PROJECT\_DIR/rpt/dc\_launch.log"

FFN\_PROJECT\_DIR 在这里仅用于找到启动脚本；Flow 内部仍由脚本路径推导工程根目录。正式每轮日志位于独立的报告目录，dc\_launch.log 只是本次启动日志，会覆盖同名文件。批处理退出 0 表示流程执行完成，不代表 WNS/TNS/DRV 达标。交互 source 不会自动退出 DC。



无 Ultra 许可时显式设置 FFN\_USE\_COMPILE\_ULTRA=0，使用普通 compile。不会在 Ultra 失败后自动改用另一种编译方式。

4\. SDC 的预算和边界

默认 150 MHz；setup/hold uncertainty 为 0.20/0.05 ns；数据与同步控制输入 max/min delay 为 1.00/0.10 ns；输出 max/min delay 为 1.00/-0.10 ns；输入和理想时钟 slew 为 0.10 ns；输出负载为 0.02 pF。



这些沿用原文件的初跑预算，尚未与 SoC 接口确认。SYNTH\_BUDGET\_CONFIRMED=1 只是消除“预算未确认”的提示，不改变时序含义。



先核对 00\_units.rpt 与 SDC 的 SYNTH\_TIME\_UNIT\_NS、SYNTH\_CAP\_UNIT\_PF。例如工具单位是 ps/fF，二者都应为 0.001。脚本没有假装从未知 .db 自动推断单位。SDC 允许在 source 前设置同名预算变量。



所有非时钟输入（包括 out\_ready）都有 min/max delay 和输入 slew；所有输出都有 min/max delay 和外部负载。rst\_n、abort\_i 使用单独的 CONTROL\_DELAY 预算；它们既影响同步寄存器，也参与组合握手门控，所以不作 false path，也不做 case analysis。in\_shift 保留为受约束的输入，非法参数检测逻辑不会被约束成常量。



SRAM 使用同一个 clk，时序依靠宏库的 setup/hold/CLK->Q 弧。不另建 SRAM 时钟、不对内部宏引脚加顶层 I/O delay。READ\_LATENCY 和计算迭代次数不会被转换成 multicycle 约束。



当前保留理想时钟，不做 CTS、时钟传播、物理 hold 修复或虚构的 clock latency。全局 max\_area/max\_fanout/额外 max\_transition 没有随意设值，库本身的 DRV 约束仍有效。

5\. 输出和检查顺序

每轮输出目录：work/outputs/dc/accelerator\_top/<RUN\_ID>/。

文件	用途

accelerator\_top\_mapped.v	门级网表

accelerator\_top.ddc	综合结果与约束数据库

accelerator\_top\_mapped.sdc	DC 导出的实际约束，供后续交接审核

accelerator\_top.svf	本轮 Formality guidance，analyze 前开启，改名/导出后关闭

accelerator\_top\_elaborated.ddc	综合前、已链接并加载约束的调试检查点

inputs/	全部输入 RTL、头文件、约束、Flow 及启用 hook 的快照

run\_inputs.tcl	本轮参考 RTL 快照路径、宏定义、参数、库、网表和 SVF 路径；仅数据清单

debug\_failed.ddc	失败时尽力保存的现场，不能作为正式交付





报告位于 rpt/dc/accelerator\_top/<RUN\_ID>/。建议依次看：

1\. status.rpt、dc\_run.log：是否执行完成，失败在哪个阶段。

2\. 00\_units.rpt、00\_libraries.rpt：单位、真实加载的库和各库条件。

3\. 00\_sram\_instances.rpt、mapped\_sram\_instances.rpt：综合前后是否都是 12 个宏；Flow 另检查实际库绑定。

4\. check\_design.rpt、check\_timing.rpt：连接、时钟和约束完整性；不只看最后有没有写出网表。

5\. constraints.rpt、qor.rpt、timing\_setup.rpt：DRV/setup 违例。

6\. timing\_to\_sram\_max/min.rpt、timing\_from\_sram\_max/min.rpt：宏输入与输出路径。空报告不是通过的证明，需检查模型时序弧和时钟。

7\. timing\_sync\_control\_max/min.rpt、timing\_i2o.rpt：同步复位/abort 和组合接口路径。

8\. timing\_hold\_preCTS.rpt：理想时钟、当前单套库下的 min timing 诊断，留待实际 MCMM/CTS/P\&R 继续处理。

SYNTHESIS\_COMPLETE\_STA\_REVIEW\_REQUIRED 表示网表和报告已生成，时序仍需审核。工具命令失败、check\_design 失败、宏数量/绑定异常、unmapped cell 或非 SRAM latch 会终止，并记录 ERROR、阶段和错误信息。SDC 配置或端口不匹配也会终止。



area.rpt 是库模型统计，不能直接解释为 die/core 面积；当前宏内部容量合计 96 KiB，最终宏尺寸、面积与布置以正式工艺交付为准。逻辑综合的 WLM 选择见 design\_environment.rpt；没有合适 WLM 时不可把 net delay 当作物理预测。需要指定 WLM 时设置真实模型名及内部 library 名，留空时保留库/DC 默认。



无 SAIF 时功耗是默认活动下的估计。提供 SAIF 时必须填写层级 scope，并审核 activity coverage；可选功耗报告缺失会生成 .unavailable.txt，不会抹掉已生成的综合结果。

6\. 可选 hook 与 Formality 交接

默认 ENABLE\_HOOKS=0。明确启用后，只会执行 hook/ffn\_pre\_compile.tcl 和 hook/ffn\_post\_compile.tcl，不会自动执行旧项目中任意 hook。前者在约束加载后、compile 前；后者在 compile 后、改名与最终检查前。启用的 hook 会加入快照，改动会被 SVF 记录。需要额外约束时优先修改 SDC；hook 的内容仍须工程审核。



本次只改综合与约束，不覆盖此前 Formality 主脚本。后续 Formality 应使用这轮 run\_inputs.tcl 对应的新 RTL/参数、门级网表、标准单元及 SRAM 库，并读取同目录 SVF。旧单文件 dot64 Formality 脚本不能不加修改直接验证新顶层；SRAM 黑盒/功能模型边界还需单独配置。SVF 仅是辅助信息，生成 SVF 不等于等价性验证通过。

7\. 兼容性与已验证范围

脚本使用 Synopsys DC 的 analyze/elaborate/compile/write/report 命令，不混用 Formality、Genus 或 Innovus 命令。参数化 elaboration 自动改名的情况也进行了处理。启动时检查必要命令，00\_command\_help.rpt 尽力保存本机帮助；命令选项若被当前 DC 版本拒绝，流程会停在相应阶段，不会静默换成其他语义的命令。



已完成 Tcl 语法检查和 23 项命令桩测试，覆盖两种 compile 选择、READ\_LATENCY=1/2、含空格路径/异地启动、单位换算、缺库/缺端口/重复时钟/非法参数、命令返回失败、宏数目/绑定、unmapped/latch、空 SVF 和报告异常。按真实顶层展开的 235 个端口位检查，122 个非时钟输入及 112 个输出均有 min/max delay。



命令桩测试只验证脚本控制流和约束对象覆盖，不能代替真实的 DC 运行。交付环境没有 dc\_shell、你的工艺 .db 或许可，尚未执行实际综合、库模型验证或 STA。真实运行后首先核对以上报告。



主要依据：

\- 项目综合入口说明（固定源码版本）

\- 项目顶层 RTL

\- Synopsys Design Compiler User Guide，V-2023.12（公开镜像）

\- Synopsys Synthesis Quick Reference（公开镜像）

具体服务器版本的 help/man 优先于公开镜像中的旧版示例。

