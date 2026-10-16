"""Acquire a small real validation smoke subset from the official V2 tar stream."""
import argparse
import ast
import hashlib
import io
import json
import os
from pathlib import Path, PurePosixPath
import re
import tarfile
from types import SimpleNamespace
import urllib.request
import wave

ROOT = Path(__file__).resolve().parents[1]
URL = 'https://storage.googleapis.com/download.tensorflow.org/data/speech_commands_v0.02.tar.gz'


def official_partition_function():
    source = ROOT / 'vendor/keyword-transformer/kws_streaming/data/input_data.py'
    tree = ast.parse(source.read_text(encoding='utf-8'))
    nodes = [node for node in tree.body if (
        isinstance(node, ast.FunctionDef) and node.name == 'which_set') or (
        isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and
        t.id == 'MAX_NUM_WAVS_PER_CLASS' for t in node.targets))]
    if len(nodes) != 2:
        raise ValueError('Official partition definition not found')
    namespace = {'os': os, 're': re, 'hashlib': hashlib,
                 'compat': SimpleNamespace(as_bytes=lambda value: value.encode('utf-8'))}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(source), 'exec'), namespace)
    return namespace['which_set'], hashlib.sha256(source.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--samples', type=int, default=2)
    args = parser.parse_args()
    if args.samples < 1 or args.samples > 12:
        raise ValueError('First-batch subset must contain 1..12 real validation samples')
    flags = json.loads((ROOT / 'vendor/keyword-transformer/models_data_v2_12_labels/kwt1/flags.json').read_text())
    partition, partition_hash = official_partition_function()
    validation, testing = flags['validation_percentage'], flags['testing_percentage']
    output = ROOT / 'data/speech_commands_subset'
    output.mkdir(parents=True, exist_ok=True)
    speakers, records = set(), []
    request = urllib.request.Request(URL, headers={'User-Agent': 'KWT1-validation-smoke'})
    with urllib.request.urlopen(request, timeout=120) as response:
        remote = {key: response.headers.get(key) for key in ('ETag', 'Last-Modified', 'Content-Length')}
        with tarfile.open(fileobj=response, mode='r|gz') as archive:
            for member in archive:
                path = PurePosixPath(member.name)
                if not member.isfile() or path.suffix.lower() != '.wav' or '..' in path.parts or path.is_absolute():
                    continue
                if len(path.parts) != 2 or path.parts[0].startswith('_'):
                    continue
                if partition(path.name, validation, testing) != 'validation':
                    continue
                speaker = re.sub(r'_nohash_.*$', '', path.name)
                if speaker in speakers:
                    continue
                extracted = archive.extractfile(member)
                payload = extracted.read()
                with wave.open(io.BytesIO(payload), 'rb') as audio:
                    properties = {'sample_rate': audio.getframerate(), 'channels': audio.getnchannels(),
                                  'sample_width_bytes': audio.getsampwidth(), 'frames': audio.getnframes()}
                if properties['sample_rate'] != 16000 or properties['channels'] != 1 or properties['sample_width_bytes'] != 2:
                    continue
                destination = output.joinpath(*path.parts)
                destination.parent.mkdir(parents=True, exist_ok=True)
                destination.write_bytes(payload)
                speakers.add(speaker)
                records.append({'sample_id': path.as_posix(), 'word': path.parts[0],
                                'relative_path': path.as_posix(), 'partition': 'validation',
                                'sha256': hashlib.sha256(payload).hexdigest(),
                                'archive_member': member.name, 'bytes': len(payload), **properties})
                print(f'VALIDATION_SAMPLE {path.as_posix()} frames={properties["frames"]}', flush=True)
                if len(records) == args.samples:
                    break
    if len(records) != args.samples:
        raise ValueError('Insufficient real validation samples in official archive')
    manifest = {'dataset': 'Google Speech Commands V2', 'version': 'speech_commands_v0.02',
                'dataset_url': URL, 'remote_headers': remote,
                'scope': 'Small real validation subset for pipeline smoke; not the full validation or competition evaluation set',
                'selection': 'First validation members encountered in official archive; distinct speaker IDs; no accuracy-based selection',
                'partition_basis': {'function': 'kws_streaming.data.input_data.which_set',
                                    'source_sha256': partition_hash,
                                    'validation_percentage': validation, 'testing_percentage': testing,
                                    'method': 'Executed the original AST definition with its original hash constant'},
                'archive_integrity': 'Partial streaming acquisition; no whole-archive SHA-256 claim',
                'samples': records}
    (output / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    print(f'DATA_SUBSET_PASS samples={len(records)}')


if __name__ == '__main__':
    main()
