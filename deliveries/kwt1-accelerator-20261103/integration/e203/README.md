# E203 集成准备（2026-11-02）

只需上传 `prepare_kwt_soc.py` 一个文件到服务器 `/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc/`。FileZilla 的 `/` 映射到账号 Desktop，所以右侧目录是 `/e203-integration/kwt-soc/`。

本工具读取服务器实际副本并校验预期结构。`tests/upstream/` 是用户指定 GitHub 仓库固定提交的测试样本，**不用于覆盖或替换服务器的官方 RTL**。

## 本阶段接线

| 文件 | 改动及原理 |
|---|---|
| 新增 rtl/e203/soc/kwt_soc_top.v | 用原 SoC 的引脚和外设连接作模板，完整连接 SysPer 和加速器的请求、响应；原 e203_soc_top.v 保留 |
| rtl/e203/subsys/e203_subsys_main.v | 新增 kwt_bus_rst_n 输出，直接连接现有 bus_rst_n；继续使用原有同步复位电路 |
| rtl/e203/subsys/e203_subsys_top.v | 引出 main 的总线复位和已经存在的 hfclk，供同域加速器使用 |
| tb/tb_top.v | SoC 类型改为 kwt_soc_top，实例名 u_e203_soc_top 不变，以保留测试平台已有层级引用；选择 vcs 分支 |

新顶层实例参数为 BASE_ADDR=0x11000000、SRAM_EMA=2、SRAM_EMAW=0；external_abort_req 接 0，软件仍可使用当前 ABI 的 ABORT。暂不接中断，状态通过已有寄存器轮询。加速器生产源码、计算位宽和流水结构没有改动。

时钟：main 生成 hfclk，subsys 内部 hfclk 连接 kwt_bus_clk，再连接加速器 clk。复位：main 内部 bus_rst_n 经新增端口逐层引出连接加速器 rst_n。没有跨层层级取信号，也没有新增时钟/复位生成器。

## 在服务器执行：先预览

```text
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
python3 prepare_kwt_soc.py preview
```

成功标志为 PREVIEW_READY。生成 wiring_01/before/、after/、wiring.diff 和 report.json；此时输入 RTL 尚未修改。不重复使用已有 wiring_01，以保留历史证据。未知占位接线、已有目标文件等情况会停止。

## 核对真实预览后才应用

```text
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
python3 prepare_kwt_soc.py apply
```

成功标志为 APPLY_DONE。应用前检查全部原输入和候选文件的哈希；预览后发生任何变化则停止。多文件写入不是整体原子事务，OS 写入失败时保留报错和 before 备份，不强制继续或自动覆盖。

## 本地证据及未完成项

- 在工具不存在时，预览成功测试先失败；实现后工具 7 项测试通过。
- 工程原有 33 项软件测试通过。
- 测试样本来源固定为 https://github.com/riscv-mcu/e203_hbirdv2/tree/9f3e34f337f5d0a1236a285871ffa2032491617a 。保留各文件原版权头。
- 截图确认原服务器 E203 的 rv32ui-p-add 测试为 TEST_PASS，最终 x3=1，cycle_count=25804。该截图属于原工程基线证据，不是本次集成的证据。
- 用户截图确认：服务器 `kwt-soc` 的 preview 显示 PREVIEW_READY，随后 apply 显示 APPLY_DONE。实际新顶层实例为 BASE_ADDR=0x11000000、SRAM_EMA=2、SRAM_EMAW=0，clk/rst_n 接新增的 kwt_bus_clk/kwt_bus_rst_n。
- 用户截图确认：`verification/soc_compile_01` 使用 VCS、ARM_UD_MODEL 和四个官方 SRAM 模型文件完成链接并生成 simv。编译末尾存在文件时间戳 Clock skew 警告；没有据此宣称物理时序收敛。
- 用户截图确认：集成后的 `verification/soc_compile_01/add_run_01` 显示 TEST_PASS，最终 x3=1，cycle_count=25804，valid instruction count=16560，test ending cycle=25758，与原 add 基线的这些计数一致。**该测试没有证明 CPU 访问加速器的 MMIO 或驱动正确。**下一步查找交叉编译器，编译实际访问当前寄存器 ABI 的程序，再验证驱动和数据结果。
- 官方 SRAM 功能模型继续使用 ARM_UD_MODEL；时序违例的 STA 闭合、共享 RAM、参数加载环境和性能认证仍单独待做。

工具测试命令：`python -X utf8 -m unittest discover -s integration/e203/tests -p test_prepare_kwt_soc.py -v`。

原软件测试命令：`python -X utf8 -m unittest discover -s tests -v`。
