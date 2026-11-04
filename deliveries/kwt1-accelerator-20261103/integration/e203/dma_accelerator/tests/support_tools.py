from pathlib import Path
import hashlib
import json
import math
import shutil
import struct

def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def save(path, value):
    Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False)+'\n', encoding='utf-8')

def prepare_fixture(out):
    source=Path(__file__).resolve().parent/'fixtures'
    identity=json.loads((source/'identity.json').read_text(encoding='utf-8'))
    for name,want in identity['files'].items():
        if sha(source/name)!=want:
            raise ValueError('Fixture identity mismatch '+name)
    out=Path(out)
    out.mkdir(parents=True,exist_ok=False)
    for name in identity['files']:
        shutil.copyfile(source/name,out/name)
    gold=[int(line,16) for line in (out/'gold.hex').read_text().splitlines()]
    return dict(sample=identity['sample'],gold=gold,files_sha256=identity['files'])

def audit_trace(path, gold, reference):
    seen = {}
    for line in Path(path).read_text(encoding='ascii').splitlines():
        match = re.fullmatch(r'Y (\d+) ([0-9a-fA-F]{8})', line)
        if not match: raise ValueError('Malformed actual shared readback')
        index, word = int(match[1]), int(match[2], 16)
        if index in seen or not 0 <= index < 25344: raise ValueError('Duplicate/out-of-range shared result')
        if word != gold[index]: raise ValueError('Actual shared result differs at %d'%index)
        seen[index] = word
    if len(seen) != 25344: raise ValueError('Incomplete actual shared result readback')
    raw = Path(reference).read_bytes()
    if len(raw) != 25344*4: raise ValueError('Bad reference length')
    ref = struct.unpack('<25344f', raw)
    if not all(math.isfinite(v) for v in ref): raise ValueError('Non-finite reference')
    values = [(seen[i]&65535)-(65536 if seen[i]&32768 else 0) for i in range(25344)]
    sse = math.fsum((v/4096-r)**2 for v,r in zip(values, ref))
    energy = math.fsum(r*r for r in ref)
    ratio = math.sqrt(sse/25344)/max(math.sqrt(energy/25344), 1e-8)
    if ratio > .03: raise ValueError('Actual shared output exceeds 3 percent NRMSE')
    return dict(outputs=25344, bit_mismatches=0, nrmse_percent=ratio*100)
