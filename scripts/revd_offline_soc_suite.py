#!/usr/bin/env python3
"""Freshly audit six two-task CPU reports as a bounded twelve-layer suite."""
import argparse
import re
from pathlib import Path
import sys
import numpy as np
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--reports',nargs=6,required=True);args=parser.parse_args()
    expected_cases=read_json(ROOT/'reports/prototype/vectors/manifest.json')['cases'][:12]
    expected_ids={case['case_id'] for case in expected_cases};seen=set();rows=[];report_hashes={};boots=[]
    output_total=0
    for name in args.reports:
        path=ROOT/name;report=read_json(path);cpu=report['results']['cpu'];metrics=cpu['metrics']
        if report['status']!='PASS' or not report['source_unchanged'] or cpu['command']['exit_code']!=0:
            raise RuntimeError('unsuccessful CPU evidence '+name)
        if metrics['tasks']!=2 or metrics['outputs']!=50688 or metrics['flags']!=50688 or metrics['response_outputs']!=50688 or metrics['response_flags']!=50688:
            raise RuntimeError('incomplete CPU geometry/responses '+name)
        for relative,digest in report['source_sha256'].items():
            if sha(ROOT/relative)!=digest:raise RuntimeError('current source mismatch '+relative)
        for relative,digest in report['input_sha256'].items():
            if sha(ROOT/relative)!=digest:raise RuntimeError('current input mismatch '+relative)
        for relative,digest in report['artifacts_sha256'].items():
            if sha(path.parent/relative)!=digest:raise RuntimeError('artifact changed '+relative)
        binary=Path(cpu['command']['argv'][0]);boots.append({'report':name,'actual_binary_sha256':sha(binary),
                                                          'pid':cpu['command']['pid'],'exit_code':0})
        actual_log=(path.parent/'cpu.log').read_text()
        match=re.search(r'E203_REVD_PASS ([^\n]+)',actual_log)
        if not match or {k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])}!=metrics:
            raise RuntimeError('CPU metrics do not match actual simulator log')
        if read_json(path.parent/'cpu.log.command.json')!=cpu['command']:
            raise RuntimeError('CPU command differs from actual command record')
        wanted={'cpu-output.txt':[],'cpu-flags.txt':[]}
        for task,window in zip(report['cases'],cpu['task_metrics'],strict=True):
            case_id=task['case_id']
            if case_id not in expected_ids or case_id in seen or task['outputs']!=25344 or window['effective_macs']!=1622016:
                raise RuntimeError('wrong, duplicate or incomplete layer '+case_id)
            source=next(case for case in expected_cases if case['case_id']==case_id)
            if task['layer']!=source['layer'] or task['shift']!=source['config']['output_shift']:
                raise RuntimeError('numeric parameter changed '+case_id)
            vector_root=ROOT/'reports/prototype/vectors'
            y=np.load(vector_root/source['arrays']['Yq']['path'],allow_pickle=False).reshape(-1)
            flags=np.load(vector_root/source['arrays']['overflow']['path'],allow_pickle=False).astype('u1')
            flags|=np.load(vector_root/source['arrays']['output_saturated']['path'],allow_pickle=False).astype('u1')<<1
            flags=flags.reshape(-1);flags[-1]|=4
            wanted['cpu-output.txt'].append([int(value)&0xffffffff for value in y])
            wanted['cpu-flags.txt'].append([int(value) for value in flags])
            seen.add(case_id);rows.append({'case_id':case_id,'layer':task['layer'],'cold_cycles':window['cold_cycles'],
                                          'effective_macs':window['effective_macs'],'report':name})
        output_total+=metrics['outputs'];report_hashes[name]=sha(path)
        for filename,expected in wanted.items():
            actual_seen=set();lines=(path.parent/'cpu'/filename).read_text().splitlines()
            if len(lines)!=50688:raise RuntimeError('actual CPU record count mismatch')
            for line in lines:
                task,index,value=line.split();task=int(task);index=int(index);value=int(value,16)
                key=(task,index)
                if task not in [0,1] or not 0<=index<25344 or key in actual_seen or value!=expected[task][index]:
                    raise RuntimeError('actual CPU data/flags/index duplicate or mismatch')
                actual_seen.add(key)
    if seen!=expected_ids or output_total!=304128:raise RuntimeError('twelve-task suite incomplete')
    out=ROOT/'reports/revd_offline/soc'/('suite-'+run_id());out.mkdir(parents=True,exist_ok=False)
    result={'status':'PASS','checked_utc':utc(),'scope':'12 independent FFN1 cold parameter tasks for one frozen engineering input, executed by real E203 C firmware in 6 boots of 2 tasks each.',
      'real_cpu_boots':6,'full_tasks':12,'unique_y_results':output_total,'unique_flag_records':output_total,
      'layers':sorted(rows,key=lambda row:row['layer']),'boots':boots,'source_and_artifact_refresh':True,
      'report_sha256':report_hashes,'suite_script_sha256':sha(Path(__file__)),'official_contest_acceptance':False,
      'limitations':['Not an end-to-end encoder; each layer consumes its own frozen input.','Only one of the three engineering inputs covered by this CPU suite; core36 is separate.','No official600, contest platform, physical timing, area or energy acceptance.']}
    put(out/'result.json',result);print('SOC_SUITE',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
