"""Software-only gate rejection tests using copies of a real RTL run."""
import copy
import importlib.util
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location("revd_gate",ROOT/"scripts/revd_trial_gate.py")
gate=importlib.util.module_from_spec(spec);spec.loader.exec_module(gate)

class GateTests(unittest.TestCase):
    def setUp(self):
        fixture=Path(os.environ["KWT_GATE_FIXTURE"])
        base=ROOT/"reports/revd/gate/tests";base.mkdir(parents=True,exist_ok=True)
        self.out=Path(tempfile.mkdtemp(prefix="negative-",dir=base))
        self.path=self.out/"run_manifest.json"
        for p in fixture.parent.iterdir():
            if p.is_file(): shutil.copy2(p,self.out/p.name)
        self.manifest=json.loads(self.path.read_text())
        before=fixture.parent.relative_to(ROOT).as_posix();after=self.out.relative_to(ROOT).as_posix()
        for command in self.manifest["commands"]:
            command["argv"]=[arg.replace(before,after) for arg in command["argv"]]
            command["log"]=command["log"].replace(before,after)
        self.save()
    def save(self): self.path.write_text(json.dumps(self.manifest),encoding="utf-8")
    def reject(self):
        self.save()
        with self.assertRaises((ValueError,OSError,KeyError)): gate.validate_case(self.path)
    def test_positive(self): gate.validate_case(self.path)
    def test_failed_subprocess(self): self.manifest["commands"][-1]["exit_code"]=1;self.reject()
    def test_timeout(self): self.manifest["commands"][-1]["exit_code"]=124;self.reject()
    def test_skip(self): self.manifest["status"]="SKIP";self.reject()
    def test_missing_output(self): (self.out/"output.hex").unlink();self.reject()
    def test_unknown(self):
        p=self.out/"output.hex";p.write_text(p.read_text().replace(" "," x",1));self.reject()
    def test_duplicate(self):
        p=self.out/"output.hex";s=p.read_text().splitlines();s[1]=s[0];p.write_text("\n".join(s)+"\n");self.reject()
    def test_missing_result(self):
        p=self.out/"output.hex";p.write_text("\n".join(p.read_text().splitlines()[:-1])+"\n");self.reject()
    def test_changed_source(self):
        key=next(iter(self.manifest["source_sha256"]));self.manifest["source_sha256"][key]="0"*64;self.reject()
    def test_changed_input(self):
        p=self.out/"X.npy";a=np.load(p);a[0,0]^=1;np.save(p,a,allow_pickle=False);self.reject()
    def test_missing_evidence(self):
        self.manifest.pop("commands");self.reject()
    def test_incomplete_source_inventory(self):
        self.manifest["source_sha256"]={"numeric/fixedpoint.py":self.manifest["source_sha256"]["numeric/fixedpoint.py"]};self.reject()
    def test_fake_compile(self):
        self.manifest["commands"][0]["argv"]=["iverilog","--help"];self.reject()
    def test_fake_latency(self): self.manifest["read_latency"]=2;self.reject()
    def test_fake_counters(self): self.manifest["counters"]["effective_macs"]=-1;self.reject()
    def test_missing_bank_stats(self):
        p=self.out/"stats.txt";p.write_text("\n".join(line for line in p.read_text().splitlines() if not line.startswith(("X ","W ")))+"\n")
        self.manifest["output_sha256"]["stats.txt"]=gate.sha(p);self.reject()
    def test_missing_terminal_boundary_case(self):
        protocol=json.loads(Path(os.environ["KWT_PROTOCOL_FIXTURE"]).read_text())
        gate.check_protocol_coverage(protocol)
        for omitted in [t["name"] for t in protocol["tests"] if t["name"].startswith(("last_fire_invalid_","pending_last_","next_begin_boundary_"))]:
            with self.subTest(omitted=omitted):
                changed=copy.deepcopy(protocol);changed["tests"]=[t for t in changed["tests"] if t["name"]!=omitted]
                with self.assertRaisesRegex(ValueError,"protocol cases missing"): gate.check_protocol_coverage(changed)
    def test_missing_gate_negative_sources(self):
        receipt=json.loads(Path(os.environ["KWT_GATE_NEGATIVE_FIXTURE"]).read_text());receipt.pop("source_sha256")
        with self.assertRaises((ValueError,KeyError)): gate.check_gate_negative(receipt)
    def test_stale_gate_negative_sources(self):
        receipt=json.loads(Path(os.environ["KWT_GATE_NEGATIVE_FIXTURE"]).read_text());receipt["source_sha256"]={k:"0"*64 for k in receipt["source_sha256"]}
        with self.assertRaises((ValueError,KeyError)): gate.check_gate_negative(receipt)
    def test_missing_gate_negative_command(self):
        receipt=json.loads(Path(os.environ["KWT_GATE_NEGATIVE_FIXTURE"]).read_text());receipt.pop("command")
        receipt["source_sha256"]={p:gate.sha(ROOT/p) for p in receipt["source_sha256"]}
        with self.assertRaises((ValueError,KeyError)): gate.check_gate_negative(receipt)
    def test_wrong_gate_negative_command(self):
        receipt=json.loads(Path(os.environ["KWT_GATE_NEGATIVE_FIXTURE"]).read_text())
        receipt["source_sha256"]={p:gate.sha(ROOT/p) for p in receipt["source_sha256"]}
        receipt["command"]["argv"][-1]="dv/revd/d1_runner.py"
        with self.assertRaisesRegex(ValueError,"not a gate test execution"): gate.check_gate_negative(receipt)
    def test_missing_terminal_omission_execution(self):
        receipt=json.loads(Path(os.environ["KWT_GATE_NEGATIVE_FIXTURE"]).read_text())
        receipt["source_sha256"]={p:gate.sha(ROOT/p) for p in receipt["source_sha256"]}
        log=self.out/"gate_negative.log";log.write_text((ROOT/receipt["log"]).read_text().replace("test_missing_terminal_boundary_case ","test_old_boundary_case "),encoding="utf-8")
        receipt["log"]=receipt["command"]["log"]=str(log.relative_to(ROOT))
        receipt["log_sha256"]=receipt["command"]["log_sha256"]=gate.sha(log)
        with self.assertRaisesRegex(ValueError,"terminal omission negative was not executed"): gate.check_gate_negative(receipt)

if __name__=="__main__": unittest.main(verbosity=2)
