#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
mkdir -p out
yosys_bin=${YOSYS:-yosys}
if ! command -v "$yosys_bin" >/dev/null 2>&1; then
    if [[ -x work/tools/root/usr/bin/yosys ]]; then yosys_bin=work/tools/root/usr/bin/yosys
    else echo 'Yosys missing: install yosys or set YOSYS to its executable.' >&2; exit 1; fi
fi
lib_root=${SRAM_LIB_DIR:-/mnt/d/嵌赛芯片设计赛道/tsn28hpcpl2spsrammacros_180a_nldm/TSMCHOME/sram/Front_End/timing_power_noise/NLDM/tsn28hpcpl2spsrammacros_180a}
lib="$lib_root/TS1N28HPCPL2SVTB2048X32M4MWBASO/TS1N28HPCPL2SVTB2048X32M4MWBASO_tt1v25c.lib"
[[ -f "$lib" ]] || { echo "SRAM liberty missing: $lib" >&2; exit 1; }
cat > out/synth_accelerator.ys <<EOF
read_liberty -lib "$lib"
read_verilog -sv -DSYNTHESIS -Irtl/include rtl/compute/mul_array_4x4.v rtl/compute/acc_context_bank.v rtl/compute/result_convert_v07.v rtl/compute/dot64_tile_core.v rtl/memory/sram_wrapper.sv rtl/memory/x_buffer.sv rtl/memory/w_tile_buffer.sv rtl/control/command_frontend.sv rtl/control/tile_ctrl.sv rtl/control/matrix_ctrl.sv rtl/output/result_ctrl.sv rtl/accelerator_top.sv
hierarchy -check -top accelerator_top -chparam USE_MACRO 1
synth -top accelerator_top -noabc
check -assert
stat
write_json out/accelerator_generic.json
write_verilog -noattr out/accelerator_generic.v
EOF
"$yosys_bin" -s out/synth_accelerator.ys > out/synthesis.log 2>&1
tail -38 out/synthesis.log
# 只核对宏实例数量、锁存器和结构问题；通用门级结果不冒充工艺映射/STA。
python3 -B - <<'PY'
import json
from collections import Counter
from pathlib import Path
modules = json.loads(Path('out/accelerator_generic.json').read_text())['modules']
counts = Counter()
def visit(name):
    for cell in modules[name].get('cells', {}).values():
        kind = cell['type']
        attr = modules.get(kind, {}).get('attributes', {}).get('blackbox', 0)
        blackbox = int(attr, 2) if isinstance(attr, str) else int(attr)
        if kind in modules and not blackbox:
            visit(kind)
        else:
            counts[kind] += 1
visit('accelerator_top')
macro = 'TS1N28HPCPL2SVTB2048X32M4MWBASO'
assert counts[macro] == 12, counts
assert not any('LATCH' in kind.upper() and count for kind, count in counts.items()), counts
Path('out/synthesis_summary.json').write_text(json.dumps(dict(counts), indent=2)+'\n')
print('PASS: generic synthesis/check; 12 physical SRAM macros; no latches. Not mapped area/STA.')
PY
