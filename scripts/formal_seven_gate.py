"""Fail-closed formal-seven local-draft evidence gate. Never signs off PPA."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys
import time
import os
import subprocess
import tempfile
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT));sys.path.insert(0,str(ROOT/'dv/encoder'))

def sha(path):return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def load(path):return json.loads(Path(path).read_text(encoding='utf-8-sig'))
def write(path,obj):
 path.parent.mkdir(parents=True,exist_ok=True)
 path.write_text(json.dumps(obj,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
def validate_freshness(record,run_id,started):
 if record.get('run_id')!=run_id or record.get('started_unix',0)<started or record.get('completed_unix',0)<record.get('started_unix',0):raise ValueError('stale evidence does not belong to actual invocation')
def validate_cpu_identity(record,out,policy):
 command=record.get('command',[])
 if not isinstance(command,list) or len(command)!=3 or not all(isinstance(x,str) for x in command):raise ValueError('CPU command identity missing or not a simulation')
 if Path(command[0]).resolve()!=(out/'obj/Vtb_e203_encoder').resolve() or not re.fullmatch(r'\+BYTES=[1-9][0-9]*',command[1]) or command[2]!=f'+POLICY={policy}':raise ValueError('CPU command did not run the declared simulator/firmware/policy')
 if not isinstance(record.get('pid'),int) or record['pid']<=0:raise ValueError('CPU process identity missing')
 if not re.fullmatch('[0-9a-f]{32}',str(record.get('run_id',''))):raise ValueError('CPU invocation run_id missing')
 started=record.get('started_unix',0);completed=record.get('completed_unix',0)
 if not isinstance(started,(int,float)) or not isinstance(completed,(int,float)) or started<=0 or completed<started:raise ValueError('CPU invocation timestamps missing or invalid')
def check_hashes(root,mapping,required=True):
 if required and not mapping:raise ValueError('empty source/input hash manifest')
 for rel,digest in mapping.items():
  path=(root/rel).resolve()
  if root.resolve() not in path.parents:raise ValueError('hash path escapes workspace')
  if not path.is_file() or sha(path)!=digest:raise ValueError('stale or missing evidence: '+rel)

def validate_execution(record,root,out,layers,words):
 if record.get('status')!='PASS' or record.get('exit_code')!=0:raise ValueError('failed or missing child exit')
 if record.get('layers')!=layers or record.get('output_words')!=words or record.get('bit_mismatches')!=0:raise ValueError('partial or wrong output coverage')
 check_hashes(root,record.get('source_sha256',{}));check_hashes(root,record.get('input_sha256',{}))
 command=record.get('command',[])
 if not command or any(x in ('--help','-h','--compile-only') for x in command):raise ValueError('command did not execute simulation')
 binary=Path(command[1] if command[0]=='vvp' else command[0])
 if not binary.is_absolute():binary=out/binary
 if sha(binary)!=record.get('binary_sha256'):raise ValueError('executed binary changed')
 if not record.get('pid') or not record.get('completed_unix'):raise ValueError('execution identity absent')
 output=out/'output.hex';logpath=out/'simulation.log'
 if sha(output)!=record.get('output_sha256') or sha(logpath)!=record.get('log_sha256'):raise ValueError('output/log fingerprint mismatch')
 data=output.read_text(encoding='utf-8').splitlines()
 if len(data)!=words or any(not re.fullmatch('[0-9a-f]{8}',x) or (int(x,16)>>23)&255==255 for x in data):raise ValueError('partial or nonfinite words')
 log=logpath.read_text(encoding='utf-8')
 if f'ENCODER_PASS layers={layers} words={words}' not in log:raise ValueError('simulation completion absent')
 rows=re.findall(r'ENCODER_LAYER_PASS layer=(\d+) words=(\d+) cycles=(\d+) flags=([0-9a-f]+)',log)
 if len(rows)!=layers or [int(r[0]) for r in rows]!=list(range(layers)):raise ValueError('partial layer logs')
 if any(int(r[1])!=words//layers or int(r[2])<=0 or int(r[3],16)>31 for r in rows):raise ValueError('invalid cycles/flags/words')
 return rows

def record_kind(path):
 rel=path.resolve().relative_to(ROOT.resolve()).as_posix()
 fixed={'work/fp32_handoff.json':'fp32',
        'reports/encoder/verification/checks/status.json':'checks',
        'reports/encoder/verification/mutations/status.json':'mutations',
        'reports/encoder/synthesis/status.json':'synthesis',
        'reports/encoder/synthesis/soc/status.json':'synthesis',
        'reports/system/synthesis-icb/status.json':'legacy_synthesis'}
 if rel in fixed:return fixed[rel]
 if rel.startswith('reports/encoder/rtl/nonlinear-') and rel.endswith('/status.json'):return 'nonlinear'
 return None

def bound_record(path,expected_kind=None):
 r=load(path)
 if r.get('status')!='PASS':raise ValueError(str(path)+' not PASS')
 kind=expected_kind or record_kind(path)
 schemas={'checks':{'driver_checks','icb_checks','compiled_mutants_killed','fault_reset','icb_full_layers','icb_attention_layers','log_sha256'},
          'nonlinear':{'vectors','reset_interruptions','vectors_sha256','log_sha256'},
          'synthesis':{'top','design_sha256','log_sha256'},
          'legacy_synthesis':{'top','artifacts','memories','exit_code'},
          'mutations':{'compiled_numeric_mutants_killed','mutations'},
          'fp32':{'evidence_status_sha256','pytest_log_sha256','cold_start_warmup_operations','cold_start_full_execution_processes','behavioral_mutants_killed'}}
 if kind and (kind not in schemas or not schemas[kind]<=set(r)):raise ValueError('missing mandatory '+str(kind)+' evidence fields')
 if kind=='legacy_synthesis' and (r['exit_code']!=0 or not {'yosys.log','design.json','stats.json'}<=set(r['artifacts']) or not r['memories']):raise ValueError('legacy synthesis artifacts incomplete')
 mapping=r.get('source_sha256',r.get('source_fingerprints',r.get('input_sha256',r.get('sources',{}))))
 check_hashes(ROOT,mapping)
 for key in ('report_sha256','artifacts_sha256','artifacts','frozen_files_sha256'):
  values=r.get(key,{})
  if isinstance(values,dict) and values and all('/' in x for x in values):check_hashes(ROOT,values)
  elif key=='artifacts' and isinstance(values,dict):
   for name,digest in values.items():
    target=path.parent/name
    if not target.is_file() or sha(target)!=digest:raise ValueError('foreign artifact stale '+str(target))
 out=path.parent
 def artifact(name,digest,marker=None):
  p=out/name
  if not p.is_file() or not p.stat().st_size or sha(p)!=digest:raise ValueError('missing/stale artifact '+str(p))
  if marker and marker not in p.read_text(encoding='utf-8'):raise ValueError('incomplete artifact '+str(p))
 if 'driver_checks' in r:
  if r['driver_checks']<13 or r.get('icb_checks',0)<28 or r.get('compiled_mutants_killed',0)<1 or not r.get('fault_reset') or r.get('icb_full_layers')!=2 or r.get('icb_attention_layers')!=1:raise ValueError('directed coverage incomplete')
  required={'driver.log':'ENCODER_DRIVER_PASS checks=13','icb.log':'ENCODER_ICB_PASS checks=28',
            'mutant.log':'error=0 expected=1','faults.log':'ENCODER_FAULT_RESET_PASS',
            'icb-run.log':'full_layers=2 attention_layers=1 wait_done=3 outputs=36'}
  for name,marker in required.items():artifact(name,r.get('log_sha256',{}).get(name),marker)
 if 'vectors' in r:
  count=r['vectors']
  if count<2000 or r.get('reset_interruptions')!=2:raise ValueError('nonlinear coverage incomplete')
  artifact('vectors.txt',r.get('vectors_sha256'))
  if len((out/'vectors.txt').read_text(encoding='utf-8').splitlines())!=count:raise ValueError('nonlinear vectors truncated')
  artifact('simulation.log',r.get('log_sha256'),f'ENCODER_NONLINEAR_PASS vectors={count} reset_interruptions=2')
 if 'design_sha256' in r:
  artifact('design.json',r['design_sha256']);artifact('yosys.log',r.get('log_sha256'))
  design=load(out/'design.json')
  if r.get('top') not in design.get('modules',{}):raise ValueError('synthesis top missing')
 if 'compiled_numeric_mutants_killed' in r:
  if r['compiled_numeric_mutants_killed']!=3 or len(r.get('mutations',[]))!=3:raise ValueError('numeric mutation coverage incomplete')
  for mutation in r['mutations']:
   name=mutation['name'];folder=out/name
   if mutation.get('compile_exit')!=0 or not mutation.get('simulation_failed_on_word_mismatch'):raise ValueError('mutation was not a real compile-success/behavior-failure')
   if sha(folder/'encoder_core.sv')!=mutation['mutant_sha256'] or sha(folder/'simulation.log')!=mutation['log_sha256']:raise ValueError('mutation evidence changed')
   if 'word mismatch' not in (folder/'simulation.log').read_text(encoding='utf-8'):raise ValueError('wrong mutation failure reason')
 if 'evidence_status_sha256' in r:
  report=ROOT/'reports/encoder/fp32'
  required={'all','repeat','synthesis','mutations','red','cold-red','cold-green','cold-repeat','cold-unknown',
            'mutation-cold_zero_decode_bypassed','mutation-unknown_class_casex_masked'}
  if set(r['evidence_status_sha256'])!=required:raise ValueError('FP32 cold/full evidence incomplete')
  for name,digest in r['evidence_status_sha256'].items():
   status=report/name/'status.json'
   if sha(status)!=digest:raise ValueError('FP32 evidence status changed '+name)
   data=load(status);red=name in {'red','cold-red','mutation-cold_zero_decode_bypassed','mutation-unknown_class_casex_masked'}
   if data['status']!=('EXPECTED_BEHAVIORAL_RED' if red else 'PASS'):raise ValueError('FP32 child failed '+name)
   check_hashes(ROOT,data.get('artifacts',{}))
   if name!='red':check_hashes(ROOT,data['inputs']['sha256'])
  if r.get('cold_start_warmup_operations')!=0 or r.get('cold_start_full_execution_processes')!=136 or r.get('behavioral_mutants_killed')!=7:raise ValueError('FP32 cold-start acceptance incomplete')
  if sha(report/'pytest.log')!=r['pytest_log_sha256']:raise ValueError('FP32 oracle test log changed')
  vendor=load(ROOT/'config/hardfloat-source-manifest.json')
  for entry in vendor['files']:
   if sha(ROOT/vendor['root']/entry['path'])!=entry['sha256']:raise ValueError('immutable HardFloat vendor changed')
 return r

def validate_review_metadata(r):
 if r.get('rounds',0)<2 or r.get('open_p1',1) or r.get('open_p2',1) or r.get('independent') is not True or r.get('final_evidence_review_pending') is not False:raise ValueError('final independent review incomplete')
 reviews=r.get('review_sha256',{})
 if not isinstance(reviews,dict) or len(reviews)<2:raise ValueError('two reviewed documents required')
 check_hashes(ROOT,reviews)
 for rel in reviews:
  if not (ROOT/rel).read_text(encoding='utf-8').strip():raise ValueError('empty reviewed document')
 required={'work/encoder_source_freeze.json','scripts/formal_seven_gate.py'}
 if not required<=set(r.get('source_sha256',{})):raise ValueError('review does not bind frozen source and final gate')
 check_hashes(ROOT,r['source_sha256']);check_hashes(ROOT,r.get('input_sha256',{}))

def accepted_rtl(path,layers=12,attention=False):
 r=load(path);out=path.parent
 validate_execution(r,ROOT,out,layers,layers*99*64)
 check_hashes(ROOT,r.get('compiled_source_sha256',{}))
 if sha(out/'compile.log')!=r.get('compile_log_sha256') or sha(out/'build.json')!=r.get('build_key_sha256'):raise ValueError('RTL build evidence changed')
 if r.get('geometry')!=[99,64,256] or bool(r.get('attention'))!=attention:raise ValueError('incorrect geometry/mode')
 ref=ROOT/'reports/encoder'/r['reference'];case=ref/'cases'/r['case']
 if layers==12:
  expected=[]
  for l in range(12):expected+=(case/f'layer_{l:02d}/y.hex').read_text(encoding='utf-8').splitlines()
 else:
  case=(out/'case').resolve()
  if (ref/'cases').resolve() not in case.parents:raise ValueError('standalone case not in released reference')
  expected=(case/('attn.hex' if attention else 'y.hex')).read_text(encoding='utf-8').splitlines()
 if (out/'output.hex').read_text(encoding='utf-8').splitlines()!=expected:raise ValueError('output differs from released independent C')
 if 'trace_words' in r:
  trace=out/'trace.txt'
  if sha(trace)!=r.get('trace_sha256'):raise ValueError('trace changed')
  if sum(1 for line in trace.open(encoding='utf-8'))!=r['trace_words']:raise ValueError('trace incomplete')
 return r

def small_record(path,fixture,sim):
 r=load(path);out=path.parent;validate_execution(r,ROOT,out,1,12)
 check_hashes(ROOT,r.get('compiled_source_sha256',{}))
 if sha(out/'compile.log')!=r.get('compile_log_sha256') or sha(out/'build.json')!=r.get('build_key_sha256'):raise ValueError('small build evidence changed')
 if r.get('geometry')!=[3,4,8] or r.get('simulator')!=sim or r.get('case')!=fixture:raise ValueError('small fixture identity')
 expected=(ROOT/'reports/encoder/reference/fixtures'/fixture/'y.hex').read_text(encoding='utf-8')
 if (out/'output.hex').read_text(encoding='utf-8')!=expected or r.get('trace_words')!=186:raise ValueError('small output/trace incomplete')
 if sha(out/'trace.txt')!=r.get('trace_sha256') or len((out/'trace.txt').read_text(encoding='utf-8').splitlines())!=186:raise ValueError('small trace changed')
 return r

def validate_cpu_consumed_files(r,out):
 ref=ROOT/'reports/encoder/reference';case=(ref/'cases'/r['case']).resolve()
 if (ref/'cases').resolve() not in case.parents:raise ValueError('CPU case path is outside released reference')
 artifacts={}
 def equal_file(actual,expected):
  if actual.read_bytes()!=expected.read_bytes():raise ValueError('CPU staged file differs from released input '+actual.name)
  artifacts[str(actual.relative_to(ROOT))]=sha(actual)
 equal_file(out/'input.hex',case/'input.hex')
 expected=''.join((case/f'layer_{layer:02d}/y.hex').read_text(encoding='utf-8') for layer in range(12))
 if (out/'expected.hex').read_text(encoding='utf-8')!=expected:raise ValueError('CPU staged expected file differs from released twelve layers')
 artifacts[str((out/'expected.hex').relative_to(ROOT))]=sha(out/'expected.hex')
 if (out/'weights').resolve()!=(ref/'weights').resolve():raise ValueError('CPU staged weights link does not target released weights')
 for layer in range(12):equal_file(out/f'weights/layer_{layer:02d}.hex',ref/f'weights/layer_{layer:02d}.hex')
 with tempfile.TemporaryDirectory(prefix='encoder-fw-readback-') as directory:
  image=Path(directory)/'firmware.bin'
  result=subprocess.run(['riscv64-unknown-elf-objcopy','-O','binary',str(out/'firmware.elf'),str(image)],capture_output=True,timeout=30)
  if result.returncode:raise ValueError('cannot derive CPU image from bound ELF')
  payload=image.read_bytes()
 if not payload or (out/'firmware.bin').read_bytes()!=payload:raise ValueError('CPU staged bin differs from bound ELF image')
 if (out/'firmware.hex').read_text(encoding='utf-8')!=''.join(f'{b:02x}\n' for b in payload):raise ValueError('CPU staged hex differs from bound ELF image')
 if r['command'][1]!=f'+BYTES={len(payload)}':raise ValueError('CPU BYTES does not equal actual ELF image length')
 commands=[json.loads(line) for line in (out/'commands.jsonl').read_text(encoding='utf-8').splitlines() if line.strip()]
 matching=[item for item in commands if item.get('command')==r['command'] and Path(item.get('cwd','')).resolve()==out.resolve() and isinstance(item.get('time'),(int,float)) and r['started_unix']<=item['time']<=r['completed_unix']]
 if len(matching)!=1:raise ValueError('CPU actual command log does not match recorded simulation and interval')
 for name in ('firmware.elf','firmware.bin','firmware.hex','commands.jsonl'):artifacts[str((out/name).relative_to(ROOT))]=sha(out/name)
 return artifacts

def cpu_record(path,policy):
 r=bound_record(path);out=path.parent
 validate_cpu_identity(r,out,policy)
 r={**r,'verified_runtime_artifacts_sha256':validate_cpu_consumed_files(r,out)}
 if r.get('exit_code')!=0 or r.get('layers')!=12 or r.get('neural_words')!=76032 or r.get('policy')!=policy:raise ValueError('CPU incomplete neural coverage')
 check_hashes(ROOT,r.get('compiled_source_sha256',{}));check_hashes(ROOT,r.get('input_sha256',{}))
 if sha(out/'obj/Vtb_e203_encoder')!=r['binary_sha256'] or sha(out/'firmware.elf')!=r['firmware_sha256']:raise ValueError('CPU binary/firmware changed')
 if sha(out/'compile.log')!=r.get('compile_log_sha256') or sha(out/'build.json')!=r.get('build_key_sha256'):raise ValueError('CPU build evidence changed')
 if sha(out/'simulation.log')!=r['log_sha256'] or sha(out/'cpu-output.hex')!=r['output_sha256'] or sha(out/'neural-output.hex')!=r['neural_sha256']:raise ValueError('CPU artifacts changed')
 summary=r.get('summary','')
 if 'E203_ENCODER_PASS layers=12' not in summary:raise ValueError('CPU execution marker absent')
 stats={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',summary)}
 if stats.get('end_to_end_cycles',0)<=0 or stats.get('cpu_weight_words')!=597504 or stats.get('host_words')!=597504:raise ValueError('CPU measured counters incomplete')
 if stats.get('neural_words')!=76032 or stats.get('outputs')!=(6336 if policy==1 else 76032):raise ValueError('CPU output count')
 log=(out/'simulation.log').read_text(encoding='utf-8')
 if summary not in log or len(re.findall('HOST_LAYER_LOAD layer=',log))!=12:raise ValueError('CPU log not bound to real per-layer host loads')
 if len((out/'neural-output.hex').read_text(encoding='utf-8').splitlines())!=76032:raise ValueError('CPU passive output truncated')
 ref=ROOT/'reports/encoder/reference/cases'/r['case'];expected=''.join((ref/f'layer_{i:02d}/y.hex').read_text(encoding='utf-8') for i in range(12))
 if (out/'neural-output.hex').read_text(encoding='utf-8')!=expected:raise ValueError('CPU passive output differs from independent C')
 cpu_expected=''.join(expected.splitlines(keepends=True)[11*6336:]) if policy==1 else expected
 if (out/'cpu-output.hex').read_text(encoding='utf-8')!=cpu_expected:raise ValueError('CPU actual writeback differs from independent C')
 return r,stats

def evaluate():
 from run_encoder import reference_release,verify_source_freeze
 details={};tasks={f'task{i}':False for i in range(1,8)};errors={};full={}
 def attempt(label,fn):
  try:details[label]=fn();return True
  except (ValueError,OSError,KeyError,TypeError) as exc:errors[label]=str(exc);return False
 def integer():
  icb=bound_record(ROOT/'work/icb_handoff.json');cpu=bound_record(ROOT/'work/e203_ffn1_handoff.json')
  if icb['full_cases']!=36 or icb['full_mismatches'] or not icb['repeat_hash_equal']:raise ValueError('integer36/repeat incomplete')
  if sha(ROOT/cpu['report'])!=cpu['result_sha256'] or cpu['full_output_count']!=25344 or cpu['repeat_output_count']!=25344:raise ValueError('integer CPU/report binding')
  return {'full_cases':36,'words':icb['full_outputs'],'cpu_words':25344}
 tasks['task1']=attempt('fp32',lambda:bound_record(ROOT/'work/fp32_handoff.json'))
 tasks['task2']=attempt('integer',integer)
 tasks['task3']=tasks['task2'] and attempt('ffn1_synth',lambda:bound_record(ROOT/'reports/system/synthesis-icb/status.json'))
 reference_ok=attempt('reference',lambda:reference_release()[2]);test12_ok=attempt('reference_test12',lambda:reference_release('reference-test12')[2])
 freeze_ok=attempt('source_freeze',verify_source_freeze)
 checks=attempt('directed',lambda:bound_record(ROOT/'reports/encoder/verification/checks/status.json'))
 mutants=attempt('numeric_mutations',lambda:bound_record(ROOT/'reports/encoder/verification/mutations/status.json'))
 nonlinear=attempt('nonlinear',lambda:bound_record(ROOT/'reports/encoder/rtl/nonlinear-icarus/status.json'))
 nonlinear_cross=attempt('nonlinear_cross',lambda:bound_record(ROOT/'reports/encoder/rtl/nonlinear-verilator/status.json'))
 small_ok=True
 for sim in ['icarus','verilator']:
  for fixture in ['small_3_4_8','small_zero_3_4_8']:
   good=attempt(f'small_{sim}_{fixture}',lambda sim=sim,fixture=fixture:small_record(ROOT/f'reports/encoder/rtl/small-{sim}-{fixture}/status.json',fixture,sim))
   small_ok=small_ok and good
 attention=attempt('attention',lambda:accepted_rtl(ROOT/'reports/encoder/rtl/attention-full/status.json',1,True))
 tasks['task4']=bool(attention and checks and nonlinear and nonlinear_cross and small_ok and reference_ok)
 for path in sorted((ROOT/'reports/encoder/rtl/full').glob('*/status.json')):
  try:
   r=accepted_rtl(path);full[(r['reference'],r['case'])]={'record':str(path.relative_to(ROOT)),'output_sha256':r['output_sha256'],'pid':r['pid']}
  except (ValueError,OSError,KeyError,TypeError):pass
 traced=any(load(ROOT/v['record']).get('trace_words')==1603800 for v in full.values())
 tasks['task5']=bool(full and traced and checks and mutants and nonlinear and nonlinear_cross and small_ok and reference_ok)
 original=load(ROOT/'reports/encoder/reference/manifest.json') if (ROOT/'reports/encoder/reference/manifest.json').exists() else {'samples':[]}
 test12=load(ROOT/'reports/encoder/reference-test12/manifest.json') if (ROOT/'reports/encoder/reference-test12/manifest.json').exists() else {'samples':[]}
 expected={('reference',s['sample_id']) for s in original['samples']}|{('reference-test12',s['sample_id']) for s in test12['samples']}
 details['full_cases']=[{'reference':k[0],'case':k[1],**v} for k,v in full.items()]
 errors['missing_cases']=[list(k) for k in sorted(expected-set(full))]
 def repeat():
  r=accepted_rtl(ROOT/'reports/encoder/rtl/repeat/status.json');base=full.get((r['reference'],r['case']))
  if not base or base['pid']==r['pid'] or base['output_sha256']!=r['output_sha256']:raise ValueError('repeat not independent or differs')
  return {'record':'reports/encoder/rtl/repeat/status.json','pid':r['pid']}
 rep=attempt('repeat',repeat)
 ping=attempt('cpu_pingpong',lambda:cpu_record(ROOT/'reports/encoder/system/pingpong/status.json',1))
 reload=attempt('cpu_reload',lambda:cpu_record(ROOT/'reports/encoder/system/reload/status.json',2))
 if ping and reload:
  a,sa=details['cpu_pingpong'];b,sb=details['cpu_reload']
  if a['case']!=b['case'] or a['neural_sha256']!=b['neural_sha256']:errors['reuse']='different inputs/outputs';reload=False
  else:details['reuse_comparison']={'pingpong':sa,'reload':sb,'saved_shared_transactions':sb['shared_reads']+sb['shared_writes']-sa['shared_reads']-sa['shared_writes'],'saved_cycles':sb['end_to_end_cycles']-sa['end_to_end_cycles']}
 tasks['task6']=bool(len(expected)>=15 and expected<=set(full) and rep and ping and reload and checks and reference_ok and test12_ok)
 synth=attempt('encoder_synth',lambda:bound_record(ROOT/'reports/encoder/synthesis/status.json'))
 soc=attempt('soc_synth',lambda:bound_record(ROOT/'reports/encoder/synthesis/soc/status.json'))
 def reviews():
  r=bound_record(ROOT/'reports/encoder/verification/review.json')
  validate_review_metadata(r)
  required={'reports/encoder/rtl/repeat/status.json','reports/encoder/system/pingpong/status.json',
            'reports/encoder/system/reload/status.json','reports/encoder/synthesis/status.json',
            'reports/encoder/synthesis/soc/status.json','reports/encoder/verification/checks/status.json',
            'work/fp32_handoff.json','work/encoder_reference_handoff.json'}
  required.update(v['record'] for v in full.values())
  if len(full)<15 or not required<=set(r.get('input_sha256',{})):raise ValueError('final review does not cover completed long-run evidence')
  return {'rounds':r['rounds'],'independent':r['independent']}
 review=attempt('review',reviews)
 docs=all((ROOT/p).is_file() and (ROOT/p).stat().st_size>200 for p in ['docs/encoder/README.md','reports/encoder/verification/report.md'])
 tasks['task7']=bool(synth and soc and ping and reload and docs and review)
 ready=all(tasks.values()) and len(full)>=15 and reference_ok and test12_ok and freeze_ok
 state=load(ROOT/'work/encoder_status.json')
 state.update(tasks);state.update(status='READY_FOR_REVIEW' if ready else 'IMPLEMENTING_FORMAL_SEVEN',
  full_encoder_cases=len(full),formal_acceptance='EXTERNAL_PENDING_PLATFORM_LIBRARIES_AND_600_SAMPLES',
  reuse_comparison='PASS' if ping and reload else 'RELEASED_RUNNING',updated_unix=time.time(),
  evidence_gate='reports/encoder/verification/gate.json',blockers=errors)
 result={'status':'PASS' if ready else 'INCOMPLETE','tasks':tasks,'details':details,'errors':errors,
         'run_id':os.environ.get('ENCODER_RUN_ID','STANDALONE_GATE'),
         'gate_source_sha256':sha(Path(__file__)),'created_unix':time.time()}
 write(ROOT/'reports/encoder/verification/gate.json',result);write(ROOT/'work/encoder_status.json',state)
 write(ROOT/'work/encoder_engine_handoff.json',{'status':'READY_FOR_REVIEW' if ready else 'IN_PROGRESS',
  'gate':'reports/encoder/verification/gate.json','gate_sha256':sha(ROOT/'reports/encoder/verification/gate.json'),
  'full_encoder_cases':len(full),'remaining':errors,'git_operations':False,'formal_acceptance':state['formal_acceptance']})
 print(json.dumps({'status':result['status'],'tasks':tasks,'full_encoder_cases':len(full),'errors':errors},indent=2,ensure_ascii=False))
 return 0 if ready else 1

if __name__=='__main__':
 parser=argparse.ArgumentParser(description=__doc__);parser.parse_args()
 sys.exit(evaluate())
