"""Signed fixed-point conversion and exact saturating integer linear model."""

import math
import numpy as np


def limits(bits):
    if not 2 <= bits <= 48:
        raise ValueError('Supported signed widths are 2..48 bits.')
    return -(1 << (bits-1)), (1 << (bits-1))-1


def fraction_bits(peak, bits, headroom=1.125):
    _, maximum = limits(bits)
    if not np.isfinite(peak) or peak < 0 or headroom < 1:
        raise ValueError('Invalid training peak/headroom.')
    if peak == 0:
        return bits-1
    fraction = int(math.floor(math.log2(maximum / (peak*headroom))))
    while math.ldexp(float(maximum), -fraction) < peak*headroom:
        fraction -= 1
    return fraction


def quantize(values, bits, fraction, rounding):
    values = np.asarray(values, dtype=np.float64)
    if not np.isfinite(values).all() or abs(fraction) > 48:
        raise ValueError('Invalid real data or scale.')
    low, high = limits(bits)
    scaled = np.ldexp(values, fraction)
    if rounding == 'rne':
        rounded = np.rint(scaled)
    elif rounding == 'tz':
        rounded = np.trunc(scaled)
    else:
        raise ValueError('Unknown rounding mode.')
    clips = int(np.count_nonzero((rounded < low) | (rounded > high)))
    return np.clip(rounded, low, high).astype(np.int64), clips


def round_shift(values, shift, rounding):
    values = np.asarray(values, dtype=np.int64)
    if not 0 <= shift <= 60 or np.any(values == np.iinfo(np.int64).min):
        raise ValueError('Invalid signed right shift.')
    if rounding not in ('rne', 'tz'):
        raise ValueError('Unknown rounding mode.')
    if shift == 0:
        return values.copy()
    magnitude = np.abs(values)
    quotient = magnitude >> shift
    if rounding == 'rne':
        remainder = magnitude & ((1 << shift)-1)
        half = 1 << (shift-1)
        quotient += ((remainder > half) | ((remainder == half) & ((quotient & 1) != 0)))
    return np.where(values < 0, -quotient, quotient)


def integer_linear(x, w, bias, accumulator_bits, output_shift, output_bits, rounding, x_bits):
    original = [np.asarray(a) for a in (x, w, bias)]
    if not all(np.issubdtype(a.dtype, np.signedinteger) for a in original):
        raise ValueError('Integer linear model requires signed integer operands.')
    x, w, bias = [np.asarray(a, dtype=np.int64) for a in original]
    if (x.ndim not in (2,3) or w.ndim != 2 or bias.ndim != 1 or
            x.shape[-1] != w.shape[0] or w.shape[1] != bias.shape[0] or
            not 1 <= w.shape[0] <= 1024):
        raise ValueError('Invalid integer linear shapes.')
    xlow, xhigh = limits(x_bits)
    if x_bits > 24 or np.any(x < xlow) or np.any(x > xhigh):
        raise ValueError('Input integer does not fit its declared width.')
    if np.any(w < -(1 << 30)) or np.any(w >= (1 << 30)) or np.any(bias < -(1 << 31)) or np.any(bias >= (1 << 31)):
        raise ValueError('Weight/bias outside supported exact host arithmetic bounds.')
    low, high = limits(accumulator_bits)
    olow, ohigh = limits(output_bits)
    bound = int(np.abs(w).sum(axis=0).max()) * (1 << (x_bits-1))
    prefix_safe = bound <= high
    saturations = 0
    if prefix_safe:
        # Every partial sum has magnitude <= bound, hence neither int64 nor
        # accumulator arithmetic can overflow. Integer matmul is exact here.
        accumulator = np.matmul(x, w)
    else:
        accumulator = np.zeros(x.shape[:-1] + (w.shape[1],), dtype=np.int64)
        for k in range(w.shape[0]):
            extended = accumulator + x[..., k, None] * w[k, :]
            saturations += int(np.count_nonzero((extended < low) | (extended > high)))
            accumulator = np.clip(extended, low, high)
    extended = accumulator + bias
    bias_clips = int(np.count_nonzero((extended < low) | (extended > high)))
    accumulator = np.clip(extended, low, high)
    converted = round_shift(accumulator, output_shift, rounding)
    output_clips = int(np.count_nonzero((converted < olow) | (converted > ohigh)))
    return np.clip(converted, olow, ohigh), dict(
        prefix_fast_path=bool(prefix_safe), full_input_range_prefix_bound=bound,
        full_input_range_with_bias_bound=bound+int(np.abs(bias).max()),
        accumulator_saturations=saturations, bias_saturations=bias_clips,
        output_saturations=output_clips)


def error_metrics(reference, decoded):
    reference, decoded = np.asarray(reference, dtype=np.float64), np.asarray(decoded, dtype=np.float64)
    if reference.shape != decoded.shape or not reference.size or not np.isfinite(reference).all() or not np.isfinite(decoded).all():
        raise ValueError('Error metrics require matching finite arrays.')
    error = decoded-reference
    sse = float(np.sum(error*error))
    energy = float(np.sum(reference*reference))
    nrmse = math.sqrt(sse/reference.size) / max(math.sqrt(energy/reference.size), 1e-8)
    return dict(squared_error=sse, reference_energy=energy, count=int(reference.size),
                nrmse=nrmse, max_abs_error=float(np.max(np.abs(error))))
