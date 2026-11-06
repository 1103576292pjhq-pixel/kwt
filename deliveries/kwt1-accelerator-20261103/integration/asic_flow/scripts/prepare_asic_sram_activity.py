from pathlib import Path
import os,sys

D=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
old=D/'scripts/annotate_measured_sram_q.py'
if not old.is_file():
    raise SystemExit('STOP: existing script missing: '+str(old))
s=old.read_text()

def replace(a,b):
    global s
    if s.count(a)!=1:
        raise SystemExit('STOP: script version mismatch: '+a[:90])
    s=s.replace(a,b)

start=s.index("    source,rec=latest(")
end=s.index("    run=Path(tempfile.mkdtemp(",start)
s=s[:start]+'''    power=DC/'runs/power-asic-romfix-task01-ecei0biq'
    vcd=power/'case01.vcd'
    sim=DC/'runs/asic-rom-handshake-zsdiy719'
    timing=json.loads((sim/'case01/audit-report.json').read_text())['timing']
    candidates=sorted(
        (DC/'runs').glob('asic-memory-paths-*/mapped-memory.tsv'),
        key=lambda p:p.stat().st_mtime,reverse=True)
    if not candidates:raise ValueError('Memory inventory missing')
    inventory=candidates[0]
    records=[]
    for line in inventory.read_text().splitlines():
        instance,reference=line.split()
        if reference.startswith('RAMSP'):
            records.append({'instance':instance,'reference':reference})
    counts=collections.Counter(x['reference'] for x in records)
    if counts!=dict(RAMSP128X16=16,RAMSP1024X16=8,RAMSP4096X16=128):
        raise ValueError('Unexpected SRAM inventory: '+str(counts))
    rec={'matched':records,'unmatched':[]}
    print('INVENTORY='+str(inventory),flush=True)
'''+s[end:]

replace(
    "        if not (inst.startswith('u_shared_sram/') or inst.startswith('u_kwt_accelerator/')):continue\n",
    ""
)
replace(
    "if len(matched)!=88:",
    "if len(matched)!=152:"
)
s=s.replace('Expected 88 shared/accelerator SRAMs',
            'Expected 152 ASIC SRAMs')
s=s.replace('MATCHED_SRAMS=88','MATCHED_SRAMS=152')
s=s.replace('1408','2432')
s=s.replace('TCM_STILL_PENDING','INCLUDING_ITCM_DTCM')
s=s.replace("prefix='sram-output-activity-'",
            "prefix='asic-sram-output-activity-'")

replace(
    "for name in ['read_vcd_help.txt','update_power.rpt','power_total.rpt','power_hierarchy.rpt','switching_activity.rpt','check_power.rpt']:",
    "for name in ['read_vcd_help.txt','update_power.rpt','power_total.rpt','power_hierarchy.rpt','switching_activity.rpt','check_power.rpt','power_verbose.rpt','default_activity.rpt','check_power_verbose.rpt','units.rpt']:"
)

compile(s,'asic-sram-activity','exec')
new=D/'scripts/annotate_asic_sram_q.py'
with new.open('x') as f:
    f.write(s)
print('CREATED='+str(new),flush=True)
os.execv(sys.executable,[sys.executable,'-u',str(new)])
