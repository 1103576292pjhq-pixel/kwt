# 官方SRAM存储实体和wrapper测试

这里只测试当前`kwt_storage_array.v`和`kwt_storage_wrapper.v`，不编译旧行为存储草稿或整个加速器。

## 两个TB分别做什么

- `tb_storage_array.v`：直接驱动24颗宏的原生接口，遍历物理地址，检查每个写掩码位、读写极性、写时Q保持、禁用及复位不误写。不假定待机Q保持。
- `tb_storage_wrapper.v`：用逻辑bank端口访问存储；检查L1返回、宏边界、bank和W槽独立性、全部X越界地址、同bank读写冲突、复位取消及bias组合读。黄金数组只按TB发出的合法请求更新。

## 正式模型入口

在Ubuntu WSL的活动工程根目录运行：

```bash
/usr/bin/python3 -B scripts/verify_storage.py --models-dir '/mnt/d/实际存放官方模型的目录'
```

目录中需要两种型号的完整`.v`及其现成封装，通常是`RAMSP128X16.v`、`RAMSP128X16_rtl.v`、`RAMSP1024X16.v`、`RAMSP1024X16_rtl.v`；如有include依赖也要保留。真实文件名以赛方目录为准。

可重复指定`--models-dir`，或用多个`--model-file`显式列出文件，额外include目录用`--include-dir`。编译宏通过`--define`显式传入并记入报告，不自动启用快速模型。脚本缺模型时保存`BLOCKED_MISSING_OFFICIAL_MODELS`，不会自动选替身。

## 仅自检TB和外围合同逻辑

```bash
/usr/bin/python3 -B scripts/verify_storage.py --contract-models
```

该模式显式编译`support/sram_contract_models.v`，其内容是我们编写的测试专用模型，**不是赛方代码**。它假设待机Q保持，且读延时为0.2ns；这不替代对官方模型真实行为的核对。状态固定标记`PASS_STORAGE_TB_CONTRACT_SELFTEST_ONLY`，不能当成官方宏通过。

两种模式都新建独立`verification/storage-时间-编号/`，保存源码身份、命令、退出码、日志、事务账本、错误副本检出和说明。默认周期20ns只用于功能检查，不能当150MHz的STA证据。可用`--vcd`保存波形。

首次官方宏回归仍需要把服务器上的完整模型放到本地可访问目录，或者在有Icarus/Python的服务器环境运行同一工程与脚本。本次脚本不登录或修改服务器。
