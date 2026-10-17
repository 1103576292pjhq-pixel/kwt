import importlib.util
import json
from pathlib import Path
import sys
sys.dont_write_bytecode = True
root = Path(r"D:\github\kwt")
spec = importlib.util.spec_from_file_location("gate_review", root / "scripts/revd_trial_gate.py")
gate = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)
paths = sorted((root / "reports/revd/d1/green").rglob("run_manifest.json"), key=lambda p: p.stat().st_mtime, reverse=True)
path = next(path for path in paths if json.loads(path.read_text())["passed"])
manifest = json.loads(path.read_text())
commands = [c for c in manifest["commands"] if not any("mutation_" in str(a) for a in c["command"])]
result = {"fixture": path.relative_to(root).as_posix(), "nonzero_commands_remaining": [c for c in commands if c["exit_code"] != 0]}
try:
    gate.check_commands(commands)
except Exception as error:
    result.update(accepted=False, error=str(error))
else:
    result["accepted"] = True
(Path(__file__).parent / "d1_filter_probe.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps(result, indent=2))
