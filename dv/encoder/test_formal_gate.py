"""Meaningful rejection cases for the completion gate, using isolated files."""
import importlib.util
from pathlib import Path
import json
import subprocess
import pytest
ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('formal_gate',ROOT/'scripts/formal_seven_gate.py')
gate=importlib.util.module_from_spec(spec);spec.loader.exec_module(gate)

def record(tmp_path):
 (tmp_path/'source.sv').write_text('module example; endmodule\n',encoding='utf-8')
 (tmp_path/'input.hex').write_text('00000000\n',encoding='utf-8')
 (tmp_path/'output.hex').write_text('00000000\n',encoding='utf-8')
 (tmp_path/'simulation.log').write_text('ENCODER_LAYER_PASS layer=0 words=1 cycles=10 flags=00\nENCODER_PASS layers=1 words=1\n',encoding='utf-8')
 (tmp_path/'binary').write_bytes(b'actual-test-fixture')
 return {'status':'PASS','exit_code':0,'layers':1,'output_words':1,'bit_mismatches':0,
         'source_sha256':{'source.sv':gate.sha(tmp_path/'source.sv')},
         'input_sha256':{'input.hex':gate.sha(tmp_path/'input.hex')},
         'output_sha256':gate.sha(tmp_path/'output.hex'),'log_sha256':gate.sha(tmp_path/'simulation.log'),
         'command':[str(tmp_path/'binary')],'binary_sha256':gate.sha(tmp_path/'binary'),
         'completed_unix':123,'pid':100}

def test_valid_complete_evidence(tmp_path):
 gate.validate_execution(record(tmp_path),tmp_path,tmp_path,1,1)

@pytest.mark.parametrize('kind',['stale_source','wrong_output','partial_output','failed_child','help_only','empty_log','partial_layers','missing_input','zero_cycles','binary_changed'])
def test_rejects_false_success(tmp_path,kind):
 r=record(tmp_path)
 if kind=='stale_source':(tmp_path/'source.sv').write_text('changed',encoding='utf-8')
 if kind=='wrong_output':(tmp_path/'output.hex').write_text('3f800000\n',encoding='utf-8')
 if kind=='partial_output':(tmp_path/'output.hex').write_text('',encoding='utf-8')
 if kind=='failed_child':r['exit_code']=1
 if kind=='help_only':r['command']+=['--help']
 if kind=='empty_log':(tmp_path/'simulation.log').write_text('',encoding='utf-8')
 if kind=='partial_layers':r['layers']=0
 if kind=='missing_input':(tmp_path/'input.hex').unlink()
 if kind=='zero_cycles':
  (tmp_path/'simulation.log').write_text('ENCODER_LAYER_PASS layer=0 words=1 cycles=0 flags=00\nENCODER_PASS layers=1 words=1\n',encoding='utf-8');r['log_sha256']=gate.sha(tmp_path/'simulation.log')
 if kind=='binary_changed':(tmp_path/'binary').write_bytes(b'wrong-build')
 with pytest.raises((ValueError,OSError)):gate.validate_execution(r,tmp_path,tmp_path,1,1)

@pytest.mark.parametrize('artifact',['driver.log','icb.log','mutant.log','faults.log','icb-run.log','vectors.txt','design.json'])
def test_bound_record_rejects_missing_artifacts(tmp_path,monkeypatch,artifact):
 monkeypatch.setattr(gate,'ROOT',tmp_path)
 (tmp_path/'source.sv').write_text('module test; endmodule',encoding='utf-8')
 logs={'driver.log':'ENCODER_DRIVER_PASS checks=13','icb.log':'ENCODER_ICB_PASS checks=28',
       'mutant.log':'error=0 expected=1','faults.log':'ENCODER_FAULT_RESET_PASS checks=717',
       'simulation.log':'ENCODER_NONLINEAR_PASS vectors=2030 reset_interruptions=2',
       'yosys.log':'Executing CHECK pass (checking for obvious problems).',
       'icb-run.log':'ENCODER_ICB_RUN_PASS checks=579 full_layers=2 attention_layers=1 wait_done=3 outputs=36'}
 for name,text in logs.items():(tmp_path/name).write_text(text+'\n',encoding='utf-8')
 (tmp_path/'vectors.txt').write_text('00000000 00000000 3f800000 00000000\n'*2030,encoding='utf-8')
 (tmp_path/'design.json').write_text('{"modules":{"encoder_icb":{}}}',encoding='utf-8')
 r={'status':'PASS','source_sha256':{'source.sv':gate.sha(tmp_path/'source.sv')}}
 if artifact in ('driver.log','icb.log','mutant.log','faults.log','icb-run.log'):
  r.update(driver_checks=13,icb_checks=28,compiled_mutants_killed=1,fault_reset=True,
           icb_full_layers=2,icb_attention_layers=1,
           log_sha256={name:gate.sha(tmp_path/name) for name in logs if name not in ('simulation.log','yosys.log')})
 elif artifact=='vectors.txt':r.update(vectors=2030,reset_interruptions=2,vectors_sha256=gate.sha(tmp_path/'vectors.txt'),log_sha256=gate.sha(tmp_path/'simulation.log'))
 else:r.update(top='encoder_icb',design_sha256=gate.sha(tmp_path/'design.json'),log_sha256=gate.sha(tmp_path/'yosys.log'))
 path=tmp_path/'status.json';path.write_text(json.dumps(r),encoding='utf-8')
 gate.bound_record(path)
 (tmp_path/artifact).unlink()
 with pytest.raises((ValueError,OSError)):gate.bound_record(path)

@pytest.mark.parametrize('data',[{}, {'run_id':'previous','started_unix':11,'completed_unix':12},
                                {'run_id':'current','started_unix':9,'completed_unix':12},
                                {'run_id':'current','started_unix':11,'completed_unix':10}])
def test_rejects_stale_invocation(data):
 with pytest.raises(ValueError):gate.validate_freshness(data,'current',10)

def test_accepts_real_invocation():
 gate.validate_freshness({'run_id':'current','started_unix':11,'completed_unix':12},'current',10)

@pytest.mark.parametrize('bad',['help','missing_command','missing_pid','missing_run_id','missing_start','reversed_time'])
def test_cpu_history_rejects_missing_execution_identity(tmp_path,bad):
 r={'command':[str(tmp_path/'obj/Vtb_e203_encoder'),'+BYTES=100','+POLICY=1'],
    'pid':123,'run_id':'a'*32,'started_unix':10.,'completed_unix':11.}
 if bad=='help':r['command']+=['--help']
 if bad=='missing_command':r.pop('command')
 if bad=='missing_pid':r.pop('pid')
 if bad=='missing_run_id':r.pop('run_id')
 if bad=='missing_start':r.pop('started_unix')
 if bad=='reversed_time':r['completed_unix']=9.
 with pytest.raises(ValueError):gate.validate_cpu_identity(r,tmp_path,1)

@pytest.mark.parametrize('kind',['checks','nonlinear','synthesis','mutations','fp32'])
def test_rejects_deleted_record_type_fields(tmp_path,monkeypatch,kind):
 monkeypatch.setattr(gate,'ROOT',tmp_path)
 (tmp_path/'source.sv').write_text('module test; endmodule',encoding='utf-8')
 paths={'checks':'reports/encoder/verification/checks/status.json',
        'nonlinear':'reports/encoder/rtl/nonlinear-icarus/status.json',
        'synthesis':'reports/encoder/synthesis/status.json',
        'mutations':'reports/encoder/verification/mutations/status.json','fp32':'work/fp32_handoff.json'}
 path=tmp_path/paths[kind];path.parent.mkdir(parents=True,exist_ok=True)
 path.write_text(json.dumps({'status':'PASS','source_sha256':{'source.sv':gate.sha(tmp_path/'source.sv')}}),encoding='utf-8')
 with pytest.raises(ValueError):gate.bound_record(path)

@pytest.mark.parametrize('bad',['pending','empty_reviews','single_review','missing_freeze','missing_evidence'])
def test_rejects_incomplete_final_review(tmp_path,monkeypatch,bad):
 monkeypatch.setattr(gate,'ROOT',tmp_path)
 r={'rounds':2,'independent':True,'open_p1':0,'open_p2':0,'final_evidence_review_pending':False,
    'review_sha256':{},'source_sha256':{},'input_sha256':{}}
 for name in ['first.md','final.md','work/encoder_source_freeze.json','scripts/formal_seven_gate.py','result.json']:
  path=tmp_path/name;path.parent.mkdir(parents=True,exist_ok=True);path.write_text('reviewed current evidence',encoding='utf-8')
 for name in ['first.md','final.md']:r['review_sha256'][name]=gate.sha(tmp_path/name)
 for name in ['work/encoder_source_freeze.json','scripts/formal_seven_gate.py']:r['source_sha256'][name]=gate.sha(tmp_path/name)
 r['input_sha256']={'result.json':gate.sha(tmp_path/'result.json')}
 if bad=='pending':r['final_evidence_review_pending']=True
 if bad=='empty_reviews':r['review_sha256']={}
 if bad=='single_review':r['review_sha256'].pop('final.md')
 if bad=='missing_freeze':r['source_sha256'].pop('work/encoder_source_freeze.json')
 if bad=='missing_evidence':r['input_sha256']={}
 with pytest.raises(ValueError):gate.validate_review_metadata(r)

def test_accepts_bound_final_review_metadata(tmp_path,monkeypatch):
 monkeypatch.setattr(gate,'ROOT',tmp_path)
 r={'rounds':2,'independent':True,'open_p1':0,'open_p2':0,'final_evidence_review_pending':False,
    'review_sha256':{},'source_sha256':{},'input_sha256':{}}
 for group,names in [('review_sha256',['first.md','final.md']),('source_sha256',['work/encoder_source_freeze.json','scripts/formal_seven_gate.py']),('input_sha256',['result.json'])]:
  for name in names:
   path=tmp_path/name;path.parent.mkdir(parents=True,exist_ok=True);path.write_text('independently reviewed',encoding='utf-8');r[group][name]=gate.sha(path)
 gate.validate_review_metadata(r)

@pytest.fixture
def staged_cpu(tmp_path,monkeypatch):
 monkeypatch.setattr(gate,'ROOT',tmp_path)
 out=tmp_path/'reports/encoder/system/pingpong';out.mkdir(parents=True)
 reference=tmp_path/'reports/encoder/reference';case=reference/'cases/fixture';case.mkdir(parents=True)
 (reference/'weights').mkdir()
 (case/'input.hex').write_text('3f800000\n',encoding='utf-8')
 expected=''
 for layer in range(12):
  directory=case/f'layer_{layer:02d}';directory.mkdir()
  word=f'{0x3f800000+layer:08x}\n';(directory/'y.hex').write_text(word,encoding='utf-8');expected+=word
  (reference/f'weights/layer_{layer:02d}.hex').write_text('3f800000\n',encoding='utf-8')
 (out/'input.hex').write_bytes((case/'input.hex').read_bytes())
 (out/'expected.hex').write_text(expected,encoding='utf-8')
 (out/'weights').symlink_to(reference/'weights',target_is_directory=True)
 assembly=tmp_path/'tiny.S';assembly.write_text('.section .text\n.globl _start\n_start:\n nop\n j _start\n',encoding='utf-8')
 subprocess.run(['riscv64-unknown-elf-gcc','-march=rv32imac','-mabi=ilp32','-nostdlib','-nostartfiles','-Wl,--entry=_start,-Ttext=0x80000000',str(assembly),'-o',str(out/'firmware.elf')],check=True,capture_output=True)
 subprocess.run(['riscv64-unknown-elf-objcopy','-O','binary',str(out/'firmware.elf'),str(out/'firmware.bin')],check=True,capture_output=True)
 payload=(out/'firmware.bin').read_bytes();(out/'firmware.hex').write_text(''.join(f'{b:02x}\n' for b in payload),encoding='utf-8')
 r={'case':'fixture','command':[str(out/'obj/Vtb_e203_encoder'),f'+BYTES={len(payload)}','+POLICY=1'],
    'pid':123,'run_id':'a'*32,'started_unix':10.,'completed_unix':20.}
 (out/'commands.jsonl').write_text(json.dumps({'command':r['command'],'cwd':str(out),'time':15.})+'\n',encoding='utf-8')
 return r,out

def test_accepts_cpu_consumed_files(staged_cpu):
 r,out=staged_cpu
 evidence=gate.validate_cpu_consumed_files(r,out)
 assert len(evidence)>=17

@pytest.mark.parametrize('bad',['input','expected','bin','hex','weights','bytes','command_record','command_time','elf_image'])
def test_rejects_cpu_consumed_file_drift(staged_cpu,bad):
 r,out=staged_cpu
 if bad in ('input','expected','bin','hex'):
  name={'input':'input.hex','expected':'expected.hex','bin':'firmware.bin','hex':'firmware.hex'}[bad]
  path=out/name;payload=path.read_bytes();path.write_bytes(bytes([payload[0]^1])+payload[1:])
 if bad=='weights':
  wrong=out/'wrong-weights';wrong.mkdir();(out/'weights').unlink();(out/'weights').symlink_to(wrong,target_is_directory=True)
 if bad=='bytes':r['command'][1]='+BYTES=999'
 if bad in ('command_record','command_time'):
  row=json.loads((out/'commands.jsonl').read_text(encoding='utf-8'))
  if bad=='command_record':row['command']=[r['command'][0],'--help']
  else:row['time']=9.
  (out/'commands.jsonl').write_text(json.dumps(row)+'\n',encoding='utf-8')
 if bad=='elf_image':
  payload=(out/'firmware.bin').read_bytes();payload=bytes([payload[0]^1])+payload[1:]
  (out/'firmware.bin').write_bytes(payload);(out/'firmware.hex').write_text(''.join(f'{b:02x}\n' for b in payload),encoding='utf-8')
 with pytest.raises((ValueError,OSError)):gate.validate_cpu_consumed_files(r,out)

def test_cpu_record_wires_consumed_file_validator(staged_cpu,monkeypatch):
 r,out=staged_cpu
 monkeypatch.setattr(gate,'bound_record',lambda path:r)
 def reject(record,directory):raise ValueError('consumed-files-validator-called')
 monkeypatch.setattr(gate,'validate_cpu_consumed_files',reject,raising=False)
 with pytest.raises(ValueError,match='consumed-files-validator-called'):gate.cpu_record(out/'status.json',1)
