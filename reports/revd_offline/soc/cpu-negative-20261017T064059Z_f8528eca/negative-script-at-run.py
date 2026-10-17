#!/usr/bin/env python3
"""Real CPU returns success while omitting work; the unchanged TB must reject."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,put,run_id,sha,utc

def build(run,name,sources):
    elf=run.path/(name+'.elf')
    run.cmd('build-'+name,['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32',
      '-mcmodel=medany','-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax',
      '-Os','-Wall','-Wextra','-Werror','-I',ROOT/'sw/revd_opt','-T',ROOT/'sw/e203/link.ld',
      ROOT/'sw/e203/start.S',*sources,'-o',elf])
    run.cmd('disassemble-'+name,['riscv64-unknown-elf-objdump','-d',elf])
    run.cmd('binary-'+name,['riscv64-unknown-elf-objcopy','-O','binary',elf,run.path/(name+'.bin')])
    payload=(run.path/(name+'.bin')).read_bytes();hexpath=run.path/(name+'.hex')
    if not 0<len(payload)<=65536:raise RuntimeError('invalid negative firmware size')
    hexpath.write_text(''.join(f'{v:02x}\n' for v in payload))
    return hexpath,len(payload)

def negative(run,name,binary,fw,required):
    folder=run.path/name;folder.mkdir(exist_ok=False)
    for filename in ['shared.hex','expected.hex','expected-flags.hex']:
        (folder/filename).write_bytes((run.path/'fixture'/filename).read_bytes())
    (folder/fw[0].name).write_bytes(fw[0].read_bytes())
    text,record=run.cmd(name,['vvp',binary,f'+FIRMWARE={fw[0].name}',f'+FIRMWARE_BYTES={fw[1]}'],
                         timeout=240,cwd=folder,negative='CPU coverage incomplete')
    if required not in text or 'CPU_EXIT_FAILURE' in text:
        raise RuntimeError('CPU did not reach genuine successful mailbox return with the intended omitted output count')
    # In the unchanged TB, the mailbox's BOOT/return=0 assertion is immediately
    # before this coverage assertion. A nonzero code triggers CPU_EXIT_FAILURE.
    return {'status':'EXPECTED_FAIL','firmware_intended_return':0,'successful_mailbox_precondition_passed':True,
            'reason':'Unchanged CPU TB rejected missing actual SRAM writes despite successful completion code.',
            'required_message':required,'command':record,
            'actual_output_sha256':{p.name:sha(p) for p in folder.iterdir() if p.name in ['cpu-output.txt','cpu-flags.txt']}}

def main():
    out=ROOT/'reports/revd_offline/soc'/('cpu-negative-'+run_id());out.mkdir(parents=True,exist_ok=False)
    run=soc.Run(out);frozen=soc.inventory()
    report={'status':'RUNNING','source_sha256':frozen,'started_utc':utc(),'tests':{}}
    put(out/'result.json',report)
    try:
        info=soc.fixture(out/'fixture',3,16,1)
        binary=soc.compile_cpu(run,3,16,1,4,1,'icarus')
        green=soc.firmware(run,'normal-revd-driver')
        report['tests']['normal_cpu_icarus']=soc.simulate(run,'normal-cpu-icarus',binary,'icarus',green,info)
        zero=out/'zero-main.c';zero.write_text('int main(void){return 0;}\n')
        fw=build(run,'zero-return',[zero])
        report['tests']['zero_return_no_work']=negative(run,'zero-return-no-work',binary,fw,'CPU coverage incomplete outputs=0 flags=0')
        driver=(ROOT/'sw/revd_opt/revd_opt_driver.c').read_text()
        anchor='destination[index]=(int32_t)value;\n        flag_destination[index]=(uint8_t)flags;'
        if driver.count(anchor)!=1:raise RuntimeError('skip-last driver anchor changed')
        mutated=driver.replace(anchor,'if(index+1u!=expected_count){\n        '+anchor+'\n        }',1)
        mutant=out/'skip-last-driver.c';mutant.write_text(mutated)
        main=(ROOT/'sw/revd_opt/main.c').read_text();anchor='*phase=0x100u+t;'
        if main.count(anchor)!=1:raise RuntimeError('negative phase anchor changed')
        mainpath=out/'skip-last-main.c';mainpath.write_text(main.replace(anchor,'/* Intentionally omit the phase marker so the unchanged TB observes the successful mailbox. */',1))
        fw=build(run,'skip-last',[mainpath,mutant])
        report['tests']['zero_return_missing_final_shared_write']=negative(run,'skip-last-shared-write',binary,fw,'CPU coverage incomplete outputs=47 flags=47')
        if soc.inventory()!=frozen:raise RuntimeError('normal sources changed during negative execution')
        report.update(status='PASS',finished_utc=utc(),negative_test_count=2,rtl_mutation_count=0,
          negative_script_sha256=sha(Path(__file__)),commands=run.records,
          artifacts_sha256={str(p.relative_to(out)):sha(p) for p in out.rglob('*') if p.is_file() and p.name!='result.json'})
        put(out/'result.json',report)
    except Exception as exc:
        report.update(status='FAIL',error=str(exc),finished_utc=utc(),commands=run.records);put(out/'result.json',report);raise
    print('SOC_CPU_NEGATIVE_REPORT',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
