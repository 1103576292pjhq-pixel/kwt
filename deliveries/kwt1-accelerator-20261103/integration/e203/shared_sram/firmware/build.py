#!/usr/bin/env python3
"""Build CPU RAM smoke with the already installed local Nuclei toolchain."""
import hashlib
import json
from pathlib import Path
import re
import subprocess

HERE=Path(__file__).resolve().parent
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    install=Path('/mnt/d/嵌赛芯片设计赛道/toolchains/nuclei-2024.06/installation.json')
    gcc=Path(json.loads(install.read_text())['gcc']);prefix=str(gcc)[:-3]
    out=HERE/'build-01';out.mkdir(exist_ok=False);commands=[]
    def run(args):
        r=subprocess.run(list(map(str,args)),cwd=HERE,capture_output=True,text=True,check=True)
        commands.append(dict(argv=list(map(str,args)),returncode=r.returncode,stdout=r.stdout,stderr=r.stderr));return r.stdout
    elf=out/'shared_ram_smoke.elf';binary=out/'shared_ram_smoke.bin';image=out/'shared_ram_smoke.verilog'
    run([gcc,'-std=c11','-O2','-Wall','-Wextra','-Werror','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
         '-mcmodel=medany','-msmall-data-limit=0','-mno-relax','-ffreestanding','-fno-builtin',
         '-fno-pic','-fno-stack-protector','-nostdlib','-nostartfiles','-fstack-usage',
         '-Wl,--build-id=none','-Wl,--no-relax','-T',HERE/'link.ld',HERE/'start.S',HERE/'shared_ram_smoke.c',
         '-Wl,-Map='+str(out/'shared_ram_smoke.map'),'-o',elf])
    syms=run([prefix+'nm','-n',elf]);table={v[2]:int(v[0],16) for line in syms.splitlines() if len(v:=line.split())==3}
    assert table['_start']==0x80000000 and table['test_end']==0x80000086 and table['__bss_end']<=0x80000c00
    assert table['__stack_top']==0x80001000 and not run([prefix+'nm','-u',elf]).strip()
    dump=run([prefix+'objdump','-d',elf]);assert not re.search(r'\(\s*gp\s*\)',dump)
    run([prefix+'objcopy','-O','binary','--gap-fill=0',elf,binary]);data=binary.read_bytes()
    assert 0x100<len(data)<=0xc00 and data[0x86:0x88]==b'\x01\xa0'
    image.write_text('@00000000\n'+'\n'.join(' '.join('%02X'%b for b in data[i:i+16]) for i in range(0,len(data),16))+'\n')
    assert bytes.fromhex(' '.join(image.read_text().splitlines()[1:]))==data
    (out/'shared_ram_smoke.dump').write_text(dump);(out/'symbols.txt').write_text(syms)
    report=dict(status='CROSS_COMPILED_CPU_SHARED_RAM_TEST_NOT_EXECUTED',gcc=str(gcc),version=run([gcc,'--version']).splitlines()[0],
        entry='0x80000000',test_end='0x80000086',stack_top='0x80001000',bss_end=hex(table['__bss_end']),
        binary_bytes=len(data),base='0xa0000000 DEVELOPMENT',scope='32banks first/last64words and byte/halfword stores',
        image_sha256=digest(image),sources={p.name:digest(p) for p in [HERE/'shared_ram_smoke.c',HERE/'start.S',HERE/'link.ld',Path(__file__)]},commands=commands)
    (out/'build-report.json').write_text(json.dumps(report,indent=2)+'\n')
    print('FIRMWARE_COMPILED bytes=%d sha256=%s; CPU execution pending'%(len(data),digest(image)))
if __name__=='__main__':main()
