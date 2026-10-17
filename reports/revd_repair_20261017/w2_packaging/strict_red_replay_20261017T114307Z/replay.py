"""Replay the unchanged final checker against the exact HEAD packager bytes."""
from __future__ import annotations
import contextlib
import datetime as dt
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys

sys.dont_write_bytecode = True
OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[3]
CHECKER = ROOT / 'dv/revd_opt/package_readme_command_checks.py'
PACKAGER = ROOT / 'scripts/package_revd_candidate.py'
W2 = ROOT / 'scripts/revd_offline_soc_w2_run.py'
GREEN = ROOT / 'reports/revd_repair_20261017/w2_packaging/20261017T112913Z_8fe18c78/result.json'

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def git(*args):
    process = subprocess.run(['git', *args], cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
    return process.stdout

before = {path.relative_to(ROOT).as_posix(): sha(path) for path in (CHECKER, PACKAGER, W2)}
head_commit = git('rev-parse', 'HEAD').decode('ascii').strip()
head_bytes = git('show', 'HEAD:scripts/package_revd_candidate.py')
head_sha256 = hashlib.sha256(head_bytes).hexdigest()
old_packager = OUT / 'HEAD_package_revd_candidate.py'
old_packager.write_bytes(head_bytes)
checker_bytes = CHECKER.read_bytes()
(OUT / 'final_checker_source.py.txt').write_bytes(checker_bytes)
assert b'--stage small --sim verilator --tasks 2' in head_bytes
assert sha(old_packager) == head_sha256
namespace = {'__file__': str(CHECKER), '__name__': 'strict_red_replay_checker'}
exec(compile(checker_bytes, str(CHECKER), 'exec'), namespace)
namespace['PACKAGER'] = old_packager
captured = io.StringIO()
with contextlib.redirect_stdout(captured):
    checker_exit = namespace['main']()
text = captured.getvalue()
(OUT / 'checker_stdout.log').write_text(text, encoding='utf-8')
assert checker_exit == 1, text
red_out = Path(text.strip().rsplit(' FAIL ', 1)[0])
red_path = red_out / 'result.json'
red = json.loads(red_path.read_text(encoding='utf-8'))
green = json.loads(GREEN.read_text(encoding='utf-8'))
checker_key = CHECKER.relative_to(ROOT).as_posix()
old_packager_key = old_packager.relative_to(ROOT).as_posix()
assert red['source_sha256'][checker_key] == before[checker_key] == green['source_sha256'][checker_key]
assert red['source_sha256'][old_packager_key] == head_sha256
assert red['status'] == 'FAIL'
for test in red['tests'][:2]:
    assert test['name'] in ('generated_w2_small', 'generated_w2_full')
    assert test['status'] == 'FAIL' and test['exit_code'] == 2 and test['expected_exit_code'] == 0
    assert '--sim' in test['documented_argv'] and '--tasks' in test['documented_argv']
    assert 'unrecognized arguments: --sim verilator --tasks 2' in (ROOT / test['log']).read_text(encoding='utf-8')
assert all(test['status'] == 'PASS' for test in red['tests'][2:])
after = {path.relative_to(ROOT).as_posix(): sha(path) for path in (CHECKER, PACKAGER, W2)}
assert before == after
proof = {
    'status': 'PASS',
    'scope': 'Strict red replay only; unchanged final checker, exact HEAD packager bytes, parser only; no source mutation, package build or simulation.',
    'created_utc': dt.datetime.now(dt.timezone.utc).isoformat(),
    'replay_command': [sys.executable, '-I', '-B', str(Path(__file__).resolve())],
    'replay_exit_code': 0,
    'head_commit': head_commit,
    'head_packager_command': ['git', 'show', 'HEAD:scripts/package_revd_candidate.py'],
    'head_packager_stdout_sha256': head_sha256,
    'old_packager_path': old_packager.relative_to(ROOT).as_posix(),
    'old_packager_sha256': sha(old_packager),
    'checker_sha256': before[checker_key],
    'green_checker_sha256': green['source_sha256'][checker_key],
    'red_checker_sha256': red['source_sha256'][checker_key],
    'checker_sha256_equal': True,
    'red_checker_exit_code': checker_exit,
    'red_result': red_path.relative_to(ROOT).as_posix(),
    'green_result': GREEN.relative_to(ROOT).as_posix(),
    'red_tests': red['tests'],
    'production_sha256_before': before,
    'production_sha256_after': after,
    'production_sources_unchanged': True,
    'replay_driver_sha256': sha(Path(__file__))
}
(OUT / 'proof.json').write_text(json.dumps(proof, indent=2) + '\n', encoding='utf-8')
print(OUT / 'proof.json', 'PASS', 'checker=' + before[checker_key], 'red_exit=' + str(checker_exit), flush=True)
