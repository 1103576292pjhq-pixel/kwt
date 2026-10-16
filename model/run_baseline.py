"""Run frozen official KWT-1 and export each actual FFN1 input/output.

Uses the original graph/session implementation. No vendor code is changed.
Dense.call is temporarily observed during graph construction; the returned
tensor is passed through unchanged. A separately built, restored graph with
no hook provides authoritative logits/MFCC. Its built official layer objects
are replayed for intermediate references, with exact final-logit equality.
"""
import argparse
from contextlib import contextmanager
import hashlib
import json
import os
from pathlib import Path
import platform
import sys
import wave

WORKSPACE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(WORKSPACE))
os.environ.setdefault("CUDA_VISIBLE_DEVICES", "-1")
os.environ.setdefault("TF_CPP_MIN_LOG_LEVEL", "2")
os.environ.setdefault("TF_DETERMINISTIC_OPS", "1")
os.environ.setdefault("PYTHONDONTWRITEBYTECODE", "1")
sys.dont_write_bytecode = True

import numpy as np
from model.contracts import (INFERENCE_OVERRIDES, SOURCE_COMMIT, compare_arrays, ffn1_numpy,
                             sha256_file, validate_official_flags, write_ffn1_case)


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False, sort_keys=True) + "\n", encoding="utf-8")


def verify_sources(vendor):
    source_path = WORKSPACE / "config/source-manifest.json"
    source = json.loads(source_path.read_text(encoding="utf-8"))
    if source["commit"] != SOURCE_COMMIT:
        raise ValueError("source manifest commit mismatch")
    for item in source["files"]:
        if sha256_file(vendor / item["path"]) != item["sha256"]:
            raise ValueError("immutable source SHA-256 mismatch: " + item["path"])
    return {"manifest_sha256": sha256_file(source_path), "file_count": len(source["files"]),
            "commit": SOURCE_COMMIT, "repository": source["repository"],
            "files_sha256": {item["path"]: item["sha256"] for item in source["files"]}}


def official_flags(vendor):
    # Import only the inference/model path. train.py imports transformers.
    sys.path.insert(0, str(vendor))
    from kws_streaming.train import base_parser
    # Official test entry loads the registry before the transformer. Directly
    # importing the transformer first creates utils -> registry -> transformer
    # circular initialization and accesses .model before it exists.
    from kws_streaming.models import model_flags, models
    from kws_streaming.models import kws_transformer
    if models.MODELS["kws_transformer"] is not kws_transformer.model:
        raise ValueError("official model registry entry mismatch")
    parser = base_parser.base_parser()
    kws_transformer.model_parameters(parser)
    flags = parser.parse_args([])
    checkpoint_dir = vendor / "models_data_v2_12_labels/kwt1"
    saved = json.loads((checkpoint_dir / "flags.json").read_text(encoding="utf-8"))
    flags.__dict__.update(saved)
    overrides = dict(INFERENCE_OVERRIDES)
    flags.__dict__.update(overrides)
    flags = model_flags.update_flags(flags)
    validate_official_flags(vars(flags))
    return flags, overrides, kws_transformer


def load_samples(data_root, flags, include_silence):
    from kws_streaming.data import input_data
    import tensorflow as tf
    source_path = data_root / "manifest.json"
    source = json.loads(source_path.read_text(encoding="utf-8"))
    samples = []
    for item in source["samples"]:
        path = (data_root / item["relative_path"]).resolve()
        if data_root.resolve() not in path.parents:
            raise ValueError("sample path escapes data root")
        if item["partition"] != "validation" or input_data.which_set(
                str(path), flags.validation_percentage, flags.testing_percentage) != "validation":
            raise ValueError("sample is not official validation: " + str(path))
        if sha256_file(path) != item["sha256"]:
            raise ValueError("sample SHA-256 mismatch: " + str(path))
        with wave.open(str(path), "rb") as wav:
            if (wav.getframerate(), wav.getnchannels(), wav.getsampwidth()) != (16000, 1, 2):
                raise ValueError("sample WAV must be 16kHz mono PCM16")
            original_samples = wav.getnframes()
        # Execute the official processing methods without the constructor's
        # dataset download/indexing side effects. Its graph alone is sufficient
        # for no-augmentation inference on a provenance-checked subset WAV.
        with tf.Graph().as_default(), tf.compat.v1.Session() as session:
            processor = object.__new__(input_data.AudioProcessor)
            processor.prepare_processing_graph(flags)
            audio = processor.get_features_for_wav(str(path), flags, session)[0]
        sample_id = item["word"] + "_" + path.stem
        samples.append({"sample_id": sample_id, "source_sample_id": item["sample_id"],
                        "partition": "validation", "word": item["word"],
                        "relative_path": item["relative_path"], "sample_sha256": item["sha256"],
                        "original_samples": original_samples, "audio": audio.reshape(1, -1)})
    if len(samples) < 2:
        raise ValueError("baseline needs at least two real validation samples")
    if len({s["sample_id"] for s in samples}) != len(samples):
        raise ValueError("duplicate sample_id")
    if include_silence:
        audio = np.zeros((1, flags.desired_samples), dtype=np.float32)
        samples.append({"sample_id": "synthetic_zero_silence", "partition": "synthetic_silence",
                        "word": "_silence_", "sample_sha256": hashlib.sha256(audio.tobytes()).hexdigest(),
                        "definition": "Official silence behavior: foreground_volume=0, no background; all-zero raw audio",
                        "audio": audio})
    return samples, {"manifest_sha256": sha256_file(source_path),
                     "dataset": source["dataset"], "version": source["version"],
                     "dataset_url": source["dataset_url"], "partition_basis": source["partition_basis"],
                     "selection": source["selection"], "archive_integrity": source["archive_integrity"]}


@contextmanager
def observe_dense(tf, captured, normalized):
    original = tf.keras.layers.Dense.call
    original_norm = tf.keras.layers.LayerNormalization.call

    def call(layer, inputs):
        outputs = original(layer, inputs)
        if layer.units == 256 and inputs.shape[-1] == 64:
            captured[layer] = (inputs, outputs)
        return outputs

    def normalization_call(layer, inputs):
        outputs = original_norm(layer, inputs)
        normalized[layer] = outputs
        return outputs

    tf.keras.layers.Dense.call = call
    tf.keras.layers.LayerNormalization.call = normalization_call
    try:
        yield
    finally:
        tf.keras.layers.Dense.call = original
        tf.keras.layers.LayerNormalization.call = original_norm


def official_layer_replay(tf, model, transformer):
    """Reuse original objects; the original full model remains authoritative.

    Nested subclass layers expose no Keras inbound node in this TF1 graph.
    To obtain a no-hook intermediate reference, reconstruct only token setup
    and each block's attention/residual/LN1 expression using its actual objects.
    Propagate state through the complete original block call (FFN2, residual,
    LN2 included), never through the exported FFN1 Y.
    """
    before = [id(weight) for weight in tf.compat.v1.global_variables()]
    features = model.layers[1].output
    x = transformer.patch_proj(features)
    class_token = tf.broadcast_to(transformer.class_emb, [tf.shape(x)[0], 1, transformer.d_model])
    x = tf.concat([class_token, x], axis=1) + transformer.pos_emb
    layers = []
    for block in transformer.enc_layers:
        if block.prenorm:
            raise ValueError("official replay only accepts the contracted PostNorm architecture")
        attention, _ = block.att(x)
        attention = block.dropout1(attention, training=False)
        out1 = block.layernorm1(x + attention)
        y = block.ffn.layers[0](out1)
        layers.append((out1, y))
        x, _ = block(x, training=False)
    heads = [layer for layer in model.layers if isinstance(layer, tf.keras.Sequential)]
    if len(heads) != 1 or len(heads[0].layers) != 1 or heads[0].layers[0].units != 12:
        raise ValueError("official replay requires the original single classification head")
    logits = heads[0](x[:, 0])
    if before != [id(weight) for weight in tf.compat.v1.global_variables()]:
        raise ValueError("official-layer replay unexpectedly created new model variables")
    return logits, layers


def restore_and_verify(tf, session, model, checkpoint):
    # Initialize first, then perform restore ops; never initialize after restore.
    session.run(tf.compat.v1.global_variables_initializer())
    initial = session.run(model.weights)
    status = model.load_weights(str(checkpoint))
    status.assert_existing_objects_matched()
    status.run_restore_ops(session=session)
    restored = session.run(model.weights)
    reader = tf.train.load_checkpoint(str(checkpoint))
    # Pinned TF 2.4 checkpoint internals expose the object->checkpoint mapping.
    # This independent reader check proves every live model variable equals its
    # stored value; assert_existing_objects_matched alone is insufficient.
    tracked = status._checkpoint
    objects = {id(obj): node for node, obj in tracked.object_by_proto_id.items()}
    verified = []
    for weight, before, after in zip(model.weights, initial, restored):
        node_id = objects.get(id(weight))
        if node_id is None:
            raise ValueError("model variable missing in checkpoint mapping: " + weight.name)
        node = tracked.object_graph_proto.nodes[node_id]
        attrs = [attr for attr in node.attributes if attr.name == "VARIABLE_VALUE"]
        if len(attrs) != 1:
            raise ValueError("ambiguous checkpoint mapping: " + weight.name)
        key = attrs[0].checkpoint_key
        stored = reader.get_tensor(key)
        if not np.isfinite(after).all() or not np.array_equal(after, stored):
            raise ValueError("checkpoint tensor did not restore exactly: " + weight.name)
        verified.append({"variable": weight.name, "checkpoint_key": key,
                         "shape": list(after.shape), "dtype": str(after.dtype),
                         "checkpoint_max_abs_error": 0.0,
                         "changed_from_initial": not np.array_equal(before, after)})
    changed = sum(item["changed_from_initial"] for item in verified)
    if changed == 0:
        raise ValueError("checkpoint restore left every variable at initialization")
    # Keras saved training optimizer state can be absent from inference model.
    # Partial checkpoint *extras* are permitted only after all model vars passed.
    try:
        status.assert_consumed()
        fully_consumed = True
    except AssertionError:
        fully_consumed = False
        status.expect_partial()
    return {"assert_existing_objects_matched": True, "all_model_variables_exact": True,
            "variable_count": len(verified), "changed_variable_count": changed,
            "checkpoint_fully_consumed": fully_consumed, "variables": verified}


def execute_graph(flags, official_model, checkpoint, samples, hooked):
    import tensorflow as tf
    tf.keras.backend.clear_session()
    graph = tf.Graph()
    config = tf.compat.v1.ConfigProto(intra_op_parallelism_threads=1, inter_op_parallelism_threads=1,
                                     device_count={"GPU": 0})
    with graph.as_default(), tf.compat.v1.Session(graph=graph, config=config) as session:
        tf.compat.v1.keras.backend.set_session(session)
        tf.compat.v1.keras.backend.set_learning_phase(0)
        tf.compat.v1.set_random_seed(1234)
        captured = {}
        normalized = {}
        if hooked:
            with observe_dense(tf, captured, normalized):
                model = official_model.model(flags)
        else:
            model = official_model.model(flags)
        transformers = [layer for layer in model.layers if hasattr(layer, "enc_layers")]
        if len(transformers) != 1 or len(transformers[0].enc_layers) != 12:
            raise ValueError("official model must contain one 12-layer time transformer")
        transformer = transformers[0]
        replay_logits, replay_layers = official_layer_replay(tf, model, transformer)
        tensors = [model.outputs[0], model.layers[1].output, replay_logits]
        kernels = []
        for block, (replay_x, replay_y) in zip(transformer.enc_layers, replay_layers):
            dense = block.ffn.layers[0]
            if hooked:
                if dense not in captured:
                    raise ValueError("FFN1 Dense hook did not capture a layer")
                x, y = captured[dense]
                if block.layernorm1 not in normalized:
                    raise ValueError("LN1 hook did not capture a layer")
                ln1 = normalized[block.layernorm1]
            else:
                x, y, ln1 = replay_x, replay_y, replay_x
            tensors.extend([x, y, ln1, replay_x, replay_y])
            kernels.extend([dense.kernel, dense.bias])
        if hooked and len(captured) != 12:
            raise ValueError("FFN1 hook captured unexpected Dense count")
        restored = restore_and_verify(tf, session, model, checkpoint)
        key_by_name = {item["variable"]: item["checkpoint_key"] for item in restored["variables"]}
        restored["ffn1_checkpoint_keys"] = [{"layer": index, "W": key_by_name[block.ffn.layers[0].kernel.name],
                                             "b": key_by_name[block.ffn.layers[0].bias.name]}
                                            for index, block in enumerate(transformer.enc_layers, 1)]
        parameters = session.run(kernels)
        results = []
        for sample in samples:
            values = session.run(tensors, feed_dict={model.inputs[0]: sample["audio"]})
            for value in values + parameters:
                if not np.isfinite(value).all():
                    raise ValueError("nonfinite official model tensor")
            if values[1].shape != (1, 98, 40):
                raise ValueError("official MFCC shape differs from (1,98,40)")
            replay_check = compare_arrays(values[2], values[0], atol=0.0, rtol=0.0)
            layers = []
            for index in range(12):
                x, y, ln1, replay_x, replay_y = values[3 + 5 * index:8 + 5 * index]
                compare_arrays(x, ln1, atol=0.0, rtol=0.0)
                compare_arrays(x, replay_x, atol=0.0, rtol=0.0)
                compare_arrays(y, replay_y, atol=0.0, rtol=0.0)
                layers.append({"X": x[0], "W": parameters[2 * index],
                               "b": parameters[2 * index + 1], "Y": y[0]})
            results.append({"logits": values[0][0], "mfcc": values[1][0], "layers": layers,
                            "official_layer_replay_logits_comparison": replay_check})
        return results, restored


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=WORKSPACE / "reports/model/baseline")
    parser.add_argument("--include-silence", action="store_true")
    args = parser.parse_args()
    output = args.output.resolve()
    if (WORKSPACE / "reports/model").resolve() not in output.parents:
        raise ValueError("output must be a subdirectory of workspace reports/model")
    output.mkdir(parents=True, exist_ok=True)
    for stale in ("manifest.json", "verification.json", "SUMMARY.md"):
        path = output / stale
        if path.exists():
            path.unlink()
    import tensorflow as tf
    if tf.__version__ != "2.4.0":
        raise ValueError("baseline runtime must match the explicit TensorFlow 2.4.0 compatibility contract")
    vendor = WORKSPACE / "vendor/keyword-transformer"
    source = verify_sources(vendor)
    print("Source SHA-256 checks: {} frozen files".format(source["file_count"]), flush=True)
    flags, overrides, builder = official_flags(vendor)
    samples, dataset = load_samples(WORKSPACE / "data/speech_commands_subset", flags, args.include_silence)
    checkpoint_dir = vendor / "models_data_v2_12_labels/kwt1"
    checkpoint = checkpoint_dir / "best_weights"
    checkpoint_hashes = {p.name: sha256_file(p) for p in sorted(checkpoint_dir.glob("best_weights.*"))}
    labels = (checkpoint_dir / "labels.txt").read_text(encoding="utf-8").splitlines()
    from kws_streaming.data import input_data
    if labels != input_data.prepare_words_list(flags.wanted_words.split(","), flags.split_data):
        raise ValueError("official labels disagree with model flags")
    print("Running official model, no hook", flush=True)
    reference, reference_restore = execute_graph(flags, builder, checkpoint, samples, hooked=False)
    print("Running official model with temporary Dense observation", flush=True)
    captured, captured_restore = execute_graph(flags, builder, checkpoint, samples, hooked=True)
    output.mkdir(parents=True, exist_ok=True)
    manifest = {"schema_version": 1, "status": "verified", "quantized": False, "rtl": False,
                "source": source, "checkpoint_sha256": checkpoint_hashes, "labels": labels,
                "label_sha256": sha256_file(checkpoint_dir / "labels.txt"),
                "flags_sha256": sha256_file(checkpoint_dir / "flags.json"),
                "contract_sha256": sha256_file(WORKSPACE / "config/model-contract.json"),
                "flags": vars(flags), "inference_overrides": overrides, "dataset": dataset,
                "audio_preprocessing": {"source_method": "kws_streaming.data.input_data.AudioProcessor.prepare_processing_graph + get_features_for_wav",
                                        "PCM16_scale": 32768, "desired_samples": 16000,
                                        "foreground_volume": 1.0, "foreground_resampling": 1.0,
                                        "time_shift": 0, "background_volume": 0.0},
                "restore": reference_restore, "hook_restore": captured_restore,
                "intermediate_reference_method": "Same-object official-layer replay without hooks; state propagation calls each full original block; replay final logits exactly equal original unhook complete model",
                "samples": [], "cases": [],
                "scope": "Float32 software baseline; subset predictions only; no full dataset accuracy, quantization or RTL claims"}
    for sample, plain, hooked in zip(samples, reference, captured):
        item = {key: value for key, value in sample.items() if key != "audio"}
        predicted = int(np.argmax(plain["logits"]))
        item.update(predicted_index=predicted, predicted_label=labels[predicted],
                    ground_truth_label=sample["word"] if sample["word"] in labels else "_unknown_",
                    logits=plain["logits"].tolist(),
                    hook_logits_comparison=compare_arrays(hooked["logits"], plain["logits"], 0.0, 0.0),
                    hook_mfcc_comparison=compare_arrays(hooked["mfcc"], plain["mfcc"], 0.0, 0.0))
        item["unhook_official_layer_replay_logits_comparison"] = plain["official_layer_replay_logits_comparison"]
        item["hook_official_layer_replay_logits_comparison"] = hooked["official_layer_replay_logits_comparison"]
        sample_dir = output / "samples" / sample["sample_id"]
        sample_dir.mkdir(parents=True, exist_ok=True)
        for name, array in (("audio", sample["audio"][0]), ("mfcc", plain["mfcc"]), ("logits", plain["logits"])):
            path = sample_dir / (name + ".npy")
            np.save(str(path), array, allow_pickle=False)
            item[name + "_array"] = {"path": path.relative_to(output).as_posix(), "sha256": sha256_file(path),
                                     "shape": list(array.shape), "dtype": str(array.dtype)}
        provenance = {"sample_id": sample["sample_id"], "partition": sample["partition"],
                      "sample_sha256": sample["sample_sha256"], "source_commit": SOURCE_COMMIT,
                      "source_manifest_sha256": source["manifest_sha256"], "checkpoint_sha256": checkpoint_hashes}
        for index, (plain_layer, hook_layer) in enumerate(zip(plain["layers"], hooked["layers"]), 1):
            comparisons = {name: compare_arrays(hook_layer[name], plain_layer[name], 0.0, 0.0)
                           for name in ("X", "W", "b", "Y")}
            case = write_ffn1_case(output, index, hook_layer, provenance)
            case["export_origin"] = "Original complete model Dense.call observation, checked against no-hook same-object official-layer replay"
            case["checkpoint_keys"] = {key: reference_restore["ffn1_checkpoint_keys"][index - 1][key] for key in ("W", "b")}
            case["hook_comparison"] = comparisons
            case["numpy_comparison"] = compare_arrays(ffn1_numpy(plain_layer["X"], plain_layer["W"], plain_layer["b"]),
                                                      plain_layer["Y"], 1e-5, 1e-5)
            manifest["cases"].append(case)
        manifest["samples"].append(item)
        print("Exported {}: prediction={} [{}]".format(sample["sample_id"], labels[predicted], sample["partition"]), flush=True)
    import tensorflow as tf
    import tensorflow_addons as tfa
    manifest["runtime"] = {"requested_tensorflow": "2.4.0rc1", "installed_tensorflow": tf.__version__,
                           "compatibility_note": "Upstream rc1 wheel unavailable on checked current indices; closest stable 2.4.0 used without source/checkpoint changes. No rc1 bit-equality claim."}
    write_json(output / "environment.json", {"python": platform.python_version(), "platform": platform.platform(),
                                             "tensorflow": tf.__version__, "tensorflow_addons": tfa.__version__,
                                             "numpy": np.__version__, "cpu_threads": 1, "gpu": False})
    manifest["environment_sha256"] = sha256_file(output / "environment.json")
    write_json(output / "manifest.json", manifest)
    write_json(output / "restore-verification.json", reference_restore)
    write_json(output / "effective-flags.json", vars(flags))
    print("Baseline artifacts: {}".format(output), flush=True)


if __name__ == "__main__":
    main()
