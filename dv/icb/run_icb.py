"""Public ICB regression; complete vectors are independently provenance checked."""
from pathlib import Path
import argparse, hashlib, json, subprocess, sys, re, fcntl, os, time, threading
from datetime import datetime, timezone
import numpy as np
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.artifacts import verify_vectors,load_array
REPORT=ROOT/'reports/system/icb'
VECTORS=ROOT/'reports/prototype/vectors'
SOURCES=[ROOT/'rtl'/p for p in ['ffn1_icb.sv','ffn1_top.sv','prototype_sync_ram.sv','dot64.sv']]
TB=ROOT/'dv/icb/tb_icb.sv'
def sha(p): return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,v):
 p.parent.mkdir(parents=True,exist_ok=True); t=p.with_suffix('.tmp');t.write_text(json.dumps(v,indent=2)+'\n');t.replace(p)
def fingerprint(): return {str(p.relative_to(ROOT)):sha(p) for p in [*SOURCES,TB,Path(__file__),ROOT/'dv/icb/run_mutations.py',ROOT/'scripts/run_icb.sh',ROOT/'numeric/fixedpoint.py',ROOT/'numeric/artifacts.py',ROOT/'config/prototype-numeric.json',ROOT/'config/source-manifest.json',ROOT/'reports/model/baseline/manifest.json',VECTORS/'manifest.json']}
def hexfile(p,a,b):p.write_text(''.join(f'{int(v)&((1<<b)-1):0{(b+3)//4}x}\n' for v in a.flat),encoding='ascii')
def simulate(folder,command,case_count):
 started=time.monotonic()
 process=subprocess.Popen(command,cwd=folder,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,bufsize=1)
 base={'pid':process.pid,'parent_pid':os.getpid(),'command':command,'cwd':str(folder),'started_utc':datetime.now(timezone.utc).isoformat(),'expected_cases':case_count}
 save(folder/'process.json',dict(base,status='RUNNING'))
 timeout=threading.Timer(7200,process.kill);timeout.start();completed=0
 try:
  with (folder/'run.log').open('w') as log:
   for line in process.stdout:
    log.write(line);log.flush()
    if line.startswith('CASE_PASS '):
     completed+=1
     progress=dict(base,status='RUNNING',completed_cases=completed,elapsed_seconds=time.monotonic()-started,latest_case=line.strip())
     save(folder/'progress.json',progress)
     print(f'ICB {completed}/{case_count or 2} {line.strip()} elapsed={progress["elapsed_seconds"]:.1f}s',flush=True)
  code=process.wait();elapsed=time.monotonic()-started
  save(folder/'process.json',dict(base,status='EXITED',exit_code=code,elapsed_seconds=elapsed,completed_cases=completed,completed_utc=datetime.now(timezone.utc).isoformat()))
  if code:raise RuntimeError(f'vvp exit={code}: {(folder/"run.log").read_text()[-3000:]}')
  return elapsed
 finally:
  timeout.cancel()
  if process.poll() is None:process.kill();process.wait()
def main():
 p=argparse.ArgumentParser();p.add_argument('--mode',choices=['protocol','full','full36','repeat'],default='protocol');args=p.parse_args()
 folder=REPORT/args.mode;folder.mkdir(parents=True,exist_ok=True);status=folder/'status.json'
 lock=(REPORT/'run.lock').open('w');fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
 save(status,{'status':'RUNNING','mode':args.mode,'started_utc':datetime.now(timezone.utc).isoformat()})
 started=time.monotonic()
 try:
  mode=args.mode; m,n=(3,4) if mode=='protocol' else (99,256)
  before=fingerprint();extra=[];cases=[]
  if mode!='protocol':
   verify_vectors(ROOT,ROOT/'reports/model/baseline',VECTORS)
   manifest=json.loads((VECTORS/'manifest.json').read_text());cases=manifest['cases'] if mode=='full36' else manifest['cases'][:1]
   jobs=[str(len(cases))]
   for k,c in enumerate(cases):
    target=folder/f'{k:02d}';target.mkdir(exist_ok=True)
    a={key:load_array(VECTORS,c['arrays'][key],shape,dtype) for key,shape,dtype in [('Xq',(99,64),'int16'),('Wq_packed',(256,64),'int16'),('bq',(256,),'int64'),('Yq',(99,256),'int32'),('overflow',(99,256),'bool'),('output_saturated',(99,256),'bool')]}
    for key,bits in [('Xq',16),('Wq_packed',16),('bq',48)]:hexfile(target/f'{key}.hex',a[key],bits)
    expected=(a['Yq'].astype(np.int64)&0xffffffff).astype(np.uint64)|(a['overflow'].astype(np.uint64)<<32)|(a['output_saturated'].astype(np.uint64)<<33)
    hexfile(target/'expected.hex',expected,34)
    jobs.append(' '.join([c['case_id'],str(c['config']['output_shift']),*[f'{k:02d}/{x}.hex' for x in ['Xq','Wq_packed','bq','expected','actual']]]))
   (folder/'jobs.txt').write_text('\n'.join(jobs)+'\n');extra=['+jobs=jobs.txt']
  else: extra=['+trace=1']
  command=['/usr/bin/iverilog','-g2012','-s','tb_icb',f'-Ptb_icb.M={m}',f'-Ptb_icb.N={n}','-o',str(folder/'sim.vvp'),*map(str,SOURCES),str(TB)]
  lint=['/usr/bin/verilator','--lint-only','--top-module','ffn1_icb','-Wall','-Wno-fatal',*map(str,SOURCES)]
  with (folder/'lint.log').open('w') as log:subprocess.run(lint,stdout=log,stderr=subprocess.STDOUT,check=True)
  simulation=['/usr/bin/vvp',str(folder/'sim.vvp'),*extra]
  save(folder/'commands.json',{'lint':lint,'compile':command,'simulation':simulation,'simulation_cwd':str(folder)})
  with (folder/'compile.log').open('w') as log:subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True)
  simulation_elapsed=simulate(folder,simulation,len(cases))
  text=(folder/'run.log').read_text(); records=[]
  if mode=='protocol':
   match=re.search(r'PROTOCOL_PASS M=3 N=4 outputs=(\d+) transactions=(\d+)',text)
   if not match or not (folder/'protocol.vcd').exists():raise ValueError('protocol evidence missing')
   result={'outputs':int(match[1]),'transactions':int(match[2]),'wave_sha256':sha(folder/'protocol.vcd')}
  else:
   verify_vectors(ROOT,ROOT/'reports/model/baseline',VECTORS)
   for k,c in enumerate(cases):
    output=folder/f'{k:02d}/actual.hex';lines=output.read_text().splitlines()
    if len(lines)!=25344 or any(not re.fullmatch('[0-3][0-9a-f]{8}',line) for line in lines):raise ValueError('invalid output file')
    expected=(folder/f'{k:02d}/expected.hex').read_bytes()
    if output.read_bytes()!=expected:raise ValueError('output/reference mismatch')
    match=re.findall(rf'CASE_PASS {re.escape(c["case_id"])} outputs=25344 cycles=(\d+) macs=1622016',text)
    if len(match)!=1:raise ValueError('missing/duplicate case evidence')
    records.append({'case_id':c['case_id'],'sample_id':c['sample_id'],'layer':c['layer'],'output_count':25344,'output_sha256':sha(output),'expected_sha256':sha(folder/f'{k:02d}/expected.hex'),'output_file':str(output.relative_to(ROOT)),'cycles':int(match[0]),'actual_macs':1622016,'mismatches':0,'input_array_sha256':{name:c['arrays'][name]['sha256'] for name in ['Xq','Wq_packed','bq']},'integer_reference_sha256':c['arrays']['Yq']['sha256'],'numeric_metrics':c['metrics'],'saturation':c['saturation']})
   completion=re.findall(rf'ALL_PASS cases={len(cases)} outputs={len(cases)*25344} transactions=(\d+)',text)
   if len(completion)!=1 or text.count('CASE_PASS ')!=len(cases) or text.count('ALL_PASS ')!=1:raise ValueError('missing/duplicate completion')
   result={'case_count':len(cases),'output_count':len(cases)*25344,'actual_macs':len(cases)*1622016,'transactions':int(completion[0]),'cases':records,'rtl_reference_mismatches':0}
   if mode=='repeat':
    accepted=None
    for baseline in [REPORT/'full36/status.json',REPORT/'full/status.json']:
     if baseline.exists():
      old=json.loads(baseline.read_text())
      if old.get('status')=='PASS' and old.get('fingerprints')==before:accepted=(baseline,old);break
    if accepted is None:raise ValueError('repeat requires current full36 or full PASS baseline')
    baseline,old=accepted
    if old['cases'][0]['output_sha256']!=records[0]['output_sha256']:raise ValueError('independent repeat mismatch')
    result['repeat_baseline']=str(baseline.relative_to(ROOT));result['repeat_baseline_sha256']=sha(baseline)
  if fingerprint()!=before:raise ValueError('sources changed during simulation')
  result.update(status='PASS',mode=mode,fingerprints=before,log_sha256=sha(folder/'run.log'),lint_sha256=sha(folder/'lint.log'),exit_code=0,elapsed_seconds=time.monotonic()-started,simulation_elapsed_seconds=simulation_elapsed,completed_utc=datetime.now(timezone.utc).isoformat())
  save(folder/'progress.json',{'status':'PASS','mode':mode,'completed_cases':len(cases),'completed_utc':result['completed_utc']})
  save(status,result);print(f'ICB {mode} PASS',flush=True)
 except BaseException as e:save(status,{'status':'FAIL','error':str(e),'exit_code':1});raise
if __name__=='__main__':main()
