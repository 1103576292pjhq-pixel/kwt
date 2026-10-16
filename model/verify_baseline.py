"""Read back FFN1 artifacts, recompute their checks, and compare repeat runs."""
import argparse
import json
from pathlib import Path
import sys
import wave

WORKSPACE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(WORKSPACE))

import numpy as np
from model.contracts import (INFERENCE_OVERRIDES, SOURCE_COMMIT, compare_arrays, ffn1_numpy, sha256_file,
                             validate_official_flags, verify_ffn1_case)


def load_array(root, descriptor, shape):
    path = (root / descriptor["path"]).resolve()
    if root.resolve() not in path.parents:
        raise ValueError("sample array path escapes artifact root")
    if sha256_file(path) != descriptor["sha256"]:
        raise ValueError("sample array SHA-256 mismatch")
    array = np.load(str(path), allow_pickle=False)
    if array.shape != shape or array.dtype != np.float32 or not np.isfinite(array).all():
        raise ValueError("sample array shape/dtype/finite contract failed")
    if list(array.shape) != descriptor["shape"] or str(array.dtype) != descriptor["dtype"]:
        raise ValueError("sample array metadata mismatch")
    return array


def verify_run(root):
    root = Path(root).resolve()
    manifest = json.loads((root / "manifest.json").read_text(encoding="utf-8"))
    if manifest.get("schema_version") != 1 or manifest.get("status") != "verified":
        raise ValueError("unsupported or unverified manifest")
    if manifest.get("quantized") is not False or manifest.get("rtl") is not False:
        raise ValueError("this artifact must be a float software baseline")
    if manifest["source"]["commit"] != SOURCE_COMMIT:
        raise ValueError("source commit mismatch")
    source_path = WORKSPACE / "config/source-manifest.json"
    if sha256_file(source_path) != manifest["source"]["manifest_sha256"]:
        raise ValueError("source manifest SHA-256 mismatch")
    official_source = json.loads(source_path.read_text(encoding="utf-8"))
    if official_source["commit"] != SOURCE_COMMIT:
        raise ValueError("official source commit mismatch")
    vendor = WORKSPACE / "vendor/keyword-transformer"
    source_hashes = {item["path"]: item["sha256"] for item in official_source["files"]}
    if source_hashes != manifest["source"]["files_sha256"]:
        raise ValueError("source file hash inventory mismatch")
    for relative, expected_hash in source_hashes.items():
        if sha256_file(vendor / relative) != expected_hash:
            raise ValueError("immutable source SHA-256 mismatch: " + relative)
    checkpoint_dir = vendor / "models_data_v2_12_labels/kwt1"
    actual_checkpoint_hashes = {p.name: sha256_file(p) for p in sorted(checkpoint_dir.glob("best_weights.*"))}
    if actual_checkpoint_hashes != manifest["checkpoint_sha256"]:
        raise ValueError("checkpoint SHA-256 mismatch")
    if sha256_file(checkpoint_dir / "flags.json") != manifest["flags_sha256"]:
        raise ValueError("official flags SHA-256 mismatch")
    if manifest["inference_overrides"] != INFERENCE_OVERRIDES:
        raise ValueError("unapproved inference flag overrides")
    saved_flags = json.loads((checkpoint_dir / "flags.json").read_text())
    for key, expected_value in dict(saved_flags, **INFERENCE_OVERRIDES).items():
        if manifest["flags"].get(key) != expected_value:
            raise ValueError("effective flag differs from official configuration: " + key)
    if sha256_file(checkpoint_dir / "labels.txt") != manifest["label_sha256"] or (checkpoint_dir / "labels.txt").read_text().splitlines() != manifest["labels"]:
        raise ValueError("official label hash/order mismatch")
    if sha256_file(WORKSPACE / "config/model-contract.json") != manifest["contract_sha256"]:
        raise ValueError("model contract SHA-256 mismatch")
    environment = json.loads((root / "environment.json").read_text())
    if sha256_file(root / "environment.json") != manifest["environment_sha256"]:
        raise ValueError("environment SHA-256 mismatch")
    if manifest["runtime"]["requested_tensorflow"] != "2.4.0rc1" or manifest["runtime"]["installed_tensorflow"] != "2.4.0" or environment["tensorflow"] != "2.4.0":
        raise ValueError("explicit TensorFlow compatibility runtime mismatch")
    if environment["numpy"] != "1.19.5" or environment["tensorflow_addons"] != "0.12.1" or not environment["python"].startswith("3.8."):
        raise ValueError("pinned model dependency runtime mismatch")
    import tensorflow as tf
    checkpoint_reader = tf.train.load_checkpoint(str(checkpoint_dir / "best_weights"))
    validate_official_flags(manifest["flags"])
    if manifest["flags"]["training"] is not False or manifest["flags"]["batch_size"] != 1:
        raise ValueError("baseline must disable training and use batch=1")
    if any(manifest["flags"][key] != 0 for key in ("use_spec_augment", "use_spec_cutout", "time_shift_ms", "sp_time_shift_ms", "resample", "sp_resample", "volume_resample", "background_frequency", "background_volume")):
        raise ValueError("augmentation must be disabled")
    for restore in (manifest["restore"], manifest["hook_restore"]):
        if not restore["assert_existing_objects_matched"] or not restore["all_model_variables_exact"]:
            raise ValueError("checkpoint restoration was not independently verified")
        if restore["variable_count"] != len(restore["variables"]) or restore["variable_count"] <= 0:
            raise ValueError("checkpoint restore variable count mismatch")
        if restore["changed_variable_count"] != sum(item["changed_from_initial"] for item in restore["variables"]) or restore["changed_variable_count"] <= 0:
            raise ValueError("checkpoint restore must change initialized model weights")
        if any(item["checkpoint_max_abs_error"] != 0.0 for item in restore["variables"]):
            raise ValueError("checkpoint variables did not match")
        mapping = restore["ffn1_checkpoint_keys"]
        if [item["layer"] for item in mapping] != list(range(1, 13)):
            raise ValueError("checkpoint mapping must cover twelve ordered layers")
        for key in ("W", "b"):
            if len({item[key] for item in mapping}) != 12:
                raise ValueError("checkpoint keys must be independent for every layer")
        for item in mapping:
            for key, variable in (("W", "kernel"), ("b", "bias")):
                expected_key = "layer_with_weights-0/enc_layers/{}/ffn/layer_with_weights-0/{}/.ATTRIBUTES/VARIABLE_VALUE".format(item["layer"] - 1, variable)
                if item[key] != expected_key:
                    raise ValueError("FFN1 checkpoint mapping must use the actual layer and first Dense")
    samples = {item["sample_id"]: item for item in manifest["samples"]}
    if len(samples) != len(manifest["samples"]):
        raise ValueError("duplicate sample IDs")
    real = sum(item["partition"] == "validation" for item in samples.values())
    if real < 2:
        raise ValueError("at least two real validation WAVs required")
    if len(manifest["labels"]) != 12:
        raise ValueError("twelve official labels required")
    array_hashes = {}
    data_root = WORKSPACE / "data/speech_commands_subset"
    source_data_path = data_root / "manifest.json"
    if sha256_file(source_data_path) != manifest["dataset"]["manifest_sha256"]:
        raise ValueError("data manifest SHA-256 mismatch")
    source_data = json.loads(source_data_path.read_text())
    original_samples = {item["sample_id"]: item for item in source_data["samples"]}
    sys.path.insert(0, str(vendor))
    from kws_streaming.data import input_data
    for item in samples.values():
        audio = load_array(root, item["audio_array"], (16000,))
        mfcc = load_array(root, item["mfcc_array"], (98, 40))
        logits = load_array(root, item["logits_array"], (12,))
        if not np.array_equal(logits, np.asarray(item["logits"], dtype=np.float32)):
            raise ValueError("logits metadata disagrees with actual array")
        pred = int(np.argmax(logits))
        if pred != item["predicted_index"] or manifest["labels"][pred] != item["predicted_label"]:
            raise ValueError("prediction disagrees with logits")
        target = item["word"] if item["word"] in manifest["labels"] else "_unknown_"
        if item["ground_truth_label"] != target:
            raise ValueError("ground-truth label disagrees with original word")
        if item["partition"] == "synthetic_silence" and np.any(audio):
            raise ValueError("synthetic zero silence contains nonzero audio")
        if item["partition"] == "validation":
            original = original_samples.get(item.get("source_sample_id"))
            if original is None or original["relative_path"] != item["relative_path"] or original["sha256"] != item["sample_sha256"] or original["word"] != item["word"]:
                raise ValueError("sample provenance differs from source data manifest")
            original_path = (data_root / item["relative_path"]).resolve()
            if data_root.resolve() not in original_path.parents or sha256_file(original_path) != item["sample_sha256"]:
                raise ValueError("real WAV SHA-256 mismatch")
            if input_data.which_set(str(original_path), manifest["flags"]["validation_percentage"], manifest["flags"]["testing_percentage"]) != "validation":
                raise ValueError("sample not in official validation partition")
            with wave.open(str(original_path), "rb") as wav:
                if (wav.getframerate(), wav.getnchannels(), wav.getsampwidth()) != (16000, 1, 2):
                    raise ValueError("source WAV format mismatch")
                pcm = np.frombuffer(wav.readframes(wav.getnframes()), dtype="<i2").astype(np.float32) / 32768.0
            expected_audio = np.zeros(16000, dtype=np.float32)
            expected_audio[:min(16000, pcm.size)] = pcm[:16000]
            if not np.array_equal(audio, expected_audio):
                raise ValueError("audio.npy does not equal its real WAV PCM decoding")
        for key in ("hook_logits_comparison", "hook_mfcc_comparison", "unhook_official_layer_replay_logits_comparison", "hook_official_layer_replay_logits_comparison"):
            if item[key]["max_abs_error"] != 0.0:
                raise ValueError("hook must leave logits and MFCC identical")
        for key in ("audio_array", "mfcc_array", "logits_array"):
            descriptor = item[key]
            array_hashes[descriptor["path"]] = descriptor["sha256"]
    seen = set()
    weights_by_layer = {}
    max_abs, max_nrmse = 0.0, 0.0
    for case in manifest["cases"]:
        identity = (case["sample_id"], case["layer"])
        if identity in seen or case["sample_id"] not in samples:
            raise ValueError("duplicate or unknown FFN1 case")
        seen.add(identity)
        sample = samples[case["sample_id"]]
        if case["partition"] != sample["partition"] or case["sample_sha256"] != sample["sample_sha256"]:
            raise ValueError("FFN1 case source disagrees with its sample")
        if case["checkpoint_sha256"] != manifest["checkpoint_sha256"]:
            raise ValueError("FFN1 case checkpoint hash disagreement")
        if case["source_manifest_sha256"] != manifest["source"]["manifest_sha256"]:
            raise ValueError("FFN1 case source manifest hash disagreement")
        arrays = verify_ffn1_case(root, case)
        expected_keys = manifest["restore"]["ffn1_checkpoint_keys"][case["layer"] - 1]
        for key in ("W", "b"):
            if case["checkpoint_keys"][key] != expected_keys[key]:
                raise ValueError("FFN1 checkpoint key disagrees with restore mapping")
            stored = checkpoint_reader.get_tensor(case["checkpoint_keys"][key])
            if not np.array_equal(arrays[key], stored):
                raise ValueError("FFN1 {} is not the exact official checkpoint tensor".format(key))
        metrics = compare_arrays(ffn1_numpy(arrays["X"], arrays["W"], arrays["b"]), arrays["Y"], 1e-5, 1e-5)
        for key in ("max_abs_error", "rmse", "nrmse"):
            if not np.isclose(metrics[key], case["numpy_comparison"][key], atol=1e-12, rtol=1e-8):
                raise ValueError("recorded NumPy metric differs from recomputation")
        max_abs = max(max_abs, metrics["max_abs_error"])
        max_nrmse = max(max_nrmse, metrics["nrmse"])
        if any(case["hook_comparison"][key]["max_abs_error"] != 0.0 for key in ("X", "W", "b", "Y")):
            raise ValueError("hook modified FFN1 tensors")
        weight_hashes = (case["arrays"]["W"]["sha256"], case["arrays"]["b"]["sha256"])
        if case["layer"] in weights_by_layer and weights_by_layer[case["layer"]] != weight_hashes:
            raise ValueError("same layer weights differ between samples")
        weights_by_layer[case["layer"]] = weight_hashes
        for descriptor in case["arrays"].values():
            array_hashes[descriptor["path"]] = descriptor["sha256"]
    expected = {(sample_id, layer) for sample_id in samples for layer in range(1, 13)}
    if seen != expected:
        raise ValueError("each sample needs exactly twelve independent FFN1 cases")
    actual_arrays = {path.relative_to(root).as_posix() for path in root.rglob("*.npy")}
    if actual_arrays != set(array_hashes):
        raise ValueError("artifact contains missing or unreferenced array files")
    return {"status": "PASS", "real_validation_samples": real,
            "synthetic_samples": len(samples) - real, "case_count": len(seen),
            "restored_variable_count": manifest["restore"]["variable_count"],
            "numpy_max_abs_error": max_abs, "numpy_max_nrmse": max_nrmse,
            "array_count": len(array_hashes), "array_sha256": array_hashes,
            "predictions": [{"sample_id": item["sample_id"], "partition": item["partition"],
                              "word": item["word"], "prediction": item["predicted_label"],
                              "ground_truth_label": item["ground_truth_label"]} for item in samples.values()],
            "scope": "Float32 subset smoke only; not full-dataset accuracy or bit-true hardware validation"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report", type=Path, default=WORKSPACE / "reports/model/baseline")
    parser.add_argument("--compare", type=Path)
    args = parser.parse_args()
    result = verify_run(args.report)
    if args.compare:
        other = verify_run(args.compare)
        if result["array_sha256"] != other["array_sha256"]:
            raise ValueError("repeat run array SHA-256 values differ")
        result["repeat"] = {"status": "PASS", "compared_array_count": result["array_count"],
                            "method": "SHA-256 equality of every audio/MFCC/logits/FFN1 .npy"}
    result["manifest_sha256"] = sha256_file(args.report / "manifest.json")
    (args.report / "verification.json").write_text(json.dumps(result, indent=2, ensure_ascii=False, sort_keys=True) + "\n", encoding="utf-8")
    lines = ["# 官方 KWT-1 浮点基准", "",
             "- 验收：PASS", "- 真实 validation WAV：{} 个".format(result["real_validation_samples"]),
             "- 明确标注的合成零输入 silence：{} 个".format(result["synthetic_samples"]),
             "- 十二层独立 FFN1 案例：{} 个".format(result["case_count"]),
             "- 运行期逐变量核对：{} 个 live 模型变量全部精确等于 checkpoint reader 张量".format(result["restored_variable_count"]),
             "- 独立文件回读：每一层导出的 W/b 再次精确等于指定 checkpoint 张量",
             "- NumPy Y=XW+b 最大绝对误差：{:.9g}".format(result["numpy_max_abs_error"]),
             "- NumPy 最大 NRMSE（参考 RMS 分母下限 1e-8）：{:.9g}".format(result["numpy_max_nrmse"]),
             "- 原完整模型有/无 hook 的 logits 与 MFCC：零差",
             "- 无 hook 中间参考复用已建立的官方层对象，状态由完整原 block 传播；回放最终 logits 与原完整模型零差",
             "- 原完整模型 Dense/LN 观察值与无 hook 官方层对象回放的 X/W/b/Y：逐层零差",
             "- 重复运行全部 .npy SHA-256：{}".format("PASS" if args.compare else "未执行"),
             "", "| 样本 | 分区 | 原始词 | 12 类目标 | 预测 |",
             "|---|---|---|---|---|"]
    for item in result["predictions"]:
        lines.append("| {sample_id} | {partition} | {word} | {ground_truth_label} | {prediction} |".format(**item))
    lines += ["", "浮点容差只用于软件对照。本批没有量化、RTL、test 集调参或完整数据集准确率测量。两个真实样本均为 eight，按官方 12 类口径属于 _unknown_，不能据此推断十二类总体准确率。",
              "", "兼容限制：上游指定 TensorFlow 2.4.0rc1，当前可取得的兼容运行时为 2.4.0；不声称与 RC1 逐位等价。加载 checkpoint 时仍出现 Dense/GELU trackable 引用不一致警告，完整 checkpoint 未全部消费；实际模型数值变量均通过逐变量精确核对。保留警告，不宣称其根因已修复。",
              "", "`manifest.json` 记录数组与来源/配置哈希、逐层对照、checkpoint 身份、官方 flags 和允许的推理覆盖项。`restore-verification.json` 是运行期全部 live 变量的恢复证据；文件回读独立核对导出的 FFN1 W/b。"]
    (args.report / "SUMMARY.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(json.dumps({key: value for key, value in result.items() if key != "array_sha256"}, indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()
