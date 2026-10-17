"""FUTURE-EXTENSION numerical example; does not extend the current K=64 core.

Segment boundaries must not add bias, round, saturate or reset partial sums.
This example uses signed16 inputs and K<=256 only; softmax probability types
and mixed-precision activations require a separate contract.
"""
from __future__ import annotations
from core_model import bounded, finalize, valid_shift


def segmented_dot(x:list[int],w:list[int],bias:int,shift:int,chunk:int=64):
    if len(x)!=len(w) or not 1<=len(x)<=256:raise ValueError('expected equal lengths 1..256')
    if type(chunk) is not int or chunk<1:raise ValueError('invalid chunk size')
    bounded(bias,48,'bias');valid_shift(shift)
    a=[bounded(v,16,'x') for v in x];b=[bounded(v,16,'w') for v in w]
    acc=0
    for start in range(0,len(a),chunk):
        for k in range(start,min(start+chunk,len(a))):acc+=a[k]*b[k]
        bounded(acc,48,'unfinalized partial sum')
    return finalize(acc,bias,shift)


def worst_case_sum_bits(k:int)->int:
    if type(k) is not int or not 1<=k<=256:raise ValueError('invalid k')
    # Positive maximum is exactly K*2**30, so reserve its sign bit too.
    return (k*(1<<30)).bit_length()+1
