# W2 public E203 reproduction

Use a local Python interpreter with NumPy, a RISC-V GCC/binutils toolchain, Verilator,
Icarus, a C++ compiler and make on PATH. The selected interpreter is the command
used to invoke the scripts; no virtual-environment absolute path is required.

```sh
python -B scripts/revd_offline_soc_w2_run.py --stage small --red-only
python -B scripts/revd_offline_soc_w2_run.py --stage small
python -B scripts/revd_offline_soc_w2_run.py --stage full
```

Each invocation creates a fresh report directory and refuses existing run IDs.
`--red-only` deliberately executes the frozen full-W C schedule against W2: a
future OPEN before START must produce error `0x12`, real CPU return `-11`, and a
real simulator fatal. Its result is `RED_CONFIRMED`, not a passed candidate.

The W2 C driver starts immediately after tile zero COMMIT. Subsequent tile
parameters stream while the CPU drains results. Every emit polls status and
drains at most one published Y before testing input-event capacity. The adapter
contains one ICB endpoint; an outstanding captured event does not prevent Y
reads or POP. Driver output addressing remains `y_index`, with a uniqueness
bitmap, exact last-index check, and a fence before POP.

The small profile is two independent `3 x 64 x 32` tasks. It also runs response
backpressure and final-Y command/fault boundary tests. Three real CPU negative
controls cover nonzero return, return zero without any work, and a corrupted
verification-only expected result. Expected simulator failures require their
precise fatal reason and actual `-6` exit; timeout or missing status is rejected.
`revd_offline_soc_w2_controls.py` tests those software rejection rules separately
and receives no RTL-mutation credit.

The full profile is two independent cold `99 x 64 x 256` tasks from the frozen
engineering-vector manifest. Each task must exercise a deferred third OPEN and
CPU POP while input is pending. Every actual shared-SRAM Y/flag write, index and
write response is checked, followed by a full SRAM image check. Terminal success
waits for the final shared completion response. This scope covers two FFN1 layer
tasks, not twelve connected layers, the complete encoder, or official samples.

The cold task window begins at the phase marker immediately before the driver
call and ends at the final actual Y/flag shared write response. It includes task
descriptor reads, X/W/bias loading, CPU and bus waits, compute and draining. CPU
boot and the earlier global M/N/task-count header reads are excluded. W2's core
window also contains overlapped parameter supply; it cannot be interpreted as
isolated compute latency.

For a fresh comparison, first run the default full-W entry, then pass the two
actual `result.json` paths:

```sh
python -B scripts/revd_offline_soc_run.py --stage full --tasks 2 --pm 4
python -B scripts/revd_offline_soc_w2_compare.py --full-w <full-W-result.json> --w2 <W2-result.json>
```

The comparison verifies identical input images, tools, indexed Y/flags, adapter
namespace equivalence, and a C diff limited to namespace and START placement.
Physical timing, area, energy and contest score require external evidence and
remain unknown. The full-W PM4 default is retained until the parent accepts an
explicit selection change.

To exercise nonzero arithmetic flags with the same compiled small-profile
binary and unchanged C, pass a fresh small report:

```sh
python -B scripts/revd_offline_soc_w2_edges.py --small-report <W2-small-result.json>
```

This directed test uses three rows and two tiles, fixed signed16 extrema,
biases near signed48/signed32 boundaries, and shifts47/0. The frozen numeric
reference generates verification-only expected values. Real CPU writes must
cover neither flag, overflow only, saturation only, and both; final tail results
also carry arithmetic flags. A second real CPU run corrupts only the expected
overflow bit and must fail. Reports bind the reused binary, firmware and source
hashes and explicitly record that no fresh compilation occurred in this step.
