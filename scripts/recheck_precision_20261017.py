"""Frozen precision recheck: independent FFN1 and full FP32 classifier paths.

Run with the pinned WSL model environment.  The 15-input export cohort and the
older 36-case prototype cohort are evaluated separately; their tensors are
never exchanged.  This script performs inference only, with no fitting/search.
"""
import argparse
import csv
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import sys
import time

os.environ.setdefault('CUDA_VISIBLE_DEVICES', '-1')
os.environ.setdefault('TF_CPP_MIN_LOG_LEVEL', '2')
os.environ.setdefault('TF_DETERMINISTIC_OPS', '1')
os.environ.setdefault('OMP_NUM_THREADS', '1')
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import numpy as np
from numeric.fixedpoint import derive_layer_config, quantize_signed, ffn1_reference
from numeric.encoder.contracts import layout, metrics
from numeric.encoder.run_reference import Reference


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def read(path):
    return json.loads(Path(path).read_text(encoding='utf-8'))


def put(path, obj):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(obj, ensure_ascii=False, sort_keys=True, indent=2) + '\n', encoding='utf-8')


def display(path):
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def load(root, meta):
    path = root / meta['npy']
    if sha(path) != meta['npy_sha256']:
        raise ValueError('export array SHA mismatch: ' + str(path))
    a = np.load(str(path), allow_pickle=False)
    if a.dtype != np.float32 or list(a.shape) != meta['shape'] or not np.isfinite(a).all():
        raise ValueError('invalid float32 export array: ' + str(path))
    return a


def save_array(root, relative, value):
    value = np.ascontiguousarray(value, dtype='<f4')
    if not np.isfinite(value).all():
        raise ValueError('nonfinite live official tensor')
    path = root/(relative + '.npy')
    path.parent.mkdir(parents=True, exist_ok=True)
    np.save(str(path), value, allow_pickle=False)
    return dict(npy=relative + '.npy', npy_sha256=sha(path), shape=list(value.shape),
                dtype='float32', bits_sha256=hashlib.sha256(value.tobytes()).hexdigest())


def error(actual, truth):
    value = metrics(actual, truth)
    a, b = np.asarray(actual, np.float64), np.asarray(truth, np.float64)
    value.update(sse=float(np.sum((a-b)**2)), reference_square_sum=float(np.sum(b*b)), count=int(b.size))
    idx = np.unravel_index(np.argmax(np.abs(a-b)), b.shape)
    value['max_abs_location'] = list(map(int, idx))
    value['max_abs_actual'] = float(a[idx])
    value['max_abs_reference'] = float(b[idx])
    return value


def aggregate(rows):
    result = []
    for layer in range(1, 13):
        selected = [r for r in rows if r['layer'] == layer]
        sse = sum(r['sse'] for r in selected)
        rsq = sum(r['reference_square_sum'] for r in selected)
        count = sum(r['count'] for r in selected)
        result.append(dict(layer=layer, input_count=len(selected), count=count, sse=sse,
                           reference_square_sum=rsq,
                           nrmse=float(np.sqrt(sse/count)/max(np.sqrt(rsq/count), 1e-8)),
                           worst_case_nrmse=max(r['nrmse'] for r in selected),
                           max_abs=max(r['max_abs'] for r in selected),
                           saturation={key:sum(r['saturation'][key] for r in selected)
                                       for key in selected[0].get('saturation', {})}))
    return result


def fixed_case(x, w, b, y, sample_id, partition, layer, out):
    config = derive_layer_config(w, b)
    qx, stats = quantize_signed(x, config.input_scale, 16)
    result = ffn1_reference(qx, config.weight_q, config.bias_q, config.output_shift)
    actual = result.output.astype(np.float64) * config.output_scale
    array_path = out / 'fixed_ffn1' / sample_id / ('layer_%02d.npy' % layer)
    array_path.parent.mkdir(parents=True, exist_ok=True)
    np.save(str(array_path), result.output, allow_pickle=False)
    row = dict(sample_id=sample_id, partition=partition, layer=layer, **error(actual, y))
    row.update(config=config.metadata(), scalar_checks=result.scalar_checks,
               saturation={'input':stats['saturated'], 'weight':config.weight_stats['saturated'],
                           'bias':config.bias_stats['saturated'], 'raw48':int(result.overflow.sum()),
                           'output32':int(result.output_saturated.sum())},
               result_npy=str(array_path.relative_to(out)), result_sha256=sha(array_path))
    return row, result


def live_official(exports, out):
    """Rerun original complete graph and verify every used official tensor."""
    import tensorflow as tf
    from model.run_baseline import official_flags, restore_and_verify, verify_sources, load_samples
    from model.encoder_export import observed_model, prepare_dataset, layer_parameters
    if tf.__version__ != '2.4.0':
        raise ValueError('requires pinned official TF 2.4.0 runtime')
    vendor = ROOT / 'vendor/keyword-transformer'
    source = verify_sources(vendor)
    flags, _, builder = official_flags(vendor)
    test_samples, _ = prepare_dataset(ROOT/'data/encoder_test_subset/manifest.json', flags)
    by_id = {s['sample_id']:s['audio'] for s in test_samples}
    validation_samples, _ = load_samples(ROOT/'data/speech_commands_subset', flags, True)
    for sample in validation_samples:
        by_id[sample['sample_id']] = sample['audio']
    cfg = tf.compat.v1.ConfigProto(intra_op_parallelism_threads=1, inter_op_parallelism_threads=1,
                                  device_count={'GPU':0})
    records, fresh_exports = [], []
    tf.keras.backend.clear_session()
    with tf.Graph().as_default(), tf.compat.v1.Session(config=cfg) as session:
        tf.compat.v1.keras.backend.set_session(session)
        tf.compat.v1.keras.backend.set_learning_phase(0)
        tf.compat.v1.set_random_seed(1234)
        model, tr, initial, inputs, stages, final, replay_logits, head = observed_model(tf, builder, flags)
        restored = restore_and_verify(tf, session, model, vendor/'models_data_v2_12_labels/kwt1/best_weights')
        if restored['variable_count'] != 162:
            raise ValueError('incomplete checkpoint restore')
        before = session.run(model.weights)
        for export_root, document in exports:
            fresh_root = out/'official_current'/export_root.name
            fresh_document = {key:document[key] for key in ['status', 'shape', 'labels', 'label_to_index',
                              'label_flags', 'checkpoint_sha256', 'source', 'source_hashes']}
            fresh_document.update(samples=[], weights=[], classifier={},
                                  pinned_manifest=str((export_root/'manifest.json').relative_to(ROOT)),
                                  pinned_manifest_sha256=sha(export_root/'manifest.json'))
            packed_layers = [np.concatenate([a.reshape(-1) for a in session.run(layer_parameters(block))])
                             for block in tr.enc_layers]
            for i, packed in enumerate(packed_layers):
                meta = save_array(fresh_root, 'weights/layer_%02d' % i, packed)
                if meta['bits_sha256'] != document['weights'][i]['bits_sha256']:
                    raise ValueError('live official packed weight differs from pinned checkpoint')
                fresh_document['weights'].append(meta)
            classifier_values = session.run([head.layers[0].kernel, head.layers[0].bias])
            for name, value in zip(['classifier_kernel', 'classifier_bias'], classifier_values):
                meta = save_array(fresh_root, 'classifier/' + name, value)
                if meta['bits_sha256'] != document['classifier'][name]['bits_sha256']:
                    raise ValueError('live official classifier differs from pinned checkpoint')
                fresh_document['classifier'][name] = meta
            for sample in document['samples']:
                sid = sample['sample_id']
                # Match the existing full-observation fetch boundary to avoid
                # changing Grappler fusion merely by requesting fewer stages.
                logits, x, last, replayed, in_values, stage_values = session.run(
                    [model.outputs[0], initial, final, replay_logits, inputs, stages],
                    feed_dict={model.inputs[0]:by_id[sid]})
                if not np.array_equal(logits.view(np.uint32), replayed.view(np.uint32)):
                    raise ValueError('official original head replay differs')
                n1s, ffn1s = [s[8] for s in stage_values], [s[9] for s in stage_values]
                arrays = [(x[0], sample['input']), (last[0], sample['final']), (logits[0], sample['logits'])]
                arrays.extend((a[0], s['stages'][key]) for key, values in [('n1', n1s), ('ffn1', ffn1s)]
                              for a, s in zip(values, sample['layers']))
                checks = [hashlib.sha256(np.ascontiguousarray(a, dtype='<f4').tobytes()).hexdigest()==meta['bits_sha256']
                          for a, meta in arrays]
                directory = 'cases/' + sid
                source_audio = dict(sample['source_audio'])
                if sample['partition']=='validation':
                    original = next(s for s in validation_samples if s['sample_id']==sid)
                    audio_path = ROOT/'data/speech_commands_subset'/original['relative_path']
                    source_audio = dict(path=str(audio_path.relative_to(ROOT)), sha256=sha(audio_path))
                elif sample['partition']=='synthetic_silence':
                    audio_meta = save_array(fresh_root, directory + '/waveform', by_id[sid])
                    source_audio = dict(path=str((fresh_root/audio_meta['npy']).relative_to(ROOT)), sha256=audio_meta['npy_sha256'])
                fresh_sample = dict(sample_id=sid, partition=sample['partition'], source_audio=source_audio,
                                    ground_truth_label=sample['ground_truth_label'], layers=[],
                                    input=save_array(fresh_root, directory + '/input', x[0]),
                                    final=save_array(fresh_root, directory + '/final', last[0]),
                                    logits=save_array(fresh_root, directory + '/logits', logits[0]))
                for i, (n1, ffn1) in enumerate(zip(n1s, ffn1s)):
                    fresh_sample['layers'].append(dict(stages={
                        'n1':save_array(fresh_root, directory + '/layer_%02d/n1' % i, n1[0]),
                        'ffn1':save_array(fresh_root, directory + '/layer_%02d/ffn1' % i, ffn1[0])}))
                fresh_document['samples'].append(fresh_sample)
                records.append(dict(sample_id=sid, checked_tensors=len(checks),
                                    pinned_equal_tensor_count=sum(checks), all_pinned_tensors_bit_equal=all(checks),
                                    original_model_head_replay_bit_equal=True,
                                    source_audio=source_audio,
                                    preprocessed_waveform_bits_sha256=hashlib.sha256(np.ascontiguousarray(by_id[sid], dtype='<f4').tobytes()).hexdigest(),
                                    encoder_input_bits_sha256=fresh_sample['input']['bits_sha256'],
                                    logits_npy=str((fresh_root/fresh_sample['logits']['npy']).relative_to(out)),
                                    logits_sha256=fresh_sample['logits']['npy_sha256']))
                print('OFFICIAL_LIVE', sid, 'checked_tensors=' + str(len(checks)), flush=True)
            put(fresh_root/'manifest.json', fresh_document)
            fresh_exports.append((fresh_root, fresh_document))
        after = session.run(model.weights)
        if any(not np.array_equal(a.view(np.uint32), b.view(np.uint32)) for a, b in zip(before, after)):
            raise ValueError('official parameters changed during inference')
    put(out/'official_live.json', dict(status='PASS', source=source, restore=restored,
                                     runtime={'tensorflow':tf.__version__, 'numpy':np.__version__,
                                              'python':platform.python_version()}, samples=records))
    return records, fresh_exports


def classification_summary(rows):
    result = {}
    groups = {'validation_real':[r for r in rows if r['partition']=='validation'],
              'published_test12':[r for r in rows if r['partition']=='testing'],
              'real_audio14':[r for r in rows if r['partition']!='synthetic_silence'],
              'synthetic_silence':[r for r in rows if r['partition']=='synthetic_silence'],
              'all15_including_synthetic':rows}
    for name, selected in groups.items():
        n = len(selected)
        official = sum(r['official_correct'] for r in selected)
        design = sum(r['design_correct'] for r in selected)
        result[name] = dict(n=n, official_correct=official, design_correct=design,
                            official_accuracy=official/n, design_accuracy=design/n,
                            accuracy_drop_percentage_points=100*(official-design)/n,
                            agreement_count=sum(r['same_top1'] for r in selected),
                            agreement_rate=sum(r['same_top1'] for r in selected)/n)
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    out = args.output.resolve()
    allowed = (ROOT/'reports/revd_repair_20261017/precision').resolve()
    if out == allowed or allowed not in out.parents:
        raise ValueError('output must be a fresh run below reports/revd_repair_20261017/precision')
    out.mkdir(parents=True, exist_ok=False)
    started = time.monotonic()
    watched = [ROOT/p for p in ['config/model-contract.json', 'config/prototype-numeric.json',
                               'numeric/fixedpoint.py', 'numeric/encoder/encoder_ref.c',
                               'numeric/encoder/encoder_ref.h', 'numeric/encoder/run_reference.py',
                               'numeric/encoder/contracts.py', 'model/encoder_export.py',
                               'model/run_baseline.py', 'config/source-manifest.json']]
    watched += sorted(p for p in (ROOT/'rtl').rglob('*') if p.is_file())
    before = {str(p.relative_to(ROOT)):sha(p) for p in watched}
    exports = [(ROOT/p, read(ROOT/p/'manifest.json'))
               for p in ['reports/encoder/export', 'reports/encoder/export-test12']]
    for root, document in exports:
        if document['status'] != 'PASS' or len(document['weights']) != 12:
            raise ValueError('invalid official export')
        for path, expected in document['source_hashes'].items():
            if sha(ROOT/path) != expected:
                raise ValueError('export source changed: ' + path)
    live, exports = live_official(exports, out)
    ref = Reference(out/'current_c_build')
    fixed, fp32_layers, classifications, provenance = [], [], [], []
    layers_layout = {e['name']:e for e in layout()}
    frozen = read(ROOT/'reports/prototype/vectors/manifest.json')
    frozen_by_layer = {c['layer']:c for c in frozen['cases']}
    for export_root, document in exports:
        weights = [load(export_root, meta) for meta in document['weights']]
        kernel = load(export_root, document['classifier']['classifier_kernel'])
        bias = load(export_root, document['classifier']['classifier_bias'])
        for sample in document['samples']:
            sid, partition = sample['sample_id'], sample['partition']
            audio = ROOT/sample['source_audio']['path']
            if sha(audio) != sample['source_audio']['sha256']:
                raise ValueError('source audio SHA mismatch')
            x = load(export_root, sample['input'])
            provenance.append(dict(sample_id=sid, partition=partition, ground_truth_label=sample['ground_truth_label'],
                                   source_audio=sample['source_audio'], export_manifest=display(export_root/'manifest.json'),
                                   export_manifest_sha256=sha(export_root/'manifest.json'), input=sample['input'],
                                   official_layers=[{'n1':l['stages']['n1'], 'ffn1':l['stages']['ffn1']} for l in sample['layers']]))
            for i, (w, official_layer) in enumerate(zip(weights, sample['layers'])):
                def field(name):
                    e = layers_layout[name]
                    return w[e['offset_words']:e['offset_words']+e['words']].reshape(e['shape'])
                official_x = load(export_root, official_layer['stages']['n1'])
                official_y = load(export_root, official_layer['stages']['ffn1'])
                row, _ = fixed_case(official_x, field('w1'), field('b1'), official_y, sid, partition, i+1, out)
                # Derive only from official frozen parameters; verify identical to the existing frozen layer config.
                if row['config'] != frozen_by_layer[i+1]['config']:
                    raise ValueError('fixed scale differs from frozen prototype at layer ' + str(i+1))
                fixed.append(row)
                x, stages = ref.layer(x, w, 256)
                fp32_layers.append(dict(sample_id=sid, partition=partition, layer=i+1,
                                         saturation={}, **error(stages['ffn1'], official_y)))
            logits = ref.classify(np.ascontiguousarray(x[0]), kernel, bias)
            expected_logits = load(export_root, sample['logits'])
            expected_final = load(export_root, sample['final'])
            official_index, design_index = int(np.argmax(expected_logits)), int(np.argmax(logits))
            truth = document['label_to_index'][sample['ground_truth_label']]
            case_out = out/'fp32'/sid
            case_out.mkdir(parents=True, exist_ok=True)
            np.save(str(case_out/'final.npy'), x, allow_pickle=False)
            np.save(str(case_out/'logits.npy'), logits, allow_pickle=False)
            classifications.append(dict(sample_id=sid, partition=partition, ground_truth=sample['ground_truth_label'],
                                         official_top1=document['labels'][official_index], design_top1=document['labels'][design_index],
                                         same_top1=official_index==design_index, official_correct=official_index==truth,
                                         design_correct=design_index==truth, logits_error=error(logits, expected_logits),
                                         final_error=error(x, expected_final), design_logits_sha256=sha(case_out/'logits.npy'),
                                         classifier_kernel_sha256=document['classifier']['classifier_kernel']['npy_sha256'],
                                         classifier_bias_sha256=document['classifier']['classifier_bias']['npy_sha256']))
            print('RECHECK', sid, 'official=' + document['labels'][official_index],
                  'design=' + document['labels'][design_index], flush=True)
    prototype = []
    for case in frozen['cases']:
        source_root = ROOT/'reports/model/baseline'
        arrays = {}
        for name, meta in case['source_arrays'].items():
            path = source_root/meta['path']
            if sha(path) != meta['sha256']:
                raise ValueError('prototype source SHA mismatch')
            arrays[name] = np.load(str(path), allow_pickle=False)
        row, result = fixed_case(arrays['X'], arrays['W'], arrays['b'], arrays['Y'],
                                  'prototype36/' + case['sample_id'], case['partition'], case['layer'], out)
        for name, actual in [('Yq', result.output), ('raw48', result.raw), ('overflow', result.overflow),
                             ('output_saturated', result.output_saturated)]:
            meta = case['arrays'][name]
            path = ROOT/'reports/prototype/vectors'/meta['path']
            if sha(path) != meta['sha256'] or not np.array_equal(actual, np.load(str(path), allow_pickle=False)):
                raise ValueError('current numeric model differs from frozen prototype: ' + case['case_id'])
        prototype.append(row)
    layers = aggregate(fixed)
    worst_layer_nrmse = max(r['nrmse'] for r in layers)
    local_ffn1_pass = bool(np.isfinite(worst_layer_nrmse) and worst_layer_nrmse <= .03)
    layer_groups = {partition:aggregate([r for r in fixed if r['partition']==partition])
                    for partition in sorted({r['partition'] for r in fixed})}
    if before != {str(p.relative_to(ROOT)):sha(p) for p in watched}:
        raise ValueError('frozen source changed during evaluation')
    summary = dict(status='PASS_LOCAL_ENGINEERING_PRECISION_RECHECK' if local_ffn1_pass else 'FAIL_LOCAL_FFN1_NRMSE',
                   finished_utc=datetime.now(timezone.utc).isoformat(), seconds=time.monotonic()-started,
                   scope='15 engineering inputs = 2 real validation unknown + 1 synthetic zero + 12 class-covering published-test examples; not a population accuracy estimate or official contest 600.',
                   official_contest_acceptance=False, formal_score=None,
                   local_ffn1_criterion=dict(threshold=.03, observed_worst_layer_nrmse=worst_layer_nrmse,
                                             passed=local_ffn1_pass, scope='Only this frozen 15-input engineering cohort'),
                   model_source_commit=exports[0][1]['source']['commit'],
                   checkpoint_sha256=exports[0][1]['checkpoint_sha256'],
                   live_official_samples=len(live), live_official_checked_tensors=sum(r['checked_tensors'] for r in live),
                   live_official_pinned_equal_tensor_count=sum(r['pinned_equal_tensor_count'] for r in live),
                   distinct_preprocessed_waveform_sha256_count=len({r['preprocessed_waveform_bits_sha256'] for r in live}),
                   distinct_encoder_input_sha256_count=len({r['encoder_input_bits_sha256'] for r in live}),
                   current_c_library_sha256=ref.library_hash, current_c_build_command=ref.command,
                   definition='e_l=sqrt(sum_cases SSE_l/count_l)/max(sqrt(sum_cases reference_square_l/count_l),1e-8); e=max_l e_l',
                   fixed_ffn1_15_inputs=dict(cases=len(fixed), output_values=sum(r['count'] for r in fixed),
                                             worst_layer_nrmse=max(r['nrmse'] for r in layers),
                                             worst_case=max(fixed, key=lambda r:r['nrmse']), layers=layers,
                                             layers_by_partition=layer_groups,
                                             saturation={k:sum(r['saturation'][k] for r in fixed) for k in fixed[0]['saturation']}),
                   prototype36_separate=dict(cases=len(prototype), current_model_exact_equal_frozen_integer_outputs=True,
                                             layers=aggregate(prototype),
                                             worst_layer_nrmse=max(r['nrmse'] for r in aggregate(prototype))),
                   fp32_full_encoder=dict(classification=classification_summary(classifications),
                                           max_final_nrmse=max(r['final_error']['nrmse'] for r in classifications),
                                           max_logits_nrmse=max(r['logits_error']['nrmse'] for r in classifications),
                                           ffn1_layers=aggregate(fp32_layers)),
                   local_validation_inventory=dict(repository_wav_count=14, validation_real_count=2,
                                                     validation_classes=['_unknown_'], validation_speaker_count=2,
                                                     original_workspace_data='C:/Users/11035/Desktop/ic/kwt—1/data',
                                                     original_workspace_wav_count=14,
                                                     conclusion='No additional local validation samples. Full 12-class or 600-sample validation acceptance remains untested. No dataset download performed.'),
                   frozen_source_sha256=before, evaluator_sha256=sha(Path(__file__)),
                   input_manifest_sha256={p:sha(ROOT/p) for p in ['data/speech_commands_subset/manifest.json',
                                           'data/encoder_test_subset/manifest.json', 'reports/prototype/vectors/manifest.json']},
                   limitations=['Host inference only; no fresh RTL or E203 execution in this report.',
                                'INT16 results are isolated FFN1 operator error, not end-to-end INT16 classifier accuracy.',
                                'Full FP32 path starts from exactly the same official frontend/token input and uses the same classifier head.',
                                'Two real validation WAVs are unknown-class only; published test12 is class coverage, not random representative evaluation.',
                                'Synthetic zero input is reported separately from real labeled audio.',
                                'No training, fine-tuning, threshold tuning, test-set parameter selection, coefficient search, or weight/RTL changes.'])
    put(out/'summary.json', summary)
    put(out/'input_provenance.json', provenance)
    put(out/'fixed_ffn1_cases.json', fixed)
    put(out/'prototype36_cases.json', prototype)
    put(out/'fp32_layer_cases.json', fp32_layers)
    put(out/'classification_cases.json', classifications)
    with (out/'layer_metrics.csv').open('w', newline='', encoding='utf-8') as f:
        fields = ['layer', 'input_count', 'count', 'sse', 'reference_square_sum', 'nrmse', 'worst_case_nrmse', 'max_abs']
        writer = csv.DictWriter(f, fields, extrasaction='ignore'); writer.writeheader(); writer.writerows(layers)
    with (out/'classification.csv').open('w', newline='', encoding='utf-8') as f:
        fields = ['sample_id', 'partition', 'ground_truth', 'official_top1', 'design_top1', 'same_top1', 'official_correct', 'design_correct']
        writer = csv.DictWriter(f, fields, extrasaction='ignore'); writer.writeheader(); writer.writerows(classifications)
    print('PRECISION_RECHECK_PASS' if local_ffn1_pass else 'PRECISION_RECHECK_FAIL', out,
          'worst_layer_nrmse=', summary['fixed_ffn1_15_inputs']['worst_layer_nrmse'],
          'classification=', summary['fp32_full_encoder']['classification'], flush=True)
    return 0 if local_ffn1_pass else 1


if __name__ == '__main__':
    raise SystemExit(main())
