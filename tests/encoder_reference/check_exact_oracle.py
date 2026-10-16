from pathlib import Path
from fractions import Fraction as Q
from functools import cache
from math import isqrt, factorial
import json, struct
import numpy as np
root=Path('reports/encoder/reference')
manifest=json.loads((root/'manifest.json').read_text(encoding='utf-8'))
def bits(v): return struct.unpack('<I',struct.pack('<f',v))[0]
@cache
def val(b):
    sign=-1 if b>>31 else 1
    e=(b>>23)&255; f=b&0x7fffff
    assert e!=255
    return sign*Q(f if e==0 else f+(1<<23))*Q(2)**(-149 if e==0 else e-150)
def rndint(q):
    sign=-1 if q<0 else 1; n,d=abs(q.numerator),q.denominator
    a,r=divmod(n,d)
    return sign*(a+(2*r>d or (2*r==d and a%2==1)))
def log2(q):
    n,d=q.numerator,q.denominator; e=n.bit_length()-d.bit_length()
    if q<Q(2)**e: e-=1
    return e
@cache
def encode(q,negzero=False):
    if not q:return 0x80000000 if negzero else 0
    sg=0x80000000 if q<0 else 0; q=abs(q); e=log2(q)
    if e < -126:
        f=rndint(q*Q(2)**149)
        return sg|f
    f=rndint(q*Q(2)**(23-e))
    if f==(1<<24):f>>=1;e+=1
    assert e<=127
    return sg|((e+127)<<23)|(f-(1<<23))
def add(a,b):
    z=val(a)+val(b)
    return encode(z,not z and bool((a&b)>>31))
def sub(a,b):return add(a,b^0x80000000)
def mul(a,b):return encode(val(a)*val(b), bool((a^b)>>31))
def div(a,b):return encode(val(a)/val(b),bool((a^b)>>31))
def fma(a,b,c):
    z=val(a)*val(b)+val(c)
    negzero=not z and not val(a)*val(b) and not val(c) and bool(((a^b)&c)>>31)
    return encode(z,negzero)
def sqrt(a):
    q=val(a); assert q>=0
    if not q:return a
    e=log2(q)//2; shift=149 if e < -126 else 23-e
    s=q*Q(2)**(2*shift); n,d=s.numerator,s.denominator
    f=isqrt(n//d)
    t=4*n-d*(2*f+1)**2
    f+=t>0 or (t==0 and f%2==1)
    return encode(Q(f)*Q(2)**(-shift))
Z=bits(0.);ONE=bits(1.)
c=[encode(Q(1,factorial(k))) for k in range(9)]
def exp(a):
    x=val(a);assert x<=0
    if x<=-80:return Z
    if not x:return ONE
    n=rndint(val(mul(a,bits(1.4426950408889634))))
    nf=encode(Q(n));nnf=nf^0x80000000
    r=fma(nnf,bits(.693145751953125),a)
    r=fma(nnf,bits(1.428606765330187e-6),r)
    p=c[8]
    for k in range(7,-1,-1):p=fma(p,r,c[k])
    return mul(p,(n+127)<<23)
def gelu(a):
    x=val(a)
    if abs(x)>=10:return 0x80000000 if a>>31 else a
    aa=mul(a,a);b=mul(aa,a);cc=fma(bits(.044715),b,a)
    u=mul(bits(.7978845608028654),cc);e=exp(mul(bits(-2.),u&0x7fffffff));den=add(ONE,e)
    return div(mul(a,e),den) if a>>31 else div(a,den)
def flat(meta):return np.load(root/meta['npy'],allow_pickle=False).reshape(-1).view(np.uint32).tolist()
def dense(x,w,b,m,inn,out):
    y=[]
    for i in range(m):
        for j in range(out):
            a=Z
            for k in range(inn):a=fma(x[i*inn+k],w[k*out+j],a)
            y.append(add(a,b[j]) if b is not None else a)
    return y

def norm(x,g,b,m,d):
    y=[];id=encode(Q(1,d))
    for i in range(m):
        s=Z
        for a in x[i*d:(i+1)*d]:s=add(s,a)
        mean=mul(s,id);center=[sub(a,mean) for a in x[i*d:(i+1)*d]]
        vs=Z
        for a in center:vs=fma(a,a,vs)
        inv=div(ONE,sqrt(add(mul(vs,id),bits(1e-6))))
        y.extend(fma(mul(a,inv),gg,bb) for a,gg,bb in zip(center,g,b))
    return y
results=[]
for fixture in manifest['fixtures']:
    m,d,h=(fixture[k] for k in ('m','d','h'));w=flat(fixture['weights']);x=flat(fixture['input'])
    ww={e['name']:w[e['offset_words']:e['offset_words']+e['words']] for e in fixture['weight_layout']}
    s={}
    for n in ('q','k','v'):s[n]=dense(x,ww['w'+n],None,m,d,d)
    scores=[];prob=[];context=[]
    for i in range(m):
        row=[]
        for j in range(m):
            a=Z
            for k in range(d):a=fma(s['q'][i*d+k],s['k'][j*d+k],a)
            row.append(mul(a,bits(.125)))
        scores.extend(row);mx=max(row,key=val);p=[exp(sub(a,mx)) for a in row];sm=Z
        for a in p:sm=add(sm,a)
        p=[div(a,sm) for a in p];prob.extend(p)
        for k in range(d):
            a=Z
            for j in range(m):a=fma(p[j],s['v'][j*d+k],a)
            context.append(a)
    s.update(scores=scores,prob=prob,context=context)
    s['attn']=dense(context,ww['wo'],ww['bo'],m,d,d)
    s['r1']=[add(a,b) for a,b in zip(x,s['attn'])]
    s['n1']=norm(s['r1'],ww['ln1_gamma'],ww['ln1_beta'],m,d)
    s['ffn1']=dense(s['n1'],ww['w1'],ww['b1'],m,d,h)
    s['gelu']=[gelu(a) for a in s['ffn1']]
    s['ffn2']=dense(s['gelu'],ww['w2'],ww['b2'],m,h,d)
    s['r2']=[add(a,b) for a,b in zip(s['n1'],s['ffn2'])]
    s['y']=norm(s['r2'],ww['ln2_gamma'],ww['ln2_beta'],m,d)
    mismatches={n:sum(a!=b for a,b in zip(v,flat(fixture['stages'][n]))) for n,v in s.items()}
    print(fixture['name'],json.dumps(mismatches,sort_keys=True),'words=',sum(map(len,s.values())))
    assert not any(mismatches.values())
print('Independent exact-rational binary32 RNE stage check: PASS; no C/libm arithmetic used; no files written.')
