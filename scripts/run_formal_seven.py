"""One reproducible local-draft regression; records each real child invocation."""
from __future__ import annotations
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import time
import uuid
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT));sys.path.insert(0,str(ROOT/'scripts'));sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import sha,write,archive
from formal_seven_gate import accepted_rtl,bound_record,cpu_record,validate_freshness,small_record

def main():
 p=argparse.ArgumentParser();p.add_argument('--reuse-verified',action='store_true');p.add_argument('--gate-only',action='store_true');a=p.parse_args()
 out=ROOT/'reports/encoder/verification/unified';out.mkdir(parents=True,exist_ok=True);archive(out)
 run_id=uuid.uuid4().hex;started=time.time();commands=[]
 write(out/'status.json',{'status':'RUNNING','run_id':run_id,'pid':os.getpid(),'started_unix':started})
 def command(name,args,timeout=36000,validator=None):
  if a.reuse_verified and validator:
   try:
    prior=validator()
    commands.append({'name':name,'identity':'EXPLICIT_VERIFIED_HISTORY','evidence':prior,'checked_unix':time.time()})
    write(out/'commands.json',commands);print('Verified history',name,flush=True);return
   except (ValueError,OSError,KeyError,TypeError):pass
  cmd=[str(x) for x in args];log=out/(name+'.log');begin=time.time()
  print('Run',name,flush=True)
  with log.open('w',encoding='utf-8') as f:
   env=dict(os.environ);env['ENCODER_RUN_ID']=run_id
   proc=subprocess.Popen(cmd,cwd=ROOT,stdout=f,stderr=subprocess.STDOUT,text=True,encoding='utf-8',env=env)
   write(out/'progress.json',{'status':'RUNNING','run_id':run_id,'stage':name,'pid':proc.pid,'command':cmd,'started_unix':begin,'log':str(log),'target_cases':1})
   try:exit_code=proc.wait(timeout=timeout)
   except subprocess.TimeoutExpired:proc.kill();proc.wait();exit_code=124
  entry={'name':name,'identity':'ACTUAL_EXECUTION','run_id':run_id,'command':cmd,'pid':proc.pid,
         'started_unix':begin,'completed_unix':time.time(),'exit_code':exit_code,'log_sha256':sha(log)}
  commands.append(entry);write(out/'commands.json',commands)
  if exit_code:
   write(out/'status.json',{'status':'FAIL','run_id':run_id,'failed_stage':name,'exit_code':exit_code,'commands':commands})
   raise RuntimeError(f'{name} exit {exit_code}; see {log}')
  if validator:
   checked=validator()
   result=checked[0] if isinstance(checked,tuple) else checked
   validate_freshness(result,run_id,begin)
   entry['fresh_evidence_run_id']=result['run_id'];write(out/'commands.json',commands)
 py=ROOT/'.venv-dv/bin/python'
 if not a.gate_only:
  command('checks',[py,'dv/encoder/run_checks.py'],validator=lambda:bound_record(ROOT/'reports/encoder/verification/checks/status.json'))
  command('gate-tests',[py,'-m','pytest','dv/encoder/test_formal_gate.py','-q'])
  command('gate-schema-mutation',[py,'dv/encoder/run_gate_schema_mutation.py'])
  for sim in ['icarus','verilator']:
   command('nonlinear-'+sim,[py,'dv/encoder/run_nonlinear.py','--sim',sim],validator=lambda sim=sim:bound_record(ROOT/f'reports/encoder/rtl/nonlinear-{sim}/status.json'))
   for fixture in ['small_3_4_8','small_zero_3_4_8']:
    command('small-'+sim+'-'+fixture,[py,'dv/encoder/run_encoder.py','--mode','small','--sim',sim,'--case',fixture,'--trace','--output',f'reports/encoder/rtl/small-{sim}-{fixture}'],validator=lambda sim=sim,fixture=fixture:small_record(ROOT/f'reports/encoder/rtl/small-{sim}-{fixture}/status.json',fixture,sim))
  command('numeric-mutations',[py,'dv/encoder/run_mutations.py'],validator=lambda:bound_record(ROOT/'reports/encoder/verification/mutations/status.json'))
  command('attention-full',[py,'dv/encoder/run_encoder.py','--mode','layer','--attention','--trace','--output','reports/encoder/rtl/attention-full'],validator=lambda:accepted_rtl(ROOT/'reports/encoder/rtl/attention-full/status.json',1,True))
  command('source-freeze',[py,'dv/encoder/freeze_sources.py'])
  from run_encoder import reference_release
  for bundle in ['reference','reference-test12']:
   _,manifest,_=reference_release(bundle)
   for i,s in enumerate(manifest['samples']):
    sid=s['sample_id'];name=('original-' if bundle=='reference' else 'test12-')+str(i)
    directory='reports/encoder/rtl/full/'+name
    args=[py,'dv/encoder/run_encoder.py','--mode','full','--case',sid,'--reference',bundle,'--output',directory,'--reuse-build']
    if bundle=='reference' and i==0:args+=['--trace']
    command(name,args,validator=lambda directory=directory:accepted_rtl(ROOT/directory/'status.json'))
  command('independent-repeat',[py,'dv/encoder/run_encoder.py','--mode','full','--output','reports/encoder/rtl/repeat'],validator=lambda:accepted_rtl(ROOT/'reports/encoder/rtl/repeat/status.json'))
  for policy,name in [(1,'pingpong'),(2,'reload')]:
   command('cpu-'+name,[py,'dv/e203_encoder/run_system.py','--policy',str(policy),'--output','reports/encoder/system/'+name,'--reuse-build'],validator=lambda policy=policy,name=name:cpu_record(ROOT/f'reports/encoder/system/{name}/status.json',policy))
  command('generic-encoder-synth',[py,'dv/encoder/run_synth.py'],validator=lambda:bound_record(ROOT/'reports/encoder/synthesis/status.json'))
  command('generic-soc-synth',[py,'dv/encoder/run_soc_synth.py'],validator=lambda:bound_record(ROOT/'reports/encoder/synthesis/soc/status.json'))
 command('final-evidence-gate',[py,'scripts/formal_seven_gate.py'])
 final=json.loads((ROOT/'reports/encoder/verification/gate.json').read_text(encoding='utf-8'))
 if final['run_id']!=run_id or final['created_unix']<started or final['status']!='PASS':raise ValueError('final gate is not from this invocation')
 command('render-report',[py,'scripts/encoder_report.py'])
 write(out/'status.json',{'status':'PASS','run_id':run_id,'started_unix':started,'completed_unix':time.time(),
                         'commands':commands,'source_sha256':sha(Path(__file__))})
 print('FORMAL_SEVEN_LOCAL_DRAFT_GATE_PASS',flush=True)

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
