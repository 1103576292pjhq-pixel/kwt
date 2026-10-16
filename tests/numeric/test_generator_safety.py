"""Output validation must happen before mkdir, STATUS or manifest writes."""
import importlib.util
from pathlib import Path
import sys

import pytest


def _entry_module():
    path = Path(__file__).resolve().parents[2] / "scripts/generate_prototype_vectors.py"
    spec = importlib.util.spec_from_file_location("prototype_vector_entry", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _snapshot(root):
    return {path.relative_to(root).as_posix(): ("file", path.read_bytes()) if path.is_file() else ("directory", None)
            for path in root.rglob("*")}


@pytest.mark.parametrize("relative", [
    "reports/model/baseline", "reports/model/repeat", "config", "vendor",
    "tools", "numeric", "scripts", "data", "reports/model", "reports", ".",
    "reports/model/baseline/new-child",
])
def test_protected_output_rejected_without_any_write(tmp_path, monkeypatch, relative):
    entry = _entry_module()
    workspace = tmp_path / "mock-workspace"
    for reserved in ["reports/model/baseline", "reports/model/repeat", "config", "vendor", "tools"]:
        directory = workspace / reserved
        directory.mkdir(parents=True, exist_ok=True)
        (directory / "manifest.json").write_text("immutable input marker", encoding="utf-8")
    original = _snapshot(workspace)
    monkeypatch.setattr(entry, "WORKSPACE", workspace)
    monkeypatch.setattr(sys, "argv", ["generate_prototype_vectors.py", "--output", str(workspace / relative)])
    with pytest.raises(SystemExit) as result:
        entry.main()
    assert result.value.code != 0
    assert _snapshot(workspace) == original
    assert not list(workspace.rglob("STATUS.json"))


def test_output_symlink_into_baseline_rejected_without_write(tmp_path, monkeypatch):
    entry = _entry_module()
    workspace = tmp_path / "workspace"
    baseline = workspace / "reports/model/baseline"
    baseline.mkdir(parents=True)
    (baseline / "manifest.json").write_text("immutable", encoding="utf-8")
    alias = tmp_path / "alias"
    try:
        alias.symlink_to(baseline, target_is_directory=True)
    except OSError:
        pytest.skip("host disallows directory symlink; Linux acceptance must run this test")
    before = _snapshot(workspace)
    monkeypatch.setattr(entry, "WORKSPACE", workspace)
    monkeypatch.setattr(sys, "argv", ["generate_prototype_vectors.py", "--output", str(alias)])
    with pytest.raises(SystemExit):
        entry.main()
    assert _snapshot(workspace) == before


def test_safe_output_paths_are_accepted_without_creation(tmp_path):
    from numeric.artifacts import validate_output_path
    workspace = tmp_path / "workspace"
    workspace.mkdir()
    for target in [workspace / "reports/prototype/vectors", tmp_path / "new-output"]:
        assert validate_output_path(workspace, target) == target.resolve()
        assert not target.exists()
