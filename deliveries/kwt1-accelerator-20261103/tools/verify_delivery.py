from pathlib import Path
import hashlib
import json

root = Path(__file__).resolve().parents[1]
manifest = json.loads((root/'delivery-manifest.json').read_text(encoding='utf-8'))
for rel, info in manifest['files'].items():
    path = (root/rel).resolve()
    if root not in path.parents or not path.is_file():
        raise SystemExit('FAIL missing/invalid path: '+rel)
    if path.stat().st_size != info['bytes'] or hashlib.sha256(path.read_bytes()).hexdigest() != info['sha256']:
        raise SystemExit('FAIL changed file: '+rel)
production = [v.strip() for v in (root/'rtl/kwt.f').read_text().splitlines() if v.strip() and not v.startswith('+')]
if len(production) != 15 or any(not (root/p).is_file() for p in production):
    raise SystemExit('FAIL production filelist')
if len(list((root/'rtl/include').glob('*.vh'))) != 4:
    raise SystemExit('FAIL headers')
print('PASS DELIVERY_INTEGRITY files=%d modules=15 headers=4; not a new hardware acceptance'%len(manifest['files']))
