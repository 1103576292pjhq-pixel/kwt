"""Build a traceable local handoff; external contest gates stay unresolved."""
from __future__ import annotations
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc


def reference(name):
    path = ROOT / name
    if not path.is_file():
        raise ValueError('missing evidence ' + name)
    return {'path': Path(name).as_posix(), 'sha256': sha(path), 'bytes': path.stat().st_size}


def build(config):
    evidence = {key: reference(name) for key, name in config['evidence'].items()}
    comparison = read_json(ROOT / config['evidence']['frontend_comparison'])
    if comparison['status'] != 'PASS':
        raise ValueError('comparison has not passed')
    profiles = []
    for case in comparison['cases']:
        receipt = read_json(ROOT / case['manifest'])
        if receipt['status'] != 'PASS':
            raise ValueError('comparison case not passed')
        profiles.append({
            'profile': case['profile'], 'new_profile': case['new_profile'],
            'status': 'PASS_LOCAL_FRONTEND', 'scope': 'same synthetic99 input/public stream/seed',
            'cold_frontend_cycles': case['cold_windows'][0]['frontend_elapsed_cycles'],
            'start_to_last_output_cycles': case['cold_windows'][0]['core_elapsed_cycles'],
            'effective_macs': case['counters']['effective_macs'],
            'issue': case['counters']['issue'], 'retire': case['counters']['retire'],
            'x_read_ce': sum(row[1] for row in case['actual_banks']['X']),
            'w_read_ce': sum(row[1] for row in case['actual_banks']['W']),
            'logical_W_bytes': 32768, 'logical_bias_bytes': 1536,
            'manifest': reference(case['manifest']), 'area_mm2': None, 'power_W': None,
            'energy_J_per_task': None, 'formal_points': None,
            'real_cpu_scope': config.get('cpu_scope_by_profile', {}).get(case['profile'], 'NOT_RUN_FOR_THIS_PROFILE'),
        })
    profiles.extend(config.get('additional_profiles', []))
    source_names = sorted(set(config['source_files']))
    source_hashes = {name: sha(ROOT / name) for name in source_names}
    inventory = read_json(ROOT / 'work/revd_offline_20261017/submission_matrix.json')
    requirements = []
    for requirement in inventory['requirements']:
        item = {key: requirement[key] for key in ('id', 'physical_pages', 'requirement', 'external_dependency')}
        update = config['requirement_updates'].get(item['id'])
        if not update:
            raise ValueError('requirement lacks final disposition ' + item['id'])
        item.update(update)
        for key in item.get('evidence_keys', []):
            if key not in evidence:
                raise ValueError('requirement has unresolved evidence key ' + key)
        requirements.append(item)
    full = read_json(ROOT / config['evidence']['selected_full36'])
    if full['status'] != 'PASS' or len(full['cases']) != 36:
        raise ValueError('selected full36 is incomplete')
    precision = read_json(ROOT / config['evidence']['precision'])
    return {
        'schema_version': 1, 'status': config.get('status', 'LOCAL_EVIDENCE_REVIEW_PENDING'),
        'created_utc': utc(), 'release_id': 'MASTER_RELEASE-KWT-OFFLINE-SCORE-20261017-001',
        'selected_profile': 'D3_CTX4_FULL_PM4_X4_Y1',
        'selection_reason': config.get('selection_reason', 'The full-W PM4 profile is retained as the broadest CPU-validated reliable default; independently validated storage alternatives remain explicit Pareto candidates while physical costs are unresolved.'),
        'parent_accepted': False, 'official_contest_acceptance': False,
        'formal_score': None, 'submission_qualified': False,
        'score_scope': 'Undergraduate requirement/formula audit and local evidence comparison only.',
        'undergraduate_weights': inventory['score']['weights'],
        'formal_gate': inventory['score']['qualification_gate'],
        'score_formulas': inventory['score_formulas'],
        'formal_gaps': config['formal_gaps'], 'requirements': requirements,
        'completed': config['completed'], 'incomplete_or_not_run': config['incomplete_or_not_run'],
        'candidates': profiles,
        'same_condition_frontend_comparisons': comparison['comparisons'],
        'same_condition_real_cpu_comparison': read_json(ROOT / config['evidence']['cpu_comparison']),
        'engineering_precision': {'worst_layer_nrmse': precision['worst_layer_nrmse'],
                                  'scope': precision['scope'], 'formula': precision['formula'],
                                  'formal_precision_points': None},
        'negative_results_and_repairs': config['negative_results_and_repairs'],
        'mutation_testing': config['mutation_testing'],
        'reviews': config['reviews'], 'package': config.get('package'),
        'current_source_sha256': source_hashes, 'evidence': evidence,
        'fixed_numeric_contract': 'signed16 X/W; exact 64-product signed48 accumulation; signed49 bias add -> sat48 -> ties-to-even RNE shift0..47 -> sat32; separate raw-overflow/output-saturated flags.',
        'window_conventions': {'frontend': 'last_output_fire_cycle - first_BEGIN_accept_cycle',
                               'real_cpu': 'last_shared_write_response_cycle - cold_marker_cycle + 1; includes task layer/shift/address descriptors, all X/W/bias loading and CPU/ICB stalls; excludes boot and three global M/N/task-count header reads, host SRAM image installation and audio preprocessing; prototype boundary, not official contest timing'},
        'guardrails': ['No official600 or selected12 substitution.',
                      'No physical area/power/energy/STA inference from generic cells, memory bits, CE or simulation clocks.',
                      'PM2/PM4 and W1/W2 remain Pareto options while physical costs are unknown.',
                      'L1/L2 is a memory-latency sensitivity comparison, not an architecture-version speedup.',
                      'No Git mutation or remote publication.'],
        'summary_builder_sha256': sha(Path(__file__)),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', required=True)
    parser.add_argument('--out', required=True)
    args = parser.parse_args()
    destination = ROOT / args.out
    if destination.exists():
        raise FileExistsError('refuse overwriting handoff evidence')
    result = build(read_json(ROOT / args.config))
    put(destination, result)
    print(destination, result['status'], flush=True)


if __name__ == '__main__':
    main()
