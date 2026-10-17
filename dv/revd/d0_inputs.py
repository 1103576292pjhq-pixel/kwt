"""Validated frozen-vector loading and public tile-order conversion.

No source arrays are rewritten. New tile storage is [tile, k*16+j].
"""
import json
from pathlib import Path

import numpy as np

from numeric.artifacts import load_array, verify_vectors


def repack_weights(weights, bias, packed=None):
    if not isinstance(weights, np.ndarray) or weights.dtype != np.dtype("int16"):
        raise ValueError("weight dtype must be int16")
    if weights.ndim != 2 or weights.shape[0] != 64 or not 16 <= weights.shape[1] <= 256 or weights.shape[1] % 16:
        raise ValueError("weight shape must be [64,N], N=16..256 multiple of16")
    n = weights.shape[1]
    if not isinstance(bias, np.ndarray) or bias.dtype != np.dtype("int64"):
        raise ValueError("bias dtype must be int64")
    if bias.shape != (n,):
        raise ValueError("bias shape must be [N]")
    if np.any(bias < -(1 << 47)) or np.any(bias >= (1 << 47)):
        raise ValueError("bias outside signed48")
    if packed is not None:
        if not isinstance(packed, np.ndarray) or packed.dtype != np.dtype("int16"):
            raise ValueError("packed dtype must be int16")
        if packed.shape != (n, 64):
            raise ValueError("packed shape must be [N,64]")
        if not np.array_equal(packed.T, weights):
            raise ValueError("packed n*64+k differs from mathematical W[k,n]")
    tiles = np.stack([weights[:, nt:nt + 16].reshape(1024) for nt in range(0, n, 16)])
    return tiles, bias.reshape(n // 16, 16).copy()


def verify_frozen_inputs(workspace):
    workspace = Path(workspace).resolve()
    result = verify_vectors(workspace, workspace / "reports/model/baseline",
                            workspace / "reports/prototype/vectors")
    manifest = json.loads((workspace / "reports/prototype/vectors/manifest.json").read_text(encoding="utf-8"))
    return manifest, result


def validated_case(workspace, case):
    """Load hash/shape/dtype checked arrays after verify_frozen_inputs at run start."""
    root = Path(workspace).resolve() / "reports/prototype/vectors"
    specification = {"Xq": ((99, 64), "int16"), "Wq": ((64, 256), "int16"),
                     "Wq_packed": ((256, 64), "int16"), "bq": ((256,), "int64"),
                     "Yq": ((99, 256), "int32"), "raw48": ((99, 256), "int64"),
                     "overflow": ((99, 256), "bool"), "output_saturated": ((99, 256), "bool")}
    data = {name: load_array(root, case["arrays"][name], shape, dtype)
            for name, (shape, dtype) in specification.items()}
    data["W_tiles"], data["b_tiles"] = repack_weights(data["Wq"], data["bq"], data["Wq_packed"])
    return data
