# 2026-11-02 官方SRAM功能模型：12层真实数据RTL通过

用户截图明确显示`PASS ICB_REAL12_CONTRACT`和`PASS REAL12_OFFICIAL`：12任务、4800块、304128项Y/flags逐位一致，bit_mismatches=0，最大单任务NRMSE=0.02214978%（第5层），12项均小于3%。

服务器报告：

`/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/real12_verify_01/kwt-real12-validation/official-run-01/report.json`

统计：4296926周期、1292402次请求及响应；busy_retries=4200、errors=4212、holds=80889、aborts=1。errors由4200次满缓冲重试和12次故意提前ACK构成，是预期检错覆盖。

| 层 | 截图中的NRMSE (%) |
| --- | ---: |
| 1 | 0.01590282 |
| 2 | 0.01318576 |
| 3 | 0.01737469 |
| 4 | 0.01783309 |
| 5 | 0.02214978 |
| 6 | 0.01914097 |
| 7 | 0.01990142 |
| 8 | 0.01995284 |
| 9 | 0.02148489 |
| 10 | 0.01671152 |
| 11 | 0.01418459 |
| 12 | 0.01283760 |

[原始截图](test-pass.png)、[机器可读摘录](receipt.json)。截图仅显示取舍到8位小数的NRMSE；摘录不冒充下载的服务器原报告。上传包SHA256和来源见本地real12-20261102-02/report.json，截图文件大小2507451字节也与本地包一致。

本次是测试平台通过ICB驱动独立加速器，并使用官方ARM_UD_MODEL功能模式、EMA2/EMAW0。不是E203真实CPU12任务、官方12性能任务、600样本验收、共享RAM集成或SRAM时序通过。离线浮点提取环境TF2.4.0代替2.4.0rc1的等价性限制仍保留；此前hold问题需另行处理。
