"""Re-execute only read-only evidence functions, never finalize or a hardware tool."""
import ast
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import sys
import time

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[4]
OWN = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "work"))
import report_cycle_evidence_check as ev
import report_cycle_finalize as fin

started = time.monotonic()
scripts = {"work/" + filename: ev.sha(ROOT / "work" / filename) for filename in ("report_cycle_document_check.py", "report_cycle_evidence_check.py", "report_cycle_finalize.py")}
freeze_path = ROOT / "work/encoder_source_freeze.json"
freeze = ev.load(freeze_path)
frozen_before = {name: ev.sha(ROOT / name) for name in freeze["source_sha256"]}
ev.check_map(ROOT, freeze["source_sha256"])

evidence = ev.readback()
(OWN / "actual-evidence-readback.json").write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
quality = ev.load(ROOT / "reports/system/report-cycle/review-quality-all.json")
ev.check_map(ROOT, quality["artifacts_sha256"])
inventory_name = "reports/system/report-cycle/quality-readback/evidence-inputs.json"
assert ev.sha(ROOT / inventory_name) == quality["artifacts_sha256"][inventory_name]
inventory = ev.load(ROOT / inventory_name)
ev.check_map(ROOT, inventory)

tree = ast.parse((ROOT / "work/report_cycle_finalize.py").read_text(encoding="utf-8"))
finalize_def = next(node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name == "finalize")
check_calls = sorted([node for node in ast.walk(finalize_def) if isinstance(node, ast.Call) and isinstance(node.func, ast.Name) and node.func.id == "run_check"], key=lambda node: node.lineno)
commands = [dict(script=ast.literal_eval(node.args[0]), extra=ast.literal_eval(node.args[1]), log=ast.literal_eval(node.args[2]), line=node.lineno) for node in check_calls]
assert commands[-1]["script"] == "report_cycle_document_check.py" and commands[-1]["extra"] == []
assert all(command["script"] in ("report_cycle_evidence_check.py", "report_cycle_document_check.py") for command in commands)
assert len(check_calls) == 4
assert not any(isinstance(node, ast.Constant) and isinstance(node.value, str) and ".omx" in node.value for node in ast.walk(ast.parse((ROOT / "work/report_cycle_evidence_check.py").read_text(encoding="utf-8"))))
assert {name: ev.sha(ROOT / name) for name in freeze["source_sha256"]} == frozen_before
assert {name: ev.sha(ROOT / name) for name in scripts} == scripts
assert evidence["status"] == "PASS" and evidence["frozen_sources_checked"] == 192
assert evidence["formal_acceptance"] == "EXTERNAL_PENDING" and evidence["root_report_acceptance"] is False

result = dict(status="PASS", reviewer="cycle_checker_review", completed_utc=datetime.now(timezone.utc).isoformat(), elapsed_seconds=round(time.monotonic()-started, 3), files=scripts, frozen_files=192, frozen_bytes_changed=0, evidence_bound_files=evidence["unique_bound_files"], evidence_readback_sha256=ev.sha(OWN / "actual-evidence-readback.json"), quality_input_files=len(inventory), quality_inventory_sha256=ev.sha(ROOT / inventory_name), quality_artifacts_files=len(quality["artifacts_sha256"]), final_check_command=commands[-1], check_commands=commands, stable_baseline_only=True, finalizer_executed=False, simulation_commands_executed=0)
(OWN / "actual-readonly-readback.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps(result))
