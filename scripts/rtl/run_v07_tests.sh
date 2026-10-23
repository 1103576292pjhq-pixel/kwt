#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
mkdir -p out
python3 scripts/rtl/generate_v07_vectors.py
sources=(rtl/compute/mul_array_4x4.v rtl/compute/acc_context_bank.v
         rtl/compute/result_convert_v07.v rtl/compute/dot64_tile_core.v)
# RTL使用Verilog-2005语法，TB允许SystemVerilog自检结构。
iverilog -g2005 -Wall -I rtl/include -s dot64_tile_core -o out/v07_compile.vvp "${sources[@]}"
for tb in tb_v07_units tb_v07_compute; do
    iverilog -g2012 -Wall -I rtl/include -s "$tb" -o "out/$tb.vvp" "${sources[@]}" "tb/dot64/$tb.sv"
    vvp "out/$tb.vvp"
done
