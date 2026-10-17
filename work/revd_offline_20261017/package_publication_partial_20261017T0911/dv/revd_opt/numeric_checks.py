"""Fresh all-shift arithmetic tests and signed/k63 public-stream edge cases."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
from core_runner import ROOT,run_case
from scripts.revd_offline_common import command,put,sha,run_id,utc
sys.path.insert(0,str(ROOT))
from dv.revd.d1_runner import quant_vectors,oracle,hx,parse_output
import numpy as np

def main():
    out=ROOT/'reports/revd_offline/numeric'/run_id();out.mkdir(parents=True,exist_ok=False)
    tests=[]
    vectors=quant_vectors();vp=out/'quant_vectors.hex'
    vp.write_text(''.join(' '.join([hx(s,48),hx(b,48),hx(sh,6),hx(raw,48),hx(y,32),hx(ov,1),hx(sat,1)])+'\n'
                          for s,b,sh in vectors for raw,y,ov,sat in [oracle(s,b,sh)]),encoding='ascii')
    sources=[ROOT/'rtl/revd/quant_epilogue.sv',ROOT/'dv/revd/d1_quant_tb.sv']
    bound=[*sources,Path(__file__),ROOT/'dv/revd/d1_runner.py']
    source0={str(p.relative_to(ROOT)):sha(p) for p in bound}
    for p in bound:
        dst=out/'unit_source_snapshot'/p.relative_to(ROOT);dst.parent.mkdir(parents=True,exist_ok=True);dst.write_bytes(p.read_bytes())
    cmds=[command(['iverilog','-g2012','-s','d1_quant_tb','-o',out/'quant.vvp',*sources],out/'quant_compile.log')]
    if cmds[0]['exit_code']==0:
        cmds.append(command(['vvp',out/'quant.vvp',f'+VECTORS={vp}',f'+OUTPUT={out/"quant_output.txt"}'],out/'quant_sim.log'))
    ok=len(cmds)==2 and all(c['exit_code']==0 for c in cmds)
    if ok: ok=parse_output(out/'quant_output.txt')==[[i,*oracle(s,b,sh)] for i,(s,b,sh) in enumerate(vectors)]
    tests.append({'name':'quant_all_shifts_extrema_ties_reset','passed':ok,'vectors':len(vectors)})
    x=np.zeros((3,64),dtype=np.int16);w=np.zeros((64,16),dtype=np.int16)
    for shift in range(48):
        half=1<<(shift-1) if shift else 0
        values=[0,1,-1,(1<<47)-1,-(1<<47),(1<<31)-1,-(1<<31)]
        values += [sign*((q<<shift)+half+d) for q in (0,1,2,3) for sign in (-1,1) for d in (-1,0,1)]
        values=[v for v in values if -(1<<47)<=v<(1<<47)]
        b=np.array((values*16)[:16],dtype=np.int64)
        r=run_case(out/f'shift{shift:02d}',x,w,b,shift,latency=1+(shift%2))
        tests.append({'name':f'shift{shift:02d}','passed':r['status']=='PASS','manifest':str((out/f'shift{shift:02d}'/'run_manifest.json').relative_to(ROOT))})
        if r['status']!='PASS': break
    x=np.full((3,64),-32768,dtype=np.int16)
    w=np.tile(np.array([-32768,32767,0,1]*4,dtype=np.int16),(64,1))
    b=np.array([(1<<47)-1,-(1<<47),-5,5]*4,dtype=np.int64)
    for shift in (0,1,16,47):
        r=run_case(out/f'signed_extreme_s{shift}',x,w,b,shift)
        tests.append({'name':f'signed_extreme_s{shift}','passed':r['status']=='PASS','manifest':str((out/f'signed_extreme_s{shift}'/'run_manifest.json').relative_to(ROOT))})
    unchanged=all(sha(ROOT/p)==d for p,d in source0.items())
    result={'status':'PASS' if all(t['passed'] for t in tests) and len(tests)==53 and unchanged else 'FAIL',
            'finished_utc':utc(),'tests':tests,'commands':cmds,'unit_source_sha256':source0,'unit_source_unchanged':unchanged,
            'artifacts':{p.name:sha(p) for p in out.iterdir() if p.is_file()}}
    put(out/'summary.json',result);print(out,result['status'],flush=True)
    return 0 if result['status']=='PASS' else 1
if __name__=='__main__': raise SystemExit(main())
