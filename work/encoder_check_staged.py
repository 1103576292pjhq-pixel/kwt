"""Observe currently running CPU staged inputs; never claim CPU completion."""
from pathlib import Path
import json
import sys
import time

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
from formal_seven_gate import sha,validate_cpu_consumed_files

def read(path):return json.loads(path.read_text(encoding='utf-8-sig'))

def main():
 observed=time.time();start=read(ROOT/'work/encoder_long_validation.json')['started_unix']
 sid=read(ROOT/'reports/encoder/reference/manifest.json')['samples'][0]['sample_id'];records={}
 for name in ('pingpong','reload'):
  out=ROOT/'reports/encoder/system'/name;progress=read(out/'progress.json')
  # completed_unix here is only a local command-log interval upper bound.
  # It is not written as CPU completion and no PASS CPU status is created.
  probe={'case':sid,'command':progress['command'],'started_unix':start,'completed_unix':observed}
  records[name]={'observed_pid':progress['pid'],'artifacts_sha256':validate_cpu_consumed_files(probe,out)}
 target=ROOT/'reports/encoder/system/staging-readback.json'
 target.write_text(json.dumps({'status':'STAGING_ONLY_CURRENT_CPU_COMPLETION_NOT_ACCEPTED','observed_unix':observed,
  'scope':'Readback during active CPU run; no before-start snapshot is invented.',
  'source_sha256':{'scripts/formal_seven_gate.py':sha(ROOT/'scripts/formal_seven_gate.py'),'work/encoder_check_staged.py':sha(Path(__file__))},'observations':records},indent=2)+'\n',encoding='utf-8')
 print('STAGED_CPU_INPUTS_CURRENT policies=2 artifacts_each=18 CPU_COMPLETION_NOT_ACCEPTED')

if __name__=='__main__':main()
