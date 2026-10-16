"""Check the complete public E203/FFN1/encoder/shared-RAM generic hierarchy."""
from pathlib import Path
import json
import sys
import os,time,uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,RTL,archive

def main():
 started=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
 out=ROOT/'reports/encoder/synthesis/soc';out.mkdir(parents=True,exist_ok=True);archive(out)
 write(out/'status.json',{'status':'RUNNING','formal_ppa':'EXTERNAL_PENDING'})
 up=ROOT/'vendor/e203_hbirdv2-upstream/rtl/e203';upsrc=sorted(up.rglob('*.v'))
 own=[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',ROOT/'rtl/ffn1_icb.sv',ROOT/'rtl/ffn1_top.sv',ROOT/'rtl/dot64.sv',ROOT/'rtl/prototype_sync_ram.sv',ROOT/'soc/e203_common/e203_cpu_shell.sv',ROOT/'soc/e203_encoder/encoder_shared_ram.sv',ROOT/'soc/e203_encoder/e203_encoder_soc.sv',Path(__file__)]
 raw=[p for p in SOURCE.rglob('*') if p.is_file()]+[p for p in up.rglob('*') if p.is_file() and p.suffix in ('.vi','.vh')]
 bound=hashes(own+upsrc+raw)
 src=upsrc+prepare(out/'hardfloat')+own[:-1]
 inc=' '.join('-I'+str(p) for p in [up/'core',up/'perips',up/'perips/apb_i2c',SOURCE,SOURCE/'RISCV'])
 flow='read_verilog -sv -D DISABLE_SV_ASSERTION=1 '+inc+' '+' '.join(map(str,src))+'; hierarchy -check -top e203_encoder_soc; proc; opt; memory_dff; memory_collect; opt_clean; check -assert; stat; write_json design.json'
 run(['yosys','-p',flow],out,out/'yosys.log',1800)
 design=json.loads((out/'design.json').read_text(encoding='utf-8'))
 cells=design['modules']['e203_encoder_soc']['cells']
 for name in ['cpu','ram','encoder','ffn1']:
  if name not in cells or cells[name]['type'] not in design['modules']:raise ValueError('SoC hierarchy missing '+name)
 if hashes(own+upsrc+raw)!=bound:raise ValueError('SoC synthesis sources changed')
 write(out/'status.json',{'status':'PASS','top':'e203_encoder_soc','source_sha256':bound,
  'run_id':run_id,'started_unix':started,'completed_unix':time.time(),
  'connected_cells':{k:cells[k]['type'] for k in ['cpu','ram','encoder','ffn1']},
  'module_count':len(design['modules']),'log_sha256':sha(out/'yosys.log'),
  'design_sha256':sha(out/'design.json'),'formal_ppa':'EXTERNAL_PENDING',
  'scope':'Full generic public E203 and both accelerator windows; unmapped memories, no physical/timing/power acceptance'})
 print('ENCODER_SOC_GENERIC_SYNTH_PASS',flush=True)

if __name__=='__main__':
 try:main()
 except Exception as exc:
  write(ROOT/'reports/encoder/synthesis/soc/status.json',{'status':'FAIL','error':str(exc),'formal_ppa':'EXTERNAL_PENDING'})
  print(str(exc),file=sys.stderr);sys.exit(1)
