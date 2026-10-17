"""Independent review probes against copies; no design/source/status writes."""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import sys

sys.dont_write_bytecode = True
ROOT = Path(r"D:\github\kwt")
OUT = Path(__file__).resolve().parent


def sha(p):
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()


spec = importlib.util.spec_from_file_location("reviewed_revd_gate", ROOT / "scripts/revd_trial_gate.py")
gate = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)
sources = ["scripts/revd_trial_gate.py", "dv/revd/gate_test.py", "dv/revd/d2_runner.py",
           "dv/revd/d2_protocol.py", "dv/revd/core_tb.sv"]
start_hashes = {s: sha(ROOT / s) for s in sources}
fixture = None
for candidate in sorted((ROOT / "reports/revd/d2").rglob("run_manifest.json"), key=lambda p: p.stat().st_mtime, reverse=True):
    obj = json.loads(candidate.read_text(encoding="utf-8"))
    if obj.get("status") != "PASS" or obj.get("mutation") is not None or obj.get("expected_tasks") != 1:
        continue
    if all(sha(ROOT / p) == value for p, value in obj["source_sha256"].items()):
        fixture = candidate
        break
if fixture is None:
    raise RuntimeError("No current-source PASS fixture; no stale fixture is substituted")

results = []
def probe(label, mutate):
    folder = OUT / label
    folder.mkdir(exist_ok=False)
    for p in fixture.parent.iterdir():
        if p.is_file() and p.suffix != ".vvp":
            shutil.copy2(p, folder / p.name)
    path = folder / "run_manifest.json"
    manifest = json.loads(path.read_text(encoding="utf-8"))
    mutate(manifest, folder)
    path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    try:
        gate.validate_case(path)
    except Exception as e:
        results.append({"name": label, "accepted": False, "error": repr(e)})
    else:
        results.append({"name": label, "accepted": True})

probe("positive_current_real_run", lambda r, p: None)
probe("incomplete_source_inventory", lambda r, p: r.update(source_sha256={"numeric/fixedpoint.py": sha(ROOT / "numeric/fixedpoint.py")}))
probe("read_latency_metadata_mismatch", lambda r, p: r.update(read_latency=2 if r["read_latency"] == 1 else 1))
probe("compiler_argv_not_bound", lambda r, p: r["commands"][0].update(argv=["iverilog", "--help"]))
probe("counter_receipt_unbound", lambda r, p: r.update(counters={"effective_macs": -1}, banks={}))
def remove_banks(r, p):
    target = p / "stats.txt"
    target.write_text("\n".join(line for line in target.read_text().splitlines() if not line.startswith(("X ", "W "))) + "\n", encoding="utf-8")
    r["output_sha256"]["stats.txt"] = sha(target)
probe("missing_actual_bank_ce_evidence", remove_banks)

end_hashes = {s: sha(ROOT / s) for s in sources}
report = {"fixture": fixture.relative_to(ROOT).as_posix(), "fixture_sha256": sha(fixture),
          "source_sha256": start_hashes, "source_unchanged_during_probes": start_hashes == end_hashes,
          "kind": "SOFTWARE_GATE_REJECTION_PROBES_ON_COPIES_OF_REAL_RTL_RUN_NOT_RTL_MUTATIONS",
          "results": results}
(OUT / "probe_result.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
