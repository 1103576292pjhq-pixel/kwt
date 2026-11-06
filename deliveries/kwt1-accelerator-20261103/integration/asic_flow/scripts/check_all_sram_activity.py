from pathlib import Path
import collections,json,re,tempfile

D=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc/runs')
P=D/'power-asic-romfix-task01-ecei0biq'
M=max(D.glob('asic-sram-output-activity-*/measured-q.json'),
      key=lambda p:p.stat().st_mtime)
report=json.loads(M.read_text())
targets=report['matched']
assert len(targets)==152, 'Expected 152 SRAM macros'

scope=[]
ports=collections.defaultdict(dict)
header=[]
f=(P/'case01.vcd').open()
for line in f:
    header.append(line)
    a=line.split()
    if not a:
        continue
    if a[0]=='$enddefinitions':
        break
    if a[0]=='$scope':
        scope.append(a[2])
    elif a[0]=='$upscope':
        scope.pop()
    elif a[0]=='$var':
        ports['/'.join(scope)][a[4]]=(a[3],int(a[2]))

ts=re.search(r'\$timescale\s*(\d+)\s*(fs|ps|ns|us|ms|s)\s*\$end',
             ''.join(header))
assert ts, 'Missing timescale'
scale=int(ts.group(1))*dict(
    fs=.001,ps=1,ns=1000,us=1e6,ms=1e9,s=1e12)[ts.group(2)]
assert abs(scale-report['ps_per_tick'])<1e-12
start=report['window_start_ticks']
end=report['window_end_ticks']

macros=[]
byclock=collections.defaultdict(list)
widths={}
for m in targets:
    p=ports[m['scope']]
    assert all(k in p and p[k][1]==1
               for k in ['CLK','CEN','GWEN']), m['scope']
    assert 'Q' in p and p['Q'][1]==16, m['scope']
    row={
        'instance':m['instance'],
        'scope':m['scope'],
        'pins':{k:p[k][0] for k in ['CLK','CEN','GWEN','Q']},
        'counts':collections.Counter(),
        'pending_read':False
    }
    macros.append(row)
    byclock[p['CLK'][0]].append(row)
    for k in ['CLK','CEN','GWEN','Q']:
        code,width=p[k]
        assert code not in widths or widths[code]==width
        widths[code]=width

values={code:'x'*width for code,width in widths.items()}
changes={}
now=0

def inspect():
    old=dict(values)
    values.update(changes)
    if not start<=now<end:
        return
    for clk in changes.keys() & byclock.keys():
        if old[clk]==values[clk]:
            continue
        for m in byclock[clk]:
            p=m['pins']
            c=m['counts']
            if old[clk]=='0' and values[clk]=='1':
                c['clock_rises']+=1
                if old[p['CEN']]!=values[p['CEN']]:
                    c['ambiguous_control_edges']+=1
                elif old[p['CEN']]=='1':
                    c['disabled_edges']+=1
                elif old[p['CEN']]!='0':
                    c['unknown_enable_edges']+=1
                elif old[p['GWEN']]!=values[p['GWEN']]:
                    c['ambiguous_control_edges']+=1
                elif old[p['GWEN']]=='1':
                    c['read_edges']+=1
                    m['pending_read']=True
                elif old[p['GWEN']]=='0':
                    c['write_edges']+=1
                else:
                    c['unknown_write_mode_edges']+=1
            elif old[clk]=='1' and values[clk]=='0':
                if m['pending_read']:
                    q=old[p['Q']]
                    key=('read_Q_known' if set(q)<=set('01')
                         else 'read_Q_contains_XZ')
                    c[key]+=1
                    m['pending_read']=False

print('SCANNING_152_SRAMS; NO_SIMULATION_RERUN',flush=True)
for line in f:
    line=line.strip()
    if not line:
        continue
    if line[0]=='#':
        inspect()
        now=int(line[1:])
        changes={}
        if now>=end:
            break
    elif line[0] in '01xXzZ':
        code=line[1:]
        if code in widths:
            changes[code]=line[0].lower()*widths[code]
    elif line[0] in 'bB':
        a=line.split()
        if len(a)==2 and a[1] in widths:
            code=a[1]
            v=a[0][1:].lower()
            v=v.rjust(widths[code],v[0] if v[0] in 'xz' else '0')
            assert len(v)==widths[code], 'Unexpected vector width'
            changes[code]=v
else:
    inspect()
f.close()

def group(name):
    if 'itcm' in name:
        return 'ITCM'
    if 'dtcm' in name:
        return 'DTCM'
    if 'u_shared_sram/' in name:
        return 'SHARED'
    return 'ACCEL'

totals=collections.defaultdict(collections.Counter)
for m in macros:
    c=m['counts']
    g=totals[group(m['instance'])]
    g.update(c)
    g['macros']+=1
    g['macros_without_clock_rise']+=int(c['clock_rises']==0)
    if m['pending_read']:
        g['read_without_sample_before_window_end']+=1

out=Path(tempfile.mkdtemp(prefix='all-sram-activity-',dir=str(D)))
(out/'report.json').write_text(json.dumps({
    'source_measurement':str(M),
    'source_vcd':str(P/'case01.vcd'),
    'window_ticks':[start,end],
    'read_sample_method':'Q immediately before following falling clock edge',
    'counts_by_group':totals,
    'macros':macros
},indent=2))

for name,g in sorted(totals.items()):
    print(name+' '+json.dumps(dict(g),sort_keys=True))
print('REPORT='+str(out/'report.json'))
