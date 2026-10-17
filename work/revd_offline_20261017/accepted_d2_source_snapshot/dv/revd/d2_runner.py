"""Compile and run the public V1 stream; the dense oracle never calls a DUT address function."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import time
import uuid
from functools import lru_cache
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.fixedpoint import ffn1_reference

def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def write_json(path,value):
    Path(path).write_text(json.dumps(value,indent=2,allow_nan=False)+"\n",encoding="utf-8")

@lru_cache(maxsize=1)
def tool_versions():
    versions={"python":sys.version,"numpy":np.__version__}
    for tool,args in (("iverilog",["-V"]),("vvp",["-V"]),("verilator",["--version"])):
        p=subprocess.run([tool,*args],text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,check=True)
        versions[tool]=p.stdout
    return versions

def run_command(cmd,out,timeout=180):
    started=time.time()
    try:
        proc=subprocess.run(list(map(str,cmd)),cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=timeout)
        code=proc.returncode; output=proc.stdout
    except subprocess.TimeoutExpired as exc:
        code=124; output=str(exc.stdout or "")+"\nTIMEOUT\n"
    Path(out).write_text(output,encoding="utf-8")
    return {"argv":list(map(str,cmd)),"exit_code":code,"seconds":time.time()-started,"log":str(Path(out).relative_to(ROOT)),"log_sha256":sha(out)}

def commands(x,w,b,shift,task=27,layer=1):
    m,n=x.shape[0],w.shape[1]
    lines=[f"0 {task:x} 0 0 0 {shift:x} {layer:x}"]
    for index,val in enumerate(x.flat): lines.append(f"1 {task:x} 0 {index:x} {int(val)&((1<<48)-1):012x} 0 0")
    for tile,nt in enumerate(range(0,n,16)):
        lines.append(f"2 {task:x} {tile:x} 0 0 0 0")
        for k in range(64):
            for j in range(16):
                lines.append(f"3 {task:x} {tile:x} {k*16+j:x} {int(w[k,nt+j])&((1<<48)-1):012x} 0 0")
        for j in range(16): lines.append(f"4 {task:x} {tile:x} {j:x} {int(b[nt+j])&((1<<48)-1):012x} 0 0")
        lines.append(f"5 {task:x} {tile:x} 0 0 0 0")
    lines.extend([f"6 {task:x} 0 0 0 0 0","f 0 0 0 0 0 0"])
    return "\n".join(lines)+"\n"

def expected_records(x,w,b,shift,pm,task=27):
    ref=ffn1_reference(x,w,b,shift)
    m,n=x.shape[0],w.shape[1]
    # Mathematical coordinates in mandated publication order, independent of bank layout.
    result=[]
    for col0 in range(0,n,16):
        for row0 in range(0,m,pm):
            for row in range(row0,min(row0+pm,m)):
                for col in range(col0,col0+16):
                    result.append([task,row*n+col,int(ref.output[row,col]),int(ref.overflow[row,col]),int(ref.output_saturated[row,col]),int(row==m-1 and col==n-1)])
    return result

def check_output(path,expected):
    lines=Path(path).read_text().splitlines()
    if len(lines)!=len(expected): raise ValueError(f"output count {len(lines)} != {len(expected)}")
    seen=set()
    for pos,(line,want) in enumerate(zip(lines,expected)):
        if not re.fullmatch(r"[0-9a-fA-F]{8} [0-9a-fA-F]{8} [0-9a-fA-F]{8} [01] [01] [01]",line):
            raise ValueError(f"unknown/malformed output at {pos}: {line}")
        fields=line.split(); got=[int(t,16) for t in fields[:3]]+[int(t) for t in fields[3:]]
        if got[2] >= 1<<31: got[2]-=1<<32
        key=tuple(got[:2])
        if key in seen: raise ValueError(f"duplicate task/index at {pos}")
        seen.add(key)
        if got!=want: raise ValueError(f"output {pos}: {got} != {want}")
    return {"outputs":len(lines),"unique":len(seen),"last_count":sum(r[-1] for r in expected),"sha256":sha(path)}

def synthetic(m,n,seed=91):
    rng=np.random.default_rng(seed)
    x=rng.integers(-32768,32768,(m,64),dtype=np.int16)
    w=rng.integers(-32768,32768,(64,n),dtype=np.int16)
    b=rng.integers(-(1<<47),(1<<47),(n,),dtype=np.int64)
    return x,w,b

def run_case(out,x,w,b,shift,pm=4,latency=1,task=27,mutation=None,stream=None,expected_override=None,task_count=1,layer=1):
    out=Path(out);out.mkdir(parents=True,exist_ok=False)
    cmd=out/"commands.hex";cmd.write_text(stream if stream is not None else commands(x,w,b,shift,task,layer),encoding="ascii")
    expected=expected_records(x,w,b,shift,pm,task) if expected_override is None else expected_override
    write_json(out/"expected.json",expected)
    for name,arr in (("X",x),("W",w),("b",b)): np.save(out/(name+".npy"),arr,allow_pickle=False)
    sources=[ROOT/"rtl/revd"/name for name in ("banked_sp16.sv","core_stream_frontend.sv","quant_epilogue.sv")]
    tb=ROOT/"dv/revd/core_tb.sv"
    build=["iverilog","-g2012","-s","core_tb",f"-Pcore_tb.M={x.shape[0]}",f"-Pcore_tb.N={w.shape[1]}",f"-Pcore_tb.PM={pm}",f"-Pcore_tb.READ_LATENCY={latency}"]
    if mutation: build.append("-D"+mutation)
    build.extend(["-o",out/"sim.vvp",tb,*sources])
    receipt={"status":"FAIL","m":x.shape[0],"n":w.shape[1],"pm":pm,"read_latency":latency,"task":task,"layer":layer,"shift":shift,"mutation":mutation,"expected_tasks":task_count,
        "tools":tool_versions(),"started_at":time.time(),
        "source_sha256":{str(p.relative_to(ROOT)):sha(p) for p in [*sources,tb,Path(__file__),ROOT/"numeric/fixedpoint.py"]},
        "input_sha256":{p.name:sha(p) for p in [cmd,out/"X.npy",out/"W.npy",out/"b.npy",out/"expected.json"]},"commands":[]}
    try:
        receipt["commands"].append(run_command(build,out/"compile.log"))
        if receipt["commands"][-1]["exit_code"]: raise ValueError("RTL compilation failed")
        receipt["commands"].append(run_command(["vvp",out/"sim.vvp",f"+CMD={cmd}",f"+OUT={out/'output.hex'}",f"+STATS={out/'stats.txt'}"],out/"sim.log",timeout=240))
        if receipt["commands"][-1]["exit_code"]: raise ValueError("RTL simulation failed")
        if "RTL_COMPLETE" not in (out/"sim.log").read_text(): raise ValueError("missing simulator completion")
        receipt["comparison"]=check_output(out/"output.hex",expected)
        stats=(out/"stats.txt").read_text().splitlines()
        task_lines=[s.split() for s in stats if s.startswith("TASK ")]
        if len(task_lines)!=task_count: raise ValueError("missing/extra task stats")
        keys=["task","load_cycles","compute_cycles","output_cycles","wait_cycles","core_cycles","frontend_cycles","issue","retire","effective_macs","virtual_macs","input_accepts","event_retires"]
        m,n=x.shape[0],w.shape[1]
        receipt["task_counters"]=[dict(zip(keys,map(int,line[1:]))) for line in task_lines]
        for counters in receipt["task_counters"]:
            if counters["effective_macs"]!=m*n*64: raise ValueError("incorrect effective MAC counter")
            if counters["issue"]!=((m+pm-1)//pm)*(n//4)*64 or counters["retire"]!=counters["issue"]: raise ValueError("issue/retire mismatch")
            if counters["input_accepts"]!=counters["event_retires"]: raise ValueError("accepted commands not all retired")
        receipt["counters"]=receipt["task_counters"][-1] if task_count else None
        receipt["banks"]={kind:[list(map(int,s.split()[1:])) for s in stats if s.startswith(kind+" ")] for kind in ("X","W")}
        if task_count:
            if sum(r[1] for r in receipt["banks"]["X"])!=task_count*m*64*(n//4) or sum(r[2] for r in receipt["banks"]["X"])!=task_count*m*64: raise ValueError("X CE mismatch")
            if sum(r[1] for r in receipt["banks"]["W"])!=task_count*((m+pm-1)//pm)*n*64 or sum(r[2] for r in receipt["banks"]["W"])!=task_count*n*64: raise ValueError("W CE mismatch")
        receipt["output_sha256"]={name:sha(out/name) for name in ("output.hex","stats.txt","sim.log","compile.log")}
        if any(sha(ROOT/p)!=digest for p,digest in receipt["source_sha256"].items()): raise ValueError("source changed while running")
        if any(sha(out/p)!=digest for p,digest in receipt["input_sha256"].items()): raise ValueError("input changed while running")
        receipt["status"]="PASS"
    except (ValueError,OSError) as exc: receipt["error"]=str(exc)
    receipt["finished_at"]=time.time();write_json(out/"run_manifest.json",receipt)
    return receipt

def main():
    p=argparse.ArgumentParser();p.add_argument("--profile",choices=["small","production","full36","repeat"],default="small")
    p.add_argument("--run-id",default=time.strftime("%Y%m%d-%H%M%S")+"-"+uuid.uuid4().hex[:6]);p.add_argument("--latency",type=int,default=1)
    args=p.parse_args();out=ROOT/"reports/revd/d2"/args.profile/args.run_id;out.mkdir(parents=True,exist_ok=False)
    results=[]
    if args.profile=="small":
        cases=[(f"m{m}_n{n}_pm{pm}",*synthetic(m,n,m*n+pm),s,pm,1) for m,n,pm,s in [(1,16,4,0),(3,16,4,16),(4,32,4,47),(5,32,4,8),(5,16,2,5)]]
    elif args.profile=="production": cases=[("synthetic99",*synthetic(99,256),8,4,1)]
    else:
        from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
        manifest,verified=verify_frozen_inputs(ROOT)
        write_json(out/"validated_inputs.json",{"verification":verified,"manifest_sha256":sha(ROOT/"reports/prototype/vectors/manifest.json")})
        entries=manifest["cases"] if args.profile=="full36" else manifest["cases"][:1]
        cases=[]
        for c in entries:
            a=validated_case(ROOT,c)
            cases.append((c["case_id"].replace("/","_"),a["Xq"],a["Wq"],a["bq"],c["config"]["output_shift"],4,c["layer"]))
    for label,x,w,b,s,pm,layer in cases:
        r=run_case(out/label,x,w,b,s,pm,args.latency,layer=layer);results.append({"case":label,"path":str((out/label/"run_manifest.json").relative_to(ROOT)),"status":r["status"]})
        print(label,r["status"],r.get("error",r.get("comparison")),flush=True)
        if r["status"]!="PASS": break
    summary={"status":"PASS" if len(results)==len(cases) and all(r["status"]=="PASS" for r in results) else "FAIL","profile":args.profile,"read_latency":args.latency,"cases":results}
    write_json(out/"summary.json",summary);print(out,flush=True)
    return 0 if summary["status"]=="PASS" else 1

if __name__=="__main__": raise SystemExit(main())
