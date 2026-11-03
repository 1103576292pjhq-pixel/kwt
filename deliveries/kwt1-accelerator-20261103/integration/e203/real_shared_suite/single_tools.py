"""Portable data identity, layout conversion, simulation wiring and result audit."""
import hashlib
import json
import math
from pathlib import Path
import re
import struct


def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def save(path, value): Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False)+'\n', encoding='utf-8')
def sign_extend(value): return (value | 0xffff0000) if value & 0x8000 else value


def hex_words(path, count, bits):
    lines = Path(path).read_text(encoding='ascii').splitlines()
    if len(lines) != count or any(not re.fullmatch(r'[0-9a-fA-F]{%d}'%(bits//4), x) for x in lines):
        raise ValueError('Invalid hex format/count: '+str(path))
    return [int(line, 16) for line in lines]


def prepare_data(fixtures, out, identity):
    fixtures, out = Path(fixtures), Path(out)
    if sha(fixtures/'manifest.json') != identity['manifest_sha256']:
        raise ValueError('Real-data manifest identity mismatch')
    manifest = json.loads((fixtures/'manifest.json').read_text(encoding='utf-8'))
    sample = manifest['tasks'][2]
    if sample['path'] != 'yes/55feffd5_nohash_0.wav' or sample['layer'] != 3 or sample['split'] != 'validation':
        raise ValueError('Expected real yes recording and layer3')
    for name, digest in identity['files'].items():
        if sha(fixtures/name) != digest or manifest['files_sha256'][name] != digest:
            raise ValueError('Real-data file identity mismatch: '+name)
    x = [sign_extend(v) for v in hex_words(fixtures/'case3-x.hex', 6336, 16)]
    columns = hex_words(fixtures/'case3-w.hex', 16384, 16)
    w = [sign_extend(columns[c*64+k]) for k in range(64) for c in range(256)]
    b = hex_words(fixtures/'case3-b.hex', 256, 32)
    gold = hex_words(fixtures/'case3-y.hex', 25344, 32)
    if any(v >> 19 for v in gold): raise ValueError('Golden has reserved bits')
    ref = (fixtures/'case3-ref.f32').read_bytes()
    if len(ref) != 25344*4 or not all(math.isfinite(v) for v in struct.unpack('<25344f', ref)):
        raise ValueError('Bad floating reference')
    out.mkdir(parents=True, exist_ok=False)
    for name, values in [('x', x), ('w', w), ('b', b), ('gold', gold)]:
        (out/(name+'.hex')).write_text(''.join('%08x\n'%v for v in values), encoding='ascii')
    # Same prepared representation can be loaded by the native C/RTL test.
    (out/'payload.bin').write_bytes(struct.pack('<%dI'%(len(x)+len(w)+len(b)+len(gold)), *(x+w+b+gold)))
    return dict(sample=sample, hardware_layer=2, x=x, w=w, b=b, gold=gold,
                files_sha256={p.name:sha(p) for p in out.iterdir()})


def audit_trace(path, gold, reference):
    seen = {}
    for line in Path(path).read_text(encoding='ascii').splitlines():
        match = re.fullmatch(r'Y (\d+) ([0-9a-fA-F]{8})', line)
        if not match: raise ValueError('Malformed actual shared readback')
        index, word = int(match[1]), int(match[2], 16)
        if index in seen or not 0 <= index < 25344: raise ValueError('Duplicate/out-of-range shared result')
        if word != gold[index]: raise ValueError('Actual shared result differs at %d'%index)
        seen[index] = word
    if len(seen) != 25344: raise ValueError('Incomplete actual shared result readback')
    raw = Path(reference).read_bytes()
    if len(raw) != 25344*4: raise ValueError('Bad reference length')
    ref = struct.unpack('<25344f', raw)
    if not all(math.isfinite(v) for v in ref): raise ValueError('Non-finite reference')
    values = [(seen[i]&65535)-(65536 if seen[i]&32768 else 0) for i in range(25344)]
    sse = math.fsum((v/4096-r)**2 for v,r in zip(values, ref))
    energy = math.fsum(r*r for r in ref)
    ratio = math.sqrt(sse/25344)/max(math.sqrt(energy/25344), 1e-8)
    if ratio > .03: raise ValueError('Actual shared output exceeds 3 percent NRMSE')
    return dict(outputs=25344, bit_mismatches=0, nrmse_percent=ratio*100)


def once(text, pattern, replace):
    matches = list(re.finditer(pattern, text, re.M))
    if len(matches) != 1: raise ValueError('Unrecognized unique wiring anchor: '+pattern)
    match = matches[0]
    return text[:match.start()]+(replace(match) if callable(replace) else replace)+text[match.end():]


PORTS = '''
 input kwt_load_mode, kwt_load_clk, kwt_load_rst_n,
 input kwt_load_cmd_valid, kwt_load_cmd_read, kwt_load_rsp_ready,
 input [31:0] kwt_load_cmd_addr, kwt_load_cmd_wdata,
 input [3:0] kwt_load_cmd_wmask,
 output kwt_load_cmd_ready, kwt_load_rsp_valid, kwt_load_rsp_err,
 output [31:0] kwt_load_rsp_rdata,
'''


def prepare_wiring(soc, tb):
    soc = once(soc, r'\bmodule\s+kwt_shared_soc_top\s*\(', 'module kwt_real_soc_top('+PORTS)
    pattern = r'kwt_shared_sram\s*#\([^;]+?\)\s*u_shared_sram\s*\((.*?)\);'
    def shared(match):
        original = match[0]
        result = original
        replacements = {
            'clk': 'kwt_load_mode ? kwt_load_clk : kwt_bus_clk',
            'rst_n': 'kwt_load_mode ? kwt_load_rst_n : kwt_bus_rst_n',
            'icb_cmd_valid': 'kwt_load_mode ? kwt_load_cmd_valid : sysmem_icb_cmd_valid',
            'icb_cmd_read': 'kwt_load_mode ? kwt_load_cmd_read : sysmem_icb_cmd_read',
            'icb_cmd_addr': 'kwt_load_mode ? kwt_load_cmd_addr : sysmem_icb_cmd_addr',
            'icb_cmd_wdata': 'kwt_load_mode ? kwt_load_cmd_wdata : sysmem_icb_cmd_wdata',
            'icb_cmd_wmask': 'kwt_load_mode ? kwt_load_cmd_wmask : sysmem_icb_cmd_wmask',
            'icb_rsp_ready': 'kwt_load_mode ? kwt_load_rsp_ready : sysmem_icb_rsp_ready',
            'icb_cmd_ready': 'kwt_ram_cmd_ready', 'icb_rsp_valid': 'kwt_ram_rsp_valid',
            'icb_rsp_err': 'kwt_ram_rsp_err', 'icb_rsp_rdata': 'kwt_ram_rsp_rdata'}
        for port, value in replacements.items():
            expected = {'clk':'kwt_bus_clk', 'rst_n':'kwt_bus_rst_n'}.get(port, 'sysmem_'+port)
            result = once(result, r'\.'+port+r'\s*\(\s*'+re.escape(expected)+r'\s*\)', '.'+port+'('+value+')')
        return '''// Simulation-only loader mux. Normal mode retains original CPU/clock/reset.
 wire kwt_ram_cmd_ready, kwt_ram_rsp_valid, kwt_ram_rsp_err;
 wire [31:0] kwt_ram_rsp_rdata;
 assign kwt_load_cmd_ready = kwt_ram_cmd_ready;
 assign kwt_load_rsp_valid = kwt_ram_rsp_valid;
 assign kwt_load_rsp_err = kwt_ram_rsp_err;
 assign kwt_load_rsp_rdata = kwt_ram_rsp_rdata;
 assign sysmem_icb_cmd_ready = !kwt_load_mode && kwt_ram_cmd_ready;
 assign sysmem_icb_rsp_valid = !kwt_load_mode && kwt_ram_rsp_valid;
 assign sysmem_icb_rsp_err = kwt_ram_rsp_err;
 assign sysmem_icb_rsp_rdata = kwt_ram_rsp_rdata;
 '''+result
    matches = list(re.finditer(pattern, soc, re.S))
    if len(matches) != 1: raise ValueError('Expected single existing shared SRAM instance')
    match = matches[0]; soc = soc[:match.start()]+shared(match)+soc[match.end():]
    tb = once(tb, r'\bkwt_shared_soc_top\s+u_e203_soc_top\s*\(',
              'kwt_real_soc_top u_e203_soc_top(\n'+''.join(' .%s(%s),\n'%(v,v) for v in [
                  'kwt_load_mode','kwt_load_clk','kwt_load_rst_n','kwt_load_cmd_valid','kwt_load_cmd_read',
                  'kwt_load_rsp_ready','kwt_load_cmd_addr','kwt_load_cmd_wdata','kwt_load_cmd_wmask',
                  'kwt_load_cmd_ready','kwt_load_rsp_valid','kwt_load_rsp_err','kwt_load_rsp_rdata']))
    tb = once(tb, r'#120\s+rst_n\s*<=\s*1\s*;', 'wait(kwt_load_done); #120 rst_n <=1;')
    tb = once(tb, r'#\s*40000000\b', '#160000000')
    declarations = '''
 wire kwt_load_mode, kwt_load_rst_n, kwt_load_done;
 wire kwt_load_clk = clk;
 wire kwt_load_cmd_valid, kwt_load_cmd_read, kwt_load_rsp_ready;
 wire [31:0] kwt_load_cmd_addr, kwt_load_cmd_wdata;
 wire [3:0] kwt_load_cmd_wmask;
 wire kwt_load_cmd_ready, kwt_load_rsp_valid, kwt_load_rsp_err;
 wire [31:0] kwt_load_rsp_rdata;
 kwt_real_loader u_real_loader(
 .clk(clk), .done(kwt_load_done), .mode(kwt_load_mode), .reset_n(kwt_load_rst_n),
 .cmd_valid(kwt_load_cmd_valid), .cmd_ready(kwt_load_cmd_ready),
 .cmd_addr(kwt_load_cmd_addr), .cmd_read(kwt_load_cmd_read),
 .cmd_wdata(kwt_load_cmd_wdata), .cmd_wmask(kwt_load_cmd_wmask),
 .rsp_valid(kwt_load_rsp_valid), .rsp_ready(kwt_load_rsp_ready),
 .rsp_err(kwt_load_rsp_err), .rsp_rdata(kwt_load_rsp_rdata));
 kwt_real_monitor u_real_monitor(
 .clk(u_e203_soc_top.kwt_bus_clk), .rst_n(u_e203_soc_top.kwt_bus_rst_n),
 .cmd_valid(u_e203_soc_top.sysmem_icb_cmd_valid && !kwt_load_mode),
 .cmd_ready(u_e203_soc_top.sysmem_icb_cmd_ready),
 .cmd_read(u_e203_soc_top.sysmem_icb_cmd_read),
 .cmd_addr(u_e203_soc_top.sysmem_icb_cmd_addr),
 .cmd_data(u_e203_soc_top.sysmem_icb_cmd_wdata),
 .cmd_mask(u_e203_soc_top.sysmem_icb_cmd_wmask),
 .rsp_valid(u_e203_soc_top.sysmem_icb_rsp_valid),
 .rsp_ready(u_e203_soc_top.sysmem_icb_rsp_ready),
 .rsp_err(u_e203_soc_top.sysmem_icb_rsp_err),
 .rsp_data(u_e203_soc_top.sysmem_icb_rsp_rdata));
'''
    tb = once(tb, r'^[ \t]*reg\s+rst_n\s*;', lambda m:m[0]+declarations)
    return soc, tb
