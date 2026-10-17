#!/usr/bin/env python3
"""Compile real RTL lifecycle mutations without editing candidate sources."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
from revd_offline_common import ROOT,command,put,run_id,sha,utc

def main():
    out=ROOT/'reports/revd_offline/soc'/('adapter-mutations-'+run_id())
    out.mkdir(parents=True,exist_ok=False)
    source=ROOT/'soc/revd_opt/revd_opt_icb.sv';text=source.read_text()
    common=[ROOT/'rtl/revd_opt/core_stream_frontend_opt.sv',ROOT/'rtl/revd/banked_sp16.sv',ROOT/'rtl/revd/quant_epilogue.sv']
    tests=[('green_bus',None,None,'soc_bus_contract_tb','REVD_SOC_BUS_PASS',True),
           ('green_lifecycle',None,None,'soc_adapter_tb','REVD_SOC_ADAPTER_PASS',True),
           ('green_completion',None,None,'soc_completion_tb','REVD_SOC_COMPLETION_PASS',True),
           ('mut_early_output_release','.out_ready(pop)','.out_ready(out_valid)','soc_adapter_tb','index ',False),
           ('mut_full_capacity','out_valid,!event_valid','out_valid,1\'b1','soc_adapter_tb','event queue full capacity not reported',False),
           ('mut_response_reuse','assign icb_cmd_ready=!icb_rsp_valid;','assign icb_cmd_ready=1\'b1;','soc_bus_contract_tb','response changed or command accepted',False)]
    results=[]
    for name,needle,replacement,top,token,green in tests:
        candidate=source
        if needle:
            if text.count(needle)!=1:raise RuntimeError('mutation anchor mismatch '+name)
            candidate=out/(name+'.sv');candidate.write_text(text.replace(needle,replacement,1))
        binary=out/(name+'.vvp');tb=ROOT/f'dv/revd_opt/{top}.sv'
        compile_record=command(['iverilog','-g2012','-s',top,'-o',binary,*common,candidate,tb],out/(name+'-compile.log'),timeout=60)
        if compile_record['exit_code']!=0:raise RuntimeError('mutation did not compile '+name)
        sim_record=command(['vvp',binary],out/(name+'-simulate.log'),timeout=60)
        log=(out/(name+'-simulate.log')).read_text()
        if green:
            accepted=sim_record['exit_code']==0 and token in log
        else:
            accepted=sim_record['exit_code']!=0 and token in log and 'PASS checks=' not in log
        result={'name':name,'status':'PASS' if accepted else 'FAIL','expected_success':green,
                'source_sha256':sha(candidate),'testbench_sha256':sha(tb),'compile':compile_record,'simulate':sim_record,'required_message':token}
        results.append(result);put(out/'result.json',{'status':'RUNNING','results':results})
        if not accepted:raise RuntimeError('wrong lifecycle mutation outcome '+name)
    put(out/'result.json',{'status':'PASS','finished_utc':utc(),'rtl_mutation_count':3,'green_tests':3,
                           'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in common+[source]},'results':results})
    print('SOC_MUTATIONS_REPORT',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
