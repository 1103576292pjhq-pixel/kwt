from pathlib import Path
import collections,json,re

D=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc/runs')
P=D/'power-asic-romfix-task01-ecei0biq'
M=max(D.glob('asic-sram-output-activity-*/measured-q.json'),
      key=lambda p:p.stat().st_mtime)
report=json.loads(M.read_text())
targets=[m for m in report['matched'] if 'dtcm' in m['instance']]
assert len(targets)==32, 'Expected 32 DTCM macros'

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

signals=[]
for m in targets:
    p=ports[m['scope']]
    assert all(k in p and p[k][1]==1 for k in ['CLK','CEN','GWEN']), m['scope']
    signals.append((m['instance'],p['CLK'][0],p['CEN'][0],p['GWEN'][0]))

ts=re.search(r'\$timescale\s*(\d+)\s*(fs|ps|ns|us|ms|s)\s*\$end',
             ''.join(header))
assert ts, 'Missing VCD timescale'
scale=int(ts.group(1))*dict(fs=.001,ps=1,ns=1000,
                          us=1e6,ms=1e9,s=1e12)[ts.group(2)]
assert abs(scale-report['ps_per_tick'])<1e-12
start=report['window_start_ticks']
end=report['window_end_ticks']
codes={c for row in signals for c in row[1:]}
value={c:'x' for c in codes}
before=dict(value)
counts={row[0]:collections.Counter() for row in signals}
now=0

def inspect():
    if not start<=now<end:
        return
    for name,clk,cen,gwen in signals:
        if before[clk]=='0' and value[clk]=='1':
            c=counts[name]
            c['clock_edges']+=1
            # 控制在同一时间戳发生变化时，不猜测采样顺序。
            if before[cen]!=value[cen]:
                c['ambiguous_control_edges']+=1
            elif before[cen]=='1':
                c['disabled_edges']+=1
            elif before[cen]!='0':
                c['unknown_enable_edges']+=1
            elif before[gwen]!=value[gwen]:
                c['ambiguous_control_edges']+=1
            elif before[gwen]=='1':
                c['read_edges']+=1
            elif before[gwen]=='0':
                c['write_edges']+=1
            else:
                c['unknown_write_mode_edges']+=1

print('SCANNING_DTCM_ENABLES',flush=True)
for line in f:
    line=line.strip()
    if not line:
        continue
    if line[0]=='#':
        inspect()
        now=int(line[1:])
        if now>=end:
            break
        before=dict(value)
    elif line[0] in '01xXzZ':
        code=line[1:]
        if code in codes:
            value[code]=line[0].lower()
    elif line[0] in 'bB':
        a=line.split()
        if len(a)==2 and a[1] in codes:
            value[a[1]]=a[0][1:].lower()
else:
    inspect()
f.close()

total=collections.Counter()
for c in counts.values():
    total.update(c)
out=M.parent/'dtcm-enable-audit.json'
out.write_text(json.dumps({
    'source_vcd':str(P/'case01.vcd'),
    'counts_by_macro':counts,
    'total':total
},indent=2))
print('DTCM_MACROS='+str(len(signals)))
for k,v in sorted(total.items()):
    print(k.upper()+'='+str(v))
print('REPORT='+str(out))
