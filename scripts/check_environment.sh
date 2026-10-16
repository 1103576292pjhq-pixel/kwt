#!/usr/bin/env bash
# Invoke via bash /absolute/path/to/scripts/check_environment.sh from any cwd.
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly REPORT_DIR="$WORKSPACE/reports/environment"
mkdir -p -- "$REPORT_DIR"
# Invalidate stale PASS even if the Python launcher cannot start.
printf '{"status":"RUNNING","scope":"local environment check"}\n' > "$REPORT_DIR/readiness.json"
exec > >(/usr/bin/tee "$REPORT_DIR/check-environment.log") 2>&1
printf 'Workspace: %s\n' "$WORKSPACE"
if [[ ! -x /usr/bin/python3 ]]; then
  printf '{"status":"FAIL","error":"Missing /usr/bin/python3","exit_code":2}\n' > "$REPORT_DIR/readiness.json"
  echo 'ERROR: Missing /usr/bin/python3'
  exit 2
fi
/usr/bin/python3 "$WORKSPACE/scripts/check_environment.py"
