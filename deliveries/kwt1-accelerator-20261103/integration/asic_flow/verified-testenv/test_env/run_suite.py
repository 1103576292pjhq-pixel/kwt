"""Compile once, run 12 cold tasks; sum only loading-to-writeback windows."""
import argparse,csv,gzip,json,re,shutil,subprocess,time
from pathlib import Path
from real_tools import sha,save,audit_trace
from suite_tools import prepare_suite
from server_wiring import prepare_wiring
from throughput_tools import add_profile_wiring,audit_profile
from timing_tools import audit_timing
from prepare_soc import convert
from rtl_overlay import prepare_overlay
from run_base import audit_cpu,check_sources

HERE=Path(__file__).resolve().parent

def wire(source,tb):
    return (HERE/'platform/kwt_real_soc_top.v').read_text(),tb


def audit(log,gold,reference,trace):
    cpu=audit_cpu(log);timing=audit_timing(log);profile=audit_profile(log,timing)
    if log.count('CLEAR_SHARED_PASS words=48320 zero_readbacks=48320 ')!=1:raise ValueError('Missing full scrub')
    if log.count('CLEAR_CACHE_PASS invalidation=1 internal_sram_physical_zero=0')!=1:raise ValueError('Missing cache invalidation check')
    lines=re.findall(r'^SUITE_METRICS (.+)$',log,re.M)
    if len(lines)!=1:raise ValueError('Missing/duplicate counters')
    metrics={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',lines[0])}
    if metrics['host_reads']!=0 or metrics['host_writes']!=22976 or metrics['dma_writes']!=25344:raise ValueError('Incomplete bus counts')
    if metrics['read_bytes']!=4*(metrics['cpu_reads']+metrics['dma_reads']):raise ValueError('Read byte ledger')
    if metrics['write_bytes']!=4*(metrics['cpu_writes']+metrics['dma_writes']):raise ValueError('Write byte ledger')
    clear=re.findall(r'CLEAR_SHARED_PASS words=48320 zero_readbacks=48320 elapsed_ns=([0-9.]+)',log)
    return dict(cpu=cpu,timing=timing,profile=profile,bus=metrics,clear_elapsed_ns=float(clear[0]),
                correctness=audit_trace(trace,gold,reference))

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--root',type=Path,required=True)
    p.add_argument('--output',default='verification/dma_suite12_01')
    p.add_argument('--fixtures',default='real12_verify_01/kwt-real12-validation/fixtures')
    p.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    p.add_argument('--activity',choices=['all','none'],default='all')
    p.add_argument('--tasks',type=int,choices=[3,12],default=12)
    a=p.parse_args();root=a.root.resolve();out=(root/a.output).resolve();fixtures=(root/a.fixtures).resolve()
    if root.name!='kwt-soc' or root not in out.parents or out.exists():p.error('Use existing kwt-soc and NEW output directory')
    manifest=json.loads((HERE/'package-sha256.json').read_text());check_sources(HERE,manifest)
    hardware=json.loads((HERE/'production-sha256.json').read_text());check_sources(root,hardware)
    build=json.loads((HERE/'build-01/build-report.json').read_text());check_sources(HERE,build['sources'])
    image=HERE/'build-01/real_shared_task.verilog'
    if sha(image)!=build['image_sha256']:raise ValueError('Firmware changed')
    out.mkdir(parents=True)
    report=dict(status='RUNNING',tasks=[],expected_tasks=a.tasks,activity=a.activity,firmware_sha256=sha(image),
        dataset='Existing validation fixtures covering model layers; NOT organizer frozen evaluation selection',
        reset_policy='Separate simulator invocation per task, same executable and firmware; explicit shared scrub + internal metadata reset',
        frequency_sta_verified=False,internal_sram_physical_zero=False,
        limitations=['RTL activity requires synthesis mapping/coverage and SRAM power modeling; not a power report',
                    'Shared ICB counts are not physical SRAM macro access counts',
                    'CPU/DMA stall spans may overlap; do not add them as exclusive phase times'])
    save(out/'report.json',report)
    def run(cmd,cwd,path):
        with path.open('w') as log:
            proc=subprocess.run(list(map(str,cmd)),cwd=cwd,stdout=log,stderr=subprocess.STDOUT,timeout=14400)
        if proc.returncode:raise RuntimeError('Command failed: '+str(path))
        return path.read_text(errors='replace')
    try:
        data=prepare_suite(fixtures,out/'data',json.loads((HERE/'suite-identity.json').read_text()))[:a.tasks]
        before={str(path):sha(path) for path in fixtures.glob('*') if path.is_file()}
        top=root/'kwt_dma_soc_top.v';tb=root/'test_env/tb/tb_top.v'
        base=HERE/'platform/base-soc.f';extra=HERE/'platform/base-shared.f'
        for path in [top,tb,base,extra]:before[str(path)]=sha(path)
        overlay=prepare_overlay(root,HERE,base,extra,out);report['rtl_overlay']=overlay
        soc,tb_text=wire(top.read_text(),tb.read_text())
        (out/'kwt_real_soc_top.v').write_text(soc);(out/'tb_real.v').write_text(tb_text)
        (out/'kwt_dma_soc_top.v').write_text(top.read_text())
        (out/'soc.f').write_text('\n'.join(overlay['base_lines'])+'\n')
        (out/'shared.f').write_text('\n'.join(overlay['extra_lines'])+'\n')
        models=[a.sram_root/part/'verilog'/name for part in ['RAMSP1024X16','RAMSP128X16'] for name in [part+'_rtl.v',part+'.v']]
        for path in models:before[str(path)]=sha(path)
        print('COMPILING_DMA_SUITE tasks=%d activity=%s'%(a.tasks,a.activity),flush=True)
        cmd=['vcs','-full64','-sverilog','-timescale=1ns/1ps','-debug_access+all','+define+FPGA+ARM_UD_MODEL',
             '+incdir+'+str(root/'accelerator/rtl/include')+'+e203/core+e203/perips+e203/perips/apb_i2c',
             '-top','tb_top','-f',out/'soc.f','-f',out/'shared.f',*models,out/'kwt_real_soc_top.v',HERE/'real_loader.v',HERE/'suite_metrics.v',
             '-Mdir='+str(out/'csrc'),'-o',out/'simv']
        compile_log=run(cmd,root,out/'compile.log')
        if 'Warning-[IPDW]' in compile_log or 'Warning-[PCWM' in compile_log:raise ValueError('Declaration/port width warnings; inspect compile.log')
        print('COMPILE_PASS',flush=True)
        for d in data:
            case=d['case'];work=out/('case%02d'%case);work.mkdir()
            print('TASK_START %d/%d layer=%d'%(case,a.tasks,d['hardware_layer']),flush=True)
            log=run([out/'simv','+DUMPWAVE=0','+SIM_TOOL=vcs','+TESTCASE='+str(image.with_suffix('')),
                '+real_data=../data/case%d'%case,'+real_trace=shared-y.txt','+layer='+str(d['hardware_layer']),
                '+activity='+str(int(a.activity=='all'))],work,work/'run.log')
            result=audit(log,d['gold'],fixtures/('case%d-ref.f32'%case),work/'shared-y.txt')
            result.update(case=case,layer=d['hardware_layer'],sample=d['sample'])
            if a.activity=='all':
                vcd=work/'activity.vcd'
                if not vcd.exists() or vcd.stat().st_size==0:raise ValueError('Missing VCD')
                with vcd.open('rb') as src,gzip.open(str(vcd)+'.gz','wb',compresslevel=1) as dst:shutil.copyfileobj(src,dst)
                result['activity']=dict(file='case%02d/activity.vcd.gz'%case,uncompressed_bytes=vcd.stat().st_size,
                    sha256=sha(Path(str(vcd)+'.gz')),note='dumpvars begins at measurement arm; dumpoff 1ps after final write response; use TIMING_WINDOW timestamps for exact power crop')
                vcd.unlink() # Only this newly generated VCD, after successful compression.
            report['tasks'].append(result);save(work/'report.json',result);save(out/'report.json',report)
            print('TASK_PASS %d/%d cycles=%.0f outputs=25344 NRMSE=%.8f%%'%(case,a.tasks,result['timing']['cycles'],result['correctness']['nrmse_percent']),flush=True)
        for path,want in before.items():
            if sha(Path(path))!=want:raise ValueError('Input changed during run: '+path)
        check_sources(HERE,manifest)
        check_sources(root,hardware)
        for path,want in overlay['original_filelist_sha256'].items():
            if sha(Path(path))!=want:raise ValueError('Filelist changed')
        periods={x['timing']['period_ps'] for x in report['tasks']}
        if len(periods)!=1:raise ValueError('Different task clocks')
        total=sum(x['timing']['cycles'] for x in report['tasks'])
        report.update(status='PASS_E203_DMA_SUITE_%d'%a.tasks,total_cycles=total,
            target_150mhz_tasks_per_second=a.tasks*150000000/total,target_150mhz_mean_latency_ms=total/a.tasks/150000,
            target_150mhz_mac_per_second=a.tasks*1622016*150000000/total,
            simulated_total_seconds=sum(x['timing']['elapsed_ps'] for x in report['tasks'])/1e12,
            outputs=a.tasks*25344,bit_mismatches=0,source_input_sha256=before)
        report['simulated_tasks_per_second']=a.tasks/report['simulated_total_seconds']
        save(out/'report.json',report)
        with (out/'metrics.csv').open('w',newline='') as f:
            writer=csv.writer(f);writer.writerow(['case','model_layer','cycles','load_cycles','nrmse_percent','cpu_shared_reads','cpu_shared_writes','dma_reads','dma_writes'])
            for x in report['tasks']:writer.writerow([x['case'],x['layer']+1,x['timing']['cycles'],x['timing']['load_cycles'],x['correctness']['nrmse_percent'],*[x['bus'][k] for k in ['cpu_reads','cpu_writes','dma_reads','dma_writes']]])
        print('%s total_cycles=%.0f target150_tasks_s=%.6f STA_PENDING=1'%(report['status'],total,report['target_150mhz_tasks_per_second']),flush=True)
        print('REPORT',out/'report.json',flush=True)
    except Exception as e:
        report.update(status='FAIL_E203_DMA_SUITE',error=str(e));save(out/'report.json',report)
        print('STOP:',e,'REPORT',out/'report.json',flush=True);return 1
    return 0

if __name__=='__main__':raise SystemExit(main())
