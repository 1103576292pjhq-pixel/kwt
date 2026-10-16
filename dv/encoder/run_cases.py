"""Finite RTL case batch, each case a real independent Verilator execution."""
from concurrent.futures import ThreadPoolExecutor,as_completed
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import time
import uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'));sys.path.insert(0,str(ROOT/'scripts'))
from run_encoder import write,sha,reference_release
from formal_seven_gate import accepted_rtl

def main():
 p=argparse.ArgumentParser();p.add_argument('--jobs',type=int,choices=[1,2,3],default=3);p.add_argument('--reuse-verified',action='store_true');a=p.parse_args()
 out=ROOT/'reports/encoder/verification/case-batch';out.mkdir(parents=True,exist_ok=True)
 run_id=uuid.uuid4().hex;cases=[];results=[]
 for bundle,prefix in [('reference','original'),('reference-test12','test12')]:
  _,manifest,_=reference_release(bundle)
  cases += [(bundle,s['sample_id'],f'{prefix}-{i}',f'reports/encoder/rtl/full/{prefix}-{i}',bundle=='reference' and i==0) for i,s in enumerate(manifest['samples'])]
 cases.append(('reference',cases[0][1],'repeat','reports/encoder/rtl/repeat',False))
 def execute(item):
  bundle,sid,name,directory,trace=item
  if a.reuse_verified:
   try:
    accepted=accepted_rtl(ROOT/directory/'status.json')
    return {'name':name,'status':'PASS','identity':'EXPLICIT_VERIFIED_HISTORY','record':directory+'/status.json','record_sha256':sha(ROOT/directory/'status.json')}
   except (ValueError,OSError,KeyError):pass
  cmd=[str(ROOT/'.venv-dv/bin/python'),'dv/encoder/run_encoder.py','--mode','full','--case',sid,'--reference',bundle,'--output',directory,'--reuse-build']
  if trace:cmd+=['--trace']
  log=out/(name+'.log');started=time.time();env=dict(os.environ);env['ENCODER_RUN_ID']=run_id
  with log.open('w',encoding='utf-8') as f:
   child=subprocess.Popen(cmd,cwd=ROOT,stdout=f,stderr=subprocess.STDOUT,text=True,encoding='utf-8',env=env)
   write(out/(name+'-process.json'),{'status':'RUNNING','run_id':run_id,'pid':child.pid,'command':cmd,'started_unix':started,'target_cases':1,'expected_layers':12,'expected_output_words':76032})
   try:code=child.wait(timeout=18000)
   except subprocess.TimeoutExpired:child.kill();child.wait();code=124
  result={'name':name,'status':'FAIL','command':cmd,'exit_code':code,'started_unix':started,'completed_unix':time.time(),'log_sha256':sha(log)}
  if not code:
   try:
    record=accepted_rtl(ROOT/directory/'status.json')
    if record['run_id']!=run_id or record['started_unix']<started:raise ValueError('case result stale')
    result.update(status='PASS',record=directory+'/status.json',record_sha256=sha(ROOT/directory/'status.json'))
   except (ValueError,OSError,KeyError) as exc:result['error']=str(exc)
  write(out/(name+'-process.json'),result);return result
 write(out/'progress.json',{'status':'RUNNING','run_id':run_id,'target_cases':len(cases),'completed':0,'pid':os.getpid()})
 with ThreadPoolExecutor(max_workers=a.jobs) as pool:
  futures=[pool.submit(execute,item) for item in cases]
  for future in as_completed(futures):
   result=future.result();results.append(result)
   write(out/'progress.json',{'status':'RUNNING','run_id':run_id,'target_cases':len(cases),'completed':len(results),'passed':sum(r['status']=='PASS' for r in results),'results':results,'pid':os.getpid()})
   print(result['name'],result['status'],f'{len(results)}/{len(cases)}',flush=True)
 failed=any(r['status']!='PASS' for r in results)
 write(out/'status.json',{'status':'FAIL' if failed else 'PASS','run_id':run_id,'target_cases':len(cases),'results':results,'completed_unix':time.time()})
 return int(failed)

if __name__=='__main__':sys.exit(main())
