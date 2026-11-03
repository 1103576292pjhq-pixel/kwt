"""Catch wrong signed generation, closed form, RNE and saturation independently."""
import ctypes as c
from pathlib import Path
import subprocess
import sys
import tempfile
import numpy as np

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE.parents[2]))
from model.fixed_numeric import ffn1_int16, convert_accumulator


def main():
    assert (HERE / "fixture.c").exists(), "Missing C fixture/reference implementation"
    with tempfile.TemporaryDirectory(prefix="kwt-numeric-") as tmp:
        so = Path(tmp) / "fixture.so"
        subprocess.run(["gcc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                        str(HERE / "fixture.c"), "-o", str(so)], check=True)
        lib = c.CDLL(str(so))
        lib.fixture_x.argtypes = [c.c_uint, c.c_uint]
        lib.fixture_x.restype = c.c_int
        lib.fixture_w.argtypes = [c.c_uint, c.c_uint]
        lib.fixture_w.restype = c.c_int
        lib.fixture_bias.argtypes = [c.c_uint]
        lib.fixture_bias.restype = c.c_int
        lib.fixture_expected.argtypes = [c.c_uint, c.c_uint]
        lib.fixture_expected.restype = c.c_uint
        lib.fixture_convert.argtypes = [c.c_int64, c.c_uint]
        lib.fixture_convert.restype = c.c_uint
        # Independently specify inputs: do not call C generators to build gold.
        x = np.array([[((r-49)*8 + 2*k-63)*8 for k in range(64)]
                      for r in range(99)], dtype=np.int16)
        w = np.array([[(32767 if col == 0 else -32768 if col == 1 else
                       0 if col < 8 else ((col-128)*8+k-32)*8)
                      for col in range(256)] for k in range(64)], dtype=np.int16)
        special = [0, 0, 98304, -98304, 32768, -32768, 163840, -163840]
        bias = np.array([special[col] if col < 8 else (col-128)*1024+32736
                         for col in range(256)], dtype=np.int32)
        for r in range(99):
            for k in range(64):
                assert lib.fixture_x(r, k) == int(x[r, k]), (r, k)
        for k in range(64):
            for col in range(256):
                assert lib.fixture_w(k, col) == int(w[k, col]), (k, col)
        for col in range(256):
            assert lib.fixture_bias(col) == int(bias[col]), col
        y, flags = ffn1_int16(x, w, bias)
        for r in range(99):
            for col in range(256):
                want = (int(y[r, col]) & 65535) | int(flags[r, col]) << 16
                got = lib.fixture_expected(r, col)
                assert got == want, (r, col, hex(got), hex(want))
        # Upper/lower saturation and both tie parity cases, including negatives.
        cases = [0, 32767, 32768, 32769, 98304, 163840, -32768, -32769,
                 -98304, -163840, 2147450880, 2147483648, -2147516416,
                 6500000000, -6500000000]
        for raw in cases:
            for last in (False, True):
                converted = convert_accumulator(raw, 0, is_last=last)
                want = (converted.y & 65535) | converted.flags << 16
                assert lib.fixture_convert(raw, last) == want, (raw, last)
        assert np.any(y > 0) and np.any(y < 0)
        saturated = int(np.count_nonzero(flags & 2))
        assert saturated > 0
        assert int(np.count_nonzero(flags & 4)) == 1
        print(f"PASS C_NUMERIC outputs=25344 conversion_cases={len(cases)*2} saturated={saturated}")


if __name__ == "__main__":
    main()
