from pathlib import Path
import gzip,hashlib,json,re,shutil,subprocess,tempfile

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
OLD=DC/'runs/power-150mhz-task01-gthpdof6'
SYN=DC/'runs/soc-romfix-synth-jlkfngx9'
SIM=DC/'runs/asic-rom-handshake-zsdiy719'

def need(ok,msg):
    if not ok:
        raise RuntimeError(msg)

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

sr=json.loads((SYN/'result.json').read_text())
vr=json.loads((SIM/'suite12-report.json').read_text())
need(sr['status']=='ROMFIX_SYNTH_REPORTS_READY_REVIEW_REQUIRED',
     'Synthesis reports not ready')
need(vr.get('full12_passed') is True,'Twelve-task validation missing')
need(sr['rom_interface_sha256']==vr['experimental_rom_sha256'],
     'Simulation and synthesis ROM versions differ')

net=SYN/'synth/kwt_dma_soc_top_mapped.v'
sdc=SYN/'synth/mapped.sdc'
packed=SIM/'case01/activity.vcd.gz'
task=json.loads((SIM/'case01/audit-report.json').read_text())
need(sha(packed)==task['activity_sha256'],'Waveform hash mismatch')
pt=shutil.which('pt_shell')
need(pt,'pt_shell is not in PATH')

run=Path(tempfile.mkdtemp(
    prefix='power-asic-romfix-task01-',dir=str(DC/'runs')))
print('RUN='+str(run),flush=True)
print('DECOMPRESSING_TASK1_ACTIVITY',flush=True)
vcd=run/'case01.vcd'
with gzip.open(packed,'rb') as src:
    with vcd.open('wb') as dst:
        shutil.copyfileobj(src,dst)

text=(OLD/'power.tcl').read_text()
text=text.replace(str(OLD),str(run))

def replace_line(pattern,value):
    global text
    text,n=re.subn(pattern,lambda m:value,text,flags=re.M)
    need(n==1,'Unexpected power script: '+pattern)

replace_line(r'^\s*read_verilog[^\n]*$',
             'read_verilog {'+str(net)+'}')
replace_line(r'^\s*read_sdc[^\n]*$',
             'read_sdc {'+str(sdc)+'}')
replace_line(r'^\s*read_vcd[^\n]*$',
             'read_vcd -strip_path tb_top/u_e203_soc_top {'+str(vcd)+'}')

marker='puts "MAP_CHECK COVERAGE_REPORT_READY"'
need(text.count(marker)==1,'Missing final report marker')
extra='\n'.join([
    'redirect -file {'+str(run/'power_verbose.rpt')+
    '} {report_power -verbose}',
    'redirect -file {'+str(run/'default_activity.rpt')+
    '} {report_switching_activity -list_by_source default}',
    'redirect -file {'+str(run/'check_power_verbose.rpt')+
    '} {check_power -verbose}',
    'redirect -file {'+str(run/'units.rpt')+'} {report_units}'
])
text=text.replace(marker,extra+'\n'+marker)
script=run/'power.tcl'
script.write_text(text)

inputs={str(p):sha(p) for p in [net,sdc,packed,OLD/'power.tcl']}
(run/'input-sha256.json').write_text(json.dumps(inputs,indent=2))
receipt={
    'status':'RUNNING',
    'synthesis':str(SYN),
    'simulation':str(SIM),
    'case':1,
    'exact_window_verified':False,
    'activity_coverage_accepted':False,
    'final_power_accepted':False
}
def save():
    (run/'result.json').write_text(json.dumps(receipt,indent=2)+'\n')

save()
try:
    print('PT_START; DETAILS_IN_PT_LOG',flush=True)
    with (run/'pt.log').open('w') as out:
        p=subprocess.run(
            [pt,'-f',str(script)],cwd=str(run),
            stdout=out,stderr=subprocess.STDOUT)
    log=(run/'pt.log').read_text(errors='replace')
    errors=[x for x in log.splitlines()
            if re.match(r'^\s*(Error:|Fatal:)',x)]
    for x in errors[:5]:
        print(x)
    need(p.returncode==0 and not errors and marker[6:-1] in log,
         'Power run incomplete; inspect pt.log')
    need(all(sha(Path(p))==h for p,h in inputs.items()),
         'Input changed during analysis')
    for name in ['power_total.rpt','switching_activity.rpt']:
        print('\nREPORT: '+name)
        print('\n'.join((run/name).read_text().splitlines()[-22:]))
    receipt['status']='TASK1_POWER_REPORTS_READY_REVIEW_REQUIRED'
except Exception as e:
    receipt.update(status='STOPPED',error=str(e))
    print('STOP: '+str(e),flush=True)
finally:
    save()
    print('RESULT='+receipt['status'],flush=True)
    print('RUN='+str(run),flush=True)
