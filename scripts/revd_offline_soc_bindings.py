#!/usr/bin/env python3
"""Attach actual simulator/firmware byte hashes without editing accepted reports."""
import argparse
import json
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,read_json,sha,utc

def bind(report_path):
    path=Path(report_path)
    if not path.is_absolute():path=ROOT/path
    path=path.resolve()
    if not path.is_relative_to(ROOT.resolve()):raise RuntimeError('CPU report outside workspace')
    target=path.parent/'binary-binding.json'
    if target.exists():raise RuntimeError('refuse to overwrite binary binding')
    report_digest=sha(path)
    report=read_json(path)
    if report['status']!='PASS':raise RuntimeError('cannot bind unsuccessful CPU report')
    cpu=report['results']['cpu'];command=cpu['command'];sim=report['profile']['sim']
    if cpu['status']!='PASS' or command['exit_code']!=0 or command not in report['commands']:
        raise RuntimeError('binding requires successful actual CPU subprocess')
    if sim not in ('verilator','icarus'):raise RuntimeError('unknown CPU simulator')
    executable=path.parent/('obj/Vsoc_cpu_tb' if sim=='verilator' else 'cpu.vvp')
    expected_argv=[str(executable)] if sim=='verilator' else ['vvp',str(executable)]
    if command['argv'][:len(expected_argv)]!=expected_argv or not executable.resolve().is_relative_to(ROOT.resolve()):
        raise RuntimeError('CPU executable path differs from expected report output')
    actual_digest=sha(executable)
    if report.get('compiled_simulator_sha256')!=actual_digest:
        raise RuntimeError('compiled simulator digest missing/changed before binding')
    log=path.parent/'cpu.log'
    if command['log']!=log.relative_to(ROOT).as_posix() or command!=read_json(path.parent/'cpu.log.command.json'):
        raise RuntimeError('CPU command differs from actual record')
    if 'E203_REVD_PASS ' not in log.read_text():raise RuntimeError('CPU pass marker missing')
    binding={'status':'VERIFIED','checked_utc':utc(),'original_report':path.relative_to(ROOT).as_posix(),
      'original_report_sha256':report_digest,'actual_executable':executable.relative_to(ROOT).as_posix(),
      'actual_executable_sha256':actual_digest,'firmware_binary_sha256':sha(path.parent/'revd-driver.bin'),
      'cpu_command_record_sha256':sha(path.parent/'cpu.log.command.json'),
      'cpu_log_sha256':sha(path.parent/'cpu.log'),'binding_script_sha256':sha(Path(__file__)),
      'historical_report_modified':False}
    if binding['cpu_log_sha256']!=report['results']['cpu']['command']['log_sha256']:
        raise RuntimeError('CPU log differs from accepted record')
    if sha(path)!=report_digest:raise RuntimeError('CPU report changed during binding')
    # The report is immutable; an external one-time receipt avoids a hash cycle.
    with target.open('x',encoding='utf-8') as stream:
        stream.write(json.dumps(binding,indent=2,allow_nan=False)+'\n')
    print('SOC_BINARY_BINDING',target.relative_to(ROOT),flush=True)
    return binding
if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('--report',required=True);args=parser.parse_args();bind(args.report)
