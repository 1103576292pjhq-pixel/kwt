"""Measure TF fetch-boundary drift without changing model/weights/coefficients."""
import argparse
import os
from pathlib import Path
import sys
import time
os.environ.setdefault('CUDA_VISIBLE_DEVICES', '-1')
os.environ.setdefault('TF_CPP_MIN_LOG_LEVEL', '2')
os.environ.setdefault('TF_DETERMINISTIC_OPS', '1')
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import numpy as np
from scripts.recheck_precision_20261017 import read, put, sha, load, error


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--cache-workspace', type=Path, required=True,
                    help='Read-only historic export cache, used only for diagnosis')
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    out = args.output.resolve()
    if (ROOT/'reports/revd_repair_20261017/precision').resolve() not in out.parents:
        raise ValueError('unsafe diagnostic output')
    out.mkdir(parents=True, exist_ok=False)
    import tensorflow as tf
    from model.run_baseline import official_flags, restore_and_verify, verify_sources, load_samples
    from model.encoder_export import observed_model
    from numeric.encoder.contracts import STAGES
    vendor = ROOT/'vendor/keyword-transformer'
    source = verify_sources(vendor)
    flags, overrides, builder = official_flags(vendor)
    samples, _ = load_samples(ROOT/'data/speech_commands_subset', flags, True)
    sample = samples[0]
    official_meta = read(ROOT/'reports/encoder/export/manifest.json')
    cache = args.cache_workspace.resolve()/'reports/encoder/export'
    if sha(cache/'manifest.json') != sha(ROOT/'reports/encoder/export/manifest.json'):
        raise ValueError('historic cache manifest SHA mismatch')
    pinned = next(s for s in official_meta['samples'] if s['sample_id']==sample['sample_id'])
    cfg = tf.compat.v1.ConfigProto(intra_op_parallelism_threads=1, inter_op_parallelism_threads=1,
                                  device_count={'GPU':0})
    started = time.monotonic()
    tf.keras.backend.clear_session()
    with tf.Graph().as_default(), tf.compat.v1.Session(config=cfg) as session:
        tf.compat.v1.keras.backend.set_session(session)
        tf.compat.v1.keras.backend.set_learning_phase(0)
        tf.compat.v1.set_random_seed(1234)
        model, tr, initial, inputs, stages, final, replay, head = observed_model(tf, builder, flags)
        restored = restore_and_verify(tf, session, model, vendor/'models_data_v2_12_labels/kwt1/best_weights')
        before = session.run(model.weights)
        full = session.run([model.outputs[0], initial, final, replay, inputs, stages],
                           feed_dict={model.inputs[0]:sample['audio']})
        reduced = session.run([model.outputs[0], initial, final, [s[8] for s in stages], [s[9] for s in stages]],
                              feed_dict={model.inputs[0]:sample['audio']})
        after = session.run(model.weights)
        unchanged = all(np.array_equal(a.view(np.uint32), b.view(np.uint32)) for a, b in zip(before, after))
        if not unchanged:
            raise ValueError('model parameters changed')
    rows = []
    def add(name, actual, expected, category, layer=None):
        rows.append(dict(name=name, category=category, layer=layer, **error(actual, expected)))
    for index, name, meta in [(0, 'logits', pinned['logits']), (1, 'encoder_input', pinned['input']),
                              (2, 'encoder_final', pinned['final'])]:
        add(name, full[index][0], load(cache, meta), 'full_fetch_vs_pinned')
        add(name, reduced[index][0], full[index][0], 'reduced_fetch_vs_full_fetch')
    for i, (values, historic) in enumerate(zip(full[5], pinned['layers'])):
        for name, value in zip(STAGES, values):
            add(name, value[0], load(cache, historic['stages'][name]), 'full_fetch_vs_pinned', i+1)
        add('n1', reduced[3][i][0], values[8][0], 'reduced_fetch_vs_full_fetch', i+1)
        add('ffn1', reduced[4][i][0], values[9][0], 'reduced_fetch_vs_full_fetch', i+1)
    pinned_rows = [r for r in rows if r['category']=='full_fetch_vs_pinned']
    reduced_rows = [r for r in rows if r['category']=='reduced_fetch_vs_full_fetch']
    different = [r for r in reduced_rows if not r['bit_equal']]
    first = next((r for r in reduced_rows if r['name']=='encoder_input' and not r['bit_equal']), None)
    if first is None:
        first = next((r for r in reduced_rows if r['layer'] is not None and not r['bit_equal']), None)
    result = dict(status='DIAGNOSIS_COMPLETE', sample_id=sample['sample_id'],
                  source=source, source_hashes={p:sha(ROOT/p) for p in ['model/encoder_export.py',
                              'model/run_baseline.py', 'scripts/recheck_precision_20261017.py',
                              'scripts/diagnose_precision_trace_20261017.py']},
                  runtime=dict(tensorflow=tf.__version__, numpy=np.__version__, python=sys.version),
                  original_export_runtime=official_meta['runtime'], inference_overrides=overrides,
                  official_flags=dict(preprocess=flags.preprocess, feature_type=flags.feature_type,
                                      wanted_words=flags.wanted_words, split_data=flags.split_data),
                  checkpoint_restore_variable_count=restored['variable_count'],
                  checkpoint_restore_all_tensors_match=True, model_parameters_unchanged=unchanged,
                  pinned_tensor_count=len(pinned_rows), pinned_bit_equal_count=sum(r['bit_equal'] for r in pinned_rows),
                  reduced_fetch_compared_tensor_count=len(reduced_rows), reduced_fetch_different_count=len(different),
                  reduced_first_divergence=first, reduced_worst=max(reduced_rows, key=lambda r:r['nrmse']),
                  rows=rows, seconds=time.monotonic()-started,
                  conclusion='Experimentally, changing only requested TF fetch outputs produced numeric differences in this graph/session. Grappler/fusion is a possible mechanism, not an isolated proof, and does not fully explain the 54 historical-cache differences. No coefficient or weight was changed.')
    put(out/'trace_differences.json', result)
    put(out/'restore-verification.json', restored)
    print('TRACE_DIAGNOSIS', out, 'full_pinned_bit_equal=', result['pinned_bit_equal_count'], '/',len(pinned_rows),
          'reduced_different=', len(different), 'first=', first, 'worst=', result['reduced_worst'], flush=True)


if __name__=='__main__':
    main()
