# dot_product_block_core：单块计算顶层开发记录

整理：2026-10-29。源码：[dot_product_block_core.v](../../../rtl/compute/dot_product_block_core.v)。本文描述已实现的计算边界；SRAM请求和整矩阵调度属于外围。

## 背景与用户思路

用户提出顶层接收每组四个X/四个W，例化前三个模块并连线，并询问何时开始量化、是否每拍输出一个结果、第二块如何接续。最终采用一套acc和一份量化器：先完成一块全部乘加，再串行量化；下一块需等当前输出全部交付并回到IDLE。

## 分块与编号

| 符号 | 含义 | 推进责任 |
|---|---|---|
| row0 | 整矩阵起始行0、4…96 | 外围保存和推进 |
| tile | 当前16列块0…15 | 外围保存和推进 |
| p/q | 4×4外积中的行/列0…3 | 乘加时16路并行 |
| g/ctx | 当前四列组0…3 | 接收组编号低2位 |
| k | 同一结果的第0…63项贡献 | 输入顺序中每四组递增一次 |

```text
Y全局行号 = row0+p
Y全局列号 = tile*16+g*4+q
acc[g,p,q] += X[row0+p,k] * W[k,tile*16+g*4+q]
```

输入group_count从0到255时，g=group_count%4，k=group_count/4。9位计数在最后一次握手后可保存256；这些推导只用于有效输入阶段。

每个k依次g0、g1、g2、g3，随后k++。每块256组，每个acc只收到其中属于自己ctx的64次贡献。四X由外围在四个g间重复提供。

本次点积TB采用先横向tile0…15、再row0加4的顺序；硬件外围可采用已冻结整机调度次序。不能把TB的外层循环误说成当前计算顶层内部已有的行列计数器。

## 接口与合同

- start_valid/start_ready接受row_mask及is_final_block；活动块内标签保持。
- in_valid/in_ready接收已对齐的操作数返回流，不是SRAM读请求；只随实际握手推进计数。
- bias_addr/bias_data是组合选读16个signed32偏置之一，不能直接接有读延迟的RAM。
- 内部acc地址为{g,p,q}，bias_addr={g,q}，输出out_index={p,g,q}，即p*16+g*4+q。
- 输出Y/flags/index/block_last共同握手，受阻时全部保持。普通mask1111输出64项，尾mask0111输出48项。
- out_block_last是块末项；flags[2]只在整个矩阵最后一项有效，外围仅对最后块设置start_is_final_block。

## 三段式FSM与每个状态

| 状态 | 工作 | 正常离开条件 |
|---|---|---|
| IDLE | 等待开始、保存标签、清计数 | start_fire → CLEAR |
| CLEAR | 同步清64个acc并开启累加 | 一拍后RUN |
| RUN | 接收256组有序操作数 | 最后一组实际握手 → FLUSH |
| FLUSH | 让最后寄存乘积真正累加 | acc_done → QISSUE |
| QISSUE | 选acc/bias、发量化输入；无效行跳过 | 量化输入接受 → QWAIT |
| QWAIT | 等Y被下游接受，随后推进地址 | 普通项→QISSUE，最后项→DONE |
| DONE | 输出一拍block_done | 下一拍IDLE |

三段分别是状态寄存、组合next_state、组合控制assign；计数器/元数据另用时序always，仍用当前state与本拍握手更新。给第三段额外加输出寄存器会改变接口周期，不能仅为写法统一而加。

末组时间例子：A沿接收第256组并寄存乘积、进入FLUSH；B沿最后乘积写入acc、acc_done沿后置1；C沿顶层响应acc_done进入QISSUE。FLUSH不能门控mul_valid，否则末组会被丢弃。

QISSUE→DONE只为全0行mask扫描到地址63时收尾。正式1111的最后有效acc地址63、0111为59，均从QWAIT在最后有效Y被接收后结束，不跳过有效结果。

当前QISSUE/QWAIT交替，正常情况下每项至少经过两个状态周期；量化器本身可同沿收发不等于顶层每拍输出。DONE期间busy仍为1，回IDLE后才接受下一块。

## 讨论与优化记录

| 讨论 | 采用方案/原因 |
|---|---|
| 是否先等64项累加完 | 要等整块256组与末组写回，再开始逐项量化 |
| 第二块能否立即进入乘加 | 单套acc在量化期间仍被读取，当前实现等整块输出交付后再清零 |
| 用户要求三段式FSM | 已拆分状态、next_state、控制输出，计数另行寄存，保留原时序 |
| 第五状态为何可直接DONE | 仅空mask兜底；正式任务最后输出仍须握手 |

## 验证与数据来源

- [首次完整连接验证](../../../verification/block-core-20261028T211900-669e21/README.md)：含TB工作原理、真实数据来源及首次测试生成器共享数组错误的定位记录。
- [三段式完整回归](../../../verification/block-core-20261028T215423-d9c5a6/README.md)及[前后逐拍比较](../../../verification/fsm-three-stage-20261028/README.md)：有限激励185433拍公开端口一致。
- [后续注释版本接收](../../../verification/block-core-20261028T223900-96b70c/README.md)：5223块启动，5220完成、3故意取消，6种错误被检出，33项软件测试通过。

真实数据为本地一条音频保存的12层X/W/bias，逐层编码后由TB拆400块重建99×256。共304128项Y及flags一致，不等于12条音频、完整定点Transformer运行或官方600样本验收。

## 后续接入注意

SRAM在途返回标签、W槽和结果owner由外围管理；块done不是CPU完成。总体资料见[加速器归档规划](../accelerator/README.md)。本文件是学习/设计记录，当前源码是否匹配某次PASS必须核对报告SHA256。
