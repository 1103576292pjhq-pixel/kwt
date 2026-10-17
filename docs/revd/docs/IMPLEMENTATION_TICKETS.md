# 可执行的开发任务

## D0｜冻结与核对

在新worktree中记录baseline、dirty diff、环境和选择的配置。只读运行旧prepare/verify。使用本包compare_v0时必须提供本地原始numeric/fixedpoint.py并核Git blob；缺NumPy或源不匹配就报告未执行，不放宽哈希。

输出：requirements.md、numerical_contract.md、interface_contract.md、memory_map.md、run_manifest。所有未来stage明确NOT_RUN。

## D1｜最小阵列

待开发：rtl/revd/mac_lane.sv、micro_tile.sv、quant_epilogue.sv；dv/revd/test_micro。

要求：先4×4，再2×4可参数化；带first/last标签，48位acc、49位bias加法，输出稳定。先无后处理重叠，完整后加一份有owner的快照。

通过：正负端点、负向RNE半值、shift0..47、只有末项非零、bias溢出与输出饱和区别、输入停顿、输出堵塞和中途reset。测试失败时不运行全矩阵。

## D2｜全缓存V1

待开发：banked_x4.sv、banked_w_full.sv、ffn_scheduler.sv、core_stream_frontend.sv。输出固定tile→row_group→row→column顺序且带y_index。

通过：公开流装载，不直写内部RAM；一次完整任务必须有25344个唯一结果与1622016次有效MAC。小矩阵→一个全尺寸→已有36例→独立进程复跑。旧36例不是新增600样本验收。

## D3｜CTX4

待开发：context_tile.sv、x_vector_pair.sv。四个acc上下文，读取一次X服务四组列；与micro相同缓存和后处理队列比较。

通过：g标签正确随流水，上一输出未消费时不覆盖快照；统计真实X/W读使能。读取数量变少不能直接报告能耗。

## D4｜单权重块

待开发：banked_w_tile.sv、tile_manager.sv。N_TILE16，先W1/Y1。bias和W同块生命周期。公共接口不暴露物理槽号。

通过：按全部99行复用一个W块，每W/b每任务仅装一次；TILE_COMMIT等待物理写完成。V2仅tile0预载，START先于可能等待计算释放槽位的未来OPEN。

## D5｜分别加W2和Y2

待开发：pingpong_w.sv、result_tile_buffer.sv、read_credit.sv、stream_fifo.sv。每个改变独立提交和对照。

通过：当前权重不可写、末bias引用未结束不可释放、结果最后一笔没握手不可覆盖。源与汇并发进程、有限随机停顿、1/2拍RAM延迟和reset；已发行读必须有返回槽。

## D6｜XP2可选

待开发：banked_x2.sv、x_prefetch.sv。两个16位Xbank，四行分两拍读；两组向量寄存器，带k和lane-valid。保留X4编译开关。

通过：同样X/W/b及全部Y/flags；尾部三行；延迟1/2拍、输出堵塞、未返回RAM读和复位。较大延迟下气泡真实计数。W仍4bank。XP2没有通过时继续用X4，不阻塞已正确的主线。

## D7｜冻结核心成果

对照原7组加XP2两个延迟配置。表中分列解析槽位、真实core/frontend周期、各bank读写、寄存器/逻辑容量，不得填面积和能耗估计值。保留失败日志；run_id不复用，不以改状态恢复PASS。

## P阶段｜后续必做，不在本轮执行

P0：确认比赛平台总线/复位/地址与公开E203差异。P1：新整数核的ICB/PIO薄适配及真实CPU输出全部写回。P2：正式共享端口允许后才评估DMA。P3：16位真实宏映射及功能等价、指定库SDC/STA/面积。P4：同配置综合前后功能及规定窗口VCD/SAIF、整SoC功耗/能耗和正式性能样本。

不要用NICE替换已验证ICB来“补齐功能点”，赛题允许选择一种接入；没有必要同时做两套。[S01]

## E阶段｜完整编码器的另行扩展

按REUSE_ROADMAP的E0—E5。任务1/2既有32位输出不能作为跨K分段部分和；先新建接口测试。学习上可做，比赛主线不被它无限扩张。
