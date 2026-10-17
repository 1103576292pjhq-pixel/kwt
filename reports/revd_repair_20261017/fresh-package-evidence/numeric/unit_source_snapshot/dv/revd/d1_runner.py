"""Actual Icarus D1 arithmetic/protocol checks; artifacts are never overwritten."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import random
import subprocess
import sys
import time
import uuid

ROOT=Path(__file__).resolve().parents[2]
sys.dont_write_bytecode=True
sys.path.insert(0,str(ROOT))
from numeric.fixedpoint import saturate_signed, rshift_rne, dot64_reference

def digest(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def put(path,value): Path(path).write_text(json.dumps(value,indent=2)+"\n",encoding="utf-8")
def hx(value,bits): return f"{value & ((1<<bits)-1):0{(bits+3)//4}x}"
def oracle(total,bias,shift):
    # Standalone arithmetic, checked against the frozen scalar helpers.
    add=total+bias
    raw=max(-(1<<47),min((1<<47)-1,add))
    magnitude=abs(raw)
    quo,rem=divmod(magnitude,1<<shift)
    if shift and (rem>(1<<(shift-1)) or (rem==(1<<(shift-1)) and quo&1)): quo+=1
    rounded=-quo if raw<0 else quo
    y=max(-(1<<31),min((1<<31)-1,rounded))
    assert raw==saturate_signed(add,48) and rounded==rshift_rne(raw,shift)
    return raw,y,int(raw!=add),int(y!=rounded)

def quant_vectors():
    vectors=[]
    endpoints=[-(1<<47),-(1<<47)+1,-(1<<31)-1,-(1<<31),-1,0,1,(1<<31)-1,(1<<31),(1<<47)-2,(1<<47)-1]
    for shift in range(48):
        for value in endpoints: vectors.append((value,0,shift))
        for value,bias in [((1<<47)-1,1),(-(1<<47),-1),((1<<47)-1,(1<<47)-1),(-(1<<47),-(1<<47)),(0,(1<<47)-1),(0,-(1<<47))]: vectors.append((value,bias,shift))
        if shift:
            for q in range(4):
                for sign in (-1,1):
                    for offset in (-1,0,1):
                        value=sign*((q<<shift)+(1<<(shift-1))+offset)
                        if -(1<<47)<=value<(1<<47): vectors.append((value,0,shift))
    rng=random.Random(0xD100)
    for _ in range(256): vectors.append((rng.randrange(-(1<<47),1<<47),rng.randrange(-(1<<47),1<<47),rng.randrange(48)))
    return vectors

def command(args,folder,label,timeout=120):
    started=time.time()
    try:
        p=subprocess.run(list(map(str,args)),cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=timeout)
        code=p.returncode; output=p.stdout
    except subprocess.TimeoutExpired as exc:
        code=124; output=str(exc.stdout or "")+"\nTIMEOUT"
    (folder/f"{label}.log").write_text(output,encoding="utf-8")
    return {"command":list(map(str,args)),"exit_code":code,"seconds":time.time()-started,"log":str((folder/f"{label}.log").relative_to(ROOT))}

def micro_vectors(pm,pn):
    rng=random.Random(0xD140+pm)
    cases=[]; records=[]
    for case in range(18):
        xs=[[rng.randrange(-32768,32768) for _ in range(pm)] for _ in range(64)]
        ws=[[rng.randrange(-32768,32768) for _ in range(pn)] for _ in range(64)]
        biases=[rng.randrange(-(1<<40),1<<40) for _ in range(pn)]
        shift=[0,1,3,7,31,47][case%6]
        mask=[(1<<pm)-1,1,(1<<max(1,pm-1))-1,2 if pm==2 else 10][case%4]
        if case==0:
            xs=[[0]*pm for _ in range(64)]; ws=[[0]*pn for _ in range(64)];biases=[0]*pn
        elif case==1:
            xs=[[32767 if k%2==0 else -32767 for _ in range(pm)] for k in range(64)]
            ws=[[32767]*pn for _ in range(64)];biases=[-3,3,-5,5][:pn]
        elif case==2:
            xs=[[0]*pm for _ in range(63)]+[[(-32768+r) for r in range(pm)]]
            ws=[[0]*pn for _ in range(63)]+[[32767-c for c in range(pn)]]
            biases=[0]*pn
        elif case in (3,4):
            xs=[[-32768]*pm for _ in range(64)]
            ws=[[-32768 if case==3 else 32767]*pn for _ in range(64)]
            biases=[(1<<47)-1 if case==3 else -(1<<47)]*pn
        expected=[]
        for r in range(pm):
            for c in range(pn):
                vecx=[xs[k][r] for k in range(64)]; vecw=[ws[k][c] for k in range(64)]
                result=oracle(sum(a*b for a,b in zip(vecx,vecw)),biases[c],shift)
                golden=dot64_reference(vecx,vecw,biases[c],shift)
                assert result==(golden.raw,golden.output,int(golden.overflow),int(golden.output_saturated))
                expected.append(result)
                if mask&(1<<r):
                    last=r==max(ri for ri in range(pm) if mask&(1<<ri)) and c==pn-1
                    records.append([case,r,c,*result,int(last)])
        lines=[f"{case+0xABC000:08x} {mask:x} {shift:x}"]
        lines.extend(hx(b,48) for b in biases)
        for k in range(64): lines.extend(hx(x,16) for x in xs[k]+ws[k])
        lines.extend(" ".join([hx(raw,48),hx(y,32),hx(ov,1),hx(sat,1)]) for raw,y,ov,sat in expected)
        cases.append("\n".join(lines))
    return str(len(cases))+"\n"+"\n".join(cases)+"\n",records

def parse_output(path,micro=False):
    rows=[]
    for line in Path(path).read_text(encoding="ascii").splitlines():
        words=line.split()
        assert len(words)==(8 if micro else 5),"bad output width"
        assert all(all(ch in "0123456789abcdefABCDEF" for ch in word) for word in words),"unknown/nonhex output"
        if micro:
            case,r,c=map(int,words[:3]);raw=int(words[3],16);y=int(words[4],16)
            flags=list(map(int,words[5:]));head=[case,r,c]
        else:
            head=[int(words[0])];raw=int(words[1],16);y=int(words[2],16);flags=list(map(int,words[3:]))
        if raw&(1<<47): raw-=1<<48
        if y&(1<<31): y-=1<<32
        rows.append(head+[raw,y]+flags)
    return rows

def run_micro(folder,manifest):
    manifest["micro_runs"]=[]
    micro_sources=[ROOT/"rtl/revd/micro_tile.sv",ROOT/"rtl/revd/quant_epilogue.sv",ROOT/"dv/revd/d1_micro_tb.sv"]
    lane=ROOT/"rtl/revd/mac_lane.sv"
    if lane.exists(): micro_sources.insert(0,lane)
    for path in micro_sources:
        manifest["sources"][str(path.relative_to(ROOT))]=digest(path)
        if path.suffix==".sv": (folder/(path.stem+".source.sv")).write_bytes(path.read_bytes())
    for pm in (4,2):
        text,expected=micro_vectors(pm,4)
        vp=folder/f"micro_pm{pm}.hex";vp.write_text(text,encoding="ascii")
        exe=folder/f"micro_pm{pm}.vvp"
        c=command(["iverilog","-g2012","-s","d1_micro_tb",f"-Pd1_micro_tb.PM={pm}","-o",exe,*micro_sources],folder,f"micro_pm{pm}_compile");manifest["commands"].append(c)
        passed=False
        if c["exit_code"]==0:
            c=command(["vvp",exe,f"+VECTORS={vp}",f"+OUTPUT={folder/f'micro_pm{pm}_output.txt'}"],folder,f"micro_pm{pm}_simulate");manifest["commands"].append(c)
            log=(folder/f"micro_pm{pm}_simulate.log").read_text()
            passed=c["exit_code"]==0 and "D1_MICRO_PASS" in log
            if passed:
                try: passed=parse_output(folder/f"micro_pm{pm}_output.txt",micro=True)==expected
                except (OSError,ValueError,AssertionError): passed=False
            if c["exit_code"]!=0 and "MICRO" in log: manifest["functional_red"]=True
        manifest["micro_runs"].append({"pm":pm,"pn":4,"passed":passed,"case_count":18,"expected_outputs":len(expected)})
        if not passed: break
    manifest["micro_passed"]=len(manifest["micro_runs"])==2 and all(x["passed"] for x in manifest["micro_runs"])

def mutations_and_lint(folder,manifest):
    manifest["mutations"]=[]
    sources=[ROOT/"rtl/revd/mac_lane.sv",ROOT/"rtl/revd/quant_epilogue.sv",ROOT/"rtl/revd/micro_tile.sv"]
    for pm in (4,2):
        c=command(["verilator","--lint-only","--timing","-Wall","--top-module","micro_tile",f"-GPM={pm}",*sources],folder,f"lint_pm{pm}");manifest["commands"].append(c)
        if c["exit_code"]!=0: manifest["lint_passed"]=False;return
    manifest["lint_passed"]=True
    specs=[
        ("omit_k63",0,"if(product_valid) sum", "if(product_valid && product_k != 6'd63) sum", "MICRO numeric"),
        ("unsigned_product",0,"$signed(in_x)*$signed(in_w)","$unsigned(in_x)*$unsigned(in_w)","MICRO numeric"),
        ("done_without_handshake",2,"QWAIT: if(out_valid&&out_ready)","QWAIT: if(out_valid)","MICRO blocked payload changed"),
        ("confuse_flags",1,"out_overflow <= overflow; out_saturated <= saturated;","out_overflow <= saturated; out_saturated <= overflow;","NUMERIC vector="),
    ]
    for name,index,before,after,reason in specs:
        text=sources[index].read_text(); assert text.count(before)==1
        mutant=folder/f"mutant_{name}.sv";mutant.write_text(text.replace(before,after),encoding="utf-8")
        actual=sources.copy();actual[index]=mutant
        quant=name=="confuse_flags"
        top="d1_quant_tb" if quant else "d1_micro_tb"
        compilation=[actual[1],ROOT/"dv/revd/d1_quant_tb.sv"] if quant else [*actual,ROOT/"dv/revd/d1_micro_tb.sv"]
        exe=folder/f"mutant_{name}.vvp"
        c=command(["iverilog","-g2012","-s",top,"-o",exe,*compilation],folder,f"mutant_{name}_compile");manifest["commands"].append(c)
        result={"name":name,"kind":"RTL_compile_and_simulate","source_sha256":digest(mutant),"detected":False,"compile_exit_code":c["exit_code"]}
        if c["exit_code"]==0:
            vector=folder/("quant_vectors.hex" if quant else "micro_pm4.hex")
            c=command(["vvp",exe,f"+VECTORS={vector}",f"+OUTPUT={folder/f'mutant_{name}_output.txt'}"],folder,f"mutant_{name}_simulate");manifest["commands"].append(c)
            log=(folder/f"mutant_{name}_simulate.log").read_text()
            result.update({"simulate_exit_code":c["exit_code"],"detected":c["exit_code"]!=0 and reason in log,"expected_failure":reason})
        manifest["mutations"].append(result)
    manifest["mutations_passed"]=all(x["detected"] for x in manifest["mutations"])

def main():
    ap=argparse.ArgumentParser(); ap.add_argument("--phase",choices=["red","green"],required=True); ap.add_argument("--run-id"); ap.add_argument("--quant-only",action="store_true");ap.add_argument("--micro-only",action="store_true"); args=ap.parse_args()
    run_id=args.run_id or time.strftime("%Y%m%d-%H%M%S")+"-"+uuid.uuid4().hex[:8]
    folder=ROOT/"reports/revd/d1"/args.phase/run_id; folder.mkdir(parents=True,exist_ok=False)
    vectors=quant_vectors(); vp=folder/"quant_vectors.hex"
    vp.write_text("".join(" ".join([hx(s,48),hx(b,48),hx(sh,6),hx(raw,48),hx(y,32),hx(ov,1),hx(sat,1)])+"\n" for s,b,sh in vectors for raw,y,ov,sat in [oracle(s,b,sh)]),encoding="ascii")
    manifest={"stage":"D1","phase":args.phase,"run_id":run_id,"commands":[],"quant_vector_count":len(vectors),"golden_sha256":digest(ROOT/"numeric/fixedpoint.py"),"sources":{},"passed":False}
    sources=[ROOT/"rtl/revd/quant_epilogue.sv",ROOT/"dv/revd/d1_quant_tb.sv",Path(__file__)]
    for path in sources: manifest["sources"][str(path.relative_to(ROOT))]=digest(path)
    (folder/"quant_epilogue.source.sv").write_bytes(sources[0].read_bytes())
    exe=folder/"quant.vvp"
    c={"exit_code":-1}
    if not args.micro_only:
        c=command(["iverilog","-g2012","-s","d1_quant_tb","-o",exe,*sources[:2]],folder,"quant_compile"); manifest["commands"].append(c)
    if c["exit_code"]==0:
        c=command(["vvp",exe,f"+VECTORS={vp}",f"+OUTPUT={folder/'quant_output.txt'}"],folder,"quant_simulate");manifest["commands"].append(c)
        manifest["quant_passed"]=c["exit_code"]==0 and "D1_QUANT_PASS" in (folder/"quant_simulate.log").read_text()
        if manifest["quant_passed"]:
            try: manifest["quant_passed"]=parse_output(folder/"quant_output.txt")==[[i,*oracle(s,b,sh)] for i,(s,b,sh) in enumerate(vectors)]
            except (OSError,ValueError,AssertionError): manifest["quant_passed"]=False
        manifest["functional_red"]=c["exit_code"]!=0 and "NUMERIC vector=" in (folder/"quant_simulate.log").read_text()
    if args.micro_only or (args.phase=="green" and manifest.get("quant_passed") and not args.quant_only):
        run_micro(folder,manifest)
    manifest["passed"]=(args.micro_only or bool(manifest.get("quant_passed"))) and (args.quant_only or bool(manifest.get("micro_passed")))
    if args.phase=="green" and manifest["passed"] and not args.quant_only and not args.micro_only:
        mutations_and_lint(folder,manifest)
        manifest["passed"]=manifest.get("lint_passed",False) and manifest.get("mutations_passed",False)
    manifest["artifacts"]={str(p.relative_to(ROOT)):digest(p) for p in folder.iterdir() if p.is_file()}
    put(folder/"run_manifest.json",manifest)
    print(json.dumps({"manifest":str((folder/"run_manifest.json").relative_to(ROOT)),"passed":manifest["passed"],"functional_red":manifest.get("functional_red",False)}))
    return 0 if (manifest["passed"] if args.phase=="green" else manifest.get("functional_red")) else 1

if __name__=="__main__": sys.exit(main())
