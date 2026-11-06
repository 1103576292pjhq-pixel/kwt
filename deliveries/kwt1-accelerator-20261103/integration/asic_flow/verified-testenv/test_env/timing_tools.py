"""Simulation-only timing instrumentation; no accelerator/firmware edits."""
import math
import re


def timed_loader(text):
    gold="   for(i=0;i<25344;i=i+1)write_word(32'ha0040000+4*i,gold[i]);\n"
    anchor="   for(i=0;i<6336;i=i+1)write_word(32'ha0000000+4*i,x[i]);\n"
    if text.count(gold)!=1 or text.count(anchor)!=1 or text.index(gold)<text.index(anchor):
        raise ValueError('Unrecognized/already timed loader')
    return text.replace(gold,'').replace(anchor,gold+anchor)


def audit_timing(text):
    lines=re.findall(r'^TIMING_WINDOW (.+)$',text,re.M)
    if len(lines)!=1:raise ValueError('Missing/duplicate timing window')
    keys=['start_cycle','first_accept_cycle','end_cycle','cycles','load_cycles','cpu_path_cycles',
          'elapsed_ps','period_ps','host_period_ps','load_words','result_words']
    pairs=re.findall(r'(\w+)=([0-9]+(?:\.[0-9]+)?)',lines[0])
    if len(pairs)!=len(keys) or set(k for k,v in pairs)!=set(keys):raise ValueError('Malformed timing window')
    v={k:float(value) for k,value in pairs}
    if not all(math.isfinite(x) for x in v.values()):raise ValueError('Nonfinite timing')
    if not(v['start_cycle']<=v['first_accept_cycle']<v['end_cycle'] and v['cycles']>0 and
           v['load_cycles']>0 and v['cpu_path_cycles']>0 and v['period_ps']>0 and
           v['host_period_ps']==v['period_ps'] and v['load_words']==22976 and v['result_words']==25344):
        raise ValueError('Invalid timing/counts/clocks')
    for delta in [v['end_cycle']-v['start_cycle']-v['cycles'],
                  v['load_cycles']+v['cpu_path_cycles']-v['cycles'],
                  v['elapsed_ps']/v['period_ps']-v['cycles']]:
        if abs(delta)>1e-6:raise ValueError('Inconsistent timing arithmetic')
    v.update(simulated_latency_ms=v['elapsed_ps']/1e9,
             target_150mhz_latency_ms=v['cycles']/150000,
             target_150mhz_tasks_per_second=150000000/v['cycles'],
             target_150mhz_mac_per_second=1622016*150000000/v['cycles'],
             target_frequency_validated_by_sta=False)
    return v


def timed_wiring(soc,tb,prepare):
    soc,tb=prepare(soc,tb)
    connections='''
 kwt_timing_probe u_timing_probe(
 .clk(clk),.cpu_clk(u_e203_soc_top.kwt_bus_clk),.host_mode(kwt_load_mode),
 .host_valid(kwt_load_cmd_valid),.host_ready(kwt_load_cmd_ready),.host_read(kwt_load_cmd_read),
 .host_addr(kwt_load_cmd_addr),.host_data(kwt_load_cmd_wdata),.host_mask(kwt_load_cmd_wmask),
 .host_rsp_valid(kwt_load_rsp_valid),.host_rsp_ready(kwt_load_rsp_ready),.host_rsp_err(kwt_load_rsp_err),
 .cpu_valid(u_e203_soc_top.sysmem_icb_cmd_valid && !kwt_load_mode),
 .cpu_ready(u_e203_soc_top.sysmem_icb_cmd_ready),.cpu_read(u_e203_soc_top.sysmem_icb_cmd_read),
 .cpu_addr(u_e203_soc_top.sysmem_icb_cmd_addr),.cpu_data(u_e203_soc_top.sysmem_icb_cmd_wdata),
 .cpu_mask(u_e203_soc_top.sysmem_icb_cmd_wmask),
 .cpu_rsp_valid(u_e203_soc_top.sysmem_icb_rsp_valid),.cpu_rsp_ready(u_e203_soc_top.sysmem_icb_rsp_ready),
 .cpu_rsp_err(u_e203_soc_top.sysmem_icb_rsp_err));
'''
    # Insert after base loader/monitor declarations, where clk is already declared.
    matches=list(re.finditer(r'^[ \t]*endmodule\b',tb,re.M))
    if len(matches)!=1:raise ValueError('Expected one original TB module')
    at=matches[0].start()
    return soc,tb[:at]+connections+tb[at:]
