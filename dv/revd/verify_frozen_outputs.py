"""Compare public RTL records directly with frozen Yq/flags, without recomputing GEMM."""
import argparse
import hashlib
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from numeric.artifacts import load_array


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--summary", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    if args.out.exists():
        parser.error("refusing existing output")
    frozen_path = ROOT / "reports/prototype/vectors/manifest.json"
    frozen = json.loads(frozen_path.read_text())
    lookup = {c["case_id"].replace("/", "_"): c for c in frozen["cases"]}
    summary = json.loads(args.summary.read_text())
    assert summary["status"] == "PASS" and len(summary["cases"]) == 36
    assert {c["case"] for c in summary["cases"]} == set(lookup)
    results = []
    for entry in summary["cases"]:
        source = lookup[entry["case"]]
        arrays = {
            name: load_array(frozen_path.parent, source["arrays"][name], (99, 256), dtype).reshape(-1)
            for name, dtype in (("Yq", "int32"), ("overflow", "bool"), ("output_saturated", "bool"))
        }
        manifest_path = ROOT / entry["path"]
        manifest = json.loads(manifest_path.read_text())
        output = manifest_path.parent / "output.hex"
        lines = output.read_text().splitlines()
        assert len(lines) == 25344
        seen = set()
        for line in lines:
            fields = line.split()
            assert len(fields) == 6
            task, index, value = [int(x, 16) for x in fields[:3]]
            overflow, saturated, last = [int(x) for x in fields[3:]]
            if value >= 1 << 31:
                value -= 1 << 32
            assert task == manifest["task"] and index not in seen and 0 <= index < 25344
            seen.add(index)
            assert value == int(arrays["Yq"][index])
            assert overflow == int(arrays["overflow"][index])
            assert saturated == int(arrays["output_saturated"][index])
            assert last == int(index == 25343)
        results.append({"case": entry["case"], "outputs": len(lines), "output_sha256": sha(output),
                        "frozen_arrays": {name: source["arrays"][name]["sha256"] for name in arrays}})
    result = {"status": "PASS", "cases": results, "total_outputs": sum(c["outputs"] for c in results),
              "differences": 0, "fields": ["Y", "overflow", "saturated", "task", "index", "last"],
              "raw48_compared_at_D2": False, "official_contest_acceptance": False,
              "input_manifest_sha256": sha(frozen_path), "summary_sha256": sha(args.summary),
              "source_sha256": {str(p.relative_to(ROOT)): sha(p) for p in (Path(__file__), ROOT / "numeric/artifacts.py")}}
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print("FROZEN_OUTPUTS_MATCH", result["total_outputs"])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
