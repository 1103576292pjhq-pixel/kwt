"""Failure-injection tests for acceptance evidence, without running long simulations."""
import importlib.util
from pathlib import Path
import pytest
import json
import subprocess

ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('prototype_gate', ROOT/'scripts/prototype_gate.py')
gate=importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)


def test_prototype_review_scope_tracks_only_its_actual_rtl():
    paths = gate.review_sources()
    rtl = {p for p in paths if p.startswith('rtl/')}
    assert rtl == {'rtl/dot64.sv', 'rtl/ffn1_top.sv', 'rtl/prototype_sync_ram.sv'}


@pytest.mark.parametrize('body',[
    '<testsuite/>',
    '<testsuite><testcase><skipped/></testcase></testsuite>',
    '<testsuite><testcase><failure/></testcase></testsuite>',
    '<testsuite><testcase><error/></testcase></testsuite>',
])
def test_xml_rejects_missing_failed_or_skipped(tmp_path,body):
    p=tmp_path/'result.xml'; p.write_text(body)
    with pytest.raises(ValueError): gate.validate_xml(p,1)


def test_xml_accepts_exact_success(tmp_path):
    p=tmp_path/'result.xml'; p.write_text('<testsuite><testcase name="real"/></testsuite>')
    assert gate.validate_xml(p,1)==1


def test_xml_rejects_wrong_count(tmp_path):
    p=tmp_path/'result.xml'; p.write_text('<testsuite><testcase/></testsuite>')
    with pytest.raises(ValueError): gate.validate_xml(p,2)


@pytest.mark.parametrize('updates',[
    {'case_count':35}, {'output_count':912383}, {'actual_macs':0},
    {'rtl_reference_mismatches':1}, {'status':'RUNNING'},
])
def test_full_metadata_rejects_incomplete(updates):
    value={'status':'PASS','case_count':36,'output_count':912384,
           'actual_macs':58392576,'rtl_reference_mismatches':0}
    value.update(updates)
    with pytest.raises(ValueError): gate.validate_totals(value,36)


def test_full_metadata_accepts_exact_counts():
    gate.validate_totals({'status':'PASS','case_count':36,'output_count':912384,
                          'actual_macs':58392576,'rtl_reference_mismatches':0},36)


@pytest.mark.parametrize('interpreter',['missing','fails'])
def test_entry_invalidates_old_pass_even_if_python_cannot_start(tmp_path,interpreter):
    (tmp_path/'scripts').mkdir()
    script=tmp_path/'scripts/run_prototype.sh'
    script.write_bytes((ROOT/'scripts/run_prototype.sh').read_bytes())
    (tmp_path/'work').mkdir()
    status=tmp_path/'work/prototype_status.json'
    status.write_text('{"status":"READY_FOR_REVIEW","ffn1":true}')
    if interpreter=='fails':
        (tmp_path/'.venv-dv/bin').mkdir(parents=True)
        python=tmp_path/'.venv-dv/bin/python'
        python.write_text('#!/bin/sh\nexit 1\n')
        python.chmod(0o755)
    result=subprocess.run(['/usr/bin/bash',str(script)],cwd='/tmp',capture_output=True,timeout=10)
    assert result.returncode!=0
    assert json.loads(status.read_text())['status']=='FAILED'


DOT_PATHS={
    'rtl/dot64.sv','dv/dot64/test_dot64.py','dv/dot64/run_dot64.py',
    'dv/dot64/inspect_wave.py','reports/prototype/dot64/results.xml',
    'reports/prototype/dot64/build/dot64.fst','reports/prototype/dot64/dot64.vcd',
}


@pytest.mark.parametrize('damage',['empty','missing','extra','changed','absent'])
def test_dot_required_inventory_fails_closed(tmp_path,monkeypatch,damage):
    import hashlib
    hashes={}
    for relative in DOT_PATHS:
        path=tmp_path/relative; path.parent.mkdir(parents=True,exist_ok=True)
        path.write_text(relative)
        hashes[relative]=hashlib.sha256(path.read_bytes()).hexdigest()
    monkeypatch.setattr(gate,'ROOT',tmp_path)
    if damage=='empty': hashes={}
    elif damage=='missing': hashes.pop('rtl/dot64.sv')
    elif damage=='extra': hashes['unexpected']='0'*64
    elif damage=='changed': (tmp_path/'rtl/dot64.sv').write_text('changed')
    else: (tmp_path/'rtl/dot64.sv').unlink()
    with pytest.raises((ValueError,FileNotFoundError)):
        gate.validate_dot_hashes(hashes)


def test_dot_accepts_exact_inventory(tmp_path,monkeypatch):
    import hashlib
    hashes={}
    for relative in DOT_PATHS:
        path=tmp_path/relative; path.parent.mkdir(parents=True,exist_ok=True)
        path.write_text(relative)
        hashes[relative]=hashlib.sha256(path.read_bytes()).hexdigest()
    monkeypatch.setattr(gate,'ROOT',tmp_path)
    gate.validate_dot_hashes(hashes)


def test_xml_rejects_duplicate_test_identifiers(tmp_path):
    xml=tmp_path/'duplicate.xml'
    xml.write_text('<testsuite><testcase classname="a" name="same"/><testcase classname="a" name="same"/></testsuite>')
    with pytest.raises(ValueError): gate.validate_xml(xml,2)


@pytest.fixture
def unit_workspace(tmp_path,monkeypatch):
    monkeypatch.setattr(gate,'ROOT',tmp_path)
    monkeypatch.setattr(gate,'REPORT',tmp_path/'reports/prototype')
    monkeypatch.setattr(gate,'expected_unit_count',lambda group:1)
    for relative in [
        'scripts/prototype_gate.py','scripts/run_prototype.sh','dv/ffn1/test_gate.py',
        'numeric/__init__.py','numeric/artifacts.py','numeric/fixedpoint.py',
        'tests/numeric/test_artifacts.py','tests/numeric/test_fixedpoint.py',
        'tests/numeric/test_generator_safety.py','scripts/generate_prototype_vectors.py',
        'config/prototype-numeric.json',
    ]:
        path=tmp_path/relative; path.parent.mkdir(parents=True,exist_ok=True)
        path.write_text(relative)
    return tmp_path


def _unit_xml(group='gate',name='real'):
    path=gate.REPORT/f'integration-{group}.xml'
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(f'<testsuite><testcase classname="unit" name="{name}"/></testsuite>')
    return path


@pytest.mark.parametrize('group',['numeric','gate'])
def test_unit_start_finish_and_current_verification(unit_workspace,group):
    gate.unit_start(group)
    _unit_xml(group)
    gate.unit_finish(group)
    assert gate.verify_unit_binding(group)['tests']==1


@pytest.mark.parametrize('damage',['no-binding','no-xml','xml-changed','source-changed',
                                  'missing-source-key','wrong-count','duplicate-tests',
                                  'run-id-changed','source-before-changed'])
def test_unit_binding_rejects_stale_or_incomplete(unit_workspace,damage):
    gate.unit_start('gate'); xml=_unit_xml(); gate.unit_finish('gate')
    binding=gate.REPORT/'integration-gate.unit.json'
    value=json.loads(binding.read_text())
    if damage=='no-binding': binding.unlink()
    elif damage=='no-xml': xml.unlink()
    elif damage=='xml-changed': xml.write_text('<testsuite/>')
    elif damage=='source-changed': (unit_workspace/'scripts/prototype_gate.py').write_text('new code')
    elif damage=='missing-source-key': value['source_hashes_after'].pop('scripts/prototype_gate.py')
    elif damage=='wrong-count': value['tests']=2
    elif damage=='duplicate-tests':
        xml.write_text('<testsuite><testcase name="x"/><testcase name="x"/></testsuite>')
        import hashlib
        value['xml_sha256']=hashlib.sha256(xml.read_bytes()).hexdigest()
    elif damage=='run-id-changed': value['run_id']='stale'
    else: value['source_hashes_before']['scripts/prototype_gate.py']='0'*64
    if binding.exists(): binding.write_text(json.dumps(value))
    with pytest.raises((ValueError,FileNotFoundError)):
        gate.verify_unit_binding('gate')


@pytest.mark.parametrize('damage',['changed-source','old-xml','missing-xml','repeat-finish'])
def test_unit_finish_rejects_unproven_execution(unit_workspace,damage):
    import os
    old=_unit_xml().read_bytes()
    gate.unit_start('gate')
    assert not (gate.REPORT/'integration-gate.xml').exists()
    if damage!='missing-xml':
        xml=_unit_xml()
        if damage=='old-xml':
            xml.write_bytes(old)
            os.utime(xml,ns=(1,1))
        elif damage=='changed-source':
            (unit_workspace/'scripts/prototype_gate.py').write_text('changed while testing')
        else: gate.unit_finish('gate')
    with pytest.raises((ValueError,FileNotFoundError)):
        gate.unit_finish('gate')


def test_new_unit_start_invalidates_previous_pass(unit_workspace):
    gate.unit_start('gate'); _unit_xml(); gate.unit_finish('gate')
    gate.unit_start('gate')
    with pytest.raises(ValueError): gate.verify_unit_binding('gate')


def test_unit_required_numeric_source_missing_is_rejected(unit_workspace):
    (unit_workspace/'numeric/fixedpoint.py').unlink()
    with pytest.raises((ValueError,FileNotFoundError)):
        gate.unit_start('numeric')
