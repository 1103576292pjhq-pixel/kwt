#!/usr/bin/env python3
"""Load the latest task candidate into PrimeTime power analysis and collect simulation adapters.
No power number is claimed without matching task-window activity and coverage.
"""
import gzip,hashlib,json,re,shutil,subprocess,tempfile,os
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
PARTS={'RAMSP1024X16':8,'RAMSP128X16':16,'RAMSP4096X16':128,'ROM1KX32':1}
LIBS=['scc40nll_vhsc40_hvt_tt_v1p1_125c_basic','RAMSP1024X16_tt_1p10v_1p10v_125c',
 'RAMSP128X16_tt_1p10v_1p10v_125c','RAMSP4096X16_tt_1p10v_1p10v_125c','ROM1KX32_tt_1p10v_1p10v_125c']
def need(v,s):
    if not v:raise ValueError(s)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def q(p):
    s=str(p);need(not any(c in s for c in '{}\r\n'),'Unsupported path');return '{'+s+'}'
def make_tcl(run,netlist,sdc,libs):
    a=['if {[catch {','set power_enable_analysis true','set power_analysis_mode averaged',
       'set link_path [list * '+' '.join(q(p) for p in libs)+']',
       'read_verilog '+q(netlist),'current_design kwt_dma_soc_top',
       'if {![link_design kwt_dma_soc_top]} {error {PrimeTime netlist link failed}}',
       'puts "POWER_PREP NETLIST_LINK_PASS"','read_sdc '+q(sdc),
       'puts "POWER_PREP CONSTRAINTS_READ"']
    for part,n in PARTS.items():
        a+=['set ms [get_cells -hierarchical -filter {ref_name == '+part+'}]',
            'if {[sizeof_collection $ms] != '+str(n)+'} {error {Memory count mismatch: '+part+'}}',
            'puts "POWER_PREP '+part+'_COUNT=[sizeof_collection $ms]"']
    a+=['redirect -file '+q(run/'units.rpt')+' {report_units}',
        'redirect -file '+q(run/'check_power_without_activity.rpt')+' {check_power}',
        'redirect -file '+q(run/'check_timing.rpt')+' {check_timing}',
        'puts "POWER_PREP SESSION_READY_ACTIVITY_REQUIRED"',
        '} why]} {puts "POWER_PREP FAIL=$why"; exit 1}','exit 0','']
    return '\n'.join(a)

def main():
    files=sorted((DC/'runs').glob('soc-task-candidate-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    receipt=next((p for p in files if json.loads(p.read_text()).get('status')=='TASK_MODE_CANDIDATE_REPORTS_READY_REVIEW_REQUIRED'),None)
    need(receipt,'Latest candidate reports not ready');data=json.loads(receipt.read_text());root=receipt.parent;synth=Path(data['synthesis'])
    original=json.loads((root/'input-sha256.json').read_text())
    for p,h in original.items():need(Path(p).is_file() and sha(p)==h,'Frozen input changed: '+p)
    libs=[DC/'libs/tt_hvt_1p1_125c'/(n+'.db') for n in LIBS]
    for p in libs:need(p.is_file() and sha(p)==original.get(str(p)),'Library mismatch: '+str(p))
    pt=shutil.which('pt_shell');need(pt,'pt_shell not in PATH')
    netlist=synth/'kwt_dma_soc_top_mapped.v';sdc=synth/'mapped.sdc'
    need(netlist.is_file() and sdc.is_file(),'Candidate netlist/SDC missing')
    run=Path(tempfile.mkdtemp(prefix='soc-power-',dir=str(DC/'runs')))
    print('RUN='+str(run),flush=True);print('CANDIDATE='+str(root),flush=True)
    hashes={str(p):sha(p) for p in libs+[netlist,sdc,receipt]}
    # Read-only lookup in the teammate library directory; never source teammate scripts.
    model_candidates=[];scan_root=DC.parent/'kwt_dc/library'
    for directory,dirs,names in os.walk(scan_root):
        if len(Path(directory).relative_to(scan_root).parts)>=6:dirs[:]=[]
        for name in names:
            if not name.endswith(('.v','.sv','.v.gz','.sv.gz')):continue
            p=Path(directory)/name
            try:
                opener=gzip.open if name.endswith('.gz') else open
                with opener(p,'rt',errors='replace') as f:
                    found=any(re.search(r'\bmodule\s+CLKLANAQV4_12TH40\b',line) for line in f)
                if found:model_candidates.append(str(p));hashes[str(p)]=sha(p)
            except OSError:continue
    print('HVT_SIM_MODEL_CANDIDATES='+str(len(model_candidates)),flush=True)
    for p in model_candidates[:2]:print('MODEL='+p,flush=True)
    # Capture real loader and firmware hooks that must be adapted for physical TCM macros.
    evidence=[];printed=0
    for p in (ROOT/'test_env').rglob('*'):
        if not p.is_file() or p.suffix not in {'.v','.sv','.py'} or p.stat().st_size>600000:continue
        lines=p.read_text(errors='replace').splitlines()
        hits=[i for i,s in enumerate(lines) if re.search(r'readmem|itcm.*mem|dtcm.*mem|ITCM.*RAM|DTCM.*RAM|dumpvars|dumpoff|dumpon|hfclk_period|hfextclk.*#',s,re.I)]
        if not hits:continue
        keep=set()
        for i in hits:keep.update(range(max(0,i-4),min(len(lines),i+5)))
        evidence.append({'path':str(p),'sha256':sha(p),'context':[str(i+1)+': '+lines[i] for i in sorted(keep)]})
        hashes[str(p)]=sha(p)
        for i in hits:
            if printed<8 and re.search(r'readmem|itcm.*mem|dtcm.*mem',lines[i],re.I):
                print('INIT '+str(p.relative_to(ROOT))+':'+str(i+1)+' '+lines[i].strip()[:260],flush=True);printed+=1
    (run/'simulation-adaptation-evidence.json').write_text(json.dumps(evidence,indent=2)+'\n')
    runner=ROOT/'test_env/run_suite.py'
    shutil.copyfile(runner,run/'runner-original.txt');hashes[str(runner)]=sha(runner)
    (run/'model-candidates.json').write_text(json.dumps(model_candidates,indent=2)+'\n')
    (run/'input-sha256.json').write_text(json.dumps(hashes,indent=2)+'\n')
    (run/'README.txt').write_text('Power preparation for latest mapped task candidate; not a power result.\n'
      'No read_vcd/read_saif yet, no default-activity report_power, no numeric power claim.\n'
      'Averaged power setup; full task-window activity and mapping coverage still required.\n'
      'PrimeTime check_power warnings before activity are diagnostic, not acceptance.\n'
      'SRAM, ROM and standard-cell libraries match synthesis. Dynamic/static memory coverage remains to verify.\n')
    script=run/'prepare_power.tcl';script.write_text(make_tcl(run,netlist,sdc,libs))
    print('PRIMETIME_POWER_PREPARATION_RUNNING; no synthesis',flush=True)
    with (run/'pt.log').open('w') as log:proc=subprocess.run([pt,'-f',str(script)],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    text=(run/'pt.log').read_text(errors='replace');markers=[s for s in text.splitlines() if s.startswith('POWER_PREP ')]
    for s in markers:print(s)
    errors=[s for s in text.splitlines() if re.match(r'^\s*(Error:|Fatal:)',s)]
    for s in errors[:4]:print(s)
    pp=run/'check_power_without_activity.rpt'
    if pp.exists():
        lines=[s.strip() for s in pp.read_text(errors='replace').splitlines() if re.search(r'Warning|Error|missing|no.power|unannotated|not.annotated',s,re.I)]
        for s in lines[:6]:print('POWER_MODEL_CHECK '+s[:240])
    changed=[p for p,h in hashes.items() if not Path(p).is_file() or sha(p)!=h]
    ok=proc.returncode==0 and not errors and not changed and 'POWER_PREP SESSION_READY_ACTIVITY_REQUIRED' in markers
    status='POWER_NETLIST_READY_ACTIVITY_REQUIRED' if ok else 'FAIL_POWER_PREPARATION'
    (run/'result.json').write_text(json.dumps({'status':status,'candidate':str(root),'synthesis':str(synth),
      'tool':pt,'errors':errors,'changed_inputs':changed,'simulation_model_candidates':model_candidates,
      'activity_loaded':False,'power_evaluated':False,'functional_equivalence_proven':False},indent=2)+'\n')
    print('RESULT='+status)
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
