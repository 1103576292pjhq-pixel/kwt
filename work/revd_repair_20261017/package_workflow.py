"""Run the authorized repair in a new package; preserve all historical receipts."""
from pathlib import Path
import argparse
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from scripts import revd_offline_common as common
from scripts.revd_offline_common import read_json, put, sha, utc, run_id

WORK = ROOT / 'work/revd_repair_20261017'
STATE = WORK / 'package_state.json'
common.WORK = WORK  # This new batch never rewrites or extends the old budget.


def build():
    from scripts import package_revd_candidate as packager
    plan = read_json(ROOT / 'work/revd_offline_20261017/package_plan_final_v3.json')
    plan['files'] += [
        'tests/test_revd_cpu_binary_identity.py',
        'tests/probe_revd_fresh_cpu_identity.py',
        'dv/revd_opt/package_readme_command_checks.py',
        'work/revd_repair_20261017/PLAN.md',
        'work/revd_repair_20261017/package_workflow.py',
        'work/revd_offline_20261017/ROOT_FINAL.json',
        'work/revd_offline_20261017/root_acceptance.json',
    ]
    plan['files'] = sorted(set(plan['files']))
    summary = {
        'status': 'REPAIR_CANDIDATE_PENDING_FRESH_EXTRACTED_CHECK',
        'created_utc': utc(),
        'scope': 'CPU executable identity enforcement and generated W2 command repair; arithmetic unchanged.',
        'historical_batch_status': 'TIMEBOX_ENDED_PARTIAL',
        'historical_summary': 'evidence/historical-offline-summary.json',
        'historical_root_status': 'work/revd_offline_20261017/ROOT_FINAL.json',
        'historical_evidence_note': 'Archived full36/full-size CPU reports belong to their original source inventories. Fresh repaired gate/consumer acceptance is recorded outside this immutable package after extraction.',
        'official_contest_acceptance': False,
        'known_formal_gaps': plan['known_formal_gaps'],
        'selected_profile': plan['selected_profile'],
        'current_delivery_source_sha256': {
            name: sha(ROOT / name) for name in plan['files']
            if name.startswith(('scripts/', 'rtl/', 'soc/', 'sw/', 'dv/', 'numeric/', 'tests/'))
        },
    }
    put(WORK / 'package_summary.json', summary)
    plan['copies'] = [
        {'source': 'work/revd_repair_20261017/package_summary.json', 'destination': 'SUMMARY.json'},
        {'source': 'work/revd_offline_20261017/closure_drafts/package-summary-frozen.json',
         'destination': 'evidence/historical-offline-summary.json'},
    ]
    put(WORK / 'package_plan.json', plan)
    packager.NAME = 'kwt_revd_v2_repaired_20261017'
    stage = packager.build(WORK / 'package_plan.json')
    state = {'status': 'BUILT_PENDING_CHECK', 'created_utc': utc(),
             'stage': stage.relative_to(ROOT).as_posix(),
             'manifest_sha256': sha(stage / 'MANIFEST.json'),
             'plan_sha256': sha(WORK / 'package_plan.json')}
    put(STATE, state)
    print(json.dumps(state), flush=True)


def check():
    from scripts import revd_offline_package_check as checker
    state = read_json(STATE)
    base = ROOT / 'work/revd_offline_20261017/package_checks'
    before = set(base.glob('*/result.json'))
    sys.argv = [str(Path(checker.__file__)), '--stage', state['stage'], '--cpu']
    code = checker.main()
    found = set(base.glob('*/result.json')) - before
    if len(found) != 1:
        raise ValueError('new package-check receipt cardinality')
    receipt = found.pop()
    state.update(status='ROUNDTRIP_PASS' if code == 0 else 'ROUNDTRIP_FAIL',
                 roundtrip_report=receipt.relative_to(ROOT).as_posix(),
                 roundtrip_report_sha256=sha(receipt), checked_utc=utc())
    put(STATE, state)
    if code:
        raise RuntimeError('fresh extracted portable/CPU check failed')


def w2():
    state = read_json(STATE)
    proof = read_json(ROOT / state['roundtrip_report'])
    if proof['status'] != 'PASS' or sha(ROOT / state['roundtrip_report']) != state['roundtrip_report_sha256']:
        raise ValueError('roundtrip proof is not current')
    package = ROOT / proof['extraction']
    base = package / 'reports/revd_offline/soc'
    before = set(base.glob('*/result.json'))
    log = WORK / ('w2-actual-' + run_id() + '.log')
    record = common.command([sys.executable, '-B', 'scripts/revd_offline_soc_w2_run.py', '--stage', 'small'],
                            log, timeout=700, cwd=package, env={'PYTHONPATH': ''})
    found = set(base.glob('*/result.json')) - before
    if record['exit_code'] or len(found) != 1:
        raise ValueError('documented W2 actual command failed or receipt cardinality')
    path = found.pop()
    report = read_json(path)
    if report['status'] != 'PASS' or not report['source_unchanged']:
        raise ValueError('W2 did not finish with unchanged source')
    for name, digest in report['source_sha256'].items():
        if sha(package / name) != digest:
            raise ValueError('W2 source mismatch ' + name)
    for name, digest in report['artifacts_sha256'].items():
        if sha(path.parent / name) != digest:
            raise ValueError('W2 artifact mismatch ' + name)
    binary = Path(report['results']['cpu']['command']['argv'][0])
    if sha(binary) != report['actual_simulator_executable_sha256']:
        raise ValueError('W2 simulator identity changed')
    if sha(path.parent / 'revd-w2-driver.bin') != report['firmware_binary_sha256']:
        raise ValueError('W2 firmware identity changed')
    # Independently compare every public SRAM result and flag to the frozen integer model.
    import numpy as np
    from numeric.fixedpoint import ffn1_reference
    oracle_sources = {}
    for name in ('numeric/__init__.py', 'numeric/fixedpoint.py'):
        digest = sha(ROOT / name)
        if sha(package / name) != digest:
            raise ValueError('root/extracted numeric oracle source differs ' + name)
        oracle_sources[name] = digest
    frozen = read_json(package / 'reports/prototype/vectors/manifest.json')
    wanted = {}
    for task, case in enumerate(report['cases']):
        source = next(c for c in frozen['cases'] if c['case_id'] == case['case_id'])
        arrays = {}
        for key in ('Xq', 'Wq', 'bq'):
            item = source['arrays'][key]
            data = package / 'reports/prototype/vectors' / item['path']
            if sha(data) != item['sha256']:
                raise ValueError('W2 frozen input identity')
            arrays[key] = np.load(data, allow_pickle=False)
        ref = ffn1_reference(arrays['Xq'][:3], arrays['Wq'][:, :32], arrays['bq'][:32], case['shift'])
        for row in range(3):
            for col in range(32):
                wanted[(task, row * 32 + col)] = (
                    int(ref.output[row, col]) & 0xffffffff,
                    int(ref.overflow[row, col]) | (int(ref.output_saturated[row, col]) << 1)
                    | (4 if row == 2 and col == 31 else 0))
    for field, name in enumerate(('cpu-output.txt', 'cpu-flags.txt')):
        actual = {}
        for line in (path.parent / 'cpu' / name).read_text().splitlines():
            task, index, value = line.split()
            key = (int(task), int(index))
            if key in actual:
                raise ValueError('duplicate public W2 write')
            actual[key] = int(value, 16)
        if actual != {key: pair[field] for key, pair in wanted.items()}:
            raise ValueError('independent W2 value/flag comparison failed')
    state.update(status='ROUNDTRIP_AND_W2_PASS', w2_report=path.relative_to(ROOT).as_posix(),
                 w2_report_sha256=sha(path), w2_command=record, w2_independent_output_words=len(wanted),
                 w2_independent_flag_words=len(wanted), w2_independent_oracle_sha256=oracle_sources)
    put(STATE, state)
    print('FRESH_W2_AND_INDEPENDENT_READBACK_PASS', len(wanted), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('phase', choices=['build', 'check', 'w2'])
    args = parser.parse_args()
    {'build': build, 'check': check, 'w2': w2}[args.phase]()
