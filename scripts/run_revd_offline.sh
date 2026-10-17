#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
# Select an installed interpreter explicitly; never depend on a host-specific venv.
python_bin="${KWT_DV_PYTHON:-python3}"
export PYTHONDONTWRITEBYTECODE=1
exec "$python_bin" -B dv/revd_opt/core_runner.py "$@"
