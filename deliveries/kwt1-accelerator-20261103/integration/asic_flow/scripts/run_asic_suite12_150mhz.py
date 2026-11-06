#!/usr/bin/env python3
"""One actual E203 task on frozen ASIC RTL plus existing instrumented wrapper.
Uses isolated nominal-150MHz clock and passive observations; records actual timing.
Not gate-level equivalence or final 150MHz power acceptance.
"""
import gzip,hashlib,importlib.util,json,re,shutil,subprocess,sys,tempfile
sys.dont_write_bytecode=True
ACTIVE_RUN=None
from pathlib import Path
DC=Path('/storage1/2026contest/server2/s2_21usr/Desktop/dc')
ROOT=DC.parent/'e203-integration/kwt-soc';ENV=ROOT/'test_env'
SRAM=Path('/storage1/admin_public_dir/SRAM_Lib_2025')
def need(v,s):
    if not v:raise ValueError(s)
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def clean(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
def modules(s):return re.findall(r'\bmodule\s+(\w+)',clean(s))
def latest(pattern,status):
    for p in sorted((DC/'runs').glob(pattern),key=lambda p:p.stat().st_mtime,reverse=True):
        if json.loads(p.read_text()).get('status')==status:return p.parent
    raise ValueError('No verified '+pattern)
def adapt_tb(text):
    # Locate the entire old initialization process, including debug prints, by lexical begin/end.
    masked=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m.group()),text,flags=re.S)
    anchors=list(re.finditer(r'\$readmemh\s*\([^;]*\bitcm_mem\s*\)\s*;',text))
    need(len(anchors)==1,'Expected one ITCM readmemh')
    pos=anchors[0].start()
    starts=list(re.finditer(r'\binitial\s+begin\b',masked[:pos]))
    need(starts,'ITCM initial block missing');start=starts[-1].start();depth=0;end=None
    for token in re.finditer(r'\bbegin\b|\bend\b',masked[start:]):
        depth+=1 if token.group()=='begin' else -1
        if depth==0:end=start+token.end();break
    need(end and end>pos,'Unable to delimit ITCM initialization')
    old=text[start:end];need('mem_r' in old,'Old ITCM array initialization changed')
    path='tb_top.u_e203_soc_top.u_e203_subsys_top.u_e203_subsys_main.u_e203_cpu_top.u_e203_srams.u_e203_itcm_ram.u_sram_wrap_32KX64'
    replacement='''`define KWT_ITCM_ASIC_PATH %s
`include "itcm_asic_preload.vh"
%s
 for(i=0;i<262144;i=i+1)itcm_mem[i]=0;
 %s
 kwt_preload_asic_itcm;
 $display("ASIC_ITCM_FIRMWARE_LOADED");
end
'''%(path,text[start:pos],anchors[0].group())
    result=text[:start]+replacement+text[end:]
    need(not re.search(r'`ITCM\s*\.\s*mem_r',result),'Other old FPGA ITCM accesses remain')
    return result
def run_cmd(cmd,cwd,path,timeout):
    with path.open('w') as log:p=subprocess.run(list(map(str,cmd)),cwd=str(cwd),stdout=log,stderr=subprocess.STDOUT,timeout=timeout)
    if p.returncode:
        lines=path.read_text(errors='replace').splitlines()
        for i,s in enumerate(lines):
            if re.search(r'Error-|Fatal|FAIL|fatal',s):print('\n'.join(lines[i:i+5]));break
        raise ValueError('Command failed; see '+str(path))
    return path.read_text(errors='replace')
def adapt_clock(s):
    s,n=re.subn(r'#\s*2(?:\.0+)?\s+(clk\s*(?:<=|=)\s*~\s*clk\s*;)',r'#3.333333 \1',s)
    need(n==1,'Expected exactly one #2 main-clock generator; no source changed')
    s,n=re.subn(r'`timescale\s+1ns\s*/\s*1ps', '`timescale 1ns/1fs',s)
    if not n:s='`timescale 1ns/1fs\n'+s
    return s
def adapt_observers(s):
    s=s.replace('`timescale 1ns/1ps','`timescale 1ns/1fs')
    rules={
      'now_ps-last_host_ps!=host_period_ps':'((now_ps-last_host_ps-host_period_ps>0.01)||(host_period_ps-now_ps+last_host_ps>0.01))',
      '$realtime*1000.0-last_cpu_ps!=cpu_period_ps':'(($realtime*1000.0-last_cpu_ps-cpu_period_ps>0.01)||(cpu_period_ps-$realtime*1000.0+last_cpu_ps>0.01))',
      'host_period_ps=now_ps-last_host_ps;':'host_period_ps=6666.666;',
      'cpu_period_ps=$realtime*1000.0-last_cpu_ps;':'cpu_period_ps=6666.666;'}
    for a,b in rules.items():
        need(s.count(a)==1,'Observer format changed: '+a);s=s.replace(a,b)
    # Preserve fractions in timing/profile output; original arithmetic/count checks remain.
    s=s.replace('%.0f','%.9f').replace('%.6f','%.9f')
    # Check measured clock against target from the second observed rising edge onward.
    s=s.replace('if(last_host_ps>0)begin','if(last_host_ps>0)begin\n if(now_ps-last_host_ps<6666.656 || now_ps-last_host_ps>6666.676)$fatal(1,"Wrong 150MHz host clock");')
    s=s.replace('if(last_cpu_ps>0)begin','if(last_cpu_ps>0)begin\n if($realtime*1000.0-last_cpu_ps<6666.656 || $realtime*1000.0-last_cpu_ps>6666.676)$fatal(1,"Wrong 150MHz CPU clock");')
    return s

def observation(text):
    candidate=latest('soc-task-candidate-*/result.json','TASK_MODE_CANDIDATE_REPORTS_READY_REVIEW_REQUIRED')
    files=[Path(p) for p in json.loads((candidate/'source-selection.json').read_text())['source_files']]
    cpu='tb_top.u_e203_soc_top.u_e203_subsys_top.u_e203_subsys_main.u_e203_cpu_top'
    # Discover child instance names from the frozen sources instead of guessing paths.
    blocks={}
    for p in files:
        for m in re.finditer(r'\bmodule\s+(\w+)\b(.*?)\bendmodule\b',clean(p.read_text(errors='replace')),re.S):
            blocks[m.group(1)]=m.group(2)
    queue=[('e203_cpu',cpu+'.u_e203_cpu',0)]; groups=[]
    wanted={'e203_core','e203_ifu','e203_biu'}
    while queue:
        parent,parent_path,depth=queue.pop(0)
        if depth>=3:continue
        body=blocks.get(parent,'')
        for child in sorted(wanted):
            pattern=r'\b'+child+r'\s+(?:#\s*\(.*?\)\s*)?(\w+)\s*\('
            for match in re.finditer(pattern,body,re.S):
                path=parent_path+'.'+match.group(1)
                tag=child[len('e203_'):].upper()
                groups.append((tag,child,path));queue.append((child,path,depth+1))
    need(any(m=='e203_ifu' for _,m,_ in groups),'IFU hierarchy not found')
    groups=[g for g in groups if g[1] in {'e203_ifu','e203_biu'}]
    code=[];receipt=[]
    for idx,(tag,module,path) in enumerate(groups):
        bodies=[]
        for p in files:
            body=clean(p.read_text(errors='replace'))
            m=re.search(r'\bmodule\s+'+module+r'\b(.*?)\bendmodule\b',body,re.S)
            if m:bodies.append((p,m.group(1)))
        need(len(bodies)==1,'Cannot uniquely find '+module)
        p,body=bodies[0]
        names=re.findall(r'\b(?:input|output)\s+(?:(?:wire|reg|signed)\s+)*(?:\[[^\]]+\]\s*)?(\w+)\s*[,;)]',body)
        selected=sorted(set(n for n in names if n in {'clk','rst_n','pc_rtvec'} or ((tag=='IFU' or 'ifu' in n or 'rom' in n) and re.search(r'icb.*(?:valid|ready|addr|rdata|err)',n))))
        need(selected,'No observable ports for '+module)
        fmt='DBG_'+tag+' t=%0t '+' '.join(n+'=%h' for n in selected)
        args='$time, '+', '.join(path+'.'+n for n in selected)
        v='kwt_obs_'+str(idx)
        code+=['string '+v+'[0:2]; integer '+v+'_n=0; integer '+v+'_j;',
          'always @(negedge clk) begin '+v+'['+v+'_n%3]=$sformatf("'+fmt+'", '+args+'); '+v+'_n='+v+'_n+1; end',
          'final begin for('+v+'_j=('+v+'_n>3 ? '+v+'_n-3 : 0); '+v+'_j<'+v+'_n; '+v+'_j='+v+'_j+1) $display("%s",'+v+'['+v+'_j%3]);',
          '$display("'+fmt.replace(' t=','_FINAL t=')+'", '+args+'); end']
        receipt.append({'group':tag,'source':str(p),'instance':path,'ports':selected})
    i=text.rfind('endmodule');need(i>=0,'Missing testbench end')
    print('OBSERVATION_GROUPS='+','.join(x['group']+':'+str(len(x['ports'])) for x in receipt),flush=True)
    return text[:i]+'\n'+'\n'.join(code)+'\n'+text[i:]

def main():
    global ACTIVE_RUN
    candidate=latest('soc-task-candidate-*/result.json','TASK_MODE_CANDIDATE_REPORTS_READY_REVIEW_REQUIRED')
    preload=latest('asic-itcm-preload-*/result.json','ASIC_ITCM_PRELOAD_PASS_REQUIRES_TASK_INTEGRATION')
    power=latest('soc-power-*/result.json','POWER_NETLIST_READY_ACTIVITY_REQUIRED')
    selected=json.loads((candidate/'source-selection.json').read_text())
    prec=json.loads((preload/'result.json').read_text());need(Path(prec['candidate'])==candidate,'Preloader belongs to a different candidate')
    need(Path(json.loads((power/'result.json').read_text())['candidate'])==candidate,'Power preparation belongs to a different candidate')
    before=json.loads((candidate/'input-sha256.json').read_text())
    before.update(json.loads((preload/'input-sha256.json').read_text()))
    for p,h in before.items():need(Path(p).is_file() and sha(p)==h,'Frozen input changed: '+p)
    candidates=json.loads((power/'model-candidates.json').read_text())
    std=[Path(p) for p in candidates if Path(p).name=='scc40nll_vhsc40_hvt.v']
    need(std,'Normal HVT simulation model missing');need(len({sha(p) for p in std})==1,'HVT model copies differ; selection needs review')
    std=std[0]
    vcs=shutil.which('vcs');need(vcs,'vcs not in PATH')
    sys.path.insert(0,str(ENV));spec=importlib.util.spec_from_file_location('asic_pilot_original_suite',ENV/'run_suite.py')
    suite=importlib.util.module_from_spec(spec);spec.loader.exec_module(suite)
    # Retain original fixture/firmware identity checks before generating any task data.
    suite.check_sources(ENV,json.loads((ENV/'package-sha256.json').read_text()))
    build=json.loads((ENV/'build-01/build-report.json').read_text());suite.check_sources(ENV,build['sources'])
    firmware=ENV/'build-01/real_shared_task.verilog';need(sha(firmware)==build['image_sha256']==prec['firmware_sha256'],'Firmware mismatch')
    run=Path(tempfile.mkdtemp(prefix='asic-suite12-150mhz-',dir=str(DC/'runs')))
    ACTIVE_RUN=run
    print('RUN='+str(run),flush=True)
    work=run/'case01';work.mkdir();stage=run/'sim';stage.mkdir()
    (run/'result.json').write_text(json.dumps({'status':'RUNNING_ASIC_ACTIVITY_PILOT','candidate':str(candidate)},indent=2)+'\n')
    shutil.copyfile(preload/'itcm_asic_preload.vh',stage/'itcm_asic_preload.vh')
    tb=stage/'tb_top.v';tb.write_text(observation(adapt_clock(adapt_tb((ENV/'tb/tb_top.v').read_text()))))
    loader150=stage/'real_loader_150.v';loader150.write_text(adapt_observers((ENV/'real_loader.v').read_text()))
    metrics150=stage/'suite_metrics_150.v';metrics150.write_text((ENV/'suite_metrics.v').read_text().replace('`timescale 1ns/1ps','`timescale 1ns/1fs'))
    sources=[Path(p) for p in selected['source_files']];seen={}
    for p in sources:
        for n in modules(p.read_text()):need(n not in seen,'Duplicate candidate module: '+n);seen[n]=str(p)
    # Match the production runner's explicit simulation inputs. Recursive discovery
    # can pick historical support copies before the current combined real_loader.v.
    chosen=[ENV/'platform/kwt_real_soc_top.v',loader150,metrics150]
    for p in chosen:
        need(p.is_file(),'Missing production simulation input: '+str(p))
        names=modules(p.read_text())
        need(names,'No modules in simulation input: '+str(p))
        for n in names:
            need(n not in seen,'Duplicate selected module '+n+' in '+str(p)+'; already in '+seen.get(n,''))
            seen[n]=str(p)
    need('kwt_real_soc_top' in seen,'Instrumented SoC wrapper missing')
    need('kwt_suite_metrics' in seen,'Task-window activity monitor missing')
    sources+=chosen+[tb,std]
    need('tb_top' not in seen,'Unexpected additional testbench definition')
    model_files=[]
    for part in ['RAMSP1024X16','RAMSP128X16','RAMSP4096X16']:
        model_files.append(SRAM/part/'verilog'/(part+'.v'))
    rom=ROOT/'e203/mem_gen/ROM1KX32/verilog/ROM1KX32.v';model_files.append(rom)
    sources+=model_files
    # The ROM model reads its compiler-supplied initialization image relative to simulator cwd.
    rom_text=clean(rom.read_text())
    rom_names=sorted(set(re.findall(r'\$readmem[bh]\s*\(\s*"([^"]+)"',rom_text)))
    rom_init=[]
    for name in rom_names:
        need(Path(name).name==name,'Unexpected ROM relative path: '+name)
        matches=list((ROOT/'e203/mem_gen/ROM1KX32').rglob(name))
        need(matches and len({sha(p) for p in matches})==1,'Missing/ambiguous ROM initialization '+name)
        shutil.copyfile(matches[0],work/name);rom_init.append(matches[0]);before[str(work/name)]=sha(work/name)
    incs=[Path(s) for s in selected['include_directories']]+[ENV,ENV/'tb',stage,std.parent]
    for p in chosen:
        if p.parent not in incs:incs.append(p.parent)
    (run/'sources.f').write_text('\n'.join(['+incdir+'+str(p) for p in incs]+list(map(str,sources)))+'\n')
    fixtures=ROOT/'real12_verify_01/kwt-real12-validation/fixtures'
    tasks=suite.prepare_suite(fixtures,run/'data',json.loads((ENV/'suite-identity.json').read_text()))
    need(len(tasks)==12,'Expected 12 task fixtures')
    before.update({str(p):sha(p) for p in sources+rom_init+[firmware,ENV/'tb/tb_top.v',ENV/'real_loader.v',ENV/'suite_metrics.v',stage/'itcm_asic_preload.vh']})
    before.update({str(p):sha(p) for p in ENV.glob('*.py')})
    before.update({str(p):sha(p) for p in fixtures.iterdir() if p.is_file()})
    (run/'input-sha256.json').write_text(json.dumps(before,indent=2)+'\n')
    cmd=[vcs,'-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all','+define+ARM_UD_MODEL','+notimingcheck',
         '-top','tb_top','-f',run/'sources.f','-Mdir='+str(run/'csrc'),'-o',run/'simv']
    (run/'commands.json').write_text(json.dumps([str(x) for x in cmd],indent=2)+'\n')
    (run/'README.txt').write_text('ASIC RTL task-integration pilot, not mapped equivalence or final power.\n'
      'No FPGA define; frozen candidate hardware and verified ITCM preload; official SRAM/ROM and HVT model.\n'
      'ASIC candidate, 150MHz nominal TB (1fs grid, +0.1ppm), passive timing precision adaptation; exact timestamps retained.\n'
      'ARM_UD_MODEL and notimingcheck select functional simulation; no SDF timing claim.\n'
      'Host loader/golden-check preparation is outside the measured loading-to-writeback window as in original suite.\n'
      'Waveform mapping/coverage and SRAM power model checks remain required.\n')
    print('COMPILING_ASIC_TASK no_FPGA=1 functional_models=1',flush=True)
    compile_log=run_cmd(cmd,run,run/'compile.log',14400)
    need('Warning-[IPDW]' not in compile_log and 'Warning-[PCWM' not in compile_log,'Port-width warnings; inspect compile.log')
    print('ASIC_COMPILE_PASS; TASKS=12 NOMINAL_MHZ=150',flush=True)
    completed=[]
    for d in tasks:
        case=d['case'];work=run/('case%02d'%case);work.mkdir(exist_ok=True)
        for name in rom_names:
            if case!=1:shutil.copyfile(run/'case01'/name,work/name)
        print('TASK_START %d/12'%case,flush=True)
        log=run_cmd([run/'simv','+DUMPWAVE=0','+SIM_TOOL=vcs','+TESTCASE='+str(firmware.with_suffix('')),
          '+real_data=../data/case%d'%case,'+real_trace=shared-y.txt','+layer='+str(d['hardware_layer']),'+activity=1'],work,work/'run.log',14400)
        try:result=suite.audit(log,d['gold'],fixtures/('case%d-ref.f32'%case),work/'shared-y.txt')
        except Exception:
            for line in log.splitlines():
                if line.startswith('DBG') or any(x in line for x in ['Fatal:', 'Error:', 'Error-', 'ROM_INIT', 'WARNING']):print(line)
            print('FAILED_TASK_LOG='+str(work/'run.log'));raise
        need(abs(result['timing']['period_ps']-6666.666)<0.01,'Unexpected ASIC task frequency')
        vcd=work/'activity.vcd';need(vcd.is_file() and vcd.stat().st_size>0,'Missing task-window VCD')
        print('TASK_VERIFIED %d/12; COMPRESSING_VCD'%case,flush=True)
        with vcd.open('rb') as src,gzip.open(work/'activity.vcd.gz','wb',compresslevel=1) as dst:shutil.copyfileobj(src,dst)
        need((work/'activity.vcd.gz').stat().st_size>0,'Empty compressed VCD');vcd.unlink()
        result.update(case=case,layer=d['hardware_layer'],sample=d['sample'],activity=str(work/'activity.vcd.gz'),vcd_sha256=sha(work/'activity.vcd.gz'))
        completed.append(result)
        (work/'report.json').write_text(json.dumps(result,indent=2)+'\n')
        receipt={'status':'RUNNING_ASIC_150MHZ_SUITE','candidate':str(candidate),'tasks':completed,'firmware_sha256':sha(firmware),
          'nominal_frequency_mhz':150,'actual_frequency_mhz':1000000/6666.666,'clock_quantization_ppm':0.10000001,
          'full12_passed':False,'mapped_equivalence_proven':False,'power_evaluated':False}
        (run/'result.json').write_text(json.dumps(receipt,indent=2)+'\n')
        print('TASK_PASS %d/12 cycles=%.6f NRMSE=%.8f%%'%(case,result['timing']['cycles'],result['correctness']['nrmse_percent']),flush=True)
    changed=[p for p,h in before.items() if not Path(p).is_file() or sha(p)!=h];need(not changed,'Inputs changed during simulation')
    receipt.update(status='PASS_ASIC_RTL_SUITE12_NOMINAL_150MHZ',full12_passed=True,
      total_cycles=sum(x['timing']['cycles'] for x in completed),total_elapsed_ps=sum(x['timing']['elapsed_ps'] for x in completed),
      outputs=304128,bit_mismatches=0,max_nrmse_percent=max(x['correctness']['nrmse_percent'] for x in completed))
    receipt['simulated_tasks_per_second']=12e12/receipt['total_elapsed_ps']
    (run/'result.json').write_text(json.dumps(receipt,indent=2)+'\n')
    (run/'report.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('RESULT='+receipt['status']);print('REPORT='+str(run/'report.json'))

if __name__=='__main__':
    try:
        rom=ROOT/'e203/mem_gen/ROM1KX32/verilog/ROM1KX32.v'
        hits=[l.strip() for l in rom.read_text(errors='replace').splitlines() if re.search(r'readmem|init_file|INIT_FILE',l)]
        print('ROM_INIT_HINTS='+str(hits[:8]),flush=True)
        main()
    except Exception as e:
        if ACTIVE_RUN:
            p=ACTIVE_RUN/'result.json'
            old=json.loads(p.read_text()) if p.exists() else {}
            old.update(status='ASIC_SUITE_STOPPED',error=str(e));p.write_text(json.dumps(old,indent=2)+'\n')
        raise SystemExit('STOP: '+str(e))
