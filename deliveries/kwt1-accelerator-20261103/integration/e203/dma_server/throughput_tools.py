"""Compare timing and data while recording the two-file accelerator RTL overlay."""
import math
import re
from pathlib import Path
from real_tools import sha

BASELINE_CYCLES=2486736
BASELINE_IMAGE='c9aad8e6b06574ea721bb8a65e5da5aa63cd4a02e388797e7f10eb2951e1a8ed'

def validate_baseline(report,root):
    root=Path(root).resolve()
    if report.get('status')!='PASS_E203_THROUGHPUT_ICB':raise ValueError('Baseline must be final stream-ICB PASS')
    if report.get('firmware_sha256')!=BASELINE_IMAGE:raise ValueError('Unexpected baseline firmware')
    if report.get('timing',{}).get('cycles')!=BASELINE_CYCLES:raise ValueError('Unexpected baseline cycles')
    if report.get('audit',{}).get('outputs')!=25344 or report['audit'].get('bit_mismatches')!=0:
        raise ValueError('Baseline results incomplete')
    if not report.get('input_sha256'):raise ValueError('Baseline source hashes missing')
    for name,want in report['input_sha256'].items():
        path=Path(name)
        if not path.is_absolute() or not path.is_file() or sha(path)!=want:
            raise ValueError('Server baseline input changed/missing: '+name)
    return True

def compare_reports(baseline,current):
    for field in ['input_sha256','prepared_data_sha256','sample']:
        if not baseline.get(field) or baseline[field]!=current.get(field):
            raise ValueError('Incomparable baseline/candidate '+field)
    for field in ['period_ps','host_period_ps','load_cycles','load_words','result_words']:
        if baseline['timing'][field]!=current['timing'][field]:raise ValueError('Changed timing contract: '+field)
    old=baseline['timing']['cycles'];new=current['timing']['cycles']
    if not all(math.isfinite(v) and v>0 for v in [old,new]):raise ValueError('Invalid cycles')
    if current['audit']['outputs']!=25344 or current['audit']['bit_mismatches']!=0:raise ValueError('Candidate correctness failed')
    return dict(baseline_cycles=old,candidate_cycles=new,saved_cycles=old-new,
                cycle_reduction_percent=(old-new)/old*100,throughput_speedup=old/new,
                throughput_improved=new<old,server_baseline_sources_and_data_match=True,
                candidate_rtl_overlay=current.get('candidate_rtl_sha256'))

def audit_profile(text,timing):
    lines=re.findall(r'^DRIVER_PROFILE (.+)$',text,re.M)
    if len(lines)!=1:raise ValueError('Missing/duplicate driver profile')
    pairs=re.findall(r'(\w+)=([0-9]+(?:\.[0-9]+)?)',lines[0])
    keys=['poison_first_ps','poison_last_ps','input_first_ps','input_last_ps','result_first_ps','result_last_ps',
          'poison_words','input_words','result_words']
    if len(pairs)!=len(keys) or set(k for k,v in pairs)!=set(keys):raise ValueError('Malformed driver profile')
    v={k:float(x) for k,x in pairs}
    if not all(math.isfinite(x) for x in v.values()):raise ValueError('Nonfinite driver profile')
    if (v['poison_words'],v['input_words'],v['result_words'])!=(25344,22976,25344):raise ValueError('Profile count mismatch')
    if not(v['poison_first_ps']<=v['poison_last_ps']<v['input_first_ps']<=v['input_last_ps']<=v['result_last_ps']
           and v['input_first_ps']<=v['result_first_ps']<=v['result_last_ps']):raise ValueError('Profile ordering mismatch')
    period=timing['period_ps'];load_end=(timing['start_cycle']+timing['load_cycles'])*period
    if abs(v['result_last_ps']-timing['end_cycle']*period)>0.01 or load_end>v['poison_first_ps']:
        raise ValueError('Profile does not match timing endpoints')
    v.update(boot_initialization_setup_cycles=(v['input_first_ps']-load_end)/period,
             input_read_to_final_result_cycles=(v['result_last_ps']-v['input_first_ps'])/period,
             poison_write_span_cycles=(v['poison_last_ps']-v['poison_first_ps'])/period,
             input_read_span_cycles=(v['input_last_ps']-v['input_first_ps'])/period,
             result_write_span_cycles=(v['result_last_ps']-v['result_first_ps'])/period,
             span_warning='Input-read and result-write spans overlap computation and each other; not exclusive busy cycles')
    return v

def add_profile_wiring(tb):
    module='''
 kwt_profile_probe u_profile_probe(
 .clk(u_e203_soc_top.kwt_bus_clk),.host_mode(kwt_load_mode),
 .cmd_valid(u_e203_soc_top.sysmem_icb_cmd_valid && !kwt_load_mode),
 .cmd_ready(u_e203_soc_top.sysmem_icb_cmd_ready),.cmd_read(u_e203_soc_top.sysmem_icb_cmd_read),
 .cmd_addr(u_e203_soc_top.sysmem_icb_cmd_addr),.cmd_data(u_e203_soc_top.sysmem_icb_cmd_wdata),
 .cmd_mask(u_e203_soc_top.sysmem_icb_cmd_wmask),
 .rsp_valid(u_e203_soc_top.sysmem_icb_rsp_valid),.rsp_ready(u_e203_soc_top.sysmem_icb_rsp_ready),
 .rsp_err(u_e203_soc_top.sysmem_icb_rsp_err));
'''
    matches=list(re.finditer(r'^\s*endmodule\b',tb,re.M))
    if len(matches)!=1:raise ValueError('Unrecognized TB module boundary')
    p=matches[0].start();return tb[:p]+module+tb[p:]
