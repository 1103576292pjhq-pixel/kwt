"""Twelve-task data binding, continuous simulation wiring and actual-output audit."""
import json
import math
from pathlib import Path
import re
import struct
from single_tools import sha,save,hex_words,sign_extend,prepare_wiring as single_wiring,once


def prepare_suite(fixtures,out,identity):
    fixtures,out=Path(fixtures),Path(out)
    if sha(fixtures/'manifest.json')!=identity['manifest_sha256']:raise ValueError('Fixture manifest changed')
    manifest=json.loads((fixtures/'manifest.json').read_text())
    if len(manifest['tasks'])!=12 or len(identity['files'])!=60:raise ValueError('Expected twelve complete fixtures')
    for name,want in identity['files'].items():
        if sha(fixtures/name)!=want or manifest['files_sha256'][name]!=want:raise ValueError('Changed fixture: '+name)
    data=[]
    for case in range(1,13):
        sample=manifest['tasks'][case-1]
        if sample['split']!='validation' or sample['layer']!=case:raise ValueError('Layer/split mismatch')
        x=[sign_extend(v) for v in hex_words(fixtures/('case%d-x.hex'%case),6336,16)]
        columns=hex_words(fixtures/('case%d-w.hex'%case),16384,16)
        w=[sign_extend(columns[c*64+k]) for k in range(64) for c in range(256)]
        b=hex_words(fixtures/('case%d-b.hex'%case),256,32)
        gold=hex_words(fixtures/('case%d-y.hex'%case),25344,32)
        if any(v>>19 for v in gold):raise ValueError('Reserved result bits')
        raw=(fixtures/('case%d-ref.f32'%case)).read_bytes()
        if len(raw)!=25344*4 or not all(math.isfinite(v) for v in struct.unpack('<25344f',raw)):raise ValueError('Bad reference')
        data.append(dict(case=case,sample=sample,hardware_layer=case-1,x=x,w=w,b=b,gold=gold))
    out.mkdir(parents=True,exist_ok=False)
    for d in data:
        folder=out/('case%d'%d['case']);folder.mkdir()
        for name in ['x','w','b','gold']:(folder/(name+'.hex')).write_text(''.join('%08x\n'%v for v in d[name]),encoding='ascii')
    return data


def audit_suite(trace,data,fixtures):
    actual={d['case']:{} for d in data}
    for line in Path(trace).read_text().splitlines():
        match=re.fullmatch(r'Y (\d+) (\d+) ([0-9a-fA-F]{8})',line)
        if not match:raise ValueError('Malformed suite result')
        case,index,word=int(match[1]),int(match[2]),int(match[3],16)
        if case not in actual or not 0<=index<25344 or index in actual[case]:raise ValueError('Duplicate/out-of-range suite result')
        actual[case][index]=word
    results=[]
    for d in data:
        case=d['case'];words=actual[case]
        if len(words)!=25344:raise ValueError('Incomplete task '+str(case))
        if any(words[i]!=v for i,v in enumerate(d['gold'])):raise ValueError('Bit mismatch task '+str(case))
        ref=struct.unpack('<25344f',(Path(fixtures)/('case%d-ref.f32'%case)).read_bytes())
        values=[((words[i]&65535)-(65536 if words[i]&32768 else 0))/4096 for i in range(25344)]
        sse=math.fsum((y-r)**2 for y,r in zip(values,ref));energy=math.fsum(r*r for r in ref)
        nrmse=math.sqrt(sse/25344)/max(math.sqrt(energy/25344),1e-8)*100
        if not math.isfinite(nrmse) or nrmse>3:raise ValueError('NRMSE task '+str(case))
        results.append(dict(case=case,hardware_layer=case-1,nrmse_percent=nrmse,outputs=25344,bit_mismatches=0))
    return dict(tasks=len(data),outputs=len(data)*25344,bit_mismatches=0,tasks_audit=results,max_nrmse_percent=max(r['nrmse_percent'] for r in results))


def prepare_wiring(soc,tb):
    soc,tb=single_wiring(soc,tb)
    soc=soc.replace('module kwt_real_soc_top(', 'module kwt_suite_soc_top(')
    tb=tb.replace('kwt_real_soc_top u_e203_soc_top(', 'kwt_suite_soc_top u_e203_soc_top(')
    tb=tb.replace('wire kwt_load_clk = clk;',
        'wire kwt_load_first;\n wire [3:0] kwt_reload_seq;\n wire kwt_load_clk = kwt_load_first ? clk : u_e203_soc_top.kwt_bus_clk;')
    tb=tb.replace('kwt_real_loader u_real_loader(', 'kwt_suite_loader u_suite_loader(')
    tb=tb.replace('.clk(clk), .done(kwt_load_done)', '.clk(kwt_load_clk), .request_seq(kwt_reload_seq), .first(kwt_load_first), .done(kwt_load_done)')
    tb=tb.replace('kwt_real_monitor u_real_monitor(', 'kwt_suite_monitor u_suite_monitor(\n .reload_seq(kwt_reload_seq),')
    tb=once(tb,r'#160000000\b','#1600000000')
    return soc,tb
