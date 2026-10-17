"""Independently bind the root's actual precision repeat to the author's run."""
from pathlib import Path
import hashlib
import json
import sys

ROOT = Path(__file__).resolve().parents[2]
BASE = ROOT / 'reports/revd_repair_20261017/precision'

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

a, b = [BASE / ('run_20261017_' + number) for number in ('04', '05')]
reports = [json.loads((p / 'summary.json').read_text(encoding='utf-8')) for p in (a, b)]
assert all(r['status'] == 'PASS_LOCAL_ENGINEERING_PRECISION_RECHECK' for r in reports)
assert all(r['evaluator_sha256'] == sha(ROOT / 'scripts/recheck_precision_20261017.py') for r in reports)
arrays = [{p.relative_to(folder).as_posix(): sha(p) for p in folder.rglob('*.npy')} for folder in (a, b)]
assert arrays[0] and arrays[0] == arrays[1], 'fresh author/root output arrays differ'
for field in ('frozen_source_sha256', 'checkpoint_sha256', 'input_manifest_sha256'):
    assert reports[0][field] == reports[1][field], field
for section in ('fixed_ffn1_15_inputs', 'prototype36_separate'):
    assert reports[0][section]['layers'] == reports[1][section]['layers'], section
assert reports[0]['fp32_full_encoder'] == reports[1]['fp32_full_encoder']
for name, digest in reports[1]['frozen_source_sha256'].items():
    assert sha(ROOT / name) == digest, name
result = {
    'status': 'PASS', 'scope': 'Two actual fresh host precision executions; not RTL or official600 acceptance.',
    'author_summary_sha256': sha(a / 'summary.json'), 'root_summary_sha256': sha(b / 'summary.json'),
    'root_execution_exit_code_observed': 0,
    'identical_npy_files': len(arrays[0]), 'npy_sha256': arrays[1],
    'identical_layer_and_classification_metrics': True,
    'current_frozen_source_files': len(reports[1]['frozen_source_sha256']),
    'verifier_sha256': sha(Path(__file__)),
}
target = ROOT / 'reports/revd_repair_20261017/root-precision-repeat.json'
target.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
print('ROOT_PRECISION_REPEAT_PASS', len(arrays[0]))
