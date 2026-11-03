"""共享内存的数据对象布局；不假定官方共享基址或物理SRAM型号。"""
from collections.abc import Mapping

import numpy as np

from .fixed_numeric import M, K, N, _task_arrays


def pack_inputs(x, w, bias):
    """X行主序、W列主序、bias符号扩展int64，全部小端。"""
    x, w, bias = _task_arrays(x, w, bias)
    return {'x': x.astype('<i2').tobytes(order='C'),
            'w': w.T.astype('<i2').tobytes(order='C'),
            'bias': bias.astype('<i8').tobytes(order='C')}


def _payloads(packed, sizes):
    if not isinstance(packed, Mapping) or set(packed) != set(sizes):
        raise ValueError('payload keys differ from the required data objects')
    result = {}
    for name, size in sizes.items():
        if not isinstance(packed[name], (bytes, bytearray, memoryview)):
            raise TypeError(f'{name} payload must be bytes-like')
        data = bytes(packed[name])
        if len(data) != size:
            raise ValueError(f'{name} payload must contain exactly {size} bytes')
        result[name] = data
    return result


def unpack_inputs(packed):
    """从共享容器取输入；bias64必须在窄化前检查signed32范围。"""
    packed = _payloads(packed, {'x': M * K * 2, 'w': K * N * 2, 'bias': N * 8})
    x = np.frombuffer(packed['x'], dtype='<i2').reshape(M, K).astype(np.int16)
    w = np.frombuffer(packed['w'], dtype='<i2').reshape(N, K).T.astype(np.int16)
    wide_bias = np.frombuffer(packed['bias'], dtype='<i8')
    if np.any(wide_bias < -2147483648) or np.any(wide_bias > 2147483647):
        raise ValueError('shared int64 bias is not a legal signed32 value')
    return x, w, wide_bias.astype(np.int32)


def _output_arrays(y, flags):
    y, flags = np.asarray(y), np.asarray(flags)
    if y.dtype != np.dtype(np.int16) or flags.dtype != np.dtype(np.uint8):
        raise TypeError('Y must be int16 and flags must be uint8')
    if y.shape != (M, N) or flags.shape != (M, N):
        raise ValueError('output shapes must both be [99,256]')
    if np.any(flags & np.uint8(0xf9)):
        raise ValueError('full-task flags have reserved bits or impossible raw overflow')
    last = (flags & np.uint8(4)) != 0
    if np.count_nonzero(last) != 1 or not last[-1, -1]:
        raise ValueError('global last must occur only at Y[98,255]')
    return y, flags


def pack_outputs(y, flags):
    """Y16在边界符号扩展为int32；flags保持一项一字节。"""
    y, flags = _output_arrays(y, flags)
    return {'y': y.astype('<i4').tobytes(order='C'), 'flags': flags.tobytes(order='C')}


def unpack_outputs(packed):
    """检查Y32是否真为signed16符号扩展，再检查任务flags。"""
    packed = _payloads(packed, {'y': M * N * 4, 'flags': M * N})
    wide_y = np.frombuffer(packed['y'], dtype='<i4')
    if np.any(wide_y < -32768) or np.any(wide_y > 32767):
        raise ValueError('shared Y32 is not a signed16 sign extension')
    y = wide_y.reshape(M, N).astype(np.int16)
    flags = np.frombuffer(packed['flags'], dtype=np.uint8).reshape(M, N).copy()
    return _output_arrays(y, flags)
