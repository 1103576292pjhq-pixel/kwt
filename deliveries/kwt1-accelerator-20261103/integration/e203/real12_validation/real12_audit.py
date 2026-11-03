"""Portable response audit: standard library only, shared locally and on VCS."""
import hashlib
import math


def audit_result_trace(path, expected, references):
    if not expected or len(expected) != len(references):
        raise ValueError('Expected tasks and references differ')
    size = 99*256
    if any(len(a) != size for a in expected) or any(len(a) != size for a in references):
        raise ValueError('Wrong result/reference dimensions')
    if any(not math.isfinite(float(v)) for row in references for v in row):
        raise ValueError('Non-finite reference')
    seen = [bytearray(size) for _ in expected]
    sums = [dict(sse=0.,energy=0.,absolute=0.,maximum=0.,count=0,last=0,sat=0,overflow=0) for _ in expected]
    for line_number,line in enumerate(path.read_text(encoding='ascii').splitlines(),1):
        fields=line.split()
        if len(fields)!=4 or fields[0]!='R':
            raise ValueError('Malformed trace line %d'%line_number)
        task,index,word=int(fields[1]),int(fields[2]),int(fields[3],16)
        if not 0<=task<len(expected) or not 0<=index<size or not 0<=word<2**32:
            raise ValueError('Trace task/index/value out of range at line %d'%line_number)
        if seen[task][index]:
            raise ValueError('duplicate trace output task=%d index=%d'%(task,index))
        if word != int(expected[task][index]):
            raise ValueError('result mismatch task=%d index=%d actual=%08x expected=%08x'%
                             (task,index,word,int(expected[task][index])))
        seen[task][index]=1
        signed=word&65535
        if signed&32768: signed-=65536
        actual=signed/4096.
        reference=float(references[task][index])
        error=actual-reference
        total=sums[task]
        total['sse']+=error*error;total['energy']+=reference*reference
        total['absolute']+=abs(error);total['maximum']=max(total['maximum'],abs(error))
        total['count']+=1;total['last']+=bool(word&(4<<16))
        total['sat']+=bool(word&(2<<16));total['overflow']+=bool(word&(1<<16))
    results=[]
    for task,total in enumerate(sums):
        if total['count']!=size or not all(seen[task]):
            raise ValueError('missing outputs task=%d count=%d'%(task,total['count']))
        rmse=math.sqrt(total['sse']/size)
        nrmse=rmse/max(math.sqrt(total['energy']/size),1e-8)
        if not math.isfinite(nrmse): raise ValueError('Non-finite result error')
        results.append(dict(layer=task+1,outputs=size,nrmse=nrmse,nrmse_percent=100*nrmse,
                            within_3_percent=nrmse<=.03,rmse=rmse,mae=total['absolute']/size,
                            max_abs_error=total['maximum'],last_flags=total['last'],
                            output_saturations=total['sat'],raw_overflows=total['overflow']))
    return dict(outputs=sum(row['count'] for row in sums),tasks=results,
                bit_mismatches=0,all_tasks_within_3_percent=all(row['within_3_percent'] for row in results),
                max_task_nrmse_percent=max(row['nrmse_percent'] for row in results),
                trace_sha256=hashlib.sha256(path.read_bytes()).hexdigest())
