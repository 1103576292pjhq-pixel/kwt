#!/usr/bin/env bash
set -Eeuo pipefail
readonly ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly REPORT="$ROOT/reports/prototype/dot64"
mkdir -p -- "$REPORT"
printf '{"status":"RUNNING"}\n' > "$REPORT/status.json"
exec > >(/usr/bin/tee "$REPORT/run.log") 2>&1
trap 'rc=$?; if ((rc != 0)); then printf "{\"status\":\"FAIL\",\"exit_code\":%s}\n" "$rc" > "$REPORT/status.json"; fi; printf "dot64_exit_code=%s\n" "$rc"' EXIT
[[ -x "$ROOT/.venv-dv/bin/python" ]] || { echo 'ERROR: missing Linux .venv-dv'; exit 2; }
"$ROOT/.venv-dv/bin/python" "$ROOT/dv/dot64/run_dot64.py"
