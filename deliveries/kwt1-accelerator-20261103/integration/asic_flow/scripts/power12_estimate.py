from pathlib import Path
from decimal import Decimal
import contextlib,csv,gzip,hashlib,json,os,re,shutil,subprocess,tempfile

D=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
SIM=D/'runs/asic-rom-handshake-zsdiy719'
SYN=D/'runs/soc-romfix-synth-jlkfngx9'
BASE=D/'runs/power-asic-romfix-task01-ecei0biq'
HELPER=D/'scripts/annotate_asic_sram_q.py'

def need(ok,msg):
    if not ok: raise RuntimeError(msg)
def save(p,obj): p.write_text(json.dumps(obj,indent=2)+'\n')
def sha(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for b in iter(lambda:f.read(1048576),b''): h.update(b)
    return h.hexdigest()

def crop(src,dst,timing):
    with gzip.open(src,'rt') as f,dst.open('w') as out:
        header=[]
        for line in f:
            header.append(line)
            if '$enddefinitions' in line: break
        text=''.join(header)
        m=re.search(r'\$timescale\s*(\d+)\s*(fs|ps|ns|us|ms|s)\s*\$end',text)
        need(m is not None,'VCD timescale missing')
        scale=Decimal(m[1])*{'fs':Decimal('.001'),'ps':Decimal(1),'ns':Decimal(1000),'us':Decimal(10)**6,'ms':Decimal(10)**9,'s':Decimal(10)**12}[m[2]]
        period=Decimal(str(timing['period_ps']))
        start=round(Decimal(str(timing['start_cycle']))*period/scale)
        end=round(Decimal(str(timing['end_cycle']))*period/scale)
        need(end>start,'Invalid window')
        duration=end-start
        need(abs(Decimal(duration)*scale-Decimal(str(timing['elapsed_ps'])))<=2*scale,'Window mismatch')
        out.write(text)
        state={};now=0;started=False;last=-1
        for line in f:
            line=line.strip()
            if not line: continue
            if line[0]=='#':
                now=int(line[1:]);last=now
                if now>start and not started:
                    need(bool(state),'No initial VCD state')
                    out.write('#0\n$dumpvars\n'+'\n'.join(state.values())+'\n$end\n')
                    started=True
                if now>=end: break
                if started: out.write('#'+str(now-start)+'\n')
            elif line[0] in '01xXzZbBrRsS':
                a=line.split()
                code=a[1] if line[0] in 'bBrRsS' else line[1:]
                if now<=start: state[code]=line
                elif started: out.write(line+'\n')
        need(started and last>=end,'VCD does not cover complete task window')
        out.write('#'+str(duration)+'\n')
    return {'start_ticks':start,'end_ticks':end,'ps_per_tick':float(scale),'duration_s':float(Decimal(duration)*scale/Decimal(10)**12)}

def power_values(path):
    text=path.read_text()
    for label in ['Dynamic','Leakage']:
        need(re.search(label+r' Power Units\s*=\s*1(?:\.0+)?\s+W\b',text),'Power unit not verified: '+label)
    def number(label):
        m=re.search(r'^\s*'+label+r'\s*=\s*([-+0-9.eE]+)',text,re.M)
        need(m is not None,'Power value missing: '+label)
        return float(m[1])
    return {'power_W':number('Total Power'),
            'dynamic_W':number('Cell Internal Power')+number('Net Switching Power'),
            'leakage_W':number('Cell Leakage Power')}

def sensitivity(source,destination,rate):
    destination.mkdir()
    text=(source/'power_with_measured_q.tcl').read_text()
    for n in ['read_vcd_help.txt','update_power.rpt','power_total.rpt','power_hierarchy.rpt','switching_activity.rpt','check_power.rpt','power_verbose.rpt','default_activity.rpt','check_power_verbose.rpt','units.rpt']:
        text=text.replace(str(source/n),str(destination/n))
    extra=r'''
set sens_count 0
set sens_file [open {DEFAULT_REPORT} r]
while {[gets $sens_file sens_line] >= 0} {
    if {![regexp {^\s*(\S+)\s*$} $sens_line -> sens_name]} {continue}
    if {[string first / $sens_name] < 0} {continue}
    set sens_net [get_nets -quiet [list $sens_name]]
    if {[sizeof_collection $sens_net] != 1} {continue}
    if {[get_object_name $sens_net] ne $sens_name} {continue}
    set_switching_activity -period 1 -toggle_rate RATE -static_probability 0.5 $sens_net
    incr sens_count
}
close $sens_file
puts "SENS_DEFAULT_NETS=$sens_count"
if {$sens_count == 0} {error {No default nets selected for sensitivity test}}
'''.replace('DEFAULT_REPORT',str(source/'default_activity.rpt')).replace('RATE',str(rate))
    marker='puts "POWER150 UPDATE_START"'
    need(text.count(marker)==1,'Sensitivity marker mismatch')
    script=destination/'power.tcl';script.write_text(text.replace(marker,extra+'\n'+marker))
    with (destination/'pt.log').open('w') as out:
        p=subprocess.run(['pt_shell','-f',str(script)],cwd=str(destination),stdout=out,stderr=subprocess.STDOUT)
    log=(destination/'pt.log').read_text(errors='replace')
    need(p.returncode==0 and not re.search(r'^\s*(Error:|Fatal:)',log,re.M),'Sensitivity run failed')
    m=re.search(r'SENS_DEFAULT_NETS=(\d+)',log);need(m is not None,'No sensitivity count')
    return dict(power_values(destination/'power_total.rpt'),annotated_default_nets=int(m[1]),toggle_rate_per_ns=rate,static_probability=.5,scope='task1 listed default nets; scenarios, not rigorous bounds')

def main():
    os.environ['SYNOPSYS_LC_ROOT']='/eda/synopsys/lib_compiler/lib_compiler_2022.03-SP5'
    need(shutil.which('pt_shell'),'pt_shell missing')
    suite=json.loads((SIM/'suite12-report.json').read_text())
    syn=json.loads((SYN/'result.json').read_text())
    need(suite['full12_passed'] and suite['experimental_rom_sha256']==syn['rom_interface_sha256'],'Design version mismatch')
    before=json.loads((SYN/'input-sha256.json').read_text())
    before.update({str(p):sha(p) for p in [SYN/'synth/kwt_dma_soc_top_mapped.v',SYN/'synth/mapped.sdc',HELPER,BASE/'power.tcl']})
    need(all(Path(p).is_file() and sha(Path(p))==h for p,h in before.items()),'Frozen input changed')
    source=HELPER.read_text()
    need(source.count('def main():')==1,'Helper version mismatch')
    source=source.replace('def main():','def main(config):')
    a=source.index('    power=DC/');b=source.index('    candidates=sorted(',a)
    source=source[:a]+"    power=Path(config['power'])\n    vcd=power/'case01.vcd'\n    timing=config['timing']\n"+source[b:]
    marker="    print('RESULT='+status)"
    need(source.count(marker)==1,'Helper return marker mismatch')
    source=source.replace(marker,marker+'\n    return run')
    ns={'__name__':'batch_helper'};exec(compile(source,'batch-helper','exec'),ns)
    run=Path(tempfile.mkdtemp(prefix='asic-power12-estimate-',dir=str(D/'runs')))
    (run/'activity_helper_used.py').write_text(source)
    save(run/'input-sha256.json',before)
    receipt={'status':'RUNNING','final_accepted':False,'tasks':[],
             'limitations':['Default activity and X/Z remain under review','Electrical-range warnings require review','Task1 sensitivity scenarios do not bound all tasks','Post-synthesis functional consistency remains pending']}
    save(run/'result.json',receipt)
    print('RUN='+str(run),flush=True)
    try:
        for case in range(1,13):
            w=run/('case%02d'%case);w.mkdir()
            task=json.loads((SIM/('case%02d'%case)/'audit-report.json').read_text())
            packed=Path(task['activity'])
            need(sha(packed)==task['activity_sha256'],'Activity hash mismatch')
            print('TASK %d/12: CROP_AND_POWER'%case,flush=True)
            window=crop(packed,w/'case01.vcd',task['timing']);save(w/'window.json',window)
            template=(BASE/'power.tcl').read_text().replace(str(BASE),str(w))
            need(str(SYN/'synth/kwt_dma_soc_top_mapped.v') in template,'Wrong netlist')
            need(str(SYN/'synth/mapped.sdc') in template,'Wrong SDC')
            (w/'power.tcl').write_text(template)
            timing=dict(task['timing']);timing.update(start_cycle=0,end_cycle=(window['end_ticks']-window['start_ticks'])*window['ps_per_tick']/timing['period_ps'])
            with (w/'activity-driver.log').open('w') as log,contextlib.redirect_stdout(log):
                result=ns['main']({'power':str(w),'timing':timing})
            info=json.loads((result/'result.json').read_text())
            need(info['status']=='MEASURED_SRAM_Q_REVIEW_REQUIRED','Power helper failed: '+str(result))
            ptlog=(result/'pt.log').read_text(errors='replace')
            need('MAP_CHECK COVERAGE_REPORT_READY' in ptlog,'Power reports incomplete')
            row=dict(case=case,duration_s=window['duration_s'],report_dir=str(result),
                     annotated_Q_bits=info['annotated_bits'],unknown_Q_bits=info['unknown_bits'],
                     warning_count=len(re.findall(r'^\s*Warning:',ptlog,re.M)),**power_values(result/'power_total.rpt'))
            row['energy_mJ']=row['power_W']*row['duration_s']*1000
            receipt['tasks'].append(row);save(run/'result.json',receipt)
            print('TASK %d/12 ESTIMATE: %.4f mW, %.6f mJ'%(case,row['power_W']*1000,row['energy_mJ']),flush=True)
        need(all(Path(p).is_file() and sha(Path(p))==h for p,h in before.items()),'Inputs changed during run')
        rows=receipt['tasks'];seconds=sum(x['duration_s'] for x in rows)
        receipt.update(status='TWELVE_TASK_ESTIMATES_READY_NOT_SIGNOFF',total_time_s=seconds,
                       average_power_mW=sum(x['energy_mJ'] for x in rows)/seconds,
                       mean_task_energy_mJ=sum(x['energy_mJ'] for x in rows)/12)
        with (run/'metrics.csv').open('w',newline='') as f:
            writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
        save(run/'result.json',receipt)
        print('TASK1_DEFAULT_ACTIVITY_SENSITIVITY',flush=True)
        receipt['sensitivity']=[]
        for name,rate in [('zero_toggle',0),('two_toggles_per_cycle',.30000003)]:
            try:
                receipt['sensitivity'].append(dict(scenario=name,**sensitivity(Path(rows[0]['report_dir']),run/name,rate)))
            except Exception as e:
                receipt['sensitivity'].append({'scenario':name,'error':str(e)})
            save(run/'result.json',receipt)
        print('AVERAGE_POWER_mW=%.6f'%receipt['average_power_mW'])
        print('MEAN_TASK_ENERGY_mJ=%.9f'%receipt['mean_task_energy_mJ'])
        for x in receipt['sensitivity']:print('SENSITIVITY '+json.dumps(x))
    except Exception as e:
        receipt.update(status='STOPPED',error=str(e));print('STOP: '+str(e),flush=True)
    finally:
        save(run/'result.json',receipt)
        print('RESULT='+receipt['status']);print('REPORT='+str(run/'result.json'))

if __name__=='__main__': main()
