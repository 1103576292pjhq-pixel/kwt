#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
exec "$ROOT/.venv-dv/bin/python" "$ROOT/dv/e203_ffn1/run_system.py" "$@"
