"""Pure NumPy checks for FFN1 data and its auditable artifact envelope."""
import hashlib
import json
from pathlib import Path
import re

import numpy as np

SOURCE_COMMIT = "237e4097afd4f6851e0b82f0a8d65c2dfe8eae30"
SHAPES = {"X": (99, 64), "W": (64, 256), "b": (256,), "Y": (99, 256)}
STAGE = "ffn1_dense_pre_gelu"
INFERENCE_OVERRIDES = {
    "batch_size": 1, "training": False, "train": 0,
    "use_spec_augment": 0, "use_spec_cutout": 0,
    "time_shift_ms": 0.0, "sp_time_shift_ms": 0.0,
    "resample": 0.0, "sp_resample": 0.0, "volume_resample": 0.0,
    "background_frequency": 0.0, "background_volume": 0.0,
    "distill_teacher_json": "",
}


def validate_official_flags(flags):
    required = {
        "model_name": "kws_transformer", "num_layers": 12,
        "d_model": 64, "mlp_dim": 256, "heads": 1,
        "prenorm": False, "distill_teacher_json": "", "attention_type": "time",
        "preprocess": "raw", "feature_type": "mfcc_tf",
        "sample_rate": 16000, "desired_samples": 16000,
        "window_size_samples": 480, "window_stride_samples": 160,
        "spectrogram_length": 98, "dct_num_features": 40, "label_count": 12,
        "approximate_gelu": False, "return_softmax": 0, "dropout1": 0.0,
        "window_type": "hann", "preemph": 0.0,
        "mel_num_bins": 80, "mel_lower_edge_hertz": 20.0,
        "mel_upper_edge_hertz": 7600.0, "log_epsilon": 1e-12,
        "fft_magnitude_squared": False, "use_tf_fft": 0, "mel_non_zero_only": 1,
        "data_frame_padding": None, "data_stride": 1,
        "wanted_words": "yes,no,up,down,left,right,on,off,stop,go",
        "validation_percentage": 10, "testing_percentage": 10,
    }
    for name, value in required.items():
        if flags.get(name) != value:
            raise ValueError("{} must be {!r}, got {!r}".format(name, value, flags.get(name)))


def sha256_file(path):
    digest = hashlib.sha256()
    with Path(path).open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def ffn1_numpy(x, w, b):
    x, w, b = np.asarray(x), np.asarray(w), np.asarray(b)
    if x.ndim != 2 or w.ndim != 2 or b.ndim != 1:
        raise ValueError("FFN1 shape requires rank-2 X/W and rank-1 bias")
    if x.shape[1] != w.shape[0] or b.shape != (w.shape[1],):
        raise ValueError("incompatible FFN1 shape")
    if not all(np.isfinite(item).all() for item in (x, w, b)):
        raise ValueError("FFN1 arrays must be finite")
    return x @ w + b


def validate_ffn1_arrays(arrays):
    if set(arrays) != set(SHAPES):
        raise ValueError("FFN1 requires exactly X, W, b, Y")
    for name, shape in SHAPES.items():
        array = np.asarray(arrays[name])
        if array.shape != shape:
            raise ValueError("{} shape {} != {}".format(name, array.shape, shape))
        if array.dtype != np.dtype("float32"):
            raise ValueError("{} must use float32, got {}".format(name, array.dtype))
        if not np.isfinite(array).all():
            raise ValueError("{} must contain finite values".format(name))


def compare_arrays(actual, reference, atol, rtol):
    actual, reference = np.asarray(actual), np.asarray(reference)
    if actual.shape != reference.shape:
        raise ValueError("comparison shape mismatch")
    if not np.isfinite(actual).all() or not np.isfinite(reference).all():
        raise ValueError("comparison requires finite values")
    delta = actual.astype(np.float64) - reference.astype(np.float64)
    rmse = float(np.sqrt(np.mean(delta * delta)))
    scale = float(np.sqrt(np.mean(reference.astype(np.float64) ** 2)))
    metrics = {
        "max_abs_error": float(np.max(np.abs(delta))),
        "rmse": rmse,
        "nrmse": rmse / max(scale, 1e-8),
        "nrmse_denominator_floor": 1e-8,
        "atol": float(atol), "rtol": float(rtol),
    }
    if not np.allclose(actual, reference, atol=atol, rtol=rtol):
        raise ValueError("numeric tolerance failed: {}".format(metrics))
    return metrics


def validate_provenance(provenance):
    if provenance.get("partition") not in ("validation", "synthetic_silence"):
        raise ValueError("partition must be validation or synthetic_silence")
    if not re.fullmatch(r"[A-Za-z0-9._-]+", provenance.get("sample_id", "")):
        raise ValueError("sample_id must be a safe nonempty filename")
    if provenance.get("source_commit") != SOURCE_COMMIT:
        raise ValueError("source_commit differs from frozen official source")
    if not re.fullmatch(r"[a-f0-9]{64}", provenance.get("sample_sha256", "")):
        raise ValueError("sample_sha256 is required")
    hashes = provenance.get("checkpoint_sha256", {})
    if not hashes or not all(re.fullmatch(r"[a-f0-9]{64}", value) for value in hashes.values()):
        raise ValueError("checkpoint_sha256 is required")


def write_ffn1_case(root, layer, arrays, provenance):
    validate_ffn1_arrays(arrays)
    validate_provenance(provenance)
    if not isinstance(layer, int) or not 1 <= layer <= 12:
        raise ValueError("layer must be in 1..12")
    root = Path(root)
    directory = root / "cases" / provenance["sample_id"] / "layer_{:02d}".format(layer)
    directory.mkdir(parents=True, exist_ok=True)
    metadata = dict(provenance, layer=layer, stage=STAGE, arrays={})
    for name, array in arrays.items():
        path = directory / (name + ".npy")
        np.save(str(path), array, allow_pickle=False)
        metadata["arrays"][name] = {
            "path": path.relative_to(root).as_posix(),
            "sha256": sha256_file(path),
            "shape": list(array.shape), "dtype": str(array.dtype),
        }
    return metadata


def verify_ffn1_case(root, metadata):
    validate_provenance(metadata)
    if metadata.get("stage") != STAGE:
        raise ValueError("unexpected FFN1 stage")
    if metadata.get("layer") not in range(1, 13):
        raise ValueError("layer must be in 1..12")
    root = Path(root).resolve()
    arrays = {}
    for name, descriptor in metadata.get("arrays", {}).items():
        path = (root / descriptor["path"]).resolve()
        if root not in path.parents:
            raise ValueError("array path must stay inside artifact root")
        expected = "cases/{}/layer_{:02d}/{}.npy".format(metadata["sample_id"], metadata["layer"], name)
        if descriptor["path"] != expected:
            raise ValueError("array layer path does not match its sample and layer")
        if sha256_file(path) != descriptor["sha256"]:
            raise ValueError("{} SHA-256 mismatch".format(name))
        array = np.load(str(path), allow_pickle=False)
        if list(array.shape) != descriptor["shape"] or str(array.dtype) != descriptor["dtype"]:
            raise ValueError("{} metadata shape/dtype mismatch".format(name))
        arrays[name] = array
    validate_ffn1_arrays(arrays)
    return arrays
