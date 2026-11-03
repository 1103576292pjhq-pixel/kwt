"""Remove only explicitly identified VCS outputs; preserve source/data/evidence."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess

RUNS=('soc_compile_01','soc_shared_compile_01','shared_task_compile_01','real_shared_case3_02','real_shared_suite_01')
PROTECTED_SUFFIXES={'.v','.vh','.sv','.svh','.f','.c','.h','.s','.ld','.py','.json','.log','.hex','.f32','.verilog','.lib','.db','.sdc','.bin','.elf','.txt','.csv'}


def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()


def targets(root):
    root=Path(root)
    if root.is_symlink() or root.resolve().name!='kwt-soc':raise ValueError('Expected real kwt-soc directory')
    root=root.resolve();found=[]
    for run in RUNS:
        base=root/'verification'/run
        for name in ('csrc','simv.daidir','simv'):
            p=base/name
            if not p.exists() and not p.is_symlink():continue
            if p.is_symlink() or root not in p.resolve().parents:raise ValueError('Unsafe target '+str(p))
            if any(parent.is_symlink() for parent in p.parents if parent!=root and root in parent.parents):raise ValueError('Symlink ancestor '+str(p))
            if name=='csrc' and (not p.is_dir() or not any(p.rglob('*.a'))):raise ValueError('Unrecognized VCS csrc '+str(p))
            if name=='simv.daidir' and (not p.is_dir() or not any(p.rglob('*.so'))):raise ValueError('Unrecognized VCS daidir '+str(p))
            if name=='simv':
                if not p.is_file():raise ValueError('Unrecognized VCS executable '+str(p))
                with p.open('rb') as stream:magic=stream.read(4)
                if magic!=b'\x7fELF':raise ValueError('Unrecognized VCS executable '+str(p))
            found.append(p)
    return root,found


def protected(root,remove):
    return {p.relative_to(root).as_posix():digest(p) for p in root.rglob('*')
            if p.is_file() and p.suffix.lower() in PROTECTED_SUFFIXES and not any(t==p or t in p.parents for t in remove)}


def busy_processes():
    text=subprocess.check_output(['ps','-u',str(os.getuid()),'-o','pid=,comm=,args='],text=True)
    busy=[]
    for line in text.splitlines():
        fields=line.split(None,2)
        if len(fields)<3 or int(fields[0])==os.getpid():continue
        if fields[1] in {'simv','vcs','vcs1','vlogan','vlogan1','vhdlan','vhdlan1'} or any(Path(arg).name=='run_server.py' for arg in fields[2].split()):busy.append(line)
    return busy


def clean(root,apply=False):
    root,remove=targets(root)
    busy=busy_processes()
    if busy:raise RuntimeError('Simulation still running; no cleanup performed:\n'+'\n'.join(busy))
    receipt=root/'cleanup-vcs-20261103.json'
    if receipt.exists() or receipt.is_symlink():raise ValueError('Existing cleanup receipt preserved; do not repeat')
    before=protected(root,remove)
    entries=[]
    for p in remove:
        size=sum(v.stat().st_size for v in p.rglob('*') if v.is_file() and not v.is_symlink()) if p.is_dir() else p.stat().st_size
        entries.append(dict(path=p.relative_to(root).as_posix(),bytes=size))
    result=dict(status='PREVIEW_ONLY',root=str(root),targets=entries,bytes=sum(v['bytes'] for v in entries),protected_sha256=before)
    print('VCS_OUTPUT_CANDIDATES',flush=True)
    for item in entries:print('%8.2f MiB  %s'%(item['bytes']/1048576,item['path']),flush=True)
    print('TOTAL %.2f MiB; protected_source_data_report_files=%d'%(result['bytes']/1048576,len(before)),flush=True)
    if not apply:return result
    for p in remove:
        if p.is_dir():shutil.rmtree(p)
        else:p.unlink()
    for rel,want in before.items():
        if digest(root/rel)!=want:raise RuntimeError('Protected file changed: '+rel)
    result['status']='CLEANED_VCS_OUTPUTS_PROTECTED_FILES_UNCHANGED'
    with receipt.open('x',encoding='utf-8') as stream:stream.write(json.dumps(result,indent=2)+'\n')
    print('CLEANUP_PASS removed=%d reclaimed_MiB=%.2f protected_files=%d'%(len(remove),result['bytes']/1048576,len(before)),flush=True)
    print('RECEIPT',receipt,flush=True)
    return result


def inventory(root):
    root=Path(root).resolve()
    if root.name!='kwt-soc':raise ValueError('Expected kwt-soc')
    paths=['verification/soc_compile_01/soc.f','verification/shared_sram_wiring_01/shared_sram_additions.f']
    extra={rel:(root/rel).read_text(errors='replace') for rel in paths if (root/rel).is_file()}
    files=[];details={}
    names={'config.v','e203_defines.v','e203_srams.v','sirv_gnrl_ram.v','sirv_sim_ram.v','e203_itcm_ram.v','e203_dtcm_ram.v'}
    for folder in [root/'rtl',root/'accelerator/rtl',root/'shared_sram_bundle_01/kwt-shared-sram-v2/rtl']:
        if not folder.is_dir():continue
        for path in sorted(folder.rglob('*')):
            if path.is_file() and path.suffix.lower() in {'.v','.vh','.sv','.svh','.f','.lib','.db'}:
                rel=path.relative_to(root).as_posix()
                files.append(dict(path=rel,bytes=path.stat().st_size,sha256=digest(path)))
                if path.name in names or path.name=='kwt_shared_soc_top.v':details[rel]=path.read_text(errors='replace')
    packet=dict(root=str(root),filelists=extra,source_and_library_files=files,configuration_and_memory_sources=details,
        note='Read-only source inventory for whole-SoC handoff; no synthesis/ASIC configuration acceptance claimed')
    path=root/'soc-file-inventory-20261103.json'
    text=json.dumps(packet,ensure_ascii=False,indent=2)+'\n'
    if path.is_symlink():raise ValueError('Refusing inventory output symlink')
    if path.exists():
        if not path.is_file() or path.read_text(encoding='utf-8')!=text:raise ValueError('Existing inventory differs; preserved')
    else:
        with path.open('x',encoding='utf-8') as stream:stream.write(text)
    print('SOC_SOURCE_INVENTORY',path,flush=True)


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,required=True);p.add_argument('--apply',action='store_true')
    args=p.parse_args()
    if not args.apply:inventory(args.root)
    clean(args.root,args.apply)


if __name__=='__main__':main()
