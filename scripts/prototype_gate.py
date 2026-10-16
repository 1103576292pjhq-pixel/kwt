"""Fail-closed prototype acceptance: re-read files, hashes, outputs, XML and reviews."""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import importlib.util
import hashlib
import json
from pathlib import Path
import sys
import time
import uuid
import xml.etree.ElementTree as ET

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
REPORT=ROOT/'reports/prototype'
STATUS=ROOT/'work/prototype_status.json'
GATE_TEST_COUNT=39
DOT_REQUIRED_PATHS=frozenset({
    'rtl/dot64.sv','dv/dot64/test_dot64.py','dv/dot64/run_dot64.py',
    'dv/dot64/inspect_wave.py','reports/prototype/dot64/results.xml',
    'reports/prototype/dot64/build/dot64.fst','reports/prototype/dot64/dot64.vcd',
})
UNIT_REQUIRED={
    'numeric':frozenset({
        'numeric/__init__.py','numeric/artifacts.py','numeric/fixedpoint.py',
        'tests/numeric/test_artifacts.py','tests/numeric/test_fixedpoint.py',
        'tests/numeric/test_generator_safety.py','scripts/generate_prototype_vectors.py',
        'config/prototype-numeric.json',
    }),
    'gate':frozenset({'scripts/prototype_gate.py','scripts/run_prototype.sh','dv/ffn1/test_gate.py'}),
}


def read_json(path):
    return json.loads(path.read_text(encoding='utf-8'))


def write_json(path,value):
    path.parent.mkdir(parents=True,exist_ok=True)
    temp=path.with_suffix('.tmp')
    temp.write_text(json.dumps(value,indent=2,allow_nan=False)+'\n',encoding='utf-8')
    temp.replace(path)


def validate_xml(path, expected):
    root=ET.parse(path).getroot()
    tests=root.findall('.//testcase')
    if len(tests)!=expected or any(root.findall('.//'+name) for name in ['failure','error','skipped']):
        raise ValueError(f'invalid XML count/failure/skip: {path}')
    identifiers=[(test.get('classname',''),test.get('name','')) for test in tests]
    if any(not name for _,name in identifiers) or len(set(identifiers))!=len(identifiers):
        raise ValueError(f'missing or duplicate XML testcase identifiers: {path}')
    return len(tests)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def validate_dot_hashes(hashes):
    if not isinstance(hashes,dict) or set(hashes)!=DOT_REQUIRED_PATHS:
        raise ValueError('DOT64 hash inventory must contain exactly the seven required paths')
    for relative in sorted(DOT_REQUIRED_PATHS):
        if digest(ROOT/relative)!=hashes[relative]:
            raise ValueError(f'DOT64 stale artifact: {relative}')


def expected_unit_count(group):
    count=read_json(ROOT/'work/numeric_handoff.json')['tests'] if group=='numeric' else GATE_TEST_COUNT
    if isinstance(count,bool) or not isinstance(count,int) or count<(48 if group=='numeric' else 1):
        raise ValueError('invalid required unit test count')
    return count


def unit_sources(group):
    if group not in UNIT_REQUIRED:
        raise ValueError('unknown unit group')
    paths=set(UNIT_REQUIRED[group])
    if group=='numeric':
        paths.update(str(path.relative_to(ROOT)) for pattern in ['numeric/*.py','tests/numeric/*.py']
                     for path in ROOT.glob(pattern))
    return {relative:digest(ROOT/relative) for relative in sorted(paths)}


def unit_paths(group):
    if group not in UNIT_REQUIRED:
        raise ValueError('unknown unit group')
    return (REPORT/f'integration-{group}.unit-start.json',
            REPORT/f'integration-{group}.unit.json',REPORT/f'integration-{group}.xml')


def unit_start(group):
    start_path,binding_path,xml_path=unit_paths(group)
    run_id=uuid.uuid4().hex
    # Invalidate a previous PASS before any snapshot or pytest execution.
    write_json(binding_path,{'status':'RUNNING','run_id':run_id})
    xml_path.unlink(missing_ok=True)
    value={'status':'RUNNING','group':group,'run_id':run_id,'expected_tests':expected_unit_count(group),
           'source_hashes_before':unit_sources(group),'started_ns':time.time_ns()}
    write_json(start_path,value)
    return value


def unit_finish(group):
    start_path,binding_path,xml_path=unit_paths(group)
    start,binding=read_json(start_path),read_json(binding_path)
    if (start['status']!='RUNNING' or binding['status']!='RUNNING' or
        start['run_id']!=binding['run_id'] or start['group']!=group):
        raise ValueError('unit finish requires the current unconsumed start record')
    after=unit_sources(group)
    if start['source_hashes_before']!=after or start['expected_tests']!=expected_unit_count(group):
        raise ValueError('unit sources/configuration changed during execution')
    # start removes the old XML; also reject one restored with an old timestamp.
    if xml_path.stat().st_mtime_ns<start_path.stat().st_mtime_ns:
        raise ValueError('unit XML predates this execution start')
    count=validate_xml(xml_path,start['expected_tests'])
    result={'status':'PASS','group':group,'run_id':start['run_id'],'tests':count,
            'expected_tests':start['expected_tests'],'source_hashes_before':start['source_hashes_before'],
            'source_hashes_after':after,'xml_path':str(xml_path.relative_to(ROOT)),
            'xml_sha256':digest(xml_path),'finished_ns':time.time_ns()}
    start['status']='FINISHED'
    write_json(start_path,start)
    write_json(binding_path,result)
    return result


def verify_unit_binding(group):
    start_path,binding_path,xml_path=unit_paths(group)
    start,binding=read_json(start_path),read_json(binding_path)
    current=unit_sources(group)
    expected=expected_unit_count(group)
    if (binding['status']!='PASS' or start['status']!='FINISHED' or
        binding['group']!=group or start['group']!=group or binding['run_id']!=start['run_id'] or
        start['expected_tests']!=expected or binding['expected_tests']!=expected or binding['tests']!=expected or
        start['source_hashes_before']!=current or binding['source_hashes_before']!=current or
        binding['source_hashes_after']!=current or binding['xml_path']!=str(xml_path.relative_to(ROOT))):
        raise ValueError('unit execution binding is incomplete or stale')
    if binding['xml_sha256']!=digest(xml_path):
        raise ValueError('unit XML changed after execution')
    validate_xml(xml_path,expected)
    return binding


def validate_totals(value, count):
    if (value.get('status')!='PASS' or value.get('case_count')!=count or
        value.get('output_count')!=count*25344 or value.get('actual_macs')!=count*1622016 or
        value.get('rtl_reference_mismatches')!=0):
        raise ValueError('incomplete or failed full-size matrix evidence')


def load_dv():
    spec=importlib.util.spec_from_file_location('ffn1_runner',ROOT/'dv/ffn1/run_ffn1.py')
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def review_sources():
    dv=load_dv()
    # This batch's evidence covers its exact design hierarchy. Other accelerators
    # have separate gates; adding one must not silently expand this review scope.
    paths=[*(ROOT/p for p in ('rtl/dot64.sv','rtl/ffn1_top.sv','rtl/prototype_sync_ram.sv')),
           *ROOT.glob('dv/ffn1/*.py'),*ROOT.glob('dv/ffn1/*.sv'),
           *ROOT.glob('dv/dot64/*.py'),*ROOT.glob('numeric/*.py'),*ROOT.glob('tests/numeric/*.py'),
           ROOT/'scripts/prototype_gate.py',ROOT/'scripts/run_prototype.sh',
           ROOT/'scripts/generate_prototype_vectors.py',ROOT/'scripts/run_dot64.sh',
           ROOT/'config/prototype-numeric.json']
    return {str(p.relative_to(ROOT)):dv.digest(p) for p in sorted(paths)}


def preflight():
    from numeric.artifacts import verify_vectors
    for name in ['numeric','dot64']:
        if read_json(ROOT/f'work/{name}_handoff.json')['status']!='PASS':
            raise ValueError(f'{name} handoff incomplete')
    result=verify_vectors(ROOT,ROOT/'reports/model/baseline',REPORT/'vectors')
    if result['case_count']!=36 or result['output_count']!=912384 or result['official_files_verified']!=124:
        raise ValueError('vector verification incomplete')
    write_json(REPORT/'integration-numeric.json',result)
    return result


def verify_existing():
    dv=load_dv()
    current=dv.fingerprints()
    manifest=read_json(REPORT/'vectors/manifest.json')
    full=None
    for mode,count in [('full',36),('repeat',1)]:
        folder=REPORT/f'ffn1/{mode}'
        result=read_json(folder/'status.json')
        validate_totals(result,count)
        if result['fingerprints']!=current or result['log_sha256']!=dv.digest(folder/'run.log'):
            raise ValueError(f'{mode} evidence is stale')
        records=dv.verify_results(manifest['cases'][:count],folder,(folder/'run.log').read_text())
        if records!=result['cases']:
            raise ValueError(f'{mode} recorded evidence differs from real outputs')
        if mode=='full': full=result
        elif result['cases'][0]['output_sha256']!=full['cases'][0]['output_sha256']:
            raise ValueError('repeat output hash mismatch')
    return full


def finalize():
    numeric=preflight()
    dv=load_dv()
    verify_unit_binding('numeric')
    verify_unit_binding('gate')
    dot=read_json(REPORT/'dot64/status.json')
    if dot['status']!='PASS' or dot['tests']!=8 or dot['failures'] or dot['skips'] or dot['lint']!='PASS':
        raise ValueError('DOT64 acceptance incomplete')
    validate_xml(REPORT/'dot64/results.xml',8)
    validate_dot_hashes(dot['hashes'])
    protocol=read_json(REPORT/'ffn1/protocol/status.json')
    if (protocol['status']!='PASS' or protocol['fingerprints']!=dv.fingerprints() or
        protocol['log_sha256']!=dv.digest(REPORT/'ffn1/protocol/run.log') or
        protocol['wave_sha256']!=dv.digest(REPORT/'ffn1/protocol/protocol.vcd')):
        raise ValueError('FFN1 protocol evidence missing/stale')
    full=verify_existing()
    lint=read_json(REPORT/'ffn1/lint.json')
    if lint['status']!='PASS' or lint['fingerprints']!=dv.fingerprints():
        raise ValueError('FFN1 lint absent/stale')
    review=read_json(REPORT/'review.json')
    if (review['status']!='PASS' or review['rounds']<2 or review['unresolved_major'] or
        review['source_hashes']!=review_sources()):
        raise ValueError('two-round self-review incomplete/stale')
    for name in ['review-spec.md','review-quality.md']:
        if dv.digest(REPORT/name)!=review['report_hashes'][name]:
            raise ValueError('review report changed after review')
    if numeric['max_case_nrmse']>0.03:
        raise ValueError('fixed numeric subset exceeds 3%; retain actual report')
    write_json(STATUS,{
        'status':'READY_FOR_REVIEW','numeric':True,'dot64':True,'ffn1':True,
        'full_matrix_cases':full['case_count'],'outputs':full['output_count'],
        'actual_macs':full['actual_macs'],'full_size_repeat_cases':1,
        'rtl_reference_mismatches':0,'max_case_nrmse':numeric['max_case_nrmse'],
        'max_layer_nrmse':numeric['max_layer_nrmse'],
        'reports':{'numeric':'reports/prototype/vectors/manifest.json','dot64':'reports/prototype/dot64/status.json',
                   'ffn1':'reports/prototype/ffn1/full/status.json','repeat':'reports/prototype/ffn1/repeat/status.json',
                   'review':'reports/prototype/review.json'},
        'completed_utc':datetime.now(timezone.utc).isoformat(),
        'scope':'36 frozen cases only; no official 600-sample, E203, 150MHz or PPA acceptance'})


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action',choices=['begin','failed','preflight','verify-existing','lint','finalize',
                                         'unit-start','unit-finish'])
    parser.add_argument('--group',choices=['numeric','gate'])
    args=parser.parse_args()
    try:
        if args.action in ['begin','failed']:
            write_json(STATUS,{'status':'RUNNING' if args.action=='begin' else 'FAILED',
                'numeric':False,'dot64':False,'ffn1':False,'full_matrix_cases':0,
                'updated_utc':datetime.now(timezone.utc).isoformat()})
        elif args.action in ['unit-start','unit-finish']:
            if args.group is None: parser.error('--group is required for unit actions')
            (unit_start if args.action=='unit-start' else unit_finish)(args.group)
        elif args.action=='preflight': preflight()
        elif args.action=='verify-existing': verify_existing()
        elif args.action=='finalize': finalize()
        elif args.action=='lint':
            import subprocess
            dv=load_dv()
            before=dv.fingerprints()
            with (REPORT/'ffn1/lint.log').open('w') as log:
                subprocess.run(['/usr/bin/verilator','--lint-only','--Wall','-Wno-PINCONNECTEMPTY',
                    '-Wno-UNUSEDSIGNAL','--top-module','ffn1_top',*map(str,dv.SOURCES)],
                    check=True,stdout=log,stderr=subprocess.STDOUT)
            if before!=dv.fingerprints(): raise ValueError('RTL changed during lint')
            write_json(REPORT/'ffn1/lint.json',{'status':'PASS','exit_code':0,'fingerprints':before})
        print(f'prototype gate {args.action}: PASS',flush=True)
    except BaseException as error:
        if args.action!='begin':
            write_json(STATUS,{'status':'FAILED','numeric':False,'dot64':False,'ffn1':False,
                              'full_matrix_cases':0,'error':str(error)})
        raise


if __name__=='__main__': main()
