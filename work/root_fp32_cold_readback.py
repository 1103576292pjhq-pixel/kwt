"""Independent fresh-process port checks of frozen FP32 simulator binaries."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / 'reports/system/root-fp32-cold'
CASES = [
    ('zero_div_two', 4, 0, 0x40000000, 0, 0),
    ('negative_zero_div_two', 4, 0x80000000, 0x40000000, 0x80000000, 0),
    ('sqrt_negative_zero', 5, 0x80000000, 0, 0x80000000, 0),
    ('zero_div_zero', 4, 0, 0, 0x7fc00000, 0x10),
    ('one_div_negative_inf', 4, 0x3f800000, 0xff800000, 0x80000000, 0),
    ('signaling_nan_div_one', 4, 0x7f812345, 0x3f800000, 0x7fc00000, 0x10),
    ('integer_minus_two', 6, 0xbfc00000, 0, 0xfffffffe, 1),
    ('exact_add', 0, 0x3f800000, 0x3fc00000, 0x40200000, 0),
]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    base = ROOT / 'reports/encoder/fp32/cold-green'
    binaries = {'icarus': base / 'iverilog/sim.vvp',
                'verilator': base / 'verilator/obj/Vtb_fp32_cold'}
    sources = [ROOT / 'rtl/encoder_fp32.sv', ROOT / 'dv/fp32/tb_fp32_cold.sv']
    hashes = {str(p.relative_to(ROOT)): sha(p) for p in sources}
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    out = REPORT / stamp
    out.mkdir(parents=True)
    result = {'status': 'RUNNING', 'started_utc': stamp, 'sources': hashes,
              'binary_sha256': {s: sha(p) for s, p in binaries.items()},
              'scope': 'root cold port check; every vector is first request in new OS process',
              'new_processes': [], 'warmup_operations': 0}
    try:
        for sim, binary in binaries.items():
            for name, op, a, b, expected, flags in CASES:
                directory = out / (sim + '-' + name)
                directory.mkdir()
                command = (['vvp', str(binary)] if sim == 'icarus' else [str(binary)]) + [
                    f'+OP={op:x}', f'+A={a:08x}', f'+B={b:08x}', '+C=00000000',
                    f'+EXPECTED={expected:08x}', f'+FLAGS={flags:02x}', '+ERROR=0', '+RESULTS=results.hex']
                with (directory / 'simulation.log').open('w', encoding='utf-8') as log:
                    child = subprocess.Popen(command, cwd=directory, stdout=log, stderr=subprocess.STDOUT)
                    code = child.wait(timeout=20)
                text = (directory / 'simulation.log').read_text(encoding='utf-8')
                if code or 'FP32_COLD_PASS accepted_requests=1' not in text:
                    raise ValueError(f'{sim}/{name} failed: exit {code}')
                result['new_processes'].append({'simulator': sim, 'case': name, 'pid': child.pid,
                    'command': command, 'exit_code': code,
                    'log_sha256': sha(directory / 'simulation.log'),
                    'result_sha256': sha(directory / 'results.hex')})
        for path, digest in hashes.items():
            if sha(ROOT / path) != digest:
                raise ValueError('Source changed during root check: ' + path)
        result['status'] = 'PASS'
    except Exception as exc:
        result.update(status='FAIL', error=str(exc))
        raise
    finally:
        result['completed_utc'] = datetime.now(timezone.utc).isoformat()
        (out / 'status.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
        print(json.dumps({'status': result['status'], 'new_processes': len(result['new_processes']),
                          'report': str((out / 'status.json').relative_to(ROOT))}))


if __name__ == '__main__':
    main()
