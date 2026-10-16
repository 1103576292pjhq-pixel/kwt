"""Check that realistic driver faults are rejected by the independent bus oracle."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "reports/system/driver"


def main() -> None:
    source = (ROOT / "sw/ffn1_driver.c").read_text(encoding="utf-8")
    original_hash = hashlib.sha256(source.encode()).hexdigest()
    mutations = [
        ("int16_missing_sign_extension", "lo = (uint32_t)(int32_t)words[address];",
         "lo = (uint32_t)(uint16_t)words[address];"),
        ("bias_high_word_stale", "(uint32_t)((bits >> 32) & UINT64_C(65535))",
         "UINT32_C(0)"),
        ("row_ack_wrong_index", "write_register(io, KWT1_REG_ROW_ACK, row)",
         "write_register(io, KWT1_REG_ROW_ACK, row + 1)"),
        ("invalid_flags_accepted",
         "if ((row_flags & ~UINT32_C(7)) != 0 || (row_flags & 4) == 0)",
         "if (row_flags == UINT32_MAX)"),
        ("transport_error_swallowed",
         "return io->write32(io->context, offset, value) == 0 ? KWT1_OK : KWT1_ERR_IO;",
         "(void)io->write32(io->context, offset, value); return KWT1_OK;"),
        ("negative_result_narrowed_incorrectly",
         "return value <= INT32_MAX ? (int32_t)value : -1 - (int32_t)(~value);",
         "return (int32_t)(value & INT32_MAX);"),
        ("timeout_one_extra_poll", "poll < limit;", "poll <= limit;"),
        ("final_sticky_error_ignored", "return check_error(io);", "return KWT1_OK;"),
    ]
    results = []
    with tempfile.TemporaryDirectory(prefix="kwt1-driver-mutants-") as directory:
        tmp = Path(directory)
        for name, before, after in mutations:
            if source.count(before) != 1:
                raise RuntimeError(f"ambiguous mutation {name}")
            mutant = tmp / f"{name}.c"
            binary = tmp / name
            mutant.write_text(source.replace(before, after), encoding="utf-8")
            command = ["gcc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-Wpedantic",
                       "-O2", f"-I{ROOT / 'sw'}", "-fsanitize=undefined",
                       "-fno-sanitize-recover=all", str(mutant),
                       str(ROOT / "tests/driver/test_driver.c"), "-o", str(binary)]
            built = subprocess.run(command, capture_output=True, text=True, check=False)
            if built.returncode:
                raise RuntimeError(f"mutant {name} must compile before rejection: {built.stderr}")
            result = subprocess.run([str(binary)], capture_output=True, timeout=10, check=False)
            if result.returncode != 1:
                raise RuntimeError(f"mutant {name} escaped or crashed: {result.returncode}")
            log = result.stdout + result.stderr
            (OUT / f"mutation-{name}.log").write_bytes(log)
            results.append({"name": name, "compile_exit": built.returncode,
                            "test_exit": result.returncode, "killed": True,
                            "log_sha256": hashlib.sha256(log).hexdigest()})
    if hashlib.sha256((ROOT / "sw/ffn1_driver.c").read_bytes()).hexdigest() != original_hash:
        raise RuntimeError("production source changed during mutation checks")
    (OUT / "mutations.json").write_text(json.dumps({
        "status": "PASS", "production_sha256": original_hash,
        "mutation_count": len(results), "results": results,
    }, indent=2) + "\n", encoding="utf-8")
    print(f"DRIVER_MUTATIONS={len(results)} KILLED={len(results)}")


if __name__ == "__main__":
    main()
