#!/usr/bin/env python3
"""Read-only SHA256 comparison of this delivery's own RTL and server copies."""
import argparse
import hashlib
import json
from pathlib import Path


def contained(root,relative):
    root=Path(root).resolve();path=(root/relative).resolve()
    if Path(relative).is_absolute() or root not in path.parents:raise ValueError('Path escapes declared root: '+relative)
    return path


def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()


def verify(repo_root,soc_root,mapping,standalone_root=None):
    errors=[];soc_count=0;standalone_count=0
    for entry in mapping['files']:
        source=contained(repo_root,entry['repository_path'])
        if not source.is_file():errors.append('repository missing: '+entry['repository_path']);continue
        if digest(source)!=entry['sha256']:errors.append('repository hash mismatch: '+entry['repository_path']);continue
        target=contained(soc_root,entry['server_soc_path'])
        if not target.is_file():errors.append('server missing: '+entry['server_soc_path'])
        elif digest(target)!=entry['sha256']:errors.append('server hash mismatch: '+entry['server_soc_path'])
        else:soc_count+=1
        if standalone_root is not None and entry['kind']=='accelerator':
            target=contained(standalone_root,entry['repository_path'])
            if not target.is_file():errors.append('standalone missing: '+entry['repository_path'])
            elif digest(target)!=entry['sha256']:errors.append('standalone hash mismatch: '+entry['repository_path'])
            else:standalone_count+=1
    platform=[]
    for relative in mapping.get('platform_files',[]):
        p=contained(soc_root,relative)
        if not p.is_file():errors.append('platform file missing: '+relative)
        else:platform.append(relative)
    if errors:raise ValueError('\n'.join(errors))
    return dict(matched_soc_files=soc_count,matched_standalone_files=standalone_count,
                platform_paths_present=platform,platform_content_hash_verified=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--soc-root',type=Path,required=True)
    parser.add_argument('--standalone-root',type=Path)
    args=parser.parse_args();root=Path(__file__).resolve().parents[1]
    try:
        mapping=json.loads((root/'server-source-map.json').read_text(encoding='utf-8'))
        result=verify(root,args.soc_root,mapping,args.standalone_root)
    except (OSError,ValueError,KeyError) as error:
        print('FAIL SERVER_OWN_RTL_IDENTITY\n'+str(error));return 1
    print('PASS SERVER_OWN_RTL_IDENTITY soc_files=%d standalone_files=%d'%(result['matched_soc_files'],result['matched_standalone_files']))
    print('PLATFORM_PATHS_PRESENT count=%d; platform content/library/SDC not certified by this tool'%len(result['platform_paths_present']))
    print('READ_ONLY; no server source copied, moved or overwritten')
    return 0


if __name__=='__main__':raise SystemExit(main())
