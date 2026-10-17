"""Calculate architecture counts. No timing/area/power claims."""
from __future__ import annotations
import argparse
import csv
import io
import json
from pathlib import Path
from core_model import Geometry, analytic

ROOT = Path(__file__).resolve().parents[1]


def calculate(path: Path) -> dict:
    obj = json.loads(path.read_text(encoding="utf-8"))
    return dict(config=path.stem, x_banks=obj.get("x_banks",obj["geometry"]["pm"]),
                ram_read_latency=obj["ram_read_latency"],
                x_prefetch=obj.get("x_prefetch","baseline"), **analytic(Geometry(**obj["geometry"]), obj["schedule"],
                                             obj["memory"], obj["w_slots"], obj["y_slots"]))


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--config", type=Path, help="One config; default is all production configs")
    p.add_argument("--out", type=Path, help="New output directory")
    args = p.parse_args()
    try:
        paths = [args.config] if args.config else sorted((ROOT / "configs").glob("p*.json"))
        data = [calculate(path) for path in paths]
        fields = ["config", "x_banks", "ram_read_latency", "mac_lanes", "ideal_issue_slots", "x_bank_reads", "w_bank_reads",
                  "operand_bank_reads", "accumulator_bytes", "snapshot_bytes", "w_bytes", "y_bytes"]
        text = io.StringIO(); writer = csv.DictWriter(text, fields, extrasaction="ignore")
        writer.writeheader(); writer.writerows(data)
        print(text.getvalue())
        if args.out:
            args.out.mkdir(parents=True, exist_ok=False)
            (args.out / "analysis.json").write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
            (args.out / "analysis.csv").write_text(text.getvalue(), encoding="utf-8", newline="")
        return 0
    except (ValueError, KeyError, OSError, TypeError) as exc:
        p.error(str(exc))
        return 2

if __name__ == "__main__":
    raise SystemExit(main())
