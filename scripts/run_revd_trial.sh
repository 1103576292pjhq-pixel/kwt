#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
export PYTHONDONTWRITEBYTECODE=1
trial_python="${KWT_DV_PYTHON:-/mnt/c/Users/11035/Desktop/ic/kwt—1/.venv-dv/bin/python}"
stage="${1:---check}"
if [[ "$stage" == --check ]]; then
  [[ "$(git branch --show-current)" == v2 ]]
  git merge-base --is-ancestor 3d9d0fc77457b8869cbf525d826dafb114f2a8e1 HEAD
  python3 scripts/prepare_repository.py --check
  command -v iverilog
  command -v vvp
  command -v verilator
  "$trial_python" -B -c 'import numpy; print("DV_PYTHON_READY", numpy.__version__)'
elif [[ "$stage" == d1 ]]; then
  "$trial_python" -B dv/revd/d1_runner.py --phase green
elif [[ "$stage" == protocol ]]; then
  "$trial_python" -B dv/revd/d2_protocol.py
elif [[ "$stage" == lint ]]; then
  "$trial_python" -B dv/revd/d2_lint.py
elif [[ "$stage" == gate ]]; then
  shift
  "$trial_python" -B scripts/revd_trial_gate.py "$@"
elif [[ "$stage" =~ ^(small|production|full36|repeat)$ ]]; then
  shift
  "$trial_python" -B dv/revd/d2_runner.py --profile "$stage" "$@"
else
  echo 'usage: run_revd_trial.sh [--check|d1|protocol|lint|small|production|full36|repeat|gate] [stage arguments]' >&2
  exit 2
fi
