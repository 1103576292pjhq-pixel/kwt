"""Generic encoder structure and clocked bulk-memory inference, no PDK claims."""
import json
from pathlib import Path
import sys
import os,time,uuid
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import run,write,sha,hashes,prepare,SOURCE,RTL

def main():
 started=time.time();run_id=os.environ.get('ENCODER_RUN_ID',uuid.uuid4().hex)
 out=ROOT/'reports/encoder/synthesis';out.mkdir(parents=True,exist_ok=True)
 write(out/'status.json',{'status':'RUNNING','formal_ppa':'EXTERNAL_PENDING'})
 own=[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv',Path(__file__)]
 own += [ROOT/'dv/encoder/run_encoder.py',ROOT/'dv/fp32/hardfloat_sources.py']
 bound=hashes(own);src=prepare(out/'hardfloat')+[ROOT/x for x in RTL]+[ROOT/'rtl/encoder_icb.sv']
 flow='read_verilog -sv '+f'-I{SOURCE} -I{SOURCE/"RISCV"} '+' '.join(map(str,src))+'; hierarchy -check -top encoder_icb; proc; opt; memory_dff; memory_collect; opt_clean; check -assert; stat; write_json design.json'
 run(['yosys','-p',flow],out,out/'yosys.log',1200)
 design=json.loads((out/'design.json').read_text(encoding='utf-8'));memories=[]
 for module,body in design['modules'].items():
  for name,cell in body.get('cells',{}).items():
   if cell['type']=='$mem_v2':
    p=cell['parameters'];words=int(p['SIZE'],2);clock=int(p['RD_CLK_ENABLE'],2)
    if words>=6336 and not clock:raise ValueError('unclocked bulk RAM '+module+'.'+name)
    memories.append({'module':module,'name':name,'words':words,'width':int(p['WIDTH'],2),'read_clock_enable':clock})
 bulk=sorted({(x['words'],x['width']) for x in memories if x['words']>=6336})
 if bulk!=[(6336,32),(49792,32)]:raise ValueError('bulk geometry missing '+str(bulk))
 instances=[]
 for module,body in design['modules'].items():
  if 'encoder_core' in module:
   instances=[name for name,c in body.get('cells',{}).items() if 'encoder_sync_ram' in c['type']]
 if sorted(instances)!=['keys','values_ram','weights_ram','x0','x1']:raise ValueError('bulk instances differ '+str(instances))
 if hashes(own)!=bound:raise ValueError('synthesis source changed')
 tool=run(['yosys','-V'],out,out/'tool.log')
 result={'status':'PASS','top':'encoder_icb','source_sha256':bound,'memories':memories,
         'run_id':run_id,'started_unix':started,'completed_unix':time.time(),
         'bulk_instances':instances,'bulk_words':49792+4*6336,'bulk_bytes':4*(49792+4*6336),
         'design_sha256':sha(out/'design.json'),'log_sha256':sha(out/'yosys.log'),
         'tool':tool.strip(),'formal_ppa':'EXTERNAL_PENDING',
         'scope':'Generic complete encoder hierarchy; SoC validation is separately linked to real CPU execution.',
         'no_claims':['technology mapping','SRAM macro mapping','150MHz timing','physical area','power','gate-level simulation']}
 write(out/'status.json',result);print('ENCODER_GENERIC_SYNTH_PASS',flush=True)

if __name__=='__main__':
 try:main()
 except Exception as exc:
  write(ROOT/'reports/encoder/synthesis/status.json',{'status':'FAIL','error':str(exc),'formal_ppa':'EXTERNAL_PENDING'})
  print(str(exc),file=sys.stderr);sys.exit(1)
