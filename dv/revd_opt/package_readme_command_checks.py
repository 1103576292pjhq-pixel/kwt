"""Check generated W2 README commands against its real parser, without simulation."""
from __future__ import annotations
import argparse
import ast
import datetime as dt
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess
import sys
import tempfile
import uuid

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
PACKAGER = ROOT / 'scripts/package_revd_candidate.py'
W2 = ROOT / 'scripts/revd_offline_soc_w2_run.py'


def generated_readme(stage):
    """Execute the packager's README writes only; do not build a package."""
    tree = ast.parse(PACKAGER.read_text(encoding='utf-8'), filename=str(PACKAGER))
    build = next(node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name == 'build')
    writes = [node for node in build.body
              if isinstance(node, (ast.Expr, ast.With))
              and "stage / 'README.md'" in ast.unparse(node)]
    if len(writes) != 2:
        raise AssertionError('expected the two production README write statements')
    module = ast.fix_missing_locations(ast.Module(body=writes, type_ignores=[]))
    exec(compile(module, str(PACKAGER), 'exec'), {'stage': stage})
    return (stage / 'README.md').read_text(encoding='utf-8')


def parse_real_w2(argv):
    """Execute main's actual parser prefix, stopping before any runtime action."""
    tree = ast.parse(W2.read_text(encoding='utf-8'), filename=str(W2))
    main = next(node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name == 'main')
    prefix = []
    for node in main.body:
        prefix.append(node)
        if (isinstance(node, ast.Assign) and isinstance(node.value, ast.Call)
                and isinstance(node.value.func, ast.Attribute)
                and node.value.func.attr == 'parse_args'):
            break
    else:
        raise AssertionError('W2 main parse_args statement not found')
    module = ast.fix_missing_locations(ast.Module(body=prefix, type_ignores=[]))
    namespace = {'argparse': argparse}
    sys.argv = [str(W2), *argv]
    exec(compile(module, str(W2), 'exec'), namespace)
    print(json.dumps(vars(namespace['args']), sort_keys=True))


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    out = ROOT / 'reports/revd_repair_20261017/w2_packaging' / (
        dt.datetime.now(dt.timezone.utc).strftime('%Y%m%dT%H%M%SZ') + '_' + uuid.uuid4().hex[:8])
    out.mkdir(parents=True, exist_ok=False)
    with tempfile.TemporaryDirectory(dir=out) as folder:
        readme = generated_readme(Path(folder))
    (out / 'generated_README.md').write_text(readme, encoding='utf-8')
    commands = re.findall(r'`(python3 -B scripts/revd_offline_soc_w2_run\.py [^`]+)`', readme)
    if len(commands) != 1:
        raise AssertionError('expected exactly one generated W2 entry command')
    documented = shlex.split(commands[0])
    documented_args = documented[3:]
    if documented_args[:2] != ['--stage', 'small']:
        raise AssertionError('W2 README entry must select the bounded small stage')
    cases = [
        ('generated_w2_small', documented_args, 0, 'small'),
        ('generated_w2_full', ['--stage', 'full', *documented_args[2:]], 0, 'full'),
        ('unsupported_sim_rejected', ['--stage', 'small', '--sim', 'verilator'], 2, None),
        ('unsupported_tasks_rejected', ['--stage', 'small', '--tasks', '2'], 2, None),
        ('invalid_stage_rejected', ['--stage', 'invalid'], 2, None),
    ]
    tests = []
    for name, args, expected_exit, expected_stage in cases:
        argv = [sys.executable, '-I', '-B', str(Path(__file__).resolve()), '--parse-w2', *args]
        process = subprocess.run(argv, cwd=ROOT, text=True, encoding='utf-8',
                                 stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=30)
        log = out / (name + '.log')
        log.write_text(process.stdout, encoding='utf-8')
        passed = process.returncode == expected_exit
        if expected_stage and process.returncode == 0:
            passed = passed and json.loads(process.stdout)['stage'] == expected_stage
        if expected_exit == 2:
            passed = passed and ('unrecognized arguments:' in process.stdout
                                 or 'invalid choice:' in process.stdout)
        tests.append({'name': name, 'status': 'PASS' if passed else 'FAIL',
                      'documented_argv': [*documented[:3], *args], 'parser_argv': argv,
                      'exit_code': process.returncode, 'expected_exit_code': expected_exit,
                      'log': log.relative_to(ROOT).as_posix(), 'log_sha256': sha(log)})
    status = 'PASS' if all(test['status'] == 'PASS' for test in tests) else 'FAIL'
    report = {'status': status, 'scope': 'README generation and actual W2 CLI parser only; no package build or simulation.',
              'tests': tests, 'source_sha256': {path.relative_to(ROOT).as_posix(): sha(path)
                                              for path in (PACKAGER, W2, Path(__file__).resolve())}}
    (out / 'result.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(out, status, len(tests), flush=True)
    return 0 if status == 'PASS' else 1


if __name__ == '__main__':
    if sys.argv[1:2] == ['--parse-w2']:
        parse_real_w2(sys.argv[2:])
    else:
        raise SystemExit(main())
