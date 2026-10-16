"""Stop only the positively identified obsolete encoder simulation, never a lane."""
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import signal

root = Path(__file__).resolve().parents[1]
out = root / 'reports/encoder/system/pingpong'
progress = json.loads((out / 'progress.json').read_text(encoding='utf-8'))
build = json.loads((out / 'build.json').read_text(encoding='utf-8'))
pid = int(progress['pid'])
if pid != 1161:
    raise SystemExit('Refusing: current simulation PID differs from independently reviewed PID1161')
proc = Path(f'/proc/{pid}')
if not proc.exists():
    print('Reviewed obsolete simulation already exited; no signal sent')
    raise SystemExit(0)
argv = (proc / 'cmdline').read_bytes().rstrip(b'\0').split(b'\0')
argv = [item.decode('utf-8') for item in argv]
expected = [str(out / 'obj/Vtb_e203_encoder'), '+BYTES=1488', '+POLICY=1']
if argv != expected or argv != progress['command']:
    raise SystemExit('Refusing: exact live simulation command differs')
ppid = int((proc / 'stat').read_text(encoding='utf-8').split(') ', 1)[1].split()[1])
if ppid != 834:
    raise SystemExit('Refusing: simulation parent differs from reviewed PID834')
parent_args = (Path(f'/proc/{ppid}') / 'cmdline').read_bytes()
if b'dv/e203_encoder/run_system.py' not in parent_args or b'reports/encoder/system/pingpong' not in parent_args:
    raise SystemExit('Refusing: parent is not this workspace encoder run')
changes = {}
for name, old in build['sources'].items():
    path = root / name
    current = hashlib.sha256(path.read_bytes()).hexdigest()
    if old != current:
        changes[name] = {'compiled': old, 'current': current}
if 'rtl/encoder_core.sv' not in changes or 'soc/e203_encoder/e203_encoder_soc.sv' not in changes:
    raise SystemExit('Refusing: reviewed stale source condition is no longer present')
record = {'status': 'ABORTING_STALE_EXECUTION', 'pid': pid, 'parent_pid': ppid,
          'command': argv, 'changed_sources': changes,
          'reason': 'Compiled/live sources differ; this process cannot pass current-source acceptance. Preserve all files and rerun after final freeze.',
          'utc': datetime.now(timezone.utc).isoformat()}
record_path = out / 'root-abort.json'
record_path.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
os.kill(pid, signal.SIGTERM)
record['status'] = 'SIGTERM_SENT_TO_OBSOLETE_SIMULATION_ONLY'
record_path.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
print(f'SIGTERM sent only to obsolete encoder simulation PID{pid}; runner and files preserved')
