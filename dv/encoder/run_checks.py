"""Directed interface, production-driver fault checks, and compilable mutations."""
import json
from pathlib import Path
import sys
import os,time,uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,RTL,fp32_release

def main():
 started=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
 fp_handoff=fp32_release()
 out=ROOT/'reports/encoder/verification/checks';out.mkdir(parents=True,exist_ok=True)
 write(out/'status.json',{'status':'RUNNING'})
 own=[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'sw/encoder_driver.c',ROOT/'sw/encoder_driver.h',ROOT/'dv/encoder/test_driver.c',ROOT/'dv/encoder/tb_encoder_icb.sv',ROOT/'dv/encoder/tb_encoder_faults.sv',ROOT/'dv/encoder/tb_encoder_icb_run.sv',Path(__file__)]
 own += [ROOT/'dv/encoder/run_encoder.py',ROOT/'dv/fp32/hardfloat_sources.py']
 bound=hashes(own)
 log=run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-fsanitize=undefined,address','-g',ROOT/'sw/encoder_driver.c',ROOT/'dv/encoder/test_driver.c','-o',out/'driver'],out,out/'driver-build.log')
 log=run([out/'driver'],out,out/'driver.log')
 if 'ENCODER_DRIVER_PASS checks=13' not in log:raise ValueError('driver coverage')
 src=prepare(out/'hardfloat')+[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'dv/encoder/tb_encoder_icb.sv']
 cmd=['iverilog','-g2012','-s','tb_encoder_icb','-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV')]
 run(cmd+['-o',out/'icb.vvp',*src],out,out/'icb-build.log')
 log=run(['vvp',out/'icb.vvp'],out,out/'icb.log')
 if 'ENCODER_ICB_PASS checks=28' not in log:raise ValueError('ICB coverage '+log)
 faultsrc=[p for p in src if p!=ROOT/'dv/encoder/tb_encoder_icb.sv']+[ROOT/'dv/encoder/tb_encoder_faults.sv']
 run(['iverilog','-g2012','-s','tb_encoder_faults','-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV'),'-o',out/'faults.vvp',*faultsrc],out,out/'faults-build.log')
 faultlog=run(['vvp',out/'faults.vvp'],out,out/'faults.log')
 if 'ENCODER_FAULT_RESET_PASS' not in faultlog:raise ValueError('fault/reset coverage')
 runsrc=[p for p in src if p!=ROOT/'dv/encoder/tb_encoder_icb.sv']+[ROOT/'dv/encoder/tb_encoder_icb_run.sv']
 run(['iverilog','-g2012','-s','tb_encoder_icb_run','-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV'),'-o',out/'icb-run.vvp',*runsrc],out,out/'icb-run-build.log')
 runlog=run(['vvp',out/'icb-run.vvp'],out,out/'icb-run.log')
 if 'full_layers=2 attention_layers=1 wait_done=3 outputs=36' not in runlog:raise ValueError('ICB real completion coverage')
 # A real, compiled wrong response must be rejected by the same consumer.
 original=(ROOT/'rtl/encoder_icb.sv').read_text(encoding='utf-8')
 needle='icb_rsp_err<=rsp_error;'
 if original.count(needle)!=1:raise ValueError('mutation anchor changed')
 mutant=out/'encoder_icb_mutant.sv';mutant.write_text(original.replace(needle,'icb_rsp_err<=0;'),encoding='utf-8')
 altered=[mutant if p==ROOT/'rtl/encoder_icb.sv' else p for p in src]
 run(cmd+['-o',out/'mutant.vvp',*altered],out,out/'mutant-build.log')
 try:run(['vvp',out/'mutant.vvp'],out,out/'mutant.log')
 except RuntimeError:
  if 'error=0 expected=1' not in (out/'mutant.log').read_text(encoding='utf-8'):raise
 else:raise ValueError('incorrect core-error response survived')
 if hashes(own)!=bound:raise ValueError('check sources changed')
 if fp32_release()!=fp_handoff:raise ValueError('checks FP32 release changed')
 write(out/'status.json',{'status':'PASS','driver_checks':13,'icb_checks':28,'compiled_mutants_killed':1,
  'run_id':run_id,'started_unix':started,'completed_unix':time.time(),
  'fault_reset':True,'icb_full_layers':2,'icb_attention_layers':1,'source_sha256':bound,'log_sha256':{n:sha(out/n) for n in ['driver.log','icb.log','mutant.log','faults.log','icb-run.log']}})
 print('ENCODER_CHECKS_PASS')

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
