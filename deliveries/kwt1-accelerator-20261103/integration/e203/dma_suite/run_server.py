#!/usr/bin/env python3
"""Run actual E203 DMA firmware against the passed stream-interface baseline."""
import argparse
import json
from pathlib import Path
import sys
import run_base
from timing_tools import timed_wiring,audit_timing
from throughput_tools import validate_baseline,compare_reports,audit_profile,add_profile_wiring
from server_wiring import prepare_wiring as dma_wiring

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,required=True)
    parser.add_argument('--output',default='verification/dma_soc_01')
    parser.add_argument('--baseline',default='verification/throughput_icb_02/report.json')
    args,extra=parser.parse_known_args()
    root=args.root.resolve();baseline_path=(root/args.baseline).resolve()
    baseline=json.loads(baseline_path.read_text(encoding='utf-8'))
    baseline_digest=run_base.sha(baseline_path)
    validate_baseline(baseline,root)
    cpu_audit=run_base.audit_cpu
    def prepared(soc,tb):
        soc,tb=dma_wiring(soc,tb)
        tb=add_profile_wiring(tb)
        return soc,tb.replace('u_e203_soc_top.sysmem_icb_','u_e203_soc_top.kwt_dma_shared_')
    def audited(text):
        result=cpu_audit(text);timing=audit_timing(text)
        result['load_to_writeback_timing']=timing
        result['driver_profile']=audit_profile(text,timing)
        return result
    run_base.prepare_wiring=prepared;run_base.audit_cpu=audited
    run_base.__file__=str(Path(__file__).resolve())
    sys.argv=[sys.argv[0],'--root',str(root),'--output',args.output,*extra]
    code=run_base.main()
    if code:return code
    out=root/args.output;report=json.loads((out/'report.json').read_text(encoding='utf-8'))
    report['timing']=report['cpu']['load_to_writeback_timing']
    report['driver_profile']=report['cpu']['driver_profile']
    try:
        # Reject changed sources/data or different timing mode, even if results pass.
        validate_baseline(baseline,root)
        if run_base.sha(baseline_path)!=baseline_digest:raise ValueError('Baseline report changed during candidate run')
        comparison=compare_reports(baseline,report)
    except Exception as error:
        report.update(status='FAIL_THROUGHPUT_COMPARISON',error=str(error));run_base.save(out/'report.json',report)
        print('STOP comparison:',error,flush=True);return 1
    report.update(status='PASS_E203_DMA_SOC',comparison=comparison,baseline_report=str(baseline_path),
                  baseline_report_sha256=baseline_digest,
                  timing_scope=baseline['timing_scope'])
    report['limitations']=[x for x in report['limitations'] if 'Initialization and software comparisons' not in x]
    report['limitations']+=['Single task cold-start, not sustained throughput; 150MHz is target normalization only',
                           'DMA performs operand and result transfers; CPU poison initialization, configuration and golden checks retained']
    run_base.save(out/'report.json',report)
    print('PASS E203_DMA_SOC correctness=PASS cycles=%.0f baseline=%.0f speedup=%.6f cycle_reduction_percent=%.4f'%(
        comparison['candidate_cycles'],comparison['baseline_cycles'],comparison['throughput_speedup'],comparison['cycle_reduction_percent']),flush=True)
    print('PERFORMANCE', 'IMPROVED' if comparison['throughput_improved'] else 'NOT_IMPROVED',flush=True)
    print('TARGET_150MHZ latency_ms=%.6f inverse_latency_tasks_per_second=%.6f STA_pending=1'%(
        report['timing']['target_150mhz_latency_ms'],report['timing']['target_150mhz_tasks_per_second']),flush=True)
    print('DRIVER_PHASES',json.dumps(report['driver_profile']),flush=True)
    return 0

if __name__=='__main__':raise SystemExit(main())
