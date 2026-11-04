#!/usr/bin/env python3
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[2]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    gcc=Path(json.loads(Path('/mnt/d/嵌赛芯片设计赛道/toolchains/nuclei-2024.06/installation.json').read_text())['gcc'])
    prefix=str(gcc)[:-3];out=HERE/'build-01';out.mkdir(exist_ok=False);commands=[]
    def run(args):
        p=subprocess.run(list(map(str,args)),cwd=HERE,capture_output=True,text=True)
        commands.append(dict(argv=list(map(str,args)),returncode=p.returncode,stdout=p.stdout,stderr=p.stderr))
        (out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');p.check_returncode();return p.stdout
    elf=out/'real_shared_task.elf';binary=out/'real_shared_task.bin';image=out/'real_shared_task.verilog'
    sources=[HERE/n for n in ['start.S','link.ld','kwt_mmio.h','task_test.h','task_test.c','shared_task.h','shared_task.c','real_io.c','build.py']]
    run([gcc,'-std=c11','-O2','-flto','-Wall','-Wextra','-Werror','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
         '-mcmodel=medany','-msmall-data-limit=0','-mno-relax','-ffreestanding','-fno-builtin','-fno-pic',
         '-fno-stack-protector','-fstack-usage','-nostdlib','-nostartfiles','-Wl,--build-id=none','-Wl,--no-relax',
         '-Wl,-Map='+str(out/'real_shared_task.map'),'-T',HERE/'link.ld',HERE/'start.S',HERE/'task_test.c',
         HERE/'shared_task.c',HERE/'real_io.c','-o',elf])
    syms=run([prefix+'nm','-n',elf]);table={s[2]:int(s[0],16) for line in syms.splitlines() if len(s:=line.split())==3}
    assert table['_start']==0x80000000 and table['test_end']==0x80000086 and table['__bss_end']<=0x80000c00
    assert table['__stack_top']==0x80001000 and not run([prefix+'nm','-u',elf]).strip()
    eh=elf.read_bytes()[:52];assert eh[:7]==b'\x7fELF\x01\x01\x01' and struct.unpack_from('<I',eh,24)[0]==0x80000000
    dump=run([prefix+'objdump','-d',elf]);assert not re.search(r'\(\s*gp\s*\)',dump)
    (out/'real_shared_task.dump').write_text(dump);(out/'symbols.txt').write_text(syms)
    run([prefix+'objcopy','-O','binary','--gap-fill=0',elf,binary]);data=binary.read_bytes()
    assert data[0x86:0x88]==b'\x01\xa0' and 0x100<len(data)<=0xc00
    image.write_text('@00000000\n'+'\n'.join(' '.join('%02X'%b for b in data[i:i+16]) for i in range(0,len(data),16))+'\n')
    assert bytes.fromhex(' '.join(image.read_text().splitlines()[1:]))==data
    report=dict(status='CROSS_COMPILED_REAL_SHARED_TASK_NOT_CPU_EXECUTED',compiler=str(gcc),version=run([gcc,'--version']).splitlines()[0],
        entry=hex(table['_start']),test_end=hex(table['test_end']),bss_end=hex(table['__bss_end']),stack_top=hex(table['__stack_top']),
        binary_bytes=len(data),expected_blocks=400,outputs=25344,image_sha256=sha(image),
        sources={p.name:sha(p) for p in sources},optimization='CPU configures DMA descriptor then polls; DMA performs all parameter/result transfers',
        scope='Real case3 file input in shared SRAM, original poison/checks and protocol retained; throughput candidate pending actual E203 measurement')
    (out/'build-report.json').write_text(json.dumps(report,indent=2)+'\n')
    print('SHARED_TASK_FIRMWARE_READY bytes=%d bss_end=%x sha256=%s'%(len(data),table['__bss_end'],sha(image)))
if __name__=='__main__':main()
