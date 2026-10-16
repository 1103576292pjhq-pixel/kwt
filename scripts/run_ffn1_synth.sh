#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
exec "$ROOT/.venv-dv/bin/python" "$ROOT/dv/synthesis/run_ffn1_synth.py" "$@"
