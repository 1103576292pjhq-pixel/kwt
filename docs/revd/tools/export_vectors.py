"""Create synthetic inputs and a SEPARATE reference file for component tests."""
import argparse
import hashlib
import json
from pathlib import Path
from core_model import Geometry, dense_reference, make_case, records


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--m", type=int, default=5)
    p.add_argument("--n", type=int, default=16)
    p.add_argument("--pm", type=int, default=4)
    p.add_argument("--shift", type=int, default=8)
    p.add_argument("--seed", type=int, default=20261017)
    p.add_argument("--task-id", type=int, default=1)
    p.add_argument("--out", required=True, type=Path)
    args = p.parse_args()
    try:
        g = Geometry(m=args.m, n=args.n, pm=args.pm)
        case = make_case(g, args.seed, args.shift)
        ref = dense_reference(g, case["x"], case["w"], case["bias"], args.shift)
        args.out.mkdir(parents=True, exist_ok=False)
        (args.out / "input.json").write_text(json.dumps(case) + "\n", encoding="utf-8")
        (args.out / "expected.jsonl").write_text("".join(json.dumps(r) + "\n" for r in records(g, ref, args.task_id)), encoding="utf-8")
        (args.out / "README.txt").write_text("Synthetic data only. input.json is the sole DUT stimulus. expected.jsonl stays outside the DUT and is not actual RTL output.\n", encoding="utf-8")
        hashes = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in args.out.iterdir() if p.is_file()}
        (args.out / "manifest.json").write_text(json.dumps({"kind": "SYNTHETIC_NOT_OFFICIAL", "sha256": hashes}, indent=2) + "\n", encoding="utf-8")
        print(f"Exported {g.m * g.n} expected outputs; NO RTL has run.")
        return 0
    except (ValueError, OSError) as exc:
        p.error(str(exc)); return 2

if __name__ == "__main__":
    raise SystemExit(main())
