#!/usr/bin/env python3
"""Rebuild one isolated ASIC candidate using validated UART fix and actual task straps.
Existing production, teammate trees, and previous results are never overwritten.
Reuses already tested server helper generators; captures their hashes.
"""
import hashlib,importlib.util,json,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
STRAPS={'io_pads_jtag_TCK_i_ival':0,'io_pads_aon_pmu_dwakeup_n_i_ival':1,
 'io_pads_bootrom_n_i_ival':0,'io_pads_dbgmode0_n_i_ival':1,
 'io_pads_dbgmode1_n_i_ival':1,'io_pads_dbgmode2_n_i_ival':1}
def need(v,s):
    if not v:raise ValueError(s)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def q(p):
    s=str(p);need(not any(c in s for c in '{}\r\n'),'Unsupported path');return '{'+s+'}'
def newest(pattern,status):
    for p in sorted((DC/'runs').glob(pattern),key=lambda p:p.stat().st_mtime,reverse=True):
        if json.loads(p.read_text()).get('status')==status:return p.parent
    raise ValueError('No verified '+pattern)
def helper(name):
    p=DC/'scripts'/name;s=importlib.util.spec_from_file_location(name[:-3],p)
    m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m,p
def verify_hashes(manifest):
    for p,h in manifest.items():need(Path(p).is_file() and sha(p)==h,'Changed verified input: '+p)
def run_dc(dc,script,run,label):
    print(label+'_RUNNING',flush=True)
    log=run/(label+'.log')
    with log.open('w') as f:p=subprocess.run([dc,'-no_gui','-f',str(script)],cwd=str(run),stdout=f,stderr=subprocess.STDOUT)
    text=log.read_text(errors='replace');errors=[s for s in text.splitlines() if re.match(r'^\s*(Error:|Fatal:)',s)]
    for s in text.splitlines():
        if s.startswith(('SOC FAIL=','SOC_SYNTH FAIL=','CANDIDATE ','REVIEW VERIFIED_CHAINS=')):print(s,flush=True)
    for e in errors[:3]:print(e)
    need(p.returncode==0 and not errors,label+' failed; see '+str(log))
    return text

def main():
    elab=newest('soc-elab-*/result.json','PASS_SOC_ANALYZE_ELABORATE_LINK_ONLY')
    uart=newest('uart-latch-fix-*/result.json','UART_PATCH_DIFFERENTIAL_PASS_REQUIRES_SOC_REBUILD')
    old=json.loads((elab/'input-sha256.json').read_text());verify_hashes(old)
    uh=json.loads((uart/'input-sha256.json').read_text());verify_hashes(uh)
    candidate=uart/'apb_uart.v';original=ROOT/'e203/perips/apb_uart/apb_uart.v'
    need(str(candidate) in uh and str(original) in uh,'UART test not bound to source bytes')
    tb=ROOT/'test_env/tb/tb_top.v';tbtext=re.sub(r'/\*.*?\*/|//[^\n]*','',tb.read_text(),flags=re.S)
    for pin,value in STRAPS.items():
        if 'jtag_TCK' in pin:
            need(re.search(r"\bwire\s+jtag_TCK\s*=\s*1'b0",tbtext) and re.search(r'\.'+pin+r'\s*\(\s*jtag_TCK\s*\)',tbtext),'JTAG task connection changed')
        else:need(re.search(r'\.'+pin+r"\s*\(\s*1'b"+str(value)+r'\s*\)',tbtext),'Task strap changed: '+pin)
    reader,rp=helper('read_soc_design.py');synth,sp=helper('run_soc_synthesis.py');review,cp=helper('review_soc_clock_constraints.py')
    dc=shutil.which('dc_shell');need(dc,'dc_shell not in PATH')
    run=Path(tempfile.mkdtemp(prefix='soc-task-candidate-',dir=str(DC/'runs')))
    print('RUN='+str(run),flush=True)
    readrun=run/'elab';readrun.mkdir();(readrun/'work').mkdir()
    build=run/'synth';build.mkdir()
    staged=run/'rtl';staged.mkdir();uartcopy=staged/'apb_uart.v';shutil.copyfile(candidate,uartcopy)
    selected=json.loads((elab/'source-selection.json').read_text())
    sources=[Path(p) for p in selected['source_files']];need(sources.count(original)==1,'Original UART source not unique')
    sources[sources.index(original)]=uartcopy
    includes=[Path(p) for p in selected['include_directories']]
    if original.parent not in includes:includes.append(original.parent)
    libs=[DC/'libs/tt_hvt_1p1_125c'/(n+'.db') for n in synth.LIBS]
    before=dict(old);before.update(uh)
    before.update({str(p):sha(p) for p in [tb,rp,sp,cp,uartcopy,uart/'result.json']})
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'sources.f').write_text('\n'.join(['+incdir+'+str(p) for p in includes]+list(map(str,sources)))+'\n')
    selected.update({'source_files':list(map(str,sources)),'include_directories':list(map(str,includes)),
      'uart_differential_receipt':str(uart/'result.json'),'task_straps':STRAPS})
    (run/'source-selection.json').write_text(json.dumps(selected,indent=2)+'\n')
    (run/'assumptions.json').write_text(json.dumps({'base_assumptions':synth.ASSUMPTIONS,
      'overrides':{'task_straps':STRAPS,'CDC':'Per-chain structural checks before LF-to-first-stage-only exception',
      'clock_network':'Ideal HF driver net in logical synthesis; min-cap and physical clock implementation remain separately reportable'},
      'still_pending':['Divider/firmware frequency consistency','Detailed external IO budgets','ASIC and mapped functional verification',
                       'Full constraint coverage review','Activity coverage and system power/energy','Area-unit and budget-scope confirmation']},indent=2)+'\n')
    (run/'README.txt').write_text('Isolated task-mode ASIC candidate, not final acceptance or production promotion.\n'
      'Validated UART combinational default; original module/source path retained separately.\n'
      'Task straps are checked against actual tb_top.v. No reset forced inactive.\n'
      'HF150MHz/LF32768Hz, divider envelope and IO trial budgets retained.\n'
      'Run elab/read.tcl then synth/compile.tcl. All reports/netlists under synth/.\n'
      'Mode-constrained results do not establish active JTAG/debug-mode timing.\n')
    readscript=readrun/'read.tcl';readscript.write_text(reader.make_tcl(readrun,libs,sources,includes))
    checkpoint=readrun/'kwt_dma_soc_top_elaborated.ddc'
    straps='\n# Actual competition testbench pin settings; operating scenario, not RTL tie-offs.\n'
    for pin,value in STRAPS.items():
        straps+='if {[sizeof_collection [get_ports -quiet '+pin+']] != 1} {error {Missing task strap '+pin+'}}\n'
        straps+='set_case_analysis '+str(value)+' [get_ports '+pin+']\n'
    (build/'constraints.sdc').write_text(synth.SDC+straps)
    tcl=synth.make_tcl(build,checkpoint,libs)
    # Use the verified structural CDC checks on the newly mapped design, not old instance assumptions.
    rt=review.make_tcl(build,checkpoint,libs)
    a=rt.index('set hfregs [all_registers');b=rt.index('set gp [get_ports',a)
    cdc=rt[a:b]
    need('foreach_in_collection head $heads' in cdc and 'get_nets -segments' in cdc,'Need verified multi-timer review helper')
    ideal='''
change_names -rules verilog -hierarchy
set h [get_cells -hierarchical -filter {ref_name =~ e203_subsys_hclkgen*}]
set hp [get_pins -quiet __none__]
foreach_in_collection hc $h {set hp [add_to_collection $hp [get_pins -quiet [get_object_name $hc]/hfclk]]}
if {[sizeof_collection $hp] != 1} {error {Ambiguous HF output}}
set cone [all_fanin -flat -levels 1 -to $hp]
set drv [remove_from_collection [filter_collection $cone {object_class == pin && direction == out}] $hp]
if {[sizeof_collection $drv] != 1} {error {Ambiguous HF driver}}
set_ideal_network -no_propagate $drv
'''
    anchor='compile -map_effort medium';need(tcl.count(anchor)==1,'Compile helper changed')
    tcl=tcl.replace(anchor,anchor+'\n'+ideal+cdc+'\nunset c\nputs "CANDIDATE INCREMENTAL_OPTIMIZATION_START"\ncompile -incremental_mapping -map_effort high\n')
    end='puts "SOC_SYNTH REPORTS_READY_REVIEW_REQUIRED"';need(tcl.count(end)==1,'Report helper changed')
    extra='''set uart_storage [get_cells -hierarchical -filter {full_name =~ */u_perips_apb_uart*/fifo_tx_data_reg*}]
puts "CANDIDATE UART_TX_DATA_STORAGE_CELLS=[sizeof_collection $uart_storage]"
if {[sizeof_collection $uart_storage] != 0} {error {UART TX data storage remains; review fix}}
'''
    extra+='redirect -file '+q(build/'constraints_precise.rpt')+' {report_constraint -all_violators -significant_digits 8}\n'
    extra+='redirect -file '+q(build/'case_analysis.rpt')+' {report_case_analysis}\n'
    tcl=tcl.replace(end,extra+end)
    script=build/'compile.tcl';script.write_text(tcl)
    (run/'result.json').write_text(json.dumps({'status':'CANDIDATE_RUNNING','run':str(run)},indent=2)+'\n')
    run_dc(dc,readscript,readrun,'read')
    need(checkpoint.is_file(),'Elaboration did not save checkpoint')
    print('CANDIDATE ELAB_PASS; starting unified compile and incremental optimization',flush=True)
    text=run_dc(dc,script,build,'compile')
    need('SOC_SYNTH REPORTS_READY_REVIEW_REQUIRED' in text,'Missing completion marker')
    verify_hashes(before)
    for name in ['timing_setup.rpt','timing_hold.rpt']:
        found=re.findall(r'slack\s*\(([^)]+)\)\s*([-+\d.]+)',(build/name).read_text(),re.I)
        print(name+': '+(' '.join(found[0]) if found else 'NO_PATH_REPORTED'))
    area=(build/'area.rpt').read_text()
    for line in area.splitlines():
        if 'Total cell area:' in line or 'Macro/Black Box area:' in line:print(line.strip())
    coverage=(build/'check_timing_after.rpt').read_text();eps=[];active=False
    for line in coverage.splitlines():
        if 'not constrained for maximum delay' in line:active=True;continue
        if active and re.match(r'\s*(Information:|Warning:|Error:)',line):active=False
        s=line.strip()
        if active and ('/D' in s or s.startswith('io_')):eps.append(s)
    print('UNCONSTRAINED_MAX_ENDPOINTS='+str(len(eps)))
    (run/'remaining-endpoints.json').write_text(json.dumps(eps,indent=2)+'\n')
    for line in (build/'constraints_precise.rpt').read_text().splitlines():
        if 'VIOLATED' in line:print('CONSTRAINT '+line.strip())
    result={'status':'TASK_MODE_CANDIDATE_REPORTS_READY_REVIEW_REQUIRED','elaboration':str(readrun),'synthesis':str(build),
      'uart_receipt':str(uart/'result.json'),'task_straps':STRAPS,'unconstrained_endpoints':eps,
      'timing_accepted':False,'soc_functional_verification_passed':False,'power_evaluated':False,'production_modified':False}
    (run/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    print('RESULT='+result['status'])

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
