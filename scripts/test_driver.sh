#!/usr/bin/env bash
set -euo pipefail
root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
out="$root/reports/system/driver"
mkdir -p "$out"
rm -f -- "$out/PASS"
printf '{"status":"RUNNING"}\n' > "$out/result.json"
trap 'rc=$?; printf "{\"status\":\"FAIL\",\"exit_code\":%s}\n" "$rc" > "$out/result.json"; exit "$rc"' ERR
: > "$out/commands.log"
run() {
    printf '%q ' "$@" >> "$out/commands.log"
    printf '\n' >> "$out/commands.log"
    "$@"
}
{
    date -u '+%Y-%m-%dT%H:%M:%SZ'
    gcc --version
    riscv64-unknown-elf-gcc --version
    riscv64-unknown-elf-objdump --version
    python3 --version
} > "$out/tool-versions.log"
flags=(-std=c11 -Wall -Wextra -Werror -Wpedantic -O2 -I"$root/sw")
run gcc "${flags[@]}" -fsanitize=undefined -fno-sanitize-recover=all \
    "$root/sw/ffn1_driver.c" "$root/tests/driver/test_driver.c" -o "$out/test_driver"
run "$out/test_driver" | tee "$out/host.log"
run python3 "$root/tests/driver/test_driver_mutations.py" | tee "$out/mutations.log"
run riscv64-unknown-elf-gcc "${flags[@]}" -ffreestanding -fno-builtin \
    -march=rv32imac -mabi=ilp32 -c "$root/sw/ffn1_driver.c" -o "$out/ffn1_driver.rv32.o"
run riscv64-unknown-elf-objdump -dr "$out/ffn1_driver.rv32.o" > "$out/ffn1_driver.rv32.dis"
if riscv64-unknown-elf-nm -u "$out/ffn1_driver.rv32.o" | grep -q .; then
    echo 'unexpected freestanding unresolved symbols' >&2
    riscv64-unknown-elf-nm -u "$out/ffn1_driver.rv32.o" >&2
    exit 1
fi
sha256sum "$root/sw/ffn1_driver.h" "$root/sw/ffn1_driver.c" \
    "$root/tests/driver/test_driver.c" "$root/tests/driver/test_driver_mutations.py" \
    "$root/scripts/test_driver.sh" "$out/ffn1_driver.rv32.o" > "$out/hashes.sha256"
run python3 - "$out" <<'PY'
import json
from pathlib import Path
import re
import sys
out = Path(sys.argv[1])
match = re.fullmatch(r"DRIVER_TESTS=(\d+) FAILURES=0\n", (out / "host.log").read_text())
mutations = json.loads((out / "mutations.json").read_text())
if not match or mutations["status"] != "PASS" or not mutations["mutation_count"]:
    raise SystemExit("missing or invalid fresh driver evidence")
(out / "result.json").write_text(json.dumps({
    "status": "PASS", "exit_code": 0, "host_test_cases": int(match.group(1)),
    "undefined_behavior_sanitizer": True,
    "mutations_killed": mutations["mutation_count"],
    "rv32": {"march": "rv32imac", "mabi": "ilp32", "freestanding": True,
             "unresolved_symbols": []},
    "commands": "commands.log", "versions": "tool-versions.log", "hashes": "hashes.sha256",
}, indent=2) + "\n")
PY
printf 'DRIVER_HOST_AND_RV32_PASS\n' > "$out/PASS"
