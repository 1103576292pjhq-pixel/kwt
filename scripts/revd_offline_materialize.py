"""Materialize an independently validated package using native Windows I/O.

This control-only utility is not a hardware/reproduction source. It copies the
exact already tested ZIP, then requires a separate final-ZIP reproduction.
"""
from pathlib import Path
import argparse
import os
import shutil
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, run_id, utc
from scripts.revd_offline_reproduce import manifest_check


def need(value, reason):
    if not value:
        raise ValueError(reason)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--stage', required=True)
    ap.add_argument('--proof', required=True)
    ap.add_argument('--review', required=True)
    args = ap.parse_args()
    need(os.name == 'nt', 'use native Windows with extended filesystem paths')
    started = utc()
    stage = (ROOT/args.stage).resolve()
    allowed = (ROOT/'work/revd_offline_20261017/package_build').resolve()
    need(allowed in stage.parents, 'stage outside authorized workspace')
    proof_path = ROOT/args.proof
    review_path = ROOT/args.review
    proof = read_json(proof_path)
    review = read_json(review_path)
    execution_path = review_path.parent/'execution.json'
    execution = read_json(execution_path)
    probe_path = review_path.parent/'probe.py'
    need(sha(probe_path) == review['probe_source_sha256'], 'independent probe source changed')
    need(execution['status'] == 'PASS' and execution['exit_code'] == 0 and execution['pid'] > 0,
         'independent probe process did not pass')
    need(execution['argv'][-2:] == [args.stage, args.proof] and
         execution['argv'][-3] == '/mnt/d/github/kwt/'+probe_path.relative_to(ROOT).as_posix(),
         'independent probe execution identifies other inputs')
    need(review['status'] == 'PASS' and review['source_unchanged'] and review['proof_unchanged'], 'independent rebind not passed')
    need(review['stage'] == stage.relative_to(ROOT).as_posix() and review['proof'] == Path(args.proof).as_posix(), 'review identifies another artifact')
    need(sha(proof_path) == review['proof_sha256'], 'independently reviewed proof changed')
    for name, digest in review['source_sha256'].items():
        need(sha(ROOT/name) == digest and sha(stage/name) == digest, 'validator source changed: '+name)
    negative = review['negative_test_reused']
    need(negative['source_identity_exact'] and negative['negative_count'] == 26 and sha(ROOT/negative['path']) == negative['sha256'], 'negative review binding changed')
    need(proof['status'] == 'PASS' and proof['source_unchanged'] and proof['suites'] == ['manifest', 'smoke', 'numeric', 'cpu-small'], 'incomplete portable proof')
    need(proof['commands'][0]['pid'] == review['actual_portable_pid'] and proof['commands'][0]['exit_code'] == review['actual_portable_exit_code'] == 0, 'actual portable process not accepted')
    need(sha(ROOT/review['actual_portable_detail']) == review['actual_portable_detail_sha256'], 'actual portable result changed')
    before = manifest_check(stage, allow_runtime=False)
    need(before == review['manifest'] and before['manifest_sha256'] == proof['package_manifest_sha256'], 'full stage differs from accepted bytes')
    source_archive = (ROOT/proof['archive']).resolve()
    need(ROOT in source_archive.parents and sha(source_archive) == proof['archive_sha256'], 'tested archive changed')
    target = ROOT/'deliverables/kwt_revd_v2_candidate_20261017'
    archive = target.with_suffix('.zip')
    need(not target.exists() and not archive.exists(), 'refuse overwriting a deliverable')
    out = ROOT/'work/revd_offline_20261017/materializations'/run_id()
    out.mkdir(parents=True, exist_ok=False)
    self_digest = sha(Path(__file__))
    source_manifest_digest = sha(stage/'MANIFEST.json')
    shutil.copytree(stage, target)
    after = manifest_check(target, allow_runtime=False)
    need(after == before, 'materialized directory differs')
    shutil.copyfile(source_archive, archive)
    archive_digest = sha(archive)
    need(archive_digest == proof['archive_sha256'] and sha(stage/'MANIFEST.json') == source_manifest_digest, 'copied ZIP or source manifest changed')
    need(sha(Path(__file__)) == self_digest, 'materializer source changed during copy')
    put(out/'result.json', {
        'status': 'MATERIALIZED_EXACT_INDEPENDENTLY_REVIEWED_BYTES', 'started_utc': started, 'finished_utc': utc(),
        'actual_native_pid': os.getpid(), 'run_identity': os.environ.get('KWT_OFFLINE_RUN_ID'),
        'stage': args.stage, 'proof': args.proof, 'proof_sha256': sha(proof_path),
        'independent_review': args.review, 'independent_review_sha256': sha(review_path),
        'independent_execution': execution_path.relative_to(ROOT).as_posix(), 'independent_execution_sha256': sha(execution_path),
        'independent_probe_sha256': sha(probe_path), 'independent_probe_process_pid': execution['pid'],
        'source_archive': proof['archive'], 'archive': archive.relative_to(ROOT).as_posix(), 'archive_sha256': archive_digest,
        'folder': target.relative_to(ROOT).as_posix(), 'manifest_before': before, 'manifest_after': after,
        'materializer_source_sha256': self_digest, 'validator_source_sha256': review['source_sha256'],
        'actual_final_archive_reproduction': 'PENDING_SEPARATE_CHECK',
        'parent_accepted': False, 'official_contest_acceptance': False,
    })
    print(out.relative_to(ROOT).as_posix(), archive_digest, flush=True)


if __name__ == '__main__':
    main()
