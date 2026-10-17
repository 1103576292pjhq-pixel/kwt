#!/usr/bin/env python3
"""Emit a verified minimal public-E203 packaging recipe; no old file writes."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,WORK,put,read_json,sha

def dependency_recipe():
    original_path=ROOT/'config/e203-source-manifest.json'
    original=read_json(original_path)
    repo=next(r for r in original['repositories'] if r['root']=='vendor/e203_hbirdv2-upstream')
    entries={entry['path']:entry for entry in repo['files']}
    cpu_root=ROOT/repo['root'];rtl=cpu_root/'rtl/e203'
    wanted=sorted({str(p.relative_to(cpu_root)) for p in rtl.rglob('*') if p.is_file()}|{'LICENSE'})
    selected=[];hashes={}
    for name in wanted:
        entry=entries.get(name)
        if entry is None:raise RuntimeError('dependency absent from frozen upstream manifest '+name)
        path=cpu_root/name
        if entry['type']=='symlink':
            if not path.is_symlink() or str(path.readlink())!=entry['target']:raise RuntimeError('upstream link mismatch')
        elif sha(path)!=entry['sha256']:raise RuntimeError('upstream dependency hash mismatch '+name)
        selected.append(entry);hashes[str(path.relative_to(ROOT))]=sha(path)
    subset={**original,'purpose':'Derived minimum public E203 RTL/include/license closure for the new CPU reproduction entry.',
      'derivation':{'original_manifest':'config/e203-source-manifest.json','original_manifest_sha256':sha(original_path),
                    'selection':'All actual rtl/e203 files compiled/included by the new entry plus root LICENSE; no SDK dependency.',
                    'omitted_repositories':['vendor/hbird-sdk-upstream']},
      'repositories':[{**repo,'files':selected}]}
    return {'status':'VERIFIED_RECIPE','source_manifest_sha256':sha(original_path),'file_count':len(wanted),
      'total_vendor_bytes':sum((ROOT/p).stat().st_size for p in hashes),'vendor_file_sha256':hashes,
      'package_manifest_destination':'config/e203-source-manifest.json','derived_package_manifest':subset,
      'retain_original_manifest_as':'evidence/original-e203-source-manifest.json',
      'instructions':'Write this derived manifest inside the new package only. Never replace the frozen workspace manifest. Keep compiled shell/RAM/start/link/timescale plus new driver/TBs/scripts and selected vectors alongside it.'}

if __name__=='__main__':
    out=WORK/'soc/e203-minimal-package-recipe.json'
    if out.exists():raise RuntimeError('refuse to overwrite existing recipe')
    recipe=dependency_recipe();put(out,recipe)
    print('SOC_MINIMAL_DEPENDENCIES',out.relative_to(ROOT),'files',recipe['file_count'],'bytes',recipe['total_vendor_bytes'])
