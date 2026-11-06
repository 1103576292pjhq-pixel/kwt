from pathlib import Path
import os,json,subprocess,tempfile

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
P=DC/'runs/power-asic-romfix-task01-ecei0biq'
R=Path(tempfile.mkdtemp(prefix='asic-memory-paths-',dir=str(DC/'runs')))
os.environ['SYNOPSYS_LC_ROOT']='/eda/synopsys/lib_compiler/lib_compiler_2022.03-SP5'

# 保存全部 Q 声明，包括完整路径、位宽和 VCD 标识符。
scope=[]
signals=[]
with (P/'case01.vcd').open() as f:
    for line in f:
        a=line.split()
        if not a:
            continue
        if a[0]=='$enddefinitions':
            break
        if a[0]=='$scope':
            scope.append(a[2])
        elif a[0]=='$upscope':
            scope.pop()
        elif a[0]=='$var' and a[4]=='Q':
            signals.append({
                'scope':'/'.join(scope),
                'width':int(a[2]),
                'code':a[3],
                'range':' '.join(a[5:-1])
            })
(R/'vcd-q-signals.json').write_text(json.dumps(signals,indent=2))

# 只复用网表、库和 SDC 读取部分，不读取大波形、不计算功耗。
text=(P/'power.tcl').read_text()
prefix=text.split('redirect -file',1)[0]
assert 'read_sdc' in prefix and 'read_vcd' not in prefix

tail=r'''
set f [open {OUTPUT} w]
foreach ref {RAMSP128X16 RAMSP1024X16 RAMSP4096X16 ROM1KX32} {
    set cells [get_cells -hierarchical -filter "ref_name == $ref"]
    puts "MEMORY_COUNT $ref [sizeof_collection $cells]"
    foreach_in_collection cell $cells {
        puts $f "[get_object_name $cell]\t$ref"
    }
}
close $f
puts "MEMORY_PATH_EXPORT_PASS"
} why]} {puts "MEMORY_PATH_EXPORT_FAIL=$why"; exit 1}
exit 0
'''
script=R/'inspect.tcl'
script.write_text(prefix+tail.replace('OUTPUT',str(R/'mapped-memory.tsv')))
print('READING_MAPPED_MEMORY_PATHS',flush=True)
with (R/'pt.log').open('w') as out:
    p=subprocess.run(['pt_shell','-f',str(script)],cwd=str(R),
                     stdout=out,stderr=subprocess.STDOUT)
log=(R/'pt.log').read_text(errors='replace')
for line in log.splitlines():
    if line.startswith(('MEMORY_','Error:')):
        print(line)
if p.returncode!=0 or 'MEMORY_PATH_EXPORT_PASS' not in log:
    raise SystemExit('STOP: '+str(R/'pt.log'))

rows=(R/'mapped-memory.tsv').read_text().splitlines()
for label,key in [('ITCM','itcm'),('DTCM','dtcm'),
                  ('SHARED','u_shared_sram'),('ACCEL','u_kwt_accelerator')]:
    print(label+':')
    print('\n'.join([x for x in rows if key in x][:2]))
print('VCD_Q_DECLARATIONS='+str(len(signals)))
print('RUN='+str(R))
