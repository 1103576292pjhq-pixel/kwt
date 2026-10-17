#!/usr/bin/env python3
"""Select a fixed frozen pair without changing quantization or normal sources."""
from __future__ import annotations
import argparse
from pathlib import Path
import sys
sys.dont_write_bytecode=True
sys.path.insert(0,str(Path(__file__).resolve().parent))
import revd_offline_soc_run as soc
from revd_offline_common import ROOT,put,read_json,run_id,sha

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--case-offset',type=int,choices=[2,4,6,8,10],required=True)
    parser.add_argument('--run-id',default=None);args=parser.parse_args()
    rid=args.run_id or run_id();manifest_path=ROOT/'reports/prototype/vectors/manifest.json'
    frozen=read_json(manifest_path)
    selected=frozen['cases'][args.case_offset:args.case_offset+2]
    if len(selected)!=2:raise RuntimeError('missing exact frozen pair')
    # Scope the manifest view in memory only. The original file and every
    # numeric parameter stay unchanged, and their original SHA remains bound.
    original_reader=soc.read_json
    def pair_view(path):
        value=original_reader(path)
        if Path(path)==manifest_path:value={**value,'cases':value['cases'][args.case_offset:args.case_offset+2]}
        return value
    soc.read_json=pair_view
    soc.IMPLEMENTATION.append('scripts/revd_offline_soc_layers.py')
    sys.argv=[sys.argv[0],'--stage','full','--tasks','2','--pm','4','--latency','1','--run-id',rid]
    soc.main(defer_binary_binding=True)
    out=ROOT/'reports/revd_offline/soc'/rid
    report=read_json(out/'result.json')
    expected=[case['case_id'] for case in selected]
    if [case['case_id'] for case in report['cases']]!=expected:raise RuntimeError('actual report does not match explicit case selection')
    binding={'normal_sources_modified':False,'selection':'Fixed frozen engineering layers; no tuning or new numeric parameters.',
      'case_indices':list(range(args.case_offset,args.case_offset+2)),'case_ids':expected,
      'original_manifest_sha256':sha(manifest_path),'wrapper_sha256':sha(Path(__file__)),
      'actual_simulator_executable':str((out/'obj/Vsoc_cpu_tb').relative_to(ROOT)),
      'actual_simulator_executable_sha256':sha(out/'obj/Vsoc_cpu_tb'),
      'firmware_binary_sha256':sha(out/'revd-driver.bin'),
      'normal_soc_runner_sha256':sha(ROOT/'scripts/revd_offline_soc_run.py'),
      'scope':'Two cold parameter tasks in one real E203 boot, not a full encoder.'}
    put(out/'pair-binding.json',binding)
    report['profile']['case_offset']=args.case_offset
    report['pair_binding']=binding
    report['artifacts_sha256']['pair-binding.json']=sha(out/'pair-binding.json')
    put(out/'result.json',report)
    from revd_offline_soc_bindings import bind
    bind(out/'result.json')
if __name__=='__main__':main()
