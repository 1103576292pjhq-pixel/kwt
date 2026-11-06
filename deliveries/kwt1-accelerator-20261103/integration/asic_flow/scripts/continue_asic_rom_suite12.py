from pathlib import Path
import sys,json,hashlib,subprocess,shutil,gzip
sys.dont_write_bytecode=True

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
R=DC/'runs/asic-rom-handshake-zsdiy719'
ENV=ROOT/'test_env'
F=ROOT/'real12_verify_01/kwt-real12-validation/fixtures'
sys.path.insert(0,str(ENV))
import run_suite as suite

def need(ok,msg):
    if not ok:
        raise RuntimeError(msg)

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

original=json.loads((R/'original-source-sha256.json').read_text())
pilot=json.loads((R/'result.json').read_text())
fixed=Path(pilot['experimental_rom_interface'])

def check_sources():
    need(all(Path(p).is_file() and sha(Path(p))==h
             for p,h in original.items()),'Original source changed')
    need(sha(fixed)==pilot['experimental_sha256'],
         'Experimental ROM interface changed')

check_sources()
need((R/'case01/audit-report.json').is_file(),'Task1 audit missing')
need(not (R/'suite12-progress.json').exists(),
     'Continuation already exists; inspect its status before restarting')

tasks=suite.prepare_suite(
    F,R/'suite12-data',json.loads((ENV/'suite-identity.json').read_text()))
need(len(tasks)==12,'Expected twelve tasks')

rom=R/'case01/ROM1KX32_verilog.rcf'
words=[int(x,2) for x in rom.read_text().split()]
need(words==[0x7ffff297,0x00028067]+[0]*1022,
     'Unexpected boot ROM contents')

command=json.loads((R/'sim-command.json').read_text())
results=[]
receipt={
    'status':'RUNNING',
    'tasks':results,
    'full12_passed':False,
    'power_evaluated':False,
    'mapped_equivalence_proven':False,
    'experimental_rom_sha256':sha(fixed),
    'boot_rom_sha256':sha(rom)
}

def save():
    (R/'suite12-progress.json').write_text(
        json.dumps(receipt,indent=2)+'\n')

save()
try:
    for d in tasks:
        case=d['case']
        w=R/('case%02d'%case)
        if case!=1:
            w.mkdir(exist_ok=False)
            shutil.copyfile(rom,w/rom.name)
            cmd=[]
            for arg in command:
                if arg.startswith('+real_data='):
                    arg='+real_data='+str(R/'suite12-data'/('case%d'%case))
                elif arg.startswith('+layer='):
                    arg='+layer='+str(d['hardware_layer'])
                cmd.append(arg)
            (w/'commands.json').write_text(json.dumps(cmd,indent=2))
            print('TASK_START %d/12'%case,flush=True)
            with (w/'run.log').open('w') as out:
                p=subprocess.run(
                    cmd,cwd=str(w),stdout=out,
                    stderr=subprocess.STDOUT,timeout=1800)
            need(p.returncode==0,'Simulator exit failure: '+str(w))
        log=(w/'run.log').read_text(errors='replace')
        need('Fatal:' not in log and 'Error-' not in log,
             'Simulation error: '+str(w/'run.log'))
        a=suite.audit(
            log,d['gold'],F/('case%d-ref.f32'%case),w/'shared-y.txt')
        need(abs(a['timing']['period_ps']-6666.666)<0.01,
             'Unexpected clock period')
        vcd=w/'activity.vcd'
        need(vcd.is_file() and vcd.stat().st_size>0,'Missing activity')
        print('TASK_VERIFIED %d/12; COMPRESSING'%case,flush=True)
        packed=w/'activity.vcd.gz'
        need(not packed.exists(),'Compressed activity already exists')
        with vcd.open('rb') as src:
            with gzip.open(packed,'wb',compresslevel=1) as dst:
                shutil.copyfileobj(src,dst)
        need(packed.stat().st_size>0,'Empty compressed activity')
        vcd.unlink()
        a.update(case=case,hardware_layer=d['hardware_layer'],
                 activity=str(packed),activity_sha256=sha(packed))
        (w/'audit-report.json').write_text(json.dumps(a,indent=2)+'\n')
        results.append(a)
        check_sources()
        save()
        print('TASK_PASS %d/12 cycles=%.6f NRMSE=%.8f%%'%(
            case,a['timing']['cycles'],
            a['correctness']['nrmse_percent']),flush=True)

    receipt.update(
        status='PASS_ASIC_ROMFIX_SUITE12_FUNCTIONAL',
        full12_passed=True,
        total_cycles=sum(x['timing']['cycles'] for x in results),
        total_elapsed_ps=sum(x['timing']['elapsed_ps'] for x in results),
        max_nrmse_percent=max(
            x['correctness']['nrmse_percent'] for x in results))
    receipt['simulated_tasks_per_second']=(
        12e12/receipt['total_elapsed_ps'])
    (R/'suite12-report.json').write_text(
        json.dumps(receipt,indent=2)+'\n')
except Exception as e:
    receipt.update(status='STOPPED',error=str(e))
    print('STOP: '+str(e),flush=True)
finally:
    save()
    print('RESULT='+receipt['status'],flush=True)
    print('REPORT_DIR='+str(R),flush=True)
