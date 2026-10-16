#!/usr/bin/env bash
# Install the approved minimal WSL/Linux DV toolchain; no global Python packages.
set -Eeuo pipefail

readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly REPORT_DIR="$WORKSPACE/reports/environment"
readonly VENV="$WORKSPACE/.venv-dv"
mkdir -p -- "$REPORT_DIR"
exec > >(/usr/bin/tee "$REPORT_DIR/setup.log") 2>&1
trap 'rc=$?; printf "setup_exit_code=%s\n" "$rc"; exit "$rc"' EXIT

printf 'Workspace: %s\n' "$WORKSPACE"
printf 'Setup started (UTC): %s\n' "$(/usr/bin/date -u +%FT%TZ)"
[[ "$(/usr/bin/uname -s)" == Linux ]] || { echo 'ERROR: Run this script inside WSL/Linux.'; exit 2; }
for binary in /usr/bin/python3 /usr/bin/apt-get /usr/bin/sudo; do
    [[ -x "$binary" ]] || { printf 'ERROR: Required binary missing: %s\n' "$binary"; exit 2; }
done
if ! /usr/bin/sudo -n true 2>/dev/null; then
    echo 'ERROR: Noninteractive sudo is unavailable; no packages were installed.'
    exit 3
fi
echo 'Noninteractive sudo: available'

/usr/bin/sudo -n /usr/bin/apt-get update
/usr/bin/sudo -n /usr/bin/env DEBIAN_FRONTEND=noninteractive /usr/bin/apt-get install -y --no-install-recommends \
    iverilog gtkwave verilator python3-venv build-essential git

if [[ ! -e "$VENV" ]]; then
    /usr/bin/python3 -m venv --copies "$VENV"
fi
[[ -x "$VENV/bin/python" ]] || { echo 'ERROR: Existing .venv-dv is not a usable Linux virtual environment.'; exit 4; }
"$VENV/bin/python" -c 'import sys; assert sys.prefix != sys.base_prefix, "Not a virtual environment"'
"$VENV/bin/python" -m pip install --disable-pip-version-check -r "$WORKSPACE/config/requirements-dv.txt"
"$VENV/bin/python" -m pip check
"$VENV/bin/python" -m pip freeze > "$REPORT_DIR/pip-freeze.txt"
"$VENV/bin/python" "$WORKSPACE/dv/smoke/write_environment.py"
echo 'DV tools installed. Run bash scripts/run_smoke.sh to validate simulation.'
