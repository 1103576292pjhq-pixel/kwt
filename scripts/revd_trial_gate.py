"""Fail-closed acceptance of fresh RevD trial execution evidence."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import time
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT));sys.path.insert(0,str(ROOT/"dv/revd"))
import numpy as np
from d2_runner import check_output,expected_records,commands
from dv.revd.d0_inputs import verify_frozen_inputs,validated_case
from dv.revd.d0_run import identity,source_manifest

def read(path): return json.loads(Path(path).read_text(encoding="utf-8-sig"))
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def require(ok,message):
    if not ok: raise ValueError(message)
def check_hashes(mapping,base=ROOT):
    require(isinstance(mapping,dict) and bool(mapping),"missing hash inventory")
    for path,digest in mapping.items(): require(sha(base/path)==digest,"hash mismatch: "+path)
def check_commands(records):
    require(isinstance(records,list) and bool(records),"missing command executions")
    for r in records:
        require(type(r["exit_code"]) is int and r["exit_code"]==0,"nonzero/timeout subprocess")
        if "log" in r:
            path=ROOT/r["log"];text=path.read_text(encoding="utf-8")
            require("SKIP" not in text and "TIMEOUT" not in text,"SKIP/timeout evidence")
            if "log_sha256" in r: require(sha(path)==r["log_sha256"],"changed process log")

def normalize_arg(value):
    value=str(value).replace("\\","/")
    for prefix in ("/mnt/d/github/kwt/","D:/github/kwt/",ROOT.as_posix()+"/"):
        value=value.replace(prefix,"")
    return value

def validate_case(path,dense=True):
    path=Path(path);r=read(path);folder=path.parent
    require(r["status"]=="PASS","case did not pass")
    require(r.get("mutation") is None,"mutated implementation cannot qualify as normal")
    source_paths={"rtl/revd/"+n for n in ("banked_sp16.sv","core_stream_frontend.sv","quant_epilogue.sv")}|{"dv/revd/core_tb.sv","dv/revd/d2_runner.py","numeric/fixedpoint.py"}
    require(set(r["source_sha256"])==source_paths,"incomplete/extra source inventory")
    require(set(r["input_sha256"])=={"commands.hex","X.npy","W.npy","b.npy","expected.json"},"incomplete input inventory")
    require(set(r["output_sha256"])=={"output.hex","stats.txt","sim.log","compile.log"},"incomplete output inventory")
    require(r["read_latency"] in (1,2),"invalid read latency")
    check_commands(r["commands"])
    require(len(r["commands"])==2 and r["commands"][0]["argv"][0]=="iverilog" and r["commands"][1]["argv"][0]=="vvp","not an Icarus compile and simulation")
    relative=folder.resolve().relative_to(ROOT).as_posix()
    compile_expected=["iverilog","-g2012","-s","core_tb",f"-Pcore_tb.M={r['m']}",f"-Pcore_tb.N={r['n']}",f"-Pcore_tb.PM={r['pm']}",f"-Pcore_tb.READ_LATENCY={r['read_latency']}","-o",relative+"/sim.vvp","dv/revd/core_tb.sv",*["rtl/revd/"+n for n in ("banked_sp16.sv","core_stream_frontend.sv","quant_epilogue.sv")]]
    sim_expected=["vvp",relative+"/sim.vvp",f"+CMD={relative}/commands.hex",f"+OUT={relative}/output.hex",f"+STATS={relative}/stats.txt"]
    require([normalize_arg(a) for a in r["commands"][0]["argv"]]==compile_expected,"compile argv/config/source binding mismatch")
    require([normalize_arg(a) for a in r["commands"][1]["argv"]]==sim_expected,"simulation argv/output binding mismatch")
    require((folder/"sim.vvp").is_file() and bool(r["tools"]["iverilog"]) and bool(r["tools"]["vvp"]),"missing simulator binary/tools")
    check_hashes(r["source_sha256"]);check_hashes(r["input_sha256"],folder);check_hashes(r["output_sha256"],folder)
    require("RTL_COMPLETE" in (folder/"sim.log").read_text(),"missing simulation completion")
    expected=read(folder/"expected.json")
    if dense:
        require(r["expected_tasks"]==1,"dense case needs one cold task")
        x=np.load(folder/"X.npy",allow_pickle=False);w=np.load(folder/"W.npy",allow_pickle=False);b=np.load(folder/"b.npy",allow_pickle=False)
        require(x.shape==(r["m"],64) and w.shape==(64,r["n"]) and b.shape==(r["n"],),"bad input shape")
        require(x.dtype==np.int16 and w.dtype==np.int16 and b.dtype==np.int64,"bad input dtype")
        expected=expected_records(x,w,b,r["shift"],r["pm"],r["task"])
        require(read(folder/"expected.json")==expected,"altered dense oracle")
        require((folder/"commands.hex").read_text()==commands(x,w,b,r["shift"],r["task"],r["layer"]),"stream not bound to declared dense inputs/layer/shift")
    comparison=check_output(folder/"output.hex",expected)
    require(comparison==r["comparison"],"comparison summary mismatch")
    stats=(folder/"stats.txt").read_text().splitlines()
    tasks=[list(map(int,s.split()[1:])) for s in stats if s.startswith("TASK ")]
    require(len(tasks)==r["expected_tasks"],"missing done/counters")
    keys=["task","load_cycles","compute_cycles","output_cycles","wait_cycles","core_cycles","frontend_cycles","issue","retire","effective_macs","virtual_macs","input_accepts","event_retires"]
    require(r["task_counters"]==[dict(zip(keys,v)) for v in tasks],"counter receipt differs from actual RTL stats")
    require(r["counters"]==(r["task_counters"][-1] if tasks else None),"counter summary mismatch")
    for v in tasks:
        require(len(v)==13 and v[9]==r["m"]*r["n"]*64,"effective MAC mismatch")
        slots=((r["m"]+r["pm"]-1)//r["pm"])*(r["n"]//4)*64
        require(v[7]==v[8]==slots,"issue/retire mismatch")
        require(v[10]==slots*r["pm"]*4-v[9],"virtual lane count mismatch")
        require(v[11]==v[12],"input accept/retire mismatch")
        require(v[5]==v[2]+v[3] and v[6]==v[1]+v[5],"cycle windows do not reconcile")
        require(all(x>=0 for x in v) and v[4]<=v[6],"invalid cycle counters")
        if dense: require(v[11]==r["m"]*64+(r["n"]//16)*1042+2,"incorrect actual input retirement count")
    banks={kind:[list(map(int,s.split()[1:])) for s in stats if s.startswith(kind+" ")] for kind in ("X","W")}
    require(r["banks"]==banks,"bank receipt differs from actual RTL stats")
    for kind,bank_count in (("X",r["pm"]),("W",4)):
        require(len(banks[kind])==len(tasks)*bank_count,"missing bank CE evidence")
        for task_index in range(len(tasks)):
            for bank in range(bank_count):
                record=banks[kind][task_index*bank_count+bank]
                if kind=="X":
                    rows=(r["m"]-1-bank)//r["pm"]+1 if r["m"]>bank else 0
                    expected_bank=[bank,rows*64*(r["n"]//4),rows*64]
                else: expected_bank=[bank,((r["m"]+r["pm"]-1)//r["pm"])*(r["n"]//4)*64,r["n"]*16]
                require(record==expected_bank,"actual bank CE counts mismatch")
    return r

def summary_cases(path):
    s=read(ROOT/path);require(s["status"]=="PASS" and bool(s["cases"]),"incomplete profile")
    results=[]
    for c in s["cases"]:
        require(c["status"]=="PASS","failed profile case")
        r=validate_case(ROOT/c["path"]);results.append((c,r))
    return s,results


def check_protocol_coverage(protocol):
    required={f"reset_l{l}_phase{p}" for l in (1,2) for p in (1,2,3)}|{"continuous","early_commit","duplicate_x","bad_dtype_value","bad_layer","wrong_tile","fault_preserves_block","fault_on_fire","MUT_DROP_K63","MUT_UNSIGNED"}
    required|={f"{name}_l{latency}" for name in ("last_fire_invalid","pending_last_fire","pending_last_blocked","next_begin_boundary") for latency in (1,2)}
    names=[t["name"] for t in protocol["tests"]]
    require(len(names)==len(set(names)),"duplicate protocol cases")
    require(set(names)>=required,"protocol cases missing (including terminal boundary)")


def check_boundary_evidence(test):
    name=test["name"]
    modes={"last_fire_invalid":0,"pending_last_fire":1,"pending_last_blocked":2,"next_begin_boundary":3}
    prefix=name.rsplit("_l",1)[0]
    if prefix not in modes: return
    mode=modes[prefix];manifest=ROOT/test["manifest"];r=read(manifest)
    require((r["m"],r["n"],r["pm"],r["read_latency"])==(5,32,4,int(name[-1])),"terminal geometry/latency mismatch")
    records=[list(map(int,line.split()[1:])) for line in (manifest.parent/"stats.txt").read_text().splitlines() if line.startswith("BOUNDARY ")]
    expected_first={0:[0,0,0,0,1,1,1,0,0,0],1:[1,0,1,1,1,0,1,0,0,0],2:[2,0,1,1,1,0,0,0,0,0],3:[3,0,0,0,1,1,1,0,0,0]}
    require(bool(records) and records[0]==expected_first[mode],"terminal in_ready/in_fire scenario not exercised")
    require(len(records)==(1 if mode==0 else 2),"missing/extra terminal observations")
    require(r["expected_tasks"]==({0:1,1:0,2:0,3:2}[mode]),"incorrect terminal completion count")
    if mode in (1,2):
        require(records[1][0:2]==[mode,1] and records[1][-3:]==[0,1,0],"accepted terminal event did not fault before success")
    if mode==2: require(records[1][4:7]==[1,1,0],"final fault output was not held blocked")
    if mode==3: require(records[1]==[3,2,1,1,0,1,1,0,0,0],"next BEGIN handshake ownership mismatch")


def check_gate_negative(negative):
    require(negative["exit_code"]==0 and negative["negative_tests"]>=16,"gate negative tests missing")
    require(set(negative["source_sha256"])=={"scripts/revd_trial_gate.py","dv/revd/gate_test.py"},"incomplete gate negative source inventory")
    check_hashes(negative["source_sha256"])
    check_commands([negative["command"]])
    command=negative["command"]
    require(len(command["argv"])==3 and command["argv"][1]=="-B" and normalize_arg(command["argv"][2])=="dv/revd/gate_test.py","not a gate test execution")
    require(command["log"]==negative["log"] and command["log_sha256"]==negative["log_sha256"],"gate negative command/log mismatch")
    log=(ROOT/negative["log"]).read_text()
    require(sha(ROOT/negative["log"])==negative["log_sha256"] and "\nOK\n" in log,"gate tests log missing/changed/failed")
    require(any(line.startswith("test_missing_terminal_boundary_case ") and line.endswith(" ... ok") for line in log.splitlines()),"terminal omission negative was not executed")

def evaluate(bundle):
    b=read(bundle)
    require(b["source_sha256"]==source_manifest()["files"],"current source inventory changed/missing untracked code")
    config=read(ROOT/"config/revd/trial.json")
    require([config[k] for k in ("M","N","K","PM","PN","N_TILE")]==[99,256,64,4,4,16] and config["read_latencies"]==[1,2] and config["postprocessing_overlap"] is False,"unapproved trial configuration")
    frozen=identity();launch=read(ROOT/"work/revd/launch_baseline.json")
    require(frozen["baseline_is_ancestor"] and frozen["git_remotes"]==read(ROOT/"work/revd/baseline.json")["git_remotes"],"Git baseline/remote changed")
    snapshot=read(ROOT/launch["source_snapshot_receipt"])
    actual={p.relative_to(ROOT/"docs/revd").as_posix() for p in (ROOT/"docs/revd").rglob("*") if p.is_file()}
    require(actual=={x["path"] for x in snapshot["files"]},"read-only package contains missing/extra files")
    original,verified=verify_frozen_inputs(ROOT)
    d0=read(ROOT/b["d0"]);require(d0["status"]=="PASS" and d0["exit_code"]==0,"D0 failed")
    check_commands(d0["commands"]);check_hashes(d0["artifacts_sha256"]);check_hashes(d0["execution_sources"])
    require(d0["v0_compare"]["vectors"]==768 and d0["v0_compare"]["full_matrix_outputs"]==25344,"incomplete V0 comparison")
    d1=read(ROOT/b["d1"])
    require(all(d1.get(k) is True for k in ("passed","quant_passed","micro_passed","lint_passed","mutations_passed")),"D1 not complete")
    check_hashes(d1["sources"]);check_hashes(d1["artifacts"])
    # Expected failing mutation subprocesses are verified separately from positive command runs.
    check_commands([r for r in d1["commands"] if not any("/mutant_" in str(arg) for arg in r["command"])])
    require(d1["quant_vector_count"]>=2170 and {r["pm"] for r in d1["micro_runs"]}=={2,4},"insufficient D1 coverage")
    for mut in d1["mutations"]:
        require(mut["detected"] is True and mut["compile_exit_code"]==0 and mut["simulate_exit_code"]==1,"undetected D1 RTL mutation")
        compile_runs=[c for c in d1["commands"] if str(c.get("log","")).endswith("mutant_"+mut["name"]+"_compile.log")]
        sim_runs=[c for c in d1["commands"] if str(c.get("log","")).endswith("mutant_"+mut["name"]+"_simulate.log")]
        check_commands(compile_runs)
        require(len(sim_runs)==1 and sim_runs[0]["exit_code"]==1 and mut["expected_failure"] in (ROOT/sim_runs[0]["log"]).read_text(),"not a functional RTL mutation failure")
    profiles={key:summary_cases(b[key]) for key in ("small","production","full36","repeat","latency2")}
    require({(r["m"],r["n"],r["pm"]) for c,r in profiles["small"][1]}>={(1,16,4),(3,16,4),(4,32,4),(5,32,4),(5,16,2)},"missing small geometries")
    for key,latency in (("production",1),("latency2",2)):
        require(len(profiles[key][1])==1 and [(r["m"],r["n"],r["pm"],r["read_latency"]) for c,r in profiles[key][1]]==[(99,256,4,latency)],"missing production latency profile")
    main=profiles["full36"][1]
    require(len(main)==36,"requires all36 engineering cases")
    expected_names={c["case_id"].replace("/","_"):c for c in original["cases"]}
    require({c["case"] for c,r in main}==set(expected_names),"incorrect3x12 coverage")
    for c,r in main:
        source=expected_names[c["case"]];a=validated_case(ROOT,source);folder=(ROOT/c["path"]).parent
        require((r["m"],r["n"],r["pm"],r["layer"],r["shift"] )==(99,256,4,source["layer"],source["config"]["output_shift"]),"production profile/layer/config mismatch")
        for file,key in (("X","Xq"),("W","Wq"),("b","bq")):
            require(np.array_equal(np.load(folder/(file+".npy"),allow_pickle=False),a[key]),"source array not actually consumed")
    repeat=profiles["repeat"][1];require(len(repeat)>=1,"no independent repeat")
    c2,r2=repeat[0];lookup={c["case"]:(c,r) for c,r in main};c1,r1=lookup[c2["case"]]
    require(c1["path"]!=c2["path"] and r2["started_at"]>r1["finished_at"],"not a fresh repeat")
    require(r1["comparison"]==r2["comparison"] and r1["counters"]==r2["counters"],"repeat mismatch")
    require(profiles["production"][1][0][1]["comparison"]==profiles["latency2"][1][0][1]["comparison"] and profiles["latency2"][1][0][1]["read_latency"]==2,"RAM latency rerun mismatch")
    protocol=read(ROOT/b["protocol"]);require(protocol["status"]=="PASS","protocol failures");check_hashes(protocol["source_sha256"])
    check_protocol_coverage(protocol)
    for t in protocol["tests"]:
        require(t["status"]=="PASS","failed protocol check")
        if t.get("mutation_detected"):
            r=read(ROOT/t["manifest"]);check_commands(r["commands"]);check_hashes(r["source_sha256"])
            try: check_output((ROOT/t["manifest"]).parent/"output.hex",read((ROOT/t["manifest"]).parent/"expected.json"))
            except ValueError: pass
            else: raise ValueError("RTL mutation not actually detected")
        else:
            validate_case(ROOT/t["manifest"],dense=False)
            check_boundary_evidence(t)
    lint=read(ROOT/b["lint"]);check_commands(lint["commands"]);check_hashes(lint["source_sha256"])
    require(lint["warnings"]==[],"unresolved lint warnings")
    for kind in ("spec","quality"):
        review=read(ROOT/b[kind+"_review"])
        require(review["status"]=="PASS" and review["blocking_findings"]==[],kind+" review incomplete")
        check_hashes(review["source_sha256"])
    check_gate_negative(read(ROOT/b["gate_negative"]))
    return {"status":"READY_FOR_REVIEW","stage":"D0-D2","d0":True,"d1":True,"d2":True,"numeric":True,"micro":True,"full_matrix":True,"full_matrix_cases":36,"independent_repeat":True,"spec_review":True,"quality_review":True,"requirements_met":True,
       "parent_accepted":False,"official_contest_acceptance":False,"source_sha256":b["source_sha256"],"input_manifest_sha256":sha(ROOT/"reports/prototype/vectors/manifest.json"),"output_summary_sha256":{key:sha(ROOT/b[key]) for key in profiles},"evidence":b,"verified_identity":frozen,"verified_inputs":verified,"updated_at":time.time(),
       "not_run":["D3_PLUS","E203_INTEGRATION","OFFICIAL_600","FORMAL_12_PERFORMANCE","MACRO_MAPPING","PRE_POST_SYNTH","STA_150MHZ","AREA_POWER_ENERGY"]}

def main():
    p=argparse.ArgumentParser();p.add_argument("--bundle",type=Path,required=True);p.add_argument("--out",type=Path,required=True);p.add_argument("--publish-status",action="store_true");args=p.parse_args()
    if args.out.exists(): p.error("refusing existing gate output")
    try: result=evaluate(args.bundle);code=0
    except (ValueError,OSError,KeyError,TypeError,subprocess.SubprocessError) as exc: result={"status":"FAIL","error":str(exc),"parent_accepted":False,"official_contest_acceptance":False};code=1
    args.out.parent.mkdir(parents=True,exist_ok=True);args.out.write_text(json.dumps(result,indent=2,allow_nan=False)+"\n",encoding="utf-8")
    if code==0 and args.publish_status: (ROOT/"work/revd/STATUS.json").write_text(json.dumps(result,indent=2,allow_nan=False)+"\n",encoding="utf-8")
    print(json.dumps({"status":result["status"],"error":result.get("error"),"evidence":str(args.out)}));return code

if __name__=="__main__": raise SystemExit(main())
