"""Deterministic smoke assertions: clock, reset, enable, wrap and restart."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge, Timer


@cocotb.test(timeout_time=2, timeout_unit="us")
async def counter_reset_enable_wrap_and_restart(dut):
    dut.clk.value = 0
    dut.rst_n.value = 1
    dut.en.value = 0
    clock = Clock(dut.clk, 10, unit="ns")
    clock.start()

    # Exercise reset between clock edges, then count through two full wraps.
    await Timer(2, unit="ns")
    dut.rst_n.value = 0
    await Timer(1, unit="ns")
    assert int(dut.count.value) == 0, "asynchronous reset must clear count"
    await FallingEdge(dut.clk)
    dut.rst_n.value = 1
    dut.en.value = 1
    for step in range(1, 36):
        await RisingEdge(dut.clk)
        await ReadOnly()
        expected = step % 16
        actual = int(dut.count.value)
        assert actual == expected, f"continuous enabled count: step={step}, expected={expected}, actual={actual}"
        await FallingEdge(dut.clk)

    dut.en.value = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
        await ReadOnly()
        assert int(dut.count.value) == 3, "disabled counter must hold its state"
        await FallingEdge(dut.clk)

    # Assert reset while the clock is high, away from a rising edge.
    await Timer(7, unit="ns")
    dut.rst_n.value = 0
    await Timer(1, unit="ns")
    assert int(dut.count.value) == 0, "mid-run asynchronous reset must clear count"
    for _ in range(3):
        await RisingEdge(dut.clk)
        await ReadOnly()
        assert int(dut.count.value) == 0, "reset-held cycles must remain zero"
    await FallingEdge(dut.clk)
    dut.rst_n.value = 1
    dut.en.value = 1
    for expected in range(1, 6):
        await RisingEdge(dut.clk)
        await ReadOnly()
        assert int(dut.count.value) == expected, "counter must restart after reset"
    clock.stop()
    dut._log.info("Checked 35 continuous increments, two wraps, 5 hold cycles, asynchronous reset and 5 restart increments.")
