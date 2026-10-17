#!/usr/bin/env python3
"""Attach actual simulator/firmware byte hashes without editing accepted reports."""
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,put,read_json,sha,utc

def bind(report_path):
    path=Path(report_path)
    if not path.is_absolute():path=ROOT/path
    report=read_json(path)
    if report['status']!='PASS':raise RuntimeError('cannot bind unsuccessful CPU report')
    executable=Path(report['results']['cpu']['command']['argv'][0])
    if not executable.resolve().is_relative_to(ROOT.resolve()):raise RuntimeError('CPU executable outside workspace')
    target=path.parent/'binary-binding.json'
    if target.exists():raise RuntimeError('refuse to overwrite binary binding')
    binding={'status':'VERIFIED','checked_utc':utc(),'original_report':str(path.relative_to(ROOT)),
      'original_report_sha256':sha(path),'actual_executable':str(executable.relative_to(ROOT)),
      'actual_executable_sha256':sha(executable),'firmware_binary_sha256':sha(path.parent/'revd-driver.bin'),
      'cpu_command_record_sha256':sha(path.parent/'cpu.log.command.json'),
      'cpu_log_sha256':sha(path.parent/'cpu.log'),'binding_script_sha256':sha(Path(__file__)),
      'historical_report_modified':False}
    if binding['cpu_log_sha256']!=report['results']['cpu']['command']['log_sha256']:
        raise RuntimeError('CPU log differs from accepted record')
    put(target,binding);print('SOC_BINARY_BINDING',target.relative_to(ROOT),flush=True)
    return binding
if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('--report',required=True);args=parser.parse_args();bind(args.report)
