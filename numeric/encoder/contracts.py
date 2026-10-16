"""Shared file-format metadata, without neural computation."""
import hashlib
import json
from pathlib import Path
import numpy as np

STAGES = ('q','k','v','scores','prob','context','attn','r1','n1','ffn1','gelu','ffn2','r2','y')


def layout(d=64, h=256):
    shapes = [('wq',(d,d)),('wk',(d,d)),('wv',(d,d)),('wo',(d,d)),
              ('bo',(d,)),('ln1_gamma',(d,)),('ln1_beta',(d,)),
              ('w1',(d,h)),('b1',(h,)),('w2',(h,d)),('b2',(d,)),
              ('ln2_gamma',(d,)),('ln2_beta',(d,))]
    offset=0
    result=[]
    for name,shape in shapes:
        words=int(np.prod(shape))
        result.append({'name':name,'shape':list(shape),'offset_words':offset,'words':words})
        offset+=words
    return result


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_write(path, value):
    path=Path(path)
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(json.dumps(value,indent=2,sort_keys=True,ensure_ascii=False)+'\n',encoding='utf-8')


def write_array(root, relative, array):
    root=Path(root)
    array=np.ascontiguousarray(array,dtype='<f4')
    if not np.isfinite(array).all():
        raise ValueError('nonfinite array: '+str(relative))
    base=root/relative
    base.parent.mkdir(parents=True,exist_ok=True)
    np.save(str(base)+'.npy',array,allow_pickle=False)
    bits=array.reshape(-1).view('<u4')
    Path(str(base)+'.hex').write_text(''.join('{:08x}\n'.format(int(v)) for v in bits),encoding='ascii')
    Path(str(base)+'.bin').write_bytes(array.tobytes())
    return {'shape':list(array.shape),'dtype':'float32','words':int(array.size),
            'npy':str(relative)+'.npy','npy_sha256':sha(str(base)+'.npy'),
            'hex':str(relative)+'.hex','hex_sha256':sha(str(base)+'.hex'),
            'bin':str(relative)+'.bin','bits_sha256':sha(str(base)+'.bin')}


def metrics(actual, expected):
    a=np.asarray(actual,np.float64)
    e=np.asarray(expected,np.float64)
    if a.shape!=e.shape or not np.isfinite(a).all() or not np.isfinite(e).all():
        raise ValueError('shape/nonfinite comparison')
    delta=a-e
    rmse=float(np.sqrt(np.mean(delta*delta)))
    denom=max(float(np.sqrt(np.mean(e*e))),1e-8)
    return {'nrmse':rmse/denom,'rmse':rmse,'max_abs':float(np.max(np.abs(delta))),
            'bit_equal':bool(np.array_equal(np.asarray(actual,np.float32).view(np.uint32),
                                           np.asarray(expected,np.float32).view(np.uint32)))}
