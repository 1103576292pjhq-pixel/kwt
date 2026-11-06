#!/usr/bin/env python3
"""First 150MHz task power estimate plus mandatory coverage diagnostics. No design writes."""
import gzip,hashlib,json,os,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
def latest(pattern,status):
    for p in sorted((DC/'runs').glob(pattern),key=lambda p:p.stat().st_mtime,reverse=True):
        d=json.loads(p.read_text())
        if d.get('status')==status:return p,d
    raise ValueError('No completed '+status)
def main():
    receipt,suite=latest('fpga-suite12-150mhz-*/report.json','PASS_FPGA_SUITE12_NOMINAL_150MHZ')
    oldrec,olddata=latest('fpga-vcd-slash-map-*/result.json','MAPPING_REVIEW_REQUIRED');old=oldrec.parent
    task=suite['tasks'][0]
    if abs(task['timing']['period_ps']-6666.666)>0.01:raise ValueError('Unexpected task clock')
    wave=Path(task['activity']['file'])
    if hashlib.sha256(wave.read_bytes()).hexdigest()!=task['activity']['sha256']:raise ValueError('Waveform hash changed')
    run=Path(tempfile.mkdtemp(prefix='power-150mhz-task01-',dir=str(DC/'runs')))
    print('RUN='+str(run),flush=True);print('PREPARING_VERIFIED_150MHZ_ACTIVITY',flush=True)
    vcd=run/'case01.vcd'
    with gzip.open(wave,'rb') as src,vcd.open('wb') as dst:shutil.copyfileobj(src,dst)
    s=(old/'map_check.tcl').read_text()
    # Validate existing netlist/libraries against the prior successful power-preparation receipt.
    prep,pd=latest('soc-power-*/result.json','POWER_NETLIST_READY_ACTIVITY_REQUIRED')
    frozen=json.loads((prep.parent/'input-sha256.json').read_text())
    for name,want in frozen.items():
        p=Path(name)
        if p.suffix=='.db' or p.name in {'kwt_dma_soc_top_mapped.v','mapped.sdc'}:
            if hashlib.sha256(p.read_bytes()).hexdigest()!=want:raise ValueError('Mapped input changed: '+name)
            if str(p) not in s:raise ValueError('Mapping script/input mismatch: '+name)
    s,n=re.subn(r'read_vcd -strip_path tb_top/u_e203_soc_top \{[^}]+\}',lambda m:'read_vcd -strip_path tb_top/u_e203_soc_top {'+str(vcd)+'}',s)
    if n!=1:raise ValueError('Unexpected VCD command')
    for name in ['read_vcd_help.txt','switching_activity.rpt','check_power.rpt']:
        s=s.replace(str(old/name),str(run/name))
    anchor='puts "MAP_CHECK VCD_READ_COMPLETE"'
    extra='\n'.join(['puts "POWER150 UPDATE_START"',
      'redirect -file {'+str(run/'update_power.rpt')+'} {update_power}',
      'redirect -file {'+str(run/'power_total.rpt')+'} {report_power}',
      'redirect -file {'+str(run/'power_hierarchy.rpt')+'} {report_power -hierarchy}',
      'puts "POWER150 ESTIMATE_AND_HIERARCHY_READY"'])
    if s.count(anchor)!=1:raise ValueError('Mapping anchor changed')
    s=s.replace(anchor,anchor+'\n'+extra)
    script=run/'power.tcl';script.write_text(s)
    print('PRIMETIME_RUNNING; estimate pending coverage and SRAM review',flush=True)
    env=dict(os.environ);env['SYNOPSYS_LC_ROOT']='/eda/synopsys/lib_compiler/lib_compiler_2022.03-SP5'
    tool=shutil.which('pt_shell')
    if not tool:raise ValueError('pt_shell missing')
    with (run/'pt.log').open('w') as f:p=subprocess.run([tool,'-f',str(script)],cwd=str(run),env=env,stdout=f,stderr=subprocess.STDOUT)
    errors=[];warnings=[]
    for name in ['pt.log','update_power.rpt','power_total.rpt','power_hierarchy.rpt','switching_activity.rpt','check_power.rpt']:
        f=run/name
        if f.exists():
            for l in f.read_text(errors='replace').splitlines():
                if re.match(r'\s*(Error:|Fatal:)',l):errors.append(l)
                if re.match(r'\s*Warning:',l):warnings.append(l)
    print('ERROR_COUNT='+str(len(errors))+' WARNING_COUNT='+str(len(warnings)))
    for l in list(dict.fromkeys(errors))[:4]:print(l)
    for l in list(dict.fromkeys(warnings))[:4]:print(l[:260])
    for name,limit in [('power_total.rpt',35),('switching_activity.rpt',28)]:
        f=run/name
        if f.exists():print('REPORT='+name+'\n'+'\n'.join([l for l in f.read_text(errors='replace').splitlines() if l.strip()][:limit]))
    result={'status':'POWER_ESTIMATE_REVIEW_REQUIRED' if p.returncode==0 and not errors else 'POWER_RUN_FAILED',
      'suite_report':str(receipt),'task':1,'task_timing':task['timing'],'source_vcd':str(wave),'errors':errors,'warnings':warnings,
      'final_power_accepted':False,'all12_power_done':False,
      'limitations':['Raw recorded VCD envelope; exact measurement-window crop still to verify','RTL-to-netlist and TCM mapping/coverage pending','SRAM models and power-table range warnings pending']}
    (run/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    print('RESULT='+result['status']);print('REPORT_DIR='+str(run))
if __name__=='__main__':
    try:main()
    except Exception as e:raise SystemExit('STOP: '+str(e))
