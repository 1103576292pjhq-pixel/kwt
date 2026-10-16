"""Read back the completed local draft; never launch simulation or change its gate."""
from pathlib import Path
import argparse
import csv
import hashlib
import json
import re
import time

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'reports/encoder/verification'


def load(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run-id', required=True)
    args = parser.parse_args()
    unified = load(OUT / 'unified/status.json')
    gate = load(OUT / 'gate.json')
    state = load(ROOT / 'work/encoder_status.json')
    handoff = load(ROOT / 'work/encoder_engine_handoff.json')
    assert unified['status'] == gate['status'] == 'PASS'
    assert unified['run_id'] == gate['run_id'] == args.run_id
    assert unified['started_unix'] <= gate['created_unix'] <= unified['completed_unix']
    assert unified['source_sha256'] == sha(ROOT / 'scripts/run_formal_seven.py')
    assert gate['gate_source_sha256'] == sha(ROOT / 'scripts/formal_seven_gate.py')
    assert state['status'] == handoff['status'] == 'READY_FOR_REVIEW'
    assert all(gate['tasks'][f'task{i}'] is True and state[f'task{i}'] is True for i in range(1, 8))
    assert state['full_encoder_cases'] == handoff['full_encoder_cases'] == len(gate['details']['full_cases']) == 15
    assert not any(gate['errors'].values())
    assert handoff['gate_sha256'] == sha(OUT / 'gate.json')
    assert state['formal_acceptance'].startswith('EXTERNAL_PENDING')

    commands = unified['commands']
    assert len(commands) == len({c['name'] for c in commands}) == 34
    actual = [c for c in commands if c['identity'] == 'ACTUAL_EXECUTION']
    assert {c['name'] for c in actual} == {'gate-tests', 'gate-schema-mutation', 'source-freeze', 'final-evidence-gate', 'render-report'}
    assert len([c for c in commands if c['identity'] == 'EXPLICIT_VERIFIED_HISTORY']) == 29
    for command in actual:
        log = OUT / 'unified' / (command['name'] + '.log')
        assert command['exit_code'] == 0 and command['run_id'] == args.run_id and command['pid'] > 0
        assert unified['started_unix'] <= command['started_unix'] <= command['completed_unix'] <= unified['completed_unix']
        assert log.stat().st_size > 0 and sha(log) == command['log_sha256']
    assert re.search(r'\b51 passed\b', (OUT / 'unified/gate-tests.log').read_text(encoding='utf-8'))
    mutation = load(OUT / 'gate/schema-mutation/status.json')
    assert mutation['status'] == 'PASS' and mutation['mutant_compilation_succeeded']
    assert mutation['behavioral_mutants_killed'] == 1 and len(mutation['corrupt_records']) == 5
    assert all(c['current_rejected'] and c['compiled_mutant_accepted_corrupt_record'] for c in mutation['corrupt_records'])

    freeze = load(ROOT / 'work/encoder_source_freeze.json')
    assert len(freeze['source_sha256']) == 192
    review = load(OUT / 'review.json')
    assert review['status'] == 'PASS' and review['rounds'] >= 2 and review['independent'] is True
    assert review['final_evidence_review_pending'] is False and review['open_p1'] == review['open_p2'] == 0
    for mapping in [freeze['source_sha256'], review['review_sha256'], review['source_sha256'], review['input_sha256'], mutation['source_sha256']]:
        for rel, digest in mapping.items():
            assert sha(ROOT / rel) == digest, rel

    artifact = load(OUT / 'report-artifact.json')
    report = OUT / 'report.md'
    text = report.read_text(encoding='utf-8')
    assert '\ufffd' not in text and 'READY_FOR_REVIEW' in text
    assert artifact['report_sha256'] == sha(report)
    assert artifact['generator_sha256'] == sha(ROOT / 'scripts/encoder_report.py')
    assert artifact['gate_sha256'] == sha(OUT / 'gate.json')
    assert artifact['utf8_readback'] and artifact['all_local_links_exist']
    links = re.findall(r'\]\(([^)]+)\)', text)
    assert all(target.startswith(('http://', 'https://', '#')) or (OUT / target).resolve().is_file() for target in links)
    for name, digest in artifact['derived_sha256'].items():
        assert sha(OUT / name) == digest, name
    with (OUT / 'rtl-layer-results.csv').open(encoding='utf-8', newline='') as handle:
        assert len(list(csv.DictReader(handle))) == 180
    with (OUT / 'rtl-case-results.csv').open(encoding='utf-8', newline='') as handle:
        assert len(list(csv.DictReader(handle))) == 15

    performance = load(OUT / 'performance.json')
    metric = performance['comparison']
    assert len(metric) == 10
    assert metric['end_to_end_cycles']['pingpong'] == 284353480
    assert metric['end_to_end_cycles']['reload'] == 290627429
    assert metric['end_to_end_cycles']['saved'] == 6273949
    assert metric['cpu_shared_transactions']['saved'] == metric['model_shared_transactions']['saved'] == 139392
    cpu = []
    for name, words in [('pingpong', 6336), ('reload', 76032)]:
        r, stats = gate['details']['cpu_' + name]
        assert r['layers'] == 12 and r['neural_words'] == 76032 and r['output_words'] == words
        folder = ROOT / 'reports/encoder/system' / name
        assert sha(folder / 'neural-output.hex') == r['neural_sha256']
        assert sha(folder / 'cpu-output.hex') == r['output_sha256']
        assert len(performance['policies'][name]['layers']) == 12
        cpu.append({'policy': name, 'neural_words': 76032, 'cpu_words': words, 'neural_sha256': r['neural_sha256'], 'end_to_end_cycles': stats['end_to_end_cycles']})
    assert cpu[0]['neural_sha256'] == cpu[1]['neural_sha256']
    rtl_words = 0
    for item in gate['details']['full_cases']:
        path = ROOT / item['record']
        record = load(path)
        assert record['layers'] == 12 and record['output_words'] == 76032
        assert sha(path.parent / 'output.hex') == item['output_sha256'] == record['output_sha256']
        rtl_words += record['output_words']

    result = {'status': 'PASS', 'run_id': args.run_id, 'observed_unix': time.time(),
              'checker_sha256': sha(Path(__file__)), 'unified_sha256': sha(OUT / 'unified/status.json'),
              'gate_sha256': sha(OUT / 'gate.json'), 'report_sha256': sha(report),
              'review_sha256': sha(OUT / 'review.json'), 'source_freeze_sha256': sha(ROOT / 'work/encoder_source_freeze.json'),
              'frozen_sources_checked': 192, 'review_documents': len(review['review_sha256']),
              'review_sources': len(review['source_sha256']), 'review_inputs': len(review['input_sha256']),
              'actual_commands': len(actual), 'typed_history_commands': 29, 'gate_tests': 51,
              'rtl_cases': 15, 'rtl_layers': 180, 'rtl_words': rtl_words,
              'report_links_checked': len(links), 'cpu': cpu,
              'formal_acceptance': state['formal_acceptance'], 'scope': 'Completed local draft evidence readback; no simulation or gate mutation'}
    (OUT / 'final-readback.json').write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    print(json.dumps(result, ensure_ascii=False))


if __name__ == '__main__':
    main()
