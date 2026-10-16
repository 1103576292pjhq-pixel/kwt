"""Frozen integer arithmetic for the platform-independent FFN1 prototype."""

from .fixedpoint import (
    DotResult, MatrixResult, LayerConfig, derive_layer_config,
    dot64_reference, ffn1_reference, quantize_signed, rshift_rne, saturate_signed,
)

__all__ = [
    "DotResult", "MatrixResult", "LayerConfig", "derive_layer_config",
    "dot64_reference", "ffn1_reference", "quantize_signed", "rshift_rne",
    "saturate_signed",
]
