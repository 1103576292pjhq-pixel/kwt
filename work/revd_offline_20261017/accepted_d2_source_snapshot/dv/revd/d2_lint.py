"""Verilator cross-check with fresh logs; does not perform synthesis or STA."""
from pathlib import Path
import time
import uuid
from d2_runner import ROOT,run_command,write_json,sha

def main():
    out=ROOT/"reports/revd/d2/lint"/(time.strftime("%Y%m%d-%H%M%S")+"-"+uuid.uuid4().hex[:6])
    out.mkdir(parents=True,exist_ok=False)
    sources=[ROOT/"rtl/revd"/p for p in ("core_stream_frontend.sv","banked_sp16.sv","quant_epilogue.sv")]
    hashes={p.relative_to(ROOT).as_posix():sha(p) for p in [*sources,Path(__file__)]}
    receipt=run_command(["verilator","--lint-only","--top-module","core_stream_frontend","-Wall",*sources],out/"lint.log")
    warnings=[line for line in (out/"lint.log").read_text().splitlines() if "%Warning" in line or "%Error" in line]
    passed=receipt["exit_code"]==0 and not warnings and all(sha(ROOT/p)==v for p,v in hashes.items())
    write_json(out/"run_manifest.json",{"status":"PASS" if passed else "FAIL","commands":[receipt],"warnings":warnings,"source_sha256":hashes,"not_run":["STA","SYNTHESIS","PPA"]})
    print(out,passed,flush=True);return 0 if passed else 1

if __name__=="__main__": raise SystemExit(main())
