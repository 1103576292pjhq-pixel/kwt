"""Fetch one archive-order example for each published Speech Commands test class."""
from datetime import datetime, timezone
import hashlib
import io
import json
from pathlib import Path, PurePosixPath
import tarfile
import urllib.request
import wave

ROOT = Path(__file__).resolve().parents[1]
URL = 'https://storage.googleapis.com/download.tensorflow.org/data/speech_commands_test_set_v0.02.tar.gz'
BUILDER = 'https://raw.githubusercontent.com/tensorflow/datasets/master/tensorflow_datasets/datasets/speech_commands/speech_commands_dataset_builder.py'
WORDS = ('yes', 'no', 'up', 'down', 'left', 'right', 'on', 'off', 'stop', 'go')
LABELS = ('_silence_', '_unknown_', *WORDS)
OUTPUT = ROOT / 'data/encoder_test_subset'
REPORT = ROOT / 'reports/encoder/dataset'


def label_for(member):
    path = PurePosixPath(member)
    if path.is_absolute() or '..' in path.parts or len(path.parts) != 2 or path.suffix.lower() != '.wav':
        return None
    word = path.parts[0]
    if word in ('_silence_', '_background_noise_'):
        return '_silence_'
    return word if word in WORDS else '_unknown_'


def validate_audio(payload, label):
    with wave.open(io.BytesIO(payload), 'rb') as audio:
        info = dict(sample_rate=audio.getframerate(), channels=audio.getnchannels(),
                    sample_width_bytes=audio.getsampwidth(), frames=audio.getnframes())
        if (info['sample_rate'], info['channels'], info['sample_width_bytes']) != (16000, 1, 2):
            raise ValueError(f'unsupported WAV {info}')
        if info['frames'] <= 0:
            raise ValueError('empty WAV')
        if info['frames'] > 16000:
            if label != '_silence_':
                raise ValueError('speech example exceeds one second')
            raw = audio.readframes(16000)
            output = io.BytesIO()
            with wave.open(output, 'wb') as clipped:
                clipped.setnchannels(1)
                clipped.setsampwidth(2)
                clipped.setframerate(16000)
                clipped.writeframes(raw)
            info.update(original_frames=info['frames'], frames=16000, clip_offset_frames=0)
            payload = output.getvalue()
    return payload, info


class HashedReader:
    def __init__(self, stream):
        self.stream = stream
        self.sha = hashlib.sha256()
        self.md5 = hashlib.md5()
        self.count = 0

    def read(self, size=-1):
        data = self.stream.read(size)
        self.sha.update(data)
        self.md5.update(data)
        self.count += len(data)
        return data


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')


def main():
    OUTPUT.mkdir(parents=True, exist_ok=True)
    REPORT.mkdir(parents=True, exist_ok=True)
    status = dict(status='RUNNING', expected_classes=12, started_utc=datetime.now(timezone.utc).isoformat())
    write_json(REPORT / 'status.json', status)
    records = {}
    try:
        with urllib.request.urlopen(BUILDER, timeout=45) as source:
            source_bytes = source.read()
        (REPORT / 'tfds_builder.py').write_bytes(source_bytes)
        if b'speech_commands_test_set_v0.02.tar.gz' not in source_bytes:
            raise ValueError('official TensorFlow Datasets source no longer names the expected test archive')
        request = urllib.request.Request(URL, headers={'User-Agent': 'KWT1-published-test-coverage'})
        with urllib.request.urlopen(request, timeout=120) as response:
            metadata = {key: response.headers.get(key) for key in
                        ('Content-Length', 'ETag', 'Last-Modified', 'x-goog-generation', 'x-goog-hash')}
            reader = HashedReader(response)
            with tarfile.open(fileobj=reader, mode='r|gz') as archive:
                for member in archive:
                    label = label_for(member.name)
                    if not member.isfile() or label is None or label in records:
                        continue
                    # Read only WAV entries; never extract archive paths to disk.
                    if member.size > 8 * 1024 * 1024:
                        raise ValueError('unexpectedly large selected audio member')
                    raw = archive.extractfile(member).read()
                    payload, info = validate_audio(raw, label)
                    digest = hashlib.sha256(payload).hexdigest()
                    relative = Path(label) / f'{digest[:20]}.wav'
                    destination = OUTPUT / relative
                    destination.parent.mkdir(parents=True, exist_ok=True)
                    if destination.exists() and destination.read_bytes() != payload:
                        raise ValueError('refusing to replace a different existing sample')
                    destination.write_bytes(payload)
                    records[label] = dict(sample_id=f'test_{label.strip("_")}_{digest[:12]}',
                        relative_path=relative.as_posix(), sha256=digest, word=PurePosixPath(member.name).parts[0],
                        ground_truth_label=label, partition='testing', archive_member=member.name,
                        archive_member_sha256=hashlib.sha256(raw).hexdigest(), bytes=len(payload), **info)
                    status.update(completed_classes=len(records), archive_bytes_read=reader.count)
                    write_json(REPORT / 'status.json', status)
                    print(f'CLASS {label} {member.name} classes={len(records)}/12', flush=True)
                    if len(records) == 12:
                        break
            # Finish the public 112MB stream to bind the whole gzip digest; it is
            # never saved as a second raw dataset in the workspace.
            while reader.read(1024 * 1024):
                pass
        if set(records) != set(LABELS):
            raise ValueError(f'missing test classes {set(LABELS) - set(records)}')
        if metadata['Content-Length'] and reader.count != int(metadata['Content-Length']):
            raise ValueError('truncated archive stream')
        etag = (metadata['ETag'] or '').strip('"')
        if len(etag) == 32 and reader.md5.hexdigest() != etag:
            raise ValueError('whole archive MD5 differs from public object ETag')
        manifest = dict(dataset='Google Speech Commands V2 published test set', version='v0.02',
            archive_url=URL, archive_sha256=reader.sha.hexdigest(), archive_bytes=reader.count,
            archive_md5=reader.md5.hexdigest(), remote_headers=metadata,
            official_builder_url=BUILDER, official_builder_sha256=hashlib.sha256(source_bytes).hexdigest(),
            license='CC-BY-4.0; credit Google Speech Commands / Pete Warden',
            selection='First encountered usable archive member for each of the 12 classes; no model outputs inspected',
            scope='12-class engineering coverage only; not the contest 600 examples or an accuracy estimate',
            preprocessing='Original WAV, except any long silence uses first 16000 frames; model frontend pads short WAVs',
            samples=[records[label] for label in LABELS])
        write_json(OUTPUT / 'manifest.json', manifest)
        status.update(status='PASS', archive_bytes=reader.count, archive_sha256=reader.sha.hexdigest(),
                      manifest_sha256=hashlib.sha256((OUTPUT / 'manifest.json').read_bytes()).hexdigest(),
                      completed_utc=datetime.now(timezone.utc).isoformat())
        write_json(REPORT / 'status.json', status)
        print('PUBLISHED_TEST_SUBSET_PASS classes=12', flush=True)
    except Exception as exc:
        status.update(status='FAIL', error=str(exc), completed_classes=len(records))
        write_json(REPORT / 'status.json', status)
        raise


if __name__ == '__main__':
    main()
