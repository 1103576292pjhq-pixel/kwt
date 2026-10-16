# 编码器共享 FP32 运算器契约 v1

本文件是正式七项初稿的基础运算接口，已在用户授权范围内。官方原始 HardFloat Release 1 只读，清单见 config/hardfloat-source-manifest.json；使用 source/RISCV 专用配置及原 BSD 许可。

模块 rtl/encoder_fp32.sv，接口：clk、rst_n；req_valid、req_ready、req_op[3:0]、req_a/req_b/req_c[31:0]；rsp_valid、rsp_ready、rsp_data[31:0]、rsp_flags[4:0]、rsp_error；busy。

- 输入/输出均 IEEE binary32 原始位，roundingMode=0（最近偶数），tininessAfterRounding。
- 操作：0 ADD(a+b)，1 SUB(a-b)，2 MUL(a*b)，3 FMA(a*b+c，单次舍入)，4 DIV(a/b)，5 SQRT(a)，6 F32_TO_I32(a，最近偶数有符号整数，结果为整数32位)，7 I32_TO_F32(a作为int32)。8—15返回7fc00000，rsp_error=1，flags=0。
- ADD/SUB/MUL各使用对应标准 HardFloat 模块，FMA使用 mulAddRecFN；DIV/SQRT使用 divSqrtRecFN_small。不得将普通乘法借助加正零改变负零语义。转换使用对应官方模块。
- req_valid&&req_ready只接受一笔。单笔未完成响应前不接受下一笔；rsp_valid保持至rsp_ready。DIV/SQRT的一周期outValid必须锁存，不能丢响应。busy从接受请求至响应消费为1；req_ready仅空闲时1。响应消费后下一周期可接受新请求。
- rst_n为低有效同步系统复位；复位清除在途请求/响应，重新请求可正常工作；HardFloat子模块的nReset接rst_n。
- flags保持HardFloat五位顺序：invalid/divide-by-zero/overflow/underflow/inexact。转换的intExceptionFlags需按官方语义映射并在文档说明。rsp_error仅未知操作=1，IEEE异常通过flags表达。
- upstream默认canonical NaN，位真参考对NaN同样规范化；不得用真实数、$exp、$sqrt、DPI或软件计算替代可综合数据通路。

所有权：基础运算worker只负责rtl/encoder_fp32.sv、dv/fp32/、tests/fp32/、scripts/run_fp32.sh、reports/encoder/fp32/及work/fp32_handoff.json。非线性、整个编码器、SoC、导出/其他numerics文件归root或后续单独分配。

验收：先保留真实可编译行为RED证据，再定向IEEE角落/独立主机浮点参考的随机有限数测试/响应背压/复位中断/无效操作；每种操作有非零实际事务覆盖；正确处理符号零/次正规/除零/平方根负数/溢出/舍入。产生可复现源清单、实际工具命令、日志、源码/输入/输出哈希和独立重复证据。Verilator实际执行优先；用Icarus至少交叉核对一组。Yosys可做未映射结构检查，不冒称IEEE全形式证明或工艺PPA。不能因没有正式库而停下功能验证。
