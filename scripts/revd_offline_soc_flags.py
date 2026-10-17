#!/usr/bin/env python3
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,command,put,run_id,sha,utc
out=ROOT/'reports/revd_offline/soc'/('positive-flags-'+run_id());out.mkdir(parents=True,exist_ok=False)
sources=[ROOT/p for p in ['rtl/revd_opt/core_stream_frontend_opt.sv','rtl/revd/banked_sp16.sv',
          'rtl/revd/quant_epilogue.sv','soc/revd_opt/revd_opt_icb.sv','dv/revd_opt/soc_flags_tb.sv']]
binary=out/'flags.vvp'
compile_record=command(['iverilog','-g2012','-s','soc_flags_tb','-o',binary,*sources],out/'compile.log',timeout=60)
if compile_record['exit_code']!=0:raise RuntimeError('flags compile failed')
sim_record=command(['vvp',binary],out/'simulate.log',timeout=60)
text=(out/'simulate.log').read_text()
passed=sim_record['exit_code']==0 and 'REVD_SOC_FLAGS_PASS outputs=16 overflow=16 saturated=16 last=1' in text
put(out/'result.json',{'status':'PASS' if passed else 'FAIL','checked_utc':utc(),
    'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in sources},'script_sha256':sha(Path(__file__)),
    'compile':compile_record,'simulate':sim_record,'simulator_binary_sha256':sha(binary)})
if not passed:raise RuntimeError('positive flags not preserved through public MMIO')
print('SOC_FLAGS_REPORT',out.relative_to(ROOT),flush=True)
