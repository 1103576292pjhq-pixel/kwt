# 独立V07加速器测试

入口：`bash scripts/rtl/run_accelerator_tests.sh`。从工作树根目录运行。

`tb_buffers.sv`独立核对X的4-bank地址映射、两槽W的bank/ctx/k映射、偏置符号扩展、尾行和另一槽并发写入，共8480项lane/bias检查。

`tb_accelerator.sv`发送真实命令加载输入及参数，所有结果均经过实际核心计算。期望由Python精确整数点积、signed floor商余数RNE和sat16独立生成，不把RTL结果作为参考。核对data、flags、task、全局索引、重复、缺失及输出顺序。

默认M5/N32/两层，用于快速排错；支持M1..99、N16..256且为16的倍数、层数1..12。包含连续X写入、数据间断、输出短/长背压、尾行、完成当拍下一BEGIN、非法命令、运行期故障、受阻输出故障、同步复位和abort恢复。

```bash
TEST_LATENCY=2 bash scripts/rtl/run_accelerator_tests.sh
TEST_M=99 TEST_N=256 TEST_LAYERS=12 bash scripts/rtl/run_accelerator_tests.sh
TEST_MACRO=1 bash scripts/rtl/run_accelerator_tests.sh
TEST_MACRO=1 TEST_LATENCY=2 bash scripts/rtl/run_accelerator_tests.sh
```

宏模式使用本地实际模型及UNIT_DELAY；模型0时刻的CEB唤醒警告单列记录，功能通过不等于库时序通过。测试时钟10ns也不是150MHz验收。

脚本会覆盖out中的对应向量和测试可执行文件。不同配置串行执行，不能共享一个out目录并行运行。
