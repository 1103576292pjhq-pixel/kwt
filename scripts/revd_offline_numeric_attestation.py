"""Fresh converter and precision receipts bound to the selected RTL evidence."""
from pathlib import Path
import argparse
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import command, put, sha, read_json, run_id, utc
from scripts.revd_offline_final_regression import tool_inventory


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--suite', required=True)
    args = parser.parse_args()
    suite = (ROOT / args.suite).resolve()
    if ROOT not in suite.parents:
        raise ValueError('selected suite outside workspace')
    out = ROOT / 'reports/revd_offline/numeric_attestation' / run_id()
    out.mkdir(parents=True, exist_ok=False)
    names = ['scripts/revd_offline_numeric_attestation.py', 'scripts/revd_offline_precision.py',
        'scripts/revd_offline_convert.py', 'scripts/revd_offline_gate.py',
        'scripts/revd_offline_common.py', 'scripts/revd_offline_final_regression.py',
        'numeric/fixedpoint.py', 'reports/prototype/vectors/manifest.json',
        'reports/model/baseline/manifest.json', str(suite.relative_to(ROOT))]
    sources = {name: sha(ROOT / name) for name in names}
    for name in names:
        target = out / 'source_snapshot' / name
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes((ROOT / name).read_bytes())
    tools = tool_inventory()
    result = {'status': 'RUNNING', 'started_utc': utc(), 'tool_binary_sha256_before': tools,
              'source_sha256_before': sources, 'tests': []}
    put(out / 'result.json', result)
    try:
        for kind, script, extra in [('precision', 'revd_offline_precision.py', ['--suite', str(suite)]),
                                     ('conversion', 'revd_offline_convert.py', [])]:
            base = ROOT / 'reports/revd_offline' / kind
            before = set(base.glob('*/summary.json'))
            c = command([sys.executable, '-B', ROOT / 'scripts' / script, *extra], out / (kind + '.log'), timeout=180)
            added = set(base.glob('*/summary.json')) - before
            if c['exit_code'] != 0 or len(added) != 1:
                raise ValueError('fresh numeric artifact/process failure ' + kind)
            summary = added.pop()
            report = read_json(summary)
            if report['status'] not in ('PASS', 'PASS_LOCAL_ENGINEERING_SUBSET') or len(report['cases']) != 36:
                raise ValueError('fresh numeric scope incomplete ' + kind)
            result['tests'].append({'kind': kind, 'summary': str(summary.relative_to(ROOT)),
                'summary_sha256': sha(summary), 'command': c})
        result['source_unchanged'] = all(sha(ROOT / name) == digest for name, digest in sources.items())
        result['tool_binary_sha256_after'] = tool_inventory()
        result['tools_unchanged'] = result['tool_binary_sha256_after'] == tools
        if not result['source_unchanged'] or not result['tools_unchanged']:
            raise ValueError('numeric tool/source changed during validation')
        result['status'] = 'PASS'
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
    result['finished_utc'] = utc()
    put(out / 'result.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
