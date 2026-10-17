"""Archive raw fresh-run evidence with source mapping; never rewrite originals."""
from pathlib import Path
import hashlib
import json
import shutil
import sys

ROOT = Path(__file__).resolve().parents[2]
TARGET = ROOT / 'reports/revd_repair_20261017/fresh-package-evidence'

def disk(p):
    s = str(p.resolve())
    return Path('\\\\?\\' + s) if sys.platform == 'win32' and not s.startswith('\\\\?\\') else p

def sha(p):
    return hashlib.sha256(disk(p).read_bytes()).hexdigest()

def read(p):
    return json.loads(disk(p).read_text(encoding='utf-8'))

state = read(ROOT / 'work/revd_repair_20261017/package_state.json')
assert state['status'] == 'ROUNDTRIP_AND_W2_PASS'
proof_path = ROOT / state['roundtrip_report']
proof = read(proof_path)
package = ROOT / proof['extraction']
detail_path = ROOT / proof['portable_result']
detail = read(detail_path)
assert proof['status'] == detail['status'] == 'PASS'
TARGET.mkdir(parents=True, exist_ok=False)
members = {}

def copy(source, relative):
    target = disk(TARGET / relative)
    target.parent.mkdir(parents=True, exist_ok=True)
    original = sha(source)
    shutil.copyfile(disk(source), target)
    assert sha(target) == original
    members[relative] = {'original_repository_path': source.relative_to(ROOT).as_posix(), 'sha256': original}

def tree(source, relative):
    for p in sorted(disk(source).rglob('*')):
        if not p.is_file():
            continue
        parts = p.relative_to(disk(source))
        if 'obj' in parts.parts and p.name not in ('Vsoc_cpu_tb', 'Vsoc_cpu_tb_w2'):
            continue
        if p.suffix in ('.pyc', '.pyo'):
            continue
        copy(source / parts, (Path(relative) / parts).as_posix())

for name in ('result.json', 'portable.log', 'portable.log.command.json'):
    copy(proof_path.parent / name, 'checker/' + name)
copy(detail_path, 'portable/result.json')
copy(package / 'MANIFEST.json', 'verified-package-MANIFEST.json')
for phase in detail['phase_results']:
    if phase['phase'] == 'smoke':
        for run in phase['runs']:
            tree((package / run['manifest']).parent, 'smoke/latency' + str(run['config']['READ_LATENCY']))
    else:
        tree((package / phase['evidence']).parent, phase['phase'])
        log = package / phase['command']['log']
        copy(log, 'portable/' + log.name)
        copy(log.with_suffix(log.suffix + '.command.json'), 'portable/' + log.name + '.command.json')
tree((ROOT / state['w2_report']).parent, 'w2')
copy(ROOT / state['w2_command']['log'], 'w2-actual-command.log')
copy((ROOT / state['w2_command']['log']).with_suffix('.log.command.json'), 'w2-actual-command.log.command.json')
result = {'status': 'PASS', 'scope': 'Byte-identical archival copies of fresh raw evidence, not a rerun from archived paths.',
          'members': members, 'file_count': len(members),
          'excluded': 'Compiler intermediate object trees; actual simulator payloads are retained.',
          'archiver_sha256': sha(Path(__file__))}
(TARGET / 'SOURCE_MAP.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
print('FRESH_EVIDENCE_ARCHIVE_PASS', len(members))
