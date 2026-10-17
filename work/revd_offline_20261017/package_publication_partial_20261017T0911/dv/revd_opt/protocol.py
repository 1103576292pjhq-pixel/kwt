"""Directed public-stream reset/fault, continuous-task and real RTL mutation runs."""
import json
from pathlib import Path
import sys
import time
import uuid
import argparse
import numpy as np
from core_runner import ROOT,commands,expected_records,run_case,sha
from scripts.revd_offline_common import put as write_json,run_id

def main():
    parser=argparse.ArgumentParser();parser.add_argument("--boundary-only",action="store_true");args=parser.parse_args()
    source_sha256={str(Path(__file__).relative_to(ROOT)):sha(__file__)}
    out=ROOT/"reports/revd_offline/protocol"/run_id()
    out.mkdir(parents=True,exist_ok=False);results=[]
    x=np.zeros((5,64),dtype=np.int16);w=np.zeros((64,32),dtype=np.int16)
    x[:,63]=[-32768,-3,1,4,32767];w[63]=np.arange(-16,16,dtype=np.int16)
    b=np.arange(-16,16,dtype=np.int64)
    def test(name,**kw):
        r=run_case(out/name,x,w,b,0,**kw);results.append({"name":name,"status":r["status"],"manifest":str((out/name/"run_manifest.json").relative_to(ROOT))})
        print(name,r["status"],r.get("error",""),flush=True);return r
    full=commands(x,w,b,0).rsplit("f 0 0 0 0 0 0",1)[0]
    for latency in (1,2):
        for mode,name in ((0,"last_fire_invalid"),(1,"pending_last_fire"),(2,"pending_last_blocked"),(3,"next_begin_boundary")):
            if mode==0:
                stream=full+"9 1b 0 0 0 0 0\n";expect=expected_records(x,w,b,0,4);count=1
            elif mode in (1,2):
                stream=full+f"9 1b 0 {mode:x} 0 0 0\nc 0 0 0 0 0 0\n";expect=expected_records(x,w,b,0,4);count=0
            else:
                second=commands(-x,(7-w).astype(np.int16),123-b,7,28,12).splitlines()[1:]
                stream=full+"9 1c 0 3 0 7 c\n"+"\n".join(second)+"\n"
                expect=expected_records(x,w,b,0,4)+expected_records(-x,(7-w).astype(np.int16),123-b,7,4,28);count=2
            test(f"{name}_l{latency}",latency=latency,stream=stream,expected_override=expect,task_count=count)
    if args.boundary_only:
        summary={"status":"PASS" if all(r["status"]=="PASS" for r in results) else "FAIL","tests":results,"source_sha256":source_sha256}
        write_json(out/"summary.json",summary);print(out,flush=True);return 0 if summary["status"]=="PASS" else 1
    # First task is interrupted before its first public handshake; second is cold-reloaded.
    for latency in (1,2):
        for phase in (1,2,3,4,5):
            first=commands(x,w,b,0,27).rsplit("f 0 0 0 0 0 0",1)[0]
            stream="b 0 0 0 0 0 0\n"+first+f"e 0 0 {phase:x} 0 0 0\n"+commands(-x,w,-b,0,28)
            test(f"reset_l{latency}_phase{phase}",latency=latency,stream=stream,expected_override=expected_records(-x,w,-b,0,4,28))
    w2=(7-w).astype(np.int16);b2=123-b
    stream=commands(x,w,b,0,27,1)+commands(-x,w2,b2,7,28,12)
    test("continuous",stream=stream,task_count=2,expected_override=expected_records(x,w,b,0,4,27)+expected_records(-x,w2,b2,7,4,28))
    prefixes={
      "early_commit":"0 1b 0 0 0 0 1\n5 1b 0 0 0 0 0\n",
      "duplicate_x":"0 1b 0 0 0 0 1\n1 1b 0 0 0 0 0\n1 1b 0 0 0 0 0\n",
      "bad_dtype_value":"0 1b 0 0 0 0 1\n1 1b 0 0 8000 0 0\n",
      "bad_layer":"0 1b 0 0 0 0 d\n",
      "wrong_tile":commands(x,w,b,0).split("2 1b 0",1)[0]+"2 1b 1 0 0 0 0\n",
    }
    for name,prefix in prefixes.items(): test(name,stream=prefix+"c 0 0 0 0 0 0\n",expected_override=[],task_count=0)
    full=commands(x,w,b,0).rsplit("f 0 0 0 0 0 0",1)[0]
    test("fault_preserves_block",stream="b 0 0 0 0 0 0\n"+full+"d 0 0 0 0 0 0\n7 1b 0 0 0 0 0\nc 0 0 0 0 0 0\n",expected_override=expected_records(x,w,b,0,4)[:64],task_count=0)
    test("fault_on_fire",stream="b 0 0 0 0 0 0\n"+full+"d 0 0 0 0 0 0\n7 1b 0 0 0 0 0\na 0 0 0 0 0 0\nc 0 0 0 0 0 0\n",expected_override=expected_records(x,w,b,0,4)[:64],task_count=0)
    # These compile and simulate actual altered RTL; they are not scoreboard-only mutations.
    for mutation in ("MUT_DROP_K63","MUT_UNSIGNED","MUT_TAG_G","MUT_WRONG_INDEX","MUT_EARLY_DONE","MUT_NO_OUTPUT_CREDIT"):
        r=test(mutation,mutation=mutation)
        detected=r["status"]=="FAIL" and len(r["commands"])==2 and r["commands"][0]["exit_code"]==0 and ((r["commands"][1]["exit_code"]==0 and (r.get("error","").startswith("output ") or r.get("error","").startswith("raw48"))) or (r["commands"][1]["exit_code"]!=0 and any(t in (out/mutation/"sim.log").read_text() for t in ("early done","unstable blocked output","DONE_WITH_PENDING_INPUT","PIPE_"))))
        results[-1]["status"]="PASS" if detected else "FAIL";results[-1]["mutation_detected"]=detected
    summary={"status":"PASS" if all(r["status"]=="PASS" for r in results) and all(sha(ROOT/p)==v for p,v in source_sha256.items()) else "FAIL","tests":results,"source_sha256":source_sha256}
    write_json(out/"summary.json",summary);print(out,flush=True)
    return 0 if summary["status"]=="PASS" else 1

if __name__=="__main__": raise SystemExit(main())
