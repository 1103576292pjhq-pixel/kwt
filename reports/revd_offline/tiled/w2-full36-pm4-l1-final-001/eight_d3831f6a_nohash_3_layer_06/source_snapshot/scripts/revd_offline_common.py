"""Bounded subprocesses and immutable evidence for the authorized offline batch."""
from __future__ import annotations
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import signal
import subprocess
import time
import uuid

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / 'work/revd_offline_20261017'

def utc():
    return dt.datetime.now(dt.timezone.utc).isoformat()

def sha(path):
    h = hashlib.sha256()
    with Path(path).open('rb') as f:
        for b in iter(lambda: f.read(1024 * 1024), b''): h.update(b)
    return h.hexdigest()

def read_json(path):
    return json.loads(Path(path).read_text(encoding='utf-8-sig'))

def put(path, value):
    p = Path(path)
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps(value, indent=2, allow_nan=False) + '\n', encoding='utf-8')

def run_id():
    return time.strftime('%Y%m%dT%H%M%SZ', time.gmtime()) + '_' + uuid.uuid4().hex[:8]

def remaining():
    budget = WORK / 'budget.json'
    if not budget.exists(): return 900.0  # portable reproduction, no active lane
    stop = dt.datetime.fromisoformat(read_json(budget)['hard_stop_utc'].replace('Z', '+00:00'))
    return (stop - dt.datetime.now(dt.timezone.utc)).total_seconds()

def command(argv, out, timeout=240, cwd=ROOT, env=None):
    """Record live PID before waiting; kill the entire child group on timeout."""
    out = Path(out)
    limit = min(float(timeout), 899.0, remaining() - 15)
    if limit < 1: raise RuntimeError('insufficient deadline budget to launch subprocess')
    argv = list(map(str, argv))
    record = {'argv': argv, 'cwd': str(cwd), 'started_utc': utc(),
              'timeout_seconds': limit, 'run_identity': os.environ.get('KWT_OFFLINE_RUN_ID'),
              'parent_pid': os.getpid(), 'exit_code': None}
    record_path = out.with_suffix(out.suffix + '.command.json')
    child_env = os.environ.copy()
    child_env['PYTHONDONTWRITEBYTECODE'] = '1'
    if env: child_env.update(env)
    with out.open('w', encoding='utf-8') as stream:
        p = subprocess.Popen(argv, cwd=cwd, stdout=stream, stderr=subprocess.STDOUT,
                             env=child_env, start_new_session=(os.name != 'nt'))
        record['pid'] = p.pid
        put(record_path, record)
        start = time.monotonic()
        try:
            code = p.wait(timeout=limit)
        except subprocess.TimeoutExpired:
            if os.name == 'nt':
                subprocess.run(['taskkill', '/PID', str(p.pid), '/T', '/F'], timeout=10,
                               stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            else:
                os.killpg(p.pid, signal.SIGKILL)
            p.wait(timeout=10)
            code = 124
            stream.write('\nTIMEOUT_PROCESS_GROUP_KILLED\n')
    record.update(exit_code=code, finished_utc=utc(), seconds=time.monotonic()-start,
                  log=str(out.relative_to(ROOT)), log_sha256=sha(out))
    put(record_path, record)
    return record

def check_baseline(destination):
    guard = read_json(WORK / 'baseline_guard.json')
    old = read_json(ROOT / guard['old_tracked_manifest'])
    files = {**old['tracked_file_sha256'], **guard['protected_additional_files']}
    failures = []
    for path, digest in files.items():
        p = ROOT / path
        if not p.is_file() or sha(p) != digest: failures.append(path)
    for key in ('old_tracked_manifest', 'accepted_d2_receipt'):
        if sha(ROOT / guard[key]) != guard[key + '_sha256']: failures.append(key)
    head = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, timeout=15, text=True).strip()
    branch = subprocess.check_output(['git', 'branch', '--show-current'], cwd=ROOT, timeout=15, text=True).strip()
    if head != guard['head'] or branch != guard['branch']: failures.append('HEAD/branch')
    result = {'status': 'PASS' if not failures else 'FAIL', 'checked_utc': utc(),
              'file_count': len(files), 'failures': failures, 'head': head, 'branch': branch,
              'guard_sha256': sha(WORK / 'baseline_guard.json')}
    put(destination, result)
    if failures: raise ValueError('baseline integrity failure: ' + str(failures[:10]))
    return result

def status(stage, **values):
    p = WORK / 'STATUS.json'
    state = read_json(p) if p.exists() else {}
    state.update(status='RUNNING', stage=stage, updated_utc=utc(), real_pid=os.getpid(),
                 run_identity=os.environ.get('KWT_OFFLINE_RUN_ID'), remaining_seconds=remaining(), **values)
    put(p, state)
    with (WORK / 'execution.jsonl').open('a', encoding='utf-8') as f:
        f.write(json.dumps({'utc': utc(), 'stage': stage, 'pid': os.getpid(), **values}) + '\n')
    print(utc(), stage, json.dumps(values), flush=True)
