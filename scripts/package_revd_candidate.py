"""Explicit, relative dependency closure; no repository-wide or venv packaging."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import shutil
import sys
import zipfile
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import read_json,put,sha,run_id,utc

NAME='kwt_revd_v2_candidate_20261017'

def build(plan_path):
    plan=read_json(plan_path);stage=ROOT/'work/revd_offline_20261017/package_build'/run_id()/NAME
    stage.mkdir(parents=True,exist_ok=False);copied=set()
    def copy_file(relative,destination=None):
        src=(ROOT/relative).resolve();name=destination or Path(relative).as_posix();dest=stage/name
        if ROOT not in src.parents or not src.is_file():raise ValueError('unresolved/outside package source '+str(relative))
        if stage.resolve() not in dest.resolve().parents:raise ValueError('unsafe package destination')
        if name in copied:
            if sha(dest)!=sha(src):raise ValueError('conflicting package member '+name)
            return
        dest.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(src,dest);copied.add(name)
    for name in plan['files']:copy_file(name)
    for item in plan.get('copies',[]):copy_file(item['source'],item['destination'])
    copy_file('numeric/__init__.py')
    for name in plan.get('trees',[]):
        p=ROOT/name
        for file in sorted(p.rglob('*')):
            if not file.is_file() or '__pycache__' in file.parts or file.suffix in ('.pyc','.pyo','.vcd','.fst'):continue
            if 'obj' in file.relative_to(p).parts and file.name not in ('Vsoc_cpu_tb','Vcore_tb'):continue
            copy_file(file.relative_to(ROOT).as_posix())
    # Frozen model/reference dependency verification is kept reproducible, rather
    # than deleting files required by the frozen provenance checker.
    for d in read_json(ROOT/'config/source-manifest.json')['files']:
        relative='vendor/keyword-transformer/'+d['path'];copy_file(relative)
        if sha(stage/relative)!=d['sha256']:raise ValueError('pinned model source mismatch')
    recipe=read_json(ROOT/'work/revd_offline_20261017/soc/e203-minimal-package-recipe.json')
    for name,digest in recipe['vendor_file_sha256'].items():
        copy_file(name)
        if sha(stage/name)!=digest:raise ValueError('pinned CPU dependency mismatch '+name)
    copy_file('config/e203-source-manifest.json','evidence/original-e203-source-manifest.json')
    put(stage/'config/e203-source-manifest.json',recipe['derived_package_manifest'])
    copy_file('THIRD_PARTY.md','evidence/original-THIRD_PARTY.md')
    copy_file('work/revd_offline_20261017/licensing/CC-BY-4.0.txt','licenses/CC-BY-4.0.txt')
    copy_file('work/revd_offline_20261017/licensing/provenance.json','licenses/provenance.json')
    copy_file('data/speech_commands_subset/manifest.json')
    (stage/'THIRD_PARTY.md').write_text('''# 本包第三方来源与许可\n\n| 内容 | 冻结来源与用途 | 许可文本 |\n| --- | --- | --- |\n| 公开 E203 RTL/include | riscv-mcu/e203_hbirdv2；真实 CPU 执行依赖，派生最小清单见 config/e203-source-manifest.json | vendor/e203_hbirdv2-upstream/LICENSE（Apache 2.0） |\n| KWT 模型代码、best_weights 与前处理来源 | ARM-software/keyword-transformer，提交237e4097；124文件清单见 config/source-manifest.json | vendor/keyword-transformer/LICENSE.txt（Apache 2.0，含原文件通知） |\n| Speech Commands V2 工程输入及派生 FFN1 数组 | Pete Warden / Google Brain，2018；两条 validation WAV，加独立合成静音；选择与SHA见 data/speech_commands_subset/manifest.json | licenses/CC-BY-4.0.txt；获取来源见 licenses/provenance.json |\n\n数据集许可依据为[作者原始论文](https://arxiv.org/pdf/1804.03209)物理第1页；[原许可代码](https://creativecommons.org/licenses/by/4.0/legalcode.en)及其 SPDX 文本镜像已记录。派生步骤为既有模型前处理、逐层 FFN1 输入/参数冻结、按固定尺度量化；没有修改音频说话内容或重新训练。工程子集不是正式600样本。\n\n赛题指南仅作为用户提供的需求依据，其权利归原权利人。自有 RTL/驱动/验证修改不自动改变继承文件的许可证。工具和 Python 虚拟环境未分发；本文件仅列本包实际存在的第三方依赖。历史完整仓库清单与第三方说明保留在 evidence/original-*，不作为本包的现有文件索引。\n''',encoding='utf-8')
    for name in ('MASTER_RELEASE.json','budget.json','score_audit.json','architecture_priority.json','verification_risk.json'):
        copy_file('work/revd_offline_20261017/'+name,'evidence/authorization/'+name)
    for name in plan.get('review_files',[]):copy_file(name,'evidence/reviews/'+Path(name).name)
    for folder in ('scripts','dv','dv/revd','dv/revd_opt'):
        (stage/folder/'__init__.py').write_text('"""Package-local reproducible sources."""\n',encoding='utf-8')
    put(stage/'PACKAGE.json',{'schema_version':1,'created_utc':utc(),'selected_profile':plan['selected_profile'],
        'release_id':'MASTER_RELEASE-KWT-OFFLINE-SCORE-20261017-001','source_workspace_commit':'3d9d0fc77457b8869cbf525d826dafb114f2a8e1',
        'scope':'Local candidate, current-source engineering evidence; not organizer platform or contest acceptance.',
        'parent_accepted':False,'official_contest_acceptance':False,'formal_score':None,
        'known_formal_gaps':plan['known_formal_gaps'],'evidence':plan['evidence'],
        'e203_dependency_note':'137 regular byte-identical RTL/include/license files derived from the pinned full inventory; original full inventory retained as evidence. Symlink targets are dereferenced into portable regular files.',
        'historical_paths_note':'Archived run commands/logs retain original paths; fresh reproduction compiles package-relative sources and creates new receipts.'})
    (stage/'requirements-dv.lock.txt').write_text('numpy==2.4.6\n',encoding='ascii')
    (stage/'README.md').write_text('''# KWT RevD/V2 本地候选\n\n所选配置见 `PACKAGE.json`。这是本地工程候选，正式赛题门槛缺口见同文件；没有正式分数、指定工艺 STA、mm² 或功耗通过声明。\n\n依赖：Linux/WSL、Python 3.12、NumPy 2.4.6、Icarus 12、Verilator 5.020；CPU 复现另需 GNU RISC-V GCC 13.2 / Binutils 2.42、g++、make。自行选择已安装的 Python，无本机绝对 venv 依赖。\n\n```sh\npython3 -B scripts/revd_offline_reproduce.py --suite manifest\npython3 -B scripts/revd_offline_reproduce.py --suite smoke\npython3 -B scripts/revd_offline_reproduce.py --suite numeric\npython3 -B scripts/revd_offline_reproduce.py --suite full36\npython3 -B scripts/revd_offline_reproduce.py --suite cpu-small\n```\n\n`smoke` 会新编译 L1/L2 RTL 并逐值核数据、flags、索引和末项。`numeric` 包含全部 48 shifts、边界、舍入与复位。`full36` 为 3×12 工程例，共 912384 唯一结果，并非正式 600 样本。`cpu-small` 运行真实 E203/C 驱动与冷切参；完整 CPU 运行入口为 `scripts/revd_offline_soc_run.py --stage full --tasks 2`。可用选定解释器直接执行上述 Python 文件。\n\n冻结浮点参数按现有尺度转换：`python3 -B scripts/revd_offline_convert.py`，不重新拟合量化参数。`numeric/fixedpoint.py` 是位真数值模型。历史证据的命令绝对路径仅用于追溯；复现结果写入包内 `reports/revd_offline/` 的全新 run_id，拒绝覆盖。\n\n提交前按 `PACKAGE.json` 中的资格与工艺缺口补齐官方平台、指定库/宏模型、150 MHz STA、面积/功耗、正式样本与所选性能任务。未生成的映射网表、SDC、功耗文件均未用占位物代替。通过后的同一配置与工况再提交；Git 提交和远程发布另行授权。\n\n许可见 `THIRD_PARTY.md`、`vendor/keyword-transformer/LICENSE.txt` 和 `vendor/e203_hbirdv2-upstream/LICENSE`。\n''',encoding='utf-8')
    with (stage/'README.md').open('a',encoding='utf-8') as reader:
        reader.write('\n当前证据汇总见 [SUMMARY](SUMMARY.json) 与 [候选报告](reports/revd_offline/CANDIDATE_REPORT.md)。默认 full-W PM4 有12层CPU覆盖；W2有两层完整CPU冷任务与非零flags证据，是单列的可运行备选。W2入口为 `python3 -B scripts/revd_offline_soc_w2_run.py --stage small`，固定使用 Verilator 与两项冷任务，完整尺寸用 `--stage full`。W1/W2的重复协议历史仅收录范围摘要；其原始独立审查和源码入口保留，不声称所有历史绝对命令可直接移植执行。最终ZIP解压复现收据属于外部本轮SUMMARY/STATUS，避免把尚未生成的ZIP哈希写进其自身。\n')
    files={p.relative_to(stage).as_posix():sha(p) for p in sorted(stage.rglob('*')) if p.is_file()}
    if len({p.casefold() for p in files})!=len(files):raise ValueError('Windows casefold alias in package')
    put(stage/'MANIFEST.json',{'schema_version':1,'files':files,'file_count':len(files),
                             'excluded':'No venv, Git metadata, PDK placeholders, failed runs, waveform dumps or compiler object trees.'})
    return stage

def publish(stage,verification):
    from scripts.revd_offline_reproduce import manifest_check
    manifest_check(stage,allow_runtime=False)
    proof=read_json(verification)
    if proof['status']!='PASS' or proof['package_manifest_sha256']!=sha(stage/'MANIFEST.json'):
        raise ValueError('publication requires a successful round-trip of these exact bytes')
    suites=proof['suites']
    if suites not in (['manifest','smoke','numeric'],['manifest','smoke','numeric','cpu-small']):
        raise ValueError('missing required portable reproduction suites')
    if len(proof['commands'])!=1:raise ValueError('exactly one actual portable reproduction command required')
    if not proof.get('source_unchanged') or not proof.get('python_isolated_flag') or not proof.get('original_root_excluded_from_pythonpath'):
        raise ValueError('portable reproduction did not retain source/isolation integrity')
    expected_sources={'scripts/revd_offline_package_check.py','scripts/revd_offline_common.py'}
    if set(proof['source_sha256'])!=expected_sources or any(sha(ROOT/name)!=digest for name,digest in proof['source_sha256'].items()):
        raise ValueError('portable checker source changed or inventory incomplete')
    extracted=(ROOT/proof['extraction']).resolve()
    archive=(ROOT/proof['archive']).resolve()
    if ROOT not in extracted.parents or ROOT not in archive.parents or sha(archive)!=proof['archive_sha256']:
        raise ValueError('portable archive/extraction identity mismatch')
    if sha(extracted/'MANIFEST.json')!=sha(stage/'MANIFEST.json'):
        raise ValueError('portable extraction used a different manifest')
    entry=extracted/'scripts/revd_offline_reproduce.py'
    if sha(entry)!=proof['entry_sha256'] or sha(stage/'scripts/revd_offline_reproduce.py')!=proof['entry_sha256']:
        raise ValueError('portable entry source mismatch')
    c=proof['commands'][0];log=ROOT/c['log']
    required=['-I','-B',str(entry),'--suite','portable']+(['--with-cpu'] if 'cpu-small' in suites else [])
    if (c['exit_code']!=0 or c['argv'][1:]!=required or Path(c['cwd']).resolve()!=extracted
        or not isinstance(c.get('pid'),int) or c['pid']<=0 or not c.get('finished_utc')
        or not 0<float(c['timeout_seconds'])<=899 or sha(log)!=c['log_sha256']
        or read_json(log.with_suffix(log.suffix+'.command.json'))!=c):
        raise ValueError('portable reproduction process evidence invalid')
    detail_path=(ROOT/proof['portable_result']).resolve()
    if extracted not in detail_path.parents or 'reports/revd_offline/reproduction/' not in detail_path.as_posix():
        raise ValueError('portable result outside isolated extraction')
    detail=read_json(detail_path)
    if (detail.get('status')!='PASS' or detail.get('suite')!='portable' or detail.get('completed_phases')!=suites
        or detail.get('manifest',{}).get('manifest_sha256')!=sha(stage/'MANIFEST.json') or detail.get('python')!=c['argv'][0]
        or detail.get('tools_unchanged') is not True or not detail.get('tool_binary_sha256_before')
        or detail.get('tool_binary_sha256_before')!=detail.get('tool_binary_sha256_after')):
        raise ValueError('actual portable result does not prove required suites')
    if str(detail_path.parent)+' PASS' not in log.read_text(encoding='utf-8'):
        raise ValueError('actual portable success missing from process log')
    target=ROOT/'deliverables'/NAME;archive=target.with_suffix('.zip')
    if target.exists() or archive.exists():raise FileExistsError('refuse overwriting candidate deliverable')
    target.parent.mkdir(parents=True,exist_ok=True);shutil.copytree(stage,target)
    with zipfile.ZipFile(archive,'x',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
        for p in sorted(target.rglob('*')):
            if p.is_file():z.write(p,Path(NAME)/p.relative_to(target))
    return target,archive

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--plan');ap.add_argument('--publish-stage');ap.add_argument('--verification-report');a=ap.parse_args()
    if a.publish_stage:
        stage=Path(a.publish_stage).resolve()
        permitted=(ROOT/'work/revd_offline_20261017/package_build').resolve()
        if permitted not in stage.parents:raise ValueError('publication source outside checked staging workspace')
        if not a.verification_report:ap.error('--verification-report required before publication')
        target,archive=publish(stage,ROOT/a.verification_report);print(json.dumps({'folder':str(target),'zip':str(archive),'zip_sha256':sha(archive)}))
    else:
        if not a.plan:ap.error('--plan required')
        stage=build(ROOT/a.plan);print(stage)
if __name__=='__main__':raise SystemExit(main())
