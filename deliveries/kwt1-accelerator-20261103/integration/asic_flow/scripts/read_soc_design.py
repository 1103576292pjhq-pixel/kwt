#!/usr/bin/env python3
"""Whole-SoC ASIC analyze/elaborate/link using tested staged TCM adapters.

No compile, no PPA pass. Writes only Desktop/dc; production and peer trees read-only.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

DESKTOP=Path('/storage1/2026contest/server2/s2_21usr/Desktop')
ROOT=DESKTOP/'e203-integration/kwt-soc'
DC=DESKTOP/'dc'
LIBS=['scc40nll_vhsc40_hvt_tt_v1p1_125c_basic',
      'RAMSP1024X16_tt_1p10v_1p10v_125c',
      'RAMSP128X16_tt_1p10v_1p10v_125c',
      'RAMSP4096X16_tt_1p10v_1p10v_125c']

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def clean(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
def need(v,s):
    if not v:raise ValueError(s)
def q(p):
    s=str(p)
    need(not any(c in s for c in '{}\n\r'),'Unsupported Tcl path: '+s)
    return '{'+s+'}'

def explicit_port_nets(body):
    """Declare ANSI port nets explicitly for DC with default_nettype none."""
    old=''' input CLK, input RSTN, input [ADDRWIDTH-1:0] ADDRESS,
 input CS, input WE, input [DATAWIDTH/8-1:0] WEM,
 input [DATAWIDTH-1:0] WDATA, output [DATAWIDTH-1:0] RDATA'''
    new=''' input wire CLK, input wire RSTN, input wire [ADDRWIDTH-1:0] ADDRESS,
 input wire CS, input wire WE, input wire [DATAWIDTH/8-1:0] WEM,
 input wire [DATAWIDTH-1:0] WDATA, output wire [DATAWIDTH-1:0] RDATA'''
    need(body.count(old)==1,'Unexpected tested TCM port declarations; stop instead of broad rewrite')
    return body.replace(old,new,1)

def sources_and_includes(root,adapter):
    sources=[];incdirs=[];excluded=[]
    remove={'GENERIC_LVT_ARM.v','GENERIC_RVT_ARM.v','GENERIC_RVT_SYNOPSYS.v',
            'sram_wrap_32KX64.v','sram_wrap_64KX32.v'}
    for raw in (root/'sources.f').read_text().splitlines():
        line=raw.strip()
        if not line or line.startswith(('//','#')):continue
        need('$' not in line,'Unexpanded variable in source candidate: '+line)
        if line.startswith('+incdir+'):
            for name in line[8:].split('+'):
                p=(root/name).resolve()
                need(p.is_dir(),'Include directory missing: '+str(p))
                if p not in incdirs:incdirs.append(p)
            continue
        need(not line.startswith(('+','-')),'Candidate has unsupported option: '+line)
        p=(root/line).resolve();need(root in p.parents,'External candidate source requires review: '+line)
        need(p.is_file(),'Candidate source missing: '+str(p))
        if p.name in remove or p in {root/'e203/core/config.v',root/'e203/core/e203_defines.v'}:
            excluded.append(str(p));continue
        need(p.suffix in {'.v','.sv'},'Unexpected source suffix: '+str(p))
        need(not any(x in p.parts for x in ['test_env','tb','verification']), 'Simulation input in candidate: '+str(p))
        if p not in sources:sources.append(p)
    for name in ['GENERIC_LVT_SMIC.v','GENERIC_RVT_SMIC.v']:
        p=root/'e203/generic'/name;need(p.is_file(),'Missing selected generic implementation: '+name)
        if p not in sources:sources.append(p)
    for name in ['kwt_soc_tcm_configuration_guard.v','sram_wrap_32KX64.v','sram_wrap_64KX32.v']:
        p=adapter/name;need(p.is_file(),'Tested TCM adapter missing: '+name);sources.append(p)
    for rel in ['e203/core','accelerator/rtl/include']:
        p=root/rel
        if p not in incdirs:incdirs.append(p)
    return sources,incdirs,excluded

def stage_hvt_gate(body):
    pattern=r'\bCLKLANAQV4_8TR40(?=\s+u_donttouch_CLOCKGATE\s*\(\s*\.Q\(ECK\),\s*\.E\(E\),\s*\.TE\(SE\),\s*\.CK\(CK\)\s*\)\s*;)'
    result,n=re.subn(pattern,'CLKLANAQV4_12TH40',body)
    need(n==1,'Expected exactly one known gate instance/connection; stop for source review')
    return result

def make_tcl(run,libs,sources,incdirs):
    lines=['if {[catch {',
           'define_design_lib WORK -path '+q(run/'work'),
           'set_app_var search_path [concat [list '+' '.join(q(p) for p in incdirs)+'] $search_path]',
           'set_app_var target_library [list '+q(libs[0])+']',
           'set_app_var link_library [concat [list *] [list '+' '.join(q(p) for p in libs)+']]',
           'foreach lib [list '+' '.join(q(p) for p in libs)+'] {read_db $lib}',
           'puts "SOC LIBRARIES_READ"',
           'set gc [get_lib_cells -quiet */CLKLANAQV4_12TH40]',
           'if {[sizeof_collection $gc] != 1} {error {Missing or ambiguous HVT gate}}',
           'if {[get_attribute $gc clock_gating_integrated_cell] ne "latch_posedge_postcontrol"} {error {HVT gate type mismatch}}',
           'set gn [get_object_name $gc]',
           'foreach {pin dir role} {CK in clock_gate_clock_pin E in clock_gate_enable_pin TE in clock_gate_test_pin Q out clock_gate_out_pin} {',
           '  set gp [get_lib_pins -quiet ${gn}/${pin}]',
           '  if {[sizeof_collection $gp] != 1} {error "Missing gate pin $pin"}',
           '  if {[get_attribute $gp direction] ne $dir || [get_attribute -quiet $gp $role] ne "true"} {error "Gate pin role mismatch: $pin"}',
           '}',
           'puts "SOC HVT_GATE_LIBRARY_CHECK_PASS=CLKLANAQV4_12TH40"',
           'set gf [open '+q(run/'clock-gate-library.tsv')+' w]',
           'set gate_n 0',
           'foreach_in_collection c [get_lib_cells -quiet */*] {',
           '  set kind [get_attribute -quiet $c clock_gating_integrated_cell]',
           '  if {$kind == ""} {continue}',
           '  incr gate_n',
           '  set cname [get_object_name $c]',
           '  puts $gf "$cname type=$kind"',
           '  foreach_in_collection p [get_lib_pins -quiet ${cname}/*] {',
           '    set detail "[get_object_name $p]"',
           '    foreach a {direction function clock_gate_clock_pin clock_gate_enable_pin clock_gate_test_pin clock_gate_out_pin} {',
           '      append detail " $a=[get_attribute -quiet $p $a]"',
           '    }',
           '    puts $gf $detail',
           '  }',
           '}',
           'close $gf',
           'puts "SOC GATE_CANDIDATE_COUNT=$gate_n"',
           'if {![analyze -format sverilog -define SYNTHESIS [list '+' '.join(q(p) for p in sources)+']]} {error {SoC RTL analyze failed}}',
           'puts "SOC ANALYZE_PASS"',
           'elaborate kwt_dma_soc_top',
           'if {[sizeof_collection [get_designs -quiet kwt_dma_soc_top]] != 1} {error {Production top missing}}',
           'current_design kwt_dma_soc_top',
           'puts "SOC ELABORATE_PASS"',
           'set linked [link]',
           'redirect -file '+q(run/'check_design.rpt')+' {set valid [check_design]}',
           'redirect -file '+q(run/'references.rpt')+' {report_reference -hierarchy}',
           'redirect -file '+q(run/'design.rpt')+' {report_design}',
           'redirect -file '+q(run/'top_ports.rpt')+' {report_port -verbose}',
           'puts "SOC CLOCK_RESET_PORT_NAMES=[get_object_name [get_ports -quiet {*clk* *clock* *rst* *reset*}]]"',
           'set fh [open '+q(run/'sram_instances.tsv')+' w]',
           'puts $fh "instance\tref_name"','set counts_ok 1']
    for part,n in [('RAMSP1024X16',8),('RAMSP128X16',16),('RAMSP4096X16',128)]:
        lines += ['set cells [get_cells -hierarchical -filter {ref_name == '+part+'}]',
                  'set n [sizeof_collection $cells]',
                  'puts "SOC '+part+'_COUNT=$n EXPECTED='+str(n)+'"',
                  'if {$n != '+str(n)+'} {set counts_ok 0}',
                  'foreach_in_collection c $cells {puts $fh "[get_object_name $c]\t'+part+'"}']
    lines += ['close $fh',
              'if {!$linked} {error {Whole-SoC link failed; unresolved references must be fixed}}',
              'if {!$valid} {error {Whole-SoC check_design failed}}',
              'if {!$counts_ok} {error {Unexpected whole-SoC SRAM counts; inspect hierarchy/configuration}}',
              'foreach name {RAMSP1024X16 RAMSP128X16 RAMSP4096X16 ROM1KX32} {',
              '    if {[sizeof_collection [get_designs -quiet $name]] != 0} {error "SRAM behavioral module present: $name"}',
              '    if {[sizeof_collection [get_lib_cells -quiet */$name]] != 1} {error "Missing/ambiguous SRAM library cell: $name"}',
              '    set_dont_touch [get_cells -hierarchical -filter "ref_name == $name"] true',
              '}',
              'write -format ddc -hierarchy -output '+q(run/'kwt_dma_soc_top_elaborated.ddc'),
              'puts "SOC PASS_ANALYZE_ELABORATE_LINK_ONLY"',
              '} soc_error]} {puts "SOC FAIL=$soc_error"; exit 1}', 'exit 0','']
    return '\n'.join(lines)

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--tcm-run',type=Path,help='Defaults to newest official-model PASS TCM run')
    ap.add_argument('--prepare-only',action='store_true');a=ap.parse_args()
    need((ROOT/'kwt_dma_soc_top.v').is_file(),'Current production SoC top missing')
    runs=sorted((DC/'runs').glob('soc-tcm-prepare-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    tcm=None
    if a.tcm_run:tcm=a.tcm_run.resolve()
    else:
        for rp in runs:
            if json.loads(rp.read_text()).get('status')=='PASS_TCM_OFFICIAL_FUNCTIONAL_REQUIRES_SOC_INTEGRATION':tcm=rp.parent;break
    need(tcm is not None,'No passed official-model TCM run')
    need((DC/'runs').resolve() in tcm.parents,'TCM run must be inside our dc/runs')
    previous=json.loads((tcm/'result.json').read_text())
    need(previous.get('status')=='PASS_TCM_OFFICIAL_FUNCTIONAL_REQUIRES_SOC_INTEGRATION','TCM official-model test did not pass')
    old_hashes=json.loads((tcm/'input-sha256.json').read_text())
    for name,want in old_hashes.items():need(Path(name).is_file() and sha(Path(name))==want,'TCM test input changed: '+name)
    adapter=tcm/'adapter'
    for p in adapter.glob('*.v'):need(str(p) in old_hashes,'Adapter is not bound to successful test manifest: '+str(p))
    sources,incdirs,excluded=sources_and_includes(ROOT,adapter)
    need(ROOT/'kwt_dma_soc_top.v' in sources,'Production top not in candidate')
    libs=[DC/'libs/tt_hvt_1p1_125c'/(n+'.db') for n in LIBS]
    for p in libs:need(p.is_file(),'Library missing: '+str(p))
    need(sha(libs[3])==old_hashes.get(str(libs[3])),'4096 SRAM DB differs from TCM stage')
    rom_source=ROOT/'e203/mem_gen/ROM1KX32/db/ROM1KX32_tt_1p10v_1p10v_125c.db'
    need(rom_source.is_file(),'Matching ROM TT library missing: '+str(rom_source))
    rom_dest=DC/'libs/tt_hvt_1p1_125c'/rom_source.name
    if rom_dest.exists():need(sha(rom_dest)==sha(rom_source),'Existing ROM copy differs; will not overwrite')
    else:
        with rom_source.open('rb') as src,rom_dest.open('xb') as dst:shutil.copyfileobj(src,dst)
    libs.append(rom_dest)
    dc=shutil.which('dc_shell');need(dc or a.prepare_only,'dc_shell not in PATH')
    run=Path(tempfile.mkdtemp(prefix='soc-elab-',dir=str(DC/'runs')))
    (run/'work').mkdir();(run/'vendor-wrappers').mkdir()
    # Keep the successful functional-test inputs immutable. Only make net types
    # explicit in new synthesis copies; all logic and strict net checks remain.
    (run/'adapter').mkdir()
    generic_original=ROOT/'e203/generic/GENERIC_RVT_SMIC.v'
    generic_staged=run/'adapter/GENERIC_RVT_SMIC.v'
    generic_staged.write_text(stage_hvt_gate(generic_original.read_text()))
    sources[sources.index(generic_original)]=generic_staged
    if generic_original.parent not in incdirs:incdirs.append(generic_original.parent)
    (run/'clock-gate-substitution.json').write_text(json.dumps({
        'original':str(generic_original),'original_sha256':sha(generic_original),
        'staged':str(generic_staged),'staged_sha256':sha(generic_staged),
        'from_cell':'CLKLANAQV4_8TR40','to_cell':'CLKLANAQV4_12TH40',
        'connections':'Q(ECK), E(E), TE(SE), CK(CK), unchanged',
        'functional_equivalence_proven':False,
        'note':'Technology mapping for elaboration; system functional verification remains required.'},indent=2)+'\n')
    port_fixes=[]
    for name in ['sram_wrap_32KX64.v','sram_wrap_64KX32.v']:
        original=adapter/name
        dest=run/'adapter'/name
        dest.write_text(explicit_port_nets(original.read_text()))
        sources[sources.index(original)]=dest
        port_fixes.append({'original':str(original),'original_sha256':sha(original),
                          'staged':str(dest),'staged_sha256':sha(dest),
                          'change':'Explicit wire on eight ANSI ports only; logic unchanged'})
    (run/'port-declaration-fix.json').write_text(json.dumps(port_fixes,indent=2)+'\n')
    for part in ['RAMSP1024X16','RAMSP128X16','RAMSP4096X16']:
        p=Path('/storage1/admin_public_dir/SRAM_Lib_2025')/part/'verilog'/(part+'_rtl.v')
        body=clean(p.read_text())
        names=re.findall(r'\bmodule\s+(\w+)',body)
        need(sorted(names)==sorted([part+'_rtl_top',part+'_fr_top']),'Unexpected official wrapper content: '+str(p))
        need(not re.search(r'\b(always|initial)\b|`include',body),'Unexpected behavioral content in SRAM wrapper')
        dest=run/'vendor-wrappers'/p.name;shutil.copyfile(str(p),str(dest));sources.append(dest)
    # Resolve literal includes for provenance; inactive conditional includes are left to DC to decide.
    visited=set();headers={};missing=[]
    def scan(p):
        if p in visited:return
        visited.add(p)
        for name in re.findall(r'`include\s+"([^"]+)"',clean(p.read_text(errors='replace'))):
            found=next((x.resolve() for x in [p.parent/name,ROOT/name]+[d/name for d in incdirs] if x.is_file()),None)
            if found is None:missing.append({'from':str(p),'include':name})
            else:headers[str(found)]=sha(found);scan(found)
    for p in sources:scan(p)
    modules={}
    for p in sources:
        for name in re.findall(r'\bmodule\s+(?:automatic\s+)?([A-Za-z_$][\w$]*)',clean(p.read_text(errors='replace'))):
            modules.setdefault(name,[]).append(str(p))
    duplicates={n:ps for n,ps in modules.items() if len(set(ps))>1}
    need(not duplicates,'Cross-file duplicate modules remain: '+','.join(list(duplicates)[:8]))
    before={str(p):sha(p) for p in sources+libs+[ROOT/'sources.f',tcm/'result.json',tcm/'input-sha256.json']}
    before.update(headers)
    before[str(rom_source)]=sha(rom_source)
    before[str(generic_original)]=sha(generic_original)
    before.update({str(adapter/n):sha(adapter/n) for n in ['sram_wrap_32KX64.v','sram_wrap_64KX32.v']})
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'source-selection.json').write_text(json.dumps({'top':'kwt_dma_soc_top','tcm_run':str(tcm),'source_files':list(map(str,sources)),
        'include_directories':list(map(str,incdirs)),'excluded_original_files':excluded,
        'technology_choice':'SMIC generic implementation files selected; HVT leaf compatibility must be proven by link',
        'unresolved_literal_includes_lexical':missing,'defines':['SYNTHESIS'],'fpga_define':False,
        'expected_sram_counts':{'1024x16':8,'128x16':16,'4096x16':128}},indent=2)+'\n')
    (run/'sources.f').write_text('\n'.join(['+incdir+'+str(p) for p in incdirs]+list(map(str,sources)))+'\n')
    script=run/'read_soc.tcl';script.write_text(make_tcl(run,libs,sources,incdirs))
    (run/'README.txt').write_text('Whole-SoC ASIC source staging, not a synthesis result. No FPGA define.\n'
        'Two old TCM wrappers are replaced in this input set by officially function-tested adapters, production files unchanged.\n'
        'Only SMIC generic definitions selected to remove ARM/SMIC/SYNOPSYS duplicate names; unresolved leaf cells are fatal.\n'
        'SRAM expected: 8x1024x16 +16x128x16 +128x4096x16 (64 shared +64 CPU TCM).\n'
        'Clock ports/relationships, reset behavior and top-level I/O budgets must be reviewed before compile.\n')
    print('RUN='+str(run),flush=True)
    print('TOP=kwt_dma_soc_top SOURCES=%d; ASIC(no FPGA), tested TCM adapters; no compile'%len(sources),flush=True)
    if a.prepare_only:print('PREPARED_ONLY');return
    print('DC_READING_WHOLE_SOC; full log saved in run directory',flush=True)
    with (run/'dc.log').open('w') as log:proc=subprocess.run([dc,'-no_gui','-f',str(script)],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    text=(run/'dc.log').read_text(errors='replace')
    markers=[s for s in text.splitlines() if s.startswith('SOC ')]
    for s in markers:print(s)
    errors=[s for s in text.splitlines() if re.match(r'^\s*(Error:|Fatal:)',s)]
    warnings=[s for s in text.splitlines() if re.match(r'^\s*Warning:',s)]
    unresolved=sorted(set(re.findall(r"Unable to resolve reference\s+['\"]([^'\"]+)['\"]",text)))
    for s in errors[:5]:print(s)
    if unresolved:print('UNRESOLVED_REFERENCES='+','.join(unresolved[:12]))
    print('LOG_ERRORS=%d LOG_WARNINGS=%d'%(len(errors),len(warnings)))
    for s in warnings[:2]:print(s)
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(Path(p))!=h]
    passed=proc.returncode==0 and 'SOC PASS_ANALYZE_ELABORATE_LINK_ONLY' in markers and not errors and not unresolved and not changed
    report={'status':'PASS_SOC_ANALYZE_ELABORATE_LINK_ONLY' if passed else 'FAIL_SOC_READ_LINK',
            'top':'kwt_dma_soc_top','tcm_run':str(tcm),'process_returncode':proc.returncode,'markers':markers,
            'errors':errors,'unresolved_references':unresolved,'warning_count':len(warnings),'changed_inputs':changed,
            'compiled':False,'production_modified':False,'peer_modified':False,'post_synthesis_function_proven':False}
    (run/'result.json').write_text(json.dumps(report,indent=2)+'\n')
    need(passed,'Whole-SoC read/link not passed; keep '+str(run/'dc.log'))
    print('RESULT=PASS_SOC_ANALYZE_ELABORATE_LINK_ONLY; next=clock/interface constraints')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
