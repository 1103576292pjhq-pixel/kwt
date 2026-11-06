#!/usr/bin/env python3
"""First whole-SoC compile. Writes only own Desktop/dc, never production/peer.
Timing is a trial fastest-clock envelope, NOT a verified firmware operating mode.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
LIBS=['scc40nll_vhsc40_hvt_tt_v1p1_125c_basic','RAMSP1024X16_tt_1p10v_1p10v_125c',
      'RAMSP128X16_tt_1p10v_1p10v_125c','RAMSP4096X16_tt_1p10v_1p10v_125c',
      'ROM1KX32_tt_1p10v_1p10v_125c']
ASSUMPTIONS={'scope':'First logical synthesis, not competition acceptance',
 'hf_external_mhz':150,'lf_external_hz':32768,
 'divider':'Output modeled as divide-by-one fastest envelope; firmware mode and slower modes not yet verified',
 'mode':'No test/reset/mux control forced; no false paths or asynchronous clock groups',
 'io':'Trial all data I/O relative to HF: max 1ns/min 0.1ns; transition 0.1ns; load 0.05pF. AON and async IO require individual review.',
 'clock_uncertainty_ns':{'setup':0.1,'hold':0.05},
 'physical':'Ideal clocks, no specified wire-load model, no extracted interconnect',
 'pending':['Clock configuration/firmware consistency','CDC and generated-clock coverage',
            'Interface budgets','Post-synthesis functional verification','Activity/power/energy','Area units and budget partition']}

def need(v,msg):
    if not v:raise ValueError(msg)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def q(p):
    s=str(p);need(not any(c in s for c in '{}\r\n'),'Unsupported path');return '{'+s+'}'

SDC='''# TRIAL FASTEST-CLOCK ENVELOPE, NOT FINAL MULTIMODE CONSTRAINTS.
create_clock -name HF -period 6.666666666667 [get_ports hfextclk]
create_clock -name LF -period 30517.578125 [get_ports lfextclk]
# Model existing divider output at maximum frequency; do not tie control pins.
set divs [get_cells -hierarchical -filter {ref_name =~ e203_subsys_pllclkdiv*}]
if {[sizeof_collection $divs] != 1} {error {Expected one reviewed PLL divider; inspect clock-source-audit.txt}}
set dp [get_pins [get_object_name $divs]/clkout]
create_generated_clock -name HF_DIV1_ENVELOPE -source [get_ports hfextclk] -divide_by 1 $dp
set_clock_uncertainty -setup 0.10 [all_clocks]
set_clock_uncertainty -hold 0.05 [all_clocks]
set_clock_transition 0.10 [all_clocks]
set din [remove_from_collection [all_inputs] [get_ports {hfextclk lfextclk}]]
set dout [all_outputs]
set_input_delay -clock HF -max 1.0 $din
set_input_delay -clock HF -min 0.1 $din
set_input_transition 0.1 $din
set_output_delay -clock HF -max 1.0 $dout
set_output_delay -clock HF -min 0.1 $dout
set_load 0.05 $dout
'''

def make_tcl(run,checkpoint,libs):
    lines=['if {[catch {',
      'set_app_var target_library [list '+q(libs[0])+']',
      'set_app_var link_library [concat [list *] [list '+' '.join(q(p) for p in libs)+']]',
      'foreach lib [list '+' '.join(q(p) for p in libs)+'] {read_db $lib}',
      'read_ddc '+q(checkpoint),'current_design kwt_dma_soc_top',
      'if {![link]} {error {Checkpoint link failed}}',
      'puts "SOC_SYNTH CHECKPOINT_LINK_PASS"',
      'proc require_memories {} {',
      ' foreach {part expected} {RAMSP1024X16 8 RAMSP128X16 16 RAMSP4096X16 128 ROM1KX32 1} {',
      '  set cs [get_cells -hierarchical -filter "ref_name == $part"]',
      '  set n [sizeof_collection $cs]',
      '  if {$n != $expected} {error "Memory count $part=$n expected=$expected"}',
      '  if {[sizeof_collection [get_designs -quiet $part]] != 0} {error "Behavioral memory present: $part"}',
      '  if {[sizeof_collection [get_lib_cells -quiet */$part]] != 1} {error "Library ambiguity: $part"}',
      '  set_dont_touch $cs true',
      ' }','}', 'require_memories',
      'redirect -variable units_text {report_units}',
      'set f [open '+q(run/'units.rpt')+' w]; puts $f $units_text; close $f',
      r'if {![regexp -nocase {Time_unit\s*:\s*1\.0e-09\s+Second\(ns\)} $units_text]} {error {Expected ns units}}',
      r'if {![regexp -nocase {Capacitive_load_unit\s*:\s*1\.0e-12\s+Farad\(pF\)} $units_text]} {error {Expected pF units}}',
      'source '+q(run/'constraints.sdc'),
      'puts "SOC_SYNTH TRIAL_CLOCKS_APPLIED HF=150MHz LF=32768Hz DIV1_ENVELOPE"']
    for name,cmd in [('clocks_before','report_clock'),('check_timing_before','check_timing'),('ports','report_port -verbose')]:
        lines.append('redirect -file '+q(run/(name+'.rpt'))+' {'+cmd+'}')
    lines += ['redirect -file '+q(run/'check_design_before.rpt')+' {set ok [check_design]}',
      'if {!$ok} {error {Pre-compile check_design failed}}',
      'puts "SOC_SYNTH COMPILE_START"','compile -map_effort medium',
      'puts "SOC_SYNTH COMPILE_RETURNED"',
      'write -format ddc -hierarchy -output '+q(run/'post_compile_raw.ddc'),
      'if {![link]} {error {Post-compile link failed}}','require_memories',
      'redirect -file '+q(run/'check_design_after.rpt')+' {set ok [check_design]}',
      'if {!$ok} {error {Post-compile check_design failed}}',
      'set librefs [list]',
      'foreach_in_collection lc [get_lib_cells */*] {lappend librefs [lindex [split [get_object_name $lc] /] end]}',
      'set bad [list]',
      'foreach_in_collection c [get_cells -hierarchical -filter {is_hierarchical == false}] {',
      ' set ref [get_attribute $c ref_name]',
      ' if {$ref ne {**logic_0**} && $ref ne {**logic_1**} && [lsearch -exact $librefs $ref] < 0} {lappend bad "[get_object_name $c]:$ref"}',
      '}',
      'set f [open '+q(run/'unmapped.txt')+' w]; puts $f [join $bad "\n"]; close $f',
      'if {[llength $bad]} {error {Unmapped leaf cells remain}}']
    reports={'qor':'report_qor','area':'report_area -hierarchy','references':'report_reference -hierarchy',
       'timing_setup':'report_timing -delay_type max -max_paths 20 -nworst 1 -input_pins -nets',
       'timing_hold':'report_timing -delay_type min -max_paths 20 -nworst 1 -input_pins -nets',
       'constraint_violators':'report_constraint -all_violators','check_timing_after':'check_timing',
       'clocks_after':'report_clock'}
    for name,cmd in reports.items():lines.append('redirect -file '+q(run/(name+'.rpt'))+' {'+cmd+'}')
    lines += ['set f [open '+q(run/'hierarchical-area.tsv')+' w]',
      'puts $f "instance\tref_name\tarea_library_units"',
      'foreach_in_collection c [get_cells -hierarchical -filter {is_hierarchical == true}] {puts $f "[get_object_name $c]\t[get_attribute $c ref_name]\t[get_attribute -quiet $c area]"}',
      'close $f','change_names -rules verilog -hierarchy',
      'write -format ddc -hierarchy -output '+q(run/'kwt_dma_soc_top_mapped.ddc'),
      'write -format verilog -hierarchy -output '+q(run/'kwt_dma_soc_top_mapped.v'),
      'write_sdc '+q(run/'mapped.sdc'),
      'puts "SOC_SYNTH REPORTS_READY_REVIEW_REQUIRED"',
      '} reason]} {puts "SOC_SYNTH FAIL=$reason"; exit 1}','exit 0','']
    return '\n'.join(lines)

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--prepare-only',action='store_true');a=ap.parse_args()
    candidates=sorted((DC/'runs').glob('soc-elab-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    previous=next((p.parent for p in candidates if json.loads(p.read_text()).get('status')=='PASS_SOC_ANALYZE_ELABORATE_LINK_ONLY'),None)
    need(previous,'No successful whole-SoC elaboration')
    before=json.loads((previous/'input-sha256.json').read_text())
    for p,h in before.items():need(Path(p).is_file() and sha(p)==h,'Elaboration input changed: '+p)
    checkpoint=previous/'kwt_dma_soc_top_elaborated.ddc';need(checkpoint.is_file(),'Missing DDC')
    before[str(checkpoint)]=sha(checkpoint)
    libs=[DC/'libs/tt_hvt_1p1_125c'/(n+'.db') for n in LIBS]
    for p in libs:need(str(p) in before,'Library not bound to elaboration: '+str(p))
    pll=ROOT/'e203/subsys/e203_subsys_pll.v'
    body=re.sub(r'/\*.*?\*/|//[^\n]*','',pll.read_text(),flags=re.S)
    need(re.search(r'assign\s+pllout\s*=\s*pllrefclk\s*;',body),'PLL implementation changed')
    need(re.search(r'assign\s+plloutclk\s*=\s*pllout\s*;',body),'PLL output changed')
    dc=shutil.which('dc_shell');need(dc or a.prepare_only,'dc_shell not in PATH')
    run=Path(tempfile.mkdtemp(prefix='soc-synth-',dir=str(DC/'runs')))
    # Save clock RTL and relevant firmware/testbench evidence together for later mode review.
    audit=[]
    for p in sorted((ROOT/'e203/subsys').glob('*.v')):
        if any(x in p.name for x in ['clkgen','pll','gfcm']):
            audit.append('\n### '+str(p)+'\n'+p.read_text());before[str(p)]=sha(p)
    for p in (ROOT/'test_env').rglob('*'):
        if p.is_file() and p.suffix in {'.c','.h','.S','.v'} and p.stat().st_size<300000:
            matches=[str(i)+': '+s for i,s in enumerate(p.read_text(errors='replace').splitlines(),1)
                     if re.search(r'pll|pllbypass|plloutdiv|hfextclk|lfextclk|PRCI|HFXOSC',s,re.I)]
            if matches:audit.append('\n### '+str(p)+'\n'+'\n'.join(matches));before[str(p)]=sha(p)
    (run/'clock-source-audit.txt').write_text('\n'.join(audit))
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'assumptions.json').write_text(json.dumps(ASSUMPTIONS,indent=2)+'\n')
    (run/'constraints.sdc').write_text(SDC)
    script=run/'compile.tcl';script.write_text(make_tcl(run,checkpoint,libs))
    (run/'README.txt').write_text('First whole-SoC logical compile; trial fastest clock envelope and IO budgets.\n'
      'Full area includes E203/shared SRAM/ROM; do not compare full area with accelerator-only budget.\n'
      'Hierarchy TSV rows overlap; do not sum parents and descendants. Raw library area units.\n'
      'REPORTS_READY is not timing/functional/competition acceptance. See assumptions.json.\n'
      'No production or teammate files modified. Reports and outputs remain in this directory.\n')
    print('RUN='+str(run),flush=True);print('ELAB='+str(previous),flush=True)
    if a.prepare_only:print('PREPARED_ONLY');return
    print('DC_RUNNING whole SoC; trial constraints; detailed log=dc.log',flush=True)
    with (run/'dc.log').open('w') as log:
        proc=subprocess.run([dc,'-no_gui','-f',str(script)],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    log=(run/'dc.log').read_text(errors='replace');markers=[s for s in log.splitlines() if s.startswith('SOC_SYNTH ')]
    for s in markers:print(s)
    errors=[s for s in log.splitlines() if re.match(r'^\s*(Error:|Fatal:)',s)]
    warnings=[s for s in log.splitlines() if re.match(r'^\s*Warning:',s)]
    for s in errors[:4]:print(s)
    print('LOG_ERRORS=%d LOG_WARNINGS=%d'%(len(errors),len(warnings)))
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(p)!=h]
    required=['kwt_dma_soc_top_mapped.ddc','kwt_dma_soc_top_mapped.v','mapped.sdc','area.rpt','qor.rpt',
              'timing_setup.rpt','timing_hold.rpt','check_timing_after.rpt','constraint_violators.rpt']
    passed=proc.returncode==0 and not errors and not changed and 'SOC_SYNTH REPORTS_READY_REVIEW_REQUIRED' in markers and all((run/n).is_file() and (run/n).stat().st_size for n in required)
    result={'status':'SOC_COMPILE_REPORTS_READY_REVIEW_REQUIRED' if passed else 'FAIL_SOC_SYNTHESIS',
      'elaboration':str(previous),'errors':errors,'warning_count':len(warnings),'changed_inputs':changed,
      'process_returncode':proc.returncode,'assumptions':ASSUMPTIONS,'timing_accepted':False,
      'functional_equivalence_proven':False,'power_evaluated':False,'competition_accepted':False}
    (run/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    for name,pat in [('area.rpt',r'Total cell area:|Macro/Black Box area:'),('timing_setup.rpt',r'\bslack\s*\('),('timing_hold.rpt',r'\bslack\s*\(')]:
        p=run/name
        if p.exists():
            found=[s.strip() for s in p.read_text().splitlines() if re.search(pat,s,re.I)]
            for s in found[:2 if name=='area.rpt' else 1]:print(name+': '+s)
    print('RESULT='+result['status'])
    need(passed,'See dc.log in '+str(run))

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
