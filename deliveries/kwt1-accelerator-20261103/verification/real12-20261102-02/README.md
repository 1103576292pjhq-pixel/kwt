# 12层真实数据：完整独立加速器RTL对照

状态：PASS_REAL12_RTL_CONTRACT。实际ICB响应304128项Y/flags与当前整数模型逐位一致，连续12任务4800块；生产RTL未修改。

| 层 | 样本类 | 实际RTL NRMSE (%) |
| --- | --- | ---: |
| 1 | _silence_ | 0.01590282 |
| 2 | _unknown_ | 0.01318576 |
| 3 | yes | 0.01737469 |
| 4 | no | 0.01783309 |
| 5 | up | 0.02214978 |
| 6 | down | 0.01914097 |
| 7 | left | 0.01990142 |
| 8 | right | 0.01995284 |
| 9 | on | 0.02148489 |
| 10 | off | 0.01671152 |
| 11 | stop | 0.01418459 |
| 12 | go | 0.01283760 |

后端为本地SRAM合同模型，发起方为TB。官方模型待服务器运行；不是E203真实CPU12任务、官方任务性能或STA通过。
误差范围、输入来源、所有源码及浮点文件SHA256、实际ICB账本、负向检错和打包信息见report.json。

## 本次统计与审查

4296926个功能仿真周期，1292402次请求/响应配对，4200次满缓冲重试、12次故意过早ACK拒绝，因此errors=4212是预期检错覆盖；响应保持80889拍，末尾ABORT1次。故意改错golden第0项的独立负向运行准确失败，未覆盖正向响应账本。

43项软件测试通过；独立代码审查无Critical/Important。审查提出本地启动哈希未包含rtl/kwt.f：本次文件顺序已与初始记录的15源文件集合核对，并另存filelist-audit.json，明确为运行后核对；后续脚本已补入文件清单的启动/结束快照。原本次源码快照/原报告和服务器包保留，不伪称补有运行前哈希，也未因此重复长仿真。15个生产RTL、数值模型和合同的本次运行前后哈希一致。

## 下一步服务器复验

上传本目录kwt-real12-validation.tar.gz（2507451字节）到FileZilla远程/e203-integration/kwt-soc/。SHA256：c59e99bab546013b19793894d32e7a54912660de5ace778c98d524e08337a0db。包内86个文件的校验已核对，不含赛方SRAM库。

```sh
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc && \
ls -l kwt-real12-validation.tar.gz && \
mkdir real12_verify_01 && \
tar -xzf kwt-real12-validation.tar.gz -C real12_verify_01 && \
cd real12_verify_01/kwt-real12-validation && \
python3 run_official.py
```

脚本先校验包，再在新的official-run-01编译和运行官方ARM_UD_MODEL功能模型；不改原加速器/E203目录或之前运行。这一步发起方为TB，不是E203固件。

2026-11-02结果更新：用户已执行上段命令，截图显示PASS REAL12_OFFICIAL、304128项逐位差异0、12任务最大NRMSE0.02214978%；4296926周期、1292402次请求/响应及预期错误统计与本地一致。官方SRAM功能模型的复验已通过，[证据](../real12-official-server-20261102-01/receipt.json)；未直接读取全部服务器报告，不能据截图声称零警告或时序通过。
