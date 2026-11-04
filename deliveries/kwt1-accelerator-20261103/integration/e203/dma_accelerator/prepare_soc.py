"""Generate a separate DMA SoC top from this project's shared-SRAM SoC top."""
import argparse
import hashlib
import json
from pathlib import Path
import re

BUS=['cmd_valid','cmd_ready','cmd_addr','cmd_read','cmd_wdata','cmd_wmask',
     'rsp_valid','rsp_ready','rsp_rdata','rsp_err']

def convert(source):
    if 'kwt_dma_accelerator' in source:raise ValueError('Source already contains DMA')
    text,count=re.subn(r'\bmodule\s+kwt_shared_soc_top\s*\(', 'module kwt_dma_soc_top(',source,count=1)
    if count!=1:raise ValueError('Expected production kwt_shared_soc_top')
    pattern=r'kwt_accelerator\s*#\((.*?)\)\s*u_kwt_accelerator\s*\((.*?)\);'
    matches=list(re.finditer(pattern,text,re.S))
    if len(matches)!=1:raise ValueError('Expected one known accelerator instance')
    match=matches[0]
    ports=dict(re.findall(r'\.(\w+)\s*\(([^()]*)\)',match[2]))
    required=['clk','rst_n']+['icb_'+name for name in BUS]
    if any(name not in ports for name in required):raise ValueError('Missing accelerator bus ports')
    for name in ['busy','compute_done','task_done','fault','error_code','abort_pending','abort_done']:
        if ports.get(name,'').strip():raise ValueError('Connected status port requires explicit migration: '+name)
    if re.sub(r'\s+','',ports.get('external_abort_req',''))!="1'b0":
        raise ValueError('External abort source requires explicit migration')
    connections=['.'+name+'('+ports[name]+')' for name in required]
    connections+=['.mem_'+name+'(kwt_dma_mem_'+name+')' for name in BUS]
    connections+=['.irq()']
    replacement='kwt_dma_accelerator #('+match[1]+') u_kwt_accelerator(\n'+',\n'.join(connections)+'\n);'
    text=text[:match.start()]+replacement+text[match.end():]
    pattern=r'kwt_shared_sram\s*#\((.*?)\)\s*u_shared_sram\s*\((.*?)\);'
    matches=list(re.finditer(pattern,text,re.S))
    if len(matches)!=1:raise ValueError('Expected one shared SRAM instance')
    match=matches[0];replacement=match[0]
    for name in BUS:
        replacement,count=re.subn(r'\.icb_'+name+r'\s*\(\s*sysmem_icb_'+name+r'\s*\)',
            '.icb_'+name+'(kwt_dma_shared_'+name+')',replacement)
        if count!=1:raise ValueError('Unrecognized shared-memory connection: '+name)
    text=text[:match.start()]+replacement+text[match.end():]
    declarations=[]
    for prefix in ['kwt_dma_mem','kwt_dma_shared']:
        for name in BUS:
            width='[31:0] ' if name in ['cmd_addr','cmd_wdata','rsp_rdata'] else ('[3:0] ' if name=='cmd_wmask' else '')
            declarations.append('wire '+width+prefix+'_'+name+';')
    connections=['.clk(kwt_bus_clk)','.rst_n(kwt_bus_rst_n)']
    names={'valid':'cmd_valid','ready':'cmd_ready','addr':'cmd_addr','data':'cmd_wdata',
           'read':'cmd_read','mask':'cmd_wmask','rsp_valid':'rsp_valid','rsp_ready':'rsp_ready',
           'rsp_data':'rsp_rdata','rsp_err':'rsp_err'}
    for port,prefix in [('a','sysmem_icb'),('b','kwt_dma_mem'),('m','kwt_dma_shared')]:
        connections+=['.'+port+'_'+name+'('+prefix+'_'+suffix+')' for name,suffix in names.items()]
    connections+=['.idle()']
    additions='\n'+'\n'.join(declarations)+'\nkwt_icb_arbiter2 u_dma_shared_arbiter(\n'+',\n'.join(connections)+'\n);\n'
    text,count=re.subn(r'^[ \t]*endmodule\b',lambda match:additions+match[0],text,count=1,flags=re.M)
    if count!=1:raise ValueError('Missing top module end')
    # Declare buses before instances: VCS otherwise creates implicit scalar nets.
    declaration_block='\n'.join(declarations)+'\n'
    if text.count(declaration_block)!=1:raise ValueError('Expected one DMA declaration block')
    text=text.replace(declaration_block,'',1)
    module_start=re.search(r'^\s*module\s+kwt_dma_soc_top\s*\(',text,re.M)
    if module_start is None:raise ValueError('Missing DMA module header')
    header_end=text.index(');',module_start.end())+2
    text=text[:header_end]+'\n'+declaration_block+text[header_end:]
    return text

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    raw=args.source.read_bytes()
    result=convert(raw.decode('utf-8'))
    args.output.mkdir(parents=True,exist_ok=False)
    target=args.output/'kwt_dma_soc_top.v'
    target.write_text(result,encoding='utf-8')
    report=dict(status='GENERATED_TOP_REQUIRES_PLATFORM_COMPILE',source=str(args.source.resolve()),
        source_sha256=hashlib.sha256(raw).hexdigest(),output=str(target.resolve()),
        output_sha256=hashlib.sha256(target.read_bytes()).hexdigest(),source_overwritten=False,
        irq_mode='CPU polls DMA_STATUS; IRQ output available on accelerator, left unconnected in this top')
    (args.output/'report.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report))

if __name__=='__main__':main()
