"""Independent root readback of frozen common evidence; no simulator is started."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
OUT = ROOT / 'reports/system/root-readback.json'


def load(path):
    return json.loads(path.read_text(encoding='utf-8'))


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition, reason):
    if not condition:
        raise ValueError(reason)


def hashes(values, base=ROOT):
    require(bool(values), 'empty hash inventory')
    for name, expected in values.items():
        path = base / name
        require(path.resolve().is_relative_to(ROOT.resolve()), 'path outside workspace')
        require(digest(path) == expected, 'stale source/artifact: ' + name)
    return len(values)


def main():
    import numpy as np
    from numeric.artifacts import verify_vectors
    if OUT.exists():
        history = OUT.parent / 'root-readback-history'
        history.mkdir(exist_ok=True)
        (history / (datetime.now(timezone.utc).strftime('%Y%m%d-%H%M%S-%f') + '.json')).write_bytes(OUT.read_bytes())
    result = {'status': 'RUNNING', 'mode': 'EXPLICIT_HISTORICAL_EVIDENCE_REUSE',
              'started_utc': datetime.now(timezone.utc).isoformat(),
              'no_simulation_started': True}
    OUT.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    inventory = {}
    for name, field in [('e203_boot', 'input_sha256'), ('driver', 'hashes'),
                        ('icb', 'source_fingerprints'), ('fp32', 'source_sha256'),
                        ('e203_ffn1', 'input_sha256')]:
        handoff = load(ROOT / f'work/{name}_handoff.json')
        require(handoff['status'] == 'PASS', 'dependency not PASS: ' + name)
        inventory[name] = hashes(handoff[field])
    cpu_handoff = load(ROOT / 'work/e203_ffn1_handoff.json')
    require(cpu_handoff['command'] == 'bash scripts/run_e203_ffn1.sh' and
            cpu_handoff['exit_code'] == 0, 'not the real standard CPU command')
    cpu_path = ROOT / cpu_handoff['report']
    require(digest(cpu_path) == cpu_handoff['result_sha256'], 'CPU report changed')
    cpu = load(cpu_path)
    require(cpu['status'] == 'PASS', 'CPU result not PASS')
    inventory['cpu_artifacts'] = hashes(cpu['artifacts'], cpu_path.parent)
    inventory['icb_reports'] = hashes(load(ROOT / 'work/icb_handoff.json')['report_sha256'])
    vectors = verify_vectors(ROOT, ROOT / 'reports/model/baseline', ROOT / 'reports/prototype/vectors')
    manifest = load(ROOT / 'reports/prototype/vectors/manifest.json')
    records = manifest['cases']

    def expected(record):
        def array(key):
            return np.load(ROOT / 'reports/prototype/vectors' / record['arrays'][key]['path'], allow_pickle=False).reshape(-1)
        y = array('Yq').astype('<i4').view('<u4').astype(np.uint64)
        ov = array('overflow').astype(np.uint64)
        sat = array('output_saturated').astype(np.uint64)
        return y, ov, sat

    full = load(ROOT / 'reports/system/icb/full36/status.json')
    require(full['status'] == 'PASS' and full['exit_code'] == 0 and
            len(full['cases']) == len(records) == 36, 'ICB case coverage')
    require(full['output_count'] == 912384 and full['actual_macs'] == 58392576,
            'ICB totals')
    icb_words = 0
    for observed, case in zip(full['cases'], records):
        require(observed['case_id'] == case['case_id'], 'ICB order/identity')
        path = ROOT / observed['output_file']
        require(digest(path) == observed['output_sha256'], 'ICB actual file stale')
        words = np.array([int(x, 16) for x in path.read_text(encoding='utf-8').splitlines()], dtype=np.uint64)
        y, ov, sat = expected(case)
        packed = y | (ov << 32) | (sat << 33)
        require(words.size == 25344 and np.array_equal(words, packed), 'ICB output/flags differ')
        icb_words += words.size

    y, ov, sat = expected(records[0])
    flags = 4 | ov | (sat << 1)
    commands_path = cpu_path.parent / 'commands.jsonl'
    commands = [json.loads(line) for line in commands_path.read_text(encoding='utf-8').splitlines()]
    executed_binaries = {}
    for mode, folder in [('full', 'full-verilator'), ('repeat', 'repeat-verilator')]:
        data = cpu['results'][mode]
        require(data['status'] == 'PASS' and data['exit_code'] == 0, 'CPU execution failure')
        starts = [entry for entry in commands if entry['name'] == folder and 'command' in entry]
        finishes = [entry for entry in commands if entry['name'] == folder and 'exit_code' in entry]
        require(len(starts) == len(finishes) == 1 and finishes[0]['exit_code'] == 0,
                'CPU commands/execution identity mismatch')
        argv = starts[0]['command']
        # The frozen execution uses GNU stdbuf solely for live log delivery.
        executable_index = 2 if argv[:2] == ['stdbuf', '-oL'] else 0
        binary = Path(argv[executable_index])
        require(binary.resolve().is_relative_to(ROOT.resolve()) and binary.name == 'Vtb_e203_ffn1',
                'unexpected CPU simulation command')
        require(digest(binary) == data['simulator_binary_sha256'], 'CPU executed binary differs')
        require(digest(cpu_path.parent / (folder + '.log')) == finishes[0]['log_sha256'], 'CPU execution log differs')
        executed_binaries[folder] = {'command': starts[0]['command'],
                                     'binary_sha256': data['simulator_binary_sha256'], 'exit_code': 0}
        metrics = data['metrics']
        for key, value in [('outputs', 25344), ('flags', 25344), ('commits', 22976), ('starts', 1), ('acks', 99)]:
            require(metrics[key] == value, 'CPU transaction coverage: ' + key)
        for filename, reference in [('cpu-output.txt', y), ('cpu-flags.txt', flags)]:
            path = cpu_path.parent / folder / filename
            parsed = [line.split() for line in path.read_text(encoding='utf-8').splitlines()]
            require(len(parsed) == 25344, 'CPU truncated output')
            require(all(len(items) == 2 and int(items[0]) == i and int(items[1], 16) == int(reference[i])
                        for i, items in enumerate(parsed)), 'CPU actual indexed output differs')
        log = (cpu_path.parent / (folder + '.log')).read_text(encoding='utf-8')
        require('E203_FFN1_PASS' in log and 'outputs=25344 flags=25344 commits=22976 starts=1 acks=99' in log,
                'CPU log incomplete')
    require(cpu['results']['full']['metrics'] == cpu['results']['repeat']['metrics'], 'CPU repeat counts differ')
    for key in ('red', 'negative_corrupt_expected'):
        require(cpu['results'][key]['status'] == 'EXPECTED_FAIL' and cpu['results'][key]['exit_code'] != 0,
                'CPU negative test not actually failed')
    for top in ('core', 'icb'):
        synth_path = ROOT / f'reports/system/synthesis-{top}/status.json'
        synth = load(synth_path)
        require(synth['status'] == 'PASS' and synth['exit_code'] == 0, 'generic synthesis failed')
        hashes(synth['sources'])
        hashes(synth['artifacts'], synth_path.parent)
    result.update(status='PASS', inventories=inventory, icb_complete_cases=36,
                  icb_outputs_and_both_flags_rechecked=icb_words,
                  cpu_full_output_and_flags_rechecked=25344, cpu_repeat_output_and_flags_rechecked=25344,
                  cpu_metrics=cpu['results']['full']['metrics'], vector_verification=vectors,
                  cpu_executed_binaries=executed_binaries, cpu_commands_sha256=digest(commands_path),
                  cpu_result_sha256=digest(cpu_path), common_review_sha256=digest(ROOT / 'reports/system/review/common-final.md'),
                  completed_utc=datetime.now(timezone.utc).isoformat(),
                  limits=['Explicit frozen historical executions, not a newly run CPU simulation',
                          'Python startup/--help cannot serve as execution proof; this verifier reads all bound evidence',
                          'Generic synthesis only; official contest platform/library/PPA/600 samples pending'])
    OUT.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print('ROOT_COMMON_READBACK_PASS ICB=912384 CPU=25344+25344 with all flags')


if __name__ == '__main__':
    try:
        main()
    except Exception as exc:
        OUT.parent.mkdir(parents=True, exist_ok=True)
        OUT.write_text(json.dumps({'status': 'FAIL', 'error': str(exc)}, indent=2) + '\n', encoding='utf-8')
        raise
