# 第一轮自审：规格逐项核对

审查范围：`work/approved_prototype_v01.md` 与本批代码、测试和证据门禁。审查分工为集成器规格核对、独立只读子代理复核RTL/协议；没有委派新的实现worker。

| 批准项 | 实现与证据 | 判断 |
|---|---|---|
| 数值格式/编码 | numeric/fixedpoint.py；固定sx=2^-8、冻结全W范围推出sw与r、无样本搜索；67项独立测试 | 通过 |
| 整数溢出语义 | Python任意精度标量；NumPy矩阵先证明int64范围；DOT64的16×16/48acc、49位偏置、sat48→RNE→sat32 | 通过 |
| DOT64有效计数和握手 | 8项cocotb、52笔结果，输入停顿、反压、非法移位、复位；小波形自动计64次且还原−8 | 通过 |
| 同步存储 | prototype_sync_ram只在posedge读写，读写互斥，不逐字复位；B_REQ/PRIME显式读延迟 | 通过 |
| 完整矩阵/单MAC | FFN1固定K64，默认M99/N256；W_pack只重排；一个dot64实例，无预计算替代 | 通过 |
| 装载完整性 | 三银行独立顺序计数、拒绝跳号/超长/非int16、START之前loaded检查、busy拒绝写入 | 通过 |
| ROW_READY/ACK | Y最后一项写入同拍后才进入ROW_WAIT；busy和行号保持；匹配行号ACK；最后ACK才DONE | 通过 |
| 复位/连续任务 | 小矩阵计算与行等待中复位后重载；全回归不在案例间复位，覆盖12层及3输入切换 | 通过，36例连续任务全部完成 |
| 全36例/912384输出 | SV真实公开装载与读取；只读DOT握手计数，每例1622016次；Python二次重读输出 | 通过，36个CASE_PASS、全部实际输出、58392576次有效MAC与哈希均由门禁核查 |
| 独立完整尺寸复跑 | 新vvp进程重跑首例，完整25344输出哈希匹配 | 通过，输出数组SHA-256为b6ef91b483286a3826dc25e9a53d0a7946ec388d3f112dcd2fe7a01122fbe599 |
| 误差/尺度与数据边界 | 每案例/每层NRMSE、最大绝对误差、饱和计数在vectors/manifest；3%仅此36案例子集 | 通过，禁止扩大到600样本 |
| 来源只读 | preflight/full/repeat/finalize重新核查124官方文件、冻结float、代码/配置/数组哈希 | 通过 |
| 失败关闭/缺例 | shell先失效旧PASS；固定DOT七项哈希、单元运行ID/源码/配置/XML绑定、输出计数、案例集合及复跑逐项核对 | 38项门禁测试通过，统一入口已重新核对当前绑定 |
| 交付与学习入口 | scripts/run_prototype.sh、docs/prototype、README、真实日志/输出/波形/状态 | 通过 |

自审发现并处理：初次全尺寸启动时Icarus的Unicode plusarg损坏路径，尚未运算即退出1。jobs与所有数据文件改为ASCII相对路径；旧失败保留在`attempts/path-failure/`，不纳入成功案例。

无未解决重大规格问题。完整入口实际退出0，`ffn1/full/status.json`、`ffn1/repeat/status.json`和顶层门禁均通过；顶层状态READY_FOR_REVIEW，等待主控复核。运行事实仍以实际输出、哈希及JSON为准。
