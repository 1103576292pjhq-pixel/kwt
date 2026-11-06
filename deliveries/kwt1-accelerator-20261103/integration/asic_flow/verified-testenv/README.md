# 已核对的参数加载与测试环境文件

2026-11-07：用户提供服务器摘要截图，以下9个文件与本地副本在UTF-8、LF统一换行后SHA256一致。包含注释及其他空白，并非只比较有效代码。原始换行字节一致性未确认。

- test_env/：real_loader.v、suite_metrics.v、run_suite.py、suite_tools.py、timing_tools.py、task_test.c、shared_task.c。
- asic150/：real_loader_150.v、suite_metrics_150.v，按原脚本生成后与服务器摘要匹配。

此目录是部分已验证快照，**不是独立可运行的新入口**。尚缺其他导入模块、数据/身份清单、TB和平台连接封装等依赖闭包；不能直接用这里的run_suite.py替代完整环境。原来的配套环境、脚本和相对路径保持不变。

服务器test_env/platform/kwt_real_soc_top.v与本地副本不同；ASIC tb_top.v只有服务器摘要、尚无匹配副本。未上传旧副本替代，也未新增E203平台RTL。核对明细见 [server-check.json](server-check.json)。
