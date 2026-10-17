"""Assemble explicit closure inputs and inventory; never self-approve evidence."""
from pathlib import Path
import json
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc

WORK = ROOT / 'work/revd_offline_20261017'


def main():
    config = read_json(WORK / 'closure_inputs_draft.json')
    config['status'] = 'LOCAL_CANDIDATE_SOURCE_FROZEN_EXTERNAL_ARCHIVE_ATTESTATION_PENDING'
    ev = config['evidence']
    ev.update({
        'pm2_full36': 'reports/revd_offline/core/pm2-toolbound-20261017T075744Z_38842fbf/summary.json',
        'pm2_tool_binding': 'reports/revd_offline/tool_bound_validation/20261017T075744Z_38842fbf/result.json',
        'cpu_pm2': 'reports/revd_offline/soc/soc-full-pm2-20261017T074930Z/result.json',
        'cpu_pm_comparison': 'reports/revd_offline/soc/pm-compare-20261017T080146Z_6b04725c/result.json',
        'cpu_current_small': 'reports/revd_offline/soc/soc-current-small-20261017T081500Z/result.json',
        'cpu_current_small_gate': 'work/revd_offline_20261017/cpu_current_small_gate_0817.json',
        'W1_full36': 'reports/revd_offline/tiled/w1-full36-pm4-l1-001/summary.json',
        'W2_full36': 'reports/revd_offline/tiled/w2-full36-pm4-l1-final-001/summary.json',
        'W1_review': 'work/revd_offline_20261017/review_tiled_round2.json',
        'W2_review': 'work/revd_offline_20261017/review_w2_round2.json',
        'W2_soc_review': 'work/revd_offline_20261017/review_soc_w2_round1.json',
        'W2_cpu_small': 'reports/revd_offline/soc/soc-w2-small-20261017T080450Z/result.json',
        'W2_cpu_full': 'reports/revd_offline/soc/soc-w2-full-20261017T080700Z/result.json',
        'W2_cpu_edges': 'reports/revd_offline/soc/soc-w2-edges-20261017T081514Z_ed425203/result.json',
        'W2_cpu_comparison': 'reports/revd_offline/soc/w2-comparison-20261017T081511Z_d6770d5e/result.json',
        'soc_final_handoff': 'work/revd_offline_20261017/soc/handoff-20261017T081659Z_82b3c4b3.json',
        'cpu_summary_review': 'work/revd_offline_20261017/review_summary_cpu_round2.json',
        'cpu_command_exit_green': 'reports/revd_offline/review_d3_final/cpu-command-exit-green-20261017T081718Z/summary.json',
        'cpu_command_exit_red': 'reports/revd_offline/review_d3_final/cpu-command-exit-red-20261017T080523Z/summary.json',
    })
    ev = {k: Path(v).as_posix() for k, v in ev.items()}
    config['evidence'] = ev
    config['selection_reason'] = ('Full-W CTX4 PM4 is the reliable default with all36 core cases and public E203/C coverage of all12 frozen layers in six two-task boots. W2 is a separately validated two-full-task Pareto alternative with 7.7882% lower measured CPU cold cycles and smaller logical W capacity; physical timing, area and energy are unknown. Keeping the broader CPU-qualified default is not a claim that it is physically optimal.')
    config['cpu_scope_by_profile'] = {'D2_pm4_l1': 'two matched cold tasks; L1 only',
        'CTX4_pm4_l1': 'all12 frozen layers in six two-task boots; L1 only',
        'CTX4_pm2_l1': 'two full cold tasks; L1 only'}
    config['completed'] += [
        'W1 and W2 PM4/L1 each passed36 core cases/912384 outputs, independent complete-case recompilation, all shifts and lifecycle/mutation coverage.',
        'PM2 real E203 ran two complete cold tasks; measured cold cycles5809223/5809221, slower than PM4 despite fewer generic multipliers.',
        'W2 public E203 ran two complete cold tasks:50688 Y and flags with actual shared-write responses; deferred OPEN1937018 cycles and16542 POPs during pending input prove bounded feed/drain progress.',
        'W2 independent directed CPU fixture covers192 Y/flags and all four flag combinations, with a real wrong-overflow-bit rejection.',
    ]
    config['completed'] = list(dict.fromkeys(config['completed']))
    config['incomplete_or_not_run'] = [
        'Official600/selected12/organizer platform and all designated-process PPA gates remain NOT_RUN.',
        'W1 CPU is NOT_RUN; W2 CPU covers two full tasks, not12; tiled PM2 has directed/protocol evidence, not full36.',
        'Y2 and PM4 XP2 are NOT_RUN; native PM2 two X banks are not an XP2 packing experiment.',
        'Final archive round-trip, independent package review and baseline recheck are external post-publication attestations; see the run SUMMARY/STATUS for final state.',
    ]
    config['negative_results_and_repairs'] += [
        'A real W2 CPU red run rejected future OPEN before START; the authorized thin C variant moves START after tile0 COMMIT and retains one-Y-per-poll fair drain.',
        'CPU evidence gate falsely accepted coherently relabelled nonzero/timeout tool commands; the repaired gate requires all ordinary commands exit0 and exact actual functional-failure exits for the two declared small negative controls. Fresh CPU-small passed the repaired gate.',
    ]
    config['negative_results_and_repairs'] = list(dict.fromkeys(config['negative_results_and_repairs']))
    config['negative_results_and_repairs'] = [
        'Earlier CPU Icarus negative batch was aborted after a normal simulation exceeded the intended later runtime cap; that incomplete failed batch is excluded. Actual Verilator false-success and missing-final-write controls are retained.'
        if line.startswith('Earlier CPU Icarus negative batch') else line
        for line in config['negative_results_and_repairs']]
    config['additional_profiles'] = []
    tc = read_json(ROOT / ev['W1_W2_comparison'])
    for case in tc['cases']:
        for family, idx, weight, bias in [('W1', 0, 2048, 96), ('W2', 1, 4096, 192)]:
            counters = case[family + '_task_counters'][0]
            config['additional_profiles'].append({
                'profile': f'CTX4_PM4_{family}_Y1_X4_L{case["latency"]}', 'new_profile': True,
                'status': 'PASS_LOCAL_FRONTEND', 'scope': 'same synthetic99 public stream and seed; full36 is PM4/L1 only',
                'cold_frontend_cycles': case[family + '_cold_frontend_cycles'],
                'effective_macs': counters['effective_macs'], 'issue': counters['issue'], 'retire': counters['retire'],
                'x_read_ce': sum(row[1] for row in case[family + '_banks']['X']),
                'w_read_ce': sum(row[1] for row in case[family + '_banks']['W']),
                'logical_W_bytes': weight, 'logical_bias_bytes': bias,
                'manifest': case['manifests'][idx], 'area_mm2': None, 'power_W': None,
                'energy_J_per_task': None, 'formal_points': None,
                'real_cpu_scope': 'NOT_RUN_W1_CPU' if family == 'W1' else
                    'NOT_RUN_CPU_L2' if case['latency'] == 2 else 'two full cold tasks; L1 only, not12',
            })
    # The counter is START inclusive whereas the timestamp window is elapsed.
    # Read the actual recorded timestamps rather than infer that edge convention.
    for profile in config['additional_profiles']:
        manifest = read_json(ROOT / profile['manifest']['path'])
        windows = manifest.get('cold_windows')
        if windows:
            profile['start_to_last_output_cycles'] = windows[0]['core_elapsed_cycles']
        else:
            profile.pop('start_to_last_output_cycles', None)
    config['reviews'].update(W1=ev['W1_review'], W2=ev['W2_review'], W2_soc=ev['W2_soc_review'])
    config['requirement_updates']['REPRODUCIBLE_PROJECT'] = {
        'local_status': 'PACKAGE_SOURCE_AND_RECIPE_COMPLETE;_ACTUAL_ARCHIVE_PROOF_EXTERNAL',
        'evidence_keys': ['verification_review'],
    }
    sources = []
    for base in ('rtl/revd_opt', 'dv/revd_opt', 'soc/revd_opt', 'sw/revd_opt', 'config/revd_opt'):
        sources += [p.relative_to(ROOT).as_posix() for p in (ROOT/base).rglob('*') if p.is_file() and p.suffix in ('.py', '.sv', '.c', '.h', '.json') and '__pycache__' not in p.parts]
    sources += [p.relative_to(ROOT).as_posix() for p in (ROOT/'scripts').glob('revd_offline_*.py')]
    sources += ['scripts/package_revd_candidate.py', 'scripts/run_revd_offline.sh']
    config['source_files'] = sorted(set(config['source_files'] + sources))
    put(WORK/'closure_inputs_final.json', config)

    plan = read_json(WORK/'package_plan_preflight.json')
    plan['files'] = sorted(set(plan['files'] + sources + list(ev.values())))
    # Full selected scope, finite candidate results, actual CPU sources and logs.
    trees = {'reports/prototype/vectors', 'reports/model/baseline'}
    direct_tree_keys = ['selected_full36', 'pm2_full36', 'protocol', 'numeric', 'frontend_comparison',
        'cpu_first_two', 'cpu_fake_done_negatives', 'adapter_mutations', 'cross_simulator_repeat',
        'precision', 'conversion', 'generic_structure', 'final_selected_regression',
        'protocol_numeric_tool_binding', 'comparison_tool_binding', 'precision_conversion_tool_binding',
        'cpu_flag_edges', 'cpu_current_small', 'cpu_pm2', 'pm2_tool_binding',
        'W1_full36', 'W2_full36', 'W2_cpu_small', 'W2_cpu_full', 'W2_cpu_edges', 'tiled_generic_structure']
    trees.update(str(Path(ev[key]).parent).replace('\\', '/') for key in direct_tree_keys)
    cpu_suite = read_json(ROOT/ev['cpu_twelve'])
    # Suite producers retain either a list or dict of report records.
    for p in (ROOT/'reports/revd_offline/soc').glob('soc-layers*/result.json'):
        if read_json(p).get('status') == 'PASS':
            trees.add(p.parent.relative_to(ROOT).as_posix())
    for family, key in [('W1', 'W1_handoff'), ('W2', 'W2_handoff')]:
        handoff = read_json(ROOT/ev[key])
        for item in handoff['evidence']:
            name = item['summary']
            if any(token in item['run_id'] for token in ('production-', 'repeat-')):
                trees.add(str(Path(name).parent).replace('\\', '/'))
            else:
                # Keep alternative coverage receipts without duplicating every
                # historical protocol binary. The sources/entrypoints are shipped.
                plan['files'].append(name)
    plan['trees'] = sorted(trees)
    plan['review_files'] = sorted(p.relative_to(ROOT).as_posix() for p in WORK.glob('review_*round*.json'))
    plan['known_formal_gaps'] = config['formal_gaps']
    plan['evidence'] = ev
    plan['copies'] = [
        {'source': 'work/revd_offline_20261017/closure_drafts/package-summary-frozen.json', 'destination': 'SUMMARY.json'},
    ]
    plan['files'] = sorted(set(plan['files']))
    put(WORK/'package_plan_final.json', plan)
    inventory = set(plan['files'])
    for name in plan['trees']:
        for p in (ROOT/name).rglob('*'):
            if not p.is_file() or '__pycache__' in p.parts or p.suffix in ('.pyc', '.pyo', '.vcd', '.fst'):
                continue
            if 'obj' in p.relative_to(ROOT/name).parts and p.name not in ('Vsoc_cpu_tb', 'Vcore_tb'):
                continue
            inventory.add(p.relative_to(ROOT).as_posix())
    missing = [name for name in inventory if not (ROOT/name).is_file()]
    if missing:
        raise ValueError('unresolved explicit package dependency ' + repr(missing))
    put(WORK/'package_plan_inventory.json', {'created_utc': utc(), 'explicit_files_before_vendor_and_generated': len(inventory),
        'bytes': sum((ROOT/name).stat().st_size for name in inventory), 'plan_sha256': sha(WORK/'package_plan_final.json'),
        'alternative_scope_note': 'All four PM4/PM2/full-W/W1/W2 full36 results shipped; repeated alternative protocol binaries are summarized, with tested source and runnable entrypoints retained. No claim all original archival command paths are portable.'})
    print('Closure inputs and package plan assembled; no acceptance decision made.', len(inventory), flush=True)


if __name__ == '__main__':
    main()
