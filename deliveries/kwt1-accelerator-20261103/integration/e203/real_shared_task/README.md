# 一个真实录音样本的E203共享SRAM验证

**当前状态更新：**真实case3已在服务器修复副本`real_shared_case3_test_01/kwt-real-shared-case3-v2`通过，输出位差异0、NRMSE0.01737469%、6079053个测试程序周期。原v1包有clk声明顺序编译错误，生成器已修复；现有服务器沿用v2，不重新安装旧v1包。下文为设计及原部署记录，当前结论见[主交接](../../../docs/handoff/team-handoff-20261103.md)。

复用服务器已有`real12_verify_01/kwt-real12-validation/fixtures`，不重传音频、原数据或生产RTL。本轮选case3（yes/55feffd5_nohash_0.wav、模型第3层，硬件LAYER=2）；case1是合成静音，不能把它称为真实录音。

## 验证链路

Python先核对旧manifest及五个case3文件SHA256，严格检查数量/格式/浮点有限值。旧W按列保存（每列64项），加载前转换为共享row-major；X/W符号扩展到32位容器，内部有效16位不变。数值继续使用X16/Q12、W16/Q16、bias32/Q28、acc40、RNE右移16、Y16/Q12及原3位flags。

TB文件加载器在CPU保持外部复位期间，通过真正的共享ICB接口写X/W/bias和独立整数黄金，共48320个字。仅在新仿真目录生成的SoC副本中增加加载mux和专用加载时钟/复位；原kwt_shared_soc_top及生产共享阵列/E203/加速器不改。加载结束先取消共享协议、复位，再切回原CPU端口/总线时钟/复位，随后才释放CPU。共享复位不清除RAM。

CPU预填Y=DEADBEEF及两侧guard，复用原驱动完成400块，逐项把实际Y/flags写共享，之后从共享回读25344项并与独立共享黄金逐项比较。全部正确且guard通过才返回x3=1；golden不从被测输出生成。TB在实际CPU共享响应退休时记录Y，并核对25344笔完整结果写入/回读；Python对实际轨迹再次逐位审计和计算NRMSE。

## 共享布局（开发地址）

| 内容 | 地址 | 32位字数 |
|---|---|---:|
| X | a0000000 | 6336 |
| W，row-major | a0008000 | 16384 |
| bias | a0018000 | 256 |
| guard-before | a001fffc | 1 |
| Y/flags | a0020000 | 25344 |
| guard-after | a0038c00 | 1 |
| 独立整数黄金（测试专用） | a0040000 | 25344 |

均在512KiB内且不重叠。a0000000仍是开发地址，不是确认过的赛方正式分配。原驱动只在副本中删除未使用fixture头并将LAYER从0改为2；生产RTL和冻结数值不变。

## 上传运行

只上传`kwt-real-shared-case3.tar.gz`到FileZilla的`/e203-integration/kwt-soc/`，无需重传fixtures或替换旧文件。复制以下整个命令块，创建新目录：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
mkdir real_shared_case3_test_01 && \
tar -xzf kwt-real-shared-case3.tar.gz -C real_shared_case3_test_01 && \
cd real_shared_case3_test_01/kwt-real-shared-case3 && \
python3 run_server.py --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
```

旧数据缺失或哈希变化会停止；不要改manifest绕过。默认新输出目录为`verification/real_shared_case3_01`，已有目录拒绝覆盖。保留旧所有仿真和simv。服务器无需编译器，使用包内预编译镜像。

先显示`DATA_IDENTITY_PASS`，编译后显示`REAL_SHARED_CASE3_RUNNING`，运行可能10～20分钟或更久。应最终显示：

```text
PASS E203_REAL_SHARED case=3 blocks=400 outputs=25344 bit_mismatches=0 NRMSE=...%
```

输出包含`report.json`、compile.log、run.log、新TB/SoC/filelist、原TB/SoC备份、加载用转换文件和`run-01/shared-y.txt`。VCS即使rc0也可能失败，因此runner要求唯一TEST_PASS、x3=1、加载/结果完整标记、25344项实际轨迹且逐位/NRMSE通过；TEST_FAIL、Time Out或Fatal都拒绝。

## 本地验证及边界

`tests/check_driver.py`用同一C固件经FIFO驱动实际加速器和64宏共享RTL；宏使用独立合同模型，不冒充真实E203或官方宏。通过后记录完整结果、漏写首结果负向、当前Python整数模型交叉校验及生产哈希。短单测另测源身份、W排列、坏轨迹拒绝、监视器响应背压/重复/部分写入，以及实际生成mux在不同加载/CPU时钟和复位交接后的数据保持。

服务器实际E203和官方SRAM快速功能模型结果待用户运行。本轮模拟文件加载器是验证工具，没有实现生产host接口、DMA或正式双主仲裁；加载时间不作为正式平台加载性能。总CPU周期含结果初始化和软件黄金比较，不用于正式FFN吞吐或与旧任务直接算加速比。官方600/12任务、正式参数加载/计时、150MHz/hold/STA、面积/功耗仍需各自证据。浮点提取TF2.4.0替代2.4.0rc1的等价性限制沿用既有记录。
