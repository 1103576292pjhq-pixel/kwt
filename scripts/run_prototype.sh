#!/usr/bin/env bash
# Entire local prototype acceptance. Runs from any working directory.
set -Eeuo pipefail
readonly WORKSPACE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
readonly PYTHON="$WORKSPACE/.venv-dv/bin/python"
readonly REPORT="$WORKSPACE/reports/prototype"
readonly STATUS="$WORKSPACE/work/prototype_status.json"
write_state() {
    printf '{"status":"%s","numeric":false,"dot64":false,"ffn1":false,"full_matrix_cases":0}\n' "$1" > "$STATUS.tmp"
    /usr/bin/mv -f -- "$STATUS.tmp" "$STATUS"
}
mkdir -p "$REPORT"
exec 9>"$REPORT/run.lock"
flock -n 9 || { echo 'Prototype acceptance already running; read reports/prototype/run.log'; exit 3; }
cd "$WORKSPACE"
write_state RUNNING
exec > >(tee "$REPORT/run.log") 2>&1
trap 'rc=$?; if (( rc != 0 )); then write_state FAILED; fi; printf "prototype_exit_code=%s\n" "$rc"; exit "$rc"' EXIT
"$PYTHON" scripts/prototype_gate.py begin
printf 'stage\texit_code\n' > "$REPORT/command-results.tsv"
stage() {
    local name="$1" code
    shift
    printf 'STAGE %s\n' "$name"
    if "$@"; then code=0; else code=$?; fi
    printf '%s\t%s\n' "$name" "$code" >> "$REPORT/command-results.tsv"
    return "$code"
}
if (( $# > 1 )) || { (( $# == 1 )) && [[ "$1" != '--reuse-verified' ]]; }; then
    echo 'Usage: bash scripts/run_prototype.sh [--reuse-verified]'
    exit 2
fi
stage preflight "$PYTHON" scripts/prototype_gate.py preflight
stage numeric-start "$PYTHON" scripts/prototype_gate.py unit-start --group numeric
stage numeric "$PYTHON" -m pytest tests/numeric -q --junitxml="$REPORT/integration-numeric.xml"
stage numeric-finish "$PYTHON" scripts/prototype_gate.py unit-finish --group numeric
stage gate-start "$PYTHON" scripts/prototype_gate.py unit-start --group gate
stage gate-tests "$PYTHON" -m pytest dv/ffn1/test_gate.py -q --junitxml="$REPORT/integration-gate.xml"
stage gate-finish "$PYTHON" scripts/prototype_gate.py unit-finish --group gate
stage dot64 bash scripts/run_dot64.sh
stage protocol "$PYTHON" dv/ffn1/run_ffn1.py --mode protocol
if [[ "${1:-}" == '--reuse-verified' ]]; then
    stage reuse-verified "$PYTHON" scripts/prototype_gate.py verify-existing
else
    stage full "$PYTHON" dv/ffn1/run_ffn1.py --mode full
    stage repeat "$PYTHON" dv/ffn1/run_ffn1.py --mode repeat
fi
stage lint "$PYTHON" scripts/prototype_gate.py lint
stage finalize "$PYTHON" scripts/prototype_gate.py finalize
echo 'READY_FOR_REVIEW: work/prototype_status.json'
