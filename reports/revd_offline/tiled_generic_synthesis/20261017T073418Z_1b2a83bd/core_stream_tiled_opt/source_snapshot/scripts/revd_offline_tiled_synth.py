"""Coarse W1/W2 structural and storage proxies; no mapped PPA claims."""
from pathlib import Path
import sys
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import command, put, sha, read_json, run_id, utc
from scripts.revd_offline_generic_ledger import number


def main():
    out = ROOT / 'reports/revd_offline/tiled_generic_synthesis' / run_id()
    out.mkdir(parents=True, exist_ok=False)
    reports = []
    for top in ('core_stream_tiled_opt', 'core_stream_tiled_w2_opt'):
        dest = out / top
        dest.mkdir()
        hdl = [ROOT / 'rtl/revd/banked_sp16.sv', ROOT / 'rtl/revd/quant_epilogue.sv',
               ROOT / 'rtl/revd_opt' / (top + '.sv')]
        sources = [*hdl, Path(__file__), ROOT / 'scripts/revd_offline_common.py',
                   ROOT / 'scripts/revd_offline_generic_ledger.py']
        initial = {str(p.relative_to(ROOT)): sha(p) for p in sources}
        for p in sources:
            snapshot = dest / 'source_snapshot' / p.relative_to(ROOT)
            snapshot.parent.mkdir(parents=True, exist_ok=True)
            snapshot.write_bytes(p.read_bytes())
        script = dest / 'structure.ys'
        script.write_text('read_verilog -sv -DSYNTHESIS ' + ' '.join(map(str, hdl)) + '\n'
            + f'chparam -set PM 4 {top}\nhierarchy -check -top {top}\n'
            + 'proc\nopt\nmemory_collect\nopt_clean\ncheck\n'
            + f'tee -o {dest / "stat.json"} stat -json\nwrite_json {dest / "generic.json"}\n', encoding='utf-8')
        c = command(['yosys', '-Q', '-T', '-s', script], dest / 'yosys.log', timeout=180)
        unchanged = all(sha(ROOT / p) == digest for p, digest in initial.items())
        passed = c['exit_code'] == 0 and 'Found and reported 0 problems.' in (dest / 'yosys.log').read_text()
        rows = []
        stats = None
        if passed:
            net = read_json(dest / 'generic.json')
            tops = [name for name, module in net['modules'].items()
                    if number(module.get('attributes', {}).get('top', 0)) == 1]
            if len(tops) != 1:
                raise ValueError('coarse synthesis has ambiguous top')
            def walk(module, location):
                for name, cell in net['modules'][module].get('cells', {}).items():
                    if cell['type'] in net['modules']:
                        walk(cell['type'], location + '/' + name)
                    elif cell['type'] == '$mem_v2':
                        p = cell['parameters']
                        words, width = number(p['SIZE']), number(p['WIDTH'])
                        rows.append({'hierarchy': location + '/' + name, 'words': words,
                            'width_bits': width, 'bits': words * width,
                            'read_ports': number(p['RD_PORTS']), 'write_ports': number(p['WR_PORTS']),
                            'banked_sp16': 'banked_sp16' in module})
            walk(tops[0], top)
            stats = read_json(dest / 'stat.json')['design']
        reports.append({'profile': top, 'pm': 4, 'status': 'PASS_GENERIC_ONLY' if passed and unchanged else 'FAIL',
            'source_sha256': initial, 'source_unchanged': unchanged, 'command': c,
            'inferred_memories': rows, 'total_inferred_data_bits': sum(row['bits'] for row in rows),
            'banked_sp16_data_bits': sum(row['bits'] for row in rows if row['banked_sp16']),
            'generic_statistics': stats, 'area_mm2': None, 'STA_MHz': None, 'power_W': None,
            'artifact_sha256': {p.name: sha(p) for p in dest.iterdir() if p.is_file()}})
    result = {'status': 'PASS_GENERIC_ONLY' if all(r['status'] == 'PASS_GENERIC_ONLY' for r in reports) else 'PARTIAL',
        'finished_utc': utc(), 'profiles': reports,
        'scope': 'Memory-preserving Yosys coarse RTL only; inferred arrays/multipliers are not a designated macro/cell mapping, timing, area, power, or post-synthesis functional signoff.'}
    put(out / 'summary.json', result)
    print(out, result['status'], flush=True)
    return 0 if result['status'] == 'PASS_GENERIC_ONLY' else 1


if __name__ == '__main__':
    raise SystemExit(main())
