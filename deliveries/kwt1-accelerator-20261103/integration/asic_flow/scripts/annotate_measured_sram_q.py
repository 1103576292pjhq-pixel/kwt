#!/usr/bin/env python3
"""Measure SRAM Q activity in exact task window; annotate only fully known bits.
No forced DUT values, invented toggles, design edits or library edits.
"""
import collections,json,os,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
def norm(s):return re.sub(r'[^A-Za-z0-9]','',s)
def latest(pat,status):
    for p in sorted((DC/'runs').glob(pat),key=lambda p:p.stat().st_mtime,reverse=True):
        d=json.loads(p.read_text())
        if d.get('status')==status:return p,d
    raise ValueError('Missing '+status)
def main():
    source,rec=latest('memory-vcd-name-map-*/result.json','MEMORY_NAME_MAP_CANDIDATES_READY')
    power=Path(rec['source_power_run']);vcd=Path(rec['source_vcd'])
    pr=json.loads((power/'result.json').read_text());timing=pr['task_timing']
    run=Path(tempfile.mkdtemp(prefix='sram-output-activity-',dir=str(DC/'runs')))
    print('RUN='+str(run),flush=True)
    stack=[];scopes={};header=[]
    stream=vcd.open(errors='replace')
    for line in stream:
        header.append(line);a=line.split()
        if a[:1]==['$scope']:stack.append(a[2]);scopes.setdefault('/'.join(stack),[])
        elif a[:1]==['$upscope']:stack.pop()
        elif a[:1]==['$var']:scopes['/'.join(stack)].append((a[4],int(a[2]),a[3],' '.join(a[5:-1])))
        if '$enddefinitions' in line:break
    ts=re.search(r'\$timescale\s*(\d+)\s*(fs|ps|ns|us|ms|s)\s*\$end',''.join(header))
    if not ts:raise ValueError('VCD timescale missing')
    ps_per_tick=int(ts.group(1))*{'fs':.001,'ps':1,'ns':1000,'us':1e6,'ms':1e9,'s':1e12}[ts.group(2)]
    start=round(timing['start_cycle']*timing['period_ps']/ps_per_tick)
    end=round(timing['end_cycle']*timing['period_ps']/ps_per_tick);duration=end-start
    if duration<=0:raise ValueError('Bad task interval')
    bykey=collections.defaultdict(list);prefix='tb_top/u_e203_soc_top/'
    for path in scopes:
        if path.startswith(prefix):bykey[norm(path[len(prefix):])].append(path)
    matched=[];unmatched=[];signals={}
    for m in rec['unmatched']+rec['matched']:
        inst=m['instance'];ref=m['reference']
        if not (inst.startswith('u_shared_sram/') or inst.startswith('u_kwt_accelerator/')):continue
        # Evidence shows simulation SRAM wrapper exposes Q one u0 above mapped macro.
        if not inst.endswith('/u0/u0'):raise ValueError('Unexpected macro suffix '+inst)
        paths=bykey[norm(inst[:-3])]
        if len(paths)!=1:unmatched.append(inst);continue
        ports=[v for v in scopes[paths[0]] if v[0]=='Q']
        if len(ports)!=1 or ports[0][1]!=16 or ports[0][3]!='[15:0]':raise ValueError('Q width/range mismatch '+inst)
        _,width,code,_=ports[0]
        matched.append({'instance':inst,'ref':ref,'scope':paths[0],'code':code})
        signals.setdefault(code,{'value':'x'*16,'last':start,'high':[0]*16,'unknown':[0]*16,'toggles':[0]*16})
    if len(matched)!=88:raise ValueError('Expected 88 shared/accelerator SRAMs, found '+str(len(matched))+' unmatched='+str(unmatched[:3]))
    print('MATCHED_SRAMS=88; SCANNING_TASK_WINDOW_FOR_Q_ACTIVITY',flush=True)
    now=0
    def advance(d,t):
        t=max(start,min(end,t));delta=t-d['last']
        if delta>0:
            for i,c in enumerate(d['value']):
                if c=='1':d['high'][i]+=delta
                elif c not in '01':d['unknown'][i]+=delta
            d['last']=t
    for line in stream:
        line=line.strip()
        if not line:continue
        if line[0]=='#':
            now=int(line[1:])
            if now>end:break
        elif line[0] in 'bB':
            parts=line.split()
            if len(parts)!=2 or parts[1] not in signals:continue
            value=parts[0][1:].lower();d=signals[parts[1]]
            value=value.rjust(16,value[0] if value[0] in 'xz' else '0')
            if len(value)!=16:raise ValueError('Unexpected vector width')
            if now>=start:
                advance(d,now)
                if now>start and now<end:
                    for i,(a,b) in enumerate(zip(d['value'],value)):
                        if a in '01' and b in '01' and a!=b:d['toggles'][i]+=1
            d['value']=value
    stream.close()
    for d in signals.values():advance(d,end)
    duration_ns=duration*ps_per_tick/1000
    tcl=['# Measured Q activity from actual VCD; only bits known for entire task window.']
    bits=[];unknown=0
    for m in matched:
        d=signals[m['code']]
        for bit in range(16):
            i=15-bit;pin=m['instance']+'/Q['+str(bit)+']'
            row={'pin':pin,'toggles':d['toggles'][i],'high_fraction':d['high'][i]/duration,'unknown_fraction':d['unknown'][i]/duration}
            bits.append(row)
            if d['unknown'][i]:unknown+=1;continue
            # PT time unit is ns; explicit period=1 keeps toggle rate per ns.
            tcl+=['set qp [get_pins -quiet {'+pin+'}]',
              'if {[sizeof_collection $qp] != 1} {error {Missing unique mapped SRAM Q pin: '+pin+'}}',
              'set_switching_activity -period 1 -toggle_rate %.15g -static_probability %.15g $qp'%(d['toggles'][i]/duration_ns,d['high'][i]/duration)]
    annotation=run/'measured_q_activity.tcl';annotation.write_text('\n'.join(tcl)+'\n')
    (run/'measured-q.json').write_text(json.dumps({'window_start_ticks':start,'window_end_ticks':end,'ps_per_tick':ps_per_tick,'duration_ns':duration_ns,'matched':matched,'bits':bits},indent=2)+'\n')
    print('Q_BITS_MEASURED=1408 FULLY_KNOWN_BITS='+str(1408-unknown)+' UNKNOWN_BITS_NOT_ANNOTATED='+str(unknown),flush=True)
    script=(power/'power.tcl').read_text()
    for name in ['read_vcd_help.txt','update_power.rpt','power_total.rpt','power_hierarchy.rpt','switching_activity.rpt','check_power.rpt']:
        script=script.replace(str(power/name),str(run/name))
    anchor='puts "POWER150 UPDATE_START"'
    if script.count(anchor)!=1:raise ValueError('Power script marker changed')
    script=script.replace(anchor,'source {'+str(annotation)+'}\n'+anchor)
    script=script.replace('{report_power}','{report_power -verbose}')
    ptfile=run/'power_with_measured_q.tcl';ptfile.write_text(script)
    tool=shutil.which('pt_shell')
    if not tool:raise ValueError('pt_shell missing')
    env=dict(os.environ);env['SYNOPSYS_LC_ROOT']='/eda/synopsys/lib_compiler/lib_compiler_2022.03-SP5'
    print('RECALCULATING_WITH_MEASURED_Q; TCM_STILL_PENDING',flush=True)
    with (run/'pt.log').open('w') as f:p=subprocess.run([tool,'-f',str(ptfile)],cwd=str(run),env=env,stdout=f,stderr=subprocess.STDOUT)
    errors=[]
    for name in ['pt.log','update_power.rpt','power_total.rpt','switching_activity.rpt']:
        f=run/name
        if f.exists():errors.extend(l for l in f.read_text(errors='replace').splitlines() if re.match(r'\s*(Error:|Fatal:)',l))
    for l in errors[:4]:print(l)
    for name in ['power_total.rpt','switching_activity.rpt']:
        f=run/name
        if not f.exists():continue
        lines=f.read_text(errors='replace').splitlines();print('REPORT='+name)
        if name=='power_total.rpt':
            for l in lines:
                if re.search(r'Power Units|Total Power|Cell Internal Power|Cell Leakage Power|Net Switching Power',l):print(l)
        else:print('\n'.join([l for l in lines if l.strip()][:28]))
    status='MEASURED_SRAM_Q_REVIEW_REQUIRED' if p.returncode==0 and not errors else 'MEASURED_SRAM_Q_RUN_FAILED'
    (run/'result.json').write_text(json.dumps({'status':status,'source_power_run':str(power),'annotated_bits':1408-unknown,'unknown_bits':unknown,'errors':errors,'final_power_accepted':False,'TCM_activity_complete':False},indent=2)+'\n')
    print('RESULT='+status)
if __name__=='__main__':
    try:main()
    except Exception as e:raise SystemExit('STOP: '+str(e))
