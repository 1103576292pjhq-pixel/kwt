"""Independent integer scoreboard for DOT64, including handshake/reset behavior."""
import random

import cocotb
from cocotb.triggers import Timer


def signed(signal):
    value = int(signal.value)
    width = len(signal)
    return value - (1 << width) if value & (1 << (width - 1)) else value


def expected(xs, ws, bias, shift):
    total = sum(int(x) * int(w) for x, w in zip(xs, ws, strict=True)) + bias
    low48, high48 = -(1 << 47), (1 << 47) - 1
    raw = max(low48, min(high48, total))
    magnitude = abs(raw)
    quotient, remainder = divmod(magnitude, 1 << shift)
    if shift and (remainder * 2 > (1 << shift) or
                  (remainder * 2 == (1 << shift) and quotient & 1)):
        quotient += 1
    rounded = -quotient if raw < 0 else quotient
    result = max(-(1 << 31), min((1 << 31) - 1, rounded))
    return result, raw, int(raw != total), int(result != rounded), 0


class Bench:
    def __init__(self, dut):
        self.dut = dut
        self.cycles = 0
        self.random = random.Random(20261015)

    async def tick(self):
        self.dut.clk.value = 0
        await Timer(5, unit="ns")
        self.dut.clk.value = 1
        await Timer(5, unit="ns")
        self.dut.clk.value = 0
        self.cycles += 1

    async def reset(self):
        d = self.dut
        d.clk.value = 0
        d.rst_n.value = 1
        d.start_valid.value = 0
        d.start_bias.value = 0
        d.start_shift.value = 0
        d.in_valid.value = 0
        d.in_x.value = 0
        d.in_w.value = 0
        d.out_ready.value = 0
        await Timer(1, unit="ns")
        d.rst_n.value = 0
        await Timer(1, unit="ns")
        assert int(d.out_valid.value) == 0
        assert int(d.busy.value) == 0
        await self.tick()
        d.rst_n.value = 1
        await Timer(1, unit="ns")
        assert int(d.start_ready.value) == 1
        assert int(d.in_ready.value) == 0

    async def start(self, bias, shift):
        d = self.dut
        assert int(d.start_ready.value) == 1, "idle task acceptance required"
        d.start_bias.value = bias
        d.start_shift.value = shift
        d.start_valid.value = 1
        await self.tick()
        d.start_valid.value = 0
        await Timer(1, unit="ns")
        assert int(d.busy.value) == 1
        assert int(d.start_ready.value) == 0

    async def send(self, xs, ws, stall=False):
        d = self.dut
        for index, (x, w) in enumerate(zip(xs, ws, strict=True)):
            if stall:
                d.in_valid.value = 0
                for _ in range(self.random.randrange(4)):
                    await self.tick()
                    assert int(d.out_valid.value) == 0, f"premature result before input {index}"
            assert int(d.in_ready.value) == 1, f"input {index} was not ready"
            d.in_valid.value = 1
            d.in_x.value = x
            d.in_w.value = w
            await self.tick()
            assert int(d.out_valid.value) == 0, f"must finalize after accepted input {index}"
        d.in_valid.value = 0

    def result(self):
        d = self.dut
        return (signed(d.out_data), signed(d.out_raw), int(d.out_overflow.value),
                int(d.out_saturated.value), int(d.out_error.value))

    async def check_output(self, wanted, hold=0):
        d = self.dut
        if not int(d.out_valid.value):
            await self.tick()
        assert int(d.out_valid.value) == 1, "result must arrive one cycle after the 64th input"
        assert self.result() == wanted, f"expected={wanted}, actual={self.result()}"
        for _ in range(hold):
            d.start_valid.value = 1
            d.start_bias.value = 777
            d.start_shift.value = 63
            d.in_valid.value = 1
            d.in_x.value = -32768
            d.in_w.value = -32768
            await self.tick()
            assert int(d.out_valid.value) == 1
            assert int(d.busy.value) == 1
            assert int(d.start_ready.value) == int(d.in_ready.value) == 0
            assert self.result() == wanted, "backpressure must hold every output bit"
        d.start_valid.value = 0
        d.in_valid.value = 0
        d.out_ready.value = 1
        await self.tick()
        d.out_ready.value = 0
        await Timer(1, unit="ns")
        assert int(d.out_valid.value) == int(d.busy.value) == 0
        assert int(d.start_ready.value) == 1

    async def run(self, xs, ws, bias=0, shift=0, stall=False, hold=0):
        assert len(xs) == len(ws) == 64
        await self.start(bias, shift)
        await self.send(xs, ws, stall)
        await self.check_output(expected(xs, ws, bias, shift), hold)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def hand_computed_and_exactly_64_inputs(dut):
    b = Bench(dut)
    await b.reset()
    xs, ws = [1, -2, 3] + [0] * 61, [2, 4, -1] + [0] * 61
    assert expected(xs, ws, 1, 0)[0] == -8
    await b.run(xs, ws, 1, 0, hold=3)
    # Only the final accepted product contributes: catches dropped 64th product.
    await b.run([0] * 63 + [-32768], [0] * 63 + [32767], 9, 0)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def nearest_even_positive_negative_and_shift_boundaries(dut):
    b = Bench(dut)
    await b.reset()
    for bias, shift, wanted in [(3, 1, 2), (5, 1, 2), (-3, 1, -2), (-5, 1, -2),
                                 (1, 1, 0), (-1, 1, 0), (7, 1, 4), (-7, 1, -4),
                                 (123, 0, 123), ((1 << 46), 47, 0),
                                 ((1 << 46) + 1, 47, 1), (-(1 << 47), 47, -1)]:
        assert expected([0] * 64, [0] * 64, bias, shift)[0] == wanted
        await b.run([0] * 64, [0] * 64, bias, shift)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def product_extremes_bias49_overflow_and_saturation(dut):
    b = Bench(dut)
    await b.reset()
    vectors = [([-32768] * 64, [-32768] * 64, (1 << 47) - 1, 0),
               ([-32768] * 64, [32767] * 64, -(1 << 47), 4),
               ([32767] * 64, [32767] * 64, 0, 6),
               ([-32768, -32768] * 32, [-32768, 32767] * 32, 0, 0),
               ([0] * 64, [0] * 64, (1 << 31) - 1, 0),
               ([0] * 64, [0] * 64, -(1 << 31), 0),
               ([0] * 64, [0] * 64, (1 << 31), 0),
               ([0] * 64, [0] * 64, -(1 << 31) - 1, 0),
               ([0] * 64, [0] * 64, (1 << 32) - 1, 1),
               ([0] * 64, [0] * 64, (1 << 32) - 3, 1),
               ([0] * 64, [0] * 64, -(1 << 32) - 1, 1),
               ([0] * 64, [0] * 64, -(1 << 32) - 3, 1),
               ([1, 1] + [0] * 62, [1, -1] + [0] * 62, (1 << 47) - 1, 47),
               ([1, 1] + [0] * 62, [-1, 1] + [0] * 62, -(1 << 47), 47)]
    for xs, ws, bias, shift in vectors:
        await b.run(xs, ws, bias, shift, hold=2)


@cocotb.test(timeout_time=200, timeout_unit="us")
async def deterministic_random_input_stalls_and_output_backpressure(dut):
    b = Bench(dut)
    await b.reset()
    for _ in range(12):
        xs = [b.random.randint(-32768, 32767) for _ in range(64)]
        ws = [b.random.randint(-32768, 32767) for _ in range(64)]
        bias = b.random.randint(-(1 << 47), (1 << 47) - 1)
        await b.run(xs, ws, bias, b.random.randrange(48), stall=True, hold=7)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def continuous_tasks_capture_start_configuration(dut):
    b = Bench(dut)
    await b.reset()
    for task in range(6):
        bias, shift = task * 999 - 2048, task
        await b.start(bias, shift)
        dut.start_bias.value = (1 << 47) - 1
        dut.start_shift.value = 63
        xs, ws = [task - 3] * 64, [2] * 64
        await b.send(xs, ws)
        await b.check_output(expected(xs, ws, bias, shift))


@cocotb.test(timeout_time=100, timeout_unit="us")
async def illegal_shift_rejects_operands_then_recovers(dut):
    b = Bench(dut)
    await b.reset()
    for shift in (48, 63):
        await b.start(123, shift)
        assert int(dut.in_ready.value) == 0
        await b.check_output((0, 0, 0, 0, 1), hold=4)
        await b.run([1] * 64, [1] * 64, -1, 0)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def asynchronous_reset_aborts_input_and_pending_result(dut):
    b = Bench(dut)
    await b.reset()
    await b.start(123, 0)
    await b.send([1] * 17, [2] * 17)
    await b.reset()
    for _ in range(4):
        await b.tick()
        assert int(dut.out_valid.value) == 0
    await b.start(5, 0)
    await b.send([1] * 64, [3] * 64)
    await b.tick()
    assert int(dut.out_valid.value) == 1
    await b.reset()
    await b.run([-1] * 64, [2] * 64, 4, 0)


@cocotb.test(timeout_time=100, timeout_unit="us")
async def ignored_unaccepted_inputs_and_starts(dut):
    b = Bench(dut)
    await b.reset()
    dut.in_valid.value = 1
    dut.in_x.value = 999
    dut.in_w.value = 999
    for _ in range(3):
        await b.tick()
        assert int(dut.in_ready.value) == int(dut.busy.value) == 0
    dut.in_valid.value = 0
    await b.start(7, 0)
    dut.start_valid.value = 1
    dut.start_bias.value = 99999
    dut.start_shift.value = 63
    await b.send([1] * 64, [2] * 64)
    # A 65th offered pair cannot become part of the completed dot.
    dut.in_valid.value = 1
    dut.in_x.value = -32768
    dut.in_w.value = -32768
    await b.tick()
    assert int(dut.in_ready.value) == 0
    await b.check_output((135, 135, 0, 0, 0), hold=3)
