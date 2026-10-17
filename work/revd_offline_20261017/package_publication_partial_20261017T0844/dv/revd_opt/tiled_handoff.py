"""Author handoff: verify existing W1 evidence bytes, never self-accept RTL."""
import json
from pathlib import Path
import sys
from tiled_runner import ROOT
from scripts.revd_offline_common import put,sha,utc,run_id
from scripts.revd_offline_tiled_gate import check_suite,check_protocol,check_numeric

RUNS=['w1-production-pm4-l1-001','w1-production-pm4-l2-001','w1-full36-pm4-l1-001','w1-repeat-pm4-l1-001',
      'w1-small-pm2-l1-001','w1-small-pm2-l2-001','w1-small-pm4-l2-002','w1-protocol-pm4-final-001','w1-protocol-pm2-001','w1-numeric-001']

def verify_receipt(path):
    r=json.loads(path.read_text());folder=path.parent
    for p,digest in r['source_sha256'].items():
        if sha(ROOT/p)!=digest or sha(folder/'source_snapshot'/p)!=digest:raise ValueError('stale/missing source '+str(path)+':'+p)
    for key in ('input_sha256','output_sha256'):
        for p,digest in r[key].items():
            if sha(folder/p)!=digest:raise ValueError('changed input/output '+str(folder/p))
    if sha(folder/'config.json')!=r['config_sha256'] or sha(folder/'sim.vvp')!=r['binary_sha256']:raise ValueError('changed config/binary')
    if len(r['commands'])!=2 or r['commands'][0]['exit_code']!=0:raise ValueError('not a compiled RTL run')
    for c in r['commands']:
        if c['pid']<1 or c['exit_code'] is None or c['timeout_seconds']<=0 or not c['finished_utc']:raise ValueError('missing subprocess completion evidence')
        if sha(ROOT/c['log'])!=c['log_sha256']:raise ValueError('changed process log')
    if r['status']=='PASS' and r['commands'][1]['exit_code']!=0:raise ValueError('false passing subprocess')
    return r

def main():
    dest=ROOT/'reports/revd_offline/tiled'/('w1-handoff-'+run_id());dest.mkdir(parents=True,exist_ok=False)
    reports=[];failures=[];all36=[];gate_reports=[]
    gate_sha=sha(ROOT/'scripts/revd_offline_tiled_gate.py')
    for rid in RUNS:
        folder=ROOT/'reports/revd_offline/tiled'/rid
        try:
            summary=json.loads((folder/'summary.json').read_text())
            if summary['status']!='PASS':raise ValueError('summary did not pass')
            for p,digest in summary.get('source_sha256',{}).items():
                if sha(ROOT/p)!=digest:raise ValueError('changed suite source')
            receipts=[verify_receipt(path) for path in sorted(folder.rglob('run_manifest.json'))]
            if not receipts:raise ValueError('no actual RTL receipts')
            if 'full36' in rid:
                if len(receipts)!=36 or any(r['status']!='PASS' for r in receipts):raise ValueError('not36 passing cases')
                if sum(r['comparison']['outputs'] for r in receipts)!=912384:raise ValueError('wrong frozen output total')
                all36=receipts
            if 'protocol' in rid:gate=check_protocol(folder/'summary.json',2 if 'pm2' in rid else 4)
            elif 'numeric' in rid:gate=check_numeric(folder/'summary.json')
            else:gate=check_suite(folder/'summary.json',2 if 'pm2' in rid else 4,2 if '-l2-' in rid else 1)
            gate_reports.append({'run_id':rid,'result':gate})
            reports.append({'run_id':rid,'summary':str((folder/'summary.json').relative_to(ROOT)),'summary_sha256':sha(folder/'summary.json'),'actual_RTL_receipts':len(receipts)})
        except (ValueError,OSError,KeyError) as exc:failures.append({'run_id':rid,'error':str(exc)})
    production=json.loads((ROOT/'reports/revd_offline/tiled/w1-production-pm4-l1-001/synthetic99/run_manifest.json').read_text())
    negatives=ROOT/'reports/revd_offline/tiled/w1-gate-negatives-final-005/summary.json'
    neg=json.loads(negatives.read_text())
    if neg['status']!='PASS' or neg['software_checker_negative_count']!=25 or neg['source_sha256']['scripts/revd_offline_tiled_gate.py']!=gate_sha or sha(ROOT/'scripts/revd_offline_tiled_gate.py')!=gate_sha:
        failures.append({'run_id':'software_negatives','error':'missing/stale 25-case negative proof or gate changed'})
    result={'status':'CORE_EVIDENCE_COMPLETE_PENDING_INDEPENDENT_REVIEW' if not failures else 'PARTIAL','created_utc':utc(),
            'profile':'CTX4_W1_Y1_fullX_PM4_L1','parent_accepted':False,'official_contest_acceptance':False,
            'source_sha256':{str(p.relative_to(ROOT)):sha(p) for p in [ROOT/'rtl/revd_opt/core_stream_tiled_opt.sv',ROOT/'dv/revd_opt/tiled_core_tb.sv',ROOT/'dv/revd_opt/tiled_runner.py',ROOT/'dv/revd_opt/tiled_protocol.py',ROOT/'dv/revd_opt/tiled_numeric.py',ROOT/'config/revd_opt/tiled_w1_y1.json']},
            'evidence':reports,'failures':failures,'frozen_cases':len(all36),'frozen_outputs':sum(r['comparison']['outputs'] for r in all36),
            'independent_checker_results':gate_reports,'gate_sha256':gate_sha,'software_negative_summary':str(negatives.relative_to(ROOT)),'software_negative_summary_sha256':sha(negatives),
            'production_counters':production['task_counters'],'production_windows':production['windows'],'production_tile_counters':production['tile_counters'],
            'tested_scope':{'PM4_L1':'full36+independent_repeat+production+protocol','PM4_L2':'production+small+protocol; nofull36_L2','PM2_L1_L2':'small+protocol; nofull36_PM2'},
            'numeric_scope':{'PM':4,'shifts':list(range(48)),'READ_LATENCY':'1+shift%2; all48 alternate L1/L2, not48 per latency'},
            'actual_RTL_mutations':{'classes_per_profile':8,'PM_values':[2,4],'READ_LATENCY':1,'compiled_and_run_mutant_cases':16,'software_negatives_are_separate':True},
            'checker_fix_red_green':{'Python_tool_SHA':['reports/revd_offline/tiled/toolsha-red-001/summary.json','reports/revd_offline/tiled/toolsha-green-001/summary.json'],'suite_role_alias':['reports/revd_offline/tiled/suite-role-red-001/summary.json','reports/revd_offline/tiled/suite-role-green-001/summary.json'],'tool_path_and_version':['reports/revd_offline/tiled/toolpath-red-001/summary.json','reports/revd_offline/tiled/toolpath-green-001/summary.json']},
            'handoff_source_sha256':sha(__file__),
            'storage_proxy':{'fullW_bytes':32768,'W1_bytes':2048,'full_bias_bytes':1536,'W1_bias_bytes':96,'macro_options':'depth256 logical bank requires e.g.2x128 or1x1024; no specified macro mapping acceptance'},
            'limitations':['W1 CPU integration NOT_RUN; fullW driver schedule is incompatible unless adapted.','No official600,150MHz,2.25mm2,power/energy acceptance.','Cold frontend timestamp is comparable; START window includes postSTART tile loads and differs from fullW preload contract.','Capacity reduction is a logical proxy; source changes invalidate affected receipts.'],
            'author_review_only':True}
    put(dest/'handoff.json',result);print(dest/'handoff.json',result['status'],flush=True);return 0 if not failures else 1

if __name__=='__main__':raise SystemExit(main())
