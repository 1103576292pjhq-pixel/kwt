"""ZIP round trip and independent package-relative fresh build, never overwrite."""
from pathlib import Path
import argparse
import os
import sys
import zipfile
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import put,sha,command,run_id,utc

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--stage',required=True);ap.add_argument('--zip',dest='zip_path');ap.add_argument('--cpu',action='store_true');args=ap.parse_args()
    stage=(ROOT/args.stage).resolve()
    if ROOT not in stage.parents:raise ValueError('source outside workspace')
    out=ROOT/'work/revd_offline_20261017/package_checks'/run_id();out.mkdir(parents=True,exist_ok=False)
    bound=[Path(__file__),ROOT/'scripts/revd_offline_common.py']
    source0={str(p.relative_to(ROOT)):sha(p) for p in bound}
    for p in bound:
        dest=out/'source_snapshot'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(p.read_bytes())
    archive=ROOT/args.zip_path if args.zip_path else out/'roundtrip.zip'
    if not args.zip_path:
        with zipfile.ZipFile(archive,'x',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
            for p in sorted(stage.rglob('*')):
                if p.is_file():z.write(p,Path(stage.name)/p.relative_to(stage))
    extracted=out/'extracted';extracted.mkdir()
    with zipfile.ZipFile(archive) as z:
        for name in z.namelist():
            dest=(extracted/name).resolve()
            if extracted.resolve() not in dest.parents:raise ValueError('unsafe ZIP member')
        z.extractall(extracted)
    package=extracted/stage.name;records=[]
    suites=['manifest','smoke','numeric']+(['cpu-small'] if args.cpu else [])
    c=command([sys.executable,'-I','-B',package/'scripts/revd_offline_reproduce.py','--suite','portable',*(['--with-cpu'] if args.cpu else [])],out/'portable.log',timeout=880,cwd=package,env={'PYTHONPATH':''})
    records.append(c)
    receipts=[p for p in (package/'reports/revd_offline/reproduction').glob('*/result.json') if p.is_file()]
    portable=[p for p in receipts if __import__('json').loads(p.read_text())['suite']=='portable']
    detail=__import__('json').loads(portable[0].read_text()) if len(portable)==1 else {}
    result={'status':'PASS' if c['exit_code']==0 and detail.get('status')=='PASS' and detail.get('completed_phases')==suites else 'FAIL',
      'archive':str(archive.relative_to(ROOT)),'archive_sha256':sha(archive),'extraction':str(package.relative_to(ROOT)),
      'original_root_excluded_from_pythonpath':True,'python_isolated_flag':True,'suites':suites,'commands':records,
      'entry_sha256':sha(package/'scripts/revd_offline_reproduce.py'),'package_manifest_sha256':sha(package/'MANIFEST.json'),
      'portable_result':str(portable[0].relative_to(ROOT)) if len(portable)==1 else None,
      'source_sha256':source0,'source_unchanged':all(sha(ROOT/p)==d for p,d in source0.items()),
      'finished_utc':utc()}
    if not result['source_unchanged']:result['status']='FAIL'
    put(out/'result.json',result);print(out,result['status'],flush=True)
    return 0 if result['status']=='PASS' else 1
if __name__=='__main__':raise SystemExit(main())
