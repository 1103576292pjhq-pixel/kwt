"""Check the two isolated local runtimes; this is not RTL/SoC/PPA acceptance."""
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import subprocess
import sys


class CheckError(RuntimeError):
    pass


def normalize(name):
    return re.sub(r"[-_.]+", "-", name).lower()


def read_lock(path):
    versions = {}
    for line in path.read_text(encoding="utf-8-sig").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        match = re.fullmatch(r"([A-Za-z0-9_.-]+)==([^\s=<>!]+)", line)
        if not match:
            raise CheckError("Expected a name==version dependency: " + line)
        name, version = normalize(match[1]), match[2]
        if name in versions and versions[name] != version:
            raise CheckError("Conflicting dependency pin: " + name)
        versions[name] = version
    if not versions:
        raise CheckError("Empty dependency lock: " + str(path))
    return versions


def compare_versions(expected, actual):
    actual = {normalize(name): version for name, version in actual.items()}
    for name, version in expected.items():
        installed = actual.get(normalize(name), "MISSING")
        if installed != version:
            raise CheckError("{}: expected {}, installed {}".format(name, version, installed))


def safe_path(base, relative):
    path = (base / relative).resolve()
    try:
        path.relative_to(base.resolve())
    except ValueError:
        raise CheckError("Manifest path outside expected directory: " + str(relative))
    return path


def verify_files(base, entries, path_key):
    if not isinstance(entries, list) or not entries:
        raise CheckError("Manifest file list is empty or invalid")
    seen = set()
    for entry in entries:
        path = safe_path(base, entry[path_key])
        if path in seen:
            raise CheckError("Duplicate manifest file: " + str(path))
        seen.add(path)
        if not path.is_file():
            raise CheckError("Missing manifest file: " + str(path))
        if hashlib.sha256(path.read_bytes()).hexdigest() != entry["sha256"]:
            raise CheckError("SHA-256 mismatch: " + str(path))
    return len(entries)


def run_command(command):
    print("$ " + " ".join(str(value) for value in command), flush=True)
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            text=True, encoding="utf-8", errors="replace", timeout=120,
                            env=dict(os.environ, CUDA_VISIBLE_DEVICES="-1", TF_CPP_MIN_LOG_LEVEL="2"))
    print(result.stdout.rstrip(), flush=True)
    if result.returncode:
        raise CheckError("Command failed with exit {}: {}".format(result.returncode, command[0]))
    return result.stdout


PROBE = r'''
import importlib.metadata as metadata
import io
import json
from pathlib import Path
import platform
import re
import sys
import sysconfig
import numpy as np

def installed_packages():
    # Imports may add setuptools/_vendor to sys.path. Those bundled metadata
    # directories are not packages installed into this virtual environment.
    roots = list(dict.fromkeys(str(Path(sysconfig.get_path(key)).resolve())
                               for key in ("purelib", "platlib")))
    versions = {}
    for dist in metadata.distributions(path=roots):
        name = dist.metadata["Name"]
        if not name:
            raise RuntimeError("Installed package metadata has no Name")
        key = re.sub(r"[-_.]+", "-", name).lower()
        if key in versions:
            raise RuntimeError("Duplicate installed package metadata: " + key)
        versions[key] = dist.version
    return versions

imported_versions = {"numpy": np.__version__}
imported_module_paths = {"numpy": np.__file__}
if sys.argv[1] == "dv":
    import cocotb
    import pytest
    imported_versions.update(cocotb=cocotb.__version__, pytest=pytest.__version__)
    imported_module_paths.update(cocotb=cocotb.__file__, pytest=pytest.__file__)
    x = np.array([[1, 2], [3, 4]], dtype=np.int64)
    y = x @ np.array([[5], [6]], dtype=np.int64)
    np.testing.assert_array_equal(y, [[17], [39]])
    buffer = io.BytesIO()
    np.save(buffer, y, allow_pickle=False)
    buffer.seek(0)
    np.testing.assert_array_equal(np.load(buffer, allow_pickle=False), y)
else:
    import tensorflow as tf
    import tensorflow_addons as tfa
    imported_versions.update({"tensorflow": tf.__version__, "tensorflow-addons": tfa.__version__})
    imported_module_paths.update({"tensorflow": tf.__file__, "tensorflow-addons": tfa.__file__})
versions = installed_packages()
print("READINESS_PROBE=" + json.dumps({"python": platform.python_version(),
    "executable": sys.executable, "prefix": sys.prefix,
    "isolated": sys.prefix != sys.base_prefix, "packages": versions,
    "metadata_roots": list(dict.fromkeys(str(Path(sysconfig.get_path(key)).resolve())
                                         for key in ("purelib", "platlib"))),
    "imported_versions": imported_versions, "imported_module_paths": imported_module_paths,
    "numpy_matrix_and_npy_roundtrip": sys.argv[1] == "dv"}))
'''


def check_venv(root, kind):
    # Resolve the project directory link, not bin/python's interpreter symlink:
    # resolving the executable would bypass the venv and use base packages.
    directory = (root / (".venv-" + kind)).resolve()
    python = directory / "bin" / "python"
    if not python.is_file() or not os.access(python, os.X_OK):
        raise CheckError("Missing executable .venv-{}: {}".format(kind, python))
    lock_name = "requirements-dv.txt" if kind == "dv" else "requirements-model.lock.txt"
    lock = root / "config" / lock_name
    expected = read_lock(lock)
    pins = ({"cocotb": "2.0.1", "pytest": "8.4.2", "numpy": "2.4.6"} if kind == "dv"
            else {"tensorflow": "2.4.0", "tensorflow-addons": "0.12.1", "numpy": "1.19.5"})
    compare_versions(pins, expected)
    output = run_command([str(python), "-c", PROBE, kind])
    records = [line.removeprefix("READINESS_PROBE=") for line in output.splitlines()
               if line.startswith("READINESS_PROBE=")]
    if len(records) != 1:
        raise CheckError("Missing or ambiguous runtime probe: " + kind)
    info = json.loads(records[0])
    minor = "3.12." if kind == "dv" else "3.8."
    if not info["python"].startswith(minor) or not info["isolated"]:
        raise CheckError("Wrong Python or non-isolated venv: " + kind)
    compare_versions(expected, info["packages"])
    compare_versions(info["imported_versions"], info["packages"])
    if kind == "dv":
        run_command([str(python), "-m", "pip", "check"])
    else:
        candidates = [root / "tools/uv-package/uv-0.13.0.data/scripts/uv",
                      root / ".venv-bootstrap/bin/uv"]
        uv = next((path for path in candidates if path.is_file() and os.access(path, os.X_OK)), None)
        if uv is None:
            raise CheckError("Missing project uv executable for model dependency check")
        run_command([str(uv), "pip", "check", "--python", str(python)])
    info.update(lock=str(lock.relative_to(root)), checked_pins=len(expected), dependency_check="PASS")
    return info


def check_tools():
    tools = {}
    for name in ("python3", "gcc", "g++", "make", "git", "iverilog", "vvp",
                 "verilator", "gtkwave", "fst2vcd"):
        path = Path("/usr/bin") / name
        if not path.is_file() or not os.access(path, os.X_OK):
            raise CheckError("Missing required /usr/bin tool: " + name)
        flag = "-V" if name in ("iverilog", "vvp") else "--version"
        if name == "fst2vcd":
            run_command([str(path), "--help"])
            output = run_command(["/usr/bin/dpkg-query", "-W", "-f=${Version}", "gtkwave"])
            version = "GTKWave package " + output.strip()
        else:
            output = run_command([str(path), flag])
            version = next((line.strip() for line in output.splitlines() if line.strip()), "")
        if not version:
            raise CheckError("No version output: " + name)
        tools[name] = {"path": str(path), "version": version}
    return tools


def read_json(path):
    value = json.loads(path.read_text(encoding="utf-8-sig"))
    if not isinstance(value, dict) or not value:
        raise CheckError("Expected non-empty JSON object: " + str(path))
    return value


def execute_checks(root, report):
    report["dv"] = check_venv(root, "dv")
    report["model"] = check_venv(root, "model")
    if platform.system() != "Linux":
        raise CheckError("Run this entry inside the configured WSL/Linux environment")
    report["platform"] = {"system": platform.system(), "kernel": platform.release(),
                          "wsl": "microsoft" in platform.release().lower()}
    report["tools"] = check_tools()
    source = read_json(root / "config/source-manifest.json")
    snapshot = safe_path(root, source["snapshot"])
    source_count = verify_files(snapshot, source["files"], "path")
    if source_count != 124:
        raise CheckError("Expected 124 pinned official source files, got " + str(source_count))
    data_root = root / "data/speech_commands_subset"
    data = read_json(data_root / "manifest.json")
    report["integrity"] = {"source_files": source_count,
                           "source_commit": source["commit"],
                           "real_wav_files": verify_files(data_root, data["samples"], "relative_path")}
    read_json(root / "config/model-contract.json")
    report["integrity"]["model_contract"] = "readable"


def main(root=None):
    root = Path(root) if root is not None else Path(__file__).resolve().parents[1]
    path = root / "reports/environment/readiness.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    report = {"schema_version": 1, "status": "RUNNING", "workspace": str(root),
              "started_at_utc": datetime.now(timezone.utc).isoformat(),
              "scope": "local module development environment; not RTL, SoC or PPA acceptance",
              "primary_simulator": "Icarus Verilog", "verilator_role": "lint only",
              "future_external_inputs": ["organizer E203 platform", "matching RISC-V toolchain",
                                         "specified SRAM models", "backend synthesis libraries/licenses"],
              "optional_scope": {"graduate_encoder_extension": "reserved; not implemented or accepted"}}
    path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    try:
        execute_checks(root, report)
        report.update(status="PASS", exit_code=0)
    except (Exception, KeyboardInterrupt) as error:
        report.update(status="FAIL", exit_code=1, error=str(error))
        print("ERROR: " + str(error), flush=True)
    report["completed_at_utc"] = datetime.now(timezone.utc).isoformat()
    path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("Environment readiness: " + report["status"], flush=True)
    return report["exit_code"]


if __name__ == "__main__":
    sys.exit(main())
