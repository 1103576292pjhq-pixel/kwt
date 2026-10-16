"""Read-only root audit of frozen reference release; no model or RTL run."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'reports/system/root-reference-readback.json'


def load(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition, message):
    if not condition:
        raise ValueError(message)


def bound_path(base, name):
    path = (base / name).resolve()
    require(path.is_relative_to(base.resolve()), 'path outside reference bundle')
    return path


def tensor(base, record):
    raw = bound_path(base, record['bin']).read_bytes()
    require(hashlib.sha256(raw).hexdigest() == record['bits_sha256'], 'bin hash mismatch')
    require(len(raw) == record['words'] * 4, 'partial tensor')
    words = list(struct.unpack('<' + 'I' * record['words'], raw))
    text = bound_path(base, record['hex'])
    require(sha(text) == record['hex_sha256'], 'hex hash mismatch')
    require([int(line, 16) for line in text.read_text(encoding='utf-8').splitlines()] == words,
            'hex/bin words disagree')
    require(all((word >> 23) & 255 != 255 for word in words), 'nonfinite tensor')
    return raw


def main():
    result = {'status': 'RUNNING', 'started_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'frozen reference integrity and layer chaining only',
              'no_model_or_simulation_started': True}
    OUT.parent.mkdir(parents=True, exist_ok=True)
    try:
        handoff_path = ROOT / 'work/encoder_reference_handoff.json'
        handoff = load(handoff_path)
        require(handoff['status'] == 'PASS' and handoff['read_only_after_handoff'],
                'reference not released/frozen')
        count = 0
        for group in ['source_sha256', 'artifacts_sha256']:
            require(bool(handoff[group]), 'missing released fingerprints')
            for name, digest in handoff[group].items():
                require(sha(bound_path(ROOT, name)) == digest, 'stale release: ' + name)
                count += 1
        totals = {'samples': 0, 'layers': 0, 'layer_output_words': 0}
        bundles = []
        for name, expected_count in [('reference', 3), ('reference-test12', 12)]:
            base = ROOT / 'reports/encoder' / name
            manifest = load(base / 'manifest.json')
            require(len(manifest['samples']) == expected_count, 'wrong case count')
            require(manifest['weight_words'] == 49792 and len(manifest['weights']) == 12,
                    'incomplete parameter schedule')
            ids = [s['sample_id'] for s in manifest['samples']]
            require(len(set(ids)) == expected_count, 'duplicate cases')
            for sample in manifest['samples']:
                require(len(sample['layers']) == 12, 'partial layer sequence')
                previous = tensor(base, sample['input'])
                require(len(previous) == 99 * 64 * 4, 'wrong input size')
                for layer_index, layer in enumerate(sample['layers']):
                    require(layer['layer_index'] == layer_index, 'wrong layer ordering')
                    require(tensor(base, layer['input']) == previous, 'broken layer dependency')
                    require(set(layer['stages']) == set(manifest['stages']), 'missing stage oracle')
                    previous = tensor(base, layer['stages']['y'])
                    require(len(previous) == 99 * 64 * 4, 'partial layer output')
                    totals['layers'] += 1
                    totals['layer_output_words'] += 99 * 64
                require(tensor(base, sample['final']) == previous, 'final output differs from layer 11')
                totals['samples'] += 1
            if expected_count == 12:
                dataset = load(ROOT / 'data/encoder_test_subset/manifest.json')
                require(set(ids) == {s['sample_id'] for s in dataset['samples']}, 'test set changed')
                require({s['ground_truth_label'] for s in manifest['samples']} == set(manifest['labels']),
                        'missing one of the twelve ground-truth classes')
                by_id = {s['sample_id']: s for s in manifest['samples']}
                for sample in dataset['samples']:
                    require(sha(ROOT / 'data/encoder_test_subset' / sample['relative_path']) == sample['sha256'],
                            'test WAV changed')
                    require(by_id[sample['sample_id']]['ground_truth_label'] == sample['ground_truth_label'],
                            'test label changed')
            bundles.append({'name': name, 'samples': expected_count, 'manifest_sha256': sha(base / 'manifest.json')})
        result.update(status='PASS', release_files_checked=count, totals=totals, bundles=bundles,
                      handoff_sha256=sha(handoff_path), own_source_sha256=sha(Path(__file__)),
                      note='No claim of RTL, SoC, PPA, or official 600-sample acceptance.')
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
        raise
    finally:
        result['completed_utc'] = datetime.now(timezone.utc).isoformat()
        OUT.write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
        print(json.dumps(result, indent=2, ensure_ascii=False))


if __name__ == '__main__':
    main()
