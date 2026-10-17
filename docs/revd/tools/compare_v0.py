"""Optional: execute trusted, exact pinned numeric/fixedpoint.py from LOCAL KWT.

Requires its NumPy dependency. No download; fails closed on a different blob.
This utility was not used for the bundled software-check acceptance.
"""
from __future__ import annotations
import argparse
from dataclasses import asdict
import hashlib
import importlib.util
import json
from pathlib import Path
import random
import sys
from core_model import Geometry, candidate, finalize, make_case

BLOB = "116dfb84c51a6847cb10678c9e5a7230fb796598"


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--source", type=Path, required=True, help="Trusted local numeric/fixedpoint.py")
    p.add_argument("--out", type=Path, required=True, help="New output directory")
    p.add_argument("--full", action="store_true", help="Also compare one full synthetic matrix")
    args = p.parse_args()
    try:
        if args.out.exists():
            raise ValueError("output directory already exists")
        body = args.source.read_bytes()
        sha = hashlib.sha1(b"blob " + str(len(body)).encode() + b"\0" + body).hexdigest()
        if sha != BLOB:
            raise ValueError("V0 numeric blob differs; do not silently change the reference")
        spec = importlib.util.spec_from_file_location("pinned_kwt_numeric", args.source)
        if spec is None or spec.loader is None:
            raise ImportError("cannot create source loader")
        module = importlib.util.module_from_spec(spec)
        sys.modules[spec.name] = module
        spec.loader.exec_module(module)
        rng = random.Random(20261017)
        count = 0
        for shift in range(48):
            for _ in range(16):
                x = [rng.randint(-32768, 32767) for _ in range(64)]
                w = [rng.randint(-32768, 32767) for _ in range(64)]
                bias = rng.choice([-(2**47), 2**47 - 1, rng.randint(-(2**46), 2**46)])
                old = module.dot64_reference(x, w, bias, shift)
                new = finalize(sum(a * b for a, b in zip(x, w)), bias, shift)
                if (old.raw, old.output, old.overflow, old.output_saturated) != (new.raw, new.data, new.overflow, new.saturated):
                    raise ValueError(f"V0 numerical mismatch at vector {count}")
                count += 1
        words = 0
        if args.full:
            g = Geometry(); case = make_case(g, 20261017, 8)
            old = module.ffn1_reference(case["x"], case["w"], case["bias"], 8)
            output, _ = candidate(g, case["x"], case["w"], case["bias"], 8, "ctx4")
            for i, new in enumerate(output):
                r, c = divmod(i, g.n)
                if (int(old.raw[r, c]), int(old.output[r, c]), bool(old.overflow[r, c]), bool(old.output_saturated[r, c])) != (new.raw, new.data, new.overflow, new.saturated):
                    raise ValueError(f"V0 full-matrix mismatch at {i}")
                words += 1
        report = dict(status="V0_SOFTWARE_REFERENCE_COMPARISON_PASS", vectors=count,
                      full_matrix_outputs=words, source_sha256=hashlib.sha256(body).hexdigest(), git_blob=sha,
                      not_run=["OFFICIAL_MODEL_DATA", "RTL", "E203", "PPA"])
        args.out.mkdir(parents=True, exist_ok=False)
        (args.out / "compare_v0.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(report, indent=2)); return 0
    except (ValueError, OSError, ImportError, TypeError) as exc:
        print(f"FAIL: {exc}", file=sys.stderr); return 1

if __name__ == "__main__":
    raise SystemExit(main())
