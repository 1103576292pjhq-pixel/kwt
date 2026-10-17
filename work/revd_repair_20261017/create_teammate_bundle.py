"""Create one external teammate ZIP from frozen base + verified RevD extension."""
from pathlib import Path
import hashlib
import json
import stat
import subprocess
import sys
import zipfile
from datetime import datetime

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
OUT = Path(r'C:\Users\11035\Desktop\ic\交付包')
PREFIX = 'KWT_完整工程_20261017'


def disk(path):
    value = str(path.resolve())
    return Path('\\\\?\\' + value) if sys.platform == 'win32' and not value.startswith('\\\\?\\') else path


def sha(path):
    h = hashlib.sha256()
    with disk(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def read(path):
    return json.loads(disk(path).read_text(encoding='utf-8'))


def main():
    acceptance = read(ROOT / 'reports/revd_repair_20261017/root-acceptance.json')
    if acceptance['status'] != 'ACCEPTED_LOCAL_REPAIR_AND_PRECISION' or acceptance['official_contest_acceptance']:
        raise ValueError('current scoped root acceptance required; no contest acceptance implied')
    state = read(ROOT / 'work/revd_repair_20261017/package_state.json')
    if state['status'] != 'ROUNDTRIP_AND_W2_PASS':
        raise ValueError('fresh extracted package and W2 proof required')
    stage = ROOT / state['stage']
    base = read(ROOT / 'config/repository-delivery.json')
    candidate = read(stage / 'MANIFEST.json')
    if sha(stage / 'MANIFEST.json') != state['manifest_sha256']:
        raise ValueError('candidate manifest changed')
    entries = {}

    def add(name, source, expected=None, component='base'):
        if name in entries:
            raise ValueError('duplicate package path ' + name)
        parts = Path(name).parts
        if '..' in parts or Path(name).is_absolute() or '.git' in parts:
            raise ValueError('unsafe package path ' + name)
        entries[name] = (source, expected, component)

    for name, digest in base['files_sha256'].items():
        add(name, ROOT / name, digest)
    add('config/repository-delivery.json', ROOT / 'config/repository-delivery.json')
    for name, digest in candidate['files'].items():
        add('extensions/RevD/' + name, stage / name, digest, 'verified_revd_extension')
        # Keep the current repository's source/evidence layout readable too.
        # Generated package aliases and its derived minimal E203 inventory do
        # not replace the frozen full inventory in the base project.
        original = ROOT / name
        if name not in entries and disk(original).is_file() and sha(original) == digest:
            add(name, original, digest, 'current_revd_sources_and_history')
    add('extensions/RevD/MANIFEST.json', stage / 'MANIFEST.json', state['manifest_sha256'], 'verified_revd_extension')
    for p in sorted(disk(ROOT / 'docs/revd').rglob('*')):
        if p.is_file():
            name = 'docs/revd/' + p.relative_to(disk(ROOT / 'docs/revd')).as_posix()
            if name not in entries:
                add(name, p, component='revd_design_documents')
    for name in ('recheck_precision_20261017.py', 'audit_precision_outputs_20261017.py', 'diagnose_precision_trace_20261017.py'):
        add('scripts/' + name, ROOT / 'scripts' / name, component='precision_recheck')
    original_export = ROOT / 'reports/encoder/export-recheck-20261017'
    for p in sorted(disk(original_export).rglob('*')):
        if p.is_file():
            name = 'reports/encoder/export-recheck-20261017/' + p.relative_to(disk(original_export)).as_posix()
            add(name, p, component='unmodified_official_export_recheck')
    repair = ROOT / 'reports/revd_repair_20261017'
    for p in sorted(disk(repair).rglob('*')):
        if p.is_file():
            relative = p.relative_to(disk(repair)).as_posix()
            add('reports/revd_repair_20261017/' + relative, p, component='repair_and_precision_evidence')
    add('work/revd_current.json', ROOT / 'work/revd_current.json', component='latest_scoped_status_pointer')
    if len({name.casefold() for name in entries}) != len(entries):
        raise ValueError('Windows casefold path collision')

    guide = '''# KWT 完整工程交付说明

本包包含已接受的七项基础原型、技术报告，以及本轮修复后独立验证的 RevD FFN1 扩展。请将整个文件夹解压后阅读，不要只传单个 RTL 文件。

## 阅读顺序

1. [基础工程 README](README.md)：架构、环境、七项任务与正式待验边界。
2. [七项技术报告](docs/encoder/reports/README.md)：本科先读01→02→03，再读04→05→06→07。
3. [本轮详细交付报告](reports/revd_repair_20261017/REPORT.md)：修复、实测、复现、范围与风险。
4. [精度复测说明](reports/revd_repair_20261017/precision/README.md)：180个FFN1案例、完整FP32分类、历史浮点微差。
5. [RevD扩展 README](extensions/RevD/README.md)：优化FFN1的独立运行入口。RevD不是完整十二层编码器。

根目录也保留当前RevD源码和历史证据，便于沿原仓库路径阅读。`docs/revd/STATUS.json`是实现前的设计快照；本轮状态以新详细交付报告及root-acceptance为准。

## 基础七项工程

在本包根目录用WSL/Linux执行：

```bash
python3 scripts/prepare_repository.py
python3 scripts/verify_repository.py
```

准备命令仅恢复四个固定E203相对链接。Python环境和EDA工具不打包，按根README安装。快速小案例按根README执行；历史报告的原绝对路径保留用于追溯，不表示在队友机器重新验收。

## 本轮RevD扩展

该目录与基础版分开冻结，保留自己的数值契约、来源清单和MANIFEST。不要把其中派生的最小E203清单覆盖基础工程的完整清单。

```bash
cd extensions/RevD
python3 -B scripts/revd_offline_reproduce.py --suite manifest
python3 -B scripts/revd_offline_reproduce.py --suite portable --with-cpu
python3 -B scripts/revd_offline_soc_w2_run.py --stage small
```

最后一条W2命令固定用Verilator执行两个小任务；不接受`--sim`或`--tasks`。真实运行需要Linux/WSL、对应Python/NumPy、Icarus、Verilator、GNU RISC-V工具链、g++和make，版本见扩展README。

## 验收与交接边界

基础七项是本地原型验收；RevD新记录只关闭CPU执行文件身份与W2命令两项交付缺陷，并复测精度。原定时批次的PARTIAL记录作为历史保留，不被改写。本包没有正式600样本、官方十二性能任务、指定平台/库/宏、150MHz、2.25mm²、综合后功能、功耗能耗的正式通过声明。

本轮不改变RTL、权重或量化尺度。新的180案例误差与旧36案例分开统计，不能将不同样本集合的较低误差称为硬件优化收益。

`DELIVERY_MANIFEST.json`列出全部成员的SHA-256；外部同名`.sha256`校验整个ZIP。压缩包不含Git历史、虚拟环境或新的压缩包副本。部分编译结果和历史日志属于既有证据，因此保留。
'''
    OUT.mkdir(parents=True, exist_ok=True)
    archive = OUT / (PREFIX + '.zip')
    if archive.exists():
        raise FileExistsError('refuse overwriting teammate archive')
    files = {}
    bundle_time = datetime.now().timetuple()[:6]
    with zipfile.ZipFile(archive, 'x', zipfile.ZIP_DEFLATED, compresslevel=6) as z:
        for name, (source, expected, component) in sorted(entries.items()):
            source = disk(source)
            digest = sha(source)
            if expected and digest != expected:
                raise ValueError('frozen source changed ' + name)
            info = zipfile.ZipInfo(PREFIX + '/' + name, date_time=bundle_time)
            info.create_system = 3
            mode = 0o755 if source.suffix == '.sh' else 0o644
            info.external_attr = (stat.S_IFREG | mode) << 16
            info.compress_type = zipfile.ZIP_DEFLATED
            h = hashlib.sha256()
            with source.open('rb') as inp, z.open(info, 'w') as target:
                for block in iter(lambda: inp.read(1024 * 1024), b''):
                    target.write(block)
                    h.update(block)
            if h.hexdigest() != digest:
                raise ValueError('source changed while packaging ' + name)
            files[name] = {'sha256': digest, 'component': component}
        guide_bytes = guide.encode('utf-8')
        z.writestr(PREFIX + '/00_交付说明.md', guide_bytes)
        files['00_交付说明.md'] = {'sha256': hashlib.sha256(guide_bytes).hexdigest(), 'component': 'reader_entry'}
        manifest = {'status': 'LOCAL_REVIEWED_DELIVERY', 'official_contest_acceptance': False,
                    'source_workspace_base_commit': 'ef92c1adee24ec48a422b3e8bfc0eb0cbba1281e',
                    'working_changes_included_without_commit': True,
                    'base_source_manifest_sha256': sha(ROOT / 'config/repository-delivery.json'),
                    'revd_source_manifest_sha256': state['manifest_sha256'],
                    'root_acceptance_sha256': sha(repair / 'root-acceptance.json'),
                    'files': files, 'file_count': len(files),
                    'self_hash_note': 'DELIVERY_MANIFEST.json is excluded from its own file map.'}
        z.writestr(PREFIX + '/DELIVERY_MANIFEST.json', json.dumps(manifest, ensure_ascii=False, indent=2).encode('utf-8'))
    # Independent ZIP member reads validate both decompression CRC and every SHA.
    with zipfile.ZipFile(archive) as z:
        assert len(z.namelist()) == len(files) + 1
        assert len(set(name.casefold() for name in z.namelist())) == len(z.namelist())
        for name, item in files.items():
            with z.open(PREFIX + '/' + name) as stream:
                h = hashlib.sha256()
                for block in iter(lambda: stream.read(1024 * 1024), b''):
                    h.update(block)
            if h.hexdigest() != item['sha256']:
                raise ValueError('archive readback mismatch ' + name)
    digest = sha(archive)
    (OUT / (PREFIX + '.zip.sha256')).write_text(digest + '  ' + archive.name + '\n', encoding='utf-8', newline='\n')
    (OUT / '先读我.md').write_text('请发送`' + archive.name + '`和同名`.sha256`给队友。\n\n解压后先读`00_交付说明.md`。完整工程含基础七项与独立RevD扩展；正式赛题评测仍待完成。\n', encoding='utf-8')
    result = {'status': 'PASS', 'archive': str(archive), 'archive_bytes': archive.stat().st_size,
              'archive_sha256': digest, 'zip_members': len(files) + 1,
              'base_files': len(base['files_sha256']) + 1,
              'revd_files': len(candidate['files']) + 1,
              'all_member_sha_readback_passed': True, 'builder_sha256': sha(Path(__file__)),
              'official_contest_acceptance': False}
    (OUT / '交付包校验.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    (ROOT / 'work/revd_repair_20261017/delivery_result.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result, ensure_ascii=False), flush=True)


if __name__ == '__main__':
    main()
