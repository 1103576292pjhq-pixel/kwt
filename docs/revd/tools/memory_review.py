"""Capacity / port / vector-prefetch explorer. NOT SRAM characterization or RTL.

All macro examples assume 16-bit, single-port synchronous banks. No area,
power or official macro-pin model is supplied. Latency counts abstract events.
"""
from __future__ import annotations
from dataclasses import dataclass
import argparse, json, math
from pathlib import Path


def positive_int(x: int, name: str) -> int:
    if type(x) is not int or x < 1:
        raise ValueError(f'{name} must be a positive integer')
    return x


def cover_words(words: int, objective: str = 'capacity') -> dict:
    positive_int(words, 'words')
    if objective not in ('capacity', 'macro_count'):
        raise ValueError('objective must be capacity or macro_count')
    candidates = []
    # Exact small search over specified depths; one-bank capacity only.
    for a in range(math.ceil(words / 4096) + 1):
        for b in range(math.ceil(words / 1024) + 1):
            c = max(0, math.ceil((words - 4096*a - 1024*b) / 128))
            allocated = 4096*a + 1024*b + 128*c
            if allocated >= words:
                candidates.append((allocated, a+b+c, a, b, c))
    best = min(candidates, key=lambda t: (t[0],t[1]) if objective=='capacity' else (t[1],t[0]))
    allocated,count,a,b,c = best
    return dict(words=words, allocated_words=allocated, macros=count,
                by_depth={'4096':a,'1024':b,'128':c}, objective=objective,
                area_mm2=None, power_w=None)


def x_location(row: int, k: int, banks: int) -> tuple[int,int]:
    if type(row) is not int or not 0 <= row < 99 or type(k) is not int or not 0 <= k < 64:
        raise ValueError('invalid X coordinates')
    if banks not in (2,4):
        raise ValueError('example supports 2 or 4 banks')
    return row % banks, (row // banks)*64+k


def prefetch(vectors: int=64, banks: int=2, latency: int=2,
             rows: int=4, groups: int=4, stall_period: int=0) -> dict:
    """Two tagged X vector registers; at most one read per bank per cycle.

    Arrivals at cycle t become visible before that cycle's consumption.
    A released vector slot can be reserved on the NEXT cycle only.
    W/accumulator/epilogue latency is deliberately not modeled.
    """
    for name,value in [('vectors',vectors),('latency',latency),('rows',rows),('groups',groups)]:
        positive_int(value,name)
    if banks not in (1,2,4) or rows>4 or type(stall_period) is not int or stall_period<0:
        raise ValueError('unsupported prefetch parameters')
    if stall_period == 1:
        raise ValueError('stall every cycle provides no fairness')
    slots = [None,None]
    pending = []
    next_load=0; expected=0; active=None; g=0; now=0
    starts=[]; reads=0; issues=0; stalls=0; max_outstanding=0; checked=0
    while expected < vectors:
        if now > vectors*(latency+groups+32)*8:
            raise RuntimeError('prefetch progress watchdog')
        remaining=[]
        for due,si,tag,r in pending:
            if due == now:
                s=slots[si]
                if s is None or s['k']!=tag or r in s['data']:
                    raise AssertionError('late/duplicate/stale return')
                s['data'][r] = (tag,r)
            else:
                remaining.append((due,si,tag,r))
        pending=remaining
        if active is None:
            for si,s in enumerate(slots):
                if s is not None and s['k']==expected and len(s['data'])==rows:
                    active=si; g=0; starts.append(now); break
        if next_load<vectors:
            free=next((si for si,s in enumerate(slots) if s is None),None)
            if free is not None:
                slots[free]={'k':next_load,'issued':set(),'data':{}}
                next_load+=1
        used=set()
        for si,s in enumerate(slots):
            if s is None: continue
            for r in range(rows):
                b=r%banks
                if r not in s['issued'] and b not in used:
                    used.add(b);s['issued'].add(r)
                    pending.append((now+latency,si,s['k'],r));reads+=1
        max_outstanding=max(max_outstanding,len(pending))
        block=stall_period>0 and now%stall_period==0
        if active is not None and not block:
            s=slots[active]
            if s is None or s['k']!=expected or len(s['data'])!=rows:
                raise AssertionError('consumed incomplete vector')
            for r in range(rows):
                if s['data'][r]!=(expected,r):raise AssertionError('wrong operand identity')
                checked+=1
            issues+=1;g+=1
            if g==groups:
                if any(si==active for _,si,_,_ in pending):
                    raise AssertionError('freed slot with in-flight read')
                slots[active]=None;active=None;expected+=1
        elif active is None or block:
            stalls+=1
        now+=1
    if pending or any(s is not None for s in slots):raise AssertionError('not drained')
    return dict(scope='ABSTRACT_X_PREFETCH_ONLY_NOT_RTL_TIMING', vectors=vectors,
                rows=rows,banks=banks,read_latency=latency,groups=groups,
                elapsed_abstract_cycles=now,issue_slots=issues,x_scalar_reads=reads,
                operand_identity_checks=checked,first_vector_cycle=starts[0],
                post_start_nonissue_cycles=now-starts[0]-issues,
                max_outstanding=max_outstanding,
                gaps_between_vector_starts=sorted(set(b-a for a,b in zip(starts,starts[1:]))))


def examples() -> dict:
    return {
        'scope':'CAPACITY_AND_ABSTRACT_PREFETCH_NOT_PHYSICAL_PPA',
        'one_int16_feature_bytes':99*64*2,
        'two_4096_macros_bytes':2*4096*2,
        'x_and_y_int16_bytes':2*99*64*2,
        'ffn1_int32_output_bytes':99*256*4,
        'x4_capacity_min_per_bank':cover_words(1600,'capacity'),
        'x4_fewer_macros_per_bank':{'macros':2,'allocated_words':2048,'by_depth':{'1024':2}},
        'xp2_per_bank':cover_words(3200,'macro_count'),
        'bulk_candidate_x4':{'x_macros':8,'w_macros':16,'y_macros':4,'total_macros':28,'allocated_bytes':21504},
        'bulk_candidate_xp2':{'x_macros':2,'w_macros':16,'y_macros':4,'total_macros':22,'allocated_bytes':21504},
        'exclusions':['bias','flags','accumulators','snapshot','FIFO','control','macro_pin_timing','area','power'],
        'prefetch':[prefetch(banks=b,latency=l) for b in (2,4) for l in (1,2)],
    }


def main() -> int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--out',type=Path,help='New directory; never overwrite')
    a=p.parse_args()
    try:
        report=examples();print(json.dumps(report,indent=2,ensure_ascii=False))
        if a.out:
            a.out.mkdir(parents=True,exist_ok=False)
            (a.out/'memory_review.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
        return 0
    except (ValueError,OSError) as e:p.error(str(e));return 2
if __name__=='__main__':raise SystemExit(main())
