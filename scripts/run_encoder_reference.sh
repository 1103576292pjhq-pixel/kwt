#!/usr/bin/env bash
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
export PYTHONDONTWRITEBYTECODE=1
readonly PYTHON="$WORKSPACE/.venv-dv/bin/python"
mkdir -p "$WORKSPACE/reports/encoder/reference"
OUTPUT="$WORKSPACE/reports/encoder/reference"
previous=''
for value in "$@"; do
  if [[ "$previous" == '--output' ]]; then OUTPUT="$value"; fi
  previous="$value"
done
mkdir -p "$OUTPUT" "$WORKSPACE/reports/encoder/reference/tests"
"$PYTHON" -m unittest discover -s "$WORKSPACE/tests/encoder_reference" -v 2>&1 | tee "$WORKSPACE/reports/encoder/reference/tests/green.log"
"$PYTHON" "$WORKSPACE/numeric/encoder/run_reference.py" "$@" 2>&1 | tee "$OUTPUT/run.log"
