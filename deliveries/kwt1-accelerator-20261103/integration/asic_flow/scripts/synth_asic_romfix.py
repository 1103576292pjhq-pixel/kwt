from pathlib import Path
import hashlib,json,re,shutil,subprocess,tempfile

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
OLD=DC/'runs/soc-task-candidate-mzv1e12o'
SIM=DC/'runs/asic-rom-handshake-zsdiy719'

def need(ok,msg):
    if not ok:
        raise RuntimeError(msg)

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

suite=json.loads((SIM/'suite12-report.json').read_text())
need(suite.get('full12_passed') is True,'Twelve-task validation missing')
pilot=json.loads((SIM/'result.json').read_text())
fixed=Path(pilot['experimental_rom_interface'])
original=Path(pilot['original_rom_interface'])
need(sha(fixed)==suite['experimental_rom_sha256'],'ROM RTL changed')

before=json.loads((SIM/'original-source-sha256.json').read_text())
for p,h in json.loads((OLD/'input-sha256.json').read_text()).items():
    need(p not in before or before[p]==h,'Conflicting source identity: '+p)
    before[p]=h
for p in [fixed,OLD/'elab/read.tcl',OLD/'synth/compile.tcl',
          OLD/'synth/constraints.sdc',SIM/'suite12-report.json']:
    before[str(p)]=sha(p)

def check_inputs():
    need(all(Path(p).is_file() and sha(Path(p))==h
             for p,h in before.items()),'Frozen input changed')

check_inputs()
dc=shutil.which('dc_shell')
need(dc,'dc_shell is not in PATH')
run=Path(tempfile.mkdtemp(prefix='soc-romfix-synth-',dir=str(DC/'runs')))
for name in ['elab','synth','rtl','elab/work']:
    (run/name).mkdir(exist_ok=True)
newrtl=run/'rtl'/fixed.name
shutil.copyfile(fixed,newrtl)

read=(OLD/'elab/read.tcl').read_text()
needle='{'+str(original)+'}'
need(read.count(needle)==1,'Expected one original ROM interface in read.tcl')
read=read.replace(needle,'{'+str(newrtl)+'}')

def relocate(text):
    for folder in ['elab','synth']:
        text=text.replace(str(OLD/folder),str(run/folder))
    return text

read=relocate(read)
compile_text=relocate((OLD/'synth/compile.tcl').read_text())
anchor='if {![link]} {error {Post-compile link failed}}'
need(compile_text.count(anchor)==1,'Unexpected compile script')
compile_text=compile_text.replace(
    anchor,'catch {unset c}\n'+anchor)

(run/'elab/read.tcl').write_text(read)
(run/'synth/compile.tcl').write_text(compile_text)
(run/'synth/constraints.sdc').write_text(
    relocate((OLD/'synth/constraints.sdc').read_text()))
(run/'input-sha256.json').write_text(json.dumps(before,indent=2))
receipt={
    'status':'RUNNING',
    'simulation_run':str(SIM),
    'original_candidate':str(OLD),
    'rom_interface':str(newrtl),
    'rom_interface_sha256':sha(newrtl),
    'production_modified':False,
    'timing_accepted':False,
    'power_evaluated':False
}

def save():
    (run/'result.json').write_text(json.dumps(receipt,indent=2)+'\n')

def execute(folder,script,marker):
    log=run/folder/'dc.log'
    print('START '+folder+'; LOG='+str(log),flush=True)
    with log.open('w') as out:
        p=subprocess.run(
            [dc,'-no_gui','-f',str(run/folder/script)],
            cwd=str(run/folder),stdout=out,
            stderr=subprocess.STDOUT)
    text=log.read_text(errors='replace')
    errors=[x for x in text.splitlines()
            if re.match(r'^\s*(Error:|Fatal:)',x)]
    for x in errors[:5]:
        print(x,flush=True)
    need(p.returncode==0 and not errors and marker in text,
         'Stage failed; inspect '+str(log))
    print('PASS '+folder,flush=True)

save()
print('RUN='+str(run),flush=True)
try:
    execute('elab','read.tcl','SOC PASS_ANALYZE_ELABORATE_LINK_ONLY')
    check_inputs()
    execute('synth','compile.tcl','SOC_SYNTH REPORTS_READY_REVIEW_REQUIRED')
    check_inputs()
    need(sha(newrtl)==suite['experimental_rom_sha256'],
         'Staged ROM RTL changed')
    required=[
        'kwt_dma_soc_top_mapped.ddc','kwt_dma_soc_top_mapped.v',
        'mapped.sdc','area.rpt','timing_setup.rpt','timing_hold.rpt',
        'constraints_precise.rpt','check_timing_after.rpt'
    ]
    need(all((run/'synth'/n).is_file() and
             (run/'synth'/n).stat().st_size>0 for n in required),
         'Required output missing')
    for line in (run/'synth/area.rpt').read_text().splitlines():
        if 'Total cell area:' in line or 'Macro/Black Box area:' in line:
            print(line.strip())
    for name in ['timing_setup.rpt','timing_hold.rpt']:
        text=(run/'synth'/name).read_text()
        slacks=re.findall(
            r'slack\s*\(([^)]+)\)\s*([-+\d.]+)',text,re.I)
        print(name+': '+str(slacks[:1]))
    violations=[x.strip() for x in
        (run/'synth/constraints_precise.rpt').read_text().splitlines()
        if 'VIOLATED' in x]
    print('CONSTRAINT_VIOLATION_LINES='+str(len(violations)))
    for x in violations[:5]:
        print(x)
    receipt['status']='ROMFIX_SYNTH_REPORTS_READY_REVIEW_REQUIRED'
except Exception as e:
    receipt.update(status='STOPPED',error=str(e))
    print('STOP: '+str(e),flush=True)
finally:
    save()
    print('RESULT='+receipt['status'],flush=True)
    print('RUN='+str(run),flush=True)
