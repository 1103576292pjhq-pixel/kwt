"""Independent fixed-value oracle and immutable-source adapter checks."""
from pathlib import Path
import hashlib
import importlib.util
import subprocess
import pytest

ROOT=Path(__file__).resolve().parents[2]

@pytest.fixture(scope='module')
def vectors(tmp_path_factory):
    folder=tmp_path_factory.mktemp('host-fp32')
    binary=folder/'reference'
    subprocess.run(['gcc','-std=c11','-O0','-frounding-math','-ffp-contract=off',
                    '-fno-fast-math','-fsignaling-nans',str(ROOT/'dv/fp32/host_reference.c'),
                    '-lm','-o',str(binary)],check=True)
    subprocess.run([str(binary),str(folder/'vectors.hex'),'0'],check=True)
    rows={}
    for line in (folder/'vectors.hex').read_text(encoding='utf-8').splitlines():
        values=[int(x,16) for x in line.split()]
        rows.setdefault((values[0],values[1],values[2]),[]).append(values[3:])
    return rows

@pytest.mark.parametrize('op,a,b,y,flags',[
    (0,0x3f800000,0x3f800000,0x40000000,0),
    (1,0x3f800000,0x40000000,0xbf800000,0),
    (2,0x80000000,0x3f800000,0x80000000,0),
    (2,0x7f7fffff,0x40000000,0x7f800000,5),
    (2,0x00000001,0x3f000000,0,3),
    (4,0x3f800000,0,0x7f800000,8),
    (4,0,0,0x7fc00000,16),
    (5,0x80000000,0,0x80000000,0),
    (5,0xbf800000,0,0x7fc00000,16),
    (5,0x40000000,0,0x3fb504f3,1),
    (6,0x3fc00000,0,2,1),
    (6,0x3f000000,0,0,1),
    (6,0xbfc00000,0,0xfffffffe,1),
    (6,0x4f000000,0,0x7fffffff,16),
    (6,0xcf000000,0,0x80000000,0),
    (6,0xcf000001,0,0x80000000,16),
    (6,0x7fc12345,0,0x7fffffff,16),
    (7,0x80000000,0,0xcf000000,0),
    (7,0x00000001,0,0x3f800000,0),
])
def test_host_known_bits_and_flags(vectors,op,a,b,y,flags):
    matches=vectors[(op,a,b)]
    assert all(row[1:]==[y,flags,0] for row in matches)

def test_fma_is_fused(vectors):
    rows=vectors[(3,0x3f800001,0x3f7ffffe)]
    assert [0xbf800000,0xa8800000,0,0] in rows

def test_riscv_inf_zero_fma_invalid_even_with_quiet_nan(vectors):
    rows=vectors[(3,0xff800000,0)]
    assert [0x7fc12345,0x7fc00000,16,0] in rows

def test_all_unknown_opcodes_are_error_nan(vectors):
    for op in range(8,16):
        assert vectors[(op,0x3f800000,0)]==[[0,0x7fc00000,0,1]]

def test_compatibility_copy_changes_only_redundant_net(tmp_path):
    spec=importlib.util.spec_from_file_location('hardfloat_sources',ROOT/'dv/fp32/hardfloat_sources.py')
    helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
    original=ROOT/'vendor/HardFloat-1-upstream/source/divSqrtRecFN_small.v'
    raw=original.read_bytes();prior=hashlib.sha256(raw).hexdigest()
    selected=helper.prepare(tmp_path)
    changed=[p for p in selected if p.parent==tmp_path]
    assert len(changed)==1
    expected=raw.replace(b'    wire sqrtOpOut;',b'    // Redundant ANSI output net declaration removed for Icarus compatibility.')
    assert changed[0].read_bytes()==expected
    assert hashlib.sha256(original.read_bytes()).hexdigest()==prior
    assert b'Copyright 2019 The Regents of the University of California.' in expected
