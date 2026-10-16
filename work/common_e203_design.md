# 后续共同工程：公开 E203 与 FFN1 总线闭环

本次授权：用户已选择1A，按正式赛题七项补齐SoC及完整编码器并反复验收。本文件固定共同 E203、MMIO、C 驱动底座接口；完整扩展规格见formal_seven_design.md。初稿完成不等于正式比赛验收。

已有数值模型、DOT64、FFN1保持数学行为及接口不变。Yosys0.33的unsigned整线经$signed直接接子模块端口会触发前端内部断言，已用最小例复现；root允许把FFN1的x_q/w_q显式声明为signed以兼容该工具，不改位宽、运算或周期。旧36例证据完整归档，新源码必须重跑全部36例后再验收。禁止Git写、修改上游快照/原始权重/冻结float、参数优化搜索或用软件代算硬件。当前SDK/公开E203不冒充组委会定制工程；没有指定库不声明150MHz、面积或功耗通过。

## 方案与边界

推荐公开官方 E203 的 ICB 外设通路；原FFN1外包桥，不改计算核心。NICE需要自定义指令与SDK修改，初稿不采用。只做总线BFM可更快验证桥，但不能替代真实CPU执行证据，因此同时准备真实E203启动与C驱动。

- E203固定提交：9f3e34f337f5d0a1236a285871ffa2032491617a。
- SDK固定提交：0e0e9083569721578c42f07a95b05a26c0760db6（0.1.4）。
- 上游只读：vendor/e203_hbirdv2-upstream、vendor/hbird-sdk-upstream；来源清单config/e203-source-manifest.json。
- CPU薄外壳实例化官方e203_subsys_top，导出sysper/sysmem ICB；不使用把外接口接零回环的原soc_top作为最终连接。
- 暂定本项目MMIO基址0x11000000，属于官方sysper扩展区。共享SRAM512KiB基址0xa0000000。地址是公开平台初稿选择，非比赛确认配置。
- 单时钟、单outstanding；响应反压时锁住rsp_valid/rdata/err，不能重复执行任何命令。复位撤销所有未完成事务。
- 生产驱动仅搬运、控制、读取，禁止计算矩阵答案。测试期望保留在验证环境，不写入加速器作为预计算输出。

## 固定 MMIO 契约

模块rtl/ffn1_icb.sv：参数M=99,N=256,BASE_ADDR=32'h11000000；clk/rst_n；ICB cmd_valid/ready、cmd_addr[31:0]、cmd_read、cmd_wdata[31:0]、cmd_wmask[3:0]；rsp_valid/ready、rsp_rdata[31:0]、rsp_err。信号名统一前缀icb_，如icb_cmd_valid。内部实例化现有ffn1_top。只接收32位字对齐访问，写wmask必须1111；地址窗口256字节，其余地址和未定义寄存器报错。

| 偏移 | 寄存器 | 行为 |
|---|---|---|
| 0x00 | ID RO | 0x4b575431 |
| 0x04 | STATUS RO | bit0 busy、1 loaded、2 row_ready、3 done、4 sticky error非零 |
| 0x08 | COMMAND WO | 值1=load_begin、值2=start；其他值拒绝，不做组合命令 |
| 0x0c | ERROR RW1C | bit0地址错、1访问类型/掩码错、2值错、3暂存不完整、4核心拒绝；当前事务rsp_err不依赖历史错误 |
| 0x10 | SHIFT RW | 0..47，上方位必须零；busy拒写 |
| 0x14 | LOAD_KIND RW | 0=X、1=W_pack、2=b；busy拒写 |
| 0x18 | LOAD_ADDR RW | 当前银行字地址；busy拒写，核心检查连续装载 |
| 0x1c | LOAD_LO RW | 新低32位；busy拒写，记fresh |
| 0x20 | LOAD_HI RW | 新高16位，上16位必须零；busy拒写，记fresh |
| 0x24 | LOAD_COMMIT WO | 仅值1；X/W要新LO并正确int16符号扩展；b要新LO及HI，拼成signed48；每次提交尝试消费暂存fresh，禁止沿用旧半字 |
| 0x28 | ROW_INDEX RO | 当前行号 |
| 0x2c | ROW_ADDR RW | 0..N-1；busy且非row_ready时拒写 |
| 0x30 | ROW_DATA RO | 只在row_ready读，等同步row_rd_valid后锁结果再返回 |
| 0x34 | ROW_FLAGS RO | 最近成功ROW_DATA的bit0 overflow、1 saturated、2有效；ACK/START/load_begin清有效 |
| 0x38 | ROW_ACK WO | 写当前行号，独立事务产生一拍ACK；等待核心结果后响应 |
| 0x3c | GEOMETRY RO | 低16位M，高16位N |
| 0x40 | DOT_LENGTH RO | 64 |

RW寄存器可读；WO读/RO写报访问错。ERROR允许随时W1C清已知五位，上方位写1拒绝。load_begin成功清fresh/行读flags，保留历史sticky错误直至W1C或系统复位。非法操作不改变核心和合法配置；带来错误的当前总线事务rsp_err=1，并锁存对应sticky位。核心command_error是延后一拍的脉冲，必须等核心处理后判断再回响应。ROW_ACK与读事务串行；不能在未消费读响应时提前ACK。

## C 驱动契约

sw/ffn1_driver.h/.c使用stdint/stddef，不依赖libc、动态内存或SDK新版NMSIS。kwt1_io包含void* context及read32/write32回调；回调返回0成功、非零访问失败，read32通过uint32_t*输出。回调偏移均相对基址。生产E203回调使用volatile32位和RISC-V fence。

提供kwt1_run：io、m、n、X行主序int16[m*64]、W_pack int16[n*64]、bias int64[n]、shift、Y int32[m*n]、可空flags uint8[m*n]、poll_limit。启动前核对ID/GEOMETRY/K、指针、尺寸、shift和bias48范围；负bias先转uint64_t再拆位，避免有符号位移UB。逐银行连续装载、START、逐行轮询、ROW_DATA/FLAGS读回、写入输出缓冲，再ACK，末行后确认DONE。全部轮询有界，回调失败、核心错误、超时、次序错分别返回明确非零码，不吞错。

## 启动与验证

- GCC使用实际可用的RV32IMAC/ILP32（新CSR汇编需要zicsr时明确加），独立freestanding startup设置sp/gp/bss/trap；ELF、map、反汇编和hex均保存。
- 先用真实E203启动最小C程序，通过明确的共享内存邮箱记录PASS/错误码/周期；不得沿用上游固定PC+x3成功判据。
- 测试平台仅装固件和原始输入；真实CPU通过MMIO装载并运行加速器。共享SRAM按单层使用，不一次存十二套W和完整Y。
- 桥TDD涵盖32/48位拆装、错误类型、反压/只执行一次、同步行读、busy拒绝、复位、负bias极值、连续任务。先小尺寸，再至少一个默认完整尺寸；后续系统回归覆盖全部36案例及十二层参数切换。
- 真实CPU完整尺寸至少一例25344输出零差；总线BFM全部36例证据与CPU覆盖范围分开写。周期包含装载、CPU、总线、计算、读回和ACK，先报告行为周期，不宣称已通过150MHz。
- 保留既有数值/RTL输入和报告；新报告放reports/system/与reports/integration/，每一阶段非零退出/缺证/失配不得保留成功。两轮独立规格和质量复核后再交付。
