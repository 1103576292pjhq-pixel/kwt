"""Reuse the passed loader/timing environment around the new production DMA top."""
import re
from prepare_soc import convert
from real_tools import prepare_wiring as loader_wiring
from timing_tools import timed_wiring

SHARED=r'kwt_shared_sram\s*#\([^;]+?\)\s*u_shared_sram\s*\((.*?)\);'

def replace_shared(text,transform):
    matches=list(re.finditer(SHARED,text,re.S))
    if len(matches)!=1:
        raise ValueError('Expected exactly one shared SRAM instance')
    match=matches[0]
    return text[:match.start()]+transform(match[0])+text[match.end():]

def prepare_wiring(original_soc,original_tb):
    # The original source supplies platform ports, clocks and resets.
    production=convert(original_soc)
    adapted,count=re.subn(r'\bmodule\s+kwt_dma_soc_top\s*\(', 'module kwt_shared_soc_top(',production,count=1)
    if count!=1:
        raise ValueError('Missing generated DMA module header')
    adapted=replace_shared(adapted,lambda instance:instance.replace('kwt_dma_shared_','sysmem_icb_'))
    soc,tb=timed_wiring(adapted,original_tb,loader_wiring)
    # Retarget only the loader's SRAM mux and return assignments to the arbiter output.
    # The CPU-facing arbiter ports keep their original SysMem signals.
    soc=replace_shared(soc,lambda instance:instance.replace('sysmem_icb_','kwt_dma_shared_'))
    for suffix in ['cmd_ready','rsp_valid','rsp_err','rsp_rdata']:
        soc,count=re.subn(r'assign\s+sysmem_icb_'+suffix+r'\s*=',
                         'assign kwt_dma_shared_'+suffix+' =',soc)
        if count!=1:
            raise ValueError('Unrecognized loader response mux '+suffix)
    # Observe DMA and CPU traffic together at the shared SRAM boundary.
    tb=tb.replace('u_e203_soc_top.sysmem_icb_','u_e203_soc_top.kwt_dma_shared_')
    return soc,tb
