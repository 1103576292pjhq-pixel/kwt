"""Read-only audit of a LOCAL KWT checkout; never checkout/pull/install/run RTL."""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

BASE = "3d9d0fc77457b8869cbf525d826dafb114f2a8e1"
NUMERIC_BLOB = "116dfb84c51a6847cb10678c9e5a7230fb796598"
CHECK_FILES = ["numeric/fixedpoint.py", "rtl/dot64.sv", "rtl/ffn1_top.sv",
               "soc/e203_common/e203_cpu_shell.sv", "docs/platform/official-sources.md"]


def git(repo: Path, *args: str) -> str:
    return subprocess.run(["git", "-C", str(repo), *args], check=True,
                          capture_output=True, text=True, timeout=25).stdout.strip()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", required=True, type=Path)
    parser.add_argument("--out", required=True, type=Path, help="New directory outside the checkout")
    args = parser.parse_args()
    try:
        repo = args.repo.resolve(strict=True)
        out = args.out.resolve()
        if out == repo or repo in out.parents:
            raise ValueError("Audit output must be outside the checkout")
        head = git(repo, "rev-parse", "HEAD")
        actual_root = Path(git(repo, "rev-parse", "--show-toplevel")).resolve()
        if repo != actual_root:
            raise ValueError("--repo must be the repository root")
        files = {}
        for name in CHECK_FILES:
            body = (repo / name).read_bytes()
            blob = hashlib.sha1(b"blob " + str(len(body)).encode() + b"\0" + body).hexdigest()
            files[name] = {"sha256": hashlib.sha256(body).hexdigest(), "git_blob": blob}
        status = git(repo, "status", "--porcelain=v1", "--untracked-files=all")
        okay = head == BASE and files["numeric/fixedpoint.py"]["git_blob"] == NUMERIC_BLOB
        report = {"status": "BASELINE_ID_MATCH_REVIEW_DIRTY_FILES" if okay else "BASELINE_MISMATCH_STOP_AND_REVIEW",
                  "checked_utc": datetime.now(timezone.utc).isoformat(),
                  "head": head, "expected_head": BASE, "dirty_files": status,
                  "files": files, "tools_found": {n: shutil.which(n) for n in ("iverilog", "verilator", "git")},
                  "scope": "Read-only file identity check; NOT repository integrity or simulation acceptance"}
        out.mkdir(parents=True, exist_ok=False)
        (out / "preflight.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(report, ensure_ascii=False, indent=2))
        return 0 if okay else 1
    except (ValueError, OSError, subprocess.SubprocessError) as exc:
        print(f"FAIL: {exc}", file=sys.stderr)
        return 2

if __name__ == "__main__":
    raise SystemExit(main())
