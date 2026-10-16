"""Exercise the old schema bypass as an actual executable gate mutation."""
from pathlib import Path
import hashlib
import importlib.util
import json
import tempfile
import types

ROOT=Path(__file__).resolve().parents[2]

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
 source=ROOT/'scripts/formal_seven_gate.py';out=ROOT/'reports/encoder/verification/gate/schema-mutation';out.mkdir(parents=True,exist_ok=True)
 original=source.read_text(encoding='utf-8')
 needle='kind=expected_kind or record_kind(path)'
 if original.count(needle)!=1:raise ValueError('mutation point is not unique')
 mutant=original.replace(needle,'kind=None  # Deliberately reproduce deleted-discriminator bypass')
 path=out/'mutant_gate.py';path.write_text(mutant,encoding='utf-8')
 spec=importlib.util.spec_from_file_location('current_gate',source);current=importlib.util.module_from_spec(spec);spec.loader.exec_module(current)
 broken=types.ModuleType('mutant_gate');broken.__file__=str(source);exec(compile(mutant,str(path),'exec'),broken.__dict__)
 records=['reports/encoder/verification/checks/status.json','reports/encoder/rtl/nonlinear-icarus/status.json',
          'reports/encoder/synthesis/status.json','reports/encoder/verification/mutations/status.json','work/fp32_handoff.json'];results=[]
 with tempfile.TemporaryDirectory(prefix='encoder-gate-schema-') as directory:
  root=Path(directory);(root/'source.sv').write_text('module example; endmodule\n',encoding='utf-8')
  current.ROOT=broken.ROOT=root
  for rel in records:
   fixture=root/rel;fixture.parent.mkdir(parents=True,exist_ok=True)
   fixture.write_text(json.dumps({'status':'PASS','source_sha256':{'source.sv':digest(root/'source.sv')}}),encoding='utf-8')
   rejected=False
   try:current.bound_record(fixture)
   except ValueError:rejected=True
   broken.bound_record(fixture)  # Must actually accept the same corrupt record.
   if not rejected:raise ValueError('current gate accepted deleted schema '+rel)
   results.append({'record':rel,'current_rejected':True,'compiled_mutant_accepted_corrupt_record':True})
 record={'status':'PASS','source_sha256':{'scripts/formal_seven_gate.py':digest(source),'dv/encoder/run_gate_schema_mutation.py':digest(Path(__file__))},
         'mutant_compilation_succeeded':True,'behavioral_mutants_killed':1,'corrupt_records':results,'mutant_sha256':digest(path)}
 (out/'status.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
 print('ENCODER_GATE_SCHEMA_MUTANT_KILLED corrupt_records=5 compile_success=1')

if __name__=='__main__':main()
