"""Independent read-only recheck of fixed evidence-gate findings."""
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


def read(p):
    return json.loads(Path(p).read_text(encoding="utf-8-sig"))


spec = importlib.util.spec_from_file_location("rechecked_revd_gate", ROOT / "scripts/revd_trial_gate.py")
gate = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)
sources = ["scripts/revd_trial_gate.py", "dv/revd/gate_test.py", "dv/revd/d2_runner.py",
           "dv/revd/d2_protocol.py", "dv/revd/core_tb.sv"]
source_sha256 = {s: sha(ROOT / s) for s in sources}
fixture = None
for candidate in sorted((ROOT / "reports/revd/d2/full36").rglob("run_manifest.json"), key=lambda p: p.stat().st_mtime, reverse=True):
    r = read(candidate)
    if r.get("status") == "PASS" and r.get("read_latency") == 1 and all(sha(ROOT / p) == h for p, h in r["source_sha256"].items()):
        fixture = candidate
        break
if fixture is None:
    raise RuntimeError("No current-source real full36 fixture")

results = []
def probe(label, mutate, should_accept):
    folder = OUT / label
    folder.mkdir(exist_ok=False)
    for p in fixture.parent.iterdir():
        if p.is_file():
            shutil.copy2(p, folder / p.name)
    path = folder / "run_manifest.json"
    r = read(path)
    before = fixture.parent.relative_to(ROOT).as_posix()
    after = folder.relative_to(ROOT).as_posix()
    for command in r["commands"]:
        command["argv"] = [arg.replace(before, after) for arg in command["argv"]]
        command["log"] = command["log"].replace(before, after)
    mutate(r, folder)
    path.write_text(json.dumps(r, indent=2) + "\n", encoding="utf-8")
    try:
        gate.validate_case(path)
    except Exception as e:
        accepted = False
        error = repr(e)
    else:
        accepted = True
        error = None
    results.append({"name": label, "accepted": accepted, "expected_accept": should_accept,
                    "passed": accepted == should_accept, "error": error})


probe("positive_current_real_run", lambda r, p: None, True)
probe("incomplete_source_inventory", lambda r, p: r.update(source_sha256={"numeric/fixedpoint.py": sha(ROOT / "numeric/fixedpoint.py")}), False)
probe("read_latency_metadata_mismatch", lambda r, p: r.update(read_latency=2), False)
probe("compiler_argv_not_bound", lambda r, p: r["commands"][0].update(argv=["iverilog", "--help"]), False)
probe("counter_receipt_unbound", lambda r, p: r.update(counters={"effective_macs": -1}, banks={}), False)
def remove_banks(r, p):
    target = p / "stats.txt"
    target.write_text("\n".join(line for line in target.read_text().splitlines() if not line.startswith(("X ", "W "))) + "\n", encoding="utf-8")
    r["output_sha256"]["stats.txt"] = sha(target)
probe("missing_actual_bank_ce_evidence", remove_banks, False)

# Recheck the positive D1 manifest including all expected functional failures.
d1_paths = sorted((ROOT / "reports/revd/d1/green").rglob("run_manifest.json"), key=lambda p: p.stat().st_mtime, reverse=True)
d1_path = next(p for p in d1_paths if read(p).get("passed") and read(p).get("mutations_passed"))
d1 = read(d1_path)
positive_commands = [r for r in d1["commands"] if not any("/mutant_" in str(arg) for arg in r["command"])]
gate.check_commands(positive_commands)
mutation_checks = []
for mutation in d1["mutations"]:
    compilations = [c for c in d1["commands"] if str(c.get("log", "")).endswith("mutant_" + mutation["name"] + "_compile.log")]
    simulations = [c for c in d1["commands"] if str(c.get("log", "")).endswith("mutant_" + mutation["name"] + "_simulate.log")]
    gate.check_commands(compilations)
    mutation_checks.append({"name": mutation["name"], "passed": mutation["detected"] is True and mutation["compile_exit_code"] == 0 and mutation["simulate_exit_code"] == 1 and len(simulations) == 1 and simulations[0]["exit_code"] == 1 and mutation["expected_failure"] in (ROOT / simulations[0]["log"]).read_text()})

# Validate current protocol producer identity and every ordinary directed run.
protocol_path = ROOT / "reports/revd/d2/protocol/20261017-131233-b945ed/summary.json"
protocol = read(protocol_path)
gate.check_hashes(protocol["source_sha256"])
protocol_checks = []
for test in protocol["tests"]:
    path = ROOT / test["manifest"]
    if test.get("mutation_detected"):
        run = read(path)
        gate.check_commands(run["commands"])
        gate.check_hashes(run["source_sha256"])
        try:
            gate.check_output(path.parent / "output.hex", read(path.parent / "expected.json"))
        except ValueError:
            passed = True
        else:
            passed = False
    else:
        gate.validate_case(path, dense=False)
        passed = True
    protocol_checks.append({"name": test["name"], "passed": passed})

gate_receipt_path = ROOT / "reports/revd/gate/green/20261017-02/receipt.json"
gate_receipt = read(gate_receipt_path)
log = (ROOT / gate_receipt["log"]).read_text()
gate_regression = gate_receipt["exit_code"] == 0 and gate_receipt["negative_tests"] == 15 and sha(ROOT / gate_receipt["log"]) == gate_receipt["log_sha256"] and "Ran 16 tests" in log and "\nOK\n" in log and "FAILED" not in log and "SKIP" not in log
unchanged = all(sha(ROOT / p) == h for p, h in source_sha256.items())
passed = all(x["passed"] for x in results + mutation_checks + protocol_checks) and gate_regression and unchanged
report = {"status": "PASS" if passed else "FAIL", "scope": "INDEPENDENT_READ_ONLY_QUALITY_RECHECK",
          "blocking_findings": [], "source_sha256": source_sha256,
          "checked_scope": ["Current source identities for trial gate, gate rejection tests, D2 runner/protocol producer and public-stream TB", "Five previously accepted bad-evidence variants rejected using independent copies of a real current-source full36 RTL run; positive control accepted", "D1 positive subprocesses and four compile0/simulate1 functional RTL mutations with exact expected reasons", "All16 current directed protocol results including six reset phase/latency cases and two real RTL mutations", "Existing true gate RED5-to-GREEN16 regression evidence and log hash", "Static checks of exact source/input/output inventories, full compiler/simulator argument binding, actual per-bank CE and counter receipt reconciliation, small geometry set and production read-latency profiles"],
          "fixture": fixture.relative_to(ROOT).as_posix(), "fixture_sha256": sha(fixture),
          "gate_probes": results, "d1_manifest": d1_path.relative_to(ROOT).as_posix(),
          "d1_mutations": mutation_checks, "protocol_manifest": protocol_path.relative_to(ROOT).as_posix(),
          "protocol_checks": protocol_checks, "gate_regression_receipt": gate_receipt_path.relative_to(ROOT).as_posix(),
          "gate_regression_passed": gate_regression, "source_unchanged_during_review": unchanged,
          "implementation_modified": False, "status_modified": False, "parent_accepted": False,
          "official_contest_acceptance": False,
          "limits": ["Quality review does not run or grant the final aggregate gate; root assembles and validates complete bundle", "No new RTL simulation claimed by the review; inspected real RTL results and independently executed gate rejection probes"]}
if not passed:
    report["blocking_findings"] = [{"id": "RECHECK_FAILED", "details": [x for x in results + mutation_checks + protocol_checks if not x["passed"]], "gate_regression": gate_regression, "source_unchanged": unchanged}]
(OUT / "review.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
