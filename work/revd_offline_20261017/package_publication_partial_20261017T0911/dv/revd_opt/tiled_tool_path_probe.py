"""Software-only probes for executable path and version receipt aliases."""
import argparse
import sys
from pathlib import Path

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import put, sha, utc
from tiled_gate_negatives import clone, rewrite
from scripts.revd_offline_tiled_gate import check_case as check_w1
from scripts.revd_offline_tiled_w2_gate import check_case as check_w2


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--run-id', required=True)
    a = p.parse_args()
    out = ROOT / 'reports/revd_offline/tiled' / a.run_id
    out.mkdir(parents=True, exist_ok=False)
    tests = []
    for label, source, gate, gate_path in (
        ('W1', 'w1-production-pm4-l1-001', check_w1, 'scripts/revd_offline_tiled_gate.py'),
        ('W2', 'w2-production-pm4-l1-final-002', check_w2, 'scripts/revd_offline_tiled_w2_gate.py'),
    ):
        for field in ('path', 'version'):
            dest = out / (label + '_' + field)
            r = clone(ROOT / 'reports/revd_offline/tiled' / source / 'synthetic99', dest)
            gate(dest / 'run_manifest.json')
            if field == 'path':
                r['tools']['iverilog']['path'] = '/usr/bin/true'
                r['tools']['iverilog']['sha256'] = sha(Path('/usr/bin/true'))
            else:
                r['tools']['iverilog']['version'] = 'FICTITIOUS_TOOL_VERSION'
            rewrite(dest, r)
            try:
                gate(dest / 'run_manifest.json')
                tests.append({'profile': label, 'field': field, 'rejected': False, 'result': 'FALSE_ACCEPT', 'gate_sha256': sha(ROOT / gate_path)})
            except (ValueError, KeyError, IndexError, OSError) as exc:
                tests.append({'profile': label, 'field': field, 'rejected': True, 'reason': str(exc), 'gate_sha256': sha(ROOT / gate_path)})
    result = {'status': 'PASS' if all(t['rejected'] for t in tests) else 'FAIL', 'created_utc': utc(),
              'software_checker_tests': tests, 'actual_RTL_mutations': 0,
              'source_sha256': {str(Path(__file__).relative_to(ROOT)): sha(__file__)}}
    put(out / 'summary.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
