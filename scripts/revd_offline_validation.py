"""Fresh validation batches bound to tool bytes without editing frozen runners."""
from pathlib import Path
import argparse
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import command, put, sha, read_json, run_id, utc
from scripts.revd_offline_final_regression import tool_inventory
from scripts.revd_offline_gate import check_protocol, check_numeric, check_suite, check_case


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--scope', choices=['protocol-numeric', 'pm2full36', 'comparison'], required=True)
    args = p.parse_args()
    rid = run_id()
    out = ROOT / 'reports/revd_offline/tool_bound_validation' / rid
    out.mkdir(parents=True, exist_ok=False)
    names = ['scripts/revd_offline_validation.py', 'scripts/revd_offline_final_regression.py',
        'scripts/revd_offline_common.py', 'scripts/revd_offline_gate.py',
        'rtl/revd_opt/core_stream_frontend_opt.sv', 'rtl/revd/core_stream_frontend.sv',
        'rtl/revd/banked_sp16.sv', 'rtl/revd/quant_epilogue.sv', 'numeric/fixedpoint.py',
        'dv/revd_opt/core_tb.sv', 'dv/revd_opt/core_runner.py', 'dv/revd_opt/protocol.py',
        'dv/revd_opt/numeric_checks.py', 'scripts/revd_offline_compare.py']
    sources = {name: sha(ROOT / name) for name in names}
    tools = tool_inventory()
    result = {'status': 'RUNNING', 'started_utc': utc(), 'scope': args.scope,
        'source_sha256_before': sources, 'tool_binary_sha256_before': tools, 'tests': []}
    put(out / 'result.json', result)
    try:
        if args.scope == 'protocol-numeric':
            batches = [('protocol', 'dv/revd_opt/protocol.py'), ('numeric', 'dv/revd_opt/numeric_checks.py')]
        elif args.scope == 'comparison':
            batches = [('comparison', 'scripts/revd_offline_compare.py')]
        else:
            batches = [('core', 'dv/revd_opt/core_runner.py')]
        for kind, entry in batches:
            base = ROOT / 'reports/revd_offline' / kind
            before = set(base.glob('*/summary.json'))
            extra = ['--profile', 'full36', '--pm', '2', '--run-id', 'pm2-toolbound-' + rid] if kind == 'core' else []
            c = command([sys.executable, '-B', ROOT / entry, *extra], out / (kind + '.log'),
                        timeout=880 if kind == 'core' else 400)
            new = set(base.glob('*/summary.json')) - before
            if c['exit_code'] != 0 or len(new) != 1:
                raise ValueError('fresh ' + kind + ' process/evidence cardinality failed')
            summary = new.pop()
            if kind == 'protocol':
                check = check_protocol(summary)
            elif kind == 'numeric':
                check = check_numeric(summary)
            elif kind == 'core':
                check = check_suite(summary, 36, 2)
            else:
                report = read_json(summary)
                if report['status'] != 'PASS' or len(report['cases']) != 6:
                    raise ValueError('comparison scope incomplete')
                check = [check_case(ROOT / case['manifest']) for case in report['cases']]
            manifest_paths = [item['manifest'] for item in read_json(summary).get('tests', read_json(summary).get('cases', [])) if 'manifest' in item]
            result['tests'].append({'kind': kind, 'command': c, 'summary': str(summary.relative_to(ROOT)),
                'summary_sha256': sha(summary), 'gate': check,
                'run_manifest_sha256': {name: sha(ROOT / name) for name in manifest_paths}})
            put(out / 'result.json', result)
        result['source_unchanged'] = all(sha(ROOT / name) == digest for name, digest in sources.items())
        result['tool_binary_sha256_after'] = tool_inventory()
        result['tools_unchanged'] = result['tool_binary_sha256_after'] == tools
        if not result['source_unchanged'] or not result['tools_unchanged']:
            raise ValueError('source/tool bytes changed during fresh validation')
        result['status'] = 'PASS'
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
    result['finished_utc'] = utc()
    put(out / 'result.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
