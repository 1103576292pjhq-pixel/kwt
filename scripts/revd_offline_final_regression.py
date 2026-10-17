"""Fresh selected-profile regression with before/after tool and source binding."""
from pathlib import Path
import importlib
import shutil
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import numpy as np
from scripts.revd_offline_common import command, put, sha, read_json, run_id, utc
from scripts.revd_offline_gate import check_suite


def tool_inventory():
    tools = [Path(sys.executable).resolve(), Path(np.__file__).resolve()]
    for name in ('iverilog', 'vvp', 'verilator'):
        binary = shutil.which(name)
        if not binary:
            raise ValueError('required actual tool missing ' + name)
        tools.append(Path(binary).resolve())
    extension = importlib.import_module('numpy._core._multiarray_umath')
    tools.append(Path(extension.__file__).resolve())
    # Icarus is a driver; bind its actual parser/preprocessor/backend as well.
    ivl = Path('/usr/lib/x86_64-linux-gnu/ivl')
    for name in ('ivl', 'ivlpp', 'vvp.tgt', 'system.vpi', 'v2005_math.vpi', 'v2009.vpi'):
        p = ivl / name
        if not p.is_file():
            raise ValueError('Icarus backend dependency missing ' + str(p))
        tools.append(p)
    return {str(p): sha(p) for p in tools}


def main():
    rid = run_id()
    out = ROOT / 'reports/revd_offline/final_regression' / rid
    out.mkdir(parents=True, exist_ok=False)
    names = ['rtl/revd_opt/core_stream_frontend_opt.sv', 'rtl/revd/banked_sp16.sv',
        'rtl/revd/quant_epilogue.sv', 'dv/revd_opt/core_tb.sv', 'dv/revd_opt/core_runner.py',
        'scripts/revd_offline_common.py', 'scripts/revd_offline_gate.py',
        'scripts/revd_offline_final_regression.py', 'numeric/fixedpoint.py',
        'config/revd_opt/ctx4_full_pm4.json', 'reports/prototype/vectors/manifest.json']
    sources = {name: sha(ROOT / name) for name in names}
    for name in names:
        p = out / 'source_snapshot' / name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_bytes((ROOT / name).read_bytes())
    tools = tool_inventory()
    child_id = 'ctx4-selected-final36-' + rid
    child = ROOT / 'reports/revd_offline/core' / child_id
    result = {'status': 'RUNNING', 'started_utc': utc(), 'selected_profile': 'D3_CTX4_FULL_PM4_X4_Y1',
        'source_sha256_before': sources, 'tool_binary_sha256_before': tools,
        'tool_binding_scope': 'Captured before this fresh whole regression and refreshed afterwards; each actual child receipt is bound below. No old report is rewritten.',
        'python_version': sys.version, 'numpy_version': np.__version__}
    put(out / 'result.json', result)
    try:
        c = command([sys.executable, '-B', ROOT / 'dv/revd_opt/core_runner.py',
                     '--profile', 'full36', '--pm', '4', '--latency', '1', '--run-id', child_id],
                    out / 'full36.log', timeout=880)
        result['command'] = c
        if c['exit_code'] != 0:
            raise ValueError('fresh full36 subprocess failed')
        result['gate'] = check_suite(child / 'summary.json', 36, 4)
        receipts = read_json(child / 'summary.json')['cases']
        result['run_manifest_sha256'] = {r['manifest']: sha(ROOT / r['manifest']) for r in receipts}
        result['source_unchanged'] = all(sha(ROOT / name) == digest for name, digest in sources.items())
        result['tool_binary_sha256_after'] = tool_inventory()
        result['tools_unchanged'] = result['tool_binary_sha256_after'] == tools
        if not result['source_unchanged'] or not result['tools_unchanged']:
            raise ValueError('source or tool changed during selected final regression')
        result.update(status='PASS', full36=str((child / 'summary.json').relative_to(ROOT)),
                      unique_outputs=result['gate']['outputs'])
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
    result['finished_utc'] = utc()
    put(out / 'result.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())
