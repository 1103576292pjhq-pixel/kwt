#!/usr/bin/env bash
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly PYTHON="$(readlink -f -- "$WORKSPACE/.venv-model")/bin/python"
OUTPUT="$WORKSPACE/reports/encoder/export"
previous=''
for value in "$@"; do
  if [[ "$previous" == '--output' ]]; then OUTPUT="$value"; fi
  previous="$value"
done
mkdir -p "$OUTPUT"
export PYTHONDONTWRITEBYTECODE=1 CUDA_VISIBLE_DEVICES=-1 OMP_NUM_THREADS=1 OPENBLAS_NUM_THREADS=1 TF_DETERMINISTIC_OPS=1 TF_CPP_MIN_LOG_LEVEL=2
"$PYTHON" "$WORKSPACE/model/encoder_export.py" "$@" 2>&1 | tee "$OUTPUT/run.log"
