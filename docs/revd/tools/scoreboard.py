"""Strict JSONL comparison; use actual DUT records, never expected as input."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import sys
from core_model import Geometry, dense_reference, expected_indices


def verify(actual: list[dict], expected: list, g: Geometry, task_id: int) -> dict:
    if len(actual) != g.m * g.n:
        raise ValueError(f"expected {g.m * g.n} outputs, found {len(actual)}")
    order = expected_indices(g)
    seen = set()
    fields = {"task_id", "y_index", "data", "overflow", "saturated", "last"}
    for ordinal, item in enumerate(actual):
        if not isinstance(item, dict) or set(item) != fields:
            raise ValueError(f"record {ordinal}: schema mismatch")
        for name in ("task_id", "y_index", "data"):
            if type(item[name]) is not int:
                raise ValueError(f"record {ordinal}: {name} must be integer")
        for name in ("overflow", "saturated", "last"):
            if type(item[name]) is not bool:
                raise ValueError(f"record {ordinal}: {name} must be boolean")
        index = item["y_index"]
        if item["task_id"] != task_id or index in seen or not 0 <= index < len(expected):
            raise ValueError(f"record {ordinal}: task/duplicate/bounds error")
        if index != order[ordinal]:
            raise ValueError(f"record {ordinal}: wrong publication order")
        ref = expected[index]
        if (item["data"], item["overflow"], item["saturated"]) != (ref.data, ref.overflow, ref.saturated):
            raise ValueError(f"record {ordinal}, Y[{index}]: numeric/flags mismatch")
        if item["last"] != (ordinal == len(actual) - 1):
            raise ValueError(f"record {ordinal}: incorrect last marker")
        seen.add(index)
    return {"scope": "OUTPUT_FILE_COMPARISON_ONLY_NOT_PROOF_OF_EXECUTION",
            "outputs": len(seen), "mismatches": 0, "task_id": task_id}


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--case", required=True, type=Path)
    p.add_argument("--actual", required=True, type=Path)
    p.add_argument("--task-id", type=int, default=1)
    args = p.parse_args()
    try:
        case = json.loads(args.case.read_text(encoding="utf-8"))
        g = Geometry(**case["geometry"])
        expected = dense_reference(g, case["x"], case["w"], case["bias"], case["shift"])
        actual = [json.loads(line) for line in args.actual.read_text(encoding="utf-8").splitlines() if line.strip()]
        print(json.dumps(verify(actual, expected, g, args.task_id), ensure_ascii=False, indent=2))
        return 0
    except (ValueError, KeyError, OSError, TypeError) as exc:
        print(f"FAIL: {exc}", file=sys.stderr)
        return 1

if __name__ == "__main__":
    raise SystemExit(main())
