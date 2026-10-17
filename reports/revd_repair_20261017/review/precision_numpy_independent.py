"""Independent saved-array/aggregation audit; no TensorFlow or model execution."""
from pathlib import Path
import collections
import hashlib
import json
import math
import wave
import numpy as np

ROOT = Path(__file__).resolve().parents[3]
RUN = ROOT / 'reports/revd_repair_20261017/precision/run_20261017_04'
OUT = Path(__file__).with_name('precision_numpy_independent.json')

def read(p):
    return json.loads(p.read_text(encoding='utf-8'))

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def close(a, b):
    assert math.isclose(a, b, rel_tol=1e-12, abs_tol=1e-15), (a, b)

def array(folder, meta):
    p = folder / meta['npy']
    assert sha(p) == meta['npy_sha256'], str(p)
    a = np.load(p, allow_pickle=False)
    assert a.dtype == np.float32 and list(a.shape) == meta['shape'] and np.isfinite(a).all()
    assert hashlib.sha256(np.ascontiguousarray(a, dtype='<f4').tobytes()).hexdigest() == meta['bits_sha256']
    return a

def metrics(a, b):
    a, b = np.asarray(a, np.float64), np.asarray(b, np.float64)
    assert a.shape == b.shape and np.isfinite(a).all() and np.isfinite(b).all()
    sse = float(np.sum(np.square(a-b)))
    rsq = float(np.sum(np.square(b)))
    count = int(b.size)
    return dict(sse=sse, reference_square_sum=rsq, count=count,
                nrmse=math.sqrt(sse/count)/max(math.sqrt(rsq/count), 1e-8),
                max_abs=float(np.max(np.abs(a-b))))

def aggregate(rows):
    layers = []
    for layer in range(1, 13):
        part = [r for r in rows if r['layer'] == layer]
        n = sum(r['count'] for r in part)
        sse = sum(r['sse'] for r in part)
        rsq = sum(r['reference_square_sum'] for r in part)
        layers.append(dict(layer=layer, input_count=len(part), count=n, sse=sse,
                           reference_square_sum=rsq,
                           nrmse=math.sqrt(sse/n)/max(math.sqrt(rsq/n), 1e-8)))
    return layers

def main():
    summary = read(RUN/'summary.json')
    assert summary['evaluator_sha256'] == sha(ROOT/'scripts/recheck_precision_20261017.py')
    assert all(sha(ROOT/p) == digest for p,digest in summary['frozen_source_sha256'].items())
    assert all(sha(ROOT/p) == digest for p,digest in summary['input_manifest_sha256'].items())
    checkpoint = ROOT/'vendor/keyword-transformer/models_data_v2_12_labels/kwt1'
    assert all(sha(checkpoint/p) == digest for p,digest in summary['checkpoint_sha256'].items())
    assert sha(RUN/'current_c_build/libencoder_ref.so') == summary['current_c_library_sha256']
    integrity = read(RUN/'array_integrity_manifest.json')
    assert len(integrity['arrays']) == integrity['array_count']
    assert {r['path'] for r in integrity['arrays']} == {p.relative_to(RUN).as_posix() for p in RUN.rglob('*.npy')}
    assert all(sha(RUN/r['path']) == r['sha256'] and (RUN/r['path']).stat().st_size == r['bytes'] for r in integrity['arrays'])
    live = read(RUN/'official_live.json')
    restore = live['restore']
    assert live['status'] == 'PASS' and restore['variable_count'] == len(restore['variables']) == 162
    assert restore['all_model_variables_exact'] and all(v['checkpoint_max_abs_error'] == 0 for v in restore['variables'])
    live_by_id = {r['sample_id']:r for r in live['samples']}
    samples = {}
    pinned_equal = []
    waveform_checks = []
    packed_weight_checks = 0
    for name in ('export', 'export-test12'):
        folder = RUN/'official_current'/name
        document = read(folder/'manifest.json')
        pinned_path = ROOT/document['pinned_manifest']
        assert sha(pinned_path) == document['pinned_manifest_sha256']
        pinned = read(pinned_path)
        for current, old in zip(document['weights'], pinned['weights']):
            array(folder,current)
            assert current['bits_sha256'] == old['bits_sha256']
            packed_weight_checks += 1
        for key,current in document['classifier'].items():
            array(folder,current)
            assert current['bits_sha256'] == pinned['classifier'][key]['bits_sha256']
            packed_weight_checks += 1
        old_by_id = {s['sample_id']:s for s in pinned['samples']}
        for sample in document['samples']:
            sid = sample['sample_id']
            assert sid not in samples
            samples[sid] = folder,sample,document
            source = ROOT/sample['source_audio']['path']
            assert sha(source) == sample['source_audio']['sha256']
            if sample['partition'] == 'synthetic_silence':
                wav = np.load(source,allow_pickle=False)
                assert wav.shape == (1,16000) and np.count_nonzero(wav) == 0
            else:
                with wave.open(str(source),'rb') as f:
                    assert (f.getframerate(),f.getnchannels(),f.getsampwidth()) == (16000,1,2)
                    pcm = np.frombuffer(f.readframes(f.getnframes()),dtype='<i2')
                wav = pcm.astype(np.float32)/32768
                assert wav.size == 16000
            assert hashlib.sha256(np.ascontiguousarray(wav,dtype='<f4').tobytes()).hexdigest() == live_by_id[sid]['preprocessed_waveform_bits_sha256']
            waveform_checks.append(dict(sample_id=sid, partition=sample['partition'], nonzero=int(np.count_nonzero(wav))))
            old = old_by_id[sid]
            pairs = [(sample[k],old[k]) for k in ('input','final','logits')]
            pairs += [(l['stages'][k],old['layers'][i]['stages'][k]) for i,l in enumerate(sample['layers']) for k in ('n1','ffn1')]
            count = 0
            for current_meta,old_meta in pairs:
                array(folder,current_meta)
                count += current_meta['bits_sha256'] == old_meta['bits_sha256']
            assert count == live_by_id[sid]['pinned_equal_tensor_count']
            pinned_equal.append(dict(sample_id=sid,count=len(pairs),equal=count))
    assert len(samples) == 15
    provenance = read(RUN/'input_provenance.json')
    assert len(provenance) == 15 and {r['sample_id'] for r in provenance} == set(samples)
    for row in provenance:
        folder,sample,_ = samples[row['sample_id']]
        assert sha(ROOT/row['export_manifest']) == row['export_manifest_sha256']
        assert row['input'] == sample['input'] and row['source_audio'] == sample['source_audio']
    fixed = read(RUN/'fixed_ffn1_cases.json')
    frozen = read(ROOT/'reports/prototype/vectors/manifest.json')
    configs = {c['layer']:c['config'] for c in frozen['cases']}
    assert len(fixed) == 180 and len({(r['sample_id'],r['layer']) for r in fixed}) == 180
    recalculated = []
    for row in fixed:
        folder,sample,_ = samples[row['sample_id']]
        y = array(folder,sample['layers'][row['layer']-1]['stages']['ffn1'])
        p = RUN/row['result_npy']
        assert sha(p) == row['result_sha256'] and row['config'] == configs[row['layer']]
        q = np.load(p,allow_pickle=False)
        assert q.dtype == np.int32 and q.shape == (99,256)
        new = metrics(q.astype(np.float64)*row['config']['output_scale'],y)
        for key,value in new.items():close(value,row[key])
        recalculated.append(dict(layer=row['layer'],**new))
    layers = aggregate(recalculated)
    for current,reported in zip(layers,summary['fixed_ffn1_15_inputs']['layers']):
        for k,v in current.items():close(v,reported[k])
    prototype = read(RUN/'prototype36_cases.json')
    assert len(prototype) == 36
    prototype_rows = []
    for row,case in zip(prototype,frozen['cases']):
        assert row['layer'] == case['layer'] and row['sample_id'] == 'prototype36/'+case['sample_id']
        path = RUN/row['result_npy'];assert sha(path) == row['result_sha256']
        expected_q = ROOT/'reports/prototype/vectors'/case['arrays']['Yq']['path']
        assert sha(expected_q) == case['arrays']['Yq']['sha256']
        assert np.array_equal(np.load(path,allow_pickle=False),np.load(expected_q,allow_pickle=False))
        expected_y = ROOT/'reports/model/baseline'/case['source_arrays']['Y']['path']
        assert sha(expected_y) == case['source_arrays']['Y']['sha256']
        new = metrics(np.load(path,allow_pickle=False).astype(np.float64)*row['config']['output_scale'],np.load(expected_y,allow_pickle=False))
        for key,value in new.items():close(value,row[key])
        prototype_rows.append(dict(layer=row['layer'],**new))
    prototype_layers = aggregate(prototype_rows)
    for current,reported in zip(prototype_layers,summary['prototype36_separate']['layers']):
        for k,v in current.items():close(v,reported[k])
    classes = read(RUN/'classification_cases.json')
    assert len(classes) == 15
    class_rows = []
    for row in classes:
        folder,sample,document = samples[row['sample_id']]
        official = array(folder,sample['logits'])
        path = RUN/'fp32'/row['sample_id']/'logits.npy'
        assert sha(path) == row['design_logits_sha256']
        design = np.load(path,allow_pickle=False)
        oi,di = int(np.argmax(official)),int(np.argmax(design))
        truth = document['label_to_index'][sample['ground_truth_label']]
        assert row['ground_truth'] == sample['ground_truth_label']
        assert row['official_top1'] == document['labels'][oi] and row['design_top1'] == document['labels'][di]
        assert row['official_correct'] == (oi==truth) and row['design_correct'] == (di==truth) and row['same_top1'] == (oi==di)
        for key,value in metrics(design,official).items():close(value,row['logits_error'][key])
        class_rows.append(row)
    grouped = {}
    predicates = {'all15_including_synthetic':lambda r:True,'real_audio14':lambda r:r['partition']!='synthetic_silence',
                  'published_test12':lambda r:r['partition']=='testing','validation_real':lambda r:r['partition']=='validation',
                  'synthetic_silence':lambda r:r['partition']=='synthetic_silence'}
    for name,predicate in predicates.items():
        group=[r for r in class_rows if predicate(r)];n=len(group)
        result=dict(n=n,official_correct=sum(r['official_correct'] for r in group),design_correct=sum(r['design_correct'] for r in group),agreement_count=sum(r['same_top1'] for r in group))
        reported=summary['fp32_full_encoder']['classification'][name]
        for k,v in result.items():assert reported[k]==v
        close(reported['accuracy_drop_percentage_points'],100*(result['official_correct']-result['design_correct'])/n)
        grouped[name]=result
    worst=max(r['nrmse'] for r in layers);old_worst=max(r['nrmse'] for r in prototype_layers)
    close(worst,summary['fixed_ffn1_15_inputs']['worst_layer_nrmse']);close(old_worst,summary['prototype36_separate']['worst_layer_nrmse'])
    result=dict(status='PASS_INDEPENDENT_SAVED_ARRAY_AND_AGGREGATE_AUDIT',numpy=np.__version__,run=RUN.relative_to(ROOT).as_posix(),
                audit_source_sha256=sha(Path(__file__)),evaluator_sha256=summary['evaluator_sha256'],array_count_hashed=integrity['array_count'],
                fixed_cases=180,fixed_values=sum(r['count'] for r in recalculated),fixed_layers=layers,
                fixed_worst_nrmse_fraction=worst,fixed_worst_nrmse_percent=100*worst,prototype_cases=36,
                prototype_worst_nrmse_fraction=old_worst,prototype_worst_nrmse_percent=100*old_worst,
                classification=grouped,pinned_tensor_comparison=pinned_equal,pinned_equal=sum(r['equal'] for r in pinned_equal),
                pinned_compared=sum(r['count'] for r in pinned_equal),waveform_checks=waveform_checks,
                packed_encoder_weight_and_head_checks=packed_weight_checks,checkpoint_variables_verified_in_saved_restore=162,
                all_frozen_sources_and_input_manifests_match=True,source_audio_reconstructed_from_D_wav_or_explicit_zero=True,
                scope='Independent NumPy re-read, SHA, metrics, grouping and PCM16 decode only; no TF inference, no precision tuning, no hardware simulation.')
    with OUT.open('x',encoding='utf-8') as f:f.write(json.dumps(result,indent=2)+'\n')
    print(json.dumps({k:v for k,v in result.items() if k not in ['fixed_layers','waveform_checks','pinned_tensor_comparison']},indent=2))

if __name__=='__main__':main()
