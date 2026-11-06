#!/usr/bin/env python3
"""Stage and functionally test E203 TCM adapters using official 4096x16 SRAMs.

Writes only Desktop/dc. No production/peer RTL is changed, no DC compile is run.
The server's original FPGA TCM wrappers are the independent reference models.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

DESKTOP=Path('/storage1/2026contest/server2/s2_21usr/Desktop')
ROOT=DESKTOP/'e203-integration/kwt-soc'
DC=DESKTOP/'dc'
SRAM=Path('/storage1/admin_public_dir/SRAM_Lib_2025')

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def clean(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
def need(v,s):
    if not v:raise ValueError(s)

GUARD='''`include "e203_defines.v"
module kwt_soc_tcm_configuration_guard;
`ifndef E203_HAS_ITCM
  KWT_TCM_REQUIRES_EXISTING_ITCM bad_itcm();
`endif
`ifndef E203_HAS_DTCM
  KWT_TCM_REQUIRES_EXISTING_DTCM bad_dtcm();
`endif
`ifdef E203_HAS_ECC
  KWT_TCM_ECC_CONFIGURATION_NEEDS_REVIEW bad_ecc();
`endif
generate
 if (`E203_ITCM_RAM_AW != 15 || `E203_ITCM_RAM_DW != 64 || `E203_ITCM_RAM_MW != 8 ||
     `E203_ITCM_RAM_DP != 32768) begin : invalid_itcm
   KWT_TCM_ITCM_CONFIGURATION_MISMATCH stop();
 end
 if (`E203_DTCM_RAM_AW != 16 || `E203_DTCM_RAM_DW != 32 || `E203_DTCM_RAM_MW != 4 ||
     `E203_DTCM_RAM_DP != 65536) begin : invalid_dtcm
   KWT_TCM_DTCM_CONFIGURATION_MISMATCH stop();
 end
endgenerate
endmodule
'''

def adapter(name,aw,dw):
    return '''`default_nettype none
// ASIC adapter; identical public TCM interface, one-cycle reads, active-high byte WEM.
// No FPGA branch: this file always instantiates official SRAM, including during its test.
module %s #(parameter ADDRWIDTH=%d, parameter DATAWIDTH=%d)(
 input CLK, input RSTN, input [ADDRWIDTH-1:0] ADDRESS,
 input CS, input WE, input [DATAWIDTH/8-1:0] WEM,
 input [DATAWIDTH-1:0] WDATA, output [DATAWIDTH-1:0] RDATA
);
localparam BANK_BITS=ADDRWIDTH-12;
localparam BANKS=1<<BANK_BITS;
localparam LANES=DATAWIDTH/16;
wire [DATAWIDTH-1:0] bank_q [0:BANKS-1];
reg [BANK_BITS-1:0] read_bank;
kwt_soc_tcm_configuration_guard u_configuration_guard();
generate if (ADDRWIDTH!=%d || DATAWIDTH!=%d) begin : invalid_parameters
 KWT_TCM_WRAPPER_PARAMETER_MISMATCH stop();
end endgenerate
// Original ASIC wrapper records bank bits every clock and resets only this selector.
always @(posedge CLK or negedge RSTN) begin
 if (!RSTN) read_bank <= {BANK_BITS{1'b0}};
 else read_bank <= ADDRESS[ADDRWIDTH-1:12];
end
assign RDATA=bank_q[read_bank];
genvar b,l;
generate for(b=0;b<BANKS;b=b+1) begin : gen_bank
 localparam [BANK_BITS-1:0] BANK_ID=b;
 for(l=0;l<LANES;l=l+1) begin : gen_lane
  wire [15:0] wen=~{{8{WEM[2*l+1]}},{8{WEM[2*l]}}};
  RAMSP4096X16_rtl_top u_sram(
   .Q(bank_q[b][16*l +: 16]), .CLK(CLK),
   .CEN(!(CS && ADDRESS[ADDRWIDTH-1:12]==BANK_ID)),
   .GWEN(!WE), .WEN(wen), .A(ADDRESS[11:0]), .D(WDATA[16*l +: 16]),
   .EMA(3'd2), .EMAW(2'd0), .RET1N(1'b1));
 end
end endgenerate
endmodule
`default_nettype wire
'''%(name,aw,dw,aw,dw)

TB='''`timescale 1ns/1ps
module tb_soc_tcm;
 reg clk=0; always #10 clk=~clk;
 reg rst_n=0;
 reg ics=0,iwe=0,dcs=0,dwe=0;
 reg [14:0] ia=0; reg [15:0] da=0;
 reg [7:0] im=0; reg [3:0] dm=0;
 reg [63:0] id=0; reg [31:0] dd=0;
 wire [63:0] iq,irq; wire [31:0] dq,drq;
 integer transactions=0;
 sram_wrap_32KX64 dut_i(.CLK(clk),.RSTN(rst_n),.ADDRESS(ia),.CS(ics),.WE(iwe),.WEM(im),.WDATA(id),.RDATA(iq));
 sram_wrap_64KX32 dut_d(.CLK(clk),.RSTN(rst_n),.ADDRESS(da),.CS(dcs),.WE(dwe),.WEM(dm),.WDATA(dd),.RDATA(dq));
 ref_sram_wrap_32KX64 ref_i(.CLK(clk),.RSTN(rst_n),.ADDRESS(ia),.CS(ics),.WE(iwe),.WEM(im),.WDATA(id),.RDATA(irq));
 ref_sram_wrap_64KX32 ref_d(.CLK(clk),.RSTN(rst_n),.ADDRESS(da),.CS(dcs),.WE(dwe),.WEM(dm),.WDATA(dd),.RDATA(drq));
 function [63:0] base_data;
  input integer a;
  begin base_data={32'h87654321 ^ a,32'h13579bdf+a*32'h10203};end
 endfunction
 function [63:0] masked;
  input [63:0] old_word,new_word; input [7:0] mask;
  integer j;
  begin masked=old_word;for(j=0;j<8;j=j+1)if(mask[j])masked[j*8 +:8]=new_word[j*8 +:8];end
 endfunction
 task istep;
  input wr;input [14:0] a;input [63:0] data;input [7:0] mask;input [63:0] expected;
  begin
   @(negedge clk);ics=1;iwe=wr;ia=a;id=data;im=mask;
   @(posedge clk);#3;transactions=transactions+1;
   if(!wr && (iq!==expected || irq!==expected))begin
    $display("TCM_FAIL ITCM addr=%%h got=%%h reference=%%h expected=%%h",a,iq,irq,expected);$fatal(1);
   end
  end
 endtask
 task dstep;
  input wr;input [15:0] a;input [31:0] data;input [3:0] mask;input [31:0] expected;
  begin
   @(negedge clk);dcs=1;dwe=wr;da=a;dd=data;dm=mask;
   @(posedge clk);#3;transactions=transactions+1;
   if(!wr && (dq!==expected || drq!==expected))begin
    $display("TCM_FAIL DTCM addr=%%h got=%%h reference=%%h expected=%%h",a,dq,drq,expected);$fatal(1);
   end
  end
 endtask
 integer a,b,m,words; reg [63:0] initial_word,changed,expected;
 initial begin
  repeat(3)@(negedge clk);rst_n=1;
  $display("TCM_TEST_START ITCM_WORDS=32768 DTCM_WORDS=65536");
  for(a=0;a<32768;a=a+1)istep(1,a,base_data(a),8'hff,0);
  for(a=0;a<32768;a=a+1)istep(0,a,0,0,base_data(a));
  @(negedge clk);ics=0;
  $display("TCM_ITCM_FULL_CAPACITY_PASS words=32768");
  for(a=0;a<65536;a=a+1)dstep(1,a,base_data(a),4'hf,0);
  for(a=0;a<65536;a=a+1)dstep(0,a,0,0,base_data(a));
  @(negedge clk);dcs=0;
  $display("TCM_DTCM_FULL_CAPACITY_PASS words=65536");
  for(b=0;b<8;b=b+1)begin
   a=b*4096+37;initial_word=base_data(a);changed=~initial_word;
   for(m=0;m<256;m=m+1)begin
    istep(1,a,initial_word,8'hff,0);istep(1,a,changed,m,0);
    expected=masked(initial_word,changed,m);istep(0,a,0,0,expected);
   end
  end
  @(negedge clk);ics=0;
  for(b=0;b<16;b=b+1)begin
   a=b*4096+37;initial_word=base_data(a);changed=~initial_word;
   for(m=0;m<16;m=m+1)begin
    dstep(1,a,initial_word,4'hf,0);dstep(1,a,changed,m,0);
    expected=masked(initial_word,changed,m);dstep(0,a,0,0,expected);
   end
  end
  @(negedge clk);dcs=0;
  $display("TCM_ALL_BYTE_MASKS_PASS itcm_masks=256 dtcm_masks=16");
  // Force rapid changes of depth bank; cover both sides of every bank boundary.
  for(b=7;b>=0;b=b-1)begin
   a=b*4096;istep(0,a,0,0,base_data(a));a=b*4096+4095;istep(0,a,0,0,base_data(a));
  end
  @(negedge clk);ics=0;
  for(b=15;b>=0;b=b-1)begin
   a=b*4096;dstep(0,a,0,0,base_data(a));a=b*4096+4095;dstep(0,a,0,0,base_data(a));
  end
  @(negedge clk);dcs=0;ics=0;rst_n=0;ia=32767;da=65535;
  repeat(3)@(negedge clk);rst_n=1;
  istep(0,32767,0,0,base_data(32767));
  @(negedge clk);ics=0;
  dstep(0,65535,0,0,base_data(65535));
  @(negedge clk);dcs=0;
  $display("TCM_BANK_BOUNDARY_AND_RESET_RETENTION_PASS");
  $display("PASS_TCM_OFFICIAL_FUNCTIONAL transactions=%%0d physical_4096x16_macros=64",transactions);
  $finish;
 end
 initial begin #10000000; $display("TCM_FAIL TIMEOUT");$fatal(1);end
endmodule
'''.replace('%%','%')

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--prepare-only',action='store_true');a=ap.parse_args()
    need((ROOT/'kwt_dma_soc_top.v').is_file(),'Current relocated kwt-soc top missing')
    core=ROOT/'e203/core';wrap=ROOT/'e203/mem_wrap'
    refs=[wrap/(n+'.v') for n in ['sram_wrap_32KX64','sram_wrap_64KX32']]
    models=[SRAM/'RAMSP4096X16/verilog'/n for n in ['RAMSP4096X16_rtl.v','RAMSP4096X16.v']]
    inputs=refs+models+[core/'config.v',core/'e203_defines.v']
    for p in inputs:need(p.is_file(),'Missing input: '+str(p))
    # Source-side defaults and ports must still match the server screenshots we reviewed.
    for p,aw,dw in zip(refs,[15,16],[64,32]):
        s=clean(p.read_text())
        need(re.search(r'parameter\s+ADDRWIDTH\s*=\s*%d\b'%aw,s) is not None,'Wrapper ADDRWIDTH changed: '+p.name)
        need(re.search(r'parameter\s+DATAWIDTH\s*=\s*%d\b'%dw,s) is not None,'Wrapper DATAWIDTH changed: '+p.name)
        need('`ifdef FPGA' in s,'Original FPGA reference branch missing')
    need(re.search(r'`define\s+E203_CFG_ITCM_ADDR_WIDTH\s+18\b',clean((core/'config.v').read_text())) is not None,'ITCM capacity changed')
    need(re.search(r'`define\s+E203_CFG_DTCM_ADDR_WIDTH\s+18\b',clean((core/'config.v').read_text())) is not None,'DTCM capacity changed')
    vcs=shutil.which('vcs');need(vcs or a.prepare_only,'vcs not in PATH')
    (DC/'runs').mkdir(parents=True,exist_ok=True)
    run=Path(tempfile.mkdtemp(prefix='soc-tcm-prepare-',dir=str(DC/'runs')))
    stage=run/'adapter';stage.mkdir();reference=run/'reference';reference.mkdir()
    before={str(p):sha(p) for p in inputs}
    for p in refs:
        s=p.read_text();name=p.stem
        s,count=re.subn(r'(\bmodule\s+)'+name+r'\b',r'\1ref_'+name,s)
        need(count==1,'Ambiguous reference module: '+name)
        (reference/p.name).write_text(s)
    for name,aw,dw in [('sram_wrap_32KX64',15,64),('sram_wrap_64KX32',16,32)]:
        (stage/(name+'.v')).write_text(adapter(name,aw,dw))
    (stage/'kwt_soc_tcm_configuration_guard.v').write_text(GUARD)
    (run/'tb_soc_tcm.v').write_text(TB)
    # Copy the shared-SRAM TT DB from the peer read-only into our own library directory.
    libname='RAMSP4096X16_tt_1p10v_1p10v_125c.db'
    source_lib=DESKTOP/'kwt_dc/library/tt_corner'/libname
    need(source_lib.is_file(),'Previously observed shared-SRAM TT DB missing')
    before[str(source_lib)]=sha(source_lib)
    dest=DC/'libs/tt_hvt_1p1_125c'/libname;dest.parent.mkdir(parents=True,exist_ok=True)
    if dest.exists():need(sha(dest)==sha(source_lib),'Existing own SRAM DB differs; do not overwrite')
    else:
        with source_lib.open('rb') as src,dest.open('xb') as out:shutil.copyfileobj(src,out)
    before[str(dest)]=sha(dest)
    before.update({str(p):sha(p) for p in list(stage.glob('*.v'))+list(reference.glob('*.v'))+[run/'tb_soc_tcm.v']})
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'soc_memory_sources.f').write_text('+incdir+'+str(core)+'\n'+'\n'.join(str(p) for p in [stage/'kwt_soc_tcm_configuration_guard.v',stage/'sram_wrap_32KX64.v',stage/'sram_wrap_64KX32.v',models[0]])+'\n')
    (run/'README.txt').write_text('Staged E203 TCM ASIC adapters only. Production/peer source files are unchanged.\n'
        'ITCM: 32768x64, 256KiB, 32 approved 4096x16 SRAMs. DTCM: 65536x32, 256KiB, another32.\n'
        'Full byte-mask interface and one-cycle selected reads retained. No memory clear on reset.\n'
        'Original server wrappers, with module names prefixed ref_, provide FPGA-array reference.\n'
        'VCS functional test uses FPGA only for those reference models and ARM_UD_MODEL for official macros.\n'
        'ASIC staged adapters themselves have no FPGA branch; whole-SoC synthesis must not define FPGA.\n'
        'This is not a whole-SoC test, SRAM timing acceptance or synthesis pass.\n'
        'Before using soc_memory_sources.f, remove original two TCM wrapper compilation units to avoid duplicates.\n')
    print('RUN='+str(run),flush=True)
    print('STAGED_ONLY ITCM=256KiB/32macros DTCM=256KiB/32macros; production unchanged',flush=True)
    if a.prepare_only:print('PREPARED_ONLY; functional test not run');return
    sources=[stage/'kwt_soc_tcm_configuration_guard.v',stage/'sram_wrap_32KX64.v',stage/'sram_wrap_64KX32.v',*models,*[reference/p.name for p in refs],run/'tb_soc_tcm.v']
    cmd=[vcs,'-full64','-sverilog','-timescale=1ns/1ps','+define+FPGA+ARM_UD_MODEL','+incdir+'+str(core),'-top','tb_soc_tcm',*map(str,sources),'-Mdir='+str(run/'csrc'),'-o',str(run/'simv')]
    report={'status':'RUNNING_TCM_ADAPTER_TEST','production_modified':False,'peer_modified':False,'synthesis_run':False,'expected_4096x16_macros':64,'commands':[cmd]}
    def save(): (run/'result.json').write_text(json.dumps(report,indent=2)+'\n')
    save()
    print('COMPILING_TCM_UNIT_TEST; detailed logs saved in run directory',flush=True)
    with (run/'compile.log').open('w') as log:proc=subprocess.run(cmd,cwd=str(run),stdout=log,stderr=subprocess.STDOUT,timeout=7200)
    text=(run/'compile.log').read_text(errors='replace')
    if proc.returncode or re.search(r'Error-\[|Warning-\[(?:IPDW|PCWM)',text):
        report.update(status='FAIL_TCM_COMPILE',returncode=proc.returncode);save();raise ValueError('TCM compile failed; see '+str(run/'compile.log'))
    print('TCM_COMPILE_PASS',flush=True)
    with (run/'run.log').open('w') as log:proc=subprocess.run([str(run/'simv')],cwd=str(run),stdout=log,stderr=subprocess.STDOUT,timeout=7200)
    text=(run/'run.log').read_text(errors='replace')
    for line in text.splitlines():
        if line.startswith(('TCM_','PASS_TCM_')):print(line)
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(Path(p))!=h]
    passed=(proc.returncode==0 and text.count('PASS_TCM_OFFICIAL_FUNCTIONAL transactions=')==1
            and not re.search(r'TCM_FAIL|\bFatal\b|\bFATAL\b',text) and not changed)
    report.update(status='PASS_TCM_OFFICIAL_FUNCTIONAL_REQUIRES_SOC_INTEGRATION' if passed else 'FAIL_TCM_FUNCTIONAL',returncode=proc.returncode,changed_inputs=changed)
    save()
    need(passed,'TCM test not passed; preserve '+str(run/'run.log'))
    # Compact read-only inventory for the next whole-SoC source/link step.
    generic={}
    for name in ['GENERIC_RVT_SMIC.v','GENERIC_LVT_SMIC.v']:
        p=ROOT/'e203/generic'/name
        if p.is_file():
            body=clean(p.read_text())
            refs=sorted(set(t for t,inst in re.findall(r'\b([A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*\(',body)
                            if t not in {'module','if','else','for','while','case','function','task','begin','end'}))
            generic[name]={'sha256':sha(p),'primitive_tokens_lexical':refs}
            print('NEXT_GENERIC '+name+' REFS='+','.join(refs[:10])+' TOTAL='+str(len(refs)))
    report['generic_inventory_lexical']=generic;save()
    print('RESULT=PASS_TCM_OFFICIAL_FUNCTIONAL; next=whole-SoC source selection and link')

if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:raise SystemExit('STOP: '+str(e))
