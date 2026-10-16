"""Independent readback of completed frozen RTL jobs; starts no simulations."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'reports/system/root-encoder-completed-readback.json'
STAGES = ('q', 'k', 'v', 'scores', 'prob', 'context', 'attn', 'r1', 'n1',
          'ffn1', 'gelu', 'ffn2', 'r2', 'y')


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))


def require(ok, message):
    if not ok:
        raise ValueError(message)


def hashes(mapping):
    require(bool(mapping), 'empty input/source inventory')
    for name, digest in mapping.items():
        path = (ROOT / name).resolve()
        require(path.is_relative_to(ROOT.resolve()), 'inventory path escapes workspace')
        require(sha(path) == digest, 'stale evidence: ' + name)


def main():
    result = {'status': 'RUNNING', 'started_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'completed RTL records only; no CPU or formal contest acceptance',
              'no_simulations_started': True, 'overall_local_draft_accepted': False}
    try:
        freeze_path = ROOT / 'work/encoder_source_freeze.json'
        freeze = load(freeze_path)
        hashes(freeze['source_sha256'])
        require(sha(ROOT / 'work/fp32_handoff.json') == freeze['fp32_handoff_sha256'], 'FP32 changed')
        expected = {}
        for name, key in [('reference', 'reference_manifest_sha256'),
                          ('reference-test12', 'test12_manifest_sha256')]:
            path = ROOT / 'reports/encoder' / name / 'manifest.json'
            require(sha(path) == freeze[key], 'reference manifest changed')
            expected[name] = {s['sample_id'] for s in load(path)['samples']}
        batch = load(ROOT / 'reports/encoder/verification/case-batch/progress.json')
        records = []
        unique = set()
        traced_words = 0
        for item in batch.get('results', []):
            if item['status'] != 'PASS':
                continue
            path = (ROOT / item['record']).resolve()
            require(path.is_relative_to(ROOT.resolve()), 'record outside workspace')
            if 'record_sha256' in item:
                require(sha(path) == item['record_sha256'], 'published case record changed')
            r = load(path)
            out = path.parent
            require(r['status'] == 'PASS' and r['exit_code'] == 0, 'child did not pass')
            require(r['geometry'] == [99, 64, 256] and not r['attention'], 'wrong dimensions/mode')
            require(r['layers'] == 12 and r['output_words'] == 76032 and r['bit_mismatches'] == 0,
                    'partial full encoder')
            require(r['pid'] > 0 and re.fullmatch('[0-9a-f]{32}', r['run_id']), 'missing process identity')
            require(r['completed_unix'] >= r['started_unix'] >= freeze['created_unix'], 'old execution')
            for key in ('source_sha256', 'compiled_source_sha256', 'input_sha256'):
                hashes(r[key])
            require(r['input_sha256']['work/encoder_source_freeze.json'] == sha(freeze_path),
                    'execution does not bind this freeze')
            command = r['command']
            require(command[1:5] == ['+CASE=case', '+WEIGHTS=weights', '+LAYERS=12', '+OUTPUT=output.hex'],
                    'not a full execution command')
            executable = out / 'obj/Vtb_encoder'
            require(command[0].replace('/mnt/c/', 'C:/') == executable.as_posix(), 'wrong executable path')
            for name, key in [('obj/Vtb_encoder', 'binary_sha256'), ('output.hex', 'output_sha256'),
                              ('simulation.log', 'log_sha256'), ('compile.log', 'compile_log_sha256'),
                              ('build.json', 'build_key_sha256')]:
                require(sha(out / name) == r[key], 'execution artifact changed: ' + name)
            require(r['case'] in expected[r['reference']], 'unknown reference case')
            base = ROOT / 'reports/encoder' / r['reference'] / 'cases' / r['case']
            wanted = []
            for layer in range(12):
                wanted.extend((base / f'layer_{layer:02d}/y.hex').read_text(encoding='utf-8').splitlines())
            actual = (out / 'output.hex').read_text(encoding='utf-8').splitlines()
            require(actual == wanted and len(actual) == 76032, 'full output differs from C')
            require(all((int(word, 16) >> 23) & 255 != 255 for word in actual), 'nonfinite output')
            log = (out / 'simulation.log').read_text(encoding='utf-8')
            require('ENCODER_PASS layers=12 words=76032' in log, 'missing completion marker')
            layers = re.findall(r'ENCODER_LAYER_PASS layer=(\d+) words=(\d+) cycles=(\d+) flags=([0-9a-f]+)', log)
            require(len(layers) == 12 and [int(x[0]) for x in layers] == list(range(12)), 'layer log incomplete')
            require(all(int(x[1]) == 6336 and int(x[2]) > 0 and int(x[3], 16) <= 31 for x in layers),
                    'invalid per-layer counters')
            if r.get('trace_words'):
                require(sha(out / 'trace.txt') == r['trace_sha256'], 'trace changed')
                arrays = {}
                for layer in range(12):
                    for stage, name in enumerate(STAGES):
                        words = (base / f'layer_{layer:02d}' / (name + '.hex')).read_text(encoding='utf-8').splitlines()
                        arrays[layer, stage] = (words, bytearray(len(words)))
                seen = 0
                with (out / 'trace.txt').open(encoding='utf-8') as stream:
                    for line in stream:
                        layer, stage, address, bits = line.split()
                        words, marked = arrays[int(layer), int(stage)]
                        index = int(address)
                        require(0 <= index < len(words) and not marked[index] and bits == words[index],
                                'trace mismatch, duplicate, or invalid address')
                        marked[index] = 1
                        seen += 1
                require(seen == r['trace_words'] == 1603800 and
                        all(all(marked) for words, marked in arrays.values()), 'partial trace')
                traced_words += seen
            if item['name'] != 'repeat':
                require((r['reference'], r['case']) not in unique, 'duplicate unique case')
                unique.add((r['reference'], r['case']))
            records.append({'name': item['name'], 'record': item['record'], 'record_sha256': sha(path),
                            'pid': r['pid'], 'case': r['case'], 'run_id': r['run_id'],
                            'output_sha256': r['output_sha256'], 'output_words': len(actual)})
        require(records, 'no completed RTL jobs available')
        result.update(status='COMPLETED_RECORDS_READBACK_PASS', freeze_sha256=sha(freeze_path),
                      batch_run_id=batch['run_id'], completed_processes=len(records),
                      unique_full12_cases=len(unique), full12_output_words=sum(r['output_words'] for r in records),
                      independently_compared_trace_words=traced_words, expected_unique_cases=15, records=records,
                      own_source_sha256=sha(Path(__file__)))
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
        raise
    finally:
        result['completed_utc'] = datetime.now(timezone.utc).isoformat()
        OUT.parent.mkdir(parents=True, exist_ok=True)
        if OUT.exists():
            old = OUT.parent / 'root-encoder-readback-history'
            old.mkdir(exist_ok=True)
            (old / (datetime.now(timezone.utc).strftime('%Y%m%d-%H%M%S-%f') + '.json')).write_bytes(OUT.read_bytes())
        OUT.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
        print(json.dumps({k: v for k, v in result.items() if k != 'records'}, indent=2))


if __name__ == '__main__':
    main()
