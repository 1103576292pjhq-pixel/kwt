"""Software-only role-alias probe; no RTL process is started."""
import argparse
import copy
import sys
from pathlib import Path

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc
from scripts.revd_offline_tiled_gate import check_suite as check_w1
from scripts.revd_offline_tiled_w2_gate import check_suite as check_w2


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--run-id', required=True)
    a = p.parse_args()
    out = ROOT / 'reports/revd_offline/tiled' / a.run_id
    out.mkdir(parents=True, exist_ok=False)
    tests = []
    for label, source, pm, gate, gate_path in (
        ('W1', 'w1-small-pm4-l2-002', 4, check_w1, 'scripts/revd_offline_tiled_gate.py'),
        ('W2', 'w2-small-pm2-l2-final-001', 2, check_w2, 'scripts/revd_offline_tiled_w2_gate.py'),
    ):
        j = read_json(ROOT / 'reports/revd_offline/tiled' / source / 'summary.json')
        gate(ROOT / 'reports/revd_offline/tiled' / source / 'summary.json', pm, 2)
        alias = copy.deepcopy(j)
        alias['profile'] = 'production'
        alias['cases'] = alias['cases'][:1]
        alias['cases'][0]['case'] = 'synthetic99'
        path = out / (label + '-small-as-production.json')
        put(path, alias)
        try:
            gate(path, pm, 2)
            tests.append({'profile': label, 'rejected': False, 'result': 'FALSE_ACCEPT', 'gate_sha256': sha(ROOT / gate_path)})
        except (ValueError, KeyError, IndexError, OSError) as exc:
            tests.append({'profile': label, 'rejected': True, 'reason': str(exc), 'gate_sha256': sha(ROOT / gate_path)})
    result = {'status': 'PASS' if all(t['rejected'] for t in tests) else 'FAIL', 'created_utc': utc(),
              'software_checker_tests': tests, 'actual_RTL_mutations': 0,
              'source_sha256': {str(Path(__file__).relative_to(ROOT)): sha(__file__)}}
    put(out / 'summary.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
