#!/usr/bin/env python3
"""Software-only subprocess-status negative gate checks, never RTL evidence."""
from pathlib import Path
import sys
from unittest.mock import patch
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_w2_run as w2
from revd_offline_common import ROOT,put,run_id,sha,utc

def main():
    out=ROOT/'reports/revd_offline/soc'/('w2-software-controls-'+run_id());out.mkdir(parents=True,exist_ok=False)
    results=[];report={'status':'RUNNING','scope':'Software-only mocked process records; no real RTL/CPU processes and no RTL mutation credit.',
      'started_utc':utc(),'w2_runner_sha256':sha(Path(w2.__file__)),'test_sha256':sha(Path(__file__))}
    try:
        for code in [124,None,-999,-9,0,-6]:
            folder=out/str(code);folder.mkdir()
            def fake(argv,path,**kwargs):
                Path(path).write_text('CPU_EXIT_FAILURE precise-test-marker\n')
                return {'exit_code':code,'seconds':0,'log':str(Path(path).relative_to(ROOT)),'software_mock':True}
            accepted=False
            with patch.object(w2.soc,'command',fake):
                try:w2.Run(folder).cmd('control',['unused'],negative='CPU_EXIT_FAILURE');accepted=True
                except RuntimeError:pass
            expected=code==-6
            results.append({'mock_exit_code':code,'accepted':accepted,'expected_accept':expected})
            if accepted!=expected:raise RuntimeError('W2 accepted incomplete/invalid subprocess status '+str(code))
        report['status']='PASS'
    except Exception as exc:
        report.update(status='FAIL',error=str(exc));raise
    finally:
        report.update(results=results,finished_utc=utc());put(out/'result.json',report)
        print('W2_SOFTWARE_CONTROLS',out.relative_to(ROOT),report['status'],flush=True)
if __name__=='__main__':main()
