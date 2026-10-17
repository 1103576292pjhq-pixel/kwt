"""Verify saved precision artifacts and quantify historical cache differences."""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import wave
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import numpy as np
from scripts.recheck_precision_20261017 import read, put, sha, load, error


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--run', type=Path, required=True)
    ap.add_argument('--cache-workspace', type=Path, required=True)
    ap.add_argument('--current-original-export', type=Path)
    args = ap.parse_args()
    run = args.run.resolve()
    if (ROOT/'reports/revd_repair_20261017/precision').resolve() not in run.parents:
        raise ValueError('unsafe precision run')
    summary = read(run/'summary.json')
    if summary['evaluator_sha256'] != sha(ROOT/'scripts/recheck_precision_20261017.py'):
        raise ValueError('run bound to another evaluator version')
    fixed = read(run/'fixed_ffn1_cases.json')
    if len(fixed) != 180:
        raise ValueError('incorrect FFN1 case count')
    fresh = {}
    old = {}
    for name in ['export', 'export-test12']:
        root = run/'official_current'/name
        document = read(root/'manifest.json')
        cache = args.cache_workspace.resolve()/'reports/encoder'/name
        original = read(ROOT/'reports/encoder'/name/'manifest.json')
        if sha(cache/'manifest.json') != document['pinned_manifest_sha256']:
            raise ValueError('historic manifest mismatch')
        for sample in document['samples']:
            fresh[sample['sample_id']] = (root, sample)
        for sample in original['samples']:
            old[sample['sample_id']] = (cache, sample)
    checked = []
    for row in fixed:
        root, sample = fresh[row['sample_id']]
        expected = load(root, sample['layers'][row['layer']-1]['stages']['ffn1'])
        path = run/row['result_npy']
        if sha(path) != row['result_sha256']:
            raise ValueError('fixed result checksum mismatch')
        q = np.load(str(path), allow_pickle=False)
        if q.dtype != np.int32 or q.shape != (99, 256):
            raise ValueError('fixed output format mismatch')
        values = error(q.astype(np.float64)*row['config']['output_scale'], expected)
        for key in ['sse', 'reference_square_sum', 'nrmse', 'max_abs']:
            if not np.isclose(values[key], row[key], rtol=1e-13, atol=1e-15):
                raise ValueError('stored metric inconsistent: ' + key)
        checked.append(values)
    comparisons = []
    for sid, (root, current) in fresh.items():
        cache, historical = old[sid]
        pairs = [(name, None, current[name], historical[name]) for name in ['input', 'final', 'logits']]
        pairs += [(name, i+1, layer['stages'][name], historical['layers'][i]['stages'][name])
                  for i, layer in enumerate(current['layers']) for name in ['n1', 'ffn1']]
        for name, layer, current_meta, old_meta in pairs:
            actual, expected = load(root, current_meta), load(cache, old_meta)
            unequal = np.flatnonzero(actual.reshape(-1).view(np.uint32) != expected.reshape(-1).view(np.uint32))
            comparisons.append(dict(sample_id=sid, name=name, layer=layer,
                                    current_sha256=current_meta['npy_sha256'], old_sha256=old_meta['npy_sha256'],
                                    first_differing_element=list(map(int, np.unravel_index(int(unequal[0]), actual.shape))) if unequal.size else None,
                                    **error(actual, expected)))
    different = [r for r in comparisons if not r['bit_equal']]
    classes = []
    for row in read(run/'classification_cases.json'):
        sid = row['sample_id']
        root, current = fresh[sid]
        cache, historical = old[sid]
        actual, expected = load(root, current['logits']), load(cache, historical['logits'])
        classes.append(dict(sample_id=sid, current_top1=int(np.argmax(actual)),
                            historical_top1=int(np.argmax(expected)), same_top1=int(np.argmax(actual))==int(np.argmax(expected))))
    audio = []
    baseline = read(ROOT/'reports/model/baseline/manifest.json')
    for sample in baseline['samples']:
        path = ROOT/'reports/model/baseline'/sample['audio_array']['path']
        if sha(path) != sample['audio_array']['sha256']:
            raise ValueError('old baseline audio SHA mismatch')
        value = np.load(str(path), allow_pickle=False)
        if sample['partition']=='validation':
            wav_path = ROOT/'data/speech_commands_subset'/sample['relative_path']
            with wave.open(str(wav_path), 'rb') as w:
                pcm = np.frombuffer(w.readframes(w.getnframes()), dtype='<i2').astype(np.float32)/32768
            same = bool(np.array_equal(value.reshape(-1), pcm))
        else:
            same = bool(np.count_nonzero(value)==0)
        audio.append(dict(sample_id=sample['sample_id'], source_audio_sha256=sha(path),
                          baseline_matches_pcm16_decode_or_explicit_zero=same,
                          waveform_bits_sha256=hashlib.sha256(value.astype('<f4').tobytes()).hexdigest()))
        if not same:
            raise ValueError('baseline waveform differs')
    silence_path = ROOT/'data/encoder_test_subset/_silence_/f5468c2d20ffa8aa0bd3.wav'
    with wave.open(str(silence_path), 'rb') as w:
        pcm = np.frombuffer(w.readframes(w.getnframes()), dtype='<i2')
    silence = dict(sample_id='test_silence_f5468c2d20ff', pcm16_nonzero_count=int(np.count_nonzero(pcm)),
                   pcm16_min=int(pcm.min()), pcm16_max=int(pcm.max()), source_audio_sha256=sha(silence_path),
                   ground_truth='_silence_', source_is_all_zero=bool(not np.count_nonzero(pcm)))
    original_comparisons, original_pinned_comparisons = [], []
    if args.current_original_export:
        original_root = args.current_original_export.resolve()
        original_doc = read(original_root/'manifest.json')
        for sample in original_doc['samples']:
            root, current = fresh[sample['sample_id']]
            pairs = [(name, None, current[name], sample[name]) for name in ['input', 'final', 'logits']]
            pairs += [(name, i+1, layer['stages'][name], sample['layers'][i]['stages'][name])
                      for i, layer in enumerate(current['layers']) for name in ['n1', 'ffn1']]
            for name, layer, cmeta, ometa in pairs:
                original_comparisons.append(dict(sample_id=sample['sample_id'], name=name, layer=layer,
                                                 **error(load(root, cmeta), load(original_root, ometa))))
                cache, historic = old[sample['sample_id']]
                hmeta = historic[name] if layer is None else historic['layers'][layer-1]['stages'][name]
                original_pinned_comparisons.append(dict(sample_id=sample['sample_id'], name=name, layer=layer,
                                                        **error(load(original_root, ometa), load(cache, hmeta))))
    put(run/'historical_tensor_comparisons.json', dict(compared_tensor_count=len(comparisons),
         bit_equal_tensor_count=len(comparisons)-len(different), differing_tensor_count=len(different),
         differences=different, all_comparisons=comparisons, classification_comparison=classes,
         waveform_checks=audio, published_silence=silence,
         current_original_export_comparisons=original_comparisons,
         current_original_export_vs_pinned=original_pinned_comparisons))
    assets = [p for p in run.rglob('*.npy') if p.is_file()]
    put(run/'array_integrity_manifest.json', dict(array_count=len(assets),
        arrays=[dict(path=str(p.relative_to(run)), sha256=sha(p), bytes=p.stat().st_size) for p in sorted(assets)]))
    result = dict(status='PASS_SAVED_ARTIFACT_SELF_AUDIT', evaluator_sha256=summary['evaluator_sha256'],
                  auditor_sha256=sha(Path(__file__)), fixed_cases_recomputed=len(checked),
                  fixed_output_values_checked=sum(r['count'] for r in checked),
                  current_official_snapshot_array_count=len(assets),
                  cached_comparison_tensor_count=len(comparisons), cached_differing_tensor_count=len(different),
                  cached_differing_sample_ids=sorted({r['sample_id'] for r in different}),
                  cached_worst_nrmse=max(comparisons, key=lambda r:r['nrmse']),
                  cached_worst_maxabs=max(comparisons, key=lambda r:r['max_abs']),
                  cached_classifications_all_unchanged=all(r['same_top1'] for r in classes),
                  current_original_export_compared_count=len(original_comparisons),
                  current_original_export_bit_equal_count=sum(r['bit_equal'] for r in original_comparisons),
                  current_original_export_pinned_compared_count=len(original_pinned_comparisons),
                  current_original_export_pinned_bit_equal_count=sum(r['bit_equal'] for r in original_pinned_comparisons),
                  published_silence=silence,
                  scope='Artifact/metric consistency check; does not establish contest acceptance or population accuracy.')
    put(run/'self_audit.json', result)
    print(json.dumps(result, indent=2), flush=True)


if __name__=='__main__':
    main()
