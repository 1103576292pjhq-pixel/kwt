"""Read-only adversarial checks of a real freshly reproduced package CPU run."""
from __future__ import annotations
import argparse
import copy
import json
from pathlib import Path
import sys
import tempfile
from unittest.mock import patch

sys.dont_write_bytecode=True

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--package-root',required=True);parser.add_argument('--report',required=True)
    parser.add_argument('--out',required=True);args=parser.parse_args()
    root=Path(args.package_root).resolve();sys.path.insert(0,str(root))
    from scripts import revd_offline_gate as gate
    from scripts.revd_offline_common import sha,put,read_json,utc
    if gate.ROOT.resolve()!=root:raise RuntimeError('gate import escaped requested package')
    path=Path(args.report)
    if not path.is_absolute():path=root/path
    path=path.resolve()
    if not path.is_relative_to(root):raise RuntimeError('report outside requested package')
    binding_path=path.parent/'binary-binding.json';binding=read_json(binding_path)
    binary=root/binding['actual_executable']
    immutable={str(p):sha(p) for p in (path,binding_path,binary)}
    observed=[]
    original_read,original_sha,original_is_file=gate.read_json,gate.sha,Path.is_file
    def check(name,expected,token=None,binding_mutation=None,report_mutation=None,missing=False,replacement=None):
        def read_view(p):
            value=original_read(p)
            if Path(p)==binding_path and binding_mutation:
                value=copy.deepcopy(value);binding_mutation(value)
            if Path(p)==path and report_mutation:
                value=copy.deepcopy(value);report_mutation(value)
            return value
        def hash_view(p):
            return original_sha(replacement) if replacement is not None and Path(p)==binary else original_sha(p)
        def file_view(p):return False if missing and p==binding_path else original_is_file(p)
        with patch.object(gate,'read_json',read_view),patch.object(gate,'sha',hash_view),patch.object(Path,'is_file',file_view):
            try:
                result=gate.check_cpu(path)
                item={'name':name,'expected':expected,'actual':'ACCEPT','gate':result}
            except (ValueError,OSError) as exc:
                item={'name':name,'expected':expected,'actual':'REJECT','error':str(exc)}
        item['matches_expected']=item['actual']==expected and (not token or token in item.get('error',''))
        observed.append(item)
    check('fresh_current_positive','ACCEPT')
    check('fresh_legacy_creator_downgrade','REJECT','legacy binding requires explicit historical validation',
          binding_mutation=lambda b:b.update(binding_script_sha256='7f8b910cfd555bba00cf304af383db55f0a0b1ccc193a941abc3145400b88974'))
    check('fresh_wrong_compiled_digest','REJECT','CPU compiled simulator binding mismatch',
          report_mutation=lambda r:r.update(compiled_simulator_sha256='0'*64))
    check('fresh_missing_binding','REJECT','binary binding missing',missing=True)
    with tempfile.TemporaryDirectory() as folder:
        replacement=Path(folder)/'replacement';replacement.write_bytes(b'not the real CPU simulator\n')
        check('fresh_changed_binary','REJECT','CPU compiled simulator binding mismatch',replacement=replacement)
    unchanged=all(sha(Path(p))==digest for p,digest in immutable.items())
    result={'status':'PASS' if unchanged and all(o['matches_expected'] for o in observed) else 'FAIL',
            'checked_utc':utc(),'actual_python':sys.executable,'package_root':str(root),'report':str(path),
            'observations':observed,'immutable_bytes_unchanged':unchanged,'immutable_sha256':immutable,
            'source_sha256':{str(p.relative_to(root)):sha(p) for p in [root/'scripts/revd_offline_gate.py',root/'scripts/revd_offline_soc_bindings.py',root/'scripts/revd_offline_soc_run.py']},
            'probe_sha256':sha(Path(__file__)),'mutation_policy':'Explicit in-memory read/hash/file overlays against real fresh result; no package files changed.'}
    put(Path(args.out),result);print(json.dumps(result,indent=2));return 0 if result['status']=='PASS' else 1

if __name__=='__main__':raise SystemExit(main())
