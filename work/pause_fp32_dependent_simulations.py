"""Pause only this workspace's encoder simulations before an authorized FPU fix."""
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import signal

root = Path(__file__).resolve().parents[1]
report_root = (root / 'reports/encoder').resolve()
stopped = []
for proc in Path('/proc').iterdir():
    if not proc.name.isdigit():
        continue
    try:
        argv = [part.decode('utf-8') for part in (proc / 'cmdline').read_bytes().rstrip(b'\0').split(b'\0')]
        if not argv or not argv[0]:
            continue
        binary = Path(argv[0])
        if binary.name not in ('Vtb_encoder', 'Vtb_e203_encoder') or not binary.is_absolute():
            continue
        if not binary.resolve().is_relative_to(report_root):
            continue
        ppid = int((proc / 'stat').read_text(encoding='utf-8').split(') ', 1)[1].split()[1])
        parent = Path(f'/proc/{ppid}')
        parent_args = (parent / 'cmdline').read_bytes().decode('utf-8')
        if not any(name in parent_args for name in ('dv/encoder/run_encoder.py', 'dv/e203_encoder/run_system.py')):
            continue
        parent_cwd = (parent / 'cwd').resolve()
        if not parent_cwd.is_relative_to(root.resolve()):
            continue
        pid = int(proc.name)
        note = {'pid': pid, 'parent_pid': ppid, 'command': argv,
                'reason': 'Pausing FP32 dependent execution before cold-start special-value fix; no numerical failure inferred.',
                'utc': datetime.now(timezone.utc).isoformat()}
        evidence = binary.parent.parent / 'root-fp32-pause.json'
        evidence.write_text(json.dumps(note, indent=2) + '\n', encoding='utf-8')
        os.kill(pid, signal.SIGTERM)
        stopped.append(note)
    except (FileNotFoundError, ProcessLookupError):
        continue
record = {'status': 'ENCODER_SIMULATIONS_PAUSED_FOR_FP32_REVALIDATION',
          'stopped': stopped, 'runner_untouched': True, 'files_preserved': True,
          'utc': datetime.now(timezone.utc).isoformat()}
(root / 'work/fp32_pause_confirmation.json').write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
print(json.dumps(record, indent=2))
