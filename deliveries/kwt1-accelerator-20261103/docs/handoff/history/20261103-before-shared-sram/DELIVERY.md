# 本次交付范围与复现

本交付复制15个生产RTL、4个头文件、当前模型、TB、脚本、C驱动/镜像、E203接线工具和4个固定上游测试样本；包含模块说明、历史开发文档、选定报告/日志、精度原报告与两个已封存服务器复测包。本次没有修改生产RTL或将它们合并到仓库根目录的工程。

没有携带官方SRAM/工艺库、EDA软件/许可证、编译器运行时、音频/权重全库、大型trace、故意错误副本、完整历史源快照、ELF/二进制和simv。服务器截图不转载，receipt保留截图哈希及截图转录身份，不能将其描述成已下载完整服务器报告。旧文档对省略文件的链接可能只在原本地工程可用；不改写原证据。早期架构文档记录草拟过程，当前ICB无PAIR/可变shift，缓冲深度1，字段宽度以生产宏及ICB说明为准。

`delivery-manifest.json`记录全部交付文件的SHA256（不含其自身）。`handoff-summary.json`给出机器可读状态。完整原验证精度报告副本放在verification/precision-20261102-01/original-reports/；原summary中的绝对路径保留用于追溯。

## 使用方式

在这个独立工程根目录运行，建议Linux/WSL，Python3.10+、NumPy、Icarus。安装依赖须按各自机器环境决定。

```sh
python3 -B tools/verify_delivery.py
python3 -B -m unittest discover -s tests -v
python3 -B -m unittest discover -s integration/e203/tests -p test_prepare_kwt_soc.py -v
```

RTL基础回归可运行`python3 -B scripts/verify_icb.py --contract-models`，只使用本地合同模型，不代表官方宏。默认真实数据导出依赖本地原始模型/音频路径；GitHub不携带这些全库。需要重放固定真实12任务时直接使用server-packages中的封存包，它自带所需量化矩阵、黄金、浮点参考及来源清单，服务器只需Python标准库/VCS和原路径官方SRAM模型。请阅读对应包README，解压并用新的输出目录，不覆盖历史。

性能包解压后的默认输出为official-run-01，只读引用官方模型。原始integration/e203/performance_baseline/run_official.py是打包素材；可直接运行的部署形状由tar.gz提供，不要单独复制这个py后省略performance.py、real12_audit.py、package-sha256.json、fixtures和rtl。

`integration/e203/shared_ram_dev`仅保留本地原型，不在生产filelist中，未接入服务器SoC。其仿真数组禁止综合。交叉编译器已安装在原本地WSL，不含在本交付；构建报告有版本/ISA/ABI。固件构建报告中的PENDING是构建时历史状态，后续CPU成功凭据另见receipt和README，不覆盖历史JSON。

本次交付前仅重新运行短的软件/接线工具测试并校验源哈希/封存包。已有长RTL、真实CPU和官方SRAM结果沿用其原报告及证据边界，不冒充本次又跑了一遍。
