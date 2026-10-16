#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."
exec .venv-dv/bin/python scripts/run_formal_seven.py "$@"
