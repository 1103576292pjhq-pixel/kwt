"""Read the delivered ZIP independently; never update accepted source evidence."""
from pathlib import Path, PurePosixPath
import hashlib
import json
import re
import zipfile
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'work/revd_repair_20261017'
delivery = json.loads((WORK / 'delivery_result.json').read_text(encoding='utf-8'))
archive = Path(delivery['archive'])
prefix = archive.stem + '/'

def digest(stream):
    h = hashlib.sha256()
    for block in iter(lambda: stream.read(1048576), b''):
        h.update(block)
    return h.hexdigest()

with archive.open('rb') as source:
    archive_sha = digest(source)
assert archive_sha == delivery['archive_sha256']
assert archive.with_suffix('.zip.sha256').read_text(encoding='utf-8').split()[0] == archive_sha

with zipfile.ZipFile(archive) as z:
    members = z.namelist()
    assert len(members) == len(set(members)) == delivery['zip_members']
    assert len(members) == len({name.casefold() for name in members})
    manifest = json.loads(z.read(prefix + 'DELIVERY_MANIFEST.json'))
    assert set(members) == {prefix + name for name in manifest['files']} | {prefix + 'DELIVERY_MANIFEST.json'}
    assert manifest['file_count'] == len(manifest['files'])
    member_hashes = {}
    for name, record in manifest['files'].items():
        parts = PurePosixPath(name).parts
        assert '..' not in parts and '.git' not in parts and '.venv-dv' not in parts
        with z.open(prefix + name) as source:
            member_hashes[name] = digest(source)
        assert member_hashes[name] == record['sha256'], name
    base = json.loads(z.read(prefix + 'config/repository-delivery.json'))
    for name, expected in base['files_sha256'].items():
        assert member_hashes[name] == expected, name
    candidate = json.loads(z.read(prefix + 'extensions/RevD/MANIFEST.json'))
    assert member_hashes['extensions/RevD/MANIFEST.json'] == manifest['revd_source_manifest_sha256']
    for name, expected in candidate['files'].items():
        assert member_hashes['extensions/RevD/' + name] == expected, name
    assert member_hashes['reports/revd_repair_20261017/root-acceptance.json'] == manifest['root_acceptance_sha256']
    accepted = json.loads(z.read(prefix + 'reports/revd_repair_20261017/root-acceptance.json'))
    assert accepted['status'] == 'ACCEPTED_LOCAL_REPAIR_AND_PRECISION'
    assert not accepted['official_contest_acceptance']
    local_evidence = 0
    for name, expected in accepted['evidence_sha256'].items():
        if name in member_hashes:
            assert member_hashes[name] == expected, name
            local_evidence += 1
    archive_map_name = 'reports/revd_repair_20261017/fresh-package-evidence/SOURCE_MAP.json'
    archived = json.loads(z.read(prefix + archive_map_name))['members']
    for name, record in archived.items():
        actual_name = 'reports/revd_repair_20261017/fresh-package-evidence/' + name
        assert member_hashes[actual_name] == record['sha256'], actual_name
    required = [
        '00_交付说明.md', 'README.md', 'docs/encoder/reports/README.md',
        'reports/revd_repair_20261017/REPORT.md',
        'reports/revd_repair_20261017/precision/README.md',
        'tests/test_revd_cpu_binary_identity.py', 'tests/probe_revd_fresh_cpu_identity.py',
        'dv/revd_opt/package_readme_command_checks.py',
        'scripts/recheck_precision_20261017.py', 'extensions/RevD/README.md',
    ]
    assert all(name in member_hashes for name in required)
    links_checked = 0
    for document in ['00_交付说明.md', 'reports/revd_repair_20261017/REPORT.md', 'docs/encoder/reports/README.md']:
        content = z.read(prefix + document).decode('utf-8')
        for target in re.findall(r'\[[^\]]*\]\(([^)]+)\)', content):
            if '://' in target or target.startswith('#'):
                continue
            relative = PurePosixPath(document).parent / target.split('#')[0]
            normalized = []
            for part in relative.parts:
                if part == '..':
                    normalized.pop()
                elif part != '.':
                    normalized.append(part)
            resolved = '/'.join(normalized)
            assert resolved in member_hashes or any(n.startswith(resolved.rstrip('/') + '/') for n in member_hashes), (document, target)
            links_checked += 1
    reports = [n for n in member_hashes if n.startswith('docs/encoder/reports/') and n.endswith('.md')]
    assert len(reports) == 11  # seven reports, matrix, summary, reproduction guide, navigation
    for number in range(1, 8):
        assert sum(PurePosixPath(name).name.startswith(f'{number:02d}_') for name in reports) == 1

result = {
    'status': 'PASS_INDEPENDENT_DELIVERY_READBACK',
    'checked_utc': datetime.now(timezone.utc).isoformat(),
    'archive': str(archive), 'archive_bytes': archive.stat().st_size,
    'archive_sha256': archive_sha,
    'zip_members': len(members), 'payload_sha256_checks': len(member_hashes),
    'frozen_base_files_checked': len(base['files_sha256']),
    'frozen_revd_files_checked': len(candidate['files']),
    'archived_fresh_evidence_files_checked': len(archived),
    'direct_accepted_evidence_files_checked': local_evidence,
    'navigation_links_checked': links_checked, 'technical_report_markdown_files': len(reports),
    'official_contest_acceptance': False,
    'no_new_simulation_or_performance_claim': True,
}
(WORK / 'delivery-final-check.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
(archive.parent / '最终复核.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(result, ensure_ascii=False), flush=True)
