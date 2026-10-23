#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
mkdir -p out
m=${TEST_M:-5}; n=${TEST_N:-32}; layers=${TEST_LAYERS:-2}
latency=${TEST_LATENCY:-1}; macro=${TEST_MACRO:-0}
sources=(rtl/memory/sram_wrapper.sv rtl/memory/x_buffer.sv rtl/memory/w_tile_buffer.sv
         rtl/control/command_frontend.sv rtl/control/tile_ctrl.sv rtl/control/matrix_ctrl.sv
         rtl/output/result_ctrl.sv rtl/compute/mul_array_4x4.v rtl/compute/acc_context_bank.v
         rtl/compute/result_convert_v07.v rtl/compute/dot64_tile_core.v rtl/accelerator_top.sv)
extra=()
if [[ "$macro" == 1 ]]; then
    macro_dir=${SRAM_MODEL_DIR:-/mnt/d/嵌赛芯片设计赛道/tsn28hpcpl2spsrammacros_180a_vlg/TSMCHOME/sram/Front_End/verilog/tsn28hpcpl2spsrammacros_180a}
    model="$macro_dir/TS1N28HPCPL2SVTB2048X32M4MWBASO/TS1N28HPCPL2SVTB2048X32M4MWBASO_tt1v25c.v"
    [[ -f "$model" ]] || { echo "SRAM model missing: $model" >&2; exit 1; }
    # 功能模式不进行库时序检查；这不是STA或150MHz通过证明。
    sources+=("$model"); extra+=(-DUNIT_DELAY)
fi
for tb in tb_buffers tb_accelerator; do
    if [[ "$tb" == tb_accelerator ]]; then
        python3 -B scripts/rtl/generate_accelerator_vectors.py --m "$m" --n "$n" --layers "$layers"
    fi
    iverilog -g2012 -Wall -I rtl/include "${extra[@]}" \
        -DTEST_M="$m" -DTEST_N="$n" -DTEST_LAYERS="$layers" \
        -DTEST_LATENCY="$latency" -DTEST_MACRO="$macro" \
        -s "$tb" -o "out/$tb.vvp" "${sources[@]}" "tb/accelerator/$tb.sv"
    vvp "out/$tb.vvp"
done
