"""Read actual local processes and progress once; this never accepts results."""
from pathlib import Path
import hashlib
import json
import time

ROOT=Path(__file__).resolve().parents[2]

def load(path):
 return json.loads(path.read_text(encoding='utf-8-sig')) if path.is_file() else {}

def alive(pid,command):
 try:
  actual=(Path('/proc')/str(pid)/'cmdline').read_bytes().replace(b'\0',b' ').decode('utf-8')
  return bool(command and command[0] in actual),actual
 except (OSError,UnicodeDecodeError):return False,''

def main():
 now=time.time();items=[]
 for name,rel in [('cpu_pingpong','system/pingpong'),('cpu_reload','system/reload')]+[(f'rtl_{p.name}',str(p.relative_to(ROOT/'reports/encoder'))) for p in sorted((ROOT/'reports/encoder/rtl/full').glob('*')) if p.is_dir()]+[('rtl_repeat','rtl/repeat')]:
  folder=ROOT/'reports/encoder'/rel;progress=load(folder/'progress.json');status=load(folder/'status.json')
  running,actual=alive(progress.get('pid'),progress.get('command'))
  log=folder/'simulation.log';text=log.read_text(encoding='utf-8') if log.is_file() else ''
  layers=[line for line in text.splitlines() if 'ENCODER_LAYER_PASS' in line]
  items.append({'name':name,'producer_status':status.get('status','NOT_STARTED'),
                'process_matches_progress':running,'pid':progress.get('pid'),'command':progress.get('command'),
                'actual_process':actual,'progress_age_seconds':round(now-(folder/'progress.json').stat().st_mtime,1) if (folder/'progress.json').is_file() else None,
                'cycles':load(folder/'cycle-progress.json'),'completed_layer_markers':layers,
                'last_log_lines':text.splitlines()[-2:],'record':str((folder/'status.json').relative_to(ROOT))})
 freeze=ROOT/'work/encoder_source_freeze.json';manifest=load(freeze)
 stale=[rel for rel,digest in manifest.get('source_sha256',{}).items() if not (ROOT/rel).is_file() or hashlib.sha256((ROOT/rel).read_bytes()).hexdigest()!=digest]
 batch=load(ROOT/'reports/encoder/verification/case-batch/progress.json')
 batch_final=load(ROOT/'reports/encoder/verification/case-batch/status.json')
 if batch_final.get('run_id')==batch.get('run_id') and batch_final.get('status') in {'PASS','FAIL'}:
  batch={**batch,**batch_final}
 result={'status':'OBSERVATION_ONLY','observed_unix':now,'source_freeze_current':not stale,'stale_sources':stale,
         'batch':batch,'items':items,
         'scope':'Live process/progress observation; result acceptance remains the typed formal_seven_gate.'}
 (ROOT/'work/encoder_live_checkpoint.json').write_text(json.dumps(result,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
 summary=[f'FREEZE_CURRENT={not stale}',f'BATCH={result["batch"].get("completed")}/{result["batch"].get("target_cases")}']
 for r in items:
  if r['process_matches_progress']:
   c=r['cycles']
   summary.append(f'{r["name"]}:PID{r["pid"]}:cycles={c.get("cycles","-")}:started={c.get("started_layers","-")}:words={c.get("neural_words","-")}:RTL_layers={len(r["completed_layer_markers"])}')
 print(' '.join(summary))

if __name__=='__main__':main()
