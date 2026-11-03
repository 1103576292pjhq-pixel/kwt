# 12层真实数据的官方SRAM功能验证包

此包包含当前独立加速器15个生产RTL、头文件、新的12任务ICB测试平台、真实验证输入/权重/bias、整数黄金、浮点参考，以及仅依赖Python标准库的编译/运行/审计工具。不包含或分发赛方SRAM模型。

运行目的：同一次复位后连续执行12个BEGIN/装载/计算/读取/ACK/完成任务，LAYER依次0..11。每任务400块25344项，共4800块304128项；所有数值和flags逐位比较。实际ICB结果再由Python解码，与浮点参考分别计算12个NRMSE，要求每项<=3%。同时保留原测试的背压、忙重试、故意早ACK拒绝和末尾ABORT检查；汇总errors包含这些预期负向访问，不能直接当作未解决故障。

发起方为ICB测试平台，不是E203 CPU固件；这些是本地代表性用例，不是组委会最终抽取的12个性能任务。当前不接共享RAM、不声称正式性能。SRAM沿用已通过的ARM_UD_MODEL功能模式，EMA2/EMAW0；通过不表示解决了先前hold违例或150MHz STA。

## 来源

从本地221条分层验证缓存固定选取静音、其他、yes、no、up、down、left、right、on、off、stop、go各第一条，分别对应12层的FFN第一线性层。来源为指定模型237e4097提交及best_weights；manifest记录音频/浮点文件/格式/黄金校验。浮点提取环境TF2.4.0替代2.4.0rc1，等价性未证明。没有用测试集调参，也未修改数值尺度。

## 服务器运行

将外层tar.gz上传到自己的工作目录，解压到新目录，不覆盖已有工程或日志。进入解压后的kwt-real12-validation，运行：

```sh
python3 run_official.py
```

默认只读引用：

`/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP1024X16/verilog/RAMSP1024X16_rtl.v`

`/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP1024X16/verilog/RAMSP1024X16.v`

以及RAMSP128X16对应两文件。编译和仿真日志、实际ICB账本、报告保存到新的official-run-01。目录已存在会拒绝覆盖，重跑时指定`--output official-run-02`。

成功应显示PASS ICB_REAL12_CONTRACT以及PASS REAL12_OFFICIAL；报告status为PASS_REAL12_OFFICIAL_FUNCTIONAL，bit_mismatches=0，每层NRMSE<=3%。已有单任务E203通过记录和完整验证集软件精度报告均保留，不被此次覆盖。
