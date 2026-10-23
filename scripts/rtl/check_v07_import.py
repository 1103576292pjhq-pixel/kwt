"""Verify the imported standalone V07 snapshot without external dependencies."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    manifest = json.loads((ROOT / 'docs/shared/standalone-v07-import.json').read_text())
    for entry in manifest['files']:
        path = (ROOT / entry['path']).resolve()
        if ROOT not in path.parents:
            raise ValueError('Import path escapes repository: ' + entry['path'])
        digest = hashlib.sha256(path.read_bytes()).hexdigest()
        if digest != entry['sha256']:
            raise ValueError('Imported file differs: ' + entry['path'])
    print('PASS: {} imported V07 files match source snapshot'.format(len(manifest['files'])))


if __name__ == '__main__':
    main()
