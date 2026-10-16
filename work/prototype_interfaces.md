# 原型基础件交接接口

由两个实际实现worker于2026-10-15回报并冻结；发现实现与本文件不符时先记录并修复一致性，不私自分叉协议。

## DOT64

```systemverilog
module dot64(
  input clk, rst_n,
  input start_valid,
  output start_ready,
  input signed [47:0] start_bias,
  input [5:0] start_shift,
  input in_valid,
  output in_ready,
  input signed [15:0] in_x, in_w,
  output out_valid,
  input out_ready,
  output signed [31:0] out_data,
  output signed [47:0] out_raw,
  output out_overflow, out_saturated, out_error, busy
);
```

- start_valid&&start_ready在IDLE接收bias/shift；合法shift0..47，48..63直接生成out_error=1零结果，不收操作数。
- 合法任务接收恰好64次in_valid&&in_ready，之后完成bias49位检查和RNE/sat32。
- out_raw为饱和48位原始和；out_overflow仅raw48溢出；out_saturated为32位输出饱和；flag随out_valid保持。
- out_valid后结果稳定到out_ready消费；busy覆盖收集/计算/等待；消费后再接新任务。异步低有效复位中止。
- 真实实现和测试证据在 `work/dot64_handoff.json`。

## 数值模型与向量

模块：`numeric.fixedpoint`，计划API：`rshift_rne`、`saturate_signed`、`dot64_reference`、`ffn1_reference`。
DotResult：`raw, output, overflow, output_saturated`。

生成器输出manifest的cases字段包括Xq/Wq/bq/Yq，以及Wq_packed=Wq.T、raw48、overflow、output_saturated；数组为.npy并记录sha256/shape/dtype。每例配置含input_scale、weight_scale、output_scale、output_shift。

最终具体manifest路径和API签名以数值worker的 `work/numeric_handoff.json` 与已通过测试为准，集成器验证后消费，不凭猜测读取。
