# 单颗官方4096×16 SRAM功能验证

本轮只测试RAMSP4096X16_rtl_top，不接共享SRAM阵列或E203，不改独立加速器RTL。只需上传同目录run_sram4096_smoke.py一个文件；脚本内嵌TB，Python标准库即可运行，服务器使用已有VCS和两份官方模型。

## 检查什么

- 两轮全4096地址、地址相关互补模式写入/读回。
- 16种单bit写掩码、全1禁止所有位写入、高低字节写掩码。
- CEN禁用时写操作不改变内容。
- 0、1、2047、2048、4094、4095的全0/全1边界，以及最终全量回读。
- 正向通过后故意改错首次读期望，必须准确报告addr0、actual9a53/expected9a52的故意错误且无PASS；兼容VCS2020返回0及Icarus返回1，不仅凭退出码判断。

独立黄金数组只由TB发出的请求更新，不读取DUT内部状态。未知/X读值会报错。输出统计应为words4096、reads12336、writes8238、masked_writes18、zero_mask_writes16、disabled_writes2。writes包括16次全禁止掩码的写周期，另外两次CEN禁用写单独统计；不是所有write周期都修改内容。

## 条件及边界

官方模型固定引用：/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP4096X16/verilog/RAMSP4096X16_rtl.v和RAMSP4096X16.v。不下载或再分发官方文件，报告绑定其实际哈希。

使用ARM_UD_MODEL快速功能模式，20ns测试时钟；控制在下降沿后1ns更新，数据在上升沿后8ns比较，避免CLK与控制同时间戳变化。EMA默认2、EMAW默认0，是待测候选，并非已经核实的4096宏通用推荐；可用--ema/--emaw显式更改合法值，换配置必须新输出目录并说明依据，不自动试到通过。

不测试待机Q保持、写时Q保持/写穿、保持模式切换、完整建立保持时序；不证明150MHz、512KiB拼接/仲裁、CPU访问、面积或功耗。TB无SRAM清零复位假设；从全位写入开始，不检查未装载内容。

## 上传和服务器运行

本地文件：D:/嵌赛芯片设计赛道/kwt1-accelerator/integration/e203/sram4096_smoke/run_sram4096_smoke.py。

FileZilla右侧目录：/e203-integration/kwt-soc/。

上传后执行整段：

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
python3 run_sram4096_smoke.py --output verification/sram4096_smoke_01 --ema 2 --emaw 0
```

成功应出现PASS SRAM4096_OFFICIAL。结果在新的verification/sram4096_smoke_01/report.json，另有生成的TB、compile.log、run.log和negative-golden.log。negative-golden.log中的故意失败是正确检错，最终报告必须同时确认正向完整通过和负向被检出。

已有目录拒绝覆盖；再次测试改为_02等新编号。缺模型明确标记BLOCKED_MISSING_OFFICIAL_MODELS，不自动使用替身；其他编译/读写/覆盖失败记FAIL。失败时发最后终端输出并保留对应日志，不修改官方宏或关闭检查恢复PASS。

## 本地工具自检

WSL工程根目录：python3 -B -m unittest discover -s integration/e203/sram4096_smoke/tests -v。

本地仅有独立4096合同替身，测试同一份内嵌TB的正向行为与改错golden、地址别名、忽略WEN、忽略CEN四个负向场景。它不是官方模型；本地通过不能登记为服务器4096功能已通过。Windows没有Icarus时这五项会跳过，须使用WSL完成实际TB自检。
