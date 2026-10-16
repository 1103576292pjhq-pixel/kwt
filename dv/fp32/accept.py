#!/usr/bin/env python3
"""Read-only evidence checks, then write the FP32 handoff manifest."""
from pathlib import Path
import datetime as dt
import hashlib
import json
import re
import subprocess
from hardfloat_sources import ROOT

REPORT=ROOT/'reports/encoder/fp32'
def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    previous=json.loads((ROOT/'work/fp32_handoff.json').read_text(encoding='utf-8'))
    archive_relative=previous.get('archive',previous.get('revalidation',{}).get('archive'))
    assert archive_relative,'Missing historical evidence archive'
    archive=ROOT/str(archive_relative).replace('\\','/')
    evidence={}
    for name in ['all','repeat','synthesis','mutations','red','cold-red','cold-green','cold-repeat','cold-unknown',
                 'mutation-cold_zero_decode_bypassed','mutation-unknown_class_casex_masked']:
        p=REPORT/name/'status.json'
        data=json.loads(p.read_text(encoding='utf-8'))
        expected_red=name in ('red','cold-red','mutation-cold_zero_decode_bypassed','mutation-unknown_class_casex_masked')
        assert data['status']==('EXPECTED_BEHAVIORAL_RED' if expected_red else 'PASS'),name
        for relative,digest in data['artifacts'].items(): assert sha(ROOT/relative)==digest,relative
        if name not in ('red',):
            for relative,digest in data['inputs']['sha256'].items(): assert sha(ROOT/relative)==digest,relative
        evidence[name]=data
    a=evidence['all'];b=evidence['repeat']
    assert a['inputs']==b['inputs']
    assert a['vector_count']==b['vector_count']==21291
    assert a['vector_sha256']==b['vector_sha256']
    assert a['results_sha256']==b['results_sha256']
    assert sha(REPORT/'all/iverilog/results.hex')==a['results_sha256']
    assert all(c['exit_code']==0 for c in a['commands']+b['commands']+evidence['synthesis']['commands'])
    assert len(evidence['mutations']['mutations'])==7
    assert all(m['compiled'] and m['killed'] for m in evidence['mutations']['mutations'].values())
    for mutant in evidence['mutations']['mutations'].values():
        if 'cold_status_path' in mutant:
            assert sha(ROOT/mutant['cold_status_path'])==mutant['cold_status_sha256']
    cold=evidence['cold-green'];cold_repeat=evidence['cold-repeat']
    assert cold['inputs']==cold_repeat['inputs']
    assert cold['cases']==cold_repeat['cases']
    assert len(cold['cases']['iverilog'])==len(cold['cases']['verilator'])==34
    assert cold['cases']['iverilog']==cold['cases']['verilator']
    assert all(c['pass'] for sim in cold['cases'].values() for c in sim.values())
    assert all(c['exit_code']==0 for c in cold['commands']+cold_repeat['commands']+evidence['cold-unknown']['commands'])
    cold_red=evidence['cold-red']
    old_rtl=archive/'source/rtl/encoder_fp32.sv'
    assert cold_red['rtl_sha256']==sha(old_rtl)
    assert sha(ROOT/'rtl/encoder_fp32.sv')!=cold_red['rtl_sha256']
    assert any(c['exit_code']==1 and 'positive_zero_div_two/run.log' in c['log'] for c in cold_red['commands'])
    assert all(c['exit_code']==0 for c in cold_red['commands'] if 'compile.log' in c['log'])
    initial=json.loads((archive/'initial-cold-red/status.json').read_text(encoding='utf-8'))
    assert initial['status']=='EXPECTED_BEHAVIORAL_RED'
    assert initial['rtl_sha256']==sha(old_rtl)
    old_all=json.loads((archive/'reports/all/status.json').read_text(encoding='utf-8'))
    assert old_all['vector_sha256']==a['vector_sha256']
    assert old_all['results_sha256']==a['results_sha256']
    coverage={}
    log=(REPORT/'all/verilator/run.log').read_text(encoding='utf-8')
    for op,count,wait in re.findall(r'COVERAGE op=(\d+) count=(\d+) maximum_wait=(\d+)',log):
        coverage[op]={'transactions':int(count),'maximum_wait_cycles':int(wait)}
    assert set(coverage)=={str(i) for i in range(16)}
    assert 'FP32_PASS transactions=21291 cycles=246891 reset_interruptions=4' in log
    assert '23 passed' in (REPORT/'pytest.log').read_text(encoding='utf-8')
    upstream=json.loads((ROOT/'config/hardfloat-source-manifest.json').read_text(encoding='utf-8'))
    for item in upstream['files']:
        assert sha(ROOT/upstream['root']/item['path'])==item['sha256']
    sources=[ROOT/'rtl/encoder_fp32.sv',ROOT/'scripts/run_fp32.sh',
             ROOT/'work/encoder_fp32_contract.md',ROOT/'config/hardfloat-source-manifest.json']
    sources+=sorted(p for p in (ROOT/'dv/fp32').rglob('*') if p.is_file() and '__pycache__' not in p.parts)
    sources+=sorted(p for p in (ROOT/'tests/fp32').rglob('*') if p.is_file() and '__pycache__' not in p.parts)
    versions={}
    for name,cmd in [('gcc',['gcc','--version']),('iverilog',['iverilog','-V']),
                     ('verilator',['verilator','--version']),('yosys',['yosys','-V'])]:
        p=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,encoding='utf-8',check=True)
        versions[name]=p.stdout.splitlines()[0]
    handoff={'status':'PASS','created_utc':dt.datetime.now(dt.timezone.utc).isoformat(),
        'module':'rtl/encoder_fp32.sv','contract':'work/encoder_fp32_contract.md',
        'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in sources},
        'upstream_files_verified':len(upstream['files']),'tool_versions':versions,
        'coverage':coverage,'transactions_per_process':21291,'cycles_per_process':246891,
        'full_execution_processes':3,'simulators':['Verilator actual binary','Icarus actual vvp'],
        'reset_interruptions_per_process':4,'behavioral_mutants_killed':7,
        'initial_compilable_red':True,'oracle_known_value_tests':23,
        'cold_start_cases_per_simulator':34,'cold_start_full_execution_processes':136,
        'cold_start_warmup_operations':0,'unknown_class_injection':'Icarus four-state guard PASS; casex masking mutant killed.',
        'revalidation':{'reason':'P1 first special DIV cold-start X leakage fixed at recoded-to-IEEE boundary.',
            'archive':str(archive.relative_to(ROOT)),'old_rtl_sha256':sha(old_rtl),
            'initial_cold_red_status_sha256':sha(archive/'initial-cold-red/status.json'),
            'old_full_outputs_unchanged':True,'vendor_changed':False},
        'reference':'Independent standalone host C binary32 arithmetic, explicit fmaf/sqrtf/fenv, plus documented RISC-V exception/NaN/conversion rules.',
        'vector_sha256':a['vector_sha256'],'results_sha256':a['results_sha256'],
        'evidence_status_sha256':{name:sha(REPORT/name/'status.json') for name in evidence},
        'pytest_log_sha256':sha(REPORT/'pytest.log'),
        'limitations':[
            'No exhaustive IEEE/TestFloat/formal floating-point certification.',
            'Only round-nearest-even and canonical RISCV NaN are exposed.',
            'Generic Yosys structure only; no PDK mapping, frequency, physical area or power claim.',
            'Upstream generic default-parameter range/width warnings retained in logs.',
            'Full encoder/SoC accuracy and performance require separate integration verification.'
        ]}
    out=ROOT/'work/fp32_handoff.json';out.write_text(json.dumps(handoff,indent=2)+'\n',encoding='utf-8')
    assert json.loads(out.read_text(encoding='utf-8'))==handoff
    print('FP32_HANDOFF_PASS 21291 transactions x 3 processes; 34 cold cases x 2 simulators x 2 runs; 7 mutants; 23 oracle checks; 131 immutable upstream files')

if __name__=='__main__': main()
