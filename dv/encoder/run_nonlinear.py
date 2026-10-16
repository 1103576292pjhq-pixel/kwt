"""Standalone nonlinear RTL vs the independently authored released C reference."""
import argparse
import ctypes
from pathlib import Path
import random
import struct
import sys
import os,time,uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'));sys.path.insert(0,str(ROOT))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,reference_release,archive,fp32_release

def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def f32(x):return struct.unpack('<f',struct.pack('<I',x))[0]
def main():
 started=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
 fp_handoff=fp32_release()
 p=argparse.ArgumentParser();p.add_argument('--sim',choices=['icarus','verilator'],default='icarus');a=p.parse_args()
 out=ROOT/'reports/encoder/rtl'/('nonlinear-'+a.sim);out.mkdir(parents=True,exist_ok=True);archive(out)
 ref,manifest,verified=reference_release();write(out/'reference-readback.json',verified)
 from numeric.encoder.run_reference import Reference
 model=Reference(out)
 rng=random.Random(20261015);vectors=[]
 for mode in range(2):
  values=[0x00000000,0x80000000,0x3f800000,0xbf800000,0xc2a00000,0xc29fffff,
          0x41200000,0xc1200000,0x411fffff,0xc11fffff,0x00000001,0x80000001,
          0x7f800000,0xff800000,0x7fc00000]
  values+=[bits(rng.uniform(-12,12) if mode else rng.uniform(-100,0)) for _ in range(1000)]
  for x in values:
   value=f32(x);invalid=x&0x7f800000==0x7f800000 or (not mode and value>0)
   answer=0x7fc00000 if invalid else bits((model.lib.kwt_gelu if mode else model.lib.kwt_exp_neg)(ctypes.c_float(value)))
   vectors.append(f'{mode:08x} {x:08x} {answer:08x} {int(invalid):08x}\n')
 (out/'vectors.txt').write_text(''.join(vectors),encoding='utf-8')
 own=[ROOT/'rtl/encoder_fp32.sv',ROOT/'rtl/encoder_nonlinear.sv',ROOT/'dv/encoder/tb_nonlinear.sv',Path(__file__),ROOT/'numeric/encoder/encoder_ref.c']
 own += [ROOT/'dv/encoder/run_encoder.py',ROOT/'dv/fp32/hardfloat_sources.py',ROOT/'numeric/encoder/run_reference.py']
 bound=hashes(own);src=prepare(out/'hardfloat')+own[:3];inc=['-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV')]
 if a.sim=='icarus':
  binary=out/'test.vvp';cmd=['iverilog','-g2012','-s','tb_nonlinear','-o',binary,*inc,*src]
  execute=['vvp',binary]
 else:
  binary=out/'obj/Vtb_nonlinear';cmd=['verilator','--binary','--timing','-Wno-fatal','--top-module','tb_nonlinear','--Mdir',out/'obj','-j','4',*inc,*src]
  execute=[binary]
 run(cmd,out,out/'compile.log',600);log=run(execute,out,out/'simulation.log')
 if f'ENCODER_NONLINEAR_PASS vectors={len(vectors)} reset_interruptions=2' not in log:raise ValueError('nonlinear incomplete')
 if hashes(own)!=bound:raise ValueError('nonlinear sources changed')
 if fp32_release()!=fp_handoff:raise ValueError('nonlinear FP32 release changed')
 write(out/'status.json',{'status':'PASS','vectors':len(vectors),'simulator':a.sim,'reset_interruptions':2,
  'run_id':run_id,'started_unix':started,'completed_unix':time.time(),
  'source_sha256':bound,'vectors_sha256':sha(out/'vectors.txt'),'log_sha256':sha(out/'simulation.log'),
  'binary_sha256':sha(binary),'reference_manifest_sha256':sha(ref/'manifest.json')})
 print('ENCODER_NONLINEAR_PASS',len(vectors),flush=True)

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
