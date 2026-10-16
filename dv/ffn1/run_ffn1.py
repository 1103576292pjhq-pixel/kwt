"""Real Icarus public-port FFN1 regression; no cocotb per-cycle overhead."""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import hashlib
import fcntl
import json
import os
from pathlib import Path
import re
import subprocess
import sys

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from numeric.artifacts import load_array, validate_case_coverage, verify_vectors

REPORT = ROOT / 'reports/prototype/ffn1'
VECTORS = ROOT / 'reports/prototype/vectors'
SOURCES = [ROOT / 'rtl/prototype_sync_ram.sv', ROOT / 'rtl/ffn1_top.sv', ROOT / 'rtl/dot64.sv']
TB = ROOT / 'dv/ffn1/tb_ffn1.sv'
SEED = 0x20261015


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_suffix('.tmp')
    temp.write_text(json.dumps(value, indent=2, allow_nan=False) + '\n', encoding='utf-8')
    temp.replace(path)


def fingerprints():
    paths = [*SOURCES, TB, Path(__file__), ROOT / 'numeric/fixedpoint.py',
             ROOT / 'numeric/artifacts.py', ROOT / 'config/prototype-numeric.json', VECTORS / 'manifest.json']
    if (ROOT / 'rtl/round_sat.sv').exists():
        paths.append(ROOT / 'rtl/round_sat.sv')
    return {str(p.relative_to(ROOT)): digest(p) for p in paths}


def compile_tb(folder, m, n):
    folder.mkdir(parents=True, exist_ok=True)
    # round_sat may be a separate module or embedded by the DOT64 owner.
    sources = list(SOURCES)
    if (ROOT / 'rtl/round_sat.sv').exists():
        sources.append(ROOT / 'rtl/round_sat.sv')
    command = ['/usr/bin/iverilog', '-g2012', '-s', 'tb_ffn1', f'-Ptb_ffn1.M={m}',
               f'-Ptb_ffn1.N={n}', '-o', str(folder / 'sim.vvp'), *map(str, sources), str(TB)]
    with (folder / 'compile.log').open('w') as log:
        subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)


def simulate(folder, arguments):
    command = ['/usr/bin/vvp', str(folder / 'sim.vvp'), *arguments]
    print('RUN ' + ' '.join(command), flush=True)
    with (folder / 'run.log').open('w') as log:
        process = subprocess.Popen(command, cwd=folder, stdout=log, stderr=subprocess.STDOUT)
        write_json(folder / 'process.json', {'pid': process.pid, 'command': command, 'status': 'RUNNING'})
        try:
            code = process.wait(timeout=7200)
        except BaseException:
            process.kill()
            process.wait()
            write_json(folder / 'process.json', {'pid': process.pid, 'status': 'FAIL', 'exit_code': -1})
            raise
    write_json(folder / 'process.json', {'pid': process.pid, 'status': 'EXITED', 'exit_code': code})
    if code:
        raise RuntimeError(f'vvp exit={code}: {(folder / "run.log").read_text()[-5000:]}')
    return (folder / 'run.log').read_text()


def hexfile(path, values, bits):
    mask = (1 << bits) - 1
    path.write_text(''.join(f'{int(v)&mask:0{(bits+3)//4}x}\n' for v in values.flat), encoding='ascii')


def read_vectors(case):
    shapes = {'Xq': ((99,64),'int16'), 'Wq_packed': ((256,64),'int16'),
              'bq': ((256,),'int64'), 'Yq': ((99,256),'int32'),
              'overflow': ((99,256),'bool'), 'output_saturated': ((99,256),'bool')}
    return {name: load_array(VECTORS, case['arrays'][name], *shape_type)
            for name, shape_type in shapes.items()}


def verify_results(cases, folder, text):
    records = []
    for index, case in enumerate(cases):
        arrays = read_vectors(case)
        output = folder / f'{index:02d}' / 'actual.hex'
        lines = output.read_text(encoding='ascii').splitlines()
        if len(lines) != 25344 or any(not re.fullmatch('[0-3][0-9a-f]{8}', x) for x in lines):
            raise ValueError(f'{case["case_id"]}: missing, unknown, or invalid output')
        raw = np.array([int(x,16) for x in lines], dtype=np.uint64).reshape(99,256)
        values = (raw & 0xffffffff).astype('<u4').view('<i4')
        ov = ((raw >> 32) & 1).astype(bool)
        sat = ((raw >> 33) & 1).astype(bool)
        if not (np.array_equal(values, arrays['Yq']) and np.array_equal(ov, arrays['overflow'])
                and np.array_equal(sat, arrays['output_saturated'])):
            raise ValueError(f'{case["case_id"]}: RTL/reference mismatch')
        pattern = (rf'CASE_PASS {re.escape(case["case_id"])} outputs=25344 load=(\d+) '
                   r'compute=(\d+) wait=(\d+) read=(\d+) macs=1622016')
        match = re.findall(pattern, text)
        if len(match) != 1:
            raise ValueError(f'{case["case_id"]}: missing/duplicate cycle evidence')
        records.append({'case_id': case['case_id'], 'layer': case['layer'], 'sample_id': case['sample_id'],
                        'outputs': 25344, 'macs': 1622016, 'mismatches': 0,
                        'output_sha256': hashlib.sha256(values.tobytes()).hexdigest(),
                        'file': str(output.relative_to(ROOT)), 'file_sha256': digest(output),
                        'cycles': dict(zip(['load','compute','row_wait','readback'], map(int,match[0]))),
                        'overflow_count': int(ov.sum()), 'saturated_count': int(sat.sum())})
    if text.count('CASE_PASS ') != len(cases) or f'ALL_PASS cases={len(cases)}\n' not in text:
        raise ValueError('missing or extra completion evidence')
    return records


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mode', choices=['protocol','full','repeat'], default='full')
    args = parser.parse_args()
    REPORT.mkdir(parents=True, exist_ok=True)
    lock = (REPORT / 'simulation.lock').open('w')
    try:
        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        raise RuntimeError('FFN1 simulation already running; inspect process.json/run.log')
    folder = REPORT / args.mode
    folder.mkdir(parents=True, exist_ok=True)
    status = folder / 'status.json'
    write_json(status, {'status': 'RUNNING', 'started_utc': datetime.now(timezone.utc).isoformat()})
    try:
        if args.mode == 'protocol':
            before = fingerprints()
            compile_tb(folder, 3, 4)
            text = simulate(folder, ['+trace=1'])
            if 'PROTOCOL_PASS M=3 N=4' not in text or not (folder / 'protocol.vcd').is_file():
                raise ValueError('protocol evidence missing')
            if before != fingerprints():
                raise ValueError('sources changed during protocol regression')
            result = {'status': 'PASS', 'mode': 'protocol', 'm': 3, 'n': 4, 'fingerprints':before,
                      'log_sha256': digest(folder/'run.log'), 'wave_sha256': digest(folder/'protocol.vcd')}
        else:
            for handoff in ['numeric', 'dot64']:
                if json.loads((ROOT / f'work/{handoff}_handoff.json').read_text())['status'] != 'PASS':
                    raise ValueError(f'{handoff} handoff not PASS')
            verified = verify_vectors(ROOT, ROOT / 'reports/model/baseline', VECTORS)
            if verified['case_count'] != 36 or verified['output_count'] != 912384:
                raise ValueError('complete vector provenance validation failed')
            manifest = json.loads((VECTORS/'manifest.json').read_text())
            if manifest['status'] != 'PASS':
                raise ValueError('unverified manifest')
            validate_case_coverage(manifest['cases'])
            cases = manifest['cases'] if args.mode == 'full' else manifest['cases'][:1]
            before = fingerprints()
            jobs = [str(len(cases))]
            for index, case in enumerate(cases):
                target = folder / f'{index:02d}'
                target.mkdir(exist_ok=True)
                arrays = read_vectors(case)
                for name,bits in [('Xq',16),('Wq_packed',16),('bq',48)]:
                    hexfile(target/f'{name}.hex', arrays[name], bits)
                expected = (arrays['Yq'].astype(np.int64)&0xffffffff).astype(np.uint64)
                expected |= arrays['overflow'].astype(np.uint64)<<32
                expected |= arrays['output_saturated'].astype(np.uint64)<<33
                hexfile(target/'expected.hex', expected, 34)
                jobs.append(' '.join([case['case_id'],str(case['config']['output_shift']),
                    *[str((target/f'{x}.hex').relative_to(folder)) for x in ['Xq','Wq_packed','bq','expected','actual']]]))
            jobfile = folder / 'jobs.txt'
            jobfile.write_text('\n'.join(jobs)+'\n', encoding='utf-8')
            compile_tb(folder, 99, 256)
            # Icarus plusarg strings corrupt non-ASCII bytes; all runtime paths
            # are ASCII relative to the vvp cwd, including under Unicode roots.
            text = simulate(folder, ['+jobs=jobs.txt'])
            records = verify_results(cases, folder, text)
            if before != fingerprints():
                raise ValueError('sources/config/vectors changed during regression')
            if args.mode == 'repeat':
                full = json.loads((REPORT/'full/status.json').read_text())
                if full['status']!='PASS' or full['fingerprints']!=before:
                    raise ValueError('full evidence stale/missing')
                if records[0]['output_sha256'] != full['cases'][0]['output_sha256']:
                    raise ValueError('independent full-size repeat hash mismatch')
            result = {'status':'PASS','mode':args.mode,'case_count':len(records),
                      'full_matrix_cases':len(records),'output_count':len(records)*25344,
                      'actual_macs':len(records)*1622016,'cases':records,'seed':SEED,
                      'fingerprints':before,'log_sha256':digest(folder/'run.log'), 'rtl_reference_mismatches':0}
        result['exit_code']=0
        result['completed_utc']=datetime.now(timezone.utc).isoformat()
        write_json(status,result)
        print(f'FFN1 {args.mode} PASS',flush=True)
    except BaseException as error:
        write_json(status,{'status':'FAIL','exit_code':1,'error':str(error)})
        raise


if __name__ == '__main__':
    main()
