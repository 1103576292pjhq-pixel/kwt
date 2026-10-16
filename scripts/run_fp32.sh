#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."
exec .venv-dv/bin/python dv/fp32/run_fp32.py "$@"
