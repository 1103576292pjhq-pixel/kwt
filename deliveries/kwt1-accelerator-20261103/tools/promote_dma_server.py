"""Promote the verified DMA12 bundle; archive replaced inputs outside kwt-soc.

Default is read-only preview. --apply stages, validates, moves and records rollback.
No source, report, waveform or library is permanently deleted.
"""
from pathlib import Path
import argparse,hashlib,importlib.util,json,os,re,shutil,sys,time

def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,v):Path(p).write_text(json.dumps(v,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def need(ok,message):
    if not ok:raise RuntimeError(message)
def inventory(p):
    need(not p.is_symlink(),'Symlink target refused: '+str(p))
    items=[p] if p.is_file() else list(p.rglob('*'))
    need(not any(x.is_symlink() for x in items),'Symlink in replacement target: '+str(p))
    return {str(x):sha(x) for x in items if x.is_file()}

OVERLAY='''from pathlib import Path
import hashlib,json
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def prepare_overlay(root,bundle,base,extra,out):
    root,bundle,out=Path(root).resolve(),Path(bundle).resolve(),Path(out).resolve()
    result=[]
    for f in [base,extra]:
        lines=[]
        for line in Path(f).read_text().splitlines():
            if line==str(root/'tb/tb_top.v'):line=str(out/'tb_real.v')
            if line and not line.startswith('+') and line!=str(out/'tb_real.v'):
                if not Path(line).is_file():raise ValueError('Missing source: '+line)
            lines.append(line)
        result.append(lines)
    return dict(base_lines=result[0],extra_lines=result[1],original_filelist_sha256={str(p):sha(p) for p in [base,extra]},
                candidate_rtl_sha256={str(p.relative_to(bundle)):sha(p) for p in (bundle/'rtl').rglob('*') if p.is_file()},mapping={},changed_files=[])
'''

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root',type=Path,required=True);p.add_argument('--apply',action='store_true')
    a=p.parse_args();root=a.root.resolve()
    need(root.name=='kwt-soc' and root.is_dir(),'Expected existing kwt-soc')
    need(not (root/'DMA_CURRENT.json').exists(),'Already promoted; do not repeat')
    bundle=root/'dma_suite_test_01/kwt-dma-suite';passed=root/'verification/dma_suite12_01'
    report=json.loads((passed/'report.json').read_text())
    need(report['status']=='PASS_E203_DMA_SUITE_12' and len(report['tasks'])==12,'Need full DMA12 PASS')
    need(report['total_cycles']==sum(t['timing']['cycles'] for t in report['tasks']),'Cycle sum mismatch')
    need(all(t['correctness']['bit_mismatches']==0 and t['correctness']['nrmse_percent']<=3 for t in report['tasks']),'Correctness failed')
    manifest=json.loads((bundle/'package-sha256.json').read_text())
    for rel,want in manifest.items():
        target=(bundle/rel).resolve();need(bundle.resolve() in target.parents,'Manifest escapes bundle')
        need(target.is_file() and sha(target)==want,'Bundle hash mismatch: '+rel)
    need(sha(bundle/'build-01/real_shared_task.verilog')==report['firmware_sha256'],'Firmware differs from PASS')
    for rel,want in report['rtl_overlay']['candidate_rtl_sha256'].items():need(sha(bundle/rel)==want,'RTL differs from PASS: '+rel)
    for path,want in report['source_input_sha256'].items():need(Path(path).is_file() and sha(path)==want,'Input changed since PASS: '+path)
    for path,want in report['rtl_overlay']['original_filelist_sha256'].items():need(sha(path)==want,'Original filelist changed: '+path)
    # The production top must equal generation from the verified platform source.
    sys.path.insert(0,str(bundle));from prepare_soc import convert
    original=root/'rtl/e203/soc/kwt_shared_soc_top.v'
    need(convert(original.read_text())==(passed/'kwt_dma_soc_top.v').read_text(),'Production top differs from verified generator')
    need('module kwt_dma_soc_top(' in (passed/'kwt_dma_soc_top.v').read_text(),'Wrong production module')
    archive_names=['accelerator','tb/tb_top.v','rtl/e203/soc/kwt_shared_soc_top.v','rtl/e203/soc/kwt_soc_top.v',
        'dma_server_test_01','dma_suite_test_01','throughput_driver_test_01','throughput_icb_test_01','throughput_icb_test_02',
        'real_shared_timing_test_01','real_shared_case3_test_01','real_shared_suite_test_01','shared_task_test_01',
        'kwt-dma-server.tar.gz','kwt-dma-suite12.tar.gz','kwt-throughput-driver.tar.gz','kwt-throughput-icb.tar.gz',
        'kwt-real-shared-timing.tar.gz','build-01','task_smoke.verilog','prepare_kwt_soc.py','wiring_01']
    targets=[root/n for n in archive_names if (root/n).exists()]
    old={}
    for target in targets:old.update(inventory(target))
    # Do not modify or silently invalidate a teammate's synthesis scripts.
    risks=[]
    for script in root.rglob('*'):
        if not script.is_file() or script.suffix not in {'.tcl','.sdc','.f'}:continue
        rel=script.relative_to(root)
        if rel.parts[0] in {'verification','rtl','real12_verify_01','shared_sram_bundle_01'}:continue
        if any(script==t or t in script.parents for t in targets):continue
        if re.search(r'kwt_accelerator|kwt_shared_soc_top|kwt_soc_top|accelerator/rtl|dma_suite_test',script.read_text(errors='replace')):risks.append(str(rel))
    need(not risks,'Teammate script needs migration first: '+', '.join(risks))
    print('PREFLIGHT_PASS tasks=12 targets=%d old_files=%d'%(len(targets),len(old)))
    print('KEEP verification reports/waves, platform rtl, shared_sram_bundle_01 and real12_verify_01')
    if not a.apply:
        print('PREVIEW_ONLY; use --apply after reviewing scope');return
    stamp=time.strftime('%Y%m%d-%H%M%S')
    backup=root.parent/('kwt-soc-before-dma-'+stamp);backup.mkdir(exist_ok=False)
    stage=backup/'staged-new';stage.mkdir()
    acc=stage/'accelerator';shutil.copytree(bundle,acc)
    platform=acc/'platform';platform.mkdir()
    shutil.copyfile(passed/'kwt_real_soc_top.v',platform/'kwt_real_soc_top.v')
    # Keep shared RAM source in its already-active external directory; avoid duplicate definitions.
    shared_copy=acc/'rtl/shared'
    if shared_copy.exists():
        for x in shared_copy.glob('*.v'):
            counterpart=root/'shared_sram_bundle_01/kwt-shared-sram-v2/rtl'/x.name
            need(counterpart.is_file() and sha(x)==sha(counterpart),'Shared SRAM duplicate differs: '+x.name)
        shutil.move(str(shared_copy),str(backup/'packaged-shared-source-copy'))
    new_sources=[]
    for name in ['soc.f','shared.f']:
        lines=(passed/name).read_text().splitlines();mapped=[]
        for line in lines:
            line=line.replace(str(bundle),str(root/'accelerator')).replace(str(passed/'tb_real.v'),str(root/'tb/tb_top.v'))
            mapped.append(line)
        (platform/('base-'+name)).write_text('\n'.join(mapped)+'\n')
        new_sources.extend(mapped)
    (acc/'rtl_overlay.py').write_text(OVERLAY)
    runner=acc/'run_suite.py';text=runner.read_text()
    start=text.index('def wire(source,tb):');end=text.index('\ndef audit(',start)
    text=text[:start]+"def wire(source,tb):\n    return (HERE/'platform/kwt_real_soc_top.v').read_text(),tb\n\n"+text[end:]
    replacements={"top=root/'rtl/e203/soc/kwt_shared_soc_top.v'":"top=root/'rtl/e203/soc/kwt_dma_soc_top.v'",
      "base=root/'verification/soc_compile_01/soc.f';extra=root/'verification/shared_sram_wiring_01/shared_sram_additions.f'":"base=HERE/'platform/base-soc.f';extra=HERE/'platform/base-shared.f'",
      "(out/'kwt_dma_soc_top.v').write_text(convert(top.read_text()))":"(out/'kwt_dma_soc_top.v').write_text(top.read_text())"}
    for old_text,new_text in replacements.items():
        need(text.count(old_text)==1,'Runner anchor differs: '+old_text);text=text.replace(old_text,new_text)
    runner.write_text(text);compile(text,str(runner),'exec');compile(OVERLAY,'rtl_overlay.py','exec')
    # One accelerator list, root-relative. No obsolete kwt.f or duplicate shared copies.
    fl=acc/'rtl/dma.f'
    fl.write_text('+incdir+accelerator/rtl/include\n'+'\n'.join('accelerator/'+p.relative_to(acc).as_posix() for p in sorted((acc/'rtl').rglob('*.v')))+'\n'+
       '\n'.join(str(p.relative_to(root)) for p in sorted((root/'shared_sram_bundle_01/kwt-shared-sram-v2/rtl').glob('*.v')))+'\n')
    (acc/'README.md').write_text('''# 当前正式DMA加速器
RTL: rtl/；CPU驱动: task_test.c、shared_task.c、real_io.c；镜像: build-01/real_shared_task.verilog。
从kwt-soc运行 python3 accelerator/run_suite.py --root "$PWD" --output verification/dma_current_check_01 --tasks 3 --activity none
12任务评测省略--tasks 3；功耗活动导出省略--activity none。
此目录由已经通过12任务的封存包提升；仅更新路径/接线复用，不改变RTL数值或固件。
平台依赖在platform/，仿真顶层不能代替生产顶层。完整指南口径见kwt-soc/README_CURRENT.md。
''')
    # Template paths are absolute by design, matching the actual platform.
    for line in new_sources:
        if not line or line.startswith('+'):continue
        pth=Path(line);planned=acc/pth.relative_to(root/'accelerator') if root/'accelerator' in pth.parents else pth
        need(planned.exists(),'Relocated source absent: '+line)
    # Check functional sources and image byte-identical before any replacement.
    for rel,want in manifest.items():
        if rel.startswith('rtl/') and rel.endswith(('.v','.vh')) and not rel.startswith('rtl/shared/'):
            need(sha(acc/rel)==want,'RTL changed during promotion: '+rel)
    need(sha(acc/'build-01/real_shared_task.verilog')==report['firmware_sha256'],'Staged firmware changed')
    files={p.relative_to(acc).as_posix():sha(p) for p in acc.rglob('*') if p.is_file() and p.name!='package-sha256.json' and '__pycache__' not in p.parts}
    save(acc/'package-sha256.json',files)
    new_top=stage/'kwt_dma_soc_top.v';shutil.copyfile(passed/'kwt_dma_soc_top.v',new_top)
    new_tb=stage/'tb_top.v';shutil.copyfile(passed/'tb_real.v',new_tb)
    readme=stage/'README_CURRENT.md'
    readme.write_text('''# 唯一正式入口：DMA版

生产SoC顶层：rtl/e203/soc/kwt_dma_soc_top.v，模块kwt_dma_soc_top。
加速器：accelerator/rtl，模块kwt_dma_accelerator；配套CPU驱动/镜像在accelerator/。
共享SRAM：shared_sram_bundle_01/kwt-shared-sram-v2/rtl（当前有效，不是旧加速器）。
测试数据：real12_verify_01/kwt-real12-validation/fixtures（数据依赖，非当前综合入口）。
测试入口：accelerator/run_suite.py。旧源码与旧测试包已移出工程，位置见DMA_CURRENT.json。
已测报告/日志/波形全部保留在verification，历史日志可能包含备份前路径，不要拿历史.f作为当前入口。

三任务迁移检查：
python3 accelerator/run_suite.py --root "$PWD" --output verification/dma_current_check_01 --tasks 3 --activity none

12任务：
python3 accelerator/run_suite.py --root "$PWD" --output verification/dma_current_suite12_01

原12任务成绩verification/dma_suite12_01：每项554144周期，累计6649728周期，150MHz归一化270.687763 task/s，最大NRMSE0.02214978%。
这些是验证集预评测，STA待完成。移动后的三任务检查仍需运行。

accelerator/rtl/dma.f是加速器组合源码入口，从kwt-soc解析相对路径；其中包含共享模块。
accelerator/platform/base-*.f是VCS仿真来源模板，含平台FPGA配置，不能直接当ASIC综合配置。
队友做SoC综合需使用新生产顶层，按库与目标配置ASIC宏、源清单和SDC；本脚本不声称综合/时序已通过。
SRAM/工艺库与波形不删除，VCD仍需映射及覆盖检查后用于功耗分析。
''')
    installs=[(acc,root/'accelerator'),(new_top,root/'rtl/e203/soc/kwt_dma_soc_top.v'),(new_tb,root/'tb/tb_top.v'),(readme,root/'README_CURRENT.md')]
    for _,dest in installs:
        need(not dest.exists() or dest in targets,'New target already exists: '+str(dest))
    plan=dict(root=str(root),backup=str(backup),status='STAGED_NOT_APPLIED',old_sha256=old,moves=[str(t.relative_to(root)) for t in targets],installs=[str(d.relative_to(root)) for _,d in installs])
    save(backup/'receipt.json',plan)
    moved=[];installed=[]
    try:
        for target in targets:
            dst=backup/'old'/target.relative_to(root);dst.parent.mkdir(parents=True,exist_ok=True)
            os.replace(target,dst);moved.append((target,dst))
        for src,dest in installs:
            dest.parent.mkdir(parents=True,exist_ok=True);os.replace(src,dest);installed.append(dest)
        for path,want in old.items():need(sha(backup/'old'/Path(path).relative_to(root))==want,'Archived file changed')
        for rel,want in files.items():need(sha(root/'accelerator'/rel)==want,'Installed file changed: '+rel)
        plan['status']='PROMOTED_PENDING_RELOCATION_REGRESSION';save(backup/'receipt.json',plan)
        save(root/'DMA_CURRENT.json',dict(status=plan['status'],backup=str(backup),source_report=str(passed/'report.json'),
            source_report_sha256=sha(passed/'report.json'),current_rtl='accelerator/rtl',soc_top='rtl/e203/soc/kwt_dma_soc_top.v',test_entry='accelerator/run_suite.py',
            old_files_archived=len(old),rtl_and_firmware_byte_identical=True))
    except Exception:
        for dest in reversed(installed):
            recovery=backup/'failed-install'/dest.relative_to(root);recovery.parent.mkdir(parents=True,exist_ok=True);os.replace(dest,recovery)
        for target,dst in reversed(moved):target.parent.mkdir(parents=True,exist_ok=True);os.replace(dst,target)
        plan['status']='ROLLED_BACK';save(backup/'receipt.json',plan);raise
    print('PROMOTED: accelerator/rtl + kwt_dma_soc_top + current driver/test entry')
    print('BACKUP',backup)
    print('NEXT: run 3-task relocation check; old reports and all waveforms retained')

if __name__=='__main__':main()
