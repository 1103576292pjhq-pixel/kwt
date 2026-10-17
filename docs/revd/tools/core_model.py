"""Independent-integer design explorer for KWT RevC (NOT an RTL simulator).

KWT V0 numerical contract: signed16 products, signed48 bias, sat48, RNE,
sat32. Dense reference uses Fraction rounding; the candidate uses an
integer magnitude path. No third-party packages are required.
"""
from __future__ import annotations
from dataclasses import asdict, dataclass
from fractions import Fraction
from typing import Iterable
import random


def integer(value: object, name: str) -> int:
    if type(value) is not int:
        raise ValueError(f"{name} must be an integer, not bool/float")
    return value


def bounded(value: object, bits: int, name: str) -> int:
    value = integer(value, name)
    if not -(1 << (bits - 1)) <= value < (1 << (bits - 1)):
        raise ValueError(f"{name} outside signed{bits}")
    return value


def sat(value: int, bits: int) -> int:
    return min(max(value, -(1 << (bits - 1))), (1 << (bits - 1)) - 1)


def valid_shift(shift: int) -> int:
    shift = integer(shift, "shift")
    if not 0 <= shift <= 47:
        raise ValueError("shift must be in 0..47")
    return shift


@dataclass(frozen=True)
class Result:
    raw: int
    data: int
    overflow: bool
    saturated: bool


def finalize(dot: int, bias: int, shift: int) -> Result:
    """Candidate postprocessing: abs/divmod, tie-to-even, no wrap."""
    dot = bounded(dot, 48, "dot")
    bias = bounded(bias, 48, "bias")
    valid_shift(shift)
    total = dot + bias
    raw = sat(total, 48)
    quotient, remainder = divmod(abs(raw), 1 << shift)
    if shift:
        half = 1 << (shift - 1)
        if remainder > half or (remainder == half and quotient & 1):
            quotient += 1
    rounded = -quotient if raw < 0 else quotient
    output = sat(rounded, 32)
    return Result(raw, output, raw != total, output != rounded)


def reference_finalize(dot: int, bias: int, shift: int) -> Result:
    """Independent rational-number reference, not the candidate RNE path."""
    bounded(dot, 48, "dot")
    bounded(bias, 48, "bias")
    valid_shift(shift)
    total = dot + bias
    raw = max(-(2**47), min(2**47 - 1, total))
    rounded = round(Fraction(raw, 2**shift))
    output = max(-(2**31), min(2**31 - 1, rounded))
    return Result(raw, output, total != raw, rounded != output)


@dataclass(frozen=True)
class Geometry:
    m: int = 99
    k: int = 64
    n: int = 256
    pm: int = 4
    pn: int = 4
    n_tile: int = 16

    def __post_init__(self) -> None:
        for name, value in asdict(self).items():
            integer(value, name)
        if not 1 <= self.m <= 99:
            raise ValueError("m must be in 1..99")
        if self.k != 64 or self.pn != 4 or self.n_tile != 16:
            raise ValueError("RevC fixes K=64, PN=4, N_TILE=16")
        if self.pm not in (1, 2, 4):
            raise ValueError("pm must be 1, 2 or 4")
        if not 16 <= self.n <= 256 or self.n % 16:
            raise ValueError("engine supports N=16..256, multiples of 16 only")

    @property
    def row_groups(self) -> int:
        return (self.m + self.pm - 1) // self.pm

    @property
    def tile_count(self) -> int:
        return self.n // self.n_tile


def x_address(g: Geometry, m: int, k: int) -> tuple[int, int]:
    if not 0 <= m < g.m or not 0 <= k < g.k:
        raise ValueError("X index out of range")
    return m % g.pm, (m // g.pm) * g.k + k


def w_address(g: Geometry, k: int, n: int, tiled: bool) -> tuple[int, int]:
    if not 0 <= n < g.n or not 0 <= k < g.k:
        raise ValueError("W index out of range")
    j = n % g.n_tile if tiled else n
    return j % g.pn, (j // g.pn) * g.k + k


def expected_indices(g: Geometry) -> list[int]:
    """Public result order: tile -> row group -> row -> local column."""
    return [m * g.n + n
            for nt in range(0, g.n, g.n_tile)
            for m0 in range(0, g.m, g.pm)
            for m in range(m0, min(m0 + g.pm, g.m))
            for n in range(nt, nt + g.n_tile)]


def validate_inputs(g: Geometry, x: list, w: list, bias: list) -> None:
    if len(x) != g.m or len(w) != 64 or len(bias) != g.n:
        raise ValueError("wrong matrix shape")
    for row in x:
        if len(row) != 64:
            raise ValueError("X must be [M,64]")
        for value in row:
            bounded(value, 16, "x")
    for row in w:
        if len(row) != g.n:
            raise ValueError("W must be [64,N]")
        for value in row:
            bounded(value, 16, "w")
    for value in bias:
        bounded(value, 48, "bias")


def dense_reference(g: Geometry, x: list, w: list, bias: list,
                    shift: int) -> list[Result]:
    validate_inputs(g, x, w, bias)
    valid_shift(shift)
    return [reference_finalize(sum(x[m][k] * w[k][n] for k in range(64)),
                               bias[n], shift)
            for m in range(g.m) for n in range(g.n)]


def candidate(g: Geometry, x: list, w: list, bias: list, shift: int,
              schedule: str = "ctx4") -> tuple[list[Result], dict]:
    """Functional loop execution with counted logical reads, NOT cycle timing.

    micro: independently reduce each PMxPN microtile.
    ctx4: keep PMx16 sums; one X vector serves four PN column groups per k.
    """
    validate_inputs(g, x, w, bias)
    valid_shift(shift)
    if schedule not in ("micro", "ctx4"):
        raise ValueError("unknown schedule")
    output: list[Result | None] = [None] * (g.m * g.n)
    counts = dict(x_bank_reads=0, w_bank_reads=0, useful_macs=0,
                  issue_slots=0, invalid_lane_slots=0)
    for nt in range(0, g.n, 16):
        for m0 in range(0, g.m, g.pm):
            nr = min(g.pm, g.m - m0)
            acc = [[0] * 16 for _ in range(nr)]
            steps = ((k, j0) for k in range(64) for j0 in range(0, 16, 4))
            if schedule == "micro":
                steps = ((k, j0) for j0 in range(0, 16, 4) for k in range(64))
            held_x: list[int] = []
            for k, j0 in steps:
                if schedule == "micro" or j0 == 0:
                    held_x = [x[m0 + r][k] for r in range(nr)]
                    counts["x_bank_reads"] += nr
                weights = w[k][nt + j0:nt + j0 + 4]
                counts["w_bank_reads"] += 4
                counts["issue_slots"] += 1
                counts["invalid_lane_slots"] += (g.pm - nr) * 4
                for r in range(nr):
                    for c in range(4):
                        acc[r][j0 + c] += held_x[r] * weights[c]
                        counts["useful_macs"] += 1
            for r in range(nr):
                for j in range(16):
                    i = (m0 + r) * g.n + nt + j
                    if output[i] is not None:
                        raise AssertionError("duplicate output")
                    output[i] = finalize(acc[r][j], bias[nt + j], shift)
    if any(v is None for v in output):
        raise AssertionError("missing output")
    return output, counts  # type: ignore[return-value]


def analytic(g: Geometry, schedule: str, mode: str = "tiled",
             w_slots: int = 2, y_slots: int = 2) -> dict:
    if schedule not in ("micro", "ctx4") or mode not in ("full", "tiled"):
        raise ValueError("invalid schedule/mode")
    if w_slots not in (1, 2) or y_slots not in (1, 2):
        raise ValueError("slot counts must be 1 or 2")
    issue = g.row_groups * (g.n // 4) * 64
    xr = g.m * 64 * (g.n // (16 if schedule == "ctx4" else 4))
    wr = g.row_groups * g.n * 64
    contexts = 4 if schedule == "ctx4" else 1
    return dict(
        geometry=asdict(g), schedule=schedule, mode=mode,
        prediction_kind="ANALYTIC_COUNTS_NOT_RTL_CYCLES_OR_PPA",
        mac_lanes=g.pm * 4, ideal_issue_slots=issue,
        useful_macs=g.m * g.n * 64,
        invalid_lane_slots=issue * g.pm * 4 - g.m * g.n * 64,
        x_bank_reads=xr, w_bank_reads=wr, operand_bank_reads=xr + wr,
        accumulator_bytes=g.pm * 4 * contexts * 6,
        snapshot_bytes=g.pm * 4 * contexts * 6,
        x_vector_register_bytes=(2 * g.pm * 2 if schedule == "ctx4" else 0),
        x_allocated_bytes=g.row_groups * g.pm * 64 * 2,
        w_bytes=(64 * g.n * 2 if mode == "full" else w_slots * 64 * 16 * 2),
        bias_bytes=(g.n * 6 if mode == "full" else w_slots * 16 * 6),
        y_bytes=y_slots * g.pm * 16 * 4,
        flags_bytes=(y_slots * g.pm * 16 * 2 + 7) // 8,
        task_load_elements=g.m * 64 + 64 * g.n + g.n,
        result_elements=g.m * g.n,
        note="Register/mux/FIFO/control cost remains; bytes are not macro area."
    )


def make_case(g: Geometry, seed: int, shift: int = 8) -> dict:
    rng = random.Random(integer(seed, "seed"))
    valid_shift(shift)
    values = [-32768, -32767, -1, 0, 1, 32766, 32767]
    def operand() -> int:
        return rng.choice(values) if rng.randrange(5) == 0 else rng.randint(-2048, 2047)
    bias = [rng.randint(-2**32, 2**32) for _ in range(g.n)]
    if g.n >= 2:
        bias[0], bias[1] = -(2**47), 2**47 - 1
    return dict(kind="SYNTHETIC_COMPONENT_TEST_NOT_OFFICIAL_MODEL_DATA",
                geometry=asdict(g), seed=seed, shift=shift,
                x=[[operand() for _ in range(64)] for _ in range(g.m)],
                w=[[operand() for _ in range(g.n)] for _ in range(64)], bias=bias)


def records(g: Geometry, results: list[Result], task_id: int) -> Iterable[dict]:
    order = expected_indices(g)
    for position, index in enumerate(order):
        result = results[index]
        yield dict(task_id=task_id, y_index=index, data=result.data,
                   overflow=result.overflow, saturated=result.saturated,
                   last=position == len(order) - 1)
