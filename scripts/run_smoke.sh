#!/usr/bin/env bash
# Run with: bash /absolute/path/to/scripts/run_smoke.sh (any current directory).
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly PYTHON="$WORKSPACE/.venv-dv/bin/python"
readonly REPORT_DIR="$WORKSPACE/reports/environment"
readonly LOG_NAME="${SMOKE_LOG_NAME:-smoke.log}"
[[ "$LOG_NAME" =~ ^[a-zA-Z0-9._-]+$ ]] || { echo 'ERROR: SMOKE_LOG_NAME must be a filename.'; exit 2; }
mkdir -p -- "$REPORT_DIR"
exec > >(/usr/bin/tee "$REPORT_DIR/$LOG_NAME") 2>&1
trap 'rc=$?; printf "smoke_exit_code=%s\n" "$rc"; /usr/bin/python3 "$WORKSPACE/dv/smoke/update_smoke_status.py" finalize "$rc" || rc=1; if [[ -x "$PYTHON" ]]; then "$PYTHON" "$WORKSPACE/dv/smoke/write_environment.py" || true; fi; exit "$rc"' EXIT
printf 'Workspace: %s\n' "$WORKSPACE"
printf 'Smoke started (UTC): %s\n' "$(/usr/bin/date -u +%FT%TZ)"
/usr/bin/python3 "$WORKSPACE/dv/smoke/update_smoke_status.py" begin
[[ -x "$PYTHON" ]] || { echo 'ERROR: Missing Linux .venv-dv; run bash scripts/setup_dv.sh first.'; exit 2; }
"$PYTHON" "$WORKSPACE/dv/smoke/run_smoke.py"
