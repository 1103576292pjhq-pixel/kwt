"""Record matched W1/W2 cold-frontend evidence; this is not a SoC/PPA score."""
import argparse
import sys
from pathlib import Path

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import read_json, put, sha, utc


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--run-id', required=True)
    a = p.parse_args()
    out = ROOT / 'reports/revd_offline/tiled' / a.run_id
    out.mkdir(parents=True, exist_ok=False)
    cases = []
    for latency in (1, 2):
        paths = [ROOT / 'reports/revd_offline/tiled' / name / 'synthetic99/run_manifest.json' for name in (
            f'w1-production-pm4-l{latency}-001', f'w2-production-pm4-l{latency}-final-002')]
        runs = [read_json(path) for path in paths]
        for path, r in zip(paths, runs):
            if r['status'] != 'PASS' or any(c['exit_code'] != 0 for c in r['commands']):
                raise ValueError('not an actually passing compile/simulation: ' + str(path))
            for name, digest in r['input_sha256'].items():
                if sha(path.parent / name) != digest:
                    raise ValueError('changed inputs: ' + str(path.parent / name))
            for name in ('output.hex', 'stats.txt'):
                if sha(path.parent / name) != r['output_sha256'][name]:
                    raise ValueError('changed actual RTL outputs: ' + str(path.parent / name))
        x1, x2 = runs
        if any(x1['input_sha256'][n] != x2['input_sha256'][n] for n in ('X.npy', 'W.npy', 'b.npy', 'commands.hex')):
            raise ValueError('unmatched data/public command stream')
        fields = ('M', 'N', 'PM', 'READ_LATENCY', 'shift', 'task', 'layer', 'source_gap', 'sink_seed')
        if any(x1['config'][n] != x2['config'][n] for n in fields) or x1['tools'] != x2['tools']:
            raise ValueError('unmatched interface/stalls/parameters/toolchain')
        if x1['output_sha256']['output.hex'] != x2['output_sha256']['output.hex']:
            raise ValueError('actual Y/flags/task/index/last output differs')
        windows = [r['windows'][0] for r in runs]
        if any(v[4] != v[3] - v[1] for v in windows):
            raise ValueError('invalid cold task timestamps')
        cold1, cold2 = (v[4] for v in windows)
        cases.append({'latency': latency,
                      'manifests': [{'path': str(path.relative_to(ROOT)), 'sha256': sha(path)} for path in paths],
                      'matched_input_sha256': {n: x1['input_sha256'][n] for n in ('X.npy', 'W.npy', 'b.npy', 'commands.hex')},
                      'matched_interface_policy': {n: x1['config'][n] for n in fields},
                      'W1_cold_frontend_cycles': cold1, 'W2_cold_frontend_cycles': cold2,
                      'W2_to_W1_speedup_proxy': cold1 / cold2,
                      'W2_cycle_reduction_fraction': (cold1 - cold2) / cold1,
                      'W1_task_counters': x1['task_counters'], 'W2_task_counters': x2['task_counters'],
                      'W1_banks': x1['banks'], 'W2_banks': x2['banks'],
                      'W2_physical_overlap_trace': x2['w2_counters'],
                      'actual_output_sha256': x1['output_sha256']['output.hex']})
    result = {'status': 'MATCHED_FRONTEND_PROXY_EVIDENCE', 'created_utc': utc(), 'cases': cases,
              'source_sha256': {str(Path(__file__).relative_to(ROOT)): sha(__file__)},
              'window': 'first BEGIN accepted at public core ingress through final output handshake; includes X, W and bias loading, deferred input and finite sink stalls',
              'storage_proxy_bytes': {'W1_weights': 2048, 'W2_weights': 4096, 'full_weights': 32768,
                                      'W1_bias': 96, 'W2_bias': 192, 'full_bias': 1536},
              'interpretation': 'W2 overlaps loads with the other physically separate SP bank set. These frontend measurements do not include a CPU, MMIO or shared-SRAM final write response.',
              'limitations': ['No official competition score or unknown competitor comparison.',
                              'No specified macro area, 150 MHz STA, power or single-task energy acceptance.',
                              'W1 and W2 remain Pareto candidates until system/physical evidence resolves the added W2 storage versus reduced frontend cycles.'],
              'parent_accepted': False, 'official_contest_acceptance': False}
    put(out / 'comparison.json', result)
    print(out / 'comparison.json', result['status'], flush=True)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
