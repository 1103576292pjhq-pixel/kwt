# 真实 E203 双策略：最终独立证据回读

**状态：PASS；本次 CPU 证据范围内未发现开放 P1/P2。** 只读回收在2026-10-15 15:30:53 UTC开始，两条任务均于30分钟观察界限内完成；独立完整核查于15:52:36 UTC通过，脚本退出0。没有启动仿真/runner，没有修改生产源、gate、状态、真实日志或输出。本报告不代表正式比赛平台、十二项整机性能、600样本精度或PPA验收。

## 独立核对结果

两策略均使用真实输入 `eight_750e3e75_nohash_0`，执行全部12层。除已有只读 gate 佐证外，审查脚本自行解析十六进制 word，检查计数和所有输出为有限 FP32，再逐项与 canonical 独立 C 层输出比较。

| 项目 | 内部交换 policy1 | 外部重载 policy2 |
|---|---:|---:|
| 被动 neural 输出逐word比较 | 76032 | 76032 |
| 真实 CPU 共享RAM写回逐word比较 | 最终层6336 | 全12层76032 |
| 位差 / 非有限word | 0 / 0 | 0 / 0 |
| own / compiled / input 哈希回读数量 | 178 / 172 / 30 | 178 / 172 / 30 |
| 当前已绑定 ELF 派生镜像 | 1512B | 1512B |
| 独立核对的参数层数/每层word | 12 / 49792 | 12 / 49792 |

合计独立比较152064个 neural word和82368个 CPU写回word。两份实际 `input.hex` SHA均为 `e9782df2afe3870050d410ed8cee38d6d4c7c67533a36232edba088a2a3186f0`；全部12层 neural输出SHA均为 `ae7f60afa77bd974c7f82c3b3333cc9c746768cea90efc71eb53725c48198fea`。policy2的全部CPU写回具有同一SHA；policy1最终写回SHA为 `fe75d03d9e95952d3ffe80440ec3b355b17d34d2ef49091e4419527c54f9ae40`，逐word等于该完整层链最后6336word。

## 运行身份、来源及消费物

- 两份记录均 `status=PASS`、`exit_code=0`，完成标记在各自实际日志中恰出现一次并与摘要一致。观察到实际仿真PID716和665的 `/proc` 命令分别携带 `+BYTES=1512 +POLICY=1/2`，回收结束两进程均已退出。记录中的PID404/408是Python调用方身份，未混称硬件仿真子进程。
- policy1 run_id为 `d18f738a74a7484ea373579705c2adef`，policy2为 `33b068f04ba448339d21251dec76f2c3`；各自开始/结束时间有效，commands.jsonl在相应时间区间内恰有一次完全相同的实际模拟器命令和cwd。
- 192项生产冻结源在观察期间和完整回读末尾均逐项hash匹配。冻结清单SHA保持 `4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17`，两记录均绑定该清单。
- 每份自身源、编译源、输入的所有哈希均回读；build.json的172项sources等于记录compiled映射。归一化各自生成HardFloat目录名后，编译来源及Verilator/C++选项一致；实际两模拟器binary SHA也相同：`f3757e5e36e51fd8c67140ed2992f6b2074fae48a8699113880a6435ea071bf9`。固件因策略差异而不同，并分别绑定其ELF。
- 实际 staged input逐byte等于canonical input；expected等于按0…11层拼接的canonical y；weights解析到正式reference目录，12层文件逐一核对，且canonical输入、各层期望值和权重均包含在原始input哈希映射内。
- 在系统临时目录真实重新执行objcopy，由已绑定ELF派生bin，核对实际firmware.bin、逐byte hex编码及BYTES。没有假设或补造运行前staging快照；这是验收时消费物回读，原runner的canonical/生产来源前后绑定另经原始记录核验。
- binary、ELF、compile.log、build.json、simulation.log、CPU/neural输出等产物SHA全部匹配。随后独立调用只读 `gate.cpu_record()`，两策略均PASS，各得到18项运行消费物摘要；未调用会修改状态的 `evaluate()`。

## 实测周期与流量

| 指标 | 内部pingpong | 外部reload基准 | reload减pingpong | 相对本行reload |
|---|---:|---:|---:|---:|
| 端到端周期 | 284353480 | 290627429 | 6273949 | 2.158760% |
| CPU侧共享读事务 | 653640 | 723336 | 69696 | — |
| CPU侧共享写事务 | 6394 | 76090 | 69696 | — |
| CPU侧共享事务合计 | 660034 | 799426 | 139392 | 17.436511% |
| CPU侧32位字节折算 | 2640136 | 3197704 | 557568 | 17.436511% |
| Host参数写word | 597504 | 597504 | 0 | 0% |
| Host ready写word | 12 | 12 | 0 | 0% |
| Host请求层号读word | 12 | 12 | 0 | 0% |
| CPU+供参host逻辑事务合计 | 1257562 | 1396954 | 139392 | 9.978281% |
| CPU+供参host逻辑32位字节折算 | 5030248 | 5587816 | 557568 | 9.978281% |

CPU侧读/写差各为11×6336，符合内部交换省掉11次中间激活读回及重装的实际路径。比例分别使用CPU侧或逻辑合计的本行reload分母，没有混用口径。合计是逻辑访问量，非物理SRAM端口或逐byte掩码测量；不含复位前输入fixture、内部RAM和旁路核验探针。

| 不重叠周期区段 | pingpong | reload |
|---|---:|---:|
| 首MMIO至首host请求，含CPU输入搬运 | 285547 | 285547 |
| 12层host供参 | 597504 | 597504 |
| 参数ready至START | 28685484 | 28685484 |
| START至下一请求/最终共享写回 | 254784945 | 261058894 |
| 合计 | 284353480 | 290627429 |

两份首MMIO周期均4543，末完整共享写分别284358022/290631971，独立验证 `末−首+1` 及全部12层host/START顺序、分段求和。末拍指最后word接受且实际写入共享RAM的拍，排除后续响应消费/BOOT。初始输入fixture预装在窗外，CPU输入搬运、逐层host参数、CPU装载、等待及调度在窗内。`bus_waits=0`仅说明命令端无背压，完成响应等待仍包含在端到端周期中；instructions是IFU交付握手，不作退休指令数。

## 报告器口径与证据索引

reporter快照 `7c58df30fe5e456fc6722f5f95e4df43fb4867c0872f3b9054847758075db748` 已复制到审查子目录。对照已关闭性能P2的公式重新检查AST：CPU总量、host参数/12次ready/12次请求读、逻辑合计和各行reload分母保持同一口径；新增实际输入列及正式十二项整机性能待验说明未改变统计公式。另用实际日志调用 `cpu_timing()` 与自行分段结果交叉一致，未调用报告器main或写真实报告目录。

- [独立脚本](encoder-final-cpu-readback/readback.py)与[汇总结果](encoder-final-cpu-readback/result.json)。
- [pingpong完整回读](encoder-final-cpu-readback/pingpong.json)、[reload完整回读](encoder-final-cpu-readback/reload.json)：含实际来源计数、命令、身份、产物SHA、全部原始计数和周期区段。
- [初始进程核对](encoder-final-cpu-readback/initial-processes.json)、[退出进程核对](encoder-final-cpu-readback/final-processes.json)、[有界观察记录](encoder-final-cpu-readback/observations.jsonl)。周期进度文件只周期刷新，最终接受依据是已结束的完整输出及status/log，而非最后一条旧进度。
- [192源初查](encoder-final-cpu-readback/initial-freeze-check.json)、[报告器公式检查](encoder-final-cpu-readback/reporter-formula-check.json)、[报告器快照](encoder-final-cpu-readback/reporter-snapshot.py)、[证据哈希清单](encoder-final-cpu-readback/manifest.json)。

独立脚本SHA为 `6713cad3144a6b4c0b56246dfab38358fc1ff34b9f4c77f34c817ea47ecfe9ec`；只读gate快照为 `dc2483a43acd314f783d274d61946c9c904a595700f4cf6b2060ae87cd16c494`。原始status SHA：pingpong `a7f02731525f35de51b14b704f68034f71068a61baa0a37d39da39385e1890ef`，reload `774e2f0b5079dd024c5f1f717612e42de39a1781bae48b9f9816d2d626bd61df`。

这项对照仅证明同一输入、同一冻结实现中两种层间传递策略的差异；正式目标平台、指定库/SRAM宏、150MHz、面积功耗能耗、官方十二项性能和600样本精度继续由总控按原边界验收。本次回读没有改变实现范围或增加优化搜索。
