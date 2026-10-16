"""Inspect the first hand-computed transaction in a plain VCD artifact."""
from pathlib import Path


def inspect_first_result(path: Path):
    ids = {}
    widths = {}
    values = {}
    before = {}
    now = 0
    accepted = 0

    def number(name):
        bits = values.get(ids[name], "x")
        if "x" in bits.lower() or "z" in bits.lower():
            return None
        return int(bits, 2)

    def signed_number(name):
        value = number(name)
        if value is None:
            return None
        return value - (1 << widths[name]) if value & (1 << (widths[name] - 1)) else value

    def finish_timestamp():
        nonlocal accepted
        if not ids or "clk" not in ids:
            return None
        if before.get(ids["clk"]) == "0" and values.get(ids["clk"]) == "1":
            if (before.get(ids["rst_n"]) == "1" and
                    before.get(ids["in_valid"]) == "1" and
                    before.get(ids["in_ready"]) == "1"):
                accepted += 1
        if number("out_valid") == 1:
            assert accepted == 64, f"first waveform result followed {accepted}, expected 64 handshakes"
            assert signed_number("out_raw") == signed_number("out_data") == -8
            assert number("out_error") == number("out_overflow") == number("out_saturated") == 0
            return {"first_result_time_ps": now, "accepted_pairs": accepted,
                    "out_raw": -8, "out_data": -8, "flags": 0}
        return None

    for line in path.read_text(encoding="ascii").splitlines():
        parts = line.split()
        if line.startswith("$var"):
            widths[parts[4]] = int(parts[2])
            ids[parts[4]] = parts[3]
        elif line.startswith("#"):
            result = finish_timestamp()
            if result is not None:
                return result
            before = values.copy()
            now = int(line[1:])
        elif line.startswith("b") and len(parts) == 2:
            values[parts[1]] = parts[0][1:]
        elif line and line[0] in "01xXzZ" and not line.startswith("$"):
            values[line[1:]] = line[0]
    raise AssertionError("No checked first result in DOT64 waveform")
