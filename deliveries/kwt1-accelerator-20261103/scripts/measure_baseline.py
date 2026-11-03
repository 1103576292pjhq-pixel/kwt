#!/usr/bin/env python3
"""Measure a normal ICB task sequence without modifying accelerator RTL."""
import argparse
import json
from pathlib import Path
import re
import shutil
import struct
import subprocess
import sys
import tarfile

ROOT=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(ROOT/'scripts'),str(ROOT/'integration/e203/performance_baseline'),str(ROOT/'integration/e203/real12_validation')]
from evaluate_precision import sha256
from real12_audit import audit_result_trace
from performance import analyse_metrics


def save(path,value):path.write_text(json.dumps(value,ensure_ascii=False,indent=2,allow_nan=False)+'\n',encoding='utf-8')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--fixtures',type=Path,default=ROOT/'verification/real12-20261102-02/fixtures')
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    production=[ROOT/line.strip() for line in (ROOT/'rtl/kwt.f').read_text().splitlines() if line.strip() and not line.startswith('+')]
    production+=list((ROOT/'rtl/include').glob('*.vh'))+[ROOT/'rtl/kwt.f']
    tb=ROOT/'tb/interface/tb_icb_perf12.v';support=ROOT/'integration/e203/performance_baseline'
    sources=production+[tb,ROOT/'tb/memory/support/sram_contract_models.v',Path(__file__),
                        ROOT/'model/fixed_numeric.py',ROOT/'model/numeric-contract.json',
                        ROOT/'integration/e203/real12_validation/real12_audit.py',
                        support/'performance.py',support/'run_official.py',support/'README.md']
    before={str(p.relative_to(ROOT)):sha256(p) for p in sources}
    for p in sources:
        dest=out/'source'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,dest)
    report=dict(status='RUNNING',soc_cpu_executed=False,shared_ram_included=False,official_macro_verified=False,
                source_sha256=before,commands=[])
    def run(name,argv,cwd=ROOT,negative=False):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            result=subprocess.run(list(map(str,argv)),cwd=cwd,stdout=log,stderr=subprocess.STDOUT,timeout=1800)
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=result.returncode));save(out/'report.json',report)
        text=(out/(name+'.log')).read_text(errors='replace')
        if (result.returncode!=0)!=negative:raise RuntimeError(name+': '+text[-2500:])
        return text
    try:
        origin=args.fixtures.resolve();manifest=json.loads((origin/'manifest.json').read_text())
        if len(manifest['tasks'])!=12:raise ValueError('Need12 real tasks')
        for name,want in manifest['files_sha256'].items():
            if sha256(origin/name)!=want:raise ValueError('Frozen fixture changed: '+name)
        previous=json.loads((origin.parent/'report.json').read_text())
        for rel in ('model/fixed_numeric.py','model/numeric-contract.json'):
            if before[rel]!=previous['source_sha256'][rel]:raise ValueError('Current numerical contract differs from fixtures')
        shutil.copytree(origin,out/'fixtures');report['fixture_manifest_sha256']=sha256(origin/'manifest.json')
        gold=[];references=[]
        for case in range(1,13):
            gold.append([int(v,16) for v in (origin/('case%d-y.hex'%case)).read_text().splitlines()])
            references.append(struct.unpack('<25344f',(origin/('case%d-ref.f32'%case)).read_bytes()))
        binary=out/'performance.vvp'
        run('compile',['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-s','tb_icb_perf12','-o',binary,
                       '-f','rtl/kwt.f',ROOT/'tb/memory/support/sram_contract_models.v',tb])
        text=run('run',['vvp',binary,'+fixtures=fixtures','+trace=icb-trace.txt','+metrics=metrics.csv'],cwd=out)
        match=re.search(r'^PASS ICB_PERF12 (.*)$',text,re.M)
        if not match:raise ValueError('No performance PASS')
        totals={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',match[1])};report['rtl']=totals
        if totals.get('tasks')!=12 or totals.get('outputs')!=304128 or totals.get('errors')!=0:raise ValueError('Wrong totals')
        report['audit']=audit_result_trace(out/'icb-trace.txt',gold,references)
        report['performance']=analyse_metrics(out/'metrics.csv',12,150.)
        if not report['audit']['all_tasks_within_3_percent'] or report['performance']['total_cycles']!=totals['window_cycles']:
            raise ValueError('Numerical or timing audit failed')
        if sum(t['mmio_requests'] for t in report['performance']['tasks'])!=totals['requests'] or totals['requests']!=totals['responses']:
            raise ValueError('Request totals mismatch')
        bad=run('corrupt-golden',['vvp',binary,'+fixtures=fixtures','+trace=negative-trace.txt',
                                '+metrics=negative-metrics.csv','+task_count=1','+corrupt_first'],cwd=out,negative=True)
        if 'FAIL PERF_GOLDEN task0 index0' not in bad:raise ValueError('Negative golden check missed')
        report['corrupt_golden_caught']=True
        run('software-tests',['python3','-B','-m','unittest','discover','-s','tests','-v'])
        if before!={str(p.relative_to(ROOT)):sha256(p) for p in sources}:raise ValueError('Source changed during measurement')
        package=out/'server-package/kwt-performance-baseline';package.mkdir(parents=True)
        for p in production+[tb]:
            dest=package/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,dest)
        shutil.copytree(out/'fixtures',package/'fixtures')
        for name in ('performance.py','run_official.py','README.md'):shutil.copy2(support/name,package/name)
        shutil.copy2(ROOT/'integration/e203/real12_validation/real12_audit.py',package/'real12_audit.py')
        save(package/'package-sha256.json',{p.relative_to(package).as_posix():sha256(p) for p in package.rglob('*') if p.is_file()})
        archive=out/'kwt-performance-baseline.tar.gz'
        with tarfile.open(archive,'w:gz') as tar:tar.add(package,arcname='kwt-performance-baseline')
        report.update(status='PASS_ACCELERATOR_ICB_PERFORMANCE_BASELINE_CONTRACT',archive=str(archive),
                      archive_sha256=sha256(archive),archive_bytes=archive.stat().st_size,
                      limitations=report['performance']['exclusions'])
        save(out/'report.json',report)
        perf=report['performance']
        lines=['# 不含CPU/共享SRAM的加速器ICB性能基线','',
               '本地SRAM合同模型；12个真实任务304128项Y/flags逐位一致，正常过程errors=0。',
               '总周期%d，按150MHz目标折算吞吐量%.6f任务/秒；不是最终系统性能或150MHz STA通过。'%(perf['total_cycles'],perf['normalized_tasks_per_second']),
               '', '| 层 | 周期 | 核忙碌周期 | 装载总线 | 状态总线 | 输出总线 | ACK总线 | TB间隔 |',
               '| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |']
        lines+=['| %d | %d | %d | %d | %d | %d | %d | %d |'%(t['layer'],t['span_cycles'],t['core_busy_cycles'],
                  t['load_bus_cycles'],t['status_bus_cycles'],t['output_bus_cycles'],t['ack_bus_cycles'],t['tb_gap_cycles']) for t in perf['tasks']]
        lines+=['','互斥的五类总线/TB间隔之和等于总周期；核心忙碌周期与它们重叠，不可相加。',
                '起点首笔TASK请求接受，终点最后完成STATUS响应退休；实际传输/轮询/等待/正确ACK均计入，预读文件和golden比较在窗外。',
                '计数/峰值分母、事件、波形时钟取整及排除项见report.json。服务器官方模型复测尚待用户上传。']
        (out/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
        print(match[0],flush=True)
        print('BASELINE tasks_per_second_at150MHz=%.6f excludesCPU/sharedRAM'%perf['normalized_tasks_per_second'],flush=True)
        print('UPLOAD',archive,flush=True)
    except Exception as error:
        report.update(status='FAIL_PERFORMANCE_BASELINE',error=str(error));save(out/'report.json',report);raise


if __name__=='__main__':main()
