#!/usr/bin/env python3
"""Validate actual firmware preload against official SRAM port reads, all ITCM words.
Creates a reusable simulation-only preload task; no production RTL/library edits.
"""
import hashlib,json,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
SRAM=Path('/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP4096X16/verilog')
def need(v,s):
    if not v:raise ValueError(s)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def clean(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
def child(text,parent,cell):
    block=re.search(r'\bmodule\s+'+parent+r'\b(.*?)\bendmodule\b',clean(text),re.S)
    need(block,'Missing wrapper '+parent)
    instances=re.findall(r'\b'+cell+r'\s+(\w+)\s*\(',block.group(1))
    need(len(instances)==1,'Ambiguous SRAM wrapper hierarchy: '+parent)
    return instances[0]
def task_text(hierarchy):
    lines=['// Simulation-only initialization; byte order matches original testbench.',
      '// Define KWT_ITCM_ASIC_PATH to the sram_wrap_32KX64 instance.',
      '// Caller supplies reg [7:0] itcm_mem [0:262143], loaded from the frozen firmware.',
      'task kwt_preload_asic_itcm;', ' integer pa,pb;', ' begin',
      '  #1; // Run after the official model initial blocks, before CPU release.']
    for bank in range(8):
        for lane in range(4):
            path='`KWT_ITCM_ASIC_PATH.gen_bank[%d].gen_lane[%d].u_sram.%s.mem'%(bank,lane,hierarchy)
            lines += ['  for(pa=0;pa<4096;pa=pa+1) for(pb=0;pb<16;pb=pb+1)',
              '   '+path+'[pa>>3][8*pb+(pa&7)] = itcm_mem[(%d*4096+pa)*8+%d*2+(pb/8)][pb%%8];'%(bank,lane)]
    lines += [' end','endtask','']
    return '\n'.join(lines)
TB='''`timescale 1ns/1ps
`define KWT_ITCM_ASIC_PATH tb_itcm_preload.dut
module tb_itcm_preload;
reg clk=0;always #10 clk=~clk;
reg rst_n=0,cs=0,we=0;reg [14:0] addr=0;reg [7:0] mask=0;reg [63:0] data=0;
wire [63:0] q;
reg [7:0] itcm_mem [0:262143];
reg [4095:0] image;
integer i,j;reg [63:0] expected;
sram_wrap_32KX64 #(.ADDRWIDTH(15),.DATAWIDTH(64)) dut(
 .CLK(clk),.RSTN(rst_n),.ADDRESS(addr),.CS(cs),.WE(we),.WEM(mask),.WDATA(data),.RDATA(q));
`include "itcm_asic_preload.vh"
initial begin
 if(!$value$plusargs("firmware=%s",image))$fatal(1,"PRELOAD_FAIL missing firmware");
 for(i=0;i<262144;i=i+1)itcm_mem[i]=0;
 $readmemh(image,itcm_mem);
 kwt_preload_asic_itcm;
 repeat(3)@(negedge clk);rst_n=1;
 for(i=0;i<32768;i=i+1)begin
  @(negedge clk);addr=i;cs=1;
  for(j=0;j<8;j=j+1)expected[j*8 +:8]=itcm_mem[i*8+j];
  @(posedge clk);#3;
  if(q!==expected)begin $display("PRELOAD_FAIL firmware addr=%0d actual=%h expected=%h",i,q,expected);$fatal(1);end
 end
 @(negedge clk);cs=0;
 $display("FIRMWARE_PORT_READBACK_PASS words=32768 bytes=262144 macros=32");
 // Second pass fills unused firmware locations too, exercising all banks/columns/bits.
 for(i=0;i<262144;i=i+1)itcm_mem[i]=(i ^ (i>>8) ^ (i>>16) ^ 8'ha5);
 kwt_preload_asic_itcm;
 for(i=0;i<32768;i=i+1)begin
  @(negedge clk);addr=i;cs=1;
  for(j=0;j<8;j=j+1)expected[j*8 +:8]=itcm_mem[i*8+j];
  @(posedge clk);#3;
  if(q!==expected)begin $display("PRELOAD_FAIL pattern addr=%0d actual=%h expected=%h",i,q,expected);$fatal(1);end
 end
 $display("ASIC_ITCM_PRELOAD_PASS words_checked=65536 firmware_and_address_pattern=1");$finish;
end
initial begin #2000000;$fatal(1,"PRELOAD_FAIL timeout");end
endmodule
'''
def main():
    rs=sorted((DC/'runs').glob('soc-task-candidate-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    candidate=next((p.parent for p in rs if json.loads(p.read_text()).get('status')=='TASK_MODE_CANDIDATE_REPORTS_READY_REVIEW_REQUIRED'),None)
    need(candidate,'No current ASIC candidate')
    selected=json.loads((candidate/'source-selection.json').read_text())
    sources=[Path(p) for p in selected['source_files']]
    def find(name):
        ps=[p for p in sources if p.name==name];need(len(ps)==1,'Ambiguous source '+name);return ps[0]
    adapter=find('sram_wrap_32KX64.v');guard=find('kwt_soc_tcm_configuration_guard.v')
    firmware=ROOT/'test_env/build-01/real_shared_task.verilog'
    receipt=ROOT/'test_env/build-01/build-report.json'
    need(sha(firmware)==json.loads(receipt.read_text())['image_sha256'],'Firmware image differs from verified build')
    wrapper=SRAM/'RAMSP4096X16_rtl.v';model=SRAM/'RAMSP4096X16.v'
    model_text=clean(model.read_text());read_order=re.search(r'readLatch0\s*=\s*\{([^}]+)\}',model_text)
    need(read_order and [int(n) for n in re.findall(r'data_out\[(\d+)\]',read_order.group(1))]==list(range(120,-1,-8)),'Official SRAM bit layout changed')
    need(re.search(r'row_address\s*=\s*\(\s*A_int\s*>>\s*3\s*\)',model_text),'Official SRAM row layout changed')
    hierarchy=child(wrapper.read_text(),'RAMSP4096X16_rtl_top','RAMSP4096X16_fr_top')+'.'+child(wrapper.read_text(),'RAMSP4096X16_fr_top','RAMSP4096X16')
    vcs=shutil.which('vcs');need(vcs,'vcs not in PATH')
    run=Path(tempfile.mkdtemp(prefix='asic-itcm-preload-',dir=str(DC/'runs')))
    (run/'itcm_asic_preload.vh').write_text(task_text(hierarchy))
    tb=run/'tb_itcm_preload.sv';tb.write_text(TB)
    inputs=[adapter,guard,wrapper,model,firmware,receipt,ROOT/'e203/core/config.v',ROOT/'e203/core/e203_defines.v',tb,run/'itcm_asic_preload.vh']
    frozen=json.loads((candidate/'input-sha256.json').read_text())
    for p in [adapter,guard]:need(sha(p)==frozen.get(str(p)),'Candidate TCM source changed: '+str(p))
    before={str(p):sha(p) for p in inputs}
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    cmd=[vcs,'-full64','-sverilog','-timescale=1ns/1ps','+define+ARM_UD_MODEL',
      '+incdir+'+str(ROOT/'e203/core')+'+'+str(run),'-top','tb_itcm_preload',str(guard),str(adapter),str(wrapper),str(model),str(tb),'-Mdir='+str(run/'csrc'),'-o',str(run/'simv')]
    (run/'command.json').write_text(json.dumps(cmd,indent=2)+'\n')
    print('RUN='+str(run),flush=True);print('VERIFYING_ASIC_FIRMWARE_PRELOAD; official macros; no FPGA define',flush=True)
    with (run/'compile.log').open('w') as log:c=subprocess.run(cmd,cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    ok=False
    if c.returncode==0:
        with (run/'simulation.log').open('w') as log:p=subprocess.run([str(run/'simv'),'+firmware='+str(firmware)],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
        text=(run/'simulation.log').read_text(errors='replace')
        for s in text.splitlines():
            if any(k in s for k in ['PRELOAD_PASS','READBACK_PASS','PRELOAD_FAIL','Fatal']):print(s)
        ok=p.returncode==0 and 'ASIC_ITCM_PRELOAD_PASS' in text
    else:
        lines=(run/'compile.log').read_text(errors='replace').splitlines()
        for i,s in enumerate(lines):
            if 'Error-' in s:print('\n'.join(lines[i:i+6]));break
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(p)!=h]
    ok=ok and not changed
    status='ASIC_ITCM_PRELOAD_PASS_REQUIRES_TASK_INTEGRATION' if ok else 'FAIL_ASIC_ITCM_PRELOAD'
    (run/'result.json').write_text(json.dumps({'status':status,'candidate':str(candidate),'firmware_sha256':sha(firmware),
      'include':str(run/'itcm_asic_preload.vh'),'macro_hierarchy':hierarchy,'changed_inputs':changed,
      'initialization_policy':'Unused firmware bytes zero-filled; initialization is outside measured task window',
      'full_soc_tested':False,'power_evaluated':False,'production_modified':False},indent=2)+'\n')
    print('RESULT='+status)
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
