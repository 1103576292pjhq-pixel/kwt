"""Reproduce real E203 firmware, public shared-memory host, and passive output DV."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import sys
import time
import os
import uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,RTL,archive,reference_release,fp32_release,verify_source_freeze

def compile_soc(out,reuse):
 rtlroot=ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203'
 upstream=sorted(rtlroot.rglob('*.v'))
 local=[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'soc/e203_encoder/e203_encoder_soc.sv',ROOT/'dv/e203_encoder/tb_e203_encoder.sv',Path(__file__)]
 src=[ROOT/'dv/e203_boot/timescale.v']+upstream+[ROOT/'soc/e203_common/e203_cpu_shell.sv',ROOT/'soc/e203_encoder/encoder_shared_ram.sv']+prepare(out/'hardfloat')+[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'rtl/ffn1_icb.sv',ROOT/'rtl/ffn1_top.sv',ROOT/'rtl/dot64.sv',ROOT/'rtl/prototype_sync_ram.sv',ROOT/'soc/e203_encoder/e203_encoder_soc.sv',ROOT/'dv/e203_encoder/tb_e203_encoder.sv']
 inc=['-I'+str(x) for x in [rtlroot/'core',rtlroot/'perips',rtlroot/'perips/apb_i2c',SOURCE,SOURCE/'RISCV']]
 includes=[p for p in SOURCE.rglob('*') if p.is_file()]+[p for p in rtlroot.rglob('*') if p.is_file() and p.suffix in ('.vh','.vi')]
 build_flags=['--binary','--timing','-O3','-CFLAGS','-O3','-Wno-fatal','-Wno-BLKLOOPINIT']
 binary=out/'obj/Vtb_e203_encoder';key={'sources':hashes(src+includes),'compiler_options':build_flags,'fp':sha(ROOT/'work/fp32_handoff.json'),'e203':sha(ROOT/'work/e203_boot_handoff.json')}
 if not(reuse and binary.exists() and (out/'build.json').exists() and json.loads((out/'build.json').read_text(encoding='utf-8'))==key):
  run(['verilator',*build_flags,'--top-module','tb_e203_encoder','--Mdir',out/'obj','-j','4','-Diverilog','-DDISABLE_SV_ASSERTION=1',*inc,*src],out,out/'compile.log',900);write(out/'build.json',key)
 return binary

def main():
 started_invocation=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
 p=argparse.ArgumentParser();p.add_argument('--small',action='store_true');p.add_argument('--case');p.add_argument('--policy',type=int,choices=[0,1,2],default=0);p.add_argument('--reuse-build',action='store_true');p.add_argument('--compile-only',action='store_true');p.add_argument('--output',default='reports/encoder/system/full');a=p.parse_args()
 out=(ROOT/a.output).resolve()
 if (ROOT/'reports/encoder').resolve() not in out.parents:raise ValueError('unsafe output')
 out.mkdir(parents=True,exist_ok=True);archive(out);write(out/'status.json',{'status':'RUNNING'})
 if a.compile_only:
  binary=compile_soc(out,a.reuse_build)
  write(out/'status.json',{'status':'COMPILED_ONLY','binary_sha256':sha(binary),'functional_acceptance':False})
  print('E203_ENCODER_COMPILED_ONLY');return
 hand=ROOT/'work/encoder_reference_handoff.json'
 if not hand.exists():hand=ROOT/'work/encoder_reference_core_ready.json'
 if not hand.exists() or json.loads(hand.read_text(encoding='utf-8'))['status']!='PASS':raise ValueError('reference dependency not released')
 if a.policy:
  release=ROOT/'work/MASTER_RELEASE_encoder_reuse.md'
  if not release.exists() or 'RELEASED' not in release.read_text(encoding='utf-8'):raise ValueError('reuse experiment not released')
 fp_handoff=fp32_release()
 freeze=verify_source_freeze()
 boot=json.loads((ROOT/'work/e203_boot_handoff.json').read_text(encoding='utf-8'))
 for rel,digest in boot['input_sha256'].items():
  if sha(ROOT/rel)!=digest:raise ValueError('boot source changed: '+rel)
 ref,manifest,verified=reference_release();write(out/'reference-readback.json',verified)
 if manifest['status']!='PASS':raise ValueError('reference manifest failed')
 for rel,digest in manifest['source_hashes'].items():
  if sha(ROOT/rel)!=digest:raise ValueError('stale reference source '+rel)
 if a.small:
  raise ValueError('CPU small requires explicit independently generated twelve-layer fixture; use full released case')
 m,d,h=99,64,256;sid=a.case or manifest['samples'][0]['sample_id'];case=ref/'cases'/sid
 inputs={str(hand.relative_to(ROOT)):sha(hand),'reports/encoder/reference/manifest.json':sha(ref/'manifest.json'),'work/fp32_handoff.json':fp_handoff}
 inputs['work/encoder_source_freeze.json']=freeze
 if a.policy:inputs['work/MASTER_RELEASE_encoder_reuse.md']=sha(release)
 (out/'input.hex').write_bytes((case/'input.hex').read_bytes());inputs[str((case/'input.hex').relative_to(ROOT))]=sha(case/'input.hex')
 expected=''
 for l in range(12):
  path=case/f'layer_{l:02d}/y.hex';expected+=path.read_text(encoding='utf-8');inputs[str(path.relative_to(ROOT))]=sha(path)
 (out/'expected.hex').write_text(expected,encoding='utf-8')
 dest=out/'weights'
 if not dest.exists():dest.symlink_to(ref/'weights',target_is_directory=True)
 for l in range(12):
  path=ref/f'weights/layer_{l:02d}.hex';inputs[str(path.relative_to(ROOT))]=sha(path)
 own=[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'soc/e203_encoder/e203_encoder_soc.sv',ROOT/'sw/encoder_driver.c',ROOT/'sw/encoder_driver.h',ROOT/'sw/e203_encoder/main.c',Path(__file__),ROOT/'dv/e203_encoder/tb_e203_encoder.sv',ROOT/'dv/encoder/run_encoder.py',ROOT/'sw/e203/start.S',ROOT/'sw/e203/link.ld']
 own+=[ROOT/'soc/e203_common/e203_cpu_shell.sv',ROOT/'soc/e203_encoder/encoder_shared_ram.sv',ROOT/'rtl/ffn1_icb.sv',ROOT/'rtl/ffn1_top.sv',ROOT/'rtl/dot64.sv',ROOT/'rtl/prototype_sync_ram.sv',ROOT/'dv/e203_boot/timescale.v']
 own+=sorted((ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203').rglob('*.v'))
 own+=[p for p in SOURCE.rglob('*') if p.is_file()]
 own+=[p for p in (ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203').rglob('*') if p.is_file() and p.suffix in ('.vh','.vi')]
 bound=hashes(own)
 gcc=['riscv64-unknown-elf-gcc','-march=rv32imac_zicsr_zifencei','-mabi=ilp32','-mcmodel=medany','-nostdlib','-nostartfiles','-ffreestanding','-fno-builtin','-Wl,--no-relax','-Os','-g','-Wall','-Wextra','-Werror',f'-DENCODER_POLICY={a.policy}']
 run(gcc+['-T',ROOT/'sw/e203/link.ld',f'-Wl,-Map,{out/"firmware.map"}',ROOT/'sw/e203/start.S',ROOT/'sw/encoder_driver.c',ROOT/'sw/e203_encoder/main.c','-o',out/'firmware.elf'],out,out/'build-firmware.log')
 run(['riscv64-unknown-elf-objdump','-d',out/'firmware.elf'],out,out/'firmware-disassembly.log')
 run(['riscv64-unknown-elf-objcopy','-O','binary',out/'firmware.elf',out/'firmware.bin'],out,out/'firmware-binary.log')
 payload=(out/'firmware.bin').read_bytes()
 (out/'firmware.hex').write_text(''.join(f'{b:02x}\n' for b in payload),encoding='utf-8')
 binary=compile_soc(out,a.reuse_build)
 compiled=json.loads((out/'build.json').read_text(encoding='utf-8'))['sources']
 for rel,digest in compiled.items():
  if sha(ROOT/rel)!=digest:raise ValueError('compiled source changed '+rel)
 frozen=json.loads((ROOT/'work/encoder_source_freeze.json').read_text(encoding='utf-8'))
 if sha(out/'hardfloat/divSqrtRecFN_small.v')!=frozen['source_sha256']['reports/encoder/verification/frozen-hardfloat/divSqrtRecFN_small.v']:raise ValueError('CPU generated HardFloat differs from frozen source')
 print('Real E203 full12 execution',sid,flush=True);started=time.time()
 if fp32_release()!=fp_handoff:raise ValueError('FP32 release changed before CPU run')
 if verify_source_freeze()!=freeze:raise ValueError('source freeze changed before CPU run')
 executed_binary=sha(binary)
 actual_command=[str(binary),f'+BYTES={len(payload)}',f'+POLICY={a.policy}']
 log=run(actual_command,out,out/'simulation.log',28800)
 count=m*d if a.policy==1 else 12*m*d
 if f'E203_ENCODER_PASS layers=12 outputs={count} neural_words={12*m*d}' not in log:raise ValueError('CPU coverage marker missing')
 cpu_expected=''.join(expected.splitlines(keepends=True)[11*m*d:]) if a.policy==1 else expected
 if (out/'cpu-output.hex').read_text(encoding='utf-8')!=cpu_expected:raise ValueError('CPU output file differs')
 if (out/'neural-output.hex').read_text(encoding='utf-8')!=expected:raise ValueError('passive neural output file differs')
 if hashes(own)!=bound:raise ValueError('CPU sources changed during run')
 if sha(binary)!=executed_binary:raise ValueError('CPU binary changed during run')
 for rel,digest in compiled.items():
  if sha(ROOT/rel)!=digest:raise ValueError('compiled CPU source changed during run '+rel)
 for rel,digest in inputs.items():
  if sha(ROOT/rel)!=digest:raise ValueError('CPU inputs changed: '+rel)
 write(out/'status.json',{'status':'PASS','case':sid,'layers':12,'output_words':count,'neural_words':12*m*d,'policy':a.policy,
  'source_sha256':bound,'input_sha256':inputs,'firmware_sha256':sha(out/'firmware.elf'),
  'compiled_source_sha256':compiled,'binary_sha256':sha(binary),
  'compile_log_sha256':sha(out/'compile.log'),'build_key_sha256':sha(out/'build.json'),
  'output_sha256':sha(out/'cpu-output.hex'),'log_sha256':sha(out/'simulation.log'),
  'neural_sha256':sha(out/'neural-output.hex'),'exit_code':0,
  'command':actual_command,'pid':os.getpid(),'run_id':run_id,'started_unix':started_invocation,'completed_unix':time.time(),
  'wall_seconds':time.time()-started,'summary':log[log.rfind('E203_ENCODER_PASS'):].splitlines()[0]})
 write(out/'progress.json',{'status':'PASS'})

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
