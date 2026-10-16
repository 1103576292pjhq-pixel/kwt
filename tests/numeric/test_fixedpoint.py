"""Independent integer expectations for the frozen prototype arithmetic."""
import numpy as np
import pytest

from numeric.fixedpoint import (
    dot64_reference, ffn1_reference, derive_layer_config,
    quantize_signed, rshift_rne, saturate_signed,
)


@pytest.mark.parametrize("value,shift,expected", [
    (3, 1, 2), (5, 1, 2), (-3, 1, -2), (-5, 1, -2),
    (7, 1, 4), (-7, 1, -4), (0, 47, 0),
    ((1 << 46), 47, 0), (3 * (1 << 46), 47, 2),
    (-3 * (1 << 46), 47, -2), (-(1 << 47), 0, -(1 << 47)),
    ((1 << 46) - 1, 47, 0), ((1 << 46) + 1, 47, 1),
])
def test_rne_independent_ties(value, shift, expected):
    assert rshift_rne(value, shift) == expected


@pytest.mark.parametrize("shift", [-1, 48, 1.0, True])
def test_bad_shifts(shift):
    with pytest.raises((TypeError, ValueError)):
        rshift_rne(3, shift)


@pytest.mark.parametrize("bits", [16, 32, 48])
def test_signed_saturation(bits):
    lo, hi = -(1 << (bits - 1)), (1 << (bits - 1)) - 1
    assert saturate_signed(lo - 1, bits) == lo
    assert saturate_signed(hi + 1, bits) == hi
    assert saturate_signed(lo, bits) == lo
    assert saturate_signed(hi, bits) == hi


def test_hand_dot_and_bias():
    result = dot64_reference([1, -2, 3] + [0] * 61,
                             [2, 4, -1] + [0] * 61, 1, 0)
    assert (result.raw, result.output, result.overflow, result.output_saturated) == (-8, -8, False, False)


def test_last_product_and_cancellation():
    assert dot64_reference([0] * 63 + [7], [0] * 63 + [-3], 2, 0).raw == -19
    x = [32767, -32767] * 32
    assert dot64_reference(x, [32767] * 64, -1, 0).raw == -1


def test_extreme_16_bit_product_and_output_saturation():
    result = dot64_reference([-32768] * 64, [-32768] * 64, 0, 0)
    assert result.raw == 68_719_476_736
    assert result.output == 2_147_483_647
    assert result.output_saturated and not result.overflow


@pytest.mark.parametrize("sign", [1, -1])
def test_49_bit_bias_add_saturates_48(sign):
    bias = (1 << 47) - 1 if sign == 1 else -(1 << 47)
    result = dot64_reference([sign] * 64, [1] * 64, bias, 47)
    assert result.raw == bias
    assert result.overflow
    assert result.output == sign
    assert not result.output_saturated


@pytest.mark.parametrize("x,w,b,shift", [
    ([0] * 63, [0] * 64, 0, 0),
    ([32768] * 64, [0] * 64, 0, 0),
    ([0] * 64, [1.0] * 64, 0, 0),
    ([0] * 64, [0] * 64, 1 << 47, 0),
    ([0] * 64, [0] * 64, 0, 48),
])
def test_dot_rejects_invalid_inputs(x, w, b, shift):
    with pytest.raises((TypeError, ValueError)):
        dot64_reference(x, w, b, shift)


def test_matrix_independent_expected_and_integer_types():
    x = np.zeros((2, 64), dtype=np.int16)
    w = np.zeros((64, 3), dtype=np.int16)
    x[0, :3], x[1, :3] = [1, -2, 3], [-1, 2, -3]
    w[:3, :] = [[2, 1, -1], [4, 1, -1], [-1, 1, -1]]
    result = ffn1_reference(x, w, np.array([1, 0, -1], dtype=np.int64), 0)
    assert result.output.tolist() == [[-8, 2, -3], [10, -2, 1]]
    assert result.raw.dtype == np.int64
    assert not result.overflow.any()


@pytest.mark.parametrize("kind", ["shape", "float", "range", "bias"])
def test_matrix_rejects_invalid_inputs(kind):
    x, w, b = np.zeros((1, 64), dtype=np.int16), np.zeros((64, 1), dtype=np.int16), np.zeros(1, dtype=np.int64)
    if kind == "shape":
        x = x[:, :-1]
    elif kind == "float":
        w = w.astype(float)
    elif kind == "range":
        x = np.full((1, 64), 32768, dtype=np.int64)
    else:
        b[0] = 1 << 47
    with pytest.raises((TypeError, ValueError)):
        ffn1_reference(x, w, b, 0)


def test_quantizer_ties_saturation_and_nonfinite():
    q, stats = quantize_signed(np.array([1.5, 2.5, -1.5, -2.5, 40000.0]), 1.0, 16)
    assert q.tolist() == [2, 2, -2, -2, 32767]
    assert stats["saturated"] == 1
    assert stats["rounded_ties"] == 4
    for data in [np.array([np.nan]), np.array([np.inf])]:
        with pytest.raises(ValueError):
            quantize_signed(data, 1.0, 16)
    for scale in [0, -1, np.inf, np.nan, 0.3]:
        with pytest.raises(ValueError):
            quantize_signed(np.array([0.0]), scale, 16)


def test_zero_weights_and_deterministic_conservative_shift():
    cfg = derive_layer_config(np.zeros((64, 2)), np.array([0.0, 1.0]))
    assert cfg.weight_scale == 1.0
    assert cfg.input_scale == 1 / 256
    assert cfg.output_shift == 0
    assert cfg.bias_q.tolist() == [0, 256]
    # max|Qw|=16384; 64*32768*16384 needs a right shift of 5
    cfg = derive_layer_config(np.full((64, 1), 0.5), np.zeros(1))
    assert cfg.weight_scale == 2 ** -15
    assert cfg.output_shift == 5
    assert cfg.safe_raw_bound == 34_359_738_368
    assert cfg.output_scale == cfg.input_scale * cfg.weight_scale * (1 << cfg.output_shift)


def test_config_rejects_bad_shapes_nonfinite_and_huge_bias():
    for w, b in [(np.zeros((63, 1)), np.zeros(1)),
                 (np.zeros((64, 1)), np.zeros(2)),
                 (np.full((64, 1), np.nan), np.zeros(1)),
                 (np.zeros((64, 1)), np.array([1e30]))]:
        with pytest.raises((ValueError, OverflowError)):
            derive_layer_config(w, b)


def test_matrix_matches_49_bit_bias_add_and_rne_extremes():
    x = np.ones((1, 64), dtype=np.int16)
    w = np.stack([np.ones(64), -np.ones(64)], axis=1).astype(np.int16)
    b = np.array([(1 << 47) - 1, -(1 << 47)], dtype=np.int64)
    result = ffn1_reference(x, w, b, 47)
    assert result.raw.tolist() == [[(1 << 47) - 1, -(1 << 47)]]
    assert result.output.tolist() == [[1, -1]]
    assert result.overflow.tolist() == [[True, True]]
    assert not result.output_saturated.any()


def test_rne_against_independent_exact_fraction_rounding():
    from fractions import Fraction
    from random import Random
    rng = Random(20261015)
    for shift in range(48):
        for _ in range(20):
            value = rng.randrange(-(1 << 48), 1 << 48)
            assert rshift_rne(value, shift) == round(Fraction(value, 1 << shift))


@pytest.mark.parametrize("maximum", [1.0, 32767.0, 32768.0, 0.5, 2 ** -20])
def test_weight_scale_is_minimal_covering_power_of_two(maximum):
    cfg = derive_layer_config(np.full((64, 1), maximum), np.zeros(1))
    assert maximum <= 32767 * cfg.weight_scale
    assert maximum > 32767 * (cfg.weight_scale / 2)
    assert cfg.weight_stats["saturated"] == 0
