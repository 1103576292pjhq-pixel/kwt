#!/usr/bin/env python3
"""Generate 36 full FFN1 integer vector sets; any failure invalidates old PASS."""
import argparse
from pathlib import Path
import sys
import traceback

WORKSPACE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(WORKSPACE))

from numeric.artifacts import generate_vectors, validate_output_path, verify_vectors, write_json


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=WORKSPACE / "reports/prototype/vectors")
    parser.add_argument("--verify-only", action="store_true")
    arguments = parser.parse_args()
    baseline = WORKSPACE / "reports/model/baseline"
    # Input protection must precede mkdir and every status/manifest write.
    try:
        output = validate_output_path(WORKSPACE, arguments.output)
    except ValueError as error:
        parser.error(str(error))
    output.mkdir(parents=True, exist_ok=True)
    write_json(output / "STATUS.json", {"status": "RUNNING"})
    if not arguments.verify_only:
        write_json(output / "manifest.json", {"status": "RUNNING", "schema_version": 1})
    try:
        if not arguments.verify_only:
            generate_vectors(WORKSPACE, baseline, output)
        verification = verify_vectors(WORKSPACE, baseline, output)
        write_json(output / "verification.json", verification)
        write_json(output / "STATUS.json", {"status": "PASS", "exit_code": 0})
        print(verification, flush=True)
    except Exception as error:
        write_json(output / "STATUS.json", {"status": "FAIL", "exit_code": 1, "error": str(error)})
        write_json(output / "manifest.json", {"status": "FAIL", "schema_version": 1, "error": str(error)})
        traceback.print_exc()
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
