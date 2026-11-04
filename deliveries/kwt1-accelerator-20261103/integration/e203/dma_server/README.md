# DMA完整E203服务器验证包

本包用于在现有kwt-soc中运行DMA加速器和新RV32固件，比较已通过的ICB版2486736周期。包含匹配的DMA RTL、882字节预编译固件、接线生成、源码清单转换、加载器、计时和结果审计工具。

## 第一步 上传

将kwt-dma-server.tar.gz上传到现有e203-integration/kwt-soc目录。本包使用服务器已有的real12_verify_01/kwt-real12-validation/fixtures和赛方SRAM库。

## 第二步 启动

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
mkdir dma_server_test_01 && \
tar -xzf kwt-dma-server.tar.gz -C dma_server_test_01 && \
python3 dma_server_test_01/kwt-dma-server/run_server.py \
  --root /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc \
  --baseline verification/throughput_icb_02/report.json \
  --output verification/dma_soc_01
```

目录已存在时停止，后续使用新目录。新运行的源码清单会选中包内DMA模块，E203平台和共享SRAM继续引用现有服务器资料。原工程作为基线保留。

## 实际连接和检查

- CPU SysPer连接DMA配置从接口，CPU SysMem与DMA主接口通过仲裁连接共享SRAM。
- TB在CPU复位期间通过原ICB加载mux写入黄金和实际输入参数，完成后释放CPU执行新程序。
- CPU执行结果区初始化、配置DMA并等待完成，DMA执行输入装载和结果写回，CPU再完整回读校验。
- 计时和结果监视器观察仲裁后的共享接口，因此同时看到CPU和DMA事务。计时从首笔X0装载请求有效采样至最后结果写响应退休。
- 所有25344项实际共享回读必须与原整数黄金一致，计算NRMSE后才输出最终PASS。
- 启动及结束检查原源码、库、清单、数据、固件身份，比较时核对基线时钟、加载周期和数据一致。

## 输出和判断

结果位于verification/dma_soc_01。report.json保存周期、分阶段统计、NRMSE、源码版本及比较结果，compile.log/run.log保存编译和仿真输出，run-01/shared-y.txt保存实际结果回读。

kwt_dma_soc_top.v为生产连接候选，kwt_real_soc_top.v和tb_real.v为本轮含仿真加载mux的测试副本。soc_real.f/shared_candidate.f记录本次实际选择的源码。完整SoC综合需使用生产连接候选并另配ASIC库和约束。

最终应看到PASS E203_DMA_SOC以及PERFORMANCE IMPROVED或NOT_IMPROVED。报告的150MHz值为目标频率归一化，STA/PPA另行确认。

## 当前本地准备结果

同一生成器输出的加载mux、DMA/CPU仲裁、合并总线监视器已在本地跑通完整400块25344项，逐位差异0，NRMSE0.01737469%，通过源码清单和基线身份检查。此项本地验证使用CPU总线发起器和自有SRAM合同模型。实际E203和赛方模型的结果由上述服务器运行取得。
