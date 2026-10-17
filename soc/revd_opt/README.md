# RevD_opt public E203 / ICB reproduction

Use a Linux Python interpreter with NumPy, Icarus, Verilator, GNU make, a C++ compiler, and `riscv64-unknown-elf-{gcc,objcopy,objdump,readelf}` on `PATH`. The firmware targets RV32IMAC/Zicsr/Zifencei, ILP32, and the unchanged public E203 shell. No Python interpreter path is embedded in the entry point.

```sh
python -B scripts/revd_offline_soc_run.py --stage adapter
python -B scripts/revd_offline_soc_run.py --stage small --sim verilator
python -B scripts/revd_offline_soc_run.py --stage small --sim icarus
python -B scripts/revd_offline_soc_run.py --stage full --tasks 2
python -B scripts/revd_offline_soc_baseline.py --stage full --tasks 2
python -B scripts/revd_offline_soc_layers.py --case-offset 2
python -B scripts/revd_offline_soc_edges.py
```

Each invocation creates a new report directory and refuses to overwrite one. The full run executes the first two frozen engineering vector cases as separate cold parameter tasks in one CPU boot; it is not an official 600-sample test or a twelve-layer encoder run. The baseline command uses accepted D2, with only its module name changed in a new comparison copy. It is a reference, not a new optimized profile.

For the remaining engineering layers, repeat the `soc_layers` entry with fixed offsets `2,4,6,8,10`. Each selects exactly two frozen cases and binds their identities and the actual simulator executable SHA. Six boots cover twelve independent FFN1 cold tasks for one engineering input; each task consumes its own frozen input. The `soc_edges` entry uses explicit signed16/signed48 boundary arrays and the unchanged numeric reference, with shifts 47 and 0. It validates nonzero overflow/saturated flags through real CPU shared writes and a corrupted-flag negative control; these directed cases are not contest or engineering model samples.

The MMIO base is `0x11000000`. All MMIO transactions are 32-bit and aligned. Input fields are captured by COMMIT; subsequent staging writes cannot change an already queued event. A full COMMIT returns an immediate ICB error. Software polls capacity and drains available results before retrying. Output fields remain stable until POP, so CPU writes can use the supplied `y_index` rather than assuming arrival order.

| Offset | Access | Meaning |
|---|---|---|
| `0x00` | R | bit 0 input event capacity, bit 1 result valid, bit 2 core completion sticky, bit 3 fault |
| `0x04` | RW | operation `[3:0]`, layer `[7:4]`, shift `[13:8]` |
| `0x08` | RW | task ID |
| `0x0c` | RW | tile `[23:16]`, input index `[15:0]` |
| `0x10` | RW | input data `[31:0]` |
| `0x14` | RW | input data `[47:32]` in low 16 bits |
| `0x18` | W | COMMIT captured event |
| `0x1c` | R | output `y_index = row*N + column` |
| `0x20` | R | signed 32-bit output |
| `0x24` | R | bit 0 overflow, bit 1 saturated, bit 2 last |
| `0x28` | R | output task ID |
| `0x2c` | W | POP published output |
| `0x30` | R | core error code |
| `0x34` | R | accepted core event counter |
| `0x38` | R | current-task popped output counter |

There are three different event boundaries. MMIO COMMIT captures the staging payload into the adapter slot; `event_valid && core_ready` transfers that payload into the frontend; `core.retire_event` applies the ordered frontend command. Register `0x34` counts the second boundary. `soc_completion_tb.sv` passively counts and checks all three boundaries. A COMMIT response acknowledges adapter capture only. When the final Y is held, the frontend closes ingress: an event captured into the adapter at that time remains queued until the old task's final-output/completion barrier has passed. Such an event is not counted as an old-task frontend acceptance. A subsequent fault takes precedence over sticky old-task completion in the C driver.

Shared SRAM remains `0xa0000000`, 512 KiB, with one outstanding response. Its test fixture contains only raw inputs and poisoned destinations. Expected outputs stay outside CPU-visible memory. The header at offset `0x100` holds `M,N,task_count`; task descriptors at `0x120` use the layout in `sw/revd_opt/revd_opt_driver.h`. Bias entries are sign-extended signed 48-bit values carried in 64-bit slots. A descriptor's offsets are relative to the shared SRAM base.

The production C driver writes `destination[y_index]`, checks task/index/last/uniqueness, stores both flags plus the last bit, fences, and then POPs. Final CPU success is observed only after the actual mailbox write response; the testbench also counts every Y and flag write response and verifies the final shared SRAM image. Cold task windows start at each firmware phase write before descriptor/input loading and end at the final shared output/flag response. Core and frontend counters are reported separately.

The report's `instructions` field counts IFU valid/ready fetch handshakes. It is not an architectural retirement counter and is not used to infer IPC. Testbench clock periods are functional simulation settings; cycle counts do not establish physical timing closure.

This is a public upstream integration with behavioral SRAM, not confirmation of the contest-specific platform, official SRAM macros, 150 MHz timing, area, power, or full contest acceptance. Host simulator wall time is recorded separately from RTL cycle counts.

Additional closure checks are `python -B scripts/revd_offline_soc_mutations.py` and `python -B scripts/revd_offline_soc_negative.py`. The former runs bus/completion lifecycle tests and three actual compiled RTL mutations. The latter executes real CPU firmware that returns zero while doing no work or omitting the final shared Y/flags write; the unchanged CPU testbench must reject both. CPU/software negative controls are reported separately from RTL mutation counts.
