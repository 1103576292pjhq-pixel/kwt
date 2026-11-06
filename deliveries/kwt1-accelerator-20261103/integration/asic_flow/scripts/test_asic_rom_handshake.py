from pathlib import Path
import hashlib,json,re,subprocess,tempfile

DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
OLD=DC/'runs/asic-suite12-150mhz-1h92bwv4'
ROOT=DC.parent/'e203-integration/kwt-soc'

def need(ok,msg):
    if not ok:
        raise RuntimeError(msg)

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

lines=(OLD/'sources.f').read_text().splitlines()
files=[Path(x.strip()) for x in lines
       if x.strip() and not x.startswith('+')]
files=[p for p in files if p.is_file()]
hits=[p for p in files if re.search(
    r'\bmodule\s+sirv_mrom_top\b',p.read_text(errors='replace'))]
need(len(hits)==1,'Expected exactly one sirv_mrom_top')
source=hits[0]
text=source.read_text()
before={str(p):sha(p) for p in files}

pattern=(
    r'assign\s+rom_icb_rsp_valid\s*=\s*rom_icb_cmd_valid\s*;\s*'
    r'assign\s+rom_icb_cmd_ready\s*=\s*rom_icb_rsp_ready\s*;\s*'
    r'assign\s+rom_icb_rsp_err\s*=\s*~rom_icb_cmd_read\s*;'
)
m=re.search(pattern,text)
need(m is not None,'Unexpected handshake source')

logic='''`ifndef FPGA
reg rom_pending;
reg rom_error;
wire rom_accept;
assign rom_icb_cmd_ready = rst_n & ~rom_pending;
assign rom_accept = rom_icb_cmd_valid & rom_icb_cmd_ready;
assign rom_icb_rsp_valid = rom_pending;
assign rom_icb_rsp_err = rom_error;
always @(posedge clk or negedge rst_n) begin
  if (!rst_n) begin
    rom_pending <= 1'b0;
    rom_error <= 1'b0;
  end else begin
    if (rom_pending && rom_icb_rsp_ready)
      rom_pending <= 1'b0;
    if (rom_accept) begin
      rom_pending <= 1'b1;
      rom_error <= ~rom_icb_cmd_read;
    end
  end
end
`else
'''+m.group(0)+'\n`endif\n'

text=text[:m.start()]+logic+text[m.end():]
text,n=re.subn(
    r'\.CEN\s*\(\s*!rom_icb_cmd_read\s*\)',
    '.CEN (!(rom_accept & rom_icb_cmd_read))',text)
need(n==1,'Expected exactly one ROM CEN connection')

run=Path(tempfile.mkdtemp(
    prefix='asic-rom-handshake-',dir=str(DC/'runs')))
stage=run/'sim'
stage.mkdir()
work=run/'case01'
work.mkdir()
fixed=stage/source.name
fixed.write_text(text)

newlines=[str(fixed) if x.strip()==str(source) else x for x in lines]
need(newlines.count(str(fixed))==1,'Source list replacement failed')
(run/'sources.f').write_text('\n'.join(newlines)+'\n')
(run/'data').symlink_to(OLD/'data',target_is_directory=True)

words=[0x7ffff297,0x00028067]+[0]*1022
(work/'ROM1KX32_verilog.rcf').write_text(
    ''.join(format(x,'032b')+'\n' for x in words))

cmd=json.loads((OLD/'commands.json').read_text())
need(isinstance(cmd,list) and all(isinstance(x,str) for x in cmd),
     'Unexpected compile commands')
need(not any('+define+FPGA' in x for x in cmd),'FPGA define present')
for flag,value in [('-f',run/'sources.f'),('-o',run/'simv')]:
    cmd[cmd.index(flag)+1]=str(value)
cmd=[('-Mdir='+str(run/'csrc')) if x.startswith('-Mdir=') else x
     for x in cmd]

(run/'compile-command.json').write_text(json.dumps(cmd,indent=2))
(run/'original-source-sha256.json').write_text(
    json.dumps(before,indent=2))
receipt={
    'status':'COMPILING',
    'original_rom_interface':str(source),
    'experimental_rom_interface':str(fixed),
    'experimental_sha256':sha(fixed),
    'production_modified':False,
    'power_evaluated':False,
    'full12_passed':False
}

def save():
    (run/'result.json').write_text(json.dumps(receipt,indent=2)+'\n')

def execute(command,cwd,log):
    with log.open('w') as out:
        result=subprocess.run(
            command,cwd=str(cwd),stdout=out,
            stderr=subprocess.STDOUT,timeout=1800)
    data=log.read_text(errors='replace')
    need(result.returncode==0 and
         not re.search(r'Error-|Fatal:|\$fatal',data),
         'Failed; see '+str(log))
    return data

save()
print('RUN='+str(run),flush=True)
try:
    print('COMPILING_EXPERIMENTAL_ASIC_ROM',flush=True)
    execute(cmd,run,run/'compile.log')
    fw=ROOT/'test_env/build-01/real_shared_task'
    sim=[
        str(run/'simv'),'+DUMPWAVE=0','+SIM_TOOL=vcs',
        '+TESTCASE='+str(fw),'+real_data=../data/case1',
        '+real_trace=shared-y.txt','+layer=0','+activity=1'
    ]
    (run/'sim-command.json').write_text(json.dumps(sim,indent=2))
    receipt['status']='RUNNING_TASK1'
    save()
    print('COMPILE_PASS; TASK1_RUNNING',flush=True)
    data=execute(sim,work,work/'run.log')
    need('TEST_PASS' in data,'No TEST_PASS; see '+str(work/'run.log'))
    receipt['status']='TASK1_TEST_PASS_REQUIRES_FULL_AUDIT'
except Exception as e:
    receipt.update(status='STOPPED',error=str(e))
    log=work/'run.log' if (work/'run.log').exists() else run/'compile.log'
    if log.exists():
        entries=log.read_text(errors='replace').splitlines()
        chosen=[x for x in entries
                if re.search(r'Fatal|Error|FAIL|DBG_e203_ifu',x)]
        print('\n'.join(chosen[-8:] if chosen else entries[-8:]))
    print('STOP: '+str(e),flush=True)
finally:
    changed=[p for p,h in before.items()
             if not Path(p).is_file() or sha(Path(p))!=h]
    receipt['original_source_changes']=changed
    if changed:
        receipt['status']='INPUT_CHANGED_REVIEW_REQUIRED'
    save()
    print('RESULT='+receipt['status'])
    print('RUN='+str(run))
