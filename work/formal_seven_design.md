# 正式七项功能初稿：冻结设计

用户已明确选择1A：按赛题正式七项补齐SoC、注意力和完整编码器。此次是已经批准的工程执行，不再停在范围确认。先前三个子功能只覆盖正式任务1—2的本地功能，不能当成正式前三项。

## 目标、输入输出和边界

输入为官方冻结KWT-1权重和主机离线预处理得到的[99,64]序列。输出为完整十二层编码器[99,64]，主机允许取CLS并分类。CPU仅搬运、命令、层参数调度，所有矩阵、Softmax、两次残差、两次LN、GELU在可综合RTL。不得重新训练、微调、拟合样本参数或用TB/软件预计算替代硬件输出。

保留本科必做int16/48位累加FFN1，新增FP32完整编码器。初稿选择共享标量运算、同步RAM、多周期状态机，原因是尽快形成全部运算的可复核闭环，并可从逐拍行为学习；后续再基于真实瓶颈改并行度。全定点统一更省资源，但十二层LN/Softmax/GELU的尺度验证成本高；一次铺大阵列会先增加调试及存储端口复杂度，本批不选。该选择未宣称满足150MHz或2.25mm²。

官方实际语义以reports/encoder/research/model-semantics.md为准：PostNorm，Q/K/V无偏置，Wo有偏置；LN最后64维、eps=1e-6、独立gamma/beta；官方GELU为erf语义。最终取CLS线性分类，无末尾额外LN。既有FFN1向量X不能当整层输入。

## 固定数值运算顺序

基元契约见encoder_fp32_contract.md，IEEE binary32、最近偶数、逐操作舍入、规范NaN。独立C参考采用float、明确fmaf，禁止fast-math与隐式收缩，所有constants先四舍五入成binary32并输出十六进制清单。

矩阵行主序。每个点积从+0开始，k由0递增，acc=fmaf(a,b,acc)，结束后若有偏置再执行ADD。注意力：Q=XWq、K=XWk、V=XWv；score[i,j]=dot(Qi,Kj)*0.125；max从首个score开始，稳定Softmax为exp(score-max)/sum；context[i,d]=sum_j(prob[i,j]*V[j,d])；attn=context*Wo+bo。

单层：r1=X+attn；n1=LN1(r1)；h=GELU(n1*W1+b1)；f=h*W2+b2；r2=n1+f；Y=LN2(r2)。LN依次左到右ADD求sum、MUL(1/D)求mean；逐项SUB求center；从+0开始FMA(center,center,varsum)，MUL(1/D)、ADD(eps)、SQRT、DIV(1,std)；输出FMA(MUL(center,invstd),gamma,beta)。

exp_neg仅接受有限x<=0；x<=-80输出+0，±0输出1。否则n=RNE(MUL(x,log2(e)))有符号整数；nf=F32(n)；r=FMA(-nf,ln2_hi,x)，再r=FMA(-nf,ln2_lo,r)；degree8 Horner从c8=1/40320开始，依次c7...c0，其中ck=1/k!。每步FMA(p,r,ck)。最终MUL(p,2^n)，2^n直接构造normal FP32指数。常数log2e=1.4426950408889634，ln2_hi=0.693145751953125，ln2_lo=1.428606765330187e-6。不得重新拟合。

GELU采用原始论文公开tanh近似，https://arxiv.org/html/1606.08415v5 第2节；明确不是官方erf逐位实现。对|x|>=10返回正支x或负支-0。其余顺序a=MUL(x,x)，b=MUL(a,x)，c=FMA(0.044715,b,x)，u=MUL(sqrt(2/pi),c)，e=exp_neg(-2*abs(u))（先MUL(abs(u),-2)）；den=ADD(1,e)；正支DIV(x,den)，负支DIV(MUL(x,e),den)。须报告相对精确erf绝对误差、全层NRMSE、分类变化，不把小样本同类代替600样本Top1标准。

## 权重打包与存储

固定M=99,D=64,H=256；小尺寸参数仅用于测试。每层weight顺序Wq[D,D]、Wk、Wv、Wo、bo[D]、LN1gamma[D]、LN1beta[D]、W1[D,H]、b1[H]、W2[H,D]、b2[D]、LN2gamma[D]、LN2beta[D]，全部row-major。总4D²+2DH+H+6D=49792 words。所有导出/RTL/C驱动使用同一打包清单，禁止凭变量数组顺序猜。

内部同步存储：逐层weight一份；X/Y两银行；完整K/V；行级Q、score/prob、context、hidden和LN暂存。先计算全部K/V；再逐query行完成注意力、残差/LN/FFN，再输出Y行。不得省掉其他98个token只算CLS。大RAM不异步读、不整体复位；装载计数或有效状态保障未写内容不可使用。小行向量可用寄存器。

十二层只保留当前层权重；全部FP32权重约2.4MB，无法同时放512KiB共享SRAM，必须逐层提供。本地验证外部host只在CPU请求下一层时更新共享SRAM参数区，记录该边界；它不是DDR控制器，也不能偷偷写内部weight。CPU负责将该层参数搬入加速器。输出激活可内部双缓冲交换为下一层输入。正式复用优化比较须等用户对决策变量、目标、约束的明确确认，功能性双缓冲实现本身可以继续。

## 共享接口和SoC

原FFN1基址0x11000000及寄存器不变。完整编码器新增0x11010000窗口，需先把寄存器及RTL外部请求契约落盘再写驱动。一事务ICB，响应阻塞保持，非法地址/类型/掩码/忙时写返回本事务错误并置sticky error；禁止基于历史error污染后续合法response。

新增encoder core用显式装载、启动、完成、读回及交换请求，不能依赖TB层次写内部RAM。读回有同步延迟握手，未完成读回不得冒充有效结果。每层weight/input加载完整性与layer_index可观察，12次完成后job_done。真实E203必须运行生产驱动，监视器只旁路核对，不能驱动预计算输出。

## 本批可执行验收

1. 已有整数路径：重验当前源36完整案例、独立repeat、协议/数值/DOT/门禁、当前源码绑定；真实E203至少一例完整FFN1，错误参考能失败。
2. FP32：独立运算参考、IEEE角落/随机、背压/复位/无效op、两仿真器小组、可编译错误变异、结构综合检查。
3. 新导出：读取官方checkpoint162张量/607308参数，三输入每层/最终输出与同次原模型一致，来源哈希；旧float冻结文件只读，允许报告跨运行微小数值差异。
4. 注意力/单层：小尺寸手算与随机，再M99D64H256官方真实输入；RTL对自身C参考每word零差、输出有限；逐阶段对官方浮点报告误差。
5. 十二层：至少三个完整输入各跑12层，所有层完整输出逐位对C参考，独立进程repeat；CPU至少一整次12层调度及存储/参数加载计数。目标12类每类一完整任务，若样本未到位，明确实际覆盖不冒称12类。
6. Generic Yosys结构/存储推断、完整可复现入口、源/工具/固件/参数/结果哈希、实际计时范围、SRAM与参数流量、两轮独立审查和统一回归。

正式竞赛外部待验：组委会定制平台/工艺和SRAM库、150MHz时序/面积/功耗/能量、综合后门级仿真、官方600样本及Top1下降<=2个百分点。没有数据/库则该子项保持EXTERNAL_PENDING。任务3/7的本地初稿可交付结构检查与报告模板，不能将正式综合评测称通过。

## 执行与完成门

普通native agents仅负责明确文件，不称Potter。Potter当前内置Git自动提交与禁止Git写冲突，继续使用已验证的桌面Codex CLI可见CMD持久runner，状态为.omx/prototype-run.json，日志为.omx/prototype-run.log；未启动进程前不称后台运行。

work/encoder_status.json为新唯一完成门；七项bool只表示上述本地初稿证据充分，formal_acceptance单独记待验。不得复用旧numeric/dot64/ffn1三flag就结束。至少两轮自审；失败留日志、撤销过期PASS、修复后复验。
