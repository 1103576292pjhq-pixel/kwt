"""KWT1-FFN1的整数黄金模型。

所有硬件数值解释集中在这里：16×16精确乘积、逐k的sat40、bias32、
RNE右移16、sat16。NumPy int64是软件运算容器，目标硬件acc仍为40位。
不模拟时钟、FIFO、SRAM时序或总线；这些应由后续RTL测试平台检查。
"""
from dataclasses import dataclass
import json
from numbers import Integral
from pathlib import Path

import numpy as np

SPEC_ID = 'KWT1-FFN1'
M, K, N = 99, 64, 256
ACC_MIN, ACC_MAX = -(1 << 39), (1 << 39) - 1
RAW_MIN, RAW_MAX = -70864863232, 70866960383


def _signed_integer(value, bits, name):
    """检查原值，再转换Python int；bool不能偷偷作为0/1参与计算。"""
    if isinstance(value, (bool, np.bool_)) or not isinstance(value, Integral):
        raise TypeError(f'{name} must be an integer, excluding bool')
    value = int(value)
    if not -(1 << (bits - 1)) <= value < (1 << (bits - 1)):
        raise ValueError(f'{name} outside signed{bits}')
    return value


def _clip(value, lower, upper):
    return max(lower, min(upper, value))


@dataclass(frozen=True)
class Conversion:
    """raw是sat40后的Q28；rounded尚未sat16；y是最终16位编码整数。"""
    raw: int
    rounded: int
    y: int
    flags: int


def convert_accumulator(accumulator, bias, *, is_last=False):
    """转换一个acc40+bias32。任意合法acc40可用于组件溢出压力验证。

    完整K64任务不会触发raw overflow；组件接口仍定义并检查该标志。
    固定右移16，不接受可变shift参数。
    """
    accumulator = _signed_integer(accumulator, 40, 'accumulator')
    bias = _signed_integer(bias, 32, 'bias')
    if type(is_last) is not bool:
        raise TypeError('is_last must be bool')

    # Python整数表示硬件41位临时和，避免先发生40位回绕再检查。
    extended = accumulator + bias
    raw = _clip(extended, ACC_MIN, ACC_MAX)
    overflow = extended != raw

    # 使用绝对值做除法，明确保证负数tie同样按偶数舍入。
    quotient, remainder = divmod(abs(raw), 65536)
    if remainder > 32768 or (remainder == 32768 and quotient & 1):
        quotient += 1
    rounded = -quotient if raw < 0 else quotient
    y = _clip(rounded, -32768, 32767)
    flags = int(overflow) | (int(y != rounded) << 1) | (int(is_last) << 2)
    return Conversion(raw, rounded, y, flags)


def dot64_scalar(x, w, bias, *, is_last=False):
    """逐项Python-int参考：严格64项，输入signed16，偏置signed32。"""
    x, w = tuple(x), tuple(w)
    if len(x) != K or len(w) != K:
        raise ValueError('dot length must be 64')
    bias = _signed_integer(bias, 32, 'bias')
    x = [_signed_integer(value, 16, 'x') for value in x]
    w = [_signed_integer(value, 16, 'w') for value in w]
    accumulator = 0
    for k in range(K):
        # 数学合同每个前缀sat40；在当前合法域内限幅不会发生。
        accumulator = _clip(accumulator + x[k] * w[k], ACC_MIN, ACC_MAX)
    return convert_accumulator(accumulator, bias, is_last=is_last)


def _task_arrays(x, w, bias):
    """拒绝隐式窄化，防止int64非法高位在转换成int16前消失。"""
    x, w, bias = np.asarray(x), np.asarray(w), np.asarray(bias)
    if x.dtype != np.dtype(np.int16) or w.dtype != np.dtype(np.int16):
        raise TypeError('X and W must have native int16 dtype')
    if bias.dtype != np.dtype(np.int32):
        raise TypeError('bias must have native int32 dtype')
    if x.shape != (M, K) or w.shape != (K, N) or bias.shape != (N,):
        raise ValueError('production shapes are X[99,64], W[64,256], bias[256]')
    return x, w, bias


def ffn1_int16(x, w, bias):
    """完整任务，返回Y int16[99,256]与flags uint8[99,256]。

    依据范围证明使用int64矩阵乘法：所有K64前缀及加bias结果严格在
    signed40内，所以该合法域中逐次sat40与精确整数matmul等价。
    这不表示任意长度/任意精度下都可以删除逐前缀饱和。
    """
    x, w, bias = _task_arrays(x, w, bias)
    raw = x.astype(np.int64) @ w.astype(np.int64) + bias.astype(np.int64)
    if np.any(raw < RAW_MIN) or np.any(raw > RAW_MAX):
        raise ArithmeticError('K64 legal-domain bound violated')

    magnitude = np.abs(raw)
    quotient, remainder = magnitude >> 16, magnitude & 65535
    increment = (remainder > 32768) | ((remainder == 32768) & ((quotient & 1) != 0))
    rounded = quotient + increment.astype(np.int64)
    rounded = np.where(raw < 0, -rounded, rounded)
    saturated = (rounded < -32768) | (rounded > 32767)
    y = np.clip(rounded, -32768, 32767).astype(np.int16)
    flags = saturated.astype(np.uint8) << 1  # 合法整任务raw overflow恒为0。
    flags[-1, -1] |= np.uint8(4)
    return y, flags


@dataclass(frozen=True)
class Encoding:
    """values为编码整数；计数表示浮点原值被裁到可表示端点的项数。"""
    values: np.ndarray
    endpoint_clipped_count: int


_FORMATS = {'x': (16, 12, np.int16), 'w': (16, 16, np.int16),
            'bias': (32, 28, np.int32), 'y': (16, 12, np.int16)}


def _format(role, *, allow_output):
    if not isinstance(role, str) or role not in _FORMATS or (role == 'y' and not allow_output):
        raise ValueError('role must be x, w, bias' + (' or y' if allow_output else ''))
    return _FORMATS[role]


def encode_finite(values, role):
    """有限float16/32/64按固定尺度RNE编码，返回编码及端点裁剪数。

    先在实数域裁到可表示端点，避免巨大有限浮点数乘尺度时溢出。
    裁剪统计针对原实数值，不仅统计最后整数是否越界。
    """
    bits, fraction, dtype = _format(role, allow_output=False)
    values = np.asarray(values)
    if not np.issubdtype(values.dtype, np.floating) or values.dtype.itemsize > 8:
        raise TypeError('encoding requires real float16/32/64 values')
    if not np.all(np.isfinite(values)):
        raise ValueError('encoding refuses NaN and infinity')
    values = values.astype(np.float64)
    scale = float(1 << fraction)
    low, high = -(1 << (bits - 1)), (1 << (bits - 1)) - 1
    real_low, real_high = low / scale, high / scale
    clipped_count = int(np.count_nonzero((values < real_low) | (values > real_high)))
    clipped = np.clip(values, real_low, real_high)
    encoded = np.clip(np.rint(clipped * scale), low, high).astype(dtype)
    return Encoding(encoded, clipped_count)


def decode_fixed(values, role):
    """将合法编码解码为float64；宽容器可以使用，超有效位宽不能使用。"""
    bits, fraction, _ = _format(role, allow_output=True)
    values = np.asarray(values)
    if not np.issubdtype(values.dtype, np.signedinteger):
        raise TypeError('decoding requires a signed integer array')
    if np.any(values < -(1 << (bits - 1))) or np.any(values > (1 << (bits - 1)) - 1):
        raise ValueError(f'{role} encoding outside signed{bits}')
    return np.ldexp(values.astype(np.float64), -fraction)


def _contract_definition():
    # JSON是冻结身份记录，不是允许临时切换acc48/sat32的配置开关。
    return {
        'spec_id': SPEC_ID, 'format_version': 1,
        'encoding': 'signed_twos_complement', 'zero_point': 0,
        'geometry': {'m': M, 'k': K, 'n': N, 'parameter_layers': 12},
        'widths': {'x': 16, 'w': 16, 'product': 32, 'bias': 32,
                   'accumulator': 40, 'adder_temporary': 41, 'output': 16},
        'fraction_bits': {'x': 12, 'w': 16, 'product': 28, 'bias': 28,
                          'accumulator': 28, 'output': 12},
        'output_right_shift': 16, 'rounding': 'nearest_ties_to_even',
        'accumulation': 'k_ascending_sat40_each_prefix_then_bias',
        'output_saturation': 'signed16_after_rounding',
        'flags': {'raw_overflow': 0, 'output_saturated': 1, 'global_last': 2},
        'legal_raw_range': [RAW_MIN, RAW_MAX],
        'transport_bits': {'legacy_command': 48, 'shared_bias': 64, 'shared_y': 32},
    }


def load_contract(path):
    """读取并核对冻结JSON；拒绝重复key和所有数值/结构漂移。"""
    def unique_keys(pairs):
        result = {}
        for key, value in pairs:
            if key in result:
                raise ValueError(f'duplicate contract key: {key}')
            result[key] = value
        return result

    contract = json.loads(Path(path).read_text(encoding='utf-8-sig'), object_pairs_hook=unique_keys)
    canonical = lambda value: json.dumps(value, sort_keys=True, separators=(',', ':'), allow_nan=False)
    if canonical(contract) != canonical(_contract_definition()):
        raise ValueError('numeric contract differs from the frozen FFN1 definition')
    return contract
