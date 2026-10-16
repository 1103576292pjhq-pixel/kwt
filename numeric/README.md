# 整数数值模型与向量接口

固定规则见 `config/prototype-numeric.json`。输入步长 `sx=2^-8`，权重步长只从该层冻结 W 的完整范围推导；不根据输入样本、Y 或精度反馈调整。偏置同乘积尺度，先加完 64 个乘积，再加偏置；超 48 位时饱和并置 overflow。输出 RNE 右移 0..47 位，再饱和到 32 位。

```python
from numeric.fixedpoint import dot64_reference, ffn1_reference
result = dot64_reference(x64, w64, bias48, shift)
# result.raw: signed48, result.output: signed32
# result.overflow: 49-bit bias addition clipped to 48 bits
# result.output_saturated: final 32-bit clipping only
matrix = ffn1_reference(Xq, Wq, bq, shift)
# same field names; arrays have M x N shape
```

`saturate_signed(value,bits)` 返回一个 Python int。`rshift_rne(value,shift)` 返回一个 Python int，负数半值也遵循偶数舍入。`quantize_signed(array,scale,bits)` 返回 int64 数组和统计字典。`derive_layer_config(W,b)` 返回 `LayerConfig`；`metadata()` 是可序列化的尺度、位移、保守范围及统计。

向量入口：在工作区根目录以 `.venv-dv/bin/python scripts/generate_prototype_vectors.py` 运行。输出根目录为 `reports/prototype/vectors`，`manifest.json` 只有所有 36 案例成功并回读后才是 PASS。

`--output` 在创建目录或写入状态前检查路径，拒绝与 baseline/repeat、源码、配置、数据、工具及环境等保留输入的祖先/后代重叠；目录符号链接先解析。源码哈希字段必须恰好包含 `numeric/fixedpoint.py`、`numeric/artifacts.py`、`scripts/generate_prototype_vectors.py` 三项，缺项、空字典和额外项都拒绝。

## manifest schema（版本 1）

- 顶层：`status`, `schema_version`, `source`, `numeric_config`, `case_count`, `output_count`, `cases`, `per_layer`, `summary`, `scope`。
- `cases[]`: `case_id`（`<sample_id>/layer_XX`）, `sample_id`, `layer`, `partition`, `config`, `arrays`, `metrics`, `saturation`, `scalar_checks`, `int64_bound`。
- `config`: `input_scale`, `weight_scale`, `product_scale`, `output_scale`, `output_shift`, `safe_raw_bound`, `weight_stats`, `bias_stats`。
- `arrays.<name>`: `{path,sha256,shape,dtype}`；path 相对向量根目录，不相对工作区。
- 数组：`Xq` int16[99,64]；`Wq` int16[64,256]；`Wq_packed` int16[256,64]；`bq` int64[256]（仅低 48 位有意义）；`Yq` int32[99,256]；`raw48` int64[99,256]；`overflow` bool[99,256]；`output_saturated` bool[99,256]。
- `metrics`: `nrmse`, `rmse`, `max_abs_error`, `sum_squared_error`, `sum_squared_reference`, `output_count`, `within_3_percent`。
- `saturation`: `input`, `weight`, `bias`, `raw48`, `output32`，均为实际元素次数。
- `per_layer` 汇总三个输入的误差能量后计算 NRMSE，不取 case NRMSE 平均；`summary.max_case_nrmse` 和 `max_layer_nrmse` 均保留。

`raw48` 是饱和后、移位前的原始整数和。`Yq * output_scale` 是解码值。所有案例完整保留尺寸；十二层是独立案例，不把上一层 FFN1 输出当作下一层输入。
