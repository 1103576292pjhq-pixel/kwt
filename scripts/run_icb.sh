#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
exec "$ROOT/.venv-dv/bin/python" "$ROOT/dv/icb/run_icb.py" "$@"
