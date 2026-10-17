"""Root-local closure receipt; no parent or official acceptance is granted."""
from pathlib import Path
import argparse
import datetime as dt
import os
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc


def ref(path):
    p = ROOT / path
    return {'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p), 'bytes': p.stat().st_size}


def require(value, message):
    if not value:
        raise ValueError(message)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--proof', required=True)
    ap.add_argument('--package-review', required=True)
    ap.add_argument('--baseline', required=True)
    ap.add_argument('--materialization', required=True)
    args = ap.parse_args()
    work = ROOT / 'work/revd_offline_20261017'
    summary_path = work / 'SUMMARY.json'
    require(not summary_path.exists(), 'refuse overwriting final closure')
    summary = read_json(work / 'closure_drafts/package-summary-frozen.json')
    budget = read_json(work / 'budget.json')
    now = dt.datetime.now(dt.timezone.utc)
    stop = dt.datetime.fromisoformat(budget['hard_stop_utc'].replace('Z', '+00:00'))
    soft_finish = dt.datetime.fromisoformat(budget['soft_finish_utc'].replace('Z', '+00:00'))
    require(now < stop, 'deadline reached; use honest partial closure instead')
    require(now < soft_finish, 'review/closure deadline reached; use honest partial closure instead')
    freeze = read_json(work/'ARCHITECTURE_FREEZE.json')
    architecture_deadline = dt.datetime.fromisoformat(budget['architecture_freeze_utc'].replace('Z', '+00:00'))
    require(dt.datetime.fromisoformat(freeze['verified_utc']) < architecture_deadline, 'architecture freeze missed deadline')
    require(all(sha(ROOT/name) == digest for name, digest in freeze['source_sha256'].items()), 'architecture changed after frozen snapshot')
    baseline = read_json(ROOT / args.baseline)
    require(baseline['status'] == 'PASS' and baseline['file_count'] == 17120 and not baseline['failures'], 'baseline guard failed')
    require(baseline['head'] == '3d9d0fc77457b8869cbf525d826dafb114f2a8e1' and baseline['branch'] == 'v2', 'baseline identity changed')
    proof = read_json(ROOT / args.proof)
    folder = ROOT / 'deliverables/kwt_revd_v2_candidate_20261017'
    archive = folder.with_suffix('.zip')
    require(proof['status'] == 'PASS' and (ROOT / proof['archive']).resolve() == archive.resolve(), 'not the actual final ZIP proof')
    require(sha(archive) == proof['archive_sha256'] and sha(folder / 'MANIFEST.json') == proof['package_manifest_sha256'], 'final ZIP/manifest changed')
    materialization = read_json(ROOT/args.materialization)
    require(materialization['status'] == 'MATERIALIZED_EXACT_INDEPENDENTLY_REVIEWED_BYTES' and
            materialization['archive'] == proof['archive'] and
            materialization['archive_sha256'] == proof['archive_sha256'], 'materialization does not bind this final ZIP')
    require(materialization['manifest_before'] == materialization['manifest_after'] and
            materialization['manifest_after']['manifest_sha256'] == proof['package_manifest_sha256'], 'materialization manifest differs')
    require(materialization['actual_native_pid'] > 0 and
            sha(ROOT/'scripts/revd_offline_materialize.py') == materialization['materializer_source_sha256'], 'materialization source/process missing')
    for key in ('proof', 'independent_review', 'independent_execution'):
        require(sha(ROOT/materialization[key]) == materialization[key+'_sha256'], 'materialization evidence changed: '+key)
    require(proof['suites'] == ['manifest', 'smoke', 'numeric', 'cpu-small'] and proof['source_unchanged'], 'incomplete package suites')
    require(len(proof['commands']) == 1 and proof['commands'][0]['exit_code'] == 0, 'portable subprocess did not complete')
    command = proof['commands'][0]
    log = ROOT / command['log']
    require(read_json(log.with_suffix(log.suffix + '.command.json')) == command and sha(log) == command['log_sha256'], 'portable process record changed')
    detail = read_json(ROOT / proof['portable_result'])
    require(detail['status'] == 'PASS' and detail['completed_phases'] == proof['suites'] and detail['tools_unchanged'], 'portable checks not complete')
    require(detail['tool_binary_sha256_before'] == detail['tool_binary_sha256_after'], 'portable tools changed')
    for phase in detail['phase_results']:
        if phase['phase'] in ('numeric', 'cpu-small'):
            require(phase['command']['exit_code'] == 0 and phase['gate']['status'] == 'PASS', 'portable independent gate failed')
            require(sha(ROOT/proof['extraction']/phase['evidence']) == phase['evidence_sha256'], 'portable phase evidence changed')
        elif phase['phase'] == 'smoke':
            require(len(phase['runs']) == 2 and all(x['status'] == 'PASS' for x in phase['runs']), 'portable L1/L2 check missing')
    for name, digest in summary['current_source_sha256'].items():
        require(sha(ROOT / name) == digest, 'accepted source changed: ' + name)
        require(sha(folder / name) == digest, 'delivered source differs: ' + name)
    for item in summary['evidence'].values():
        require(sha(ROOT / item['path']) == item['sha256'], 'frozen evidence changed: ' + item['path'])
    review = read_json(ROOT / args.package_review)
    require(review.get('status') in ('PASS_LOCAL_PACKAGE_REVIEW', 'RECOMMEND_LOCAL_PACKAGE_ACCEPTANCE_WITH_LIMITS'), 'final independent package review not accepted')
    require(review['actual_final_zip_proof'] == {'path': args.proof, 'sha256': sha(ROOT/args.proof)}, 'final review bound to another portable proof')
    require(review['native_materialization'] == {'path': args.materialization, 'sha256': sha(ROOT/args.materialization)}, 'final review bound to another materialization')
    review_names = ['review_rtl_round1.json', 'review_verification_round2.json', 'review_tiled_round2.json',
                   'review_w2_round2.json', 'review_soc_w2_round1.json', 'review_summary_cpu_round2.json']
    reviews = {name: ref('work/revd_offline_20261017/' + name) for name in review_names}
    reviews['final_package'] = ref(args.package_review)
    cpu_package_review = work / 'review_package_cpu_closure.json'
    if cpu_package_review.exists():
        cpu_closure = read_json(cpu_package_review)
        require(cpu_closure.get('status') == 'PASS_SELECTED_CPU_EVIDENCE_PLAN_CLOSURE', 'CPU historical evidence package closure not reviewed')
        green = cpu_closure['new_plan_green']
        require(green['all_required_members_exist_and_are_selected'] and sha(ROOT/green['path']) == green['sha256'], 'reviewed package plan changed')
        delivered_members = read_json(folder/'MANIFEST.json')['files']
        for member in cpu_closure['required_members']:
            require(member['path'] in delivered_members and sha(ROOT/member['path']) == delivered_members[member['path']], 'CPU report/binary/alias missing from actual delivery')
        reviews['cpu_package_closure'] = ref(cpu_package_review.relative_to(ROOT))
    require(read_json(work/'review_verification_round2.json')['status'] == 'RECOMMEND_LOCAL_ACCEPTANCE_WITH_LIMITS', 'verification review not closed')
    require(read_json(work/'review_soc_w2_round1.json')['status'] == 'PASS_SCOPED_W2_SOC_REVIEW', 'W2 SoC review not closed')
    summary.update(status='READY_FOR_REVIEW', finalized_utc=utc(), parent_accepted=False,
        official_contest_acceptance=False, submission_qualified=False, formal_score=None,
        reviews=reviews, completed_candidates=5, new_completed_candidates=4,
        completed_candidate_families=[
            {'profile': 'D2_PM4_FULL_W', 'new_profile': False, 'scope': 'immutable accepted control; fresh same-input complete-case comparison'},
            {'profile': 'D3_CTX4_PM4_FULL_W_X4_Y1', 'new_profile': True, 'scope': 'core36 plus12 public-CPU cold tasks'},
            {'profile': 'D3_CTX4_PM2_FULL_W_X2_Y1', 'new_profile': True, 'scope': 'core36 plus2 public-CPU cold tasks'},
            {'profile': 'D4_CTX4_PM4_W1_X4_Y1', 'new_profile': True, 'scope': 'core36; CPU NOT_RUN'},
            {'profile': 'D5_CTX4_PM4_W2_X4_Y1', 'new_profile': True, 'scope': 'core36 plus2 public-CPU cold tasks and directed flags'}],
        package={'folder': folder.relative_to(ROOT).as_posix(), 'zip': ref(archive.relative_to(ROOT)),
                 'manifest': ref((folder/'MANIFEST.json').relative_to(ROOT)), 'actual_zip_reproduction': ref(args.proof),
                 'independent_review': ref(args.package_review), 'native_materialization': ref(args.materialization),
                 'attestation_external_to_immutable_zip': True},
        baseline_final=ref(args.baseline), closure_source=ref(Path(__file__).relative_to(ROOT)),
        architecture_freeze=ref('work/revd_offline_20261017/ARCHITECTURE_FREEZE.json'),
        frozen_input_manifest=ref('reports/prototype/vectors/manifest.json'),
        portable_runtime_tool_sha256=detail['tool_binary_sha256_before'],
        ready_scope='All promised local selected-profile checks and actual ZIP portable reproduction passed; external formal contest/PPA gaps remain explicit.',
        deadline_respected=True, architecture_freeze_deadline=budget['architecture_freeze_utc'],
        soft_finish_utc=budget['soft_finish_utc'], hard_stop_utc=budget['hard_stop_utc'])
    summary['incomplete_or_not_run'] = [line for line in summary['incomplete_or_not_run'] if not line.startswith('Final archive')]
    for item in summary['requirements']:
        if item['id'] == 'REPRODUCIBLE_PROJECT':
            item['local_status'] = 'PASS_ACTUAL_FINAL_ZIP_ISOLATED_MANIFEST_SMOKE_NUMERIC_REAL_CPU_SMALL'
            item['external_evidence'] = ref(args.proof)
    summary['completed'].append('Actual delivered ZIP extracted into a new directory, outside original ROOT/PYTHONPATH: manifest, newly compiled L1/L2 RTL, all-shift numeric suite and real E203/C small cold tasks independently passed.')
    summary['packaging_repairs'] = [ref('work/revd_offline_20261017/' + name) for name in
        ('package_windows_path_failure.json', 'package_closure_repair.json', 'package_w2_binary_closure_repair.json',
         'package_native_materialization_repair.json')]
    summary['negative_results_and_repairs'].append('WSL filesystem copy was stopped during publication and its partial tree preserved. Native Windows copying materialized the independently validated directory and the exact already tested ZIP bytes; a separate fresh extraction and portable execution then tested the actual delivered ZIP. No source or evidence checks were relaxed.')
    summary['negative_results_and_repairs'].append('Artifact review found omitted CPU comparison counterpart/alias and two W2-named simulator binaries. Only the explicit packaging plan changed; partial publication was preserved outside deliverables, the final archive was rebuilt and its exact bytes re-extracted and retested. All core and CPU source/results remained unchanged.')
    summary['check_boolean_meanings'] = {'submission_checked': 'Every undergraduate deliverable mapped to actual local evidence or an explicit formal gap; not submission qualification.',
        'score_evaluated': 'Undergraduate weights/formulas/qualification audited; no formal points awarded.'}
    require(dt.datetime.now(dt.timezone.utc) < soft_finish, 'closure checks exceeded review deadline; use honest partial closure instead')
    summary['finalized_utc'] = utc()
    put(summary_path, summary)
    state = dict(status='READY_FOR_REVIEW', stage='LOCAL_DELIVERY_CLOSED_AWAITING_PARENT_REVIEW', updated_utc=utc(),
        release_id=summary['release_id'], user_updates='silent', selected_profile=summary['selected_profile'],
        submission_checked=True, regression_checked=True, score_evaluated=True, reviews_passed=True,
        baseline_preserved=True, deadline_respected=True, completed_candidates=5, new_completed_candidates=4,
        parent_accepted=False, official_contest_acceptance=False, formal_score=None, active_cpu=None,
        real_pid=os.getpid(), active_eda_pids=[], run_identity=os.environ.get('KWT_OFFLINE_RUN_ID'),
        summary=ref(summary_path.relative_to(ROOT)), package=summary['package'], baseline_final=ref(args.baseline),
        completed_candidate_families=summary['completed_candidate_families'], reviews=reviews,
        formal_gaps=summary['formal_gaps'], source_sha256=summary['current_source_sha256'],
        core36_unique_outputs_per_new_profile=912384, core36_new_profiles=4,
        default_cpu_scope='six boots, twelve independent FFN1 cold tasks, one engineering input; L1 only',
        W2_cpu_scope='two full FFN1 cold tasks plus directed nonzero flags; L1 only',
        budget='work/revd_offline_20261017/budget.json', hard_stop_utc=budget['hard_stop_utc'],
        remaining_seconds=(stop-now).total_seconds(), remaining=['External official data/platform/designated-process gates; parent independent acceptance'],
        next=['Parent read-only acceptance of this immutable candidate; no further local architecture changes'])
    put(work/'STATUS.json', state)
    print(summary_path, 'READY_FOR_REVIEW', flush=True)


if __name__ == '__main__':
    main()
