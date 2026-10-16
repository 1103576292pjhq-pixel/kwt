"""Compiled arithmetic/control mutations must fail real independent RTL DV."""
from pathlib import Path
import os,sys,time,uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,RTL,reference_release,fp32_release,archive

def main():
 started=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex);fp=fp32_release()
 out=ROOT/'reports/encoder/verification/mutations';out.mkdir(parents=True,exist_ok=True);archive(out)
 ref,manifest,verified=reference_release();case=ref/'fixtures/small_3_4_8'
 original=(ROOT/'rtl/encoder_core.sv').read_text(encoding='utf-8')
 definitions=[('score_scale',"a=acc;b=32'h3e000000;","a=acc;b=32'h3e800000;"),
              ('normalization_bias','op=3;a=scaled;b=wd;c=center;','op=3;a=scaled;b=wd;c=0;'),
              ('omit_last_token','else if(row+1<M)begin row<=row+1;phase<=PQ;end\n        else begin busy<=0;done<=1;job_done<=layer_index==11;end',
               'else if(row+2<M)begin row<=row+1;phase<=PQ;end\n        else begin busy<=0;done<=1;job_done<=layer_index==11;end')]
 sources=[ROOT/x for x in RTL]+[ROOT/'dv/encoder/tb_encoder.sv',Path(__file__)]
 dependencies=sources+[ROOT/'dv/encoder/run_encoder.py',ROOT/'dv/fp32/hardfloat_sources.py']
 bound=hashes(dependencies);results=[]
 for name,needle,replacement in definitions:
  if original.count(needle)!=1:raise ValueError('mutation anchor changed '+name)
  folder=out/name;folder.mkdir(parents=True,exist_ok=True)
  core=folder/'encoder_core.sv';core.write_text(original.replace(needle,replacement),encoding='utf-8')
  link=folder/'case'
  if not link.exists():link.symlink_to(case,target_is_directory=True)
  src=prepare(folder/'hardfloat')+[core if p==ROOT/'rtl/encoder_core.sv' else p for p in sources[:-1]]
  binary=folder/'test.vvp'
  run(['iverilog','-g2012','-s','tb_encoder','-I'+str(SOURCE),'-I'+str(SOURCE/'RISCV'),'-o',binary,*src],folder,folder/'compile.log')
  try:run(['vvp',binary,'+CASE=case','+WEIGHTS=case','+LAYERS=1','+OUTPUT=wrong.hex'],folder,folder/'simulation.log')
  except RuntimeError:
   log=(folder/'simulation.log').read_text(encoding='utf-8')
   if 'word mismatch' not in log:raise ValueError('mutation failed for wrong reason '+name+' '+log[-500:])
  else:raise ValueError('arithmetic/control mutation survived '+name)
  results.append({'name':name,'compile_exit':0,'simulation_failed_on_word_mismatch':True,
                  'mutant_sha256':sha(core),'log_sha256':sha(folder/'simulation.log')})
 if hashes(dependencies)!=bound or fp32_release()!=fp:raise ValueError('mutation sources/dependency changed')
 write(out/'status.json',{'status':'PASS','run_id':run_id,'started_unix':started,'completed_unix':time.time(),
                        'source_sha256':bound,'compiled_numeric_mutants_killed':3,'mutations':results,
                        'reference_manifest_sha256':sha(ref/'manifest.json')})
 print('ENCODER_NUMERIC_MUTANTS_KILLED count=3',flush=True)

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
