"""Preserve actual local results after the soft deadline; never grant READY."""
from pathlib import Path
import datetime as dt
import os
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc


def ref(name):
    path = ROOT/name
    return {'path': path.relative_to(ROOT).as_posix(), 'sha256': sha(path)}


def need(value, reason):
    if not value:
        raise ValueError(reason)


def main():
    work = ROOT/'work/revd_offline_20261017'
    need(not (work/'SUMMARY.json').exists(), 'refuse replacing final closure')
    budget = read_json(work/'budget.json')
    hard = dt.datetime.fromisoformat(budget['hard_stop_utc'].replace('Z', '+00:00'))
    need(dt.datetime.now(dt.timezone.utc) < hard, 'hard stop reached')
    summary = read_json(work/'closure_drafts/package-summary-frozen.json')
    proof_name = 'work/revd_offline_20261017/package_checks/20261017T091521Z_81edc325/result.json'
    review_name = 'work/revd_offline_20261017/review_package_final.json'
    materialization_name = 'work/revd_offline_20261017/materializations/20261017T091444Z_aba21dd0/result.json'
    proof = read_json(ROOT/proof_name)
    review = read_json(ROOT/review_name)
    folder = ROOT/'deliverables/kwt_revd_v2_candidate_20261017'
    archive = folder.with_suffix('.zip')
    need(proof['status'] == 'PASS' and proof['source_unchanged'], 'actual portable proof incomplete')
    need((ROOT/proof['archive']).resolve() == archive.resolve(), 'not the actual delivered archive')
    need(sha(archive) == proof['archive_sha256'] and sha(folder/'MANIFEST.json') == proof['package_manifest_sha256'], 'delivered bytes changed')
    need(proof['suites'] == ['manifest', 'smoke', 'numeric', 'cpu-small'], 'portable suites missing')
    command = proof['commands'][0]
    need(command['exit_code'] == 0 and command['pid'] == 467, 'actual portable child did not exit0')
    log = ROOT/command['log']
    need(sha(log) == command['log_sha256'] and read_json(log.with_suffix(log.suffix+'.command.json')) == command, 'portable process record changed')
    detail = read_json(ROOT/proof['portable_result'])
    need(detail['status'] == 'PASS' and detail['completed_phases'] == proof['suites'], 'portable phase incomplete')
    need(detail['tools_unchanged'] and detail['tool_binary_sha256_before'] == detail['tool_binary_sha256_after'], 'tools changed')
    for phase in detail['phase_results']:
        if phase['phase'] in ('numeric', 'cpu-small'):
            need(phase['command']['exit_code'] == 0 and phase['gate']['status'] == 'PASS', 'independent phase gate failed')
            need(sha(ROOT/proof['extraction']/phase['evidence']) == phase['evidence_sha256'], 'phase evidence changed')
        elif phase['phase'] == 'smoke':
            need(len(phase['runs']) == 2 and all(x['status'] == 'PASS' for x in phase['runs']), 'L1/L2 smoke missing')
    need(review['review_scope_passed'] and review['actual_final_artifact_review_complete'], 'artifact review not complete')
    need(review['actual_final_zip_proof'] == ref(proof_name) and review['native_materialization'] == ref(materialization_name), 'review bound to other evidence')
    need(review['overall_run_status_required'] == 'TIMEBOX_ENDED_PARTIAL' and not review['deadline_respected'] and not review['ready_for_review_eligible'], 'late review scope changed')
    for name, digest in summary['current_source_sha256'].items():
        need(sha(ROOT/name) == digest and sha(folder/name) == digest, 'current/delivered source differs: '+name)
    for evidence in summary['evidence'].values():
        need(sha(ROOT/evidence['path']) == evidence['sha256'], 'accepted evidence changed')
    baseline = read_json(work/'baseline_final.json')
    need(baseline['status'] == 'PASS' and baseline['file_count'] == 17120 and not baseline['failures'], 'baseline guard failed')
    need(baseline['head'] == '3d9d0fc77457b8869cbf525d826dafb114f2a8e1' and baseline['branch'] == 'v2', 'baseline identity changed')
    need(sha(work/'baseline_guard.json') == baseline['guard_sha256'], 'guard changed')
    cleanup = read_json(work/'process_cleanup_final.json')
    need(cleanup['status'] == 'PASS' and not cleanup['active_eda_processes'] and not cleanup['old_checker_wrapper_or_CPU_processes'], 'owned processes remain')
    exit_receipt = read_json(work/'final_archive_checker_exit.json')
    handoff = read_json(work/'final_archive_timeout_handoff_final.json')
    need(exit_receipt['checker_exit_code'] == exit_receipt['portable_exit_code'] == 0 and handoff['outer_exit_code'] == 1, 'process outcome misreported')
    reviews = {name: ref('work/revd_offline_20261017/'+name) for name in (
        'review_rtl_round1.json', 'review_verification_round2.json', 'review_tiled_round2.json',
        'review_w2_round2.json', 'review_soc_w2_round1.json', 'review_summary_cpu_round2.json',
        'review_package_cpu_closure.json', 'review_package_final.json')}
    cpu_closure = read_json(work/'review_package_cpu_closure.json')
    need(cpu_closure['status'] == 'PASS_SELECTED_CPU_EVIDENCE_PLAN_CLOSURE', 'CPU dependency review failed')
    delivered = read_json(folder/'MANIFEST.json')['files']
    for member in cpu_closure['required_members']:
        need(member['path'] in delivered and sha(ROOT/member['path']) == delivered[member['path']], 'CPU dependency absent')
    families = [
        {'profile': 'D2_PM4_FULL_W', 'new_profile': False, 'scope': 'immutable control; fresh matched complete-case comparison'},
        {'profile': 'D3_CTX4_PM4_FULL_W_X4_Y1', 'new_profile': True, 'scope': 'core36;12 public-CPU cold tasks in6 boots; L1 CPU'},
        {'profile': 'D3_CTX4_PM2_FULL_W_X2_Y1', 'new_profile': True, 'scope': 'core36;2 public-CPU cold tasks; L1 CPU'},
        {'profile': 'D4_CTX4_PM4_W1_X4_Y1', 'new_profile': True, 'scope': 'core36; CPU NOT_RUN'},
        {'profile': 'D5_CTX4_PM4_W2_X4_Y1', 'new_profile': True, 'scope': 'core36;2 public-CPU cold tasks plus directed flags; L1 CPU'}]
    partial_reason = 'Final ZIP proof completed09:34:28, but final independent review and root closure missed09:35 soft_finish. All local artifact checks below passed; the overall run is PARTIAL and no READY acceptance is granted.'
    package = {'folder': folder.relative_to(ROOT).as_posix(), 'zip': ref(archive.relative_to(ROOT)),
        'manifest': ref((folder/'MANIFEST.json').relative_to(ROOT)), 'actual_zip_reproduction': ref(proof_name),
        'independent_review': ref(review_name), 'native_materialization': ref(materialization_name),
        'attestation_external_to_immutable_zip': True, 'outer_envelope_passed': False,
        'checker_exit': ref('work/revd_offline_20261017/final_archive_checker_exit.json'),
        'outer_timeout_handoff': ref('work/revd_offline_20261017/final_archive_timeout_handoff_final.json')}
    summary.update(status='TIMEBOX_ENDED_PARTIAL', finalized_utc=utc(), partial_reason=partial_reason,
        parent_accepted=False, official_contest_acceptance=False, formal_score=None, submission_qualified=False,
        submission_checked=True, regression_checked=True, score_evaluated=True, reviews_passed=True,
        baseline_preserved=True, deadline_respected=False, hard_stop_respected=True,
        completed_candidates=5, new_completed_candidates=4, completed_candidate_families=families,
        reviews=reviews, package=package, baseline_final=ref('work/revd_offline_20261017/baseline_final.json'),
        process_cleanup=ref('work/revd_offline_20261017/process_cleanup_final.json'),
        architecture_freeze=ref('work/revd_offline_20261017/ARCHITECTURE_FREEZE.json'),
        frozen_input_manifest=ref('reports/prototype/vectors/manifest.json'),
        portable_runtime_tool_sha256=detail['tool_binary_sha256_before'],
        soft_finish_utc=budget['soft_finish_utc'], hard_stop_utc=budget['hard_stop_utc'],
        local_artifact_checks_passed=True, ready_for_review_eligible=False,
        partial_closeout_source=ref(Path(__file__).relative_to(ROOT)),
        partial_closeout_pid=os.getpid(), native_python_executable=sys.executable,
        native_python_sha256=sha(Path(sys.executable)))
    summary['incomplete_or_not_run'] = [x for x in summary['incomplete_or_not_run'] if not x.startswith('Final archive')]+[partial_reason]
    summary['completed'].append('Actual final ZIP independently extracted; fresh L1/L2 RTL,2170 numeric vectors,52 public all-shift cases and real E203/C two-task96-output fixture passed with12 actual tools unchanged.')
    for item in summary['requirements']:
        if item['id'] == 'REPRODUCIBLE_PROJECT':
            item.update(local_status='PASS_ACTUAL_FINAL_ZIP_ISOLATED_MANIFEST_SMOKE_NUMERIC_REAL_CPU_SMALL;_FINAL_REVIEW_LATE', external_evidence=ref(proof_name))
    summary['packaging_repairs'] = [ref('work/revd_offline_20261017/'+name) for name in (
        'package_windows_path_failure.json', 'package_closure_repair.json', 'package_w2_binary_closure_repair.json',
        'package_native_materialization_repair.json', 'final_archive_timeout_handoff.json', 'final_archive_timeout_handoff_final.json')]
    summary['negative_results_and_repairs'] += [
        'Artifact review found missing D2 comparison dependencies and two W2-named simulator binaries; v3 explicit packaging fixes preserved all sources/results and passed actual final ZIP review.',
        'WSL file copying was replaced by native copying of independently checked exact directory/ZIP bytes, followed by separate actual final-ZIP reproduction.',
        'Final file validation exceeded the original outer filesystem timeout envelope. Only that supervisor was paused/killed after all simulations finished; checker420 actual0 and portable467 actual0 were recorded, while the Windows WSL client actually exited1. No outer PASS is claimed.',
        partial_reason]
    summary['check_boolean_meanings'] = {'submission_checked': 'Requirements mapped to local evidence or formal gaps; not formal eligibility.',
        'score_evaluated': 'Undergraduate rules/weights/formulas audited; no formal points.',
        'reviews_passed': 'Artifact-local review scopes passed; final review was late and grants no overall READY.'}
    need(dt.datetime.now(dt.timezone.utc) < hard, 'hard stop reached before publication')
    summary['finalized_utc'] = utc()
    put(work/'SUMMARY.json', summary)
    state = {key: summary[key] for key in ('status', 'selected_profile', 'partial_reason', 'submission_checked',
        'regression_checked', 'score_evaluated', 'reviews_passed', 'baseline_preserved', 'deadline_respected',
        'hard_stop_respected', 'completed_candidates', 'new_completed_candidates', 'parent_accepted',
        'official_contest_acceptance', 'formal_score', 'completed_candidate_families', 'reviews', 'formal_gaps')}
    state.update(stage='LOCAL_ARTIFACT_PASSED_CLOSURE_MISSED_SOFT_DEADLINE', updated_utc=utc(),
        release_id=summary['release_id'], user_updates='silent', summary=ref('work/revd_offline_20261017/SUMMARY.json'),
        package=package, baseline_final=summary['baseline_final'], process_cleanup=summary['process_cleanup'],
        source_sha256=summary['current_source_sha256'], real_pid=os.getpid(), active_eda_pids=[], active_cpu=None,
        run_identity=os.environ.get('KWT_OFFLINE_RUN_ID'), ready_for_review_eligible=False,
        core36_unique_outputs_per_new_profile=912384, core36_new_profiles=4,
        budget='work/revd_offline_20261017/budget.json', soft_finish_utc=budget['soft_finish_utc'], hard_stop_utc=budget['hard_stop_utc'],
        remaining=['Overall review/closure missed soft deadline; no READY granted.', *summary['formal_gaps'], 'Parent independent acceptance'],
        next=['Preserve immutable candidate and evidence for parent review; no further local execution.'])
    put(work/'STATUS.json', state)
    print('TIMEBOX_ENDED_PARTIAL; local artifact passed, soft deadline missed', flush=True)


if __name__ == '__main__':
    main()
