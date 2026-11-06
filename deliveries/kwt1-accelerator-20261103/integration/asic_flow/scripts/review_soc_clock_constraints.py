#!/usr/bin/env python3
"""Verify all matching timer LF synchronizers; report normal GPIO scenario separately."""
import hashlib,json,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
LIBS=['scc40nll_vhsc40_hvt_tt_v1p1_125c_basic','RAMSP1024X16_tt_1p10v_1p10v_125c',
 'RAMSP128X16_tt_1p10v_1p10v_125c','RAMSP4096X16_tt_1p10v_1p10v_125c','ROM1KX32_tt_1p10v_1p10v_125c']
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def need(v,s):
    if not v:raise ValueError(s)
def q(p):
    s=str(p);need(not any(c in s for c in '{}\r\n'),'Unsupported path');return '{'+s+'}'

def make_tcl(run,ddc,libs):
    lines=['if {[catch {',
      'set_app_var target_library [list '+q(libs[0])+']',
      'set_app_var link_library [concat [list *] [list '+' '.join(q(p) for p in libs)+']]',
      'foreach lib [list '+' '.join(q(p) for p in libs)+'] {read_db $lib}',
      'read_ddc '+q(ddc),'current_design kwt_dma_soc_top',
      'if {![link]} {error {Mapped design link failed}}',
      'if {[sizeof_collection [get_clocks -quiet LF]] != 1 || [sizeof_collection [get_clocks -quiet HF]] != 1} {error {Saved clocks missing}}',
      'set hfregs [all_registers -clock HF -cells]',
      'set heads [get_cells -hierarchical -filter {full_name =~ */u_perips_apb_pwm/u_tim*/u_in_stage/r_ls_clk_sync_reg_0_}]',
      'if {[sizeof_collection $heads] == 0} {error {No timer synchronizers found}}',
      'set chain_from [get_pins -quiet __none__]; set chain_to [get_pins -quiet __none__]',
      'set chain_count 0',
      'foreach_in_collection head $heads {',
      'set base [regsub {r_ls_clk_sync_reg_0_$} [get_object_name $head] {}]',
      'for {set i 0} {$i < 3} {incr i} {',
      ' set pattern "${base}r_ls_clk_sync_reg_${i}_"',
      ' set c($i) [get_cells -hierarchical -filter "full_name =~ $pattern"]',
      ' if {[sizeof_collection $c($i)] != 1} {error "Expected one synchronizer stage $i"}',
      ' if {[sizeof_collection [remove_from_collection $c($i) $hfregs]] != 0} {error "Stage $i not recognized in HF clock domain"}',
      ' set d($i) [get_pins -quiet [get_object_name $c($i)]/D]',
      ' set qp($i) [get_pins -quiet [get_object_name $c($i)]/Q]',
      ' if {[sizeof_collection $d($i)] != 1 || [sizeof_collection $qp($i)] != 1} {error "Unexpected stage pins: $i"}',
      '}',
      'set starts [all_fanin -flat -startpoints_only -to $d(0)]',
      'if {[sizeof_collection $starts] != 1 || [get_object_name $starts] ne "lfextclk"} {error "Unexpected first-stage source: [get_object_name $starts]"}',
      'for {set i 0} {$i < 2} {incr i} {',
      ' set j [expr {$i+1}]',
      ' set src [get_pins -quiet __none__]; foreach_in_collection dp [get_pins -of_objects [get_nets -segments -of_objects $d($j)] -filter {direction == out}] {if {[sizeof_collection [get_cells -of_objects $dp -filter {is_hierarchical == false}]] == 1} {set src [add_to_collection $src $dp]}}',
      ' if {[sizeof_collection $src] != 1 || [get_object_name $src] ne [get_object_name $qp($i)]} {error "Synchronizer chain changed at stage $j"}',
      '}',
      '# First-stage metastable value must only feed the second stage.',
      'set ends [all_fanout -flat -endpoints_only -from $qp(0)]',
      'if {[sizeof_collection $ends] != 1 || [get_object_name $ends] ne [get_object_name $d(1)]} {error "First-stage fanout requires review: [get_object_name $ends]"}',
      'puts "REVIEW FIRST_STAGE_D=[get_object_name $d(0)]"',
      'redirect -append -file '+q(run/'first_stage_before.rpt')+' {report_timing -delay_type min -to $d(0) -max_paths 1 -input_pins -nets}',
      '# Separate external crystal clocks: exempt only the asynchronous arrival at stage0/D.',
      'set_false_path -from [get_clocks LF] -to $d(0)',
      'incr chain_count',
      'set chain_from [add_to_collection $chain_from $qp(0)]; set chain_from [add_to_collection $chain_from $qp(1)]',
      'set chain_to [add_to_collection $chain_to $d(1)]; set chain_to [add_to_collection $chain_to $d(2)]',
      '}',
      'puts "REVIEW VERIFIED_CHAINS=$chain_count; first_stage_exceptions_only"',
      'set gp [get_ports -quiet {io_pads_gpioA_o_oval[29]}]',
      'if {[sizeof_collection $gp] != 1} {error {GPIO29 port not found}}',
      'redirect -file '+q(run/'gpio29_fanin.rpt')+' {puts [get_object_name [all_fanin -flat -to $gp]]}',
      'redirect -file '+q(run/'gpio29_max.rpt')+' {report_timing -to $gp -delay_type max -max_paths 3 -input_pins -nets}',
      'redirect -file '+q(run/'gpio29_min.rpt')+' {report_timing -to $gp -delay_type min -max_paths 3 -input_pins -nets}',
      'set regs [all_registers -data_pins]',
      'set mp [filter_collection [get_pins -of_objects [get_cells -hierarchical -filter {ref_name == RAMSP1024X16 || ref_name == RAMSP128X16 || ref_name == RAMSP4096X16}] -filter {direction == in}] {full_name !~ */CLK}]']
    for kind,to in [('overall',''),('registers',' -to $regs'),('sram',' -to $mp'),('synchronizer_interstage',' -from $chain_from -to $chain_to')]:
        for delay in ['max','min']:
            lines+=['redirect -file '+q(run/(kind+'_'+delay+'.rpt'))+' {report_timing -delay_type '+delay+' -max_paths 5 -input_pins -nets'+to+'}']
    lines+=['redirect -file '+q(run/'check_timing.rpt')+' {check_timing}',
      'redirect -file '+q(run/'constraints.rpt')+' {report_constraint -all_violators}',
      'write_sdc '+q(run/'candidate_constraints.sdc')]
    lines += ['set mode [get_pins -hierarchical -filter {full_name =~ */u_e203_subsys_main/inspect_mode}]',
      'if {[sizeof_collection $mode] != 1} {error {Normal-mode selector is missing or ambiguous}}',
      'redirect -file '+q(run/'inspect_mode_source.rpt')+' {puts [get_object_name [all_fanin -flat -startpoints_only -to $mode]]}',
      '# Operating-scenario constraint only; not an RTL edit or proof of firmware mode.',
      'set_case_analysis 0 $mode',
      'puts "REVIEW NORMAL_GPIO_SCENARIO inspect_mode=0; operating_mode_confirmation_pending"']
    for kind,to in [('normal_overall',''),('normal_registers',' -to $regs'),('normal_sram',' -to $mp')]:
        for delay in ['max','min']:
            lines += ['redirect -file '+q(run/(kind+'_'+delay+'.rpt'))+' {report_timing -delay_type '+delay+' -max_paths 5 -input_pins -nets'+to+'}']
    lines += ['redirect -file '+q(run/'normal_check_timing.rpt')+' {check_timing}',
      'redirect -file '+q(run/'normal_constraints.rpt')+' {report_constraint -all_violators}',
      'write_sdc '+q(run/'candidate_normal_gpio.sdc'),
      'puts "REVIEW REPORTS_READY; normal_GPIO_scenario_only; no_compile"',
      '} err]} {puts "REVIEW FAIL=$err"; exit 1}','exit 0','']
    return '\n'.join(lines)

def main():
    candidates=sorted((DC/'runs').glob('soc-incremental-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    prev=next((p.parent for p in candidates if json.loads(p.read_text()).get('status')=='INCREMENTAL_REPORTS_READY_REVIEW_REQUIRED'),None)
    need(prev,'No successful incremental run')
    before=json.loads((prev/'input-sha256.json').read_text())
    for p,h in before.items():need(Path(p).is_file() and sha(p)==h,'Input changed: '+p)
    ddc=prev/'kwt_dma_soc_top_mapped.ddc';need(ddc.is_file(),'Missing mapped DDC');before[str(ddc)]=sha(ddc)
    libs=[DC/'libs/tt_hvt_1p1_125c'/(n+'.db') for n in LIBS]
    for p in libs:need(sha(p)==before.get(str(p)),'Library mismatch')
    source=ROOT/'e203/perips/apb_adv_timer/input_stage.v'
    body=re.sub(r'/\*.*?\*/|//[^\n]*','',source.read_text(),flags=re.S)
    need(re.search(r'reg\s*\[2:0\]\s*r_ls_clk_sync\b',body),'Synchronizer width changed')
    need(re.search(r'r_ls_clk_sync\s*<=\s*\{\s*r_ls_clk_sync\s*\[1:0\]\s*,\s*ls_clk_i\s*\}',body),'Synchronizer update changed')
    before[str(source)]=sha(source)
    dc=shutil.which('dc_shell');need(dc,'dc_shell not in PATH')
    run=Path(tempfile.mkdtemp(prefix='soc-clock-review-',dir=str(DC/'runs')))
    print('RUN='+str(run),flush=True)
    # Include complete nearby source expressions instead of guessing GPIO mux mode.
    evidence=[]
    for p in [ROOT/'e203/subsys/e203_subsys_main.v',ROOT/'e203/subsys/e203_subsys_top.v',ROOT/'kwt_dma_soc_top.v']:
        text=p.read_text().splitlines();before[str(p)]=sha(p)
        hits=[i for i,s in enumerate(text) if re.search(r'inspect.*(?:lf|32k|ls)|gpioA_o_oval\s*\[\s*29\s*\]',s,re.I)]
        keep=set()
        for i in hits:keep.update(range(max(0,i-4),min(len(text),i+5)))
        if keep:
            evidence.append('### '+str(p)+'\n'+'\n'.join(str(i+1)+': '+text[i] for i in sorted(keep)))
    (run/'gpio-source-review.txt').write_text('\n\n'.join(evidence))
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'README.txt').write_text('Candidate constraint review only, not final timing acceptance.\n'
      'Only LF clock to verified synchronizer stage0/D is false-pathed, conditional on structural guards.\n'
      'HF/LF treated as independent external crystal clocks; original periods/IO/divider assumptions retained.\n'
      'No clock-group cut; no reset exceptions; no interstage cut.\n'
      'Unprefixed reports retain all modes. normal_* reports add inspect_mode=0 only; normal operation must be confirmed separately.\n'
      'Observation-mode forwarded-clock IO requirements remain pending; normal-mode success is not all-mode success.\n'
      'No compile, no original checkpoint overwrite, no area/power change claimed.\n')
    script=run/'review.tcl';script.write_text(make_tcl(run,ddc,libs))
    print('DC_REVIEW_RUNNING; no compile',flush=True)
    with (run/'dc.log').open('w') as log:proc=subprocess.run([dc,'-no_gui','-f',str(script)],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    text=(run/'dc.log').read_text(errors='replace');markers=[s for s in text.splitlines() if s.startswith('REVIEW ')]
    for s in markers:print(s)
    errors=[s for s in text.splitlines() if re.match(r'^\s*(Error:|Fatal:)',s)]
    for s in errors[:4]:print(s)
    summary={}
    for kind in ['overall','registers','sram','synchronizer_interstage','normal_overall','normal_registers','normal_sram']:
        for delay in ['max','min']:
            p=run/(kind+'_'+delay+'.rpt')
            if p.exists():
                found=re.findall(r'slack\s*\(([^)]+)\)\s*([-+\d.]+)',p.read_text(),re.I)
                summary[p.stem]=found;print(p.stem+': '+(' '.join(found[0]) if found else 'NO_PATH_REPORTED'))
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(p)!=h]
    ok=proc.returncode==0 and not errors and not changed and 'REVIEW REPORTS_READY; normal_GPIO_scenario_only; no_compile' in markers
    status='CONSTRAINT_REVIEW_READY_MODE_CONFIRMATION_PENDING' if ok else 'FAIL_CONSTRAINT_REVIEW'
    (run/'result.json').write_text(json.dumps({'status':status,'source_run':str(prev),'errors':errors,
      'changed_inputs':changed,'summaries':summary,'timing_accepted':False,'compiled':False},indent=2)+'\n')
    print('RESULT='+status)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
