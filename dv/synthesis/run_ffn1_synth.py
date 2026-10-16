"""Reproducible generic structure/memory check; no technology PPA claim."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def run(top):
    report = ROOT / 'reports/system' / ('synthesis-core' if top == 'ffn1_top' else 'synthesis-icb')
    report.mkdir(parents=True, exist_ok=True)
    previous = report / 'status.json'
    if previous.exists():
        attempt = report / 'attempts' / datetime.now(timezone.utc).strftime('%Y%m%d-%H%M%S-%f')
        attempt.mkdir(parents=True)
        for name in ('status.json', 'stdout.log', 'yosys.log', 'stats.json'):
            path = report / name
            if path.exists():
                shutil.copy2(path, attempt / name)
    sources = ['rtl/prototype_sync_ram.sv', 'rtl/dot64.sv', 'rtl/ffn1_top.sv']
    if top == 'ffn1_icb':
        sources.append('rtl/ffn1_icb.sv')
    hashes = {name: sha(ROOT / name) for name in sources}
    common = {
        'status': 'RUNNING', 'top': top, 'sources': hashes,
        'scope': 'Generic RTL lowering, synchronous memory inference and structural checks.',
        'formal_technology_ppa': 'EXTERNAL_PENDING',
        'no_claims': ['150MHz timing', 'mm2 area', 'power or energy', 'technology mapping', 'gate-level signoff'],
    }
    previous.write_text(json.dumps(common, indent=2) + '\n', encoding='utf-8')
    yosys = shutil.which('yosys')
    if not yosys:
        raise RuntimeError('yosys is required')
    relative = report.relative_to(ROOT).as_posix()
    flow = (f"read_verilog -sv {' '.join(sources)}; hierarchy -check -top {top}; "
            'proc; opt; memory_dff; memory_collect; opt_clean; check -assert; '
            f'tee -o {relative}/stats.json stat -json; '
            f'write_json {relative}/design.json; write_verilog -noattr {relative}/generic.v')
    command = [yosys, '-Q', '-T', '-l', str(report / 'yosys.log'), '-p', flow]
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, encoding='utf-8')
    (report / 'stdout.log').write_text(result.stdout + result.stderr, encoding='utf-8')
    common.update(command=command, exit_code=result.returncode,
                  tool=subprocess.check_output([yosys, '-V'], text=True).strip(),
                  completed_utc=datetime.now(timezone.utc).isoformat())
    error = None
    if result.returncode == 0:
        try:
            design = json.loads((report / 'design.json').read_text(encoding='utf-8'))
            memories = []
            for module, body in design['modules'].items():
                for name, cell in body.get('cells', {}).items():
                    if cell['type'] == '$mem_v2':
                        params = cell['parameters']
                        read_clk = int(params['RD_CLK_ENABLE'], 2)
                        if read_clk == 0:
                            raise ValueError(f'asynchronous memory read: {module}.{name}')
                        memories.append({'module': module, 'name': name,
                                         'width': int(params['WIDTH'], 2),
                                         'words': int(params['SIZE'], 2),
                                         'read_clock_enable': read_clk})
            # X, packed W, bias and the output row are four physical banks.
            dimensions = sorted((mem['width'], mem['words']) for mem in memories)
            expected = sorted(((16, 99 * 64), (16, 256 * 64), (48, 256), (34, 256)))
            if dimensions != expected:
                raise ValueError(f'FFN1 memory geometry differs: {dimensions}, expected {expected}')
            if hashes != {name: sha(ROOT / name) for name in sources}:
                raise ValueError('source changed during synthesis')
            common['memories'] = memories
            common['artifacts'] = {name: sha(report / name) for name in
                                   ('stdout.log', 'yosys.log', 'stats.json', 'design.json', 'generic.v')}
        except (ValueError, KeyError, OSError) as exc:
            error = str(exc)
    common['status'] = 'PASS' if result.returncode == 0 and error is None else 'FAIL'
    if error:
        common['error'] = error
    previous.write_text(json.dumps(common, indent=2) + '\n', encoding='utf-8')
    print(f"{top} generic synthesis {common['status']}")
    return 0 if common['status'] == 'PASS' else 1


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--top', choices=['ffn1_top', 'ffn1_icb', 'both'], default='both')
    args = parser.parse_args()
    tops = ('ffn1_top', 'ffn1_icb') if args.top == 'both' else (args.top,)
    # Sequential runs: each lowering reads shared RTL and produces a complete report.
    failures = [run(top) for top in tops]
    sys.exit(1 if any(failures) else 0)
