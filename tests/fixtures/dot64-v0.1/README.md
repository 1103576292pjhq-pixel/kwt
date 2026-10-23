# 64 点积固定验证向量

本目录提供 30 个用例，不依赖 TensorFlow、音频或完整权重缓存：

- `layer_00.json` 至 `layer_11.json`：从已验证的定点方案每层取一个真实诊断点积，保留原输入、权重、偏置、期望输出、浮点参考和样本身份。
- `boundaries.json`：18 个合成用例，覆盖零、正负半值取偶数、半值两侧、偏置边界、正负输出饱和、抵消和最后一项。
- `manifest.json`：数值规格哈希、来源和每个用例文件的 SHA-256。

使用本仓库 [数值规格 v0.1](../../../docs/shared/numeric-format-v0.1.json)。`x` 和 `w` 各含 64 个 signed16 十进制编码，`bias` 为 signed32；`accumulator_after_bias` 为按 k 递增累加并加偏置的 signed40 期望值，`y_integer` 为 RNE 右移 16 位、饱和到 signed16 后的期望值。真实用例的 `y_float` 是浮点参考，RTL 应比较 `y_integer`，而非浮点值。

这些是整数数值用例，尚未规定握手、拍数、复位或输出背压。RTL testbench 须另行覆盖协议。文件是 JSON，不可直接交给 `$readmemh`；后续按确认的端口转换，保留编码位模式。

合法的 64 个 signed16 乘积加 signed32 偏置不会超过 signed40 范围，因此这套固定格式的外部合法输入无法触发 40 位累加饱和。软件已有缩小位宽的部分和饱和测试；不要伪造超位宽输入来宣称覆盖合法接口的饱和事件。

## 核对方法

从本仓库根目录，在具有 NumPy 的 Python 环境运行：

```bash
python -B - <<'PY'
import hashlib, json, sys
from pathlib import Path
import numpy as np
sys.path.insert(0, 'scripts/model')
from fixed_point import integer_linear
root = Path('tests/fixtures/dot64-v0.1')
manifest = json.loads((root/'manifest.json').read_text())
spec = Path(manifest['numeric_spec_path'])
assert hashlib.sha256(spec.read_bytes()).hexdigest() == manifest['numeric_spec_sha256']
count = 0
for item in manifest['files']:
    path = root/item['path']
    assert hashlib.sha256(path.read_bytes()).hexdigest() == item['sha256']
    data = json.loads(path.read_text())
    for case in data.get('cases', [data]):
        x = np.array([case['x']], dtype=np.int64)
        w = np.array(case['w'], dtype=np.int64).reshape(64, 1)
        b = np.array([case['bias']], dtype=np.int64)
        result, _ = integer_linear(x, w, b, 40, 16, 16, 'rne', 16)
        assert int(result[0, 0]) == case['y_integer'], case['case_id']
        count += 1
assert count == manifest['total_cases']
print('Verified', count, 'dot64 cases')
PY
```

打包时还使用 Python 任意精度整数逐项重算全部期望值，与 NumPy 定点参考交叉核对。此检查不是 RTL 仿真。
