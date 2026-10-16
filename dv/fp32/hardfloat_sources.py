"""Reproducible source selection; upstream remains byte-for-byte untouched.

Release 1 repeats `wire sqrtOpOut` after the ANSI output declaration. Icarus
rejects it. The sole compatibility edit removes this redundant declaration
in a generated build copy, without changing any logic, port or width.
"""
from pathlib import Path
import hashlib
import json

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'vendor/HardFloat-1-upstream/source'
NAMES=['HardFloat_primitives.v','HardFloat_rawFN.v','isSigNaNRecFN.v',
 'fNToRecFN.v','recFNToFN.v','addRecFN.v','mulRecFN.v','mulAddRecFN.v',
 'divSqrtRecFN_small.v','recFNToIN.v','iNToRecFN.v','RISCV/HardFloat_specialize.v']

def prepare(target:Path)->list[Path]:
    target.mkdir(parents=True,exist_ok=True)
    original=SOURCE/'divSqrtRecFN_small.v'
    raw=original.read_bytes()
    needle=b'    wire sqrtOpOut;'
    if raw.count(needle)!=1: raise RuntimeError('Unexpected upstream declaration count')
    modified=raw.replace(needle,b'    // Redundant ANSI output net declaration removed for Icarus compatibility.')
    generated=target/'divSqrtRecFN_small.v'
    generated.write_bytes(modified)
    manifest={'source':str(original.relative_to(ROOT)),
              'source_sha256':hashlib.sha256(raw).hexdigest(),
              'generated_sha256':hashlib.sha256(modified).hexdigest(),
              'transform':'Remove exactly one redundant wire sqrtOpOut; after existing ANSI output declaration.',
              'logic_change':False,'license':'Original BSD notice retained in full.'}
    (target/'compatibility.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
    return [generated if n=='divSqrtRecFN_small.v' else SOURCE/n for n in NAMES]
