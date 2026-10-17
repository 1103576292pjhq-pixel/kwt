#!/usr/bin/env python3
"""Assemble a lane evidence card; parent and official acceptance remain false."""
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,put,read_json,run_id,sha,utc

BASE='reports/revd_offline/soc/'
NORMAL_RUNS=[
 'soc-full-pm4-20261017T062100Z','soc-layers03-04-20261017T064820Z',
 'soc-layers05-06-20261017T070120Z','soc-layers07-08-20261017T071130Z',
 'soc-layers09-10-20261017T071950Z','soc-layers11-12-20261017T073140Z']
EVIDENCE={
 'twelve_task_suite':'suite-20261017T074534Z_56788626',
 'same_cpu_d2':'soc-d2-20261017T063010Z',
 'same_cpu_d2_comparison':'comparison-20261017T064142Z_6f7686d3',
 'adapter_rtl_mutations':'adapter-mutations-20261017T062633Z_0bc11c0a',
 'real_cpu_correct_return_missing_writes':'cpu-negative-20261017T064658Z_8fcbbd89',
 'public_mmio_nonzero_flags':'positive-flags-20261017T070110Z_0995cbc8',
 'real_cpu_directed_nonzero_flags':'directed-edges-20261017T074550Z_710fe80e'}

def audit_cpu(path):
    report=read_json(path)
    if report['status']!='PASS' or not report.get('source_unchanged'):raise RuntimeError('unsuccessful CPU report '+str(path))
    for relative,digest in report['source_sha256'].items():
        if sha(ROOT/relative)!=digest:raise RuntimeError('current CPU source mismatch '+relative)
    for relative,digest in report['input_sha256'].items():
        if sha(ROOT/relative)!=digest:raise RuntimeError('current CPU input mismatch '+relative)
    for relative,digest in report['artifacts_sha256'].items():
        if sha(path.parent/relative)!=digest:raise RuntimeError('CPU artifact changed '+relative)
    cpu=report['results']['cpu'];record=cpu['command']
    if record['exit_code']!=0 or read_json(path.parent/'cpu.log.command.json')!=record or sha(ROOT/record['log'])!=record['log_sha256']:
        raise RuntimeError('actual CPU command/log mismatch')
    binary=Path(record['argv'][0])
    return {'report':str(path.relative_to(ROOT)),'report_sha256':sha(path),'profile':report['profile'],
      'cases':report['cases'],'task_metrics':cpu['task_metrics'],'metrics':cpu['metrics'],
      'actual_simulator_binary_sha256':sha(binary),'cpu_pid':record['pid'],
      'cpu_exit_code':record['exit_code'],'cpu_seconds':record['seconds'],
      'actual_output_sha256':cpu['output_sha256']}

def main():
    p=argparse.ArgumentParser();p.add_argument('--pm2');p.add_argument('--pm-comparison');
    p.add_argument('--w2-small');p.add_argument('--w2-full');p.add_argument('--w2-edges');p.add_argument('--w2-comparison');p.add_argument('--w2-red');args=p.parse_args()
    normal=[audit_cpu(ROOT/BASE/name/'result.json') for name in NORMAL_RUNS]
    directed=audit_cpu(ROOT/BASE/EVIDENCE['real_cpu_directed_nonzero_flags']/'result.json')
    entries={}
    for kind,name in EVIDENCE.items():
        path=ROOT/BASE/name/'result.json';report=read_json(path)
        if report['status']!='PASS':raise RuntimeError('unsuccessful evidence '+kind)
        entries[kind]={'path':str(path.relative_to(ROOT)),'sha256':sha(path)}
    extras={}
    for kind,name in vars(args).items():
        if not name:continue
        path=ROOT/name;report=read_json(path)
        if report['status'] not in ['PASS','RED_CONFIRMED']:raise RuntimeError('unsuccessful optional evidence '+kind)
        extras[kind]={'path':str(path.relative_to(ROOT)),'sha256':sha(path),'status':report['status']}
        if kind in ['pm2','w2_small','w2_full','w2_edges']:extras[kind]['cpu']=audit_cpu(path)
    out=ROOT/'work/revd_offline_20261017/soc'/('handoff-'+run_id()+'.json')
    put(out,{'status':'LANE_EVIDENCE_READY_FOR_PARENT_REVIEW','checked_utc':utc(),
      'parent_accepted':False,'official_contest_acceptance':False,'current_default_source_sha256':soc.inventory(),
      'normal_pm4_cpu':{'scope':'Six real public E203 boots, each two independently cold-loaded frozen FFN1 tasks. One engineering input, layers01-12; not a continuous full encoder.',
        'boots':6,'tasks':12,'unique_y_results':304128,'unique_flag_results':304128,'runs':normal},
      'real_cpu_directed_edges':{'scope':'Explicit fixed numeric contract edges M3/N16, shifts47 and0, not model or contest samples.',
        'run':directed,'arithmetic_flag_categories':{'neither':40,'overflow_only':25,'saturated_only':23,'both':8},
        'last_result_flags':[5,7],'negative_wrong_overflow_bit_detected':True},
      'evidence':entries,'optional_profiles':extras,
      'rtl_adapter_mutations':{'compiled_and_simulated':3,'scope':['premature Y ownership release','false event capacity','response ready while backpressured'],
        'software_or_CPU_negatives_included_in_count':False},
      'real_cpu_negatives':{'correct_return_zero_without_work':'coverage rejected outputs0/flags0',
        'correct_return_zero_skip_last_write':'coverage rejected outputs47/flags47 despite final POP',
        'wrong_value_golden':'actual first SRAM write mismatch','wrong_overflow_golden':'actual flag SRAM write mismatch'},
      'retained_failure':{'path':BASE+'cpu-negative-20261017T064059Z_f8528eca/result.json',
        'status':'FAIL','reason':'Standalone Icarus negative-run timeout was too tight; only its own marked process group stopped, then fresh Verilator positives/negatives passed. Failed whole run is not counted as PASS.'},
      'package_dependency_recipe':'work/revd_offline_20261017/soc/e203-minimal-package-recipe.json',
      'package_cpu_small_command':'python -B scripts/revd_offline_soc_run.py --stage small --sim verilator --tasks 1',
      'package_cpu_small_estimated_seconds':[70,110],
      'limitations':['CPU36 not run; CPU coverage is12 independent frozen layer tasks for one engineering input.',
        'Cold task window starts at phase before driver descriptor/input/parameter reads; CPU boot and pre-phase global M/N/count header reads are excluded.',
        'No official600/platform acceptance or specified-library MHz/mm2/energy proof.',
        'Instruction counter records IFU fetch handshakes, not architectural retired instructions.',
        'Core windows include real CPU output backpressure; do not compare them as isolated compute latency.'],
      'competition_score':None,'physical_area_mm2':None,'energy_joules':None,
      'handoff_script_sha256':sha(Path(__file__))})
    print('SOC_HANDOFF',out.relative_to(ROOT),flush=True)
if __name__=='__main__':main()
