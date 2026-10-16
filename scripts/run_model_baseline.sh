#!/usr/bin/env bash
# WSL/Linux entry, runnable from any cwd including a Unicode workspace path.
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly ENVIRONMENT="$(readlink -f -- "$WORKSPACE/.venv-model")"
readonly PYTHON="$ENVIRONMENT/bin/python"
readonly REPORT_DIR="$WORKSPACE/reports/model"
mkdir -p -- "$REPORT_DIR"
exec > >(/usr/bin/tee "$REPORT_DIR/model-baseline.log") 2>&1
finish() {
  local rc=$?
  local status=FAIL
  if [[ "$rc" -eq 0 ]]; then status=PASS; fi
  printf '{"status":"%s","exit_code":%s}\n' "$status" "$rc" > "$REPORT_DIR/STATUS.json"
  printf "model_baseline_exit_code=%s\n" "$rc"
  exit "$rc"
}
trap finish EXIT
printf '{"status":"RUNNING"}\n' > "$REPORT_DIR/STATUS.json"
printf 'Workspace: %s\n' "$WORKSPACE"
printf 'Model baseline started (UTC): %s\n' "$(/usr/bin/date -u +%FT%TZ)"
[[ -x "$PYTHON" ]] || { echo 'ERROR: Missing .venv-model Python; run setup_model.sh first.'; exit 2; }
export PYTHONPATH="$WORKSPACE${PYTHONPATH:+:$PYTHONPATH}"
export PYTHONDONTWRITEBYTECODE=1
export CUDA_VISIBLE_DEVICES=-1
export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export TF_DETERMINISTIC_OPS=1
export TF_CPP_MIN_LOG_LEVEL=2
"$PYTHON" -m unittest discover -s "$WORKSPACE/tests/model" -p test_contracts.py -v
KWT_TEST_OFFICIAL_FLAGS=1 "$PYTHON" -m unittest discover -s "$WORKSPACE/tests/model" -p test_official_entry.py -v
"$PYTHON" "$WORKSPACE/model/run_baseline.py" --include-silence --output "$REPORT_DIR/baseline"
"$PYTHON" "$WORKSPACE/model/run_baseline.py" --include-silence --output "$REPORT_DIR/repeat"
"$PYTHON" "$WORKSPACE/model/verify_baseline.py" --report "$REPORT_DIR/baseline" --compare "$REPORT_DIR/repeat"
KWT_BASELINE_REPORT="$REPORT_DIR/baseline" "$PYTHON" -m unittest discover -s "$WORKSPACE/tests/model" -p test_integration.py -v
