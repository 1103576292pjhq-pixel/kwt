"""Bit-true FFN1 arithmetic, independent of RTL.

All scalar arithmetic uses arbitrary-precision Python integers. The matrix fast
path proves its int64 bound before NumPy multiplication and checks selected
outputs against the scalar implementation. There is no calibration or search.
"""
from dataclasses import dataclass
import math
from numbers import Integral

import numpy as np


def _integer(value, name):
    if isinstance(value, (bool, np.bool_)) or not isinstance(value, Integral):
        raise TypeError(f"{name} must be an integer")
    return int(value)


def _shift(shift):
    shift = _integer(shift, "shift")
    if not 0 <= shift <= 47:
        raise ValueError("shift must lie in 0..47")
    return shift


def saturate_signed(value, bits):
    """Return integer value clipped to signed bits; no natural-width wrap."""
    value, bits = _integer(value, "value"), _integer(bits, "bits")
    if bits < 1:
        raise ValueError("bits must be positive")
    return min(max(value, -(1 << (bits - 1))), (1 << (bits - 1)) - 1)


def rshift_rne(value, shift):
    """Divide by 2**shift, rounding ties to even symmetrically about zero."""
    value, shift = _integer(value, "value"), _shift(shift)
    if shift == 0:
        return value
    quotient, remainder = divmod(abs(value), 1 << shift)
    half = 1 << (shift - 1)
    if remainder > half or (remainder == half and quotient % 2):
        quotient += 1
    return -quotient if value < 0 else quotient


def _scalar_in_range(value, bits, name):
    value = _integer(value, name)
    if value != saturate_signed(value, bits):
        raise ValueError(f"{name} does not fit signed {bits} bits")
    return value


@dataclass(frozen=True)
class DotResult:
    raw: int
    output: int
    overflow: bool
    output_saturated: bool


def dot64_reference(x, w, bias, shift):
    """64 signed16 products -> add signed48 bias -> sat48 -> RNE -> sat32.

    raw is the saturated signed48 sum, overflow flags the 49-bit bias addition,
    and output_saturated flags only the final signed32 clipping.
    """
    shift = _shift(shift)
    x, w = list(x), list(w)
    if len(x) != 64 or len(w) != 64:
        raise ValueError("DOT64 requires exactly 64 x and 64 w values")
    bias = _scalar_in_range(bias, 48, "bias")
    dot = sum(_scalar_in_range(a, 16, "x") * _scalar_in_range(b, 16, "w")
              for a, b in zip(x, w))
    mathematical_sum = dot + bias
    raw = saturate_signed(mathematical_sum, 48)
    rounded = rshift_rne(raw, shift)
    output = saturate_signed(rounded, 32)
    return DotResult(raw, output, raw != mathematical_sum, output != rounded)


def _integer_array(value, bits, name):
    array = np.asarray(value)
    if array.dtype.kind not in "iu":
        raise TypeError(f"{name} must contain integers")
    if not array.size:
        raise ValueError(f"{name} must not be empty")
    lo, hi = -(1 << (bits - 1)), (1 << (bits - 1)) - 1
    # Compare before int64 conversion so uint64 outliers cannot wrap.
    if array.dtype.kind == "u":
        invalid = np.any(array > hi)
    else:
        invalid = np.any(array < lo) or np.any(array > hi)
    if invalid:
        raise ValueError(f"{name} does not fit signed {bits} bits")
    return array.astype(np.int64, copy=False)


@dataclass(frozen=True)
class MatrixResult:
    raw: np.ndarray
    output: np.ndarray
    overflow: np.ndarray
    output_saturated: np.ndarray
    int64_bound: int
    scalar_checks: int


def ffn1_reference(x, w, bias, shift):
    """Evaluate any positive M x 64 times 64 x N matrix using the DOT64 rule."""
    shift = _shift(shift)
    x, w = _integer_array(x, 16, "x"), _integer_array(w, 16, "w")
    bias = _integer_array(bias, 48, "bias")
    if x.ndim != 2 or w.ndim != 2 or bias.ndim != 1:
        raise ValueError("x/w must be matrices and bias must be a vector")
    if x.shape[1] != 64 or w.shape[0] != 64 or w.shape[1] != bias.size:
        raise ValueError("expected x[M,64], w[64,N], bias[N]")
    bound = 64 * max(abs(int(x.min())), abs(int(x.max()))) * max(abs(int(w.min())), abs(int(w.max())))
    bound += max(abs(int(bias.min())), abs(int(bias.max())))
    if bound > (1 << 63) - 1:
        raise OverflowError("matrix int64 mathematical bound is unsafe")
    mathematical_sum = x @ w + bias
    raw = np.clip(mathematical_sum, -(1 << 47), (1 << 47) - 1)
    if shift:
        magnitude = np.abs(raw)
        quotient = magnitude >> shift
        remainder = magnitude & ((1 << shift) - 1)
        half = 1 << (shift - 1)
        rounded_abs = quotient + ((remainder > half) | ((remainder == half) & ((quotient & 1) != 0)))
        rounded = np.where(raw < 0, -rounded_abs, rounded_abs)
    else:
        rounded = raw.copy()
    output = np.clip(rounded, -(1 << 31), (1 << 31) - 1).astype(np.int32)
    overflow = raw != mathematical_sum
    output_saturated = output.astype(np.int64) != rounded
    # Check corners and a deterministic spread, using Python sum/int/rshift.
    rows, cols = x.shape[0], w.shape[1]
    points = {(0, 0), (0, cols - 1), (rows - 1, 0), (rows - 1, cols - 1)}
    points.update((i * (rows - 1) // 7, (i * 37) % cols) for i in range(8))
    for row, col in sorted(points):
        scalar = dot64_reference(x[row], w[:, col], bias[col], shift)
        if (int(raw[row, col]), int(output[row, col]), bool(overflow[row, col]), bool(output_saturated[row, col])) != (
                scalar.raw, scalar.output, scalar.overflow, scalar.output_saturated):
            raise AssertionError("vectorized matrix differs from independent integer DOT64")
    return MatrixResult(raw, output, overflow, output_saturated, bound, len(points))


def _finite_real_array(value, name):
    array = np.asarray(value)
    if array.dtype.kind not in "fiu" or not array.size:
        raise ValueError(f"{name} must be a nonempty real numeric array")
    array = array.astype(np.float64)
    if not np.isfinite(array).all():
        raise ValueError(f"{name} must be finite")
    return array


def _scale_exponent(scale):
    if not isinstance(scale, (int, float, np.floating)) or isinstance(scale, bool):
        raise ValueError("scale must be a positive finite power of two")
    scale = float(scale)
    if not math.isfinite(scale) or scale <= 0 or math.frexp(scale)[0] != 0.5:
        raise ValueError("scale must be a positive finite power of two")
    return math.frexp(scale)[1] - 1


def quantize_signed(value, scale, bits):
    """RNE of finite real values / dyadic scale, then signed clipping.

    Returns (int64 array, counts). Float32 source and dyadic division are exact
    in float64 until well beyond the clipping bounds (bits <= 48).
    """
    bits = _integer(bits, "bits")
    if not 1 <= bits <= 48:
        raise ValueError("quantizer supports signed widths 1..48")
    exponent = _scale_exponent(scale)
    value = _finite_real_array(value, "value")
    with np.errstate(over="ignore", under="ignore", invalid="raise"):
        scaled = np.ldexp(value, -exponent)
        rounded = np.rint(scaled)
    lo, hi = -(1 << (bits - 1)), (1 << (bits - 1)) - 1
    saturated = (rounded < lo) | (rounded > hi)
    finite_scaled = scaled[np.isfinite(scaled)]
    ties = np.abs(finite_scaled - np.trunc(finite_scaled)) == 0.5
    result = np.clip(rounded, lo, hi).astype(np.int64)
    return result, {"elements": int(value.size), "saturated": int(saturated.sum()),
                    "rounded_ties": int(ties.sum()), "zeros": int((result == 0).sum())}


@dataclass(frozen=True)
class LayerConfig:
    input_scale: float
    weight_scale: float
    product_scale: float
    output_scale: float
    output_shift: int
    safe_raw_bound: int
    weight_q: np.ndarray
    bias_q: np.ndarray
    weight_stats: dict
    bias_stats: dict

    def metadata(self):
        return {"input_scale": self.input_scale, "weight_scale": self.weight_scale,
                "product_scale": self.product_scale, "output_scale": self.output_scale,
                "output_shift": self.output_shift, "safe_raw_bound": self.safe_raw_bound,
                "weight_stats": self.weight_stats, "bias_stats": self.bias_stats}


def derive_layer_config(weights, bias):
    """Derive range coverage from frozen W/b only; never inspect X or Y."""
    weights, bias = _finite_real_array(weights, "weights"), _finite_real_array(bias, "bias")
    if weights.ndim != 2 or weights.shape[0] != 64 or bias.shape != (weights.shape[1],):
        raise ValueError("expected weights[64,N] and bias[N]")
    maximum = float(np.max(np.abs(weights)))
    if maximum == 0:
        weight_scale = 1.0
    else:
        exponent = math.frexp(maximum)[1] - 15
        while maximum > math.ldexp(32767.0, exponent):
            exponent += 1
        while maximum <= math.ldexp(32767.0, exponent - 1):
            exponent -= 1
        weight_scale = math.ldexp(1.0, exponent)
    input_scale = 2.0 ** -8
    product_scale = input_scale * weight_scale
    if product_scale == 0 or not math.isfinite(product_scale):
        raise OverflowError("product scale is not representable")
    weight_q, weight_stats = quantize_signed(weights, weight_scale, 16)
    bias_q, bias_stats = quantize_signed(bias, product_scale, 48)
    if weight_stats["saturated"] or bias_stats["saturated"]:
        raise OverflowError("frozen weight/bias range cannot be represented")
    bound = 64 * 32768 * max(abs(int(weight_q.min())), abs(int(weight_q.max())))
    bound += max(abs(int(bias_q.min())), abs(int(bias_q.max())))
    if bound > (1 << 47) - 1:
        raise OverflowError("conservative raw range exceeds signed48 positive bound")
    shift = 0
    while rshift_rne(bound, shift) > (1 << 31) - 1:
        shift += 1
        if shift > 47:
            raise OverflowError("cannot represent output using shift<=47")
    return LayerConfig(input_scale, weight_scale, product_scale, product_scale * (1 << shift),
                       shift, bound, weight_q.astype(np.int16), bias_q, weight_stats, bias_stats)
