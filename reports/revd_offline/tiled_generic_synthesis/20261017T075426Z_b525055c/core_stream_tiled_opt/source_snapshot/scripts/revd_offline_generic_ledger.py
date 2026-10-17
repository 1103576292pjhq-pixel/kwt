"""Read actual Yosys inferred-memory cells without treating them as physical SRAM."""
from pathlib import Path
import argparse
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import read_json,put,sha,run_id,utc

def number(value):return value if isinstance(value,int) else int(value,2)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--synthesis',required=True);a=ap.parse_args()
    source=ROOT/a.synthesis;report=read_json(source/'summary.json')
    if report['status']!='PASS_GENERIC_ONLY':raise ValueError('not a complete coarse synthesis')
    result=[]
    for pm in (2,4):
        p=source/f'pm{pm}/generic.json';net=read_json(p);rows=[]
        def walk(module,path):
            for name,c in net['modules'][module].get('cells',{}).items():
                if c['type'] in net['modules']:walk(c['type'],path+'/'+name)
                elif c['type']=='$mem_v2':
                    pars=c['parameters'];size=number(pars['SIZE']);width=number(pars['WIDTH'])
                    rows.append({'hierarchy':path+'/'+name,'module':module,'words':size,'width_bits':width,
                                 'data_bits':size*width,'read_ports':number(pars['RD_PORTS']),'write_ports':number(pars['WR_PORTS']),
                                 'storage_class':'banked_sp16_behavioral' if 'banked_sp16' in module else 'unmapped_internal_array'})
        tops=[k for k,v in net['modules'].items() if number(v.get('attributes',{}).get('top',0))==1]
        if len(tops)!=1:raise ValueError('missing/ambiguous actual synthesis top')
        walk(tops[0],'core_stream_frontend_opt')
        result.append({'pm':pm,'inferred_memory_cells':rows,'total_inferred_data_bits':sum(v['data_bits'] for v in rows),
                       'banked_sp16_data_bits':sum(v['data_bits'] for v in rows if v['storage_class']=='banked_sp16_behavioral'),
                       'netlist_sha256':sha(p),'physical_area_mm2':None,'power_W':None,'STA_MHz':None})
    out=ROOT/'reports/revd_offline/generic_synthesis_ledger'/run_id();out.mkdir(parents=True,exist_ok=False)
    put(out/'summary.json',{'status':'PASS_GENERIC_LEDGER_ONLY','profiles':result,'source_report':str(source.relative_to(ROOT)),
        'note':'Yosys stat num_memories=0 after memory_collect does not mean zero storage: capacity is in the listed $mem_v2 cells. Small inferred arrays are not claimed to map to designated SRAM macros.',
        'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in [Path(__file__),source/'summary.json']},'finished_utc':utc()})
    print(out,flush=True)
if __name__=='__main__':main()
