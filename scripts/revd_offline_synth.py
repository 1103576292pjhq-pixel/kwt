"""Memory-preserving generic structure check, explicitly not technology PPA."""
import sys
from pathlib import Path
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import command,put,sha,run_id,utc

def main():
    out=ROOT/'reports/revd_offline/generic_synthesis'/run_id();out.mkdir(parents=True,exist_ok=False)
    hdl=[ROOT/'rtl/revd/banked_sp16.sv',ROOT/'rtl/revd/quant_epilogue.sv',ROOT/'rtl/revd_opt/core_stream_frontend_opt.sv']
    initial={str(p.relative_to(ROOT)):sha(p) for p in [*hdl,Path(__file__)]};tests=[]
    for pm in (4,2):
        dest=out/f'pm{pm}';dest.mkdir()
        script=dest/'structure.ys'
        # No memory_map, abc or fabricated target cells: keep synchronous SRAMs
        # as $mem_v2 and multipliers as generic arithmetic cells.
        script.write_text('read_verilog -sv -DSYNTHESIS '+ ' '.join(str(p) for p in hdl)+'\n'+
          f'chparam -set PM {pm} core_stream_frontend_opt\n'+
          'hierarchy -check -top core_stream_frontend_opt\nproc\nopt\nmemory_collect\nopt_clean\ncheck\n'+
          f'tee -o {dest/"stat.json"} stat -json\nwrite_json {dest/"generic.json"}\n',encoding='utf-8')
        c=command(['yosys','-Q','-T','-s',script],dest/'yosys.log',timeout=180)
        ok=c['exit_code']==0 and (dest/'generic.json').is_file() and (dest/'stat.json').is_file()
        tests.append({'pm':pm,'status':'PASS_GENERIC_ONLY' if ok else 'FAIL','command':c,
          'artifacts':{p.name:sha(p) for p in dest.iterdir() if p.is_file()},
          'not_sta':True,'not_mapped_area':True,'not_power':True})
    unchanged=all(sha(ROOT/p)==d for p,d in initial.items())
    result={'status':'PASS_GENERIC_ONLY' if unchanged and all(t['status']=='PASS_GENERIC_ONLY' for t in tests) else 'PARTIAL',
            'scope':'Generic coarse RTL structure with inferred memories; no technology mapping, STA, area mm2, energy or contest eligibility claim.',
            'source_sha256':initial,'source_unchanged':unchanged,'profiles':tests,'finished_utc':utc()}
    put(out/'summary.json',result);print(out,result['status'],flush=True)
    return 0 if result['status']=='PASS_GENERIC_ONLY' else 1
if __name__=='__main__':raise SystemExit(main())
