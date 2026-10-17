#!/usr/bin/env python3
"""Same CPU/driver/adapter cold-window comparison using immutable accepted D2."""
from __future__ import annotations
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,WORK,put,read_json,run_id,sha

def main():
    p=argparse.ArgumentParser();p.add_argument('--run-id',default=None)
    p.add_argument('--tasks',type=int,choices=[1,2],default=2)
    p.add_argument('--stage',choices=['small','full'],default='full');args=p.parse_args()
    rid=args.run_id or run_id();source=ROOT/'rtl/revd/core_stream_frontend.sv'
    text=source.read_text(encoding='utf-8')
    needle='module core_stream_frontend #('
    if text.count(needle)!=1:raise RuntimeError('unexpected D2 module declaration')
    alias_dir=WORK/'soc'/('baseline-alias-'+rid);alias_dir.mkdir(parents=True,exist_ok=False)
    alias=alias_dir/'core_stream_frontend_opt.sv'
    alias.write_text(text.replace(needle,'module core_stream_frontend_opt #(',1),encoding='utf-8')
    transform={'source':str(source.relative_to(ROOT)),'source_sha256':sha(source),
               'alias':str(alias.relative_to(ROOT)),'alias_sha256':sha(alias),
               'change':'Exactly one module identifier renamed for the shared new ICB adapter; no other source text change.',
               'new_profile':False,'reference':'accepted frozen D2 full-W micro PM4'}
    soc.IMPLEMENTATION[0]=str(alias.relative_to(ROOT))
    soc.IMPLEMENTATION.extend(['rtl/revd/core_stream_frontend.sv','scripts/revd_offline_soc_baseline.py'])
    sys.argv=[sys.argv[0],'--stage',args.stage,'--tasks',str(args.tasks),'--sim','verilator','--pm','4','--latency','1','--run-id',rid]
    soc.main()
    out=ROOT/'reports/revd_offline/soc'/rid
    put(out/'baseline-transformation.json',transform)
    report=read_json(out/'result.json');report['baseline_reference']=transform
    report['profile']['core']='accepted_D2_micro_namespace_alias'
    report['artifacts_sha256']['baseline-transformation.json']=sha(out/'baseline-transformation.json')
    put(out/'result.json',report)
if __name__=='__main__':main()
