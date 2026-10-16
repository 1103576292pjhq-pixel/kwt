"""Compile behavioral bridge mutants in isolated fixtures, then reject them."""
from pathlib import Path
import hashlib
import json
import subprocess

ROOT = Path(__file__).resolve().parents[2]
REPORT = ROOT / 'reports/system/icb/mutations'
BRIDGE = ROOT / 'rtl/ffn1_icb.sv'
TB = ROOT / 'dv/icb/tb_icb.sv'


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def main():
    REPORT.mkdir(parents=True, exist_ok=True)
    status = REPORT / 'status.json'
    status.write_text('{"status":"RUNNING"}\n')
    source = BRIDGE.read_text()
    originals = [BRIDGE, TB, ROOT / 'rtl/ffn1_top.sv',
                 ROOT / 'rtl/prototype_sync_ram.sv', ROOT / 'rtl/dot64.sv']
    before = {str(path.relative_to(ROOT)): digest(path) for path in originals}
    mutations = [
        ('ignore_delayed_error', "if(command_error)reject(5'b10000);",
         "if(1'b0)reject(5'b10000);", 'rsp_err mismatch'),
        ('response_changes_while_stalled', 'case(state)',
         'if(state==RESPONSE && !icb_rsp_ready) icb_rsp_rdata<=icb_rsp_rdata+1;\n     case(state)',
         'response unstable under backpressure'),
        ('ignore_fresh_halves', "else if(!fresh_lo || (kind_reg==2 && !fresh_hi))reject(5'b01000);",
         "else if(1'b0)reject(5'b01000);", 'reg 0000000c'),
        ('stale_row_data', 'respond(row_rd_data);', 'respond(0);', 'matrix mismatch'),
    ]
    records = []
    try:
        for name, old, new, assertion in mutations:
            if source.count(old) != 1:
                raise ValueError(f'{name}: mutation anchor not unique')
            folder = REPORT / name
            folder.mkdir(exist_ok=True)
            fixture = folder / 'ffn1_icb.sv'
            fixture.write_text(source.replace(old, new), encoding='utf-8')
            command = ['/usr/bin/iverilog', '-g2012', '-s', 'tb_icb',
                       '-Ptb_icb.M=3', '-Ptb_icb.N=4', '-o', str(folder / 'sim.vvp'),
                       str(fixture), *map(str, originals[2:]), str(TB)]
            simulation = ['/usr/bin/vvp', str(folder / 'sim.vvp')]
            (folder / 'commands.json').write_text(json.dumps(
                {'compile': command, 'simulation': simulation}, indent=2) + '\n')
            with (folder / 'compile.log').open('w') as log:
                compiled = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT)
            if compiled.returncode != 0:
                raise ValueError(f'{name}: mutant must compile successfully')
            with (folder / 'run.log').open('w') as log:
                executed = subprocess.run(simulation, cwd=folder, stdout=log,
                                          stderr=subprocess.STDOUT, timeout=120)
            text = (folder / 'run.log').read_text()
            if executed.returncode == 0 or assertion not in text:
                raise ValueError(f'{name}: mutant not rejected by intended behavior assertion: {text[-2000:]}')
            records.append({'name': name, 'compile_exit_code': 0,
                            'simulation_exit_code': executed.returncode,
                            'assertion': assertion,
                            'fixture_sha256': digest(fixture),
                            'log_sha256': digest(folder / 'run.log')})
        if before != {str(path.relative_to(ROOT)): digest(path) for path in originals}:
            raise ValueError('production sources changed during mutation checks')
        result = {'status': 'PASS', 'mutants_rejected': len(records), 'cases': records,
                  'production_fingerprints': before,
                  'scope': 'Compiled behavioral mutants only; production RTL was never edited.'}
        status.write_text(json.dumps(result, indent=2) + '\n')
        print(f'ICB mutations PASS: {len(records)}/{len(mutations)} behavioral mutants rejected')
    except BaseException as error:
        status.write_text(json.dumps({'status': 'FAIL', 'error': str(error)}, indent=2) + '\n')
        raise


if __name__ == '__main__':
    main()
