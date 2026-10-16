"""Failure-oriented checks for the local environment readiness report."""
import contextlib
import ast
import hashlib
import importlib.util
import importlib.metadata
import io
import json
from pathlib import Path
import re
import sys
import sysconfig
import tempfile
import unittest
from unittest import mock


SCRIPT = Path(__file__).resolve().parents[2] / "scripts" / "check_environment.py"
SPEC = importlib.util.spec_from_file_location("check_environment", SCRIPT)
checker = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(checker)


class EnvironmentChecks(unittest.TestCase):
    def metadata_probe(self, site, vendor):
        # Execute the actual collector from the interpreter probe. TensorFlow
        # itself need not be available to recreate setuptools' sys.path change.
        nodes = [node for node in ast.parse(checker.PROBE).body
                 if isinstance(node, ast.FunctionDef)
                 or (isinstance(node, ast.Assign)
                     and any(isinstance(target, ast.Name) and target.id == "versions"
                             for target in node.targets))]
        namespace = {"metadata": importlib.metadata, "sysconfig": sysconfig,
                     "Path": Path, "re": re}
        with mock.patch.object(sys, "path", [str(site), str(vendor)]):
            with mock.patch.object(sysconfig, "get_path", return_value=str(site)):
                exec(compile(ast.Module(body=nodes, type_ignores=[]), "<metadata-probe>", "exec"), namespace)
        return namespace["versions"]

    def write_distribution(self, root, directory, version):
        path = root / directory
        path.mkdir(parents=True)
        (path / "METADATA").write_text(
            "Metadata-Version: 2.1\nName: numpy\nVersion: " + version + "\n", encoding="utf-8")

    def test_vendored_metadata_does_not_override_installed_package(self):
        with tempfile.TemporaryDirectory() as directory:
            site = Path(directory) / "site-packages"
            vendor = site / "setuptools" / "_vendor"
            self.write_distribution(site, "numpy-2.4.6.dist-info", "2.4.6")
            self.write_distribution(vendor, "numpy-1.19.5.dist-info", "1.19.5")
            self.assertEqual(self.metadata_probe(site, vendor), {"numpy": "2.4.6"})

    def test_duplicate_real_install_metadata_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            site = Path(directory) / "site-packages"
            vendor = site / "setuptools" / "_vendor"
            vendor.mkdir(parents=True)
            self.write_distribution(site, "numpy-2.4.6.dist-info", "2.4.6")
            self.write_distribution(site, "numpy-1.19.5.dist-info", "1.19.5")
            with self.assertRaisesRegex(RuntimeError, "Duplicate installed package"):
                self.metadata_probe(site, vendor)

    def test_dependency_lock_must_match_actual_metadata(self):
        with self.assertRaisesRegex(checker.CheckError, "numpy.*2.4.6.*1.19.5"):
            checker.compare_versions({"numpy": "2.4.6"}, {"numpy": "1.19.5"})
        checker.compare_versions({"tensorflow-addons": "0.12.1"},
                                 {"tensorflow_addons": "0.12.1"})

    def test_lock_rejects_unpinned_or_conflicting_dependencies(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "requirements.txt"
            for contents in ("numpy>=2.4.6\n", "numpy==2.4.6\nnumpy==1.19.5\n"):
                path.write_text(contents, encoding="utf-8")
                with self.assertRaises(checker.CheckError):
                    checker.read_lock(path)

    def test_hash_check_reads_actual_bytes_and_rejects_path_escape(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "source.py").write_bytes(b"original")
            entries = [{"path": "source.py", "sha256": hashlib.sha256(b"original").hexdigest()}]
            self.assertEqual(checker.verify_files(root, entries, "path"), 1)
            (root / "source.py").write_bytes(b"modified")
            with self.assertRaisesRegex(checker.CheckError, "SHA-256"):
                checker.verify_files(root, entries, "path")
            with self.assertRaisesRegex(checker.CheckError, "outside"):
                checker.verify_files(root, [{"path": "../outside", "sha256": "0" * 64}], "path")

    def test_failed_command_is_not_accepted(self):
        with contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaisesRegex(checker.CheckError, "exit 7"):
                checker.run_command([sys.executable, "-c", "raise SystemExit(7)"])

    def test_missing_dv_replaces_stale_pass(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            report = root / "reports" / "environment" / "readiness.json"
            report.parent.mkdir(parents=True)
            report.write_text('{"status":"PASS"}', encoding="utf-8")
            with contextlib.redirect_stdout(io.StringIO()):
                code = checker.main(root)
            current = json.loads(report.read_text(encoding="utf-8"))
            self.assertNotEqual(code, 0)
            self.assertEqual(current["status"], "FAIL")
            self.assertIn(".venv-dv", current["error"])

    def test_probe_failure_invalidates_pass_before_checks_start(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            report = root / "reports" / "environment" / "readiness.json"
            report.parent.mkdir(parents=True)
            report.write_text('{"status":"PASS"}', encoding="utf-8")

            def broken_probe(_root, _report):
                self.assertEqual(json.loads(report.read_text(encoding="utf-8"))["status"], "RUNNING")
                raise checker.CheckError("subprocess failed")

            with mock.patch.object(checker, "execute_checks", side_effect=broken_probe):
                with contextlib.redirect_stdout(io.StringIO()):
                    self.assertEqual(checker.main(root), 1)
            self.assertEqual(json.loads(report.read_text(encoding="utf-8"))["status"], "FAIL")


if __name__ == "__main__":
    unittest.main()
