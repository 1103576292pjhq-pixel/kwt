#!/usr/bin/env python3
"""Stage minimal UART combinational default and compare actual UART instances.
Production unchanged. Passing simulation is bounded regression, not formal equivalence.
"""
import hashlib,json,re,shutil,subprocess,tempfile
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc'
def need(v,s):
    if not v:raise ValueError(s)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def clean(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
def stage(body):
    need(len(re.findall(r'\bfifo_tx_data\s*(?:<=|=(?!=))',clean(body)))==1,'UART data assignments changed')
    pattern=r"(?m)^(\s*)fifo_tx_valid\s*=\s*1'b0\s*;"
    need(len(re.findall(pattern,body))==1,'Default-valid anchor ambiguous')
    return re.sub(pattern,lambda m:m.group(0)+"\n"+m.group(1)+"fifo_tx_data = 8'h00; // Defined when no TX FIFO write is requested.",body,count=1)
def ports(body):
    need(len(re.findall(r"\bmodule\s+[A-Za-z_]\w*\b",clean(body)))==1,"Expected one UART module definition")
    s=clean(body);m=re.search(r'\bmodule\s+[A-Za-z_]\w*\b',s);need(m,'UART module declaration missing')
    header=s[m.end():s.index(';',m.end())];start=re.search(r'\binput\b',header);need(start,'ANSI input ports not found')
    header=header[start.start():].rstrip().rstrip(')').strip();out=[];direction=None
    for piece in header.split(','):
        d=re.match(r'\s*(input|output|inout)\b',piece)
        if d:direction=d.group(1);piece=piece[d.end():]
        piece=re.sub(r'\[[^\]]+\]',' ',piece)
        piece=re.sub(r'\b(wire|reg|logic|signed|unsigned)\b',' ',piece).strip()
        need(re.fullmatch(r'[A-Za-z_]\w*',piece) and direction,'Unsupported port declaration: '+piece)
        need(direction!='inout','Inout UART port requires manual harness review')
        out.append((direction,piece))
    need({'CLK','RSTN','PADDR','PWDATA','PSEL','PENABLE','PWRITE'}<=set(n for d,n in out),'Unexpected APB interface')
    return out
def make_tb(ps):
    mapping={'CLK':'clk','RSTN':'rst_n','PADDR':'addr','PWDATA':'wdata','PSEL':'sel','PENABLE':'enable','PWRITE':'wr'}
    connections=[];checks=[]
    for d,n in ps:
        if d=='input':
            v=mapping.get(n,'rx' if n.lower() in {'rx','rx_i','sin'} else "'0")
            connections.append('.'+n+'('+v+')')
        else:
            connections.append('.'+n+'()')
            checks.append('if (ref_uart.%s !== fix_uart.%s) begin $display("UART_FAIL output=%s cycle=%%0d",cycles); $fatal(1); end'%(n,n,n))
    con=','.join(connections)
    return '''`timescale 1ns/1ps
module tb_uart_fix;
reg clk=0; always #5 clk=~clk;
reg rst_n=0,sel=0,enable=0,wr=0,rx=1;
reg [31:0] addr=0,wdata=0;
integer cycles=0,valid_writes=0; integer i,j;
apb_uart_reference ref_uart(%s);
apb_uart_candidate fix_uart(%s);
always @(posedge clk) begin
 if(rst_n) begin
  if(ref_uart.fifo_tx_valid !== fix_uart.fifo_tx_valid) $fatal(1,"UART_FAIL TX valid differs");
  if(ref_uart.fifo_tx_valid) begin
   valid_writes=valid_writes+1;
   if(ref_uart.fifo_tx_data !== fix_uart.fifo_tx_data) $fatal(1,"UART_FAIL valid TX data differs");
  end
 end
 #1;
 if(rst_n) begin
  cycles=cycles+1;
  %s
 end
end
task access;
input write_en; input [31:0] a,d;
begin
 @(negedge clk);sel=1;enable=0;wr=write_en;addr=a;wdata=d;
 @(negedge clk);enable=1;
 @(negedge clk);sel=0;enable=0;wr=0;wdata=~d;
end endtask
initial begin
 repeat(4) @(negedge clk);rst_n=1;
 // 16550 register byte offsets are word-spaced on this APB interface.
 access(1,12,8'h83);access(1,0,2);access(1,4,0);access(1,12,3);
 access(1,8,6);access(1,4,3);
 // All byte values, FIFO pressure, status reads, and idle input changes.
 for(i=0;i<256;i=i+1) begin
  access(1,0,i);access(0,20,0);
  @(negedge clk);wdata=32'hdead0000+i;addr=28;
  if(i%%16==0)repeat(400)@(negedge clk);
 end
 repeat(6000)@(negedge clk);
 // DLAB writes must not act as THR writes; then clear FIFO and recover.
 access(1,12,8'h83);
 for(i=0;i<16;i=i+1)begin access(1,0,i+1);access(1,4,0);end
 access(1,12,3);access(1,8,6);
 for(i=0;i<16;i=i+1)access(1,0,255-i);
 repeat(3000)@(negedge clk);
 // Reset with traffic outstanding and restart transmission.
 rst_n=0;repeat(4)@(negedge clk);rst_n=1;
 access(1,12,8'h83);access(1,0,2);access(1,4,0);access(1,12,3);
 access(1,0,8'h55);access(1,0,8'haa);repeat(2000)@(negedge clk);
 if(valid_writes<256) $fatal(1,"UART_FAIL insufficient write coverage/address mapping");
 $display("UART_FIX_DIFFERENTIAL_PASS cycles=%%0d valid_writes=%%0d",cycles,valid_writes);$finish;
end
initial begin #1000000;$fatal(1,"UART_FAIL timeout");end
endmodule
'''%(con,con,'\n  '.join(checks))

def main():
    source=ROOT/'e203/perips/apb_uart/apb_uart.v';body=source.read_text();patched=stage(body);ps=ports(body)
    # Confirm the word-address mapping instead of assuming the stimulus is meaningful.
    need(re.search(r'register_adr\s*=\s*\{?\s*PADDR\s*\[\s*4\s*:\s*2\s*\]',clean(body)),
         'Unexpected UART register address mapping; stop for harness adjustment')
    rs=sorted((DC/'runs').glob('soc-elab-*/result.json'),key=lambda p:p.stat().st_mtime,reverse=True)
    elab=next((p.parent for p in rs if json.loads(p.read_text()).get('status')=='PASS_SOC_ANALYZE_ELABORATE_LINK_ONLY'),None)
    need(elab,'No source manifest');selected=json.loads((elab/'source-selection.json').read_text())
    vcs=shutil.which('vcs');need(vcs,'vcs not in PATH')
    run=Path(tempfile.mkdtemp(prefix='uart-latch-fix-',dir=str(DC/'runs')))
    (run/'apb_uart.v').write_text(patched)
    for name,text in [('reference',body),('candidate',patched)]:
        text,n=re.subn(r'\bmodule\s+[A-Za-z_]\w*\b','module apb_uart_'+name,text,count=1);need(n==1,'UART module mismatch')
        (run/('apb_uart_'+name+'.v')).write_text(text)
    tb=run/'tb_uart_fix.sv';tb.write_text(make_tb(ps))
    sources=[Path(p) for p in selected['source_files'] if Path(p).resolve()!=source.resolve()]
    sources += [run/'apb_uart_reference.v',run/'apb_uart_candidate.v',tb]
    before={str(p):sha(p) for p in sources+[source,run/'apb_uart.v']}
    includes=selected['include_directories']+[str(source.parent)]
    cmd=[vcs,'-full64','-sverilog','-timescale=1ns/1ps','-top','tb_uart_fix',
         *['+incdir+'+s for s in includes],*map(str,sources),'-Mdir='+str(run/'csrc'),'-o',str(run/'simv')]
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    (run/'commands.json').write_text(json.dumps(cmd,indent=2)+'\n')
    print('RUN='+str(run),flush=True);print('UART_PATCH_STAGED; production unchanged; compiling differential test',flush=True)
    with (run/'compile.log').open('w') as log:c=subprocess.run(cmd,cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
    ok=False
    if c.returncode==0:
        with (run/'simulation.log').open('w') as log:p=subprocess.run([str(run/'simv')],cwd=str(run),stdout=log,stderr=subprocess.STDOUT)
        text=(run/'simulation.log').read_text(errors='replace')
        for line in text.splitlines():
            if 'UART_FIX_' in line or 'UART_FAIL' in line or 'Fatal' in line:print(line)
        ok=p.returncode==0 and 'UART_FIX_DIFFERENTIAL_PASS' in text
    else:
        lines=(run/'compile.log').read_text(errors='replace').splitlines()
        for i,s in enumerate(lines):
            if 'Error-' in s:print('\n'.join(lines[i:i+5]));break
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(p)!=h]
    ok=ok and not changed
    status='UART_PATCH_DIFFERENTIAL_PASS_REQUIRES_SOC_REBUILD' if ok else 'FAIL_UART_PATCH_TEST'
    (run/'result.json').write_text(json.dumps({'status':status,'original':str(source),'candidate':str(run/'apb_uart.v'),
      'changed_inputs':changed,'production_modified':False,'soc_rebuilt':False,'formal_equivalence_proven':False,
      'test_scope':'Original vs patched actual UART ports plus valid FIFO-write data, all byte values, FIFO pressure, DLAB, clearing, reset; RX held idle'},indent=2)+'\n')
    print('RESULT='+status)

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,KeyError) as e:raise SystemExit('STOP: '+str(e))
