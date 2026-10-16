"""Fetch the immutable KWT-1 source subset and verify upstream Git blob hashes."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path, PurePosixPath
import time
import urllib.request

COMMIT = '237e4097afd4f6851e0b82f0a8d65c2dfe8eae30'
ROOT = Path(__file__).resolve().parents[1]
MODEL_FILES = {
    'best_weights.data-00000-of-00001', 'best_weights.index', 'checkpoint',
    'flags.json', 'flags.txt', 'labels.txt', 'model_summary.txt',
}
TOP_FILES = {'README.md', 'requirements.txt', 'eval.sh', 'LICENSE.txt'}


def select_sources(tree):
    return [item for item in tree if item['type'] == 'blob' and (
        item['path'].startswith('kws_streaming/') or item['path'] in TOP_FILES or
        (item['path'].startswith('models_data_v2_12_labels/kwt1/') and
         PurePosixPath(item['path']).name in MODEL_FILES and
         len(PurePosixPath(item['path']).parts) == 3))]


def safe_destination(root, relative):
    path = PurePosixPath(relative)
    if path.is_absolute() or '..' in path.parts or '\\' in relative:
        raise ValueError(f'Unsafe upstream path: {relative}')
    destination = root.joinpath(*path.parts).resolve()
    if not destination.is_relative_to(root.resolve()):
        raise ValueError(f'Outside snapshot: {relative}')
    return destination


def verify_blob(payload, expected):
    actual = hashlib.sha1(b'blob ' + str(len(payload)).encode() + b'\0' + payload).hexdigest()
    if actual != expected:
        raise ValueError(f'Upstream Git blob mismatch: {actual} != {expected}')


def fetch_one(root, item):
    target = safe_destination(root, item['path'])
    url = f"https://raw.githubusercontent.com/ARM-software/keyword-transformer/{COMMIT}/{item['path']}"
    payload = target.read_bytes() if target.is_file() else None
    if payload is not None:
        try:
            verify_blob(payload, item['sha'])
        except ValueError:
            payload = None
    if payload is None:
        for attempt in range(3):
            try:
                request = urllib.request.Request(url, headers={'User-Agent': 'KWT1-source-freeze'})
                with urllib.request.urlopen(request, timeout=120) as response:
                    payload = response.read()
                verify_blob(payload, item['sha'])
                target.parent.mkdir(parents=True, exist_ok=True)
                temporary = target.with_name(target.name + '.download')
                temporary.write_bytes(payload)
                temporary.replace(target)
                break
            except (OSError, ValueError):
                if attempt == 2:
                    raise
                time.sleep(1 + attempt)
    return {'path': item['path'], 'url': url, 'bytes': len(payload),
            'git_blob_sha1': item['sha'], 'sha256': hashlib.sha256(payload).hexdigest()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--workers', type=int, default=8)
    args = parser.parse_args()
    commit = json.loads((ROOT / 'config/upstream-commit.json').read_text(encoding='utf-8'))
    tree = json.loads((ROOT / 'config/upstream-tree.json').read_text(encoding='utf-8'))
    if (commit['sha'] != COMMIT or tree.get('truncated') or
            commit['commit']['tree']['sha'] != tree['sha']):
        raise ValueError('Commit mismatch or truncated upstream file list')
    files = select_sources(tree['tree'])
    snapshot = ROOT / 'vendor/keyword-transformer'
    snapshot.mkdir(parents=True, exist_ok=True)
    with ThreadPoolExecutor(max_workers=args.workers) as executor:
        records = list(executor.map(lambda item: fetch_one(snapshot, item), files))
    manifest = {'repository': 'https://github.com/ARM-software/keyword-transformer',
                'commit': COMMIT, 'snapshot': 'vendor/keyword-transformer',
                'scope': 'All kws_streaming sources, KWT-1 best checkpoint/config and top-level license/setup',
                'files': sorted(records, key=lambda item: item['path'])}
    (ROOT / 'config/source-manifest.json').write_text(
        json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    print(f'SOURCE_FREEZE_PASS files={len(records)} bytes={sum(r["bytes"] for r in records)} commit={COMMIT}')


if __name__ == '__main__':
    main()
