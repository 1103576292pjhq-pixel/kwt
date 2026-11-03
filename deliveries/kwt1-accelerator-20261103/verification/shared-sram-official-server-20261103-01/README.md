# 512KiB共享SRAM服务器官方功能验证通过

日期2026-11-03。用户截图显示修复副本kwt-shared-sram-v2依次STEP1_PASS及PASS SHARED_SRAM_OFFICIAL。完整官方报告/日志尚未下载读取，凭据身份为截图转录，不伪装成直接读取服务器JSON。

单颗4096宏及64颗宏拼成的512KiB阵列与ICB接口通过。两轮全容量读写、最终回读、32组*16掩码、背压、越界、响应有效时复位、WAIT_MEM读/写复位和合法队列命令均达到封存TB统计。656397请求、656394响应、393735次读检查、1264拍保持；3次故意越界错误与3笔故意复位取消，非异常丢失。EMA2/EMAW0、20ns功能周期、ARM_UD_MODEL。

原V1因VCS故意Fatal返回0而被脚本误判，V2保留原目录/日志，仅更新两份runner并绑定修订哈希，截图确认REPAIR_READY。通过依赖严格负向日志审计，不是屏蔽错误或改写历史PASS。

尚未apply共享SoC接线，尚未由真实E203执行本共享RAM镜像；150MHz、物理hold、面积/功耗、正式真实数据加载/写回/计时均未因此完成。下一步先preview现有kwt_soc_top到新kwt_shared_soc_top的接线，备份和diff在kwt-soc/verification/shared_sram_wiring_01。
